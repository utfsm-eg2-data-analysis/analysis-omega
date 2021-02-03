#ifndef TMIXINGBKGCLUSTER_HXX
#define TMIXINGBKGCLUSTER_HXX

#include "TMixingBkgBuffer.hxx"

class TMixingBkgCluster {
  /*
    TMixingBkgCluster is a two-dimensional structure that contains <NBinsQ2> x <NBinsNu> buffers.
  */

 public:
  TMixingBkgCluster(Int_t N, Int_t M, Int_t K = 2, Int_t L = 100) : NBinsQ2(N), NBinsNu(M), NBinsVertex(K), BufferLength(L) {
    // Default constructor
    // first, resize cluster
    Cluster.resize(NBinsQ2);
    for (Int_t i = 0; i < NBinsQ2; i++) {
      Cluster[i].resize(NBinsNu);
      for (Int_t j = 0; j < NBinsNu; j++) {
	Cluster[i][j].resize(NBinsVertex);
      }
    }
    // then, create buffers
    for (Int_t x = 0; x < NBinsQ2; x++) {
      for (Int_t y = 0; y < NBinsNu; y++) {
	for (Int_t z = 0; z < NBinsVertex; z++) {
	  GetBuffer(x, y, z)->SetBin(x, y, z);
	  GetBuffer(x, y, z)->Resize(BufferLength);
	}
      }
    }
  }
    
  ~TMixingBkgCluster() {
    // Default destructor
    // (?)
  }

  TMixingBkgBuffer* GetBuffer(Int_t X, Int_t Y, Int_t Z) { return &Cluster[X][Y][Z]; }

  Int_t AssignBinQ2(Double_t Q2) {
    Double_t LowerLimit = 1.0;
    Double_t UpperLimit = 4.0;
    Double_t BinWidth = (UpperLimit - LowerLimit) / (Double_t)NBinsQ2;
    Int_t Bin;
    for (Int_t c = NBinsQ2; c >= 0; c--) {
      if (Q2 > LowerLimit + c * BinWidth) {
        Bin = c;
        break;
      }
    }
    return Bin;
  }

  Int_t AssignBinNu(Double_t Nu) {
    Double_t LowerLimit = 2.2;
    Double_t UpperLimit = 4.2;
    Double_t BinWidth = (UpperLimit - LowerLimit) / (Double_t)NBinsNu;
    Int_t Bin;
    for (Int_t c = NBinsNu; c >= 0; c--) {
      if (Nu > LowerLimit + c * BinWidth) {
        Bin = c;
        break;
      }
    }
    return Bin;
  }

  void Add(Int_t entry, Int_t evnt, Int_t pid, Double_t Q2, Double_t Nu, Int_t TargType, std::vector<Int_t>& Candidate, Double_t fPex, Double_t fPey, Double_t fPez, Double_t fPx, Double_t fPy,
           Double_t fPz, TVector3* lastElectron, std::vector<TVector3*> rotatedMomentum) {
    if (Q2 > 1. && Q2 < 4. && Nu > 2.2 && Nu < 4.2 && (TargType == 1 || TargType == 2)) {
      GetBuffer(AssignBinQ2(Q2), AssignBinNu(Nu), TargType-1)->AddParticle(entry, evnt, pid, Candidate, fPex, fPey, fPez, fPx, fPy, fPz, lastElectron, rotatedMomentum);
    }
  }

  void Print() {
    for (Int_t i = 0; i < NBinsQ2; i++) {
      for (Int_t j = 0; j < NBinsNu; j++) {
	for (Int_t k = 0; k < NBinsVertex; k++) {
	  GetBuffer(i, j, k)->Print();
	}
      }
    }
  }

 private:
  Int_t NBinsQ2, NBinsNu;
  Int_t NBinsVertex;
  Int_t BufferLength;  // same size for all buffers
  std::vector<std::vector<std::vector<TMixingBkgBuffer>>> Cluster;
};

#endif
