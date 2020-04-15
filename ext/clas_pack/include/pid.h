#ifndef pidH_INCLUDED
#define pidH_INCLUDED


/*------------------------ pid.h ----------------------------*/

/*generic structure for HBID and TBID banks */

typedef struct {
  int stat;  /*  status of hit matching */
  int id;    /*  Fortran style pointer to bank */
  float time;    /* time for this trac at detector plane */
  float qual;    /* quality factor */
  float vtime;    /*  time at vertex using time */
  float beta;    /*  Beta as calculated from time*/
} match_t;

typedef struct {
  int track;    /*  Track Candidate (ptr to H/TBTR) */
  int sec;    /*  Sector track is in */
  float beta;    /*  Beta of the track in units of c */	
  float vtime; /*vertex time for track */
  match_t sc;
  match_t cc;
  match_t ec;
  match_t st;
  match_t lac;
} bid_t;

typedef struct {
  bankHeader_t bank;
  bid_t bid[1];
} clasBID_t;

#define PART_SIZE 30                               /* maximum size of PART */
/* macros for hbid->xx_status */
/* These should be define such that the higher xx_stat, the better the quality of the matching.
   This way, sort_hbid will put better matching at the top of the bid banks */
#define NONFIDUCIAL_MATCH 1   /* geometrically match, but outside of fiducial region */
#define GOOD_MATCH        2   /* geometrically matched inside fiducial region */
#define NEUTRAL_MATCH     3
/* more macro definitions for status word in part */
#define BEAM_FLAG 20
#define TARGET_FLAG 10


#define BAD_VERTEX_TIME -9999.0

#define EC_FIDUCIAL_CUT 10.0  /* cm */

#define ST_TAG_COINCIDENCE_WINDOW 15.0 /* Half-width in ns of the software 
				       coincidence between the start counter 
				       and the tagger */
#define HIT_BASED 0   /* Macros for get_vertex_time */
#define TIME_BASED 1
#define KILL_RADIUS 30.0

/* macro used in tof matching*/
#define SQUARE(X) ((X)*(X))

/* macros used in qsort*/
#define QS_SWAP 1
#define QS_NO_SWAP -1

/* see bosddl.h clasBID_t for general data structure for HBID/TBID */



/* prototypes */

/* Routines for matching tracks to the outer detectors */
int match_to_tof(hdpl_t *hpdl, clasSCRC_t *SCRC, match_t *match);
int match_to_CC01(hdpl_t *hpdl, clasCC01_t *CC01, match_t *match);
int match_to_st(hdpl_t *hdpl, clasSTR_t *STR, bid_t *bid, int trk_sec);
int match_to_ec(hdpl_t *hdpl, int TrkSector, clasECHB_t *ECHB, match_t *match);
int match_to_lac(hdpl_t *hdpl,int TrkSector, clasEC1R_t *EC1R, match_t *match);

/* Routines for matching hits between scintillators and the calorimeters */ 
int match_sc_to_ec(echb_t *echb,scrc_t *scrc,int sec);
int match_sc_to_lac(ec1r_t *ec1r,scrc_t *scrc,int sec);

int sort_hbid( const void *hbid1 , const void *hbid2);
float dist_to_vertex(hdpl_t *hbpl);
float hbtr_momentum(hbtr_t hbtr);
trks_t *get_hbid_trks(hbid_t *hbid);
clasBID_t *make_HBID_bank();
int make_HBID_bank_(); /*Fortran callable wrappers */
int make_tbid_bank_();
int make_TBID_bank();
int make_HDPL_from_TDPL();
clasBID_t *make_TBID_group(int number);
int make_tbid_group_(int *groupno); /*Fortran callable wrapper */ 


/* particle id routines */
int ElectronID(bid_t * , int tbid_index, part_t *);
int ElectronID_old(bid_t * , int tbid_index, part_t *);
int PositronID(bid_t * , int tbid_index, part_t *);
int PositronID_old(bid_t * , int tbid_index, part_t *);
int HadronID  (bid_t * , int tbid_index, part_t *);
int GammaID   (bid_t * , int tbid_index, part_t *);

float get_sc_energy(tbid_t *tbid, tbtr_t *tbtr);
float get_sc_mass(tbid_t *tbid, tbtr_t *tbtr);

clasGPID_t *makeGPID(int bankNum, int calib);
int initGPID(int run);

clasTRKS_t *make_TRKS_bank(int sec, clasBID_t *BID);
clasTRKS_t *make_TRKS_bank_plus(int sec, clasBID_t *BID);
trks_t piminus2trks(hbtr_t *hbtr, int trkno, float vtime);
bid_t *match_hbtr2tbid(int hbtr_ind,clasBID_t *BID,clasTBTR_t *TBTR);

int make_trks_banks_();
int make_PART_bank();
clasPART_t *make_PART_group(int group);
int make_part_group_(int *groupno); /* Fortran callable versions*/
int make_part_bank_();

int trk2part(bid_t *tbid, clasTBTR_t *TBTR, float mass, part_t *part);
vector4_t part2v4(part_t part);
int ECHBmatch2TBID(int ec_index, clasTBID_t *TBID);
int echb2part(echb_t *echb, float mass, part_t *part);
int ec1r2part(ec1r_t *ec1r, float mass, part_t *part);
float pathlen2sc(bid_t *bid, hdpl_t *hdpl);
float echb_close2trk(echb_t *echb, clasTBID_t *TBID);
float echb_close2tbtr(echb_t *);
float ec1r_close2tbtr(ec1r_t *);
float gamma_energy(echb_t *echb);
float predict_e(vector3_t pvec);
float predict_e_in_out(vector3_t pvec);
float predict_sigma_e(vector3_t pvec);
float predict_sigma_e_in_out(vector3_t pvec);
/*various routines to calculate dedx in the sc*/
int sc_dedx_(int *sec, int *id, float c[3], float *del_e, float *dedx);
float sc_dedx(int sec, int id, vector3_t dir_cos_sec, float del_e);
float tbid2dedx(bid_t *tbid);
float hbid2dedx(bid_t *hbid);
float get_vertex_time(int nHBID,bid_t *bid,clasTAGR_t *TAGR, int trk_level);
float get_vertex_timeG7(int nHBID,bid_t *bid,clasTAGR_t *TAGR, int trk_level);
float get_vertex_timeG2b(int nHBID,bid_t *bid,clasTAGR_t *TAGR, int trk_level);
vector4_t get_photon_v4(clasTAGR_t *TAGR,clasBID_t *BID);
float get_photon_energy(clasTAGR_t *TAGR,clasBID_t *BID);
tagr_t *get_photon_tagr(clasTAGR_t *TAGR,clasBID_t *BID);
tagr_t *get_photon_tagrG7(clasTAGR_t *TAGR,clasBID_t *BID);
double target_z();

/* for filter programs */

#define BID_BANKS "CC01SC1 SCR SCRCECHBECPITAGITAGRST1 STR PSO "

int ConfigEvent(int RunNo, int pid_flag);   /* calls initPID and make_RUNC_bank */
int initPID(int runno); /*initialize all detector packages needed for pid*/
clasBID_t *make_BID_banks(int number);

/* momentum correction */
float p_corr_angle(int sec, float p,float theta);
vector4_t p_correction(vector4_t particle);
int init_mom_corr(int runno);
float p_corr_phi(int sector,float p,float phi);
float p_corr_p(float p);


/* rematch HBID to TOF */
int reMatchSCRC(); 

/* routine for matching hits between EC and SC */
vector3_t sc_pos2whole_plane(scrc_t *scrc,int sec);
/*float TARGET_POSITION[3];*/
 
#define MIN_GAMMA_ENERGY 0.1 /* GeV */
#define EC_SC_RADIUS 30 /* cm */

#define LIGHT_SPEED  29.979 /* speed of light in cm/nanosec */

#include <make_TGEO.h>


#endif
