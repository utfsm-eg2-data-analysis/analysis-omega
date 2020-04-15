//////////////////////////////////////////////////////////////
//
//   File Fill_MCHD_Bank.cc
//
//   This procedure Fills TMCHDClass class from BOS Bank 
//
//  Author :  Hovanes Egiyan   UNH  10/07/2006
//
//
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TMCHDClass.h"

#include "clasbanks.h"


// Function Prototype 
//void  Fill_MCHD_Bank(TMCHDClass *gcMCHD,MCHD *pMCHD , int nrow);


void  Fill_MCHD_Bank( TMCHDClass *gcMCHD, MCHD *pMCHD , int nrow ) {
  gcMCHD->Nrun  = pMCHD->get_NRUN(nrow);
  gcMCHD->Nevent  = pMCHD->get_NEVENT(nrow);
  gcMCHD->Time  = pMCHD->get_TIME(nrow);
  gcMCHD->Type  = pMCHD->get_TYPE(nrow);
  gcMCHD->ReacType  = pMCHD->get_REACTYPE(nrow); 
  gcMCHD->Weight  = pMCHD->get_WEIGHT(nrow);

  gcMCHD->Photon.SetPxPyPzE( pMCHD->get_PX_PHOT(nrow), pMCHD->get_PY_PHOT(nrow), 
			      pMCHD->get_PZ_PHOT(nrow), pMCHD->get_E_PHOT(nrow) );
  gcMCHD->Target.SetPxPyPzE( pMCHD->get_PX_TARG(nrow), pMCHD->get_PY_TARG(nrow), 
			      pMCHD->get_PZ_TARG(nrow), pMCHD->get_E_TARG(nrow) );
}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_MCHD_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

