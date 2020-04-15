////////////////////////////////////////////////////////////////////////
// File TECPBBank.h  
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
#ifndef _TCCPBClass_ 
#define _TCCPBClass_ 
#include <iostream>
using namespace std;

#include "TObject.h"
#include "TString.h"

class TCCPBClass: public TObject{
  
 public:
  Int_t     Scsght; // 1000*sector+100*CC_segm_ID+Hit_ID in CCRC
  Float_t   Nphe;   // Number of photo-electrons
  Float_t   Time;   // Flight time relative to the evnt start time
  Float_t   Path;   // Path lenght from target
  Float_t   Chi2cc; // Quality measure of geometrical matching
  Int_t     Status; // Status word (not defined yet)
 public:
  TCCPBClass(){};
  TCCPBClass(TCCPBClass *TmpCCPB);
  virtual ~TCCPBClass(){};
  void 	 Print();
  //
  ClassDef(TCCPBClass,1) // Class for accessing the CCPB bank: Cherencov.
    };
#endif


