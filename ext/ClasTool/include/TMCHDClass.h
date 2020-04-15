////////////////////////////////////////////////////////////////////////
// TMCHDClass
// Initial Author: Hovanes Egiyan  UNH  10/07/2006 
//
//
////////////////////////////////////////////////////////////////////////
#ifndef _TMCHDClass_ 
#define _TMCHDClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TString.h"
#include "TLorentzVector.h"

class TMCHDClass: public TObject {
  
 public:
  Int_t      Nrun;    // Run number for this run
  Int_t      Nevent;  // Event number for this run, starts with 1, increases with one for BOS each event in BOS file.
  Int_t      Time;    // Event Time as UNIX time.
  Int_t      Type;    // Event Type: 1-9 Physics event (2= sync, 4=level2 late fail) 10 Scaler event. < 0 Monte Carlo
  Int_t      ReacType;// Reaction Type 
  Float_t    Weight;  // event Weight
  TLorentzVector Photon; // Photon (real or virtual) vector 
  TLorentzVector Target; // Target vector 
  
 public:
  TMCHDClass(){};
  TMCHDClass(TMCHDClass *TmpMVHD);
  virtual ~TMCHDClass(){};
  void 	 Print();

  inline Int_t    GetNrun() { return Nrun ; }
  inline Int_t    GetNevent() { return Nevent ; }
  inline Int_t    GetTime() { return Time ; }
  inline Int_t    GetType() { return Type ; }
  inline Int_t    GetReacType() { return ReacType ; }
  inline Float_t  GetWeight() { return Weight ; }
  inline TLorentzVector GetPhoton() { return Photon ; }
  inline TLorentzVector GetTarget() { return Target ; }
  //
  ClassDef(TMCHDClass,1) //Header information for event
};
#endif


