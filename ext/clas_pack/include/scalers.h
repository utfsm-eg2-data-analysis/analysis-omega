/*scaler manipulation routines */

#define CLOCK_RATE 10.0 /* clock rate in KHz*/ 
#define NUM_T_COUNTERS 61 
#define NUM_E_COUNTERS 384
#define SCALER_BANK_SIZE 64 /* size of XXSL banks and TRGS bank */
#define TGS_BANK_SIZE 192
#define TRGS_BANK_SIZE 64
#define NUM_E_BINS 767
#define NUM_T_BINS 121
#define EVEN 0
#define ODD 1
#define E_T_ARRAY_SIZE 2690

#define GAUSS 0
#define POLYNOMIAL 1


/* PC=1; PS=2; PCdelay=3; PSdelay=4; TAC=5 */ 
#define PC_PS_TAC_TAC 1255 /* Normalization scaler configuration */ 
#define PC_TAC_PS_TAC 1525 /* for g1a data:                      */ 
#define TAC_PS_PS_TAC 5225 /* set1_set2_set3_set4                */

#define PC_PS_PCdelay_PSdelay 1234 /* Production run setting */
#define PSdelay_PS_PS_PSdelay 4224 /* Production run setting */

/* generic scaler data structure */ 
typedef struct{ 
  bankHeader_t bank; 
  uint32 scaler[1]; 
} clasSCALER_t;

void addarr(uint32 *first, uint32 *second, uint32 *sum, int size); 
void subarr(uint32 *first, uint32 *second, uint32 *sub, int size); 
int scaler_event(int runno); 
clasSCALER_t *make_trgs_sum(int runno); 
clasSCALER_t *make_tgs_sum(int runno); 
clasS1ST_t *make_s1st_sum(int runno);


void addarr(uint32 *first, uint32 *second, uint32 *sum, int size);
void subarr(uint32 *first, uint32 *second, uint32 *sub, int size);
int scaler_event(int runno);
clasSCALER_t *make_trgs_sum(int runno);
clasSCALER_t *make_tgs_sum(int runno);
int printarr(FILE *file, uint32 *arr, int size);
/*build a TGS and TRGS bank that is a running total in the wcs array*/ 
int scaler_event_(); 
/* just fill a tagger scaler array*/ 
int fill_rtsl(clasSCALER_t *TGS, uint32 *rtsl); 
int fill_g1sl( clasSCALER_t *TGS, uint32 *g1sl); 
int fill_g2sl( clasSCALER_t *TGS, uint32 *g2sl); 
int fill_g3sl( clasSCALER_t *TGS, uint32 *g3sl); 
int fill_g4sl( clasSCALER_t *TGS, uint32 *g4sl); 
/* make a tagger scaler bank */ 
clasSCALER_t *make_RTSL_bank(BOSbank *bcs, clasSCALER_t *TGS, int banknum); 
clasSCALER_t *make_G1SL_bank(BOSbank *bcs, clasSCALER_t *TGS, int banknum); 
clasSCALER_t *make_G2SL_bank(BOSbank *bcs, clasSCALER_t *TGS, int banknum); 
clasSCALER_t *make_G3SL_bank(BOSbank *bcs, clasSCALER_t *TGS, int banknum); 
clasSCALER_t *make_G4SL_bank(BOSbank *bcs, clasSCALER_t *TGS, int banknum);
clasSCALER_t *make_TGS_from_map(BOSbank *bcs, int runno, int banknum);

/* formatted print functions other print functions in printBOS.h*/ 
void printTRGSinfo(FILE *fp, clasTRGS_t *TRGS); 
void printTGSinfo(FILE *fp, clasSCALER_t *TGS); 
void printTGSrates(FILE *fp, clasSCALER_t *TGS, clasTRGS_t *TRGS);

/* located in scalers/E_T_util.c*/
int fill_E_T_map(); /* fill the E_T conicidence map from the flat file*/
int fill_E_T_map_(); /* fortran wrapper*/
tgs_t make_tgs_from_map(int runno);
float epsilon_ijk(int E_T_count, int Tcount);

int E_T_matrix2arr(int matrix[NUM_E_BINS + 1][NUM_T_BINS +1], int *intarray); /*convert matrix to an array */
int arr2E_T_matrix(int *intarray, int matrix[NUM_E_BINS + 1][NUM_T_BINS +1]); /*convert array into matrix*/

/* navigate between E_T matrix and its array representation */
int matrix2arrayind(int e_bin_target, int t_bin_target);
int arrayind2matrix(int arrayind, int *e_bin_out, int *t_bin_out);
int check_array_size(); /* for debugging purposes - to return the E_T_MATRIX_ARRAY size*/

int put_E_T_MATRIX_map(int runno, int matrix[NUM_E_BINS + 1][NUM_T_BINS +1]); /*fill E_T_matrix into map*/
int get_E_T_MATRIX_map(int runno, int matrix[NUM_E_BINS + 1][NUM_T_BINS +1]); /*get E_T_matrix from map*/

/* construct the Tbin array from the E_T_matrix*/
int E_T_matrix2Tbin(int matrix[NUM_E_BINS+1][NUM_T_BINS+1], int *Tbin);

int T_binmax(int e_bin);
int T_binmin(int e_bin);
int E_binmax(int t_id);
int E_binmin(int t_id);
int T2Tbinmax(int t_id);
int T2Tbinmin(int t_id);
int Tbin2Tid_arr(int Tbin[122], int Tid[62]);


int smooth(int histo,int fit_type,int parms,float *matrix);
int get_eff(uint32 px1[64], uint32 px2[64], float eff[64]); 
float fit_polynomial(float tcounter,float fit_pc[5],int order); 
float fit_gauss(float tcounter,float fit_ps[3]);
 
int DSD_efficiency(int gate,clasSCALER_t *TGS,float PC_Eff[64], 
    float PS_Eff[64],float Tag_Eff[64]); 
void book_scaler_histos(int runno); 
int get_scalers_map(int runno,float PC_Eff[64],float PS_Eff[64],float Tag_Eff[64]); 
int calc_scalers_data(int runno);
int DSD_peak_norm(); 
int fill_ET_histo(); 
int tag_eff_prod(clasSCALER_t *TGS,float PC_T[64],float PCdelay_T[64],
    float PS_T[64],float PSdelay_T[64]);
int tag_eff_prod2(clasSCALER_t *TGS,float PS_T[64],float PSdelay_T[64]);

/* simple read/write routines*/
int write_E_T_array(FILE *fp, int *array);
int read_E_T_array(FILE *fp, int *array);
/* print routine in scaler_mon */
int write_e_ijk_info(FILE *fp, int matrix[NUM_E_BINS+1][NUM_T_BINS+1]);

/* E_T_map "object" */
typedef struct{
  int n_tcounter;
  int tmin;
  int tmax;
} e_t_map_t;

/* T_E_map "object" */
typedef struct{
  int emin;
  int emax;
} t_e_map_t;

int fill_ET_map();
int fill_E_T_matrix(int E_T_matrix[768][122]);

/* ebin map constructor and member functions*/
int fill_ebin_map();
int fill_ebin_map_(); /*fortran wrapper*/
float ebin_mean(int ebin);
float ebin_mass(int ebin);
float ebin_min(int ebin);
float ebin_max(int ebin);
int fill_tbin_map();
int fill_tbin_map_(); /*fortran wrapper*/
float tbin_min(int tbin);
float tbin_max(int tbin);

int n_tcounter(int Eid); 
int tmin(int Eid);
int tmax(int Eid);
int n_ecounter(int Tid);
int emin(int Tid);
int emax(int Tid);
int calc_Ngamma(int E_T_matrix[768][122], float PS_Eff[64], float Tag_Eff[64], 
    uint32 rawt[64], float PS_T[64], float PSdelay_T[64], float Nphoton[768]);
int get_Ngamma_(int runno, float Nphoton[768]);

int calc_ngamma_prod(int runno, float Nphoton_prod[NUM_E_BINS],
		     float PS_ratio[64],float prod_live_time);

/*** function definition for pflux_tscalers.c ***/
#define nchan_T 200
#define min_T -5.
#define max_T 15.
/* --------------------------------------------------- */
int flux_norm(int runno, clasSCALER_t *TGS, clasTRGS_t *TRGS, clasS1ST_t *S1ST, float *F_NORM, float *DELTA_F_NORM, int batch);
int flux_prod(int runno, float prod_live_time, float prescale_prod, float prescale_norm, int norm_run, uint32 *RAW_T, float *Ngam, float *Delta_Ngam, int batch);
int calc_flux_data(int runno, int gate, int norm_run, float *F_NORM, float *DELTA_F_NORM, float *Ngam, float *Delta_Ngam, int batch);
int ngamma_flux_prod(int runno, uint32 *SCALERS, float prod_live_time, int norm_run, float *Ngam, float *Delta_Ngam);
void book_histos_test(int runno);
/* --------------------------------------------------- */



/* the bottom line, number of gammas in each E bin*/
int ngamma_prod(int runno, float Nphoton[NUM_E_BINS]);
int ngamma_prod_(int *runno, float Nphoton[NUM_E_BINS]);
int ngamma_part_prod(int runno, float Nphoton_prod[NUM_E_BINS]);

int get_Ngamma(int runno, clasSCALER_t *TGS, float Nphoton[NUM_E_BINS+1]);
int get_Ngamma_wcs(int runno, float Nphoton[768]);
int get_Ngamma_map(int runno, float Nphoton[768]);

/*make TAGR bank from MC data*/
clasTAGR_t *make_mctagr(BOSbank *bcs,float E_electron, float E_gamma, float t_offset,int use_energy);
int make_mctagr_(float *E_electron, float *E_gamma, float *t_offset,int *use_energy);






