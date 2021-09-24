#ifndef THREEPFTREE_H
#define THREEPFTREE_H

/*
   NAMING CONVENTIONS

   stable_t : output variables for final-state or "stable" particles (data or simulations)
   pi0_t    : output variables for pi0 candidates (data or simulations)
   omega_t  : output variables for omega candidates (data or simulations)
*/

struct stable_t {
  // electron (16 variables)
  Float_t Q2, W, Nu, Xb, Yb;
  Float_t Pex, Pey, Pez, Pe;
  Float_t Xec, Yec, Zec;
  Float_t TargType;
  Float_t PhiLabEl, ThetaLabEl;
  Float_t SectorEl;
  // particles (14/15 vars)
  Float_t E[4], Z[4], Px[4], Py[4], Pz[4], P[4];
  Float_t ThetaPQ[4], PhiPQ[4], Pt2[4], Pl2[4];
  Float_t ThetaLab[4], PhiLab[4];
  Float_t deltaZ[4];
  Float_t Pid[4];
  Float_t ParentID[4];  // empty for data or sim.rec.
  // event related (2 vars)
  Float_t Entry[4];  // for debug purposes
  Float_t Event;
};

struct pi0_t {
  // pi0 (7 variables)
  Float_t E, M;
  Float_t Px, Py, Pz, P;
  Float_t Theta;  // opening angle between 2 gammas
};

struct omega_t {
  // (14 variables)
  Float_t E, P, Px, Py, Pz, M;
  Float_t Z, D;
  Float_t ThetaPQ, PhiPQ;
  Float_t Pt2, Pl2;
  Float_t ThetaLab, PhiLab;
};

#endif
