#ifndef PDG_HXX
#define PDG_HXX

#ifndef INVLD
#define INVLD -9999
#endif

#include "Constants.hxx"

Int_t GetParticleID(TString particleName) {
  if (particleName == "gamma")
    return 22;
  else if (particleName == "positron")
    return -11;
  else if (particleName == "electron")
    return 11;
  else if (particleName == "neutrino")
    return 12;
  else if (particleName == "muon+")
    return -13;
  else if (particleName == "muon")
    return 13;
  else if (particleName == "pi0")
    return 111;
  else if (particleName == "pi+")
    return 211;
  else if (particleName == "pi-")
    return -211;
  else if (particleName == "K0L")
    return 130;
  else if (particleName == "K+")
    return 321;
  else if (particleName == "K-")
    return -321;
  else if (particleName == "neutron")
    return 2112;
  else if (particleName == "proton")
    return 2212;
  else if (particleName == "K0S")
    return 310;
  else if (particleName == "eta")
    return 221;
  else if (particleName == "omega")
    return 223;
  else if (particleName == "K0")
    return 311;
  else
    return 0;
}

Double_t GetParticleMass(Int_t fPid) {
  // only receives PDG
  if (fPid == INVLD)
    return INVLD;
  else if (fPid == 22)
    return kMassGamma;
  else if (fPid == -11)
    return kMassPositron;
  else if (fPid == 11)
    return kMassElectron;
  else if (fPid == 12)
    return kMassNeutrino;
  else if (fPid == -13)
    return kMassMuonPlus;
  else if (fPid == 13)
    return kMassMuonMinus;
  else if (fPid == 111)
    return kMassPiZero;
  else if (fPid == 211)
    return kMassPiPlus;
  else if (fPid == -211)
    return kMassPiMinus;
  else if (fPid == 130)
    return kMassKaonZeroLong;
  else if (fPid == 321)
    return kMassKaonPlus;
  else if (fPid == -321)
    return kMassKaonMinus;
  else if (fPid == 2112)
    return kMassNeutron;
  else if (fPid == 2212)
    return kMassProton;
  else if (fPid == 310)
    return kMassKaonZeroShort;
  else if (fPid == 221)
    return kMassEta;
  else if (fPid == 223)
    return kMassOmega;
  else if (fPid == 311)
    return kMassKaonZero;
  else
    return INVLD; // closure
}

#endif
