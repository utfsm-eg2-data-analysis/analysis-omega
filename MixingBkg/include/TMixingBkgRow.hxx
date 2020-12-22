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

  void Fill(Int_t entry, Int_t evnt, Int_t pid) {
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
    std::cout << "(" << rPid[0] << ", " << rPid[1] << ", " << rPid[2] << ", " << rPid[3] << ")" << std::endl;
    std::cout << "(" << rEntry[0] << ", " << rEntry[1] << ", " << rEntry[2] << ", " << rEntry[3] << ")" << std::endl;
    std::cout << "(" << rEvent[0] << ", " << rEvent[1] << ", " << rEvent[2] << ", " << rEvent[3] << ")" << std::endl;
  }

  Bool_t IsFull() { return (rPid[0] == 211) && (rPid[1] == -211) && (rPid[2] == 22) && (rPid[3] == 22); }
  Bool_t IsEmpty() { return (rPid[0] == 0) & (rPid[1] == 0) && (rPid[2] == 0) && (rPid[3] == 0); }

  void Reset() {
    for (Int_t i = 0; i < 4; i++) {
      rEntry[i] = 0;
      rPid[i] = 0;
      rEvent[i] = 0;
    }
  }

private:

  Int_t rEntry[4];
  Int_t rPid[4];
  Int_t rEvent[4];

  Int_t lastEvent = -1;
};

#endif
