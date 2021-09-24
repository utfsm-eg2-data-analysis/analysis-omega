#ifndef TREEOPS_HXX
#define TREEOPS_HXX

#include "Headers.hxx"
#include "Math.hxx"
#include "PDG.hxx"

#include "GSTtree.h"

#include "3PFtree.h"

#ifndef INVLD
#define INVLD -9999
#endif

void SetInputTree_REC(TTree* tree, elec_t& elec, part_t& part) {
  // electron (16 vars)
  tree->SetBranchAddress("Q2", &elec.Q2);
  tree->SetBranchAddress("W", &elec.W);
  tree->SetBranchAddress("Nu", &elec.Nu);
  tree->SetBranchAddress("Xb", &elec.Xb);
  tree->SetBranchAddress("Yb", &elec.Yb);
  tree->SetBranchAddress("Pex", &elec.Px);
  tree->SetBranchAddress("Pey", &elec.Py);
  tree->SetBranchAddress("Pez", &elec.Pz);
  tree->SetBranchAddress("Pe", &elec.P);
  tree->SetBranchAddress("vxec", &elec.vxc);
  tree->SetBranchAddress("vyec", &elec.vyc);
  tree->SetBranchAddress("vzec", &elec.vzc);
  tree->SetBranchAddress("TargType", &elec.TargType);
  tree->SetBranchAddress("PhiLabEl", &elec.PhiLab);
  tree->SetBranchAddress("ThetaLabEl", &elec.ThetaLab);
  tree->SetBranchAddress("SectorEl", &elec.Sector);
  // event (1 var)
  tree->SetBranchAddress("evnt", &elec.evnt);
  // particles (14 vars)
  tree->SetBranchAddress("Eh", &part.Eh);
  tree->SetBranchAddress("Zh", &part.Zh);
  tree->SetBranchAddress("Px", &part.Px);
  tree->SetBranchAddress("Py", &part.Py);
  tree->SetBranchAddress("Pz", &part.Pz);
  tree->SetBranchAddress("P", &part.P);
  tree->SetBranchAddress("ThetaPQ", &part.ThetaPQ);
  tree->SetBranchAddress("PhiPQ", &part.PhiPQ);
  tree->SetBranchAddress("Pt2", &part.Pt2);
  tree->SetBranchAddress("Pl2", &part.Pl2);
  tree->SetBranchAddress("ThetaLab", &part.ThetaLab);
  tree->SetBranchAddress("PhiLab", &part.PhiLab);
  tree->SetBranchAddress("deltaZ", &part.deltaZ);
  tree->SetBranchAddress("pid", &part.pid);
}

void SetOutputTree_REC(TTree* tree, stable_t& stable, pi0_t& pi0, omega_t& omega) {
  // electron (16)
  tree->Branch("Q2", &stable.Q2);
  tree->Branch("W", &stable.W);
  tree->Branch("Nu", &stable.Nu);
  tree->Branch("Xb", &stable.Xb);
  tree->Branch("Yb", &stable.Yb);
  tree->Branch("Pex", &stable.Pex);
  tree->Branch("Pey", &stable.Pey);
  tree->Branch("Pez", &stable.Pez);
  tree->Branch("Pe", &stable.Pe);
  tree->Branch("Xec", &stable.Xec);
  tree->Branch("Yec", &stable.Yec);
  tree->Branch("Zec", &stable.Zec);
  tree->Branch("TargType", &stable.TargType);
  tree->Branch("PhiLabEl", &stable.PhiLabEl);
  tree->Branch("ThetaLabEl", &stable.ThetaLabEl);
  tree->Branch("SectorEl", &stable.SectorEl);
  // event related (2 vars)
  tree->Branch("Entry", &stable.Entry, "Entry[4]/F");
  tree->Branch("Event", &stable.Event);
  // particles (14 vars)
  tree->Branch("E", &stable.E, "E[4]/F");
  tree->Branch("Z", &stable.Z, "Z[4]/F");
  tree->Branch("Px", &stable.Px, "Px[4]/F");
  tree->Branch("Py", &stable.Py, "Py[4]/F");
  tree->Branch("Pz", &stable.Pz, "Pz[4]/F");
  tree->Branch("P", &stable.P, "P[4]/F");
  tree->Branch("PhiPQ", &stable.PhiPQ, "PhiPQ[4]/F");
  tree->Branch("ThetaPQ", &stable.ThetaPQ, "ThetaPQ[4]/F");
  tree->Branch("Pt2", &stable.Pt2, "Pt2[4]/F");
  tree->Branch("Pl2", &stable.Pl2, "Pl2[4]/F");
  tree->Branch("PhiLab", &stable.PhiLab, "PhiLab[4]/F");
  tree->Branch("ThetaLab", &stable.ThetaLab, "ThetaLab[4]/F");
  tree->Branch("deltaZ", &stable.deltaZ, "deltaZ[4]/F");
  tree->Branch("Pid", &stable.Pid, "Pid[4]/F");
  // pi0 (7 vars)
  tree->Branch("pi0Px", &pi0.Px);
  tree->Branch("pi0Py", &pi0.Py);
  tree->Branch("pi0Pz", &pi0.Pz);
  tree->Branch("pi0P", &pi0.P);
  tree->Branch("pi0E", &pi0.E);
  tree->Branch("pi0M", &pi0.M);
  tree->Branch("pi0Theta", &pi0.Theta);
  // omega (14 vars)
  tree->Branch("wPx", &omega.Px);
  tree->Branch("wPy", &omega.Py);
  tree->Branch("wPz", &omega.Pz);
  tree->Branch("wP", &omega.P);
  tree->Branch("wE", &omega.E);
  tree->Branch("wM", &omega.M);
  tree->Branch("wZ", &omega.Z);
  tree->Branch("wD", &omega.D);
  tree->Branch("wPhiLab", &omega.PhiLab);
  tree->Branch("wThetaLab", &omega.ThetaLab);
  tree->Branch("wPhiPQ", &omega.PhiPQ);
  tree->Branch("wThetaPQ", &omega.ThetaPQ);
  tree->Branch("wPt2", &omega.Pt2);
  tree->Branch("wPl2", &omega.Pl2);
}

void WriteStableVars_REC(elec_t& elec, part_t& part, stable_t& stable, Int_t entry, Int_t index) {
  // electron (19)
  stable.Q2 = elec.Q2;
  stable.W = elec.W;
  stable.Nu = elec.Nu;
  stable.Xb = elec.Xb;
  stable.Yb = elec.Yb;
  stable.Pex = elec.Px;
  stable.Pey = elec.Py;
  stable.Pez = elec.Pz;
  stable.Pe = elec.P;
  stable.Xec = elec.vxc;
  stable.Yec = elec.vyc;
  stable.Zec = elec.vzc;
  stable.TargType = elec.TargType;
  stable.PhiLabEl = PhiLab(elec.Px, elec.Py, elec.Pz);
  stable.ThetaLabEl = ThetaLab(elec.Px, elec.Py, elec.Pz);
  stable.SectorEl = elec.Sector;
  // event-related (2)
  stable.Entry[index] = (Float_t)entry;
  stable.Event = elec.evnt;
  // particles (22)
  TLorentzVector* fGamma = GetCorrPhotonEnergy(part);
  stable.E[index] = (part.pid == 22) * fGamma->E() + (part.pid != 22) * part.Eh;
  stable.Z[index] = stable.E[index] / stable.Nu;
  stable.Px[index] = (part.pid == 22) * fGamma->Px() + (part.pid != 22) * part.Px;
  stable.Py[index] = (part.pid == 22) * fGamma->Py() + (part.pid != 22) * part.Py;
  stable.Pz[index] = (part.pid == 22) * fGamma->Pz() + (part.pid != 22) * part.Pz;
  stable.P[index] = (part.pid == 22) * fGamma->P() + (part.pid != 22) * part.P;
  stable.ThetaPQ[index] = ThetaPQ(stable.Pex, stable.Pey, stable.Pez, stable.Px[index], stable.Py[index], stable.Pz[index]);
  stable.PhiPQ[index] = PhiPQ(stable.Pex, stable.Pey, stable.Pez, stable.Px[index], stable.Py[index], stable.Pz[index]);
  Double_t fCosThetaPQ = ((kEbeam - stable.Pez) * stable.Pz[index] - stable.Pex * stable.Px[index] - stable.Pey * stable.Py[index]) /
                         (TMath::Sqrt(stable.P[index] * stable.P[index] * (stable.Q2 + stable.Nu * stable.Nu)));
  stable.Pt2[index] = stable.P[index] * stable.P[index] * (1 - fCosThetaPQ * fCosThetaPQ);
  stable.Pl2[index] = stable.P[index] * stable.P[index] * fCosThetaPQ * fCosThetaPQ;
  stable.ThetaLab[index] = ThetaLab(stable.Px[index], stable.Py[index], stable.Pz[index]);
  stable.PhiLab[index] = PhiLab(stable.Px[index], stable.Py[index], stable.Pz[index]);
  stable.deltaZ[index] = part.deltaZ;
  stable.Pid[index] = part.pid;  // important!
}

void WritePi0Vars(stable_t& stable, pi0_t& pi0) {
  // pi0 (7 vars)
  pi0.E = stable.E[2] + stable.E[3];
  pi0.Px = stable.Px[2] + stable.Px[3];
  pi0.Py = stable.Py[2] + stable.Py[3];
  pi0.Pz = stable.Pz[2] + stable.Pz[3];
  pi0.P = TMath::Sqrt(pi0.Px * pi0.Px + pi0.Py * pi0.Py + pi0.Pz * pi0.Pz);
  pi0.M = TMath::Sqrt(pi0.E * pi0.E - pi0.P * pi0.P);
  Double_t fDot = stable.Px[2] * stable.Px[3] + stable.Py[2] * stable.Py[3] + stable.Pz[2] * stable.Pz[3];
  Double_t fMag0 = TMath::Sqrt(stable.Px[2] * stable.Px[2] + stable.Py[2] * stable.Py[2] + stable.Pz[2] * stable.Pz[2]);
  Double_t fMag1 = TMath::Sqrt(stable.Px[3] * stable.Px[3] + stable.Py[3] * stable.Py[3] + stable.Pz[3] * stable.Pz[3]);
  pi0.Theta = TMath::RadToDeg() * TMath::ACos(fDot / (fMag0 * fMag1));
}

void WriteOmegaVars(stable_t& stable, pi0_t& pi0, omega_t& omega) {
  // omega (15)
  omega.E = pi0.E + stable.E[0] + stable.E[1];
  omega.Px = pi0.Px + stable.Px[0] + stable.Px[1];
  omega.Py = pi0.Py + stable.Py[0] + stable.Py[1];
  omega.Pz = pi0.Pz + stable.Pz[0] + stable.Pz[1];
  omega.P = TMath::Sqrt(omega.Px * omega.Px + omega.Py * omega.Py + omega.Pz * omega.Pz);
  omega.M = TMath::Sqrt(omega.E * omega.E - omega.P * omega.P);
  omega.D = omega.M - pi0.M + kMassPiZero;
  omega.Z = omega.E / stable.Nu;
  omega.ThetaPQ = ThetaPQ(stable.Pex, stable.Pey, stable.Pez, omega.Px, omega.Py, omega.Pz);
  omega.PhiPQ = PhiPQ(stable.Pex, stable.Pey, stable.Pez, omega.Px, omega.Py, omega.Pz);
  Double_t fCosThetaPQ = ((kEbeam - stable.Pez) * omega.Pz - stable.Pex * omega.Px - stable.Pey * omega.Py) /
                         (TMath::Sqrt(omega.P * omega.P * (stable.Q2 + stable.Nu * stable.Nu)));
  omega.Pt2 = omega.P * omega.P * (1 - fCosThetaPQ * fCosThetaPQ);
  omega.Pl2 = omega.P * omega.P * fCosThetaPQ * fCosThetaPQ;
  omega.ThetaLab = ThetaLab(omega.Px, omega.Py, omega.Pz);
  omega.PhiLab = PhiLab(omega.Px, omega.Py, omega.Pz);
}

void SetInputTree_GEN(TTree* tree, elec_t& elec, part_t& part) {
  // electron (16 vars)
  tree->SetBranchAddress("mc_Q2", &elec.Q2);
  tree->SetBranchAddress("mc_W", &elec.W);
  tree->SetBranchAddress("mc_Nu", &elec.Nu);
  tree->SetBranchAddress("mc_Xb", &elec.Xb);
  tree->SetBranchAddress("mc_Yb", &elec.Yb);
  tree->SetBranchAddress("mc_Pex", &elec.Px);
  tree->SetBranchAddress("mc_Pey", &elec.Py);
  tree->SetBranchAddress("mc_Pez", &elec.Pz);
  tree->SetBranchAddress("mc_Pe", &elec.P);
  tree->SetBranchAddress("mc_vxe", &elec.vx);
  tree->SetBranchAddress("mc_vye", &elec.vy);
  tree->SetBranchAddress("mc_vze", &elec.vz);
  tree->SetBranchAddress("mc_TargType", &elec.TargType);
  tree->SetBranchAddress("mc_PhiLabEl", &elec.PhiLab);
  tree->SetBranchAddress("mc_ThetaLabEl", &elec.ThetaLab);
  tree->SetBranchAddress("mc_SectorEl", &elec.Sector);
  // particles (15 vars)
  tree->SetBranchAddress("mc_Eh", &part.Eh);
  tree->SetBranchAddress("mc_Zh", &part.Zh);
  tree->SetBranchAddress("mc_Px", &part.Px);
  tree->SetBranchAddress("mc_Py", &part.Py);
  tree->SetBranchAddress("mc_Pz", &part.Pz);
  tree->SetBranchAddress("mc_P", &part.P);
  tree->SetBranchAddress("mc_PhiPQ", &part.PhiPQ);
  tree->SetBranchAddress("mc_ThetaPQ", &part.ThetaPQ);
  tree->SetBranchAddress("mc_Pt2", &part.Pt2);
  tree->SetBranchAddress("mc_Pl2", &part.Pl2);
  tree->SetBranchAddress("mc_ThetaLab", &part.ThetaLab);
  tree->SetBranchAddress("mc_PhiLab", &part.PhiLab);
  tree->SetBranchAddress("mc_deltaZ", &part.deltaZ);
  tree->SetBranchAddress("mc_pid", &part.pid);
  tree->SetBranchAddress("mc_ParentID", &part.ParentID);  // extra!
}

void SetOutputTree_GEN(TTree* tree, stable_t& stable, pi0_t& pi0, omega_t& omega) {
  // electron (13 vars)
  tree->Branch("mc_Q2", &stable.Q2);
  tree->Branch("mc_W", &stable.W);
  tree->Branch("mc_Nu", &stable.Nu);
  tree->Branch("mc_Xb", &stable.Xb);
  tree->Branch("mc_Yb", &stable.Yb);
  tree->Branch("mc_Pex", &stable.Pex);
  tree->Branch("mc_Pey", &stable.Pey);
  tree->Branch("mc_Pez", &stable.Pez);
  tree->Branch("mc_Pe", &stable.Pe);
  tree->Branch("mc_TargType", &stable.TargType);
  tree->Branch("mc_PhiLabEl", &stable.PhiLabEl);
  tree->Branch("mc_ThetaLabEl", &stable.ThetaLabEl);
  tree->Branch("mc_SectorEl", &stable.SectorEl);
  // particle (15 vars)
  tree->Branch("mc_E", &stable.E, "mc_E[4]/F");
  tree->Branch("mc_Z", &stable.Z, "mc_Z[4]/F");
  tree->Branch("mc_Px", &stable.Px, "mc_Px[4]/F");
  tree->Branch("mc_Py", &stable.Py, "mc_Py[4]/F");
  tree->Branch("mc_Pz", &stable.Pz, "mc_Pz[4]/F");
  tree->Branch("mc_P", &stable.P, "mc_P[4]/F");
  tree->Branch("mc_PhiPQ", &stable.PhiPQ, "mc_PhiPQ[4]/F");
  tree->Branch("mc_ThetaPQ", &stable.ThetaPQ, "mc_ThetaPQ[4]/F");
  tree->Branch("mc_Pt2", &stable.Pt2, "mc_Pt2[4]/F");
  tree->Branch("mc_Pl2", &stable.Pl2, "mc_Pl2[4]/F");
  tree->Branch("mc_PhiLab", &stable.PhiLab, "mc_PhiLab[4]/F");
  tree->Branch("mc_ThetaLab", &stable.ThetaLab, "mc_ThetaLab[4]/F");
  tree->Branch("mc_deltaZ", &stable.deltaZ, "mc_deltaZ[4]/F");
  tree->Branch("mc_Pid", &stable.Pid, "mc_Pid[4]/F");
  tree->Branch("mc_ParentID", &stable.ParentID, "mc_ParentID[4]/F");  // extra!
  // event-related (1 var)
  tree->Branch("mc_Entry", &stable.Entry, "mc_Entry[4]/F");
  // pi0 (7 vars)
  tree->Branch("mc_pi0Px", &pi0.Px);
  tree->Branch("mc_pi0Py", &pi0.Py);
  tree->Branch("mc_pi0Pz", &pi0.Pz);
  tree->Branch("mc_pi0P", &pi0.P);
  tree->Branch("mc_pi0E", &pi0.E);
  tree->Branch("mc_pi0M", &pi0.M);
  tree->Branch("mc_pi0Theta", &pi0.Theta);
  // omega (14 vars)
  tree->Branch("mc_wE", &omega.E);
  tree->Branch("mc_wP", &omega.P);
  tree->Branch("mc_wPx", &omega.Px);
  tree->Branch("mc_wPy", &omega.Py);
  tree->Branch("mc_wPz", &omega.Pz);
  tree->Branch("mc_wM", &omega.M);
  tree->Branch("mc_wZ", &omega.Z);
  tree->Branch("mc_wD", &omega.D);
  tree->Branch("mc_wPhiPQ", &omega.PhiPQ);
  tree->Branch("mc_wThetaPQ", &omega.ThetaPQ);
  tree->Branch("mc_wPt2", &omega.Pt2);
  tree->Branch("mc_wPl2", &omega.Pl2);
  tree->Branch("mc_wPhiLab", &omega.PhiLab);
  tree->Branch("mc_wThetaLab", &omega.ThetaLab);
}

void NullOutputVars(stable_t& stable, pi0_t& pi0, omega_t& omega) {
  // robust function: does the same for REC and GEN
  // electron (16 vars)
  stable.Q2 = INVLD;
  stable.W = INVLD;
  stable.Nu = INVLD;
  stable.Xb = INVLD;
  stable.Yb = INVLD;
  stable.Pex = INVLD;
  stable.Pey = INVLD;
  stable.Pez = INVLD;
  stable.Pe = INVLD;
  stable.Xec = INVLD;
  stable.Yec = INVLD;
  stable.Zec = INVLD;
  stable.TargType = INVLD;
  stable.PhiLabEl = INVLD;
  stable.ThetaLabEl = INVLD;
  stable.SectorEl = INVLD;
  for (Int_t index = 0; index < 4; index++) {
    // particles ( vars)
    stable.E[index] = INVLD;
    stable.Z[index] = INVLD;
    stable.Px[index] = INVLD;
    stable.Py[index] = INVLD;
    stable.Pz[index] = INVLD;
    stable.P[index] = INVLD;
    stable.ThetaPQ[index] = INVLD;
    stable.PhiPQ[index] = INVLD;
    stable.Pt2[index] = INVLD;
    stable.Pl2[index] = INVLD;
    stable.ThetaLab[index] = INVLD;
    stable.PhiLab[index] = INVLD;
    stable.deltaZ[index] = INVLD;
    stable.Pid[index] = INVLD;
    stable.ParentID[index] = INVLD;
    // event-related (1 var)
    stable.Entry[index] = INVLD;
  }
  // pi0 (7 vars)
  pi0.Px = INVLD;
  pi0.Py = INVLD;
  pi0.Pz = INVLD;
  pi0.P = INVLD;
  pi0.M = INVLD;
  pi0.E = INVLD;
  pi0.Theta = INVLD;
  // omega (14 vars)
  omega.Px = INVLD;
  omega.Py = INVLD;
  omega.Pz = INVLD;
  omega.P = INVLD;
  omega.E = INVLD;
  omega.M = INVLD;
  omega.D = INVLD;
  omega.Z = INVLD;
  omega.PhiPQ = INVLD;
  omega.ThetaPQ = INVLD;
  omega.Pt2 = INVLD;
  omega.Pl2 = INVLD;
  omega.PhiLab = INVLD;
  omega.ThetaLab = INVLD;
}

void WriteStableVars_GEN(elec_t& elec, part_t& part, stable_t& stable, Int_t entry, Int_t index) {
  // electron (13 vars)
  stable.Q2 = elec.Q2;
  stable.W = elec.W;
  stable.Nu = elec.Nu;
  stable.Xb = elec.Xb;
  stable.Yb = elec.Yb;
  stable.Pex = elec.Px;
  stable.Pey = elec.Py;
  stable.Pez = elec.Pz;
  stable.Pe = elec.P;
  stable.TargType = elec.TargType;
  stable.PhiLabEl = PhiLab(elec.Px, elec.Py, elec.Pz);
  stable.ThetaLabEl = ThetaLab(elec.Px, elec.Py, elec.Pz);
  stable.SectorEl = elec.Sector;
  // particle (15 vars)
  stable.Px[index] = part.Px;
  stable.Py[index] = part.Py;
  stable.Pz[index] = part.Pz;
  stable.P[index] = part.P;
  stable.E[index] = part.Eh;
  stable.Z[index] = part.Zh;
  stable.PhiPQ[index] = part.PhiPQ;
  stable.ThetaPQ[index] = part.ThetaPQ;
  stable.Pt2[index] = part.Pt2;
  stable.Pl2[index] = part.Pl2;
  stable.PhiLab[index] = part.PhiLab;
  stable.ThetaLab[index] = part.ThetaLab;
  stable.deltaZ[index] = part.deltaZ;
  stable.Pid[index] = part.pid;
  stable.ParentID[index] = part.ParentID;
  // event-related (1)
  stable.Entry[index] = entry;
}

#endif
