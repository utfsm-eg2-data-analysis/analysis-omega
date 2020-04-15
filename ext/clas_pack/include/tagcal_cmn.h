/*--------------*
 * tagcal_cmn.h *
 *--------------*/
/* -=======================================================- *
$Id: tagcal_cmn.h,v 1.6 2006/04/24 05:19:03 pasyuk Exp $
* -=======================================================- */


/* images of common blocks from tagcal.CMN */

typedef struct {
  int ectcmapsMM;
  int tmin[384];
  int tmax[384];
  int tbinmnin[767];
  int t1min[384];
  int t1max[384];
  int tchmin[384];
  int tchmax[384];
} ectcmaps_t;

extern ectcmaps_t ectcmaps_; /* common/ECTCMAPS/ */

typedef struct {
  float Tboundary[122];
  float Eboundary[768];
  float Eaverage[767];
  float Edeviation[767];
  int tagEboundsMM;
  int tagTboundsMM;
} tagEnergyBounadaries_t;
extern tagEnergyBounadaries_t tagenergyboundaries_; /* common/TAGENERGYBOUNDARIES/ */

typedef struct {
  float posTpeakL[61];
  float posTpeakR[61];
  float posEpeak[384];
  float tagTDCbaseEpeakMM;
  float tagTDCbaseTpeakMM;
} tagTDCbasePeak_t;
extern tagTDCbasePeak_t tagtdcbasepeak_; /* common/TAGTDCBASEPEAK/ */

typedef struct {
  float ECchWidth;
  float TCchWidthL[61];
  float TCchWidthR[61];
  float TagTDCCalTMM;
  float TAGTDCCalEMM;
} tagTDCCal_t;
extern tagTDCCal_t tagtdccal_; /* common/TAGTDCCAL/  */ 

typedef struct {
  float TagTCi[121];
  float TagCivalMM;
  float TagTCiMean;
} tagCiVal_t;
extern tagCiVal_t tagcival_; /* common/TAGCIVAL/ */

typedef struct {
  int E_hw_status[384];
  int TL_hw_status[61];
  int TR_hw_status[61];
} tagHW_status_t;
tagHW_status_t hwstatus_; /* COMMON/hwstatus/ */ 

typedef struct {
  int tac_ped_lt;
  int tac_ped_rt;
  int tac_ped_lb;
  int tac_ped_rb;
  int tac_ped_sum1;
  int tac_ped_sum2;
  int tac_ped_sum3;
  float tac_sca_lt;
  float tac_sca_rt;
  float tac_sca_lb;
  float tac_sca_rb;
  float tac_sca_sum1;
  float tac_sca_sum2;
  float tac_sca_sum3;
  float tac_tdc_w;
  float posTACpeak;
  int pc_ped_ve;
  int pc_ped_mn;
  int pc_ped_lt;
  int pc_ped_rb;
  int pc_ped_lb;
  int pc_ped_rt;
  float pc_TDC_w;
  float posPCpeak;
  int ps_ped[8];
  float ps_tdc_w[8];
  float posPSpeal[8];
  float timwk1;
  float timwk2;
  float timwk3;
  float PSthreshold;
  int tagDSDCalMM;
} tagDSDcal_t;
extern tagDSDcal_t tagdsdcal_; /* common/TAGDSDCAL/ */

typedef struct {
  float tag2tof;
} tagtotof_t;
extern tagtotof_t tagtotof_; /* common/TAGTOTOF/ */

typedef struct {
  int TTranslateTo[122];
  int TagTTranslateMM;
  int TAGTTransOK;
} tagTTranstable_t;
extern tagTTranstable_t tagttranstable_; /* common/TAGTTRANSLATETABLE/ */

typedef struct {  /* common/t_ref/ */
  int do_correct;
  int runno_read;
  int event_first;
  int event_last;
  int eevent_first;
  int eevent_last;
  int tl_ref[61];
  int tr_ref[61];
  int tl_read[61];
  int tr_read[61];
  int tl_shift[61];
  int tr_shift[61];
} tagTref_t;
extern tagTref_t t_ref_;

typedef struct {
  float ecor[767];
} tag_ecor_t;
extern tag_ecor_t ecor_table_;
