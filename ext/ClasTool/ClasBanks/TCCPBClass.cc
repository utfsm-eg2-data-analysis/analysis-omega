// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TCCPBClass.cc,v 1.4 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* --> </pre>
<h1>TCCPBClass</h1>
This class is used to access the 
CCPB bank data written into the ROOT DST by WriteRootDST.
It was generated automatically from the ddl file in 
packages/bankdefs/ccpb.ddl
and later hand edited to provide comments and additional modifications.
The details on how exactly each variable is defined have to be extraced
from the RECSIS code.
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "TCCPBClass.h"

ClassImp(TCCPBClass)

TCCPBClass::TCCPBClass(TCCPBClass *TmpCCPB){
Scsght   =   TmpCCPB->Scsght;
Nphe   =   TmpCCPB->Nphe;
Time   =   TmpCCPB->Time;
Path   =   TmpCCPB->Path;
Chi2cc   =   TmpCCPB->Chi2cc;
Status   =   TmpCCPB->Status;
}

void   TCCPBClass::Print(){
cout << "ScSgHt    " <<  Scsght  << endl;
cout << "Nphe    " <<  Nphe  << endl;
cout << "Time    " <<  Time  << endl;
cout << "Path    " <<  Path  << endl;
cout << "Chi2CC    " <<  Chi2cc  << endl;
cout << "Status    " <<  Status  << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TCCPBClass.cc
////////////////////////////////////////////////////////////////
