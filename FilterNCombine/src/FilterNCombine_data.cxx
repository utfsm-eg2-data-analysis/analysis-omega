/*****************************************/
/*  FilterNCombine_data.cxx              */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// December 2020

#include "FilterNCombine_data.hxx"

int main(int argc, char **argv) {
  gDataKind = "data";

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

  Int_t Ne = (Int_t)tree->GetEntries();  // 500 for testing
  Int_t currentEvent, previousEvent;

  // loop in entries
  for (Int_t i = 0; i <= Ne; i++) {
    tree->GetEntry(i);
    currentEvent = (Int_t)t.evnt;

    // prevents repetition of same event
    if (i > 0) {
      tree->GetEntry(i - 1);
      previousEvent = (Int_t)t.evnt;
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
      if (currentEvent == (Int_t)t.evnt) {
        // commentary
        /*
        std::cout << "  Entry number: " << j << std::endl;
        std::cout << "  pid    =      " << t.pid << std::endl;
        std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
        */
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

    // commentary
    /*
    std::cout << "  nPip     = " << nPipThisEvent     << std::endl;
    std::cout << "  nPim     = " << nPimThisEvent     << std::endl;
    std::cout << "  nGamma   = " << nGammaThisEvent   << std::endl;
    std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    */

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
              // commentary
              // std::cout << "currentComb = {" << currentComb[0] << ", " << currentComb[1] << ", "  << currentComb[2] << ", " << currentComb[3] << "}" << std::endl;
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
  }  // end of loop in entries

  /*** WRITE ***/

  rootFile->Write();
  rootFile->Close();

  std::cout << "This file has been created: " << gOutputFile << std::endl;

  return 0;
}
