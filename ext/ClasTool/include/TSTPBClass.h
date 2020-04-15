////////////////////////////////////////////////////////////////////////
// File TSTPBBank.h  
//
// Initial Author: Maurik Holtrop 9/2004
//
////////////////////////////////////////////////////////////////////////
#ifndef _TSTPBClass_ 
#define _TSTPBClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TString.h"

class TSTPBClass: public TObject {
  
 public:
  Int_t     SThid;  //  100*sector+Hit_ID 
  Float_t   Time;   //  Flight time relative to the evnt start time
  Float_t   Path;   //  Path lenght from target
  //  Float_t   charge; //  charge (get from tracking) NOT USEFULL 
  Int_t     Status; // Status word (not defined yet)
 public:
  TSTPBClass(){};
  TSTPBClass(TSTPBClass *TmpSTPB);
  virtual ~TSTPBClass(){};

  inline  Int_t    GetHitID()  { return ( SThid % 100 ); }
  inline  Int_t    GetSector() { return ( SThid / 100 ) ; }
  inline  Float_t  GetPath()   { return Path; }
  //  inline  Float_t  GetCharge() { return charge; }
  inline  Int_t    GetStatus() { return Status; } 
  void 	 Print();
  //
  ClassDef(TSTPBClass,1) // Class for accessing the STPB bank: Time of Flight.
    };
#endif


