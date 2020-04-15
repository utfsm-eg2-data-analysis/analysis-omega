//////////////////////////////////////////////////////////////
//
//   File Fill_GSIM_Bank.cc
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
#include "TGSIMClass.h"

#include "clasbanks.h"


// Function Prototypes (overloaded)
void  Fill_GSIM_Bank(TGSIMClass *gcGSIM,PART *pPART , int nrow);
void  Fill_GSIM_Bank(TGSIMClass *gcGSIM,MCTK *pMCTK, MCVX *pMCVX , int nrow);

void  Fill_GSIM_Bank(TGSIMClass *gcGSIM,MCTK *pMCTK, MCVX *pMCVX , int nrow){

  Int_t vertex_num = pMCTK->get_beg_vtx(nrow);
  if( pMCTK->get_end_vtx(nrow) == 0){
    gcGSIM->Status  = 1; 
  }else{                    // This was not a final track, it decayed...
    gcGSIM->Status  = 0;
  }

  gcGSIM->Id  =pMCTK->get_id(nrow);
  //  cerr << "ID: " <<  pMCTK->get_id(nrow) << endl;
  gcGSIM->Charge  = (Char_t)pMCTK->get_charge(nrow);

  if(  pMCTK->get_pmom(nrow) > 0.0 ) {
    gcGSIM->Betta  =  pMCTK->get_pmom(nrow) / 
      sqrt( pow( pMCTK->get_pmom(nrow), 2 ) + pow( pMCTK->get_mass(nrow) , 2) ) ;
  } else {
    gcGSIM->Betta  = 0;
  }
    
  gcGSIM->Px  = pMCTK->get_cx(nrow) * pMCTK->get_pmom(nrow);
  gcGSIM->Py  = pMCTK->get_cy(nrow) * pMCTK->get_pmom(nrow);
  gcGSIM->Pz  = pMCTK->get_cz(nrow) * pMCTK->get_pmom(nrow);
  if(vertex_num<1 || vertex_num > pMCVX->get_nrows()){ // OOPS, not a good vertex.    
    gcGSIM->Status  = 0;    
    gcGSIM->X  = 0;
    gcGSIM->Y  = 0;
    gcGSIM->Z  = 0;
  }else{
    gcGSIM->X  = pMCVX->get_x(vertex_num-1);
    gcGSIM->Y  = pMCVX->get_y(vertex_num-1);
    gcGSIM->Z  = pMCVX->get_z(vertex_num-1);
  }
  gcGSIM->Dcstat  = 0;
  gcGSIM->Ccstat  = 0;
  gcGSIM->Scstat  = 0;
  gcGSIM->Ecstat  = 0;
  gcGSIM->Lcstat  = 0;
  gcGSIM->Ststat  = 0;
}

void  Fill_GSIM_Bank(TGSIMClass *gcGSIM, PART *pPART , int nrow){

  gcGSIM->Id  = TDatabasePDG::Instance()->ConvertGeant3ToPdg( pPART->get_pid(nrow) );
  //  cerr << "ID: " << gcGSIM->Id  << endl;
  //gcGSIM->Pmom  = pPART->get_Pmom(nrow);
  //gcGSIM->Mass  = pPART->get_Mass(nrow);
  gcGSIM->Charge  = (Char_t) pPART->get_q(nrow);
  //  gcGSIM->Betta  =  0;// pPART->get_Betta(nrow);
  if( pPART->get_E(nrow) > 0 ) {
    gcGSIM->Betta  =  sqrt( pow(  pPART->get_px(nrow), 2 ) + 
			    pow(  pPART->get_py(nrow), 2 ) + 
			    pow(  pPART->get_pz(nrow), 2 ) ) / 
      pPART->get_E(nrow);
  } else {
    gcGSIM->Betta = 0;
  }
  gcGSIM->Px  = pPART->get_px(nrow);
  gcGSIM->Py  = pPART->get_py(nrow);
  gcGSIM->Pz  = pPART->get_pz(nrow);
  gcGSIM->X  = pPART->get_x(nrow);
  gcGSIM->Y  = pPART->get_y(nrow);
  gcGSIM->Z  = pPART->get_z(nrow);
  gcGSIM->Dcstat  = 0;
  gcGSIM->Ccstat  = 0;//(UChar_t) pPART->get_CCstat(nrow);
  gcGSIM->Scstat  = 0;//(UChar_t) pPART->get_SCstat(nrow);
  gcGSIM->Ecstat  = 0;//(UChar_t) pPART->get_ECstat(nrow);
  gcGSIM->Lcstat  = 0;//(UChar_t) pPART->get_LCstat(nrow);
  gcGSIM->Ststat  = 0;// gcGSIM->Ststat  = (UChar_t) pPART->get_STstat(nrow);
  gcGSIM->Status  = 1;// (UChar_t) pPART->get_Status(nrow);  
}


////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_GSIM_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

