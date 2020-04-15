#ifndef _TRK_RUN_
#define _TRK_RUN_
/* data structures - mirror of the trktcl_var.inc common blocks
 so C can access the tracking control cards */

typedef struct {
  char spar_torus_bfield_name[128], spar_torus_bfield_loc[128];
  char spar_minitorus_bfield_name[128], spar_minitorus_bfield_loc[128];
  char spar_poltarget_bfield_name[128], spar_poltarget_bfield_loc[128];
  char spar_prlink_name[128], spar_prlink_loc[128];
  double dpar_bfield_grid[10];
  double dpar_TargetPos[3];
  double dpar_TargetLen;
  double dpar_TargetMagPos[3];
  double dpar_TargetMagAng[3];
  double dpar_SigmaBeam;
  double dpar_BeamOff[2];
  double dpar_BeamAngle[2];
  double dpar_trk_prfit_chi2;
  double dpar_trk_lrambfit_chi2;
  double dpar_trk_tbtfit_chi2;
  double dpar_trk_vx2fit_chi2;
  double dpar_trk_vxfit_chi2;
  double dpar_trk_zstep[2];
  double dpar_trk_zangle;
  double dpar_trk_Chi2diff;
  double dpar_trk_SCerr_scale;
  int ipar_trk_magtyp;
  int ipar_trk_bgridtyp;
  int ipar_torus_current;
  int ipar_minitorus_current;
  int ipar_poltarget_current;
  int ipar_Bsign_torus;
  int ipar_trk_statistics;
  int ipar_trk_level;
  int ipar_trk_sector;
  int ipar_trk_mintracks;
  int ipar_trk_minhits[6];
  int ipar_trk_maxsegm;
  int ipar_trk_startlink;
  int ipar_trk_minlinks;
  int ipar_trk_minlramb;
  int ipar_trk_electron_id;
  int ipar_trk_make_prlink;
  int ipar_trk_prlink_param;
  int ipar_trk_multscat;
  int ipar_trk_maxiter;
  int ipar_trk_VXconstr;
  int ipar_trk_SCconstr;
  int ipar_trk_calcTM;
  int ipar_trk_print[8];
  int ipar_trk_histo;
  int ipar_trk_ntuple;
  int ipar_trk_region1;
  int ipar_trk_lramb;
  int ipar_ntswitch;
  int ipar_reg1_use_dhcl;
  int ipar_reg1_min;
  int ipar_reg1_max;
  int ipar_trk_fitregion;
} trktcl_t;

extern trktcl_t trktcl_;

/* function prototypes */
int trk_run_control_();
float get_map_current(char name[], int runno);
int set_currents(float torus, float minitorus);
char *prlinkFile(float torusCurrent,float miniCurrent);
int GetRatio(float r);
int ProcessTimeBased();
int ProcessHitBased();
int NewProcessTimeBased();
float get_map_position(char name[], int runno, float *position);

#endif
