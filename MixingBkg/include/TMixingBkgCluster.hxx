#ifndef TMIXINGBKGCLUSTER_HXX
#define TMIXINGBKGCLUSTER_HXX

#include "TMixingBkgBuffer.hxx"

class TMixingBkgCluster {
  /*
    TMixingBkgCluster is a two-dimensional structure that contains <NBinsQ2> x <NBinsNu> buffers.
  */

 public:

  TMixingBkgCluster(Int_t N, Int_t M, Int_t L) : NBinsQ2(N), NBinsNu(M), BufferLength(L) {
    // Default constructor
    // first, resize cluster
    Cluster.resize(NBinsQ2);
    for (Int_t i = 0; i < NBinsQ2; i++) Cluster[i].resize(NBinsNu);
    // then, create buffers
    for (Int_t x = 0; x < NBinsQ2; x++) {
      for (Int_t y = 0; y < NBinsNu; y++) {
        GetBuffer(x, y)->SetBin(x, y);
        GetBuffer(x, y)->Resize(BufferLength);
      }
    }
  }

  ~TMixingBkgCluster() {
    // Default destructor
    // (?)
  }

  TMixingBkgBuffer* GetBuffer(Int_t X, Int_t Y) { return &Cluster[X][Y]; }

  Int_t AssignBinQ2(Double_t Q2) {  // there must be a more elegant way to do this
    if (Q2 > 1. && Q2 <= 1.3)
      return 0;
    else if (Q2 > 1.3 && Q2 <= 1.6)
      return 1;
    else if (Q2 > 1.6 && Q2 <= 1.9)
      return 2;
    else if (Q2 > 1.9 && Q2 <= 2.2)
      return 3;
    else if (Q2 > 2.2 && Q2 <= 2.5)
      return 4;
    else if (Q2 > 2.5 && Q2 <= 2.8)
      return 5;
    else if (Q2 > 2.8 && Q2 <= 3.1)
      return 6;
    else if (Q2 > 3.1 && Q2 <= 3.4)
      return 7;
    else if (Q2 > 3.4 && Q2 <= 3.7)
      return 8;
    else if (Q2 > 3.4 && Q2 <= 4.0)
      return 9;
  }

  Int_t AssignBinNu(Double_t Nu) {  // there must be a more elegant way to do this
    if (Nu > 2.2 && Nu <= 2.4)
      return 0;
    else if (Nu > 2.4 && Nu <= 2.6)
      return 1;
    else if (Nu > 2.6 && Nu <= 2.8)
      return 2;
    else if (Nu > 2.8 && Nu <= 3.0)
      return 3;
    else if (Nu > 3.0 && Nu <= 3.2)
      return 4;
    else if (Nu > 3.2 && Nu <= 3.4)
      return 5;
    else if (Nu > 3.4 && Nu <= 3.6)
      return 6;
    else if (Nu > 3.6 && Nu <= 3.8)
      return 7;
    else if (Nu > 3.8 && Nu <= 4.0)
      return 8;
    else if (Nu > 4.0 && Nu <= 4.2)
      return 9;
  }

  void Add(Int_t entry, Int_t evnt, Int_t pid, Double_t Q2, Double_t Nu, std::vector<Int_t>& Candidate) {
    if (Q2 > 1. && Q2 < 4. && Nu > 2.2 && Nu < 4.2) {
      GetBuffer(AssignBinQ2(Q2), AssignBinNu(Nu))->AddParticle(entry, evnt, pid, Candidate);
    }
  }

  void Print() {
    for (Int_t i = 0; i < 10; i++) {
      for (Int_t j = 0; j < 10; j++) {
        GetBuffer(i, j)->Print();
      }
    }
  }

 private:

  Int_t NBinsQ2, NBinsNu;
  Int_t BufferLength;  // same size for all buffers
  std::vector<std::vector<TMixingBkgBuffer>> Cluster;
};

#endif
