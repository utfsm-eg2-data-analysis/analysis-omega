//////////////////////////////////////////////////////////////
//
//   File Fill_HLS_Bank.cc
//
//   This procedure Fills THLSClass class from BOS Bank 
//
//  Author :  Gagik Gavalian   UNH  11/10/1999
//
//
//  This file was automaticaly Generated on : 
//	Tue Nov 23 18:22:06 EST 1999 
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "THLSClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_HLS_Bank(THLSClass *gcHLS,HLS *pHLS , int nrow);


void  Fill_HLS_Bank(THLSClass *gcHLS, HLS *pHLS , int nrow){
gcHLS->TenMhz = pHLS->get_S1(nrow);
gcHLS->OTR1 = pHLS->get_S1(nrow);
gcHLS->OTR2 = pHLS->get_S1(nrow);
gcHLS->SLM = pHLS->get_S1(nrow);
gcHLS->LVL1R = pHLS->get_S1(nrow);
gcHLS->LRC = pHLS->get_S1(nrow);
gcHLS->LRA = pHLS->get_S1(nrow);
gcHLS->Fci = pHLS->get_S1(nrow);
gcHLS->Pmt1 = pHLS->get_S1(nrow);
gcHLS->Pmt2 = pHLS->get_S1(nrow);
gcHLS->Pmt3 = pHLS->get_S1(nrow);
gcHLS->Pmt4 = pHLS->get_S1(nrow);
gcHLS->Res1 = pHLS->get_S1(nrow);
gcHLS->Res2 = pHLS->get_S1(nrow);
gcHLS->HelAcc = pHLS->get_S1(nrow);
gcHLS->HLSAcc = pHLS->get_S1(nrow);
}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_HLS_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

