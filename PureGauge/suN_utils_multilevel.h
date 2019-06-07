/***************************************************************************\
 * Copyright (c) 2019, Antonio Rago                                          *   
 * All rights reserved.                                                      * 
 \***************************************************************************/

#ifndef SUN_UTILS_ML_H
#define SUN_UTILS_ML_H

#include "input_par.h"
#include "glueballs.h"
#define GENERIC_MAX(x, y) ((x) > (y) ? (x) : (y))

#define ENSURE_int(i)   _Generic((i), int:   (i))
#define ENSURE_float(f) _Generic((f), float: (f))

#define MAX(type, x, y) \
  (type)GENERIC_MAX(ENSURE_##type(x), ENSURE_##type(y))

/* suN variables */
typedef struct _input_pg_ml
{

  double beta, APEsmear;
  int nhb, nor, ml_levels, nblk;
  int *ml_niteration;
  int *ml_nskip;
  cor_list corrs;

  char cml_niteration[64];
  char cml_nskip[64];
  char cml_corrs[256];

  /* for the reading function */
  input_record_t read[10];

} input_pg_ml;

#define init_input_pg_ml(varname)                                                                                             \
  {                                                                                                                           \
    .read = {                                                                                                                 \
      {"beta", "beta = %lf", DOUBLE_T, &(varname).beta},                                                                      \
      {"nhb", "nhb = %d", INT_T, &(varname).nhb},                                                                             \
      {"nor", "nor = %d", INT_T, &(varname).nor},                                                                             \
      {"number of ML levels", "ML levels = %d", INT_T, &(varname).ml_levels},                                                 \
      {"number of iterations per level", "ML iterations per level = %s", STRING_T, &((varname).cml_niteration[0])},           \
      {"number of skip steps at the beginning of each level", "ML skip per level = %s", STRING_T, &((varname).cml_nskip[0])}, \
      {"number of skip steps at the beginning of each level", "ML correlators = %s", STRING_T, &((varname).cml_corrs[0])},    \
      {"APEsmear parameter", "APEsmear = %lf", DOUBLE_T, &(varname).APEsmear},                                                \
      {"nnumber of spatial blocking level to generate lueballs", "nblk = %d", INT_T, &((varname).nblk)},                      \
      {NULL, NULL, INT_T, NULL}                                                                                               \
    }                                                                                                                         \
  }

/* Flow control variables variables */
typedef struct _pg_flow_ml
{
  char run_name[64]; /* name for this run */
  char g_start[64];  /* for gauge fields => unit, random, file */

  int therm;

  char last_conf[64]; /* last conf: can be a number or of the format "+n" */
  char conf_dir[64];  /* directory to store gconfs */

  int save_freq; /* save gauge conf if number%save_freq==0 */
  int nskip;
  /* these are not actually read from input
   * but inferred from the above
   */
  int start, end;
  input_pg_ml *pg_v;

  /* for the reading function */
  input_record_t read[8];

} pg_flow_ml;

#define init_pg_flow_ml(varname)                                                        \
  {                                                                                     \
    .read = {                                                                           \
      {"thermalization", "therm = %d", INT_T, &((varname).therm)},                      \
      {"run name", "run name = %s", STRING_T, &((varname).run_name[0])},                \
      {"number of update between each measure", "nskip = %d", INT_T, &(varname).nskip}, \
      {"conf save frequency", "save freq = %d", INT_T, &((varname).save_freq)},         \
      {"gauge start", "gauge start = %s", STRING_T, &((varname).g_start[0])},           \
      {"gauge last conf", "last conf = %s", STRING_T, &((varname).last_conf[0])},       \
      {"config dir", "conf dir = %s", STRING_T, &((varname).conf_dir[0])},              \
      {NULL, NULL, INT_T, NULL}                                                         \
    }                                                                                   \
  }

int init_mc_ml(pg_flow_ml *rf, char *ifile);
int save_conf(pg_flow_ml *rf, int id);
int end_mc_ml();

#endif /* SUN_UTILS_ML_H */
