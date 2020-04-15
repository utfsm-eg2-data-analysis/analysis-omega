// @(#)ClasTool/ClasBanks:$Name:  $:$Id: THEADClass.cc,v 1.4 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1> THEADClass</h1>
<pre>
 Modified:
           Maurik (2/3/00) Comments.
</pre>
This class is used to access the 
HEAD
bank data written into the ROOT DST by WriteRootDST
It was generated automatically from the ddl file in 
packages/bankdefs/head.ddl
and later hand edited to provide comments and additional modifications.
The details on how exactly each variable is defined have to be extraced
from the RECSIS code.
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "THEADClass.h"

ClassImp(THEADClass)

THEADClass::THEADClass(THEADClass *TmpHEAD){
Version   =   TmpHEAD->Version;
Nrun   =   TmpHEAD->Nrun;
Nevent   =   TmpHEAD->Nevent;
Time   =   TmpHEAD->Time;
Type   =   TmpHEAD->Type;
Roc   =   TmpHEAD->Roc;
Evtclass   =   TmpHEAD->Evtclass;
Trigbits   =   TmpHEAD->Trigbits;
}

void   THEADClass::Print(){
cout << "VERSION    " <<  Version  << endl;
cout << "NRUN    " <<  Nrun  << endl;
cout << "NEVENT    " <<  Nevent  << endl;
cout << "TIME    " <<  Time  << endl;
cout << "TYPE    " <<  Type  << endl;
cout << "ROC    " <<  Roc  << endl;
cout << "EVTCLASS    " <<  Evtclass  << endl;
cout << "TRIGBITS    " <<  Trigbits  << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  THEADClass.cc
////////////////////////////////////////////////////////////////
