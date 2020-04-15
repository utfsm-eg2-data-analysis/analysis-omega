//////////////////////////////////////////////////////////////
//
//   File Fill_LCPB_Bank.cc
//
//   This procedure Fills TLCPBClass class from BOS Bank 
//
//  Author :  Gagik Gavalian   UNH  11/10/1999
//
//
//  This file was automaticaly Generated on : 
//	Tue Nov 23 18:21:58 EST 1999 
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TLCPBClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_LCPB_Bank(TLCPBClass *gcLCPB,LCPB *pLCPB , int nrow);


void  Fill_LCPB_Bank(TLCPBClass *gcLCPB, LCPB *pLCPB , int nrow){
gcLCPB->Scht  = pLCPB->get_ScHt(nrow);
gcLCPB->Etot  = pLCPB->get_Etot(nrow);
gcLCPB->Time  = pLCPB->get_Time(nrow);
gcLCPB->Path  = pLCPB->get_Path(nrow);
gcLCPB->X  = pLCPB->get_X(nrow);
gcLCPB->Y  = pLCPB->get_Y(nrow);
gcLCPB->Z  = pLCPB->get_Z(nrow);
gcLCPB->Chi2lc  = pLCPB->get_Chi2LC(nrow);
gcLCPB->Status  = pLCPB->get_Status(nrow);
gcLCPB->Ein  = pLCPB->get_Ein(nrow);

}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_LCPB_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

