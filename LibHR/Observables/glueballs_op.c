#include <stdlib.h>
#include "global.h"
#include "geometry.h"
#include "suN.h"
#include "utils.h"
#include "glueballs.h"

#include <string.h>
#define npaths 49
static double PI=3.141592653589793238462643383279502884197;
static double complex *mom_def_Re_tr_paths=NULL;
static double complex *mom_def_Im_tr_paths=NULL;
static double complex *path_storage=NULL;
int ** direct_spatial_rotations(){
int i;
int ** res=malloc(sizeof(int *)*48);
int *res1=malloc(sizeof(int *)*48*4);
for (i=0;i<48;i++)
res[i]=res1+4*i;

res1[0]=0;
res1[1]=1;
res1[2]=2;
res1[3]=3;
res1[4]=0;
res1[5]=2;
res1[6]=1;
res1[7]=-3;
res1[8]=0;
res1[9]=-2;
res1[10]=-1;
res1[11]=-3;
res1[12]=0;
res1[13]=-1;
res1[14]=3;
res1[15]=2;
res1[16]=0;
res1[17]=-1;
res1[18]=-3;
res1[19]=-2;
res1[20]=0;
res1[21]=3;
res1[22]=-2;
res1[23]=1;
res1[24]=0;
res1[25]=-3;
res1[26]=-2;
res1[27]=-1;
res1[28]=0;
res1[29]=-2;
res1[30]=-3;
res1[31]=1;
res1[32]=0;
res1[33]=3;
res1[34]=-1;
res1[35]=-2;
res1[36]=0;
res1[37]=-3;
res1[38]=-1;
res1[39]=2;
res1[40]=0;
res1[41]=-2;
res1[42]=3;
res1[43]=-1;
res1[44]=0;
res1[45]=3;
res1[46]=1;
res1[47]=2;
res1[48]=0;
res1[49]=2;
res1[50]=3;
res1[51]=1;
res1[52]=0;
res1[53]=2;
res1[54]=-3;
res1[55]=-1;
res1[56]=0;
res1[57]=-3;
res1[58]=1;
res1[59]=-2;
res1[60]=0;
res1[61]=-2;
res1[62]=1;
res1[63]=3;
res1[64]=0;
res1[65]=2;
res1[66]=-1;
res1[67]=3;
res1[68]=0;
res1[69]=3;
res1[70]=2;
res1[71]=-1;
res1[72]=0;
res1[73]=-3;
res1[74]=2;
res1[75]=1;
res1[76]=0;
res1[77]=1;
res1[78]=3;
res1[79]=-2;
res1[80]=0;
res1[81]=1;
res1[82]=-3;
res1[83]=2;
res1[84]=0;
res1[85]=-1;
res1[86]=-2;
res1[87]=3;
res1[88]=0;
res1[89]=-1;
res1[90]=2;
res1[91]=-3;
res1[92]=0;
res1[93]=1;
res1[94]=-2;
res1[95]=-3;
res1[96]=0;
res1[97]=-1;
res1[98]=-2;
res1[99]=-3;
res1[100]=0;
res1[101]=-2;
res1[102]=-1;
res1[103]=3;
res1[104]=0;
res1[105]=2;
res1[106]=1;
res1[107]=3;
res1[108]=0;
res1[109]=1;
res1[110]=-3;
res1[111]=-2;
res1[112]=0;
res1[113]=1;
res1[114]=3;
res1[115]=2;
res1[116]=0;
res1[117]=-3;
res1[118]=2;
res1[119]=-1;
res1[120]=0;
res1[121]=3;
res1[122]=2;
res1[123]=1;
res1[124]=0;
res1[125]=2;
res1[126]=3;
res1[127]=-1;
res1[128]=0;
res1[129]=-3;
res1[130]=1;
res1[131]=2;
res1[132]=0;
res1[133]=3;
res1[134]=1;
res1[135]=-2;
res1[136]=0;
res1[137]=2;
res1[138]=-3;
res1[139]=1;
res1[140]=0;
res1[141]=-3;
res1[142]=-1;
res1[143]=-2;
res1[144]=0;
res1[145]=-2;
res1[146]=-3;
res1[147]=-1;
res1[148]=0;
res1[149]=-2;
res1[150]=3;
res1[151]=1;
res1[152]=0;
res1[153]=3;
res1[154]=-1;
res1[155]=2;
res1[156]=0;
res1[157]=2;
res1[158]=-1;
res1[159]=-3;
res1[160]=0;
res1[161]=-2;
res1[162]=1;
res1[163]=-3;
res1[164]=0;
res1[165]=-3;
res1[166]=-2;
res1[167]=1;
res1[168]=0;
res1[169]=3;
res1[170]=-2;
res1[171]=-1;
res1[172]=0;
res1[173]=-1;
res1[174]=-3;
res1[175]=2;
res1[176]=0;
res1[177]=-1;
res1[178]=3;
res1[179]=-2;
res1[180]=0;
res1[181]=1;
res1[182]=2;
res1[183]=-3;
res1[184]=0;
res1[185]=1;
res1[186]=-2;
res1[187]=3;
res1[188]=0;
res1[189]=-1;
res1[190]=2;
res1[191]=3;
return res;
}
int ** inverse_spatial_rotations(){
int i;
int ** res=malloc(sizeof(int *)*48);
int *res1=malloc(sizeof(int *)*48*4);
for (i=0;i<48;i++)
res[i]=res1+4*i;
res1[0]=0;
res1[1]=1;
res1[2]=2;
res1[3]=3;
res1[4]=0;
res1[5]=2;
res1[6]=1;
res1[7]=-3;
res1[8]=0;
res1[9]=-2;
res1[10]=-1;
res1[11]=-3;
res1[12]=0;
res1[13]=-1;
res1[14]=3;
res1[15]=2;
res1[16]=0;
res1[17]=-1;
res1[18]=-3;
res1[19]=-2;
res1[20]=0;
res1[21]=3;
res1[22]=-2;
res1[23]=1;
res1[24]=0;
res1[25]=-3;
res1[26]=-2;
res1[27]=-1;
res1[28]=0;
res1[29]=3;
res1[30]=-1;
res1[31]=-2;
res1[32]=0;
res1[33]=-2;
res1[34]=-3;
res1[35]=1;
res1[36]=0;
res1[37]=-2;
res1[38]=3;
res1[39]=-1;
res1[40]=0;
res1[41]=-3;
res1[42]=-1;
res1[43]=2;
res1[44]=0;
res1[45]=2;
res1[46]=3;
res1[47]=1;
res1[48]=0;
res1[49]=3;
res1[50]=1;
res1[51]=2;
res1[52]=0;
res1[53]=-3;
res1[54]=1;
res1[55]=-2;
res1[56]=0;
res1[57]=2;
res1[58]=-3;
res1[59]=-1;
res1[60]=0;
res1[61]=2;
res1[62]=-1;
res1[63]=3;
res1[64]=0;
res1[65]=-2;
res1[66]=1;
res1[67]=3;
res1[68]=0;
res1[69]=-3;
res1[70]=2;
res1[71]=1;
res1[72]=0;
res1[73]=3;
res1[74]=2;
res1[75]=-1;
res1[76]=0;
res1[77]=1;
res1[78]=-3;
res1[79]=2;
res1[80]=0;
res1[81]=1;
res1[82]=3;
res1[83]=-2;
res1[84]=0;
res1[85]=-1;
res1[86]=-2;
res1[87]=3;
res1[88]=0;
res1[89]=-1;
res1[90]=2;
res1[91]=-3;
res1[92]=0;
res1[93]=1;
res1[94]=-2;
res1[95]=-3;
res1[96]=0;
res1[97]=-1;
res1[98]=-2;
res1[99]=-3;
res1[100]=0;
res1[101]=-2;
res1[102]=-1;
res1[103]=3;
res1[104]=0;
res1[105]=2;
res1[106]=1;
res1[107]=3;
res1[108]=0;
res1[109]=1;
res1[110]=-3;
res1[111]=-2;
res1[112]=0;
res1[113]=1;
res1[114]=3;
res1[115]=2;
res1[116]=0;
res1[117]=-3;
res1[118]=2;
res1[119]=-1;
res1[120]=0;
res1[121]=3;
res1[122]=2;
res1[123]=1;
res1[124]=0;
res1[125]=-3;
res1[126]=1;
res1[127]=2;
res1[128]=0;
res1[129]=2;
res1[130]=3;
res1[131]=-1;
res1[132]=0;
res1[133]=2;
res1[134]=-3;
res1[135]=1;
res1[136]=0;
res1[137]=3;
res1[138]=1;
res1[139]=-2;
res1[140]=0;
res1[141]=-2;
res1[142]=-3;
res1[143]=-1;
res1[144]=0;
res1[145]=-3;
res1[146]=-1;
res1[147]=-2;
res1[148]=0;
res1[149]=3;
res1[150]=-1;
res1[151]=2;
res1[152]=0;
res1[153]=-2;
res1[154]=3;
res1[155]=1;
res1[156]=0;
res1[157]=-2;
res1[158]=1;
res1[159]=-3;
res1[160]=0;
res1[161]=2;
res1[162]=-1;
res1[163]=-3;
res1[164]=0;
res1[165]=3;
res1[166]=-2;
res1[167]=-1;
res1[168]=0;
res1[169]=-3;
res1[170]=-2;
res1[171]=1;
res1[172]=0;
res1[173]=-1;
res1[174]=3;
res1[175]=-2;
res1[176]=0;
res1[177]=-1;
res1[178]=-3;
res1[179]=2;
res1[180]=0;
res1[181]=1;
res1[182]=2;
res1[183]=-3;
res1[184]=0;
res1[185]=1;
res1[186]=-2;
res1[187]=3;
res1[188]=0;
res1[189]=-1;
res1[190]=2;
res1[191]=3;
return res;
}
static double complex path0(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path1(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger( res, *w2, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path2(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 2);
w2 = pu_gauge_wrk(site,2);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger( res, *w2, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static void OP_oneTr_p_0_0_0_Ir_1_C_1_n_1(double complex * op_out)
{
*op_out =+(16.)*mom_def_Re_tr_paths[0]+(16.)*mom_def_Re_tr_paths[1]+(16.)*mom_def_Re_tr_paths[2];
}

static double complex path3(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path4(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path5(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 2);
w2 = pu_gauge_wrk(site,2);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path6(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 2);
w2 = pu_gauge_wrk(site,2);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path7(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 3);
w2 = pu_gauge_wrk(site,3);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path8(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 3);
w2 = pu_gauge_wrk(site,3);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static void OP_oneTr_p_0_0_0_Ir_1_C_1_n_2(double complex * op_out)
{
*op_out =+(8.)*mom_def_Re_tr_paths[3]+(8.)*mom_def_Re_tr_paths[4]+(8.)*mom_def_Re_tr_paths[5]+(8.)*mom_def_Re_tr_paths[6]+(8.)*mom_def_Re_tr_paths[7]+(8.)*mom_def_Re_tr_paths[8];
}

static double complex path9(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path10(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path11(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path12(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static void OP_oneTr_p_0_0_0_Ir_1_C_1_n_3(double complex * op_out)
{
*op_out =+(12.)*mom_def_Re_tr_paths[9]+(12.)*mom_def_Re_tr_paths[10]+(12.)*mom_def_Re_tr_paths[11]+(12.)*mom_def_Re_tr_paths[12];
}

static double complex path13(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path14(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path15(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger( res, *w2, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path16(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger( res, *w2, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path17(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path18(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path19(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path20(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path21(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 2);
w2 = pu_gauge_wrk(site,2);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger( res, *w2, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path22(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 2);
w2 = pu_gauge_wrk(site,2);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger( res, *w2, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path23(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,2);

site = iup_wrk(site, 2);
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path24(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,2);

site = iup_wrk(site, 2);
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static void OP_oneTr_p_0_0_0_Ir_1_C_1_n_4(double complex * op_out)
{
*op_out =+(4.)*mom_def_Re_tr_paths[13]+(4.)*mom_def_Re_tr_paths[14]+(4.)*mom_def_Re_tr_paths[15]+(4.)*mom_def_Re_tr_paths[16]+(4.)*mom_def_Re_tr_paths[17]+(4.)*mom_def_Re_tr_paths[18]+(4.)*mom_def_Re_tr_paths[19]+(4.)*mom_def_Re_tr_paths[20]+(4.)*mom_def_Re_tr_paths[21]+(4.)*mom_def_Re_tr_paths[22]+(4.)*mom_def_Re_tr_paths[23]+(4.)*mom_def_Re_tr_paths[24];
}

static double complex path25(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path26(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path27(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path28(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 1);
w2 = pu_gauge_wrk(site,1);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path29(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res, res1, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path30(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res, res1, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path31(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res, res1, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path32(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res, res1, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path33(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 2);
w2 = pu_gauge_wrk(site,2);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path34(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 2);
w2 = pu_gauge_wrk(site,2);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path35(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 2);
w2 = pu_gauge_wrk(site,2);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path36(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 2);
w2 = pu_gauge_wrk(site,2);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path37(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,2);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path38(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,2);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path39(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,2);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path40(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,2);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path41(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 3);
w2 = pu_gauge_wrk(site,3);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path42(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 3);
w2 = pu_gauge_wrk(site,3);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path43(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 3);
w2 = pu_gauge_wrk(site,3);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path44(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

site = idn_wrk(site, 3);
w2 = pu_gauge_wrk(site,3);

_suNg_dagger(res1,*w2);
w2 = &res1;
site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger( res, *w2, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path45(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,3);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 3);
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path46(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,3);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 3);
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 1);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path47(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,3);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 3);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res, res1, *w1);

w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static double complex path48(int in)
{
suNg *w1, *w2;
suNg res, res1;
int site=in;
double complex p;

w2 = pu_gauge_wrk(site,3);

site = iup_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg( res, *w2, *w1);

site = iup_wrk(site, 3);
site = idn_wrk(site, 2);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg_dagger(res1, res, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res, res1, *w1);

site = idn_wrk(site, 3);
w1 = pu_gauge_wrk(site,3);
_suNg_times_suNg_dagger(res1, res, *w1);

w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg(res, res1, *w1);

site = iup_wrk(site, 1);
w1 = pu_gauge_wrk(site,2);
_suNg_times_suNg(res1, res, *w1);

site = iup_wrk(site, 2);
site = idn_wrk(site, 1);
w1 = pu_gauge_wrk(site,1);
_suNg_times_suNg_dagger(res, res1, *w1);

_suNg_trace(p,res);
return p;
}

static void OP_oneTr_p_0_0_0_Ir_1_C_1_n_5(double complex * op_out)
{
*op_out =+(2.)*mom_def_Re_tr_paths[25]+(2.)*mom_def_Re_tr_paths[26]+(2.)*mom_def_Re_tr_paths[27]+(2.)*mom_def_Re_tr_paths[28]+(2.)*mom_def_Re_tr_paths[29]+(2.)*mom_def_Re_tr_paths[30]+(2.)*mom_def_Re_tr_paths[31]+(2.)*mom_def_Re_tr_paths[32]+(2.)*mom_def_Re_tr_paths[33]+(2.)*mom_def_Re_tr_paths[34]+(2.)*mom_def_Re_tr_paths[35]+(2.)*mom_def_Re_tr_paths[36]+(2.)*mom_def_Re_tr_paths[37]+(2.)*mom_def_Re_tr_paths[38]+(2.)*mom_def_Re_tr_paths[39]+(2.)*mom_def_Re_tr_paths[40]+(2.)*mom_def_Re_tr_paths[41]+(2.)*mom_def_Re_tr_paths[42]+(2.)*mom_def_Re_tr_paths[43]+(2.)*mom_def_Re_tr_paths[44]+(2.)*mom_def_Re_tr_paths[45]+(2.)*mom_def_Re_tr_paths[46]+(2.)*mom_def_Re_tr_paths[47]+(2.)*mom_def_Re_tr_paths[48];
}

static void OP_oneTr_p_0_0_0_Ir_3_C_1_n_1(double complex * op_out)
{
*op_out =+(16.)*mom_def_Re_tr_paths[0]+(-8.)*mom_def_Re_tr_paths[1]+(-8.)*mom_def_Re_tr_paths[2];
}

static void OP_oneTr_p_0_0_0_Ir_3_C_1_n_2(double complex * op_out)
{
*op_out =+(8.)*mom_def_Re_tr_paths[3]+(8.)*mom_def_Re_tr_paths[4]+(8.)*mom_def_Re_tr_paths[5]+(8.)*mom_def_Re_tr_paths[6]+(-16.)*mom_def_Re_tr_paths[7]+(-16.)*mom_def_Re_tr_paths[8];
}

static void OP_oneTr_p_0_0_0_Ir_3_C_1_n_3(double complex * op_out)
{
*op_out =+(-2.)*mom_def_Re_tr_paths[13]+(-2.)*mom_def_Re_tr_paths[14]+(4.)*mom_def_Re_tr_paths[15]+(4.)*mom_def_Re_tr_paths[16]+(-2.)*mom_def_Re_tr_paths[17]+(-2.)*mom_def_Re_tr_paths[18]+(4.)*mom_def_Re_tr_paths[19]+(4.)*mom_def_Re_tr_paths[20]+(-2.)*mom_def_Re_tr_paths[21]+(-2.)*mom_def_Re_tr_paths[22]+(-2.)*mom_def_Re_tr_paths[23]+(-2.)*mom_def_Re_tr_paths[24];
}

static void OP_oneTr_p_0_0_0_Ir_3_C_1_n_4(double complex * op_out)
{
*op_out =+(2.)*mom_def_Re_tr_paths[25]+(2.)*mom_def_Re_tr_paths[26]+(2.)*mom_def_Re_tr_paths[27]+(2.)*mom_def_Re_tr_paths[28]+(2.)*mom_def_Re_tr_paths[29]+(2.)*mom_def_Re_tr_paths[30]+(2.)*mom_def_Re_tr_paths[31]+(2.)*mom_def_Re_tr_paths[32]+(2.)*mom_def_Re_tr_paths[33]+(2.)*mom_def_Re_tr_paths[34]+(2.)*mom_def_Re_tr_paths[35]+(2.)*mom_def_Re_tr_paths[36]+(2.)*mom_def_Re_tr_paths[37]+(2.)*mom_def_Re_tr_paths[38]+(2.)*mom_def_Re_tr_paths[39]+(2.)*mom_def_Re_tr_paths[40]+(-4.)*mom_def_Re_tr_paths[41]+(-4.)*mom_def_Re_tr_paths[42]+(-4.)*mom_def_Re_tr_paths[43]+(-4.)*mom_def_Re_tr_paths[44]+(-4.)*mom_def_Re_tr_paths[45]+(-4.)*mom_def_Re_tr_paths[46]+(-4.)*mom_def_Re_tr_paths[47]+(-4.)*mom_def_Re_tr_paths[48];
}

static void OP_oneTr_p_0_0_1_Ir_1_C_1_n_1(double complex * op_out)
{
*op_out =+(8.)*mom_def_Re_tr_paths[0];
}

static void OP_oneTr_p_0_0_1_Ir_1_C_1_n_2(double complex * op_out)
{
*op_out =+(4.)*mom_def_Re_tr_paths[3]+(4.)*mom_def_Re_tr_paths[5];
}

static double complex c0;
static void OP_oneTr_p_0_1_0_Ir_1_C_1_n_1(double complex * op_out)
{
*op_out =+(4.)*c0*mom_def_Re_tr_paths[0]+(4.)*c0*mom_def_Re_tr_paths[2];
}

static void OP_oneTr_p_0_1_0_Ir_1_C_1_n_2(double complex * op_out)
{
*op_out =+(4.)*c0*mom_def_Re_tr_paths[3]+(4.)*c0*mom_def_Re_tr_paths[8];
}

static void OP_oneTr_p_1_0_0_Ir_1_C_1_n_1(double complex * op_out)
{
*op_out =+(4.)*c0*mom_def_Re_tr_paths[0]+(4.)*c0*mom_def_Re_tr_paths[1];
}

static double complex c1;
static void OP_oneTr_p_1_0_0_Ir_1_C_1_n_2(double complex * op_out)
{
*op_out =+(4.)*c1*mom_def_Re_tr_paths[3]+(4.)*c1*mom_def_Re_tr_paths[4];
}

static int last_t = -10;
void request_space_paths_evaluation(){last_t=-10;}

static void eval_time_momentum_glueball_paths(int t, int px, int py, int pz)
{
int n_x, n_y, n_z, idx, in;
double complex ce = 0.;
if(path_storage==NULL)
{
c0=cexp(I*PI*(-2./GLB_X));
c1=cexp(I*PI*(-4./GLB_X));
path_storage=malloc(npaths*X*Y*Z*sizeof(double complex));
mom_def_Re_tr_paths=malloc(npaths*sizeof(double complex));
mom_def_Im_tr_paths=malloc(npaths*sizeof(double complex));
}

for(in = 0; in < npaths; in++)
{
mom_def_Re_tr_paths[in]=0.;
mom_def_Im_tr_paths[in]=0.;
}
if (t != last_t)
{
last_t=t;
for (n_x = 0; n_x < X; n_x++)
for (n_y = 0; n_y < Y; n_y++)
for (n_z = 0; n_z < Z; n_z++)
{
in = ipt(t, n_x, n_y, n_z);
ce = cexp(I * 2.0 * PI * (double)(n_x * px + n_y * py + n_z * pz) / GLB_X);
idx = npaths * (n_x + X * (n_y + Y * n_z));
path_storage[0+idx]= path0(in);
mom_def_Re_tr_paths[0]+=ce*creal(path_storage[0+idx]);
mom_def_Im_tr_paths[0]+=I*ce*cimag(path_storage[0+idx]);
path_storage[1+idx]= path1(in);
mom_def_Re_tr_paths[1]+=ce*creal(path_storage[1+idx]);
mom_def_Im_tr_paths[1]+=I*ce*cimag(path_storage[1+idx]);
path_storage[2+idx]= path2(in);
mom_def_Re_tr_paths[2]+=ce*creal(path_storage[2+idx]);
mom_def_Im_tr_paths[2]+=I*ce*cimag(path_storage[2+idx]);
path_storage[3+idx]= path3(in);
mom_def_Re_tr_paths[3]+=ce*creal(path_storage[3+idx]);
mom_def_Im_tr_paths[3]+=I*ce*cimag(path_storage[3+idx]);
path_storage[4+idx]= path4(in);
mom_def_Re_tr_paths[4]+=ce*creal(path_storage[4+idx]);
mom_def_Im_tr_paths[4]+=I*ce*cimag(path_storage[4+idx]);
path_storage[5+idx]= path5(in);
mom_def_Re_tr_paths[5]+=ce*creal(path_storage[5+idx]);
mom_def_Im_tr_paths[5]+=I*ce*cimag(path_storage[5+idx]);
path_storage[6+idx]= path6(in);
mom_def_Re_tr_paths[6]+=ce*creal(path_storage[6+idx]);
mom_def_Im_tr_paths[6]+=I*ce*cimag(path_storage[6+idx]);
path_storage[7+idx]= path7(in);
mom_def_Re_tr_paths[7]+=ce*creal(path_storage[7+idx]);
mom_def_Im_tr_paths[7]+=I*ce*cimag(path_storage[7+idx]);
path_storage[8+idx]= path8(in);
mom_def_Re_tr_paths[8]+=ce*creal(path_storage[8+idx]);
mom_def_Im_tr_paths[8]+=I*ce*cimag(path_storage[8+idx]);
path_storage[9+idx]= path9(in);
mom_def_Re_tr_paths[9]+=ce*creal(path_storage[9+idx]);
mom_def_Im_tr_paths[9]+=I*ce*cimag(path_storage[9+idx]);
path_storage[10+idx]= path10(in);
mom_def_Re_tr_paths[10]+=ce*creal(path_storage[10+idx]);
mom_def_Im_tr_paths[10]+=I*ce*cimag(path_storage[10+idx]);
path_storage[11+idx]= path11(in);
mom_def_Re_tr_paths[11]+=ce*creal(path_storage[11+idx]);
mom_def_Im_tr_paths[11]+=I*ce*cimag(path_storage[11+idx]);
path_storage[12+idx]= path12(in);
mom_def_Re_tr_paths[12]+=ce*creal(path_storage[12+idx]);
mom_def_Im_tr_paths[12]+=I*ce*cimag(path_storage[12+idx]);
path_storage[13+idx]= path13(in);
mom_def_Re_tr_paths[13]+=ce*creal(path_storage[13+idx]);
mom_def_Im_tr_paths[13]+=I*ce*cimag(path_storage[13+idx]);
path_storage[14+idx]= path14(in);
mom_def_Re_tr_paths[14]+=ce*creal(path_storage[14+idx]);
mom_def_Im_tr_paths[14]+=I*ce*cimag(path_storage[14+idx]);
path_storage[15+idx]= path15(in);
mom_def_Re_tr_paths[15]+=ce*creal(path_storage[15+idx]);
mom_def_Im_tr_paths[15]+=I*ce*cimag(path_storage[15+idx]);
path_storage[16+idx]= path16(in);
mom_def_Re_tr_paths[16]+=ce*creal(path_storage[16+idx]);
mom_def_Im_tr_paths[16]+=I*ce*cimag(path_storage[16+idx]);
path_storage[17+idx]= path17(in);
mom_def_Re_tr_paths[17]+=ce*creal(path_storage[17+idx]);
mom_def_Im_tr_paths[17]+=I*ce*cimag(path_storage[17+idx]);
path_storage[18+idx]= path18(in);
mom_def_Re_tr_paths[18]+=ce*creal(path_storage[18+idx]);
mom_def_Im_tr_paths[18]+=I*ce*cimag(path_storage[18+idx]);
path_storage[19+idx]= path19(in);
mom_def_Re_tr_paths[19]+=ce*creal(path_storage[19+idx]);
mom_def_Im_tr_paths[19]+=I*ce*cimag(path_storage[19+idx]);
path_storage[20+idx]= path20(in);
mom_def_Re_tr_paths[20]+=ce*creal(path_storage[20+idx]);
mom_def_Im_tr_paths[20]+=I*ce*cimag(path_storage[20+idx]);
path_storage[21+idx]= path21(in);
mom_def_Re_tr_paths[21]+=ce*creal(path_storage[21+idx]);
mom_def_Im_tr_paths[21]+=I*ce*cimag(path_storage[21+idx]);
path_storage[22+idx]= path22(in);
mom_def_Re_tr_paths[22]+=ce*creal(path_storage[22+idx]);
mom_def_Im_tr_paths[22]+=I*ce*cimag(path_storage[22+idx]);
path_storage[23+idx]= path23(in);
mom_def_Re_tr_paths[23]+=ce*creal(path_storage[23+idx]);
mom_def_Im_tr_paths[23]+=I*ce*cimag(path_storage[23+idx]);
path_storage[24+idx]= path24(in);
mom_def_Re_tr_paths[24]+=ce*creal(path_storage[24+idx]);
mom_def_Im_tr_paths[24]+=I*ce*cimag(path_storage[24+idx]);
path_storage[25+idx]= path25(in);
mom_def_Re_tr_paths[25]+=ce*creal(path_storage[25+idx]);
mom_def_Im_tr_paths[25]+=I*ce*cimag(path_storage[25+idx]);
path_storage[26+idx]= path26(in);
mom_def_Re_tr_paths[26]+=ce*creal(path_storage[26+idx]);
mom_def_Im_tr_paths[26]+=I*ce*cimag(path_storage[26+idx]);
path_storage[27+idx]= path27(in);
mom_def_Re_tr_paths[27]+=ce*creal(path_storage[27+idx]);
mom_def_Im_tr_paths[27]+=I*ce*cimag(path_storage[27+idx]);
path_storage[28+idx]= path28(in);
mom_def_Re_tr_paths[28]+=ce*creal(path_storage[28+idx]);
mom_def_Im_tr_paths[28]+=I*ce*cimag(path_storage[28+idx]);
path_storage[29+idx]= path29(in);
mom_def_Re_tr_paths[29]+=ce*creal(path_storage[29+idx]);
mom_def_Im_tr_paths[29]+=I*ce*cimag(path_storage[29+idx]);
path_storage[30+idx]= path30(in);
mom_def_Re_tr_paths[30]+=ce*creal(path_storage[30+idx]);
mom_def_Im_tr_paths[30]+=I*ce*cimag(path_storage[30+idx]);
path_storage[31+idx]= path31(in);
mom_def_Re_tr_paths[31]+=ce*creal(path_storage[31+idx]);
mom_def_Im_tr_paths[31]+=I*ce*cimag(path_storage[31+idx]);
path_storage[32+idx]= path32(in);
mom_def_Re_tr_paths[32]+=ce*creal(path_storage[32+idx]);
mom_def_Im_tr_paths[32]+=I*ce*cimag(path_storage[32+idx]);
path_storage[33+idx]= path33(in);
mom_def_Re_tr_paths[33]+=ce*creal(path_storage[33+idx]);
mom_def_Im_tr_paths[33]+=I*ce*cimag(path_storage[33+idx]);
path_storage[34+idx]= path34(in);
mom_def_Re_tr_paths[34]+=ce*creal(path_storage[34+idx]);
mom_def_Im_tr_paths[34]+=I*ce*cimag(path_storage[34+idx]);
path_storage[35+idx]= path35(in);
mom_def_Re_tr_paths[35]+=ce*creal(path_storage[35+idx]);
mom_def_Im_tr_paths[35]+=I*ce*cimag(path_storage[35+idx]);
path_storage[36+idx]= path36(in);
mom_def_Re_tr_paths[36]+=ce*creal(path_storage[36+idx]);
mom_def_Im_tr_paths[36]+=I*ce*cimag(path_storage[36+idx]);
path_storage[37+idx]= path37(in);
mom_def_Re_tr_paths[37]+=ce*creal(path_storage[37+idx]);
mom_def_Im_tr_paths[37]+=I*ce*cimag(path_storage[37+idx]);
path_storage[38+idx]= path38(in);
mom_def_Re_tr_paths[38]+=ce*creal(path_storage[38+idx]);
mom_def_Im_tr_paths[38]+=I*ce*cimag(path_storage[38+idx]);
path_storage[39+idx]= path39(in);
mom_def_Re_tr_paths[39]+=ce*creal(path_storage[39+idx]);
mom_def_Im_tr_paths[39]+=I*ce*cimag(path_storage[39+idx]);
path_storage[40+idx]= path40(in);
mom_def_Re_tr_paths[40]+=ce*creal(path_storage[40+idx]);
mom_def_Im_tr_paths[40]+=I*ce*cimag(path_storage[40+idx]);
path_storage[41+idx]= path41(in);
mom_def_Re_tr_paths[41]+=ce*creal(path_storage[41+idx]);
mom_def_Im_tr_paths[41]+=I*ce*cimag(path_storage[41+idx]);
path_storage[42+idx]= path42(in);
mom_def_Re_tr_paths[42]+=ce*creal(path_storage[42+idx]);
mom_def_Im_tr_paths[42]+=I*ce*cimag(path_storage[42+idx]);
path_storage[43+idx]= path43(in);
mom_def_Re_tr_paths[43]+=ce*creal(path_storage[43+idx]);
mom_def_Im_tr_paths[43]+=I*ce*cimag(path_storage[43+idx]);
path_storage[44+idx]= path44(in);
mom_def_Re_tr_paths[44]+=ce*creal(path_storage[44+idx]);
mom_def_Im_tr_paths[44]+=I*ce*cimag(path_storage[44+idx]);
path_storage[45+idx]= path45(in);
mom_def_Re_tr_paths[45]+=ce*creal(path_storage[45+idx]);
mom_def_Im_tr_paths[45]+=I*ce*cimag(path_storage[45+idx]);
path_storage[46+idx]= path46(in);
mom_def_Re_tr_paths[46]+=ce*creal(path_storage[46+idx]);
mom_def_Im_tr_paths[46]+=I*ce*cimag(path_storage[46+idx]);
path_storage[47+idx]= path47(in);
mom_def_Re_tr_paths[47]+=ce*creal(path_storage[47+idx]);
mom_def_Im_tr_paths[47]+=I*ce*cimag(path_storage[47+idx]);
path_storage[48+idx]= path48(in);
mom_def_Re_tr_paths[48]+=ce*creal(path_storage[48+idx]);
mom_def_Im_tr_paths[48]+=I*ce*cimag(path_storage[48+idx]);
}
}
else{
for (n_x = 0; n_x < X; n_x++)
for (n_y = 0; n_y < Y; n_y++)
for (n_z = 0; n_z < Z; n_z++)
{
ce = cexp(I * 2.0 * PI * (double)(n_x * px + n_y * py + n_z * pz) / GLB_X);
idx = npaths * (n_x + X * (n_y + Y * n_z));
for (int i = 0; i < 49; i++)
{
mom_def_Re_tr_paths[i]+=ce*creal(path_storage[i+idx]);
mom_def_Im_tr_paths[i]+=I*ce*cimag(path_storage[i+idx]);
}
}
}
};
void eval_all_glueball_ops(int t, double complex *numerical_op_out)
{
    static double complex *numerical_op = NULL;
    if (numerical_op == NULL)
    {
        numerical_op = malloc(total_n_glue_op * sizeof(double complex));
    }
    request_space_paths_evaluation();
    eval_time_momentum_glueball_paths(t,0,0,0);
OP_oneTr_p_0_0_0_Ir_1_C_1_n_1(numerical_op+0);
OP_oneTr_p_0_0_0_Ir_1_C_1_n_2(numerical_op+1);
OP_oneTr_p_0_0_0_Ir_1_C_1_n_3(numerical_op+2);
OP_oneTr_p_0_0_0_Ir_1_C_1_n_4(numerical_op+3);
OP_oneTr_p_0_0_0_Ir_1_C_1_n_5(numerical_op+4);
OP_oneTr_p_0_0_0_Ir_3_C_1_n_1(numerical_op+7);
OP_oneTr_p_0_0_0_Ir_3_C_1_n_2(numerical_op+8);
OP_oneTr_p_0_0_0_Ir_3_C_1_n_3(numerical_op+9);
OP_oneTr_p_0_0_0_Ir_3_C_1_n_4(numerical_op+10);
eval_time_momentum_glueball_paths(t,0,0,1);
OP_oneTr_p_0_0_1_Ir_1_C_1_n_1(numerical_op+11);
OP_oneTr_p_0_0_1_Ir_1_C_1_n_2(numerical_op+12);
eval_time_momentum_glueball_paths(t,0,1,0);
OP_oneTr_p_0_1_0_Ir_1_C_1_n_1(numerical_op+13);
OP_oneTr_p_0_1_0_Ir_1_C_1_n_2(numerical_op+14);
eval_time_momentum_glueball_paths(t,1,0,0);
OP_oneTr_p_1_0_0_Ir_1_C_1_n_1(numerical_op+15);
OP_oneTr_p_1_0_0_Ir_1_C_1_n_2(numerical_op+16);
*(numerical_op+5)=+(0.816496580927726033)*(conj(*(numerical_op+11)))*((*(numerical_op+11)))+(0.816496580927726033)*(conj(*(numerical_op+13)))*((*(numerical_op+13)))+(0.816496580927726033)*(conj(*(numerical_op+15)))*((*(numerical_op+15)));
*(numerical_op+6)=+(0.816496580927726033)*(conj(*(numerical_op+12)))*((*(numerical_op+12)))+(0.816496580927726033)*(conj(*(numerical_op+14)))*((*(numerical_op+14)))+(0.816496580927726033)*(conj(*(numerical_op+16)))*((*(numerical_op+16)));
    for(int i=0;i<total_n_glue_op;i++)
        *(numerical_op_out+i)+=*(numerical_op+i);
}
void eval_all_glueball_oneTr_ops_p_0_0_0_Ir_1_C_1(double complex * numerical_op)
{
OP_oneTr_p_0_0_0_Ir_1_C_1_n_1(numerical_op+0);
OP_oneTr_p_0_0_0_Ir_1_C_1_n_2(numerical_op+1);
OP_oneTr_p_0_0_0_Ir_1_C_1_n_3(numerical_op+2);
OP_oneTr_p_0_0_0_Ir_1_C_1_n_4(numerical_op+3);
OP_oneTr_p_0_0_0_Ir_1_C_1_n_5(numerical_op+4);
OP_oneTr_p_0_0_0_Ir_1_C_1_n_-2(numerical_op+5);
OP_oneTr_p_0_0_0_Ir_1_C_1_n_-2(numerical_op+6);
}

void eval_all_glueball_oneTr_ops_p_0_0_0_Ir_3_C_1(double complex * numerical_op)
{
OP_oneTr_p_0_0_0_Ir_3_C_1_n_1(numerical_op+0);
OP_oneTr_p_0_0_0_Ir_3_C_1_n_2(numerical_op+1);
OP_oneTr_p_0_0_0_Ir_3_C_1_n_3(numerical_op+2);
OP_oneTr_p_0_0_0_Ir_3_C_1_n_4(numerical_op+3);
}

void eval_all_glueball_oneTr_ops_p_0_0_1_Ir_1_C_1(double complex * numerical_op)
{
OP_oneTr_p_0_0_1_Ir_1_C_1_n_1(numerical_op+0);
OP_oneTr_p_0_0_1_Ir_1_C_1_n_2(numerical_op+1);
}

void eval_all_glueball_oneTr_ops_p_0_1_0_Ir_1_C_1(double complex * numerical_op)
{
OP_oneTr_p_0_1_0_Ir_1_C_1_n_1(numerical_op+0);
OP_oneTr_p_0_1_0_Ir_1_C_1_n_2(numerical_op+1);
}

void eval_all_glueball_oneTr_ops_p_1_0_0_Ir_1_C_1(double complex * numerical_op)
{
OP_oneTr_p_1_0_0_Ir_1_C_1_n_1(numerical_op+0);
OP_oneTr_p_1_0_0_Ir_1_C_1_n_2(numerical_op+1);
}


void evaluate_correlators(cor_list *lcor, int nblocking, double complex *gb_storage, double *cor_storage)
{
    int totalsize, i1, i2, t1, t2, id, n1, n2, b1, b2, icor, i;
    double norm;
    double *cor_pointer, tmp;
    static double complex *gb1_bf;
    static int n_total_active_slices = 0;    
    static int *listactive = NULL;
    if (listactive == NULL)
    {
        listactive = malloc(sizeof(int) * GLB_T);
        for (i = 0; i < GLB_T; i++)
            listactive[i] = -1;

        for (i = 0; i < lcor->n_entries; i++)
        {
            listactive[lcor->list[i].t1] = 1;
            listactive[lcor->list[i].t2] = 1;
        }

        for (i = 0; i < GLB_T; i++)
            if (listactive[i] == 1)
            {
                listactive[i] = n_total_active_slices;
                n_total_active_slices++;
            }
    }


#ifdef WITH_MPI
    static int *t_to_proc = NULL;
    static int *listsent = NULL;

    if (t_to_proc == NULL)
    {
        listsent = malloc(sizeof(int) * GLB_T);

        gb1_bf = malloc(sizeof(double complex) * total_n_glue_op * nblocking * n_total_active_slices);

        t_to_proc = malloc(sizeof(int) * GLB_T);
        for (i = 0; i < GLB_T; i++)
        {
            int x[4] = {i, 0, 0, 0}, p[4];
            glb_to_proc(x, p);
            t_to_proc[i] = p[0];
        }
    }

    for (i = 0; i < GLB_T; i++)
        listsent[i] = -1;

    MPI_Status r1, r2;
#else
    gb1_bf = gb_storage;
#endif

    static double complex *gb1;
    static double complex *gb2;

    for (int icor = 0; icor < lcor->n_entries; icor++)
    {
        t1 = glbT_to_active_slices[lcor->list[icor].t1];
        t2 = glbT_to_active_slices[lcor->list[icor].t2];
        id = lcor->list[icor].id;
        gb1 = gb1_bf + total_n_glue_op * nblocking * listactive[lcor->list[icor].t1];
        gb2 = gb1_bf + total_n_glue_op * nblocking * listactive[lcor->list[icor].t2];

#ifdef WITH_MPI

        if (listsent[lcor->list[icor].t1] == -1)
        {
            if (t1 != -1)
            {
                if (PID == 0)
                {
                    memcpy(gb1, gb_storage + t1 * total_n_glue_op * nblocking, sizeof(double complex) * total_n_glue_op * nblocking);
                }
                else
                {
                    MPI_Send(gb_storage + t1 * total_n_glue_op * nblocking, total_n_glue_op * nblocking * 2, MPI_DOUBLE, 0, lcor->list[icor].t1, cart_comm);
                }
            }

            if (PID == 0 && t1 == -1)
            {
                MPI_Recv(gb1, total_n_glue_op * nblocking * 2, MPI_DOUBLE, t_to_proc[lcor->list[icor].t1], lcor->list[icor].t1, cart_comm, &r1);
            }
            listsent[lcor->list[icor].t1] = 0;
        }

      if (lcor->list[icor].t1 != lcor->list[icor].t2)
        {
            if (listsent[lcor->list[icor].t2] == -1)
            {
                if (t2 != -1)
                {
                    if (PID == 0)
                    {
                        memcpy(gb2, gb_storage + t2 * total_n_glue_op * nblocking, sizeof(double complex) * total_n_glue_op * nblocking);
                    }
                    else
                    {
                        MPI_Send(gb_storage + t2 * total_n_glue_op * nblocking, total_n_glue_op * nblocking * 2, MPI_DOUBLE, 0, GLB_T + lcor->list[icor].t2, cart_comm);
                    }
                }

                if (PID == 0 && t2 == -1)
                {
                    MPI_Recv(gb2, total_n_glue_op * nblocking * 2, MPI_DOUBLE, t_to_proc[lcor->list[icor].t2], GLB_T + lcor->list[icor].t2, cart_comm, &r2);
                }
                listsent[lcor->list[icor].t2] = 0;
            }
        }
#endif

        totalsize = 0;
        norm = 0.5 / lcor->list[icor].n_pairs;
        
        cor_pointer = cor_storage + totalsize + id * nblocking * nblocking * 49;

        for (n1 = 0; n1 < nblocking; n1++)
            for (b1 = 0; b1 < 7; b1++)
            {
                i1 = 0 + b1 + total_n_glue_op * n1;

                n2 = n1;
                b2 = b1;
                i2 = 0 + b2 + total_n_glue_op * n2;
                tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                cor_pointer[b1 + 7 * (n1 + nblocking * (b2 + 7 * n2))] += tmp;


                for (b2 = b1 + 1; b2 < 7; b2++)
                {
                    i2 = 0 + b2 + total_n_glue_op * n2;
                    tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                    cor_pointer[b1 + 7 * (n1 + nblocking * (b2 + 7 * n2))] += tmp;
                    cor_pointer[b2 + 7 * (n2 + nblocking * (b1 + 7 * n1))] += tmp;
                }

                for (n2 = n1 + 1; n2 < nblocking; n2++)
                    for (b2 = 0; b2 < 7; b2++)
                    {
                        i2 = 0 + b2 + total_n_glue_op * n2;
                        tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                        cor_pointer[b1 + 7 * (n1 + nblocking * (b2 + 7 * n2))] += tmp;
                        cor_pointer[b2 + 7 * (n2 + nblocking * (b1 + 7 * n1))] += tmp;
                    }
            }
        totalsize += (nblocking * nblocking * 49 * (lcor->n_corrs));
        
        cor_pointer = cor_storage + totalsize + id * nblocking * nblocking * 16;

        for (n1 = 0; n1 < nblocking; n1++)
            for (b1 = 0; b1 < 4; b1++)
            {
                i1 = 7 + b1 + total_n_glue_op * n1;

                n2 = n1;
                b2 = b1;
                i2 = 7 + b2 + total_n_glue_op * n2;
                tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                cor_pointer[b1 + 4 * (n1 + nblocking * (b2 + 4 * n2))] += tmp;


                for (b2 = b1 + 1; b2 < 4; b2++)
                {
                    i2 = 7 + b2 + total_n_glue_op * n2;
                    tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                    cor_pointer[b1 + 4 * (n1 + nblocking * (b2 + 4 * n2))] += tmp;
                    cor_pointer[b2 + 4 * (n2 + nblocking * (b1 + 4 * n1))] += tmp;
                }

                for (n2 = n1 + 1; n2 < nblocking; n2++)
                    for (b2 = 0; b2 < 4; b2++)
                    {
                        i2 = 7 + b2 + total_n_glue_op * n2;
                        tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                        cor_pointer[b1 + 4 * (n1 + nblocking * (b2 + 4 * n2))] += tmp;
                        cor_pointer[b2 + 4 * (n2 + nblocking * (b1 + 4 * n1))] += tmp;
                    }
            }
        totalsize += (nblocking * nblocking * 16 * (lcor->n_corrs));
        
        cor_pointer = cor_storage + totalsize + id * nblocking * nblocking * 4;

        for (n1 = 0; n1 < nblocking; n1++)
            for (b1 = 0; b1 < 2; b1++)
            {
                i1 = 11 + b1 + total_n_glue_op * n1;

                n2 = n1;
                b2 = b1;
                i2 = 11 + b2 + total_n_glue_op * n2;
                tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                cor_pointer[b1 + 2 * (n1 + nblocking * (b2 + 2 * n2))] += tmp;


                for (b2 = b1 + 1; b2 < 2; b2++)
                {
                    i2 = 11 + b2 + total_n_glue_op * n2;
                    tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                    cor_pointer[b1 + 2 * (n1 + nblocking * (b2 + 2 * n2))] += tmp;
                    cor_pointer[b2 + 2 * (n2 + nblocking * (b1 + 2 * n1))] += tmp;
                }

                for (n2 = n1 + 1; n2 < nblocking; n2++)
                    for (b2 = 0; b2 < 2; b2++)
                    {
                        i2 = 11 + b2 + total_n_glue_op * n2;
                        tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                        cor_pointer[b1 + 2 * (n1 + nblocking * (b2 + 2 * n2))] += tmp;
                        cor_pointer[b2 + 2 * (n2 + nblocking * (b1 + 2 * n1))] += tmp;
                    }
            }
        totalsize += (nblocking * nblocking * 4 * (lcor->n_corrs));
        
        cor_pointer = cor_storage + totalsize + id * nblocking * nblocking * 4;

        for (n1 = 0; n1 < nblocking; n1++)
            for (b1 = 0; b1 < 2; b1++)
            {
                i1 = 13 + b1 + total_n_glue_op * n1;

                n2 = n1;
                b2 = b1;
                i2 = 13 + b2 + total_n_glue_op * n2;
                tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                cor_pointer[b1 + 2 * (n1 + nblocking * (b2 + 2 * n2))] += tmp;


                for (b2 = b1 + 1; b2 < 2; b2++)
                {
                    i2 = 13 + b2 + total_n_glue_op * n2;
                    tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                    cor_pointer[b1 + 2 * (n1 + nblocking * (b2 + 2 * n2))] += tmp;
                    cor_pointer[b2 + 2 * (n2 + nblocking * (b1 + 2 * n1))] += tmp;
                }

                for (n2 = n1 + 1; n2 < nblocking; n2++)
                    for (b2 = 0; b2 < 2; b2++)
                    {
                        i2 = 13 + b2 + total_n_glue_op * n2;
                        tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                        cor_pointer[b1 + 2 * (n1 + nblocking * (b2 + 2 * n2))] += tmp;
                        cor_pointer[b2 + 2 * (n2 + nblocking * (b1 + 2 * n1))] += tmp;
                    }
            }
        totalsize += (nblocking * nblocking * 4 * (lcor->n_corrs));
        
        cor_pointer = cor_storage + totalsize + id * nblocking * nblocking * 4;

        for (n1 = 0; n1 < nblocking; n1++)
            for (b1 = 0; b1 < 2; b1++)
            {
                i1 = 15 + b1 + total_n_glue_op * n1;

                n2 = n1;
                b2 = b1;
                i2 = 15 + b2 + total_n_glue_op * n2;
                tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                cor_pointer[b1 + 2 * (n1 + nblocking * (b2 + 2 * n2))] += tmp;


                for (b2 = b1 + 1; b2 < 2; b2++)
                {
                    i2 = 15 + b2 + total_n_glue_op * n2;
                    tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                    cor_pointer[b1 + 2 * (n1 + nblocking * (b2 + 2 * n2))] += tmp;
                    cor_pointer[b2 + 2 * (n2 + nblocking * (b1 + 2 * n1))] += tmp;
                }

                for (n2 = n1 + 1; n2 < nblocking; n2++)
                    for (b2 = 0; b2 < 2; b2++)
                    {
                        i2 = 15 + b2 + total_n_glue_op * n2;
                        tmp = norm * creal(conj(gb1[i1]) * gb2[i2] + gb1[i2] * conj(gb2[i1]));
                        cor_pointer[b1 + 2 * (n1 + nblocking * (b2 + 2 * n2))] += tmp;
                        cor_pointer[b2 + 2 * (n2 + nblocking * (b1 + 2 * n1))] += tmp;
                    }
            }
        totalsize += (nblocking * nblocking * 4 * (lcor->n_corrs));
}

totalsize = 0 ;

    lprintf("Measure ML", 0, "\n1pt function P=(0,0,0) Irrep=A1plusOhP Irrep ev=1/1 Charge=+ nop=%d\n",7 * nblocking );
    lprintf("Measure ML", 0, "Op id= 0 1 2 3 4 5 6 (repeated nblocking times)\n");
    for (n1 = 0; n1 < GLB_T; n1++)
        if (listactive[n1] > -1)
        {
            lprintf("Measure ML", 0, " t=%d", n1);
            for (n2 = 0; n2 < nblocking; n2++)
                for (i = 0; i < 7; i++)
                    lprintf("Measure ML", 0, " ( %.10e %.10e )", creal(gb1_bf[i + total_n_glue_op * (n2 + nblocking * listactive[n1])]),
                            cimag(gb1_bf[i + total_n_glue_op * (n2 + nblocking * listactive[n1])]));
            lprintf("Measure ML", 0, "\n");
        }

    b2 = 0;
    b1 = 0;
    
    lprintf("Measure ML", 0,"\nCorr Total P=(0,0,0) Irrep=A1plusOhP Irrep ev=1/1 Charge=+\n");
   

    for (icor = 0; icor < lcor->n_corrs; icor++)
    {
        cor_pointer = cor_storage + totalsize;
        lprintf("Measure ML", 0, "\n Corr points: ");
        n2=lcor->list[b1].n_pairs;
        for (b2 = 0; b2 < n2; b2++)
        {
            lprintf("Measure ML", 0, "( %d %d ) ", lcor->list[b1].t2, lcor->list[b1].t1);
            b1++;
        }
        lprintf("Measure ML", 0, "\n");

        for (i1 = 0; i1 < (nblocking * 7); i1++)
        {
            for (i2 = 0; i2 < (nblocking * 7); i2++)
                lprintf("Measure ML", 0, " ( %.6e ) ", cor_pointer[i1 + nblocking * 7 * i2]);

            lprintf("Measure ML", 0, "\n");
        }
        totalsize += (nblocking * nblocking * 49);
    }

    lprintf("Measure ML", 0, "\n1pt function P=(0,0,0) Irrep=EplusOhP Irrep ev=1/2 Charge=+ nop=%d\n",4 * nblocking );
    lprintf("Measure ML", 0, "Op id= 7 8 9 10 (repeated nblocking times)\n");
    for (n1 = 0; n1 < GLB_T; n1++)
        if (listactive[n1] > -1)
        {
            lprintf("Measure ML", 0, " t=%d", n1);
            for (n2 = 0; n2 < nblocking; n2++)
                for (i = 7; i < 11; i++)
                    lprintf("Measure ML", 0, " ( %.10e %.10e )", creal(gb1_bf[i + total_n_glue_op * (n2 + nblocking * listactive[n1])]),
                            cimag(gb1_bf[i + total_n_glue_op * (n2 + nblocking * listactive[n1])]));
            lprintf("Measure ML", 0, "\n");
        }

    b2 = 0;
    b1 = 0;
    
    lprintf("Measure ML", 0,"\nCorr Total P=(0,0,0) Irrep=EplusOhP Irrep ev=1/2 Charge=+\n");
   

    for (icor = 0; icor < lcor->n_corrs; icor++)
    {
        cor_pointer = cor_storage + totalsize;
        lprintf("Measure ML", 0, "\n Corr points: ");
        n2=lcor->list[b1].n_pairs;
        for (b2 = 0; b2 < n2; b2++)
        {
            lprintf("Measure ML", 0, "( %d %d ) ", lcor->list[b1].t2, lcor->list[b1].t1);
            b1++;
        }
        lprintf("Measure ML", 0, "\n");

        for (i1 = 0; i1 < (nblocking * 4); i1++)
        {
            for (i2 = 0; i2 < (nblocking * 4); i2++)
                lprintf("Measure ML", 0, " ( %.6e ) ", cor_pointer[i1 + nblocking * 4 * i2]);

            lprintf("Measure ML", 0, "\n");
        }
        totalsize += (nblocking * nblocking * 16);
    }

    lprintf("Measure ML", 0, "\n1pt function P=(0,0,1) Irrep=A1Dic4 Irrep ev=1/1 Charge=+ nop=%d\n",2 * nblocking );
    lprintf("Measure ML", 0, "Op id= 11 12 (repeated nblocking times)\n");
    for (n1 = 0; n1 < GLB_T; n1++)
        if (listactive[n1] > -1)
        {
            lprintf("Measure ML", 0, " t=%d", n1);
            for (n2 = 0; n2 < nblocking; n2++)
                for (i = 11; i < 13; i++)
                    lprintf("Measure ML", 0, " ( %.10e %.10e )", creal(gb1_bf[i + total_n_glue_op * (n2 + nblocking * listactive[n1])]),
                            cimag(gb1_bf[i + total_n_glue_op * (n2 + nblocking * listactive[n1])]));
            lprintf("Measure ML", 0, "\n");
        }

    b2 = 0;
    b1 = 0;
    
    lprintf("Measure ML", 0,"\nCorr Total P=(0,0,1) Irrep=A1Dic4 Irrep ev=1/1 Charge=+\n");
   

    for (icor = 0; icor < lcor->n_corrs; icor++)
    {
        cor_pointer = cor_storage + totalsize;
        lprintf("Measure ML", 0, "\n Corr points: ");
        n2=lcor->list[b1].n_pairs;
        for (b2 = 0; b2 < n2; b2++)
        {
            lprintf("Measure ML", 0, "( %d %d ) ", lcor->list[b1].t2, lcor->list[b1].t1);
            b1++;
        }
        lprintf("Measure ML", 0, "\n");

        for (i1 = 0; i1 < (nblocking * 2); i1++)
        {
            for (i2 = 0; i2 < (nblocking * 2); i2++)
                lprintf("Measure ML", 0, " ( %.6e ) ", cor_pointer[i1 + nblocking * 2 * i2]);

            lprintf("Measure ML", 0, "\n");
        }
        totalsize += (nblocking * nblocking * 4);
    }

    lprintf("Measure ML", 0, "\n1pt function P=(0,1,0) Irrep=A1Dic4 Irrep ev=1/1 Charge=+ nop=%d\n",2 * nblocking );
    lprintf("Measure ML", 0, "Op id= 13 14 (repeated nblocking times)\n");
    for (n1 = 0; n1 < GLB_T; n1++)
        if (listactive[n1] > -1)
        {
            lprintf("Measure ML", 0, " t=%d", n1);
            for (n2 = 0; n2 < nblocking; n2++)
                for (i = 13; i < 15; i++)
                    lprintf("Measure ML", 0, " ( %.10e %.10e )", creal(gb1_bf[i + total_n_glue_op * (n2 + nblocking * listactive[n1])]),
                            cimag(gb1_bf[i + total_n_glue_op * (n2 + nblocking * listactive[n1])]));
            lprintf("Measure ML", 0, "\n");
        }

    b2 = 0;
    b1 = 0;
    
    lprintf("Measure ML", 0,"\nCorr Total P=(0,1,0) Irrep=A1Dic4 Irrep ev=1/1 Charge=+\n");
   

    for (icor = 0; icor < lcor->n_corrs; icor++)
    {
        cor_pointer = cor_storage + totalsize;
        lprintf("Measure ML", 0, "\n Corr points: ");
        n2=lcor->list[b1].n_pairs;
        for (b2 = 0; b2 < n2; b2++)
        {
            lprintf("Measure ML", 0, "( %d %d ) ", lcor->list[b1].t2, lcor->list[b1].t1);
            b1++;
        }
        lprintf("Measure ML", 0, "\n");

        for (i1 = 0; i1 < (nblocking * 2); i1++)
        {
            for (i2 = 0; i2 < (nblocking * 2); i2++)
                lprintf("Measure ML", 0, " ( %.6e ) ", cor_pointer[i1 + nblocking * 2 * i2]);

            lprintf("Measure ML", 0, "\n");
        }
        totalsize += (nblocking * nblocking * 4);
    }

    lprintf("Measure ML", 0, "\n1pt function P=(1,0,0) Irrep=A1Dic4 Irrep ev=1/1 Charge=+ nop=%d\n",2 * nblocking );
    lprintf("Measure ML", 0, "Op id= 15 16 (repeated nblocking times)\n");
    for (n1 = 0; n1 < GLB_T; n1++)
        if (listactive[n1] > -1)
        {
            lprintf("Measure ML", 0, " t=%d", n1);
            for (n2 = 0; n2 < nblocking; n2++)
                for (i = 15; i < 17; i++)
                    lprintf("Measure ML", 0, " ( %.10e %.10e )", creal(gb1_bf[i + total_n_glue_op * (n2 + nblocking * listactive[n1])]),
                            cimag(gb1_bf[i + total_n_glue_op * (n2 + nblocking * listactive[n1])]));
            lprintf("Measure ML", 0, "\n");
        }

    b2 = 0;
    b1 = 0;
    
    lprintf("Measure ML", 0,"\nCorr Total P=(1,0,0) Irrep=A1Dic4 Irrep ev=1/1 Charge=+\n");
   

    for (icor = 0; icor < lcor->n_corrs; icor++)
    {
        cor_pointer = cor_storage + totalsize;
        lprintf("Measure ML", 0, "\n Corr points: ");
        n2=lcor->list[b1].n_pairs;
        for (b2 = 0; b2 < n2; b2++)
        {
            lprintf("Measure ML", 0, "( %d %d ) ", lcor->list[b1].t2, lcor->list[b1].t1);
            b1++;
        }
        lprintf("Measure ML", 0, "\n");

        for (i1 = 0; i1 < (nblocking * 2); i1++)
        {
            for (i2 = 0; i2 < (nblocking * 2); i2++)
                lprintf("Measure ML", 0, " ( %.6e ) ", cor_pointer[i1 + nblocking * 2 * i2]);

            lprintf("Measure ML", 0, "\n");
        }
        totalsize += (nblocking * nblocking * 4);
    }
}
void report_op_group_setup()
{
lprintf("INIT Measure ML",0,"\n1pt Irrep multiplets Total P=(0,0,0) Irrep=A1plusOhP Charge=+");
lprintf("INIT Measure ML",0," |0|1|2|3|4|2tr|2tr|");
lprintf("INIT Measure ML",0,"\n1pt Irrep multiplets Total P=(0,0,0) Irrep=EplusOhP Charge=+");
lprintf("INIT Measure ML",0," |7,na|8,na|9,na|10,na|");
lprintf("INIT Measure ML",0,"\n1pt Irrep multiplets Total P=(0,0,1) Irrep=A1Dic4 Charge=+");
lprintf("INIT Measure ML",0," |11|12|");
lprintf("INIT Measure ML",0,"\n1pt Irrep multiplets Total P=(0,1,0) Irrep=A1Dic4 Charge=+");
lprintf("INIT Measure ML",0," |13|14|");
lprintf("INIT Measure ML",0,"\n1pt Irrep multiplets Total P=(1,0,0) Irrep=A1Dic4 Charge=+");
lprintf("INIT Measure ML",0," |15|16|");
}