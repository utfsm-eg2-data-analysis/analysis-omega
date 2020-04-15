// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TSTPBClass.cc,v 1.3 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>
//____________________ 
//Begin_Html <!--
/* -->
<h1>TSTPBClass</h1>
</pre>
This class is used to access the STPB
bank data written into the ROOT DST by the CLAS TOOL package.
See also packages/bankdefs/stpb.ddl
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "TSTPBClass.h"

ClassImp(TSTPBClass)

TSTPBClass::TSTPBClass(TSTPBClass *TmpSTPB){
SThid   =   TmpSTPB->SThid;
Time   =   TmpSTPB->Time;
Path   =   TmpSTPB->Path;
Status   =   TmpSTPB->Status;
}

void   TSTPBClass::Print(){
cout << "SThid    " <<  SThid  << endl;
cout << "Time    " <<  Time  << endl;
cout << "Path    " <<  Path  << endl;
cout << "Status    " <<  Status  << endl;
}

