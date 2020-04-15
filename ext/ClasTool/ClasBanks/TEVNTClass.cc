// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TEVNTClass.cc,v 1.5 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TEVNTClass</h1>
<pre>
 Modified:
           Maurik (2/3/00) Comments.
           Maurik (Nov/01) Derive from TVirtualData
</pre>
This class is used to access the EVNT 
bank data written into the ROOT DST by WriteRootDST
It was generated automatically from the ddl file in 
packages/bankdefs/evnt.ddl
and later hand edited to provide comments and additional modifications.
The details on how exactly each variable is defined have to be extraced
from the RECSIS code. <p>
The class has been updated to derive from TVirtualData, so that it can 
be used interchangably with TGSIMClass.
<pre>
______________________________________________________________________*/ 
//End_Html
////////////////////////////////////////////////////////

#include "TEVNTClass.h"

ClassImp(TEVNTClass)

TEVNTClass::TEVNTClass(TEVNTClass *TmpEVNT){
  Id   =   TmpEVNT->Id;
  //Pmom   =   TmpEVNT->Pmom;
  //Mass   =   TmpEVNT->Mass;
  Charge   =   TmpEVNT->Charge;
  Betta   =   TmpEVNT->Betta;
  Px   =   TmpEVNT->Px;
  Py   =   TmpEVNT->Py;
  Pz   =   TmpEVNT->Pz;
  X   =   TmpEVNT->X;
  Y   =   TmpEVNT->Y;
  Z   =   TmpEVNT->Z;
  Dcstat   =   TmpEVNT->Dcstat;
  Ccstat   =   TmpEVNT->Ccstat;
  Scstat   =   TmpEVNT->Scstat;
  Ecstat   =   TmpEVNT->Ecstat;
  Lcstat   =   TmpEVNT->Lcstat;
  Ststat   =   TmpEVNT->Ststat;
  Status   =   TmpEVNT->Status;
}

void   TEVNTClass::Print(){
  cout << "TEVNTClass::TVirtualData::" << endl;
  cout << "ID      " << GetId()  << endl;
  //cout << "Pmom    " <<  Pmom  << endl;
  //cout << "Mass    " <<  Mass  << endl;
  cout << "Charge  " << GetCharge()  << endl;
  cout << "Betta   " << GetBeta()  << endl;
  cout << "Px      " << GetPx()  << endl;
  cout << "Py      " << GetPy()  << endl;
  cout << "Pz      " << GetPz()  << endl;
  cout << "X       " << GetX()  << endl;
  cout << "Y       " << GetY()  << endl;
  cout << "Z       " << GetZ()  << endl;
  cout << "DCstat  " << (Int_t)GetDCStat()  << endl;
  cout << "CCstat  " << (Int_t)GetCCStat()  << endl;
  cout << "SCstat  " << (Int_t)GetSCStat()  << endl;
  cout << "ECstat  " << (Int_t)GetECStat()  << endl;
  cout << "LCstat  " << (Int_t)GetLCStat()  << endl;
  cout << "STstat  " << (Int_t)GetSTStat()  << endl;
  cout << "Status  " << (Int_t)GetStat()  << endl;
  cout << "IsEVNT  " << (Int_t)IsEVNT() << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TEVNTClass.cc
////////////////////////////////////////////////////////////////
