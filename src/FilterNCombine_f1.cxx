/*****************************************/
/*  FilterNCombine_f1.cxx                */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// Exclusive for Data, we are searching for f1(1285) candidates
// from the 4 pion decay channel: f1 -> 2pi0 pi+ pi-

#include "FilterNCombine_f1.h"

/*** Constants ***/

Float_t kEbeam = 5.014;

/*** Global variables ***/

/*** Input variables ***/

// (83 variables for data)
// electron (40)
Float_t tQ2, tW, tNu, tXb, tYb, tvxe, tvye, tvze, tSectorEl, tTargType, tPex, tPey, tPez, tPe, tBettaEl, tEtote, tEine, tEoute, tvxec, tvyec, tvzec, tXECe, tYECe, tZECe;
Float_t tStatDCEl, tDCStatusEl, tStatECEl, tECStatusEl, tTimeECEl, tPathECEl, tChi2ECEl, tStatSCEl, tSCStatusEl, tTimeSCEl, tPathSCEl, tStatCCEl, tCCStatusEl, tNpheEl, tChi2CCEl, tStatusEl;
// particle (42)
Float_t tZh, tThetaPQ, tPt2, tPl2, tPhiPQ, tMx2, tT, tvxh, tvyh, tvzh, tSector, tPx, tPy, tPz, tP, tBetta, tMass2, tEtot, tEin, tEout, tXEC, tYEC, tZEC, tpid, tT4, tdeltaZ;
Float_t tStatDC, tDCStatus, tStatEC, tECStatus, tTimeEC, tPathEC, tChi2EC, tStatSC, tSCStatus, tTimeSC, tPathSC, tStatCC, tCCStatus, tNphe, tChi2CC, tStatus;
// event (1)
Float_t tevnt;

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

/*** Output/mix variables ***/

// (194 variables for data)
// electron (41)
Float_t mQ2, mW, mNu, mXb, mYb, mXe, mYe, mZe, mSectorEl, mTargType, mPex, mPey, mPez, mPe, mBettaEl, mEtote, mEine, mEoute, mXec, mYec, mZec, mXECe, mYECe, mZECe;
Float_t mP2e;
Float_t mStatDCEl, mDCStatusEl, mStatECEl, mECStatusEl, mTimeECEl, mPathECEl, mChi2ECEl, mStatSCEl, mSCStatusEl, mTimeSCEl, mPathSCEl, mStatCCEl, mCCStatusEl, mNpheEl, mChi2CCEl, mStatusEl;
// particles (60) (16 + 3*6 + 10 + 16)
Float_t mvxh[6], mvyh[6], mvzh[6], mSector[6], mBetta[6], mMass2[6], mEtot[6], mEin[6], mEout[6], mXEC[6], mYEC[6], mZEC[6], mPid[6], mT4[6], mdeltaZ[6], mM[6];
Float_t mE_prev[6], mPx_prev[6], mPy_prev[6], mPz_prev[6], mP2_prev[6], mP_prev[6];
Float_t mE_true[6], mPx_true[6], mPy_true[6], mPz_true[6], mP2_true[6], mP_true[6];
Float_t mE_corr[6], mPx_corr[6], mPy_corr[6], mPz_corr[6], mP2_corr[6], mP_corr[6];
Float_t mZ[6], mThetaPQ[6], mPt2[6], mPl2[6], mPhiPQ[6], mMx2[6], mT[6], mCosThetaPQ[6], mBettaCalc[6], mdeltaTheta[6];
Float_t mStatDC[6], mDCStatus[6], mStatEC[6], mECStatus[6], mTimeEC[6], mPathEC[6], mChi2EC[6], mStatSC[6];
Float_t mSCStatus[6], mTimeSC[6], mPathSC[6], mStatCC[6], mCCStatus[6], mNphe[6], mChi2CC[6], mStatus[6];
// pi0A (24) (3*8new)
Float_t pi0A_Px_prev, pi0A_Py_prev, pi0A_Pz_prev, pi0A_P2_prev, pi0A_P_prev, pi0A_E_prev, pi0A_M_prev, pi0A_Theta_prev;
Float_t pi0A_Px_true, pi0A_Py_true, pi0A_Pz_true, pi0A_P2_true, pi0A_P_true, pi0A_E_true, pi0A_M_true, pi0A_Theta_true;
Float_t pi0A_Px_corr, pi0A_Py_corr, pi0A_Pz_corr, pi0A_P2_corr, pi0A_P_corr, pi0A_E_corr, pi0A_M_corr, pi0A_Theta_corr;
// pi0B (24) (3*8new)
Float_t pi0B_Px_prev, pi0B_Py_prev, pi0B_Pz_prev, pi0B_P2_prev, pi0B_P_prev, pi0B_E_prev, pi0B_M_prev, pi0B_Theta_prev;
Float_t pi0B_Px_true, pi0B_Py_true, pi0B_Pz_true, pi0B_P2_true, pi0B_P_true, pi0B_E_true, pi0B_M_true, pi0B_Theta_true;
Float_t pi0B_Px_corr, pi0B_Py_corr, pi0B_Pz_corr, pi0B_P2_corr, pi0B_P_corr, pi0B_E_corr, pi0B_M_corr, pi0B_Theta_corr;
// f1 (54) (3*18new)
Float_t wPx_prev, wPy_prev, wPz_prev, wP_prev, wP2_prev, wE_prev;
Float_t wZ_prev, wCosThetaPQ_prev, wThetaPQ_prev, wPt2_prev, wPl2_prev, wPhiPQ_prev, wMx2_prev, wT_prev, wBettaCalc_prev, wdeltaTheta_prev, wM_prev;
Float_t wPx_true, wPy_true, wPz_true, wP_true, wP2_true, wE_true;
Float_t wZ_true, wCosThetaPQ_true, wThetaPQ_true, wPt2_true, wPl2_true, wPhiPQ_true, wMx2_true, wT_true, wBettaCalc_true, wdeltaTheta_true, wM_true;
Float_t wPx_corr, wPy_corr, wPz_corr, wP_corr, wP2_corr, wE_corr;
Float_t wZ_corr, wCosThetaPQ_corr, wThetaPQ_corr, wPt2_corr, wPl2_corr, wPhiPQ_corr, wMx2_corr, wT_corr, wBettaCalc_corr, wdeltaTheta_corr, wM_corr;
// number of particles (3)
Float_t nPip, nPim, nGamma;
// event related (2)
Float_t mEvent;
Float_t mEntry[6];

/*** Options ***/

TString targetOption;
TString rnOption;
TString analyserOption; // for photon's energy correction

TString outFile;

// input
TString inputFile;

/*** Declaration of functions ***/

int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  // measure time
  // auto begin = Clock::now();
  
  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();
  
  /*** Init tree ***/
  
  // hadrons (t - tree)
  TChain *t = new TChain();
  t->Add(inputFile + "/ntuple_data"); // input

  SetInputBranches(t);
  
  /*** Output settings ***/
  
  TFile *rootFile = new TFile(outFile, "RECREATE", "f1(1285) Filtered Combinations"); // output

  TTree *tOriginal = new TTree("original", "Original particles");
  SetOutputBranches(tOriginal, "original");

  TTree *tMix = new TTree("mix", "Combination of particles");
  SetOutputBranches(tMix, "mix");
  
  /*** START FILTERING ***/

  // counting variables
  Int_t nPipThisEvent = 0;
  Int_t nPimThisEvent = 0;
  Int_t nGammaThisEvent = 0;
  Int_t nParticles = 0;

  Int_t nCombThisEvent = 0;

  Int_t nf1 = 0;
  Int_t nAtLeastf1 = 0;
  
  // combination vectors for the 3 possible f1
  std::vector<std::vector <int>> combVectorX;
  std::vector<std::vector <int>> combVectorY;
  std::vector<std::vector <int>> combVectorZ;
  
  /*** START ***/
  
  Int_t Ne = (Int_t) t->GetEntries(); // "415" for -tC -r42011 or "(Int_t) t->GetEntries()"
  Int_t currentEvent, previousEvent;
  
  // loop in entries
  for (Int_t i = 0; i <= Ne; i++) { // "Ne"
    t->GetEntry(i);
    currentEvent = (Int_t) tevnt;
    
    // prevents repetition of same event
    if (i > 0) {
      t->GetEntry(i-1);
      previousEvent = (Int_t) tevnt;
      if (previousEvent == currentEvent) continue;
    }

    // commentary
    /*
      std::cout << "Current event number: " << currentEvent << std::endl;
      std::cout << "Current entry number: " << i << std::endl;
      std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    */
    
    // count particles in the current event
    for (Int_t j = i; j <= Ne; j++) {
      t->GetEntry(j);
      if (currentEvent == (Int_t) tevnt) {
	// commentary
	/*
	  std::cout << "  Entry number: " << j << std::endl;
	  std::cout << "  pid:          " << tpid << std::endl;
	  std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
	*/
	// count the data particles
	if (tpid == (Float_t) 211) nPipThisEvent++;
	if (tpid == (Float_t) -211) nPimThisEvent++;
	if (tpid == (Float_t) 22) nGammaThisEvent++;
      } else {
	j = Ne; // break loop, optimize
      }
    }
    
    // commentary
    /*
    std::cout << "  nPip     = " << nPipThisEvent << std::endl;
    std::cout << "  nPim     = " << nPimThisEvent << std::endl;
    std::cout << "  nGamma   = " << nGammaThisEvent << std::endl;
    std::cout << "  " << nPipThisEvent << " - " << nPimThisEvent << " - " << nGammaThisEvent << " - " << i << std::endl;
    std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    */
    
    // f1 candidate appeared for data!
    if (nPipThisEvent >= 1 && nPimThisEvent >= 1 && nGammaThisEvent >= 4) {
      nAtLeastf1++;
      nCombThisEvent = TMath::Binomial(nPipThisEvent, 1)*TMath::Binomial(nPimThisEvent, 1)*TMath::Binomial(nGammaThisEvent, 4)*3;
      nf1 += nCombThisEvent;
      nParticles = nGammaThisEvent + nPipThisEvent + nPimThisEvent;
    }

    // commentary
    /*
    std::cout << "  There are " << nCombThisEvent << " f1!" << std::endl;
    std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    */
    
    /*** ORIGINAL ***/

    // saves all information from the original particles from an approved event, with no mixing
    // warning: all the hadronic variables correspond to the respective hadron, nothing more
    if (nCombThisEvent > 0) {
      // looks at the entries (particles) of the current event
      for (Int_t j = i; j < (i+nParticles); j++) {
	t->GetEntry(j);
	AssignOriginal(j); // AOV(Int_t entry)	
	tOriginal->Fill();
      } // end of particles loop
    } // end of candidate condition

    // commentary
    // std::cout << "  !! Fill original ready!" << std::endl;

    /*** THE MIXING ***/

    // PART 1: obtain & keep combinations from data
    
    // tag
    Int_t jPip = 0;
    Int_t jPim = 0;
        
    Int_t jGammaA1 = 0;
    Int_t jGammaA2 = 0;
    Int_t jGammaB1 = 0;
    Int_t jGammaB2 = 0;
    
    Int_t partialComb_1 = 0;
    Int_t partialLim_1  = nGammaThisEvent - 1;
    Int_t partialFlag_1 = 1;

    Int_t partialComb_2 = 0;
    Int_t partialLim_2  = nGammaThisEvent - 2;
    Int_t partialFlag_2 = 1;

    Int_t partialComb_3 = 0;
    Int_t partialLim_3  = nGammaThisEvent - 3;
    Int_t partialFlag_3 = 1;

    if (nCombThisEvent > 0) {
      for (Int_t iPip = 0; iPip < TMath::Binomial(nPipThisEvent, 1); iPip++) {
	
	// find and tag pip (loop in particles)
	for (Int_t j = i; j < (i+nParticles); j++) {
	  t->GetEntry(j);
	  if (tpid == (Float_t) 211 && j > jPip) {
	    jPip = j;           // tag pip
	    j = (i+nParticles); // break search
	  }
	}
	
	// reset tag for other particles
	jPim = 0;
	jGammaA1 = 0;
	jGammaA2 = 0;
	jGammaB1 = 0;
	jGammaB2 = 0;
	
	for (Int_t iPim = 0; iPim < TMath::Binomial(nPimThisEvent, 1); iPim++) {
	  
	  // find and tag pim
	  for (Int_t j = i; j < (i+nParticles); j++) {
	    t->GetEntry(j);
	    if (tpid == (Float_t) -211 && j > jPim) {
	      jPim = j;           // tag pim
	      j = (i+nParticles); // break search
	    }
	  }
	  
	  // reset tag for other particles
	  jGammaA1 = 0;
	  jGammaA2 = 0;	  
	  jGammaB1 = 0;
	  jGammaB2 = 0;	  

	  // iGamma stands for each possible combination of 4 gammas
	  for (Int_t iGamma = 0; iGamma < TMath::Binomial(nGammaThisEvent, 4); iGamma++) {
	    
	    // debug
	    if (iGamma == 0) {
	      partialComb_1 = 0;
	      partialLim_1  = nGammaThisEvent - 1;
	      partialFlag_1 = 1;
	      
	      partialComb_2 = 0;
	      partialLim_2  = nGammaThisEvent - 2;
	      partialFlag_2 = 1;
	      
	      partialComb_3 = 0;
	      partialLim_3  = nGammaThisEvent - 3;
	      partialFlag_3 = 1;
	    }
	    
	    if (partialFlag_1) {
	      // find and tag gammaA1
	      for (Int_t j = i; j < (i+nParticles); j++) {
		t->GetEntry(j);
		if (tpid == (Float_t) 22 && j > jGammaA1) { // excludes previous gammaA1
		  jGammaA1 = j;        // tag gammaA1
		  j = (i+nParticles); // break search for j
		}
	      }
	      jGammaA2 = 0; // resets gammaA2
	      jGammaB1 = 0; // resets gammaB1
	      jGammaB2 = 0; // resets gammaB2
	      partialFlag_1 = 0;
	    }
	    
	    if (partialFlag_2) {
	      // find and tag gammaA2
	      for (Int_t j = i; j < (i+nParticles); j++) {
		t->GetEntry(j);
		if (tpid == (Float_t) 22 && j > jGammaA1 && j > jGammaA2) { // excludes gammaA1 and previous gammaA2
		  jGammaA2 = j;       // tag gammaA2
		  j = (i+nParticles); // break search for j
		}
	      }
	      jGammaB1 = 0; // resets gammaB1
	      jGammaB2 = 0; // resets gammaB2
	      partialFlag_2 = 0;	      
	    }

	    if (partialFlag_3) {
	      // find and tag gammaB1
	      for (Int_t j = i; j < (i+nParticles); j++) {
		t->GetEntry(j);
		if (tpid == (Float_t) 22 && j > jGammaA1 && j > jGammaA2 && j > jGammaB1) { // excludes gammaA1, gammaA2 and prev gammaB1
		  jGammaB1 = j;       // tag gammaB1
		  j = (i+nParticles); // break search for j
		}
	      }
	      jGammaB2 = 0; // resets gammaB2
	      partialFlag_3 = 0;	      
	    }
	    
	    // find and tag gammaB2
	    for (Int_t j = i; j < (i+nParticles); j++) {
	      t->GetEntry(j);
	      if (tpid == (Float_t) 22 && j > jGammaA1 && j > jGammaA2 && j > jGammaB1 && j > jGammaB2) { // excludes gammaA1, gammaA2, gammaB1 and prev gammaB2
		jGammaB2 = j;       // tag gammaB2
		j = (i+nParticles); // break search for j
	      }
	    }
	    
	    // fix partial comb (1)
	    partialComb_1++;
	    if (partialComb_1 == partialLim_1) {
	      partialComb_1 = 0;
	      partialLim_1--;
	      partialFlag_1 = 1;
	      partialFlag_2 = 1;
	      partialFlag_3 = 1;
	    }

	    // fix partial comb (2)
	    partialComb_2++;
	    if (partialComb_2 == partialLim_2) {
	      partialComb_2 = 0;
	      partialLim_2--;
	      partialFlag_2 = 1;
	      partialFlag_3 = 1;
	    }

	    // fix partial comb (3)
	    partialComb_3++;
	    if (partialComb_3 == partialLim_3) {
	      partialComb_3 = 0;
	      partialLim_3--;
	      partialFlag_3 = 1;
	    }
	    
	    // fill the three f1 vectors!
	    combVectorX.push_back({jGammaA1, jGammaA2, jGammaB1, jGammaB2, jPip, jPim});
	    combVectorY.push_back({jGammaA1, jGammaB1, jGammaA2, jGammaB2, jPip, jPim});
	    combVectorZ.push_back({jGammaA1, jGammaB2, jGammaA2, jGammaB1, jPip, jPim});

	  } // end of loop in gammas
	  
	} // end of loop in pi-
	
      } // end of loop in pi+

    } // end of at-least-one-f1 condition

    // commentary
    // std::cout << "  !! Obtain & keep combinations from data ready!" << std::endl;

    // PART 2: fill

    // commentary
    /*
    std::cout << "  f1 candidates for data:" << std::endl;
    for (Int_t c = 0; c < (nCombThisEvent/3); c++) {
      std::cout << "  {" << combVectorX[c][0] << ", " << combVectorX[c][1]
		<< ", "  << combVectorX[c][2] << ", " << combVectorX[c][3]
		<< ", "  <<  combVectorX[c][4] << ", " << combVectorX[c][5] << "}" << std::endl;
      std::cout << "  {" << combVectorY[c][0] << ", " << combVectorY[c][1]
		<< ", "  << combVectorY[c][2] << ", " << combVectorY[c][3]
		<< ", "  <<  combVectorY[c][4] << ", " << combVectorY[c][5] << "}" << std::endl;
      std::cout << "  {" << combVectorZ[c][0] << ", " << combVectorZ[c][1]
		<< ", "  << combVectorZ[c][2] << ", " << combVectorZ[c][3]
		<< ", "  <<  combVectorZ[c][4] << ", " << combVectorZ[c][5] << "}" << std::endl;
    }
    std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    */
    
    // extract for (X)
    for (Int_t cc = 0; cc < (nCombThisEvent/3); cc++) { // loop on combinations
      for (Int_t pp = 0; pp < 6; pp++) { // loop on particles
	// (0 -> gammaA1, 1 -> gammaA2, 2 -> gammaB1, 3 -> gammaB2, 4 -> pip, 5 -> pim)
	t->GetEntry(combVectorX[cc][pp]);
	AssignMix(combVectorX[cc][pp], pp); // AMV(entry, index) - inside is the condition of a valid pid
      } // end of loop in particles

      // after assigning each decay particle, assign the rest of variables
      AssignPi0A();
      AssignPi0B();
      Assignf1();
      AssignMore(nGammaThisEvent, nPipThisEvent, nPimThisEvent);

      // ...and fill
      tMix->Fill();      
    } // end of loop in combinations
    // std::cout << "Fill f1 - X ready!" << std::endl;
    
    // extract for (Y)
    for (Int_t cc = 0; cc < (nCombThisEvent/3); cc++) { // loop on combinations
      for (Int_t pp = 0; pp < 6; pp++) { // loop on particles
	// (0 -> gammaA1, 1 -> gammaA2, 2 -> gammaB1, 3 -> gammaB2, 4 -> pip, 5 -> pim)
	t->GetEntry(combVectorY[cc][pp]);
	AssignMix(combVectorY[cc][pp], pp); // AMV(entry, index) - inside is the condition of a valid pid
      } // end of loop in particles

      // after assigning each decay particle, assign the rest of variables
      AssignPi0A();
      AssignPi0B();
      Assignf1();
      AssignMore(nGammaThisEvent, nPipThisEvent, nPimThisEvent);

      // ...and fill
      tMix->Fill();      
    } // end of loop in combinations
    // std::cout << "Fill f1 - Y ready!" << std::endl;
    
    // extract for (Z)
    for (Int_t cc = 0; cc < (nCombThisEvent/3); cc++) { // loop on combinations
      for (Int_t pp = 0; pp < 6; pp++) { // loop on particles
	// (0 -> gammaA1, 1 -> gammaA2, 2 -> gammaB1, 3 -> gammaB2, 4 -> pip, 5 -> pim)
	t->GetEntry(combVectorZ[cc][pp]);
	AssignMix(combVectorZ[cc][pp], pp); // AMV(entry, index) - inside is the condition of a valid pid
      } // end of loop in particles

      // after assigning each decay particle, assign the rest of variables
      AssignPi0A();
      AssignPi0B();
      Assignf1();
      AssignMore(nGammaThisEvent, nPipThisEvent, nPimThisEvent);

      // ...and fill
      tMix->Fill();      
    } // end of loop in combinations
    // std::cout << "Fill f1 - Z ready!" << std::endl;
    
    // commentary
    // std::cout << "  !! Fill combinations in mix ready!" << std::endl;
    
    // reset counters
    nPipThisEvent = 0;
    nPimThisEvent = 0;
    nGammaThisEvent = 0;
    nCombThisEvent = 0;
    
    nParticles = 0;

    // reset vectors
    combVectorX.clear();
    combVectorY.clear();
    combVectorZ.clear();
    
    // commentary
    /*
    std::cout << "  !! Finished event" << std::endl;
    std::cout << std::endl;
    */
  } // end of loop in entries

  /*** Writing tree ***/
  
  rootFile->Write();
  rootFile->Close();

  std::cout << "This file has been created: " << outFile << std::endl;

  // measure time
  /*
  auto end = Clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << std::endl;
  */
  
  return 0;
}

/*** Input-related functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./FilterNCombine_f1 -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:r:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'r': rnOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./FilterNCombine_f1 -h to print help." << std::endl;
      exit(0);
      break;
    }
}

void assignOptions() {
  // for data type
  analyserOption = targetOption;
  // for everyone, at node dir
  inputFile = "pruned" + targetOption + "_" + rnOption + ".root";
  outFile = "comb" + targetOption + "_" + rnOption + ".root";
}

void printUsage() {
  std::cout << "FilterNCombine_f1 program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_f1 -h" << std::endl;
  std::cout << "    prints this message and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_f1 -t[C, Fe, Pb]" << std::endl;
  std::cout << "    filters the respective target" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_f1 -r[run number]" << std::endl;
  std::cout << "    selects run number" << std::endl;
  std::cout << "    numbering scheme for input files = pruned<target>_<run number>.root" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing FilterNCombine_f1 program. The chosen parameters are: " << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  rnOption     = " << rnOption << std::endl;
  std::cout << std::endl;
}
