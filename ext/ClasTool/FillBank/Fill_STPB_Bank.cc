//////////////////////////////////////////////////////////////
//
//   File Fill_STPB_Bank.cc
//
//   This procedure Fills TSTPBClass class from BOS Bank 
//
//  Author :  Gagik Gavalian   UNH  11/10/1999
//
//
//  This file was automaticaly Generated on : 
//	Tue Nov 23 18:21:58 EST 1999 
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TSTPBClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_STPB_Bank(TSTPBClass *gcSTPB,STPB *pSTPB , int nrow);


void  Fill_STPB_Bank(TSTPBClass *gcSTPB, STPB *pSTPB , int nrow){
gcSTPB->SThid  = pSTPB->get_SThid(nrow);
gcSTPB->Time  = pSTPB->get_Time(nrow);
gcSTPB->Path  = pSTPB->get_Path(nrow);
gcSTPB->Status  = pSTPB->get_Status(nrow);
}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_STPB_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

