//////////////////////////////////////////////////////////////
//
//   File Fill_HEAD_Bank.cc
//
//   This procedure Fills THEADClass class from BOS Bank 
//
//  Author :  Gagik Gavalian   UNH  11/10/1999
//
//
//  This file was automaticaly Generated on : 
//	Tue Nov 23 18:21:43 EST 1999 
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "THEADClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_HEAD_Bank(THEADClass *gcHEAD,HEAD *pHEAD , int nrow);


void  Fill_HEAD_Bank(THEADClass *gcHEAD, HEAD *pHEAD , int nrow){
gcHEAD->Version  = pHEAD->get_VERSION(nrow);
gcHEAD->Nrun  = pHEAD->get_NRUN(nrow);
gcHEAD->Nevent  = pHEAD->get_NEVENT(nrow);
gcHEAD->Time  = pHEAD->get_TIME(nrow);
gcHEAD->Type  = pHEAD->get_TYPE(nrow);
gcHEAD->Roc  = pHEAD->get_ROC(nrow);
gcHEAD->Evtclass  = pHEAD->get_EVTCLASS(nrow);
gcHEAD->Trigbits  = pHEAD->get_TRIGBITS(nrow);

}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_HEAD_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

