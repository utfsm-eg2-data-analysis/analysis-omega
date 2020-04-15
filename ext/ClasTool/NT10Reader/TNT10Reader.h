/////////////////////////////////////////////////////////////////////////////////
//
//    Header File for TNT10Reader Class 
//
//    Created: Maurik Holtrop UNH  Dec-7-2000
//
//  Modifications:
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __TNT10Reader__
#define __TNT10Reader__

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <unistd.h>

// ROOT includes 

#include "TROOT.h"
#include "TTree.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TFile.h"
#include "TSelector.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TBrowser.h"
#include "TFriendElement.h"
#include "TSystem.h"
#include "TRegexp.h"
#include "TObject.h"
#include "TString.h"
#include "THbookFile.h"
#include "THbookKey.h"

// TARGET_INCLUDE1
#include "TVirtualData.h"
#include "TEVNTClass.h"
#include "TECPBClass.h"
#include "TSCPBClass.h"
#include "TDCPBClass.h"
#include "TCCPBClass.h"
#include "TLCPBClass.h"
#include "THEADClass.h"
#include "THEADERClass.h"
#include "TGSIMClass.h"
#include "THLSClass.h"
#include "TS1STClass.h"
#include "TTRGSClass.h"

#include "TVirtualReader.h"


const Int_t k__BUFSIZE__ = 16384;
const Int_t k__SCALER_BUFSIZE__ = 1024;
const Int_t k__COMPRESS__ = 9;
const Int_t k__MAXFILESIZE__ = 2000000000;  // Max file is about 2Gig.


class TNT10Reader : public TChain, public TVirtualReader{
  //
  // WOA, Multiple inheritance, ain't that cool C++ !
  //
  // A note about multiple inheritance: read Bjarn Stroustrup Chapter 15
  // 
  // Since both TChain and TVirtualReader inherit from TObject, there is
  // an ambiguity whenever any TObject level pointers or methods are 
  // requested, so we have to make specific whether we want the TChain
  // or the TVirtualReader version! You do this for pointers with a cast:
  // TObject *ok = (TChain *)NT10Read;
  // For methods with a ::
  // NT10Read::GetName()
  //
  // Cheers!
  //
 public:


  //
  // Data specific to THIS implementation of a READER.
  //
  THEADERClass *fEvntHeader;   // Event Header pointer
  THEADClass   *fScalerHead;   // Scaler Event Header pointer
  
  TClonesArray *fcaDataPointer;  // Points to fcaEVNTStore or fcaGSIMStore
  TClonesArray *fcaEVNTStore;  // Clones Array for EVNT bank
  TClonesArray *fcaECPBStore;  // Clones Array for ECPB bank
  TClonesArray *fcaSCPBStore;  // Clones Array for SCPB bank
  TClonesArray *fcaDCPBStore;  // Clones Array for DCPB bank
  TClonesArray *fcaCCPBStore;  // Clones Array for CCPB bank
  TClonesArray *fcaLCPBStore;  // Clones Array for LCPB bank
  TClonesArray *fcaTGBIStore;  // Clones Array for TGBI bank


  TBranch *fEvntHeaderBranch;

  TBranch *fEVNTBranch;
  Int_t fnEVNT_Store;
  TEVNTClass *fEVNT;  

  TBranch *fECPBBranch;
  Int_t fnECPB_Store;
  TECPBClass *fECPB;
  
  TBranch *fSCPBBranch;
  Int_t fnSCPB_Store;
  TSCPBClass *fSCPB;

  TBranch *fDCPBBranch;
  Int_t fnDCPB_Store;
  TDCPBClass *fDCPB;

  TBranch *fCCPBBranch;
  Int_t fnCCPB_Store;
  TCCPBClass *fCCPB;
  
  TBranch *fLCPBBranch;
  Int_t fnLCPB_Store;
  TLCPBClass *fLCPB;
  
  TObjArray *fHbookFiles;

  Int_t fNRun;      // The hbook does not store this. Is extracted from filename!
  Int_t fNevents;  // This should contain the total number of entries in the current file.

  
  Int_t fNtLastRead; // Contains the last event read from the ntuple chain.
  Bool_t fReadSequential; // If set false, allow now sequential reads.

  Int_t fNtNum;    // Which ntuple to use, default is 10.

 public:

  // protected:

  static Bool_t fgPawInit;       // Is PAW already initialized?
  static Int_t  *fgLuns;         // Stores the Luns. 10 max.
  Int_t fHbookLun;      // Lun used to open file. Zero if file is not open.
  
  TList    *fList; // list of objects in memory
  TList    *fKeys; //list of Hbook keys (Ids) on disk.


 public:
  TNT10Reader(const char *name="CLASEVENT",const char *title="CLAS Event Tree from hbook ntuple 10 file.");
  ~TNT10Reader();
                                                                                 
  Int_t      Add(const char *name,Int_t nentries=TChain::kBigNumber);
  Int_t      AddFile(const char *name,Int_t nentries=TChain::kBigNumber);
  void       Browse(TBrowser *b);
  Int_t      Draw(const char *varexp, const char *selection, Option_t *option="",Int_t nentries=TChain::kBigNumber, Int_t firstentry=0); // *MENU*
  TObject   *GetBankRow(const Char_t *bankname,Int_t nrow);
  Int_t      GetCurrentEvent();
  GetEntries_return_t   GetEntries() const;
  GetEntries_return_t   GetEntriesFast() const;
  Int_t      GetEntry(Int_t entry=-1, Int_t getall=0);
  Int_t      GetEventNumber();
  TObjArray *GetFiles(void){return fFiles;};
  THEADERClass *GetHEADER(){return(fEvntHeader);}; // return the HEADER bank.
  Int_t      GetNPart(){return(GetNRows());};   // Returns number of particles in event
  Int_t      GetNRows(const Char_t *bankname="EVNT");
  Int_t      GetNtrees(void){return fNtrees;};
  TVector3   GetPart3Vector(Int_t indx);    // Get 3 Vector of Particle in indx-th row
  Int_t      GetPartCharge(Int_t indx);     // Get Particle ID from indx-th row
  Int_t      GetPartID(Int_t indx);         // Get Particle ID from indx-th row
  TVector3   GetPartVertex(Int_t indx);
  TString    GetReaderType();               // Returns the reader type
  Int_t      GetRunNumber();
  TChain    *GetTree(Char_t *treename="EVENT"); // return TChain pointer.
  Int_t      GetTreeNum(void){return fTreeNumber;};
  GetEntries_return_t     *GetTreeOffset(void){return (GetEntries_return_t*)fTreeOffset;};
  Bool_t     IsZombie(){return(fHbookLun==0);} // Is current file OK?
  Int_t      Next(void);              // Get the next entry.
  void       PrintEventStatus();

// HBOOK ONLY:

  Double_t   GetEntriesLoaded(){return fTree->GetEntriesFast();};
  Int_t      GetNTEntries(void) const;
  Bool_t     GetPawInit(void){return fgPawInit;};
  void       Dir(void);
  Int_t      LoadTree(Int_t entry);
  void       NTPrint(void);
  Int_t      SetNtNum(Int_t ntnum=10); // Set the number of the ntuple to use. Default =10.

                                                                  
// protected:

  void  CleanEventClones(void);   // Clean up clones arrays.
  Int_t Close(void);                // Close HBook File.
  Double_t Compute_Entries();
  Int_t Fill_Tree_from_Paw(void);
  void  Fill_HEADER(void);
  void  Fill_EVNT(void);
  void  Fill_DCPB(void);
  void  Fill_ECPB(void);
  void  Fill_SCPB(void);
  void  Fill_CCPB(void);
  void  Fill_LCPB(void);
  void  InitBanks(void);
  Int_t InitBranches(void);
  void  InitClones(void);
  Double_t LoadAll(void);
  Int_t Open(const char *name); // Open HBook File.
  void       SetBranchAddress(const char *bname,void **add);


  ClassDef(TNT10Reader,1) // A class for interfacing to the Monte Carlo.
};

#endif
