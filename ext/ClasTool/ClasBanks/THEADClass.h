////////////////////////////////////////////////////////////////////////
// THEADClass
// Initial Author: Gagik Gavalian  UNH  11/13/1999 
//
// Generation DATE : Tue Nov 23 18:21:43 EST 1999
//
////////////////////////////////////////////////////////////////////////
#ifndef _THEADClass_ 
#define _THEADClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TString.h"

class THEADClass: public TObject{
  
 public:
  Int_t     Version; // Version number from Recsis
  Int_t     Nrun;    // Run number for this run
  Int_t     Nevent;  // Event number for this run, starts with 1, increases with one for BOS each event in BOS file.
  Int_t     Time;    // Event Time as UNIX time.
  Int_t     Type;    // Event Type: 1-9 Physics event (2= sync, 4=level2 late fail) 10 Scaler event. < 0 Monte Carlo
  Int_t     Roc;     // =0 Sync status ok, >0 = bit pattern of offending ROC.
  Int_t     Evtclass;// Event Classification from DAQ 0=special event, 1-15 Physics event, 16 Sync Event, 17 Prestart, 18 Go, 19 Pause, 20 End.
  Int_t     Trigbits;// Level 1 Trigger Latch word.
 public:
  THEADClass(){};
  THEADClass(THEADClass *TmpHEAD);
  virtual ~THEADClass(){};
  void 	 Print();
  //
  ClassDef(THEADClass,1) //Header information for event
};
#endif


