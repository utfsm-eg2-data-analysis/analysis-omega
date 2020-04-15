/*==============================================
// Fill_Event_from_BOS routine
// Fills Event Class Structure from BOS banks
// 
//
// Author : G. Gavalian
// Date   : 10/30/99
===============================================*/

#include "TROOT.h"
#include "THEADERClass.h"

#include "clasbanks.h"

void Fill_HEADER_Bank(THEADERClass *fHeader){

  HEAD HEAD_b(0);
  HEVT HEVT_b(0);
  TGBI TGBI_b(0);

  if(HEAD_b.get_nrows()>0){
    //______________________________________________
    fHeader->NRun     = HEAD_b.get_NRUN(0);
    fHeader->NEvent   = HEAD_b.get_NEVENT(0);
    fHeader->Time     = HEAD_b.get_TIME(0);
    fHeader->Type     = HEAD_b.get_TYPE(0);
    fHeader->ROC      = HEAD_b.get_ROC(0);
    fHeader->EvtClas  = HEAD_b.get_EVTCLASS(0);
    fHeader->TrigBits = HEAD_b.get_TRIGBITS(0);
  }else{
    fHeader->NRun     = 0;
    fHeader->NEvent   = 0;
    fHeader->Time     = 0;
    fHeader->Type     = 0;
    fHeader->ROC      = 0;
    fHeader->EvtClas  = 0;
    fHeader->TrigBits = 0;
  }
  //
  // Filling EVENT Structure from HEVT Bank
  //______________________________________________
  if(HEVT_b.get_nrows()>0){
    fHeader->EStatus	 = HEVT_b.get_ESTATUS(0);
    fHeader->NPGP     = HEVT_b.get_NPGP(0);
    fHeader->TrgPrs   = HEVT_b.get_TRGPRS(0);
    fHeader->FC       = HEVT_b.get_FC(0);
    fHeader->FCG      = HEVT_b.get_FCG(0);
    fHeader->TG       = HEVT_b.get_TG(0);
    fHeader->STT      = HEVT_b.get_STT(0);
    fHeader->RF1      = HEVT_b.get_RF1(0);
    fHeader->RF2      = HEVT_b.get_RF2(0);
  }else{
    fHeader->EStatus  = 0; 
    fHeader->NPGP     = 0;
    fHeader->TrgPrs   = 0;
    fHeader->FC       = 0;
    fHeader->FCG      = 0;
    fHeader->TG       = 0;
    fHeader->STT      = 0;
    fHeader->RF1      = 0;
    fHeader->RF2      = 0;
  }    
//
// Filling EVENT Structure from TGBI Bank
//______________________________________________
  if(TGBI_b.get_nrows()>0){
    fHeader->Latch1          = TGBI_b.get_latch1(0);
    fHeader->Helicity_Scaler = TGBI_b.get_helicity_scaler(0);
    fHeader->Interrupt_Time  = TGBI_b.get_interrupt_time(0);
    fHeader->Level2          = TGBI_b.get_latch1(0);
    fHeader->Level3          = TGBI_b.get_level3(0);

  }else{
    fHeader->Latch1          = 0;
    fHeader->Helicity_Scaler = 0;
    fHeader->Interrupt_Time  = 0;
  }
    
//______________________________________________
}

