//$Id: trk.h,v 1.10 2006/03/15 14:51:41 pasyuk Exp $
/* trk package header file, J. J. Manak, Jan 1999*/

/* information from the sdaswim COMMON BLOCK (ew, but simpler for now) */
#ifndef trkH_INCLUDED
#define trkH_INCLUDED

#define NPLN 46
#define NPL_ST 2
#define NPL_DC 36
#define NPL_CC 1
#define NPL_SC 4
#define NPL_EC 2

/*    the MIN, MAX are set for use at C indices (they are Fortran_value-1) */
#define NST_MIN 1
#define NST_MAX (NST_MIN+NPL_ST-1)
#define NDC_MIN (NST_MAX+1)
#define NDC_MAX (NDC_MIN+NPL_DC-1)
#define NCC_MIN (NDC_MAX+1)
#define NCC_MAX (NCC_MIN+NPL_CC-1)
#define NSC_MIN (NCC_MAX+1)
#define NSC_MAX (NSC_MIN+NPL_SC-1)
#define NEC_MIN (NSC_MAX+1)
#define NEC_MAX (NEC_MIN+NPL_EC-1)

#define NTBLA_ROW 34 /*number of rows in TBLA */

extern struct {
  float sda_pln[6][NPLN][20];
  float st_Zpos[6][4];
  float sda_trp[NPLN][10];
  float sda_tmat[NPLN][5][5];
} sdaswim_;

/* END sdaswim.inc COMMON block and definitions */
/*--located in trk_remake_tbla.c--*/
int trk_remake_tbla_(int *psect1banknumber, float *pzangle, float *pminstep, float *pmaxstep, int *pickwire);

int trk_remake_tbla(int sect1banknumber, float zangle,float minstep,float maxstep, int pickwire);

int trk_remake_tdpl(int sect1banknumber, float zangle,float minstep,float maxstep);

int get_track_hits(tber_t *tber, float beta, float st_time,
		   float zangle, float minstep, float maxstep,
		   int pickwire, tbla_t *tbla, tdpl_t *tdpl);
int get_tber_info(tber_t *tber,int slinfo[6], int *psec, int *ptrk_in_sect,int *ptrk_in_hbtr);         
int put_tber_info(tber_t *tber, vector3_t vrt, vector3_t p, float charge, float chi2, float c[5][5], int slinfo[6], int trk_in_sect, int trk_in_hbtr);

int trk_remake_swim_banks(int sect1banknumber, float zangle,float minstep,float maxstep, int pickwire, int blabank, int dplbank, int tbased);

float trk_redoca_(vector3_t *ptpos, vector3_t *ptdir, int *psector, int *player, int *pwire);

/*
 * c routines to help with remaking the tbla bank
 *
 */

float trk_find_dc1_hit_tdc(int sector, int layer, int wire, int *index);
trks_t *trkn2trks(int trackno, int sector);
float phinorm(int sector, int layer, int wire);
float trk_redoca_(vector3_t *ptpos, vector3_t *ptdir, int *psector, int *player, int *pwire);
void trk_dtime_retbla_(int *sect,int *lay,int *wire,vector3_t *hitp,float *alpha, float *tdc, float *Tlen, float *beta, float *start_time, float *driftt, float *tdoca, float *tsigma, float *wlen,vector3_t *B);

int trk_swim(tber_t *tber,vector3_t trkint[NPL_DC],vector3_t trkintdir[NPL_DC],
     float trklength[NPL_DC], float zangle,float minstep, float maxstep);
#endif

