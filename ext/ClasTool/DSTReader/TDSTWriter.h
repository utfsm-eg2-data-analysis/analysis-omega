//========================================================
//   TDSTWriter class provides interface to selectively write
//   banks from ROOT Dst. This can be used to leave out unneccesay banks.
//  Also for writing specific events matching user given pattern.
//
//  Author : G.Gavalian (ODU)
//  Date   : 01/07/2008
//
//=========================================================


#ifndef __TGDST_WRITER__
#define __TGDST_WRITER__


#define __BUFFSIZE__  16384

#include <TROOT.h>
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>

#include "TVirtualReader.h"
#include "TDSTReader.h"

//
// CLAS Banks Includes
//

#include "THEADERClass.h"
#include "TEVNTClass.h"
#include "TECPBClass.h"
#include "TSCPBClass.h"
#include "TDCPBClass.h"
#include "TCCPBClass.h"
#include "TICPBClass.h"
#include "TICHBClass.h"
#include "TFBPMClass.h"
#include "TLCPBClass.h"
#include "THEADClass.h"
#include "TTGBIClass.h"
#include "TEPICClass.h"

// Photon Banks

#include "TSTPBClass.h"
#include "TTGPBClass.h"
#include "TTAGRClass.h"


// GSIM Bank 
#include "TMCHDClass.h"

#include "TGSIMClass.h"
#include "TVERTClass.h"
#include "TMVRTClass.h"
#include "TTBERClass.h"

//
// Scaler Banks
//
#include "THLSClass.h"
#include "TS1STClass.h"
#include "TTRGSClass.h"

// Storage helper class.
#include "TStoreClone.h"


class TDSTWriter : public TObject
{

 public:

  TDSTWriter();
  ~TDSTWriter();

  void   SetCompression(Int_t level);
  Int_t  OpenFile(const char *filename, const char *title = "UNTITLED");
  void   ClearEvent();
  void   WriteEvent();
  void   CopyBanks(TVirtualReader *fReader);
  void   AddBank(const char *_bnkname,TObject *_bnkptr);
  //  void   AddBankList();
  void   SetHeader(THEADERClass  *_fHeader);
  void   CloseFile();
  Int_t  BankStatus(const char *_bnk_name);
  void   Init_Clones();
  void   ClearClones();
  void   Init_Branches();

  void   AddBankName(const char *_bnkname);
  void   AddBankList(const char *_bnkname);
  void   ShowBanks();

  //  void   SetHeader(TMiniHEADClass *tc_header);
  //  void   SetElectron(TMiniDSTClass *tc_elec);
  //  void   SetProton(TMiniDSTClass *tc_prot);
  //  void   AddParticle(TMiniDSTClass *tc_part);
  void   Print();
  void   PrintStat();

 public:
  
  TFile  *fDSTFile;
  TTree  *fEventTree;

  //  TMiniHEADClass  *fEventHeader;
  TClonesArray    *fcaPARTStore;
  //  TMiniDSTClass   *fbElectron;
  //  TMiniDSTClass   *fbProton;
  Int_t            nPARTStore;
  Int_t            fCompression;
 
  TClonesArray *EVNTStore;
  //static  TClonesArray *fgEVNTStore;
  TClonesArray *ECPBStore;
  //static  TClonesArray *fgECPBStore;
  TClonesArray *SCPBStore;
  //static  TClonesArray *fgSCPBStore;
  TClonesArray *DCPBStore;
  //static  TClonesArray *fgDCPBStore;
  TClonesArray *CCPBStore;
  
  TClonesArray *ICPBStore;
  TClonesArray *ICHBStore;
  TClonesArray *FBPMStore;
  //static  TClonesArray *fgCCPBStore;
  TClonesArray *LCPBStore;
  //static  TClonesArray *fgLCPBStore;
  TClonesArray *STPBStore;
  //static TClonesArray *fgSTPBStore;
  TClonesArray *TGPBStore;
  //static TClonesArray *fgTGPBStore;
  TClonesArray *TAGRStore;
  //static TClonesArray *fgTAGRStore;
  TClonesArray *VERTStore;
  //static TClonesArray *fgVERTStore;
  TClonesArray *MVRTStore;
  //static TClonesArray *fgMVRTStore;
  TClonesArray *TBERStore;
  //static TClonesArray *fgTBERStore;
  TClonesArray *TGBIStore;
  //static  TClonesArray *fgTGBIStore;
  TClonesArray *GSIMStore;
  //static  TClonesArray *fgGSIMStore;

  // Branches
 
  TBranch *brHeader;
  TBranch *brPART;
  TBranch *brElectron;
  TBranch *brProton;

  THashList fClones;          // Store pointers to TClonesArray of main data
  THashList fScalerClones;    // Store pointers to TClonesArray of scalers.

  ////////////////////////////////////////////////
//    Branch Declaration ...
/////////////////////////////////////////////////

  THEADERClass *hHEADER;
  TBranch *HEADERBranch;
  
  // TARGET_INCLUDE4
  TBranch *EVNTBranch;
  Int_t nEVNT_Store;
  
  TBranch *ECPBBranch;
  Int_t nECPB_Store;
  
  TBranch *SCPBBranch;
  Int_t nSCPB_Store;
  
  TBranch *DCPBBranch;
  Int_t nDCPB_Store;
  
  TBranch *CCPBBranch;
  Int_t nCCPB_Store;

  TBranch *ICPBBranch;
  Int_t nICPB_Store;

  TBranch *ICHBBranch;
  Int_t nICHB_Store;
  TBranch *FBPMBranch;
  Int_t nFBPM_Store;

  TBranch *LCPBBranch;
  Int_t nLCPB_Store;
  
  
  TBranch *STPBBranch;
  Int_t nSTPB_Store;
  
  TBranch *TGPBBranch;
  Int_t nTGPB_Store;
  
  TBranch *TAGRBranch;
  Int_t nTAGR_Store;
  
  
  
  
  TBranch *VERTBranch;
  Int_t nVERT_Store;
  
  TBranch *MVRTBranch;
  Int_t nMVRT_Store;
  
  
  
  TBranch *TBERBranch;
  Int_t nTBER_Store;
  
  
  TBranch *TGBIBranch;
  Int_t nTGBI_Store;
  
  TBranch *GSIMBranch;
  Int_t nGSIM_Store;

  

  ClassDef(TDSTWriter,1) // Example of a limited DST that takes less space (writer).
};

#endif
