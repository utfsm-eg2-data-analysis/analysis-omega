// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TICPBClass.cc,v 1.1 2009/02/03 19:35:31 gavalian Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* --> </pre>
<h1>TICPBClass</h1>
This class is used to access the 
ICPB bank data written into the ROOT DST by WriteRootDST.
It was generated automatically from the ddl file in 
packages/bankdefs/icpb.ddl
and later hand edited to provide comments and additional modifications.
The details on how exactly each variable is defined have to be extraced
from the RECSIS code.
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "TICPBClass.h"

ClassImp(TICPBClass)

TICPBClass::TICPBClass(TICPBClass *TmpICPB){
  Etot = TmpICPB->Etot;
    Ecen= TmpICPB->Ecen;
    Time= TmpICPB->Time;
    T_next= TmpICPB->T_next;
    X= TmpICPB->X;
    Y= TmpICPB->Y;
    Z= TmpICPB->Z;
    M2_hit= TmpICPB->M2_hit;
    M3_hit= TmpICPB->M3_hit;
    Status= TmpICPB->Status;
}

void   TICPBClass::Print(){

}


////////////////////////////////////////////////////////////////
//
//  End of File  TICPBClass.cc
////////////////////////////////////////////////////////////////
