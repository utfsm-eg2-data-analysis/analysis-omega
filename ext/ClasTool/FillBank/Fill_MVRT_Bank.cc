//////////////////////////////////////////////////////////////
//
//   File Fill_MVRT_Bank.cc
//
//   This procedure Fills TMVRTClass class from BOS Bank 
//
//  Author :  Maurik Holtrop UNH 9/2004
//
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TMVRTClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_MVRT_Bank(TMVRTClass *gcMVRT,MVRT *pMVRT , int nrow);


void  Fill_MVRT_Bank(TMVRTClass *gcMVRT, MVRT *pMVRT , int nrow){
  gcMVRT->v_id   = pMVRT->get_v_id(nrow);
  gcMVRT->ntrk   = pMVRT->get_ntrk(nrow);
  gcMVRT->x      = pMVRT->get_x(nrow);
  gcMVRT->y      = pMVRT->get_y(nrow);
  gcMVRT->z      = pMVRT->get_z(nrow);
  gcMVRT->chi2   = pMVRT->get_chi2(nrow);
  gcMVRT->cxx    = pMVRT->get_cxx(nrow);
  gcMVRT->cxy    = pMVRT->get_cxy(nrow);
  gcMVRT->cxz    = pMVRT->get_cxz(nrow);
  gcMVRT->cyy    = pMVRT->get_cyy(nrow);
  gcMVRT->cyz    = pMVRT->get_cyz(nrow);
  gcMVRT->czz    = pMVRT->get_czz(nrow);
  gcMVRT->stat   = pMVRT->get_stat(nrow);   

}

////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_MVRT_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

