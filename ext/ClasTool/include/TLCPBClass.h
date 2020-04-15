////////////////////////////////////////////////////////////////////////
// TLCPBBank
//
// Initial Author: Gagik Gavalian  UNH  11/13/1999 
//
// This file is generated automatically by make_bank_class.pl 
//
// Generation DATE : Tue Nov 23 18:21:58 EST 1999
////////////////////////////////////////////////////////////////////////
#ifndef _TLCPBClass_ 
#define _TLCPBClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TString.h"

class TLCPBClass: public TObject{

 public:
  Int_t     Scht;   // 100*sector+Hit_ID in EC1R
  Float_t   Etot;   // Reconstructed total energy 
  Float_t   Time;   // Flight time relative to the evnt start time
  Float_t   Path;   // Path lenght from target
  Float_t   X;      // x coordinate of the hit
  Float_t   Y;      // y coordinate of the hit
  Float_t   Z;      // z coordinate of the hit
  Float_t   Chi2lc; // Quality measure of geometrical matching
  Int_t     Status; // Status word
  Float_t   Ein;    // Reconstructed energy in the inner part
 public:
  TLCPBClass(){};
  TLCPBClass(TLCPBClass *TmpLCPB);
  virtual ~TLCPBClass(){};
  void 	 Print();
  //
  ClassDef(TLCPBClass,1) //Class for accessing the LCPB Bank (Large Angle Calorimeter)
    };
#endif


