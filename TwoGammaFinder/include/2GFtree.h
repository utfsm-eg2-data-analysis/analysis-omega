#ifndef TWOGFTREE_H
#define TWOGFTREE_H

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

/*
   NAMING CONVENTIONS

   stable_t : output variables for final-state or "stable" particles (data or simulations)
   eta_t    : output variables for eta candidates (data or simulations)
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
  Float_t E[2], Z[2], Px[2], Py[2], Pz[2], P[2];
  Float_t ThetaPQ[2], PhiPQ[2], Pt2[2], Pl2[2];
  Float_t ThetaLab[2], PhiLab[2];
  Float_t deltaZ[2];
  Float_t Pid[2];
  Float_t ParentID[2]; // empty for data or sim.rec.
  // event related (2 vars)
  Float_t Entry[2];  // for debug purposes
  Float_t Event;
};

struct eta_t {
  // (14 variables)
  Float_t E, P, Px, Py, Pz, M;
  Float_t Z;
  Float_t ThetaPQ, PhiPQ;
  Float_t Pt2, Pl2;
  Float_t ThetaLab, PhiLab;
  Float_t Theta;  // opening angle between 2 gammas
};

#endif
