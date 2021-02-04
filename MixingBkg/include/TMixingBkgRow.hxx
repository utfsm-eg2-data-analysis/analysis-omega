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
    // assign direction of last electron
    electronDir->SetXYZ(fPex, fPey, fPez); // electron, test
    // electronDir->SetXYZ(-fPex, -fPey, kEbeam - fPez);  // virt photon, test
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
    std::cout << std::fixed << std::setprecision(4) << std::setw(7) << "Event\t" << std::setw(7) << "Entry\t" << std::setw(7) << "PID\t" << std::setw(7) << "Px\t" << std::setw(7)
              << "Py\t" << std::setw(7) << "Pz\t" << std::setw(7) << "Pex\t" << std::setw(7) << "Pey\t" << std::setw(7) << "Pez" << std::endl;
    for (Int_t i = 0; i < 4; i++) {
      std::cout << std::fixed << std::setprecision(4) << std::setw(7) << rEvent[i] << "\t" << std::setw(7) << rEntry[i] << "\t" << std::setw(7) << rPid[i] << "\t" << std::setw(7)
                << particleDir[i]->X() << "\t" << std::setw(7) << particleDir[i]->Y() << "\t" << std::setw(7) << particleDir[i]->Z() << "\t" << std::setw(7) << electronDir->X()
                << "\t" << std::setw(7) << electronDir->Y() << "\t" << std::setw(7) << electronDir->Z() << std::endl;
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
      particleDir[i]->SetXYZ(0, 0, 0);
    }
    electronDir->SetXYZ(0, 0, 0);
  }

  void RotateParticle(Int_t index) {
    /* Rotation alla Antonio */
    /*
    // rotate phi angle in delta phi of virtual photons
    TVector3* auxP = new TVector3(Particle_OVP[index]->X(), Particle_OVP[index]->Y(), Particle_OVP[index]->Z());
    auxP->RotateZ(NewVirtPhoton->Phi() - OrigVirtPhoton[index]->Phi());

    // rotate theta angle
    // first, align virtual photons to same phi angle
    TVector3* auxOVP = new TVector3(0, 0, 0);
    auxOVP->SetMagThetaPhi(1, OrigVirtPhoton[index]->Theta(), NewVirtPhoton->Phi());  // same phi as NVP

    // then, rotate angle-axis
    TVector3 auxAxis = auxOVP->Cross(*NewVirtPhoton); // vector perp to the theta rotation plane
    Double_t deltaTheta = TMath::Abs(OrigVirtPhoton[index]->Theta() - NewVirtPhoton->Theta());
    auxP->Rotate(deltaTheta, auxAxis);

    // set magnitude, just in case
    auxP->SetMag(Particle_OVP[index]->Mag());

    // set vector
    Particle_NVP[index]->SetX(auxP->X());
    Particle_NVP[index]->SetY(auxP->Y());
    Particle_NVP[index]->SetZ(auxP->Z());
    */
    // rotate on theta
    // particleDir[index]->SetTheta(electronDir->Theta() + rDeltaTheta[index]);
    // rotate on phi
    // particleDir[index]->SetPhi(electronDir->Phi() + rDeltaPhi[index]);
  }

  void GetParticleDir(std::vector<TVector3*> rotatedMomentum, Int_t index) {
    rotatedMomentum[index]->SetX(particleDir[index]->X());
    rotatedMomentum[index]->SetY(particleDir[index]->Y());
    rotatedMomentum[index]->SetZ(particleDir[index]->Z());
  }

  void GetElectronDir(TVector3* lastElectron) {
    lastElectron->SetX(electronDir->X());
    lastElectron->SetY(electronDir->Y());
    lastElectron->SetZ(electronDir->Z());
    /*
    lastElectron->SetX(-electronDir->X());
    lastElectron->SetY(-electronDir->Y());
    lastElectron->SetZ(kEbeam - electronDir->Z());
    */
  }

  Double_t GetDeltaTheta(Int_t index) { return particleDir[index]->Theta() - electronDir->Theta(); }

  Double_t GetDeltaPhi(Int_t index) { return particleDir[index]->Phi() - electronDir->Phi(); }

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
