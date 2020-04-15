// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TMCHDClass.cc,v 1.2 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TMCHDClass</h1>
This class is used to access the 
MCHD
bank data written into the ROOT DST by WriteRootDST
The details on how exactly each variable is defined have to be extraced
from the RECSIS code.
This class is not optimized for disk usage, it is only designed to be used 
for MC data, but it is mostly for convenience. Some of the information in this 
bank is already contained in HEAD bank and MCTK. 
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "TMCHDClass.h"

ClassImp(TMCHDClass)

TMCHDClass::TMCHDClass( TMCHDClass *TmpMCHD ) {
  Nrun     =   TmpMCHD->Nrun;
  Nevent   =   TmpMCHD->Nevent;
  Time     =   TmpMCHD->Time;
  Type     =   TmpMCHD->Type;
  ReacType =   TmpMCHD->ReacType;
  Weight   =   TmpMCHD->Weight;
  Photon   =   TmpMCHD->Photon;
  Target   =   TmpMCHD->Target;
}

void   TMCHDClass::Print(){
  cout << "NRUN      " <<  Nrun  << endl;
  cout << "NEVENT    " <<  Nevent  << endl;
  cout << "TIME      " <<  Time  << endl;
  cout << "TYPE      " <<  Type  << endl;
  cout << "REACTYPE  " <<  ReacType   << endl;
  cout << "WEIGHT    " <<  Weight  << endl;
  cout << "PHOTON    " <<  Photon.E() << " : " << Photon.X() << " : " << Photon.Y() << " : " << Photon.Z() << endl;
  cout << "PHOTON    " <<  Target.E() << " : " << Target.X() << " : " << Target.Y() << " : " << Target.Z() << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TMCHDClass.cc
////////////////////////////////////////////////////////////////
