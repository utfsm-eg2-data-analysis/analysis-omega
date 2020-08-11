/*****************************************/
/*  FilterNCombine_data.cxx              */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// Exclusive for Data

#include "FilterNCombine_data.h"

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
Float_t wZ_prev, wCosThetaPQ_prev, wThetaPQ_prev, wPt2_prev, wPl2_prev, wPhiPQ_prev, wMx2_prev, wT_prev, wBettaCalc_prev, wdeltaTheta_prev, wD_prev, wM_prev;
Float_t wPx_true, wPy_true, wPz_true, wP_true, wP2_true, wE_true;
Float_t wZ_true, wCosThetaPQ_true, wThetaPQ_true, wPt2_true, wPl2_true, wPhiPQ_true, wMx2_true, wT_true, wBettaCalc_true, wdeltaTheta_true, wD_true, wM_true;
Float_t wPx_corr, wPy_corr, wPz_corr, wP_corr, wP2_corr, wE_corr;
Float_t wZ_corr, wCosThetaPQ_corr, wThetaPQ_corr, wPt2_corr, wPl2_corr, wPhiPQ_corr, wMx2_corr, wT_corr, wBettaCalc_corr, wdeltaTheta_corr, wD_corr, wM_corr;
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
  Int_t nParticles = 0;
  Int_t nCombThisEvent = 0;

  Int_t nOmega = 0;
  Int_t nAtLeastOmega = 0;
  
  // combination vectors
  std::vector<std::vector <int>> combVector;
  
  /*** START ***/
  
  Int_t Ne = (Int_t) t->GetEntries(); // 415 for -tC -r42011
  Int_t currentEvent, previousEvent;
  
  // loop in entries
  for (Int_t i = 0; i <= Ne; i++) {
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
    std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    */
    
    // candidate appeared for data
    if (nPipThisEvent >= 1 && nPimThisEvent >= 1 && nGammaThisEvent >= 2) {
      nAtLeastOmega++;
      nCombThisEvent = TMath::Binomial(nPipThisEvent, 1)*TMath::Binomial(nPimThisEvent, 1)*TMath::Binomial(nGammaThisEvent, 2);
      nOmega += nCombThisEvent;
      nParticles = nGammaThisEvent + nPipThisEvent + nPimThisEvent;
    }

    // commentary
    /*
    std::cout << "  There are " << nCombThisEvent << " omegas!" << std::endl;
    std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    */
    
    /*** ORIGINAL ***/

    // saves all information from the original particles from an approved event, with no mixing
    // warning: all the hadronic variables correspond to the respective hadron, nothing more
    
    if (nCombThisEvent > 0) {
      // looks at the entries (particles) of the current event
      for (Int_t j = i; j < (i+nParticles); j++) {
	t->GetEntry(j);
	AssignOriginalVariables(j); // AOV(Int_t entry)	
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
    Int_t jGamma1 = 0;
    Int_t jGamma2 = 0;
    
    Int_t partialComb = 0;
    Int_t partialLim = nGammaThisEvent - 1;
    Int_t partialFlag = 1;
    
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
	
	// force a new beginning for the other particles
	jPim = 0;
	jGamma1 = 0;
	jGamma2 = 0;
	
	for (Int_t iPim = 0; iPim < TMath::Binomial(nPimThisEvent, 1); iPim++) {
	  
	  // find and tag pim
	  for (Int_t j = i; j < (i+nParticles); j++) {
	    t->GetEntry(j);
	    if (tpid == (Float_t) -211 && j > jPim) {
	      jPim = j;           // tag pim
	      j = (i+nParticles); // break search
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
	      for (Int_t j = i; j < (i+nParticles); j++) {
		t->GetEntry(j);
		if (tpid == (Float_t) 22 && j > jGamma1) { // excludes previous gamma1
		  jGamma1 = j;        // tag gamma1
		  j = (i+nParticles); // break search for j
		}
	      }
	      jGamma2 = 0; // resets gamma2
	      partialFlag = 0;
	    }
	    
	    // find and tag gamma2
	    for (Int_t j = i; j < (i+nParticles); j++) {
	      t->GetEntry(j);
	      if (tpid == (Float_t) 22 && j > jGamma2 && j > jGamma1) { // excludes gamma1 and previous gamma2
		jGamma2 = j;        // tag gamma2
		j = (i+nParticles); // break search for j
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

    // commentary
    // std::cout << "  !! Obtain & keep combinations from data ready!" << std::endl;

    // PART 2: fill

    // commentary
    /*
    std::cout << "  candidates for data:" << std::endl;
    for (Int_t c = 0; c < nCombThisEvent; c++) std::cout << "  {" << combVector[c][0] << ", " << combVector[c][1] << ", "  << combVector[c][2] << ", " << combVector[c][3] << "}" << std::endl;
    std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    */
    
    // extract
    for (Int_t cc = 0; cc < nCombThisEvent; cc++) { // loop on combinations
      for (Int_t pp = 0; pp < 4; pp++) { // loop on particles
	t->GetEntry(combVector[cc][pp]);
	AssignMixVariables(combVector[cc][pp], pp); // AMV(entry, index) - inside is the condition of a valid pid
      } // end of loop in particles

      // after assigning each decay particle, assign the rest of variables
      AssignPi0Variables();
      AssignOmegaVariables();
      AssignMoreVariables(nGammaThisEvent, nPipThisEvent, nPimThisEvent);

      // ...and fill
      tMix->Fill();      
    } // end of loop in combinations

    // commentary
    // std::cout << "  !! Fill combinations in mix ready!" << std::endl;
    
    // reset counters
    nPipThisEvent = 0;
    nPimThisEvent = 0;
    nGammaThisEvent = 0;
    nCombThisEvent = 0;
    
    nParticles = 0;

    // reset vector
    combVector.clear();
    
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
    std::cerr << "Empty command line. Execute ./FilterNCombine_data -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:r:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'r': rnOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./FilterNCombine_data -h to print help." << std::endl;
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
  std::cout << "FilterNCombine_data program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_data -h" << std::endl;
  std::cout << "    prints this message and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_data -t[C, Fe, Pb]" << std::endl;
  std::cout << "    filters the respective target" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_data -r[run number]" << std::endl;
  std::cout << "    selects run number" << std::endl;
  std::cout << "    numbering scheme for input files = pruned<target>_<run number>.root" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing FilterNCombine_data program. The chosen parameters are: " << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  rnOption     = " << rnOption << std::endl;
  std::cout << std::endl;
}