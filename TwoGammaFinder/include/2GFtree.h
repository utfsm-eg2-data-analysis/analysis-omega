#ifndef TWOGFTREE_H
#define TWOGFTREE_H

/*
   NAMING CONVENTIONS

   rec_i   : input variables for reconstructed particles (simulations or data)
   rec_m   : output variables for reconstructed particles (simulations or data) with combinations
   rec_eta : output variables for reconstructed particles (simulations or data) for the eta candidates

   gen_i   : input variables for generated particles (simulations)
   gen_m   : output variables for generated particles (simulations) with combinations
   gen_eta : output variables for generated particles (simulations) for the eta candidates
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
  Float_t vxh[2];
  Float_t vyh[2];
  Float_t vzh[2];
  Float_t Sector[2];
  Float_t Betta[2];
  Float_t Mass2[2];
  Float_t Pid[2];
  Float_t T4[2];
  Float_t E[2];
  Float_t Px[2];
  Float_t Py[2];
  Float_t Pz[2];
  Float_t Z[2];
  Float_t Pt2[2];
  Float_t Pl2[2];
  Float_t Mx2[2];
  Float_t ThetaPQ[2];
  Float_t PhiPQ[2];
  Float_t ThetaLab[2];
  Float_t PhiLab[2];
  Float_t deltaZ[2];
  Float_t deltaTheta[2]; // added
  Float_t TruePid[2]; // true pid, from gsim (only for sim)
  // number of particles (2)
  Float_t nGamma;
  Float_t cIndex;
  // event related (2)
  Float_t Entry[2];
  Float_t Event;
};

struct rec_eta {
  // (15)
  Float_t Px;
  Float_t Py;
  Float_t Pz;
  Float_t P;
  Float_t E;
  Float_t M;
  Float_t Theta; // opening angle between 2 gammas
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
  Float_t vxh[2];
  Float_t vyh[2];
  Float_t vzh[2];
  Float_t Sector[2];
  Float_t Betta[2];
  Float_t Mass2[2];
  Float_t Pid[2];
  Float_t E[2];
  Float_t Px[2];
  Float_t Py[2];
  Float_t Pz[2];
  Float_t Z[2];
  Float_t Pt2[2];
  Float_t Pl2[2];
  Float_t Mx2[2];
  Float_t ThetaPQ[2];
  Float_t PhiPQ[2];
  Float_t ThetaLab[2];
  Float_t PhiLab[2];
  Float_t deltaZ[2];
  Float_t deltaTheta[2];
  // number of particles (2)
  Float_t nGamma;
  Float_t cIndex;
  // event related (1)
  Float_t Entry[2];
};

struct gen_eta {
  // eta (15)
  Float_t Px;
  Float_t Py;
  Float_t Pz;
  Float_t P;
  Float_t E;
  Float_t M;
  Float_t Theta; // opening angle between 2 gammas
  Float_t Z;
  Float_t ThetaPQ;
  Float_t PhiPQ;
  Float_t Pt2;
  Float_t Pl2;
  Float_t Mx2;
  Float_t ThetaLab;
  Float_t PhiLab;
};

#endif
