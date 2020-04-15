/* DC DEFINES */
#define DRIFT_VELOCITY 50.0  /* (microns/nanosec) */
#define DC_WIRES_SEC 6912
#define DC_WIRES_LAYER 192
#define DC_TDC_TO_NS  2.0 /*tdc counts per ns*/

#define NSEC 6
#define NLAY 36
#define MIN_ID 1
#define MAX_ID 192
#define MAX_LAYER 36
#define MIN_LAYER 1
#define DC_TDC_MIN 0
#define DC_TDC_MAX 16384

/* digi junk*/
#define MAXHITS 192
#define WIRE_ID 0
#define TDC 1

/* CC stuff */
#define CC_STRIPS 36
#define CC_TIME_UNDERFLOW -9999.0
#define CC_TIME_OVERFLOW 9999.0
#define CC_TDC_TO_NS 0.05
#define CC_TDC_MAX 4095

/*------------prototypes------------------*/


/*--located in dc_makebanks.c */
int ddly_num(int i);
int id2ddly(int id);
int ind2wire(int ind);
int ind2layer(int ind);
int ind2region(int i);
int id2region(int id);
int ddly2id(int i);
int wire2ind(int wire, int layer);
int make_DDLY_bank(int runno, int sector);
int make_DCDW_bank(int runno,int sector);
int ddly_to_status_(int arr[6][36][192]);
int ddly_to_t0_(float arr[6][36][192]);
int make_ddly_banks_(int *runno);

/*located in dc_begin_run.c--*/
int dc_begin_run_(int *runno); /*FORTRANesque wrapper for dc_begin_run*/
int dc_begin_run(int runno); /* control routine for RECSIS/a1 */
int configure_dc(int runno); /* initialize tracking for a given run number*/

/*--located in trk_makebanks.c--*/
/* FORTRANesque wrappers for RECSIS*/ 
int init_trk_trans(int runno); /*initialize offline translation tables */
int init_trk_trans_(int *runno);/*initialize offline translation tables FORTRAN style*/
int make_dc1_banks_(); /*make DC1 banks for sectors 1-6*/
int make_dc1_(); /*not used - only makes dc1 if no DC1 bank already*/
int make_digi_common_(int dc_digi[NSEC][NLAY][MAXHITS][2], int dc_ndig[NSEC][NLAY], int pt_digi[NSEC][NLAY][MAXHITS]);
/* C routines that do the work*/
int make_DC1_bank(int sector);
int DC1_to_digi(int sector, int dc_digi[NSEC][NLAY][MAXHITS][2], int dc_ndigi[NSEC][NLAY], int pt_digi[NSEC][NLAY][MAXHITS]);
/*FORTRAN callable routine that loops over sectors*/
int build_digi_arrays_(int dc_digi[NSEC][NLAY][MAXHITS][2], int dc_ndigi[NSEC][NLAY], int pt_digi[NSEC][NLAY][MAXHITS]); 
/* given hbtr and hbtb go back to DC0*/
int hbtr2dc0(hbtr_t *hbtr);

/*--located in cc_makeCC01.c--*/
float get_CC01_n_phe(int adc, float pedestal, float counts_per_photoelectron);
int valid_CC_hit(cc0_t  cc0);
float CC2theta(int id);
int make_CC01_bank(int sector);
int make_cc01_banks_();
int cc_begin_run(int runno);
int cc_init(int runno);
int cc01_init_(int *runno);
cc0_t *cc01_2_cc0(cc01_t *cc01, int sec);
float get_CC01_time(int tdc, float t0);

#define NPARS_REGION_1_3 360
#define NPARS_REGION_2 1008
#define LAYERS_PER_REGION 12 /*36 layers per sector*/
#define NPARS_REGION_2 1008
#define DCV1_NCOL (sizeof(dcv1_t)/4)
#define DCV2_NCOL (sizeof(dcv2_t)/4)
#define DCV3_NCOL (sizeof(dcv3_t)/4)

/*--located in dc_makeDCV.c--*/
int make_dcv_banks_(int *runno);
int make_DCV1banks(int runno);
int map2dcv1(int i, int sec);
int make_DCV2banks(int runno);
int map2dcv2(int i, int sec);
int make_DCV3banks(int runno);


