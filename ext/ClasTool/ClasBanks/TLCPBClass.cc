// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TLCPBClass.cc,v 1.4 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TLCPBClass</h1>
<pre>
 Modified:
           Maurik (2/3/00) Comments.
</pre>
This class is used to access the 
LCPB
bank data written into the ROOT DST for the E2 run at Jefferson Lab.
It was generated automatically from the ddl file in 
packages/bankdefs/LCPB.ddl
and later hand edited to provide comments and additional modifications.
The details on how exactly each variable is defined have to be extraced
from the RECSIS code.
<pre> 
<!-- */ 
// --> End_Html   
/////////////////////////////////////////////////////////////////////////

#include "TLCPBClass.h"

ClassImp(TLCPBClass)

TLCPBClass::TLCPBClass(TLCPBClass *TmpLCPB){
Scht   =   TmpLCPB->Scht;
Etot   =   TmpLCPB->Etot;
Time   =   TmpLCPB->Time;
Path   =   TmpLCPB->Path;
X   =   TmpLCPB->X;
Y   =   TmpLCPB->Y;
Z   =   TmpLCPB->Z;
Chi2lc   =   TmpLCPB->Chi2lc;
Status   =   TmpLCPB->Status;
Ein   =   TmpLCPB->Ein;
}

void   TLCPBClass::Print(){
cout << "ScHt    " <<  Scht  << endl;
cout << "Etot    " <<  Etot  << endl;
cout << "Time    " <<  Time  << endl;
cout << "Path    " <<  Path  << endl;
cout << "X    " <<  X  << endl;
cout << "Y    " <<  Y  << endl;
cout << "Z    " <<  Z  << endl;
cout << "Chi2LC    " <<  Chi2lc  << endl;
cout << "Status    " <<  Status  << endl;
cout << "Ein    " <<  Ein  << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TLCPBClass.cc
////////////////////////////////////////////////////////////////
