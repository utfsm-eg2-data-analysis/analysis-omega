/*****************************************/
/*  FilterNCombine.cxx                   */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// PENDING:
// - do the momentum/angular matching for omegas
// - add Pt_{x,y,z} as a vector for every decay particle -> Pt2 should be enough... I can derive it
// - add a way to have the P of all photons -> just sum mP[0] with mP[1} hist

#include "FilterNCombine.h"

/*** Constants ***/

Float_t kEbeam = 5.014;

/*** Global variables ***/

/*** Input variables ***/

// (81 variables for data)
// electron (39)
Float_t tQ2, tW, tNu, tXb, tYb, tvxe, tvye, tvze, tSectorEl, tTargType, tPex, tPey, tPez, tPe, tBettaEl, tEtote, tEine, tEoute, tvxec, tvyec, tvzec, tXECe, tYECe, tZECe;
Float_t tStatDCEl, tDCStatusEl, tStatECEl, tECStatusEl, tTimeECEl, tPathECEl, tChi2ECEl, tStatSCEl, tSCStatusEl, tTimeSCEl, tPathSCEl, tStatCCEl, tCCStatusEl, tChi2CCEl, tStatusEl;
// particle (41)
Float_t tZh, tThetaPQ, tPt2, tPl2, tPhiPQ, tMx2, tT, tvxh, tvyh, tvzh, tSector, tPx, tPy, tPz, tP, tBetta, tMass2, tEtot, tEin, tEout, tXEC, tYEC, tZEC, tpid, tT4, tdeltaZ;
Float_t tStatDC, tDCStatus, tStatEC, tECStatus, tTimeEC, tPathEC, tChi2EC, tStatSC, tSCStatus, tTimeSC, tPathSC, tStatCC, tCCStatus, tChi2CC, tStatus;
// event (1)
Float_t tevnt;

/*** Output/original variables ***/

// (101 variables for data)
// electron (40)
Float_t oQ2, oW, oNu, oXb, oYb, oXe, oYe, oZe, oSectorEl, oTargType, oPex, oPey, oPez, oPe, oBettaEl, oEtote, oEine, oEoute, oXec, oYec, oZec, oXECe, oYECe, oZECe;
Float_t oP2e;
Float_t oStatDCEl, oDCStatusEl, oStatECEl, oECStatusEl, oTimeECEl, oPathECEl, oChi2ECEl, oStatSCEl, oSCStatusEl, oTimeSCEl, oPathSCEl, oStatCCEl, oCCStatusEl, oChi2CCEl, oStatusEl;
// particle (59) (16 + 3*6 + 10 + 15)
Float_t ovxh, ovyh, ovzh, oSector, oBetta, oMass2, oEtot, oEin, oEout, oXEC, oYEC, oZEC, oPid, oT4, odeltaZ, oM;
Float_t oE_prev, oPx_prev, oPy_prev, oPz_prev, oP2_prev, oP_prev;
Float_t oE_true, oPx_true, oPy_true, oPz_true, oP2_true, oP_true;
Float_t oE_corr, oPx_corr, oPy_corr, oPz_corr, oP2_corr, oP_corr;
Float_t oZ, oThetaPQ, oPt2, oPl2, oPhiPQ, oMx2, oT, oCosThetaPQ, oBettaCalc, odeltaTheta;
Float_t oStatDC, oDCStatus, oStatEC, oECStatus, oTimeEC, oPathEC, oChi2EC, oStatSC, oSCStatus, oTimeSC, oPathSC, oStatCC, oCCStatus, oChi2CC, oStatus;
// event (2)
Float_t oEvent;
Float_t oEntry; // debug purposes

/*** Output/mix variables ***/

// (194 variables for data)
// electron (40) (39+1new)
Float_t mQ2, mW, mNu, mXb, mYb, mXe, mYe, mZe, mSectorEl, mTargType, mPex, mPey, mPez, mPe, mBettaEl, mEtote, mEine, mEoute, mXec, mYec, mZec, mXECe, mYECe, mZECe;
Float_t mP2e;
Float_t mStatDCEl, mDCStatusEl, mStatECEl, mECStatusEl, mTimeECEl, mPathECEl, mChi2ECEl, mStatSCEl, mSCStatusEl, mTimeSCEl, mPathSCEl, mStatCCEl, mCCStatusEl, mChi2CCEl, mStatusEl;
// particles (59) (16 + 3*6 + 10 + 15)
Float_t mvxh[4], mvyh[4], mvzh[4], mSector[4], mBetta[4], mMass2[4], mEtot[4], mEin[4], mEout[4], mXEC[4], mYEC[4], mZEC[4], mPid[4], mT4[4], mdeltaZ[4], mM[4];
Float_t mE_prev[4], mPx_prev[4], mPy_prev[4], mPz_prev[4], mP2_prev[4], mP_prev[4];
Float_t mE_true[4], mPx_true[4], mPy_true[4], mPz_true[4], mP2_true[4], mP_true[4];
Float_t mE_corr[4], mPx_corr[4], mPy_corr[4], mPz_corr[4], mP2_corr[4], mP_corr[4];
Float_t mZ[4], mThetaPQ[4], mPt2[4], mPl2[4], mPhiPQ[4], mMx2[4], mT[4], mCosThetaPQ[4], mBettaCalc[4], mdeltaTheta[4];
Float_t mStatDC[4], mDCStatus[4], mStatEC[4], mECStatus[4], mTimeEC[4], mPathEC[4], mChi2EC[4], mStatSC[4], mSCStatus[4], mTimeSC[4], mPathSC[4], mStatCC[4], mCCStatus[4], mChi2CC[4], mStatus[4];
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

/*** Options ***/

TString targetOption;
Int_t   simFlag = 0;
TString setOption;
TString rnOption;
TString analyserOption; // new, for photon's energy correction

TString treeName;

TString outDir; // depends on data type
TString outFile;

// input
TString inputFile;

// new
TString eventBranchName;

/*** Declaration of functions ***/

int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();
  
  // dir structure, just in case
  system("mkdir -p " + outDir);

  /*** Init tree ***/
  
  // hadrons (t - tree)
  TChain *t = new TChain();
  t->Add(inputFile + "/" + treeName); // input

  SetInputBranches(t, simFlag);
  
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

  Int_t nEvents = 0;
  
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
  Int_t start, finish;
  if (!simFlag) {
    start = (Int_t) t->GetMinimum(eventBranchName);
    finish = (Int_t) t->GetMaximum(eventBranchName); // 10000
  } else if (simFlag) {
    start = 0;
    finish = (Int_t) t->GetMaximum(eventBranchName);
  }
  
  // loop in events
  // i = event number
  for (Int_t i = start; i <= finish; i++) { // t->GetMinimum(eventBranchName), t->GetMaximum(eventBranchName)
    
    // std::cout << "Current event number: " << i << std::endl;
    // std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    
    TString theCondition;
    TString listName = Form("elist_%d", i);

    if (simFlag) theCondition = Form("evnt == %d || mc_evnt == %d", i, i);
    else theCondition = Form("evnt == %d", i);

    // selects all entries from the same event
    t->Draw(">>" + listName, theCondition, "entrylist");
    l = (TEntryList*) gDirectory->Get(listName);
    t->SetEntryList(l);
      
    // looks at the entries (particles) of the current event
    // j = iterator, jj = real entry number
    for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
      Int_t jj = t->GetEntryNumber(j);
      t->GetEntry(jj);
      // std::cout << "  Entry number: " << jj << std::endl;
      // std::cout << "  pid:          " << tpid << std::endl;
      // // std::cout << "  mc_pid:       " << tmc_Pid << std::endl;
      // std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
      // count the data/simrec particles
      if (tpid == (Float_t) 211) nPipThisEvent++;
      if (tpid == (Float_t) -211) nPimThisEvent++;
      if (tpid == (Float_t) 22) nGammaThisEvent++;
      // count the gsim particles
      // if (tmc_Pid == (Float_t) 211) nMCPipThisEvent++;
      // if (tmc_Pid == (Float_t) -211) nMCPimThisEvent++;
      // if (tmc_Pid == (Float_t) 22) nMCGammaThisEvent++;
    }
    
    // show counts
    // std::cout << "  nPip     = " << nPipThisEvent << std::endl;
    // std::cout << "  nPim     = " << nPimThisEvent << std::endl;
    // std::cout << "  nGamma   = " << nGammaThisEvent << std::endl;
    // // std::cout << "  nMCPip   = " << nMCPipThisEvent << std::endl;
    // // std::cout << "  nMCPim   = " << nMCPimThisEvent << std::endl;
    // // std::cout << "  nMCGamma = " << nMCGammaThisEvent << std::endl;
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

    // std::cout << "  There are " << nCombThisEvent << " omegas!" << std::endl;
    // // std::cout << "  There are " << nCombThisEvent << " reconstructed omegas!" << std::endl;
    // // std::cout << "  There are " << nMCCombThisEvent << " generated omegas!" << std::endl;
    // std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    /*** ORIGINAL ***/

    // saves all information from the original particles from an approved event, with no mixing
    // warning: all the hadronic variables correspond to the respective hadron, nothing more
    
    if (nCombThisEvent > 0 || nMCCombThisEvent > 0) {

      // looks at the entries (particles) of the current event
      // j = iterator, jj = real entry number
      for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
	Int_t jj = t->GetEntryNumber(j);
	t->GetEntry(jj);

        AssignVariables("original", jj, 5, analyserOption); // 5 won't mind, it's just there...
	tOriginal->Fill();

      } // end of particles loop
    } // end of candidate condition
      
    /*** THE MIXING ***/

    // PART 1: obtain & keep combinations from simrec
    
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
	    jPip = jj;      // tag pip
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
	      jPim = jj; // tag pim
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
		  jGamma1 = jj;  // tag gamma1
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
		jGamma2 = jj;  // tag gamma2
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
	  // if (tmc_Pid == (Float_t) 211 && jj > jPip) {
	  //   jPip = jj;      // tag pip
	  //   j = (Int_t) l->GetN(); // break search
	  // }
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
	    // if (tmc_Pid == (Float_t) -211 && jj > jPim) {
	    //   jPim = jj; // tag pim
	    //   j = (Int_t) l->GetN(); // break search
	    // }
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
		// if (tmc_Pid == (Float_t) 22 && jj > jGamma1) { // excludes previous gamma1
		//   jGamma1 = jj;  // tag gamma1
		//   j = (Int_t) l->GetN(); // break search for j
		// }
	      }
	      jGamma2 = 0; // resets gamma2
	      partialFlag = 0;
	    }
	  
	    // find and tag gamma2
	    // jj = real entry number, j = iterator
	    for (Int_t j = 0; j < (Int_t) l->GetN(); j++) {
	      Int_t jj = t->GetEntryNumber(j);
	      t->GetEntry(jj);
	      // if (tmc_Pid == (Float_t) 22 && jj > jGamma2 && jj > jGamma1) { // excludes gamma1 and previous gamma2
	      // 	jGamma2 = jj;  // tag gamma2
	      // 	j = (Int_t) l->GetN(); // break search for j
	      // }
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
      
    // PART 3: fill

    // std::cout << "  candidates for data:" << std::endl;
    for (Int_t c = 0; c < nCombThisEvent; c++) // std::cout << "  {" << combVector[c][0] << ", " << combVector[c][1] << ", "  << combVector[c][2] << ", " << combVector[c][3] << "}" << std::endl;
    // // std::cout << "  candidates for simrec:" << std::endl;
    // for (Int_t c = 0; c < nCombThisEvent; c++) // std::cout << "  {" << combVector[c][0] << ", " << combVector[c][1] << ", "  << combVector[c][2] << ", " << combVector[c][3] << "}" << std::endl;
    // // std::cout << "  candidates for gsim:" << std::endl;
    // for (Int_t c = 0; c < nMCCombThisEvent; c++) // std::cout << "  {" << mc_combVector[c][0] << ", " << mc_combVector[c][1] << ", "  << mc_combVector[c][2] << ", " << mc_combVector[c][3] << "}" << std::endl;
    // std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    // extract
    for (Int_t cc = 0; cc < TMath::Max(nCombThisEvent, nMCCombThisEvent); cc++) { // loop on combinations
      for (Int_t pp = 0; pp < 4; pp++) { // loop on particles
	
	  t->GetEntry(combVector[cc][pp]);
	  AssignVariables("mix", combVector[cc][pp], pp, analyserOption);
	  
      } // end of loop in particles

      AssignPi0Variables();
      AssignOmegaVariables();
      AssignMoreVariables(nGammaThisEvent, nPipThisEvent, nPimThisEvent);
      
      tMix->Fill();      
    } // end of loop in combinations

    // reset count variables
    nPipThisEvent = 0;
    nPimThisEvent = 0;
    nGammaThisEvent = 0;
    nCombThisEvent = 0;
    
    nMCPipThisEvent = 0;
    nMCPimThisEvent = 0;
    nMCGammaThisEvent = 0;
    nMCCombThisEvent = 0;

    // update event counter
    nEvents++;
    
    // reset vectors!
    combVector.clear();
    mc_combVector.clear();

    // for data
    Int_t ii;
    if (!simFlag) {
      ii = t->GetEntryNumber(l->GetN() - 1); // look last entry from event list
    }
    
    // set tree back to original tree
    t->SetEntryList(0);

    // for data
    if (!simFlag) {
      if (i == (Int_t) t->GetMaximum(eventBranchName)) break; // break infinite loop
      t->GetEntry(ii+1); // stand in first entry of the next event
      i = (Int_t) tevnt - 1; // jump to next event number
    }
    
    // clean some memory
    gDirectory->Delete(listName + ";1");
    rootFile->Delete(listName);
    
    // std::cout << std::endl;
  } // end of loop in events

  /*** Writing tree ***/

  if (simFlag) {
    // std::cout << "From a total of " << nEvents << " generated events." << std::endl;
    // std::cout << "There are at least " << nAtLeastMCOmega << " generated events with at least one omega particle," << std::endl;
    // std::cout << "being in total this amount of generated omega candidates: " << nMCOmega << "."  << std::endl;
    // std::cout << "Also, there are at least " << nAtLeastOmega << " reconstructed events with at least one omega particle," << std::endl;
    // std::cout << "being in total this amount of reconstructed omega candidates: " << nOmega << "."  << std::endl;
    // std::cout << std::endl;
  } else {
    // std::cout << "From a total of " << nEvents << " events." << std::endl;
    // std::cout << "There are at least " << nAtLeastOmega << " events with at least one omega particle," << std::endl;
    // std::cout << "being in total this amount of omega candidates: " << nOmega << "."  << std::endl;
    // std::cout << std::endl;
  }
  
  rootFile->Write();
  rootFile->Close();

  // std::cout << "File " << outFile << " has been created!" << std::endl;
  
  return 0;
}

/*** Input-related functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./FilterNCombine -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:dS:r:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'd': simFlag = 0; break;
    case 'S': simFlag = 1; setOption = optarg; break;
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
    // set
    setOption = "data";
    // ntuple name
    treeName = "ntuple_data";
    eventBranchName = "evnt";
    // input
    // inputFile = proDir + "/out/prunedData/" + targetOption + "/pruned_data_" + rnOption + ".root";
    inputFile = proDir + "/out/ToyGST/data/" + targetOption + "/pruned" + targetOption + "_" + rnOption + ".root"; // new
    // out
    outDir = dataDir + "/" + targetOption;
    // new!
    analyserOption = targetOption;
  } else if (simFlag) {
    // ntuple name
    treeName = "ntuple_sim";
    eventBranchName = "mc_evnt";
    // input
    inputFile = proDir + "/out/prunedSim/" + setOption + "/" + targetOption + "/pruned_sim" + targetOption + "_" + rnOption + ".root"; // new
    // if (setOption == "jlab") inputFile = proDir + "/out/prunedSim/" + setOption + "/" + targetOption + "/" + jlabNDir + "/pruned_sim" + targetOption + "_" + rnOption + ".root"; // new (for jlab)
    // out
    outDir = simDir + "/" + setOption + "/" + targetOption;
    // if (setOption == "jlab") outDir += "/" + jlabNDir;
    // new!
    analyserOption = "Sim";
  }
  // regardless of the data type
  outFile = outDir + "/comb_" + setOption + targetOption + "_" + rnOption + ".root";
}

void printUsage() {
  // std::cout << "FilterNCombine program." << std::endl;
  // std::cout << "The input file should have this name scheme: " << std::endl;
  // std::cout << "    for data     = out/ToyGST/data/[target]/pruned[target]_[rn].root" << std::endl;
  // std::cout << "    for old/usm  = out/ToyGST/[set]/[target]/pruned[target]_[rn].root" << std::endl;
  // std::cout << "    for jlab     = pruned[target]_[rn].root" << std::endl;
  // std::cout << "Usage is:" << std::endl;
  // std::cout << std::endl;
  // std::cout << "./FilterNCombine -h" << std::endl;
  // std::cout << "    prints this message and exits program" << std::endl;
  // std::cout << std::endl;
  // std::cout << "./FilterNCombine -t[D, C, Fe, Pb]" << std::endl;
  // std::cout << "    filters the respective target" << std::endl;
  // std::cout << "    IMPORTANT: D option is only for simulations" << std::endl;
  // std::cout << std::endl;
  // std::cout << "./FilterNCombine -d" << std::endl;
  // std::cout << "    filters data" << std::endl;
  // std::cout << std::endl;
  // std::cout << "./FilterNCombine -S[old, usm, jlab]" << std::endl;
  // std::cout << "    filters sim for chosen set" << std::endl;
  // std::cout << std::endl;
  // std::cout << "./GetSimpleTuple -r[0001,...,9999]" << std::endl;
  // std::cout << "    selects run number (mandatory for all)" << std::endl;
  // std::cout << "    (please, maintain numbering scheme!)" << std::endl;
  // std::cout << std::endl;
}

void printOptions() {
  // std::cout << "Executing FilterNCombine program. The chosen parameters are: " << std::endl;
  // std::cout << "  targetOption   = " << targetOption << std::endl;
  // std::cout << "  simFlag        = " << simFlag << std::endl;
  // std::cout << "  setOption      = " << setOption << std::endl;
  // std::cout << "  rnOption       = " << rnOption << std::endl;
  // std::cout << "  inputFile      = " << inputFile << std::endl;
  // std::cout << "  setOption      = " << setOption << std::endl;
  // std::cout << std::endl;
}
