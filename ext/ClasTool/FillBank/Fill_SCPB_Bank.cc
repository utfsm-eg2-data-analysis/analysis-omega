//////////////////////////////////////////////////////////////
//
//   File Fill_SCPB_Bank.cc
//
//   This procedure Fills TSCPBClass class from BOS Bank 
//
//  Author :  Gagik Gavalian   UNH  11/10/1999
//
//
//  This file was automaticaly Generated on : 
//	Tue Nov 23 18:21:50 EST 1999 
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TSCPBClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_SCPB_Bank(TSCPBClass *gcSCPB,SCPB *pSCPB , int nrow);


void  Fill_SCPB_Bank(TSCPBClass *gcSCPB, SCPB *pSCPB , int nrow){
gcSCPB->Scpdht  = pSCPB->get_ScPdHt(nrow);
gcSCPB->Edep  = pSCPB->get_Edep(nrow);
gcSCPB->Time  = pSCPB->get_Time(nrow);
gcSCPB->Path  = pSCPB->get_Path(nrow);
gcSCPB->Chi2sc  = pSCPB->get_Chi2SC(nrow);
gcSCPB->Status  = pSCPB->get_Status(nrow);

}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_SCPB_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

