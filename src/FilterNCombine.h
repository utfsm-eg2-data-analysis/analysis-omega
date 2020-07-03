#include "analysisConfig.h"

/*** Constants ***/

extern Float_t kEbeam;

/*** Input variables ***/

// (83 variables for data/simrec)
// electron (40)
extern Float_t tQ2, tW, tNu, tXb, tYb, tvxe, tvye, tvze, tSectorEl, tTargType, tPex, tPey, tPez, tPe, tBettaEl, tEtote, tEine, tEoute, tvxec, tvyec, tvzec, tXECe, tYECe, tZECe;
extern Float_t tStatDCEl, tDCStatusEl, tStatECEl, tECStatusEl, tTimeECEl, tPathECEl, tChi2ECEl, tStatSCEl, tSCStatusEl, tTimeSCEl, tPathSCEl, tStatCCEl, tCCStatusEl, tNpheEl, tChi2CCEl, tStatusEl;
// particle (42)
extern Float_t tZh, tThetaPQ, tPt2, tPl2, tPhiPQ, tMx2, tT, tvxh, tvyh, tvzh, tSector, tPx, tPy, tPz, tP, tBetta, tMass2, tEtot, tEin, tEout, tXEC, tYEC, tZEC, tpid, tT4, tdeltaZ;
extern Float_t tStatDC, tDCStatus, tStatEC, tECStatus, tTimeEC, tPathEC, tChi2EC, tStatSC, tSCStatus, tTimeSC, tPathSC, tStatCC, tCCStatus, tNphe, tChi2CC, tStatus;
// event (1)
extern Float_t tevnt;
// (34 variables for gsim)
// electron (15)
extern Float_t mc_tQ2, mc_tW, mc_tNu, mc_tXb, mc_tYb, mc_tvxe, mc_tvye, mc_tvze, mc_tSectorEl, mc_tTargType, mc_tPex, mc_tPey, mc_tPez, mc_tPe, mc_tBettaEl;
// particle (19)
extern Float_t mc_tZh, mc_tThetaPQ, mc_tPt2, mc_tPl2, mc_tPhiPQ, mc_tMx2, mc_tT, mc_tvxh, mc_tvyh, mc_tvzh, mc_tSector, mc_tPx, mc_tPy, mc_tPz, mc_tP, mc_tBetta, mc_tMass2, mc_tpid, mc_tdeltaZ;

/*** Output/original variables ***/

// (101 variables for data/simrec)
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
// (41 variables for gsim)
// electron (16)
extern Float_t mc_oQ2, mc_oW, mc_oNu, mc_oXb, mc_oYb, mc_oXe, mc_oYe, mc_oZe, mc_oSectorEl, mc_oTargType, mc_oPex, mc_oPey, mc_oPez, mc_oPe, mc_oBettaEl;
extern Float_t mc_oP2e;
// particle (25)
extern Float_t mc_ovxh, mc_ovyh, mc_ovzh, mc_oSector, mc_oBetta, mc_oMass2, mc_oPid, mc_odeltaZ, mc_oM;
extern Float_t mc_oE, mc_oPx, mc_oPy, mc_oPz, mc_oP2, mc_oP;
extern Float_t mc_oZ, mc_oThetaPQ, mc_oPt2, mc_oPl2, mc_oPhiPQ, mc_oMx2, mc_oT, mc_oCosThetaPQ, mc_oBettaCalc, mc_odeltaTheta;

/*** Output/mix variables ***/

// (194 variables for data/simrec)
// electron (41)
extern Float_t mQ2, mW, mNu, mXb, mYb, mXe, mYe, mZe, mSectorEl, mTargType, mPex, mPey, mPez, mPe, mBettaEl, mEtote, mEine, mEoute, mXec, mYec, mZec, mXECe, mYECe, mZECe;
extern Float_t mP2e;
extern Float_t mStatDCEl, mDCStatusEl, mStatECEl, mECStatusEl, mTimeECEl, mPathECEl, mChi2ECEl, mStatSCEl, mSCStatusEl, mTimeSCEl, mPathSCEl, mStatCCEl, mCCStatusEl, mNpheEl, mChi2CCEl, mStatusEl;
// particles (60) (16 + 3*6 + 10 + 16)
extern Float_t mvxh[4], mvyh[4], mvzh[4], mSector[4], mBetta[4], mMass2[4], mEtot[4], mEin[4], mEout[4], mXEC[4], mYEC[4], mZEC[4], mPid[4], mT4[4], mdeltaZ[4], mM[4];
extern Float_t mE_prev[4], mPx_prev[4], mPy_prev[4], mPz_prev[4], mP2_prev[4], mP_prev[4];
extern Float_t mE_true[4], mPx_true[4], mPy_true[4], mPz_true[4], mP2_true[4], mP_true[4];
extern Float_t mE_corr[4], mPx_corr[4], mPy_corr[4], mPz_corr[4], mP2_corr[4], mP_corr[4];
extern Float_t mZ[4], mThetaPQ[4], mPt2[4], mPl2[4], mPhiPQ[4], mMx2[4], mT[4], mCosThetaPQ[4], mBettaCalc[4], mdeltaTheta[4];
extern Float_t mStatDC[4], mDCStatus[4], mStatEC[4], mECStatus[4], mTimeEC[4], mPathEC[4], mChi2EC[4], mStatSC[4];
extern Float_t mSCStatus[4], mTimeSC[4], mPathSC[4], mStatCC[4], mCCStatus[4], mNphe[4], mChi2CC[4], mStatus[4];
// pi0 (24) (3*8new)
extern Float_t pi0Px_prev, pi0Py_prev, pi0Pz_prev, pi0P2_prev, pi0P_prev, pi0E_prev, pi0M_prev, pi0Theta_prev;
extern Float_t pi0Px_true, pi0Py_true, pi0Pz_true, pi0P2_true, pi0P_true, pi0E_true, pi0M_true, pi0Theta_true;
extern Float_t pi0Px_corr, pi0Py_corr, pi0Pz_corr, pi0P2_corr, pi0P_corr, pi0E_corr, pi0M_corr, pi0Theta_corr;
// omega (57) (3*19new)
extern Float_t wPx_prev, wPy_prev, wPz_prev, wP_prev, wP2_prev, wE_prev;
extern Float_t wZ_prev, wCosThetaPQ_prev, wThetaPQ_prev, wPt2_prev, wPl2_prev, wPhiPQ_prev, wMx2_prev, wT_prev, wBettaCalc_prev, wdeltaTheta_prev, wD_prev, wM_prev, wSD_prev;
extern Float_t wPx_true, wPy_true, wPz_true, wP_true, wP2_true, wE_true;
extern Float_t wZ_true, wCosThetaPQ_true, wThetaPQ_true, wPt2_true, wPl2_true, wPhiPQ_true, wMx2_true, wT_true, wBettaCalc_true, wdeltaTheta_true, wD_true, wM_true, wSD_true;
extern Float_t wPx_corr, wPy_corr, wPz_corr, wP_corr, wP2_corr, wE_corr;
extern Float_t wZ_corr, wCosThetaPQ_corr, wThetaPQ_corr, wPt2_corr, wPl2_corr, wPhiPQ_corr, wMx2_corr, wT_corr, wBettaCalc_corr, wdeltaTheta_corr, wD_corr, wM_corr, wSD_corr;
// crossed terms (9)
extern Float_t pippimP, pippimE, pippimM;
extern Float_t pippi0P, pippi0E, pippi0M;
extern Float_t pimpi0P, pimpi0E, pimpi0M;
// number of particles (3)
extern Float_t nPip, nPim, nGamma;
// event related (2)
extern Float_t mEvent;
extern Float_t mEntry[4];
// (72 variables for gsim)
// electron (16)
extern Float_t mc_mQ2, mc_mW, mc_mNu, mc_mXb, mc_mYb, mc_mXe, mc_mYe, mc_mZe, mc_mSectorEl, mc_mTargType, mc_mPex, mc_mPey, mc_mPez, mc_mPe, mc_mBettaEl;
extern Float_t mc_mP2e;
// particle (25)
extern Float_t mc_mvxh[4], mc_mvyh[4], mc_mvzh[4], mc_mSector[4], mc_mBetta[4], mc_mMass2[4], mc_mPid[4], mc_mdeltaZ[4], mc_mM[4];
extern Float_t mc_mE[4], mc_mPx[4], mc_mPy[4], mc_mPz[4], mc_mP2[4], mc_mP[4];
extern Float_t mc_mZ[4], mc_mThetaPQ[4], mc_mPt2[4], mc_mPl2[4], mc_mPhiPQ[4], mc_mMx2[4], mc_mT[4], mc_mCosThetaPQ[4], mc_mBettaCalc[4], mc_mdeltaTheta[4];
// pi0 (8)
extern Float_t mc_pi0Px, mc_pi0Py, mc_pi0Pz, mc_pi0P2, mc_pi0P, mc_pi0E, mc_pi0M, mc_pi0Theta;
// omega (19)
extern Float_t mc_wPx, mc_wPy, mc_wPz, mc_wP, mc_wP2, mc_wE;
extern Float_t mc_wZ, mc_wCosThetaPQ, mc_wThetaPQ, mc_wPt2, mc_wPl2, mc_wPhiPQ, mc_wMx2, mc_wT, mc_wBettaCalc, mc_wdeltaTheta, mc_wD, mc_wM, mc_wSD;
// crossed terms (9)
extern Float_t mc_pippimP, mc_pippimE, mc_pippimM;
extern Float_t mc_pippi0P, mc_pippi0E, mc_pippi0M;
extern Float_t mc_pimpi0P, mc_pimpi0E, mc_pimpi0M;
// number of particles (3)
extern Float_t mc_nPip, mc_nPim, mc_nGamma;

/*** Options ***/

extern Int_t simFlag;
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
  // (uses simFlag as global var)
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
  // (34 variables for gsim)
  if (simFlag) {
    // electron (15)
    chain->SetBranchAddress("mc_Q2", &mc_tQ2);
    chain->SetBranchAddress("mc_W", &mc_tW);
    chain->SetBranchAddress("mc_Nu", &mc_tNu);
    chain->SetBranchAddress("mc_Xb", &mc_tXb);
    chain->SetBranchAddress("mc_Yb", &mc_tYb);
    chain->SetBranchAddress("mc_vxe", &mc_tvxe);
    chain->SetBranchAddress("mc_vye", &mc_tvye);
    chain->SetBranchAddress("mc_vze", &mc_tvze);
    chain->SetBranchAddress("mc_SectorEl", &mc_tSectorEl);
    chain->SetBranchAddress("mc_TargType", &mc_tTargType);
    chain->SetBranchAddress("mc_Pex", &mc_tPex);
    chain->SetBranchAddress("mc_Pey", &mc_tPey);
    chain->SetBranchAddress("mc_Pez", &mc_tPez);
    chain->SetBranchAddress("mc_Pe", &mc_tPe);
    chain->SetBranchAddress("mc_BettaEl", &mc_tBettaEl);
    // particle (19)
    chain->SetBranchAddress("mc_Zh", &mc_tZh);
    chain->SetBranchAddress("mc_ThetaPQ", &mc_tThetaPQ);
    chain->SetBranchAddress("mc_Pt2", &mc_tPt2);
    chain->SetBranchAddress("mc_Pl2", &mc_tPl2);
    chain->SetBranchAddress("mc_PhiPQ", &mc_tPhiPQ);
    chain->SetBranchAddress("mc_Mx2", &mc_tMx2);
    chain->SetBranchAddress("mc_T", &mc_tT);
    chain->SetBranchAddress("mc_vxh", &mc_tvxh);
    chain->SetBranchAddress("mc_vyh", &mc_tvyh);
    chain->SetBranchAddress("mc_vzh", &mc_tvzh);
    chain->SetBranchAddress("mc_Sector", &mc_tSector);
    chain->SetBranchAddress("mc_Px", &mc_tPx);
    chain->SetBranchAddress("mc_Py", &mc_tPy);
    chain->SetBranchAddress("mc_Pz", &mc_tPz);
    chain->SetBranchAddress("mc_P", &mc_tP);
    chain->SetBranchAddress("mc_Betta", &mc_tBetta);
    chain->SetBranchAddress("mc_Mass2", &mc_tMass2);
    chain->SetBranchAddress("mc_pid", &mc_tpid);
    chain->SetBranchAddress("mc_deltaZ", &mc_tdeltaZ);
    std::cout << "  !! SIB simflag ready!" << std::endl;
  }
}

void SetOutputBranches(TTree *tree, TString option) {
  // (uses simFlag as global var)
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
    // (41 variables for gsim)
    if (simFlag) {
      // electron (16)
      tree->Branch("mc_Q2", &mc_oQ2);
      tree->Branch("mc_W", &mc_oW);
      tree->Branch("mc_Nu", &mc_oNu);
      tree->Branch("mc_Xb", &mc_oXb);
      tree->Branch("mc_Yb", &mc_oYb);
      tree->Branch("mc_Xe", &mc_oXe);
      tree->Branch("mc_Ye", &mc_oYe);
      tree->Branch("mc_Ze", &mc_oZe);
      tree->Branch("mc_SectorEl", &mc_oSectorEl);
      tree->Branch("mc_TargType", &mc_oTargType);
      tree->Branch("mc_Pex", &mc_oPex);
      tree->Branch("mc_Pey", &mc_oPey);
      tree->Branch("mc_Pez", &mc_oPez);
      tree->Branch("mc_Pe", &mc_oPe);
      tree->Branch("mc_BettaEl", &mc_oBettaEl);
      tree->Branch("mc_P2e", &mc_oP2e);
      // particle (25)
      tree->Branch("mc_vxh", &mc_ovxh);
      tree->Branch("mc_vyh", &mc_ovyh);
      tree->Branch("mc_vzh", &mc_ovzh);
      tree->Branch("mc_Sector", &mc_oSector);
      tree->Branch("mc_Betta", &mc_oBetta);
      tree->Branch("mc_Mass2", &mc_oMass2);
      tree->Branch("mc_Pid", &mc_oPid);
      tree->Branch("mc_deltaZ", &mc_odeltaZ);
      tree->Branch("mc_M", &mc_oM);
      tree->Branch("mc_E", &mc_oE);
      tree->Branch("mc_Px", &mc_oPx);
      tree->Branch("mc_Py", &mc_oPy);
      tree->Branch("mc_Pz", &mc_oPz);
      tree->Branch("mc_P2", &mc_oP2);
      tree->Branch("mc_P", &mc_oP);
      tree->Branch("mc_Z", &mc_oZ);
      tree->Branch("mc_ThetaPQ", &mc_oThetaPQ);
      tree->Branch("mc_Pt2", &mc_oPt2);
      tree->Branch("mc_Pl2", &mc_oPl2);
      tree->Branch("mc_PhiPQ", &mc_oPhiPQ);
      tree->Branch("mc_Mx2", &mc_oMx2);
      tree->Branch("mc_T", &mc_oT);
      tree->Branch("mc_CosThetaPQ", &mc_oCosThetaPQ);
      tree->Branch("mc_BettaCalc", &mc_oBettaCalc);
      tree->Branch("mc_deltaTheta", &mc_odeltaTheta);
      std::cout << "  !! SOB orig simflag ready!" << std::endl;
    }
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
    tree->Branch("vxh", &mvxh, "vxh[4]/F");
    tree->Branch("vyh", &mvyh, "vyh[4]/F");
    tree->Branch("vzh", &mvzh, "vzh[4]/F");
    tree->Branch("Sector", &mSector, "Sector[4]/F");
    tree->Branch("Betta", &mBetta, "Betta[4]/F");
    tree->Branch("Mass2", &mMass2, "Mass2[4]/F");
    tree->Branch("Etot", &mEtot, "Etot[4]/F");
    tree->Branch("Ein", &mEin, "Ein[4]/F");
    tree->Branch("Eout", &mEout, "Eout[4]/F");
    tree->Branch("XEC", &mXEC, "XEC[4]/F");
    tree->Branch("YEC", &mYEC, "YEC[4]/F");
    tree->Branch("ZEC", &mZEC, "ZEC[4]/F");
    tree->Branch("Pid", &mPid, "Pid[4]/F");
    tree->Branch("M", &mM, "M[4]/F");
    tree->Branch("T4", &mT4, "T4[4]/F");
    tree->Branch("deltaZ", &mdeltaZ, "deltaZ[4]/F");
    // prev (6)
    tree->Branch("Px_prev", &mPx_prev, "Px_prev[4]/F");
    tree->Branch("Py_prev", &mPy_prev, "Py_prev[4]/F");
    tree->Branch("Pz_prev", &mPz_prev, "Pz_prev[4]/F");
    tree->Branch("P2_prev", &mP2_prev, "P2_prev[4]/F");
    tree->Branch("P_prev", &mP_prev, "P_prev[4]/F");
    tree->Branch("E_prev", &mE_prev, "E_prev[4]/F");
    // true (6)
    tree->Branch("Px_true", &mPx_true, "Px_true[4]/F");
    tree->Branch("Py_true", &mPy_true, "Py_true[4]/F");
    tree->Branch("Pz_true", &mPz_true, "Pz_true[4]/F");
    tree->Branch("P2_true", &mP2_true, "P2_true[4]/F");
    tree->Branch("P_true", &mP_true, "P_true[4]/F");
    tree->Branch("E_true", &mE_true, "E_true[4]/F");
    // corr (6)
    tree->Branch("Px_corr", &mPx_corr, "Px_corr[4]/F");
    tree->Branch("Py_corr", &mPy_corr, "Py_corr[4]/F");
    tree->Branch("Pz_corr", &mPz_corr, "Pz_corr[4]/F");
    tree->Branch("P2_corr", &mP2_corr, "P2_corr[4]/F");
    tree->Branch("P_corr", &mP_corr, "P_corr[4]/F");
    tree->Branch("E_corr", &mE_corr, "E_corr[4]/F");
    // remaining (10)
    tree->Branch("Z", &mZ, "Z[4]/F");
    tree->Branch("PhiPQ", &mPhiPQ, "PhiPQ[4]/F");
    tree->Branch("ThetaPQ", &mThetaPQ, "ThetaPQ[4]/F");
    tree->Branch("CosThetaPQ", &mCosThetaPQ, "CosThetaPQ[4]/F");
    tree->Branch("Pt2", &mPt2, "Pt2[4]/F");
    tree->Branch("Pl2", &mPl2, "Pl2[4]/F");
    tree->Branch("Mx2", &mMx2, "Mx2[4]/F");
    tree->Branch("T", &mT, "T[4]/F");
    tree->Branch("deltaTheta", &mdeltaTheta, "deltaTheta[4]/F");
    tree->Branch("BettaCalc", &mBettaCalc, "BettaCalc[4]/F");
    // status (16)
    tree->Branch("StatDC", &mStatDC, "StatDC[4]/F");
    tree->Branch("DCStatus", &mDCStatus, "DCStatus[4]/F");
    tree->Branch("StatEC", &mStatEC, "StatEC[4]/F");
    tree->Branch("ECStatus", &mECStatus, "ECStatus[4]/F");
    tree->Branch("TimeEC", &mTimeEC, "TimeEC[4]/F");
    tree->Branch("PathEC", &mPathEC, "PathEC[4]/F");
    tree->Branch("Chi2EC", &mChi2EC, "Chi2EC[4]/F");
    tree->Branch("StatSC", &mStatSC, "StatSC[4]/F");
    tree->Branch("SCStatus", &mSCStatus, "SCStatus[4]/F");
    tree->Branch("TimeSC", &mTimeSC, "TimeSC[4]/F");
    tree->Branch("PathSC", &mPathSC, "PathSC[4]/F");
    tree->Branch("StatCC", &mStatCC, "StatCC[4]/F");
    tree->Branch("CCStatus", &mCCStatus, "CCStatus[4]/F");
    tree->Branch("Nphe", &mNphe, "Nphe[4]/F");
    tree->Branch("Chi2CC", &mChi2CC, "Chi2CC[4]/F");
    tree->Branch("Status", &mStatus, "Status[4]/F");
    // pi0 prev (8)
    tree->Branch("pi0Px_prev", &pi0Px_prev);
    tree->Branch("pi0Py_prev", &pi0Py_prev);
    tree->Branch("pi0Pz_prev", &pi0Pz_prev);
    tree->Branch("pi0P2_prev", &pi0P2_prev);
    tree->Branch("pi0P_prev", &pi0P_prev);
    tree->Branch("pi0E_prev", &pi0E_prev);
    tree->Branch("pi0M_prev", &pi0M_prev);
    tree->Branch("pi0Theta_prev", &pi0Theta_prev);
    // pi0 true (8)
    tree->Branch("pi0Px_true", &pi0Px_true);
    tree->Branch("pi0Py_true", &pi0Py_true);
    tree->Branch("pi0Pz_true", &pi0Pz_true);
    tree->Branch("pi0P2_true", &pi0P2_true);
    tree->Branch("pi0P_true", &pi0P_true);
    tree->Branch("pi0E_true", &pi0E_true);
    tree->Branch("pi0M_true", &pi0M_true);
    tree->Branch("pi0Theta_true", &pi0Theta_true);
    // pi0 corr (8)
    tree->Branch("pi0Px_corr", &pi0Px_corr);
    tree->Branch("pi0Py_corr", &pi0Py_corr);
    tree->Branch("pi0Pz_corr", &pi0Pz_corr);
    tree->Branch("pi0P2_corr", &pi0P2_corr);
    tree->Branch("pi0P_corr", &pi0P_corr);
    tree->Branch("pi0E_corr", &pi0E_corr);
    tree->Branch("pi0M_corr", &pi0M_corr);
    tree->Branch("pi0Theta_corr", &pi0Theta_corr);
    // omega prev (19)
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
    tree->Branch("wD_prev", &wD_prev);
    tree->Branch("wM_prev", &wM_prev);
    tree->Branch("wSD_prev", &wSD_prev);
    // omega true (19)
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
    tree->Branch("wD_true", &wD_true);
    tree->Branch("wM_true", &wM_true);
    tree->Branch("wSD_true", &wSD_true);
    // omega corr (19)
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
    tree->Branch("wD_corr", &wD_corr);
    tree->Branch("wM_corr", &wM_corr);
    tree->Branch("wSD_corr", &wSD_corr);
    // crossed terms (9)
    tree->Branch("pippimP", &pippimP);
    tree->Branch("pippimE", &pippimE);
    tree->Branch("pippimM", &pippimM);
    tree->Branch("pippi0P", &pippi0P);
    tree->Branch("pippi0E", &pippi0E);
    tree->Branch("pippi0M", &pippi0M);
    tree->Branch("pimpi0P", &pimpi0P);
    tree->Branch("pimpi0E", &pimpi0E);
    tree->Branch("pimpi0M", &pimpi0M);
    // number of particles in that event (3)
    tree->Branch("nPip", &nPip);
    tree->Branch("nPim", &nPim);
    tree->Branch("nGamma", &nGamma);
    // event related (2)
    tree->Branch("Entry", &mEntry, "Entry[4]/F");
    tree->Branch("Event", &mEvent);
    // (72 variables for gsim)
    if (simFlag) {
      // electron (16)
      tree->Branch("mc_Q2", &mc_mQ2);
      tree->Branch("mc_W", &mc_mW);
      tree->Branch("mc_Nu", &mc_mNu);
      tree->Branch("mc_Xb", &mc_mXb);
      tree->Branch("mc_Yb", &mc_mYb);
      tree->Branch("mc_Xe", &mc_mXe);
      tree->Branch("mc_Ye", &mc_mYe);
      tree->Branch("mc_Ze", &mc_mZe);
      tree->Branch("mc_SectorEl", &mc_mSectorEl);
      tree->Branch("mc_TargType", &mc_mTargType);
      tree->Branch("mc_Pex", &mc_mPex);
      tree->Branch("mc_Pey", &mc_mPey);
      tree->Branch("mc_Pez", &mc_mPez);
      tree->Branch("mc_Pe", &mc_mPe);
      tree->Branch("mc_BettaEl", &mc_mBettaEl);
      tree->Branch("mc_P2e", &mc_mP2e);
      // particle (25)
      tree->Branch("mc_vxh", &mc_mvxh, "mc_vxh[4]/F");
      tree->Branch("mc_vyh", &mc_mvyh, "mc_vyh[4]/F");
      tree->Branch("mc_vzh", &mc_mvzh, "mc_vzh[4]/F");
      tree->Branch("mc_Sector", &mc_mSector, "mc_Sector[4]/F");
      tree->Branch("mc_Betta", &mc_mBetta, "mc_Betta[4]/F");
      tree->Branch("mc_Mass2", &mc_mMass2, "mc_Mass2[4]/F");
      tree->Branch("mc_Pid", &mc_mPid, "mc_Pid[4]/F");
      tree->Branch("mc_deltaZ", &mc_mdeltaZ, "mc_deltaZ[4]/F");
      tree->Branch("mc_M", &mc_mM, "mc_M[4]/F");
      tree->Branch("mc_E", &mc_mE, "mc_E[4]/F");
      tree->Branch("mc_Px", &mc_mPx, "mc_Px[4]/F");
      tree->Branch("mc_Py", &mc_mPy, "mc_Py[4]/F");
      tree->Branch("mc_Pz", &mc_mPz, "mc_Pz[4]/F");
      tree->Branch("mc_P2", &mc_mP2, "mc_P2[4]/F");
      tree->Branch("mc_P", &mc_mP, "mc_P[4]/F");
      tree->Branch("mc_Z", &mc_mZ, "mc_Z[4]/F");
      tree->Branch("mc_ThetaPQ", &mc_mThetaPQ, "mc_ThetaPQ[4]/F");
      tree->Branch("mc_Pt2", &mc_mPt2, "mc_Pt2[4]/F");
      tree->Branch("mc_Pl2", &mc_mPl2, "mc_Pl2[4]/F");
      tree->Branch("mc_PhiPQ", &mc_mPhiPQ, "mc_PhiPQ[4]/F");
      tree->Branch("mc_Mx2", &mc_mMx2, "mc_Mx2[4]/F");
      tree->Branch("mc_T", &mc_mT, "mc_T[4]/F");
      tree->Branch("mc_CosThetaPQ", &mc_mCosThetaPQ, "mc_CosThetaPQ[4]/F");
      tree->Branch("mc_BettaCalc", &mc_mBettaCalc, "mc_BettaCalc[4]/F");
      tree->Branch("mc_deltaTheta", &mc_mdeltaTheta, "mc_deltaTheta[4]/F");
      // pi0 (8)
      tree->Branch("mc_pi0Px", &mc_pi0Px);
      tree->Branch("mc_pi0Py", &mc_pi0Py);
      tree->Branch("mc_pi0Pz", &mc_pi0Pz);
      tree->Branch("mc_pi0P2", &mc_pi0P2);
      tree->Branch("mc_pi0P", &mc_pi0P);
      tree->Branch("mc_pi0E", &mc_pi0E);
      tree->Branch("mc_pi0M", &mc_pi0M);
      tree->Branch("mc_pi0Theta", &mc_pi0Theta);
      // omega (19)
      tree->Branch("mc_wPx", &mc_wPx);
      tree->Branch("mc_wPy", &mc_wPy);
      tree->Branch("mc_wPz", &mc_wPz);
      tree->Branch("mc_wP", &mc_wP);
      tree->Branch("mc_wP2", &mc_wP2);
      tree->Branch("mc_wE", &mc_wE);
      tree->Branch("mc_wZ", &mc_wZ);
      tree->Branch("mc_wCosThetaPQ", &mc_wCosThetaPQ);
      tree->Branch("mc_wThetaPQ", &mc_wThetaPQ);
      tree->Branch("mc_wPt2", &mc_wPt2);
      tree->Branch("mc_wPl2", &mc_wPl2);
      tree->Branch("mc_wPhiPQ", &mc_wPhiPQ);
      tree->Branch("mc_wMx2", &mc_wMx2);
      tree->Branch("mc_wT", &mc_wT);
      tree->Branch("mc_wBettaCalc", &mc_wBettaCalc);
      tree->Branch("mc_wdeltaTheta", &mc_wdeltaTheta);
      tree->Branch("mc_wD", &mc_wD);
      tree->Branch("mc_wM", &mc_wM);
      tree->Branch("mc_wSD", &mc_wSD);
      // crossed terms (9)
      tree->Branch("mc_pippimP", &mc_pippimP);
      tree->Branch("mc_pippimE", &mc_pippimE);
      tree->Branch("mc_pippimM", &mc_pippimM);
      tree->Branch("mc_pippi0P", &mc_pippi0P);
      tree->Branch("mc_pippi0E", &mc_pippi0E);
      tree->Branch("mc_pippi0M", &mc_pippi0M);
      tree->Branch("mc_pimpi0P", &mc_pimpi0P);
      tree->Branch("mc_pimpi0E", &mc_pimpi0E);
      tree->Branch("mc_pimpi0M", &mc_pimpi0M);
      // number of particles (3)
      tree->Branch("mc_nPip", &mc_nPip);
      tree->Branch("mc_nPim", &mc_nPim);
      tree->Branch("mc_nGamma", &mc_nGamma);
    }
  }
}

void AssignOriginalVariables(Int_t entry, Int_t nCombInSimrec) {
  // (uses simFlag as global var)
  std::cout << "  !! AOV initiating..." << std::endl;
  if (nCombInSimrec) {
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
    oP2e = tPe*tPe;
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
    oPid = tpid;
    oM = ParticleMass(tpid);
    // prev (6)
    oE_prev  = CorrectEnergy("prev");
    oPx_prev = tPx;
    oPy_prev = tPy;
    oPz_prev = tPz;
    oP_prev  = tP;
    oP2_prev = tP*tP;
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
    // remaining (10)
    oZ = oE_corr/oNu;
    oPhiPQ = PhiPQ(oPx_corr, oPy_corr, oPz_corr);
    oThetaPQ = ThetaPQ(oPx_corr, oPy_corr, oPz_corr);
    oCosThetaPQ = ((kEbeam - oPez)*oPz_corr - oPex*oPx_corr - oPey*oPy_corr)/(TMath::Sqrt(oP2_corr*(oQ2 + oNu*oNu)));
    oPt2 = oP2_corr*(1 - oCosThetaPQ*oCosThetaPQ);
    oPl2 = oP2_corr*oCosThetaPQ*oCosThetaPQ;
    oMx2 = tW*tW + oM*oM - 2*oZ*oNu*oNu + 2*TMath::Sqrt(oPl2*(oNu*oNu + oQ2)) - 2*kMproton*oZ*oNu;
    oT = oM*oM - 2*oZ*oNu*oNu + 2*TMath::Sqrt(oPl2*(oNu*oNu + oQ2)) - oQ2;
    oBettaCalc = BettaCalc(oP_corr, oPid);
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
  } else {
    // electron (41)
    oQ2 = -9999;
    oW  = -9999;
    oNu = -9999;
    oXb = -9999;
    oYb = -9999;
    oXe = -9999;
    oYe = -9999;
    oZe = -9999;
    oSectorEl = -9999;
    oTargType = -9999;
    oPex = -9999;
    oPey = -9999;
    oPez = -9999;
    oPe  = -9999;
    oP2e = -9999;
    oBettaEl = -9999;
    oEtote = -9999;
    oEine  = -9999;
    oEoute = -9999;
    oXec = -9999;
    oYec = -9999;
    oZec = -9999;
    oXECe = -9999;
    oYECe = -9999;
    oZECe = -9999;
    oStatDCEl   = -9999;
    oDCStatusEl = -9999;
    oStatECEl   = -9999;
    oECStatusEl = -9999;
    oTimeECEl   = -9999;
    oPathECEl   = -9999;
    oChi2ECEl   = -9999;
    oStatSCEl   = -9999;
    oSCStatusEl = -9999;
    oTimeSCEl   = -9999;
    oPathSCEl   = -9999;
    oStatCCEl   = -9999;
    oCCStatusEl = -9999;
    oNpheEl     = -9999;
    oChi2CCEl   = -9999;
    oStatusEl   = -9999;
    // independent variables (16)
    ovxh = -9999;
    ovyh = -9999;
    ovzh = -9999;
    oSector = -9999;
    oEtot = -9999;
    oEin  = -9999;
    oEout = -9999;
    oXEC = -9999;
    oYEC = -9999;
    oZEC = -9999;
    odeltaZ = -9999;
    oBetta = -9999;
    oMass2 = -9999;
    oT4 = -9999;
    oPid = -9999;
    oM = -9999;
    // prev (6)
    oE_prev  = -9999;
    oPx_prev = -9999;
    oPy_prev = -9999;
    oPz_prev = -9999;
    oP_prev  = -9999;
    oP2_prev = -9999;
    // true (6)
    oE_true  = -9999;
    oPx_true = -9999;
    oPy_true = -9999;
    oPz_true = -9999;
    oP2_true = -9999;
    oP_true  = -9999;
    // corr (6)
    oE_corr  = -9999;
    oPx_corr = -9999;
    oPy_corr = -9999;
    oPz_corr = -9999;
    oP2_corr = -9999;
    oP_corr  = -9999;
    // remaining (10)
    oZ = -9999;
    oPhiPQ = -9999;
    oThetaPQ = -9999;
    oCosThetaPQ = -9999;
    oPt2 = -9999;
    oPl2 = -9999;
    oMx2 = -9999;
    oT = -9999;
    oBettaCalc = -9999;
    odeltaTheta = -9999;
    // status (16)
    oStatDC   = -9999;
    oDCStatus = -9999;
    oStatEC   = -9999;
    oECStatus = -9999;
    oTimeEC   = -9999;
    oPathEC   = -9999;
    oChi2EC   = -9999;
    oStatSC   = -9999;
    oSCStatus = -9999;
    oTimeSC   = -9999;
    oPathSC   = -9999;
    oStatCC   = -9999;
    oCCStatus = -9999;
    oNphe     = -9999;
    oChi2CC   = -9999;
    oStatus   = -9999;
  }
  // event-related (2)
  oEvent = tevnt;
  oEntry = (Float_t) entry;
  // gsim vars
  if (simFlag) {
    // electron (16)
    mc_oQ2 = mc_tQ2;
    mc_oW = mc_tW;
    mc_oNu = mc_tNu;
    mc_oXb = mc_tXb;
    mc_oYb = mc_tYb;
    mc_oXe = mc_tvxe;
    mc_oYe = mc_tvye;
    mc_oZe = mc_tvze;
    mc_oSectorEl = mc_tSectorEl;
    mc_oTargType = mc_tTargType;
    mc_oPex = mc_tPex;
    mc_oPey = mc_tPey;
    mc_oPez = mc_tPez;
    mc_oPe = mc_tPe;
    mc_oBettaEl = mc_tBettaEl;
    mc_oP2e = mc_oPe*mc_oPe; // recalc
    // particle (25)
    mc_ovxh = mc_tvxh;
    mc_ovyh = mc_tvyh;
    mc_ovzh = mc_tvzh;
    mc_oSector = mc_tSector;
    mc_oBetta = mc_tBetta;
    mc_oMass2 = mc_tMass2;
    mc_oPid = mc_tpid;
    mc_odeltaZ = mc_tdeltaZ;
    mc_oPx = mc_tPx;
    mc_oPy = mc_tPy;
    mc_oPz = mc_tPz;
    mc_oP = mc_tP;
    mc_oZ = mc_tZh;
    mc_oThetaPQ = mc_tThetaPQ;
    mc_oPt2 = mc_tPt2;
    mc_oPl2 = mc_tPl2;
    mc_oPhiPQ = mc_tPhiPQ;
    mc_oMx2 = mc_tMx2;
    mc_oT = mc_tT;
    mc_oP2 = mc_oP*mc_oP; // recalc
    mc_oM  = ParticleMass(mc_oPid); // recalc
    mc_oE  = TMath::Sqrt(mc_oP2 + mc_oM*mc_oM); // recalc
    mc_oCosThetaPQ = ((kEbeam - mc_oPez)*mc_oPz - mc_oPex*mc_oPx - mc_oPey*mc_oPy)/(TMath::Sqrt(mc_oP2*(mc_oQ2 + mc_oNu*mc_oNu))); // recalc
    mc_oBettaCalc  = BettaCalc(mc_oP, mc_oPid); // recalc
    mc_odeltaTheta = DeltaTheta(mc_oPx, mc_oPy, mc_oPz); // recalc
    std::cout << "  !! AOV simflag ready" << std::endl;
  }
}

void NullMixSIMRECVariables(Int_t index) {
  std::cout << "  !! NMSV initiating..." << std::endl;
  // electron (41)
  mQ2 = -9999;
  mW  = -9999;
  mNu = -9999;
  mXb = -9999;
  mYb = -9999;
  mXe = -9999;
  mYe = -9999;
  mZe = -9999;
  mSectorEl = -9999;
  mTargType = -9999;
  mPex = -9999;
  mPey = -9999;
  mPez = -9999;
  mPe = -9999;
  mP2e = -9999;
  mBettaEl = -9999;
  mEtote = -9999;
  mEine  = -9999;
  mEoute = -9999;
  mXec = -9999;
  mYec = -9999;
  mZec = -9999;
  mXECe = -9999;
  mYECe = -9999;
  mZECe = -9999;
  mStatDCEl   = -9999;
  mDCStatusEl = -9999;
  mStatECEl   = -9999;
  mECStatusEl = -9999;
  mTimeECEl   = -9999;
  mPathECEl   = -9999;
  mChi2ECEl   = -9999;
  mStatSCEl   = -9999;
  mSCStatusEl = -9999;
  mTimeSCEl   = -9999;
  mPathSCEl   = -9999;
  mStatCCEl   = -9999;
  mCCStatusEl = -9999;
  mNpheEl     = -9999;
  mChi2CCEl   = -9999;
  mStatusEl   = -9999;
  // independent variables (16)
  mvxh[index] = -9999;
  mvyh[index] = -9999;
  mvzh[index] = -9999;
  mSector[index] = -9999;
  mXEC[index] = -9999;
  mYEC[index] = -9999;
  mZEC[index] = -9999;
  mEtot[index] = -9999;
  mEin[index]  = -9999;
  mEout[index] = -9999;
  mdeltaZ[index] = -9999;
  mT4[index] = -9999;
  mMass2[index] = -9999;
  mBetta[index] = -9999;
  mPid[index] = -9999;
  mM[index] = -9999;
  // prev (6)
  mE_prev[index]  = -9999;
  mPx_prev[index] = -9999;
  mPy_prev[index] = -9999;
  mPz_prev[index] = -9999;
  mP_prev[index]  = -9999;
  mP2_prev[index] = -9999;
  // true (6)
  mE_true[index]  = -9999;
  mPx_true[index] = -9999;
  mPy_true[index] = -9999;
  mPz_true[index] = -9999;
  mP2_true[index] = -9999;
  mP_true[index]  = -9999;
  // corr (6)
  mE_corr[index]  = -9999;
  mPx_corr[index] = -9999;
  mPy_corr[index] = -9999;
  mPz_corr[index] = -9999;
  mP2_corr[index] = -9999;
  mP_corr[index]  = -9999;
  // remaining (10)
  mZ[index] = -9999;
  mPhiPQ[index]   = -9999;
  mThetaPQ[index] = -9999;
  mCosThetaPQ[index] = -9999;
  mPt2[index] = -9999;
  mPl2[index] = -9999;
  mdeltaTheta[index] = -9999;
  mMx2[index] = -9999;
  mT[index] = -9999;
  mBettaCalc[index] = -9999;
  // status (16)
  mStatDC[index]   = -9999;
  mDCStatus[index] = -9999;
  mStatEC[index]   = -9999;
  mECStatus[index] = -9999;
  mTimeEC[index]   = -9999;
  mPathEC[index]   = -9999;
  mChi2EC[index]   = -9999;
  mStatSC[index]   = -9999;
  mSCStatus[index] = -9999;
  mTimeSC[index]   = -9999;
  mPathSC[index]   = -9999;
  mStatCC[index]   = -9999;
  mCCStatus[index] = -9999;
  mNphe[index]     = -9999;
  mChi2CC[index]   = -9999;
  mStatus[index]   = -9999;
  // pi0 prev (8)
  pi0Px_prev = -9999;
  pi0Py_prev = -9999;
  pi0Pz_prev = -9999;
  pi0P2_prev = -9999;
  pi0P_prev  = -9999;
  pi0M_prev  = -9999;
  pi0E_prev  = -9999;
  pi0Theta_prev = -9999;
  // pi0 true (8)
  pi0Px_true = -9999;
  pi0Py_true = -9999;
  pi0Pz_true = -9999;
  pi0P2_true = -9999;
  pi0P_true  = -9999;
  pi0M_true  = -9999;
  pi0E_true  = -9999;
  pi0Theta_true = -9999;
  // pi0 corr (8)
  pi0Px_corr = -9999;
  pi0Py_corr = -9999;
  pi0Pz_corr = -9999;
  pi0P2_corr = -9999;
  pi0P_corr  = -9999;
  pi0M_corr  = -9999;
  pi0E_corr  = -9999;
  pi0Theta_corr = -9999;
  // omega prev (6+13)
  wPx_prev = -9999;
  wPy_prev = -9999;
  wPz_prev = -9999;
  wP2_prev = -9999;
  wP_prev  = -9999;
  wE_prev  = -9999;
  wM_prev  = -9999;
  wD_prev  = -9999;
  wSD_prev = -9999;
  wZ_prev  = -9999;
  wPhiPQ_prev = -9999;
  wThetaPQ_prev = -9999;
  wCosThetaPQ_prev = -9999;
  wPt2_prev = -9999;
  wPl2_prev = -9999;
  wMx2_prev = -9999;
  wT_prev = -9999;
  wBettaCalc_prev = -9999;
  wdeltaTheta_prev = -9999;
  // omega true (6+13)
  wPx_true = -9999;
  wPy_true = -9999;
  wPz_true = -9999;
  wP2_true = -9999;
  wP_true  = -9999;
  wE_true  = -9999;
  wM_true  = -9999;
  wD_true  = -9999;
  wSD_true = -9999;
  wZ_true  = -9999;
  wPhiPQ_true = -9999;
  wThetaPQ_true = -9999;
  wCosThetaPQ_true = -9999;
  wPt2_true = -9999;
  wPl2_true = -9999;
  wMx2_true = -9999;
  wT_true = -9999;
  wBettaCalc_true = -9999;
  wdeltaTheta_true = -9999;
  // omega corr (6+13)
  wPx_corr = -9999;
  wPy_corr = -9999;
  wPz_corr = -9999;
  wP2_corr = -9999;
  wP_corr  = -9999;
  wE_corr  = -9999;
  wM_corr  = -9999;
  wD_corr  = -9999;
  wSD_corr = -9999;
  wZ_corr  = -9999;
  wPhiPQ_corr = -9999;
  wThetaPQ_corr = -9999;
  wCosThetaPQ_corr = -9999;
  wPt2_corr = -9999;
  wPl2_corr = -9999;
  wMx2_corr = -9999;
  wT_corr = -9999;
  wBettaCalc_corr = -9999;
  wdeltaTheta_corr = -9999;
  // crossed terms (9)
  pippimP = -9999;
  pippimE = -9999;
  pippimM = -9999;
  pippi0P = -9999;
  pippi0E = -9999;
  pippi0M = -9999;
  pimpi0P = -9999;
  pimpi0E = -9999;
  pimpi0M = -9999;
  // number of particles (3) -> only keep real number when there is at least one omega!
  nGamma = -9999;
  nPip   = -9999;
  nPim   = -9999;
  std::cout << "  !! NMSV ready!" << std::endl;
}

void AssignMixVariables(Float_t entry, Int_t index) {
  std::cout << "  !! AMV initiating..." << std::endl;
  // requirement: particle is not null
  if (tpid != -9999) {
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
    mPe = tPe;
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
    mPid[index] = tpid;
    mM[index] = ParticleMass(tpid);
    // prev (6)
    mE_prev[index]  = CorrectEnergy("prev");
    mPx_prev[index] = tPx;
    mPy_prev[index] = tPy;
    mPz_prev[index] = tPz;
    mP_prev[index]  = tP;
    mP2_prev[index] = tP*tP;
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
    // remaining (10)
    mZ[index] = mE_corr[index]/mNu;
    mPhiPQ[index]   = PhiPQ(mPx_corr[index], mPy_corr[index], mPz_corr[index]);
    mThetaPQ[index] = ThetaPQ(mPx_corr[index], mPy_corr[index], mPz_corr[index]);
    mCosThetaPQ[index] = ((kEbeam - mPez)*mPz_corr[index] - mPex*mPx_corr[index] - mPey*mPy_corr[index])/(TMath::Sqrt(mP2_corr[index]*(mQ2 + mNu*mNu)));
    mPt2[index] = mP2_corr[index]*(1 - mCosThetaPQ[index]*mCosThetaPQ[index]);
    mPl2[index] = mP2_corr[index]*mCosThetaPQ[index]*mCosThetaPQ[index];
    mdeltaTheta[index] = DeltaTheta(mPx_corr[index], mPy_corr[index], mPz_corr[index]);
    mMx2[index] = mW*mW + mM[index]*mM[index] - 2*mZ[index]*mNu*mNu + 2*TMath::Sqrt(mPl2[index]*(mNu*mNu + mQ2)) - 2*kMproton*mZ[index]*mNu;
    mT[index] = mM[index]*mM[index] - 2*mZ[index]*mNu*mNu + 2*TMath::Sqrt(mPl2[index]*(mNu*mNu + mQ2)) - mQ2;
    mBettaCalc[index] = BettaCalc(mP_corr[index], mPid[index]);
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
    mEvent = tevnt;
    mEntry[index] = entry;
  } else {
    NullMixSIMRECVariables(index);
  }
}

void AssignMixGSIMVariables(Float_t entry, Int_t index) {
  std::cout << "  !! AMGV initiating..." << std::endl;
  // event related (2) -> only non-null
  mEvent = tevnt;
  mEntry[index] = entry;
  // electron (16)
  mc_mQ2 = mc_tQ2;
  mc_mW = mc_tW;
  mc_mNu = mc_tNu;
  mc_mXb = mc_tXb;
  mc_mYb = mc_tYb;
  mc_mXe = mc_tvxe;
  mc_mYe = mc_tvye;
  mc_mZe = mc_tvze;
  mc_mSectorEl = mc_tSectorEl;
  mc_mTargType = mc_tTargType;
  mc_mPex = mc_tPex;
  mc_mPey = mc_tPey;
  mc_mPez = mc_tPez;
  mc_mPe = mc_tPe;
  mc_mBettaEl = mc_tBettaEl;
  mc_mP2e = mc_mPe*mc_mPe; // recalc
  // particle (25)
  mc_mvxh[index] = mc_tvxh;
  mc_mvyh[index] = mc_tvyh;
  mc_mvzh[index] = mc_tvzh;
  mc_mSector[index] = mc_tSector;
  mc_mBetta[index] = mc_tBetta;
  mc_mMass2[index] = mc_tMass2;
  mc_mPid[index] = mc_tpid;
  mc_mdeltaZ[index] = mc_tdeltaZ;
  mc_mPx[index] = mc_tPx;
  mc_mPy[index] = mc_tPy;
  mc_mPz[index] = mc_tPz;
  mc_mP[index] = mc_tP;
  mc_mZ[index] = mc_tZh;
  mc_mThetaPQ[index] = mc_tThetaPQ;
  mc_mPt2[index] = mc_tPt2;
  mc_mPl2[index] = mc_tPl2;
  mc_mPhiPQ[index] = mc_tPhiPQ;
  mc_mMx2[index] = mc_tMx2;
  mc_mT[index] = mc_tT;
  mc_mP2[index] = mc_mP[index]*mc_mP[index]; // recalc
  mc_mM[index] = ParticleMass(mc_mPid[index]); // recalc
  mc_mE[index] = TMath::Sqrt(mc_mP2[index] + mc_mM[index]*mc_mM[index]); // recalc
  mc_mCosThetaPQ[index] = ((kEbeam - mc_mPez)*mc_mPz[index] - mc_mPex*mc_mPx[index] - mc_mPey*mc_mPy[index])/(TMath::Sqrt(mc_mP2[index]*(mc_mQ2 + mc_mNu*mc_mNu))); // recalc
  mc_mdeltaTheta[index] = DeltaTheta(mc_mPx[index], mc_mPy[index], mc_mPz[index]); // recalc
  mc_mBettaCalc[index] = BettaCalc(mc_mP[index], mc_mPid[index]); // recalc
  std::cout << "  !! AMGV ready!" << std::endl;
}

void AssignPi0Variables() {
  std::cout << "  !! APi0V initiating..." << std::endl;
  // pi0 prev (8)
  TLorentzVector Gamma1_prev(mPx_prev[0], mPy_prev[0], mPz_prev[0], mE_prev[0]);
  TLorentzVector Gamma2_prev(mPx_prev[1], mPy_prev[1], mPz_prev[1], mE_prev[1]);
  TLorentzVector Pi0_prev = Gamma1_prev + Gamma2_prev;
  pi0Px_prev = Pi0_prev.Px();
  pi0Py_prev = Pi0_prev.Py();
  pi0Pz_prev = Pi0_prev.Pz();
  pi0P2_prev = Pi0_prev.Vect().Mag2();
  pi0P_prev  = Pi0_prev.Vect().Mag();
  pi0M_prev  = Pi0_prev.M();
  pi0E_prev  = Pi0_prev.E();
  pi0Theta_prev = TMath::RadToDeg()*Gamma1_prev.Vect().Angle(Gamma2_prev.Vect());
  // pi0 true (8)
  TLorentzVector Gamma1_true(mPx_true[0], mPy_true[0], mPz_true[0], mE_true[0]);
  TLorentzVector Gamma2_true(mPx_true[1], mPy_true[1], mPz_true[1], mE_true[1]);
  TLorentzVector Pi0_true = Gamma1_true + Gamma2_true;
  pi0Px_true = Pi0_true.Px();
  pi0Py_true = Pi0_true.Py();
  pi0Pz_true = Pi0_true.Pz();
  pi0P2_true = Pi0_true.Vect().Mag2();
  pi0P_true  = Pi0_true.Vect().Mag();
  pi0M_true  = Pi0_true.M();
  pi0E_true  = Pi0_true.E();
  pi0Theta_true = TMath::RadToDeg()*Gamma1_true.Vect().Angle(Gamma2_true.Vect());
  // pi0 corr (8)
  TLorentzVector Gamma1_corr(mPx_corr[0], mPy_corr[0], mPz_corr[0], mE_corr[0]);
  TLorentzVector Gamma2_corr(mPx_corr[1], mPy_corr[1], mPz_corr[1], mE_corr[1]);
  TLorentzVector Pi0_corr = Gamma1_corr + Gamma2_corr;
  pi0Px_corr = Pi0_corr.Px();
  pi0Py_corr = Pi0_corr.Py();
  pi0Pz_corr = Pi0_corr.Pz();
  pi0P2_corr = Pi0_corr.Vect().Mag2();
  pi0P_corr  = Pi0_corr.Vect().Mag();
  pi0M_corr  = Pi0_corr.M();
  pi0E_corr  = Pi0_corr.E();
  pi0Theta_corr = TMath::RadToDeg()*Gamma1_corr.Vect().Angle(Gamma2_corr.Vect());
  std::cout << "  !! APi0V ready!" << std::endl;
}

void AssignPi0GSIMVariables() {
  std::cout << "  !! APi0GV initiating..." << std::endl;
  // pi0 (8)
  TLorentzVector mc_Gamma1(mc_mPx[0], mc_mPy[0], mc_mPz[0], mc_mE[0]);
  TLorentzVector mc_Gamma2(mc_mPx[1], mc_mPy[1], mc_mPz[1], mc_mE[1]);
  TLorentzVector mc_Pi0 = mc_Gamma1 + mc_Gamma2;
  mc_pi0Px = mc_Pi0.Px();
  mc_pi0Py = mc_Pi0.Py();
  mc_pi0Pz = mc_Pi0.Pz();
  mc_pi0P2 = mc_Pi0.Vect().Mag2();
  mc_pi0P  = mc_Pi0.Vect().Mag();
  mc_pi0E  = mc_Pi0.E();
  mc_pi0M  = mc_Pi0.M();
  mc_pi0Theta = TMath::RadToDeg()*mc_Gamma1.Vect().Angle(mc_Gamma2.Vect());
  std::cout << "  !! APi0GV ready!" << std::endl;
}

void AssignOmegaVariables() {
  std::cout << "  !! AomegaV initiating..." << std::endl;
  // omega prev (6+13)
  TLorentzVector Pi0_prev(pi0Px_prev, pi0Py_prev, pi0Pz_prev, pi0E_prev);
  TLorentzVector Pip_prev(mPx_prev[2], mPy_prev[2], mPz_prev[2], mE_prev[2]);
  TLorentzVector Pim_prev(mPx_prev[3], mPy_prev[3], mPz_prev[3], mE_prev[3]);
  TLorentzVector omega_prev = Pi0_prev + Pip_prev + Pim_prev;
  wPx_prev = omega_prev.Px();
  wPy_prev = omega_prev.Py();
  wPz_prev = omega_prev.Pz();
  wP2_prev = omega_prev.Vect().Mag2();
  wP_prev  = omega_prev.Vect().Mag();
  wE_prev  = omega_prev.E();
  wM_prev  = omega_prev.M();
  wD_prev  = wM_prev - Pi0_prev.M() - Pip_prev.M() - Pim_prev.M();
  wSD_prev = wD_prev + 2*kMpi + kMpi0; // shifted
  wZ_prev  = wE_prev/mNu;
  wPhiPQ_prev = PhiPQ(wPx_prev, wPy_prev, wPz_prev);
  wThetaPQ_prev = ThetaPQ(wPx_prev, wPy_prev, wPz_prev);
  wCosThetaPQ_prev = ((kEbeam - mPez)*wPz_prev - mPex*wPx_prev - mPey*wPy_prev)/(TMath::Sqrt(wP2_prev*(mQ2 + mNu*mNu)));
  wPt2_prev = wP2_prev*(1 - wCosThetaPQ_prev*wCosThetaPQ_prev);
  wPl2_prev = wP2_prev*wCosThetaPQ_prev*wCosThetaPQ_prev;
  wMx2_prev = mW*mW + wM_prev*wM_prev - 2*wZ_prev*mNu*mNu + 2*TMath::Sqrt(wPl2_prev*(mNu*mNu + mQ2)) - 2*kMproton*wZ_prev*mNu;
  wT_prev = wM_prev*wM_prev - 2*wZ_prev*mNu*mNu + 2*TMath::Sqrt(wPl2_prev*(mNu*mNu + mQ2)) - mQ2;
  wBettaCalc_prev = BettaCalc(wP_prev, 223);
  wdeltaTheta_prev = DeltaTheta(wPx_prev, wPy_prev, wPz_prev);
  // omega true (6+13)
  TLorentzVector Pi0_true(pi0Px_true, pi0Py_true, pi0Pz_true, pi0E_true);
  TLorentzVector Pip_true(mPx_true[2], mPy_true[2], mPz_true[2], mE_true[2]);
  TLorentzVector Pim_true(mPx_true[3], mPy_true[3], mPz_true[3], mE_true[3]);
  TLorentzVector omega_true = Pi0_true + Pip_true + Pim_true;
  wPx_true = omega_true.Px();
  wPy_true = omega_true.Py();
  wPz_true = omega_true.Pz();
  wP2_true = omega_true.Vect().Mag2();
  wP_true  = omega_true.Vect().Mag();
  wE_true  = omega_true.E();
  wM_true  = omega_true.M();
  wD_true  = wM_true - Pi0_true.M() - Pip_true.M() - Pim_true.M();
  wSD_true = wD_true + 2*kMpi + kMpi0; // shifted
  wZ_true  = wE_true/mNu;
  wPhiPQ_true = PhiPQ(wPx_true, wPy_true, wPz_true);
  wThetaPQ_true = ThetaPQ(wPx_true, wPy_true, wPz_true);
  wCosThetaPQ_true = ((kEbeam - mPez)*wPz_true - mPex*wPx_true - mPey*wPy_true)/(TMath::Sqrt(wP2_true*(mQ2 + mNu*mNu)));
  wPt2_true = wP2_true*(1 - wCosThetaPQ_true*wCosThetaPQ_true);
  wPl2_true = wP2_true*wCosThetaPQ_true*wCosThetaPQ_true;
  wMx2_true = mW*mW + wM_true*wM_true - 2*wZ_true*mNu*mNu + 2*TMath::Sqrt(wPl2_true*(mNu*mNu + mQ2)) - 2*kMproton*wZ_true*mNu;
  wT_true = wM_true*wM_true - 2*wZ_true*mNu*mNu + 2*TMath::Sqrt(wPl2_true*(mNu*mNu + mQ2)) - mQ2;
  wBettaCalc_true = BettaCalc(wP_true, 223);
  wdeltaTheta_true = DeltaTheta(wPx_true, wPy_true, wPz_true);
  // omega corr (6+13)
  TLorentzVector Pi0_corr(pi0Px_corr, pi0Py_corr, pi0Pz_corr, pi0E_corr);
  TLorentzVector Pip_corr(mPx_corr[2], mPy_corr[2], mPz_corr[2], mE_corr[2]);
  TLorentzVector Pim_corr(mPx_corr[3], mPy_corr[3], mPz_corr[3], mE_corr[3]);
  TLorentzVector omega_corr = Pi0_corr + Pip_corr + Pim_corr;
  wPx_corr = omega_corr.Px();
  wPy_corr = omega_corr.Py();
  wPz_corr = omega_corr.Pz();
  wP2_corr = omega_corr.Vect().Mag2();
  wP_corr  = omega_corr.Vect().Mag();
  wE_corr  = omega_corr.E();
  wM_corr  = omega_corr.M();
  wD_corr  = wM_corr - Pi0_corr.M() - Pip_corr.M() - Pim_corr.M();
  wSD_corr = wD_corr + 2*kMpi + kMpi0; // shifted
  wZ_corr  = wE_corr/mNu;
  wPhiPQ_corr = PhiPQ(wPx_corr, wPy_corr, wPz_corr);
  wThetaPQ_corr = ThetaPQ(wPx_corr, wPy_corr, wPz_corr);
  wCosThetaPQ_corr = ((kEbeam - mPez)*wPz_corr - mPex*wPx_corr - mPey*wPy_corr)/(TMath::Sqrt(wP2_corr*(mQ2 + mNu*mNu)));
  wPt2_corr = wP2_corr*(1 - wCosThetaPQ_corr*wCosThetaPQ_corr);
  wPl2_corr = wP2_corr*wCosThetaPQ_corr*wCosThetaPQ_corr;
  wMx2_corr = mW*mW + wM_corr*wM_corr - 2*wZ_corr*mNu*mNu + 2*TMath::Sqrt(wPl2_corr*(mNu*mNu + mQ2)) - 2*kMproton*wZ_corr*mNu;
  wT_corr = wM_corr*wM_corr - 2*wZ_corr*mNu*mNu + 2*TMath::Sqrt(wPl2_corr*(mNu*mNu + mQ2)) - mQ2;
  wBettaCalc_corr = BettaCalc(wP_corr, 223);
  wdeltaTheta_corr = DeltaTheta(wPx_corr, wPy_corr, wPz_corr);
  std::cout << "  !! AomegaV ready!" << std::endl;
}

void AssignOmegaGSIMVariables() {
  std::cout << "  !! AomegaGV initiating..." << std::endl;
  // omega (19)
  TLorentzVector mc_Pi0(mc_pi0Px,  mc_pi0Py,  mc_pi0Pz,  mc_pi0E);
  TLorentzVector mc_Pip(mc_mPx[2], mc_mPy[2], mc_mPz[2], mc_mE[2]);
  TLorentzVector mc_Pim(mc_mPx[3], mc_mPy[3], mc_mPz[3], mc_mE[3]);
  TLorentzVector mc_omega = mc_Pi0 + mc_Pip + mc_Pim;
  mc_wPx = mc_omega.Px();
  mc_wPy = mc_omega.Py();
  mc_wPz = mc_omega.Pz();
  mc_wP  = mc_omega.Vect().Mag();
  mc_wP2 = mc_omega.Vect().Mag2();
  mc_wE  = mc_omega.E();
  mc_wM  = mc_omega.M();
  mc_wD  = mc_wM - mc_Pi0.M() - mc_Pip.M() - mc_Pim.M();
  mc_wSD = mc_wD + 2*kMpi + kMpi0; // shifted
  mc_wZ = mc_wE/mc_mNu;
  mc_wThetaPQ = ThetaPQ(mc_wPx, mc_wPy, mc_wPz);
  mc_wPhiPQ = PhiPQ(mc_wPx, mc_wPy, mc_wPz);
  mc_wPl2 = mc_wP2*mc_wCosThetaPQ*mc_wCosThetaPQ;
  mc_wPt2 = mc_wP2*(1 - mc_wCosThetaPQ*mc_wCosThetaPQ);
  mc_wBettaCalc = BettaCalc(mc_wP, 223);
  mc_wdeltaTheta = DeltaTheta(mc_wPx, mc_wPy, mc_wPz);
  mc_wT = mc_wM*mc_wM - 2*mc_wZ*mc_mNu*mc_mNu + 2*TMath::Sqrt(mc_wPl2*(mc_mNu*mc_mNu + mc_mQ2)) - mc_mQ2;
  mc_wMx2 = mc_mW*mc_mW + mc_wM*mc_wM - 2*mc_wZ*mc_mNu*mc_mNu + 2*TMath::Sqrt(mc_wPl2*(mc_mNu*mc_mNu + mc_mQ2)) - 2*kMproton*mc_wZ*mc_mNu;
  mc_wCosThetaPQ = ((kEbeam - mc_mPez)*mc_wPz - mc_mPex*mc_wPx - mc_mPey*mc_wPy)/(TMath::Sqrt(mc_wP2*(mc_mQ2 + mc_mNu*mc_mNu)));
  std::cout << "  !! AomegaGV ready!" << std::endl;
}

void AssignMoreVariables(Int_t fnGamma, Int_t fnPip, Int_t fnPim) {
  // (these variables depend that all the other variables from decay particles are set and ready)
  std::cout << "  !! AmoreV initiating..." << std::endl;
  // crossed terms (9), assuming P_corr and E_corr as the final versions
  pippimP = mPx_corr[2]*mPx_corr[3] + mPy_corr[2]*mPy_corr[3] + mPz_corr[2]*mPz_corr[3];
  pippimE = mE_corr[2]*mE_corr[3];
  pippimM = TMath::Sqrt(2*kMpi*kMpi + 2*(pippimE - pippimP));
  pippi0P = mPx_corr[2]*pi0Px_corr + mPy_corr[2]*pi0Py_corr + mPz_corr[2]*pi0Pz_corr;
  pippi0E = mE_corr[2]*pi0E_corr;
  pippi0M = TMath::Sqrt(kMpi*kMpi + pi0M_corr*pi0M_corr + 2*(pippi0E - pippi0P));
  pimpi0P = mPx_corr[3]*pi0Px_corr + mPy_corr[3]*pi0Py_corr + mPz_corr[3]*pi0Pz_corr;
  pimpi0E = mE_corr[3]*pi0E_corr;
  pimpi0M = TMath::Sqrt(kMpi*kMpi + pi0M_corr*pi0M_corr + 2*(pimpi0E - pimpi0P));
  // number of particles (3)
  nGamma = (Float_t) fnGamma;
  nPip   = (Float_t) fnPip;
  nPim   = (Float_t) fnPim;
  std::cout << "  !! AmoreV ready!" << std::endl;
}

void AssignMoreGSIMVariables(Int_t mc_fnGamma, Int_t mc_fnPip, Int_t mc_fnPim) {
  std::cout << "  !! AMoreGV initiating..." << std::endl;
  // crossed terms (9)
  mc_pippimP = mc_mPx[2]*mc_mPx[3] + mc_mPy[2]*mc_mPy[3] + mc_mPz[2]*mc_mPz[3];
  mc_pippimE = mc_mE[2]*mc_mE[3];
  mc_pippimM = TMath::Sqrt(2*kMpi*kMpi + 2*(mc_pippimE - mc_pippimP));
  mc_pippi0P = mc_mPx[2]*mc_pi0Px + mc_mPy[2]*mc_pi0Py + mc_mPz[2]*mc_pi0Pz;
  mc_pippi0E = mc_mE[2]*mc_pi0E;
  mc_pippi0M = TMath::Sqrt(kMpi*kMpi + mc_pi0M*mc_pi0M + 2*(mc_pippi0E - mc_pippi0P));
  mc_pimpi0P = mc_mPx[3]*mc_pi0Px + mc_mPy[3]*mc_pi0Py + mc_mPz[3]*mc_pi0Pz;
  mc_pimpi0E = mc_mE[3]*mc_pi0E;
  mc_pimpi0M = TMath::Sqrt(kMpi*kMpi + mc_pi0M*mc_pi0M + 2*(mc_pimpi0E - mc_pimpi0P));
  // number of particles (3)
  mc_nGamma = (Float_t) mc_fnGamma;
  mc_nPip   = (Float_t) mc_fnPip;
  mc_nPim   = (Float_t) mc_fnPim;
  std::cout << "  !! AMoreGV ready!" << std::endl;
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
      if (analyserOption == "C" || analyserOption == "Fe" || analyserOption == "Pb") {
	fE = TMath::Max(tEtot, tEin+tEout)/0.272;
      } else if (analyserOption == "Sim") {
	fE = TMath::Max(tEtot, tEin+tEout)/0.2806; // primitive sampling fraction factor for sim
      }
    } else if (option == "corr") {
      if (analyserOption == "C" || analyserOption == "Pb") {
	fE = TMath::Max(tEtot, tEin+tEout)/0.272;
	corrFactor = 1.129 - 0.05793/fE - 1.0773e-12/(fE*fE);
      } else if (analyserOption == "Fe") {
	fE = TMath::Max(tEtot, tEin+tEout)/0.272;
	corrFactor = 1.116 - 0.09213/fE + 0.01007/(fE*fE);
      } else if (analyserOption == "Sim") {
	fE = TMath::Max(tEtot, tEin+tEout)/0.2806;
	corrFactor = 1.000 + 0.005/fE - 0.0052/(fE*fE);
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
