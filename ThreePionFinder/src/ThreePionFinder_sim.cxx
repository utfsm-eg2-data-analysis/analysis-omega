/*****************************************/
/*  ThreePionFinder_sim.cxx              */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// September 2021

#include "ThreePionFinder_sim.hxx"

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
  pi0_t pi0_out, mc_pi0_out;
  omega_t omega_out, mc_omega_out;

  /*** INPUT ***/

  TFile *InputRootFile = new TFile(gInputFile, "READ");

  TTree *tree = (TTree *)InputRootFile->Get("ntuple_sim");
  tree->SetBranchStatus("*", 1);
  SetInputTree_REC(tree, elec_in, part_in);
  if (!gMixReconstructed) {
    SetInputTree_GEN(tree, mc_elec_in, mc_part_in);
  }

  /*** OUTPUT ***/

  TFile *OutputRootFile = new TFile(gOutputFile, "RECREATE", "Omega Meson Candidates");

  TTree *tMix = new TTree("mix", "Combination of particles");
  SetOutputTree_REC(tMix, stable_out, pi0_out, omega_out);
  if (!gMixReconstructed) {
    SetOutputTree_GEN(tMix, mc_stable_out, mc_pi0_out, mc_omega_out);
  }

  // variables to tag the decay channel of interest
  Int_t nMCPipFromOmega = 0;    // count the number of Pid == 211 that have ParentID == 223
  Int_t nMCPimFromOmega = 0;    // count the number of Pid == -211 that have ParentID == 223
  Int_t nMCGammaFromOmega = 0;  // count the number of Pid == 22 that have ParentID == 223
  Bool_t flagOmega2PPGG = 0;    // if and only if 1 gen. pi+, 1 gen. pi- & 2 gen. gammas have ParentID == 223

  // additional branches to look for the decay channel of interest
  tMix->Branch("mc_Omega2PPGG", &flagOmega2PPGG);

  /*** DECLARATIONS ***/

  // gsim counting variables
  Int_t nMCPipThisEvent = 0;
  Int_t nMCPimThisEvent = 0;
  Int_t nMCGammaThisEvent = 0;

  std::vector<int> mc_gammaVector;
  std::vector<int> mc_pipVector;
  std::vector<int> mc_pimVector;

  std::vector<int> mc_currentOrig;  // exclusive
  std::vector<int> mc_currentComb;

  std::vector<std::vector<int>> mc_combVector;

  // simrec counting variables
  Int_t nPipThisEvent = 0;
  Int_t nPimThisEvent = 0;
  Int_t nGammaThisEvent = 0;

  std::vector<int> gammaVector;
  std::vector<int> pipVector;
  std::vector<int> pimVector;

  std::vector<int> currentComb;

  std::vector<std::vector<int>> combVector;

  // definition of variables for event-mixing
  TRandom3 r;  // variable to create random event numbers
  Int_t rng;
  Int_t ParticleIndex =
      0 * (gParticleToSwap == 211) + 1 * (gParticleToSwap == -211) + 2 * (gParticleToSwap == 111) + 0 * (gParticleToSwap == 999);
  Int_t LastIndex = ParticleIndex + 1 * (gParticleToSwap == 211 || gParticleToSwap == -211 || gParticleToSwap == 111) +
                    3 * (gParticleToSwap == 999);  // generalization
  Int_t ParticleToSwap[3] = {211, -211, 22};       // generalization

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
        } else if (part_in.pid == (Float_t)211) {
          pipVector.push_back(j);
        } else if (part_in.pid == (Float_t)-211) {
          pimVector.push_back(j);
        }
        // count the gsim particles
        if (mc_part_in.pid == (Float_t)22) {
          mc_gammaVector.push_back(j);
          // decay channel of interest: count how many gammas come from an omega decay
          if (mc_part_in.ParentID == (Float_t)223) {
            nMCGammaFromOmega++;
          }
        } else if (mc_part_in.pid == (Float_t)211) {
          mc_pipVector.push_back(j);
          // decay channel of interest: count how many pi+ come from an omega decay
          if (mc_part_in.ParentID == (Float_t)223) {
            nMCPipFromOmega++;
          }
        } else if (mc_part_in.pid == (Float_t)-211) {
          mc_pimVector.push_back(j);
          // decay channel of interest: count how many pi- come from an omega decay
          if (mc_part_in.ParentID == (Float_t)223) {
            nMCPimFromOmega++;
          }
        }
      } else {
        break;
      }
    }

    // update counters
    nPipThisEvent = pipVector.size();
    nPimThisEvent = pimVector.size();
    nGammaThisEvent = gammaVector.size();

    nMCPipThisEvent = mc_pipVector.size();
    nMCPimThisEvent = mc_pimVector.size();
    nMCGammaThisEvent = mc_gammaVector.size();

    /*** COMBINE ***/

    // generated omega candidate appeared
    if (nMCPipThisEvent >= 1 && nMCPimThisEvent >= 1 && nMCGammaThisEvent >= 2) {
      for (Int_t iPip = 0; iPip < nMCPipThisEvent; iPip++) {
        mc_currentComb.push_back(mc_pipVector[iPip]);
        for (Int_t iPim = 0; iPim < nMCPimThisEvent; iPim++) {
          mc_currentComb.push_back(mc_pimVector[iPim]);
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
          mc_currentComb.pop_back();
        }  // end of loop in pi-
        mc_currentComb.pop_back();
      }  // end of loop in pi+
    }    // end of at-least-one-omega condition

    // reconstructed omega candidate appeared
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

    /*** EVENT MIXING OR OMEGA MATCHING ***/

    // declare output vectors - initially empty
    std::vector<std::vector<int>> mc_newVector;
    std::vector<int> auxVector;
    std::vector<std::vector<int>> newVector;
    std::vector<int> nullVector = {-1, -1, -1, -1};

    if (gMixReconstructed) {

      // do the event mixing for sim. reconstructed particles
      newVector = combVector;
      for (Int_t Index = ParticleIndex; Index < LastIndex; Index++) {
        // when choosing to change pi0, search for one gamma, it stays at 22
        if (gParticleToSwap == 111) {
          gParticleToSwap = 22;
        }
        // loop on possible combinations, each desired particle will be swapped
        for (Size_t s = 0; s < newVector.size(); s++) {
          // choose a random entry
          while (1) {
            rng = r.Integer(nEntries);
            tree->GetEntry(rng);
            // check if it corresponds to the desired particle, same target and it's different from previous random entry
            if (((Int_t)part_in.pid == gParticleToSwap || (Int_t)part_in.pid == ParticleToSwap[Index])) {
              newVector[s][Index] = rng;
              // in the case of one gamma, find its partner to form a pi0, which can be the previous or next entry
              // and save it into the spot of the 4th particle
              if (gParticleToSwap == 22 || ParticleToSwap[Index] == 22) {
                tree->GetEntry(rng - 1);
                if ((Int_t)part_in.pid == 22) {
                  newVector[s][Index + 1] = rng - 1;
                }
                tree->GetEntry(rng + 1);
                if ((Int_t)part_in.pid == 22) {
                  newVector[s][Index + 1] = rng + 1;
                }
              }
              break;
            }
          }
        }
      }

    } else {

      // regular case: no event-mixing
      // if the final state particles are already match, then the omegas are also matched
      for (Size_t m = 0; m < mc_combVector.size(); m++) {
        for (Size_t n = 0; n < combVector.size(); n++) {
          Bool_t fMatchingCondition = (mc_combVector[m] == combVector[n]);  // compare entry numbers
          if (fMatchingCondition) {
            mc_newVector.push_back(mc_combVector[m]);
            newVector.push_back(combVector[n]);
          }
        }
      }
      // fill remaining generated omegas
      for (Size_t m = 0; m < mc_combVector.size(); m++) {
        if (std::find(mc_newVector.begin(), mc_newVector.end(), mc_combVector[m]) == mc_newVector.end()) {
          // std::find function returns an iterator to the first element in the range ["begin","end"[ that compares equal to "row"
          // if no such element is found, the function returns "end", this is done to prevent particles that already matched
          mc_newVector.push_back(mc_combVector[m]);  // add gsim_row to gsim_new
          newVector.push_back(nullVector);           // add null simrec
        }
      }
      // fill remaining reconstructed omegas
      for (Size_t n = 0; n < combVector.size(); n++) {
        if (std::find(newVector.begin(), newVector.end(), combVector[n]) == newVector.end()) {
          newVector.push_back(combVector[n]);  // add simrec_row to simrec_new
          mc_newVector.push_back(nullVector);  // add null gsim
        }
      }
    }

    /*** FILL MIX ***/

    if (gMixReconstructed) {

      // after mixing reconstructed simulations, fill just as data
      // candidate appeared for SIMREC
      for (Size_t cc = 0; cc < newVector.size(); cc++) {  // loop on combinations
        for (Int_t pp = 0; pp < 4; pp++) {                // loop on final state particles
          tree->GetEntry(newVector[cc][pp]);
          WriteStableVars_REC(elec_in, part_in, stable_out, newVector[cc][pp], pp);
        }  // end of loop on fs particles
        WritePi0Vars(stable_out, pi0_out);
        WriteOmegaVars(stable_out, pi0_out, omega_out);
        NullOutputVars(mc_stable_out, mc_pi0_out, mc_omega_out);
        // fill
        tMix->Fill();
      }  // end of loop on combinations

    } else {

      // regular case: no event-mixing, attempts to do a matching
      // candidate appeared for MC
      for (Size_t cc = 0; cc < mc_newVector.size(); cc++) {
        // assign generated particles
        if (mc_newVector[cc][0] != -1) {
          for (Int_t gg = 0; gg < 4; gg++) {  // loop on final state particles
            tree->GetEntry(mc_newVector[cc][gg]);
            WriteStableVars_GEN(mc_elec_in, mc_part_in, mc_stable_out, mc_newVector[cc][gg], gg);
            stable_out.Event = elec_in.evnt;                                                            // don't forget the evnt!
            flagOmega2PPGG = (nMCPipFromOmega == 1 && nMCPimFromOmega == 1 && nMCGammaFromOmega == 2);  // decay channel of interest
          }
          WritePi0Vars(mc_stable_out, mc_pi0_out);
          WriteOmegaVars(mc_stable_out, mc_pi0_out, mc_omega_out);
        } else {
          NullOutputVars(mc_stable_out, mc_pi0_out, mc_omega_out);
          flagOmega2PPGG = INVLD;  // decay channel of interest
        }
        // assign sim reconstructed particles
        if (newVector[cc][0] != -1) {
          for (Int_t rr = 0; rr < 4; rr++) {  // loop on final state particles
            tree->GetEntry(newVector[cc][rr]);
            WriteStableVars_REC(elec_in, part_in, stable_out, newVector[cc][rr], rr);
          }
          WritePi0Vars(stable_out, pi0_out);
          WriteOmegaVars(stable_out, pi0_out, omega_out);
        } else {
          NullOutputVars(stable_out, pi0_out, omega_out);
        }
        // fill
        tMix->Fill();
      }  // end of loop on combinations
    }

    /*** RESET ***/

    // reset gsim counters
    nMCPipThisEvent = 0;
    nMCPimThisEvent = 0;
    nMCGammaThisEvent = 0;
    nMCPipFromOmega = 0;
    nMCPimFromOmega = 0;
    nMCGammaFromOmega = 0;
    flagOmega2PPGG = 0;

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

    mc_newVector.clear();
    newVector.clear();
  }  // end of loop in entries

  /*** WRITE ***/

  OutputRootFile->Write();
  OutputRootFile->Close();

  std::cout << "This file has been created: " << gOutputFile << std::endl;

  return 0;
}
