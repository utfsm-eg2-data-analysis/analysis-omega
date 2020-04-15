// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TTGBIClass.cc,v 1.4 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TTGBIClass.cc<h1>
<!-- */ // -->


#include "TTGBIClass.h"

ClassImp(TTGBIClass)

TTGBIClass::TTGBIClass(TTGBIClass *TmpTGBI){
Latch1   =   TmpTGBI->Latch1;
Helicity_scaler   =   TmpTGBI->Helicity_scaler;
Interrupt_time   =   TmpTGBI->Interrupt_time;
Latch2   =   TmpTGBI->Latch2;
Level3   =   TmpTGBI->Level3;
}

void   TTGBIClass::Print(){
cout << "latch1    " <<  Latch1  << endl;
cout << "helicity_scaler    " <<  Helicity_scaler  << endl;
cout << "interrupt_time    " <<  Interrupt_time  << endl;
cout << "latch2    " <<  Latch2  << endl;
cout << "level3    " <<  Level3  << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TTGBIClass.cc
////////////////////////////////////////////////////////////////
