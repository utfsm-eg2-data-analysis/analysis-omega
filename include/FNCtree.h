#ifndef __FNCTREE__H
#define __FNCTREE__H

/*
   NAMING CONVENTIONS

   data_i : input variables for data
   data_o : output variables for data with no combination

   data_m   : output variables for data with combinations
   data_pi0 : output variables for data for pi0 candidates
   data_w   : output variables for data for omega candidates

   simrec_i : input variables for simulations reconstructed (or accepted)

   gsim_i   : input variables for simulations generated (or thrown)

   simrec_o : output variables for simulations reconstructed (or accepted) with no combination

   gsim_o   : output variables for simulations generated (or thrown) with no combination

   simrec_m   : output variables for simulations reconstructed (or accepted) with combinations
   simrec_pi0 : output variables for simulations reconstructed (or accepted) for pi0 candidates
   simrec_w   : output variables for simulations reconstructed (or accepted) for omega candidates

   gsim_m   : output variables for simulations generated (or thrown) with combinations
   gsim_pi0 : output variables for simulations generated (or thrown) for pi0 candidates
   gsim_w   : output variables for simulations generated (or thrown) for omega candidates
*/

struct data_i {
  // (83 variables)
  // electron (40)
  Float_t Q2, W, Nu, Xb, Yb;
  Float_t vxe, vye, vze;
  Float_t vxec, vyec, vzec;
  Float_t XECe, YECe, ZECe;
  Float_t SectorEl, TargType;
  Float_t Pex, Pey, Pez, Pe;
  Float_t BettaEl, Etote, Eine, Eoute;
  Float_t StatDCEl, DCStatusEl, StatECEl, ECStatusEl, TimeECEl, PathECEl, Chi2ECEl, StatSCEl, SCStatusEl, TimeSCEl, PathSCEl, StatCCEl, CCStatusEl, NpheEl, Chi2CCEl, StatusEl;
  Float_t NRowsDCEl, NRowsECEl, NRowsSCEl, NRowsCCEl;
  // particle (42)
  Float_t Zh, ThetaPQ, Pt2, Pl2, PhiPQ, Mx2, T, vxh, vyh, vzh, Sector, Px, Py, Pz, P, Betta, Mass2, Etot, Ein, Eout, XEC, YEC, ZEC, pid, T4, deltaZ;
  Float_t StatDC, DCStatus, StatEC, ECStatus, TimeEC, PathEC, Chi2EC, StatSC, SCStatus, TimeSC, PathSC, StatCC, CCStatus, Nphe, Chi2CC, Status;
  Float_t NRowsDC, NRowsEC, NRowsSC, NRowsCC;
  // event (1)
  Float_t evnt;
};

struct data_o {
  // (101 variables for data)
  // electron (41)
  Float_t Q2, W, Nu, Xb, Yb, Xe, Ye, Ze, SectorEl, TargType, Pex, Pey, Pez, Pe, BettaEl, Etote, Eine, Eoute, Xec, Yec, Zec, XECe, YECe, ZECe;
  Float_t P2e;
  Float_t ThetaLabEl, PhiLabEl;
  Float_t StatDCEl, DCStatusEl, StatECEl, ECStatusEl, TimeECEl, PathECEl, Chi2ECEl, StatSCEl, SCStatusEl, TimeSCEl, PathSCEl, StatCCEl, CCStatusEl, NpheEl, Chi2CCEl, StatusEl;
  Float_t NRowsDCEl, NRowsECEl, NRowsSCEl, NRowsCCEl;
  // particle (60)
  Float_t vxh, vyh, vzh;
  Float_t Sector, Betta, Mass2;
  Float_t Etot, Ein, Eout;
  Float_t XEC, YEC, ZEC;
  Float_t Pid, T4, deltaZ, M;
  Float_t E_prev, Px_prev, Py_prev, Pz_prev, P2_prev, P_prev;
  Float_t E_true, Px_true, Py_true, Pz_true, P2_true, P_true;
  Float_t E_corr, Px_corr, Py_corr, Pz_corr, P2_corr, P_corr;
  Float_t Z, ThetaPQ, Pt2, Pl2, PhiPQ, Mx2, T, CosThetaPQ, BettaCalc, deltaTheta;
  Float_t ThetaLab, PhiLab;
  Float_t StatDC, DCStatus, StatEC, ECStatus, TimeEC, PathEC, Chi2EC, StatSC, SCStatus, TimeSC, PathSC, StatCC, CCStatus, Nphe, Chi2CC, Status;
  Float_t NRowsDC, NRowsEC, NRowsSC, NRowsCC;
  // event-related (2)
  Float_t Entry;
  Float_t Event;
};

struct data_m {
  // (194 variables)
  // electron (41)
  Float_t Q2, W, Nu, Xb, Yb, Xe, Ye, Ze, SectorEl, TargType, Pex, Pey, Pez, Pe, BettaEl, Etote, Eine, Eoute, Xec, Yec, Zec, XECe, YECe, ZECe;
  Float_t P2e;
  Float_t ThetaLabEl, PhiLabEl;
  Float_t StatDCEl, DCStatusEl, StatECEl, ECStatusEl, TimeECEl, PathECEl, Chi2ECEl, StatSCEl, SCStatusEl, TimeSCEl, PathSCEl, StatCCEl, CCStatusEl, NpheEl, Chi2CCEl, StatusEl;
  Float_t NRowsDCEl, NRowsECEl, NRowsSCEl, NRowsCCEl;
  // particles (64)
  Float_t vxh[4], vyh[4], vzh[4], Sector[4], Betta[4], Mass2[4], Etot[4], Ein[4], Eout[4], XEC[4], YEC[4], ZEC[4], Pid[4], T4[4], deltaZ[4], M[4];
  Float_t E_prev[4], Px_prev[4], Py_prev[4], Pz_prev[4], P2_prev[4], P_prev[4];
  Float_t E_true[4], Px_true[4], Py_true[4], Pz_true[4], P2_true[4], P_true[4];
  Float_t E_corr[4], Px_corr[4], Py_corr[4], Pz_corr[4], P2_corr[4], P_corr[4];
  Float_t Z[4], ThetaPQ[4], Pt2[4], Pl2[4], PhiPQ[4], Mx2[4], T[4], CosThetaPQ[4], BettaCalc[4], deltaTheta[4];
  Float_t ThetaLab[4], PhiLab[4];
  Float_t StatDC[4], DCStatus[4], StatEC[4], ECStatus[4], TimeEC[4], PathEC[4], Chi2EC[4], StatSC[4];
  Float_t SCStatus[4], TimeSC[4], PathSC[4], StatCC[4], CCStatus[4], Nphe[4], Chi2CC[4], Status[4];
  Float_t NRowsDC[4], NRowsEC[4], NRowsSC[4], NRowsCC[4];
  // crossed terms (9)
  Float_t pippimP, pippimE, pippimM;
  Float_t pippi0P, pippi0E, pippi0M;
  Float_t pimpi0P, pimpi0E, pimpi0M;
  // number of particles (4)
  Float_t nPip, nPim, nGamma;
  Float_t cIndex;
  // event related (2)
  Float_t Entry[4];
  Float_t Event;
};

struct data_pi0 {
  // pi0 (24)
  Float_t Px_prev, Py_prev, Pz_prev, P2_prev, P_prev, E_prev, M_prev, Theta_prev;
  Float_t Px_true, Py_true, Pz_true, P2_true, P_true, E_true, M_true, Theta_true;
  Float_t Px_corr, Py_corr, Pz_corr, P2_corr, P_corr, E_corr, M_corr, Theta_corr;
};

struct data_w {
  // omega (66)
  Float_t Px_prev, Py_prev, Pz_prev, P_prev, P2_prev, E_prev;
  Float_t Z_prev, CosThetaPQ_prev, ThetaPQ_prev, Pt2_prev, Pl2_prev, PhiPQ_prev, Mx2_prev, T_prev, BettaCalc_prev, deltaTheta_prev, D_prev, M_prev;
  Float_t ThetaLab_prev, PhiLab_prev;
  Float_t Px_true, Py_true, Pz_true, P_true, P2_true, E_true;
  Float_t Z_true, CosThetaPQ_true, ThetaPQ_true, Pt2_true, Pl2_true, PhiPQ_true, Mx2_true, T_true, BettaCalc_true, deltaTheta_true, D_true, M_true;
  Float_t ThetaLab_true, PhiLab_true;
  Float_t Px_corr, Py_corr, Pz_corr, P_corr, P2_corr, E_corr;
  Float_t Z_corr, CosThetaPQ_corr, ThetaPQ_corr, Pt2_corr, Pl2_corr, PhiPQ_corr, Mx2_corr, T_corr, BettaCalc_corr, deltaTheta_corr, D_corr, M_corr;
  Float_t ThetaLab_corr, PhiLab_corr;
};

struct simrec_i {
  // (83 variables for simrec)
  // electron (40)
  Float_t Q2, W, Nu, Xb, Yb;
  Float_t vxe, vye, vze;
  Float_t vxec, vyec, vzec;
  Float_t XECe, YECe, ZECe;
  Float_t SectorEl, TargType;
  Float_t Pex, Pey, Pez, Pe;
  Float_t BettaEl, Etote, Eine, Eoute;
  Float_t StatDCEl, DCStatusEl, StatECEl, ECStatusEl, TimeECEl, PathECEl, Chi2ECEl, StatSCEl, SCStatusEl, TimeSCEl, PathSCEl, StatCCEl, CCStatusEl, NpheEl, Chi2CCEl, StatusEl;
  Float_t NRowsDCEl, NRowsECEl, NRowsSCEl, NRowsCCEl;
  // particle (42)
  Float_t Zh, ThetaPQ, Pt2, Pl2, PhiPQ, Mx2, T, vxh, vyh, vzh, Sector, Px, Py, Pz, P, Betta, Mass2, Etot, Ein, Eout, XEC, YEC, ZEC, pid, T4, deltaZ;
  Float_t StatDC, DCStatus, StatEC, ECStatus, TimeEC, PathEC, Chi2EC, StatSC, SCStatus, TimeSC, PathSC, StatCC, CCStatus, Nphe, Chi2CC, Status;
  Float_t NRowsDC, NRowsEC, NRowsSC, NRowsCC;
};

struct gsim_i {
  // (35 variables for gsim)
  // electron (15)
  Float_t Q2, W, Nu, Xb, Yb;
  Float_t vxe, vye, vze;
  Float_t SectorEl, TargType;
  Float_t Pex, Pey, Pez, Pe, BettaEl;
  // particle (19)
  Float_t Zh, ThetaPQ, Pt2, Pl2, PhiPQ, Mx2, T;
  Float_t vxh, vyh, vzh;
  Float_t Sector;
  Float_t Px, Py, Pz, P;
  Float_t Betta, Mass2;
  Float_t pid;
  Float_t deltaZ;
  // event (1)
  Float_t evnt;
};

struct simrec_o {
  // (101 variables for simrec)
  // electron (41)
  Float_t Q2, W, Nu, Xb, Yb, Xe, Ye, Ze, SectorEl, TargType, Pex, Pey, Pez, Pe, BettaEl, Etote, Eine, Eoute, Xec, Yec, Zec, XECe, YECe, ZECe;
  Float_t P2e;
  Float_t PhiLabEl, ThetaLabEl;
  Float_t StatDCEl, DCStatusEl, StatECEl, ECStatusEl, TimeECEl, PathECEl, Chi2ECEl, StatSCEl, SCStatusEl, TimeSCEl, PathSCEl, StatCCEl, CCStatusEl, NpheEl, Chi2CCEl, StatusEl;
  Float_t NRowsDCEl, NRowsECEl, NRowsSCEl, NRowsCCEl;  
  // particle (60)
  Float_t vxh, vyh, vzh, Sector, Betta, Mass2, Etot, Ein, Eout, XEC, YEC, ZEC, Pid, T4, deltaZ, M;
  Float_t E_prev, Px_prev, Py_prev, Pz_prev, P2_prev, P_prev;
  Float_t E_true, Px_true, Py_true, Pz_true, P2_true, P_true;
  Float_t E_corr, Px_corr, Py_corr, Pz_corr, P2_corr, P_corr;
  Float_t Z, ThetaPQ, Pt2, Pl2, PhiPQ, Mx2, T, CosThetaPQ, BettaCalc, deltaTheta;
  Float_t PhiLab, ThetaLab;
  Float_t StatDC, DCStatus, StatEC, ECStatus, TimeEC, PathEC, Chi2EC, StatSC, SCStatus, TimeSC, PathSC, StatCC, CCStatus, Nphe, Chi2CC, Status;
  Float_t NRowsDC, NRowsEC, NRowsSC, NRowsCC;
  // event-related (1)
  Float_t Entry;
};

struct gsim_o {
  // (41 variables for gsim)
  // electron (16)
  Float_t Q2, W, Nu, Xb, Yb, Xe, Ye, Ze, SectorEl, TargType, Pex, Pey, Pez, Pe, BettaEl;
  Float_t P2e;
  Float_t ThetaLabEl, PhiLabEl;
  // particle (25)
  Float_t vxh, vyh, vzh, Sector, Betta, Mass2, Pid, deltaZ, M;
  Float_t E, Px, Py, Pz, P2, P;
  Float_t Z, ThetaPQ, Pt2, Pl2, PhiPQ, Mx2, T, CosThetaPQ, BettaCalc, deltaTheta;
  Float_t ThetaLab, PhiLab;
  // event-related (2)
  Float_t Event;
  Float_t Entry;
};

struct simrec_m {
  // (194 variables for simrec)
  // electron (41)
  Float_t Q2, W, Nu, Xb, Yb, Xe, Ye, Ze, SectorEl, TargType, Pex, Pey, Pez, Pe, BettaEl, Etote, Eine, Eoute, Xec, Yec, Zec, XECe, YECe, ZECe;
  Float_t P2e;
  Float_t ThetaLabEl, PhiLabEl;
  Float_t StatDCEl, DCStatusEl, StatECEl, ECStatusEl, TimeECEl, PathECEl, Chi2ECEl, StatSCEl, SCStatusEl, TimeSCEl, PathSCEl, StatCCEl, CCStatusEl, NpheEl, Chi2CCEl, StatusEl;
  Float_t NRowsDCEl, NRowsECEl, NRowsSCEl, NRowsCCEl;
  // particles (60)
  Float_t vxh[4], vyh[4], vzh[4], Sector[4], Betta[4], Mass2[4], Etot[4], Ein[4], Eout[4], XEC[4], YEC[4], ZEC[4], Pid[4], T4[4], deltaZ[4], M[4];
  Float_t E_prev[4], Px_prev[4], Py_prev[4], Pz_prev[4], P2_prev[4], P_prev[4];
  Float_t E_true[4], Px_true[4], Py_true[4], Pz_true[4], P2_true[4], P_true[4];
  Float_t E_corr[4], Px_corr[4], Py_corr[4], Pz_corr[4], P2_corr[4], P_corr[4];
  Float_t Z[4], ThetaPQ[4], Pt2[4], Pl2[4], PhiPQ[4], Mx2[4], T[4], CosThetaPQ[4], BettaCalc[4], deltaTheta[4];
  Float_t ThetaLab[4], PhiLab[4];
  Float_t StatDC[4], DCStatus[4], StatEC[4], ECStatus[4], TimeEC[4], PathEC[4], Chi2EC[4], StatSC[4];
  Float_t SCStatus[4], TimeSC[4], PathSC[4], StatCC[4], CCStatus[4], Nphe[4], Chi2CC[4], Status[4];
  Float_t NRowsDC[4], NRowsEC[4], NRowsSC[4], NRowsCC[4];
  // crossed terms (9)
  Float_t pippimP, pippimE, pippimM;
  Float_t pippi0P, pippi0E, pippi0M;
  Float_t pimpi0P, pimpi0E, pimpi0M;
  // number of particles (4)
  Float_t nPip, nPim, nGamma;
  Float_t cIndex;
  // event related (1)
  Float_t Entry[4];
};

struct simrec_pi0 {
  // pi0 (24)
  Float_t Px_prev, Py_prev, Pz_prev, P2_prev, P_prev, E_prev, M_prev, Theta_prev;
  Float_t Px_true, Py_true, Pz_true, P2_true, P_true, E_true, M_true, Theta_true;
  Float_t Px_corr, Py_corr, Pz_corr, P2_corr, P_corr, E_corr, M_corr, Theta_corr;
};

struct simrec_w {
  // omega (63)
  Float_t Px_prev, Py_prev, Pz_prev, P_prev, P2_prev, E_prev;
  Float_t Z_prev, CosThetaPQ_prev, ThetaPQ_prev, Pt2_prev, Pl2_prev, PhiPQ_prev, Mx2_prev, T_prev, BettaCalc_prev, deltaTheta_prev, D_prev, M_prev;
  Float_t ThetaLab_prev, PhiLab_prev;
  Float_t Px_true, Py_true, Pz_true, P_true, P2_true, E_true;
  Float_t Z_true, CosThetaPQ_true, ThetaPQ_true, Pt2_true, Pl2_true, PhiPQ_true, Mx2_true, T_true, BettaCalc_true, deltaTheta_true, D_true, M_true;
  Float_t ThetaLab_true, PhiLab_true;
  Float_t Px_corr, Py_corr, Pz_corr, P_corr, P2_corr, E_corr;
  Float_t Z_corr, CosThetaPQ_corr, ThetaPQ_corr, Pt2_corr, Pl2_corr, PhiPQ_corr, Mx2_corr, T_corr, BettaCalc_corr, deltaTheta_corr, D_corr, M_corr;
  Float_t ThetaLab_corr, PhiLab_corr;
};

struct gsim_m {
  // (72 variables for gsim)
  // electron (16=5+3+2+5+1)
  Float_t Q2, W, Nu, Xb, Yb;
  Float_t Xe, Ye, Ze;
  Float_t SectorEl, TargType;
  Float_t Pex, Pey, Pez, Pe, P2e;
  Float_t BettaEl;
  Float_t ThetaLabEl, PhiLabEl;
  // particle (27)
  Float_t vxh[4], vyh[4], vzh[4], Sector[4], Betta[4], Mass2[4], Pid[4], deltaZ[4], M[4];
  Float_t E[4], Px[4], Py[4], Pz[4], P2[4], P[4];
  Float_t Z[4], ThetaPQ[4], Pt2[4], Pl2[4], PhiPQ[4], Mx2[4], T[4], CosThetaPQ[4], BettaCalc[4], deltaTheta[4];
  Float_t ThetaLab[4], PhiLab[4];
  // crossed terms (9)
  Float_t pippimP, pippimE, pippimM;
  Float_t pippi0P, pippi0E, pippi0M;
  Float_t pimpi0P, pimpi0E, pimpi0M;
  // number of particles (3)
  Float_t nPip, nPim, nGamma;
  Float_t cIndex;
  // event related (2)
  Float_t Event;
  Float_t Entry[4];
};

struct gsim_pi0 {
  // pi0 (8)
  Float_t Px, Py, Pz, P2, P;
  Float_t E, M, Theta;
};

struct gsim_w {
  // omega (20)
  Float_t Px, Py, Pz, P, P2, E;
  Float_t D, M;
  Float_t Z, CosThetaPQ, ThetaPQ, Pt2, Pl2, PhiPQ, Mx2, T, BettaCalc, deltaTheta;
  Float_t ThetaLab, PhiLab;
};

#endif
