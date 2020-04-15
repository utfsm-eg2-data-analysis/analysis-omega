//////////////////////////////////////////////////////////////////////
// 
// TFilter.h
//
//////////////////////////////////////////////////////////////////////

#ifndef __TFilter__
#define __TFilter__

#include "TClasTool.h"
#include "TDSTReader.h"
#include "TCounterCol.h"
#include "TPartSieve.h"
#include "TInterrupt.h"
#include "TH1.h"
#include "TH2.h"
#include "TStopwatch.h"
#include "TBranch.h"
#include "TLeaf.h"

class TFilter: public TClasTool{

 public:

  Int_t gFix_EC_Bank;

  TCounterCol Cuts;  // Collections of counters for all your cuts.
  TObjArray   *H;    // Array that stores your histograms.
  TInterrupt *Interrupt;
  TStopwatch *Time;
  TChain     *chain; // Pointer to input tree.
  TTree      *tree;  // Pointer to the output tree.
  TH1F *H_PID;  // Pointer to the one histogram defined here. 
  Int_t iEvent;  // Event being processed
  Int_t C_Good_Event_Out; // Example for a counter index.

 public:
  TFilter(); // Initialize code
  ~TFilter(){
    delete Time;
    DeleteHistos();
    Cuts.Delete();
  };

  virtual Int_t Run(Int_t Nevt=2147483647);
  virtual void  InitHistos(void);
  virtual Int_t SelectEvent();
  void  SetFixEC(Int_t s=1){gFix_EC_Bank=s;};
  Int_t  GetFixEC(){return gFix_EC_Bank;};
  void  DeleteHistos(void);
  void  ClearHistos(void);
  void  Write(void);
  TTree *Create_Out_Tree(TDSTReader *dstread);


ClassDef(TFilter,1) // A Generic Data Filter Class.
    ;
};

#endif
