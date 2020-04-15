//////////////////////////////////////////////////////////////
//
//   File Fill_CCPB_Bank.cc
//
//   This procedure Fills TCCPBClass class from BOS Bank 
//
//  Author :  Gagik Gavalian   UNH  11/10/1999
//
//
//  This file was automaticaly Generated on : 
//	Tue Nov 23 18:21:56 EST 1999 
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TCCPBClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_CCPB_Bank(TCCPBClass *gcCCPB,CCPB *pCCPB , int nrow);


void  Fill_CCPB_Bank(TCCPBClass *gcCCPB, CCPB *pCCPB , int nrow){
gcCCPB->Scsght  = pCCPB->get_ScSgHt(nrow);
gcCCPB->Nphe  = pCCPB->get_Nphe(nrow);
gcCCPB->Time  = pCCPB->get_Time(nrow);
gcCCPB->Path  = pCCPB->get_Path(nrow);
gcCCPB->Chi2cc  = pCCPB->get_Chi2CC(nrow);
gcCCPB->Status  = pCCPB->get_Status(nrow);

}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_CCPB_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

