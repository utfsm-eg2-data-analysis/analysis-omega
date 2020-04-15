#ifndef scH_INCLUDED
#define scH_INCLUDED




/* #define SC_NPADDLES 288
   #define SC_NPADDLES_SEC 48  */
#define SC_NPADDLES_TOTAL 342
#define SC_NPADDLES_SEC_TOTAL 57
#define SC_NPANELS 24
#define DEDX_NMIP 1.998 /* MeV/cm */
#define SC_ADC_MAX 8192
#define SC_TW_ADC_MAX 600
#define SC_TDC_MAX 8192 /* pipeline */
#define SC_TIME_OVERFLOW 10000.0
#define SC_TIME_UNDERFLOW -10000.0
#define SC_CM_PER_NS 16.0
#define BAD_HIT 666
#define TRUE 1
#define FALSE 0
#define SPEED_OF_LIGHT 2.99792E10 /* cm/sec */
#define TDCL_GOOD 1
#define ADCL_GOOD 2
#define LEFT_OK 3
#define TDCR_GOOD 4
#define TDCS_ONLY 5
#define ADCL_TDCR 6
#define LEFT_OK_NO_ADCR 7
#define ADCR_GOOD 8
#define TDCL_ADCR 9
#define ADCS_ONLY 10
#define LEFT_OK_NO_TDCR 11 
#define RIGHT_OK 12
#define RIGHT_OK_NO_ADCL 13
#define RIGHT_OK_NO_TDCL 14
#define BOTH_OK 15 
#define ALL_CALIB 0
#define TW_CALIB 1
#define C2C_CALIB 2
#define ADC_CALIB 3
#define LR_CALIB 4
#define ADC_JITTER 1.0 /* One ADC channel */
#define TDC_JITTER 1.0 /* One TDC channel */
#define SC_MATCH_DELTA 0.1

/* SC hardware status words */
#define SC_STATUS_NO_ADC 1
#define SC_STATUS_NO_TDC 2
#define SC_STATUS_DEAD   3

typedef struct {
  float left[SC_NPADDLES_TOTAL];
  float right[SC_NPADDLES_TOTAL];
} sc_const_t;

typedef struct {
  int left[SC_NPADDLES_TOTAL];
  int right[SC_NPADDLES_TOTAL];
} sc_int_const_t;


/*function prototypes*/

int sc_channel(int index);
int sc_sector(int index);
int sc_index(int sector, int channel);
int get_panel(int id);

/* SC initialization routines */
int sc_begin_run_(int *runno); /* RECSIS/a1 control structure*/
int sc_begin_run(int runno); /* RECSIS/a1 control structure*/
int initialize_tof_(int *runno);
int initialize_tof(int runno);
int fill_sc_calib(char *map, char *subsystem, sc_const_t *sc_cal, int runno, float def_value);
int sc_init(int runno,int flag);
void sc_status_setup(int runno);  /* for status checking (listed below) */
void sc_swapindex_setup(int runno);

/* routines for making SC reconstruction banks (SC1 and SCR) */
int make_sc_banks_();
int make_sc_banks_tb_();
clasSC1_t *make_SC1_bank(int sector);
clasSCR_t *make_SCR_bank(int sector, const char *dpl); /*set dpl to "TDPL" or "HDPL" */
float get_SC1_time(int tdc, int adc, float pedestal,float disc_thresh,float t0,
		   float t1, float t2, float walk0, float walk1, float walk2,
		   float tw_adc_ref,float t_scale_factor);
float get_SC1_time_unc(int tdc, int adc, float pedestal,float dp,
		       float disc_thresh,float t0,float t1, float t2, 
		       float walk0,float walk1,float walk2,float tw_adc_ref,
		       float t_scale_factor,float dt0,float dt1,float dt2,
		       float dw0,float dw1,float dw2);
float get_SC1_energy(int adc, float pedestal, float gain,float thickness);
float get_SC1_energy_unc(float energy,float dP, float gain, 
			 float dG,float thick);
int comp_sc_t(const void *sc1, const void *sc2);
int valid_SC_hit(clasSC_t *SC, int sector, int index);
scr_t make_SCR_hit(sc1_t sc1,clasSCG_t *SCG,int sector,int status, const char *dpl); /*set dpl to "TDPL" or "HDPL" */
int valid_SC1_hit(sc1_t sc1);
float get_SCR_energy(sc1_t sc1,int sector,float distance);
float get_SCR_energy_unc(int sector,sc1_t sc1,float y,float dy,
			 int status);
float get_SCR_time(sc1_t sc1,int sector,float distance);
float get_SCR_time_unc(sc1_t sc1,int sector);

/* Routines for creating SC clusters */
clasSCRC_t *make_SCRC_bank(int sector);
scrc_t get_cluster(scr_t one, scr_t two);
scrc_t scr2scrc(scr_t scr);
float get_cluster_unc(float E1,float dE1,float q1,float dq1,float E2,float dE2,
		      float q2,float dq2);

/* routines for determining the position of hit along the paddle */
float get_distance_from_time(sc1_t sc1,int sector);
float get_distance_from_energy(sc1_t sc1,int sector);
float get_distance_from_dpl(sc1_t sc1,int sector,clasSCG_t *SCG, 
			    const char *dpl, vector3_t bar_center,
			    vector3_t bar_direction); 
/* set dpl to "TDPL" or "HDPL" */

/*routines for calculating the uncertainties in the previous quantities */
float get_distance_from_time_unc(sc1_t sc1,int sector);
float get_distance_from_energy_unc(sc1_t sc1,int sector );

/* routines for determining geometrical attributes of a paddle */ 
vector3_t get_bar_center(clasSCG_t *SCG, int id);
float get_bar_length(clasSCG_t *SCG, int id);
vector3_t get_bar_direction(clasSCG_t *SCG, int id);
vector3_t get_left_edge(clasSCG_t *SCG, int id);
vector3_t get_right_edge(clasSCG_t *SCG, int id);
vector3_t get_bar_normal(clasSCP_t *SCP, clasSCG_t *SCG, int id);

/* Routines for making SC geometry banks */
int make_SCG_banks(int runno);
int make_SCP_bank(int sector);
float get_SCP_distance(vector3_t norm, int id, clasSCG_t *SCG);
vector3_t get_SCP_norm(int low_id, int high_id, clasSCG_t *SCG);

vector3_t mat_mult(double ang_rot[3][3], vector3_t vec);
void fill_ang_rot(double *ptr_mat, float ang[3]);

/*Function to match hdpl to scintillators */
int dpl2sc_id(int sec, hdpl_t *hdpl);
/* alternate (faster) function for the same purpose */
int tof_trk_match(hdpl_t *hdpl, int id, clasSCG_t *SCG, clasSCP_t *SCP,
		  float factor);
#define SLOP_FACTOR 2.0

/*Function for checking hardware status of scintillator */
int sc_HDWR_channel_status(int sector, int channel);

int get_sc_version_flag(int runno);
void set_sc_version_constants(int runno);
int get_sc_paddle_version(int runno); //returns version flag


#endif
