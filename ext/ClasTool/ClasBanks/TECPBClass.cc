// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TECPBClass.cc,v 1.6 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TECPBClass</h1>
<pre>
 Modified:
           Maurik (2/3/00) Comments.
</pre>
This class is used to access the 
ECPB
bank data written into the ROOT DST by WriteRootDST
It was generated automatically from the ddl file in 
packages/bankdefs/ecpb.ddl
and later hand edited to provide comments and additional modifications.
The details on how exactly each variable is defined have to be extraced
from the RECSIS code.
<pre> 
<p>Modified:
             Will Morrison 11/05
</p><p> Added a GetUVW function that calculates the U, V, and W coordinates
in the EC.
</p>
<!-- */ 
// --> End_Html   


////////////////////////////////////////////////////////


#include "TECPBClass.h"

ClassImp(TECPBClass)

TECPBClass::TECPBClass(TECPBClass *TmpECPB){
Scht   =   TmpECPB->Scht;
Etot   =   TmpECPB->Etot;
Ein   =   TmpECPB->Ein;
Eout   =   TmpECPB->Eout;
Time   =   TmpECPB->Time;
Path   =   TmpECPB->Path;
X   =   TmpECPB->X;
Y   =   TmpECPB->Y;
Z   =   TmpECPB->Z;
M2_hit   =   TmpECPB->M2_hit;
M3_hit   =   TmpECPB->M3_hit;
M4_hit   =   TmpECPB->M4_hit;
Innstr   =   TmpECPB->Innstr;
Outstr   =   TmpECPB->Outstr;
Chi2ec   =   TmpECPB->Chi2ec;
Status   =   TmpECPB->Status;
}

void TECPBClass::GetUVW(Float_t* u, Float_t* v, Float_t* w)
{
  // returns UVW coordinates in the EC for this hit.
  // 
  TVector3 DetCo = TVector3(X,Y,Z);
  GetUVW(u,v,w,DetCo);
}

void TECPBClass::GetUVW(Float_t* u, Float_t* v, Float_t* w,TVector3 DetCo)
{
  // returns UVW coordinates in the EC given a vector.
  // (code by Will Morrison, UNH)

  const Float_t Pi = TMath::Pi(); // 3.14159265;
    
  //Define the detector phi, take it between -30 and 330
  Float_t phi = atan2(DetCo.Y(),DetCo.X())*180./Pi;
  if (phi<0.) phi+=360.; phi=phi+30.; if(phi>360.) phi-=360.;
  
  //Get which sector point is in using phi and convert to radians
  Float_t ec_phi = (Pi/3)*int(phi/60.);
  
  //Rotate around Z in such a way that all hits are in sector coordinates
  DetCo.RotateZ(-ec_phi);
  TVector3 SectCo = TVector3(DetCo);
  
  //Switch X and Y
  Float_t xx = SectCo.X();
  SectCo.SetX(SectCo.Y());
  SectCo.SetY(xx);
  
  //Rotate around X by the EC plane's tilt from normal
  Float_t ec_the = Pi*25.0/180; // 0.4363323; // 25 degrees
  SectCo.RotateX(ec_the);
  
  //Translate Z so that Z is around zero
  SectCo.SetZ(SectCo.Z()-510.32);
  
  //
  //Change to U-V-W coordinates
  
  Float_t ylow = -182.974; 
  Float_t yhi = 189.956;
  
  Float_t rho = 1.097620706; // 62.89 degrees
  Float_t tanrho = tan(rho);
  Float_t sinrho = sin(rho); 
  Float_t cosrho = cos(rho);
  
  *u = (SectCo.Y()-ylow)/sinrho;
  *v = (yhi-ylow)/tanrho - SectCo.X() + (yhi-SectCo.Y())/tanrho;
  *w = ( (yhi-ylow)/tanrho + SectCo.X() + (yhi-SectCo.Y())/tanrho )/(2*cosrho);
}

//////////////////////////////////////////////////////////////////////
void   TECPBClass::Print(){
cout << "ScHt    " <<  Scht  << endl;
cout << "Etot    " <<  Etot  << endl;
cout << "Ein     " <<  Ein  << endl;
cout << "Eout    " <<  Eout  << endl;
cout << "Time    " <<  Time  << endl;
cout << "Path    " <<  Path  << endl;
cout << "X       " <<  X  << endl;
cout << "Y       " <<  Y  << endl;
cout << "Z       " <<  Z  << endl;
cout << "M2_hit  " <<  M2_hit  << endl;
cout << "M3_hit  " <<  M3_hit  << endl;
cout << "M4_hit  " <<  M4_hit  << endl;
cout << "InnStr  " <<  Innstr  << endl;
cout << "OutStr  " <<  Outstr  << endl;
cout << "Chi2EC  " <<  Chi2ec  << endl;
cout << "Status  " <<  Status  << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TECPBClass.cc
////////////////////////////////////////////////////////////////
