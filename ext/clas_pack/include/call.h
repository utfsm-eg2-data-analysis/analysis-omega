/* call.h - Taylor, Manak --  Jan, 1998 */
#ifndef CALL_
#define CALL_

#ifdef __cplusplus
/* make this header file useabble for c++ compiler */
extern "C" {
#endif

/* number of elements in CAllCall array*/
#define  CALL_IDS 10
/* index into CALL_IDS array for CAllCall structure (ind_cl01)*/
#define AC60HZ        1
#define FWD_DIODE     2
#define N_CLMSH_DIODE 3
#define S_CLMSH_DIODE 4
#define SPCFM_DIODE   5
#define RF1           6
#define RF2           7
#define CALL_UNUSED   8
#define RF3           9     /* raw RF values from RFT bank */
#define RF4          10

#define RF_STRUCTURE 2.004008


typedef struct{
	float t0[CALL_IDS];
	float t1[CALL_IDS];
	float t2[CALL_IDS];
	float ped[CALL_IDS];
}call_const_t;

typedef struct{
  float low;
  float high;
  float p0;
  float p1;
  float p2;
  float p3;
} F_t;

#define NO_CL01_HIT -9999
int make_cl01_bank_();
int make_cl01_bank_using(int use_rf); /* select raw RF: 1=CALL6 2=CALL7 3=RFT6 4=RFT7 */
int initcl01_(int *runno);
int make_CL01_bank();
int CL01_begin_run(int runno); /* initialize for mc and data */
int initCL01(int runno);
float getCL01time(int ind_cl01, int tdc);
int getCL01adc(int ind_cl01, int adc);
int get_diode_id(int id,int sec);
float get_diode_time(cl01_t cl01,int id,int sec);
float rf_correction(float time, float rf);
float rf_correction_center(float time, float rf);
float time2rfregion(float time, float rf);
float rf_corr_time(float time); /* use this routine only if you know what you are doing, it does _not_ give the RF corrected time */
float rf_corr_time_counter(int detid, float time); /* same as rf_corr_time() but corrects RF using running mean for detector ids in specified range */
float rf_corr_time_center(float time); /*get rf corrected time*/
float rf_corr_time_(float *time); /*Fortran-callable version of this routine*/
float rf_corr_time_counter_(int *detid, float *time); /*Fortran-callable version of this routine*/
void rf_numbers_(float *rf1, float *rf2, float *good_rf, float *rf_corr);

#ifdef __cplusplus
/* make this header file useabble for C++ compiler */
}
#endif

#endif
