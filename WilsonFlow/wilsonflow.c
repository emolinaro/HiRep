/* arXiv:1006.4518 [hep-lat] */

#include "global.h"
#include "geometry.h"
#include "suN.h"
#include "suN_repr_func.h"
#include "memory.h"
#include "global.h"
#include "logger.h"
#include "update.h"
#include "utils.h"
#include "communications.h"
#include "wilsonflow.h"
#include <math.h>

/*
#define EXP_CHECK
*/

/*
* S(x,mu) = staple in (x,mu)
* Z(A,x,mu) += - alpha * P_{AS,tl}[ U(x,mu).S(x,mu) ]
*/
static void Zeta(suNg_field *Z, const suNg_field* U, const double alpha){
  suNg s1,s2;
  int mu, n;
  _DECLARE_INT_ITERATOR(i);

  error(Z->type!=&glattice,1,"wilson_flow.c","'Z' in Zeta must be defined on the whole lattice");
  error(U->type!=&glattice,1,"wilson_flow.c","'U' in Zeta must be defined on the whole lattice");

  _MASTER_FOR(&glattice,i) {
    for (mu=0; mu<4; ++mu) {
      staples(i,mu,&s1);
      _suNg_times_suNg_dagger(s2,*_4FIELD_AT(U,i,mu),s1);
      _suNg_2TA(s1,s2);
      for(n=0; n<NG*NG; n++) {
      	_complex_mulr_assign(_4FIELD_AT(Z,i,mu)->c[n],-alpha/2.,s1.c[n]);
      }
    }
  }
}


#ifdef EXP_CHECK
static void WF_Exp_check(suNg *u, suNg *X) {
  suNg Xk, tmp;
  _suNg_unit(*u);
  _suNg_unit(Xk);
  
  int k=1;
  double error;
  while(1) {
    _suNg_times_suNg(tmp,Xk,*X);
    _suNg_mul(Xk,1./k,tmp);
    k++;
    _suNg_add_assign(*u,Xk);    

    _suNg_sqnorm(error,Xk);
    if(error<1e-28) break;
  }
  
}
#endif


#if NG==2

/*
*  u = exp(X)
*
* I AM ASSUMING
* X^dag = -X
* tr X = 0
*/
static void WF_Exp(suNg *u, suNg *X) {
  suNg_algebra_vector h,v;

  h.c[0] = X->c[1].im;
  h.c[1] = X->c[1].re;
  h.c[2] = X->c[0].im;
  
  double z=sqrt(h.c[0]*h.c[0]+h.c[1]*h.c[1]+h.c[2]*h.c[2]);
  double s=1.;
  if(z>1e-16) s=sin(z)/z;
  double c=cos(z);
  v.c[0]=h.c[0]*s;
  v.c[1]=h.c[1]*s;
  v.c[2]=h.c[2]*s;

  u->c[0].re = c;       u->c[0].im = v.c[2];
  u->c[1].re = v.c[1];  u->c[1].im = v.c[0];
  u->c[2].re = -v.c[1]; u->c[2].im = v.c[0];
  u->c[3].re = c;       u->c[3].im = -v.c[2];
  
#ifdef EXP_CHECK
  suNg w;
  double error;
  WF_Exp_check(&w,X);
  _suNg_sub_assign(w,*u);
  _suNg_sqnorm(error,w);
  lprintf("WILSONFLOW",0,"WF EXP CHECK %e\n",sqrt(error));
#endif
}

#elif NG==3

static void WF_Exp(suNg *u, suNg *X) {
  suNg X2;
  complex c[3], s[3], tmp;
  double alpha, beta;
  double norm, error;
  int n;
  
  
/* X2 = X.X */
  _suNg_times_suNg(X2,*X,*X);
  
/* alpha = Im det(X) */
  #define _X_(a,b) (X->c[a+3*b])
  #define ImProd(a,b,c) (a.re*(b.re*c.im+b.im*c.re)+a.im*(b.re*c.re-b.im*c.im))
  alpha=
    +ImProd(_X_(0,0),_X_(1,1),_X_(2,2))
    +ImProd(_X_(0,1),_X_(1,2),_X_(2,0))
    +ImProd(_X_(0,2),_X_(1,0),_X_(2,1))
    -ImProd(_X_(0,2),_X_(1,1),_X_(2,0))
    -ImProd(_X_(0,1),_X_(1,0),_X_(2,2))
    -ImProd(_X_(0,0),_X_(1,2),_X_(2,1));
  #undef _X_
  #undef ImProd
  
/* beta = tr (X2) / 2 */
/* norm = sqrt( |tr (X2)| ) */
  #define _X2_(a,b) (X2.c[a+3*b])
  beta=(_X2_(0,0).re+_X2_(1,1).re+_X2_(2,2).re)/2.;
  norm=sqrt(-_X2_(0,0).re-_X2_(1,1).re-_X2_(2,2).re);
  #undef _X2_
  
  s[0].re = 1.;          s[0].im = alpha/6.;
  s[1].re = 1.+beta/6.;  s[1].im = 0.;
  s[2].re = .5;          s[2].im = 0.;
  
  n=3;
  c[0].re = 0.;          c[0].im = alpha/6.;
  c[1].re = beta/6.;     c[1].im = 0.;
  c[2].re = 0.;          c[2].im = 0.;
  
  /* error = |X|^{n+1}/(n+1)! exp(|X|) */  
  error= exp(norm)*norm*norm*norm*norm/24.;
#error The error must be rechecked!!!

  /*
  c[0][n] = i*c[2][n-1]*alpha/n
  c[1][n] = (c[0][n-1]+c[2][n-1]*beta)/n
  c[2][n] = c[1][n-1]/n
  */
  while(1) {
    n++;
    tmp=c[1];
    c[1].re=(c[0].re+c[2].re*beta)/n;
    c[1].im=(c[0].im+c[2].im*beta)/n;
    c[0].re=-c[2].im*alpha/n;
    c[0].im=c[2].re*alpha/n;
    c[2].re=tmp.re/n;
    c[2].im=tmp.im/n;
    
    s[0].re+=c[0].re; s[0].im+=c[0].im;
    s[1].re+=c[1].re; s[1].im+=c[1].im;
    s[2].re+=c[2].re; s[2].im+=c[2].im;

    error *= norm/(n+1);
    if(error < 1.e-20) break;
  }
  
  _suNg_zero(*u);
  u->c[0].re=s[0].re; u->c[0].im=s[0].im;
  u->c[4].re=s[0].re; u->c[4].im=s[0].im;
  u->c[8].re=s[0].re; u->c[8].im=s[0].im;
  for(int i=0; i<9; i++) {
    _complex_mul_assign(u->c[i],s[1],X->c[i]);
    _complex_mul_assign(u->c[i],s[2],X2.c[i]);
  }
  
#ifdef EXP_CHECK
  suNg v;
  WF_Exp_check(&v,X);
  _suNg_sub_assign(v,*u);
  _suNg_sqnorm(error,v);
  lprintf("WILSONFLOW",0,"WF EXP CHECK %e\n",sqrt(error));
#endif
  
}
  
#else
#error The exact exponential must be implemented for this value of NG
#endif




static suNg_field* ws_gf=NULL;


void WF_initialize() {
  if(ws_gf==NULL) ws_gf=alloc_gfield(&glattice);
}


void WF_free() {
  if(ws_gf!=NULL) free_gfield(ws_gf);
}


void WilsonFlow1(suNg_field* V, const double epsilon) {
  _DECLARE_INT_ITERATOR(ix);
  suNg utmp[2];
  int mu;
  
  _MASTER_FOR(&glattice,ix) {
    for (mu=0; mu<4; ++mu) {
      _suNg_zero(*_4FIELD_AT(ws_gf,ix,mu));
    }
  }

  Zeta(ws_gf,V,epsilon);
  
  _MASTER_FOR(&glattice,ix) {
    for (mu=0; mu<4; ++mu) {
      WF_Exp(&utmp[0],_4FIELD_AT(ws_gf,ix,mu));
      _suNg_times_suNg(utmp[1],utmp[0],*_4FIELD_AT(V,ix,mu));
      *_4FIELD_AT(V,ix,mu)=utmp[1];
    }
  }
}



void WilsonFlow3(suNg_field* V, const double epsilon) {
  _DECLARE_INT_ITERATOR(ix);
  suNg utmp[2];
  int mu;
  
  _MASTER_FOR(&glattice,ix) {
    for (mu=0; mu<4; ++mu) {
      _suNg_zero(*_4FIELD_AT(ws_gf,ix,mu));
    }
  }
  
  Zeta(ws_gf,V,epsilon/4.);
  
  _MASTER_FOR(&glattice,ix) {
    for (mu=0; mu<4; ++mu) {
      WF_Exp(&utmp[0],_4FIELD_AT(ws_gf,ix,mu));
      _suNg_times_suNg(utmp[1],utmp[0],*_4FIELD_AT(V,ix,mu));
      *_4FIELD_AT(V,ix,mu)=utmp[1];
      _suNg_mul(*_4FIELD_AT(ws_gf,ix,mu),-17./9.,*_4FIELD_AT(ws_gf,ix,mu));
    }
  }
  
  Zeta(ws_gf,V,8.*epsilon/9.);
  
  _MASTER_FOR(&glattice,ix) {
    for (mu=0; mu<4; ++mu) {
      WF_Exp(&utmp[0],_4FIELD_AT(ws_gf,ix,mu));
      _suNg_times_suNg(utmp[1],utmp[0],*_4FIELD_AT(V,ix,mu));
      *_4FIELD_AT(V,ix,mu)=utmp[1];
      _suNg_mul(*_4FIELD_AT(ws_gf,ix,mu),-1.,*_4FIELD_AT(ws_gf,ix,mu));
    }
  }
  
  Zeta(ws_gf,V,3.*epsilon/4.);
  
  _MASTER_FOR(&glattice,ix) {
    for (mu=0; mu<4; ++mu) {
      WF_Exp(&utmp[0],_4FIELD_AT(ws_gf,ix,mu));
      _suNg_times_suNg(utmp[1],utmp[0],*_4FIELD_AT(V,ix,mu));
      *_4FIELD_AT(V,ix,mu)=utmp[1];
    }
  }
}


double WF_E(suNg_field* V) {
  _DECLARE_INT_ITERATOR(ix);
  int iy,iz;
  int mu,nu;
  double p;
  suNg *v1,*v2,*v3,*v4,w1,w2,w3;
  double E;
  
  E=0.;

  _MASTER_FOR(&glattice,ix) {
    for(mu=0;mu<4;mu++) for(nu=mu+1;nu<4;nu++) {
      iy=iup(ix,mu);
      iz=iup(ix,nu);
    
      v1=_4FIELD_AT(V,ix,mu);
      v2=_4FIELD_AT(V,iy,nu);
      v3=_4FIELD_AT(V,iz,mu);
      v4=_4FIELD_AT(V,ix,nu);
    
      _suNg_times_suNg(w1,(*v1),(*v2));
      _suNg_times_suNg(w2,(*v4),(*v3));
      _suNg_times_suNg_dagger(w3,w1,w2);      
  
      _suNg_trace_re(p,w3);
      
      E += NG-p;
    }
  }
  
  E *= 2./(GLB_T*GLB_X*GLB_Y*GLB_Z);
  
  return E;
}




double WF_Esym(suNg_field* V) {
  _DECLARE_INT_ITERATOR(ix);
  int iy,iz,iw;
  int mu,nu;
  double p;
  suNg *v1,*v2,*v3,*v4,w1,w2,w3;
  double E;
  
  E=0.;

  _MASTER_FOR(&glattice,ix) {
    for(mu=0;mu<4;mu++) for(nu=mu+1;nu<4;nu++) {
      _suNg_unit(w3);
      _suNg_mul(w3,-4.,w3);
      
      
      iy=iup(ix,mu);
      iz=iup(ix,nu);
    
      v1=_4FIELD_AT(V,ix,mu);
      v2=_4FIELD_AT(V,iy,nu);
      v3=_4FIELD_AT(V,iz,mu);
      v4=_4FIELD_AT(V,ix,nu);
    
      _suNg_times_suNg(w1,(*v1),(*v2));
      _suNg_times_suNg_dagger(w2,w1,(*v3));
      _suNg_times_suNg_dagger(w1,w2,(*v4));
      _suNg_add_assign(w3,w1);
      
  
      iy=idn(ix,mu);
      iz=iup(iy,nu);
    
      v1=_4FIELD_AT(V,ix,nu);
      v2=_4FIELD_AT(V,iz,mu);
      v3=_4FIELD_AT(V,iy,nu);
      v4=_4FIELD_AT(V,iy,mu);
    
      _suNg_times_suNg_dagger(w1,(*v1),(*v2));
      _suNg_times_suNg_dagger(w2,w1,(*v3));
      _suNg_times_suNg(w1,w2,(*v4));
      _suNg_add_assign(w3,w1);
      

      iy=idn(ix,mu);
      iz=idn(iy,nu);
      iw=idn(ix,nu);
    
      v1=_4FIELD_AT(V,iy,mu);
      v2=_4FIELD_AT(V,iz,nu);
      v3=_4FIELD_AT(V,iz,mu);
      v4=_4FIELD_AT(V,iw,nu);
    
      _suNg_times_suNg(w1,(*v2),(*v1));
      _suNg_dagger_times_suNg(w2,w1,(*v3));
      _suNg_times_suNg(w1,w2,(*v4));
      _suNg_add_assign(w3,w1);
      

      iy=idn(ix,nu);
      iz=iup(iy,mu);
    
      v1=_4FIELD_AT(V,iy,nu);
      v2=_4FIELD_AT(V,iy,mu);
      v3=_4FIELD_AT(V,iz,nu);
      v4=_4FIELD_AT(V,ix,mu);
    
      _suNg_dagger_times_suNg(w1,(*v1),(*v2));
      _suNg_times_suNg(w2,w1,(*v3));
      _suNg_times_suNg_dagger(w1,w2,(*v4));
      _suNg_add_assign(w3,w1);
      

      _suNg_2TA(w1,w3);
      
      _suNg_sqnorm(p,w1);
      
      E += p;
    }
  }
  
  E *= 1./(64.*(GLB_T*GLB_X*GLB_Y*GLB_Z));
  
  return E;
}

