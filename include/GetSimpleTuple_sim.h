#include "TIdentificatorV2.h"
#include "GSTtree.h"

#include "analysisConfig.h"

#include "ROOT/RVec.hxx"

using namespace ROOT::VecOps;

#define INVLD -9999

void SetElectronBranches_Sim(TTree *tree, sim_e& se) {
  // simrec (41)
  tree->Branch("Q2",       &se.Q2);
  tree->Branch("W",        &se.W);
  tree->Branch("Nu",       &se.Nu);
  tree->Branch("Xb",       &se.Xb);
  tree->Branch("Yb",       &se.Yb);
  tree->Branch("vxe",      &se.vxe);
  tree->Branch("vye",      &se.vye);
  tree->Branch("vze",      &se.vze);
  tree->Branch("Sector",   &se.Sector);
  tree->Branch("TargType", &se.TargType);
  tree->Branch("Px",       &se.Px);
  tree->Branch("Py",       &se.Py);
  tree->Branch("Pz",       &se.Pz);
  tree->Branch("P",        &se.P);
  tree->Branch("Betta",    &se.Betta);
  tree->Branch("Etot",     &se.Etot);
  tree->Branch("Ein",      &se.Ein);
  tree->Branch("Eout",     &se.Eout);
  tree->Branch("vxec",     &se.vxec);
  tree->Branch("vyec",     &se.vyec);
  tree->Branch("vzec",     &se.vzec);
  tree->Branch("XEC",      &se.XEC);
  tree->Branch("YEC",      &se.YEC);
  tree->Branch("ZEC",      &se.ZEC);
  tree->Branch("StatDC",   &se.StatDC);
  tree->Branch("DCStatus", &se.DCStatus);
  tree->Branch("StatEC",   &se.StatEC);
  tree->Branch("ECStatus", &se.ECStatus);
  tree->Branch("TimeEC",   &se.TimeEC);
  tree->Branch("PathEC",   &se.PathEC);
  tree->Branch("Chi2EC",   &se.Chi2EC);
  tree->Branch("StatSC",   &se.StatSC);
  tree->Branch("SCStatus", &se.SCStatus);
  tree->Branch("TimeSC",   &se.TimeSC);
  tree->Branch("PathSC",   &se.PathSC);
  tree->Branch("StatCC",   &se.StatCC);
  tree->Branch("CCStatus", &se.CCStatus);
  tree->Branch("Nphe",     &se.Nphe);
  tree->Branch("Chi2CC",   &se.Chi2CC);
  tree->Branch("Status",   &se.Status);
  tree->Branch("evnt",     &se.evnt);
  // gsim (15)
  tree->Branch("mc_Q2",       &se.mc_Q2);
  tree->Branch("mc_W",        &se.mc_W);
  tree->Branch("mc_Nu",       &se.mc_Nu);
  tree->Branch("mc_Xb",       &se.mc_Xb);
  tree->Branch("mc_Yb",       &se.mc_Yb);
  tree->Branch("mc_vxe",      &se.mc_vxe);
  tree->Branch("mc_vye",      &se.mc_vye);
  tree->Branch("mc_vze",      &se.mc_vze);
  tree->Branch("mc_Sector",   &se.mc_Sector);
  tree->Branch("mc_TargType", &se.mc_TargType);
  tree->Branch("mc_Px",       &se.mc_Px);
  tree->Branch("mc_Py",       &se.mc_Py);
  tree->Branch("mc_Pz",       &se.mc_Pz);
  tree->Branch("mc_P",        &se.mc_P);
  tree->Branch("mc_Betta",    &se.mc_Betta);
}

void SetParticleBranches_Sim(TTree *tree, sim_p& sp) {
  // simrec electron (40)
  tree->Branch("Q2",         &sp.Q2);
  tree->Branch("W",          &sp.W);
  tree->Branch("Nu",         &sp.Nu);
  tree->Branch("Xb",         &sp.Xb);
  tree->Branch("Yb",         &sp.Yb);
  tree->Branch("vxe",        &sp.vxe);
  tree->Branch("vye",        &sp.vye);
  tree->Branch("vze",        &sp.vze);
  tree->Branch("SectorEl",   &sp.SectorEl);
  tree->Branch("TargType",   &sp.TargType);
  tree->Branch("Pex",        &sp.Pex);
  tree->Branch("Pey",        &sp.Pey);
  tree->Branch("Pez",        &sp.Pez);
  tree->Branch("Pe",         &sp.Pe);
  tree->Branch("BettaEl",    &sp.BettaEl);
  tree->Branch("Etote",      &sp.Etote);
  tree->Branch("Eine",       &sp.Eine);
  tree->Branch("Eoute",      &sp.Eoute);
  tree->Branch("vxec",       &sp.vxec);
  tree->Branch("vyec",       &sp.vyec);
  tree->Branch("vzec",       &sp.vzec);
  tree->Branch("XECe",       &sp.XECe);
  tree->Branch("YECe",       &sp.YECe);
  tree->Branch("ZECe",       &sp.ZECe);
  tree->Branch("StatDCEl",   &sp.StatDCEl);
  tree->Branch("DCStatusEl", &sp.DCStatusEl);
  tree->Branch("StatECEl",   &sp.StatECEl);
  tree->Branch("ECStatusEl", &sp.ECStatusEl);
  tree->Branch("TimeECEl",   &sp.TimeECEl);
  tree->Branch("PathECEl",   &sp.PathECEl);
  tree->Branch("Chi2ECEl",   &sp.Chi2ECEl);
  tree->Branch("StatSCEl",   &sp.StatSCEl);
  tree->Branch("SCStatusEl", &sp.SCStatusEl);
  tree->Branch("TimeSCEl",   &sp.TimeSCEl);
  tree->Branch("PathSCEl",   &sp.PathSCEl);
  tree->Branch("StatCCEl",   &sp.StatCCEl);
  tree->Branch("CCStatusEl", &sp.CCStatusEl);
  tree->Branch("NpheEl",     &sp.NpheEl);
  tree->Branch("Chi2CCEl",   &sp.Chi2CCEl);
  tree->Branch("StatusEl",   &sp.StatusEl);
  // simrec particle (42)
  tree->Branch("Zh",       &sp.Zh);
  tree->Branch("ThetaPQ",  &sp.ThetaPQ);
  tree->Branch("Pt2",      &sp.Pt2);
  tree->Branch("Pl2",      &sp.Pl2);
  tree->Branch("PhiPQ",    &sp.PhiPQ);
  tree->Branch("Mx2",      &sp.Mx2);
  tree->Branch("T",        &sp.T);
  tree->Branch("vxh",      &sp.vxh);
  tree->Branch("vyh",      &sp.vyh);
  tree->Branch("vzh",      &sp.vzh);
  tree->Branch("Sector",   &sp.Sector);
  tree->Branch("Px",       &sp.Px);
  tree->Branch("Py",       &sp.Py);
  tree->Branch("Pz",       &sp.Pz);
  tree->Branch("P",        &sp.P);
  tree->Branch("Betta",    &sp.Betta);
  tree->Branch("Mass2",    &sp.Mass2);
  tree->Branch("Etot",     &sp.Etot);
  tree->Branch("Ein",      &sp.Ein);
  tree->Branch("Eout",     &sp.Eout);
  tree->Branch("XEC",      &sp.XEC);
  tree->Branch("YEC",      &sp.YEC);
  tree->Branch("ZEC",      &sp.ZEC);
  tree->Branch("pid",      &sp.pid);
  tree->Branch("T4",       &sp.T4);
  tree->Branch("deltaZ",   &sp.deltaZ);
  tree->Branch("StatDC",   &sp.StatDC);
  tree->Branch("DCStatus", &sp.DCStatus);
  tree->Branch("StatEC",   &sp.StatEC);
  tree->Branch("ECStatus", &sp.ECStatus);
  tree->Branch("TimeEC",   &sp.TimeEC);
  tree->Branch("PathEC",   &sp.PathEC);
  tree->Branch("Chi2EC",   &sp.Chi2EC);
  tree->Branch("StatSC",   &sp.StatSC);
  tree->Branch("SCStatus", &sp.SCStatus);
  tree->Branch("TimeSC",   &sp.TimeSC);
  tree->Branch("PathSC",   &sp.PathSC);
  tree->Branch("StatCC",   &sp.StatCC);
  tree->Branch("CCStatus", &sp.CCStatus);
  tree->Branch("Nphe",     &sp.Nphe);
  tree->Branch("Chi2CC",   &sp.Chi2CC);
  tree->Branch("Status",   &sp.Status);
  // event-related (1)
  tree->Branch("evnt",     &sp.evnt);
  // gsim electron (15)
  tree->Branch("mc_Q2",       &sp.mc_Q2);
  tree->Branch("mc_W",        &sp.mc_W);
  tree->Branch("mc_Nu",       &sp.mc_Nu);
  tree->Branch("mc_Xb",       &sp.mc_Xb);
  tree->Branch("mc_Yb",       &sp.mc_Yb);
  tree->Branch("mc_vxe",      &sp.mc_vxe);
  tree->Branch("mc_vye",      &sp.mc_vye);
  tree->Branch("mc_vze",      &sp.mc_vze);
  tree->Branch("mc_SectorEl", &sp.mc_SectorEl);
  tree->Branch("mc_TargType", &sp.mc_TargType);
  tree->Branch("mc_Pex",      &sp.mc_Pex);
  tree->Branch("mc_Pey",      &sp.mc_Pey);
  tree->Branch("mc_Pez",      &sp.mc_Pez);
  tree->Branch("mc_Pe",       &sp.mc_Pe);
  tree->Branch("mc_BettaEl",  &sp.mc_BettaEl);
  // gsim particle (19)
  tree->Branch("mc_Zh",       &sp.mc_Zh);
  tree->Branch("mc_ThetaPQ",  &sp.mc_ThetaPQ);
  tree->Branch("mc_Pt2",      &sp.mc_Pt2);
  tree->Branch("mc_Pl2",      &sp.mc_Pl2);
  tree->Branch("mc_PhiPQ",    &sp.mc_PhiPQ);
  tree->Branch("mc_Mx2",      &sp.mc_Mx2);
  tree->Branch("mc_T",        &sp.mc_T);
  tree->Branch("mc_vxh",      &sp.mc_vxh);
  tree->Branch("mc_vyh",      &sp.mc_vyh);
  tree->Branch("mc_vzh",      &sp.mc_vzh);
  tree->Branch("mc_Sector",   &sp.mc_Sector);
  tree->Branch("mc_Px",       &sp.mc_Px);
  tree->Branch("mc_Py",       &sp.mc_Py);
  tree->Branch("mc_Pz",       &sp.mc_Pz);
  tree->Branch("mc_P",        &sp.mc_P);
  tree->Branch("mc_Betta",    &sp.mc_Betta);
  tree->Branch("mc_Mass2",    &sp.mc_Mass2);
  tree->Branch("mc_pid",      &sp.mc_pid);
  tree->Branch("mc_deltaZ",   &sp.mc_deltaZ);  
}

void NullElectronVar_SIMREC(sim_e& se) {
  // (41)
  se.Q2       = INVLD;
  se.W        = INVLD;
  se.Nu       = INVLD;
  se.Xb       = INVLD;
  se.Yb       = INVLD;
  se.vxe      = INVLD;
  se.vye      = INVLD;
  se.vze      = INVLD;
  se.Sector   = INVLD;
  se.Px       = INVLD;
  se.Py       = INVLD;
  se.Pz       = INVLD;
  se.P        = INVLD;
  se.Betta    = INVLD;
  se.Etot     = INVLD;
  se.Ein      = INVLD;
  se.Eout     = INVLD;
  se.vxec     = INVLD;
  se.vyec     = INVLD;
  se.vzec     = INVLD;
  se.TargType = INVLD;
  se.XEC      = INVLD;
  se.YEC      = INVLD;
  se.ZEC      = INVLD;
  se.StatDC   = INVLD;
  se.DCStatus = INVLD;
  se.StatEC   = INVLD;
  se.ECStatus = INVLD;
  se.TimeEC   = INVLD;
  se.PathEC   = INVLD;
  se.Chi2EC   = INVLD;
  se.StatSC   = INVLD;
  se.SCStatus = INVLD;
  se.TimeSC   = INVLD;
  se.PathSC   = INVLD;
  se.StatCC   = INVLD;
  se.CCStatus = INVLD;
  se.Nphe     = INVLD;
  se.Chi2CC   = INVLD;
  se.Status   = INVLD;  
}

void NullParticleVar_SIMREC(sim_p& sp) {
  // electron (40)
  sp.Q2       = INVLD;
  sp.W        = INVLD;
  sp.Nu       = INVLD;
  sp.Xb       = INVLD;
  sp.Yb       = INVLD;
  sp.vxe      = INVLD;
  sp.vye      = INVLD;
  sp.vze      = INVLD;
  sp.Sector   = INVLD;
  sp.Px       = INVLD;
  sp.Py       = INVLD;
  sp.Pz       = INVLD;
  sp.P        = INVLD;
  sp.Betta    = INVLD;
  sp.Etot     = INVLD;
  sp.Ein      = INVLD;
  sp.Eout     = INVLD;
  sp.vxec     = INVLD;
  sp.vyec     = INVLD;
  sp.vzec     = INVLD;
  sp.TargType = INVLD;
  sp.XEC      = INVLD;
  sp.YEC      = INVLD;
  sp.ZEC      = INVLD;
  sp.StatDC   = INVLD;
  sp.DCStatus = INVLD;
  sp.StatEC   = INVLD;
  sp.ECStatus = INVLD;
  sp.TimeEC   = INVLD;
  sp.PathEC   = INVLD;
  sp.Chi2EC   = INVLD;
  sp.StatSC   = INVLD;
  sp.SCStatus = INVLD;
  sp.TimeSC   = INVLD;
  sp.PathSC   = INVLD;
  sp.StatCC   = INVLD;
  sp.CCStatus = INVLD;
  sp.Nphe     = INVLD;
  sp.Chi2CC   = INVLD;
  sp.Status   = INVLD;
  // particle (42)
  sp.pid        = INVLD;
  sp.Zh         = INVLD;
  sp.ThetaPQ    = INVLD;
  sp.PhiPQ      = INVLD;
  sp.Pt2        = INVLD;
  sp.Pl2        = INVLD;
  sp.Mx2        = INVLD;
  sp.T          = INVLD;
  sp.T4         = INVLD;
  sp.vxh        = INVLD;
  sp.vyh        = INVLD;
  sp.vzh        = INVLD;
  sp.Sector     = INVLD;
  sp.Px         = INVLD;
  sp.Py         = INVLD;
  sp.Pz         = INVLD;
  sp.P          = INVLD;
  sp.Betta      = INVLD;
  sp.Mass2      = INVLD;
  sp.Etot       = INVLD;
  sp.Ein        = INVLD;
  sp.Eout       = INVLD;
  sp.XEC        = INVLD;
  sp.YEC        = INVLD;
  sp.ZEC        = INVLD;
  sp.deltaZ     = INVLD;
  sp.StatDC     = INVLD;
  sp.DCStatus   = INVLD;
  sp.StatEC     = INVLD;
  sp.ECStatus   = INVLD;
  sp.TimeEC     = INVLD;
  sp.PathEC     = INVLD;
  sp.Chi2EC     = INVLD;
  sp.StatSC     = INVLD;
  sp.SCStatus   = INVLD;
  sp.TimeSC     = INVLD;
  sp.PathSC     = INVLD;
  sp.StatCC     = INVLD;
  sp.CCStatus   = INVLD;
  sp.Nphe       = INVLD;
  sp.Chi2CC     = INVLD;
  sp.Status     = INVLD;
}

void AssignElectronVar_SIMREC(TIdentificatorV2* t, sim_e& se, Int_t evnt, TString targetOption) {  
  // simrec (41)
  se.Q2       = t->Q2();
  se.W        = t->W();
  se.Nu       = t->Nu();
  se.Xb       = t->Xb();
  se.Yb       = t->Yb();
  se.vxe      = t->X(0);
  se.vye      = t->Y(0);
  se.vze      = t->Z(0);
  se.Sector   = t->Sector(0);
  se.Px       = t->Px(0);
  se.Py       = t->Py(0);
  se.Pz       = t->Pz(0);
  se.P        = t->Momentum(0);
  se.Betta    = t->Betta(0);
  se.Etot     = t->Etot(0);
  se.Ein      = t->Ein(0);
  se.Eout     = t->Eout(0);
  TVector3 *vert = t->GetCorrectedVert();
  se.vxec     = vert->X();
  se.vyec     = vert->Y();
  se.vzec     = vert->Z();
  se.TargType = t->TargType(vert, targetOption);
  se.XEC      = t->XEC(0);
  se.YEC      = t->YEC(0);
  se.ZEC      = t->ZEC(0);
  se.StatDC   = t->StatDC(0);
  se.DCStatus = t->DCStatus(0);
  se.StatEC   = t->StatEC(0);
  se.ECStatus = t->ECStatus(0);
  se.TimeEC   = t->TimeEC(0);
  se.PathEC   = t->PathEC(0);
  se.Chi2EC   = t->Chi2EC(0);
  se.StatSC   = t->StatSC(0);
  se.SCStatus = t->SCStatus(0);
  se.TimeSC   = t->TimeSC(0);
  se.PathSC   = t->PathSC(0);
  se.StatCC   = t->StatCC(0);
  se.CCStatus = t->CCStatus(0);
  se.Nphe     = t->Nphe(0);
  se.Chi2CC   = t->Chi2CC(0);
  se.Status   = t->Status(0);
}

void AssignElectronVar_GSIM(TIdentificatorV2* t, sim_e& se, Int_t evnt, TString targetOption) {  
  // event-related (1)
  se.evnt     = evnt;
  // gsim (15)
  se.mc_Q2       = t->Q2(1);
  se.mc_W        = t->W(1);
  se.mc_Nu       = t->Nu(1);
  se.mc_Xb       = t->Xb(1);
  se.mc_Yb       = t->Yb(1);
  se.mc_vxe      = t->X(0,1);
  se.mc_vye      = t->Y(0,1);
  se.mc_vze      = t->Z(0,1);
  se.mc_Sector   = t->Sector(0,1);
  se.mc_Px       = t->Px(0,1);
  se.mc_Py       = t->Py(0,1);
  se.mc_Pz       = t->Pz(0,1);
  se.mc_P        = t->Momentum(0,1);
  se.mc_Betta    = t->Betta(0,1);
  TVector3 *mc_vert = new TVector3(t->X(0,1), t->Y(0,1), t->Z(0,1));
  se.mc_TargType = t->TargType(mc_vert, targetOption);
}

void AssignParticleVar_SIMREC(TIdentificatorV2* t, sim_p& sp, Int_t row, Int_t evnt, TString targetOption) {
  // simrec electron (40)
  sp.Q2         = t->Q2();
  sp.W          = t->W();
  sp.Nu         = t->Nu();
  sp.Xb         = t->Xb();
  sp.Yb         = t->Yb();
  sp.vxe        = t->X(0);
  sp.vye        = t->Y(0);
  sp.vze        = t->Z(0);
  sp.SectorEl   = t->Sector(0);
  sp.Pex        = t->Px(0);
  sp.Pey        = t->Py(0);
  sp.Pez        = t->Pz(0);
  sp.Pe         = t->Momentum(0);
  sp.BettaEl    = t->Betta(0);
  sp.Etote      = t->Etot(0);
  sp.Eine       = t->Ein(0);
  sp.Eoute      = t->Eout(0);
  TVector3 *vert = t->GetCorrectedVert();
  sp.vxec       = vert->X();
  sp.vyec       = vert->Y();
  sp.vzec       = vert->Z();
  sp.TargType   = t->TargType(vert, targetOption);
  sp.XECe       = t->XEC(0);
  sp.YECe       = t->YEC(0);
  sp.ZECe       = t->ZEC(0);
  sp.StatDCEl   = t->StatDC(0);
  sp.DCStatusEl = t->DCStatus(0);
  sp.StatECEl   = t->StatEC(0);
  sp.ECStatusEl = t->ECStatus(0);
  sp.TimeECEl   = t->TimeEC(0);
  sp.PathECEl   = t->PathEC(0);
  sp.Chi2ECEl   = t->Chi2EC(0);
  sp.StatSCEl   = t->StatSC(0);
  sp.SCStatusEl = t->SCStatus(0);
  sp.TimeSCEl   = t->TimeSC(0);
  sp.PathSCEl   = t->PathSC(0);
  sp.StatCCEl   = t->StatCC(0);
  sp.CCStatusEl = t->CCStatus(0);
  sp.NpheEl     = t->Nphe(0);
  sp.Chi2CCEl   = t->Chi2CC(0);
  sp.StatusEl   = t->Status(0);
  // simrec particle (42)
  sp.pid        = particleID(t->GetCategorization(row, targetOption));
  Float_t mass  = particleMass(sp.pid);
  sp.Zh         = t->Zh(row, 0, mass);
  sp.ThetaPQ    = t->ThetaPQ(row, 0);
  sp.PhiPQ      = t->PhiPQ(row, 0);
  sp.Pt2        = t->Pt2(row, 0);
  sp.Pl2        = t->Pl2(row, 0);
  sp.Mx2        = t->Mx2(row, 0, mass);
  sp.T          = t->T(row, 0, mass);
  sp.T4         = t->TimeCorr4(row, mass);
  sp.vxh        = t->X(row);
  sp.vyh        = t->Y(row);
  sp.vzh        = t->Z(row);
  sp.Sector     = t->Sector(row);
  sp.Px         = t->Px(row);
  sp.Py         = t->Py(row);
  sp.Pz         = t->Pz(row);
  sp.P          = t->Momentum(row);
  sp.Betta      = t->Betta(row);
  sp.Mass2      = t->Mass2(row);
  sp.Etot       = t->Etot(row);
  sp.Ein        = t->Ein(row);
  sp.Eout       = t->Eout(row);
  sp.XEC        = t->XEC(row);
  sp.YEC        = t->YEC(row);
  sp.ZEC        = t->ZEC(row);
  sp.deltaZ     = t->Z(row) - vert->Z();
  sp.StatDC     = t->StatDC(row);
  sp.DCStatus   = t->DCStatus(row);
  sp.StatEC     = t->StatEC(row);
  sp.ECStatus   = t->ECStatus(row);
  sp.TimeEC     = t->TimeEC(row);
  sp.PathEC     = t->PathEC(row);
  sp.Chi2EC     = t->Chi2EC(row);
  sp.StatSC     = t->StatSC(row);
  sp.SCStatus   = t->SCStatus(row);
  sp.TimeSC     = t->TimeSC(row);
  sp.PathSC     = t->PathSC(row);
  sp.StatCC     = t->StatCC(row);
  sp.CCStatus   = t->CCStatus(row);
  sp.Nphe       = t->Nphe(row);
  sp.Chi2CC     = t->Chi2CC(row);
  sp.Status     = t->Status(row);
}

void AssignParticleVar_GSIM(TIdentificatorV2* t, sim_p& sp, Int_t row, Int_t evnt, TString targetOption) {
  // event-related (1)
  sp.evnt        = evnt;
  // gsim electron (15)
  sp.mc_Q2       = t->Q2(1);
  sp.mc_W        = t->W(1);
  sp.mc_Nu       = t->Nu(1);
  sp.mc_Xb       = t->Xb(1);
  sp.mc_Yb       = t->Yb(1);
  sp.mc_vxe      = t->X(0, 1);
  sp.mc_vye      = t->Y(0, 1);
  sp.mc_vze      = t->Z(0, 1);
  sp.mc_Sector   = t->Sector(0, 1);
  sp.mc_Px       = t->Px(0, 1);
  sp.mc_Py       = t->Py(0, 1);
  sp.mc_Pz       = t->Pz(0, 1);
  sp.mc_P        = t->Momentum(0, 1);
  sp.mc_Betta    = t->Betta(0, 1);
  TVector3 *mc_vert = new TVector3(t->X(0, 1), t->Y(0, 1), t->Z(0, 1));
  sp.mc_TargType = t->TargType(mc_vert, targetOption);
  // gsim particle (19)
  sp.mc_pid     = t->Id(row, 1);
  Float_t mc_mass = particleMass(sp.mc_pid);
  sp.mc_ThetaPQ = t->ThetaPQ(row, 1);
  sp.mc_PhiPQ   = t->PhiPQ(row, 1);
  sp.mc_Pt2     = t->Pt2(row, 1);
  sp.mc_Pl2     = t->Pl2(row, 1);
  sp.mc_Zh      = t->Zh(row, 1, mc_mass);
  sp.mc_Mx2     = t->Mx2(row, 1, mc_mass);
  sp.mc_T       = t->T(row, 1, mc_mass);
  sp.mc_vxh     = t->X(row, 1);
  sp.mc_vyh     = t->Y(row, 1);
  sp.mc_vzh     = t->Z(row, 1);
  sp.mc_Sector  = t->Sector(row, 1);
  sp.mc_Px      = t->Px(row, 1);
  sp.mc_Py      = t->Py(row, 1);
  sp.mc_Pz      = t->Pz(row, 1);
  sp.mc_P       = t->Momentum(row, 1);
  sp.mc_Betta   = t->Betta(row, 1);
  sp.mc_Mass2   = t->Mass2(row, 1);
  sp.mc_deltaZ  = t->Z(row, 1) - mc_vert->Z();
}

/************************/
/*** VECTOR FUNCTIONS ***/
/***                  ***/
/************************/

RVec<Int_t> SortByMomentum(TIdentificatorV2* t, RVec<Int_t> row, Int_t kind) {
  // Returns a new "row2" where row values are sorted by their respective momentum (from lower to higher)
  // Argsort() creates an indices-vector with the indices sorted by the input-vector values
  // Take(input-vector, indices-vector) creates a sorted-vector by moving all input-vector indices to match the order assigned by the indices-vector
  // but first, fill the momentum vector
  RVec<Float_t> momentum;
  for (Int_t m = 0; m < (Int_t) row.size(); m++) {
    momentum.push_back(t->Momentum(row[m], kind));
  }
  RVec<Int_t> indices = Argsort(momentum);
  RVec<Int_t> row2 = Take(row, indices);
  return row2;
}

RVec<Int_t> AngularMatching(TIdentificatorV2* t, RVec<Int_t> simrec_row, RVec<Int_t> gsim_row) {
  // Matches the "simrec_row" vector with the "gsim_row" vector under angular matching
  // Returns a new "simrec_row2" with the following features:
  // - same size than the "gsim_row" vector
  // - simrec rows in the same position than the matched gsim vector
  // - empty rows are filled with "-1"

  // define vector sizes - loop length
  Int_t N = (Int_t) simrec_row.size();
  Int_t M = (Int_t) gsim_row.size();
  
  // define output vector
  RVec<Int_t> simrec_row2;
  simrec_row2.resize(M, -1); // M ints with value -1
  
  RVec<Int_t> simrec_notused;
  RVec<Int_t> gsim_used;

  Bool_t wasUsed;
  
  // n, m are the vectors' indices
  for (Int_t n = 0; n < N; n++) {
    for (Int_t m = 0; m < M; m++) {

      // std::find function returns an iterator to the first element in the range ["first","last"[ that compares equal to "value"
      // if no such element is found, the function returns "last"
      wasUsed = (std::find(gsim_used.begin(), gsim_used.end(), gsim_row[m]) != gsim_used.end());
      
      // set momentum vectors
      TVector3 simrec_Pvec(t->Px(simrec_row[n], 0), t->Py(simrec_row[n], 0), t->Pz(simrec_row[n], 0));
      TVector3 gsim_Pvec(t->Px(gsim_row[m], 1), t->Py(gsim_row[m], 1), t->Pz(gsim_row[m], 1));
      
      if (TMath::RadToDeg()*simrec_Pvec.Angle(gsim_Pvec) < 10 && !wasUsed) {
	simrec_row2[m] = simrec_row[n];   // assign to output vector
	gsim_used.push_back(gsim_row[m]); // add gsim_row to gsim_used
	m = M;                            // jump to next iteration in n
      } else if (m == M-1) { // last m for a certain n, and haven't found pair yet
	simrec_notused.push_back(simrec_row[n]);
      }
      
    } // end of gsim loop
  } // end of simrec loop

  // fill output vector with not-used simrec_row
  if ((Int_t) simrec_notused.size() != 0) {
    Int_t counter = 0;
    for (Int_t q = 0; q < M; q++) {
      if (simrec_row2[q] == -1 && counter < (Int_t) simrec_notused.size()) {
	simrec_row2[q] = simrec_notused[counter]; // assign first element found in not-used vector
	counter++;                                // jump to next element in not-used vector
      }
    }
  }
  
  return simrec_row2;
}
