#include "analysisConfig.h"

/*** Constants ***/

extern Float_t kEbeam;

/*** Input variables ***/

// (81 variables for data)
// electron (39)
extern Float_t tQ2, tW, tNu, tXb, tYb, tvxe, tvye, tvze, tSectorEl, tTargType, tPex, tPey, tPez, tPe, tBettaEl, tEtote, tEine, tEoute, tvxec, tvyec, tvzec, tXECe, tYECe, tZECe;
extern Float_t tStatDCEl, tDCStatusEl, tStatECEl, tECStatusEl, tTimeECEl, tPathECEl, tChi2ECEl, tStatSCEl, tSCStatusEl, tTimeSCEl, tPathSCEl, tStatCCEl, tCCStatusEl, tChi2CCEl, tStatusEl;
// particle (41)
extern Float_t tZh, tThetaPQ, tPt2, tPl2, tPhiPQ, tMx2, tT, tvxh, tvyh, tvzh, tSector, tPx, tPy, tPz, tP, tBetta, tMass2, tEtot, tEin, tEout, tXEC, tYEC, tZEC, tpid, tT4, tdeltaZ;
extern Float_t tStatDC, tDCStatus, tStatEC, tECStatus, tTimeEC, tPathEC, tChi2EC, tStatSC, tSCStatus, tTimeSC, tPathSC, tStatCC, tCCStatus, tChi2CC, tStatus;
// event (1)
extern Float_t tevnt;

/*** Output/original variables ***/

// (90 variables for data)
// electron (40) (39+1new)
extern Float_t oQ2, oW, oNu, oXb, oYb, oXe, oYe, oZe, oSectorEl, oTargType, oPex, oPey, oPez, oPe, oBettaEl, oEtote, oEine, oEoute, oXec, oYec, oZec, oXECe, oYECe, oZECe;
extern Float_t oP2e;
extern Float_t oStatDCEl, oDCStatusEl, oStatECEl, oECStatusEl, oTimeECEl, oPathECEl, oChi2ECEl, oStatSCEl, oSCStatusEl, oTimeSCEl, oPathSCEl, oStatCCEl, oCCStatusEl, oChi2CCEl, oStatusEl;
// particle (51) (41+10new)
extern Float_t oZ, oThetaPQ, oPt2, oPl2, oPhiPQ, oMx2, oT, ovxh, ovyh, ovzh, oSector, oPx, oPy, oPz, oP, oBetta, oMass2, oEtot, oEin, oEout, oXEC, oYEC, oZEC, oPid, oT4, odeltaZ;
extern Float_t oCosThetaPQ, oP2, oM, oBettaCalc, oEtrue, oEcorr, odeltaTheta, oPxu, oPyu, oPzu;
extern Float_t oStatDC, oDCStatus, oStatEC, oECStatus, oTimeEC, oPathEC, oChi2EC, oStatSC, oSCStatus, oTimeSC, oPathSC, oStatCC, oCCStatus, oChi2CC, oStatus;
// event (2) (1+1new)
extern Float_t oEvent;
extern Float_t oEntry; // debug purposes

/*** Output/mix variables ***/

// (??? variables for data)
// electron (40) (39+1new)
extern Float_t mQ2, mW, mNu, mXb, mYb, mXe, mYe, mZe, mSectorEl, mTargType, mPex, mPey, mPez, mPe, mBettaEl, mEtote, mEine, mEoute, mXec, mYec, mZec, mXECe, mYECe, mZECe;
extern Float_t mP2e;
extern Float_t mStatDCEl, mDCStatusEl, mStatECEl, mECStatusEl, mTimeECEl, mPathECEl, mChi2ECEl, mStatSCEl, mSCStatusEl, mTimeSCEl, mPathSCEl, mStatCCEl, mCCStatusEl, mChi2CCEl, mStatusEl;
// particles (51) (41+10new)
extern Float_t mZ[4], mThetaPQ[4], mPt2[4], mPl2[4], mPhiPQ[4], mMx2[4], mT[4], mvxh[4], mvyh[4], mvzh[4], mSector[4], mPx[4], mPy[4], mPz[4], mP[4], mBetta[4], mMass2[4], mEtot[4], mEin[4], mEout[4], mXEC[4], mYEC[4], mZEC[4], mPid[4], mT4[4], mdeltaZ[4];
extern Float_t mCosThetaPQ[4], mP2[4], mM[4], mBettaCalc[4], mEtrue[4], mEcorr[4], mdeltaTheta[4], mPxu[4], mPyu[4], mPzu[4];
extern Float_t mStatDC[4], mDCStatus[4], mStatEC[4], mECStatus[4], mTimeEC[4], mPathEC[4], mChi2EC[4], mStatSC[4], mSCStatus[4], mTimeSC[4], mPathSC[4], mStatCC[4], mCCStatus[4], mChi2CC[4], mStatus[4];
// event related (2) (1+1new)
extern Float_t mEvent;
extern Float_t mEntry[4];
// omega (20) (all new)
extern Float_t wZ, wCosThetaPQ, wThetaPQ, wPt2, wPl2, wPhiPQ, wMx2, wT, wPx, wPy, wPz, wP, wP2, wE, wEprev, wBettaCalc, wdeltaTheta, wD, wM, wSD;
// pi0 (8) (all new)
extern Float_t pi0Px, pi0Py, pi0Pz, pi0P2, pi0P, pi0E, pi0M, pi0CosTheta;
// crossed terms (9) (all new)
extern Float_t pippimP, pippimE, pippimM;
extern Float_t pippi0P, pippi0E, pippi0M;
extern Float_t pimpi0P, pimpi0E, pimpi0M;
// number of particles (3) (all new)
extern Float_t nPip, nPim, nGamma;

/*** Declaration of functions ***/

Float_t ParticleMass(Float_t fPid);
Float_t CorrectEnergyStep1(Float_t fEtot, Float_t fEin, Float_t fEout, Float_t fPid, TString analyserOption);
Float_t CorrectEnergyStep2(Float_t fEtrue, Float_t fPid, TString analyserOption);
Float_t CorrectMomentum(Float_t fEcorr, Float_t fPi, Float_t fPid, Int_t i);
Float_t PhiPQ(Float_t fPx, Float_t fPy, Float_t fPz);
Float_t ThetaPQ(Float_t fPx, Float_t fPy, Float_t fPz);
Float_t DeltaTheta(Float_t fPx, Float_t fPy, Float_t fPz);
Float_t BettaCalc(Float_t fP, Float_t fPid);

/*** Functions ***/

void SetInputBranches(TChain *chain, Int_t simFlag) {
  // init all variables
  chain->SetBranchStatus("*", 1);
  // electron (39)
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
  chain->SetBranchAddress("Chi2CCEl", &tChi2CCEl);
  chain->SetBranchAddress("StatusEl", &tStatusEl);  
  // evnt related (1)
  chain->SetBranchAddress("evnt", &tevnt);
  // particle (41)
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
  chain->SetBranchAddress("Chi2CC", &tChi2CC);
  chain->SetBranchAddress("Status", &tStatus);
}

void SetOutputBranches(TTree *tree, TString option) {
  if (option == "original") {
    // electron (40)
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
    tree->Branch("Chi2CCEl", &oChi2CCEl);
    tree->Branch("StatusEl", &oStatusEl);
    // particle (51)
    tree->Branch("Z", &oZ);
    tree->Branch("ThetaPQ", &oThetaPQ);
    tree->Branch("CosThetaPQ", &oCosThetaPQ);
    tree->Branch("Pt2", &oPt2);
    tree->Branch("Pl2", &oPl2);
    tree->Branch("PhiPQ", &oPhiPQ);
    tree->Branch("Mx2", &oMx2);
    tree->Branch("T", &oT);
    tree->Branch("vxh", &ovxh);
    tree->Branch("vyh", &ovyh);
    tree->Branch("vzh", &ovzh);
    tree->Branch("Sector", &oSector);
    tree->Branch("Px", &oPx);
    tree->Branch("Py", &oPy);
    tree->Branch("Pz", &oPz);
    tree->Branch("Pxu", &oPxu);
    tree->Branch("Pyu", &oPyu);
    tree->Branch("Pzu", &oPzu);
    tree->Branch("P", &oP);
    tree->Branch("P2", &oP2);
    tree->Branch("M", &oM);
    tree->Branch("Etot", &oEtot);
    tree->Branch("Ein", &oEin);
    tree->Branch("Eout", &oEout);
    tree->Branch("Etrue", &oEtrue);
    tree->Branch("Ecorr", &oEcorr);
    tree->Branch("Betta", &oBetta);
    tree->Branch("BettaCalc", &oBettaCalc);
    tree->Branch("Mass2", &oMass2);
    tree->Branch("XEC", &oXEC);
    tree->Branch("YEC", &oYEC);
    tree->Branch("ZEC", &oZEC);
    tree->Branch("Pid", &oPid);
    tree->Branch("T4", &oT4);
    tree->Branch("deltaZ", &odeltaZ);
    tree->Branch("deltaTheta", &odeltaTheta);
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
    tree->Branch("Chi2CC", &oChi2CC);
    tree->Branch("Status", &oStatus);
    // event-related (2)
    tree->Branch("Event", &oEvent);
    tree->Branch("Entry", &oEntry);
  } else if (option == "mix") {
    // electron (40)
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
    tree->Branch("Chi2CCEl", &mChi2CCEl);
    tree->Branch("StatusEl", &mStatusEl);
    // particles (51)
    tree->Branch("Z", &mZ, "Z[4]/F");
    tree->Branch("PhiPQ", &mPhiPQ, "PhiPQ[4]/F");
    tree->Branch("ThetaPQ", &mThetaPQ, "ThetaPQ[4]/F");
    tree->Branch("CosThetaPQ", &mCosThetaPQ, "CosThetaPQ[4]/F");
    tree->Branch("Pt2", &mPt2, "Pt2[4]/F");
    tree->Branch("Pl2", &mPl2, "Pl2[4]/F");
    tree->Branch("Mx2", &mMx2, "Mx2[4]/F");
    tree->Branch("T", &mT, "T[4]/F");
    tree->Branch("vxh", &mvxh, "vxh[4]/F");
    tree->Branch("vyh", &mvyh, "vyh[4]/F");
    tree->Branch("vzh", &mvzh, "vzh[4]/F");
    tree->Branch("Sector", &mSector, "Sector[4]/F");
    tree->Branch("Px", &mPx, "Px[4]/F");
    tree->Branch("Py", &mPy, "Py[4]/F");
    tree->Branch("Pz", &mPz, "Pz[4]/F");
    tree->Branch("Pxu", &mPxu, "Pxu[4]/F");
    tree->Branch("Pyu", &mPyu, "Pyu[4]/F");
    tree->Branch("Pzu", &mPzu, "Pzu[4]/F");
    tree->Branch("P", &mP, "P[4]/F");
    tree->Branch("P2", &mP2, "P2[4]/F");
    tree->Branch("Etrue", &mEtrue, "Etrue[4]/F");
    tree->Branch("Ecorr", &mEcorr, "Ecorr[4]/F");
    tree->Branch("M", &mM, "M[4]/F");
    tree->Branch("Betta", &mBetta, "Betta[4]/F");
    tree->Branch("BettaCalc", &mBettaCalc, "BettaCalc[4]/F");
    tree->Branch("Mass2", &mMass2, "Mass2[4]/F");
    tree->Branch("Etot", &mEtot, "Etot[4]/F");
    tree->Branch("Ein", &mEin, "Ein[4]/F");
    tree->Branch("Eout", &mEout, "Eout[4]/F");
    tree->Branch("XEC", &mXEC, "XEC[4]/F");
    tree->Branch("YEC", &mYEC, "YEC[4]/F");
    tree->Branch("ZEC", &mZEC, "ZEC[4]/F");
    tree->Branch("Pid", &mPid, "Pid[4]/F");
    tree->Branch("T4", &mT4, "T4[4]/F");
    tree->Branch("deltaZ", &mdeltaZ, "deltaZ[4]/F");
    tree->Branch("deltaTheta", &mdeltaTheta, "deltaTheta[4]/F");
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
    tree->Branch("Chi2CC", &mChi2CC, "Chi2CC[4]/F");
    tree->Branch("Status", &mStatus, "Status[4]/F");
    // event related (2)
    tree->Branch("Entry", &mEntry, "Entry[4]/F");
    tree->Branch("Event", &mEvent);
    // pi0 (8)
    tree->Branch("pi0Px", &pi0Px);
    tree->Branch("pi0Py", &pi0Py);
    tree->Branch("pi0Pz", &pi0Pz);
    tree->Branch("pi0P2", &pi0P2);
    tree->Branch("pi0P", &pi0P);
    tree->Branch("pi0E", &pi0E);
    tree->Branch("pi0M", &pi0M);
    tree->Branch("pi0CosTheta", &pi0CosTheta);
    // omega (20)
    tree->Branch("wZ", &wZ);
    tree->Branch("wPhiPQ", &wPhiPQ);
    tree->Branch("wThetaPQ", &wThetaPQ);
    tree->Branch("wCosThetaPQ", &wCosThetaPQ);
    tree->Branch("wPt2", &wPt2);
    tree->Branch("wPl2", &wPl2);
    tree->Branch("wMx2", &wMx2);
    tree->Branch("wT", &wT);
    tree->Branch("wPx", &wPx);
    tree->Branch("wPy", &wPy);
    tree->Branch("wPz", &wPz);
    tree->Branch("wP2", &wP2);
    tree->Branch("wP", &wP);
    tree->Branch("wE", &wE);
    tree->Branch("wEprev", &wEprev);
    tree->Branch("wBettaCalc", &wBettaCalc);
    tree->Branch("wdeltaTheta", &wdeltaTheta);
    tree->Branch("wD", &wD);
    tree->Branch("wM", &wM);
    tree->Branch("wSD", &wSD);
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
    // number of particles found in that event (3)
    tree->Branch("nPip", &nPip);
    tree->Branch("nPim", &nPim);
    tree->Branch("nGamma", &nGamma);
  }
}

void AssignVariables(TString option, Int_t entry, Int_t index, TString analyserOption) {
  if (option == "original") {
    // electron (40) (39+1new) : nothing to correct or modify here
    oQ2 = tQ2;
    oW = tW;
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
    oPe = tPe;
    oP2e = oPe*oPe;
    oBettaEl = tBettaEl;
    oEtote = tEtote;
    oEine = tEine;
    oEoute = tEoute;
    oXec = tvxec;
    oYec = tvyec;
    oZec = tvzec;
    oXECe = tXECe;
    oYECe = tYECe;
    oZECe = tZECe;
    oStatDCEl = tStatDCEl;
    oDCStatusEl = tDCStatusEl;
    oStatECEl = tStatECEl;
    oECStatusEl = tECStatusEl;
    oTimeECEl = tTimeECEl;
    oPathECEl = tPathECEl;
    oChi2ECEl = tChi2ECEl;
    oStatSCEl = tStatSCEl;
    oSCStatusEl = tSCStatusEl;
    oTimeSCEl = tTimeSCEl;
    oPathSCEl = tPathSCEl;
    oStatCCEl = tStatCCEl;
    oCCStatusEl = tCCStatusEl;
    oChi2CCEl = tChi2CCEl;
    oStatusEl = tStatusEl;
    // particle (51)
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
    oPid = tpid;
    odeltaZ = tdeltaZ;
    oEtrue = CorrectEnergyStep1(oEtot, oEin, oEout, oPid, analyserOption);
    oEcorr = CorrectEnergyStep2(oEtrue, oPid, analyserOption);
    oPxu = tPx;
    oPyu = tPy;
    oPzu = tPz;
    oPx = CorrectMomentum(oEcorr, tPx, oPid, 0);
    oPy = CorrectMomentum(oEcorr, tPy, oPid, 1);
    oPz = CorrectMomentum(oEcorr, tPz, oPid, 2);
    oP2 = oP*oP;
    oP  = TMath::Sqrt(oP2);
    oPhiPQ = PhiPQ(oPx, oPy, oPz);
    oThetaPQ = ThetaPQ(oPx, oPy, oPz);
    oCosThetaPQ = ((kEbeam - oPez)*oPz - oPex*oPx - oPey*oPy)/(TMath::Sqrt(oP2*(oQ2 + oNu*oNu)));
    oZ = oEcorr/oNu;
    oPt2 = oP2*(1 - oCosThetaPQ*oCosThetaPQ);
    oPl2 = oP2*oCosThetaPQ*oCosThetaPQ;
    oM = ParticleMass(oPid);
    oMx2 = tW*tW + oM*oM - 2*oZ*oNu*oNu + 2*TMath::Sqrt(oPl2*(oNu*oNu + oQ2)) - 2*kMproton*oZ*oNu;
    oT = oM*oM - 2*oZ*oNu*oNu + 2*TMath::Sqrt(oPl2*(oNu*oNu + oQ2)) - oQ2;
    oT4 = tT4;
    oBettaCalc = BettaCalc(oP, oPid);
    oBetta = tBetta;
    oMass2 = tMass2;
    odeltaTheta = DeltaTheta(oPx, oPy, oPz);
    oStatDC = tStatDC;
    oDCStatus = tDCStatus;
    oStatEC = tStatEC;
    oECStatus = tECStatus;
    oTimeEC = tTimeEC;
    oPathEC = tPathEC;
    oChi2EC = tChi2EC;
    oStatSC = tStatSC;
    oSCStatus = tSCStatus;
    oTimeSC = tTimeSC;
    oPathSC = tPathSC;
    oStatCC = tStatCC;
    oCCStatus = tCCStatus;
    oChi2CC = tChi2CC;
    oStatus = tStatus;
    // event-related (2) (1+1new)
    oEvent = tevnt;
    oEntry = (Float_t) entry;
  } else if (option == "mix") {
    // electron (40) (39+1new)
    mQ2 = tQ2;
    mW = tW;
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
    mP2e = mPe*mPe;
    mBettaEl = tBettaEl;
    mEtote = tEtote;
    mEine = tEine;
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
    mChi2CCEl   = tChi2CCEl;
    mStatusEl   = tStatusEl;
    // particles (51)
    mvxh[index] = tvxh;
    mvyh[index] = tvyh;
    mvzh[index] = tvzh;
    mSector[index] = tSector;
    mXEC[index] = tXEC;
    mYEC[index] = tYEC;
    mZEC[index] = tZEC;
    mPid[index] = tpid;
    mEtot[index] = tEtot;
    mEin[index] = tEin;
    mEout[index] = tEout;
    mEtrue[index] = CorrectEnergyStep1(mEtot[index], mEin[index], mEtot[index], mPid[index], analyserOption);
    mEcorr[index] = CorrectEnergyStep2(mEtrue[index], mPid[index], analyserOption);
    mPxu[index] = tPx;
    mPyu[index] = tPy;
    mPzu[index] = tPz;
    mPx[index] = CorrectMomentum(mEcorr[index], tPx, mPid[index], 0);
    mPy[index] = CorrectMomentum(mEcorr[index], tPy, mPid[index], 1);
    mPz[index] = CorrectMomentum(mEcorr[index], tPz, mPid[index], 2);
    mP2[index] = mPx[index]*mPx[index] + mPy[index]*mPy[index] + mPz[index]*mPz[index];
    mP[index]  = TMath::Sqrt(mP2[index]);
    mZ[index] = mEcorr[index]/mNu;
    mPhiPQ[index] = PhiPQ(mPx[index], mPy[index], mPz[index]);
    mThetaPQ[index] = ThetaPQ(mPx[index], mPy[index], mPz[index]);
    mCosThetaPQ[index] = ((kEbeam - mPez)*mPz[index] - mPex*mPx[index] - mPey*mPy[index])/(TMath::Sqrt(mP2[index]*(mQ2 + mNu*mNu)));
    mPt2[index] = mP2[index]*(1 - mCosThetaPQ[index]*mCosThetaPQ[index]);
    mPl2[index] = mP2[index]*mCosThetaPQ[index]*mCosThetaPQ[index];
    mdeltaZ[index] = tdeltaZ;
    mdeltaTheta[index] = DeltaTheta(mPx[index], mPy[index], mPz[index]);
    mM[index] = ParticleMass(mPid[index]);
    mMx2[index] = mW*mW + mM[index]*mM[index] - 2*mZ[index]*mNu*mNu + 2*TMath::Sqrt(mPl2[index]*(mNu*mNu + mQ2)) - 2*kMproton*mZ[index]*mNu;
    mT[index] = mM[index]*mM[index] - 2*mZ[index]*mNu*mNu + 2*TMath::Sqrt(mPl2[index]*(mNu*mNu + mQ2)) - mQ2;
    mT4[index] = tT4;
    mBettaCalc[index] = BettaCalc(mP[index], mPid[index]);
    mMass2[index] = tMass2;
    mBetta[index] = tBetta;     
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
    mChi2CC[index]   = tChi2CC;
    mStatus[index]   = tStatus;
    // event related (2) (1+1new)
    mEvent = tevnt;
    mEntry[index] = entry; // new
  }
}

void AssignMoreVariables(Int_t nGamma, Int_t nPip, Int_t nPim) {
  // (in another function, because these variables depend that all the other variables from decay particles are set and ready)

  // more variables (39 in total)
  // pi0 (8) (all new)
  pi0Px = mPx[0] + mPx[1];
  pi0Py = mPy[0] + mPy[1];
  pi0Pz = mPz[0] + mPz[1];
  pi0P2 = pi0Px*pi0Px + pi0Py*pi0Py + pi0Pz*pi0Pz;
  pi0P  = TMath::Sqrt(pi0P2);
  pi0CosTheta = (mPx[0]*mPx[1] + mPy[0]*mPy[1] + mPz[0]*mPz[1])/(mEcorr[0]*mEcorr[1]);
  pi0M = TMath::Sqrt(2*mEcorr[0]*mEcorr[1]*(1 - pi0CosTheta));
  pi0E = TMath::Sqrt(pi0M*pi0M + pi0P*pi0P);
  // omega (20) (all new)
  wPx = pi0Px + mPx[2] + mPx[3];
  wPy = pi0Py + mPy[2] + mPy[3];
  wPz = pi0Pz + mPz[2] + mPz[3];
  wP2 = wPx*wPx + wPy*wPy + wPz*wPz;
  wP = TMath::Sqrt(wP2);
  wE = pi0E + mEtrue[2] + mEtrue[3];
  wEprev = mEtrue[0] + mEtrue[1] + mEtrue[2] + mEtrue[3];
  wZ = wE/mNu;
  wPhiPQ = PhiPQ(wPx, wPy, wPz);
  wThetaPQ = ThetaPQ(wPx, wPy, wPz);
  wCosThetaPQ = ((kEbeam - mPez)*wPz - mPex*wPx - mPey*wPy)/(TMath::Sqrt(wP2*(mQ2 + mNu*mNu)));
  wPt2 = wP2*(1 - wCosThetaPQ*wCosThetaPQ);
  wPl2 = wP2*wCosThetaPQ*wCosThetaPQ;
  wMx2 = mW*mW + wM*wM - 2*wZ*mNu*mNu + 2*TMath::Sqrt(wPl2*(mNu*mNu + mQ2)) - 2*kMproton*wZ*mNu;
  wT = wM*wM - 2*wZ*mNu*mNu + 2*TMath::Sqrt(wPl2*(mNu*mNu + mQ2)) - mQ2;
  wBettaCalc = BettaCalc(wP, 223);
  wdeltaTheta = DeltaTheta(wPx, wPy, wPz);
  wM = TMath::Sqrt(wE*wE - wP*wP);
  wD = wD - wM - wM - pi0M;
  wSD = wD - wM - wM - pi0M + 2*kMpi + kMpi0;
  // crossed terms (9) (all new)
  pippimP = mPx[2]*mPx[3] + mPy[2]*mPy[3] + mPz[2]*mPz[3];
  pippimE = mEtrue[2]*mEtrue[3];
  pippimM = TMath::Sqrt(2*kMpi*kMpi + 2*(pippimE - pippimP));
  pippi0P = mPx[2]*pi0Px + mPy[2]*pi0Py + mPz[2]*pi0Pz;
  pippi0E = mEtrue[2]*pi0E;
  pippi0M = TMath::Sqrt(kMpi*kMpi + pi0M*pi0M + 2*(pippi0E - pippi0P));
  pimpi0P = mPx[3]*pi0Px + mPy[3]*pi0Py + mPz[3]*pi0Pz;
  pimpi0E = mEtrue[3]*pi0E;
  pimpi0M = TMath::Sqrt(kMpi*kMpi + pi0M*pi0M + 2*(pimpi0E - pimpi0P));
  // number of particles (3) (all new)
  nGamma = (Float_t) nGamma;
  nPip = (Float_t) nPip;
  nPim = (Float_t) nPim;
}

/*** Mathematical functions ***/

Float_t ParticleMass(Float_t fPid) {
  TDatabasePDG pdg;
  return pdg.GetParticle((Int_t) fPid)->Mass();
}

Float_t CorrectEnergyStep1(Float_t fEtot, Float_t fEin, Float_t fEout, Float_t fPid, TString analyserOption) {
  // (it uses tP, very bad practice!!)
  
  // returns the true energy due to EC corrections
  // thanks to (Taisiya Mineeva - CLAS Analysis Note)
    
  Float_t fEtrue;
  Float_t fP2 = tP*tP;
  
  if (fPid == 22 && analyserOption == "Sim") {
    fEtrue = TMath::Max(fEtot, fEin+fEout)/0.272;
  } else if (fPid == 22 && analyserOption != "Sim") {
    fEtrue = TMath::Max(fEtot, fEin+fEout)/0.2806; // primitive sampling fraction for sim
  } else {
    fEtrue = TMath::Sqrt(fP2 + ParticleMass(fPid)*ParticleMass(fPid));
  }
  
  return fEtrue;
}

Float_t CorrectEnergyStep2(Float_t fEtrue, Float_t fPid, TString analyserOption) {
  
  // returns the respective corrected energy
  // thanks to (Taisiya Mineeva - CLAS Analysis Note)
  
  Float_t corrFactor;
  Float_t fEcorr;
  
  if (fPid == 22) {
    if (analyserOption == "C" || analyserOption == "Pb") {
      corrFactor = 1.129 - 0.05793/fEtrue - 1.0773e-12/(fEtrue*fEtrue);
    } else if (analyserOption == "Fe") {
      corrFactor = 1.116 - 0.09213/fEtrue + 0.01007/(fEtrue*fEtrue);
    } else if (analyserOption == "Sim") {
      corrFactor = 1.000 + 0.005/fEtrue - 0.0052/(fEtrue*fEtrue);
    }
  } else {
    corrFactor = 1.;
  }

  fEcorr = fEtrue/corrFactor;
  
  return fEcorr;
}

Float_t CorrectMomentum(Float_t fEcorr, Float_t fPi, Float_t fPid, Int_t i) {
  // (it uses tXECe, tYECe, tZECe, tvxec, tvyec and tvzec as global variables!)
   
  // returns the respective corrected momentum component for gammas
  // extracted from eta_id.cxx (Orlando Soto)

  Float_t fP[3];
  Float_t fPcorr;

  if (fPid == 22) {
    Float_t Rt = TMath::Sqrt(tXECe*tXECe + tYECe*tYECe);
    Float_t R = TMath::Sqrt(tXECe*tXECe + tYECe*tYECe + (tZECe - tvzec)*(tZECe - tvzec));
    Float_t theta_gam = TMath::ASin(Rt/R);
    Float_t phi_gam = TMath::ATan2(tYECe, tXECe);
    
    fP[0] = fEcorr*TMath::Sin(theta_gam)*TMath::Cos(phi_gam);
    fP[1] = fEcorr*TMath::Sin(theta_gam)*TMath::Sin(phi_gam);
    fP[2] = fEcorr*TMath::Cos(theta_gam);

    // (0 -> x, 1 -> y, 2 -> z)
    fPcorr = fP[i];
  } else {
    fPcorr = fPi;
  }
  
  return fPcorr;
}

Float_t PhiPQ(Float_t fPx, Float_t fPy, Float_t fPz) {
  // (it depends on tPex, tPey and tPez as global variables)
  
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
  // and converts it from radians to degrees
  fPhiPQ = hadr.Phi() * 180./(TMath::Pi());
  
  return fPhiPQ;
}

Float_t ThetaPQ(Float_t fPx, Float_t fPy, Float_t fPz) {
  // (it depends on tPex, tPey and tPez as global variables)
  
  Float_t fThetaPQ;
  
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 virt(-tPex, -tPey, kEbeam - tPez);

  // apparently, the angle between these two vectors is the theta angle
  // and this makes perfect sense if one draws it
  fThetaPQ = virt.Angle(hadr) * 180./(TMath::Pi());

  return fThetaPQ;
}

Float_t DeltaTheta(Float_t fPx, Float_t fPy, Float_t fPz) {
  // (it depends on tPex, tPey and tPez as global variables)

  Float_t deltaTheta;

  TVector3 part(fPx, fPy, fPz);
  TVector3 elec(tPex, tPey, tPez);
  
  deltaTheta = elec.Angle(part)*180./TMath::Pi();

  return deltaTheta;
}

Float_t BettaCalc(Float_t fP, Float_t fPid) {
  // (uses wP and wM as global variables when pid=223 (omega), very bad practice!)
  
  Float_t fM = ParticleMass(fPid);
  Float_t fBettaCalc;

  if (fPid == 223) fBettaCalc = fP/TMath::Sqrt(wP*wP + wM*wM);
  else fBettaCalc = fP/TMath::Sqrt(fP*fP + fM*fM);

  return fBettaCalc;
}
