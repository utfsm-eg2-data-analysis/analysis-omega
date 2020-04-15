//////////////////////////////////////////////////////////////
//
//   File Fill_TGPB_Bank.cc
//
//   This procedure Fills TTGPBClass class from BOS Bank 
//
//  Author :  Gagik Gavalian   UNH  11/10/1999
//
//
//  This file was automaticaly Generated on : 
//	Tue Nov 23 18:21:58 EST 1999 
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TTGPBClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_TGPB_Bank(TTGPBClass *gcTGPB,TGPB *pTGPB , int nrow);


void  Fill_TGPB_Bank(TTGPBClass *gcTGPB, TGPB *pTGPB , int nrow){
gcTGPB->pointer = pTGPB->get_pointer(nrow);
gcTGPB->Time    = pTGPB->get_Time(nrow);
gcTGPB->Energy  = pTGPB->get_Energy(nrow);
gcTGPB->dt      = pTGPB->get_dt(nrow);
}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_TGPB_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

