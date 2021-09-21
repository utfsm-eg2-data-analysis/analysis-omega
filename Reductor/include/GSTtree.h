#ifndef GSTTREE_H
#define GSTTREE_H

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

/*
   NAMING CONVENTIONS

   rec_t : output variables for reconstructed particles (data or simulations)
   gen_t : output variables for generated particles (simulations)
*/

struct rec_t {
  // electron (26 variables)
  Float_t Q2, W, Nu, Xb, Yb;
  Float_t Pex, Pey, Pez, Pe;
  Float_t Etote, Eine, Eoute;
  Float_t XECe, YECe, ZECe;
  Float_t vxe, vye, vze;
  Float_t vxec, vyec, vzec;
  Float_t TargType;
  Float_t SectorEl, PhiLabEl, ThetaLabEl;
  Float_t BettaEl;
  // evnt (1 variable)
  Float_t evnt;
  // particle (29 variables)
  Float_t Eh, Zh, ThetaPQ, Pt2, Pl2, PhiPQ, Mx2, T;
  Float_t ThetaLab, PhiLab;
  Float_t vxh, vyh, vzh;
  Float_t Sector;
  Float_t Px, Py, Pz, P;
  Float_t Betta, Mass2, Etot, Ein, Eout;
  Float_t XEC, YEC, ZEC;
  Float_t pid, T4, deltaZ;
};

struct gen_t {
  // electron (17)
  Float_t mc_Q2, mc_W, mc_Nu, mc_Xb, mc_Yb;
  Float_t mc_Pex, mc_Pey, mc_Pez, mc_Pe;
  Float_t mc_vxe, mc_vye, mc_vze;
  Float_t mc_TargType;
  Float_t mc_SectorEl, mc_PhiLabEl, mc_ThetaLabEl;
  Float_t mc_BettaEl;
  // particle (23)
  Float_t mc_Eh, mc_Zh, mc_ThetaPQ, mc_Pt2, mc_Pl2, mc_PhiPQ;
  Float_t mc_ThetaLab, mc_PhiLab;
  Float_t mc_Mx2, mc_T;
  Float_t mc_vxh, mc_vyh, mc_vzh;
  Float_t mc_Sector;
  Float_t mc_Px, mc_Py, mc_Pz, mc_P;
  Float_t mc_Betta;
  Float_t mc_Mass2, mc_deltaZ;
  Float_t mc_pid;
  Float_t mc_ParentID;
};

#endif
