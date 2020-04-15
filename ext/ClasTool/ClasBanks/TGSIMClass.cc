// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TGSIMClass.cc,v 1.5 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TGSIMClass</h1>
<pre>
 Modified:
           Maurik (2/3/00) Comments.
           Maurik (Nov/01) Derive from TVirtualData
</pre>
This class is used to access the GSIM
bank data written into the ROOT DST for the E2 run at Jefferson Lab,
when writing DST using WriteRootDST with the GSIM capability turned on 
(default). <p>
The class has been updated to derive from TVirtualData, 
so that it can  be used interchangably with TEVNTClass.
<p>
See the UseGSIM() switch function in the TE2AnaTool class for more
details.
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "TGSIMClass.h"

ClassImp(TGSIMClass)

TGSIMClass::TGSIMClass(TGSIMClass *TmpEVNT){
Id   =   TmpEVNT->Id;
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
Status   =   TmpEVNT->Status;
}

void   TGSIMClass::Print(){
  cout << "TGSIMClass::TVirtualData::" << endl;
  cout << "ID      " <<  Id  << " (= " << GetId() <<" )" << endl;
  cout << "Charge  " << (Int_t)GetCharge()  << endl;
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
  cout << "Status  " << (Int_t)GetStat()  << endl;
  cout << "GSIM ?  " << (Int_t)IsGSIM() << endl;
}



////////////////////////////////////////////////////////////////
//
//  End of File  TGSIMClass.cc
////////////////////////////////////////////////////////////////
