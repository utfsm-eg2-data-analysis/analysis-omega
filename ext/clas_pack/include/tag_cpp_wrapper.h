//$Id: tag_cpp_wrapper.h,v 1.14 2006/03/15 14:51:40 pasyuk Exp $
/* tagger Cpp wrapper routines */

#ifndef tag_cpp_wrapperH_INCLUDED
#define tag_cpp_wrapperH_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

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
    float Tboundary[122],Eboundary[768],Eaverage[767],Edeviation[767];
    int tagEboundsMM,tagTboundsMM;
  } tagenergyboundaries_t;
  extern tagenergyboundaries_t tagenergyboundaries_;
  
  typedef struct{
    int Tagger_NO_LR, Tagger_Raw_Format, Tagger_NO_E;
    int Tagger_debug_begin,Tagger_debug_end;
    int Tagger_DSD_debug,Tagger_parms_input;
    int Tagger_PC_TDC,Tagger_PS_TDC,Tagger_TAC_TDC;
    int Tagger_warning;
    int Tagger_ETmatch;
    int Tagger_convert;
    int Tagger_correct;
    int Tagger_energy_correct;
    char Tagger_tpeaks_file_name[128];
    char Tagger_ecorr_name[128];
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
  
  //T-counter TDC peak correction, g6c and g8a
  typedef struct {
    float posTpeakLhigh[61],posTpeakRhigh[61];
    float posTpeakLlow[61],posTpeakRlow[61];
    float posTpeakSigmaL[61],posTpeakSigmaR[61];
    int posTpeakStatL[61],posTpeakStatR[61];
  } TagTDCpeakCorr_t;
  extern TagTDCpeakCorr_t tagtdcpeakcorr_;

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

  typedef struct {
    int E_hw_status[384];
    int TL_hw_status[61];
    int TR_hw_status[61];
  } TagHWstat_t;
  extern TagHWstat_t hwstatus_;
#ifdef __cplusplus
}
#endif /*__cplusplus */

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

extern  void tag_brun_(int*);
extern  void tag_brun_scaler_(char*);
extern  void tag_evnt_();
extern  void tag_erun_();
extern  void tag_init_();
extern  void tag_scaler_();
extern  int tag_bin_(int*,int*);
extern  int tag_unbin_(int*);
extern  float tag_deltae_(int*);
extern  int tag_nbc_bin_(int*);
extern  void tagtcl_set_def_();

#ifdef __cplusplus
}
#endif /*__cplusplus */

int tag_brun(int); /* begin of run routine */
int tag_brun_scaler(); /* begin of run scaler routine */
int tag_evnt(); /* event tagger routine */
int tag_erun(); /* end of run tagger routine */
int tag_init(); /* tagger initialisation routine */
int tag_scaler(); /* tagger scaler event routine */
int tag_bin(int,int); /* binning routine, arguments are counter # & nb of counter hit (1 or 2) */
int tag_unbin(int); /* unbinning routine, argument is bin # */
float tag_deltae(int); /* delta-E routine, argument is E bin */
int tag_nbc_bin(int); /* number of hit (1 or 2) for a given bin */
int tagtcl_set_def(); /* set tcl default values */

  // RECSIS switches
#ifdef __cplusplus
class TTagSwitches {
 public:

float SetAdjacentT_TimeCoinc(float win);
float GetAdjacentT_TimeCoinc();
float SetAdjacentE_TimeCoinc(float win);
float GetAdjacentE_TimeCoinc();
float SetE_T_Coinc(float win);
float GetE_T_Coinc();
float SetE_TDC_Min(float win);
float GetE_TDC_Min();
float SetE_TDC_Max(float win);
float GetE_TDC_Max();
float SetT_DSD_Win(float win);
float GetT_DSD_Win();
float SetT_ST_Win(float win);
float GetT_ST_Win();
float SetPS_PaddleCoinc(float win);
float GetPS_PaddleCoinc();
char SetNOLR();
char SetUseLR();
char GetUseLR();
char SetDisregardE();
char SetRequireE();
char GetUseE();
char SetTaggerDebug(int begin,int end);
char GetDebug();
char SetDSD_Debug();
char SetDSD_NoDebug();
char GetDSD_Debug();
char SetPC_Require_TDC();
char SetPC_Disregard_TDC();
char GetPC_Use_TDC();
char SetPS_Require_TDC();
char SetPS_Disregard_TDC();
char GetPS_Use_TDC();
char SetTAC_Require_TDC();
char SetTAC_Disregard_TDC();
char GetTAC_Use_TDC();
int SetTaggerWarning(int mod);
int GetTaggerWarning();
int GetETMapTMin(int ec);
int GetETMapTMax(int ec);
int SetETMapTMin(int ec,int tmin);
int SetETMapTMax(int ec,int tmax);
int WidenETMap(int NTc);
float GetEaverage(int eb);
float SetEaverage(int eb,float eav);

};
#endif /*__cplusplus */
#endif

