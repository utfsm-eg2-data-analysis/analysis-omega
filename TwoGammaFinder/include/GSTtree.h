#ifndef GSTTREE_H
#define GSTTREE_H

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

/*
   NAMING CONVENTIONS

   elec_t : variables for scattered electrons (data or simulations)
   part_t : variables for final-state particles (data or simulations)
*/

struct elec_t {
  // electron (26 variables)
  Float_t Q2, W, Nu, Xb, Yb;
  Float_t Px, Py, Pz, P;
  Float_t Etot, Ein, Eout;
  Float_t XEC, YEC, ZEC;
  Float_t vx, vy, vz;
  Float_t vxc, vyc, vzc;
  Float_t TargType;
  Float_t Sector, ThetaLab, PhiLab;
  Float_t Betta;
  // evnt (1 variable)
  Float_t evnt;
};

struct part_t {
  // particle (30 variables)
  Float_t Eh, Zh;
  Float_t Px, Py, Pz, P;
  Float_t ThetaPQ, PhiPQ;
  Float_t Pt2, Pl2;
  Float_t ThetaLab, PhiLab;
  Float_t Mx2, T;
  Float_t vx, vy, vz;
  Float_t Sector;
  Float_t Etot, Ein, Eout;
  Float_t XEC, YEC, ZEC;
  Float_t Betta, Mass2, T4, deltaZ;
  Float_t pid;
  Float_t ParentID;
};

#endif
