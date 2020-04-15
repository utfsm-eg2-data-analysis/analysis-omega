// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TMCTKClass.cc,v 1.2 2005/06/03 12:56:30 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>
//____________________ 
// 
// TMCTKClass
//
// This class contains the MCTK banks, which is needed to write proper GSIM events.
//
// THIS NEEDS MORE DOCUMENTATION.
//

#include "TMCTKClass.h"

ClassImp(TMCTKClass)

TMCTKClass::TMCTKClass(TMCTKClass *Tmp){
  Cx      = Tmp->Cx;
  Cy      = Tmp->Cy;
  Cz      = Tmp->Cz;
  Pmom    = Tmp->Pmom;
  Mass    = Tmp->Mass;
  Charge  = Tmp->Charge;
  Id      = Tmp->Id;
  Flag    = Tmp->Flag;
  Beg_vtx = Tmp->Beg_vtx;
  End_vtx = Tmp->End_vtx;
  Parent  = Tmp->Parent;
}

TMCTKClass::TMCTKClass(void *Tmp,Int_t i){
//
// Fill a bank from a BOS pointer:
// Useage to get first bank:
//  TMCTKClass *mctk=new TMCTKClass(gsim->getBank("MCTK",0),0);  
//
// Note that the getBank() is void *, and we DON'T want to cast,
// since the CINT can not handle classes like clasMCTK_t
//
  clasMCTK_t *mctk=(clasMCTK_t *) Tmp;
  Cx      = mctk->mctk[i].cx;
  Cy      = mctk->mctk[i].cy;
  Cz      = mctk->mctk[i].cz;
  Pmom    = mctk->mctk[i].pmom;
  Mass    = mctk->mctk[i].mass;
  Charge  = mctk->mctk[i].charge;
  Id      = mctk->mctk[i].id;
  Flag    = mctk->mctk[i].flag;
  Beg_vtx = mctk->mctk[i].beg_vtx;
  End_vtx = mctk->mctk[i].end_vtx;
  Parent  = mctk->mctk[i].parent;
}


void TMCTKClass::Print(void){
  cout << " Cx       " <<  Cx << endl;
  cout << " Cy       " <<  Cy << endl;
  cout << " Cz       " <<  Cz << endl;
  cout << " Pmom     " <<  Pmom << endl;
  cout << " Mass     " <<  Mass << endl;
  cout << " Charge   " <<  Charge << endl;
  cout << " Id       " <<  Id << endl;
  cout << " Flag     " <<  Flag << endl;
  cout << " Beg_vtx  " <<  Beg_vtx << endl;
  cout << " End_vtx  " <<  End_vtx << endl;
  cout << " Parent   " <<  Parent << endl;
}
