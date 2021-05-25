/*****************************************/
/*  TwoGammaFinder_data.cxx              */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// May 2021

#include "TwoGammaFinder_data.hxx"

int main(int argc, char **argv) {

  gDataKind = "data";

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  /*** DATA STRUCTURES ***/

  // input
  rec_i t;

  // output - mix
  rec_m m;
  rec_eta eta;

  /*** INPUT ***/

  TFile *InputRootFile = new TFile(gInputFile, "READ");
  
  TTree *tree = InputRootFile->Get<TTree>("ntuple_data");
  tree->SetBranchStatus("*", 0);           // only read what's necessary
  SetMinimalBranches_REC(tree, t);

  /*** OUTPUT ***/

  TFile *OutputRootFile = new TFile(gOutputFile, "RECREATE", "Eta Meson Filtered Combinations");

  TTree *tMix = new TTree("mix", "Combination of particles");
  SetMixBranches_REC(tMix, m, eta);

  /*** DECLARATIONS ***/

  // data counting variables
  Int_t nGammaThisEvent = 0;

  std::vector<int> gammaVector;

  std::vector<int> currentComb;

  std::vector<std::vector<int>> combVector;

  // definition of variables for event-mixing
  Int_t currentTargType;
  TRandom3 r;  // variable to create random event numbers
  Int_t prevRNG = 0;
  Int_t rng;

  Int_t currentEvent, previousEvent;
  Int_t nEntries = (Int_t)tree->GetEntries();
#ifdef DEBUG
  nEntries = 500;
#endif

  /*** START ***/

  // loop in entries
  for (Int_t i = 0; i <= nEntries; i++) {
    tree->GetEntry(i);
    currentEvent = (Int_t)t.evnt;
    currentTargType = (Int_t)t.TargType;  // necessary for event-mixing
    
    // prevents repetition of same event
    if (i > 0) {
      tree->GetEntry(i - 1);
      previousEvent = (Int_t)t.evnt;
      if (previousEvent == currentEvent) continue;
    }

#ifdef DEBUG
    std::cout << "Current event number: " << currentEvent << std::endl;
    std::cout << "Current entry number: " << i << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
#endif

    // count particles in the current event
    for (Int_t j = i; j <= nEntries; j++) {
      tree->GetEntry(j);
      if (currentEvent == (Int_t)t.evnt) {
#ifdef DEBUG
        std::cout << "  Entry number: " << j << std::endl;
        std::cout << "  pid    =      " << t.pid << std::endl;
        std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
#endif
        // count the particles
        if (t.pid == (Float_t)22)
          gammaVector.push_back(j);
      } else {
        break;
      }
    }

    // update counter
    nGammaThisEvent = gammaVector.size();

#ifdef DEBUG
    std::cout << "  nGamma   = " << nGammaThisEvent << std::endl;
    std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
#endif

    // turn on all input leaves
    tree->SetBranchStatus("*", 1);
    SetInputBranches_REC(tree, t);

    /*** COMBINE ***/

    // eta candidate appeared
    if (nGammaThisEvent >= 2) {
      for (Int_t iGamma = 0; iGamma < (nGammaThisEvent - 1); iGamma++) {
	currentComb.push_back(gammaVector[iGamma]);
	for (Int_t jGamma = iGamma + 1; jGamma < nGammaThisEvent; jGamma++) {
	  currentComb.push_back(gammaVector[jGamma]);
#ifdef DEBUG
	  std::cout << "currentComb = {" << currentComb[0] << ", " << currentComb[1] << "}" << std::endl;
#endif
	  // fill vector
	  combVector.push_back(currentComb);
	  currentComb.pop_back();
	}  // end of loop in gamma 2
	currentComb.pop_back();
      }  // end of loop in gamma 1
    }    // end of at-least-one-eta condition

    /*** EVENT-MIXING ***/
    
    if (gMixData) {
      // duplicate combinations vector content
      Size_t prelSIZ = combVector.size(); // to remain unchanged when iterating
      for (Size_t s = 0; s < prelSIZ; s++) {
	currentComb.push_back(combVector[s][0]);
	currentComb.push_back(combVector[s][1]);
	combVector.push_back(currentComb);
	currentComb.pop_back();
	currentComb.pop_back();
      }
      // (first half)
      // loop on possible combinations, each desired particle will be swapped
      for (Size_t s = 0; s < combVector.size()/2; s++) {
	// choose a random entry
	while (1) {
	  rng = r.Integer(nEntries);
	  tree->GetEntry(rng);
	  // check if it corresponds to the desired particle, same target and it's different from previous random entry
	  if ((Int_t)t.pid == gParticleToSwap && (Int_t)t.TargType == currentTargType && rng != prevRNG && rng != combVector[s][0]) {
	    // change second photon of the combination
	    combVector[s][1] = rng;
	    prevRNG = rng;
	    break;
	  }
	}
      }
      // (second half)
      // loop on possible combinations, each desired particle will be swapped
      for (Size_t s = combVector.size()/2; s < combVector.size(); s++) {
	// choose a random entry
	while (1) {
	  rng = r.Integer(nEntries);
	  tree->GetEntry(rng);
	  // check if it corresponds to the desired particle, same target and it's different from previous random entry
	  if ((Int_t)t.pid == gParticleToSwap && (Int_t)t.TargType == currentTargType && rng != prevRNG && rng != combVector[s][1]) {
	    // change second photon of the combination
	    combVector[s][0] = rng;
	    prevRNG = rng;
	    break;
	  }
	}
      }
    }

    /*** FILL MIX ***/

    // candidate appeared
    for (Size_t cc = 0; cc < combVector.size(); cc++) {  // loop on combinations
#ifdef DEBUG
      std::cout << "combVector[" << cc << "] = {" << combVector[cc][0] << ", " << combVector[cc][1] << "}" << std::endl;
#endif
      for (Int_t pp = 0; pp < 2; pp++) {                       // loop on final state particles
        tree->GetEntry(combVector[cc][pp]);
        AssignMixVar_REC(t, m, combVector[cc][pp], pp);
      }  // end of loop on fs particles
      AssignMoreVar_REC(m, nGammaThisEvent, cc);
      AssignEtaVar_REC(m, eta);
      // fill
      tMix->Fill();
    }  // end of loop on combinations

    /*** RESET ***/

    // reset counters
    nGammaThisEvent = 0;

    // reset vectors
    gammaVector.clear();

    currentComb.clear();
    combVector.clear();

#ifdef DEBUG
    std::cout << "  !! Finished event" << std::endl;
    std::cout << std::endl;
#endif
  }  // end of loop in entries

  /*** WRITE ***/

  OutputRootFile->Write();
  OutputRootFile->Close();

  std::cout << "This file has been created: " << gOutputFile << std::endl;

  return 0;
}
