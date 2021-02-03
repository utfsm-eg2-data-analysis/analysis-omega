#ifndef MIXINGBKG_MATH_HXX
#define MIXINGBKG_MATH_HXX

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

#ifndef MIXINGBKG_UX_HXX
#include "MixingBkg_UX.hxx"
#endif

TLorentzVector *GetCorrPhotonEnergy_ForMixingBkg(TVector3 *gammaMomentum) {
  /*
     for gammas, based on TM's Analysis Note
     the main difference with GetCorrPhotonEnergy() from FilterNCombine is that
     it receives as an argument a 3-momentum vector!
  */

  Double_t corrFactor;
  Double_t initialEnergy = gammaMomentum->Mag();

  if (gDataKind == "data") {
    if (gTargetOption == "C" || gTargetOption == "Pb") {
      corrFactor = 1.129 - 0.05793 / initialEnergy - 1.0773e-12 / (initialEnergy * initialEnergy);
    } else if (gTargetOption == "Fe") {
      corrFactor = 1.116 - 0.09213 / initialEnergy + 0.01007 / (initialEnergy * initialEnergy);
    }
  } else if (gDataKind == "sim") {
    corrFactor = 1.000 + 0.005 / initialEnergy - 0.0052 / (initialEnergy * initialEnergy);
  }
  Double_t fGammaE = initialEnergy / corrFactor;
  Double_t fGammaPx = fGammaE * gammaMomentum->X() / initialEnergy;  // same as gammaMomentum->X() / corrFactor
  Double_t fGammaPy = fGammaE * gammaMomentum->Y() / initialEnergy;
  Double_t fGammaPz = fGammaE * gammaMomentum->Z() / initialEnergy;
  TLorentzVector *fGammaP = new TLorentzVector(fGammaPx, fGammaPy, fGammaPz, fGammaE);
  return fGammaP;
}

#else
#endif
