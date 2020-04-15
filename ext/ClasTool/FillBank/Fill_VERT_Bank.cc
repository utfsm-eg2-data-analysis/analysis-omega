//////////////////////////////////////////////////////////////
//
//   File Fill_VERT_Bank.cc
//
//   This procedure Fills TVERTClass class from BOS Bank 
//
//  Author :  Maurik Holtrop UNH 9/2004
//
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TVERTClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_VERT_Bank(TVERTClass *gcVERT,VERT *pVERT , int nrow);


void  Fill_VERT_Bank(TVERTClass *gcVERT, VERT *pVERT , int nrow){
  gcVERT->vertex  = pVERT->get_vertex(nrow);
  gcVERT->trk1    = pVERT->get_trk1(nrow);
  gcVERT->trk2    = pVERT->get_trk2(nrow);
  gcVERT->x       = pVERT->get_x(nrow);
  gcVERT->y       = pVERT->get_y(nrow);
  gcVERT->z       = pVERT->get_z(nrow);
  gcVERT->sepd    = pVERT->get_sepd(nrow);
}

////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_VERT_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

