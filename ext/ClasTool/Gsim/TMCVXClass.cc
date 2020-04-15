// @(#)ClasTool/TClasTool:$Name:  $:$Id: TMCVXClass.cc,v 1.2 2005/06/03 12:56:30 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>
//____________________ 
//
// TMCVXClass
//
// This class contains the vertex information for a GSIM event.
//
// THIS NEEDS MORE DOCUMENTATION.
//

#include "TMCVXClass.h"

ClassImp(TMCVXClass)

TMCVXClass::TMCVXClass(TMCVXClass *Tmp){
  x= Tmp->x;
  y = Tmp->y;
  z = Tmp->z;
  tof = Tmp->tof;
  flag= Tmp->flag;
}

TMCVXClass::TMCVXClass(void *Tmp,Int_t i){
//
// Fill a bank from a BOS pointer:
// Useage to get first bank:
//  TMCVXClass *mctk=new TMCVXClass(gsim->getBank("MCVX",0),0);  
//
// Note that the getBank() is void *, and we DON'T want to cast,
// since the CINT can not handle classes like clasMCVX_t
//
  clasMCVX_t *mcvx=(clasMCVX_t *)Tmp;
  x= mcvx->mcvx[i].x;
  y = mcvx->mcvx[i].y;
  z = mcvx->mcvx[i].z;
  tof = mcvx->mcvx[i].tof;
  flag= mcvx->mcvx[i].flag;
}


void TMCVXClass::Print(void){
  cout << "x    " << x << endl;
  cout << "y    " << y << endl;
  cout << "z    " << z << endl;
  cout << "tof  " << tof << endl;
  cout << "flag " << flag << endl;
}
