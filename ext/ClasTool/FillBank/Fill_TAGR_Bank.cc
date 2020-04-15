//////////////////////////////////////////////////////////////
//
//   File Fill_TAGR_Bank.cc
//
//   This procedure Fills TTAGRClass class from BOS Bank 
//
//  Author :  Maurik Holtrop UNH 9/2004
//
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TTAGRClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_TAGR_Bank(TTAGRClass *gcTAGR,TAGR *pTAGR , int nrow);


void  Fill_TAGR_Bank(TTAGRClass *gcTAGR, TAGR *pTAGR , int nrow){
gcTAGR->ERG     = pTAGR->get_ERG(nrow);
gcTAGR->TTAG    = pTAGR->get_TTAG(nrow);
gcTAGR->TPHO    = pTAGR->get_TPHO(nrow);
gcTAGR->STAT    = pTAGR->get_STAT(nrow);
gcTAGR->T_id    = pTAGR->get_T_id(nrow);
gcTAGR->E_id    = pTAGR->get_E_id(nrow);
}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_TAGR_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

