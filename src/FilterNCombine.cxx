/*****************************************/
/*  FilterNCombine.cxx                   */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

#include "FilterNCombine.h"

/*** Constants ***/

Float_t kEbeam = 5.014;

/*** Global variables ***/

/*** Input variables ***/

// (83 variables for data/simrec)
// electron (40)
Float_t tQ2, tW, tNu, tXb, tYb, tvxe, tvye, tvze, tSectorEl, tTargType, tPex, tPey, tPez, tPe, tBettaEl, tEtote, tEine, tEoute, tvxec, tvyec, tvzec, tXECe, tYECe, tZECe;
Float_t tStatDCEl, tDCStatusEl, tStatECEl, tECStatusEl, tTimeECEl, tPathECEl, tChi2ECEl, tStatSCEl, tSCStatusEl, tTimeSCEl, tPathSCEl, tStatCCEl, tCCStatusEl, tNpheEl, tChi2CCEl, tStatusEl;
// particle (42)
Float_t tZh, tThetaPQ, tPt2, tPl2, tPhiPQ, tMx2, tT, tvxh, tvyh, tvzh, tSector, tPx, tPy, tPz, tP, tBetta, tMass2, tEtot, tEin, tEout, tXEC, tYEC, tZEC, tpid, tT4, tdeltaZ;
Float_t tStatDC, tDCStatus, tStatEC, tECStatus, tTimeEC, tPathEC, tChi2EC, tStatSC, tSCStatus, tTimeSC, tPathSC, tStatCC, tCCStatus, tNphe, tChi2CC, tStatus;
// event (1)
Float_t tevnt;
// (34 variables for montecarlo)
// electron (15)
Float_t mc_tQ2, mc_tW, mc_tNu, mc_tXb, mc_tYb, mc_tvxe, mc_tvye, mc_tvze, mc_tSectorEl, mc_tTargType, mc_tPex, mc_tPey, mc_tPez, mc_tPe, mc_tBettaEl;
// particle (19)
Float_t mc_tZh, mc_tThetaPQ, mc_tPt2, mc_tPl2, mc_tPhiPQ, mc_tMx2, mc_tT, mc_tvxh, mc_tvyh, mc_tvzh, mc_tSector, mc_tPx, mc_tPy, mc_tPz, mc_tP, mc_tBetta, mc_tMass2, mc_tpid, mc_tdeltaZ;

/*** Output/original variables ***/

// (101 variables for data)
// electron (41)
Float_t oQ2, oW, oNu, oXb, oYb, oXe, oYe, oZe, oSectorEl, oTargType, oPex, oPey, oPez, oPe, oBettaEl, oEtote, oEine, oEoute, oXec, oYec, oZec, oXECe, oYECe, oZECe;
Float_t oP2e;
Float_t oStatDCEl, oDCStatusEl, oStatECEl, oECStatusEl, oTimeECEl, oPathECEl, oChi2ECEl, oStatSCEl, oSCStatusEl, oTimeSCEl, oPathSCEl, oStatCCEl, oCCStatusEl, oNpheEl, oChi2CCEl, oStatusEl;
// particle (60) (16 + 3*6 + 10 + 16)
Float_t ovxh, ovyh, ovzh, oSector, oBetta, oMass2, oEtot, oEin, oEout, oXEC, oYEC, oZEC, oPid, oT4, odeltaZ, oM;
Float_t oE_prev, oPx_prev, oPy_prev, oPz_prev, oP2_prev, oP_prev;
Float_t oE_true, oPx_true, oPy_true, oPz_true, oP2_true, oP_true;
Float_t oE_corr, oPx_corr, oPy_corr, oPz_corr, oP2_corr, oP_corr;
Float_t oZ, oThetaPQ, oPt2, oPl2, oPhiPQ, oMx2, oT, oCosThetaPQ, oBettaCalc, odeltaTheta;
Float_t oStatDC, oDCStatus, oStatEC, oECStatus, oTimeEC, oPathEC, oChi2EC, oStatSC, oSCStatus, oTimeSC, oPathSC, oStatCC, oCCStatus, oNphe, oChi2CC, oStatus;
// event (2)
Float_t oEvent;
Float_t oEntry; // debug purposes
// (41 variables for montecarlo)
// electron (16)
Float_t mc_oQ2, mc_oW, mc_oNu, mc_oXb, mc_oYb, mc_oXe, mc_oYe, mc_oZe, mc_oSectorEl, mc_oTargType, mc_oPex, mc_oPey, mc_oPez, mc_oPe, mc_oBettaEl;
Float_t mc_oP2e;
// particle (25)
Float_t mc_ovxh, mc_ovyh, mc_ovzh, mc_oSector, mc_oBetta, mc_oMass2, mc_oPid, mc_odeltaZ, mc_oM;
Float_t mc_oE, mc_oPx, mc_oPy, mc_oPz, mc_oP2, mc_oP;
Float_t mc_oZ, mc_oThetaPQ, mc_oPt2, mc_oPl2, mc_oPhiPQ, mc_oMx2, mc_oT, mc_oCosThetaPQ, mc_oBettaCalc, mc_odeltaTheta;

/*** Output/mix variables ***/

// (194 variables for data)
// electron (41)
Float_t mQ2, mW, mNu, mXb, mYb, mXe, mYe, mZe, mSectorEl, mTargType, mPex, mPey, mPez, mPe, mBettaEl, mEtote, mEine, mEoute, mXec, mYec, mZec, mXECe, mYECe, mZECe;
Float_t mP2e;
Float_t mStatDCEl, mDCStatusEl, mStatECEl, mECStatusEl, mTimeECEl, mPathECEl, mChi2ECEl, mStatSCEl, mSCStatusEl, mTimeSCEl, mPathSCEl, mStatCCEl, mCCStatusEl, mNpheEl, mChi2CCEl, mStatusEl;
// particles (60) (16 + 3*6 + 10 + 16)
Float_t mvxh[4], mvyh[4], mvzh[4], mSector[4], mBetta[4], mMass2[4], mEtot[4], mEin[4], mEout[4], mXEC[4], mYEC[4], mZEC[4], mPid[4], mT4[4], mdeltaZ[4], mM[4];
Float_t mE_prev[4], mPx_prev[4], mPy_prev[4], mPz_prev[4], mP2_prev[4], mP_prev[4];
Float_t mE_true[4], mPx_true[4], mPy_true[4], mPz_true[4], mP2_true[4], mP_true[4];
Float_t mE_corr[4], mPx_corr[4], mPy_corr[4], mPz_corr[4], mP2_corr[4], mP_corr[4];
Float_t mZ[4], mThetaPQ[4], mPt2[4], mPl2[4], mPhiPQ[4], mMx2[4], mT[4], mCosThetaPQ[4], mBettaCalc[4], mdeltaTheta[4];
Float_t mStatDC[4], mDCStatus[4], mStatEC[4], mECStatus[4], mTimeEC[4], mPathEC[4], mChi2EC[4], mStatSC[4];
Float_t mSCStatus[4], mTimeSC[4], mPathSC[4], mStatCC[4], mCCStatus[4], mNphe[4], mChi2CC[4], mStatus[4];
// pi0 (24) (3*8new)
Float_t pi0Px_prev, pi0Py_prev, pi0Pz_prev, pi0P2_prev, pi0P_prev, pi0E_prev, pi0M_prev, pi0Theta_prev;
Float_t pi0Px_true, pi0Py_true, pi0Pz_true, pi0P2_true, pi0P_true, pi0E_true, pi0M_true, pi0Theta_true;
Float_t pi0Px_corr, pi0Py_corr, pi0Pz_corr, pi0P2_corr, pi0P_corr, pi0E_corr, pi0M_corr, pi0Theta_corr;
// omega (57) (3*19new)
Float_t wPx_prev, wPy_prev, wPz_prev, wP_prev, wP2_prev, wE_prev;
Float_t wZ_prev, wCosThetaPQ_prev, wThetaPQ_prev, wPt2_prev, wPl2_prev, wPhiPQ_prev, wMx2_prev, wT_prev, wBettaCalc_prev, wdeltaTheta_prev, wD_prev, wM_prev, wSD_prev;
Float_t wPx_true, wPy_true, wPz_true, wP_true, wP2_true, wE_true;
Float_t wZ_true, wCosThetaPQ_true, wThetaPQ_true, wPt2_true, wPl2_true, wPhiPQ_true, wMx2_true, wT_true, wBettaCalc_true, wdeltaTheta_true, wD_true, wM_true, wSD_true;
Float_t wPx_corr, wPy_corr, wPz_corr, wP_corr, wP2_corr, wE_corr;
Float_t wZ_corr, wCosThetaPQ_corr, wThetaPQ_corr, wPt2_corr, wPl2_corr, wPhiPQ_corr, wMx2_corr, wT_corr, wBettaCalc_corr, wdeltaTheta_corr, wD_corr, wM_corr, wSD_corr;
// crossed terms (9)
Float_t pippimP, pippimE, pippimM;
Float_t pippi0P, pippi0E, pippi0M;
Float_t pimpi0P, pimpi0E, pimpi0M;
// number of particles (3)
Float_t nPip, nPim, nGamma;
// event related (2)
Float_t mEvent;
Float_t mEntry[4];
// (72 variables for montecarlo)
// electron (16)
Float_t mc_mQ2, mc_mW, mc_mNu, mc_mXb, mc_mYb, mc_mXe, mc_mYe, mc_mZe, mc_mSectorEl, mc_mTargType, mc_mPex, mc_mPey, mc_mPez, mc_mPe, mc_mBettaEl;
Float_t mc_mP2e;
// particle (25)
Float_t mc_mvxh[4], mc_mvyh[4], mc_mvzh[4], mc_mSector[4], mc_mBetta[4], mc_mMass2[4], mc_mPid[4], mc_mdeltaZ[4], mc_mM[4];
Float_t mc_mE[4], mc_mPx[4], mc_mPy[4], mc_mPz[4], mc_mP2[4], mc_mP[4];
Float_t mc_mZ[4], mc_mThetaPQ[4], mc_mPt2[4], mc_mPl2[4], mc_mPhiPQ[4], mc_mMx2[4], mc_mT[4], mc_mCosThetaPQ[4], mc_mBettaCalc[4], mc_mdeltaTheta[4];
// pi0 (8)
Float_t mc_pi0Px, mc_pi0Py, mc_pi0Pz, mc_pi0P2, mc_pi0P, mc_pi0E, mc_pi0M, mc_pi0Theta;
// omega (19)
Float_t mc_wPx, mc_wPy, mc_wPz, mc_wP, mc_wP2, mc_wE;
Float_t mc_wZ, mc_wCosThetaPQ, mc_wThetaPQ, mc_wPt2, mc_wPl2, mc_wPhiPQ, mc_wMx2, mc_wT, mc_wBettaCalc, mc_wdeltaTheta, mc_wD, mc_wM, mc_wSD;
// crossed terms (9)
Float_t mc_pippimP, mc_pippimE, mc_pippimM;
Float_t mc_pippi0P, mc_pippi0E, mc_pippi0M;
Float_t mc_pimpi0P, mc_pimpi0E, mc_pimpi0M;
// number of particles (3)
Float_t mc_nPip, mc_nPim, mc_nGamma;

/*** Options ***/

TString targetOption;
TString rnOption;
Int_t   simFlag = 0;
TString analyserOption; // for photon's energy correction

TString treeName;

TString outFile;

// input
TString inputFile;

/*** Declaration of functions ***/

int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();
  
  /*** Init tree ***/
  
  // hadrons (t - tree)
  TChain *t = new TChain();
  t->Add(inputFile + "/" + treeName); // input

  SetInputBranches(t);
  
  /*** Output settings ***/
  
  TFile *rootFile = new TFile(outFile, "RECREATE", "Omega Meson Filtered Combinations"); // output

  TTree *tOriginal = new TTree("original", "Original particles");
  SetOutputBranches(tOriginal, "original");

  TTree *tMix = new TTree("mix", "Combination of particles");
  SetOutputBranches(tMix, "mix");
  
  /*** START FILTERING ***/

  // counting variables
  Int_t nPipThisEvent = 0;
  Int_t nPimThisEvent = 0;
  Int_t nGammaThisEvent = 0;
  Int_t nCombThisEvent = 0;

  Int_t nOmega = 0;
  Int_t nAtLeastOmega = 0;
  
  // mc counting variables
  Int_t nMCPipThisEvent = 0;
  Int_t nMCPimThisEvent = 0;
  Int_t nMCGammaThisEvent = 0;
  Int_t nMCCombThisEvent = 0;

  Int_t nMCOmega = 0;
  Int_t nAtLeastMCOmega = 0;

  // combination vectors!
  std::vector<std::vector <int>> combVector;
  std::vector<std::vector <int>> mc_combVector;
  
  /*** START ***/
  
  // define entrylist
  TEntryList *l;

  // on the loop
  Int_t start = (Int_t) t->GetMinimum("evnt");
  Int_t finish = (Int_t) t->GetMaximum("evnt");

  // std::cout << "!! start: " << start << " - finish: " << finish << std::endl;
  
  // loop in events
  // i = event number
  for (Int_t i = start; i <= finish; i++) {
    
    // std::cout << "Current event number: " << i << std::endl;
    // std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    
    TString isFromSameEvent = Form("evnt == %d", i);;
    TString listName = Form("elist_%d", i);

    // selects all entries from the same event
    t->Draw(">>" + listName, isFromSameEvent, "entrylist");
    l = (TEntryList*) gDirectory->Get(listName);
    t->SetEntryList(l);
      
    // looks at the entries (particles) of the current event
    // j = iterator, jj = real entry number
    for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
      Int_t jj = t->GetEntryNumber(j);
      t->GetEntry(jj);
      // std::cout << "  Entry number: " << jj << std::endl;
      // std::cout << "  pid:          " << tpid << std::endl;
      // if (simFlag) std::cout << "  mc_pid:       " << mc_tpid << std::endl;
      // std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
      // count the data/simrec particles
      if (tpid == (Float_t) 211) nPipThisEvent++;
      if (tpid == (Float_t) -211) nPimThisEvent++;
      if (tpid == (Float_t) 22) nGammaThisEvent++;
      // count the gsim particles
      if (mc_tpid == (Float_t) 211) nMCPipThisEvent++;
      if (mc_tpid == (Float_t) -211) nMCPimThisEvent++;
      if (mc_tpid == (Float_t) 22) nMCGammaThisEvent++;
    }
    
    // show counts
    // std::cout << "  nPip     = " << nPipThisEvent << std::endl;
    // std::cout << "  nPim     = " << nPimThisEvent << std::endl;
    // std::cout << "  nGamma   = " << nGammaThisEvent << std::endl;
    if (simFlag) {
      // std::cout << "  nMCPip   = " << nMCPipThisEvent << std::endl;
      // std::cout << "  nMCPim   = " << nMCPimThisEvent << std::endl;
      // std::cout << "  nMCGamma = " << nMCGammaThisEvent << std::endl;
    }
    // std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // (as you can see, these conditions are not exclusive)
    // candidate appeared for data/simrec
    if (nPipThisEvent >= 1 && nPimThisEvent >= 1 && nGammaThisEvent >= 2) {
      nAtLeastOmega++;
      nCombThisEvent = TMath::Binomial(nPipThisEvent, 1)*TMath::Binomial(nPimThisEvent, 1)*TMath::Binomial(nGammaThisEvent, 2);
      nOmega += nCombThisEvent;
    }

    // candidate appeared for gsim
    if (nMCPipThisEvent >= 1 && nMCPimThisEvent >= 1 && nMCGammaThisEvent >= 2) {
      nAtLeastMCOmega++;
      nMCCombThisEvent = TMath::Binomial(nMCPipThisEvent, 1)*TMath::Binomial(nMCPimThisEvent, 1)*TMath::Binomial(nMCGammaThisEvent, 2);
      nMCOmega += nMCCombThisEvent;
    }

    if (!simFlag) {
      // std::cout << "  There are " << nCombThisEvent << " omegas!" << std::endl;
    } else {
      // std::cout << "  There are " << nCombThisEvent << " reconstructed omegas!" << std::endl;
      // std::cout << "  There are " << nMCCombThisEvent << " generated omegas!" << std::endl;
    }
    // std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    /*** ORIGINAL ***/

    // saves all information from the original particles from an approved event, with no mixing
    // warning: all the hadronic variables correspond to the respective hadron, nothing more
    
    if (nCombThisEvent > 0 || nMCCombThisEvent > 0) {

      // looks at the entries (particles) of the current event
      // j = iterator, jj = real entry number
      for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
	Int_t jj = t->GetEntryNumber(j);
	t->GetEntry(jj);

	AssignOriginalVariables(jj, nCombThisEvent); // AOV(Int_t entry, Int_t nCombInSimrec)	
	tOriginal->Fill();

      } // end of particles loop
    } // end of candidate condition

    // std::cout << "  !! Fill original ready!" << std::endl;
    
    /*** THE MIXING ***/

    // PART 1: obtain & keep combinations from data/simrec
    
    // tag
    Int_t jPip = 0;
    Int_t jPim = 0;
    Int_t jGamma1 = 0;
    Int_t jGamma2 = 0;
    
    Int_t partialComb = 0;
    Int_t partialLim = nGammaThisEvent - 1;
    Int_t partialFlag = 1;
    
    if (nCombThisEvent > 0) {
      for (Int_t iPip = 0; iPip < TMath::Binomial(nPipThisEvent, 1); iPip++) {
	
	// find and tag pip (loop in particles)
	// j = iterator, jj = real entry number
	for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
	  Int_t jj = t->GetEntryNumber(j);
	  t->GetEntry(jj);
	  if (tpid == (Float_t) 211 && jj > jPip) {
	    jPip = jj;             // tag pip
	    j = (Int_t) l->GetN(); // break search
	  }
	}
	
	// force a new beginning for the other particles
	jPim = 0;
	jGamma1 = 0;
	jGamma2 = 0;
	
	for (Int_t iPim = 0; iPim < TMath::Binomial(nPimThisEvent, 1); iPim++) {
	  
	  // find and tag pim
	  // j = iterator, jj = real entry number
	  for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
	    Int_t jj = t->GetEntryNumber(j);
	    t->GetEntry(jj);
	    if (tpid == (Float_t) -211 && jj > jPim) {
	      jPim = jj;             // tag pim
	      j = (Int_t) l->GetN(); // break search
	    }
	  }
	  
	  // force a new beginning for the other particles
	  jGamma1 = 0;
	  jGamma2 = 0;	  
	  
	  for (Int_t iGamma = 0; iGamma < TMath::Binomial(nGammaThisEvent, 2); iGamma++) {
	    
	    // debug
	    if (iGamma == 0) {
	      partialComb = 0;
	      partialLim = nGammaThisEvent - 1;
	      partialFlag = 1;
	    }
	    
	    // the big condition
	    if (partialFlag) {
	      
	      // find and tag gamma1
	      // jj = real entry number, j = iterator
	      for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
		Int_t jj = t->GetEntryNumber(j);
		t->GetEntry(jj);
		if (tpid == (Float_t) 22 && jj > jGamma1) { // excludes previous gamma1
		  jGamma1 = jj;          // tag gamma1
		  j = (Int_t) l->GetN(); // break search for j
		}
	      }
	      jGamma2 = 0; // resets gamma2
	      partialFlag = 0;
	    }
	    
	    // find and tag gamma2
	    // jj = real entry number, j = iterator
	    for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
	      Int_t jj = t->GetEntryNumber(j);
	      t->GetEntry(jj);
	      if (tpid == (Float_t) 22 && jj > jGamma2 && jj > jGamma1) { // excludes gamma1 and previous gamma2
		jGamma2 = jj;          // tag gamma2
		j = (Int_t) l->GetN(); // break search for j
	      }
	    }
	    
	    // fix partial comb
	    partialComb++;
	    if (partialComb == partialLim && partialLim > 1) {
	      partialComb = 0;
	      partialLim--;
	      partialFlag = 1;
	    }

	    // fill vector
	    combVector.push_back({jGamma1, jGamma2, jPip, jPim});

	  } // end of loop in gammas
	  
	} // end of loop in pi-
	
      } // end of loop in pi+

    } // end of at-least-one-omega condition

    // std::cout << "  !! Obtain & keep combinations from data/simrec ready!" << std::endl;
    
    // PART 2: obtain & keep combinations from gsim

    // tag
    jPip = 0;
    jPim = 0;
    jGamma1 = 0;
    jGamma2 = 0;
    
    partialComb = 0;
    partialLim = nMCGammaThisEvent - 1;
    partialFlag = 1;

    if (simFlag && nMCCombThisEvent > 0) {
      for (Int_t iPip = 0; iPip < TMath::Binomial(nMCPipThisEvent, 1); iPip++) {
	
	// find and tag pip (loop in particles)
	// j = iterator, jj = real entry number
	for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
	  Int_t jj = t->GetEntryNumber(j);
	  t->GetEntry(jj);
	  if (mc_tpid == (Float_t) 211 && jj > jPip) {
	    jPip = jj;             // tag pip
	    j = (Int_t) l->GetN(); // break search
	  }
	}
	
	// force a new beginning for the other particles
	jPim = 0;
	jGamma1 = 0;
	jGamma2 = 0;
	
	for (Int_t iPim = 0; iPim < TMath::Binomial(nMCPimThisEvent, 1); iPim++) {
	  
	  // find and tag pim
	  // j = iterator, jj = real entry number
	  for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
	    Int_t jj = t->GetEntryNumber(j);
	    t->GetEntry(jj);
	    if (mc_tpid == (Float_t) -211 && jj > jPim) {
	      jPim = jj;             // tag pim
	      j = (Int_t) l->GetN(); // break search
	    }
	  }
	  
	  // force a new beginning for the other particles
	  jGamma1 = 0;
	  jGamma2 = 0;	  
	  
	  for (Int_t iGamma = 0; iGamma < TMath::Binomial(nMCGammaThisEvent, 2); iGamma++) {
	    
	    // debug
	    if (iGamma == 0) {
	      partialComb = 0;
	      partialLim = nMCGammaThisEvent - 1;
	      partialFlag = 1;
	    }
	    
	    // the big condition
	    if (partialFlag) {
	      
	      // find and tag gamma1
	      // jj = real entry number, j = iterator
	      for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
		Int_t jj = t->GetEntryNumber(j);
		t->GetEntry(jj);
		if (mc_tpid == (Float_t) 22 && jj > jGamma1) { // excludes previous gamma1
		  jGamma1 = jj;          // tag gamma1
		  j = (Int_t) l->GetN(); // break search for j
		}
	      }
	      jGamma2 = 0; // resets gamma2
	      partialFlag = 0;
	    }
	  
	    // find and tag gamma2
	    // jj = real entry number, j = iterator
	    for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
	      Int_t jj = t->GetEntryNumber(j);
	      t->GetEntry(jj);
	      if (mc_tpid == (Float_t) 22 && jj > jGamma2 && jj > jGamma1) { // excludes gamma1 and previous gamma2
	      	jGamma2 = jj;          // tag gamma2
	      	j = (Int_t) l->GetN(); // break search for j
	      }
	    }
	    
	    // fix partial comb
	    partialComb++;
	    if (partialComb == partialLim && partialLim > 1) {
	      partialComb = 0;
	      partialLim--;
	      partialFlag = 1;
	    }

	    // fill vector
	    mc_combVector.push_back({jGamma1, jGamma2, jPip, jPim});

	  } // end of loop in gammas
	  
	} // end of loop in pi-
	
      } // end of loop in pi+

    } // end of at-least-one-omega condition

    // std::cout << "  !! Obtain & keep combinations from gsim ready!" << std::endl;
    
    // PART 3: fill

    /*
    if (!simFlag) {
      std::cout << "  candidates for data:" << std::endl;
      for (Int_t c = 0; c < nCombThisEvent; c++) std::cout << "  {" << combVector[c][0] << ", " << combVector[c][1] << ", "  << combVector[c][2] << ", " << combVector[c][3] << "}" << std::endl;
    } else {
      std::cout << "  candidates for simrec:" << std::endl;
      for (Int_t c = 0; c < nCombThisEvent; c++) std::cout << "  {" << combVector[c][0] << ", " << combVector[c][1] << ", "  << combVector[c][2] << ", " << combVector[c][3] << "}" << std::endl;
      std::cout << "  candidates for gsim:" << std::endl;
      for (Int_t c = 0; c < nMCCombThisEvent; c++) std::cout << "  {" << mc_combVector[c][0] << ", " << mc_combVector[c][1] << ", "  << mc_combVector[c][2] << ", " << mc_combVector[c][3] << "}" << std::endl;
      std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    }
    */
    
    // extract
    for (Int_t cc = 0; cc < TMath::Max(nCombThisEvent, nMCCombThisEvent); cc++) { // loop on combinations
      for (Int_t pp = 0; pp < 4; pp++) { // loop on particles

	// about AMV:
	// case 1: (no simrec in the entry)
	// we have to fill two vectors... this step will fill the MC vector of particles, and fill the REC vector of particles with null values
	// eg: {gammaA, gammaB, pip, pim} - {null}
	//     {gammaA, gammaC, pip, pim} - {null}
	//     {gammaB, gammaC, pip, pim} - {null}
	// OK!!
	// 
	// case 2: (there is simrec in the entry!)
	// this step will fill the MC vector of particles and fill the REC vector of particles
	// eg2: {gammaA, gammaB, pip, pim} - {rec gammaA, rec gammaB, rec pip, rec pim}
	//      {gammaA, gammaC, pip, pim} - {null value}
	//      {gammaB, gammaC, pip, pim} - {null value}
	// OK!!

	// obvious conditions for data, necessary conditions for simrec
	if (nCombThisEvent && cc < nCombThisEvent) {
	  t->GetEntry(combVector[cc][pp]);
	  AssignMixVariables(combVector[cc][pp], pp); // AMV(entry, index) - inside is the condition of a valid pid
	} else {
	  NullMixSIMRECVariables(pp); // NMSV()
	}

	// gsim
        if (simFlag && cc < nMCCombThisEvent) {
	  t->GetEntry(mc_combVector[cc][pp]);
	  AssignMixGSIMVariables(mc_combVector[cc][pp], pp); // AMGV(entry, index)
	}
	
      } // end of loop in particles

      // after assigning each decay particle, assign the composite variables
      // data & simrec
      if (nCombThisEvent) { 
	AssignPi0Variables();
	AssignOmegaVariables();
	AssignMoreVariables(nGammaThisEvent, nPipThisEvent, nPimThisEvent);
      }
      
      // gsim
      if (simFlag){
	AssignPi0GSIMVariables();
	AssignOmegaGSIMVariables();
	AssignMoreGSIMVariables(nMCGammaThisEvent, nMCPipThisEvent, nMCPimThisEvent);
      }
      
      tMix->Fill();      
    } // end of loop in combinations

    // std::cout << "  !! Fill combinations in mix ready!" << std::endl;
    
    // reset count variables
    nPipThisEvent = 0;
    nPimThisEvent = 0;
    nGammaThisEvent = 0;
    nCombThisEvent = 0;
    
    nMCPipThisEvent = 0;
    nMCPimThisEvent = 0;
    nMCGammaThisEvent = 0;
    nMCCombThisEvent = 0;

    // reset vectors!
    combVector.clear();
    mc_combVector.clear();

    // jump to next event number (exclusively for data)
    if (!simFlag) {
      // get last entry from current event list
      Int_t ii = t->GetEntryNumber(l->GetN() - 1);
      t->GetEntry(ii + 1);
      // stand in first entry of the next event
      i = (Int_t) tevnt - 1;
    }

    // set tree back to original tree
    t->SetEntryList(0);

    // clean some memory
    gDirectory->Delete(listName + ";1");
    rootFile->Delete(listName);
    
    // std::cout << "  !! Finished event" << std::endl;
    // std::cout << std::endl;
  } // end of loop in events

  /*** Writing tree ***/
  
  rootFile->Write();
  rootFile->Close();

  std::cout << "This file has been created: " << outFile << std::endl;
  
  return 0;
}

/*** Input-related functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./FilterNCombine -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:dSr:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'd': simFlag = 0; break;
    case 'S': simFlag = 1; break;
    case 'r': rnOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./FilterNCombine -h to print help." << std::endl;
      exit(0);
      break;
    }
}

void assignOptions() {
  // for data type
  if (!simFlag) {
    treeName = "ntuple_data";
    analyserOption = targetOption;
  } else if (simFlag) {
    treeName = "ntuple_sim";
    analyserOption = "Sim";
  }
  // for everyone, at node dir
  inputFile = "pruned" + targetOption + "_" + rnOption + ".root";
  outFile = "comb" + targetOption + "_" + rnOption + ".root";
}

void printUsage() {
  std::cout << "FilterNCombine program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -h" << std::endl;
  std::cout << "    prints this message and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -t[D, C, Fe, Pb]" << std::endl;
  std::cout << "    filters the respective target" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -d" << std::endl;
  std::cout << "    filters data" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -S" << std::endl;
  std::cout << "    filters sim" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -r[run number]" << std::endl;
  std::cout << "    selects run number" << std::endl;
  std::cout << "    numbering scheme for input files = pruned<target>_<run number>.root" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing FilterNCombine program. The chosen parameters are: " << std::endl;
  std::cout << "  targetOption   = " << targetOption << std::endl;
  std::cout << "  rnOption       = " << rnOption << std::endl;
  std::cout << "  simFlag        = " << simFlag << std::endl;
  std::cout << std::endl;
}
