////////////////////////////////////////////////////////////////////////
// File TICPBBank.h  
//
// Initial Author: Gagik Gavalian  UNH  11/13/1999 
//
// This file is generated automatically by make_bank_class.pl 
//
// Generation DATE : Tue Nov 23 18:21:56 EST 1999
//
// Modified:
//           Maurik (2/3/00) Comments
//
////////////////////////////////////////////////////////////////////////
#ifndef _TICPBClass_ 
#define _TICPBClass_ 
#include <iostream>
using namespace std;

#include "TObject.h"
#include "TString.h"

class TICPBClass: public TObject{
  
 public:

  Float_t  Etot;
  Float_t  Ecen;
  Float_t  Time;
  Float_t  T_next;
  Float_t  X;
  Float_t  Y;
  Float_t  Z;
  Float_t  M2_hit;
  Float_t  M3_hit;
  Int_t    Status;

 public:
  TICPBClass(){};
  TICPBClass(TICPBClass *TmpCCPB);
  virtual ~TICPBClass(){};
  void 	 Print();
  //
  ClassDef(TICPBClass,1) // Class for accessing the CCPB bank: Cherencov.
    };
#endif


