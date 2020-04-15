/*****************************************************************/
/*                                                               */
/*		dc.h                                                       */
/*                                                               */
/*                                                               */
/*		written by: David Lawrence    Jan. 10,1999                 */
/*    modified                      May-Aug,2000                 */
/*    modified                      Aug. 26,2000                 */
/*                                                               */  
/*                                                               */
/* Header file for the drift chamber recsis package.             */
/*                                                               */
/* The dc package's main purpose is to return the distance       */
/* given the drift time for an event in CLAS. The distances      */
/* are then used by the trk package to reconstruct the particle  */
/* path through the drift chambers.                              */
/*                                                               */
/* This header comes as part of a major overhaul of the DC       */
/* package. A major motivation for this overhaul was to provide  */
/* more modularity to the DC software to make for better         */
/* calibration diagnostics. At the same time, a cleanup of the   */
/* DC area was sort of needed since many similarly named and     */
/* obsolete files made it difficult to follow.                   */
/*                                                               */
/*                                                               */
/*                                                               */
/*****************************************************************/


#ifndef _DC_H_
#define _DC_H_

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<ctype.h>


#ifdef __cplusplus
// Post-fix to allow inclusion in C++ files
extern "C" {
#endif

#define DC_DCH_VERSION_MAJOR_h  2
#define DC_DCH_VERSION_MINOR_h  10 
extern int DC_DCLIB_VERSION_MAJOR;
extern int DC_DCLIB_VERSION_MINOR;
extern int DC_DCH_VERSION_MAJOR;
extern int DC_DCH_VERSION_MINOR;



#include <dc_tcl.h> /*defines dc_tcl COMMON block */
#define DC_XVST_CHOICE        dc_tcl_.dc_xvst_choice
#define DC_XVST_DEFAULT_SLOPE dc_tcl_.dc_xvst_default_slope  /* for MC */
#define DC_SIGMA_DOCA         dc_tcl_.dc_sigma_doca

#ifndef PI
#define PI 3.1415927
#endif

#define PI6 0.52359878
#define PI3 1.0471976
#define beta_ beta__

/* Global Variables */
extern float beta_,B_,locangle_,tmax_,tzero_,ff_;
extern int sup_,sec_,layer_;
extern int excluded[];
extern float *dc_hexsize;
extern int _dc_run_number_;
extern int do_tzero_subtraction;
extern int do_timewalk_correction;
extern int DC_TIMEWALK_PRINT_TABLE;
extern int DC_TIMEWALK_VERBOSE;
extern int DC_XVST_PRINT_TABLE;
extern int DC_FILL_XVST_TABLE;
extern int DC_TIMEWALK_PRINT_PAR;
extern int DC_XVST_VERBOSE;
extern int DC_SILENT;
extern int DC_TIMEWALK_TABLE_TYPE;

/* from dc_xvst_ana.inc */
extern float tdc_zero_[6][6];/*index is [sup][sec] REVERSE OF FORTRAN */ 
extern float dc_hexsize_[36];


/* enums */
enum dc_timewalk_types{
	DC_TIMEWALK_TYPE_LIMING,
	DC_TIMEWALK_TYPE_VIPULI,
	DC_TIMEWALK_TYPE_MAC,
	DC_TIMEWALK_TYPE_NONE,
	NUM_DC_TIMEWALK_TYPES
};

enum dc_xvst_types{
	DC_XVST_TYPE_LIMING,
	DC_XVST_TYPE_POLY,
	DC_XVST_TYPE_POWER,
	DC_XVST_TYPE_BESSEL,
	DC_XVST_TYPE_LEGENDRE,
	NUM_DC_XVST_TYPES
};

/* data structures */
typedef struct{
   float map_parms[24];
   float tmax[36];
   float chisq;
   int   DOF;
   int   POINTS_IN_FIT;

   int xvst_runno;
   int tmax_runno;
   int tw_runno[5];
   
   float tw_parm_r1[11];
   float tw_parm_r2[11];
   float tw_parm_r3[11];
   float tw_fact[4];
   float tw_tau[4];
   float tw_betaslope[7];
   int   tw_functiontype;
}xvst_parms_t;
extern xvst_parms_t default_parms;
extern xvst_parms_t *xvst_parms;
extern xvst_parms_t fit_parms[7][7];
extern xvst_parms_t map_parms[7][7];



/* function declarations */
void dc_xvst_init_(int * runno);
void dc_fill_xvst_table(void);
void dc_xvst_fct(int sector,int layer,float locangle
   ,float time,float B,float *doca,float *tmax);
void dc_xvst_fct_(int *sector,int *layer,float *locangle
   ,float *time,float *B,float *doca,float *tmax);
void dc_xvst_table(int sec,int layer,int wire,float beta
	,float locangle,float time,float B, float B_para,float *dist,float *sigma);
void dc_time_to_dist_(int *sec,int *layer,int *wire,float *beta
	,float *locangle,float *time,float *B, float *B_para,float *dist,float *sigma);
float xvst_func(float *time);
void xvst_set_cell_sizes(void);

void dc_sigma_init(int runno);

void  dc_timewalk_init(int runnumber);
void  dc_fill_timewalk_table(void);
float dc_timewalk(float superlayer,float beta,float time,float tmax);
float dc_timewalk_table(float sup,float beta,float time,float tmax);
float dc_timewalk_liming(float superlayer,float beta,float time,float tmax);
float dc_timewalk_vipuli(float superlayer,float beta,float time,float tmax);
float dc_timewalk_mac(float superlayer,float beta,float time,float tmax);
float dc_timewalk_none(float superlayer,float beta,float time,float tmax);

float dc_time_correction_(float *t,int *layer,int *sector,float *beta);


/* correction routines */
float tmax_correction(float B,float B0,int region);
float locangle_correction(float B,int region);
float doca_locangle_correction(float theta,float t,int layer);
float doca_B_correction(float t,float B,float B0,int region);
float reduced_angle_(float *alpha);


/* Originally in FORTRAN common (from dc/dc_xvst_ana.inc)*/
#define MAXSUPER 6
#define MAXSECTOR 6
#define MAXLAYER 36
#define r1layers 10
#define r2layers 12
#define r3layers 12
#define n1_dtime_bins 150
#define n2_dtime_bins 400
#define n3_dtime_bins 800
#define n_lang_bins 2
#define n_mag_bins 15
#define n_beta_bins 10
#define n_twtime_bins 450
#define n_rdoca_bins 50
#define langle_value_lo 0.0000
#define langle_value_hi PI6
#define DC_NS_PER_BIN_R1 2.0
#define DC_NS_PER_BIN_R2 2.5
#define DC_NS_PER_BIN_R3 2.5
#define DC_B_value_lo 0.0
#define DC_B_value_del 1.0

extern float DC_HEXSIZE[MAXLAYER]; 
extern float DC_XVST_TABLE_R1E[n_lang_bins][n1_dtime_bins][r1layers][MAXSECTOR];
extern float DC_XVST_TABLE_R2E[n_mag_bins][n_lang_bins][n2_dtime_bins][r2layers][MAXSECTOR];
extern float DC_XVST_TABLE_R3E[n_lang_bins][n3_dtime_bins][r3layers][MAXSECTOR];
extern float DC_SIGMA_TABLE[n_rdoca_bins][MAXSUPER];

#ifdef __cplusplus
}
#endif

#endif /* _DC_H_ */
