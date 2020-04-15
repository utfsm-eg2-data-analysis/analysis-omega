////////////////////////////////////////////////////////////////////////
// File TECPBBank.h  
//
// Initial Author: Gagik Gavalian  UNH  11/13/1999 
//
//
// This file is generated automatically by make_bank_class.pl 
//
// Generation DATE : Tue Nov 23 18:21:50 EST 1999
//
// Full documentation and comments can be found at
// http://improv.unh.edu/RootBosClasses.html 
//
////////////////////////////////////////////////////////////////////////
#ifndef _TSCPBClass_ 
#define _TSCPBClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TString.h"

class TSCPBClass: public TObject{
  
 public:
  Int_t     Scpdht; // 10000*sector+100*SC_PD_ID+Hit_ID in SCR 
  Float_t   Edep;   // Deposited energy (dE/dX)
  Float_t   Time;   // Flight time relative to the evnt start time
  Float_t   Path;   // Path lenght from target
  Float_t   Chi2sc; // Quality measure of geometrical matching
  Int_t     Status; // Status word (not defined yet)
 public:
  TSCPBClass(){};
  TSCPBClass(TSCPBClass *TmpSCPB);
  virtual ~TSCPBClass(){};
  inline Int_t     GetScpdht() { return Scpdht; }
  inline Float_t   GetEdep()   { return Edep; }
  inline Float_t   GetTime()   { return Time; }
  inline Float_t   GetPath()   { return Path; }
  inline Float_t   GetChi2()   { return Chi2sc; }
  inline Int_t     GetStatus() { return Status; }

  inline Int_t     GetSector() { return Scpdht / 10000 ; }
  inline Int_t     GetPaddle() { return ( Scpdht % 10000 ) / 100 ; }
  inline Int_t     GetHit()    { return ( Scpdht % 10000 ) % 100 ; }
  void 	 Print();
  //
  ClassDef(TSCPBClass,1) // Class for accessing the SCPB bank: Time of Flight.
    };
#endif


