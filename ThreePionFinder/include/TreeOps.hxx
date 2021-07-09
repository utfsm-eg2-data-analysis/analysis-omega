#ifndef TREEOPS_HXX
#define TREEOPS_HXX

#include "Headers.hxx"
#include "Math.hxx"
#include "PDG.hxx"

#include "TreeStructs.h"

#ifndef INVLD
#define INVLD -9999
#endif

void SetMinimalBranches_REC(TTree *tree, rec_i& t) {
  // turn on only necessary branches
  tree->SetBranchStatus("pid", 1);
  tree->SetBranchAddress("pid",  &t.pid);
  tree->SetBranchStatus("evnt", 1);
  tree->SetBranchAddress("evnt", &t.evnt); // always non-null
}

void SetMinimalBranches_GEN(TTree *tree, gen_i& mc_t) {
  // turn on only necessary branches
  tree->SetBranchStatus("mc_pid", 1);
  tree->SetBranchAddress("mc_pid", &mc_t.pid);
}

void SetInputBranches_REC(TTree* tree, rec_i& t) {
  // electron (19)
  tree->SetBranchAddress("Q2", &t.Q2);
  tree->SetBranchAddress("W", &t.W);
  tree->SetBranchAddress("Nu", &t.Nu);
  tree->SetBranchAddress("Xb", &t.Xb);
  tree->SetBranchAddress("Yb", &t.Yb);
  tree->SetBranchAddress("vxe", &t.vxe);
  tree->SetBranchAddress("vye", &t.vye);
  tree->SetBranchAddress("vze", &t.vze);
  tree->SetBranchAddress("SectorEl", &t.SectorEl);
  tree->SetBranchAddress("TargType", &t.TargType);
  tree->SetBranchAddress("Pex", &t.Pex);
  tree->SetBranchAddress("Pey", &t.Pey);
  tree->SetBranchAddress("Pez", &t.Pez);
  tree->SetBranchAddress("BettaEl", &t.BettaEl);
  tree->SetBranchAddress("vxec", &t.vxec);
  tree->SetBranchAddress("vyec", &t.vyec);
  tree->SetBranchAddress("vzec", &t.vzec);
  tree->SetBranchAddress("ThetaLabEl", &t.ThetaLabEl);
  tree->SetBranchAddress("PhiLabEl", &t.PhiLabEl);
  // particles (21)
  tree->SetBranchAddress("Eh", &t.Eh);
  tree->SetBranchAddress("Zh", &t.Zh);
  tree->SetBranchAddress("ThetaPQ", &t.ThetaPQ);
  tree->SetBranchAddress("Pt2", &t.Pt2);
  tree->SetBranchAddress("Pl2", &t.Pl2);
  tree->SetBranchAddress("PhiPQ", &t.PhiPQ);
  tree->SetBranchAddress("Mx2", &t.Mx2);
  tree->SetBranchAddress("ThetaLab", &t.ThetaLab);
  tree->SetBranchAddress("PhiLab", &t.PhiLab);
  tree->SetBranchAddress("vxh", &t.vxh);
  tree->SetBranchAddress("vyh", &t.vyh);
  tree->SetBranchAddress("vzh", &t.vzh);
  tree->SetBranchAddress("Sector", &t.Sector);
  tree->SetBranchAddress("Px", &t.Px);
  tree->SetBranchAddress("Py", &t.Py);
  tree->SetBranchAddress("Pz", &t.Pz);
  tree->SetBranchAddress("Betta", &t.Betta);
  tree->SetBranchAddress("Mass2", &t.Mass2);
  tree->SetBranchAddress("pid", &t.pid);
  tree->SetBranchAddress("T4", &t.T4);
  tree->SetBranchAddress("deltaZ", &t.deltaZ);
  // event (1)
  tree->SetBranchAddress("evnt", &t.evnt);
}

void SetInputBranches_GEN(TTree *tree, gen_i& mc_t) {
  // electron (16)
  tree->SetBranchAddress("mc_Q2", &mc_t.Q2);
  tree->SetBranchAddress("mc_W", &mc_t.W);
  tree->SetBranchAddress("mc_Nu", &mc_t.Nu);
  tree->SetBranchAddress("mc_Xb", &mc_t.Xb);
  tree->SetBranchAddress("mc_Yb", &mc_t.Yb);
  tree->SetBranchAddress("mc_vxe", &mc_t.vxe);
  tree->SetBranchAddress("mc_vye", &mc_t.vye);
  tree->SetBranchAddress("mc_vze", &mc_t.vze);
  tree->SetBranchAddress("mc_SectorEl", &mc_t.SectorEl);
  tree->SetBranchAddress("mc_TargType", &mc_t.TargType);
  tree->SetBranchAddress("mc_Pex", &mc_t.Pex);
  tree->SetBranchAddress("mc_Pey", &mc_t.Pey);
  tree->SetBranchAddress("mc_Pez", &mc_t.Pez);
  tree->SetBranchAddress("mc_BettaEl", &mc_t.BettaEl);
  tree->SetBranchAddress("mc_ThetaLabEl", &mc_t.ThetaLabEl);
  tree->SetBranchAddress("mc_PhiLabEl", &mc_t.PhiLabEl);
  // particles (20)
  tree->SetBranchAddress("mc_Eh", &mc_t.Eh);
  tree->SetBranchAddress("mc_Zh", &mc_t.Zh);
  tree->SetBranchAddress("mc_ThetaPQ", &mc_t.ThetaPQ);
  tree->SetBranchAddress("mc_Pt2", &mc_t.Pt2);
  tree->SetBranchAddress("mc_Pl2", &mc_t.Pl2);
  tree->SetBranchAddress("mc_PhiPQ", &mc_t.PhiPQ);
  tree->SetBranchAddress("mc_Mx2", &mc_t.Mx2);
  tree->SetBranchAddress("mc_ThetaLab", &mc_t.ThetaLab);
  tree->SetBranchAddress("mc_PhiLab", &mc_t.PhiLab);
  tree->SetBranchAddress("mc_vxh", &mc_t.vxh);
  tree->SetBranchAddress("mc_vyh", &mc_t.vyh);
  tree->SetBranchAddress("mc_vzh", &mc_t.vzh);
  tree->SetBranchAddress("mc_Sector", &mc_t.Sector);
  tree->SetBranchAddress("mc_Px", &mc_t.Px);
  tree->SetBranchAddress("mc_Py", &mc_t.Py);
  tree->SetBranchAddress("mc_Pz", &mc_t.Pz);
  tree->SetBranchAddress("mc_Betta", &mc_t.Betta);
  tree->SetBranchAddress("mc_Mass2", &mc_t.Mass2);
  tree->SetBranchAddress("mc_pid", &mc_t.pid);
  tree->SetBranchAddress("mc_deltaZ", &mc_t.deltaZ);
}

void SetMixBranches_REC(TTree *tree, rec_m& m, rec_pi0& pi0, rec_w& w) {
  // electron (19)
  tree->Branch("Q2", &m.Q2);
  tree->Branch("W",  &m.W);
  tree->Branch("Nu", &m.Nu);
  tree->Branch("Xb", &m.Xb);
  tree->Branch("Yb", &m.Yb);
  tree->Branch("Xe", &m.Xe);
  tree->Branch("Ye", &m.Ye);
  tree->Branch("Ze", &m.Ze);
  tree->Branch("SectorEl", &m.SectorEl);
  tree->Branch("TargType", &m.TargType);
  tree->Branch("Pex", &m.Pex);
  tree->Branch("Pey", &m.Pey);
  tree->Branch("Pez", &m.Pez);
  tree->Branch("BettaEl", &m.BettaEl);
  tree->Branch("PhiLabEl", &m.PhiLabEl);
  tree->Branch("ThetaLabEl", &m.ThetaLabEl);
  tree->Branch("Xec", &m.Xec);
  tree->Branch("Yec", &m.Yec);
  tree->Branch("Zec", &m.Zec);
  // particles (23)
  tree->Branch("vxh", &m.vxh, "vxh[4]/F");
  tree->Branch("vyh", &m.vyh, "vyh[4]/F");
  tree->Branch("vzh", &m.vzh, "vzh[4]/F");
  tree->Branch("Sector", &m.Sector, "Sector[4]/F");
  tree->Branch("Betta", &m.Betta, "Betta[4]/F");
  tree->Branch("Mass2", &m.Mass2, "Mass2[4]/F");
  tree->Branch("Pid", &m.Pid, "Pid[4]/F");
  tree->Branch("T4", &m.T4, "T4[4]/F");
  tree->Branch("Px", &m.Px, "Px[4]/F");
  tree->Branch("Py", &m.Py, "Py[4]/F");
  tree->Branch("Pz", &m.Pz, "Pz[4]/F");
  tree->Branch("E", &m.E, "E[4]/F");  
  tree->Branch("Z", &m.Z, "Z[4]/F");
  tree->Branch("PhiPQ", &m.PhiPQ, "PhiPQ[4]/F");
  tree->Branch("ThetaPQ", &m.ThetaPQ, "ThetaPQ[4]/F");
  tree->Branch("PhiLab", &m.PhiLab, "PhiLab[4]/F");
  tree->Branch("ThetaLab", &m.ThetaLab, "ThetaLab[4]/F");
  tree->Branch("Pt2", &m.Pt2, "Pt2[4]/F");
  tree->Branch("Pl2", &m.Pl2, "Pl2[4]/F");
  tree->Branch("Mx2", &m.Mx2, "Mx2[4]/F");
  tree->Branch("deltaTheta", &m.deltaTheta, "deltaTheta[4]/F");  
  tree->Branch("deltaZ", &m.deltaZ, "deltaZ[4]/F");
  tree->Branch("TruePid", &m.TruePid, "TruePid[4]/F");
  // pi0 (6)
  tree->Branch("pi0Px", &pi0.Px);
  tree->Branch("pi0Py", &pi0.Py);
  tree->Branch("pi0Pz", &pi0.Pz);
  tree->Branch("pi0P", &pi0.P);
  tree->Branch("pi0E", &pi0.E);
  tree->Branch("pi0M", &pi0.M);
  tree->Branch("pi0Theta", &pi0.Theta);
  // omega (15)
  tree->Branch("wZ", &w.Z);
  tree->Branch("wPhiPQ", &w.PhiPQ);
  tree->Branch("wThetaPQ", &w.ThetaPQ);
  tree->Branch("wPhiLab", &w.PhiLab);
  tree->Branch("wThetaLab", &w.ThetaLab);
  tree->Branch("wPt2", &w.Pt2);
  tree->Branch("wPl2", &w.Pl2);
  tree->Branch("wMx2", &w.Mx2);
  tree->Branch("wPx", &w.Px);
  tree->Branch("wPy", &w.Py);
  tree->Branch("wPz", &w.Pz);
  tree->Branch("wP", &w.P);
  tree->Branch("wE", &w.E);
  tree->Branch("wD", &w.D);
  tree->Branch("wM", &w.M);
  // number of particles in that event (4)
  tree->Branch("nPip",   &m.nPip);
  tree->Branch("nPim",   &m.nPim);
  tree->Branch("nGamma", &m.nGamma);
  tree->Branch("cIndex", &m.cIndex);
  // event related (2)
  tree->Branch("Entry", &m.Entry, "Entry[4]/F");
  tree->Branch("Event", &m.Event);
}

void SetMixBranches_GEN(TTree* tree, gen_m& mc_m, gen_pi0& mc_pi0, gen_w& mc_w) {
  // electron (16)
  tree->Branch("mc_Q2", &mc_m.Q2);
  tree->Branch("mc_W", &mc_m.W);
  tree->Branch("mc_Nu", &mc_m.Nu);
  tree->Branch("mc_Xb", &mc_m.Xb);
  tree->Branch("mc_Yb", &mc_m.Yb);
  tree->Branch("mc_Xe", &mc_m.Xe);
  tree->Branch("mc_Ye", &mc_m.Ye);
  tree->Branch("mc_Ze", &mc_m.Ze);
  tree->Branch("mc_SectorEl", &mc_m.SectorEl);
  tree->Branch("mc_TargType", &mc_m.TargType);
  tree->Branch("mc_Pex", &mc_m.Pex);
  tree->Branch("mc_Pey", &mc_m.Pey);
  tree->Branch("mc_Pez", &mc_m.Pez);
  tree->Branch("mc_BettaEl", &mc_m.BettaEl);
  tree->Branch("mc_PhiLabEl", &mc_m.PhiLabEl);
  tree->Branch("mc_ThetaLabEl", &mc_m.ThetaLabEl);
  // particle (21)
  tree->Branch("mc_vxh", &mc_m.vxh, "mc_vxh[4]/F");
  tree->Branch("mc_vyh", &mc_m.vyh, "mc_vyh[4]/F");
  tree->Branch("mc_vzh", &mc_m.vzh, "mc_vzh[4]/F");
  tree->Branch("mc_Sector", &mc_m.Sector, "mc_Sector[4]/F");
  tree->Branch("mc_Betta", &mc_m.Betta, "mc_Betta[4]/F");
  tree->Branch("mc_Mass2", &mc_m.Mass2, "mc_Mass2[4]/F");
  tree->Branch("mc_Pid", &mc_m.Pid, "mc_Pid[4]/F");
  tree->Branch("mc_E", &mc_m.E, "mc_E[4]/F");
  tree->Branch("mc_Px", &mc_m.Px, "mc_Px[4]/F");
  tree->Branch("mc_Py", &mc_m.Py, "mc_Py[4]/F");
  tree->Branch("mc_Pz", &mc_m.Pz, "mc_Pz[4]/F");
  tree->Branch("mc_Z", &mc_m.Z, "mc_Z[4]/F");
  tree->Branch("mc_Pt2", &mc_m.Pt2, "mc_Pt2[4]/F");
  tree->Branch("mc_Pl2", &mc_m.Pl2, "mc_Pl2[4]/F");
  tree->Branch("mc_PhiPQ", &mc_m.PhiPQ, "mc_PhiPQ[4]/F");
  tree->Branch("mc_ThetaPQ", &mc_m.ThetaPQ, "mc_ThetaPQ[4]/F");
  tree->Branch("mc_PhiLab", &mc_m.PhiLab, "mc_PhiLab[4]/F");
  tree->Branch("mc_ThetaLab", &mc_m.ThetaLab, "mc_ThetaLab[4]/F");
  tree->Branch("mc_Mx2", &mc_m.Mx2, "mc_Mx2[4]/F");
  tree->Branch("mc_deltaZ", &mc_m.deltaZ, "mc_deltaZ[4]/F");
  tree->Branch("mc_deltaTheta", &mc_m.deltaTheta, "mc_deltaTheta[4]/F");
  // pi0 (6)
  tree->Branch("mc_pi0Px", &mc_pi0.Px);
  tree->Branch("mc_pi0Py", &mc_pi0.Py);
  tree->Branch("mc_pi0Pz", &mc_pi0.Pz);
  tree->Branch("mc_pi0E", &mc_pi0.E);
  tree->Branch("mc_pi0M", &mc_pi0.M);
  tree->Branch("mc_pi0Theta", &mc_pi0.Theta);
  // omega (15)
  tree->Branch("mc_wPx", &mc_w.Px);
  tree->Branch("mc_wPy", &mc_w.Py);
  tree->Branch("mc_wPz", &mc_w.Pz);
  tree->Branch("mc_wP", &mc_w.P);
  tree->Branch("mc_wE", &mc_w.E);
  tree->Branch("mc_wZ", &mc_w.Z);
  tree->Branch("mc_wD", &mc_w.D);
  tree->Branch("mc_wM", &mc_w.M);
  tree->Branch("mc_wPt2", &mc_w.Pt2);
  tree->Branch("mc_wPl2", &mc_w.Pl2);
  tree->Branch("mc_wPhiPQ", &mc_w.PhiPQ);
  tree->Branch("mc_wThetaPQ", &mc_w.ThetaPQ);
  tree->Branch("mc_wPhiLab", &mc_w.PhiLab);
  tree->Branch("mc_wThetaLab", &mc_w.ThetaLab);
  tree->Branch("mc_wMx2", &mc_w.Mx2);
  // number of particles (4)
  tree->Branch("mc_nPip", &mc_m.nPip);
  tree->Branch("mc_nPim", &mc_m.nPim);
  tree->Branch("mc_nGamma", &mc_m.nGamma);
  tree->Branch("mc_cIndex", &mc_m.cIndex);
  // event related (1)
  tree->Branch("mc_Entry", &mc_m.Entry, "mc_Entry[4]/F");
}

void NullMixVar_REC(rec_m& m, rec_pi0& pi0, rec_w& w) {
  // electron (19)
  m.Q2 = INVLD;
  m.W  = INVLD;
  m.Nu = INVLD;
  m.Xb = INVLD;
  m.Yb = INVLD;
  m.Xe = INVLD;
  m.Ye = INVLD;
  m.Ze = INVLD;
  m.SectorEl = INVLD;
  m.TargType = INVLD;
  m.Pex = INVLD;
  m.Pey = INVLD;
  m.Pez = INVLD;
  m.BettaEl = INVLD;
  m.PhiLabEl = INVLD;
  m.ThetaLabEl = INVLD;
  m.Xec = INVLD;
  m.Yec = INVLD;
  m.Zec = INVLD;
  for (Int_t index = 0; index < 4; index++) {
    // partices (23)
    m.vxh[index] = INVLD;
    m.vyh[index] = INVLD;
    m.vzh[index] = INVLD;
    m.Sector[index] = INVLD;
    m.deltaZ[index] = INVLD;
    m.T4[index] = INVLD;
    m.Mass2[index] = INVLD;
    m.Betta[index] = INVLD;
    m.Pid[index] = INVLD;
    m.E[index]  = INVLD;
    m.Px[index] = INVLD;
    m.Py[index] = INVLD;
    m.Pz[index] = INVLD;
    m.Z[index] = INVLD;
    m.PhiPQ[index]   = INVLD;
    m.ThetaPQ[index] = INVLD;
    m.PhiLab[index]   = INVLD;
    m.ThetaLab[index] = INVLD;
    m.Pt2[index] = INVLD;
    m.Pl2[index] = INVLD;
    m.deltaTheta[index] = INVLD;
    m.Mx2[index] = INVLD;
    m.TruePid[index] = INVLD;
    // last but not least
    m.Entry[index] = INVLD;
  }
  // pi0 (6)
  pi0.Px = INVLD;
  pi0.Py = INVLD;
  pi0.Pz = INVLD;
  pi0.M  = INVLD;
  pi0.E  = INVLD;
  pi0.Theta = INVLD;
  // omega (15)
  w.Px = INVLD;
  w.Py = INVLD;
  w.Pz = INVLD;
  w.P  = INVLD;
  w.E  = INVLD;
  w.M  = INVLD;
  w.D  = INVLD;
  w.Z  = INVLD;
  w.PhiPQ = INVLD;
  w.ThetaPQ = INVLD;
  w.PhiLab = INVLD;
  w.ThetaLab = INVLD;
  w.Pt2 = INVLD;
  w.Pl2 = INVLD;
  w.Mx2 = INVLD;
  // number of particles (4)
  m.nGamma = INVLD;
  m.nPip   = INVLD;
  m.nPim   = INVLD;
  m.cIndex = INVLD;
}

void NullMixVar_GEN(gen_m& mc_m, gen_pi0& mc_pi0, gen_w& mc_w) {
  // electron (16)
  mc_m.Q2 = INVLD;
  mc_m.W = INVLD;
  mc_m.Nu = INVLD;
  mc_m.Xb = INVLD;
  mc_m.Yb = INVLD;
  mc_m.Xe = INVLD;
  mc_m.Ye = INVLD;
  mc_m.Ze = INVLD;
  mc_m.SectorEl = INVLD;
  mc_m.TargType = INVLD;
  mc_m.Pex = INVLD;
  mc_m.Pey = INVLD;
  mc_m.Pez = INVLD;
  mc_m.BettaEl = INVLD;
  mc_m.ThetaLabEl = INVLD;
  mc_m.PhiLabEl = INVLD;
  // particle (21)
  for (Int_t index = 0; index < 4; index++) {
    mc_m.vxh[index] = INVLD;
    mc_m.vyh[index] = INVLD;
    mc_m.vzh[index] = INVLD;
    mc_m.Sector[index] = INVLD;
    mc_m.Betta[index] = INVLD;
    mc_m.Mass2[index] = INVLD;
    mc_m.Pid[index] = INVLD;
    mc_m.E[index] = INVLD;
    mc_m.Px[index] = INVLD;
    mc_m.Py[index] = INVLD;
    mc_m.Pz[index] = INVLD;
    mc_m.Z[index] = INVLD;
    mc_m.Pt2[index] = INVLD;
    mc_m.Pl2[index] = INVLD;
    mc_m.Mx2[index] = INVLD;
    mc_m.ThetaPQ[index] = INVLD;
    mc_m.PhiPQ[index] = INVLD;
    mc_m.ThetaLab[index] = INVLD;
    mc_m.PhiLab[index] = INVLD;
    mc_m.deltaZ[index] = INVLD;
    mc_m.deltaTheta[index] = INVLD; // added
    // event-related
    mc_m.Entry[index] = INVLD;
  }
  // number of particles (4)
  mc_m.nPip = INVLD;
  mc_m.nPim = INVLD;
  mc_m.nGamma = INVLD;
  mc_m.cIndex = INVLD;
  // pi0 (6)
  mc_pi0.Px = INVLD;
  mc_pi0.Py = INVLD;
  mc_pi0.Pz = INVLD;
  mc_pi0.P = INVLD;
  mc_pi0.E = INVLD;
  mc_pi0.M = INVLD;
  mc_pi0.Theta = INVLD; // opening angle between 2 gammas
  // omega (15)
  mc_w.Px = INVLD;
  mc_w.Py = INVLD;
  mc_w.Pz = INVLD;
  mc_w.P = INVLD;
  mc_w.D = INVLD;
  mc_w.M = INVLD;
  mc_w.Z = INVLD;
  mc_w.E = INVLD;
  mc_w.ThetaPQ = INVLD;
  mc_w.PhiPQ = INVLD;
  mc_w.Pt2 = INVLD;
  mc_w.Pl2 = INVLD;
  mc_w.Mx2 = INVLD;
  mc_w.ThetaLab = INVLD;
  mc_w.PhiLab = INVLD;
}

void AssignMixVar_REC(rec_i& t, rec_m& m, Int_t entry, Int_t index) {
  // electron (19)
  m.Q2 = t.Q2;
  m.W = t.W;
  m.Nu = t.Nu;
  m.Xb = t.Xb;
  m.Yb = t.Yb;
  m.Xe = t.vxe;
  m.Ye = t.vye;
  m.Ze = t.vze;
  m.SectorEl = t.SectorEl;
  m.TargType = t.TargType;
  m.Pex = t.Pex;
  m.Pey = t.Pey;
  m.Pez = t.Pez;
  m.BettaEl = t.BettaEl;
  m.PhiLabEl = PhiLab(t.Pex, t.Pey, t.Pez);
  m.ThetaLabEl = ThetaLab(t.Pex, t.Pey, t.Pez);
  m.Xec = t.vxec;
  m.Yec = t.vyec;
  m.Zec = t.vzec;
  // particles (22)
  m.vxh[index] = t.vxh;
  m.vyh[index] = t.vyh;
  m.vzh[index] = t.vzh;
  m.Sector[index] = t.Sector;
  m.deltaZ[index] = t.deltaZ;
  m.T4[index] = t.T4;
  m.Mass2[index] = t.Mass2;
  m.Betta[index] = t.Betta;
  m.Pid[index] = t.pid;  // important!
  TLorentzVector* fGamma = GetCorrPhotonEnergy(t);
  m.E[index] = (t.pid == 22) * fGamma->E() + (t.pid != 22) * t.Eh;
  m.Px[index] = (t.pid == 22) * fGamma->Px() + (t.pid != 22) * t.Px;
  m.Py[index] = (t.pid == 22) * fGamma->Py() + (t.pid != 22) * t.Py;
  m.Pz[index] = (t.pid == 22) * fGamma->Pz() + (t.pid != 22) * t.Pz;
  m.Z[index] = m.E[index] / m.Nu;
  Double_t fP = TMath::Sqrt(m.Px[index] * m.Px[index] + m.Py[index] * m.Py[index] + m.Pz[index] * m.Pz[index]);
  Double_t fCosThetaPQ = ((kEbeam - m.Pez) * m.Pz[index] - m.Pex * m.Px[index] - m.Pey * m.Py[index]) / (TMath::Sqrt(fP * fP * (m.Q2 + m.Nu * m.Nu)));
  m.PhiPQ[index] = PhiPQ(t.Pex, t.Pey, t.Pez, m.Px[index], m.Py[index], m.Pz[index]);
  m.ThetaPQ[index] = ThetaPQ(t.Pex, t.Pey, t.Pez, m.Px[index], m.Py[index], m.Pz[index]);
  m.PhiLab[index] = PhiLab(m.Px[index], m.Py[index], m.Pz[index]);
  m.ThetaLab[index] = ThetaLab(m.Px[index], m.Py[index], m.Pz[index]);
  m.Pt2[index] = fP * fP * (1 - fCosThetaPQ * fCosThetaPQ);
  m.Pl2[index] = fP * fP * fCosThetaPQ * fCosThetaPQ;
  m.deltaTheta[index] = DeltaTheta(t.Pex, t.Pey, t.Pez, m.Px[index], m.Py[index], m.Pz[index]);
  Double_t fM = GetParticleMass((Int_t) t.pid);
  m.Mx2[index] = m.W * m.W + fM * fM - 2 * m.Z[index] * m.Nu * m.Nu + 2 * TMath::Sqrt(m.Pl2[index] * (m.Nu * m.Nu + m.Q2)) - 2 * kMassProton * m.Z[index] * m.Nu;
  // event-related (2)
  m.Entry[index] = (Float_t) entry;
  m.Event = t.evnt;
}

void CheckContamination(gen_i &mc_t, rec_m &m, Int_t index) {
  // exclusive for gDataKind == "sim"
  m.TruePid[index] = mc_t.pid;
}

void AssignMoreVar_REC(rec_m& m, Int_t nPipThisEvent, Int_t nPimThisEvent, Int_t nGammaThisEvent, Int_t cIndex) {
  // number of particles (4)
  m.nPip   = nPipThisEvent;
  m.nPim   = nPimThisEvent;
  m.nGamma = nGammaThisEvent;
  m.cIndex = (Float_t) cIndex;
}

void AssignPi0Var_REC(rec_m& m, rec_pi0& pi0) {
  // pi0 (6)
  pi0.E = m.E[2] + m.E[3];
  pi0.Px = m.Px[2] + m.Px[3];
  pi0.Py = m.Py[2] + m.Py[3];
  pi0.Pz = m.Pz[2] + m.Pz[3];
  Double_t fP = TMath::Sqrt(pi0.Px * pi0.Px + pi0.Py * pi0.Py + pi0.Pz * pi0.Pz);
  pi0.M = TMath::Sqrt(pi0.E * pi0.E - fP * fP);
  Double_t fDot = m.Px[2] * m.Px[3] + m.Py[2] * m.Py[3] + m.Pz[2] * m.Pz[3];
  Double_t fMag0 = TMath::Sqrt(m.Px[2] * m.Px[2] + m.Py[2] * m.Py[2] + m.Pz[2] * m.Pz[2]);
  Double_t fMag1 = TMath::Sqrt(m.Px[3] * m.Px[3] + m.Py[3] * m.Py[3] + m.Pz[3] * m.Pz[3]);
  pi0.Theta = TMath::RadToDeg() * TMath::ACos(fDot / (fMag0 * fMag1));
}

void AssignOmegaVar_REC(rec_m& m, rec_pi0& pi0, rec_w& w) {
  // omega (15)
  w.E = pi0.E + m.E[0] + m.E[1];
  w.Px = pi0.Px + m.Px[0] + m.Px[1];
  w.Py = pi0.Py + m.Py[0] + m.Py[1];
  w.Pz = pi0.Pz + m.Pz[0] + m.Pz[1];
  w.P = TMath::Sqrt(w.Px * w.Px + w.Py * w.Py + w.Pz * w.Pz);
  w.M = TMath::Sqrt(w.E * w.E - w.P * w.P);
  w.D = w.M - pi0.M + kMassPiZero;
  w.Z = w.E / m.Nu;
  w.PhiPQ = PhiPQ(m.Pex, m.Pey, m.Pez, w.Px, w.Py, w.Pz);
  w.ThetaPQ = ThetaPQ(m.Pex, m.Pey, m.Pez, w.Px, w.Py, w.Pz);
  Double_t fCosThetaPQ = ((kEbeam - m.Pez) * w.Pz - m.Pex * w.Px - m.Pey * w.Py) / (TMath::Sqrt(w.P * w.P * (m.Q2 + m.Nu * m.Nu)));
  w.PhiLab = PhiLab(w.Px, w.Py, w.Pz);
  w.ThetaLab = ThetaLab(w.Px, w.Py, w.Pz);
  w.Pt2 = w.P * w.P * (1 - fCosThetaPQ * fCosThetaPQ);
  w.Pl2 = w.P * w.P * fCosThetaPQ * fCosThetaPQ;
  w.Mx2 = m.W * m.W + w.M * w.M - 2 * w.Z * m.Nu * m.Nu + 2 * TMath::Sqrt(w.Pl2 * (m.Nu * m.Nu + m.Q2)) - 2 * kMassProton * w.Z * m.Nu;
}

void AssignMixVar_GEN(gen_i& mc_t, gen_m& mc_m, Int_t entry, Int_t index) {
  // electron (16)
  mc_m.Q2 = mc_t.Q2;
  mc_m.W = mc_t.W;
  mc_m.Nu = mc_t.Nu;
  mc_m.Xb = mc_t.Xb;
  mc_m.Yb = mc_t.Yb;
  mc_m.Xe = mc_t.vxe;
  mc_m.Ye = mc_t.vye;
  mc_m.Ze = mc_t.vze;
  mc_m.SectorEl = mc_t.SectorEl;
  mc_m.TargType = mc_t.TargType;
  mc_m.Pex = mc_t.Pex;
  mc_m.Pey = mc_t.Pey;
  mc_m.Pez = mc_t.Pez;
  mc_m.BettaEl = mc_t.BettaEl;
  mc_m.PhiLabEl = PhiLab(mc_t.Pex, mc_t.Pey, mc_t.Pez);
  mc_m.ThetaLabEl = ThetaLab(mc_t.Pex, mc_t.Pey, mc_t.Pez);
  // particle (21)
  mc_m.vxh[index] = mc_t.vxh;
  mc_m.vyh[index] = mc_t.vyh;
  mc_m.vzh[index] = mc_t.vzh;
  mc_m.Sector[index] = mc_t.Sector;
  mc_m.Betta[index] = mc_t.Betta;
  mc_m.Mass2[index] = mc_t.Mass2;
  mc_m.Pid[index] = mc_t.pid;
  mc_m.Px[index] = mc_t.Px;
  mc_m.Py[index] = mc_t.Py;
  mc_m.Pz[index] = mc_t.Pz;
  mc_m.E[index] = mc_t.Eh;
  mc_m.Z[index] = mc_t.Zh;
  mc_m.Pt2[index] = mc_t.Pt2;
  mc_m.Pl2[index] = mc_t.Pl2;
  mc_m.PhiPQ[index] = mc_t.PhiPQ;
  mc_m.ThetaPQ[index] = mc_t.ThetaPQ;
  mc_m.Mx2[index] = mc_t.Mx2;
  mc_m.PhiLab[index] = mc_t.PhiLab;
  mc_m.ThetaLab[index] = mc_t.ThetaLab;
  mc_m.deltaZ[index] = mc_t.deltaZ;
  mc_m.deltaTheta[index] = DeltaTheta(mc_t.Pex, mc_t.Pey, mc_t.Pez, mc_t.Px, mc_t.Py, mc_t.Pz);
  // event-related (1)
  mc_m.Entry[index] = entry;
}

void AssignMoreVar_GEN(gen_m& mc_m, Int_t nMCPipThisEvent, Int_t nMCPimThisEvent, Int_t nMCGammaThisEvent, Int_t cIndex) {
  // number of particles (4)
  mc_m.nPip = nMCPipThisEvent;
  mc_m.nPim = nMCPimThisEvent;
  mc_m.nGamma = nMCGammaThisEvent;
  mc_m.cIndex = cIndex;
}

void AssignPi0Var_GEN(gen_m& mc_m, gen_pi0& mc_pi0) {
  // pi0 (6)
  mc_pi0.E = mc_m.E[2] + mc_m.E[3];
  mc_pi0.Px = mc_m.Px[2] + mc_m.Px[3];
  mc_pi0.Py = mc_m.Py[2] + mc_m.Py[3];
  mc_pi0.Pz = mc_m.Pz[2] + mc_m.Pz[3];
  Double_t fP = TMath::Sqrt(mc_pi0.Px * mc_pi0.Px + mc_pi0.Py * mc_pi0.Py + mc_pi0.Pz * mc_pi0.Pz);
  mc_pi0.M = TMath::Sqrt(mc_pi0.E * mc_pi0.E - fP * fP);
  Double_t fDot = mc_m.Px[2] * mc_m.Px[3] + mc_m.Py[2] * mc_m.Py[3] + mc_m.Pz[2] * mc_m.Pz[3];
  Double_t fMag0 = TMath::Sqrt(mc_m.Px[2] * mc_m.Px[2] + mc_m.Py[2] * mc_m.Py[2] + mc_m.Pz[2] * mc_m.Pz[2]);
  Double_t fMag1 = TMath::Sqrt(mc_m.Px[3] * mc_m.Px[3] + mc_m.Py[3] * mc_m.Py[3] + mc_m.Pz[3] * mc_m.Pz[3]);
  mc_pi0.Theta = TMath::RadToDeg() * TMath::ACos(fDot / (fMag0 * fMag1));
}

void AssignOmegaVar_GEN(gen_m& mc_m, gen_pi0& mc_pi0, gen_w& mc_w) {
  // omega (15)
  mc_w.E = mc_pi0.E + mc_m.E[0] + mc_m.E[1];
  mc_w.Px = mc_pi0.Px + mc_m.Px[0] + mc_m.Px[1];
  mc_w.Py = mc_pi0.Py + mc_m.Py[0] + mc_m.Py[1];
  mc_w.Pz = mc_pi0.Pz + mc_m.Pz[0] + mc_m.Pz[1];
  mc_w.P = TMath::Sqrt(mc_w.Px * mc_w.Px + mc_w.Py * mc_w.Py + mc_w.Pz * mc_w.Pz);
  mc_w.M = TMath::Sqrt(mc_w.E * mc_w.E - mc_w.P * mc_w.P);
  mc_w.D = mc_w.M - mc_pi0.M + kMassPiZero;
  mc_w.Z = mc_w.E / mc_m.Nu;
  mc_w.PhiPQ = PhiPQ(mc_m.Pex, mc_m.Pey, mc_m.Pez, mc_w.Px, mc_w.Py, mc_w.Pz);
  mc_w.ThetaPQ = ThetaPQ(mc_m.Pex, mc_m.Pey, mc_m.Pez, mc_w.Px, mc_w.Py, mc_w.Pz);
  Double_t fCosThetaPQ = ((kEbeam - mc_m.Pez) * mc_w.Pz - mc_m.Pex * mc_w.Px - mc_m.Pey * mc_w.Py) / (TMath::Sqrt(mc_w.P * mc_w.P * (mc_m.Q2 + mc_m.Nu * mc_m.Nu)));
  mc_w.PhiLab = PhiLab(mc_w.Px, mc_w.Py, mc_w.Pz);
  mc_w.ThetaLab = ThetaLab(mc_w.Px, mc_w.Py, mc_w.Pz);
  mc_w.Pt2 = mc_w.P * mc_w.P * (1 - fCosThetaPQ * fCosThetaPQ);
  mc_w.Pl2 = mc_w.P * mc_w.P * fCosThetaPQ * fCosThetaPQ;
  mc_w.Mx2 = mc_m.W * mc_m.W + mc_w.M * mc_w.M - 2 * mc_w.Z * mc_m.Nu * mc_m.Nu + 2 * TMath::Sqrt(mc_w.Pl2 * (mc_m.Nu * mc_m.Nu + mc_m.Q2)) - 2 * kMassProton * mc_w.Z * mc_m.Nu;
}

#endif
