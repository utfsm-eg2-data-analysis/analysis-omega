//////////////////////////////////////////////////////////////
//
//   File Fill_ECPB_Bank.cc
//
//   This procedure Fills TECPBClass class from BOS Bank 
//
//  Author :  Gagik Gavalian   UNH  11/10/1999
//
//
//  This file was automaticaly Generated on : 
//	Tue Nov 23 18:21:47 EST 1999 
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TECPBClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_ECPB_Bank(TECPBClass *gcECPB,ECPB *pECPB , int nrow);


void  Fill_ECPB_Bank(TECPBClass *gcECPB, ECPB *pECPB , int nrow){
gcECPB->Scht  = pECPB->get_ScHt(nrow);
gcECPB->Etot  = pECPB->get_Etot(nrow);
gcECPB->Ein  = pECPB->get_Ein(nrow);
gcECPB->Eout  = pECPB->get_Eout(nrow);
gcECPB->Time  = pECPB->get_Time(nrow);
gcECPB->Path  = pECPB->get_Path(nrow);
gcECPB->X  = pECPB->get_X(nrow);
gcECPB->Y  = pECPB->get_Y(nrow);
gcECPB->Z  = pECPB->get_Z(nrow);
gcECPB->M2_hit  = pECPB->get_M2_hit(nrow);
gcECPB->M3_hit  = pECPB->get_M3_hit(nrow);
gcECPB->M4_hit  = pECPB->get_M4_hit(nrow);
gcECPB->Innstr  = pECPB->get_InnStr(nrow);
gcECPB->Outstr  = pECPB->get_OutStr(nrow);
gcECPB->Chi2ec  = pECPB->get_Chi2EC(nrow);
gcECPB->Status  = pECPB->get_Status(nrow);

}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_ECPB_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

