// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TS1STClass.cc,v 1.4 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TS1STClass</h1>
<pre>
 Modified:
           Maurik (2/3/00) Comments.
</pre>
This class is used to access the 
S1ST scaler
bank data written into the ROOT DST for the E2 run at Jefferson Lab.
It was generated automatically from the ddl file in 
packages/bankdefs/s1st.ddl
and later hand edited to provide comments and additional modifications.
The details on how exactly each variable is defined have to be extraced
from the RECSIS code.
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "TS1STClass.h"

ClassImp(TS1STClass)

TS1STClass::TS1STClass(TS1STClass *TmpS1ST){
Latch1_bit1_count   =   TmpS1ST->Latch1_bit1_count;
Latch1_bit2_count   =   TmpS1ST->Latch1_bit2_count;
Latch1_bit3_count   =   TmpS1ST->Latch1_bit3_count;
Latch1_bit4_count   =   TmpS1ST->Latch1_bit4_count;
Latch1_bit5_count   =   TmpS1ST->Latch1_bit5_count;
Latch1_bit6_count   =   TmpS1ST->Latch1_bit6_count;
Latch1_bit7_count   =   TmpS1ST->Latch1_bit7_count;
Latch1_bit8_count   =   TmpS1ST->Latch1_bit8_count;
Latch1_bit9_count   =   TmpS1ST->Latch1_bit9_count;
Latch1_bit10_count   =   TmpS1ST->Latch1_bit10_count;
Latch1_bit11_count   =   TmpS1ST->Latch1_bit11_count;
Latch1_bit12_count   =   TmpS1ST->Latch1_bit12_count;
Event_count   =   TmpS1ST->Event_count;
Latch1_zero_count   =   TmpS1ST->Latch1_zero_count;
Latch1_empty_count   =   TmpS1ST->Latch1_empty_count;
Latch1_not_empty_count   =   TmpS1ST->Latch1_not_empty_count;
Latch1_ok_count   =   TmpS1ST->Latch1_ok_count;
Level2_sector1   =   TmpS1ST->Level2_sector1;
Level2_sector2   =   TmpS1ST->Level2_sector2;
Level2_sector3   =   TmpS1ST->Level2_sector3;
Level2_sector4   =   TmpS1ST->Level2_sector4;
Level2_sector5   =   TmpS1ST->Level2_sector5;
Level2_sector6   =   TmpS1ST->Level2_sector6;
Level2_pass   =   TmpS1ST->Level2_pass;
Level2_fail   =   TmpS1ST->Level2_fail;
Latch2_zero_count   =   TmpS1ST->Latch2_zero_count;
Latch2_empty_count   =   TmpS1ST->Latch2_empty_count;
Latch2_not_empty_count   =   TmpS1ST->Latch2_not_empty_count;
Latch2_ok_count   =   TmpS1ST->Latch2_ok_count;
Roc_13_count   =   TmpS1ST->Roc_13_count;
Roc_15_count   =   TmpS1ST->Roc_15_count;
L1l2_zero_count   =   TmpS1ST->L1l2_zero_count;
L1zero_13_count   =   TmpS1ST->L1zero_13_count;
L2zero_13_count   =   TmpS1ST->L2zero_13_count;
L1l2zero_13_count   =   TmpS1ST->L1l2zero_13_count;
}

void   TS1STClass::Print(){
cout << "latch1_bit1_count    " <<  Latch1_bit1_count  << endl;
cout << "latch1_bit2_count    " <<  Latch1_bit2_count  << endl;
cout << "latch1_bit3_count    " <<  Latch1_bit3_count  << endl;
cout << "latch1_bit4_count    " <<  Latch1_bit4_count  << endl;
cout << "latch1_bit5_count    " <<  Latch1_bit5_count  << endl;
cout << "latch1_bit6_count    " <<  Latch1_bit6_count  << endl;
cout << "latch1_bit7_count    " <<  Latch1_bit7_count  << endl;
cout << "latch1_bit8_count    " <<  Latch1_bit8_count  << endl;
cout << "latch1_bit9_count    " <<  Latch1_bit9_count  << endl;
cout << "latch1_bit10_count    " <<  Latch1_bit10_count  << endl;
cout << "latch1_bit11_count    " <<  Latch1_bit11_count  << endl;
cout << "latch1_bit12_count    " <<  Latch1_bit12_count  << endl;
cout << "event_count    " <<  Event_count  << endl;
cout << "latch1_zero_count    " <<  Latch1_zero_count  << endl;
cout << "latch1_empty_count    " <<  Latch1_empty_count  << endl;
cout << "latch1_not_empty_count    " <<  Latch1_not_empty_count  << endl;
cout << "latch1_ok_count    " <<  Latch1_ok_count  << endl;
cout << "level2_sector1    " <<  Level2_sector1  << endl;
cout << "level2_sector2    " <<  Level2_sector2  << endl;
cout << "level2_sector3    " <<  Level2_sector3  << endl;
cout << "level2_sector4    " <<  Level2_sector4  << endl;
cout << "level2_sector5    " <<  Level2_sector5  << endl;
cout << "level2_sector6    " <<  Level2_sector6  << endl;
cout << "level2_pass    " <<  Level2_pass  << endl;
cout << "level2_fail    " <<  Level2_fail  << endl;
cout << "latch2_zero_count    " <<  Latch2_zero_count  << endl;
cout << "latch2_empty_count    " <<  Latch2_empty_count  << endl;
cout << "latch2_not_empty_count    " <<  Latch2_not_empty_count  << endl;
cout << "latch2_ok_count    " <<  Latch2_ok_count  << endl;
cout << "roc_13_count    " <<  Roc_13_count  << endl;
cout << "roc_15_count    " <<  Roc_15_count  << endl;
cout << "l1l2_zero_count    " <<  L1l2_zero_count  << endl;
cout << "l1zero_13_count    " <<  L1zero_13_count  << endl;
cout << "l2zero_13_count    " <<  L2zero_13_count  << endl;
cout << "l1l2zero_13_count    " <<  L1l2zero_13_count  << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TS1STClass.cc
////////////////////////////////////////////////////////////////
