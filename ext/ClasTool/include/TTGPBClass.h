////////////////////////////////////////////////////////////////////////
// File TTGPBBank.h  
//
// Initial Author: Maurik Holtrop 9/2004
//
////////////////////////////////////////////////////////////////////////
#ifndef _TTGPBClass_ 
#define _TTGPBClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TString.h"

class TTGPBClass: public TObject{
  
 public:
  Int_t     pointer;  // pointer to TAGR
  Float_t   Time;     // starttime_TAG at interaction point(ns)
  Float_t   Energy;   // photon energy (GeV)
  Float_t   dt;       //starttime_ST - starttime_TAG (ns) if no starttime_ST, dt = -starttime_TAG
 public:
  TTGPBClass(){};
  TTGPBClass(TTGPBClass *TmpSTPB);
  virtual ~TTGPBClass(){};

  inline Int_t     GetPointer() { return pointer; } 
  inline Float_t   GetTime()    { return Time ; }
  inline Float_t   GetEnergy()  { return Energy ; }
  inline Float_t   GetDt()      { return dt ; }

  void 	 Print();
  //
  ClassDef(TTGPBClass,1) // Class for accessing the TGPB bank: Tagger
    };
#endif


