////////////////////////////////////////////////////////////////////////
// File TECPBBank.h  
//
// Initial Author: Gagik Gavalian  UNH  11/13/1999 
//
//
// This file is generated automatically by make_bank_class.pl 
//
// Generation DATE : Thu Jan 31 11:55:08 EST 2002
//
// Full documentation and comments can be found at
// http://improv.unh.edu/RootBosClasses.html 
//
////////////////////////////////////////////////////////////////////////
#ifndef _TTGBIClass_ 
#define _TTGBIClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TString.h"

class TTGBIClass: public TObject{

public:
  Int_t     Latch1;           // Level 1 trigger Latch word.
  Int_t     Helicity_scaler;  // helicity interval count.
  Int_t     Interrupt_time;   // interrupt time from microsec clock/
  Int_t     Latch2;           // level2 trigger latch.
  Int_t     Level3;           // level3 trigger latch.
public:
	 TTGBIClass(){};
	 TTGBIClass(TTGBIClass *TmpTGBI);
	 virtual ~TTGBIClass(){};
void 	 Print();
//
//
//
 ClassDef(TTGBIClass,1) // Class for accessing the TGBI bank: trigger info.
};
#endif


