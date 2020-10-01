#include "analysisConfig.h"
#include "FNCtree.h"

#define INVLD -9999

/*** Declaration of functions ***/

Float_t CorrectEnergy(simrec_i& t, TString option);
Float_t CorrectMomentum(simrec_i& t, TString option, TString component);

Float_t PhiPQ(Float_t fPex, Float_t fPey, Float_t fPez, Float_t fPx, Float_t fPy, Float_t fPz);
Float_t ThetaPQ(Float_t fPex, Float_t fPey, Float_t fPez, Float_t fPx, Float_t fPy, Float_t fPz);
Float_t DeltaTheta(Float_t fPex, Float_t fPey, Float_t fPez, Float_t fPx, Float_t fPy, Float_t fPz);

Float_t BettaCalc(Float_t fP, Float_t fPid);

/*** Functions ***/

void SetMinimalBranches(TChain *chain, simrec_i& t, gsim_i& mc_t) {
  // turn off
  chain->SetBranchStatus("*", 0);
  // turn on necessary
  chain->SetBranchStatus("evnt", 1);
  chain->SetBranchStatus("pid", 1);
  chain->SetBranchStatus("mc_pid", 1);
  // set address
  chain->SetBranchAddress("pid",  &t.pid);
  chain->SetBranchAddress("mc_pid", &mc_t.pid);
  chain->SetBranchAddress("evnt", &mc_t.evnt); // always non-null
}

void SetInputBranches(TChain *chain, simrec_i& t, gsim_i& mc_t) {
  // init all variables
  chain->SetBranchStatus("*", 1);
  // electron (40)
  chain->SetBranchAddress("TargType", &t.TargType);
  chain->SetBranchAddress("Q2", &t.Q2);
  chain->SetBranchAddress("W", &t.W);
  chain->SetBranchAddress("Nu", &t.Nu);
  chain->SetBranchAddress("Xb", &t.Xb);
  chain->SetBranchAddress("Yb", &t.Yb);
  chain->SetBranchAddress("SectorEl", &t.SectorEl);  
  chain->SetBranchAddress("Pex", &t.Pex);
  chain->SetBranchAddress("Pey", &t.Pey);
  chain->SetBranchAddress("Pez", &t.Pez);
  chain->SetBranchAddress("Pe", &t.Pe);
  chain->SetBranchAddress("vxe", &t.vxe);  
  chain->SetBranchAddress("vye", &t.vye);
  chain->SetBranchAddress("vze", &t.vze);
  chain->SetBranchAddress("BettaEl", &t.BettaEl);
  chain->SetBranchAddress("Etote", &t.Etote);
  chain->SetBranchAddress("Eine", &t.Eine);
  chain->SetBranchAddress("Eoute", &t.Eoute);
  chain->SetBranchAddress("vxec", &t.vxec);
  chain->SetBranchAddress("vyec", &t.vyec);
  chain->SetBranchAddress("vzec", &t.vzec);
  chain->SetBranchAddress("XECe", &t.XECe);
  chain->SetBranchAddress("YECe", &t.YECe);
  chain->SetBranchAddress("ZECe", &t.ZECe);
  // electron status (16)
  chain->SetBranchAddress("StatDCEl", &t.StatDCEl);
  chain->SetBranchAddress("DCStatusEl", &t.DCStatusEl);
  chain->SetBranchAddress("StatECEl", &t.StatECEl);
  chain->SetBranchAddress("ECStatusEl", &t.ECStatusEl);
  chain->SetBranchAddress("TimeECEl", &t.TimeECEl);
  chain->SetBranchAddress("PathECEl", &t.PathECEl);
  chain->SetBranchAddress("Chi2ECEl", &t.Chi2ECEl);
  chain->SetBranchAddress("StatSCEl", &t.StatSCEl);
  chain->SetBranchAddress("SCStatusEl", &t.SCStatusEl);
  chain->SetBranchAddress("TimeSCEl", &t.TimeSCEl);
  chain->SetBranchAddress("PathSCEl", &t.PathSCEl);
  chain->SetBranchAddress("StatCCEl", &t.StatCCEl);
  chain->SetBranchAddress("CCStatusEl", &t.CCStatusEl);
  chain->SetBranchAddress("NpheEl", &t.NpheEl);
  chain->SetBranchAddress("Chi2CCEl", &t.Chi2CCEl);
  chain->SetBranchAddress("StatusEl", &t.StatusEl);  
  // particle (26)
  chain->SetBranchAddress("Zh", &t.Zh);
  chain->SetBranchAddress("Pt2", &t.Pt2);
  chain->SetBranchAddress("Pl2", &t.Pl2);
  chain->SetBranchAddress("Mx2", &t.Mx2);
  chain->SetBranchAddress("T", &t.T);
  chain->SetBranchAddress("vxh", &t.vxh);
  chain->SetBranchAddress("vyh", &t.vyh);
  chain->SetBranchAddress("vzh", &t.vzh);
  chain->SetBranchAddress("Sector", &t.Sector);
  chain->SetBranchAddress("PhiPQ", &t.PhiPQ);
  chain->SetBranchAddress("ThetaPQ", &t.ThetaPQ);
  chain->SetBranchAddress("Etot", &t.Etot);
  chain->SetBranchAddress("Ein", &t.Ein);
  chain->SetBranchAddress("Eout", &t.Eout);
  chain->SetBranchAddress("Px", &t.Px);
  chain->SetBranchAddress("Py", &t.Py);
  chain->SetBranchAddress("Pz", &t.Pz);
  chain->SetBranchAddress("P", &t.P);
  chain->SetBranchAddress("XEC", &t.XEC);
  chain->SetBranchAddress("YEC", &t.YEC);
  chain->SetBranchAddress("ZEC", &t.ZEC);
  chain->SetBranchAddress("pid", &t.pid);
  chain->SetBranchAddress("Betta", &t.Betta);
  chain->SetBranchAddress("Mass2", &t.Mass2);
  chain->SetBranchAddress("T4", &t.T4);
  chain->SetBranchAddress("deltaZ", &t.deltaZ);
  // status (16)
  chain->SetBranchAddress("StatDC", &t.StatDC);
  chain->SetBranchAddress("DCStatus", &t.DCStatus);
  chain->SetBranchAddress("StatEC", &t.StatEC);
  chain->SetBranchAddress("ECStatus", &t.ECStatus);
  chain->SetBranchAddress("TimeEC", &t.TimeEC);
  chain->SetBranchAddress("PathEC", &t.PathEC);
  chain->SetBranchAddress("Chi2EC", &t.Chi2EC);
  chain->SetBranchAddress("StatSC", &t.StatSC);
  chain->SetBranchAddress("SCStatus", &t.SCStatus);
  chain->SetBranchAddress("TimeSC", &t.TimeSC);
  chain->SetBranchAddress("PathSC", &t.PathSC);
  chain->SetBranchAddress("StatCC", &t.StatCC);
  chain->SetBranchAddress("CCStatus", &t.CCStatus);
  chain->SetBranchAddress("Nphe", &t.Nphe);
  chain->SetBranchAddress("Chi2CC", &t.Chi2CC);
  chain->SetBranchAddress("Status", &t.Status);
  // (34 variables for gsim)
  // electron (15)
  chain->SetBranchAddress("mc_Q2", &mc_t.Q2);
  chain->SetBranchAddress("mc_W", &mc_t.W);
  chain->SetBranchAddress("mc_Nu", &mc_t.Nu);
  chain->SetBranchAddress("mc_Xb", &mc_t.Xb);
  chain->SetBranchAddress("mc_Yb", &mc_t.Yb);
  chain->SetBranchAddress("mc_vxe", &mc_t.vxe);
  chain->SetBranchAddress("mc_vye", &mc_t.vye);
  chain->SetBranchAddress("mc_vze", &mc_t.vze);
  chain->SetBranchAddress("mc_SectorEl", &mc_t.SectorEl);
  chain->SetBranchAddress("mc_TargType", &mc_t.TargType);
  chain->SetBranchAddress("mc_Pex", &mc_t.Pex);
  chain->SetBranchAddress("mc_Pey", &mc_t.Pey);
  chain->SetBranchAddress("mc_Pez", &mc_t.Pez);
  chain->SetBranchAddress("mc_Pe", &mc_t.Pe);
  chain->SetBranchAddress("mc_BettaEl", &mc_t.BettaEl);
  // particle (19)
  chain->SetBranchAddress("mc_Zh", &mc_t.Zh);
  chain->SetBranchAddress("mc_ThetaPQ", &mc_t.ThetaPQ);
  chain->SetBranchAddress("mc_Pt2", &mc_t.Pt2);
  chain->SetBranchAddress("mc_Pl2", &mc_t.Pl2);
  chain->SetBranchAddress("mc_PhiPQ", &mc_t.PhiPQ);
  chain->SetBranchAddress("mc_Mx2", &mc_t.Mx2);
  chain->SetBranchAddress("mc_T", &mc_t.T);
  chain->SetBranchAddress("mc_vxh", &mc_t.vxh);
  chain->SetBranchAddress("mc_vyh", &mc_t.vyh);
  chain->SetBranchAddress("mc_vzh", &mc_t.vzh);
  chain->SetBranchAddress("mc_Sector", &mc_t.Sector);
  chain->SetBranchAddress("mc_Px", &mc_t.Px);
  chain->SetBranchAddress("mc_Py", &mc_t.Py);
  chain->SetBranchAddress("mc_Pz", &mc_t.Pz);
  chain->SetBranchAddress("mc_P", &mc_t.P);
  chain->SetBranchAddress("mc_Betta", &mc_t.Betta);
  chain->SetBranchAddress("mc_Mass2", &mc_t.Mass2);
  chain->SetBranchAddress("mc_pid", &mc_t.pid);
  chain->SetBranchAddress("mc_deltaZ", &mc_t.deltaZ);
  // evnt related (1)
  chain->SetBranchAddress("evnt", &mc_t.evnt);
}

void SetOriginalBranches(TTree *tree, simrec_o& o, gsim_o& mc_o) {
  // electron (41)
  // all (25)
  tree->Branch("Q2", &o.Q2);
  tree->Branch("W",  &o.W);
  tree->Branch("Nu", &o.Nu);
  tree->Branch("Xb", &o.Xb);
  tree->Branch("Yb", &o.Yb);
  tree->Branch("Xe", &o.Xe);
  tree->Branch("Ye", &o.Ye);
  tree->Branch("Ze", &o.Ze);
  tree->Branch("SectorEl", &o.SectorEl);
  tree->Branch("TargType", &o.TargType);
  tree->Branch("Pex", &o.Pex);
  tree->Branch("Pey", &o.Pey);
  tree->Branch("Pez", &o.Pez);
  tree->Branch("Pe", &o.Pe);
  tree->Branch("P2e", &o.P2e);
  tree->Branch("BettaEl", &o.BettaEl);
  tree->Branch("Etote", &o.Etote);
  tree->Branch("Eine", &o.Eine);
  tree->Branch("Eoute", &o.Eoute);
  tree->Branch("Xec", &o.Xec);
  tree->Branch("Yec", &o.Yec);
  tree->Branch("Zec", &o.Zec);
  tree->Branch("XECe", &o.XECe);
  tree->Branch("YECe", &o.YECe);
  tree->Branch("ZECe", &o.ZECe);
  tree->Branch("StatDCEl", &o.StatDCEl);
  tree->Branch("DCStatusEl", &o.DCStatusEl);
  tree->Branch("StatECEl", &o.StatECEl);
  tree->Branch("ECStatusEl", &o.ECStatusEl);
  tree->Branch("TimeECEl", &o.TimeECEl);
  tree->Branch("PathECEl", &o.PathECEl);
  tree->Branch("Chi2ECEl", &o.Chi2ECEl);
  tree->Branch("StatSCEl", &o.StatSCEl);
  tree->Branch("SCStatusEl", &o.SCStatusEl);
  tree->Branch("TimeSCEl", &o.TimeSCEl);
  tree->Branch("PathSCEl", &o.PathSCEl);
  tree->Branch("StatCCEl", &o.StatCCEl);
  tree->Branch("CCStatusEl", &o.CCStatusEl);
  tree->Branch("NpheEl", &o.NpheEl);
  tree->Branch("Chi2CCEl", &o.Chi2CCEl);
  tree->Branch("StatusEl", &o.StatusEl);
  // independent (16)
  tree->Branch("Etot", &o.Etot);
  tree->Branch("Ein", &o.Ein);
  tree->Branch("Eout", &o.Eout);
  tree->Branch("Betta", &o.Betta);
  tree->Branch("Mass2", &o.Mass2);
  tree->Branch("T4", &o.T4);
  tree->Branch("vxh", &o.vxh);
  tree->Branch("vyh", &o.vyh);
  tree->Branch("vzh", &o.vzh);
  tree->Branch("deltaZ", &o.deltaZ);
  tree->Branch("XEC", &o.XEC);
  tree->Branch("YEC", &o.YEC);
  tree->Branch("ZEC", &o.ZEC);
  tree->Branch("Sector", &o.Sector);
  tree->Branch("Pid", &o.Pid);
  tree->Branch("M", &o.M);
  // prev (6)
  tree->Branch("E_prev",  &o.E_prev);
  tree->Branch("Px_prev", &o.Px_prev);
  tree->Branch("Py_prev", &o.Py_prev);
  tree->Branch("Pz_prev", &o.Pz_prev);
  tree->Branch("P2_prev", &o.P2_prev);
  tree->Branch("P_prev",  &o.P_prev);
  // true (6)
  tree->Branch("E_true",  &o.E_true);
  tree->Branch("Px_true", &o.Px_true);
  tree->Branch("Py_true", &o.Py_true);
  tree->Branch("Pz_true", &o.Pz_true);
  tree->Branch("P2_true", &o.P2_true);
  tree->Branch("P_true",  &o.P_true);
  // corr (6)
  tree->Branch("E_corr",  &o.E_corr);
  tree->Branch("Px_corr", &o.Px_corr);
  tree->Branch("Py_corr", &o.Py_corr);
  tree->Branch("Pz_corr", &o.Pz_corr);
  tree->Branch("P2_corr", &o.P2_corr);
  tree->Branch("P_corr",  &o.P_corr);
  // remaining (10)
  tree->Branch("Z", &o.Z);
  tree->Branch("PhiPQ", &o.PhiPQ);
  tree->Branch("ThetaPQ", &o.ThetaPQ);
  tree->Branch("CosThetaPQ", &o.CosThetaPQ);
  tree->Branch("Pt2", &o.Pt2);
  tree->Branch("Pl2", &o.Pl2);
  tree->Branch("Mx2", &o.Mx2);
  tree->Branch("T", &o.T);
  tree->Branch("BettaCalc", &o.BettaCalc);
  tree->Branch("deltaTheta", &o.deltaTheta);
  // status (16)
  tree->Branch("StatDC", &o.StatDC);
  tree->Branch("DCStatus", &o.DCStatus);
  tree->Branch("StatEC", &o.StatEC);
  tree->Branch("ECStatus", &o.ECStatus);
  tree->Branch("TimeEC", &o.TimeEC);
  tree->Branch("PathEC", &o.PathEC);
  tree->Branch("Chi2EC", &o.Chi2EC);
  tree->Branch("StatSC", &o.StatSC);
  tree->Branch("SCStatus", &o.SCStatus);
  tree->Branch("TimeSC", &o.TimeSC);
  tree->Branch("PathSC", &o.PathSC);
  tree->Branch("StatCC", &o.StatCC);
  tree->Branch("CCStatus", &o.CCStatus);
  tree->Branch("Nphe", &o.Nphe);
  tree->Branch("Chi2CC", &o.Chi2CC);
  tree->Branch("Status", &o.Status);
  // event-related (2)
  tree->Branch("Entry", &o.Entry);
  // (41 variables for gsim)
  // electron (16)
  tree->Branch("mc_Q2", &mc_o.Q2);
  tree->Branch("mc_W", &mc_o.W);
  tree->Branch("mc_Nu", &mc_o.Nu);
  tree->Branch("mc_Xb", &mc_o.Xb);
  tree->Branch("mc_Yb", &mc_o.Yb);
  tree->Branch("mc_Xe", &mc_o.Xe);
  tree->Branch("mc_Ye", &mc_o.Ye);
  tree->Branch("mc_Ze", &mc_o.Ze);
  tree->Branch("mc_SectorEl", &mc_o.SectorEl);
  tree->Branch("mc_TargType", &mc_o.TargType);
  tree->Branch("mc_Pex", &mc_o.Pex);
  tree->Branch("mc_Pey", &mc_o.Pey);
  tree->Branch("mc_Pez", &mc_o.Pez);
  tree->Branch("mc_Pe", &mc_o.Pe);
  tree->Branch("mc_BettaEl", &mc_o.BettaEl);
  tree->Branch("mc_P2e", &mc_o.P2e);
  // particle (25)
  tree->Branch("mc_vxh", &mc_o.vxh);
  tree->Branch("mc_vyh", &mc_o.vyh);
  tree->Branch("mc_vzh", &mc_o.vzh);
  tree->Branch("mc_Sector", &mc_o.Sector);
  tree->Branch("mc_Betta", &mc_o.Betta);
  tree->Branch("mc_Mass2", &mc_o.Mass2);
  tree->Branch("mc_Pid", &mc_o.Pid);
  tree->Branch("mc_deltaZ", &mc_o.deltaZ);
  tree->Branch("mc_M", &mc_o.M);
  tree->Branch("mc_E", &mc_o.E);
  tree->Branch("mc_Px", &mc_o.Px);
  tree->Branch("mc_Py", &mc_o.Py);
  tree->Branch("mc_Pz", &mc_o.Pz);
  tree->Branch("mc_P2", &mc_o.P2);
  tree->Branch("mc_P", &mc_o.P);
  tree->Branch("mc_Z", &mc_o.Z);
  tree->Branch("mc_ThetaPQ", &mc_o.ThetaPQ);
  tree->Branch("mc_Pt2", &mc_o.Pt2);
  tree->Branch("mc_Pl2", &mc_o.Pl2);
  tree->Branch("mc_PhiPQ", &mc_o.PhiPQ);
  tree->Branch("mc_Mx2", &mc_o.Mx2);
  tree->Branch("mc_T", &mc_o.T);
  tree->Branch("mc_CosThetaPQ", &mc_o.CosThetaPQ);
  tree->Branch("mc_BettaCalc", &mc_o.BettaCalc);
  tree->Branch("mc_deltaTheta", &mc_o.deltaTheta);
  // event-related (2)
  tree->Branch("Event", &mc_o.Event);
  tree->Branch("mc_Entry", &mc_o.Entry);
}

void NullOriginalVar_SIMREC(simrec_o& o) {
  // electron (41)
  o.Q2 = INVLD; o.W = INVLD; o.Nu = INVLD; o.Xb = INVLD; o.Yb = INVLD;
  o.Xe = INVLD; o.Ye = INVLD; o.Ze = INVLD;
  o.SectorEl = INVLD;
  o.TargType = INVLD;
  o.Pex = INVLD; o.Pey = INVLD; o.Pez = INVLD; o.Pe = INVLD; o.P2e = INVLD;
  o.BettaEl = INVLD;
  o.Etote = INVLD; o.Eine = INVLD; o.Eoute = INVLD;
  o.Xec = INVLD; o.Yec = INVLD; o.Zec = INVLD;
  o.XECe = INVLD; o.YECe = INVLD; o.ZECe = INVLD;
  o.StatDCEl   = INVLD;
  o.DCStatusEl = INVLD;
  o.StatECEl   = INVLD;
  o.ECStatusEl = INVLD;
  o.TimeECEl  = INVLD;
  o.PathECEl  = INVLD;
  o.Chi2ECEl  = INVLD;
  o.StatSCEl  = INVLD;
  o.SCStatusEl = INVLD;
  o.TimeSCEl  = INVLD;
  o.PathSCEl  = INVLD;
  o.StatCCEl  = INVLD;
  o.CCStatusEl = INVLD;
  o.NpheEl    = INVLD;
  o.Chi2CCEl  = INVLD;
  o.StatusEl  = INVLD;
  // independent variables (16)
  o.vxh = INVLD; o.vyh = INVLD; o.vzh = INVLD;
  o.Sector = INVLD;
  o.Etot = INVLD; o.Ein = INVLD; o.Eout = INVLD;
  o.XEC = INVLD; o.YEC = INVLD; o.ZEC = INVLD;
  o.deltaZ = INVLD;
  o.Betta = INVLD;
  o.Mass2 = INVLD;
  o.T4 = INVLD;
  o.Pid = INVLD;
  o.M = INVLD;
  // prev (6)
  o.E_prev = INVLD; o.Px_prev = INVLD; o.Py_prev = INVLD; o.Pz_prev = INVLD; o.P_prev = INVLD; o.P2_prev = INVLD;
  // true (6)
  o.E_true = INVLD; o.Px_true = INVLD; o.Py_true = INVLD; o.Pz_true = INVLD; o.P2_true = INVLD; o.P_true = INVLD;
  // corr (6)
  o.E_corr = INVLD; o.Px_corr = INVLD; o.Py_corr = INVLD; o.Pz_corr = INVLD; o.P2_corr = INVLD; o.P_corr = INVLD;
  // remaining (10)
  o.Z = INVLD;
  o.PhiPQ = INVLD;
  o.ThetaPQ = INVLD;
  o.CosThetaPQ = INVLD;
  o.Pt2 = INVLD;
  o.Pl2 = INVLD;
  o.Mx2 = INVLD;
  o.T = INVLD;
  o.BettaCalc = INVLD;
  o.deltaTheta = INVLD;
  // status (16)
  o.StatDC  = INVLD;
  o.DCStatus = INVLD;
  o.StatEC  = INVLD;
  o.ECStatus = INVLD;
  o.TimeEC  = INVLD;
  o.PathEC  = INVLD;
  o.Chi2EC  = INVLD;
  o.StatSC  = INVLD;
  o.SCStatus = INVLD;
  o.TimeSC  = INVLD;
  o.PathSC  = INVLD;
  o.StatCC  = INVLD;
  o.CCStatus = INVLD;
  o.Nphe   = INVLD;
  o.Chi2CC  = INVLD;
  o.Status  = INVLD;
  // event-related (1)
  o.Entry = INVLD;
}

void AssignOriginalVar_SIMREC(simrec_i& t, simrec_o& o, Int_t entry) {
  // electron (41)
  o.Q2 = t.Q2;
  o.W  = t.W;
  o.Nu = t.Nu;
  o.Xb = t.Xb;
  o.Yb = t.Yb;
  o.Xe = t.vxe; o.Ye = t.vye; o.Ze = t.vze;
  o.SectorEl = t.SectorEl;
  o.TargType = t.TargType;
  o.Pex = t.Pex; o.Pey = t.Pey; o.Pez = t.Pez; o.Pe = t.Pe; o.P2e = o.Pe*o.Pe;
  o.BettaEl = t.BettaEl;
  o.Etote = t.Etote;
  o.Eine  = t.Eine;
  o.Eoute = t.Eoute;
  o.Xec = t.vxec;
  o.Yec = t.vyec;
  o.Zec = t.vzec;
  o.XECe = t.XECe;
  o.YECe = t.YECe;
  o.ZECe = t.ZECe;
  o.StatDCEl   = t.StatDCEl;
  o.DCStatusEl = t.DCStatusEl;
  o.StatECEl   = t.StatECEl;
  o.ECStatusEl = t.ECStatusEl;
  o.TimeECEl   = t.TimeECEl;
  o.PathECEl   = t.PathECEl;
  o.Chi2ECEl   = t.Chi2ECEl;
  o.StatSCEl   = t.StatSCEl;
  o.SCStatusEl = t.SCStatusEl;
  o.TimeSCEl   = t.TimeSCEl;
  o.PathSCEl   = t.PathSCEl;
  o.StatCCEl   = t.StatCCEl;
  o.CCStatusEl = t.CCStatusEl;
  o.NpheEl     = t.NpheEl;
  o.Chi2CCEl   = t.Chi2CCEl;
  o.StatusEl   = t.StatusEl;
  // independent variables (16)
  o.vxh = t.vxh;
  o.vyh = t.vyh;
  o.vzh = t.vzh;
  o.Sector = t.Sector;
  o.Etot = t.Etot;
  o.Ein  = t.Ein;
  o.Eout = t.Eout;
  o.XEC = t.XEC;
  o.YEC = t.YEC;
  o.ZEC = t.ZEC;
  o.deltaZ = t.deltaZ;
  o.Betta = t.Betta;
  o.Mass2 = t.Mass2;
  o.T4 = t.T4;
  o.Pid = t.pid; // important!
  o.M = particleMass(t.pid);
  // prev (6)
  o.E_prev  = CorrectEnergy(t, "prev");
  o.Px_prev = t.Px;
  o.Py_prev = t.Py;
  o.Pz_prev = t.Pz;
  o.P_prev  = t.P;
  o.P2_prev = o.P_prev*o.P_prev; // recalc
  // true (6)
  o.E_true  = CorrectEnergy(t, "true");
  o.Px_true = CorrectMomentum(t, "x", "true");
  o.Py_true = CorrectMomentum(t, "y", "true");
  o.Pz_true = CorrectMomentum(t, "z", "true");
  o.P2_true = o.Px_true*o.Px_true + o.Py_true*o.Py_true + o.Pz_true*o.Pz_true;
  o.P_true  = TMath::Sqrt(o.P2_true);
  // corr (6)
  o.E_corr  = CorrectEnergy(t, "corr");
  o.Px_corr = CorrectMomentum(t, "x", "corr");
  o.Py_corr = CorrectMomentum(t, "y", "corr");
  o.Pz_corr = CorrectMomentum(t, "z", "corr");
  o.P2_corr = o.Px_corr*o.Px_corr + o.Py_corr*o.Py_corr + o.Pz_corr*o.Pz_corr;
  o.P_corr  = TMath::Sqrt(o.P2_corr);
  // remaining (10) - using corr values
  o.Z          = o.E_corr/o.Nu;
  o.PhiPQ      = PhiPQ(t.Pex, t.Pey, t.Pez, o.Px_corr, o.Py_corr, o.Pz_corr);
  o.ThetaPQ    = ThetaPQ(t.Pex, t.Pey, t.Pez, o.Px_corr, o.Py_corr, o.Pz_corr);
  o.CosThetaPQ = ((kEbeam - o.Pez)*o.Pz_corr - o.Pex*o.Px_corr - o.Pey*o.Py_corr)/(TMath::Sqrt(o.P2_corr*(o.Q2 + o.Nu*o.Nu)));
  o.Pt2        = o.P2_corr*(1 - o.CosThetaPQ*o.CosThetaPQ);
  o.Pl2        = o.P2_corr*o.CosThetaPQ*o.CosThetaPQ;
  o.Mx2        = t.W*t.W + o.M*o.M - 2*o.Z*o.Nu*o.Nu + 2*TMath::Sqrt(o.Pl2*(o.Nu*o.Nu + o.Q2)) - 2*kMproton*o.Z*o.Nu;
  o.T          = o.M*o.M - 2*o.Z*o.Nu*o.Nu + 2*TMath::Sqrt(o.Pl2*(o.Nu*o.Nu + o.Q2)) - o.Q2;
  o.BettaCalc  = BettaCalc(o.P_corr, o.Pid);
  o.deltaTheta = DeltaTheta(t.Pex, t.Pey, t.Pez, o.Px_corr, o.Py_corr, o.Pz_corr);
  // status (16)
  o.StatDC   = t.StatDC;
  o.DCStatus = t.DCStatus;
  o.StatEC   = t.StatEC;
  o.ECStatus = t.ECStatus;
  o.TimeEC   = t.TimeEC;
  o.PathEC   = t.PathEC;
  o.Chi2EC   = t.Chi2EC;
  o.StatSC   = t.StatSC;
  o.SCStatus = t.SCStatus;
  o.TimeSC   = t.TimeSC;
  o.PathSC   = t.PathSC;
  o.StatCC   = t.StatCC;
  o.CCStatus = t.CCStatus;
  o.Nphe     = t.Nphe;
  o.Chi2CC   = t.Chi2CC;
  o.Status   = t.Status;
  // event-related (1)
  o.Entry = (Float_t) entry;
}

void AssignOriginalVar_GSIM(gsim_i& mc_t, gsim_o& mc_o, Int_t entry) {
  // electron (16)
  mc_o.Q2 = mc_t.Q2;
  mc_o.W  = mc_t.W;
  mc_o.Nu = mc_t.Nu;
  mc_o.Xb = mc_t.Xb;
  mc_o.Yb = mc_t.Yb;
  mc_o.Xe = mc_t.vxe;
  mc_o.Ye = mc_t.vye;
  mc_o.Ze = mc_t.vze;
  mc_o.SectorEl = mc_t.SectorEl;
  mc_o.TargType = mc_t.TargType;
  mc_o.Pex = mc_t.Pex;
  mc_o.Pey = mc_t.Pey;
  mc_o.Pez = mc_t.Pez;
  mc_o.Pe  = mc_t.Pe;
  mc_o.BettaEl = mc_t.BettaEl;
  mc_o.P2e = mc_o.Pe*mc_o.Pe;
  // particle (25)
  mc_o.vxh = mc_t.vxh;
  mc_o.vyh = mc_t.vyh;
  mc_o.vzh = mc_t.vzh;
  mc_o.Sector = mc_t.Sector;
  mc_o.Betta = mc_t.Betta;
  mc_o.Mass2 = mc_t.Mass2;
  mc_o.Pid = mc_t.pid; // important!
  mc_o.deltaZ = mc_t.deltaZ;
  mc_o.Px = mc_t.Px;
  mc_o.Py = mc_t.Py;
  mc_o.Pz = mc_t.Pz;
  mc_o.P = mc_t.P;
  mc_o.Z = mc_t.Zh;
  mc_o.ThetaPQ = mc_t.ThetaPQ;
  mc_o.Pt2 = mc_t.Pt2;
  mc_o.Pl2 = mc_t.Pl2;
  mc_o.PhiPQ = mc_t.PhiPQ;
  mc_o.Mx2 = mc_t.Mx2;
  mc_o.T = mc_t.T;
  mc_o.P2 = mc_o.P*mc_o.P;
  mc_o.M  = particleMass(mc_o.Pid);
  mc_o.E  = TMath::Sqrt(mc_o.P2 + mc_o.M*mc_o.M);
  mc_o.CosThetaPQ = ((kEbeam - mc_o.Pez)*mc_o.Pz - mc_o.Pex*mc_o.Px - mc_o.Pey*mc_o.Py)/(TMath::Sqrt(mc_o.P2*(mc_o.Q2 + mc_o.Nu*mc_o.Nu)));
  mc_o.BettaCalc  = BettaCalc(mc_o.P, mc_o.Pid);
  mc_o.deltaTheta = DeltaTheta(mc_t.Pex, mc_t.Pey, mc_t.Pez, mc_o.Px, mc_o.Py, mc_o.Pz);
  // event-related (2)
  mc_o.Event = mc_t.evnt; // important!
  mc_o.Entry = (Float_t) entry;
}

void SetMixBranches(TTree *tree, simrec_m& m, simrec_pi0& pi0, simrec_w& w, gsim_m& mc_m, gsim_pi0& mc_pi0, gsim_w& mc_w) {
  // electron (41)
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
  tree->Branch("Pe",  &m.Pe);
  tree->Branch("P2e", &m.P2e);
  tree->Branch("BettaEl", &m.BettaEl);
  tree->Branch("Etote", &m.Etote);
  tree->Branch("Eine", &m.Eine);
  tree->Branch("Eoute", &m.Eoute);
  tree->Branch("Xec", &m.Xec);
  tree->Branch("Yec", &m.Yec);
  tree->Branch("Zec", &m.Zec);
  tree->Branch("XECe", &m.XECe);
  tree->Branch("YECe", &m.YECe);
  tree->Branch("ZECe", &m.ZECe);
  tree->Branch("StatDCEl", &m.StatDCEl);
  tree->Branch("DCStatusEl", &m.DCStatusEl);
  tree->Branch("StatECEl", &m.StatECEl);
  tree->Branch("ECStatusEl", &m.ECStatusEl);
  tree->Branch("TimeECEl", &m.TimeECEl);
  tree->Branch("PathECEl", &m.PathECEl);
  tree->Branch("Chi2ECEl", &m.Chi2ECEl);
  tree->Branch("StatSCEl", &m.StatSCEl);
  tree->Branch("SCStatusEl", &m.SCStatusEl);
  tree->Branch("TimeSCEl", &m.TimeSCEl);
  tree->Branch("PathSCEl", &m.PathSCEl);
  tree->Branch("StatCCEl", &m.StatCCEl);
  tree->Branch("CCStatusEl", &m.CCStatusEl);
  tree->Branch("NpheEl", &m.NpheEl);
  tree->Branch("Chi2CCEl", &m.Chi2CCEl);
  tree->Branch("StatusEl", &m.StatusEl);
  // independent (16)
  tree->Branch("vxh", &m.vxh, "vxh[4]/F");
  tree->Branch("vyh", &m.vyh, "vyh[4]/F");
  tree->Branch("vzh", &m.vzh, "vzh[4]/F");
  tree->Branch("Sector", &m.Sector, "Sector[4]/F");
  tree->Branch("Betta", &m.Betta, "Betta[4]/F");
  tree->Branch("Mass2", &m.Mass2, "Mass2[4]/F");
  tree->Branch("Etot", &m.Etot, "Etot[4]/F");
  tree->Branch("Ein", &m.Ein, "Ein[4]/F");
  tree->Branch("Eout", &m.Eout, "Eout[4]/F");
  tree->Branch("XEC", &m.XEC, "XEC[4]/F");
  tree->Branch("YEC", &m.YEC, "YEC[4]/F");
  tree->Branch("ZEC", &m.ZEC, "ZEC[4]/F");
  tree->Branch("Pid", &m.Pid, "Pid[4]/F");
  tree->Branch("M", &m.M, "M[4]/F");
  tree->Branch("T4", &m.T4, "T4[4]/F");
  tree->Branch("deltaZ", &m.deltaZ, "deltaZ[4]/F");
  // prev (6)
  tree->Branch("Px_prev", &m.Px_prev, "Px_prev[4]/F");
  tree->Branch("Py_prev", &m.Py_prev, "Py_prev[4]/F");
  tree->Branch("Pz_prev", &m.Pz_prev, "Pz_prev[4]/F");
  tree->Branch("P2_prev", &m.P2_prev, "P2_prev[4]/F");
  tree->Branch("P_prev", &m.P_prev, "P_prev[4]/F");
  tree->Branch("E_prev", &m.E_prev, "E_prev[4]/F");
  // true (6)
  tree->Branch("Px_true", &m.Px_true, "Px_true[4]/F");
  tree->Branch("Py_true", &m.Py_true, "Py_true[4]/F");
  tree->Branch("Pz_true", &m.Pz_true, "Pz_true[4]/F");
  tree->Branch("P2_true", &m.P2_true, "P2_true[4]/F");
  tree->Branch("P_true", &m.P_true, "P_true[4]/F");
  tree->Branch("E_true", &m.E_true, "E_true[4]/F");
  // corr (6)
  tree->Branch("Px_corr", &m.Px_corr, "Px_corr[4]/F");
  tree->Branch("Py_corr", &m.Py_corr, "Py_corr[4]/F");
  tree->Branch("Pz_corr", &m.Pz_corr, "Pz_corr[4]/F");
  tree->Branch("P2_corr", &m.P2_corr, "P2_corr[4]/F");
  tree->Branch("P_corr", &m.P_corr, "P_corr[4]/F");
  tree->Branch("E_corr", &m.E_corr, "E_corr[4]/F");
  // remaining (10)
  tree->Branch("Z", &m.Z, "Z[4]/F");
  tree->Branch("PhiPQ", &m.PhiPQ, "PhiPQ[4]/F");
  tree->Branch("ThetaPQ", &m.ThetaPQ, "ThetaPQ[4]/F");
  tree->Branch("CosThetaPQ", &m.CosThetaPQ, "CosThetaPQ[4]/F");
  tree->Branch("Pt2", &m.Pt2, "Pt2[4]/F");
  tree->Branch("Pl2", &m.Pl2, "Pl2[4]/F");
  tree->Branch("Mx2", &m.Mx2, "Mx2[4]/F");
  tree->Branch("T", &m.T, "T[4]/F");
  tree->Branch("deltaTheta", &m.deltaTheta, "deltaTheta[4]/F");
  tree->Branch("BettaCalc", &m.BettaCalc, "BettaCalc[4]/F");
  // status (16)
  tree->Branch("StatDC", &m.StatDC, "StatDC[4]/F");
  tree->Branch("DCStatus", &m.DCStatus, "DCStatus[4]/F");
  tree->Branch("StatEC", &m.StatEC, "StatEC[4]/F");
  tree->Branch("ECStatus", &m.ECStatus, "ECStatus[4]/F");
  tree->Branch("TimeEC", &m.TimeEC, "TimeEC[4]/F");
  tree->Branch("PathEC", &m.PathEC, "PathEC[4]/F");
  tree->Branch("Chi2EC", &m.Chi2EC, "Chi2EC[4]/F");
  tree->Branch("StatSC", &m.StatSC, "StatSC[4]/F");
  tree->Branch("SCStatus", &m.SCStatus, "SCStatus[4]/F");
  tree->Branch("TimeSC", &m.TimeSC, "TimeSC[4]/F");
  tree->Branch("PathSC", &m.PathSC, "PathSC[4]/F");
  tree->Branch("StatCC", &m.StatCC, "StatCC[4]/F");
  tree->Branch("CCStatus", &m.CCStatus, "CCStatus[4]/F");
  tree->Branch("Nphe", &m.Nphe, "Nphe[4]/F");
  tree->Branch("Chi2CC", &m.Chi2CC, "Chi2CC[4]/F");
  tree->Branch("Status", &m.Status, "Status[4]/F");
  // pi0 prev (8)
  tree->Branch("pi0Px_prev", &pi0.Px_prev);
  tree->Branch("pi0Py_prev", &pi0.Py_prev);
  tree->Branch("pi0Pz_prev", &pi0.Pz_prev);
  tree->Branch("pi0P2_prev", &pi0.P2_prev);
  tree->Branch("pi0P_prev", &pi0.P_prev);
  tree->Branch("pi0E_prev", &pi0.E_prev);
  tree->Branch("pi0M_prev", &pi0.M_prev);
  tree->Branch("pi0Theta_prev", &pi0.Theta_prev);
  // pi0 true (8)
  tree->Branch("pi0Px_true", &pi0.Px_true);
  tree->Branch("pi0Py_true", &pi0.Py_true);
  tree->Branch("pi0Pz_true", &pi0.Pz_true);
  tree->Branch("pi0P2_true", &pi0.P2_true);
  tree->Branch("pi0P_true", &pi0.P_true);
  tree->Branch("pi0E_true", &pi0.E_true);
  tree->Branch("pi0M_true", &pi0.M_true);
  tree->Branch("pi0Theta_true", &pi0.Theta_true);
  // pi0 corr (8)
  tree->Branch("pi0Px_corr", &pi0.Px_corr);
  tree->Branch("pi0Py_corr", &pi0.Py_corr);
  tree->Branch("pi0Pz_corr", &pi0.Pz_corr);
  tree->Branch("pi0P2_corr", &pi0.P2_corr);
  tree->Branch("pi0P_corr", &pi0.P_corr);
  tree->Branch("pi0E_corr", &pi0.E_corr);
  tree->Branch("pi0M_corr", &pi0.M_corr);
  tree->Branch("pi0Theta_corr", &pi0.Theta_corr);
  // omega prev (18)
  tree->Branch("wZ_prev", &w.Z_prev);
  tree->Branch("wPhiPQ_prev", &w.PhiPQ_prev);
  tree->Branch("wThetaPQ_prev", &w.ThetaPQ_prev);
  tree->Branch("wCosThetaPQ_prev", &w.CosThetaPQ_prev);
  tree->Branch("wPt2_prev", &w.Pt2_prev);
  tree->Branch("wPl2_prev", &w.Pl2_prev);
  tree->Branch("wMx2_prev", &w.Mx2_prev);
  tree->Branch("wT_prev", &w.T_prev);
  tree->Branch("wPx_prev", &w.Px_prev);
  tree->Branch("wPy_prev", &w.Py_prev);
  tree->Branch("wPz_prev", &w.Pz_prev);
  tree->Branch("wP2_prev", &w.P2_prev);
  tree->Branch("wP_prev", &w.P_prev);
  tree->Branch("wE_prev", &w.E_prev);
  tree->Branch("wBettaCalc_prev", &w.BettaCalc_prev);
  tree->Branch("wdeltaTheta_prev", &w.deltaTheta_prev);
  tree->Branch("wD_prev", &w.D_prev);
  tree->Branch("wM_prev", &w.M_prev);
  // omega true (18)
  tree->Branch("wZ_true", &w.Z_true);
  tree->Branch("wPhiPQ_true", &w.PhiPQ_true);
  tree->Branch("wThetaPQ_true", &w.ThetaPQ_true);
  tree->Branch("wCosThetaPQ_true", &w.CosThetaPQ_true);
  tree->Branch("wPt2_true", &w.Pt2_true);
  tree->Branch("wPl2_true", &w.Pl2_true);
  tree->Branch("wMx2_true", &w.Mx2_true);
  tree->Branch("wT_true", &w.T_true);
  tree->Branch("wPx_true", &w.Px_true);
  tree->Branch("wPy_true", &w.Py_true);
  tree->Branch("wPz_true", &w.Pz_true);
  tree->Branch("wP2_true", &w.P2_true);
  tree->Branch("wP_true", &w.P_true);
  tree->Branch("wE_true", &w.E_true);
  tree->Branch("wBettaCalc_true", &w.BettaCalc_true);
  tree->Branch("wdeltaTheta_true", &w.deltaTheta_true);
  tree->Branch("wD_true", &w.D_true);
  tree->Branch("wM_true", &w.M_true);
  // omega corr (18)
  tree->Branch("wZ_corr", &w.Z_corr);
  tree->Branch("wPhiPQ_corr", &w.PhiPQ_corr);
  tree->Branch("wThetaPQ_corr", &w.ThetaPQ_corr);
  tree->Branch("wCosThetaPQ_corr", &w.CosThetaPQ_corr);
  tree->Branch("wPt2_corr", &w.Pt2_corr);
  tree->Branch("wPl2_corr", &w.Pl2_corr);
  tree->Branch("wMx2_corr", &w.Mx2_corr);
  tree->Branch("wT_corr", &w.T_corr);
  tree->Branch("wPx_corr", &w.Px_corr);
  tree->Branch("wPy_corr", &w.Py_corr);
  tree->Branch("wPz_corr", &w.Pz_corr);
  tree->Branch("wP2_corr", &w.P2_corr);
  tree->Branch("wP_corr", &w.P_corr);
  tree->Branch("wE_corr", &w.E_corr);
  tree->Branch("wBettaCalc_corr", &w.BettaCalc_corr);
  tree->Branch("wdeltaTheta_corr", &w.deltaTheta_corr);
  tree->Branch("wD_corr", &w.D_corr);
  tree->Branch("wM_corr", &w.M_corr);
  // crossed terms (9)
  tree->Branch("pippimP", &m.pippimP);
  tree->Branch("pippimE", &m.pippimE);
  tree->Branch("pippimM", &m.pippimM);
  tree->Branch("pippi0P", &m.pippi0P);
  tree->Branch("pippi0E", &m.pippi0E);
  tree->Branch("pippi0M", &m.pippi0M);
  tree->Branch("pimpi0P", &m.pimpi0P);
  tree->Branch("pimpi0E", &m.pimpi0E);
  tree->Branch("pimpi0M", &m.pimpi0M);
  // number of particles in that event (3)
  tree->Branch("nPip",   &m.nPip);
  tree->Branch("nPim",   &m.nPim);
  tree->Branch("nGamma", &m.nGamma);
  // event related (2)
  tree->Branch("Entry", &m.Entry, "Entry[4]/F");
  // (72 variables for gsim)
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
  tree->Branch("mc_Pe", &mc_m.Pe);
  tree->Branch("mc_BettaEl", &mc_m.BettaEl);
  tree->Branch("mc_P2e", &mc_m.P2e);
  // particle (25)
  tree->Branch("mc_vxh", &mc_m.vxh, "mc_vxh[4]/F");
  tree->Branch("mc_vyh", &mc_m.vyh, "mc_vyh[4]/F");
  tree->Branch("mc_vzh", &mc_m.vzh, "mc_vzh[4]/F");
  tree->Branch("mc_Sector", &mc_m.Sector, "mc_Sector[4]/F");
  tree->Branch("mc_Betta", &mc_m.Betta, "mc_Betta[4]/F");
  tree->Branch("mc_Mass2", &mc_m.Mass2, "mc_Mass2[4]/F");
  tree->Branch("mc_Pid", &mc_m.Pid, "mc_Pid[4]/F");
  tree->Branch("mc_deltaZ", &mc_m.deltaZ, "mc_deltaZ[4]/F");
  tree->Branch("mc_M", &mc_m.M, "mc_M[4]/F");
  tree->Branch("mc_E", &mc_m.E, "mc_E[4]/F");
  tree->Branch("mc_Px", &mc_m.Px, "mc_Px[4]/F");
  tree->Branch("mc_Py", &mc_m.Py, "mc_Py[4]/F");
  tree->Branch("mc_Pz", &mc_m.Pz, "mc_Pz[4]/F");
  tree->Branch("mc_P2", &mc_m.P2, "mc_P2[4]/F");
  tree->Branch("mc_P", &mc_m.P, "mc_P[4]/F");
  tree->Branch("mc_Z", &mc_m.Z, "mc_Z[4]/F");
  tree->Branch("mc_ThetaPQ", &mc_m.ThetaPQ, "mc_ThetaPQ[4]/F");
  tree->Branch("mc_Pt2", &mc_m.Pt2, "mc_Pt2[4]/F");
  tree->Branch("mc_Pl2", &mc_m.Pl2, "mc_Pl2[4]/F");
  tree->Branch("mc_PhiPQ", &mc_m.PhiPQ, "mc_PhiPQ[4]/F");
  tree->Branch("mc_Mx2", &mc_m.Mx2, "mc_Mx2[4]/F");
  tree->Branch("mc_T", &mc_m.T, "mc_T[4]/F");
  tree->Branch("mc_CosThetaPQ", &mc_m.CosThetaPQ, "mc_CosThetaPQ[4]/F");
  tree->Branch("mc_BettaCalc", &mc_m.BettaCalc, "mc_BettaCalc[4]/F");
  tree->Branch("mc_deltaTheta", &mc_m.deltaTheta, "mc_deltaTheta[4]/F");
  // pi0 (8)
  tree->Branch("mc_pi0Px", &mc_pi0.Px);
  tree->Branch("mc_pi0Py", &mc_pi0.Py);
  tree->Branch("mc_pi0Pz", &mc_pi0.Pz);
  tree->Branch("mc_pi0P2", &mc_pi0.P2);
  tree->Branch("mc_pi0P", &mc_pi0.P);
  tree->Branch("mc_pi0E", &mc_pi0.E);
  tree->Branch("mc_pi0M", &mc_pi0.M);
  tree->Branch("mc_pi0Theta", &mc_pi0.Theta);
  // omega (18)
  tree->Branch("mc_wPx", &mc_w.Px);
  tree->Branch("mc_wPy", &mc_w.Py);
  tree->Branch("mc_wPz", &mc_w.Pz);
  tree->Branch("mc_wP", &mc_w.P);
  tree->Branch("mc_wP2", &mc_w.P2);
  tree->Branch("mc_wE", &mc_w.E);
  tree->Branch("mc_wZ", &mc_w.Z);
  tree->Branch("mc_wCosThetaPQ", &mc_w.CosThetaPQ);
  tree->Branch("mc_wThetaPQ", &mc_w.ThetaPQ);
  tree->Branch("mc_wPt2", &mc_w.Pt2);
  tree->Branch("mc_wPl2", &mc_w.Pl2);
  tree->Branch("mc_wPhiPQ", &mc_w.PhiPQ);
  tree->Branch("mc_wMx2", &mc_w.Mx2);
  tree->Branch("mc_wT", &mc_w.T);
  tree->Branch("mc_wBettaCalc", &mc_w.BettaCalc);
  tree->Branch("mc_wdeltaTheta", &mc_w.deltaTheta);
  tree->Branch("mc_wD", &mc_w.D);
  tree->Branch("mc_wM", &mc_w.M);
  // crossed terms (9)
  tree->Branch("mc_pippimP", &mc_m.pippimP);
  tree->Branch("mc_pippimE", &mc_m.pippimE);
  tree->Branch("mc_pippimM", &mc_m.pippimM);
  tree->Branch("mc_pippi0P", &mc_m.pippi0P);
  tree->Branch("mc_pippi0E", &mc_m.pippi0E);
  tree->Branch("mc_pippi0M", &mc_m.pippi0M);
  tree->Branch("mc_pimpi0P", &mc_m.pimpi0P);
  tree->Branch("mc_pimpi0E", &mc_m.pimpi0E);
  tree->Branch("mc_pimpi0M", &mc_m.pimpi0M);
  // number of particles (3)
  tree->Branch("mc_nPip", &mc_m.nPip);
  tree->Branch("mc_nPim", &mc_m.nPim);
  tree->Branch("mc_nGamma", &mc_m.nGamma);
    // event related (2)
  tree->Branch("mc_Entry", &mc_m.Entry, "mc_Entry[4]/F");
  tree->Branch("Event", &mc_m.Event);
}

void NullMixVar_SIMREC(simrec_m& m, simrec_pi0& pi0, simrec_w& w) {
  // electron (41)
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
  m.Pe = INVLD;
  m.P2e = INVLD;
  m.BettaEl = INVLD;
  m.Etote = INVLD;
  m.Eine  = INVLD;
  m.Eoute = INVLD;
  m.Xec = INVLD;
  m.Yec = INVLD;
  m.Zec = INVLD;
  m.XECe = INVLD;
  m.YECe = INVLD;
  m.ZECe = INVLD;
  m.StatDCEl   = INVLD;
  m.DCStatusEl = INVLD;
  m.StatECEl   = INVLD;
  m.ECStatusEl = INVLD;
  m.TimeECEl   = INVLD;
  m.PathECEl   = INVLD;
  m.Chi2ECEl   = INVLD;
  m.StatSCEl   = INVLD;
  m.SCStatusEl = INVLD;
  m.TimeSCEl   = INVLD;
  m.PathSCEl   = INVLD;
  m.StatCCEl   = INVLD;
  m.CCStatusEl = INVLD;
  m.NpheEl     = INVLD;
  m.Chi2CCEl   = INVLD;
  m.StatusEl   = INVLD;
  for (Int_t index = 0; index < 4; index++) {
    // independent variables (16)
    m.vxh[index] = INVLD;
    m.vyh[index] = INVLD;
    m.vzh[index] = INVLD;
    m.Sector[index] = INVLD;
    m.XEC[index] = INVLD;
    m.YEC[index] = INVLD;
    m.ZEC[index] = INVLD;
    m.Etot[index] = INVLD;
    m.Ein[index]  = INVLD;
    m.Eout[index] = INVLD;
    m.deltaZ[index] = INVLD;
    m.T4[index] = INVLD;
    m.Mass2[index] = INVLD;
    m.Betta[index] = INVLD;
    m.Pid[index] = INVLD;
    m.M[index] = INVLD;
    // prev (6)
    m.E_prev[index]  = INVLD;
    m.Px_prev[index] = INVLD;
    m.Py_prev[index] = INVLD;
    m.Pz_prev[index] = INVLD;
    m.P_prev[index]  = INVLD;
    m.P2_prev[index] = INVLD;
    // true (6)
    m.E_true[index]  = INVLD;
    m.Px_true[index] = INVLD;
    m.Py_true[index] = INVLD;
    m.Pz_true[index] = INVLD;
    m.P2_true[index] = INVLD;
    m.P_true[index]  = INVLD;
    // corr (6)
    m.E_corr[index]  = INVLD;
    m.Px_corr[index] = INVLD;
    m.Py_corr[index] = INVLD;
    m.Pz_corr[index] = INVLD;
    m.P2_corr[index] = INVLD;
    m.P_corr[index]  = INVLD;
    // remaining (10)
    m.Z[index] = INVLD;
    m.PhiPQ[index]   = INVLD;
    m.ThetaPQ[index] = INVLD;
    m.CosThetaPQ[index] = INVLD;
    m.Pt2[index] = INVLD;
    m.Pl2[index] = INVLD;
    m.deltaTheta[index] = INVLD;
    m.Mx2[index] = INVLD;
    m.T[index] = INVLD;
    m.BettaCalc[index] = INVLD;
    // status (16)
    m.StatDC[index]   = INVLD;
    m.DCStatus[index] = INVLD;
    m.StatEC[index]   = INVLD;
    m.ECStatus[index] = INVLD;
    m.TimeEC[index]   = INVLD;
    m.PathEC[index]   = INVLD;
    m.Chi2EC[index]   = INVLD;
    m.StatSC[index]   = INVLD;
    m.SCStatus[index] = INVLD;
    m.TimeSC[index]   = INVLD;
    m.PathSC[index]   = INVLD;
    m.StatCC[index]   = INVLD;
    m.CCStatus[index] = INVLD;
    m.Nphe[index]     = INVLD;
    m.Chi2CC[index]   = INVLD;
    m.Status[index]   = INVLD;
    // last but not least
    m.Entry[index] = INVLD;
  }
  // pi0 prev (8)
  pi0.Px_prev = INVLD;
  pi0.Py_prev = INVLD;
  pi0.Pz_prev = INVLD;
  pi0.P2_prev = INVLD;
  pi0.P_prev  = INVLD;
  pi0.M_prev  = INVLD;
  pi0.E_prev  = INVLD;
  pi0.Theta_prev = INVLD;
  // pi0 true (8)
  pi0.Px_true = INVLD;
  pi0.Py_true = INVLD;
  pi0.Pz_true = INVLD;
  pi0.P2_true = INVLD;
  pi0.P_true  = INVLD;
  pi0.M_true  = INVLD;
  pi0.E_true  = INVLD;
  pi0.Theta_true = INVLD;
  // pi0 corr (8)
  pi0.Px_corr = INVLD;
  pi0.Py_corr = INVLD;
  pi0.Pz_corr = INVLD;
  pi0.P2_corr = INVLD;
  pi0.P_corr  = INVLD;
  pi0.M_corr  = INVLD;
  pi0.E_corr  = INVLD;
  pi0.Theta_corr = INVLD;
  // omega prev (6+12)
  w.Px_prev = INVLD;
  w.Py_prev = INVLD;
  w.Pz_prev = INVLD;
  w.P2_prev = INVLD;
  w.P_prev  = INVLD;
  w.E_prev  = INVLD;
  w.M_prev  = INVLD;
  w.D_prev  = INVLD;
  w.Z_prev  = INVLD;
  w.PhiPQ_prev = INVLD;
  w.ThetaPQ_prev = INVLD;
  w.CosThetaPQ_prev = INVLD;
  w.Pt2_prev = INVLD;
  w.Pl2_prev = INVLD;
  w.Mx2_prev = INVLD;
  w.T_prev = INVLD;
  w.BettaCalc_prev = INVLD;
  w.deltaTheta_prev = INVLD;
  // omega true (6+12)
  w.Px_true = INVLD;
  w.Py_true = INVLD;
  w.Pz_true = INVLD;
  w.P2_true = INVLD;
  w.P_true  = INVLD;
  w.E_true  = INVLD;
  w.M_true  = INVLD;
  w.D_true  = INVLD;
  w.Z_true  = INVLD;
  w.PhiPQ_true = INVLD;
  w.ThetaPQ_true = INVLD;
  w.CosThetaPQ_true = INVLD;
  w.Pt2_true = INVLD;
  w.Pl2_true = INVLD;
  w.Mx2_true = INVLD;
  w.T_true = INVLD;
  w.BettaCalc_true = INVLD;
  w.deltaTheta_true = INVLD;
  // omega corr (6+12)
  w.Px_corr = INVLD;
  w.Py_corr = INVLD;
  w.Pz_corr = INVLD;
  w.P2_corr = INVLD;
  w.P_corr  = INVLD;
  w.E_corr  = INVLD;
  w.M_corr  = INVLD;
  w.D_corr  = INVLD;
  w.Z_corr  = INVLD;
  w.PhiPQ_corr = INVLD;
  w.ThetaPQ_corr = INVLD;
  w.CosThetaPQ_corr = INVLD;
  w.Pt2_corr = INVLD;
  w.Pl2_corr = INVLD;
  w.Mx2_corr = INVLD;
  w.T_corr = INVLD;
  w.BettaCalc_corr = INVLD;
  w.deltaTheta_corr = INVLD;
  // crossed terms (9)
  m.pippimP = INVLD;
  m.pippimE = INVLD;
  m.pippimM = INVLD;
  m.pippi0P = INVLD;
  m.pippi0E = INVLD;
  m.pippi0M = INVLD;
  m.pimpi0P = INVLD;
  m.pimpi0E = INVLD;
  m.pimpi0M = INVLD;
  // number of particles (3)
  m.nGamma = INVLD;
  m.nPip   = INVLD;
  m.nPim   = INVLD;
}

void AssignMixVar_SIMREC(simrec_i& t, simrec_m& m, Int_t entry, Int_t index) {
  // electron (41)
  m.Q2 = t.Q2;
  m.W  = t.W;
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
  m.Pe  = t.Pe;
  m.P2e = m.Pe*m.Pe;
  m.BettaEl = t.BettaEl;
  m.Etote = t.Etote;
  m.Eine  = t.Eine;
  m.Eoute = t.Eoute;
  m.Xec = t.vxec;
  m.Yec = t.vyec;
  m.Zec = t.vzec;
  m.XECe = t.XECe;
  m.YECe = t.YECe;
  m.ZECe = t.ZECe;
  m.StatDCEl   = t.StatDCEl;
  m.DCStatusEl = t.DCStatusEl;
  m.StatECEl   = t.StatECEl;
  m.ECStatusEl = t.ECStatusEl;
  m.TimeECEl   = t.TimeECEl;
  m.PathECEl   = t.PathECEl;
  m.Chi2ECEl   = t.Chi2ECEl;
  m.StatSCEl   = t.StatSCEl;
  m.SCStatusEl = t.SCStatusEl;
  m.TimeSCEl   = t.TimeSCEl;
  m.PathSCEl   = t.PathSCEl;
  m.StatCCEl   = t.StatCCEl;
  m.CCStatusEl = t.CCStatusEl;
  m.NpheEl     = t.NpheEl;
  m.Chi2CCEl   = t.Chi2CCEl;
  m.StatusEl   = t.StatusEl;
  // independent variables (16)
  m.vxh[index] = t.vxh;
  m.vyh[index] = t.vyh;
  m.vzh[index] = t.vzh;
  m.Sector[index] = t.Sector;
  m.XEC[index] = t.XEC;
  m.YEC[index] = t.YEC;
  m.ZEC[index] = t.ZEC;
  m.Etot[index] = t.Etot;
  m.Ein[index]  = t.Ein;
  m.Eout[index] = t.Eout;
  m.deltaZ[index] = t.deltaZ;
  m.T4[index] = t.T4;
  m.Mass2[index] = t.Mass2;
  m.Betta[index] = t.Betta;
  m.Pid[index] = t.pid; // important!
  m.M[index] = particleMass(t.pid);
  // prev (6)
  m.E_prev[index]  = CorrectEnergy(t, "prev");
  m.Px_prev[index] = t.Px;
  m.Py_prev[index] = t.Py;
  m.Pz_prev[index] = t.Pz;
  m.P_prev[index]  = t.P;
  m.P2_prev[index] = m.P_prev[index]*m.P_prev[index];
  // t.rue (6)
  m.E_true[index]  = CorrectEnergy(t, "true");
  m.Px_true[index] = CorrectMomentum(t, "x", "true");
  m.Py_true[index] = CorrectMomentum(t, "y", "true");
  m.Pz_true[index] = CorrectMomentum(t, "z", "true");
  m.P2_true[index] = m.Px_true[index]*m.Px_true[index] + m.Py_true[index]*m.Py_true[index] + m.Pz_true[index]*m.Pz_true[index];
  m.P_true[index]  = TMath::Sqrt(m.P2_true[index]);
  // corr (6)
  m.E_corr[index]  = CorrectEnergy(t, "corr");
  m.Px_corr[index] = CorrectMomentum(t, "x", "corr");
  m.Py_corr[index] = CorrectMomentum(t, "y", "corr");
  m.Pz_corr[index] = CorrectMomentum(t, "z", "corr");
  m.P2_corr[index] = m.Px_corr[index]*m.Px_corr[index] + m.Py_corr[index]*m.Py_corr[index] + m.Pz_corr[index]*m.Pz_corr[index];
  m.P_corr[index]  = TMath::Sqrt(m.P2_corr[index]);
  // remaining (10) - using corr values
  m.Z[index]          = m.E_corr[index]/m.Nu;
  m.PhiPQ[index]      = PhiPQ(t.Pex, t.Pey, t.Pez, m.Px_corr[index], m.Py_corr[index], m.Pz_corr[index]);
  m.ThetaPQ[index]    = ThetaPQ(t.Pex, t.Pey, t.Pez, m.Px_corr[index], m.Py_corr[index], m.Pz_corr[index]);
  m.CosThetaPQ[index] = ((kEbeam - m.Pez)*m.Pz_corr[index] - m.Pex*m.Px_corr[index] - m.Pey*m.Py_corr[index])/(TMath::Sqrt(m.P2_corr[index]*(m.Q2 + m.Nu*m.Nu)));
  m.Pt2[index]        = m.P2_corr[index]*(1 - m.CosThetaPQ[index]*m.CosThetaPQ[index]);
  m.Pl2[index]        = m.P2_corr[index]*m.CosThetaPQ[index]*m.CosThetaPQ[index];
  m.deltaTheta[index] = DeltaTheta(m.Pex, m.Pey, m.Pez, m.Px_corr[index], m.Py_corr[index], m.Pz_corr[index]);
  m.Mx2[index]        = m.W*m.W + m.M[index]*m.M[index] - 2*m.Z[index]*m.Nu*m.Nu + 2*TMath::Sqrt(m.Pl2[index]*(m.Nu*m.Nu + m.Q2)) - 2*kMproton*m.Z[index]*m.Nu;
  m.T[index]          = m.M[index]*m.M[index] - 2*m.Z[index]*m.Nu*m.Nu + 2*TMath::Sqrt(m.Pl2[index]*(m.Nu*m.Nu + m.Q2)) - m.Q2;
  m.BettaCalc[index]  = BettaCalc(m.P_corr[index], m.Pid[index]);
  // status (16)
  m.StatDC[index]   = t.StatDC;
  m.DCStatus[index] = t.DCStatus;
  m.StatEC[index]   = t.StatEC;
  m.ECStatus[index] = t.ECStatus;
  m.TimeEC[index]   = t.TimeEC;
  m.PathEC[index]   = t.PathEC;
  m.Chi2EC[index]   = t.Chi2EC;
  m.StatSC[index]   = t.StatSC;
  m.SCStatus[index] = t.SCStatus;
  m.TimeSC[index]   = t.TimeSC;
  m.PathSC[index]   = t.PathSC;
  m.StatCC[index]   = t.StatCC;
  m.CCStatus[index] = t.CCStatus;
  m.Nphe[index]     = t.Nphe;
  m.Chi2CC[index]   = t.Chi2CC;
  m.Status[index]   = t.Status;
  // event-related (1)
  m.Entry[index] = (Float_t) entry;  
}

void AssignMoreVar_SIMREC(simrec_m& m, Int_t nPipThisEvent, Int_t nPimThisEvent, Int_t nGammaThisEvent) {
  m.nPip = nPipThisEvent;
  m.nPim = nPimThisEvent;
  m.nGamma = nGammaThisEvent;
}


void AssignPi0Var_SIMREC(simrec_m& m, simrec_pi0& pi0) {
  // pi0 prev (8)
  pi0.Px_prev = m.Px_prev[2] + m.Px_prev[3];
  pi0.Py_prev = m.Py_prev[2] + m.Py_prev[3];
  pi0.Pz_prev = m.Pz_prev[2] + m.Pz_prev[3];
  pi0.P2_prev = pi0.Px_prev*pi0.Px_prev + pi0.Py_prev*pi0.Py_prev + pi0.Pz_prev*pi0.Pz_prev;
  pi0.P_prev  = TMath::Sqrt(pi0.P2_prev);
  pi0.E_prev  = m.E_prev[2] + m.E_prev[3];
  pi0.M_prev  = TMath::Sqrt(pi0.E_prev*pi0.E_prev - pi0.P2_prev);
  Double_t dot   = m.Px_prev[2]*m.Px_prev[3] + m.Py_prev[2]*m.Py_prev[3] + m.Pz_prev[2]*m.Pz_prev[3];
  Double_t mag_0 = TMath::Sqrt(m.Px_prev[2]*m.Px_prev[2] + m.Py_prev[2]*m.Py_prev[2] + m.Pz_prev[2]*m.Pz_prev[2]);
  Double_t mag_1 = TMath::Sqrt(m.Px_prev[3]*m.Px_prev[3] + m.Py_prev[3]*m.Py_prev[3] + m.Pz_prev[3]*m.Pz_prev[3]);
  pi0.Theta_prev = TMath::RadToDeg()*TMath::ACos(dot/(mag_0*mag_1));
  // pi0. true (8)
  pi0.Px_true = m.Px_true[2] + m.Px_true[3];
  pi0.Py_true = m.Py_true[2] + m.Py_true[3];
  pi0.Pz_true = m.Pz_true[2] + m.Pz_true[3];
  pi0.P2_true = pi0.Px_true*pi0.Px_true + pi0.Py_true*pi0.Py_true + pi0.Pz_true*pi0.Pz_true;
  pi0.P_true  = TMath::Sqrt(pi0.P2_true);
  pi0.E_true  = m.E_true[2] + m.E_true[3];
  pi0.M_true  = TMath::Sqrt(pi0.E_true*pi0.E_true - pi0.P2_true);
  dot   = m.Px_true[2]*m.Px_true[3] + m.Py_true[2]*m.Py_true[3] + m.Pz_true[2]*m.Pz_true[3];
  mag_0 = TMath::Sqrt(m.Px_true[2]*m.Px_true[2] + m.Py_true[2]*m.Py_true[2] + m.Pz_true[2]*m.Pz_true[2]);
  mag_1 = TMath::Sqrt(m.Px_true[3]*m.Px_true[3] + m.Py_true[3]*m.Py_true[3] + m.Pz_true[3]*m.Pz_true[3]);
  pi0.Theta_true = TMath::RadToDeg()*TMath::ACos(dot/(mag_0*mag_1));
  // pi0. corr (8)
  pi0.Px_corr = m.Px_corr[2] + m.Px_corr[3];
  pi0.Py_corr = m.Py_corr[2] + m.Py_corr[3];
  pi0.Pz_corr = m.Pz_corr[2] + m.Pz_corr[3];
  pi0.P2_corr = pi0.Px_corr*pi0.Px_corr + pi0.Py_corr*pi0.Py_corr + pi0.Pz_corr*pi0.Pz_corr;
  pi0.P_corr  = TMath::Sqrt(pi0.P2_corr);
  pi0.E_corr  = m.E_corr[2] + m.E_corr[3];
  pi0.M_corr  = TMath::Sqrt(pi0.E_corr*pi0.E_corr - pi0.P2_corr);
  dot   = m.Px_corr[2]*m.Px_corr[3] + m.Py_corr[2]*m.Py_corr[3] + m.Pz_corr[2]*m.Pz_corr[3];
  mag_0 = TMath::Sqrt(m.Px_corr[2]*m.Px_corr[2] + m.Py_corr[2]*m.Py_corr[2] + m.Pz_corr[2]*m.Pz_corr[2]);
  mag_1 = TMath::Sqrt(m.Px_corr[3]*m.Px_corr[3] + m.Py_corr[3]*m.Py_corr[3] + m.Pz_corr[3]*m.Pz_corr[3]);
  pi0.Theta_corr = TMath::RadToDeg()*TMath::ACos(dot/(mag_0*mag_1));
}

void AssignOmegaVar_SIMREC(simrec_m& m, simrec_pi0& pi0, simrec_w& w) {
  // omega prev (6+12)
  w.Px_prev = pi0.Px_prev + m.Px_prev[0] + m.Px_prev[1];
  w.Py_prev = pi0.Py_prev + m.Py_prev[0] + m.Py_prev[1];
  w.Pz_prev = pi0.Pz_prev + m.Pz_prev[0] + m.Pz_prev[1];
  w.P2_prev = w.Px_prev*w.Px_prev + w.Py_prev*w.Py_prev + w.Pz_prev*w.Pz_prev;
  w.P_prev  = TMath::Sqrt(w.P2_prev);
  w.E_prev  = pi0.E_prev + m.E_prev[0] + m.E_prev[1];
  w.M_prev  = TMath::Sqrt(w.E_prev*w.E_prev - w.P2_prev);
  w.D_prev  = w.M_prev - pi0.M_prev + kMpi0;
  w.Z_prev  = w.E_prev/m.Nu;
  w.PhiPQ_prev = PhiPQ(m.Pex, m.Pey, m.Pez, w.Px_prev, w.Py_prev, w.Pz_prev);
  w.ThetaPQ_prev = ThetaPQ(m.Pex, m.Pey, m.Pez, w.Px_prev, w.Py_prev, w.Pz_prev);
  w.CosThetaPQ_prev = ((kEbeam - m.Pez)*w.Pz_prev - m.Pex*w.Px_prev - m.Pey*w.Py_prev)/(TMath::Sqrt(w.P2_prev*(m.Q2 + m.Nu*m.Nu)));
  w.Pt2_prev = w.P2_prev*(1 - w.CosThetaPQ_prev*w.CosThetaPQ_prev);
  w.Pl2_prev = w.P2_prev*w.CosThetaPQ_prev*w.CosThetaPQ_prev;
  w.Mx2_prev = m.W*m.W + w.M_prev*w.M_prev - 2*w.Z_prev*m.Nu*m.Nu + 2*TMath::Sqrt(w.Pl2_prev*(m.Nu*m.Nu + m.Q2)) - 2*kMproton*w.Z_prev*m.Nu;
  w.T_prev = w.M_prev*w.M_prev - 2*w.Z_prev*m.Nu*m.Nu + 2*TMath::Sqrt(w.Pl2_prev*(m.Nu*m.Nu + m.Q2)) - m.Q2;
  w.BettaCalc_prev = BettaCalc(w.P_prev, 223);
  w.deltaTheta_prev = DeltaTheta(m.Pex, m.Pey, m.Pez, w.Px_prev, w.Py_prev, w.Pz_prev);
  // omega true (6+12)
  w.Px_true = pi0.Px_true + m.Px_true[0] + m.Px_true[1];
  w.Py_true = pi0.Py_true + m.Py_true[0] + m.Py_true[1];
  w.Pz_true = pi0.Pz_true + m.Pz_true[0] + m.Pz_true[1];
  w.P2_true = w.Px_true*w.Px_true + w.Py_true*w.Py_true + w.Pz_true*w.Pz_true;
  w.P_true  = TMath::Sqrt(w.P2_true);
  w.E_true  = pi0.E_true + m.E_true[0] + m.E_true[1];
  w.M_true  = TMath::Sqrt(w.E_true*w.E_true - w.P2_true);
  w.D_true  = w.M_true - pi0.M_true + kMpi0;
  w.Z_true  = w.E_true/m.Nu;
  w.PhiPQ_true = PhiPQ(m.Pex, m.Pey, m.Pez, w.Px_true, w.Py_true, w.Pz_true);
  w.ThetaPQ_true = ThetaPQ(m.Pex, m.Pey, m.Pez, w.Px_true, w.Py_true, w.Pz_true);
  w.CosThetaPQ_true = ((kEbeam - m.Pez)*w.Pz_true - m.Pex*w.Px_true - m.Pey*w.Py_true)/(TMath::Sqrt(w.P2_true*(m.Q2 + m.Nu*m.Nu)));
  w.Pt2_true = w.P2_true*(1 - w.CosThetaPQ_true*w.CosThetaPQ_true);
  w.Pl2_true = w.P2_true*w.CosThetaPQ_true*w.CosThetaPQ_true;
  w.Mx2_true = m.W*m.W + w.M_true*w.M_true - 2*w.Z_true*m.Nu*m.Nu + 2*TMath::Sqrt(w.Pl2_true*(m.Nu*m.Nu + m.Q2)) - 2*kMproton*w.Z_true*m.Nu;
  w.T_true = w.M_true*w.M_true - 2*w.Z_true*m.Nu*m.Nu + 2*TMath::Sqrt(w.Pl2_true*(m.Nu*m.Nu + m.Q2)) - m.Q2;
  w.BettaCalc_true = BettaCalc(w.P_true, 223);
  w.deltaTheta_true = DeltaTheta(m.Pex, m.Pey, m.Pez, w.Px_true, w.Py_true, w.Pz_true);
  // omega corr (6+12)
  w.Px_corr = pi0.Px_corr + m.Px_corr[0] + m.Px_corr[1];
  w.Py_corr = pi0.Py_corr + m.Py_corr[0] + m.Py_corr[1];
  w.Pz_corr = pi0.Pz_corr + m.Pz_corr[0] + m.Pz_corr[1];
  w.P2_corr = w.Px_corr*w.Px_corr + w.Py_corr*w.Py_corr + w.Pz_corr*w.Pz_corr;
  w.P_corr  = TMath::Sqrt(w.P2_corr);
  w.E_corr  = pi0.E_corr + m.E_corr[0] + m.E_corr[1];
  w.M_corr  = TMath::Sqrt(w.E_corr*w.E_corr - w.P2_corr);
  w.D_corr  = w.M_corr - pi0.M_corr + kMpi0;
  w.Z_corr  = w.E_corr/m.Nu;
  w.PhiPQ_corr = PhiPQ(m.Pex, m.Pey, m.Pez, w.Px_corr, w.Py_corr, w.Pz_corr);
  w.ThetaPQ_corr = ThetaPQ(m.Pex, m.Pey, m.Pez, w.Px_corr, w.Py_corr, w.Pz_corr);
  w.CosThetaPQ_corr = ((kEbeam - m.Pez)*w.Pz_corr - m.Pex*w.Px_corr - m.Pey*w.Py_corr)/(TMath::Sqrt(w.P2_corr*(m.Q2 + m.Nu*m.Nu)));
  w.Pt2_corr = w.P2_corr*(1 - w.CosThetaPQ_corr*w.CosThetaPQ_corr);
  w.Pl2_corr = w.P2_corr*w.CosThetaPQ_corr*w.CosThetaPQ_corr;
  w.Mx2_corr = m.W*m.W + w.M_corr*w.M_corr - 2*w.Z_corr*m.Nu*m.Nu + 2*TMath::Sqrt(w.Pl2_corr*(m.Nu*m.Nu + m.Q2)) - 2*kMproton*w.Z_corr*m.Nu;
  w.T_corr = w.M_corr*w.M_corr - 2*w.Z_corr*m.Nu*m.Nu + 2*TMath::Sqrt(w.Pl2_corr*(m.Nu*m.Nu + m.Q2)) - m.Q2;
  w.BettaCalc_corr = BettaCalc(w.P_corr, 223);
  w.deltaTheta_corr = DeltaTheta(m.Pex, m.Pey, m.Pez, w.Px_corr, w.Py_corr, w.Pz_corr);
}

void AssignMixVar_GSIM(gsim_i& mc_t, gsim_m& mc_m, Int_t entry, Int_t index) {
  // electron (16)
  mc_m.Q2 = mc_t.Q2;
  mc_m.W  = mc_t.W;
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
  mc_m.Pe = mc_t.Pe;
  mc_m.BettaEl = mc_t.BettaEl;
  mc_m.P2e = mc_m.Pe*mc_m.Pe;
  // particle (25)
  mc_m.vxh[index] = mc_t.vxh;
  mc_m.vyh[index] = mc_t.vyh;
  mc_m.vzh[index] = mc_t.vzh;
  mc_m.Sector[index] = mc_t.Sector;
  mc_m.Betta[index] = mc_t.Betta;
  mc_m.Mass2[index] = mc_t.Mass2;
  mc_m.Pid[index] = mc_t.pid; // important!
  mc_m.deltaZ[index] = mc_t.deltaZ;
  mc_m.Px[index] = mc_t.Px;
  mc_m.Py[index] = mc_t.Py;
  mc_m.Pz[index] = mc_t.Pz;
  mc_m.P[index] = mc_t.P;
  mc_m.Z[index] = mc_t.Zh;
  mc_m.ThetaPQ[index] = mc_t.ThetaPQ;
  mc_m.Pt2[index] = mc_t.Pt2;
  mc_m.Pl2[index] = mc_t.Pl2;
  mc_m.PhiPQ[index] = mc_t.PhiPQ;
  mc_m.Mx2[index] = mc_t.Mx2;
  mc_m.T[index] = mc_t.T;
  // recalc
  mc_m.P2[index] = mc_m.P[index]*mc_m.P[index];
  mc_m.M[index]  = particleMass(mc_m.Pid[index]);
  mc_m.E[index]  = TMath::Sqrt(mc_m.P2[index] + mc_m.M[index]*mc_m.M[index]);
  mc_m.CosThetaPQ[index] = ((kEbeam - mc_m.Pez)*mc_m.Pz[index] - mc_m.Pex*mc_m.Px[index] - mc_m.Pey*mc_m.Py[index])/(TMath::Sqrt(mc_m.P2[index]*(mc_m.Q2 + mc_m.Nu*mc_m.Nu)));
  mc_m.deltaTheta[index] = DeltaTheta(mc_m.Pex, mc_m.Pey, mc_m.Pez, mc_m.Px[index], mc_m.Py[index], mc_m.Pz[index]);
  mc_m.BettaCalc[index]  = BettaCalc(mc_m.P[index], mc_m.Pid[index]);
  // event-related (2)
  mc_m.Entry[index] = (Float_t) entry;
  mc_m.Event = mc_t.evnt; // important!
}

void AssignPi0Var_GSIM(gsim_m& mc_m, gsim_pi0& mc_pi0) {
  // pi0 (8)
  mc_pi0.Px = mc_m.Px[2] + mc_m.Px[3];
  mc_pi0.Py = mc_m.Py[2] + mc_m.Py[3];
  mc_pi0.Pz = mc_m.Pz[2] + mc_m.Pz[3];
  mc_pi0.P2 = mc_pi0.Px*mc_pi0.Px + mc_pi0.Py*mc_pi0.Py + mc_pi0.Pz*mc_pi0.Pz;
  mc_pi0.P  = TMath::Sqrt(mc_pi0.P2);
  mc_pi0.E  = mc_m.E[2] + mc_m.E[3];
  mc_pi0.M  = TMath::Sqrt(mc_pi0.E*mc_pi0.E - mc_pi0.P2);
  Double_t dot   = mc_m.Px[2]*mc_m.Px[3] + mc_m.Py[2]*mc_m.Py[3] + mc_m.Pz[2]*mc_m.Pz[3];
  Double_t mag_0 = TMath::Sqrt(mc_m.Px[2]*mc_m.Px[2] + mc_m.Py[2]*mc_m.Py[2] + mc_m.Pz[2]*mc_m.Pz[2]);
  Double_t mag_1 = TMath::Sqrt(mc_m.Px[3]*mc_m.Px[3] + mc_m.Py[3]*mc_m.Py[3] + mc_m.Pz[3]*mc_m.Pz[3]);
  mc_pi0.Theta = TMath::RadToDeg()*TMath::ACos(dot/(mag_0*mag_1));
}

void AssignOmegaVar_GSIM(gsim_m& mc_m, gsim_pi0& mc_pi0, gsim_w& mc_w) {
  // omega (18)
  mc_w.Px = mc_pi0.Px + mc_m.Px[0] + mc_m.Px[1];
  mc_w.Py = mc_pi0.Py + mc_m.Py[0] + mc_m.Py[1];
  mc_w.Pz = mc_pi0.Pz + mc_m.Pz[0] + mc_m.Pz[1];
  mc_w.P2 = mc_w.Px*mc_w.Px + mc_w.Py*mc_w.Py + mc_w.Pz*mc_w.Pz;
  mc_w.P  = TMath::Sqrt(mc_w.P2);
  mc_w.E  = mc_pi0.E + mc_m.E[0] + mc_m.E[1];
  mc_w.M  = TMath::Sqrt(mc_w.E*mc_w.E - mc_w.P2);
  mc_w.D  = mc_w.M - mc_pi0.M + kMpi0;
  mc_w.Z  = mc_w.E/mc_m.Nu;
  mc_w.PhiPQ = PhiPQ(mc_m.Pex, mc_m.Pey, mc_m.Pez, mc_w.Px, mc_w.Py, mc_w.Pz);
  mc_w.ThetaPQ = ThetaPQ(mc_m.Pex, mc_m.Pey, mc_m.Pez, mc_w.Px, mc_w.Py, mc_w.Pz);
  mc_w.CosThetaPQ = ((kEbeam - mc_m.Pez)*mc_w.Pz - mc_m.Pex*mc_w.Px - mc_m.Pey*mc_w.Py)/(TMath::Sqrt(mc_w.P2*(mc_m.Q2 + mc_m.Nu*mc_m.Nu)));
  mc_w.Pt2 = mc_w.P2*(1 - mc_w.CosThetaPQ*mc_w.CosThetaPQ);
  mc_w.Pl2 = mc_w.P2*mc_w.CosThetaPQ*mc_w.CosThetaPQ;
  mc_w.Mx2 = mc_m.W*mc_m.W + mc_w.M*mc_w.M - 2*mc_w.Z*mc_m.Nu*mc_m.Nu + 2*TMath::Sqrt(mc_w.Pl2*(mc_m.Nu*mc_m.Nu + mc_m.Q2)) - 2*kMproton*mc_w.Z*mc_m.Nu;
  mc_w.T  = mc_w.M*mc_w.M - 2*mc_w.Z*mc_m.Nu*mc_m.Nu + 2*TMath::Sqrt(mc_w.Pl2*(mc_m.Nu*mc_m.Nu + mc_m.Q2)) - mc_m.Q2;
  mc_w.BettaCalc = BettaCalc(mc_w.P, 223);
  mc_w.deltaTheta = DeltaTheta(mc_m.Pex, mc_m.Pey, mc_m.Pez, mc_w.Px, mc_w.Py, mc_w.Pz);
}

/*** Mathematical functions ***/

Float_t CorrectEnergy(simrec_i& t, TString option) {  
  // for charged pions, assign energy from measured momentum and pdg mass
  // for gammas, there are 3 options
  // prev : chooses max between Etot and Ein+Eout
  // true : from prev, applies the primitive sampling fraction factor of EC
  // corr : from true, applies the correction studied by TM

  Float_t fE;
  Float_t corrFactor;

  if (t.pid == 22) {
    if (option == "prev") {
      fE = t.P;
    } else if (option == "true") {
      fE = TMath::Max(t.Etot, t.Ein + t.Eout)/0.2806; // primitive sampling fraction factor for sim
    } else if (option == "corr") {
      fE = TMath::Max(t.Etot, t.Ein + t.Eout)/0.2806;
      corrFactor = 1.000 + 0.005/fE - 0.0052/(fE*fE);
      // finally
      fE = fE/corrFactor;
    } // end of option condition
  } else if (t.pid == 211 || t.pid == -211) {
    fE = TMath::Sqrt(t.P*t.P + particleMass(t.pid)*particleMass(t.pid));
  }
  
  return fE;
}

Float_t CorrectMomentum(simrec_i& t, TString component, TString option) {  
  // for charged pions, do nothing
  // for gammas, there are 2 options
  // true : use energy obtained from CorrectEnergy("true")
  // corr : use energy obtained from CorrectEnergy("corr")

  // string to int
  Int_t i;
  Float_t fPi;
  if (component == "x") {
    i = 0;
    fPi = t.Px;
  } else if (component == "y") {
    i = 1;
    fPi = t.Py;
  } else if (component == "z") {
    i = 2;
    fPi = t.Pz;
  }
  
  Float_t fP[3];
  Float_t fPcorr;
  
  if (t.pid == 22) {
    Float_t Rt = TMath::Sqrt(t.XEC*t.XEC + t.YEC*t.YEC);
    Float_t R = TMath::Sqrt(t.XEC*t.XEC + t.YEC*t.YEC + (t.ZEC - t.vzec)*(t.ZEC - t.vzec));
    Float_t theta_gam = TMath::ASin(Rt/R);
    Float_t phi_gam = TMath::ATan2(t.YEC, t.XEC);
    
    fP[0] = CorrectEnergy(t, option)*TMath::Sin(theta_gam)*TMath::Cos(phi_gam); // x
    fP[1] = CorrectEnergy(t, option)*TMath::Sin(theta_gam)*TMath::Sin(phi_gam); // y
    fP[2] = CorrectEnergy(t, option)*TMath::Cos(theta_gam);                     // z

    fPcorr = fP[i];
  } else if (t.pid == 211 || t.pid == -211) {
    fPcorr = fPi;
  }
  
  return fPcorr;
}

Float_t PhiPQ(Float_t fPex, Float_t fPey, Float_t fPez, Float_t fPx, Float_t fPy, Float_t fPz) {
  Float_t fPhiPQ;
  // two 3-momentum vectors are defined
  // one for the hadron
  // one for the virtual photon
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 virt(-fPex, -fPey, kEbeam - fPez);
  // the function Phi() and Theta() converts the vector into spherical coordinates
  // and the function RotateZ(amount) rotates the vector around z-axis a certain amount
  // now, this paragraph turns y-component of the virtual photon vector into 0 and rotates the hadron vector the same amount
  // to have the hadron vector in function of the virtual photon direction
  // if its not clear, try to draw these two vectors in the xy plane
  Float_t Phi_z = TMath::Pi() - virt.Phi();
  virt.RotateZ(Phi_z);
  hadr.RotateZ(Phi_z);
  // the function Angle() returns the angle between two vectors
  // now, take into account that the virtual photon vector is in the y=0 plane
  // again, this paragraph turns the x-component of the virtual photon vector into 0 and rotates the hadron vector the same amount
  // to have the hadron vector in function of the virtual photon direction
  // if its not clear, try to draw these two vectors in the xz plane
  TVector3 unit(0., 0., 1.);
  Float_t Phi_y = virt.Angle(unit);
  virt.RotateY(Phi_y);
  hadr.RotateY(Phi_y);  
  // finally, it obtains the phi component (in spherical coordinates) of the hadron vector (now in the virtual photon frame of reference)
  fPhiPQ = hadr.Phi()*TMath::RadToDeg();
  
  return fPhiPQ;
}

Float_t ThetaPQ(Float_t fPex, Float_t fPey, Float_t fPez, Float_t fPx, Float_t fPy, Float_t fPz) {
  // angle between virtual photon and particle
  // (and this makes perfect sense if one draws it)
  Float_t fThetaPQ;
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 virt(-fPex, -fPey, kEbeam - fPez);
  fThetaPQ = virt.Angle(hadr)*TMath::RadToDeg();

  return fThetaPQ;
}

Float_t DeltaTheta(Float_t fPex, Float_t fPey, Float_t fPez, Float_t fPx, Float_t fPy, Float_t fPz) {
  // angle between electron and particle
  
  Float_t deltaTheta;
  TVector3 elec(fPex, fPey, fPez);
  TVector3 part(fPx, fPy, fPz);
  deltaTheta = elec.Angle(part)*TMath::RadToDeg();

  return deltaTheta;
}

Float_t BettaCalc(Float_t fP, Float_t fPid) {
  
  Float_t fM = particleMass(fPid);
  Float_t fBettaCalc = fP/TMath::Sqrt(fP*fP + fM*fM);

  return fBettaCalc;
}
