#ifndef REDUCTOR_HXX
#define REDUCTOR_HXX

#ifndef UX_HXX
#include "UX.hxx"
#endif

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

#ifndef GSTTREE_H
#include "GSTtree.h"
#endif

void ReadInputChain_REC(TChain* chain, elec_t& elec, part_t& part) {
  // electron (26)
  chain->SetBranchAddress("Q2", &elec.Q2);
  chain->SetBranchAddress("W", &elec.W);
  chain->SetBranchAddress("Nu", &elec.Nu);
  chain->SetBranchAddress("Xb", &elec.Xb);
  chain->SetBranchAddress("Yb", &elec.Yb);
  chain->SetBranchAddress("Pex", &elec.Px);
  chain->SetBranchAddress("Pey", &elec.Py);
  chain->SetBranchAddress("Pez", &elec.Pz);
  chain->SetBranchAddress("Pe", &elec.P);
  chain->SetBranchAddress("Eine", &elec.Ein);
  chain->SetBranchAddress("Eoute", &elec.Eout);
  chain->SetBranchAddress("Etote", &elec.Etot);
  chain->SetBranchAddress("XECe", &elec.XEC);
  chain->SetBranchAddress("YECe", &elec.YEC);
  chain->SetBranchAddress("ZECe", &elec.ZEC);
  chain->SetBranchAddress("vxe", &elec.vx);
  chain->SetBranchAddress("vye", &elec.vy);
  chain->SetBranchAddress("vze", &elec.vz);
  chain->SetBranchAddress("vxec", &elec.vxc);
  chain->SetBranchAddress("vyec", &elec.vyc);
  chain->SetBranchAddress("vzec", &elec.vzc);
  chain->SetBranchAddress("TargType", &elec.TargType);
  chain->SetBranchAddress("SectorEl", &elec.Sector);
  chain->SetBranchAddress("PhiLabEl", &elec.PhiLab);
  chain->SetBranchAddress("ThetaLabEl", &elec.ThetaLab);
  chain->SetBranchAddress("BettaEl", &elec.Betta);
  // event (1)
  chain->SetBranchAddress("evnt", &elec.evnt);
  // particle (29)
  chain->SetBranchAddress("Eh", &part.Eh);
  chain->SetBranchAddress("Zh", &part.Zh);
  chain->SetBranchAddress("ThetaPQ", &part.ThetaPQ);
  chain->SetBranchAddress("Pt2", &part.Pt2);
  chain->SetBranchAddress("Pl2", &part.Pl2);
  chain->SetBranchAddress("PhiPQ", &part.PhiPQ);
  chain->SetBranchAddress("Mx2", &part.Mx2);
  chain->SetBranchAddress("T", &part.T);
  chain->SetBranchAddress("PhiLab", &part.PhiLab);
  chain->SetBranchAddress("ThetaLab", &part.ThetaLab);
  chain->SetBranchAddress("vxh", &part.vx);
  chain->SetBranchAddress("vyh", &part.vy);
  chain->SetBranchAddress("vzh", &part.vz);
  chain->SetBranchAddress("Sector", &part.Sector);
  chain->SetBranchAddress("Px", &part.Px);
  chain->SetBranchAddress("Py", &part.Py);
  chain->SetBranchAddress("Pz", &part.Pz);
  chain->SetBranchAddress("P", &part.P);
  chain->SetBranchAddress("Betta", &part.Betta);
  chain->SetBranchAddress("Mass2", &part.Mass2);
  chain->SetBranchAddress("Etot", &part.Etot);
  chain->SetBranchAddress("Ein", &part.Ein);
  chain->SetBranchAddress("Eout", &part.Eout);
  chain->SetBranchAddress("XEC", &part.XEC);
  chain->SetBranchAddress("YEC", &part.YEC);
  chain->SetBranchAddress("ZEC", &part.ZEC);
  chain->SetBranchAddress("T4", &part.T4);
  chain->SetBranchAddress("deltaZ", &part.deltaZ);
  chain->SetBranchAddress("pid", &part.pid);
}

void SetOutputTree_REC(TTree* tree, elec_t& elec, part_t& part) {
  // electron (26)
  tree->Branch("Q2", &elec.Q2);
  tree->Branch("W", &elec.W);
  tree->Branch("Nu", &elec.Nu);
  tree->Branch("Xb", &elec.Xb);
  tree->Branch("Yb", &elec.Yb);
  tree->Branch("Pex", &elec.Px);
  tree->Branch("Pey", &elec.Py);
  tree->Branch("Pez", &elec.Pz);
  tree->Branch("Pe", &elec.P);
  tree->Branch("Eine", &elec.Ein);
  tree->Branch("Eoute", &elec.Eout);
  tree->Branch("Etote", &elec.Etot);
  tree->Branch("XECe", &elec.XEC);
  tree->Branch("YECe", &elec.YEC);
  tree->Branch("ZECe", &elec.ZEC);
  tree->Branch("vxe", &elec.vx);
  tree->Branch("vye", &elec.vy);
  tree->Branch("vze", &elec.vz);
  tree->Branch("vxec", &elec.vxc);
  tree->Branch("vyec", &elec.vyc);
  tree->Branch("vzec", &elec.vzc);
  tree->Branch("TargType", &elec.TargType);
  tree->Branch("SectorEl", &elec.Sector);
  tree->Branch("PhiLabEl", &elec.PhiLab);
  tree->Branch("ThetaLabEl", &elec.ThetaLab);
  tree->Branch("BettaEl", &elec.Betta);
  // event (1)
  tree->Branch("evnt", &elec.evnt);
  // particle (29)
  tree->Branch("Eh", &part.Eh);
  tree->Branch("Zh", &part.Zh);
  tree->Branch("ThetaPQ", &part.ThetaPQ);
  tree->Branch("Pt2", &part.Pt2);
  tree->Branch("Pl2", &part.Pl2);
  tree->Branch("PhiPQ", &part.PhiPQ);
  tree->Branch("Mx2", &part.Mx2);
  tree->Branch("T", &part.T);
  tree->Branch("PhiLab", &part.PhiLab);
  tree->Branch("ThetaLab", &part.ThetaLab);
  tree->Branch("vxh", &part.vx);
  tree->Branch("vyh", &part.vy);
  tree->Branch("vzh", &part.vz);
  tree->Branch("Sector", &part.Sector);
  tree->Branch("Px", &part.Px);
  tree->Branch("Py", &part.Py);
  tree->Branch("Pz", &part.Pz);
  tree->Branch("P", &part.P);
  tree->Branch("Betta", &part.Betta);
  tree->Branch("Mass2", &part.Mass2);
  tree->Branch("Ein", &part.Ein);
  tree->Branch("Eout", &part.Eout);
  tree->Branch("Etot", &part.Etot);
  tree->Branch("XEC", &part.XEC);
  tree->Branch("YEC", &part.YEC);
  tree->Branch("ZEC", &part.ZEC);
  tree->Branch("T4", &part.T4);
  tree->Branch("deltaZ", &part.deltaZ);
  tree->Branch("pid", &part.pid);
}

#endif
