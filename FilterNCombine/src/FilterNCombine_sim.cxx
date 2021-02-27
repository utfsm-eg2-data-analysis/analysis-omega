/*****************************************/
/*  FilterNCombine_sim.cxx               */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// February 2021

#include "FilterNCombine_sim.hxx"

int main(int argc, char **argv) {

  gDataKind = "sim";

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  /*** DATA STRUCTURES ***/

  // input
  rec_i t;
  gen_i mc_t;

  // output - mix
  rec_m m;
  rec_pi0 pi0;
  rec_w w;
  gen_m mc_m;
  gen_pi0 mc_pi0;
  gen_w mc_w;

  /*** INPUT ***/

  TFile *InputRootFile = new TFile(gInputFile, "READ");

  TTree *tree = InputRootFile->Get<TTree>("ntuple_sim");
  // request RAM for reading random entries faster
  // (TTree is optimized for sequential reading)
  tree->SetMaxVirtualSize(2.2 * (Int_t)tree->GetTotBytes());
  tree->LoadBaskets();

  TTree *tPip;
  TTree *tPim;
  TTree *tPi0;
  TBranch *bPip;
  TBranch *bPim;
  TBranch *bPi0;
  Int_t jPip, jPim, jPi0;
  Int_t nPip, nPim, nPi0;
  std::vector<Int_t> vPip, vPim, vPi0;
  if (gMixGenerated) {
    std::cout << "Preparing indices trees into vectors..." << std::endl;
    // pip
    tPip = InputRootFile->Get<TTree>("tPip");
    nPip = tPip->GetEntries();
    bPip = tPip->GetBranch("iPip");
    bPip->SetAddress(&jPip);
    vPip.reserve(nPip);
    for (Int_t i = 0; i < nPip; i++) {
      bPip->GetEntry(i);
      vPip.push_back(jPip);
    }
    // pim
    tPim = InputRootFile->Get<TTree>("tPim");
    nPim = tPim->GetEntries();
    bPim = tPim->GetBranch("iPim");
    bPim->SetAddress(&jPim);
    vPim.reserve(nPim);
    for (Int_t i = 0; i < nPim; i++) {
      bPim->GetEntry(i);
      vPim.push_back(jPim);
    }
    // pi0
    tPi0 = InputRootFile->Get<TTree>("tPi0");
    nPi0 = tPi0->GetEntries();
    bPi0 = tPi0->GetBranch("iPi0");
    bPi0->SetAddress(&jPi0);
    vPi0.reserve(nPi0);
    for (Int_t i = 0; i < nPi0; i++) {
      bPi0->GetEntry(i);
      vPi0.push_back(jPi0);
    }
  }

  /*** OUTPUT ***/

  TFile *OutputRootFile = new TFile(gOutputFile, "RECREATE", "Omega Meson Filtered Combinations");

  TTree *tMix = new TTree("mix", "Combination of particles");
  SetMixBranches_REC(tMix, m, pi0, w);
  SetMixBranches_GEN(tMix, mc_m, mc_pi0, mc_w);

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
  Int_t ParticleIndex = 0 * (gParticleToSwap == 211) + 1 * (gParticleToSwap == -211) + 2 * (gParticleToSwap == 111) + 0 * (gParticleToSwap == 999);
  Int_t LastIndex = ParticleIndex + 1 * (gParticleToSwap == 211 || gParticleToSwap == -211 || gParticleToSwap == 111) + 3 * (gParticleToSwap == 999);  // generalization
  Int_t ParticleToSwap[3] = {211, -211, 22};                                                                                                           // generalization

  // prepare branches
  tree->SetBranchStatus("*", 0);
  SetMinimalBranches_REC(tree, t);
  SetMinimalBranches_GEN(tree, mc_t);

  Int_t currentEvent, previousEvent;
  Int_t nEntries = (Int_t)tree->GetEntries();
  Int_t Start = 0;
#ifndef DEBUG
  if (gMixGenerated) {
    if (gParticleToSwap == 211) {
      nEntries = nEntries / 4;
    } else if (gParticleToSwap == -211) {
      Start = nEntries / 4;
      nEntries = nEntries / 2 + 1;
    } else if (gParticleToSwap == 111) {
      Start = nEntries / 2;
      nEntries = 3 * nEntries / 4 + 1;
    } else if (gParticleToSwap == 999) {
      Start = 3 * nEntries / 4;
    }
  }
#else
  nEntries = 10000;
#endif
  
  /*** START ***/

  // loop in entries
  for (Int_t i = Start; i < nEntries; i++) {
#ifndef DEBUG
    std::cout << (Double_t)i / (Double_t)nEntries * 100. << " %" << std::endl;
#endif
    tree->GetEntry(i);
    currentEvent = (Int_t)t.evnt;

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
        std::cout << "  mc_pid =      " << mc_t.pid << std::endl;
        std::cout << "  pid    =      " << t.pid << std::endl;
        std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
#endif
        // count the simrec particles
        if (t.pid == (Float_t)22)
          gammaVector.push_back(j);
        else if (t.pid == (Float_t)211)
          pipVector.push_back(j);
        else if (t.pid == (Float_t)-211)
          pimVector.push_back(j);
        // count the gsim particles
        if (mc_t.pid == (Float_t)22)
          mc_gammaVector.push_back(j);
        else if (mc_t.pid == (Float_t)211)
          mc_pipVector.push_back(j);
        else if (mc_t.pid == (Float_t)-211)
          mc_pimVector.push_back(j);
      } else {
        break;
      }
    }

    nPipThisEvent = pipVector.size();
    nPimThisEvent = pimVector.size();
    nGammaThisEvent = gammaVector.size();

    nMCPipThisEvent = mc_pipVector.size();
    nMCPimThisEvent = mc_pimVector.size();
    nMCGammaThisEvent = mc_gammaVector.size();

#ifdef DEBUG
    std::cout << "  nPip     = " << nPipThisEvent << std::endl;
    std::cout << "  nPim     = " << nPimThisEvent << std::endl;
    std::cout << "  nGamma   = " << nGammaThisEvent << std::endl;
    std::cout << "  nMCPip   = " << nMCPipThisEvent << std::endl;
    std::cout << "  nMCPim   = " << nMCPimThisEvent << std::endl;
    std::cout << "  nMCGamma = " << nMCGammaThisEvent << std::endl;
    std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
#endif

    // init all input branches
    tree->SetBranchStatus("*", 1);
    SetInputBranches_REC(tree, t);
    SetInputBranches_GEN(tree, mc_t);

    /*** COMBINE ***/

    // candidate appeared for MC
    if (nMCPipThisEvent >= 1 && nMCPimThisEvent >= 1 && nMCGammaThisEvent >= 2) {
      for (Int_t iPip = 0; iPip < nMCPipThisEvent; iPip++) {
        mc_currentComb.push_back(mc_pipVector[iPip]);
        for (Int_t iPim = 0; iPim < nMCPimThisEvent; iPim++) {
          mc_currentComb.push_back(mc_pimVector[iPim]);
          for (Int_t iGamma = 0; iGamma < (nMCGammaThisEvent - 1); iGamma++) {
            mc_currentComb.push_back(mc_gammaVector[iGamma]);
            for (Int_t jGamma = iGamma + 1; jGamma < nMCGammaThisEvent; jGamma++) {
              mc_currentComb.push_back(mc_gammaVector[jGamma]);
#ifdef DEBUG
              std::cout << "mc_currentComb = {" << mc_currentComb[0] << ", " << mc_currentComb[1] << ", " << mc_currentComb[2] << ", " << mc_currentComb[3] << "}" << std::endl;
#endif
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

    // candidate appeared for SIMREC
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

    /*** EVENT MIXING OR OMEGA MATCHING ***/

    // declare output vectors - initially empty
    std::vector<std::vector<Int_t>> mc_newVector;
    std::vector<Int_t> auxVector;
    std::vector<std::vector<Int_t>> newVector;
    std::vector<Int_t> nullVector = {-1, -1, -1, -1};

    if (gMixReconstructed) {
      // do the event mixing for sim. reconstructed particles
      newVector = combVector;
      for (Int_t Index = ParticleIndex; Index < LastIndex; Index++) {
        // when choosing to change pi0, search for one gamma, it stays at 22
        if (gParticleToSwap == 111) gParticleToSwap = 22;
        // loop on possible combinations, each desired particle will be swapped
        for (Size_t s = 0; s < newVector.size(); s++) {
          // choose a random entry
          while (1) {
            rng = r.Integer(nEntries);
            tree->GetEntry(rng);
            // check if it corresponds to the desired particle, same target and it's different from previous random entry
            if (((Int_t)t.pid == gParticleToSwap || (Int_t)t.pid == ParticleToSwap[Index])) {
              newVector[s][Index] = rng;
              // in the case of one gamma, find its partner to form a pi0, which can be the previous or next entry
              // and save it into the spot of the 4th particle
              if (gParticleToSwap == 22 || ParticleToSwap[Index] == 22) {
                tree->GetEntry(rng - 1);
                if ((Int_t)t.pid == 22) newVector[s][Index + 1] = rng - 1;
                tree->GetEntry(rng + 1);
                if ((Int_t)t.pid == 22) newVector[s][Index + 1] = rng + 1;
              }
              break;
            }
          }
        }
      }

    } else if (gMixGenerated) {
      // do the event mixing for generated particles, different because optimization
      mc_newVector = mc_combVector;
      for (Int_t Index = ParticleIndex; Index < LastIndex; Index++) {
        // loop on possible combinations, each desired particle will be swapped
        for (Size_t s = 0; s < mc_newVector.size(); s++) {
          if (Index == 0) {
            rng = r.Integer(nPip);
            mc_newVector[s][Index] = vPip[rng];
          } else if (Index == 1) {
            rng = r.Integer(nPim);
            mc_newVector[s][Index] = vPim[rng];
          } else if (Index == 2) {
            rng = r.Integer(nPi0);
            mc_newVector[s][Index] = vPi0[rng];
            mc_newVector[s][Index + 1] = vPi0[rng] + 1;
          }
        }
      }

    } else {
      // regular case
      // if the final state particles are already match, then the omegas are also matched
      for (Size_t m = 0; m < mc_combVector.size(); m++) {
        for (Size_t n = 0; n < combVector.size(); n++) {
          Bool_t fMatchingCondition = (mc_combVector[m] == combVector[n]);
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

    Int_t combCounter = 0;     // counter for simrec combinations
    Int_t mc_combCounter = 0;  // counter for gsim combinations

    if (gMixReconstructed) {
      // after mixing reconstructed simulations, fill just as data
      // candidate appeared for SIMREC
      for (Size_t cc = 0; cc < newVector.size(); cc++) {  // loop on combinations
#ifdef DEBUG
        std::cout << "newVector[" << cc << "] = {" << newVector[cc][0] << ", " << newVector[cc][1] << ", " << newVector[cc][2] << ", " << newVector[cc][3] << "}" << std::endl;
#endif
        for (Int_t pp = 0; pp < 4; pp++) {  // loop on final state particles
          tree->GetEntry(newVector[cc][pp]);
          AssignMixVar_REC(t, m, newVector[cc][pp], pp);
        }  // end of loop on fs particles
        AssignMoreVar_REC(m, nPipThisEvent, nPimThisEvent, nGammaThisEvent, cc);
        AssignPi0Var_REC(m, pi0);
        AssignOmegaVar_REC(m, pi0, w);
        NullMixVar_GEN(mc_m, mc_pi0, mc_w);
        // fill
        tMix->Fill();
      }  // end of loop on combinations
    } else if (gMixGenerated) {
      // after mixing generated particles, fill
      // candidate appeared for MC
      for (Size_t cc = 0; cc < mc_newVector.size(); cc++) {  // loop on combinations
#ifdef DEBUG
        std::cout << "mc_newVector[" << cc << "] = {" << mc_newVector[cc][0] << ", " << mc_newVector[cc][1] << ", " << mc_newVector[cc][2] << ", " << mc_newVector[cc][3] << "}"
                  << std::endl;
#endif
        for (Int_t pp = 0; pp < 4; pp++) {  // loop on final state particles
          tree->GetEntry(mc_newVector[cc][pp]);
          AssignMixVar_GEN(mc_t, mc_m, mc_newVector[cc][pp], pp);
        }  // end of loop on fs particles
        AssignMoreVar_GEN(mc_m, nMCPipThisEvent, nMCPimThisEvent, nMCGammaThisEvent, mc_combCounter);
        AssignPi0Var_GEN(mc_m, mc_pi0);
        AssignOmegaVar_GEN(mc_m, mc_pi0, mc_w);
        NullMixVar_REC(m, pi0, w);
        // evnt related vars
        for (Int_t pp = 0; pp < 4; pp++) m.Entry[pp] = (Float_t)mc_newVector[cc][pp];
        m.Event = t.evnt;
        // fill
        tMix->Fill();
      }  // end of loop on combinations
    } else {
      // regular case, attempts to do a matching
      // candidate appeared for MC
      for (Size_t cc = 0; cc < mc_newVector.size(); cc++) {
        // assign generated particles
        if (mc_newVector[cc][0] != -1) {
          for (Int_t gg = 0; gg < 4; gg++) {  // loop on final state particles
            tree->GetEntry(mc_newVector[cc][gg]);
            AssignMixVar_GEN(mc_t, mc_m, mc_newVector[cc][gg], gg);
          }
          AssignMoreVar_GEN(mc_m, nMCPipThisEvent, nMCPimThisEvent, nMCGammaThisEvent, mc_combCounter);
          AssignPi0Var_GEN(mc_m, mc_pi0);
          AssignOmegaVar_GEN(mc_m, mc_pi0, mc_w);
          mc_combCounter++;
        } else {
          NullMixVar_GEN(mc_m, mc_pi0, mc_w);
        }
        // assign sim reconstructed particles
        if (newVector[cc][0] != -1) {
          for (Int_t rr = 0; rr < 4; rr++) {  // loop on final state particles
            tree->GetEntry(newVector[cc][rr]);
            AssignMixVar_REC(t, m, newVector[cc][rr], rr);
            CheckContamination(mc_t, m, rr);
          }
          AssignMoreVar_REC(m, nPipThisEvent, nPimThisEvent, nGammaThisEvent, combCounter);
          AssignPi0Var_REC(m, pi0);
          AssignOmegaVar_REC(m, pi0, w);
          combCounter++;
        } else {
          NullMixVar_REC(m, pi0, w);
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

    // reset simrec counters
    nPipThisEvent = 0;
    nPimThisEvent = 0;
    nGammaThisEvent = 0;

    // reset comb counters
    combCounter = 0;
    mc_combCounter = 0;

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
