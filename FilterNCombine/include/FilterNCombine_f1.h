#include "analysisConfig.h"

/*** Constants ***/

extern Float_t kEbeam;

/*** Input variables ***/

// (83 variables for data)
// electron (40)
extern Float_t tQ2, tW, tNu, tXb, tYb, tvxe, tvye, tvze, tSectorEl, tTargType, tPex, tPey, tPez, tPe, tBettaEl, tEtote, tEine, tEoute, tvxec, tvyec, tvzec, tXECe, tYECe, tZECe;
extern Float_t tStatDCEl, tDCStatusEl, tStatECEl, tECStatusEl, tTimeECEl, tPathECEl, tChi2ECEl, tStatSCEl, tSCStatusEl, tTimeSCEl, tPathSCEl, tStatCCEl, tCCStatusEl, tNpheEl, tChi2CCEl, tStatusEl;
// particle (42)
extern Float_t tZh, tThetaPQ, tPt2, tPl2, tPhiPQ, tMx2, tT, tvxh, tvyh, tvzh, tSector, tPx, tPy, tPz, tP, tBetta, tMass2, tEtot, tEin, tEout, tXEC, tYEC, tZEC, tpid, tT4, tdeltaZ;
extern Float_t tStatDC, tDCStatus, tStatEC, tECStatus, tTimeEC, tPathEC, tChi2EC, tStatSC, tSCStatus, tTimeSC, tPathSC, tStatCC, tCCStatus, tNphe, tChi2CC, tStatus;
// event (1)
extern Float_t tevnt;

/*** Output/original variables ***/

// (101 variables for data)
// electron (41)
extern Float_t oQ2, oW, oNu, oXb, oYb, oXe, oYe, oZe, oSectorEl, oTargType, oPex, oPey, oPez, oPe, oBettaEl, oEtote, oEine, oEoute, oXec, oYec, oZec, oXECe, oYECe, oZECe;
extern Float_t oP2e;
extern Float_t oStatDCEl, oDCStatusEl, oStatECEl, oECStatusEl, oTimeECEl, oPathECEl, oChi2ECEl, oStatSCEl, oSCStatusEl, oTimeSCEl, oPathSCEl, oStatCCEl, oCCStatusEl, oNpheEl, oChi2CCEl, oStatusEl;
// particle (60) (16 + 3*6 + 10 + 16)
extern Float_t ovxh, ovyh, ovzh, oSector, oBetta, oMass2, oEtot, oEin, oEout, oXEC, oYEC, oZEC, oPid, oT4, odeltaZ, oM;
extern Float_t oE_prev, oPx_prev, oPy_prev, oPz_prev, oP2_prev, oP_prev;
extern Float_t oE_true, oPx_true, oPy_true, oPz_true, oP2_true, oP_true;
extern Float_t oE_corr, oPx_corr, oPy_corr, oPz_corr, oP2_corr, oP_corr;
extern Float_t oZ, oThetaPQ, oPt2, oPl2, oPhiPQ, oMx2, oT, oCosThetaPQ, oBettaCalc, odeltaTheta;
extern Float_t oStatDC, oDCStatus, oStatEC, oECStatus, oTimeEC, oPathEC, oChi2EC, oStatSC, oSCStatus, oTimeSC, oPathSC, oStatCC, oCCStatus, oNphe, oChi2CC, oStatus;
// event (2)
extern Float_t oEvent;
extern Float_t oEntry; // debug purposes

/*** Output/mix variables ***/

// (194 variables for data)
// electron (41)
extern Float_t mQ2, mW, mNu, mXb, mYb, mXe, mYe, mZe, mSectorEl, mTargType, mPex, mPey, mPez, mPe, mBettaEl, mEtote, mEine, mEoute, mXec, mYec, mZec, mXECe, mYECe, mZECe;
extern Float_t mP2e;
extern Float_t mStatDCEl, mDCStatusEl, mStatECEl, mECStatusEl, mTimeECEl, mPathECEl, mChi2ECEl, mStatSCEl, mSCStatusEl, mTimeSCEl, mPathSCEl, mStatCCEl, mCCStatusEl, mNpheEl, mChi2CCEl, mStatusEl;
// particles (60) (16 + 3*6 + 10 + 16)
extern Float_t mvxh[6], mvyh[6], mvzh[6], mSector[6], mBetta[6], mMass2[6], mEtot[6], mEin[6], mEout[6], mXEC[6], mYEC[6], mZEC[6], mPid[6], mT4[6], mdeltaZ[6], mM[6];
extern Float_t mE_prev[6], mPx_prev[6], mPy_prev[6], mPz_prev[6], mP2_prev[6], mP_prev[6];
extern Float_t mE_true[6], mPx_true[6], mPy_true[6], mPz_true[6], mP2_true[6], mP_true[6];
extern Float_t mE_corr[6], mPx_corr[6], mPy_corr[6], mPz_corr[6], mP2_corr[6], mP_corr[6];
extern Float_t mZ[6], mThetaPQ[6], mPt2[6], mPl2[6], mPhiPQ[6], mMx2[6], mT[6], mCosThetaPQ[6], mBettaCalc[6], mdeltaTheta[6];
extern Float_t mStatDC[6], mDCStatus[6], mStatEC[6], mECStatus[6], mTimeEC[6], mPathEC[6], mChi2EC[6], mStatSC[6];
extern Float_t mSCStatus[6], mTimeSC[6], mPathSC[6], mStatCC[6], mCCStatus[6], mNphe[6], mChi2CC[6], mStatus[6];
// pi0A (24) (3*8new)
extern Float_t pi0A_Px_prev, pi0A_Py_prev, pi0A_Pz_prev, pi0A_P2_prev, pi0A_P_prev, pi0A_E_prev, pi0A_M_prev, pi0A_Theta_prev;
extern Float_t pi0A_Px_true, pi0A_Py_true, pi0A_Pz_true, pi0A_P2_true, pi0A_P_true, pi0A_E_true, pi0A_M_true, pi0A_Theta_true;
extern Float_t pi0A_Px_corr, pi0A_Py_corr, pi0A_Pz_corr, pi0A_P2_corr, pi0A_P_corr, pi0A_E_corr, pi0A_M_corr, pi0A_Theta_corr;
// pi0B (24) (3*8new)
extern Float_t pi0B_Px_prev, pi0B_Py_prev, pi0B_Pz_prev, pi0B_P2_prev, pi0B_P_prev, pi0B_E_prev, pi0B_M_prev, pi0B_Theta_prev;
extern Float_t pi0B_Px_true, pi0B_Py_true, pi0B_Pz_true, pi0B_P2_true, pi0B_P_true, pi0B_E_true, pi0B_M_true, pi0B_Theta_true;
extern Float_t pi0B_Px_corr, pi0B_Py_corr, pi0B_Pz_corr, pi0B_P2_corr, pi0B_P_corr, pi0B_E_corr, pi0B_M_corr, pi0B_Theta_corr;
// f1 (54) (3*18new)
extern Float_t wPx_prev, wPy_prev, wPz_prev, wP_prev, wP2_prev, wE_prev;
extern Float_t wZ_prev, wCosThetaPQ_prev, wThetaPQ_prev, wPt2_prev, wPl2_prev, wPhiPQ_prev, wMx2_prev, wT_prev, wBettaCalc_prev, wdeltaTheta_prev, wM_prev;
extern Float_t wPx_true, wPy_true, wPz_true, wP_true, wP2_true, wE_true;
extern Float_t wZ_true, wCosThetaPQ_true, wThetaPQ_true, wPt2_true, wPl2_true, wPhiPQ_true, wMx2_true, wT_true, wBettaCalc_true, wdeltaTheta_true, wM_true;
extern Float_t wPx_corr, wPy_corr, wPz_corr, wP_corr, wP2_corr, wE_corr;
extern Float_t wZ_corr, wCosThetaPQ_corr, wThetaPQ_corr, wPt2_corr, wPl2_corr, wPhiPQ_corr, wMx2_corr, wT_corr, wBettaCalc_corr, wdeltaTheta_corr, wM_corr;
// number of particles (3)
extern Float_t nPip, nPim, nGamma;
// event related (2)
extern Float_t mEvent;
extern Float_t mEntry[6];

/*** Options ***/

extern TString analyserOption;

/*** Declaration of functions ***/

Float_t ParticleMass(Float_t fPid);
Float_t CorrectEnergy(TString option);
Float_t CorrectMomentum(TString option, TString component);
Float_t PhiPQ(Float_t fPx, Float_t fPy, Float_t fPz);
Float_t ThetaPQ(Float_t fPx, Float_t fPy, Float_t fPz);
Float_t DeltaTheta(Float_t fPx, Float_t fPy, Float_t fPz);
Float_t BettaCalc(Float_t fP, Float_t fPid);

/*** Functions ***/

void SetInputBranches(TChain *chain) {
  // init all variables
  chain->SetBranchStatus("*", 1);
  // electron (40)
  chain->SetBranchAddress("TargType", &tTargType);
  chain->SetBranchAddress("Q2", &tQ2);
  chain->SetBranchAddress("W", &tW);
  chain->SetBranchAddress("Nu", &tNu);
  chain->SetBranchAddress("Xb", &tXb);
  chain->SetBranchAddress("Yb", &tYb);
  chain->SetBranchAddress("SectorEl", &tSectorEl);  
  chain->SetBranchAddress("Pex", &tPex);
  chain->SetBranchAddress("Pey", &tPey);
  chain->SetBranchAddress("Pez", &tPez);
  chain->SetBranchAddress("Pe", &tPe);
  chain->SetBranchAddress("vxe", &tvxe);  
  chain->SetBranchAddress("vye", &tvye);
  chain->SetBranchAddress("vze", &tvze);
  chain->SetBranchAddress("BettaEl", &tBettaEl);
  chain->SetBranchAddress("Etote", &tEtote);
  chain->SetBranchAddress("Eine", &tEine);
  chain->SetBranchAddress("Eoute", &tEoute);
  chain->SetBranchAddress("vxec", &tvxec);
  chain->SetBranchAddress("vyec", &tvyec);
  chain->SetBranchAddress("vzec", &tvzec);
  chain->SetBranchAddress("XECe", &tXECe);
  chain->SetBranchAddress("YECe", &tYECe);
  chain->SetBranchAddress("ZECe", &tZECe);
  // electron status (16)
  chain->SetBranchAddress("StatDCEl", &tStatDCEl);
  chain->SetBranchAddress("DCStatusEl", &tDCStatusEl);
  chain->SetBranchAddress("StatECEl", &tStatECEl);
  chain->SetBranchAddress("ECStatusEl", &tECStatusEl);
  chain->SetBranchAddress("TimeECEl", &tTimeECEl);
  chain->SetBranchAddress("PathECEl", &tPathECEl);
  chain->SetBranchAddress("Chi2ECEl", &tChi2ECEl);
  chain->SetBranchAddress("StatSCEl", &tStatSCEl);
  chain->SetBranchAddress("SCStatusEl", &tSCStatusEl);
  chain->SetBranchAddress("TimeSCEl", &tTimeSCEl);
  chain->SetBranchAddress("PathSCEl", &tPathSCEl);
  chain->SetBranchAddress("StatCCEl", &tStatCCEl);
  chain->SetBranchAddress("CCStatusEl", &tCCStatusEl);
  chain->SetBranchAddress("NpheEl", &tNpheEl);
  chain->SetBranchAddress("Chi2CCEl", &tChi2CCEl);
  chain->SetBranchAddress("StatusEl", &tStatusEl);  
  // particle (26)
  chain->SetBranchAddress("Zh", &tZh);
  chain->SetBranchAddress("Pt2", &tPt2);
  chain->SetBranchAddress("Pl2", &tPl2);
  chain->SetBranchAddress("Mx2", &tMx2);
  chain->SetBranchAddress("T", &tT);
  chain->SetBranchAddress("vxh", &tvxh);
  chain->SetBranchAddress("vyh", &tvyh);
  chain->SetBranchAddress("vzh", &tvzh);
  chain->SetBranchAddress("Sector", &tSector);
  chain->SetBranchAddress("PhiPQ", &tPhiPQ);
  chain->SetBranchAddress("ThetaPQ", &tThetaPQ);
  chain->SetBranchAddress("Etot", &tEtot);
  chain->SetBranchAddress("Ein", &tEin);
  chain->SetBranchAddress("Eout", &tEout);
  chain->SetBranchAddress("Px", &tPx);
  chain->SetBranchAddress("Py", &tPy);
  chain->SetBranchAddress("Pz", &tPz);
  chain->SetBranchAddress("P", &tP);
  chain->SetBranchAddress("XEC", &tXEC);
  chain->SetBranchAddress("YEC", &tYEC);
  chain->SetBranchAddress("ZEC", &tZEC);
  chain->SetBranchAddress("pid", &tpid);
  chain->SetBranchAddress("Betta", &tBetta);
  chain->SetBranchAddress("Mass2", &tMass2);
  chain->SetBranchAddress("T4", &tT4);
  chain->SetBranchAddress("deltaZ", &tdeltaZ);
  // status (16)
  chain->SetBranchAddress("StatDC", &tStatDC);
  chain->SetBranchAddress("DCStatus", &tDCStatus);
  chain->SetBranchAddress("StatEC", &tStatEC);
  chain->SetBranchAddress("ECStatus", &tECStatus);
  chain->SetBranchAddress("TimeEC", &tTimeEC);
  chain->SetBranchAddress("PathEC", &tPathEC);
  chain->SetBranchAddress("Chi2EC", &tChi2EC);
  chain->SetBranchAddress("StatSC", &tStatSC);
  chain->SetBranchAddress("SCStatus", &tSCStatus);
  chain->SetBranchAddress("TimeSC", &tTimeSC);
  chain->SetBranchAddress("PathSC", &tPathSC);
  chain->SetBranchAddress("StatCC", &tStatCC);
  chain->SetBranchAddress("CCStatus", &tCCStatus);
  chain->SetBranchAddress("Nphe", &tNphe);
  chain->SetBranchAddress("Chi2CC", &tChi2CC);
  chain->SetBranchAddress("Status", &tStatus);
  // evnt related (1)
  chain->SetBranchAddress("evnt", &tevnt);
}

void SetOutputBranches(TTree *tree, TString option) {
  if (option == "original") {
    // electron (41)
    // all (25)
    tree->Branch("Q2", &oQ2);
    tree->Branch("W",  &oW);
    tree->Branch("Nu", &oNu);
    tree->Branch("Xb", &oXb);
    tree->Branch("Yb", &oYb);
    tree->Branch("Xe", &oXe);
    tree->Branch("Ye", &oYe);
    tree->Branch("Ze", &oZe);
    tree->Branch("SectorEl", &oSectorEl);
    tree->Branch("TargType", &oTargType);
    tree->Branch("Pex", &oPex);
    tree->Branch("Pey", &oPey);
    tree->Branch("Pez", &oPez);
    tree->Branch("Pe", &oPe);
    tree->Branch("P2e", &oP2e);
    tree->Branch("BettaEl", &oBettaEl);
    tree->Branch("Etote", &oEtote);
    tree->Branch("Eine", &oEine);
    tree->Branch("Eoute", &oEoute);
    tree->Branch("Xec", &oXec);
    tree->Branch("Yec", &oYec);
    tree->Branch("Zec", &oZec);
    tree->Branch("XECe", &oXECe);
    tree->Branch("YECe", &oYECe);
    tree->Branch("ZECe", &oZECe);
    tree->Branch("StatDCEl", &oStatDCEl);
    tree->Branch("DCStatusEl", &oDCStatusEl);
    tree->Branch("StatECEl", &oStatECEl);
    tree->Branch("ECStatusEl", &oECStatusEl);
    tree->Branch("TimeECEl", &oTimeECEl);
    tree->Branch("PathECEl", &oPathECEl);
    tree->Branch("Chi2ECEl", &oChi2ECEl);
    tree->Branch("StatSCEl", &oStatSCEl);
    tree->Branch("SCStatusEl", &oSCStatusEl);
    tree->Branch("TimeSCEl", &oTimeSCEl);
    tree->Branch("PathSCEl", &oPathSCEl);
    tree->Branch("StatCCEl", &oStatCCEl);
    tree->Branch("CCStatusEl", &oCCStatusEl);
    tree->Branch("NpheEl", &oNpheEl);
    tree->Branch("Chi2CCEl", &oChi2CCEl);
    tree->Branch("StatusEl", &oStatusEl);
    // independent (16)
    tree->Branch("Etot", &oEtot);
    tree->Branch("Ein", &oEin);
    tree->Branch("Eout", &oEout);
    tree->Branch("Betta", &oBetta);
    tree->Branch("Mass2", &oMass2);
    tree->Branch("T4", &oT4);
    tree->Branch("vxh", &ovxh);
    tree->Branch("vyh", &ovyh);
    tree->Branch("vzh", &ovzh);
    tree->Branch("deltaZ", &odeltaZ);
    tree->Branch("XEC", &oXEC);
    tree->Branch("YEC", &oYEC);
    tree->Branch("ZEC", &oZEC);
    tree->Branch("Sector", &oSector);
    tree->Branch("Pid", &oPid);
    tree->Branch("M", &oM);
    // prev (6)
    tree->Branch("E_prev",  &oE_prev);
    tree->Branch("Px_prev", &oPx_prev);
    tree->Branch("Py_prev", &oPy_prev);
    tree->Branch("Pz_prev", &oPz_prev);
    tree->Branch("P2_prev", &oP2_prev);
    tree->Branch("P_prev",  &oP_prev);
    // true (6)
    tree->Branch("E_true",  &oE_true);
    tree->Branch("Px_true", &oPx_true);
    tree->Branch("Py_true", &oPy_true);
    tree->Branch("Pz_true", &oPz_true);
    tree->Branch("P2_true", &oP2_true);
    tree->Branch("P_true",  &oP_true);
    // corr (6)
    tree->Branch("E_corr",  &oE_corr);
    tree->Branch("Px_corr", &oPx_corr);
    tree->Branch("Py_corr", &oPy_corr);
    tree->Branch("Pz_corr", &oPz_corr);
    tree->Branch("P2_corr", &oP2_corr);
    tree->Branch("P_corr",  &oP_corr);
    // remaining (10)
    tree->Branch("Z", &oZ);
    tree->Branch("PhiPQ", &oPhiPQ);
    tree->Branch("ThetaPQ", &oThetaPQ);
    tree->Branch("CosThetaPQ", &oCosThetaPQ);
    tree->Branch("Pt2", &oPt2);
    tree->Branch("Pl2", &oPl2);
    tree->Branch("Mx2", &oMx2);
    tree->Branch("T", &oT);
    tree->Branch("BettaCalc", &oBettaCalc);
    tree->Branch("deltaTheta", &odeltaTheta);
    // status (16)
    tree->Branch("StatDC", &oStatDC);
    tree->Branch("DCStatus", &oDCStatus);
    tree->Branch("StatEC", &oStatEC);
    tree->Branch("ECStatus", &oECStatus);
    tree->Branch("TimeEC", &oTimeEC);
    tree->Branch("PathEC", &oPathEC);
    tree->Branch("Chi2EC", &oChi2EC);
    tree->Branch("StatSC", &oStatSC);
    tree->Branch("SCStatus", &oSCStatus);
    tree->Branch("TimeSC", &oTimeSC);
    tree->Branch("PathSC", &oPathSC);
    tree->Branch("StatCC", &oStatCC);
    tree->Branch("CCStatus", &oCCStatus);
    tree->Branch("Nphe", &oNphe);
    tree->Branch("Chi2CC", &oChi2CC);
    tree->Branch("Status", &oStatus);
    // event-related (2)
    tree->Branch("Event", &oEvent);
    tree->Branch("Entry", &oEntry);
  } else if (option == "mix") {
    // electron (41)
    tree->Branch("Q2", &mQ2);
    tree->Branch("W", &mW);
    tree->Branch("Nu", &mNu);
    tree->Branch("Xb", &mXb);
    tree->Branch("Yb", &mYb);
    tree->Branch("Xe", &mXe);
    tree->Branch("Ye", &mYe);
    tree->Branch("Ze", &mZe);
    tree->Branch("SectorEl", &mSectorEl);
    tree->Branch("TargType", &mTargType);
    tree->Branch("Pex", &mPex);
    tree->Branch("Pey", &mPey);
    tree->Branch("Pez", &mPez);
    tree->Branch("Pe", &mPe);
    tree->Branch("P2e", &mP2e);
    tree->Branch("BettaEl", &mBettaEl);
    tree->Branch("Etote", &mEtote);
    tree->Branch("Eine", &mEine);
    tree->Branch("Eoute", &mEoute);
    tree->Branch("Xec", &mXec);
    tree->Branch("Yec", &mYec);
    tree->Branch("Zec", &mZec);
    tree->Branch("XECe", &mXECe);
    tree->Branch("YECe", &mYECe);
    tree->Branch("ZECe", &mZECe);
    tree->Branch("StatDCEl", &mStatDCEl);
    tree->Branch("DCStatusEl", &mDCStatusEl);
    tree->Branch("StatECEl", &mStatECEl);
    tree->Branch("ECStatusEl", &mECStatusEl);
    tree->Branch("TimeECEl", &mTimeECEl);
    tree->Branch("PathECEl", &mPathECEl);
    tree->Branch("Chi2ECEl", &mChi2ECEl);
    tree->Branch("StatSCEl", &mStatSCEl);
    tree->Branch("SCStatusEl", &mSCStatusEl);
    tree->Branch("TimeSCEl", &mTimeSCEl);
    tree->Branch("PathSCEl", &mPathSCEl);
    tree->Branch("StatCCEl", &mStatCCEl);
    tree->Branch("CCStatusEl", &mCCStatusEl);
    tree->Branch("NpheEl", &mNpheEl);
    tree->Branch("Chi2CCEl", &mChi2CCEl);
    tree->Branch("StatusEl", &mStatusEl);
    // independent (16)
    tree->Branch("vxh", &mvxh, "vxh[6]/F");
    tree->Branch("vyh", &mvyh, "vyh[6]/F");
    tree->Branch("vzh", &mvzh, "vzh[6]/F");
    tree->Branch("Sector", &mSector, "Sector[6]/F");
    tree->Branch("Betta", &mBetta, "Betta[6]/F");
    tree->Branch("Mass2", &mMass2, "Mass2[6]/F");
    tree->Branch("Etot", &mEtot, "Etot[6]/F");
    tree->Branch("Ein", &mEin, "Ein[6]/F");
    tree->Branch("Eout", &mEout, "Eout[6]/F");
    tree->Branch("XEC", &mXEC, "XEC[6]/F");
    tree->Branch("YEC", &mYEC, "YEC[6]/F");
    tree->Branch("ZEC", &mZEC, "ZEC[6]/F");
    tree->Branch("Pid", &mPid, "Pid[6]/F");
    tree->Branch("M", &mM, "M[6]/F");
    tree->Branch("T4", &mT4, "T4[6]/F");
    tree->Branch("deltaZ", &mdeltaZ, "deltaZ[6]/F");
    // prev (6)
    tree->Branch("Px_prev", &mPx_prev, "Px_prev[6]/F");
    tree->Branch("Py_prev", &mPy_prev, "Py_prev[6]/F");
    tree->Branch("Pz_prev", &mPz_prev, "Pz_prev[6]/F");
    tree->Branch("P2_prev", &mP2_prev, "P2_prev[6]/F");
    tree->Branch("P_prev", &mP_prev, "P_prev[6]/F");
    tree->Branch("E_prev", &mE_prev, "E_prev[6]/F");
    // true (6)
    tree->Branch("Px_true", &mPx_true, "Px_true[6]/F");
    tree->Branch("Py_true", &mPy_true, "Py_true[6]/F");
    tree->Branch("Pz_true", &mPz_true, "Pz_true[6]/F");
    tree->Branch("P2_true", &mP2_true, "P2_true[6]/F");
    tree->Branch("P_true", &mP_true, "P_true[6]/F");
    tree->Branch("E_true", &mE_true, "E_true[6]/F");
    // corr (6)
    tree->Branch("Px_corr", &mPx_corr, "Px_corr[6]/F");
    tree->Branch("Py_corr", &mPy_corr, "Py_corr[6]/F");
    tree->Branch("Pz_corr", &mPz_corr, "Pz_corr[6]/F");
    tree->Branch("P2_corr", &mP2_corr, "P2_corr[6]/F");
    tree->Branch("P_corr", &mP_corr, "P_corr[6]/F");
    tree->Branch("E_corr", &mE_corr, "E_corr[6]/F");
    // remaining (10)
    tree->Branch("Z", &mZ, "Z[6]/F");
    tree->Branch("PhiPQ", &mPhiPQ, "PhiPQ[6]/F");
    tree->Branch("ThetaPQ", &mThetaPQ, "ThetaPQ[6]/F");
    tree->Branch("CosThetaPQ", &mCosThetaPQ, "CosThetaPQ[6]/F");
    tree->Branch("Pt2", &mPt2, "Pt2[6]/F");
    tree->Branch("Pl2", &mPl2, "Pl2[6]/F");
    tree->Branch("Mx2", &mMx2, "Mx2[6]/F");
    tree->Branch("T", &mT, "T[6]/F");
    tree->Branch("deltaTheta", &mdeltaTheta, "deltaTheta[6]/F");
    tree->Branch("BettaCalc", &mBettaCalc, "BettaCalc[6]/F");
    // status (16)
    tree->Branch("StatDC", &mStatDC, "StatDC[6]/F");
    tree->Branch("DCStatus", &mDCStatus, "DCStatus[6]/F");
    tree->Branch("StatEC", &mStatEC, "StatEC[6]/F");
    tree->Branch("ECStatus", &mECStatus, "ECStatus[6]/F");
    tree->Branch("TimeEC", &mTimeEC, "TimeEC[6]/F");
    tree->Branch("PathEC", &mPathEC, "PathEC[6]/F");
    tree->Branch("Chi2EC", &mChi2EC, "Chi2EC[6]/F");
    tree->Branch("StatSC", &mStatSC, "StatSC[6]/F");
    tree->Branch("SCStatus", &mSCStatus, "SCStatus[6]/F");
    tree->Branch("TimeSC", &mTimeSC, "TimeSC[6]/F");
    tree->Branch("PathSC", &mPathSC, "PathSC[6]/F");
    tree->Branch("StatCC", &mStatCC, "StatCC[6]/F");
    tree->Branch("CCStatus", &mCCStatus, "CCStatus[6]/F");
    tree->Branch("Nphe", &mNphe, "Nphe[6]/F");
    tree->Branch("Chi2CC", &mChi2CC, "Chi2CC[6]/F");
    tree->Branch("Status", &mStatus, "Status[6]/F");
    // pi0A prev (8)
    tree->Branch("pi0A_Px_prev", &pi0A_Px_prev);
    tree->Branch("pi0A_Py_prev", &pi0A_Py_prev);
    tree->Branch("pi0A_Pz_prev", &pi0A_Pz_prev);
    tree->Branch("pi0A_P2_prev", &pi0A_P2_prev);
    tree->Branch("pi0A_P_prev", &pi0A_P_prev);
    tree->Branch("pi0A_E_prev", &pi0A_E_prev);
    tree->Branch("pi0A_M_prev", &pi0A_M_prev);
    tree->Branch("pi0A_Theta_prev", &pi0A_Theta_prev);
    // pi0A true (8)
    tree->Branch("pi0A_Px_true", &pi0A_Px_true);
    tree->Branch("pi0A_Py_true", &pi0A_Py_true);
    tree->Branch("pi0A_Pz_true", &pi0A_Pz_true);
    tree->Branch("pi0A_P2_true", &pi0A_P2_true);
    tree->Branch("pi0A_P_true", &pi0A_P_true);
    tree->Branch("pi0A_E_true", &pi0A_E_true);
    tree->Branch("pi0A_M_true", &pi0A_M_true);
    tree->Branch("pi0A_Theta_true", &pi0A_Theta_true);
    // pi0A corr (8)
    tree->Branch("pi0A_Px_corr", &pi0A_Px_corr);
    tree->Branch("pi0A_Py_corr", &pi0A_Py_corr);
    tree->Branch("pi0A_Pz_corr", &pi0A_Pz_corr);
    tree->Branch("pi0A_P2_corr", &pi0A_P2_corr);
    tree->Branch("pi0A_P_corr", &pi0A_P_corr);
    tree->Branch("pi0A_E_corr", &pi0A_E_corr);
    tree->Branch("pi0A_M_corr", &pi0A_M_corr);
    tree->Branch("pi0A_Theta_corr", &pi0A_Theta_corr);
    // pi0B prev (8)
    tree->Branch("pi0B_Px_prev", &pi0B_Px_prev);
    tree->Branch("pi0B_Py_prev", &pi0B_Py_prev);
    tree->Branch("pi0B_Pz_prev", &pi0B_Pz_prev);
    tree->Branch("pi0B_P2_prev", &pi0B_P2_prev);
    tree->Branch("pi0B_P_prev", &pi0B_P_prev);
    tree->Branch("pi0B_E_prev", &pi0B_E_prev);
    tree->Branch("pi0B_M_prev", &pi0B_M_prev);
    tree->Branch("pi0B_Theta_prev", &pi0B_Theta_prev);
    // pi0B true (8)
    tree->Branch("pi0B_Px_true", &pi0B_Px_true);
    tree->Branch("pi0B_Py_true", &pi0B_Py_true);
    tree->Branch("pi0B_Pz_true", &pi0B_Pz_true);
    tree->Branch("pi0B_P2_true", &pi0B_P2_true);
    tree->Branch("pi0B_P_true", &pi0B_P_true);
    tree->Branch("pi0B_E_true", &pi0B_E_true);
    tree->Branch("pi0B_M_true", &pi0B_M_true);
    tree->Branch("pi0B_Theta_true", &pi0B_Theta_true);
    // pi0B corr (8)
    tree->Branch("pi0B_Px_corr", &pi0B_Px_corr);
    tree->Branch("pi0B_Py_corr", &pi0B_Py_corr);
    tree->Branch("pi0B_Pz_corr", &pi0B_Pz_corr);
    tree->Branch("pi0B_P2_corr", &pi0B_P2_corr);
    tree->Branch("pi0B_P_corr", &pi0B_P_corr);
    tree->Branch("pi0B_E_corr", &pi0B_E_corr);
    tree->Branch("pi0B_M_corr", &pi0B_M_corr);
    tree->Branch("pi0B_Theta_corr", &pi0B_Theta_corr);
    // f1 prev (18)
    tree->Branch("wZ_prev", &wZ_prev);
    tree->Branch("wPhiPQ_prev", &wPhiPQ_prev);
    tree->Branch("wThetaPQ_prev", &wThetaPQ_prev);
    tree->Branch("wCosThetaPQ_prev", &wCosThetaPQ_prev);
    tree->Branch("wPt2_prev", &wPt2_prev);
    tree->Branch("wPl2_prev", &wPl2_prev);
    tree->Branch("wMx2_prev", &wMx2_prev);
    tree->Branch("wT_prev", &wT_prev);
    tree->Branch("wPx_prev", &wPx_prev);
    tree->Branch("wPy_prev", &wPy_prev);
    tree->Branch("wPz_prev", &wPz_prev);
    tree->Branch("wP2_prev", &wP2_prev);
    tree->Branch("wP_prev", &wP_prev);
    tree->Branch("wE_prev", &wE_prev);
    tree->Branch("wBettaCalc_prev", &wBettaCalc_prev);
    tree->Branch("wdeltaTheta_prev", &wdeltaTheta_prev);
    tree->Branch("wM_prev", &wM_prev);
    // f1 true (18)
    tree->Branch("wZ_true", &wZ_true);
    tree->Branch("wPhiPQ_true", &wPhiPQ_true);
    tree->Branch("wThetaPQ_true", &wThetaPQ_true);
    tree->Branch("wCosThetaPQ_true", &wCosThetaPQ_true);
    tree->Branch("wPt2_true", &wPt2_true);
    tree->Branch("wPl2_true", &wPl2_true);
    tree->Branch("wMx2_true", &wMx2_true);
    tree->Branch("wT_true", &wT_true);
    tree->Branch("wPx_true", &wPx_true);
    tree->Branch("wPy_true", &wPy_true);
    tree->Branch("wPz_true", &wPz_true);
    tree->Branch("wP2_true", &wP2_true);
    tree->Branch("wP_true", &wP_true);
    tree->Branch("wE_true", &wE_true);
    tree->Branch("wBettaCalc_true", &wBettaCalc_true);
    tree->Branch("wdeltaTheta_true", &wdeltaTheta_true);
    tree->Branch("wM_true", &wM_true);
    // f1 corr (18)
    tree->Branch("wZ_corr", &wZ_corr);
    tree->Branch("wPhiPQ_corr", &wPhiPQ_corr);
    tree->Branch("wThetaPQ_corr", &wThetaPQ_corr);
    tree->Branch("wCosThetaPQ_corr", &wCosThetaPQ_corr);
    tree->Branch("wPt2_corr", &wPt2_corr);
    tree->Branch("wPl2_corr", &wPl2_corr);
    tree->Branch("wMx2_corr", &wMx2_corr);
    tree->Branch("wT_corr", &wT_corr);
    tree->Branch("wPx_corr", &wPx_corr);
    tree->Branch("wPy_corr", &wPy_corr);
    tree->Branch("wPz_corr", &wPz_corr);
    tree->Branch("wP2_corr", &wP2_corr);
    tree->Branch("wP_corr", &wP_corr);
    tree->Branch("wE_corr", &wE_corr);
    tree->Branch("wBettaCalc_corr", &wBettaCalc_corr);
    tree->Branch("wdeltaTheta_corr", &wdeltaTheta_corr);
    tree->Branch("wM_corr", &wM_corr);
    // number of particles in that event (3)
    tree->Branch("nPip", &nPip);
    tree->Branch("nPim", &nPim);
    tree->Branch("nGamma", &nGamma);
    // event related (2)
    tree->Branch("Entry", &mEntry, "Entry[6]/F");
    tree->Branch("Event", &mEvent);
  }
}

void AssignOriginal(Int_t entry) {
  // std::cout << "  !! AOV initiating..." << std::endl;
  // electron (41)
  oQ2 = tQ2;
  oW  = tW;
  oNu = tNu;
  oXb = tXb;
  oYb = tYb;
  oXe = tvxe;
  oYe = tvye;
  oZe = tvze;
  oSectorEl = tSectorEl;
  oTargType = tTargType;
  oPex = tPex;
  oPey = tPey;
  oPez = tPez;
  oPe  = tPe;
  oP2e = oPe*oPe; // recalc
  oBettaEl = tBettaEl;
  oEtote = tEtote;
  oEine  = tEine;
  oEoute = tEoute;
  oXec = tvxec;
  oYec = tvyec;
  oZec = tvzec;
  oXECe = tXECe;
  oYECe = tYECe;
  oZECe = tZECe;
  oStatDCEl   = tStatDCEl;
  oDCStatusEl = tDCStatusEl;
  oStatECEl   = tStatECEl;
  oECStatusEl = tECStatusEl;
  oTimeECEl   = tTimeECEl;
  oPathECEl   = tPathECEl;
  oChi2ECEl   = tChi2ECEl;
  oStatSCEl   = tStatSCEl;
  oSCStatusEl = tSCStatusEl;
  oTimeSCEl   = tTimeSCEl;
  oPathSCEl   = tPathSCEl;
  oStatCCEl   = tStatCCEl;
  oCCStatusEl = tCCStatusEl;
  oNpheEl     = tNpheEl;
  oChi2CCEl   = tChi2CCEl;
  oStatusEl   = tStatusEl;
  // independent variables (16)
  ovxh = tvxh;
  ovyh = tvyh;
  ovzh = tvzh;
  oSector = tSector;
  oEtot = tEtot;
  oEin  = tEin;
  oEout = tEout;
  oXEC = tXEC;
  oYEC = tYEC;
  oZEC = tZEC;
  odeltaZ = tdeltaZ;
  oBetta = tBetta;
  oMass2 = tMass2;
  oT4 = tT4;
  oPid = tpid; // important!
  oM = ParticleMass(tpid);
  // prev (6)
  oE_prev  = CorrectEnergy("prev");
  oPx_prev = tPx;
  oPy_prev = tPy;
  oPz_prev = tPz;
  oP_prev  = tP;
  oP2_prev = oP_prev*oP_prev; // recalc
  // true (6)
  oE_true  = CorrectEnergy("true");
  oPx_true = CorrectMomentum("x", "true");
  oPy_true = CorrectMomentum("y", "true");
  oPz_true = CorrectMomentum("z", "true");
  oP2_true = oPx_true*oPx_true + oPy_true*oPy_true + + oPz_true*oPz_true;
  oP_true  = TMath::Sqrt(oP2_true);
  // corr (6)
  oE_corr  = CorrectEnergy("corr");
  oPx_corr = CorrectMomentum("x", "corr");
  oPy_corr = CorrectMomentum("y", "corr");
  oPz_corr = CorrectMomentum("z", "corr");
  oP2_corr = oPx_corr*oPx_corr + oPy_corr*oPy_corr + + oPz_corr*oPz_corr;
  oP_corr  = TMath::Sqrt(oP2_corr);
  // remaining (10) - using corr values
  oZ          = oE_corr/oNu;
  oPhiPQ      = PhiPQ(oPx_corr, oPy_corr, oPz_corr);
  oThetaPQ    = ThetaPQ(oPx_corr, oPy_corr, oPz_corr);
  oCosThetaPQ = ((kEbeam - oPez)*oPz_corr - oPex*oPx_corr - oPey*oPy_corr)/(TMath::Sqrt(oP2_corr*(oQ2 + oNu*oNu)));
  oPt2        = oP2_corr*(1 - oCosThetaPQ*oCosThetaPQ);
  oPl2        = oP2_corr*oCosThetaPQ*oCosThetaPQ;
  oMx2        = tW*tW + oM*oM - 2*oZ*oNu*oNu + 2*TMath::Sqrt(oPl2*(oNu*oNu + oQ2)) - 2*kMproton*oZ*oNu;
  oT          = oM*oM - 2*oZ*oNu*oNu + 2*TMath::Sqrt(oPl2*(oNu*oNu + oQ2)) - oQ2;
  oBettaCalc  = BettaCalc(oP_corr, oPid);
  odeltaTheta = DeltaTheta(oPx_corr, oPy_corr, oPz_corr);
  // status (16)
  oStatDC   = tStatDC;
  oDCStatus = tDCStatus;
  oStatEC   = tStatEC;
  oECStatus = tECStatus;
  oTimeEC   = tTimeEC;
  oPathEC   = tPathEC;
  oChi2EC   = tChi2EC;
  oStatSC   = tStatSC;
  oSCStatus = tSCStatus;
  oTimeSC   = tTimeSC;
  oPathSC   = tPathSC;
  oStatCC   = tStatCC;
  oCCStatus = tCCStatus;
  oNphe     = tNphe;
  oChi2CC   = tChi2CC;
  oStatus   = tStatus;
  // event-related (2)
  oEvent = tevnt; // important!
  oEntry = (Float_t) entry;
}

void AssignMix(Float_t entry, Int_t index) {
  // std::cout << "  !! AMV initiating..." << std::endl;
  // electron (41)
  mQ2 = tQ2;
  mW  = tW;
  mNu = tNu;
  mXb = tXb;
  mYb = tYb;
  mXe = tvxe;
  mYe = tvye;
  mZe = tvze;
  mSectorEl = tSectorEl;
  mTargType = tTargType;
  mPex = tPex;
  mPey = tPey;
  mPez = tPez;
  mPe  = tPe;
  mP2e = mPe*mPe; // recalc
  mBettaEl = tBettaEl;
  mEtote = tEtote;
  mEine  = tEine;
  mEoute = tEoute;
  mXec = tvxec;
  mYec = tvyec;
  mZec = tvzec;
  mXECe = tXECe;
  mYECe = tYECe;
  mZECe = tZECe;
  mStatDCEl   = tStatDCEl;
  mDCStatusEl = tDCStatusEl;
  mStatECEl   = tStatECEl;
  mECStatusEl = tECStatusEl;
  mTimeECEl   = tTimeECEl;
  mPathECEl   = tPathECEl;
  mChi2ECEl   = tChi2ECEl;
  mStatSCEl   = tStatSCEl;
  mSCStatusEl = tSCStatusEl;
  mTimeSCEl   = tTimeSCEl;
  mPathSCEl   = tPathSCEl;
  mStatCCEl   = tStatCCEl;
  mCCStatusEl = tCCStatusEl;
  mNpheEl     = tNpheEl;
  mChi2CCEl   = tChi2CCEl;
  mStatusEl   = tStatusEl;
  // independent variables (16)
  mvxh[index] = tvxh;
  mvyh[index] = tvyh;
  mvzh[index] = tvzh;
  mSector[index] = tSector;
  mXEC[index] = tXEC;
  mYEC[index] = tYEC;
  mZEC[index] = tZEC;
  mEtot[index] = tEtot;
  mEin[index]  = tEin;
  mEout[index] = tEout;
  mdeltaZ[index] = tdeltaZ;
  mT4[index] = tT4;
  mMass2[index] = tMass2;
  mBetta[index] = tBetta;
  mPid[index] = tpid; // important!
  mM[index] = ParticleMass(tpid);
  // prev (6)
  mE_prev[index]  = CorrectEnergy("prev");
  mPx_prev[index] = tPx;
  mPy_prev[index] = tPy;
  mPz_prev[index] = tPz;
  mP_prev[index]  = tP;
  mP2_prev[index] = mP_prev[index]*mP_prev[index]; // recalc
  // true (6)
  mE_true[index]  = CorrectEnergy("true");
  mPx_true[index] = CorrectMomentum("x", "true");
  mPy_true[index] = CorrectMomentum("y", "true");
  mPz_true[index] = CorrectMomentum("z", "true");
  mP2_true[index] = mPx_true[index]*mPx_true[index] + mPy_true[index]*mPy_true[index] + mPz_true[index]*mPz_true[index];
  mP_true[index]  = TMath::Sqrt(mP2_true[index]);
  // corr (6)
  mE_corr[index]  = CorrectEnergy("corr");
  mPx_corr[index] = CorrectMomentum("x", "corr");
  mPy_corr[index] = CorrectMomentum("y", "corr");
  mPz_corr[index] = CorrectMomentum("z", "corr");
  mP2_corr[index] = mPx_corr[index]*mPx_corr[index] + mPy_corr[index]*mPy_corr[index] + mPz_corr[index]*mPz_corr[index];
  mP_corr[index]  = TMath::Sqrt(mP2_corr[index]);
  // remaining (10) - using corr values
  mZ[index]          = mE_corr[index]/mNu;
  mPhiPQ[index]      = PhiPQ(mPx_corr[index], mPy_corr[index], mPz_corr[index]);
  mThetaPQ[index]    = ThetaPQ(mPx_corr[index], mPy_corr[index], mPz_corr[index]);
  mCosThetaPQ[index] = ((kEbeam - mPez)*mPz_corr[index] - mPex*mPx_corr[index] - mPey*mPy_corr[index])/(TMath::Sqrt(mP2_corr[index]*(mQ2 + mNu*mNu)));
  mPt2[index]        = mP2_corr[index]*(1 - mCosThetaPQ[index]*mCosThetaPQ[index]);
  mPl2[index]        = mP2_corr[index]*mCosThetaPQ[index]*mCosThetaPQ[index];
  mdeltaTheta[index] = DeltaTheta(mPx_corr[index], mPy_corr[index], mPz_corr[index]);
  mMx2[index]        = mW*mW + mM[index]*mM[index] - 2*mZ[index]*mNu*mNu + 2*TMath::Sqrt(mPl2[index]*(mNu*mNu + mQ2)) - 2*kMproton*mZ[index]*mNu;
  mT[index]          = mM[index]*mM[index] - 2*mZ[index]*mNu*mNu + 2*TMath::Sqrt(mPl2[index]*(mNu*mNu + mQ2)) - mQ2;
  mBettaCalc[index]  = BettaCalc(mP_corr[index], mPid[index]);
  // status (16)
  mStatDC[index]   = tStatDC;
  mDCStatus[index] = tDCStatus;
  mStatEC[index]   = tStatEC;
  mECStatus[index] = tECStatus;
  mTimeEC[index]   = tTimeEC;
  mPathEC[index]   = tPathEC;
  mChi2EC[index]   = tChi2EC;
  mStatSC[index]   = tStatSC;
  mSCStatus[index] = tSCStatus;
  mTimeSC[index]   = tTimeSC;
  mPathSC[index]   = tPathSC;
  mStatCC[index]   = tStatCC;
  mCCStatus[index] = tCCStatus;
  mNphe[index]     = tNphe;
  mChi2CC[index]   = tChi2CC;
  mStatus[index]   = tStatus;
  // event related (2)
  mEvent = tevnt; // important!
  mEntry[index] = entry;
}

void AssignPi0A() {
  // std::cout << "  !! APi0AV initiating..." << std::endl;
  // pi0 prev (8)
  pi0A_Px_prev = mPx_prev[0] + mPx_prev[1];
  pi0A_Py_prev = mPy_prev[0] + mPy_prev[1];
  pi0A_Pz_prev = mPz_prev[0] + mPz_prev[1];
  pi0A_P2_prev = pi0A_Px_prev*pi0A_Px_prev + pi0A_Py_prev*pi0A_Py_prev + pi0A_Pz_prev*pi0A_Pz_prev;
  pi0A_P_prev  = TMath::Sqrt(pi0A_P2_prev);
  pi0A_E_prev  = mE_prev[0] + mE_prev[1];
  pi0A_M_prev  = TMath::Sqrt(pi0A_E_prev*pi0A_E_prev - pi0A_P2_prev);
  Double_t dot   = mPx_prev[0]*mPx_prev[1] + mPy_prev[0]*mPy_prev[1] + mPz_prev[0]*mPz_prev[1];
  Double_t mag_0 = TMath::Sqrt(mPx_prev[0]*mPx_prev[0] + mPy_prev[0]*mPy_prev[0] + mPz_prev[0]*mPz_prev[0]);
  Double_t mag_1 = TMath::Sqrt(mPx_prev[1]*mPx_prev[1] + mPy_prev[1]*mPy_prev[1] + mPz_prev[1]*mPz_prev[1]);
  pi0A_Theta_prev = TMath::RadToDeg()*TMath::ACos(dot/(mag_0*mag_1));
  // pi0A_ true (8)
  pi0A_Px_true = mPx_true[0] + mPx_true[1];
  pi0A_Py_true = mPy_true[0] + mPy_true[1];
  pi0A_Pz_true = mPz_true[0] + mPz_true[1];
  pi0A_P2_true = pi0A_Px_true*pi0A_Px_true + pi0A_Py_true*pi0A_Py_true + pi0A_Pz_true*pi0A_Pz_true;
  pi0A_P_true  = TMath::Sqrt(pi0A_P2_true);
  pi0A_E_true  = mE_true[0] + mE_true[1];
  pi0A_M_true  = TMath::Sqrt(pi0A_E_true*pi0A_E_true - pi0A_P2_true);
  dot   = mPx_true[0]*mPx_true[1] + mPy_true[0]*mPy_true[1] + mPz_true[0]*mPz_true[1];
  mag_0 = TMath::Sqrt(mPx_true[0]*mPx_true[0] + mPy_true[0]*mPy_true[0] + mPz_true[0]*mPz_true[0]);
  mag_1 = TMath::Sqrt(mPx_true[1]*mPx_true[1] + mPy_true[1]*mPy_true[1] + mPz_true[1]*mPz_true[1]);
  pi0A_Theta_true = TMath::RadToDeg()*TMath::ACos(dot/(mag_0*mag_1));
  // pi0A_ corr (8)
  pi0A_Px_corr = mPx_corr[0] + mPx_corr[1];
  pi0A_Py_corr = mPy_corr[0] + mPy_corr[1];
  pi0A_Pz_corr = mPz_corr[0] + mPz_corr[1];
  pi0A_P2_corr = pi0A_Px_corr*pi0A_Px_corr + pi0A_Py_corr*pi0A_Py_corr + pi0A_Pz_corr*pi0A_Pz_corr;
  pi0A_P_corr  = TMath::Sqrt(pi0A_P2_corr);
  pi0A_E_corr  = mE_corr[0] + mE_corr[1];
  pi0A_M_corr  = TMath::Sqrt(pi0A_E_corr*pi0A_E_corr - pi0A_P2_corr);
  dot   = mPx_corr[0]*mPx_corr[1] + mPy_corr[0]*mPy_corr[1] + mPz_corr[0]*mPz_corr[1];
  mag_0 = TMath::Sqrt(mPx_corr[0]*mPx_corr[0] + mPy_corr[0]*mPy_corr[0] + mPz_corr[0]*mPz_corr[0]);
  mag_1 = TMath::Sqrt(mPx_corr[1]*mPx_corr[1] + mPy_corr[1]*mPy_corr[1] + mPz_corr[1]*mPz_corr[1]);
  pi0A_Theta_corr = TMath::RadToDeg()*TMath::ACos(dot/(mag_0*mag_1));
  // std::cout << "  !! APi0AV ready!" << std::endl;
}

void AssignPi0B() {
  // std::cout << "  !! APi0BV initiating..." << std::endl;
  // pi0 prev (8)
  pi0B_Px_prev = mPx_prev[2] + mPx_prev[3];
  pi0B_Py_prev = mPy_prev[2] + mPy_prev[3];
  pi0B_Pz_prev = mPz_prev[2] + mPz_prev[3];
  pi0B_P2_prev = pi0B_Px_prev*pi0B_Px_prev + pi0B_Py_prev*pi0B_Py_prev + pi0B_Pz_prev*pi0B_Pz_prev;
  pi0B_P_prev  = TMath::Sqrt(pi0B_P2_prev);
  pi0B_E_prev  = mE_prev[2] + mE_prev[3];
  pi0B_M_prev  = TMath::Sqrt(pi0B_E_prev*pi0B_E_prev - pi0B_P2_prev);
  Double_t dot   = mPx_prev[2]*mPx_prev[3] + mPy_prev[2]*mPy_prev[3] + mPz_prev[2]*mPz_prev[3];
  Double_t mag_0 = TMath::Sqrt(mPx_prev[2]*mPx_prev[2] + mPy_prev[2]*mPy_prev[2] + mPz_prev[2]*mPz_prev[2]);
  Double_t mag_1 = TMath::Sqrt(mPx_prev[3]*mPx_prev[3] + mPy_prev[3]*mPy_prev[3] + mPz_prev[3]*mPz_prev[3]);
  pi0B_Theta_prev = TMath::RadToDeg()*TMath::ACos(dot/(mag_0*mag_1));
  // pi0B_ true (8)
  pi0B_Px_true = mPx_true[2] + mPx_true[3];
  pi0B_Py_true = mPy_true[2] + mPy_true[3];
  pi0B_Pz_true = mPz_true[2] + mPz_true[3];
  pi0B_P2_true = pi0B_Px_true*pi0B_Px_true + pi0B_Py_true*pi0B_Py_true + pi0B_Pz_true*pi0B_Pz_true;
  pi0B_P_true  = TMath::Sqrt(pi0B_P2_true);
  pi0B_E_true  = mE_true[2] + mE_true[3];
  pi0B_M_true  = TMath::Sqrt(pi0B_E_true*pi0B_E_true - pi0B_P2_true);
  dot   = mPx_true[2]*mPx_true[3] + mPy_true[2]*mPy_true[3] + mPz_true[2]*mPz_true[3];
  mag_0 = TMath::Sqrt(mPx_true[2]*mPx_true[2] + mPy_true[2]*mPy_true[2] + mPz_true[2]*mPz_true[2]);
  mag_1 = TMath::Sqrt(mPx_true[3]*mPx_true[3] + mPy_true[3]*mPy_true[3] + mPz_true[3]*mPz_true[3]);
  pi0B_Theta_true = TMath::RadToDeg()*TMath::ACos(dot/(mag_0*mag_1));
  // pi0 corr (8)
  pi0B_Px_corr = mPx_corr[2] + mPx_corr[3];
  pi0B_Py_corr = mPy_corr[2] + mPy_corr[3];
  pi0B_Pz_corr = mPz_corr[2] + mPz_corr[3];
  pi0B_P2_corr = pi0B_Px_corr*pi0B_Px_corr + pi0B_Py_corr*pi0B_Py_corr + pi0B_Pz_corr*pi0B_Pz_corr;
  pi0B_P_corr  = TMath::Sqrt(pi0B_P2_corr);
  pi0B_E_corr  = mE_corr[2] + mE_corr[3];
  pi0B_M_corr  = TMath::Sqrt(pi0B_E_corr*pi0B_E_corr - pi0B_P2_corr);
  dot   = mPx_corr[2]*mPx_corr[3] + mPy_corr[2]*mPy_corr[3] + mPz_corr[2]*mPz_corr[3];
  mag_0 = TMath::Sqrt(mPx_corr[2]*mPx_corr[2] + mPy_corr[2]*mPy_corr[2] + mPz_corr[2]*mPz_corr[2]);
  mag_1 = TMath::Sqrt(mPx_corr[3]*mPx_corr[3] + mPy_corr[3]*mPy_corr[3] + mPz_corr[3]*mPz_corr[3]);
  pi0B_Theta_corr = TMath::RadToDeg()*TMath::ACos(dot/(mag_0*mag_1));
  // std::cout << "  !! APi0BV ready!" << std::endl;
}

void Assignf1() {
  // std::cout << "  !! Af1V initiating..." << std::endl;
  // f1 prev (6+12)
  wPx_prev = pi0A_Px_prev + pi0B_Px_prev + mPx_prev[4] + mPx_prev[5];
  wPy_prev = pi0A_Py_prev + pi0B_Py_prev + mPy_prev[4] + mPy_prev[5];
  wPz_prev = pi0A_Pz_prev + pi0B_Pz_prev + mPz_prev[4] + mPz_prev[5];
  wP2_prev = wPx_prev*wPx_prev + wPy_prev*wPy_prev + wPz_prev*wPz_prev;
  wP_prev  = TMath::Sqrt(wP2_prev);
  wE_prev  = pi0A_E_prev + pi0B_E_prev + mE_prev[4] + mE_prev[5];
  wM_prev  = TMath::Sqrt(wE_prev*wE_prev - wP2_prev);
  wZ_prev  = wE_prev/mNu;
  wPhiPQ_prev = PhiPQ(wPx_prev, wPy_prev, wPz_prev);
  wThetaPQ_prev = ThetaPQ(wPx_prev, wPy_prev, wPz_prev);
  wCosThetaPQ_prev = ((kEbeam - mPez)*wPz_prev - mPex*wPx_prev - mPey*wPy_prev)/(TMath::Sqrt(wP2_prev*(mQ2 + mNu*mNu)));
  wPt2_prev = wP2_prev*(1 - wCosThetaPQ_prev*wCosThetaPQ_prev);
  wPl2_prev = wP2_prev*wCosThetaPQ_prev*wCosThetaPQ_prev;
  wMx2_prev = mW*mW + wM_prev*wM_prev - 2*wZ_prev*mNu*mNu + 2*TMath::Sqrt(wPl2_prev*(mNu*mNu + mQ2)) - 2*kMproton*wZ_prev*mNu;
  wT_prev = wM_prev*wM_prev - 2*wZ_prev*mNu*mNu + 2*TMath::Sqrt(wPl2_prev*(mNu*mNu + mQ2)) - mQ2;
  wBettaCalc_prev = BettaCalc(wP_prev, 20223);
  wdeltaTheta_prev = DeltaTheta(wPx_prev, wPy_prev, wPz_prev);
  // f1 true (6+12)
  wPx_true = pi0A_Px_true + pi0B_Px_true + mPx_true[4] + mPx_true[5];
  wPy_true = pi0A_Py_true + pi0B_Py_true + mPy_true[4] + mPy_true[5];
  wPz_true = pi0A_Pz_true + pi0B_Pz_true + mPz_true[4] + mPz_true[5];
  wP2_true = wPx_true*wPx_true + wPy_true*wPy_true + wPz_true*wPz_true;
  wP_true  = TMath::Sqrt(wP2_true);
  wE_true  = pi0A_E_true + pi0B_E_true + mE_true[4] + mE_true[5];
  wM_true  = TMath::Sqrt(wE_true*wE_true - wP2_true);
  wZ_true  = wE_true/mNu;
  wPhiPQ_true = PhiPQ(wPx_true, wPy_true, wPz_true);
  wThetaPQ_true = ThetaPQ(wPx_true, wPy_true, wPz_true);
  wCosThetaPQ_true = ((kEbeam - mPez)*wPz_true - mPex*wPx_true - mPey*wPy_true)/(TMath::Sqrt(wP2_true*(mQ2 + mNu*mNu)));
  wPt2_true = wP2_true*(1 - wCosThetaPQ_true*wCosThetaPQ_true);
  wPl2_true = wP2_true*wCosThetaPQ_true*wCosThetaPQ_true;
  wMx2_true = mW*mW + wM_true*wM_true - 2*wZ_true*mNu*mNu + 2*TMath::Sqrt(wPl2_true*(mNu*mNu + mQ2)) - 2*kMproton*wZ_true*mNu;
  wT_true = wM_true*wM_true - 2*wZ_true*mNu*mNu + 2*TMath::Sqrt(wPl2_true*(mNu*mNu + mQ2)) - mQ2;
  wBettaCalc_true = BettaCalc(wP_true, 20223);
  wdeltaTheta_true = DeltaTheta(wPx_true, wPy_true, wPz_true);
  // f1 corr (6+12)
  wPx_corr = pi0A_Px_corr + pi0B_Px_corr + mPx_corr[4] + mPx_corr[5];
  wPy_corr = pi0A_Py_corr + pi0B_Py_corr + mPy_corr[4] + mPy_corr[5];
  wPz_corr = pi0A_Pz_corr + pi0B_Pz_corr + mPz_corr[4] + mPz_corr[5];
  wP2_corr = wPx_corr*wPx_corr + wPy_corr*wPy_corr + wPz_corr*wPz_corr;
  wP_corr  = TMath::Sqrt(wP2_corr);
  wE_corr  = pi0A_E_corr + pi0B_E_corr + mE_corr[4] + mE_corr[5];
  wM_corr  = TMath::Sqrt(wE_corr*wE_corr - wP2_corr);
  wZ_corr  = wE_corr/mNu;
  wPhiPQ_corr = PhiPQ(wPx_corr, wPy_corr, wPz_corr);
  wThetaPQ_corr = ThetaPQ(wPx_corr, wPy_corr, wPz_corr);
  wCosThetaPQ_corr = ((kEbeam - mPez)*wPz_corr - mPex*wPx_corr - mPey*wPy_corr)/(TMath::Sqrt(wP2_corr*(mQ2 + mNu*mNu)));
  wPt2_corr = wP2_corr*(1 - wCosThetaPQ_corr*wCosThetaPQ_corr);
  wPl2_corr = wP2_corr*wCosThetaPQ_corr*wCosThetaPQ_corr;
  wMx2_corr = mW*mW + wM_corr*wM_corr - 2*wZ_corr*mNu*mNu + 2*TMath::Sqrt(wPl2_corr*(mNu*mNu + mQ2)) - 2*kMproton*wZ_corr*mNu;
  wT_corr = wM_corr*wM_corr - 2*wZ_corr*mNu*mNu + 2*TMath::Sqrt(wPl2_corr*(mNu*mNu + mQ2)) - mQ2;
  wBettaCalc_corr = BettaCalc(wP_corr, 20223);
  wdeltaTheta_corr = DeltaTheta(wPx_corr, wPy_corr, wPz_corr);
  // std::cout << "  !! Af1V ready!" << std::endl;
}

void AssignMore(Int_t fnGamma, Int_t fnPip, Int_t fnPim) {
  // (these variables depend that all the other variables from decay particles are set and ready)
  // std::cout << "  !! AmoreV initiating..." << std::endl;
  // number of particles (3)
  nGamma = (Float_t) fnGamma;
  nPip   = (Float_t) fnPip;
  nPim   = (Float_t) fnPim;
  // std::cout << "  !! AmoreV ready!" << std::endl;
}

/*** Mathematical functions ***/

Float_t ParticleMass(Float_t fPid) {
  TDatabasePDG fPDG;
  if (fPid == -9999) return -9999; // closure
  return fPDG.GetParticle((Int_t) fPid)->Mass();
}

Float_t CorrectEnergy(TString option) {
  // (global variables: tEtot, tEin, tEout, tpid, tP, analyserOption)
  
  // for charged pions, assign energy from measured momentum and pdg mass
  // for gammas, there are 3 options
  // prev : chooses max between Etot and Ein+Eout
  // true : from prev, applies the primitive sampling fraction factor of EC
  // corr : from true, applies the correction studied by TM

  Float_t fE;
  Float_t corrFactor;

  if (tpid == 22) {
    if (option == "prev") {
      fE = tP;
    } else if (option == "true") {
      fE = TMath::Max(tEtot, tEin+tEout)/0.272;
    } else if (option == "corr") {
      if (analyserOption == "C" || analyserOption == "Pb") {
	fE = TMath::Max(tEtot, tEin+tEout)/0.272;
	corrFactor = 1.129 - 0.05793/fE - 1.0773e-12/(fE*fE);
      } else if (analyserOption == "Fe") {
	fE = TMath::Max(tEtot, tEin+tEout)/0.272;
	corrFactor = 1.116 - 0.09213/fE + 0.01007/(fE*fE);
      }
      // finally
      fE = fE/corrFactor;
    } // end of option condition
  } else if (tpid == 211 || tpid == -211) {
    fE = TMath::Sqrt(tP*tP + ParticleMass(tpid)*ParticleMass(tpid));
  }
  
  return fE;
}

Float_t CorrectMomentum(TString component, TString option) {
  // (global variables: tXEC, tYEC, tZEC, tvzec, tpid)
  
  // for charged pions, do nothing
  // for gammas, there are 2 options
  // true : use energy obtained from CorrectEnergy("true")
  // corr : use energy obtained from CorrectEnergy("corr")

  // string to int
  Int_t i;
  Float_t fPi;
  if (component == "x") {
    i = 0;
    fPi = tPx;
  } else if (component == "y") {
    i = 1;
    fPi = tPy;
  } else if (component == "z") {
    i = 2;
    fPi = tPz;
  }
  
  Float_t fP[3];
  Float_t fPcorr;
  
  if (tpid == 22) {
    Float_t Rt = TMath::Sqrt(tXEC*tXEC + tYEC*tYEC);
    Float_t R = TMath::Sqrt(tXEC*tXEC + tYEC*tYEC + (tZEC - tvzec)*(tZEC - tvzec));
    Float_t theta_gam = TMath::ASin(Rt/R);
    Float_t phi_gam = TMath::ATan2(tYEC, tXEC);
    
    fP[0] = CorrectEnergy(option)*TMath::Sin(theta_gam)*TMath::Cos(phi_gam); // x
    fP[1] = CorrectEnergy(option)*TMath::Sin(theta_gam)*TMath::Sin(phi_gam); // y
    fP[2] = CorrectEnergy(option)*TMath::Cos(theta_gam);                     // z

    fPcorr = fP[i];
  } else if (tpid == 211 || tpid == -211) {
    fPcorr = fPi;
  }
  
  return fPcorr;
}

Float_t PhiPQ(Float_t fPx, Float_t fPy, Float_t fPz) {
  // (global variables: tPex, tPey, tPez)
  
  Float_t fPhiPQ;

  // two 3-momentum vectors are defined
  // one for the hadron
  // one for the virtual photon
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 virt(-tPex, -tPey, kEbeam - tPez);
  
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

Float_t ThetaPQ(Float_t fPx, Float_t fPy, Float_t fPz) {
  // (global variables: tPex, tPey, tPez)

  // angle between virtual photon and particle
  // (and this makes perfect sense if one draws it)
  
  Float_t fThetaPQ;
  
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 virt(-tPex, -tPey, kEbeam - tPez);

  fThetaPQ = virt.Angle(hadr)*TMath::RadToDeg();

  return fThetaPQ;
}

Float_t DeltaTheta(Float_t fPx, Float_t fPy, Float_t fPz) {
  // (global variables: tPex, tPey, tPez)

  // angle between electron and particle
  
  Float_t deltaTheta;

  TVector3 part(fPx, fPy, fPz);
  TVector3 elec(tPex, tPey, tPez);
  
  deltaTheta = elec.Angle(part)*TMath::RadToDeg();;

  return deltaTheta;
}

Float_t BettaCalc(Float_t fP, Float_t fPid) {
  
  Float_t fM = ParticleMass(fPid);
  Float_t fBettaCalc = fP/TMath::Sqrt(fP*fP + fM*fM);

  return fBettaCalc;
}
