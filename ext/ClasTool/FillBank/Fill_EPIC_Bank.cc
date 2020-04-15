/////////////////////////////////////////////////////////////////
//
// File Fill_EPIC_Bank.cc
//
// This procedure fills the EPIC TClonesArray in the TEPICClass class
// from the EPIC events in the BOS Bank
//
// Author: Will Morrison UNH 6/2005
//
// Modified:
//
/////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;
#include "TObject.h"
#include "TROOT.h"
#include "TEPICClass.h"
#include "TString.h"
#include "clasbanks.h"
#include "TEPICValue.h"

// Function Prototype
void Fill_EPIC_Bank(TEPICClass *gcEPIC, EPIC *pEPIC, Int_t nFields);

void Fill_EPIC_Bank(TEPICClass *gcEPIC, EPIC *pEPIC, Int_t nFields){
  
  
  for(Int_t i=0; i<nFields;i++){
    
    TEPICValue* holder;
    holder = new TEPICValue(pEPIC->get_char1(i), pEPIC->get_value(i)); 
    holder->fName.Resize(32);                                      //assures consistency when using string compare functions
                                                                   //in analysis. This is currently the max length of a name in the BOS
    gcEPIC->AddEPIC(holder);
    
  }
  gcEPIC->EPIC->Sort();           //Alphabetically sort
}




  
  

  
////////////////////////////////////////////////////////////////
//
// END OF FILE
//
////////////////////////////////////////////////////////////////
