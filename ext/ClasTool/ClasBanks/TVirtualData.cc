// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TVirtualData.cc,v 1.6 2007/03/01 22:30:56 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* --> 
<h1>TVirtualData</h1>
<pre>
 Modified: 
           Maurik Holtrop 06-02-2005
	   I added the ST stat pointer back into the code, since EG3 will need
	   the ST information.
	   Hovanes 12-2006:  Changed UChar_t to Char_t for status words.
</pre>
This class is a base class for storing data. The classes
TEVNTClass and TGSIMClass derive from it. Any new datacontainer class
should also derive from this class. This allows
the classes, which contain the same data, to be mixed more easily.<br>
Most methods for dealing with data directly belong in this class.
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "TVirtualData.h"

ClassImp(TVirtualData)

TVirtualData::TVirtualData(TVirtualData *TmpEVNT){
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

void TVirtualData::Print(){
  cout << "TVirtualData::" << endl;
  cout << "ID      " <<  Id  << endl;
  //cout << "Pmom    " <<  Pmom  << endl;
  //cout << "Mass    " <<  Mass  << endl;
  cout << "Charge  " <<(Int_t) Charge  << endl;
  cout << "Betta   " <<  Betta  << endl;
  cout << "Px      " <<  Px  << endl;
  cout << "Py      " <<  Py  << endl;
  cout << "Pz      " <<  Pz  << endl;
  cout << "X       " <<  X  << endl;
  cout << "Y       " <<  Y  << endl;
  cout << "Z       " <<  Z  << endl;
  cout << "DCstat  " <<(Int_t) Dcstat  << endl;
  cout << "CCstat  " <<(Int_t)  Ccstat  << endl;
  cout << "SCstat  " <<(Int_t)  Scstat  << endl;
  cout << "ECstat  " <<(Int_t)  Ecstat  << endl;
  cout << "LCstat  " <<(Int_t)  Lcstat  << endl;
  cout << "STstat  " <<(Int_t)  Ststat  << endl;
  cout << "Status  " <<(Int_t) Status  << endl;
}

Float_t TVirtualData::GetMass(){
  //
  // Get the CALCULATED mass, from p and beta.
  // I.E. mass= P * Sqrt( 1/(beta*beta) - 1)
  //
  // Will return -1. if beta<=0, or beta>1 .
  //
  // You can get the exact mass of a particle with:
  //
  // M=TClasTool::fgParticle_Mass[kPion_Plus_Id];
  // or
  // M=TClasTool::GetPartMassID(evnt->GetId());
  // which uses TClasTool::GetTypeFromPid(pid) to look up
  // the particle.
  //
  // Alternatively, in root version>4 you can also do
  // the following:
  // You can get the PDG value for the particle with Id 
  // the following way:
  // First Load the libEG.so --> .L $ROOTSYS/lib/libEG.so
  // Then call:
  //
  // M=TDatabasePDG::Instance()->GetParticle(evnt->GetId())->Mass();
  //
  // This will give the exact PDG mass (i.e. 1.3957e-01 for a pi-)
  //

  if(Betta>0 && Betta<=1)
    return( GetMomentum()*TMath::Sqrt(1/(Betta*Betta) - 1));
  else
    return( -1.);
}


//
//  End of File  TEVNTClass.cc
////////////////////////////////////////////////////////////////
