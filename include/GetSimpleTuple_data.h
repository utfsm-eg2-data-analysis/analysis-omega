#include "TIdentificatorV2.h"
#include "GSTtree.h"

#include "analysisConfig.h"

void SetElectronBranches_Data(TTree *tree, data_e& de) {
  tree->Branch("Q2",       &de.Q2);
  tree->Branch("W",        &de.W);
  tree->Branch("Nu",       &de.Nu);
  tree->Branch("Xb",       &de.Xb);
  tree->Branch("Yb",       &de.Yb);
  tree->Branch("vxe",      &de.vxe);
  tree->Branch("vye",      &de.vye);
  tree->Branch("vze",      &de.vze);
  tree->Branch("Sector",   &de.Sector);
  tree->Branch("TargType", &de.TargType);
  tree->Branch("Px",       &de.Px);
  tree->Branch("Py",       &de.Py);
  tree->Branch("Pz",       &de.Pz);
  tree->Branch("P",        &de.P);
  tree->Branch("Betta",    &de.Betta);
  tree->Branch("Etot",     &de.Etot);
  tree->Branch("Ein",      &de.Ein);
  tree->Branch("Eout",     &de.Eout);
  tree->Branch("vxec",     &de.vxec);
  tree->Branch("vyec",     &de.vyec);
  tree->Branch("vzec",     &de.vzec);
  tree->Branch("XEC",      &de.XEC);
  tree->Branch("YEC",      &de.YEC);
  tree->Branch("ZEC",      &de.ZEC);
  // status (20)
  tree->Branch("StatDC",   &de.StatDC);
  tree->Branch("DCStatus", &de.DCStatus);
  tree->Branch("StatEC",   &de.StatEC);
  tree->Branch("ECStatus", &de.ECStatus);
  tree->Branch("TimeEC",   &de.TimeEC);
  tree->Branch("PathEC",   &de.PathEC);
  tree->Branch("Chi2EC",   &de.Chi2EC);
  tree->Branch("StatSC",   &de.StatSC);
  tree->Branch("SCStatus", &de.SCStatus);
  tree->Branch("TimeSC",   &de.TimeSC);
  tree->Branch("PathSC",   &de.PathSC);
  tree->Branch("StatCC",   &de.StatCC);
  tree->Branch("CCStatus", &de.CCStatus);
  tree->Branch("Nphe",     &de.Nphe);
  tree->Branch("Chi2CC",   &de.Chi2CC);
  tree->Branch("Status",   &de.Status);
  tree->Branch("NRowsDC",  &de.NRowsDC);
  tree->Branch("NRowsEC",  &de.NRowsEC);
  tree->Branch("NRowsSC",  &de.NRowsSC);
  tree->Branch("NRowsCC",  &de.NRowsCC);
  tree->Branch("evnt",     &de.evnt);
}

void SetParticleBranches_Data(TTree *tree, data_p& dp) {
  // electron
  tree->Branch("Q2",         &dp.Q2);
  tree->Branch("W",          &dp.W);
  tree->Branch("Nu",         &dp.Nu);
  tree->Branch("Xb",         &dp.Xb);
  tree->Branch("Yb",         &dp.Yb);
  tree->Branch("vxe",        &dp.vxe);
  tree->Branch("vye",        &dp.vye);
  tree->Branch("vze",        &dp.vze);
  tree->Branch("SectorEl",   &dp.SectorEl);
  tree->Branch("TargType",   &dp.TargType);
  tree->Branch("Pex",        &dp.Pex);
  tree->Branch("Pey",        &dp.Pey);
  tree->Branch("Pez",        &dp.Pez);
  tree->Branch("Pe",         &dp.Pe);
  tree->Branch("BettaEl",    &dp.BettaEl);
  tree->Branch("Etote",      &dp.Etote);
  tree->Branch("Eine",       &dp.Eine);
  tree->Branch("Eoute",      &dp.Eoute);
  tree->Branch("vxec",       &dp.vxec);
  tree->Branch("vyec",       &dp.vyec);
  tree->Branch("vzec",       &dp.vzec);
  tree->Branch("XECe",       &dp.XECe);
  tree->Branch("YECe",       &dp.YECe);
  tree->Branch("ZECe",       &dp.ZECe);
  // status (20)
  tree->Branch("StatDCEl",   &dp.StatDCEl);
  tree->Branch("DCStatusEl", &dp.DCStatusEl);
  tree->Branch("StatECEl",   &dp.StatECEl);
  tree->Branch("ECStatusEl", &dp.ECStatusEl);
  tree->Branch("TimeECEl",   &dp.TimeECEl);
  tree->Branch("PathECEl",   &dp.PathECEl);
  tree->Branch("Chi2ECEl",   &dp.Chi2ECEl);
  tree->Branch("StatSCEl",   &dp.StatSCEl);
  tree->Branch("SCStatusEl", &dp.SCStatusEl);
  tree->Branch("TimeSCEl",   &dp.TimeSCEl);
  tree->Branch("PathSCEl",   &dp.PathSCEl);
  tree->Branch("StatCCEl",   &dp.StatCCEl);
  tree->Branch("CCStatusEl", &dp.CCStatusEl);
  tree->Branch("NpheEl",     &dp.NpheEl);
  tree->Branch("Chi2CCEl",   &dp.Chi2CCEl);
  tree->Branch("StatusEl",   &dp.StatusEl);
  tree->Branch("NRowsDCEl",  &dp.NRowsDCEl);
  tree->Branch("NRowsECEl",  &dp.NRowsECEl);
  tree->Branch("NRowsSCEl",  &dp.NRowsSCEl);
  tree->Branch("NRowsCCEl",  &dp.NRowsCCEl);
  // particle
  tree->Branch("Zh",       &dp.Zh);
  tree->Branch("ThetaPQ",  &dp.ThetaPQ);
  tree->Branch("Pt2",      &dp.Pt2);
  tree->Branch("Pl2",      &dp.Pl2);
  tree->Branch("PhiPQ",    &dp.PhiPQ);
  tree->Branch("Mx2",      &dp.Mx2);
  tree->Branch("T",        &dp.T);
  tree->Branch("vxh",      &dp.vxh);
  tree->Branch("vyh",      &dp.vyh);
  tree->Branch("vzh",      &dp.vzh);
  tree->Branch("Sector",   &dp.Sector);
  tree->Branch("Px",       &dp.Px);
  tree->Branch("Py",       &dp.Py);
  tree->Branch("Pz",       &dp.Pz);
  tree->Branch("P",        &dp.P);
  tree->Branch("Betta",    &dp.Betta);
  tree->Branch("Mass2",    &dp.Mass2);
  tree->Branch("Etot",     &dp.Etot);
  tree->Branch("Ein",      &dp.Ein);
  tree->Branch("Eout",     &dp.Eout);
  tree->Branch("XEC",      &dp.XEC);
  tree->Branch("YEC",      &dp.YEC);
  tree->Branch("ZEC",      &dp.ZEC);
  tree->Branch("pid",      &dp.pid);
  tree->Branch("T4",       &dp.T4);
  tree->Branch("deltaZ",   &dp.deltaZ);
  // status (20)
  tree->Branch("StatDC",   &dp.StatDC);
  tree->Branch("DCStatus", &dp.DCStatus);
  tree->Branch("StatEC",   &dp.StatEC);
  tree->Branch("ECStatus", &dp.ECStatus);
  tree->Branch("TimeEC",   &dp.TimeEC);
  tree->Branch("PathEC",   &dp.PathEC);
  tree->Branch("Chi2EC",   &dp.Chi2EC);
  tree->Branch("StatSC",   &dp.StatSC);
  tree->Branch("SCStatus", &dp.SCStatus);
  tree->Branch("TimeSC",   &dp.TimeSC);
  tree->Branch("PathSC",   &dp.PathSC);
  tree->Branch("StatCC",   &dp.StatCC);
  tree->Branch("CCStatus", &dp.CCStatus);
  tree->Branch("Nphe",     &dp.Nphe);
  tree->Branch("Chi2CC",   &dp.Chi2CC);
  tree->Branch("Status",   &dp.Status);
  tree->Branch("NRowsDC",  &dp.NRowsDC);
  tree->Branch("NRowsEC",  &dp.NRowsEC);
  tree->Branch("NRowsSC",  &dp.NRowsSC);
  tree->Branch("NRowsCC",  &dp.NRowsCC);
  // event
  tree->Branch("evnt", &dp.evnt);
}

void AssignElectronVar_Data(TIdentificatorV2* t, data_e& de, Int_t evnt, TString targetOption) {  
  de.Q2       = t->Q2();
  de.W        = t->W();
  de.Nu       = t->Nu();
  de.Xb       = t->Xb();
  de.Yb       = t->Yb();
  de.vxe      = t->X(0);
  de.vye      = t->Y(0);
  de.vze      = t->Z(0);
  de.Sector   = t->Sector(0);
  de.Px       = t->Px(0);
  de.Py       = t->Py(0);
  de.Pz       = t->Pz(0);
  de.P        = t->Momentum(0);
  de.Betta    = t->Betta(0);
  de.Etot     = t->Etot(0);
  de.Ein      = t->Ein(0);
  de.Eout     = t->Eout(0);
  TVector3 *vert = t->GetCorrectedVert();
  de.vxec     = vert->X();
  de.vyec     = vert->Y();
  de.vzec     = vert->Z();
  de.TargType = t->TargType(vert, targetOption);
  de.XEC      = t->XEC(0);
  de.YEC      = t->YEC(0);
  de.ZEC      = t->ZEC(0);
  de.StatDC   = t->StatDC(0);
  de.DCStatus = t->DCStatus(0);
  de.StatEC   = t->StatEC(0);
  de.ECStatus = t->ECStatus(0);
  de.TimeEC   = t->TimeEC(0);
  de.PathEC   = t->PathEC(0);
  de.Chi2EC   = t->Chi2EC(0);
  de.StatSC   = t->StatSC(0);
  de.SCStatus = t->SCStatus(0);
  de.TimeSC   = t->TimeSC(0);
  de.PathSC   = t->PathSC(0);
  de.StatCC   = t->StatCC(0);
  de.CCStatus = t->CCStatus(0);
  de.Nphe     = t->Nphe(0);
  de.Chi2CC   = t->Chi2CC(0);
  de.Status   = t->Status(0);
  de.NRowsDC  = t->NRowsDC();
  de.NRowsEC  = t->NRowsEC();
  de.NRowsSC  = t->NRowsSC();
  de.NRowsCC  = t->NRowsCC();
  de.evnt     = evnt;
}

void AssignParticleVar_Data(TIdentificatorV2* t, data_p& dp, Int_t row, Int_t evnt, TString targetOption) {
  // electron
  dp.Q2         = t->Q2();
  dp.W          = t->W();
  dp.Nu         = t->Nu();
  dp.Xb         = t->Xb();
  dp.Yb         = t->Yb();
  dp.vxe        = t->X(0);
  dp.vye        = t->Y(0);
  dp.vze        = t->Z(0);
  dp.SectorEl   = t->Sector(0);
  dp.Pex        = t->Px(0);
  dp.Pey        = t->Py(0);
  dp.Pez        = t->Pz(0);
  dp.Pe         = t->Momentum(0);
  dp.BettaEl    = t->Betta(0);
  dp.Etote      = t->Etot(0);
  dp.Eine       = t->Ein(0);
  dp.Eoute      = t->Eout(0);
  TVector3 *vert = t->GetCorrectedVert();
  dp.vxec       = vert->X();
  dp.vyec       = vert->Y();
  dp.vzec       = vert->Z();
  dp.TargType   = t->TargType(vert, targetOption);
  dp.XECe       = t->XEC(0);
  dp.YECe       = t->YEC(0);
  dp.ZECe       = t->ZEC(0);
  dp.StatDCEl   = t->StatDC(0);
  dp.DCStatusEl = t->DCStatus(0);
  dp.StatECEl   = t->StatEC(0);
  dp.ECStatusEl = t->ECStatus(0);
  dp.TimeECEl   = t->TimeEC(0);
  dp.PathECEl   = t->PathEC(0);
  dp.Chi2ECEl   = t->Chi2EC(0);
  dp.StatSCEl   = t->StatSC(0);
  dp.SCStatusEl = t->SCStatus(0);
  dp.TimeSCEl   = t->TimeSC(0);
  dp.PathSCEl   = t->PathSC(0);
  dp.StatCCEl   = t->StatCC(0);
  dp.CCStatusEl = t->CCStatus(0);
  dp.NpheEl     = t->Nphe(0);
  dp.Chi2CCEl   = t->Chi2CC(0);
  dp.StatusEl   = t->Status(0);
  dp.NRowsDCEl  = t->NRowsDC();
  dp.NRowsECEl  = t->NRowsEC();
  dp.NRowsSCEl  = t->NRowsSC();
  dp.NRowsCCEl  = t->NRowsCC();
  // particle
  dp.pid        = particleID(t->GetCategorization(row, targetOption));
  Float_t mass  = particleMass(dp.pid);
  dp.Zh         = t->Zh(row, 0, mass);
  dp.ThetaPQ    = t->ThetaPQ(row, 0);
  dp.PhiPQ      = t->PhiPQ(row, 0);
  dp.Pt2        = t->Pt2(row, 0);
  dp.Pl2        = t->Pl2(row, 0);
  dp.Mx2        = t->Mx2(row, 0, mass);
  dp.T          = t->T(row, 0, mass);
  dp.T4         = t->TimeCorr4(row, mass);
  dp.vxh        = t->X(row);
  dp.vyh        = t->Y(row);
  dp.vzh        = t->Z(row);
  dp.Sector     = t->Sector(row);
  dp.Px         = t->Px(row);
  dp.Py         = t->Py(row);
  dp.Pz         = t->Pz(row);
  dp.P          = t->Momentum(row);
  dp.Betta      = t->Betta(row);
  dp.Mass2      = t->Mass2(row);
  dp.Etot       = t->Etot(row);
  dp.Ein        = t->Ein(row);
  dp.Eout       = t->Eout(row);
  dp.XEC        = t->XEC(row);
  dp.YEC        = t->YEC(row);
  dp.ZEC        = t->ZEC(row);
  dp.deltaZ     = t->Z(row) - vert->Z();
  dp.StatDC     = t->StatDC(row);
  dp.DCStatus   = t->DCStatus(row);
  dp.StatEC     = t->StatEC(row);
  dp.ECStatus   = t->ECStatus(row);
  dp.TimeEC     = t->TimeEC(row);
  dp.PathEC     = t->PathEC(row);
  dp.Chi2EC     = t->Chi2EC(row);
  dp.StatSC     = t->StatSC(row);
  dp.SCStatus   = t->SCStatus(row);
  dp.TimeSC     = t->TimeSC(row);
  dp.PathSC     = t->PathSC(row);
  dp.StatCC     = t->StatCC(row);
  dp.CCStatus   = t->CCStatus(row);
  dp.Nphe       = t->Nphe(row);
  dp.Chi2CC     = t->Chi2CC(row);
  dp.Status     = t->Status(row);
  dp.NRowsDC    = t->NRowsDC();
  dp.NRowsEC    = t->NRowsEC();
  dp.NRowsSC    = t->NRowsSC();
  dp.NRowsCC    = t->NRowsCC();
  dp.evnt       = evnt;
}
