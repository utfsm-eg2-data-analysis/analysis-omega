// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TSCPBClass.cc,v 1.4 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>
//____________________ 
//Begin_Html <!--
/* -->
<h1>TSCPBClass</h1>
<pre>
 Modified:
           Maurik (2/3/00) Comments.
</pre>
This class is used to access the 
SCPB
bank data written into the ROOT DST for the E2 run at Jefferson Lab.
It was generated automatically from the ddl file in 
packages/bankdefs/scpb.ddl
and later hand edited to provide comments and additional modifications.
The details on how exactly each variable is defined have to be extraced
from the RECSIS code.
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "TSCPBClass.h"

ClassImp(TSCPBClass)

TSCPBClass::TSCPBClass(TSCPBClass *TmpSCPB){
Scpdht   =   TmpSCPB->Scpdht;
Edep   =   TmpSCPB->Edep;
Time   =   TmpSCPB->Time;
Path   =   TmpSCPB->Path;
Chi2sc   =   TmpSCPB->Chi2sc;
Status   =   TmpSCPB->Status;
}

void   TSCPBClass::Print(){
cout << "ScPdHt    " <<  Scpdht  << endl;
cout << "Edep    " <<  Edep  << endl;
cout << "Time    " <<  Time  << endl;
cout << "Path    " <<  Path  << endl;
cout << "Chi2SC    " <<  Chi2sc  << endl;
cout << "Status    " <<  Status  << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TSCPBClass.cc
////////////////////////////////////////////////////////////////
