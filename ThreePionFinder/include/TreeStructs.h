#ifndef TREESTRUCTS_H
#define TREESTRUCTS_H

/*
   NAMING CONVENTIONS

   rec_i   : input variables for reconstructed particles (simulations or data)
   rec_m   : output variables for reconstructed particles (simulations or data) with combinations
   rec_pi0 : output variables for reconstructed particles (simulations or data) for pi0 candidates
   rec_w   : output variables for reconstructed particles (simulations or data) for omega candidates

   gen_i   : input variables for generated particles (simulations)
   gen_m   : output variables for generated particles (simulations) with combinations
   gen_pi0 : output variables for generated particles (simulations) for pi0 candidates
   gen_w   : output variables for generated particles (simulations) for omega candidates
*/

struct rec_i {
  // electron (19)
  Float_t Q2;
  Float_t W;
  Float_t Nu;
  Float_t Xb;
  Float_t Yb;
  Float_t vxe;
  Float_t vye;
  Float_t vze;
  Float_t SectorEl;
  Float_t TargType;
  Float_t Pex;
  Float_t Pey;
  Float_t Pez;
  Float_t BettaEl;
  Float_t vxec;
  Float_t vyec;
  Float_t vzec;
  Float_t ThetaLabEl;
  Float_t PhiLabEl;
  // particle (21)
  Float_t Eh;
  Float_t Zh;
  Float_t ThetaPQ;
  Float_t Pt2;
  Float_t Pl2;
  Float_t PhiPQ;
  Float_t Mx2;
  Float_t ThetaLab;
  Float_t PhiLab;
  Float_t vxh;
  Float_t vyh;
  Float_t vzh;
  Float_t Sector;
  Float_t Px;
  Float_t Py;
  Float_t Pz;
  Float_t Betta;
  Float_t Mass2;
  Float_t pid;
  Float_t T4;
  Float_t deltaZ;
  // event (1)
  Float_t evnt;
};

struct rec_m {
  // electron (19)
  Float_t Q2;
  Float_t W;
  Float_t Nu;
  Float_t Xb;
  Float_t Yb;
  Float_t Xe;
  Float_t Ye;
  Float_t Ze;
  Float_t SectorEl;
  Float_t TargType;
  Float_t Pex;
  Float_t Pey;
  Float_t Pez;
  Float_t BettaEl;
  Float_t Xec;
  Float_t Yec;
  Float_t Zec;
  Float_t ThetaLabEl;
  Float_t PhiLabEl;
  // particles (23)
  Float_t vxh[4];
  Float_t vyh[4];
  Float_t vzh[4];
  Float_t Sector[4];
  Float_t Betta[4];
  Float_t Mass2[4];
  Float_t Pid[4];
  Float_t T4[4];
  Float_t E[4];
  Float_t Px[4];
  Float_t Py[4];
  Float_t Pz[4];
  Float_t Z[4];
  Float_t Pt2[4];
  Float_t Pl2[4];
  Float_t Mx2[4];
  Float_t ThetaPQ[4];
  Float_t PhiPQ[4];
  Float_t ThetaLab[4];
  Float_t PhiLab[4];
  Float_t deltaZ[4];
  Float_t deltaTheta[4]; // added
  Float_t TruePid[4]; // true pid, from gsim (only for sim)
  // number of particles (4)
  Float_t nPip;
  Float_t nPim;
  Float_t nGamma;
  Float_t cIndex;
  // event related (2)
  Float_t Entry[4];
  Float_t Event;
};

struct rec_pi0 {
  // pi0 (6)
  Float_t Px;
  Float_t Py;
  Float_t Pz;
  Float_t P;
  Float_t E;
  Float_t M;
  Float_t Theta; // opening angle between 2 gammas
};

struct rec_w {
  // omega (15)
  Float_t Px;
  Float_t Py;
  Float_t Pz;
  Float_t P;
  Float_t D;
  Float_t M;
  Float_t E;
  Float_t Z;
  Float_t ThetaPQ;
  Float_t PhiPQ;
  Float_t Pt2;
  Float_t Pl2;
  Float_t Mx2;
  Float_t ThetaLab;
  Float_t PhiLab;
};

struct gen_i {
  // electron (16)
  Float_t Q2;
  Float_t W;
  Float_t Nu;
  Float_t Xb;
  Float_t Yb;
  Float_t vxe;
  Float_t vye;
  Float_t vze;
  Float_t SectorEl;
  Float_t TargType;
  Float_t Pex;
  Float_t Pey;
  Float_t Pez;
  Float_t BettaEl;
  Float_t ThetaLabEl;
  Float_t PhiLabEl;
  // particle (20)
  Float_t Eh;
  Float_t Zh;
  Float_t ThetaPQ;
  Float_t Pt2;
  Float_t Pl2;
  Float_t PhiPQ;
  Float_t Mx2;
  Float_t ThetaLab;
  Float_t PhiLab;
  Float_t vxh;
  Float_t vyh;
  Float_t vzh;
  Float_t Sector;
  Float_t Px;
  Float_t Py;
  Float_t Pz;
  Float_t Betta;
  Float_t Mass2;
  Float_t pid;
  Float_t deltaZ;
};

struct gen_m {
  // electron (16)
  Float_t Q2;
  Float_t W;
  Float_t Nu;
  Float_t Xb;
  Float_t Yb;
  Float_t Xe;
  Float_t Ye;
  Float_t Ze;
  Float_t SectorEl;
  Float_t TargType;
  Float_t Pex;
  Float_t Pey;
  Float_t Pez;
  Float_t BettaEl;
  Float_t ThetaLabEl;
  Float_t PhiLabEl;
  // particle (21)
  Float_t vxh[4];
  Float_t vyh[4];
  Float_t vzh[4];
  Float_t Sector[4];
  Float_t Betta[4];
  Float_t Mass2[4];
  Float_t Pid[4];
  Float_t E[4];
  Float_t Px[4];
  Float_t Py[4];
  Float_t Pz[4];
  Float_t Z[4];
  Float_t Pt2[4];
  Float_t Pl2[4];
  Float_t Mx2[4];
  Float_t ThetaPQ[4];
  Float_t PhiPQ[4];
  Float_t ThetaLab[4];
  Float_t PhiLab[4];
  Float_t deltaZ[4];
  Float_t deltaTheta[4]; // added
  // number of particles (4)
  Float_t nPip;
  Float_t nPim;
  Float_t nGamma;
  Float_t cIndex;
  // event related (1)
  Float_t Entry[4];
};

struct gen_pi0 {
  // pi0 (6)
  Float_t Px;
  Float_t Py;
  Float_t Pz;
  Float_t P;
  Float_t E;
  Float_t M;
  Float_t Theta; // opening angle between 2 gammas
};

struct gen_w {
  // omega (15)
  Float_t Px;
  Float_t Py;
  Float_t Pz;
  Float_t P;
  Float_t D;
  Float_t M;
  Float_t Z;
  Float_t E;
  Float_t ThetaPQ;
  Float_t PhiPQ;
  Float_t Pt2;
  Float_t Pl2;
  Float_t Mx2;
  Float_t ThetaLab;
  Float_t PhiLab;
};

#endif
