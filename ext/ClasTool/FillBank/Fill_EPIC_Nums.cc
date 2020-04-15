////////////////////////////////////////////////////////////
//
// Author: Will Morrison UNH 6/2005
//
// This procedure fills the Event Numbers in the TEPICClass.
//
// Modified:
//
////////////////////////////////////////////////////////////


#include <iostream>
using namespace std;
#include "TObject.h"
#include "TROOT.h"
#include "TEPICClass.h"
#include "TString.h"
#include "clasbanks.h"
#include "TEPICValue.h"

// Function Prototype
void Fill_EPIC_Nums(TEPICClass *gcEPIC, Int_t First, Int_t Last, Int_t run,Int_t First_time, Int_t Last_time, Int_t Current_time);

void Fill_EPIC_Nums(TEPICClass *gcEPIC, Int_t First, Int_t Last, Int_t run, Int_t First_time, Int_t Last_time, Int_t Current_time)
{

  gcEPIC->SetFirst_Phys(First);
  gcEPIC->SetLast_Phys(Last);
  gcEPIC->Setrunno(run);

  gcEPIC->SetFirst_Phys_time(First_time);
  gcEPIC->SetLast_Phys_time(Last_time);
  gcEPIC->SetEvt_time(Current_time);

}


/////////////////////////////////////////////
//
// End Of File
//
/////////////////////////////////////
