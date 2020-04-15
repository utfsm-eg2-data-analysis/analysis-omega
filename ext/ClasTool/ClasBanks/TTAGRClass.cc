// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TTAGRClass.cc,v 1.3 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
</pre>
<h1>TTAGRClass</h1>
This class is used to access the tagger hits from TGPB bank.
bank data written into the ROOT DST by the CLAS TOOL package.
See also packages/bankdefs/tgpb.ddl
<pre>
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "TTAGRClass.h"

ClassImp(TTAGRClass)

TTAGRClass::TTAGRClass(TTAGRClass *TmpTAGR){
  ERG  = TmpTAGR->ERG;
  TTAG = TmpTAGR->TTAG;
  TPHO = TmpTAGR->TPHO;
  STAT = TmpTAGR->STAT;
  T_id = TmpTAGR->T_id;
  E_id = TmpTAGR->E_id;
}

void   TTAGRClass::Print(){
  cout << "Energy (GEV)  " <<  ERG << endl;
  cout << "Time no RF    " <<  TTAG  << endl;
  cout << "Time w RF cor " <<  TPHO  << endl;
  cout << "STAT          " <<  STAT  << endl;
  cout << "T_id          " <<  T_id  << endl;
  cout << "E_id          " <<  E_id  << endl;
}

