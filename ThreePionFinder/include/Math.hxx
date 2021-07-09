#ifndef MATH_HXX
#define MATH_HXX

#ifndef TREESTRUCTS_H
#include "TreeStructs.h"
#endif

#ifndef PDG_HXX
#include "PDG.hxx"
#endif

TLorentzVector *GetCorrPhotonEnergy(rec_i& t) {  
  // for gammas, based on TM's Analysis Note
  Double_t corrFactor;
  if (gDataKind == "data") {
    if (gTargetOption == "C" || gTargetOption == "Pb") {
      corrFactor = 1.129 - 0.05793/t.Eh - 1.0773e-12/(t.Eh*t.Eh);
    } else if (gTargetOption == "Fe") {
      corrFactor = 1.116 - 0.09213/t.Eh + 0.01007/(t.Eh*t.Eh);
    }
  } else if (gDataKind == "sim") {
    corrFactor = 1.000 + 0.005/t.Eh - 0.0052/(t.Eh*t.Eh);
  }
  Double_t fGammaE  = t.Eh/corrFactor;
  Double_t fGammaPx = t.Px/corrFactor;
  Double_t fGammaPy = t.Py/corrFactor;
  Double_t fGammaPz = t.Pz/corrFactor;
  TLorentzVector *fGammaP = new TLorentzVector(fGammaPx, fGammaPy, fGammaPz, fGammaE);
  return fGammaP;
}

Float_t PhiPQ(Float_t fPex, Float_t fPey, Float_t fPez, Float_t fPx, Float_t fPy, Float_t fPz) {
  Float_t fPhiPQ;
  // two 3-momentum vectors are defined
  // one for the hadron
  // one for the virtual photon
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 virt(-fPex, -fPey, kEbeam - fPez);
  // the function Phi() and Theta() converts the vector into spherical coordinates
  // and the function RotateZ(amount) rotates the vector around z-axis a certain amount
  // now, this paragraph turns y-component of the virtual photon vector into 0 and rotates the hadron vector the same amount
  // to have the hadron vector in function of the virtual photon direction
  // if its not clear, try to draw these two vectors in the xy plane
  Float_t Phi_z = TMath::Pi() - virt.Phi();
  virt.RotateZ(Phi_z);
  hadr.RotateZ(Phi_z);
  // the function Angle() returns the angle between two vectors
  // now, take into account that the virtual photon vector is in the y=0 plane
  // again, this paragraph turns the x-component of the virtual photon vector into 0 and rotates the hadron vector the same amount
  // to have the hadron vector in function of the virtual photon direction
  // if its not clear, try to draw these two vectors in the xz plane
  TVector3 unit(0., 0., 1.);
  Float_t Phi_y = virt.Angle(unit);
  virt.RotateY(Phi_y);
  hadr.RotateY(Phi_y);  
  // finally, it obtains the phi component (in spherical coordinates) of the hadron vector (now in the virtual photon frame of reference)
  fPhiPQ = hadr.Phi()*TMath::RadToDeg();
  
  return fPhiPQ;
}

Float_t ThetaPQ(Float_t fPex, Float_t fPey, Float_t fPez, Float_t fPx, Float_t fPy, Float_t fPz) {
  // angle between virtual photon and particle
  // (and this makes perfect sense if one draws it)
  Float_t fThetaPQ;
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 virt(-fPex, -fPey, kEbeam - fPez);
  fThetaPQ = virt.Angle(hadr)*TMath::RadToDeg();

  return fThetaPQ;
}

Float_t PhiLab(Float_t fPx, Float_t fPy, Float_t fPz) {
  // Returns the azimuthal angle in Lab frame for the particle
  TVector3 v3p(fPx, fPy, fPz);
  Double_t fPhiLab = v3p.Phi()*TMath::RadToDeg();
  if (fPhiLab < -30.) {
      return fPhiLab + 360.;
  } else if (fPhiLab > 330.) {
    return fPhiLab - 360.;
  } // closure
  return fPhiLab; // default
}

Float_t ThetaLab(Float_t fPx, Float_t fPy, Float_t fPz) {
  // Returns the polar angle in Lab frame for the particle
  TVector3 v3p(fPx, fPy, fPz);
  return v3p.Theta()*TMath::RadToDeg();
}

Float_t DeltaTheta(Float_t fPex, Float_t fPey, Float_t fPez, Float_t fPx, Float_t fPy, Float_t fPz) {
  // angle between electron and particle
  
  Float_t deltaTheta;
  TVector3 elec(fPex, fPey, fPez);
  TVector3 part(fPx, fPy, fPz);
  deltaTheta = elec.Angle(part)*TMath::RadToDeg();

  return deltaTheta;
}

Float_t BettaCalc(Float_t fP, Float_t fPid) {
  
  Float_t fM = GetParticleMass((Int_t) fPid);
  Float_t fBettaCalc = fP/TMath::Sqrt(fP*fP + fM*fM);

  return fBettaCalc;
}

#endif
