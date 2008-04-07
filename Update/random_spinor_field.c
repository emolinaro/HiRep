#include "global.h"
#include "suN.h"
#include "random.h"
#include "linear_algebra.h"
#include "update.h"
#include <math.h>

void gaussian_spinor_field(spinor_field *s) {
	const double c1=1./sqrt(2.);
	unsigned int i;
	spinor_descriptor *type = s->type;
	for(i=0;i<type->local_pieces;i++)
 	  gauss((double*)(s->ptr+type->start[i]),type->len[i]*sizeof(suNf_spinor)/sizeof(double));
	spinor_field_mul_f(s,c1,s);
}

void gaussian_spinor_field_flt(spinor_field_flt *s) {
	const float c1=1./sqrt(2.);
	unsigned int i;
	spinor_descriptor *type = s->type;
	for(i=0;i<type->local_pieces;i++)
 	  gauss_flt((float*)(s->ptr+type->start[i]),type->len[i]*sizeof(suNf_spinor_flt)/sizeof(float));
	spinor_field_mul_f_flt(s,c1,s);
}
