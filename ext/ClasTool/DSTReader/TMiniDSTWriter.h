//========================================================
//   TMiniDSTWriter class provides tools for generating
//  Mini DSTs.
//
//
//  Author : G.Gavalian (UNH)
//  Date   : 04/12/2002
//
//=========================================================


#ifndef __TMINIDST_WRITER__
#define __TMINIDST_WRITER__


#define __BUFFSIZE__  16384

#include <TROOT.h>
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>
#include "TMiniDSTClass.h"
#include "TMiniHEADClass.h"
#include "TGSIMClass.h"


class TMiniDSTWriter : public TObject
{

 public:

  TMiniDSTWriter();
  ~TMiniDSTWriter();

  void   SetCompression(Int_t level);
  Int_t  OpenFile(const char *filename, const char *title = "UNTITLED");
  void   ClearEvent();
  void   WriteEvent();
  void   CloseFile();

  void   Init_Clones();
  void   ClearClones();
  void   Init_Branches();


  void   SetHeader(TMiniHEADClass *tc_header);
  void   SetElectron(TMiniDSTClass *tc_elec);
  void   SetProton(TMiniDSTClass *tc_prot);
  void   AddParticle(TMiniDSTClass *tc_part);
  void   AddGSIMParticle(TGSIMClass *tc_part);
  void   Print();
  void   PrintStat();

 public:
  
  TFile  *fDSTFile;
  TTree  *fEventTree;

  TMiniHEADClass  *fEventHeader;
  TClonesArray    *fcaPARTStore;
  TClonesArray    *fcaGSIMStore;
  TMiniDSTClass   *fbElectron;
  TMiniDSTClass   *fbProton;
  Int_t            nPARTStore;
  Int_t            nGSIMStore;
  Int_t            fCompression;

  // Branches
 
  TBranch *brHeader;
  TBranch *brPART;
  TBranch *brGSIM;
  TBranch *brElectron;
  TBranch *brProton;
  

  ClassDef(TMiniDSTWriter,1) // Example of a limited DST that takes less space (writer).
};

#endif
