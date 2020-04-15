
////////////////////////////////////////////////////////////////////////
// File TMiniDSTClass.h  
//
// Initial Author: Gagik Gavalian  UNH  11/13/1999 
//
//
////////////////////////////////////////////////////////////////////////

#ifndef _TMINIDSTClass_ 
#define _TMINIDSTClass_ 

#include <iostream>
using namespace std;

#include <iomanip>
#include "TObject.h"
#include "TVirtualData.h"
#include "TString.h"
#include "TVector3.h"
#include "TMath.h"

class TMiniDSTClass : public TObject{
  
 public:

  TMiniDSTClass();
  TMiniDSTClass(TMiniDSTClass *inst_class);
  virtual ~TMiniDSTClass();

  void   SetFromArray(void *array);
  void   GetArray(void *array);
  void   CopyFrom(TMiniDSTClass *inst_class);

  void   Print();
  void   Zero();

  TVector3  Get3Vector();
  Float_t   GetP2();
  Float_t   GetP();

  //
  //
  //
  //

  Int_t    GetPartID();
  Int_t    GetStatus();
  Float_t  GetPq();
  Float_t  GetPb();
  Float_t  GetPx();
  Float_t  GetPy();
  Float_t  GetPz();
  Float_t  GetVxp();
  Float_t  GetVyp();
  Float_t  GetVzp();
  Float_t  GetThL();
  Float_t  GetPhL();
  Float_t  GetXiec();
  Float_t  GetYiec();
  Float_t  GetEff();
  Float_t  GetEdp();

 public:

  Int_t    fPartID;  // Particle ID
  Int_t    fStatus;  //  Status 
  Float_t  fPq;      // charge
  Float_t  fPb;      // Betta
  Float_t  fPx;      // Momentum X component
  Float_t  fPy;      // Momentum Y component
  Float_t  fPz;      // Momentum Z component
  Float_t  fVxp;     // Vertex X coordinate (reconstructed)
  Float_t  fVyp;     // Vertex Y coordinate (reconstructed)
  Float_t  fVzp;     // Vertex Z coordinate (reconstructed)
  Float_t  fThL;     // Unused 
  Float_t  fPhL;     // Unused
  Float_t  fXiec;    // EC X coordinate
  Float_t  fYiec;    // EC X coordinate  
  Float_t  fEff;     // Unused
  Float_t  fEdp;     // Deposited energy (EC for id=11 and id=22, SC for id=2212)


  ClassDef(TMiniDSTClass,1) // Data class for example limited DST.
};

#endif
    

