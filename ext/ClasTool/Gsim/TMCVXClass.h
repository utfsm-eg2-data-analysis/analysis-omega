#ifndef _TMCVXClass_ 
#define _TMCVXClass_ 
#include <iostream>

#include "TObject.h"
#include "TString.h"
#include "TGsim.h"

class TMCVXClass: public TObject{

//  1  x       F   -1000.  2000.    ! x of vertex
//  2  y       F   -1000.  2000.    ! y
//  3  z       F   -1000.  2000.    ! z
//  4  tof     F     0.0   999999.   ! secs of flight
//  5  flag    I       0   65536    ! vertex flag


public:
  Float_t x; //       F   -1000.  2000.    ! x of vertex
  Float_t y; //       F   -1000.  2000.    ! y
  Float_t z; //       F   -1000.  2000.    ! z
  Float_t tof; //     F     0.0   999999.  ! secs of flight
  Int_t   flag; //    I       0   65536    ! vertex flag

public:
	 TMCVXClass(){};
	 TMCVXClass(TMCVXClass *Tmp);
	 TMCVXClass(void *Tmp,Int_t i=0);
	 virtual ~TMCVXClass(){};
	 void 	 Print(void);
//
	 ClassDef(TMCVXClass,1) // Class for accessing the MCVX bank: Monte Carlo vertex.
};
#endif
