#ifndef TMIXINGBKGROW_HXX
#define TMIXINGBKGROW_HXX

#include "Headers.hxx"

class TMixingBkgRow {
  /*
    Each class of TMixingBkgRow has a maximum of 4 particles,
    the idea is that all of them must come from different events,
    but same kinematic region (defined by the electron variables Q2 and Nu)
  */

 public:
  TMixingBkgRow() {
    // Default constructor
    Reset();
  }

  ~TMixingBkgRow() {
    // Default destructor
  }

  void Fill(Int_t entry, Int_t evnt, Int_t pid, Double_t fPex, Double_t fPey, Double_t fPez, Double_t fPx, Double_t fPy, Double_t fPz) {
    Int_t index;
    if (pid == 22) {
      if (!Gamma1Filled())
        index = 2;
      else if (!Gamma2Filled())
        index = 3;
    } else if (pid == 211) {
      index = 0;
    } else if (pid == -211) {
      index = 1;
    }
    // fill
    rPid[index] = pid;
    rEntry[index] = entry;
    rEvent[index] = evnt;
    lastEvent = evnt;
    // assign direction of last electron
    electronDir->SetXYZ(fPex, fPey, fPez);
    // assign particle direction
    particleDir[index]->SetXYZ(fPx, fPy, fPz);
    // fill the original angles w.r.t. last electron added
    rDeltaTheta[index] = GetDeltaTheta(index);
    rDeltaPhi[index] = GetDeltaPhi(index);
  }

  Int_t GetEvent(Int_t index) { return rEvent[index]; }
  Int_t GetEntry(Int_t index) { return rEntry[index]; }
  Int_t GetPid(Int_t index) { return rPid[index]; }

  Int_t GetLastEvent() { return lastEvent; }

  Bool_t ParticleFilled(Int_t pid) {
    if (pid == 211 && rPid[0] == 211) {
      return true;
    } else if (pid == -211 && rPid[1] == -211) {
      return true;
    } else if (pid == 22) {
      return Gamma1Filled() && Gamma2Filled();
    } else {
      return false;
    }
  }

  Bool_t Gamma1Filled() { return rPid[2] == 22; }
  Bool_t Gamma2Filled() { return rPid[3] == 22; }

  void Print() {
    std::cout << "PID   = (" << rPid[0] << ", " << rPid[1] << ", " << rPid[2] << ", " << rPid[3] << ")" << std::endl;
    std::cout << "Entry = (" << rEntry[0] << ", " << rEntry[1] << ", " << rEntry[2] << ", " << rEntry[3] << ")" << std::endl;
    std::cout << "Event = (" << rEvent[0] << ", " << rEvent[1] << ", " << rEvent[2] << ", " << rEvent[3] << ")" << std::endl;
    std::cout << "Px = (" << particleDir[0]->X() << ", " << particleDir[1]->X() << ", " << particleDir[2]->X() << ", " << particleDir[3]->X() << ")" << std::endl;
    std::cout << "Py = (" << particleDir[0]->Y() << ", " << particleDir[1]->Y() << ", " << particleDir[2]->Y() << ", " << particleDir[3]->Y() << ")" << std::endl;
    std::cout << "Pz = (" << particleDir[0]->Z() << ", " << particleDir[1]->Z() << ", " << particleDir[2]->Z() << ", " << particleDir[3]->Z() << ")" << std::endl;
    std::cout << "orig_DeltaTheta = (" << rDeltaTheta[0] << ", " << rDeltaTheta[1] << ", " << rDeltaTheta[2] << ", " << rDeltaTheta[3] << ")" << std::endl;
    std::cout << "curr_DeltaTheta = (" << particleDir[0]->Theta() - electronDir->Theta() << ", " << particleDir[1]->Theta() - electronDir->Theta() << ", " << particleDir[2]->Theta() - electronDir->Theta() << ", " << particleDir[3]->Theta() - electronDir->Theta() << ")" << std::endl;
    std::cout << "orig_DeltaPhi   = (" << rDeltaPhi[0] << ", " << rDeltaPhi[1] << ", " << rDeltaPhi[2] << ", " << rDeltaPhi[3] << ")" << std::endl;
    std::cout << "curr_DeltaPhi   = (" << particleDir[0]->Phi() - electronDir->Phi() << ", " << particleDir[1]->Phi() - electronDir->Phi() << ", " << particleDir[2]->Phi() - electronDir->Phi() << ", " << particleDir[3]->Phi() - electronDir->Phi() << ")" << std::endl;
    std::cout << "Pe    = (" << electronDir->X() << ", " << electronDir->Y() << ", " << electronDir->Z() << ")" << std::endl;
  }

  Bool_t IsFull() { return (rPid[0] == 211) && (rPid[1] == -211) && (rPid[2] == 22) && (rPid[3] == 22); }
  Bool_t IsEmpty() { return (rPid[0] == 0) && (rPid[1] == 0) && (rPid[2] == 0) && (rPid[3] == 0); }

  void Reset() {
    for (Int_t i = 0; i < 4; i++) {
      rEntry[i] = 0;
      rPid[i] = 0;
      rEvent[i] = 0;
      rDeltaTheta[i] = 0;
      rDeltaPhi[i] = 0;
      particleDir[i]->SetXYZ(0, 0, 0);
    }
    electronDir->SetXYZ(0, 0, 0);
  }

  void RotateParticle(Int_t index) {
    // rotate on theta
    particleDir[index]->SetTheta(electronDir->Theta() + rDeltaTheta[index]);
    // rotate on phi
    particleDir[index]->SetPhi(electronDir->Phi() + rDeltaPhi[index]);
  }

  void GetParticleDir(std::vector<TVector3 *> rotatedMomentum, Int_t index) {
    rotatedMomentum[index]->SetX(particleDir[index]->X());
    rotatedMomentum[index]->SetY(particleDir[index]->Y());
    rotatedMomentum[index]->SetZ(particleDir[index]->Z());
  }

  void GetElectronDir(TVector3* lastElectron) {
    lastElectron->SetX(electronDir->X());
    lastElectron->SetY(electronDir->Y());
    lastElectron->SetZ(electronDir->Z());
  }

  Double_t GetDeltaTheta(Int_t index) {
    return particleDir[index]->Theta() - electronDir->Theta();
  }

  Double_t GetDeltaPhi(Int_t index) {
    return particleDir[index]->Phi() - electronDir->Phi();
  }

 private:
  Int_t rEntry[4];
  Int_t rPid[4];
  Int_t rEvent[4];

  Int_t lastEvent = -1;

  Double_t rDeltaTheta[4];  // w.r.t. electron's momentum
  Double_t rDeltaPhi[4];    // w.r.t. electron's momentum

  TVector3* electronDir = new TVector3(0, 0, 0);
  std::vector<TVector3*> particleDir = {new TVector3(0, 0, 0), new TVector3(0, 0, 0), new TVector3(0, 0, 0), new TVector3(0, 0, 0)};
};

#endif
