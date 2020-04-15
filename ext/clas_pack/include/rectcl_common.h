#ifndef RECTCL_COMMON
#define RECTCL_COMMON

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

  typedef struct{
    int E_T_coincidence, Tagger_Raw_Format, Tagger_NO_E;
    int Tagger_debug_begin,Tagger_debug_end;
    int Tagger_DSD_debug,Tagger_parms_input;
    int Tagger_PC_TDC,Tagger_PS_TDC,Tagger_TAC_TDC;
    int Tagger_warning;
    char Tagger_tpeaks_file_name[128];
  } tagtcl_t;
  extern tagtcl_t tagtcl_;
  
  typedef struct {
    double ADJ_T_COINC,ADJ_E_COINC,ET_window,E_TDC_MIN,E_TDC_MAX,TAG_DSD_window;
    double TAG_ST_window,TAG_DSD_Xtrawindow,TAG_ST_Xtrawindow,PS_COINC_WINDOW;
  } TagParam_t;
  extern TagParam_t tagparam_;
  
  typedef struct {  
    float posTpeakL[61],posTpeakR[61],posEpeak[384];
    int tagTDCbaseEPeakMM,tagTDCbaseTPeakMM;    
  } TagTDCbasePeak_t;
  extern TagTDCbasePeak_t tagtdcbasepeak_;
  
  typedef struct {  
    float TagTCi[121];
    int TagCivalMM;
  }  TagCival_t;
  extern TagCival_t tagcival_;
  
  typedef struct {
    int tac_ped_lt,tac_ped_rt,tac_ped_lb,tac_ped_rb;
    int tac_ped_sum1,tac_ped_sum2,tac_ped_sum3;
    float tac_sca_lt,tac_sca_rt,tac_sca_lb,tac_sca_rb;
    float tac_sca_sum1,tac_sca_sum2,tac_sca_sum3;
    float tac_tdc_w,posTACpeak;
    int pc_ped_ve,pc_ped_mn,pc_ped_lt,pc_ped_rb,pc_ped_lb,pc_ped_rt;
    float pc_TDC_w,posPCpeak;
    int ps_ped[8];
    float ps_tdc_w[8],posPSpeak[8];
    float timwk1,timwk2,timwk3,PSthreshold;
    int TagDSDCalMM;
  } TagDSDCal_t;
  extern TagDSDCal_t tagdsdcal_;

  typedef struct {
    float tag2tof;
  } Tag2Tof_t;
  extern Tag2Tof_t tagtotof_;
  
  typedef struct {
    float ECchWidth,TCchWidthL[61],TCchWidthR[61];
    int TagTDCCalTMM, TagTDCCalEMM;
  } TagTDCCal_t;
  extern TagTDCCal_t tagtdccal_;
  
#ifdef __cplusplus
}
#endif /*__cplusplus */



#endif
