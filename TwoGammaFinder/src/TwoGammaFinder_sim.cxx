/*****************************************/
/*  TwoGammaFinder_sim.cxx               */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// September 2021

#include "TwoGammaFinder_sim.hxx"

int main(int argc, char **argv) {

  gDataKind = "sim";

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  /*** DATA STRUCTURES ***/

  // input
  elec_t elec_in, mc_elec_in;
  part_t part_in, mc_part_in;

  // output
  stable_t stable_out, mc_stable_out;
  eta_t eta_out, mc_eta_out;

  /*** INPUT ***/

  TFile *InputRootFile = new TFile(gInputFile, "READ");

  TTree *tree = InputRootFile->Get<TTree>("ntuple_sim");
  tree->SetBranchStatus("*", 1);
  SetInputTree_REC(tree, elec_in, part_in);
  SetInputTree_GEN(tree, mc_elec_in, mc_part_in);

  /*** OUTPUT ***/

  TFile *OutputRootFile = new TFile(gOutputFile, "RECREATE", "Eta Meson Candidates");

  TTree *tMix = new TTree("mix", "Combination of particles");
  SetOutputTree_REC(tMix, stable_out, eta_out);
  SetOutputTree_GEN(tMix, mc_stable_out, mc_eta_out);

  // variables to tag the decay channel of interest
  Int_t nMCGammaFromOmega = 0;  // count the number of Pid == 22 that have ParentID == 221
  Bool_t flagEta2GG = 0;        // if and only if 2 generated gammas have ParentID == 221

  // additional branches to look for the decay channel of interest
  tMix->Branch("mc_Eta2GG", &flagEta2GG);

  /*** DECLARATIONS ***/

  // gsim counting variables
  Int_t nMCGammaThisEvent = 0;

  std::vector<int> mc_gammaVector;
  std::vector<int> mc_currentComb;
  std::vector<std::vector<int>> mc_combVector;

  // simrec counting variables
  Int_t nGammaThisEvent = 0;

  std::vector<int> gammaVector;
  std::vector<int> currentComb;
  std::vector<std::vector<int>> combVector;

  Int_t currentEvent, previousEvent;
  Int_t nEntries = (Int_t)tree->GetEntries();

  /*** START ***/

  // loop in entries
  for (Int_t i = 0; i < nEntries; i++) {
    tree->GetEntry(i);
    currentEvent = (Int_t)elec_in.evnt;

    // prevents repetition of same event
    if (i > 0) {
      tree->GetEntry(i - 1);
      previousEvent = (Int_t)elec_in.evnt;
      if (previousEvent == currentEvent) {
        continue;
      }
    }

    // count particles in the current event
    for (Int_t j = i; j < nEntries; j++) {
      tree->GetEntry(j);
      if (currentEvent == (Int_t)elec_in.evnt) {
        // count the simrec particles
        if (part_in.pid == (Float_t)22) {
          gammaVector.push_back(j);
        }
        // count the gsim particles
        if (mc_part_in.pid == (Float_t)22) {
          mc_gammaVector.push_back(j);
          // decay channel of interest: count how many gammas come from an eta decay
          if (mc_part_in.ParentID == (Float_t)221) {
            nMCGammaFromOmega++;
          }
        }
      } else {
        break;
      }
    }

    // update counters
    nGammaThisEvent = gammaVector.size();
    nMCGammaThisEvent = mc_gammaVector.size();

    /*** COMBINE ***/

    // generated eta candidate appeared
    if (nMCGammaThisEvent >= 2) {
      for (Int_t iGamma = 0; iGamma < (nMCGammaThisEvent - 1); iGamma++) {
        mc_currentComb.push_back(mc_gammaVector[iGamma]);
        for (Int_t jGamma = iGamma + 1; jGamma < nMCGammaThisEvent; jGamma++) {
          mc_currentComb.push_back(mc_gammaVector[jGamma]);
          // fill vector
          mc_combVector.push_back(mc_currentComb);
          mc_currentComb.pop_back();
        }  // end of loop in gamma 2
        mc_currentComb.pop_back();
      }  // end of loop in gamma 1
    }    // end of at-least-one-eta condition

    // reconstructed eta candidate appeared
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

    /*** ETA MATCHING ***/

    // declare output vectors - initially empty
    std::vector<std::vector<int>> mc_newVector;
    std::vector<int> auxVector;
    std::vector<std::vector<int>> newVector;
    std::vector<int> nullVector = {-1, -1};

    // if the final state particles are already match, then the etas are also matched
    for (Size_t m = 0; m < mc_combVector.size(); m++) {
      for (Size_t n = 0; n < combVector.size(); n++) {
        Bool_t fMatchingCondition = (mc_combVector[m] == combVector[n]);  // compare entry numbers
        if (fMatchingCondition) {
          mc_newVector.push_back(mc_combVector[m]);
          newVector.push_back(combVector[n]);
        }
      }
    }
    // fill remaining generated etas
    for (Size_t m = 0; m < mc_combVector.size(); m++) {
      if (std::find(mc_newVector.begin(), mc_newVector.end(), mc_combVector[m]) == mc_newVector.end()) {
        // std::find function returns an iterator to the first element in the range ["begin","end"[ that compares equal to "row"
        // if no such element is found, the function returns "end", this is done to prevent particles that already matched
        mc_newVector.push_back(mc_combVector[m]);  // add gsim_row to gsim_new
        newVector.push_back(nullVector);           // add null simrec
      }
    }
    // fill remaining sim. reconstructed etas
    for (Size_t n = 0; n < combVector.size(); n++) {
      if (std::find(newVector.begin(), newVector.end(), combVector[n]) == newVector.end()) {
        newVector.push_back(combVector[n]);  // add simrec_row to simrec_new
        mc_newVector.push_back(nullVector);  // add null gsim
      }
    }

    /*** FILL MIX ***/

    // regular case, attempts to do a matching
    // candidate appeared for MC (newVector.size() would have also functioned, because now both vectors have the same size)
    for (Size_t cc = 0; cc < mc_newVector.size(); cc++) {
      // assign generated particles
      if (mc_newVector[cc][0] != -1) {
        for (Int_t gg = 0; gg < 2; gg++) {  // loop on final state particles
          tree->GetEntry(mc_newVector[cc][gg]);
          WriteStableVars_GEN(mc_elec_in, mc_part_in, mc_stable_out, mc_newVector[cc][gg], gg);
          stable_out.Event = elec_in.evnt;        // don't forget the evnt!
          flagEta2GG = (nMCGammaFromOmega == 2);  // decay channel of interest: if and only if 2 gammas come from an eta
        }
        WriteEtaVars(mc_stable_out, mc_eta_out);
      } else {
        NullOutputVars(mc_stable_out, mc_eta_out);
        flagEta2GG = INVLD;  // decay channel of interest
      }
      // assign sim reconstructed particles
      if (newVector[cc][0] != -1) {
        for (Int_t rr = 0; rr < 2; rr++) {  // loop on final state particles
          tree->GetEntry(newVector[cc][rr]);
          WriteStableVars_REC(elec_in, part_in, stable_out, newVector[cc][rr], rr);
        }
        WriteEtaVars(stable_out, eta_out);
      } else {
        NullOutputVars(stable_out, eta_out);
      }
      // fill
      tMix->Fill();
    }  // end of loop on combinations

    /*** RESET ***/

    // reset counters
    nMCGammaThisEvent = 0;
    nMCGammaFromOmega = 0;
    flagEta2GG = 0;

    nGammaThisEvent = 0;

    // reset vectors
    mc_gammaVector.clear();
    mc_currentComb.clear();
    mc_combVector.clear();

    gammaVector.clear();
    currentComb.clear();
    combVector.clear();
    mc_newVector.clear();
    newVector.clear();
  }  // end of loop in entries

  /*** WRITE ***/

  OutputRootFile->Write();
  OutputRootFile->Close();

  std::cout << "This file has been created: " << gOutputFile << std::endl;

  return 0;
}
