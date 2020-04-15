
#ifndef __TMINIHEADCLASS__
#define __TMINIHEADCLASS__


#include <iostream>
using namespace std;

#include <iomanip>
#include "TObject.h"
#include "TClonesArray.h"
#include "TString.h"


class TMiniHEADClass : public TObject {

 public:

  Int_t    NRun;
  Int_t    NEvent;
  Float_t  FC;
  Float_t  FCG;
  Float_t  RF1;
  Float_t  Beam_E;
  Float_t  Beam_DT;
  Int_t    Beam_EID;
  Int_t    Helicity;
  

 public:

  TMiniHEADClass();
  virtual ~TMiniHEADClass();

  void   Print();

  ClassDef(TMiniHEADClass,3) // Header class for example limited DST.
};

#endif
