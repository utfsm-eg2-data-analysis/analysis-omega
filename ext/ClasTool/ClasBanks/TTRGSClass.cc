// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TTRGSClass.cc,v 1.4 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TTRGSClass.cc</h1>
<pre>
 Modified:
           Maurik (2/3/00) Comments.
</pre>
This class is used to access the 
TRGS scaler
bank data written into the ROOT DST.
It was generated automatically from the ddl file in 
packages/bankdefs/trgs.ddl
and later hand edited to provide comments and additional modifications.
The details on how exactly each variable is defined have to be extraced
from the RECSIS code.
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "TTRGSClass.h"

ClassImp(TTRGSClass)

TTRGSClass::TTRGSClass(TTRGSClass *TmpTRGS){
Clock_ug   =   TmpTRGS->Clock_ug;
Fcup_ug   =   TmpTRGS->Fcup_ug;
Microsec   =   TmpTRGS->Microsec;
//Notused4   =   TmpTRGS->Notused4;
Mor_st   =   TmpTRGS->Mor_st;
Mor_pc   =   TmpTRGS->Mor_pc;
Mor_ps   =   TmpTRGS->Mor_ps;
Mor_tac   =   TmpTRGS->Mor_tac;
Mor   =   TmpTRGS->Mor;
Pc   =   TmpTRGS->Pc;
Ps   =   TmpTRGS->Ps;
Tac   =   TmpTRGS->Tac;
St   =   TmpTRGS->St;
///Notused14   =   TmpTRGS->Notused14;
Clock_ug_2   =   TmpTRGS->Clock_ug_2;
Fcup_ug_2   =   TmpTRGS->Fcup_ug_2;
Clock_g1   =   TmpTRGS->Clock_g1;
Fcup_g1   =   TmpTRGS->Fcup_g1;
//Notused19   =   TmpTRGS->Notused19;
//Notused20   =   TmpTRGS->Notused20;
Mor_st_rg   =   TmpTRGS->Mor_st_rg;
Mor_pc_rg   =   TmpTRGS->Mor_pc_rg;
Mor_ps_rg   =   TmpTRGS->Mor_ps_rg;
Mor_tac_rg   =   TmpTRGS->Mor_tac_rg;
Mor_rg   =   TmpTRGS->Mor_rg;
Pc_rg   =   TmpTRGS->Pc_rg;
Ps_rg   =   TmpTRGS->Ps_rg;
Tac_rg   =   TmpTRGS->Tac_rg;
St_rg   =   TmpTRGS->St_rg;
//Notused30   =   TmpTRGS->Notused30;
Clock_g1_2   =   TmpTRGS->Clock_g1_2;
Fcup_g1_2   =   TmpTRGS->Fcup_g1_2;
Clock_g2   =   TmpTRGS->Clock_g2;
Fcup_g2   =   TmpTRGS->Fcup_g2;
//Notused35   =   TmpTRGS->Notused35;
//Notused36   =   TmpTRGS->Notused36;
//Notused37   =   TmpTRGS->Notused37;
//Notused38   =   TmpTRGS->Notused38;
//Notused39   =   TmpTRGS->Notused39;
//Notused40   =   TmpTRGS->Notused40;
Mor_lg   =   TmpTRGS->Mor_lg;
//Notused42   =   TmpTRGS->Notused42;
//Notused43   =   TmpTRGS->Notused43;
//Notused44   =   TmpTRGS->Notused44;
//Notused45   =   TmpTRGS->Notused45;
//Notused46   =   TmpTRGS->Notused46;
Clock_g2_2   =   TmpTRGS->Clock_g2_2;
Fcup_g2_2   =   TmpTRGS->Fcup_g2_2;
Trig1_ug   =   TmpTRGS->Trig1_ug;
Trig2_ug   =   TmpTRGS->Trig2_ug;
Trig3_ug   =   TmpTRGS->Trig3_ug;
Trig4_ug   =   TmpTRGS->Trig4_ug;
Trig5_ug   =   TmpTRGS->Trig5_ug;
Trig6_ug   =   TmpTRGS->Trig6_ug;
Trig7_ug   =   TmpTRGS->Trig7_ug;
Trig8_ug   =   TmpTRGS->Trig8_ug;
Trig9_ug   =   TmpTRGS->Trig9_ug;
Trig10_ug   =   TmpTRGS->Trig10_ug;
Trig11_ug   =   TmpTRGS->Trig11_ug;
Trig12_ug   =   TmpTRGS->Trig12_ug;
Trig_or_ug   =   TmpTRGS->Trig_or_ug;
L1accept   =   TmpTRGS->L1accept;
//Notused63   =   TmpTRGS->Notused63;
//Notused64   =   TmpTRGS->Notused64;
L2fail   =   TmpTRGS->L2fail;
L2pass   =   TmpTRGS->L2pass;
L2start   =   TmpTRGS->L2start;
L2clear   =   TmpTRGS->L2clear;
L2accept   =   TmpTRGS->L2accept;
L3accept   =   TmpTRGS->L3accept;
//Notused71   =   TmpTRGS->Notused71;
//Notused72   =   TmpTRGS->Notused72;
//Notused73   =   TmpTRGS->Notused73;
//Notused74   =   TmpTRGS->Notused74;
//Notused75   =   TmpTRGS->Notused75;
//Notused76   =   TmpTRGS->Notused76;
//Notused77   =   TmpTRGS->Notused77;
//Notused78   =   TmpTRGS->Notused78;
//Notused79   =   TmpTRGS->Notused79;
//Notused80   =   TmpTRGS->Notused80;
}

void   TTRGSClass::Print(){
cout << "CLOCK_UG    " <<  Clock_ug  << endl;
cout << "FCUP_UG    " <<  Fcup_ug  << endl;
cout << "MICROSEC    " <<  Microsec  << endl;
//cout << "NotUsed4    " <<  Notused4  << endl;
cout << "MOR_ST    " <<  Mor_st  << endl;
cout << "MOR_PC    " <<  Mor_pc  << endl;
cout << "MOR_PS    " <<  Mor_ps  << endl;
cout << "MOR_TAC    " <<  Mor_tac  << endl;
cout << "MOR    " <<  Mor  << endl;
cout << "PC    " <<  Pc  << endl;
cout << "PS    " <<  Ps  << endl;
cout << "TAC    " <<  Tac  << endl;
cout << "ST    " <<  St  << endl;
//cout << "NotUsed14    " <<  Notused14  << endl;
cout << "clock_ug_2    " <<  Clock_ug_2  << endl;
cout << "fcup_ug_2    " <<  Fcup_ug_2  << endl;
cout << "CLOCK_G1    " <<  Clock_g1  << endl;
cout << "FCUP_G1    " <<  Fcup_g1  << endl;
//cout << "NotUsed19    " <<  Notused19  << endl;
//cout << "NotUsed20    " <<  Notused20  << endl;
cout << "MOR_ST_rg    " <<  Mor_st_rg  << endl;
cout << "MOR_PC_rg    " <<  Mor_pc_rg  << endl;
cout << "MOR_PS_rg    " <<  Mor_ps_rg  << endl;
cout << "MOR_TAC_rg    " <<  Mor_tac_rg  << endl;
cout << "MOR_rg    " <<  Mor_rg  << endl;
cout << "PC_rg    " <<  Pc_rg  << endl;
cout << "PS_rg    " <<  Ps_rg  << endl;
cout << "TAC_rg    " <<  Tac_rg  << endl;
cout << "ST_rg    " <<  St_rg  << endl;
//cout << "NotUsed30    " <<  Notused30  << endl;
cout << "clock_g1_2    " <<  Clock_g1_2  << endl;
cout << "fcup_g1_2    " <<  Fcup_g1_2  << endl;
cout << "CLOCK_G2    " <<  Clock_g2  << endl;
cout << "FCUP_G2    " <<  Fcup_g2  << endl;
//cout << "NotUsed35    " <<  Notused35  << endl;
//cout << "NotUsed36    " <<  Notused36  << endl;
//cout << "NotUsed37    " <<  Notused37  << endl;
//cout << "NotUsed38    " <<  Notused38  << endl;
//cout << "NotUsed39    " <<  Notused39  << endl;
//cout << "NotUsed40    " <<  Notused40  << endl;
cout << "MOR_lg    " <<  Mor_lg  << endl;
//cout << "NotUsed42    " <<  Notused42  << endl;
//cout << "NotUsed43    " <<  Notused43  << endl;
//cout << "NotUsed44    " <<  Notused44  << endl;
//cout << "NotUsed45    " <<  Notused45  << endl;
//cout << "NotUsed46    " <<  Notused46  << endl;
cout << "clock_g2_2    " <<  Clock_g2_2  << endl;
cout << "fcup_g2_2    " <<  Fcup_g2_2  << endl;
cout << "trig1_ug    " <<  Trig1_ug  << endl;
cout << "trig2_ug    " <<  Trig2_ug  << endl;
cout << "trig3_ug    " <<  Trig3_ug  << endl;
cout << "trig4_ug    " <<  Trig4_ug  << endl;
cout << "trig5_ug    " <<  Trig5_ug  << endl;
cout << "trig6_ug    " <<  Trig6_ug  << endl;
cout << "trig7_ug    " <<  Trig7_ug  << endl;
cout << "trig8_ug    " <<  Trig8_ug  << endl;
cout << "trig9_ug    " <<  Trig9_ug  << endl;
cout << "trig10_ug    " <<  Trig10_ug  << endl;
cout << "trig11_ug    " <<  Trig11_ug  << endl;
cout << "trig12_ug    " <<  Trig12_ug  << endl;
cout << "trig_or_ug    " <<  Trig_or_ug  << endl;
cout << "l1accept    " <<  L1accept  << endl;
//cout << "notused63    " <<  Notused63  << endl;
//cout << "notused64    " <<  Notused64  << endl;
cout << "l2fail    " <<  L2fail  << endl;
cout << "l2pass    " <<  L2pass  << endl;
cout << "l2start    " <<  L2start  << endl;
cout << "l2clear    " <<  L2clear  << endl;
cout << "l2accept    " <<  L2accept  << endl;
cout << "l3accept    " <<  L3accept  << endl;
//cout << "notused71    " <<  Notused71  << endl;
//cout << "notused72    " <<  Notused72  << endl;
//cout << "notused73    " <<  Notused73  << endl;
//cout << "notused74    " <<  Notused74  << endl;
//cout << "notused75    " <<  Notused75  << endl;
//cout << "notused76    " <<  Notused76  << endl;
//cout << "notused77    " <<  Notused77  << endl;
//cout << "notused78    " <<  Notused78  << endl;
//cout << "notused79    " <<  Notused79  << endl;
//cout << "notused80    " <<  Notused80  << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TTRGSClass.cc
////////////////////////////////////////////////////////////////
