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

void ReadParticleChain_REC(TChain* chain, rec_t& rec) {
  // electron (26)
  chain->SetBranchAddress("Q2", &rec.Q2);
  chain->SetBranchAddress("W", &rec.W);
  chain->SetBranchAddress("Nu", &rec.Nu);
  chain->SetBranchAddress("Xb", &rec.Xb);
  chain->SetBranchAddress("Yb", &rec.Yb);
  chain->SetBranchAddress("Pex", &rec.Pex);
  chain->SetBranchAddress("Pey", &rec.Pey);
  chain->SetBranchAddress("Pez", &rec.Pez);
  chain->SetBranchAddress("Pe", &rec.Pe);
  chain->SetBranchAddress("Eine", &rec.Eine);
  chain->SetBranchAddress("Eoute", &rec.Eoute);
  chain->SetBranchAddress("Etote", &rec.Etote);
  chain->SetBranchAddress("XECe", &rec.XECe);
  chain->SetBranchAddress("YECe", &rec.YECe);
  chain->SetBranchAddress("ZECe", &rec.ZECe);
  chain->SetBranchAddress("vxe", &rec.vxe);
  chain->SetBranchAddress("vye", &rec.vye);
  chain->SetBranchAddress("vze", &rec.vze);
  chain->SetBranchAddress("vxec", &rec.vxec);
  chain->SetBranchAddress("vyec", &rec.vyec);
  chain->SetBranchAddress("vzec", &rec.vzec);
  chain->SetBranchAddress("TargType", &rec.TargType);
  chain->SetBranchAddress("SectorEl", &rec.SectorEl);
  chain->SetBranchAddress("PhiLabEl", &rec.PhiLabEl);
  chain->SetBranchAddress("ThetaLabEl", &rec.ThetaLabEl);
  chain->SetBranchAddress("BettaEl", &rec.BettaEl);
  // event (1)
  chain->SetBranchAddress("evnt", &rec.evnt);
  // particle (29)
  chain->SetBranchAddress("Eh", &rec.Eh);
  chain->SetBranchAddress("Zh", &rec.Zh);
  chain->SetBranchAddress("ThetaPQ", &rec.ThetaPQ);
  chain->SetBranchAddress("Pt2", &rec.Pt2);
  chain->SetBranchAddress("Pl2", &rec.Pl2);
  chain->SetBranchAddress("PhiPQ", &rec.PhiPQ);
  chain->SetBranchAddress("Mx2", &rec.Mx2);
  chain->SetBranchAddress("T", &rec.T);
  chain->SetBranchAddress("PhiLab", &rec.PhiLab);
  chain->SetBranchAddress("ThetaLab", &rec.ThetaLab);
  chain->SetBranchAddress("vxh", &rec.vxh);
  chain->SetBranchAddress("vyh", &rec.vyh);
  chain->SetBranchAddress("vzh", &rec.vzh);
  chain->SetBranchAddress("Sector", &rec.Sector);
  chain->SetBranchAddress("Px", &rec.Px);
  chain->SetBranchAddress("Py", &rec.Py);
  chain->SetBranchAddress("Pz", &rec.Pz);
  chain->SetBranchAddress("P", &rec.P);
  chain->SetBranchAddress("Betta", &rec.Betta);
  chain->SetBranchAddress("Mass2", &rec.Mass2);
  chain->SetBranchAddress("Etot", &rec.Etot);
  chain->SetBranchAddress("Ein", &rec.Ein);
  chain->SetBranchAddress("Eout", &rec.Eout);
  chain->SetBranchAddress("XEC", &rec.XEC);
  chain->SetBranchAddress("YEC", &rec.YEC);
  chain->SetBranchAddress("ZEC", &rec.ZEC);
  chain->SetBranchAddress("pid", &rec.pid);
  chain->SetBranchAddress("T4", &rec.T4);
  chain->SetBranchAddress("deltaZ", &rec.deltaZ);
}

void SetParticleTree_REC(TTree* tree, rec_t& rec) {
  // electron (26)
  tree->Branch("Q2", &rec.Q2);
  tree->Branch("W", &rec.W);
  tree->Branch("Nu", &rec.Nu);
  tree->Branch("Xb", &rec.Xb);
  tree->Branch("Yb", &rec.Yb);
  tree->Branch("Pex", &rec.Pex);
  tree->Branch("Pey", &rec.Pey);
  tree->Branch("Pez", &rec.Pez);
  tree->Branch("Pe", &rec.Pe);
  tree->Branch("Eine", &rec.Eine);
  tree->Branch("Eoute", &rec.Eoute);
  tree->Branch("Etote", &rec.Etote);
  tree->Branch("XECe", &rec.XECe);
  tree->Branch("YECe", &rec.YECe);
  tree->Branch("ZECe", &rec.ZECe);
  tree->Branch("vxe", &rec.vxe);
  tree->Branch("vye", &rec.vye);
  tree->Branch("vze", &rec.vze);
  tree->Branch("vxec", &rec.vxec);
  tree->Branch("vyec", &rec.vyec);
  tree->Branch("vzec", &rec.vzec);
  tree->Branch("TargType", &rec.TargType);
  tree->Branch("SectorEl", &rec.SectorEl);
  tree->Branch("PhiLabEl", &rec.PhiLabEl);
  tree->Branch("ThetaLabEl", &rec.ThetaLabEl);
  tree->Branch("BettaEl", &rec.BettaEl);
  // event (1)
  tree->Branch("evnt", &rec.evnt);
  // particle (29)
  tree->Branch("Eh", &rec.Eh);
  tree->Branch("Zh", &rec.Zh);
  tree->Branch("ThetaPQ", &rec.ThetaPQ);
  tree->Branch("Pt2", &rec.Pt2);
  tree->Branch("Pl2", &rec.Pl2);
  tree->Branch("PhiPQ", &rec.PhiPQ);
  tree->Branch("Mx2", &rec.Mx2);
  tree->Branch("T", &rec.T);
  tree->Branch("PhiLab", &rec.PhiLab);
  tree->Branch("ThetaLab", &rec.ThetaLab);
  tree->Branch("vxh", &rec.vxh);
  tree->Branch("vyh", &rec.vyh);
  tree->Branch("vzh", &rec.vzh);
  tree->Branch("Sector", &rec.Sector);
  tree->Branch("Px", &rec.Px);
  tree->Branch("Py", &rec.Py);
  tree->Branch("Pz", &rec.Pz);
  tree->Branch("P", &rec.P);
  tree->Branch("Betta", &rec.Betta);
  tree->Branch("Mass2", &rec.Mass2);
  tree->Branch("Ein", &rec.Ein);
  tree->Branch("Eout", &rec.Eout);
  tree->Branch("Etot", &rec.Etot);
  tree->Branch("XEC", &rec.XEC);
  tree->Branch("YEC", &rec.YEC);
  tree->Branch("ZEC", &rec.ZEC);
  tree->Branch("pid", &rec.pid);
  tree->Branch("T4", &rec.T4);
  tree->Branch("deltaZ", &rec.deltaZ);
}

#endif
