//////////////////////////////////////////////////////////////
//
//   File Fill_TRGS_Bank.cc
//
//   This procedure Fills TTRGSClass class from BOS Bank 
//
//  Author :  Gagik Gavalian   UNH  11/10/1999
//
//  Modified: Maurik Holtrop UNH 3/4/00 -- TRGS class modified to lowercase the get_MICROSEC method.
//  This file was automaticaly Generated on : 
//	Tue Nov 23 18:20:39 EST 1999 
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TTRGSClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_TRGS_Bank(TTRGSClass *gcTRGS,TRGS *pTRGS , int nrow);


void  Fill_TRGS_Bank(TTRGSClass *gcTRGS, TRGS *pTRGS , int nrow){
gcTRGS->Clock_ug  = pTRGS->get_CLOCK_UG(nrow);
gcTRGS->Fcup_ug  = pTRGS->get_FCUP_UG(nrow);
 gcTRGS->Microsec  = pTRGS->get_Microsec(nrow); // Mod(3/4/00) MWH: lowercased.
//gcTRGS->Notused4  = pTRGS->get_NotUsed4(nrow);
gcTRGS->Mor_st  = pTRGS->get_MOR_ST(nrow);
gcTRGS->Mor_pc  = pTRGS->get_MOR_PC(nrow);
gcTRGS->Mor_ps  = pTRGS->get_MOR_PS(nrow);
gcTRGS->Mor_tac  = pTRGS->get_MOR_TAC(nrow);
gcTRGS->Mor  = pTRGS->get_MOR(nrow);
gcTRGS->Pc  = pTRGS->get_PC(nrow);
gcTRGS->Ps  = pTRGS->get_PS(nrow);
gcTRGS->Tac  = pTRGS->get_TAC(nrow);
gcTRGS->St  = pTRGS->get_ST(nrow);
//gcTRGS->Notused14  = pTRGS->get_NotUsed14(nrow);
gcTRGS->Clock_ug_2  = pTRGS->get_clock_ug_2(nrow);
gcTRGS->Fcup_ug_2  = pTRGS->get_fcup_ug_2(nrow);
gcTRGS->Clock_g1  = pTRGS->get_CLOCK_G1(nrow);
gcTRGS->Fcup_g1  = pTRGS->get_FCUP_G1(nrow);
//gcTRGS->Notused19  = pTRGS->get_NotUsed19(nrow);
//gcTRGS->Notused20  = pTRGS->get_NotUsed20(nrow);
gcTRGS->Mor_st_rg  = pTRGS->get_MOR_ST_rg(nrow);
gcTRGS->Mor_pc_rg  = pTRGS->get_MOR_PC_rg(nrow);
gcTRGS->Mor_ps_rg  = pTRGS->get_MOR_PS_rg(nrow);
gcTRGS->Mor_tac_rg  = pTRGS->get_MOR_TAC_rg(nrow);
gcTRGS->Mor_rg  = pTRGS->get_MOR_rg(nrow);
gcTRGS->Pc_rg  = pTRGS->get_PC_rg(nrow);
gcTRGS->Ps_rg  = pTRGS->get_PS_rg(nrow);
gcTRGS->Tac_rg  = pTRGS->get_TAC_rg(nrow);
gcTRGS->St_rg  = pTRGS->get_ST_rg(nrow);
//gcTRGS->Notused30  = pTRGS->get_NotUsed30(nrow);
gcTRGS->Clock_g1_2  = pTRGS->get_clock_g1_2(nrow);
gcTRGS->Fcup_g1_2  = pTRGS->get_fcup_g1_2(nrow);
gcTRGS->Clock_g2  = pTRGS->get_CLOCK_G2(nrow);
gcTRGS->Fcup_g2  = pTRGS->get_FCUP_G2(nrow);
//gcTRGS->Notused35  = pTRGS->get_NotUsed35(nrow);
//gcTRGS->Notused36  = pTRGS->get_NotUsed36(nrow);
//gcTRGS->Notused37  = pTRGS->get_NotUsed37(nrow);
//gcTRGS->Notused38  = pTRGS->get_NotUsed38(nrow);
//gcTRGS->Notused39  = pTRGS->get_NotUsed39(nrow);
//gcTRGS->Notused40  = pTRGS->get_NotUsed40(nrow);
gcTRGS->Mor_lg  = pTRGS->get_MOR_lg(nrow);
//gcTRGS->Notused42  = pTRGS->get_NotUsed42(nrow);
//gcTRGS->Notused43  = pTRGS->get_NotUsed43(nrow);
//gcTRGS->Notused44  = pTRGS->get_NotUsed44(nrow);
//gcTRGS->Notused45  = pTRGS->get_NotUsed45(nrow);
//gcTRGS->Notused46  = pTRGS->get_NotUsed46(nrow);
gcTRGS->Clock_g2_2  = pTRGS->get_clock_g2_2(nrow);
gcTRGS->Fcup_g2_2  = pTRGS->get_fcup_g2_2(nrow);
gcTRGS->Trig1_ug  = pTRGS->get_trig1_ug(nrow);
gcTRGS->Trig2_ug  = pTRGS->get_trig2_ug(nrow);
gcTRGS->Trig3_ug  = pTRGS->get_trig3_ug(nrow);
gcTRGS->Trig4_ug  = pTRGS->get_trig4_ug(nrow);
gcTRGS->Trig5_ug  = pTRGS->get_trig5_ug(nrow);
gcTRGS->Trig6_ug  = pTRGS->get_trig6_ug(nrow);
gcTRGS->Trig7_ug  = pTRGS->get_trig7_ug(nrow);
gcTRGS->Trig8_ug  = pTRGS->get_trig8_ug(nrow);
gcTRGS->Trig9_ug  = pTRGS->get_trig9_ug(nrow);
gcTRGS->Trig10_ug  = pTRGS->get_trig10_ug(nrow);
gcTRGS->Trig11_ug  = pTRGS->get_trig11_ug(nrow);
gcTRGS->Trig12_ug  = pTRGS->get_trig12_ug(nrow);
gcTRGS->Trig_or_ug  = pTRGS->get_trig_or_ug(nrow);
gcTRGS->L1accept  = pTRGS->get_l1accept(nrow);
//gcTRGS->Notused63  = pTRGS->get_notused63(nrow);
//gcTRGS->Notused64  = pTRGS->get_notused64(nrow);
gcTRGS->L2fail  = pTRGS->get_l2fail(nrow);
gcTRGS->L2pass  = pTRGS->get_l2pass(nrow);
gcTRGS->L2start  = pTRGS->get_l2start(nrow);
gcTRGS->L2clear  = pTRGS->get_l2clear(nrow);
gcTRGS->L2accept  = pTRGS->get_l2accept(nrow);
gcTRGS->L3accept  = pTRGS->get_l3accept(nrow);
//gcTRGS->Notused71  = pTRGS->get_notused71(nrow);
//gcTRGS->Notused72  = pTRGS->get_notused72(nrow);
//gcTRGS->Notused73  = pTRGS->get_notused73(nrow);
//gcTRGS->Notused74  = pTRGS->get_notused74(nrow);
//gcTRGS->Notused75  = pTRGS->get_notused75(nrow);
//gcTRGS->Notused76  = pTRGS->get_notused76(nrow);
//gcTRGS->Notused77  = pTRGS->get_notused77(nrow);
//gcTRGS->Notused78  = pTRGS->get_notused78(nrow);
//gcTRGS->Notused79  = pTRGS->get_notused79(nrow);
//gcTRGS->Notused80  = pTRGS->get_notused80(nrow);

}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_TRGS_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

