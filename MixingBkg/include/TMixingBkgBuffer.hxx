#ifndef TMIXINGBKGBUFFER_HXX
#define TMIXINGBKGBUFFER_HXX

#include "TMixingBkgRow.hxx"

class TMixingBkgBuffer {
  /*
    TMixingBkgBuffer is a structure that contains <BufferLength> rows.
  */

 public:
  TMixingBkgBuffer() {
    // Default constructor
    Reset();
  }

  ~TMixingBkgBuffer() {
    // Default destructor
    // (?)
  }

  TMixingBkgRow *GetRow(Int_t N) { return &Buffer[N]; }

  void SetBin(Int_t X, Int_t Y) {
    BinQ2 = X;
    BinNu = Y;
    SetBinLimits();
  }

  void SetBinLimits() {
    Q2Min = 1.0 + BinQ2 * 0.3;
    Q2Max = 1.0 + (BinQ2 + 1.) * 0.3;
    NuMin = 2.2 + BinNu * 0.2;
    NuMax = 2.2 + (BinNu + 1) * 0.2;
  }

  void Resize(Int_t L) {
    BufferLength = L;
    Buffer.resize(BufferLength);
    Reset();
  }

  void Reset() {
    for (Int_t N = 0; N < BufferLength; N++) {
      GetRow(N)->Reset();
    }
  }

  Double_t GetQ2Min() { return Q2Min; }  // just in case
  Double_t GetQ2Max() { return Q2Max; }
  Double_t GetNuMin() { return NuMin; }
  Double_t GetNuMax() { return NuMax; }

  void AddParticle(Int_t entry, Int_t evnt, Int_t pid, std::vector<Int_t> &Candidate, Double_t fPex, Double_t fPey, Double_t fPez, Double_t fPx, Double_t fPy, Double_t fPz,
                   TVector3* lastElectron, std::vector<TVector3 *> rotatedMomentum) {
    for (Int_t N = 0; N < BufferLength; N++) {
      if (evnt != GetRow(N)->GetLastEvent() && !GetRow(N)->ParticleFilled(pid)) {
        // fill
        GetRow(N)->Fill(entry, evnt, pid, fPex, fPey, fPez, fPx, fPy, fPz);
        UpdateBuffer(N, Candidate, lastElectron, rotatedMomentum);
        break;
      }
    }
  }

  void UpdateBuffer(Int_t N, std::vector<Int_t> &Candidate, TVector3* lastElectron, std::vector<TVector3 *> rotatedMomentum) {
    // assigns entry-vector to an external vector called Candidate (which corresponds to the output of an entirely filled row),
    // then it erases the first row and resizes again
    if (GetRow(N)->IsFull()) {
      // save information of last electron into "lastElectron" vector
      GetRow(N)->GetElectronDir(lastElectron);
      for (Int_t i = 0; i < 4; i++) {
	// rotate all particles w.r.t. last electron added
	GetRow(N)->RotateParticle(i);
        Candidate[i] = GetRow(N)->GetEntry(i);
	// save information of particle into "rotatedMomentum" vector
        GetRow(N)->GetParticleDir(rotatedMomentum, i);
      }
#ifdef DEBUG
      GetRow(N)->Print();
#else
#endif
      Buffer.erase(Buffer.begin() + N);
      Buffer.resize(BufferLength);
    }
  }

  void Print() {
    std::cout << "/*** PRINTING BUFFER (Q2 = " << BinQ2 << ", Nu = " << BinNu << ") ***/" << std::endl;
    std::cout << std::endl;
    for (Int_t N = 0; N < BufferLength; N++) {
      if (GetRow(N)->IsEmpty()) break;
      std::cout << "ROW " << N << ":" << std::endl;
      GetRow(N)->Print();
      std::cout << std::endl;
    }
  }

 private:
  Int_t BinQ2 = 0, BinNu = 0;
  Int_t BufferLength = 0;
  Int_t Q2Min, Q2Max;
  Int_t NuMin, NuMax;
  std::vector<TMixingBkgRow> Buffer;
};

#endif
