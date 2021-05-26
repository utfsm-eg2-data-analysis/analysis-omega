#ifndef TREEOPS_HXX
#define TREEOPS_HXX

#include "Headers.hxx"
#include "Math.hxx"
#include "PDG.hxx"

#include "2GFtree.h"

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

void SetMixBranches_REC(TTree *tree, rec_m& m, rec_eta& eta) {
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
  tree->Branch("vxh", &m.vxh, "vxh[2]/F");
  tree->Branch("vyh", &m.vyh, "vyh[2]/F");
  tree->Branch("vzh", &m.vzh, "vzh[2]/F");
  tree->Branch("Sector", &m.Sector, "Sector[2]/F");
  tree->Branch("Betta", &m.Betta, "Betta[2]/F");
  tree->Branch("Mass2", &m.Mass2, "Mass2[2]/F");
  tree->Branch("Pid", &m.Pid, "Pid[2]/F");
  tree->Branch("T4", &m.T4, "T4[2]/F");
  tree->Branch("Px", &m.Px, "Px[2]/F");
  tree->Branch("Py", &m.Py, "Py[2]/F");
  tree->Branch("Pz", &m.Pz, "Pz[2]/F");
  tree->Branch("E", &m.E, "E[2]/F");  
  tree->Branch("Z", &m.Z, "Z[2]/F");
  tree->Branch("PhiPQ", &m.PhiPQ, "PhiPQ[2]/F");
  tree->Branch("ThetaPQ", &m.ThetaPQ, "ThetaPQ[2]/F");
  tree->Branch("PhiLab", &m.PhiLab, "PhiLab[2]/F");
  tree->Branch("ThetaLab", &m.ThetaLab, "ThetaLab[2]/F");
  tree->Branch("Pt2", &m.Pt2, "Pt2[2]/F");
  tree->Branch("Pl2", &m.Pl2, "Pl2[2]/F");
  tree->Branch("Mx2", &m.Mx2, "Mx2[2]/F");
  tree->Branch("deltaTheta", &m.deltaTheta, "deltaTheta[2]/F");  
  tree->Branch("deltaZ", &m.deltaZ, "deltaZ[2]/F");
  tree->Branch("TruePid", &m.TruePid, "TruePid[2]/F");
  // eta (15)
  tree->Branch("ePx", &eta.Px);
  tree->Branch("ePy", &eta.Py);
  tree->Branch("ePz", &eta.Pz);
  tree->Branch("eP", &eta.P);
  tree->Branch("eE", &eta.E);
  tree->Branch("eM", &eta.M);
  tree->Branch("eTheta", &eta.Theta);
  tree->Branch("eZ", &eta.Z);
  tree->Branch("eThetaPQ", &eta.ThetaPQ);
  tree->Branch("ePhiPQ", &eta.PhiPQ);
  tree->Branch("ePt2", &eta.Pt2);
  tree->Branch("ePl2", &eta.Pl2);
  tree->Branch("eMx2", &eta.Mx2);
  tree->Branch("eThetaLab", &eta.ThetaLab);
  tree->Branch("ePhiLab", &eta.PhiLab);
  // number of particles in that event (2)
  tree->Branch("nGamma", &m.nGamma);
  tree->Branch("cIndex", &m.cIndex);
  // event related (2)
  tree->Branch("Entry", &m.Entry, "Entry[2]/F");
  tree->Branch("Event", &m.Event);
}

void SetMixBranches_GEN(TTree* tree, gen_m& mc_m, gen_eta& mc_eta) {
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
  tree->Branch("mc_vxh", &mc_m.vxh, "mc_vxh[2]/F");
  tree->Branch("mc_vyh", &mc_m.vyh, "mc_vyh[2]/F");
  tree->Branch("mc_vzh", &mc_m.vzh, "mc_vzh[2]/F");
  tree->Branch("mc_Sector", &mc_m.Sector, "mc_Sector[2]/F");
  tree->Branch("mc_Betta", &mc_m.Betta, "mc_Betta[2]/F");
  tree->Branch("mc_Mass2", &mc_m.Mass2, "mc_Mass2[2]/F");
  tree->Branch("mc_Pid", &mc_m.Pid, "mc_Pid[2]/F");
  tree->Branch("mc_E", &mc_m.E, "mc_E[2]/F");
  tree->Branch("mc_Px", &mc_m.Px, "mc_Px[2]/F");
  tree->Branch("mc_Py", &mc_m.Py, "mc_Py[2]/F");
  tree->Branch("mc_Pz", &mc_m.Pz, "mc_Pz[2]/F");
  tree->Branch("mc_Z", &mc_m.Z, "mc_Z[2]/F");
  tree->Branch("mc_Pt2", &mc_m.Pt2, "mc_Pt2[2]/F");
  tree->Branch("mc_Pl2", &mc_m.Pl2, "mc_Pl2[2]/F");
  tree->Branch("mc_PhiPQ", &mc_m.PhiPQ, "mc_PhiPQ[2]/F");
  tree->Branch("mc_ThetaPQ", &mc_m.ThetaPQ, "mc_ThetaPQ[2]/F");
  tree->Branch("mc_PhiLab", &mc_m.PhiLab, "mc_PhiLab[2]/F");
  tree->Branch("mc_ThetaLab", &mc_m.ThetaLab, "mc_ThetaLab[2]/F");
  tree->Branch("mc_Mx2", &mc_m.Mx2, "mc_Mx2[2]/F");
  tree->Branch("mc_deltaZ", &mc_m.deltaZ, "mc_deltaZ[2]/F");
  tree->Branch("mc_deltaTheta", &mc_m.deltaTheta, "mc_deltaTheta[2]/F");
  // eta (15)
  tree->Branch("mc_ePx", &mc_eta.Px);
  tree->Branch("mc_ePy", &mc_eta.Py);
  tree->Branch("mc_ePz", &mc_eta.Pz);
  tree->Branch("mc_eP", &mc_eta.P);
  tree->Branch("mc_eE", &mc_eta.E);
  tree->Branch("mc_eM", &mc_eta.M);
  tree->Branch("mc_eTheta", &mc_eta.Theta);
  tree->Branch("mc_eZ", &mc_eta.Z);
  tree->Branch("mc_eThetaPQ", &mc_eta.ThetaPQ);
  tree->Branch("mc_ePhiPQ", &mc_eta.PhiPQ);
  tree->Branch("mc_ePt2", &mc_eta.Pt2);
  tree->Branch("mc_ePl2", &mc_eta.Pl2);
  tree->Branch("mc_eMx2", &mc_eta.Mx2);
  tree->Branch("mc_eThetaLab", &mc_eta.ThetaLab);
  tree->Branch("mc_ePhiLab", &mc_eta.PhiLab);
  // number of particles (2)
  tree->Branch("mc_nGamma", &mc_m.nGamma);
  tree->Branch("mc_cIndex", &mc_m.cIndex);
  // event related (1)
  tree->Branch("mc_Entry", &mc_m.Entry, "mc_Entry[2]/F");
}

void NullMixVar_REC(rec_m& m, rec_eta& eta) {
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
  for (Int_t index = 0; index < 2; index++) {
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
  // eta (15)
  eta.Px = INVLD;
  eta.Py = INVLD;
  eta.Pz = INVLD;
  eta.P = INVLD;
  eta.M  = INVLD;
  eta.E  = INVLD;
  eta.Theta = INVLD;
  eta.Z = INVLD;
  eta.ThetaPQ = INVLD;
  eta.PhiPQ = INVLD;
  eta.Pt2 = INVLD;
  eta.Pl2 = INVLD;
  eta.Mx2 = INVLD;
  eta.ThetaLab = INVLD;
  eta.PhiLab = INVLD;
  // number of particles (2)
  m.nGamma   = INVLD;
  m.cIndex = INVLD;
}

void NullMixVar_GEN(gen_m& mc_m, gen_eta& mc_eta) {
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
  for (Int_t index = 0; index < 2; index++) {
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
  // number of particles (2)
  mc_m.nGamma = INVLD;
  mc_m.cIndex = INVLD;
  // eta (15)
  mc_eta.Px = INVLD;
  mc_eta.Py = INVLD;
  mc_eta.Pz = INVLD;
  mc_eta.P = INVLD;
  mc_eta.E = INVLD;
  mc_eta.M = INVLD;
  mc_eta.Theta = INVLD; // opening angle between 2 gammas
  mc_eta.Z = INVLD;
  mc_eta.ThetaPQ = INVLD;
  mc_eta.PhiPQ = INVLD;
  mc_eta.Pt2 = INVLD;
  mc_eta.Pl2 = INVLD;
  mc_eta.Mx2 = INVLD;
  mc_eta.ThetaLab = INVLD;
  mc_eta.PhiLab = INVLD;
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

void AssignMoreVar_REC(rec_m& m, Int_t nGammaThisEvent, Int_t cIndex) {
  // number of particles (2)
  m.nGamma = nGammaThisEvent;
  m.cIndex = (Float_t) cIndex;
}

void AssignEtaVar_REC(rec_m& m, rec_eta& eta) {
  // eta (15)
  eta.E = m.E[0] + m.E[1];
  eta.Px = m.Px[0] + m.Px[1];
  eta.Py = m.Py[0] + m.Py[1];
  eta.Pz = m.Pz[0] + m.Pz[1];
  Double_t fP = TMath::Sqrt(eta.Px * eta.Px + eta.Py * eta.Py + eta.Pz * eta.Pz);
  eta.P = fP;
  eta.M = TMath::Sqrt(eta.E * eta.E - fP * fP);
  Double_t fDot = m.Px[0] * m.Px[1] + m.Py[0] * m.Py[1] + m.Pz[0] * m.Pz[1];
  Double_t fMag0 = TMath::Sqrt(m.Px[0] * m.Px[0] + m.Py[0] * m.Py[0] + m.Pz[0] * m.Pz[0]);
  Double_t fMag1 = TMath::Sqrt(m.Px[1] * m.Px[1] + m.Py[1] * m.Py[1] + m.Pz[1] * m.Pz[1]);
  eta.Theta = TMath::RadToDeg() * TMath::ACos(fDot / (fMag0 * fMag1));
  eta.Z = eta.E / m.Nu;
  eta.PhiPQ = PhiPQ(m.Pex, m.Pey, m.Pez, eta.Px, eta.Py, eta.Pz);
  eta.ThetaPQ = ThetaPQ(m.Pex, m.Pey, m.Pez, eta.Px, eta.Py, eta.Pz);
  Double_t fCosThetaPQ = ((kEbeam - m.Pez) * eta.Pz - m.Pex * eta.Px - m.Pey * eta.Py) / (TMath::Sqrt(fP * fP * (m.Q2 + m.Nu * m.Nu)));
  eta.PhiLab = PhiLab(eta.Px, eta.Py, eta.Pz);
  eta.ThetaLab = ThetaLab(eta.Px, eta.Py, eta.Pz);
  eta.Pt2 = fP * fP * (1 - fCosThetaPQ * fCosThetaPQ);
  eta.Pl2 = fP * fP * fCosThetaPQ * fCosThetaPQ;
  eta.Mx2 = m.W * m.W + eta.M * eta.M - 2 * eta.Z * m.Nu * m.Nu + 2 * TMath::Sqrt(eta.Pl2 * (m.Nu * m.Nu + m.Q2)) - 2 * kMassProton * eta.Z * m.Nu;
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

void AssignMoreVar_GEN(gen_m& mc_m, Int_t nMCGammaThisEvent, Int_t cIndex) {
  // number of particles (2)
  mc_m.nGamma = nMCGammaThisEvent;
  mc_m.cIndex = cIndex;
}

void AssignEtaVar_GEN(gen_m& mc_m, gen_eta& mc_eta) {
  // eta (15)
  mc_eta.E = mc_m.E[0] + mc_m.E[1];
  mc_eta.Px = mc_m.Px[0] + mc_m.Px[1];
  mc_eta.Py = mc_m.Py[0] + mc_m.Py[1];
  mc_eta.Pz = mc_m.Pz[0] + mc_m.Pz[1];
  Double_t fP = TMath::Sqrt(mc_eta.Px * mc_eta.Px + mc_eta.Py * mc_eta.Py + mc_eta.Pz * mc_eta.Pz);
  mc_eta.P = fP;
  mc_eta.M = TMath::Sqrt(mc_eta.E * mc_eta.E - fP * fP);
  Double_t fDot = mc_m.Px[0] * mc_m.Px[1] + mc_m.Py[0] * mc_m.Py[1] + mc_m.Pz[0] * mc_m.Pz[1];
  Double_t fMag0 = TMath::Sqrt(mc_m.Px[0] * mc_m.Px[0] + mc_m.Py[0] * mc_m.Py[0] + mc_m.Pz[0] * mc_m.Pz[0]);
  Double_t fMag1 = TMath::Sqrt(mc_m.Px[1] * mc_m.Px[1] + mc_m.Py[1] * mc_m.Py[1] + mc_m.Pz[1] * mc_m.Pz[1]);
  mc_eta.Theta = TMath::RadToDeg() * TMath::ACos(fDot / (fMag0 * fMag1));
  mc_eta.Z = mc_eta.E / mc_m.Nu;
  mc_eta.PhiPQ = PhiPQ(mc_m.Pex, mc_m.Pey, mc_m.Pez, mc_eta.Px, mc_eta.Py, mc_eta.Pz);
  mc_eta.ThetaPQ = ThetaPQ(mc_m.Pex, mc_m.Pey, mc_m.Pez, mc_eta.Px, mc_eta.Py, mc_eta.Pz);
  Double_t fCosThetaPQ = ((kEbeam - mc_m.Pez) * mc_eta.Pz - mc_m.Pex * mc_eta.Px - mc_m.Pey * mc_eta.Py) / (TMath::Sqrt(fP* fP* (mc_m.Q2 + mc_m.Nu * mc_m.Nu)));
  mc_eta.PhiLab = PhiLab(mc_eta.Px, mc_eta.Py, mc_eta.Pz);
  mc_eta.ThetaLab = ThetaLab(mc_eta.Px, mc_eta.Py, mc_eta.Pz);
  mc_eta.Pt2 = fP* fP* (1 - fCosThetaPQ * fCosThetaPQ);
  mc_eta.Pl2 = fP* fP* fCosThetaPQ * fCosThetaPQ;
  mc_eta.Mx2 = mc_m.W * mc_m.W + mc_eta.M * mc_eta.M - 2 * mc_eta.Z * mc_m.Nu * mc_m.Nu + 2 * TMath::Sqrt(mc_eta.Pl2 * (mc_m.Nu * mc_m.Nu + mc_m.Q2)) - 2 * kMassProton * mc_eta.Z * mc_m.Nu;
}

#endif
