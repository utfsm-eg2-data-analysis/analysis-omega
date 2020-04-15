// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TTGPBClass.cc,v 1.3 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
</pre>
<h1>TTGPBClass</h1>
This class is used to access the tagger hits from TGPB bank.
bank data written into the ROOT DST by the CLAS TOOL package.
See also packages/bankdefs/tgpb.ddl
<pre>
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "TTGPBClass.h"

ClassImp(TTGPBClass)

TTGPBClass::TTGPBClass(TTGPBClass *TmpSTPB){
pointer  = TmpSTPB->pointer;
Time     = TmpSTPB->Time;
Energy   = TmpSTPB->Energy;
dt       = TmpSTPB->dt;
}

void   TTGPBClass::Print(){
cout << "pointer    " <<  pointer  << endl;
cout << "Time    " <<  Time  << endl;
cout << "Energy    " <<  Energy  << endl;
cout << "dt      " <<  dt  << endl;
}

