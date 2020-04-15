////////////////////////////////////////////////////////////////////////
// File TECPBBank.h  
//
// Initial Author: Gagik Gavalian  UNH  11/13/1999 
//
//
// This file is generated automatically by make_bank_class.pl 
//
// Generation DATE : Tue Nov 23 18:22:06 EST 1999
//
// Full documentation and comments can be found at
// http://improv.unh.edu/RootBosClasses.html 
//
////////////////////////////////////////////////////////////////////////
#ifndef _THLSClass_ 
#define _THLSClass_ 
#include <iostream>
using namespace std;

#include "TObject.h"
#include "TString.h"

class THLSClass: public TObject{
  
 public:
  UInt_t     TenMhz;  // 10 Mhz Clock.
  UInt_t     OTR1;  // 
  UInt_t     OTR2;  // 
  UInt_t     SLM  ;  // 
  UInt_t     LVL1R ; // Level 1 trigger rate
  UInt_t     LRC;    // Left Right Miller Coincidences
  UInt_t     LRA;    // Left Right Accidentals
  UInt_t     Fci;   // Faraday Cup Current Amplitude
  UInt_t     Pmt1;  // Luminosity monitor on beam pipe 1
  UInt_t     Pmt2;  // Luminosity monitor on beam pipe 2
  UInt_t     Pmt3;  // Luminosity monitor on beam pipe 3
  UInt_t     Pmt4;  // Luminosity monitor on beam pipe 4
  UInt_t     Res1;  // Reserved 1
  UInt_t     Res2;  // Reserved 2
  UInt_t     HelAcc; // Helicity states accumulating counter.
  UInt_t     HLSAcc; // HLS Banks accumulatiing counter.
 public:
  THLSClass(){};
  THLSClass(THLSClass *TmpHLS);
  virtual ~THLSClass(){};
  Int_t     GetTenMhz(){return((Int_t)TenMhz);};  // Sync Signal
  Int_t     GetOTR1(){return((Int_t)OTR1);}; // Current Amplitude 2C22
  Int_t     GetOTR2(){return((Int_t)OTR2);}; // X Position Amplitude on BPM 2C22
  Int_t     GetSLM(){return((Int_t)SLM);}; // Y Position Amplitude on BPM 2C22
  Int_t     GetLVL1R(){return((Int_t)LVL1R);}; // Current Amplitude 2C24
  Int_t     GetLRC(){return((Int_t)LRC);}; // X Position Amplitude on BPM 2C24
  Int_t     GetLRA(){return((Int_t)LRA);}; // Y Position Amplitude on BPM 2C24
  Int_t     GetFci(){return((Int_t)Fci);};   // Faraday Cup Current Amplitude
  Int_t     GetPmt1(){return((Int_t)Pmt1);};  // Luminosity monitor on beam pipe 1
  Int_t     GetPmt2(){return((Int_t)Pmt2);};  // Luminosity monitor on beam pipe 2
  Int_t     GetPmt3(){return((Int_t)Pmt3);};  // Luminosity monitor on beam pipe 3
  Int_t     GetPmt4(){return((Int_t)Pmt4);};  // Luminosity monitor on beam pipe 4
  Int_t     GetRes1(){return((Int_t)Res1);};  // Reserved 1
  Int_t     GetRes2(){return((Int_t)Res2);};  // Reserved 2
  Int_t     GetHelAcc(){return((Int_t)HelAcc);};
  Int_t     GetHLSAcc(){return((Int_t)HLSAcc);};


  void 	 Print();
  ClassDef(THLSClass,1) //Scaler Bank HLS for Helicity related signals
    };
#endif


