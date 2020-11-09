/*****************************************/
/*  FilterNCombine_data.cxx              */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// November 2020

#include "FilterNCombine_data.h"

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

  // data counting variables
  Int_t nPipThisEvent = 0;
  Int_t nPimThisEvent = 0;
  Int_t nGammaThisEvent = 0;

  std::vector<int> gammaVector;
  std::vector<int> pipVector;
  std::vector<int> pimVector;
  
  std::vector<int> currentOrig;
  std::vector<int> currentComb;

  std::vector<std::vector <int>> combVector;

  /*** DATA STRUCTURES ***/
  
  // input
  data_i t;
  
  // output - original
  data_o o;

  // output - mix
  data_m   m;
  data_pi0 pi0;
  data_w   w;
  
  /*** INPUT ***/

  TChain *tree = new TChain();
  tree->Add(inputFile + "/ntuple_data"); // input
  
  /*** OUTPUT ***/

  TFile *rootFile = new TFile(outputFile, "RECREATE", "Omega Meson Filtered Combinations");

  TTree *tOriginal = new TTree("original", "Original particles");
  SetOriginalBranches(tOriginal, o);

  TTree *tMix = new TTree("mix", "Combination of particles");
  SetMixBranches(tMix, m, pi0, w);
  
  /*** START ***/

  SetMinimalBranches(tree, t);
  
  Int_t Ne = (Int_t) tree->GetEntries(); // 500 for testing
  Int_t currentEvent, previousEvent;
  
  // loop in entries
  for (Int_t i = 0; i <= Ne; i++) {
    tree->GetEntry(i);
    currentEvent = (Int_t) t.evnt;
    
    // prevents repetition of same event
    if (i > 0) {
      tree->GetEntry(i-1);
      previousEvent = (Int_t) t.evnt;
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
      if (currentEvent == (Int_t) t.evnt) {
	// commentary
	/*
	std::cout << "  Entry number: " << j << std::endl;
	std::cout << "  pid    =      " << t.pid << std::endl;
	std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;	
	*/
	// count the particles
	if (t.pid == (Float_t) 22)        gammaVector.push_back(j);
	else if (t.pid == (Float_t) 211)  pipVector.push_back(j);
	else if (t.pid == (Float_t) -211) pimVector.push_back(j);
      } else {
        break;
      }
    }

    nPipThisEvent   = pipVector.size();
    nPimThisEvent   = pimVector.size();
    nGammaThisEvent = gammaVector.size();
    
    // commentary
    /*
    std::cout << "  nPip     = " << nPipThisEvent     << std::endl;
    std::cout << "  nPim     = " << nPimThisEvent     << std::endl;
    std::cout << "  nGamma   = " << nGammaThisEvent   << std::endl;
    std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    */
    // now, init ALL branches
    SetInputBranches(tree, t);
    
    /*** FILL ORIGINAL ***/

    // candidate appeared
    if (nPipThisEvent >= 1 && nPimThisEvent >= 1 && nGammaThisEvent >= 2) {
      // sort particles
      currentOrig.insert(currentOrig.end(), pipVector.begin(), pipVector.end());
      currentOrig.insert(currentOrig.end(), pimVector.begin(), pimVector.end());
      currentOrig.insert(currentOrig.end(), gammaVector.begin(), gammaVector.end());
      // loop on all fs particles
      for (Int_t k = 0; k < (Int_t) currentOrig.size(); k++) {
	tree->GetEntry(currentOrig[k]);
	AssignOriginalVar(t, o, currentOrig[k], targetOption);
	// fill
	tOriginal->Fill();	
      }
      currentOrig.clear();
    }
          
    /*** COMBINE ***/
    
    // candidate appeared
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
	      // std::cout << "currentComb = {" << currentComb[0] << ", " << currentComb[1] << ", "  << currentComb[2] << ", " << currentComb[3] << "}" << std::endl;
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

    /*** FILL MIX ***/

    // candidate appeared
    for (Int_t cc = 0; cc < (Int_t) combVector.size(); cc++) { // loop on combinations
      for (Int_t pp = 0; pp < 4; pp++) { // loop on final state particles
	tree->GetEntry(combVector[cc][pp]);
	AssignMixVar(t, m, combVector[cc][pp], pp, targetOption, cc);
      } // end of loop on fs particles
      // asign more vars
      m.nPip   = nPipThisEvent;
      m.nPim   = nPimThisEvent;
      m.nGamma = nGammaThisEvent;
      // assign pi0 and omegas
      AssignPi0Var(m, pi0);
      AssignOmegaVar(m, pi0, w);
      // fill
      tMix->Fill();
    } // end of loop on combinations
    
    /*** RESET ***/
      
    // reset counters
    nPipThisEvent = 0;
    nPimThisEvent = 0;
    nGammaThisEvent = 0;

    // reset vectors
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
  // for everyone, at node dir
  inputFile  = "pruned" + targetOption + "_" + rnOption + ".root";
  outputFile = "comb" + targetOption + "_" + rnOption + ".root";
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
