#ifndef TMIXINGBKGROW_HXX
#define TMIXINGBKGROW_HXX

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

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
    // assign direction of old particle and their respective electron
    ElectronOld[index]->SetXYZ(fPex, fPey, fPez);
    ParticleOld[index]->SetXYZ(fPx, fPy, fPz);
    // assign direction of new electron
    ElectronNew->SetXYZ(fPex, fPey, fPez); // electron
    ParticleNew[index]->SetXYZ(fPx, fPy, fPz); // will be rotated
    // ElectronNew->SetXYZ(-fPex, -fPey, kEbeam - fPez);  // virtual photon
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
    std::cout << std::fixed << std::setprecision(4) << std::setw(7) << "Event\t" << std::setw(7) << "Entry\t" << std::setw(7) << "PID\t" << std::setw(7) << "Px\t" << std::setw(7)
              << "Py\t" << std::setw(7) << "Pz\t" << std::setw(7) << "Pex\t" << std::setw(7) << "Pey\t" << std::setw(7) << "Pez" << std::endl;
    for (Int_t i = 0; i < 4; i++) {
      std::cout << std::fixed << std::setprecision(4) << std::setw(7) << rEvent[i] << "\t" << std::setw(7) << rEntry[i] << "\t" << std::setw(7) << rPid[i] << "\t" << std::setw(7)
                << ParticleNew[i]->X() << "\t" << std::setw(7) << ParticleNew[i]->Y() << "\t" << std::setw(7) << ParticleNew[i]->Z() << "\t" << std::setw(7) << ElectronNew->X()
                << "\t" << std::setw(7) << ElectronNew->Y() << "\t" << std::setw(7) << ElectronNew->Z() << std::endl;
    }
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
      ParticleNew[i]->SetXYZ(0, 0, 0);
    }
    ElectronNew->SetXYZ(0, 0, 0);
  }

  void RotateParticle(Int_t index) {
    /* Rotation alla Antonio */
    
    // rotate phi
    ParticleNew[index]->RotateZ(ElectronNew->Phi() - ElectronOld[index]->Phi());

    // rotate theta
    // first, align virtual photons to same phi angle
    TVector3* ElectronAux = new TVector3(0, 0, 0);
    ElectronAux->SetMagThetaPhi(1, ElectronOld[index]->Theta(), ElectronNew->Phi()); // same phi as ElectronNew

    // then, rotate angle-axis
    TVector3 Axis = ElectronAux->Cross(*ElectronNew); // vector perp to the theta rotation plane
    Double_t DeltaTheta = TMath::Abs(ElectronNew->Theta() - ElectronOld[index]->Theta());
    ParticleNew[index]->Rotate(DeltaTheta, Axis);

    std::cout << ElectronNew->Mag()*ParticleOld[index]->Mag()/ElectronOld[index]->Mag() << std::endl;
    ParticleNew[index]->SetMag(ElectronNew->Mag()*ParticleOld[index]->Mag()/ElectronOld[index]->Mag());

    // rotate on theta
    // ParticleNew[index]->SetTheta(ElectronNew->Theta() + rDeltaTheta[index]);
    // rotate on phi
    // ParticleNew[index]->SetPhi(ElectronNew->Phi() + rDeltaPhi[index]);
  }

  void GetParticleDir(std::vector<TVector3*> rotatedMomentum, Int_t index) {
    rotatedMomentum[index]->SetX(ParticleNew[index]->X());
    rotatedMomentum[index]->SetY(ParticleNew[index]->Y());
    rotatedMomentum[index]->SetZ(ParticleNew[index]->Z());
  }

  void GetElectronDir(TVector3* lastElectron) {
    lastElectron->SetX(ElectronNew->X());
    lastElectron->SetY(ElectronNew->Y());
    lastElectron->SetZ(ElectronNew->Z());
    /*
    lastElectron->SetX(-ElectronNew->X());
    lastElectron->SetY(-ElectronNew->Y());
    lastElectron->SetZ(kEbeam - ElectronNew->Z());
    */
  }

  Double_t GetDeltaTheta(Int_t index) { return ParticleNew[index]->Theta() - ElectronNew->Theta(); }

  Double_t GetDeltaPhi(Int_t index) { return ParticleNew[index]->Phi() - ElectronNew->Phi(); }

 private:
  Int_t rEntry[4];
  Int_t rPid[4];
  Int_t rEvent[4];

  Int_t lastEvent = -1;

  Double_t rDeltaTheta[4];  // w.r.t. electron's momentum
  Double_t rDeltaPhi[4];    // w.r.t. electron's momentum

  TVector3* ElectronNew = new TVector3(0, 0, 0);
  std::vector<TVector3*> ElectronOld = {new TVector3(0, 0, 0), new TVector3(0, 0, 0), new TVector3(0, 0, 0), new TVector3(0, 0, 0)};
  std::vector<TVector3*> ParticleOld = {new TVector3(0, 0, 0), new TVector3(0, 0, 0), new TVector3(0, 0, 0), new TVector3(0, 0, 0)};
  std::vector<TVector3*> ParticleNew = {new TVector3(0, 0, 0), new TVector3(0, 0, 0), new TVector3(0, 0, 0), new TVector3(0, 0, 0)};
};

#endif
