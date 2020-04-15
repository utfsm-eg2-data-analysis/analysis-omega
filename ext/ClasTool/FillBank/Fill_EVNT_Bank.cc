//////////////////////////////////////////////////////////////
//
//   File Fill_EVNT_Bank.cc
//
//   This procedure Fills TEVNTClass class from BOS Bank 
//
//  Author :  Gagik Gavalian   UNH  11/10/1999
//
//
//  This file was automaticaly Generated on : 
//	Tue Nov 23 18:21:36 EST 1999 
//////////////////////////////////////////////////////////////

#include "TROOT.h"
#include "TEVNTClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_EVNT_Bank(TEVNTClass *gcEVNT,EVNT *pEVNT , int nrow);


void  Fill_EVNT_Bank(TEVNTClass *gcEVNT, EVNT *pEVNT , int nrow){
gcEVNT->Id  = pEVNT->get_ID(nrow);
//gcEVNT->Pmom  = pEVNT->get_Pmom(nrow);
//gcEVNT->Mass  = pEVNT->get_Mass(nrow);
gcEVNT->Charge  = (Char_t) pEVNT->get_Charge(nrow);
gcEVNT->Betta  = pEVNT->get_Betta(nrow);
gcEVNT->Px  = pEVNT->get_Cx(nrow)*pEVNT->get_Pmom(nrow);
gcEVNT->Py  = pEVNT->get_cy(nrow)*pEVNT->get_Pmom(nrow);
gcEVNT->Pz  = pEVNT->get_cz(nrow)*pEVNT->get_Pmom(nrow);
gcEVNT->X  = pEVNT->get_X(nrow);
gcEVNT->Y  = pEVNT->get_Y(nrow);
gcEVNT->Z  = pEVNT->get_Z(nrow);
gcEVNT->Dcstat  = (Char_t) pEVNT->get_DCstat(nrow);
gcEVNT->Ccstat  = (Char_t) pEVNT->get_CCstat(nrow);
gcEVNT->Scstat  = (Char_t) pEVNT->get_SCstat(nrow);
gcEVNT->Ecstat  = (Char_t) pEVNT->get_ECstat(nrow);
gcEVNT->Lcstat  = (Char_t) pEVNT->get_LCstat(nrow);
gcEVNT->Ststat  = (Char_t) pEVNT->get_STstat(nrow);
gcEVNT->Status  = (Char_t) pEVNT->get_Status(nrow);

}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_EVNT_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

