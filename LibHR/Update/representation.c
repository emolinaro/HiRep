/*************************************************************************** \
 * Copyright (c) 2008, Claudio Pica, Agostino Patella                        *   
 * All rights reserved.                                                      * 
\***************************************************************************/

#include "global.h"
#include "representation.h"
#include "utils.h"
#include <math.h>



#define XG(m,a,b) ((m)+(a)*NG+(b))
#define XF(m,a,b) ((m)+(a)*NF+(b))

void _group_represent2(suNf* v, suNg *u) {
#ifdef WITH_QUATERNIONS
  *v = *((suNf *)u);
#elif defined REPR_ADJOINT

  int A, C;
  int a, b, i, j, k, c, d;
  double* vf = (double*)v;
  double complex* uf = (double complex*)u;

  suNg m;
  double complex* mf = (double complex*)(&m);


  A = 0;
  for(a = 0; a < NG; a++) for(b = (a==0)?1:0; b < NG; b++) {
      if(a > b)
        {
          for(i = 0; i < NG; i++) for(j = i; j < NG; j++) {
              *XG(mf,i,j) = (*XG(uf,i,a))*conj(*XG(uf,j,b))+(*XG(uf,i,b))*conj(*XG(uf,j,a));
              /* XG(mf,i,j)->re = XG(uf,i,a)->re*XG(uf,j,b)->re+XG(uf,i,a)->im*XG(uf,j,b)->im+XG(uf,i,b)->re*XG(uf,j,a)->re+XG(uf,i,b)->im*XG(uf,j,a)->im; */
              /* XG(mf,i,j)->im = -XG(uf,i,a)->re*XG(uf,j,b)->im+XG(uf,i,a)->im*XG(uf,j,b)->re-XG(uf,i,b)->re*XG(uf,j,a)->im+XG(uf,i,b)->im*XG(uf,j,a)->re; */
            }
        }
      else if(a < b)
        {
          for(i = 0; i < NG; i++) for(j = i; j < NG; j++) {
              *XG(mf,i,j)=conj(*XG(uf,i,a))*(*XG(uf,j,b)) - conj(*XG(uf,i,b))*(*XG(uf,j,a));
              /* XG(mf,i,j)->im = XG(uf,i,a)->re*XG(uf,j,b)->re+XG(uf,i,a)->im*XG(uf,j,b)->im-XG(uf,i,b)->re*XG(uf,j,a)->re-XG(uf,i,b)->im*XG(uf,j,a)->im; */
              /* XG(mf,i,j)->re = +XG(uf,i,a)->re*XG(uf,j,b)->im-XG(uf,i,a)->im*XG(uf,j,b)->re-XG(uf,i,b)->re*XG(uf,j,a)->im+XG(uf,i,b)->im*XG(uf,j,a)->re; */
            }
        }
      else if(a == b)
        {
          for(i = 0; i < NG; i++) for(j = i; j < NG; j++) {
              *XG(mf,i,j)=-a*(*XG(uf,i,a))*conj(*XG(uf,j,a));
              /* XG(mf,i,j)->re = -a*(XG(uf,i,a)->re*XG(uf,j,a)->re+XG(uf,i,a)->im*XG(uf,j,a)->im); */
              /* XG(mf,i,j)->im = -a*(XG(uf,i,a)->im*XG(uf,j,a)->re-XG(uf,i,a)->re*XG(uf,j,a)->im); */
              for(k = 0; k < a; k++) {
                *XG(mf,i,j)+=(*XG(uf,i,k))*conj(*XG(uf,j,k));
                /* XG(mf,i,j)->re += XG(uf,i,k)->re*XG(uf,j,k)->re+XG(uf,i,k)->im*XG(uf,j,k)->im; */
                /* XG(mf,i,j)->im += XG(uf,i,k)->im*XG(uf,j,k)->re-XG(uf,i,k)->re*XG(uf,j,k)->im; */
              }
              *XG(mf,i,j) *= sqrt(2./(a*(a+1.)));
            }
        }

      C = 0;
      for(c = 0; c < NG; c++) for(d = (c==0)?1:0; d < NG; d++) {
          if(c > d)
            {
              *(XF(vf,C,A)) = creal(*XG(mf,d,c));
            }
          else if(c < d)
            {
              *(XF(vf,C,A)) = cimag(*XG(mf,c,d));
            }
          else if(c == d)
            {
              *(XF(vf,C,A)) = -c*creal(*XG(mf,c,c));
              for(k = 0; k < c; k++) {
                *(XF(vf,C,A)) += creal(*XG(mf,k,k));
              }
              *(XF(vf,C,A)) *= sqrt(.5/(c*(c+1.)));
            }

          C++;
        }

      A++;
    }

#elif defined REPR_SYMMETRIC

  const double st = sqrt(2.);
  int A, C;
  int a, b, i, j, c, d;
  double complex* vf = (double complex*)v;
  double complex* uf = (double complex*)u;

  suNg m;
  double complex* mf = (double complex*)(&m);

  A = 0;
  for(a = 0; a < NG; a++) {
    for(b = 0; b < a; b++) {
      for(i = 0; i < NG; i++) for(j = i; j < NG; j++) {
         
          *XG(mf,i,j)=(*XG(uf,i,a))*(*XG(uf,j,b))+(*XG(uf,i,b))*(*XG(uf,j,a));
          /* XG(mf,i,j)->re = XG(uf,i,a)->re*XG(uf,j,b)->re-XG(uf,i,a)->im*XG(uf,j,b)->im+XG(uf,i,b)->re*XG(uf,j,a)->re-XG(uf,i,b)->im*XG(uf,j,a)->im; */
          /* XG(mf,i,j)->im = XG(uf,i,a)->re*XG(uf,j,b)->im+XG(uf,i,a)->im*XG(uf,j,b)->re+XG(uf,i,b)->re*XG(uf,j,a)->im+XG(uf,i,b)->im*XG(uf,j,a)->re; */
        }

      C = 0;
      for(c = 0; c < NG; c++) {
        for(d = 0; d < c; d++) {
          *XF(vf,C,A) = *XG(mf,d,c);
          C++;
        }
        *XF(vf,C,A) = (*XG(mf,c,c))/st;
        C++;
      }

      A++;
    }

    for(i = 0; i < NG; i++) for(j = i; j < NG; j++) {
        *XG(mf,i,j)=(*XG(uf,i,a))*(*XG(uf,j,a));
        /* XG(mf,i,j)->re = XG(uf,i,a)->re*XG(uf,j,a)->re-XG(uf,i,a)->im*XG(uf,j,a)->im; */
        /* XG(mf,i,j)->im = XG(uf,i,a)->re*XG(uf,j,a)->im+XG(uf,i,a)->im*XG(uf,j,a)->re; */
      }
    
    C = 0;
    for(c = 0; c < NG; c++) {
      for(d = 0; d < c; d++) {
        *XF(vf,C,A) = (*XG(mf,d,c))*st;
        C++;
      }
      *XF(vf,C,A) = (*XG(mf,c,c));
      C++;
    }

    A++;
  }

#elif defined REPR_ANTISYMMETRIC

  int A, C;
  int a, b, i, j, c, d;
  double complex* vf = (double complex*)v;
  double complex* uf = (double complex*)u;

  suNg m;
  double complex* mf = (double complex*)(&m);

  A = 0;
  for(a = 1; a < NG; a++)
    for(b = 0; b < a; b++)
      {
        for(i = 0; i < NG; i++) for(j = i; j < NG; j++) {
            *XG(mf,i,j) = (*XG(uf,i,a))*(*XG(uf,j,b))-(*XG(uf,i,b))*(*XG(uf,j,a));
            /* XG(mf,i,j)->re = XG(uf,i,a)->re*XG(uf,j,b)->re-XG(uf,i,a)->im*XG(uf,j,b)->im-XG(uf,i,b)->re*XG(uf,j,a)->re+XG(uf,i,b)->im*XG(uf,j,a)->im; */
            /* XG(mf,i,j)->im = XG(uf,i,a)->re*XG(uf,j,b)->im+XG(uf,i,a)->im*XG(uf,j,b)->re-XG(uf,i,b)->re*XG(uf,j,a)->im-XG(uf,i,b)->im*XG(uf,j,a)->re; */
          }

        C = 0;
        for(c = 1; c < NG; c++) for(d = 0; d < c; d++) {
            *XF(vf,C,A) = -(*XG(mf,d,c));
            C++;
          }

        A++;
      }

#elif defined REPR_FUNDAMENTAL

  *v = *((suNf *)u); 
#endif

}


void _group_represent_flt(suNf_flt* v, suNg_flt *u) {

#ifdef REPR_ADJOINT

  int A, C;
  int a, b, i, j, k, c, d;
  float* vf = (float*)v;
  hr_complex_flt* uf = (hr_complex_flt*)u;

  suNg_flt m;
  hr_complex_flt* mf = (hr_complex_flt*)(&m);


  A = 0;
  for(a = 0; a < NG; a++) for(b = (a==0)?1:0; b < NG; b++) {
      if(a > b)
        {
          for(i = 0; i < NG; i++) for(j = i; j < NG; j++) {
              *XG(mf,i,j) = (*XG(uf,i,a))*conj(*XG(uf,j,b))+(*XG(uf,i,b))*conj(*XG(uf,j,a));
              /* XG(mf,i,j)->re = XG(uf,i,a)->re*XG(uf,j,b)->re+XG(uf,i,a)->im*XG(uf,j,b)->im+XG(uf,i,b)->re*XG(uf,j,a)->re+XG(uf,i,b)->im*XG(uf,j,a)->im; */
              /* XG(mf,i,j)->im = -XG(uf,i,a)->re*XG(uf,j,b)->im+XG(uf,i,a)->im*XG(uf,j,b)->re-XG(uf,i,b)->re*XG(uf,j,a)->im+XG(uf,i,b)->im*XG(uf,j,a)->re; */
            }
        }
      else if(a < b)
        {
          for(i = 0; i < NG; i++) for(j = i; j < NG; j++) {
              *XG(mf,i,j)=conj(*XG(uf,i,a))*(*XG(uf,j,b)) - conj(*XG(uf,i,b))*(*XG(uf,j,a));
              /* XG(mf,i,j)->im = XG(uf,i,a)->re*XG(uf,j,b)->re+XG(uf,i,a)->im*XG(uf,j,b)->im-XG(uf,i,b)->re*XG(uf,j,a)->re-XG(uf,i,b)->im*XG(uf,j,a)->im; */
              /* XG(mf,i,j)->re = +XG(uf,i,a)->re*XG(uf,j,b)->im-XG(uf,i,a)->im*XG(uf,j,b)->re-XG(uf,i,b)->re*XG(uf,j,a)->im+XG(uf,i,b)->im*XG(uf,j,a)->re; */
            }
        }
      else if(a == b)
        {
          for(i = 0; i < NG; i++) for(j = i; j < NG; j++) {
              *XG(mf,i,j)=-a*(*XG(uf,i,a))*conj(*XG(uf,j,a));
              /* XG(mf,i,j)->re = -a*(XG(uf,i,a)->re*XG(uf,j,a)->re+XG(uf,i,a)->im*XG(uf,j,a)->im); */
              /* XG(mf,i,j)->im = -a*(XG(uf,i,a)->im*XG(uf,j,a)->re-XG(uf,i,a)->re*XG(uf,j,a)->im); */
              for(k = 0; k < a; k++) {
                *XG(mf,i,j)+=(*XG(uf,i,k))*conj(*XG(uf,j,k));
                /* XG(mf,i,j)->re += XG(uf,i,k)->re*XG(uf,j,k)->re+XG(uf,i,k)->im*XG(uf,j,k)->im; */
                /* XG(mf,i,j)->im += XG(uf,i,k)->im*XG(uf,j,k)->re-XG(uf,i,k)->re*XG(uf,j,k)->im; */
              }
              *XG(mf,i,j) *= (float)sqrt(2./(a*(a+1.)));
            }
        }

      C = 0;
      for(c = 0; c < NG; c++) for(d = (c==0)?1:0; d < NG; d++) {
          if(c > d)
            {
              *(XF(vf,C,A)) = creal(*XG(mf,d,c));
            }
          else if(c < d)
            {
              *(XF(vf,C,A)) = cimag(*XG(mf,c,d));
            }
          else if(c == d)
            {
              *(XF(vf,C,A)) = -c*creal(*XG(mf,c,c));
              for(k = 0; k < c; k++) {
                *(XF(vf,C,A)) += creal(*XG(mf,k,k));
              }
              *(XF(vf,C,A)) *= (float)sqrt(.5/(c*(c+1.)));
            }

          C++;
        }

      A++;
    }

#elif defined REPR_SYMMETRIC

  const double st = sqrt(2.);
  int A, C;
  int a, b, i, j, c, d;
  hr_complex_flt* vf = (hr_complex_flt*)v;
  hr_complex_flt* uf = (hr_complex_flt*)u;

  suNg_flt m;
  hr_complex_flt* mf = (hr_complex_flt*)(&m);

  A = 0;
  for(a = 0; a < NG; a++) {
    for(b = 0; b < a; b++) {
      for(i = 0; i < NG; i++) for(j = i; j < NG; j++) {
          *XG(mf,i,j)=(*XG(uf,i,a))*(*XG(uf,j,b))+(*XG(uf,i,b))*(*XG(uf,j,a));
          /* XG(mf,i,j)->re = XG(uf,i,a)->re*XG(uf,j,b)->re-XG(uf,i,a)->im*XG(uf,j,b)->im+XG(uf,i,b)->re*XG(uf,j,a)->re-XG(uf,i,b)->im*XG(uf,j,a)->im; */
          /* XG(mf,i,j)->im = XG(uf,i,a)->re*XG(uf,j,b)->im+XG(uf,i,a)->im*XG(uf,j,b)->re+XG(uf,i,b)->re*XG(uf,j,a)->im+XG(uf,i,b)->im*XG(uf,j,a)->re; */
        }

      C = 0;
      for(c = 0; c < NG; c++) {
        for(d = 0; d < c; d++) {
          *XF(vf,C,A) = *XG(mf,d,c);
          C++;
        }
        *XF(vf,C,A) = (*XG(mf,c,c))/st;
        C++;
      }

      A++;
    }

    for(i = 0; i < NG; i++) for(j = i; j < NG; j++) {
        *XG(mf,i,j)=(*XG(uf,i,a))*(*XG(uf,j,a));
        /* XG(mf,i,j)->re = XG(uf,i,a)->re*XG(uf,j,a)->re-XG(uf,i,a)->im*XG(uf,j,a)->im; */
        /* XG(mf,i,j)->im = XG(uf,i,a)->re*XG(uf,j,a)->im+XG(uf,i,a)->im*XG(uf,j,a)->re; */
      }

    C = 0;
    for(c = 0; c < NG; c++) {
      for(d = 0; d < c; d++) {
        *XF(vf,C,A) = (*XG(mf,d,c))*st;
        C++;
      }
      *XF(vf,C,A) = (*XG(mf,c,c));
      C++;
    }

    A++;
  }

#elif defined REPR_ANTISYMMETRIC

  int A, C;
  int a, b, i, j, c, d;
  hr_complex_flt* vf = (hr_complex_flt*)v;
  hr_complex_flt* uf = (hr_complex_flt*)u;

  suNg_flt m;
  hr_complex_flt* mf = (hr_complex_flt*)(&m);

  A = 0;
  for(a = 1; a < NG; a++)
    for(b = 0; b < a; b++)
      {
        for(i = 0; i < NG; i++) for(j = i; j < NG; j++) {
            *XG(mf,i,j) = (*XG(uf,i,a))*(*XG(uf,j,b))-(*XG(uf,i,b))*(*XG(uf,j,a));
            /* XG(mf,i,j)->re = XG(uf,i,a)->re*XG(uf,j,b)->re-XG(uf,i,a)->im*XG(uf,j,b)->im-XG(uf,i,b)->re*XG(uf,j,a)->re+XG(uf,i,b)->im*XG(uf,j,a)->im; */
            /* XG(mf,i,j)->im = XG(uf,i,a)->re*XG(uf,j,b)->im+XG(uf,i,a)->im*XG(uf,j,b)->re-XG(uf,i,b)->re*XG(uf,j,a)->im-XG(uf,i,b)->im*XG(uf,j,a)->re; */
          }

        C = 0;
        for(c = 1; c < NG; c++) for(d = 0; d < c; d++) {
            *XF(vf,C,A) = -(*XG(mf,d,c));
            C++;
          }
        
        A++;
      }

#elif defined REPR_FUNDAMENTAL

  *v = *((suNf_flt *)u); 
#endif

}

#undef XG
#undef XF


#include "communications.h"

void represent_gauge_field() {
#ifdef ALLOCATE_REPR_GAUGE_FIELD
  suNf *Ru;
  suNg *u;

  /* loop on local lattice first */
  _MASTER_FOR(&glattice,ix) {
    //  for(ip=0;ip<glattice.local_master_pieces;ip++)
    //    for(ix=glattice.master_start[ip];ix<=glattice.master_end[ip];ix++)
    for (int mu=0;mu<4;mu++) {
      u=pu_gauge(ix,mu);
      Ru=pu_gauge_f(ix,mu);
#ifdef UNROLL_GROUP_REPRESENT
      _group_represent(*Ru,*u);
#else
      _group_represent2(Ru,u); 
#endif
    }
  }
  
  /* wait gauge field transfer */
  complete_gf_sendrecv(u_gauge);

  /* loop on the rest of master sites */
  _OMP_PRAGMA ( _omp_parallel )
    for(int ip=glattice.local_master_pieces;ip<glattice.total_gauge_master_pieces;ip++) {
      _OMP_PRAGMA ( _omp_for )
        for(int ix=glattice.master_start[ip];ix<=glattice.master_end[ip];ix++)
          for (int mu=0;mu<4;mu++) {
            u=pu_gauge(ix,mu);
            Ru=pu_gauge_f(ix,mu);
#ifdef UNROLL_GROUP_REPRESENT
            _group_represent(*Ru,*u);
#else
            _group_represent2(Ru,u); 
#endif
          }
    }
  
  apply_BCs_on_represented_gauge_field();
#else
  static int first_time=1;
  /* wait gauge field transfer */
  complete_gf_sendrecv(u_gauge);

  if(first_time) {
    first_time=0;
    u_gauge_f=(suNf_field *)((void*)u_gauge);
    //    apply_BCs_on_represented_gauge_field(); //Already applied when configuration read or initialized 
  }
#endif
  assign_ud2u_f();
}


