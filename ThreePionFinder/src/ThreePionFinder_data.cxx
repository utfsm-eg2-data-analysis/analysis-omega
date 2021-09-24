/*****************************************/
/*  ThreePionFinder_data.cxx             */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// September 2021

#include "ThreePionFinder_data.hxx"

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
  stable_t stable_out;
  pi0_t pi0_out;
  omega_t omega_out;

  /*** INPUT ***/

  TFile *InputRootFile = new TFile(gInputFile, "READ");

  TTree *tree = (TTree *)InputRootFile->Get("ntuple_data");
  tree->SetBranchStatus("*", 1);  // turn on all input leaves
  SetInputTree_REC(tree, elec_in, part_in);

  /*** OUTPUT ***/

  TFile *OutputRootFile = new TFile(gOutputFile, "RECREATE", "Omega Meson Candidates");

  TTree *tMix = new TTree("mix", "Combination of particles");
  SetOutputTree_REC(tMix, stable_out, pi0_out, omega_out);

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
  Int_t ParticleIndex =
      0 * (gParticleToSwap == 211) + 1 * (gParticleToSwap == -211) + 2 * (gParticleToSwap == 111) + 0 * (gParticleToSwap == 999);

  // generalization
  Int_t LastIndex =
      ParticleIndex + 1 * (gParticleToSwap == 211 || gParticleToSwap == -211 || gParticleToSwap == 111) + 3 * (gParticleToSwap == 999);
  Int_t ParticleToSwap[3] = {211, -211, 22};

  Int_t currentEvent, previousEvent;
  Int_t nEntries = (Int_t)tree->GetEntries();

  /*** START ***/

  // loop in entries
  for (Int_t i = 0; i < nEntries; i++) {
    tree->GetEntry(i);
    currentEvent = (Int_t)elec_in.evnt;
    currentTargType = (Int_t)elec_in.TargType;  // necessary for event-mixing

    // prevent repetition of same event
    if (i > 0) {
      tree->GetEntry(i - 1);
      previousEvent = (Int_t)elec_in.evnt;
      if (previousEvent == currentEvent) {
        continue;
      }
    }

    // count particles in the current event and add their entry number to different vectors
    for (Int_t j = i; j < nEntries; j++) {
      tree->GetEntry(j);
      if (currentEvent == (Int_t)elec_in.evnt) {
        if (part_in.pid == (Float_t)22) {
          gammaVector.push_back(j);
        } else if (part_in.pid == (Float_t)211) {
          pipVector.push_back(j);
        } else if (part_in.pid == (Float_t)-211) {
          pimVector.push_back(j);
        }
      } else {
        break;
      }
    }

    // update counters
    nPipThisEvent = pipVector.size();
    nPimThisEvent = pimVector.size();
    nGammaThisEvent = gammaVector.size();

    /*** COMBINE ***/

    // omega candidate appeared
    if (nPipThisEvent >= 1 && nPimThisEvent >= 1 && nGammaThisEvent >= 2) {
      for (Int_t iPip = 0; iPip < nPipThisEvent; iPip++) {
        currentComb.push_back(pipVector[iPip]);
        for (Int_t iPim = 0; iPim < nPimThisEvent; iPim++) {
          currentComb.push_back(pimVector[iPim]);
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
          currentComb.pop_back();
        }  // end of loop in pi-
        currentComb.pop_back();
      }  // end of loop in pi+
    }    // end of at-least-one-omega condition

    /*** EVENT-MIXING ***/

    if (gMixData) {
      // generalization
      for (Int_t Index = ParticleIndex; Index < LastIndex; Index++) {
        // when choosing to change pi0, search for one gamma, it stays at 22
        if (gParticleToSwap == 111) {
          gParticleToSwap = 22;
        }
        // loop on possible combinations, each desired particle will be swapped
        for (Size_t s = 0; s < combVector.size(); s++) {
          // choose a random entry
          while (1) {
            rng = r.Integer(nEntries);
            tree->GetEntry(rng);
            // check if it corresponds to the desired particle, same target and it's different from previous random entry
            if (((Int_t)part_in.pid == gParticleToSwap || (Int_t)part_in.pid == ParticleToSwap[Index]) &&
                (Int_t)elec_in.TargType == currentTargType && rng != prevRNG) {
              combVector[s][Index] = rng;
              // in the case of one gamma, find its partner to form a pi0, which can be the previous or next entry
              // and save it into the spot of the 4th particle
              if (gParticleToSwap == 22 || ParticleToSwap[Index] == 22) {
                tree->GetEntry(rng - 1);
                if ((Int_t)part_in.pid == 22) {
                  combVector[s][Index + 1] = rng - 1;
                }
                tree->GetEntry(rng + 1);
                if ((Int_t)part_in.pid == 22) {
                  combVector[s][Index + 1] = rng + 1;
                }
              }
              prevRNG = rng;
              break;
            }
          }
        }
      }
    }

    /*** FILL MIX ***/

    // candidate appeared
    for (Size_t cc = 0; cc < combVector.size(); cc++) {  // loop on combinations
      for (Int_t pp = 0; pp < 4; pp++) {                 // loop on final-state particles
        tree->GetEntry(combVector[cc][pp]);
        WriteStableVars_REC(elec_in, part_in, stable_out, combVector[cc][pp], pp);
      }  // end of loop on final-state particles
      WritePi0Vars(stable_out, pi0_out);
      WriteOmegaVars(stable_out, pi0_out, omega_out);
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
  }  // end of loop in entries

  /*** WRITE ***/

  OutputRootFile->Write();
  OutputRootFile->Close();

  std::cout << "This file has been created: " << gOutputFile << std::endl;

  return 0;
}
