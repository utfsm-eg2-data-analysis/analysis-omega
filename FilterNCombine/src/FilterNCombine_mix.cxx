/*****************************************/
/*  FilterNCombine_mix.cxx               */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// February 2021

#include "FilterNCombine_mix.hxx"

int main(int argc, char **argv) {

  gDataKind = "mix";

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

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

  // definition of variables for event-mixing
  Int_t currentTargType;
  TRandom3 r;  // variable to create random event numbers
  Int_t prevRNG = 0;
  Int_t rng;
  Int_t ParticleIndex = 0 * (gParticleToSwap == 211) + 1 * (gParticleToSwap == -211) + 2 * (gParticleToSwap == 111) + 0 * (gParticleToSwap == 999);

  // generalization
  Int_t LastIndex = ParticleIndex + 1 * (gParticleToSwap == 211 || gParticleToSwap == -211 || gParticleToSwap == 111) + 3 * (gParticleToSwap == 999);
  Int_t ParticleToSwap[3] = {211, -211, 22};

  // turn off every leaf, only read what's necessary
  tree->SetBranchStatus("*", 0);
  SetMinimalBranches_REC(tree, t);

  Int_t nEntries = (Int_t)tree->GetEntries();  // 500 for testing
  Int_t currentEvent, previousEvent;

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
        else if (t.pid == (Float_t)211)
          pipVector.push_back(j);
        else if (t.pid == (Float_t)-211)
          pimVector.push_back(j);
      } else {
        break;
      }
    }

    nPipThisEvent = pipVector.size();
    nPimThisEvent = pimVector.size();
    nGammaThisEvent = gammaVector.size();

#ifdef DEBUG
    std::cout << "  nPip     = " << nPipThisEvent << std::endl;
    std::cout << "  nPim     = " << nPimThisEvent << std::endl;
    std::cout << "  nGamma   = " << nGammaThisEvent << std::endl;
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
              std::cout << "currentComb = {" << currentComb[0] << ", " << currentComb[1] << ", " << currentComb[2] << ", " << currentComb[3] << "}" << std::endl;
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

    /*** EVENT-MIXING ***/

    // generalization
    for (Int_t Index = ParticleIndex; Index < LastIndex; Index++) {
      // when choosing to change pi0, search for one gamma, it stays at 22
      if (gParticleToSwap == 111) gParticleToSwap = 22;
      // loop on possible combinations, each desired particle will be swapped
      for (Size_t s = 0; s < combVector.size(); s++) {
        // choose a random entry
        while (1) {
          rng = r.Integer(nEntries);
          tree->GetEntry(rng);
          // check if it corresponds to the desired particle, same target and it's different from previous random entry
          if (((Int_t)t.pid == gParticleToSwap || (Int_t)t.pid == ParticleToSwap[Index]) && (Int_t)t.TargType == currentTargType && rng != prevRNG) {
            combVector[s][Index] = rng;
            // in the case of one gamma, find its partner to form a pi0, which can be the previous or next entry
            // and save it into the spot of the 4th particle
            if (gParticleToSwap == 22 || ParticleToSwap[Index] == 22) {
              tree->GetEntry(rng - 1);
              if ((Int_t)t.pid == 22) combVector[s][Index + 1] = rng - 1;
              tree->GetEntry(rng + 1);
              if ((Int_t)t.pid == 22) combVector[s][Index + 1] = rng + 1;
            }
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
      std::cout << "combVector[" << cc << "] = {" << combVector[cc][0] << ", " << combVector[cc][1] << ", " << combVector[cc][2] << ", " << combVector[cc][3] << "}" << std::endl;
#endif
      for (Int_t pp = 0; pp < 4; pp++) {  // loop on final state particles
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

    // reset vectors
    pipVector.clear();
    pimVector.clear();
    gammaVector.clear();

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
