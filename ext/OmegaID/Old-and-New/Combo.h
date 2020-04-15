/*************************************************/
/*  Combo.h                                      */
/*                                               */
/*  Created by Orlando Soto, CCTVAL              */
/*  Modified for omega by Andrés Bórquez, CCTVAL */
/*                                               */
/*************************************************/

#include <vector>
#include <sys/stat.h>
#include <cstdarg>
#include <algorithm>
#include <map>
#include <string.h>

#include "TSpectrum.h"
#include "Riostream.h"
#include "TApplication.h"
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TClasTool.h"
#include "TIdentificator.h"
#include "TMath.h"
#include "TBenchmark.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TLatex.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TMatrixD.h"
#include "TClonesArray.h"

#include "do_pid.h"
#include "Particle.h"

class Combo {
 public:
  std::vector<Particle*> kParticles;
  static constexpr Float_t kQ2Tol = 0.3, kNuTol = 0.3;
  int Npart;
  Float_t lastEvent,kQ2,kNu;
  TLorentzVector *q4; // virtual photon 4th vector
  
  Combo(): Npart(0),lastEvent(0),kQ2(0),kNu(0),q4(0){}
  
  Combo(Combo &c) {
    Npart = 0;
    for (int k = 0; k < c.Npart; k++) {
      addParticle(c.kParticles[k]);
    }
    lastEvent = c.lastEvent;
    kQ2 = c.kQ2;
    kNu = c.kNu;
  }
  
  inline Double_t Px(){return getSum().Px();}
  inline Double_t Py(){return getSum().Py();}
  inline Double_t Pz(){return getSum().Pz();}
  inline Double_t P2(){return getSum().P2();}
  inline Double_t P(){return getSum().P();}
  inline Double_t E(){return getSum().E();}
  inline Double_t M(){return getSum().M();}
  inline Double_t M2(){return getSum().M2();}
  
  ~Combo() {
    delete q4;
    clear();
  }
  
  void clear(){ 
    kParticles.clear();
    Npart=0;
  }

  // Go to CM frame
  void boost() {
    //Particle *p=&getSum();
    for (int k = 0; k < Npart; k++)
      kParticles[k]->Boost(-getSum().BoostVector());
  }

  int addParticle(Particle *p, Float_t ev = 0, Bool_t rotfirst = kFALSE, Bool_t fid = kFALSE) {
    lastEvent = ev;
    if (Npart == 0) {
      kQ2= Q2; // using global variable, must be changed!
      kNu= Nu; // using global variable, must be changed!        
      q4 = new TLorentzVector(-Pex,-Pey,kEbeam-Pez,kEbeam-Ee);
    } else if (rotfirst) {
      TLorentzVector *q4n = new TLorentzVector(-Pex, -Pey, kEbeam - Pez, kEbeam - Ee);
      // Double_t Dth = q4->Theta() - q4n->Theta(); //no theta rotation, beam direction
      Double_t Dphi = q4->Phi() - q4n->Phi();
      //p->SetTheta(p->Theta()+Dth);                                                               
      p->SetPhi(p->Phi()+Dphi);
    }
    
    if (fid && !p->checkFiducial()) return Npart;
    
    kParticles.push_back(p);
    Npart++;
    
    return Npart;
  }

  Particle getSum() {
    Particle p;
    for (int k = 0; k < Npart;k++) {
      p += *kParticles[k];
    }
    return p;
  }
  
  Int_t findPid(Int_t pid) {
    Int_t ret = 0;
    for (int k = 0; k < Npart; k++) if (pid == kParticles[k]->pid) ret++;
    return ret;
  }
  
  // using global variables, must be changed!                                                                                                  
  Bool_t isCompatible() {
    if ( !( (-kQ2Tol< (kQ2 - Q2) && (kQ2 - Q2) < kQ2Tol) && (-kNuTol< (kNu - Nu) && (kNu - Nu) < kNuTol) ) )
      return kFALSE;
    return kTRUE;
  }

  inline Particle* operator [] (const int & i) const {
    if (i >= Npart || i < 0) {
      std::cout << "Index out of bounds" << std::endl;
      exit(1);
    }
    return kParticles[i];
  }
  
  //const: the object that owns the method will not be modified by this method
  inline Combo operator + (const Combo & c) const {
    Combo r;
    for (int k=0;k<c.Npart;k++) {
      r.addParticle(c[k]);
    }
    for (int k = 0; k < this->Npart; k++) {
      r.addParticle((*this)[k]);
    }
    return r;
  }
  
  inline Combo operator += (const Combo &q) {
    for (int k = 0; k < q.Npart; k++) {
	addParticle( q[k] );
    }
    return *this;
  }
  
  void print() {
    for (int k = 0; k < Npart; k++)
      std::cout << kParticles[k]->getName() << " ";
    std::cout << std::endl;
  }
};
