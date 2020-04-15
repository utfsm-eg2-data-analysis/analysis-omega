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
#include "TICPBClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_ICPB_Bank(TICPBClass *gcICPB,ICPB *pICPB , int nrow);


void  Fill_ICPB_Bank(TICPBClass *gcICPB, ICPB *pICPB , int nrow){
  gcICPB->Etot = pICPB->get_Etot(nrow);
   gcICPB->Ecen = pICPB->get_Ecen(nrow);
   gcICPB->Time = pICPB->get_Time(nrow);
   gcICPB->T_next = pICPB->get_T_next(nrow);
   gcICPB->X = pICPB->get_X(nrow);
   gcICPB->Y = pICPB->get_Y(nrow);
   gcICPB->Z = pICPB->get_Z(nrow);
   gcICPB->M2_hit = pICPB->get_M2_hit(nrow);
   gcICPB->M3_hit = pICPB->get_M3_hit(nrow);
   gcICPB->Status = pICPB->get_Status(nrow);
}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_CCPB_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

