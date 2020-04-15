
#ifndef __TInterrupt__
#define __TInterrupt__

#include <iostream>
using namespace std;
#include "TSystem.h"
#include "TSysEvtHandler.h"

class TInterrupt: public TSignalHandler {

 public:
  Int_t NumSig;
  static Int_t fgInterrupted;

 public:
  TInterrupt(): TSignalHandler(kSigInterrupt, kFALSE){NumSig=0;};
  ~TInterrupt(){};
  Bool_t Notify();  //   Override.
  Bool_t IsInterrupted(){ return( fgInterrupted>0);};
  Bool_t IsNotInterrupted(){ return( fgInterrupted==0);};
  

  ClassDef(TInterrupt,1) // TInterrupt
};

#endif
