/*****************************************/
/*  FilterNCombine_sim.cxx               */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// October 2020, reworked version

#include "FilterNCombine_sim.h"

/*** Options ***/

TString targetOption;
TString rnOption;

// input
TString inputFile;
TString outputFile;

/*** Declaration of functions ***/

int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {
  
  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  /*** DEFINITIONS ***/

  // gsim counting variables
  Int_t nMCPipThisEvent = 0;
  Int_t nMCPimThisEvent = 0;
  Int_t nMCGammaThisEvent = 0;
  
  std::vector<int> mc_gammaVector;
  std::vector<int> mc_pipVector;
  std::vector<int> mc_pimVector;

  std::vector<int> mc_currentOrig; // exclusive
  std::vector<int> mc_currentComb;
  
  std::vector<std::vector <int>> mc_combVector;

  // simrec counting variables
  Int_t nPipThisEvent = 0;
  Int_t nPimThisEvent = 0;
  Int_t nGammaThisEvent = 0;

  std::vector<int> gammaVector;
  std::vector<int> pipVector;
  std::vector<int> pimVector;

  std::vector<int> currentComb;

  std::vector<std::vector <int>> combVector;

  /*** DATA STRUCTURES ***/
  
  // input
  simrec_i t;
  gsim_i   mc_t;
  
  // output - original
  simrec_o o;
  gsim_o   mc_o;

  // output - mix
  simrec_m   m;
  simrec_pi0 pi0;
  simrec_w   w;
  gsim_m     mc_m;
  gsim_pi0   mc_pi0;
  gsim_w     mc_w;
  
  /*** INPUT ***/

  TChain *tree = new TChain();
  tree->Add(inputFile + "/ntuple_sim"); // input
  
  /*** OUTPUT ***/

  TFile *rootFile = new TFile(outputFile, "RECREATE", "Omega Meson Filtered Combinations");

  TTree *tOriginal = new TTree("original", "Original particles");
  SetOriginalBranches(tOriginal, o, mc_o);

  TTree *tMix = new TTree("mix", "Combination of particles");
  SetMixBranches(tMix, m, pi0, w, mc_m, mc_pi0, mc_w);
  
  /*** START ***/

  SetMinimalBranches(tree, t, mc_t);
  
  Int_t Ne = (Int_t) tree->GetEntries(); // 500 for testing
  Int_t currentEvent, previousEvent;
  
  // loop in entries
  for (Int_t i = 0; i <= Ne; i++) {
    tree->GetEntry(i);
    currentEvent = (Int_t) mc_t.evnt;
    
    // prevents repetition of same event
    if (i > 0) {
      tree->GetEntry(i-1);
      previousEvent = (Int_t) mc_t.evnt;
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
      tree->GetEntry(j);
      if (currentEvent == (Int_t) mc_t.evnt) {
	// commentary
	/*
	  std::cout << "  Entry number: " << j << std::endl;
	  std::cout << "  mc_pid =      " << mc_t.pid << std::endl;
	  std::cout << "  pid    =      " << t.pid << std::endl;
	  std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;	
	*/
	// count the simrec particles
	if (t.pid == (Float_t) 22)        gammaVector.push_back(j);
	else if (t.pid == (Float_t) 211)  pipVector.push_back(j);
	else if (t.pid == (Float_t) -211) pimVector.push_back(j);
	// count the gsim particles
        if (mc_t.pid == (Float_t) 22)        mc_gammaVector.push_back(j);
	else if (mc_t.pid == (Float_t) 211)  mc_pipVector.push_back(j);
	else if (mc_t.pid == (Float_t) -211) mc_pimVector.push_back(j);
      } else {
        break;
      }
    }

    nPipThisEvent   = pipVector.size();
    nPimThisEvent   = pimVector.size();
    nGammaThisEvent = gammaVector.size();  
    nMCPipThisEvent   = mc_pipVector.size();
    nMCPimThisEvent   = mc_pimVector.size();
    nMCGammaThisEvent = mc_gammaVector.size();

    // testing
    mc_m.nPip = nMCPipThisEvent;
    mc_m.nPim = nMCPimThisEvent;
    mc_m.nGamma = nMCGammaThisEvent;
    
    // commentary
    /*
      std::cout << "  nPip     = " << nPipThisEvent     << std::endl;
      std::cout << "  nPim     = " << nPimThisEvent     << std::endl;
      std::cout << "  nGamma   = " << nGammaThisEvent   << std::endl;
      std::cout << "  nMCPip   = " << nMCPipThisEvent   << std::endl;
      std::cout << "  nMCPim   = " << nMCPimThisEvent   << std::endl;
      std::cout << "  nMCGamma = " << nMCGammaThisEvent << std::endl;
      std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    */
    
    // now, init ALL branches
    SetInputBranches(tree, t, mc_t);
    
    /*** FILL ORIGINAL ***/

    // candidate appeared for GSIM
    if (nMCPipThisEvent >= 1 && nMCPimThisEvent >= 1 && nMCGammaThisEvent >= 2) {
      // concatenate vectors
      mc_currentOrig.insert(mc_currentOrig.end(), mc_pipVector.begin(), mc_pipVector.end());
      mc_currentOrig.insert(mc_currentOrig.end(), mc_pimVector.begin(), mc_pimVector.end());
      mc_currentOrig.insert(mc_currentOrig.end(), mc_gammaVector.begin(), mc_gammaVector.end());
      // loop on all fs particles
      for (Int_t k = 0; k < (Int_t) mc_currentOrig.size(); k++) {
	tree->GetEntry(mc_currentOrig[k]);
	AssignOriginalVar_GSIM(mc_t, mc_o, mc_currentOrig[k]);
	// candidate appeared for SIMREC
	if (nPipThisEvent >= 1 && nPimThisEvent >= 1 && nGammaThisEvent >= 2 && t.pid != INVLD) {
	  AssignOriginalVar_SIMREC(t, o, mc_currentOrig[k]); // maintains particle matching
	} else {
	  NullOriginalVar_SIMREC(o);
	}
	// fill
	tOriginal->Fill();	
      }
      mc_currentOrig.clear();
    }
          
    /*** COMBINE ***/
    
    // candidate appeared for GSIM
    if (nMCPipThisEvent >= 1 && nMCPimThisEvent >= 1 && nMCGammaThisEvent >= 2) {
      for (Int_t iPip = 0; iPip < nMCPipThisEvent; iPip++) {
	mc_currentComb.push_back(mc_pipVector[iPip]);
	for (Int_t iPim = 0; iPim < nMCPimThisEvent; iPim++) {
	  mc_currentComb.push_back(mc_pimVector[iPim]);
	  for (Int_t iGamma = 0; iGamma < (nMCGammaThisEvent-1); iGamma++) {
	    mc_currentComb.push_back(mc_gammaVector[iGamma]);
	    for (Int_t jGamma = iGamma+1; jGamma < nMCGammaThisEvent; jGamma++) {
	      mc_currentComb.push_back(mc_gammaVector[jGamma]);
	      // commentary
	      /*
		std::cout << "mc_currentComb = {" << mc_currentComb[0] << ", " << mc_currentComb[1] << ", "  << mc_currentComb[2] << ", " << mc_currentComb[3] << "}" << std::endl;
	      */
	      // fill vector
	      mc_combVector.push_back(mc_currentComb);
	      mc_currentComb.pop_back();
	    } // end of loop in gamma 2
	    mc_currentComb.pop_back();
	  } // end of loop in gamma 1
	  mc_currentComb.pop_back();
	} // end of loop in pi-
	mc_currentComb.pop_back();
      } // end of loop in pi+
    } // end of at-least-one-omega condition

    // candidate appeared for SIMREC
    if (nPipThisEvent >= 1 && nPimThisEvent >= 1 && nGammaThisEvent >= 2) {
      for (Int_t iPip = 0; iPip < nPipThisEvent; iPip++) {
	currentComb.push_back(pipVector[iPip]);
	for (Int_t iPim = 0; iPim < nPimThisEvent; iPim++) {
	  currentComb.push_back(pimVector[iPim]);
	  for (Int_t iGamma = 0; iGamma < (nGammaThisEvent-1); iGamma++) {
	    currentComb.push_back(gammaVector[iGamma]);
	    for (Int_t jGamma = iGamma+1; jGamma < nGammaThisEvent; jGamma++) {
	      currentComb.push_back(gammaVector[jGamma]);
	      // commentary
	      /*
		std::cout << "currentComb = {" << currentComb[0] << ", " << currentComb[1] << ", "  << currentComb[2] << ", " << currentComb[3] << "}" << std::endl;
	      */
	      // fill vector
	      combVector.push_back(currentComb);
	      currentComb.pop_back();
	    } // end of loop in gamma 2
	    currentComb.pop_back();
	  } // end of loop in gamma 1
	  currentComb.pop_back();
	} // end of loop in pi-
	currentComb.pop_back();
      } // end of loop in pi+
    } // end of at-least-one-omega condition

    /*** OMEGA MATCHING ***/

    std::vector<std::vector<int>> matchingVector;
    std::vector<int> nullVector = {-1,-1,-1,-1};
    Int_t found = -1;
    
    if ((Int_t) combVector.size() > 0){
      for (Int_t i = 0; i < (Int_t) mc_combVector.size(); i++) {
	for (Int_t j = 0; j < (Int_t) combVector.size(); j++) {
	  if (combVector[j] == mc_combVector[i]) { // it may work
	    found = j;
	    break;
	  }
	}
	if (found > -1) {
	  matchingVector.push_back(combVector[found]);
	} else {
	  matchingVector.push_back(nullVector);
	}
	found = -1;
      }
    }

    Int_t neverfound = 1;
    for (Int_t k = 0; k < (Int_t) matchingVector.size(); k++) {
      if (matchingVector[k] != nullVector) {
	neverfound = 0;
      }
    }
    if (neverfound) matchingVector.clear();
    
    /*** FILL MIX ***/

    // candidate appeared for GSIM
    for (Int_t cc = 0; cc < (Int_t) mc_combVector.size(); cc++) { // loop on combinations
      for (Int_t pp = 0; pp < 4; pp++) { // loop on final state particles
	// gsim
	tree->GetEntry(mc_combVector[cc][pp]);
	AssignMixVar_GSIM(mc_t, mc_m, mc_combVector[cc][pp], pp);
	// candidate appeared for SIMREC
	if ((Int_t) combVector.size() > 0) {
	  // any matching?
	  if ((Int_t) matchingVector.size() > 0) {
	    if (matchingVector[cc][pp] != -1) {
	      tree->GetEntry(matchingVector[cc][pp]);
	      AssignMixVar_SIMREC(t, m, matchingVector[cc][pp], pp);
	      AssignMoreVar_SIMREC(m, nPipThisEvent, nPimThisEvent, nGammaThisEvent);
	    }
	  } else {
	    if (cc < (Int_t) combVector.size()) {
	      tree->GetEntry(combVector[cc][pp]);
	      AssignMixVar_SIMREC(t, m, combVector[cc][pp], pp);
	      AssignMoreVar_SIMREC(m, nPipThisEvent, nPimThisEvent, nGammaThisEvent);
	    }
	  }
	}
      } // end of loop on fs particles
      // assign GSIM pi0 and omegas
      AssignPi0Var_GSIM(mc_m, mc_pi0);
      AssignOmegaVar_GSIM(mc_m, mc_pi0, mc_w);
      // assign SIMREC pi0 and omegas
      if ((Int_t) combVector.size() > 0) {
	// any matching?
	if ((Int_t) matchingVector.size() > 0) {
	  if (matchingVector[cc] != nullVector) {
	    AssignPi0Var_SIMREC(m, pi0);
	    AssignOmegaVar_SIMREC(m, pi0, w);
	  } else {
	    NullMixVar_SIMREC(m, pi0, w);
	  }
	} else {
	  if (cc < (Int_t) combVector.size()) {
	    AssignPi0Var_SIMREC(m, pi0);
	    AssignOmegaVar_SIMREC(m, pi0, w);
	  } else {
	    NullMixVar_SIMREC(m, pi0, w);
	  }
	}
      } else {
        NullMixVar_SIMREC(m, pi0, w);
      }
      // fill
      tMix->Fill();
    } // end of loop on combinations

    /*** RESET ***/
      
    // reset gsim counters
    nMCPipThisEvent = 0;
    nMCPimThisEvent = 0;
    nMCGammaThisEvent = 0;
    
    // reset simrec counters
    nPipThisEvent = 0;
    nPimThisEvent = 0;
    nGammaThisEvent = 0;
    	
    // reset vectors
    mc_pipVector.clear();
    mc_pimVector.clear();
    mc_gammaVector.clear();
    mc_currentComb.clear();
    mc_combVector.clear();

    pipVector.clear();
    pimVector.clear();
    gammaVector.clear();
    currentComb.clear();
    combVector.clear();
    
    // commentary
    /*
      std::cout << "  !! Finished event" << std::endl;
      std::cout << std::endl;
    */
  } // end of loop in entries

  /*** WRITE ***/

  rootFile->Write();
  rootFile->Close();

  std::cout << "This file has been created: " << outputFile << std::endl;
  
  return 0;
}

/*** Input-related functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./FilterNCombine_sim -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:r:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'r': rnOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./FilterNCombine_sim -h to print help." << std::endl;
      exit(0);
      break;
    }
}

void assignOptions() {
  // for everyone, at node dir
  inputFile  = "pruned" + targetOption + "_" + rnOption + ".root";
  outputFile = "comb" + targetOption + "_" + rnOption + ".root";
}

void printUsage() {
  std::cout << "FilterNCombine_sim program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_sim -h" << std::endl;
  std::cout << "    prints this message and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_sim -t[D, C, Fe, Pb]" << std::endl;
  std::cout << "    filters the respective target" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_sim -r[run number]" << std::endl;
  std::cout << "    selects run number" << std::endl;
  std::cout << "    numbering scheme for input files = pruned<target>_<run number>.root" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing FilterNCombine_sim program. The chosen parameters are: " << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  rnOption     = " << rnOption << std::endl;
  std::cout << std::endl;
}
