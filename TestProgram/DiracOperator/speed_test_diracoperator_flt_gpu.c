/*******************************************************************************
*
* Gauge covariance of the Dirac operator
*
*******************************************************************************/

#define MAIN_PROGRAM

#ifdef WITH_GPU


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "io.h"
#include "update.h"
#include "geometry.h"
#include "global.h"
#include "logger.h"
#include "random.h"
#include "memory.h"
#include "dirac.h"
#include "linear_algebra.h"
#include "representation.h"
#include "communications_flt.h"

static double hmass=0.1;
static suNg_field_flt *g;

double sfdiff (spinor_field_flt* sf){
  spinor_field *tmp;
  double res;
  tmp=alloc_spinor_field_f(2, &glattice);
  assign_s2sd_cpu(&tmp[0], sf);
  spinor_field_copy_from_gpu_f_flt(sf);
  assign_s2sd_cpu(&tmp[1], sf);
  spinor_field_sub_f_cpu(&tmp[0],&tmp[0],&tmp[1]);
  res= spinor_field_sqnorm_f_cpu(&tmp[0]);
  free_spinor_field_f(tmp);
  return res;
}



static void D(spinor_field_flt *out, spinor_field_flt *in){
   Dphi_flt(hmass,out,in);
}

static void random_g(void)
{
   _DECLARE_INT_ITERATOR(ix);

   _MASTER_FOR(&glattice,ix)
      random_suNg_flt(_FIELD_AT(g,ix));				// This one might not exist
}

static void transform_u(void)
{
   _DECLARE_INT_ITERATOR(ix);
   int iy,mu;
   suNg_flt *u,v;

   _MASTER_FOR(&glattice,ix) {
      for (mu=0;mu<4;mu++) {
         iy=iup(ix,mu);
         u=pu_gauge_flt(ix,mu);
         _suNg_times_suNg_dagger(v,*u,*_FIELD_AT(g,iy));
         _suNg_times_suNg(*u,*_FIELD_AT(g,ix),v);
      }
   }
   
   start_gf_sendrecv_flt(u_gauge_flt);
   represent_gauge_field_flt();
}

static void transform_s(spinor_field_flt *out, spinor_field_flt *in)
{
   _DECLARE_INT_ITERATOR(ix);
   suNf_flt gfx;
   suNf_spinor_flt *r,*s;

   _MASTER_FOR(&glattice,ix) {
      s = _FIELD_AT(in,ix);
      r = _FIELD_AT(out,ix);
     
      _group_represent2_flt(&gfx,_FIELD_AT(g,ix));

      _suNf_multiply(r->c[0],gfx,s->c[0]);
      _suNf_multiply(r->c[1],gfx,s->c[1]);
      _suNf_multiply(r->c[2],gfx,s->c[2]);
      _suNf_multiply(r->c[3],gfx,s->c[3]);
   }   
}


int main(int argc,char *argv[])
{
  char tmp[256];
  double res1,res2,res_cpu,res_gpu;
  spinor_field_flt *s0,*s1,*s2,*s3;
  gpu_timer t1;
  float elapsed, gflops;
  int i;
  int n_times=50;
  
  setup_process(&argc,&argv);
  
  logger_setlevel(0,10000); /* log all */
  logger_map("DEBUG","debug");
#ifdef WITH_MPI
  sprintf(tmp,">out_%d",PID); logger_stdout(tmp);
  sprintf(tmp,"err_%d",PID); freopen(tmp,"w",stderr);
#endif
  
  lprintf("MAIN",0,"PId =  %d [world_size: %d]\n\n",PID,WORLD_SIZE); 
  
  read_input(glb_var.read,"test_input");
  lprintf("MAIN",0,"RLXD [%d,%d]\n",glb_var.rlxd_level,glb_var.rlxd_seed);


  rlxd_init(glb_var.rlxd_level,glb_var.rlxd_seed);
  
  /* setup communication geometry */
  if (geometry_init() == 1) {
    finalize_process();
    return 0;
  }
  
  geometry_mpi_eo();
  
  
  lprintf("MAIN",0,"Gauge group: SU(%d)\n",NG);
  lprintf("MAIN",0,"Fermion representation: dim = %d\n",NF);
  lprintf("MAIN",0,"The lattice size is %dx%dx%dx%d\n",T,X,Y,Z);
  lprintf("MAIN",0,"The lattice global size is %dx%dx%dx%d\n",GLB_T,GLB_X,GLB_Y,GLB_Z);
  lprintf("MAIN",0,"The lattice borders are (%d,%d,%d,%d)\n",T_BORDER,X_BORDER,Y_BORDER,Z_BORDER);
  lprintf("MAIN",0,"\n");
  fflush(stdout);
  
  u_gauge_flt=alloc_gfield_flt(&glattice);
#if (!defined(REPR_FUNDAMENTAL) && !defined(WITH_QUATERNIONS)) || defined(ROTATED_SF) 
  u_gauge_f_flt=alloc_gfield_f_flt(&glattice);
#endif
  /* allocate memory */
  s0=alloc_spinor_field_f_flt(4,&glattice);
  s1=s0+1;
  s2=s1+1;
  s3=s2+1;
  
  gaussian_spinor_field_flt(s0);
  spinor_field_copy_to_gpu_f_flt(s0);

  gaussian_spinor_field_flt(s1);
  spinor_field_copy_to_gpu_f_flt(s1);

  lprintf("MAIN",0,"Generating a random gauge field... ");
  fflush(stdout);
  random_u_flt(u_gauge_flt);
  gfield_copy_to_gpu_flt(u_gauge_flt);
  start_gf_sendrecv_flt(u_gauge_flt);
  represent_gauge_field_flt();
  gfield_copy_to_gpu_f_flt(u_gauge_f_flt);

  lprintf("MAIN",0,"done.\n");
  
  lprintf("LA TEST",0,"Checking the diracoperator..\n");

  Dphi_flt_(s1,s0);
  Dphi_flt__cpu(s1,s0);
  
  res1 = sfdiff(s0);
  res2 = sfdiff(s1);

  res_gpu = spinor_field_sqnorm_f_flt(s1);
  res_cpu = spinor_field_sqnorm_f_flt_cpu(s1);

  lprintf("LA TEST",0,"Result, \nsqnorm(qpu)=%1.10g, sqnorm(cpu)=%1.10g,\nsqnorm(gpu-cpu)= %1.10g (check %1.10g=0?),\n",res_gpu,res_cpu,res2,res1);

  lprintf("LA TEST",0,"Checking the diracoperator with mass 0.13..\n");

  Dphi_flt(0.13,s1,s0);
  Dphi_flt_cpu(0.13,s1,s0);
  
  res1 = sfdiff(s0);
  res2 = sfdiff(s1);

  res_gpu = spinor_field_sqnorm_f_flt(s1);
  res_cpu = spinor_field_sqnorm_f_flt_cpu(s1);

  lprintf("LA TEST",0,"Result, \nsqnorm(qpu)=%1.10g, sqnorm(cpu)=%1.10g,\nsqnorm(gpu-cpu)= %1.10g (check %1.10g=0?),\n",res_gpu,res_cpu,res2,res1);


  lprintf("LA TEST",0,"Checking the gamma_5 x diracoperator with mass 0.13..\n");

  g5Dphi_flt(0.13,s1,s0);
  g5Dphi_flt_cpu(0.13,s1,s0);
  
  res1 = sfdiff(s0);
  res2 = sfdiff(s1);

  res_gpu = spinor_field_sqnorm_f_flt(s1);
  res_cpu = spinor_field_sqnorm_f_flt_cpu(s1);

  lprintf("LA TEST",0,"Result, \nsqnorm(qpu)=%1.10g, sqnorm(cpu)=%1.10g,\nsqnorm(gpu-cpu)= %1.10g (check %1.10g=0?),\n",res_gpu,res_cpu,res2,res1);

  lprintf("LA TEST",0,"Checking the (g5dphi x diracoperator)^2 with mass 0.13..\n");

  g5Dphi_sq_flt(0.13,s1,s0);
  g5Dphi_sq_flt_cpu(0.13,s1,s0);
  
  res1 = sfdiff(s0);
  res2 = sfdiff(s1);

  res_gpu = spinor_field_sqnorm_f_flt(s1);
  res_cpu = spinor_field_sqnorm_f_flt_cpu(s1);

  lprintf("LA TEST",0,"Result, \nsqnorm(qpu)=%1.10g, sqnorm(cpu)=%1.10g,\nsqnorm(gpu-cpu)= %1.10g (check %1.10g=0?),\n",res_gpu,res_cpu,res2,res1);


  lprintf("LA TEST",0,"Calculating Diracoperator %d times.\n",n_times);
  t1 = gpuTimerStart();

  for (i=0;i<n_times;++i){
    Dphi_flt_(s1,s0);
  }

  elapsed = gpuTimerStop(t1);
  lprintf("LA TEST",0,"Time: %1.10gms\n",elapsed);

  gflops=n_times*GLB_T*GLB_X*GLB_Y*GLB_Z*744./elapsed/1.e6;   // 536 //240
  lprintf("LA TEST",0,"GFLOPS: %1.6g\n\n",gflops);

  gflops=8.;
  gflops=n_times*GLB_T*GLB_X*GLB_Y*GLB_Z*((24.+28*gflops)*4.+gflops*4.)/elapsed/1.e6; 
  //gflops=n_times*GLB_T*GLB_X*GLB_Y*GLB_Z*328./elapsed/1.e6; 
  //gflops=n_times*GLB_T*GLB_X*GLB_Y*GLB_Z*212./elapsed/1.e6; 
  lprintf("LA TEST",0,"BAND: %1.6g\n\n",gflops);

  lprintf("LA TEST",0,"Calculating Diracoperator with mass=0.13 %d times.\n",n_times);
  t1 = gpuTimerStart();

  for (i=0;i<n_times;++i){
    Dphi_flt(0.13,s1,s0);
  }

  elapsed = gpuTimerStop(t1);
  lprintf("LA TEST",0,"Time: %1.10gms\n",elapsed);

  gflops=n_times*GLB_T*GLB_X*GLB_Y*GLB_Z*(744.+24.)/elapsed/1.e6;   // 536 //240
  lprintf("LA TEST",0,"GFLOPS: %1.6g\n\n",gflops);

  gflops=8.;
  gflops=n_times*GLB_T*GLB_X*GLB_Y*GLB_Z*((24.+28*gflops)*4.+gflops*4.+48*4)/elapsed/1.e6; 
  lprintf("LA TEST",0,"BAND: %1.6g\n\n",gflops);

  lprintf("LA TEST",0,"DONE!");

  lprintf("LA TEST",0,"Calculating gamma_5 x Diracoperator with mass=0.13 %d times.\n",n_times);
  t1 = gpuTimerStart();

  for (i=0;i<n_times;++i){
    g5Dphi_flt(0.13,s1,s0);
  }

  elapsed = gpuTimerStop(t1);
  lprintf("LA TEST",0,"Time: %1.10gms\n",elapsed);

  gflops=n_times*GLB_T*GLB_X*GLB_Y*GLB_Z*(744.+24.)/elapsed/1.e6;   // 536 //240
  lprintf("LA TEST",0,"GFLOPS: %1.6g\n\n",gflops);

  gflops=8.;
  gflops=n_times*GLB_T*GLB_X*GLB_Y*GLB_Z*((24.+28*gflops)*4.+gflops*4.+48*4)/elapsed/1.e6; 
  lprintf("LA TEST",0,"BAND: %1.6g\n\n",gflops);

  lprintf("LA TEST",0,"DONE!");


  lprintf("LA TEST",0,"Calculating (gamma_5 x Diracoperator)^2 with mass=0.13 %d times.\n",n_times);
  t1 = gpuTimerStart();

  for (i=0;i<n_times;++i){
    g5Dphi_sq_flt(0.13,s1,s0);
  }

  elapsed = gpuTimerStop(t1);
  lprintf("LA TEST",0,"Time: %1.10gms\n",elapsed);

  gflops=2*n_times*GLB_T*GLB_X*GLB_Y*GLB_Z*(744.+24.)/elapsed/1.e6;   // 536 //240
  lprintf("LA TEST",0,"GFLOPS: %1.6g\n\n",gflops);

  gflops=8.;
  gflops=2*n_times*GLB_T*GLB_X*GLB_Y*GLB_Z*((24.+28*gflops)*4.+gflops*4.+48*4)/elapsed/1.e6; 
  lprintf("LA TEST",0,"BAND: %1.6g\n\n",gflops);

  lprintf("LA TEST",0,"DONE!");

  free_spinor_field_f_flt(s0);
  
  finalize_process();
  exit(0);
}

#else //WITH_GPU
#include <stdio.h>
#include "global.h"

int main(){
  printf("Compile with WITH_GPU to test GPU!\n");
}
#endif //WITH_GPU