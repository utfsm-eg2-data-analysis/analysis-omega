/*****************************************/
/*  FilterNCombine_mix.cxx               */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// Slight changes to FilterNCombine
// February 2021

#include "FilterNCombine_mix.hxx"

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  /*** DECLARATIONS ***/

  // data counting variables
  Int_t nPipThisEvent = 0;
  Int_t nPimThisEvent = 0;
  Int_t nGammaThisEvent = 0;

  std::vector<int> gammaVector;
  std::vector<int> pipVector;
  std::vector<int> pimVector;

  std::vector<int> currentComb;

  std::vector<std::vector<int>> combVector;

  /*** DATA STRUCTURES ***/

  // input
  rec_i t;

  // output - mix
  rec_m m;
  rec_pi0 pi0;
  rec_w w;

  /*** INPUT ***/

  TChain *tree = new TChain();
  tree->Add(gInputFile + "/ntuple_data");  // input

  /*** OUTPUT ***/

  TFile *rootFile = new TFile(gOutputFile, "RECREATE", "Omega Meson Filtered Combinations");

  TTree *tMix = new TTree("mix", "Combination of particles");
  SetMixBranches_REC(tMix, m, pi0, w);

  /*** START ***/

  // turn off every leaf, only read what's necessary
  tree->SetBranchStatus("*", 0);
  SetMinimalBranches_REC(tree, t);

  Int_t nEntries = (Int_t) tree->GetEntries();  // 500 for testing
  Int_t currentEvent, previousEvent;

  // definition of variables for event-mixing
  std::vector<int> nParticlesSwapped = {0, 0, 0}; // counter, 3 values for pip, pim, gamma
  std::vector<int> maxParticlesToSwap = {0, 0, 0}; // 3 values for pip, pim, gamma
  std::vector<int> ParticleToSwap = {211, -211, 22}; // non-global
  std::vector<std::vector<int>> swapVector;
  swapVector.resize(3); // 3 vectors for pip, pim, gamma
  Int_t currentTargType;
  TRandom3 r;  // variable to create random event numbers
  Int_t prevRNG = 0;
  Int_t rng;

  Int_t swapFirstIndex, swapLastIndex;
  if (gParticleToSwap == 1) {
    swapFirstIndex = 0;
    swapLastIndex = 3;
  } else {
    if (gParticleToSwap == 211)
      swapFirstIndex = 0;
    else if (gParticleToSwap == -211)
      swapFirstIndex = 1;
    else if (gParticleToSwap == 22)
      swapFirstIndex = 2;
    swapLastIndex = swapFirstIndex + 1;
  }

  // loop in entries
  for (Int_t i = 0; i <= nEntries; i++) {
    tree->GetEntry(i);
    currentEvent = (Int_t)t.evnt;
    currentTargType = (Int_t)t.TargType; // necessary for event-mixing
    
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
        else if (t.pid == (Float_t)211)
          pipVector.push_back(j);
        else if (t.pid == (Float_t)-211)
          pimVector.push_back(j);
      } else {
        break;
      }
    }

    /*** EVENT-MIXING ***/
    // for the regular cases (pid=211,-211,22), only one component is used
    
    maxParticlesToSwap[0] = (Int_t) pipVector.size();
    maxParticlesToSwap[1] = (Int_t) pimVector.size();
    maxParticlesToSwap[2] = (Int_t) gammaVector.size();
    
    swapVector[0].resize(maxParticlesToSwap[0]);
    swapVector[1].resize(maxParticlesToSwap[1]);
    swapVector[2].resize(maxParticlesToSwap[2]);

    // swap them all!
    for (Int_t s = swapFirstIndex; s < swapLastIndex; s++) {
      // repeat the regular case three times
      while (nParticlesSwapped[s] < maxParticlesToSwap[s]) {
	// insert randomness!
	rng = r.Integer(nEntries);
	tree->GetEntry(rng);
	if ((Int_t)t.pid == ParticleToSwap[s] && (Int_t)t.TargType == currentTargType && rng != prevRNG) {
	  swapVector[s][nParticlesSwapped[s]] = rng; // swap particle
	  nParticlesSwapped[s]++;
	  prevRNG = rng;
	}
      }
    }

    // important conditions, don't overwrite vectors with empty vectors
    if (gParticleToSwap == 211) {
      pipVector = swapVector[0];
    } else if (gParticleToSwap == -211) {
      pimVector = swapVector[1];
    } else if (gParticleToSwap == 22) {
      gammaVector = swapVector[2];
    } else if (gParticleToSwap == 1) {
      pipVector = swapVector[0];
      pimVector = swapVector[1];
      gammaVector = swapVector[2];
    }
    
    nPipThisEvent = pipVector.size();
    nPimThisEvent = pimVector.size();
    nGammaThisEvent = gammaVector.size();

#ifdef DEBUG
    std::cout << "  nPip     = " << nPipThisEvent     << std::endl;
    std::cout << "  nPim     = " << nPimThisEvent     << std::endl;
    std::cout << "  nGamma   = " << nGammaThisEvent   << std::endl;
    std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
#endif

    // turn on all input leaves
    tree->SetBranchStatus("*", 1);
    SetInputBranches_REC(tree, t);

    /*** COMBINE ***/

    // candidate appeared
    if (nPipThisEvent >= 1 && nPimThisEvent >= 1 && nGammaThisEvent >= 2) {
      for (Int_t iPip = 0; iPip < nPipThisEvent; iPip++) {
        currentComb.push_back(pipVector[iPip]);
        for (Int_t iPim = 0; iPim < nPimThisEvent; iPim++) {
          currentComb.push_back(pimVector[iPim]);
          for (Int_t iGamma = 0; iGamma < (nGammaThisEvent - 1); iGamma++) {
            currentComb.push_back(gammaVector[iGamma]);
            for (Int_t jGamma = iGamma + 1; jGamma < nGammaThisEvent; jGamma++) {
              currentComb.push_back(gammaVector[jGamma]);
	      
#ifdef DEBUG
	      std::cout << "currentComb = {" << currentComb[0] << ", " << currentComb[1] << ", "  << currentComb[2] << ", " << currentComb[3] << "}" << std::endl;
#endif
              // fill vector
              combVector.push_back(currentComb);
              currentComb.pop_back();
            }  // end of loop in gamma 2
            currentComb.pop_back();
          }  // end of loop in gamma 1
          currentComb.pop_back();
        }  // end of loop in pi-
        currentComb.pop_back();
      }  // end of loop in pi+
    }    // end of at-least-one-omega condition

    /*** FILL MIX ***/

    // candidate appeared
    for (Int_t cc = 0; cc < (Int_t)combVector.size(); cc++) {  // loop on combinations
      for (Int_t pp = 0; pp < 4; pp++) {                       // loop on final state particles
        tree->GetEntry(combVector[cc][pp]);
        AssignMixVar_REC(t, m, combVector[cc][pp], pp);
      }  // end of loop on fs particles
      AssignMoreVar_REC(m, nPipThisEvent, nPimThisEvent, nGammaThisEvent, cc);
      AssignPi0Var_REC(m, pi0);
      AssignOmegaVar_REC(m, pi0, w);
      // fill
      tMix->Fill();
    }  // end of loop on combinations

    /*** RESET ***/

    // reset counters
    nPipThisEvent = 0;
    nPimThisEvent = 0;
    nGammaThisEvent = 0;
    nParticlesSwapped[0] = 0;
    nParticlesSwapped[1] = 0;
    nParticlesSwapped[2] = 0;
    
    // reset vectors
    pipVector.clear();
    pimVector.clear();
    gammaVector.clear();
    swapVector[0].clear();
    swapVector[1].clear();
    swapVector[2].clear();
    
    currentComb.clear();
    combVector.clear();

#ifdef DEBUG
    std::cout << "  !! Finished event" << std::endl;
    std::cout << std::endl;
#endif
  }  // end of loop in entries

  /*** WRITE ***/

  rootFile->Write();
  rootFile->Close();

  std::cout << "This file has been created: " << gOutputFile << std::endl;

  return 0;
}
