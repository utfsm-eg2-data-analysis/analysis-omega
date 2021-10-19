#ifndef TREEOPS_HXX
#define TREEOPS_HXX

#include "Headers.hxx"
#include "Math.hxx"
#include "PDG.hxx"

#include "GSTtree.h"

#include "2GFtree.h"

#ifndef INVLD
#define INVLD -9999
#endif

// IMPORTANT CONSIDERATION: elec_t & part_t are INPUT data structures, while stable_t & eta_t are OUTPUT data structures

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

void SetOutputTree_REC(TTree* tree, stable_t& stable, eta_t& eta) {
  // electron (16 vars)
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
  // particles (14 vars)
  tree->Branch("E", &stable.E, "E[2]/F");
  tree->Branch("Z", &stable.Z, "Z[2]/F");
  tree->Branch("Px", &stable.Px, "Px[2]/F");
  tree->Branch("Py", &stable.Py, "Py[2]/F");
  tree->Branch("Pz", &stable.Pz, "Pz[2]/F");
  tree->Branch("P", &stable.P, "P[2]/F");
  tree->Branch("ThetaPQ", &stable.ThetaPQ, "ThetaPQ[2]/F");
  tree->Branch("PhiPQ", &stable.PhiPQ, "PhiPQ[2]/F");
  tree->Branch("Pt2", &stable.Pt2, "Pt2[2]/F");
  tree->Branch("Pl2", &stable.Pl2, "Pl2[2]/F");
  tree->Branch("ThetaLab", &stable.ThetaLab, "ThetaLab[2]/F");
  tree->Branch("PhiLab", &stable.PhiLab, "PhiLab[2]/F");
  tree->Branch("deltaZ", &stable.deltaZ, "deltaZ[2]/F");
  tree->Branch("Pid", &stable.Pid, "Pid[2]/F");
  // event related (2 vars)
  tree->Branch("Entry", &stable.Entry, "Entry[2]/F");
  tree->Branch("Event", &stable.Event);
  // eta (14 vars)
  tree->Branch("nPx", &eta.Px);
  tree->Branch("nPy", &eta.Py);
  tree->Branch("nPz", &eta.Pz);
  tree->Branch("nP", &eta.P);
  tree->Branch("nE", &eta.E);
  tree->Branch("nM", &eta.M);
  tree->Branch("nTheta", &eta.Theta);
  tree->Branch("nZ", &eta.Z);
  tree->Branch("nThetaPQ", &eta.ThetaPQ);
  tree->Branch("nPhiPQ", &eta.PhiPQ);
  tree->Branch("nPt2", &eta.Pt2);
  tree->Branch("nPl2", &eta.Pl2);
  tree->Branch("nThetaLab", &eta.ThetaLab);
  tree->Branch("nPhiLab", &eta.PhiLab);
}

void WriteStableVars_REC(elec_t& elec, part_t& part, stable_t& stable, Int_t entry, Int_t index) {
  // electron (16 vars)
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
  // particles (14 vars)
  stable.E[index] = part.Eh;
  stable.Z[index] = stable.E[index] / stable.Nu;
  stable.Px[index] = part.Px;
  stable.Py[index] = part.Py;
  stable.Pz[index] = part.Pz;
  stable.P[index] = part.P;
  stable.ThetaPQ[index] = ThetaPQ(stable.Pex, stable.Pey, stable.Pez, stable.Px[index], stable.Py[index], stable.Pz[index]);
  stable.PhiPQ[index] = PhiPQ(stable.Pex, stable.Pey, stable.Pez, stable.Px[index], stable.Py[index], stable.Pz[index]);
  Double_t fCosThetaPQ = ((kEbeam - stable.Pez) * stable.Pz[index] - stable.Pex * stable.Px[index] - stable.Pey * stable.Py[index]) /
                         (TMath::Sqrt(stable.P[index] * stable.P[index] * (stable.Q2 + stable.Nu * stable.Nu)));
  stable.Pt2[index] = stable.P[index] * stable.P[index] * (1 - fCosThetaPQ * fCosThetaPQ);
  stable.Pl2[index] = stable.P[index] * stable.P[index] * fCosThetaPQ * fCosThetaPQ;
  stable.ThetaLab[index] = ThetaLab(stable.Px[index], stable.Py[index], stable.Pz[index]);
  stable.PhiLab[index] = PhiLab(stable.Px[index], stable.Py[index], stable.Pz[index]);
  stable.deltaZ[index] = part.deltaZ;
  stable.Pid[index] = part.pid;
}

void WriteEtaVars(stable_t& stable, eta_t& eta) {
  // robust function: does the same for REC and GEN
  // eta (14 vars)
  eta.E = stable.E[0] + stable.E[1];
  eta.Px = stable.Px[0] + stable.Px[1];
  eta.Py = stable.Py[0] + stable.Py[1];
  eta.Pz = stable.Pz[0] + stable.Pz[1];
  eta.P = TMath::Sqrt(eta.Px*eta.Px + eta.Py*eta.Py + eta.Pz*eta.Pz);
  eta.M = TMath::Sqrt(eta.E * eta.E - eta.P * eta.P);
  Double_t fDot = stable.Px[0] * stable.Px[1] + stable.Py[0] * stable.Py[1] + stable.Pz[0] * stable.Pz[1];
  Double_t fMag0 = TMath::Sqrt(stable.Px[0] * stable.Px[0] + stable.Py[0] * stable.Py[0] + stable.Pz[0] * stable.Pz[0]);
  Double_t fMag1 = TMath::Sqrt(stable.Px[1] * stable.Px[1] + stable.Py[1] * stable.Py[1] + stable.Pz[1] * stable.Pz[1]);
  eta.Theta = TMath::RadToDeg() * TMath::ACos(fDot / (fMag0 * fMag1));
  eta.Z = eta.E / stable.Nu;
  eta.PhiPQ = PhiPQ(stable.Pex, stable.Pey, stable.Pez, eta.Px, eta.Py, eta.Pz);
  eta.ThetaPQ = ThetaPQ(stable.Pex, stable.Pey, stable.Pez, eta.Px, eta.Py, eta.Pz);
  Double_t fCosThetaPQ = ((kEbeam - stable.Pez) * eta.Pz - stable.Pex * eta.Px - stable.Pey * eta.Py) /
                         (TMath::Sqrt(eta.P * eta.P * (stable.Q2 + stable.Nu * stable.Nu)));
  eta.PhiLab = PhiLab(eta.Px, eta.Py, eta.Pz);
  eta.ThetaLab = ThetaLab(eta.Px, eta.Py, eta.Pz);
  eta.Pt2 = eta.P * eta.P * (1 - fCosThetaPQ * fCosThetaPQ);
  eta.Pl2 = eta.P * eta.P * fCosThetaPQ * fCosThetaPQ;
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

void SetOutputTree_GEN(TTree* tree, stable_t& stable, eta_t& eta) {
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
  tree->Branch("mc_E", &stable.E, "mc_E[2]/F");
  tree->Branch("mc_Z", &stable.Z, "mc_Z[2]/F");
  tree->Branch("mc_Px", &stable.Px, "mc_Px[2]/F");
  tree->Branch("mc_Py", &stable.Py, "mc_Py[2]/F");
  tree->Branch("mc_Pz", &stable.Pz, "mc_Pz[2]/F");
  tree->Branch("mc_P", &stable.P, "mc_P[2]/F");
  tree->Branch("mc_PhiPQ", &stable.PhiPQ, "mc_PhiPQ[2]/F");
  tree->Branch("mc_ThetaPQ", &stable.ThetaPQ, "mc_ThetaPQ[2]/F");
  tree->Branch("mc_Pt2", &stable.Pt2, "mc_Pt2[2]/F");
  tree->Branch("mc_Pl2", &stable.Pl2, "mc_Pl2[2]/F");
  tree->Branch("mc_PhiLab", &stable.PhiLab, "mc_PhiLab[2]/F");
  tree->Branch("mc_ThetaLab", &stable.ThetaLab, "mc_ThetaLab[2]/F");
  tree->Branch("mc_deltaZ", &stable.deltaZ, "mc_deltaZ[2]/F");
  tree->Branch("mc_Pid", &stable.Pid, "mc_Pid[2]/F");
  tree->Branch("mc_ParentID", &stable.ParentID, "mc_ParentID[2]/F");  // extra!
  // event-related (1 var)
  tree->Branch("mc_Entry", &stable.Entry, "mc_Entry[2]/F");
  // eta (14 vars)
  tree->Branch("mc_nPx", &eta.Px);
  tree->Branch("mc_nPy", &eta.Py);
  tree->Branch("mc_nPz", &eta.Pz);
  tree->Branch("mc_nP", &eta.P);
  tree->Branch("mc_nE", &eta.E);
  tree->Branch("mc_nM", &eta.M);
  tree->Branch("mc_nTheta", &eta.Theta);
  tree->Branch("mc_nZ", &eta.Z);
  tree->Branch("mc_nThetaPQ", &eta.ThetaPQ);
  tree->Branch("mc_nPhiPQ", &eta.PhiPQ);
  tree->Branch("mc_nPt2", &eta.Pt2);
  tree->Branch("mc_nPl2", &eta.Pl2);
  tree->Branch("mc_nThetaLab", &eta.ThetaLab);
  tree->Branch("mc_nPhiLab", &eta.PhiLab);
}

void NullOutputVars(stable_t& stable, eta_t& eta) {
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
  for (Int_t index = 0; index < 2; index++) {
    // particles (14 vars)
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
  // eta (14 vars)
  eta.Px = INVLD;
  eta.Py = INVLD;
  eta.Pz = INVLD;
  eta.P = INVLD;
  eta.E = INVLD;
  eta.M = INVLD;
  eta.Theta = INVLD;  // opening angle between 2 gammas
  eta.Z = INVLD;
  eta.ThetaPQ = INVLD;
  eta.PhiPQ = INVLD;
  eta.Pt2 = INVLD;
  eta.Pl2 = INVLD;
  eta.ThetaLab = INVLD;
  eta.PhiLab = INVLD;
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
  stable.E[index] = part.Eh;
  stable.Z[index] = part.Zh;
  stable.Px[index] = part.Px;
  stable.Py[index] = part.Py;
  stable.Pz[index] = part.Pz;
  stable.P[index] = part.P;
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
