/*******************************************************************************
*
* Computation of the mesonic spectrum
*
*******************************************************************************/

#define MAIN_PROGRAM

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "io.h"
#include "random.h"
#include "error.h"
#include "geometry.h"
#include "memory.h"
#include "statistics.h"
#include "update.h"
#include "global.h"
#include "observables.h"
#include "suN.h"
#include "suN_types.h"
#include "dirac.h"
#include "linear_algebra.h"
#include "inverters.h"
#include "representation.h"
#include "utils.h"
#include "logger.h"
#include "communications.h"
#include "spectrum.h"
#include "cinfo.c"

#if defined(ROTATED_SF) && defined(BASIC_SF)
#error This code does not work with the Schroedinger functional !!!
#endif

#ifdef FERMION_THETA
#error This code does not work with the fermion twisting !!!
#endif

//typedef enum {semwall_src,point_src} source_type_t;
/* Mesons parameters */
typedef struct _input_mesons {
  char mstring[256];
  double precision;
  int nhits_2pt;
  int nhits_disc;
  int def_semwall;
  int def_point;
  int ext_semwall;
  int ext_point;
  int fixed_semwall;
  int fixed_point;
  int fixed_gfwall;
  int discon_semwall;
  int discon_gfwall;
  int def_gfwall;
  int dt;
  int n_mom;
  /* for the reading function */
  input_record_t read[17];
} input_mesons;

#define init_input_mesons(varname) \
{ \
  .read={\
    {"quark quenched masses", "mes:masses = %s", STRING_T, (varname).mstring}, \
    {"inverter precision", "mes:precision = %lf", DOUBLE_T, &(varname).precision},\
    {"number of noisy sources per cnfg for 2pt fn", "mes:nhits_2pt = %d", INT_T, &(varname).nhits_2pt}, \
    {"number of noisy sources per cnfg for disconnected", "mes:nhits_disc = %d", INT_T, &(varname).nhits_disc}, \
    {"enable default semwall", "mes:def_semwall = %d",INT_T, &(varname).def_semwall},	\
    {"enable default point", "mes:def_point = %d",INT_T, &(varname).def_point},		\
    {"enable default gfwall", "mes:def_gfwall = %d",INT_T, &(varname).def_gfwall},	\
    {"enable extended semwall", "mes:ext_semwall = %d",INT_T, &(varname).ext_semwall},	\
    {"enable extended point", "mes:ext_point = %d",INT_T, &(varname).ext_point},		\
    {"enable Dirichlet semwall", "mes:dirichlet_semwall = %d",INT_T, &(varname).fixed_semwall},	\
    {"enable Dirichlet point", "mes:dirichlet_point = %d",INT_T, &(varname).fixed_point},	\
    {"enable Dirichlet gfwall", "mes:dirichlet_gfwall = %d",INT_T, &(varname).fixed_gfwall},	\
    {"enable discon semwall", "mes:discon_semwall = %d",INT_T, &(varname).discon_semwall},	\
    {"enable discon gfwall", "mes:discon_gfwall = %d",INT_T, &(varname).discon_gfwall},	\
    {"Distance of t_initial from Dirichlet boundary", "mes:dirichlet_dt = %d", INT_T, &(varname).dt},\
    {"maximum component of momentum", "mes:momentum = %d", INT_T, &(varname).n_mom}, \
    {NULL, NULL, INT_T, NULL}				\
   }							\
}


char cnfg_filename[256]="";
char list_filename[256]="";
char input_filename[256] = "input_file";
char output_filename[256] = "mesons.out";
enum { UNKNOWN_CNFG, DYNAMICAL_CNFG, QUENCHED_CNFG };

input_mesons mes_var = init_input_mesons(mes_var);


typedef struct {
  char string[256];
  int t, x, y, z;
  int nc, nf;
  double b, m;
  int n;
  int type;
} filename_t;


int parse_cnfg_filename(char* filename, filename_t* fn) {
  int hm;
  char *tmp = NULL;
  char *basename;

  basename = filename;
  while ((tmp = strchr(basename, '/')) != NULL) {
    basename = tmp+1;
  }            

#ifdef REPR_FUNDAMENTAL
#define repr_name "FUN"
#elif defined REPR_SYMMETRIC
#define repr_name "SYM"
#elif defined REPR_ANTISYMMETRIC
#define repr_name "ASY"
#elif defined REPR_ADJOINT
#define repr_name "ADJ"
#endif
  hm=sscanf(basename,"%*[^_]_%dx%dx%dx%d%*[Nn]c%dr" repr_name "%*[Nn]f%db%lfm%lfn%d",
      &(fn->t),&(fn->x),&(fn->y),&(fn->z),&(fn->nc),&(fn->nf),&(fn->b),&(fn->m),&(fn->n));
  if(hm==9) {
    fn->m=-fn->m; /* invert sign of mass */
    fn->type=DYNAMICAL_CNFG;
    return DYNAMICAL_CNFG;
  }
#undef repr_name

  double kappa;
  hm=sscanf(basename,"%dx%dx%dx%d%*[Nn]c%d%*[Nn]f%db%lfk%lfn%d",
      &(fn->t),&(fn->x),&(fn->y),&(fn->z),&(fn->nc),&(fn->nf),&(fn->b),&kappa,&(fn->n));
  if(hm==9) {
    fn->m = .5/kappa-4.;
    fn->type=DYNAMICAL_CNFG;
    return DYNAMICAL_CNFG;
  }

  hm=sscanf(basename,"%dx%dx%dx%d%*[Nn]c%db%lfn%d",
      &(fn->t),&(fn->x),&(fn->y),&(fn->z),&(fn->nc),&(fn->b),&(fn->n));
  if(hm==7) {
    fn->type=QUENCHED_CNFG;
    return QUENCHED_CNFG;
  }

  hm=sscanf(basename,"%*[^_]_%dx%dx%dx%d%*[Nn]c%db%lfn%d",
      &(fn->t),&(fn->x),&(fn->y),&(fn->z),&(fn->nc),&(fn->b),&(fn->n));
  if(hm==7) {
    fn->type=QUENCHED_CNFG;
    return QUENCHED_CNFG;
  }

  fn->type=UNKNOWN_CNFG;
  return UNKNOWN_CNFG;
}


void read_cmdline(int argc, char* argv[]) {
  int i, ai=0, ao=0, ac=0, al=0, am=0;
  FILE *list=NULL;

  for (i=1;i<argc;i++) {
    if (strcmp(argv[i],"-i")==0) ai=i+1;
    else if (strcmp(argv[i],"-o")==0) ao=i+1;
    else if (strcmp(argv[i],"-c")==0) ac=i+1;
    else if (strcmp(argv[i],"-l")==0) al=i+1;
    else if (strcmp(argv[i],"-m")==0) am=i;
  }

  if (am != 0) {
    print_compiling_info();
    exit(0);
  }

  if (ao!=0) strcpy(output_filename,argv[ao]);
  if (ai!=0) strcpy(input_filename,argv[ai]);

  error((ac==0 && al==0) || (ac!=0 && al!=0),1,"parse_cmdline [mk_mesons.c]",
      "Syntax: mk_mesons { -c <config file> | -l <list file> } [-i <input file>] [-o <output file>] [-m]");

  if(ac != 0) {
    strcpy(cnfg_filename,argv[ac]);
    strcpy(list_filename,"");
  } else if(al != 0) {
    strcpy(list_filename,argv[al]);
    error((list=fopen(list_filename,"r"))==NULL,1,"parse_cmdline [mk_mesons.c]" ,
	"Failed to open list file\n");
    error(fscanf(list,"%s",cnfg_filename)==0,1,"parse_cmdline [mk_mesons.c]" ,
	"Empty list file\n");
    fclose(list);
  }


}


int main(int argc,char *argv[]) {
  int i,k,tau;
  char tmp[256], *cptr;
  FILE* list;
  filename_t fpars;
  int nm;
  double m[256];
  

  /* setup process id and communications */
  read_cmdline(argc, argv);
  setup_process(&argc,&argv);

  read_input(glb_var.read,input_filename);
  setup_replicas();

  /* logger setup */
  /* disable logger for MPI processes != 0 */
  logger_setlevel(0,10);
  if (PID!=0) { logger_disable(); }
  if (PID==0) { 
    sprintf(tmp,">%s",output_filename); logger_stdout(tmp);
    sprintf(tmp,"err_%d",PID); 
    if (!freopen(tmp,"w",stderr)) lprintf("MAIN",0,"Error out not open\n");
  }

  lprintf("MAIN",0,"Compiled with macros: %s\n",MACROS); 
  lprintf("MAIN",0,"PId =  %d [world_size: %d]\n\n",PID,WORLD_SIZE); 
  lprintf("MAIN",0,"input file [%s]\n",input_filename); 
  lprintf("MAIN",0,"output file [%s]\n",output_filename); 
  if (list_filename!=NULL) lprintf("MAIN",0,"list file [%s]\n",list_filename); 
  else lprintf("MAIN",0,"cnfg file [%s]\n",cnfg_filename); 


  /* read & broadcast parameters */
  parse_cnfg_filename(cnfg_filename,&fpars);
  read_input(mes_var.read,input_filename);

  GLB_T=fpars.t; GLB_X=fpars.x; GLB_Y=fpars.y; GLB_Z=fpars.z;
  error(fpars.type==UNKNOWN_CNFG,1,"measure_spectrum.c","Bad name for a configuration file");
  error(fpars.nc!=NG,1,"measure_spectrum.c","Bad NG");

  read_input(rlx_var.read,input_filename);
  lprintf("MAIN",0,"RLXD [%d,%d]\n",rlx_var.rlxd_level,rlx_var.rlxd_seed);
  rlxd_init(rlx_var.rlxd_level,rlx_var.rlxd_seed+MPI_PID);
  srand(rlx_var.rlxd_seed+MPI_PID);

#ifdef GAUGE_SON
  lprintf("MAIN",0,"Gauge group: SO(%d)\n",NG);
#else
  lprintf("MAIN",0,"Gauge group: SU(%d)\n",NG);
#endif
  lprintf("MAIN",0,"Fermion representation: " REPR_NAME " [dim=%d]\n",NF);

  nm=0;
  if(fpars.type==DYNAMICAL_CNFG) {
    nm=1;
    m[0] = fpars.m;
  } else if(fpars.type==QUENCHED_CNFG) {
    strcpy(tmp,mes_var.mstring);
    cptr = strtok(tmp, ";");
    nm=0;
    while(cptr != NULL) {
      m[nm]=atof(cptr);
      nm++;
      cptr = strtok(NULL, ";");
    }    
  }


  /* setup communication geometry */
  if (geometry_init() == 1) {
    finalize_process();
    return 0;
  }

  /* setup lattice geometry */
  geometry_mpi_eo();
  /* test_geometry_mpi_eo(); */

  init_BCs(NULL);

  /* alloc global gauge fields */
  u_gauge=alloc_gfield(&glattice);
#ifdef ALLOCATE_REPR_GAUGE_FIELD
  u_gauge_f=alloc_gfield_f(&glattice);
#endif

  lprintf("MAIN",0,"Inverter precision = %e\n",mes_var.precision);
  for(k=0;k<nm;k++)
    lprintf("MAIN",0,"Mass[%d] = %f\n",k,m[k]);

  lprintf("MAIN",0,"Number of noisy sources per cnfg = %d. Does not affect point sources\n",mes_var.nhits_2pt);
  if (mes_var.def_semwall){
    lprintf("MAIN",0,"Spin Explicit Method (SEM) wall sources\n");    
  }
  if (mes_var.def_point){
    lprintf("MAIN",0,"Point sources\n");    
  }
  if (mes_var.def_gfwall){
    lprintf("MAIN",0,"Gauge Fixed Wall Source\n");    
  }
  if (mes_var.ext_semwall){
    lprintf("MAIN",0,"Spin Explicit Method (SEM) wall sources on extended lattice\n");    
  }
  if (mes_var.ext_point){
    lprintf("MAIN",0,"Point sources on extended lattice\n");    
  }
  if (mes_var.fixed_semwall){
    lprintf("MAIN",0,"Spin Explicit Method (SEM) wall sources with Dirichlet boundary conditions\n"); 
    lprintf("MAIN",0,"Distance between tau and the boundary: %d\n",mes_var.dt); 
  }
  if (mes_var.fixed_point){
    lprintf("MAIN",0,"Point sources with Dirichlet boundary conditions\n");    
    lprintf("MAIN",0,"Distance between tau and the boundary: %d\n",mes_var.dt); 
  }
  if (mes_var.fixed_gfwall){
    lprintf("MAIN",0,"Gauge Fixed Wall Source with Dirichlet boundary conditions\n"); 
    lprintf("MAIN",0,"Distance between tau and the boundary: %d\n",mes_var.dt); 
  }
  if (mes_var.n_mom>1){
    lprintf("MAIN",0,"Number of maximum monentum component %d\n",mes_var.n_mom-1);
    if (mes_var.def_semwall || mes_var.ext_semwall || mes_var.fixed_semwall){
      lprintf("MAIN",0,"WARGING: wall sources measure only with zero momenta\n");
    }
  }

  list=NULL;
  if(strcmp(list_filename,"")!=0) {
    error((list=fopen(list_filename,"r"))==NULL,1,"main [mk_mesons.c]" ,
	"Failed to open list file\n");
  }

  i=0;

  while(1) {
    struct timeval start, end, etime;

    if(list!=NULL)
      if(fscanf(list,"%s",cnfg_filename)==0 || feof(list)) break;

    i++;

    lprintf("MAIN",0,"Configuration from %s\n", cnfg_filename);
    read_gauge_field(cnfg_filename);
    represent_gauge_field();

    lprintf("TEST",0,"<p> %1.6f\n",avr_plaquette());
    full_plaquette();
    gettimeofday(&start,0);

    tau=0;
    if (mes_var.def_semwall){
      measure_spectrum_semwall(nm,m,mes_var.nhits_2pt,i,mes_var.precision);
    }
    if (mes_var.def_point){
      measure_spectrum_pt(tau,nm,m,mes_var.n_mom,mes_var.nhits_2pt,i,mes_var.precision);
    }
    if (mes_var.def_gfwall){
      measure_spectrum_gfwall(nm,m,i,mes_var.precision);
    }
    if (mes_var.ext_semwall){
      measure_spectrum_semwall_ext(nm,m,mes_var.nhits_2pt,i,mes_var.precision);
    }
    if (mes_var.ext_point){
      measure_spectrum_pt_ext(tau,nm,m,mes_var.n_mom,mes_var.nhits_2pt,i,mes_var.precision);
    }
    if (mes_var.fixed_semwall){
      measure_spectrum_semwall_fixedbc(mes_var.dt,nm,m,mes_var.nhits_2pt,i,mes_var.precision);
    }
    if (mes_var.fixed_point){
      measure_spectrum_pt_fixedbc(tau,mes_var.dt,nm,m,mes_var.n_mom,mes_var.nhits_2pt,i,mes_var.precision);
    }
    if (mes_var.fixed_gfwall){
      measure_spectrum_gfwall_fixedbc(mes_var.dt,nm,m,i,mes_var.precision);
    }
    if (mes_var.discon_semwall){
      measure_spectrum_discon_semwall(nm,m,mes_var.nhits_disc,i,mes_var.precision); 
    }
    if (mes_var.discon_gfwall){
      measure_spectrum_discon_gfwall(nm,m,i,mes_var.precision);
    }

    gettimeofday(&end,0);
    timeval_subtract(&etime,&end,&start);
    lprintf("MAIN",0,"Configuration #%d: analysed in [%ld sec %ld usec]\n",i,etime.tv_sec,etime.tv_usec);
    if(list==NULL) break;
  }

  if(list!=NULL) fclose(list);

  free_BCs();

  free_gfield(u_gauge);
#ifdef ALLOCATE_REPR_GAUGE_FIELD
  free_gfield_f(u_gauge_f);
#endif

  finalize_process();

  return 0;
}

