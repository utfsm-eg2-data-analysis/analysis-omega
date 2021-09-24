/*****************************************/
/*  TwoGammaFinder_data.cxx              */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// September 2021

#include "TwoGammaFinder_data.hxx"

int main(int argc, char **argv) {

  gDataKind = "data";

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  /*** DATA STRUCTURES ***/

  // input
  elec_t elec_in;
  part_t part_in;

  // output
  stable_t gammas_out;
  eta_t eta_out;

  /*** INPUT ***/

  TFile *InputRootFile = new TFile(gInputFile, "READ");

  TTree *tree = InputRootFile->Get<TTree>("ntuple_data");
  tree->SetBranchStatus("*", 1);  // turn on all input leaves
  SetInputTree_REC(tree, elec_in, part_in);

  /*** OUTPUT ***/

  TFile *OutputRootFile = new TFile(gOutputFile, "RECREATE", "Eta Meson Candidates");

  TTree *tMix = new TTree("mix", "Combination of particles");
  SetOutputTree_REC(tMix, gammas_out, eta_out);

  /*** DECLARATIONS ***/

  // data counting variables
  Int_t nGammaThisEvent = 0;

  std::vector<int> gammaVector;              // vector to store the entry number of all gammas in one event
  std::vector<int> currentComb;              // vector to store partial combinations of gammas
  std::vector<std::vector<int>> combVector;  // array to store all possible combinations of gammas

  Int_t currentEvent, previousEvent;
  Int_t nEntries = (Int_t)tree->GetEntries();

  /*** START ***/

  // loop in entries
  for (Int_t i = 0; i < nEntries; i++) {
    tree->GetEntry(i);
    currentEvent = (Int_t)elec_in.evnt;

    // prevent repetition of same event
    if (i > 0) {
      tree->GetEntry(i - 1);
      previousEvent = (Int_t)elec_in.evnt;
      if (previousEvent == currentEvent) {
        continue;
      }
    }

    // count gammas in current event and add their entry number to vector
    for (Int_t j = i; j < nEntries; j++) {
      tree->GetEntry(j);
      if (currentEvent == (Int_t)elec_in.evnt) {
        if (part_in.pid == (Float_t)22) {
          gammaVector.push_back(j);
        }
      } else {
        break;
      }
    }

    // update counter
    nGammaThisEvent = gammaVector.size();

    /*** COMBINE ***/

    // eta candidate appeared
    if (nGammaThisEvent >= 2) {
      for (Int_t iGamma = 0; iGamma < (nGammaThisEvent - 1); iGamma++) {
        currentComb.push_back(gammaVector[iGamma]);
        for (Int_t jGamma = iGamma + 1; jGamma < nGammaThisEvent; jGamma++) {
          currentComb.push_back(gammaVector[jGamma]);
          // fill vector
          combVector.push_back(currentComb);
          currentComb.pop_back();
        }  // end of loop in gamma 2
        currentComb.pop_back();
      }  // end of loop in gamma 1
    }    // end of at-least-one-eta condition

    /*** FILL MIX ***/

    // candidate appeared
    for (Size_t cc = 0; cc < combVector.size(); cc++) {  // loop on combinations
      for (Int_t pp = 0; pp < 2; pp++) {                 // loop on gammas
        tree->GetEntry(combVector[cc][pp]);
        WriteStableVars_REC(elec_in, part_in, gammas_out, combVector[cc][pp], pp);
      }  // end of loop on fs particles
      WriteEtaVars(gammas_out, eta_out);
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
  }  // end of loop in entries

  /*** WRITE ***/

  OutputRootFile->Write();
  OutputRootFile->Close();

  std::cout << "This file has been created: " << gOutputFile << std::endl;

  return 0;
}
