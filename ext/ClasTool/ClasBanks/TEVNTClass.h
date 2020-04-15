////////////////////////////////////////////////////////////////////////
// File TEVNTClass.h  
//
// Initial Author: Gagik Gavalian  UNH  11/13/1999 
//
//
// This file is generated automatically by make_bank_class.pl 
//
// Generation DATE : Tue Nov 23 18:21:36 EST 1999
//
//
// Modified: 
//           Maurik (2/3/00)   Commented variables.
//           Maurik (11/26/01) Add Get functions etc.
//           Maurik (11/27/01) Derive from TVirtualData
////////////////////////////////////////////////////////////////////////
#ifndef _TEVNTClass_ 
#define _TEVNTClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TVirtualData.h"
#include "TString.h"
#include "TVector3.h"
#include "TMath.h"

class TEVNTClass: public TVirtualData {
  
 public:
  TEVNTClass(){};
  TEVNTClass(TEVNTClass *TmpEVNT);
  ~TEVNTClass(){};
  Bool_t IsEVNT(){return(kTRUE);};    // True, since it is an EVNT class
  Bool_t IsGSIM(){return(kFALSE);};   // False...
  void 	 Print();
  //
  //
  //
  //
  ClassDef(TEVNTClass,1) //Class for accessing the EVNT bank: particle information
    };
#endif
    

