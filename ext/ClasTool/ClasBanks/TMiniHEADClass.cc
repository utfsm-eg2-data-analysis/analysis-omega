// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TMiniHEADClass.cc,v 1.2 2005/06/03 12:56:29 holtrop Exp $
#include "TMiniHEADClass.h"


ClassImp(TMiniHEADClass)

TMiniHEADClass::TMiniHEADClass(){

}

TMiniHEADClass::~TMiniHEADClass(){

}

void TMiniHEADClass::Print(){
  cout << "MiniHEAD : " << "NRUN : " << NRun << "  NEvent : " 
       << NEvent << "  FC : " << FC << " FCG : " << FCG 
       << "  RF1 : " << RF1 << " HEL : " << Helicity << endl; 
}
