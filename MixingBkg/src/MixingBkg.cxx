/*****************************************/
/*  MixingBkg.cxx                        */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// December 2020

#include "MixingBkg_UI.hxx"

#include "RotatedTreeOps.hxx"
#include "TMixingBkgCluster.hxx"
#include "TreeOps.hxx"

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
  rec_pi0 pi0;
  rec_w w;

  /*** INPUT ***/

  TChain *tree = new TChain();
  tree->Add(gInputFile + "/ntuple_data");

  /*** OUTPUT ***/

  TFile *rootFile = new TFile(gOutputFile, "RECREATE", "Omega Meson Filtered Combinations");

  TTree *tMix = new TTree("mix", "Combination of particles");
  SetMixBranches_REC(tMix, m, pi0, w);

  /*** START ***/

  // read all branches
  tree->SetBranchStatus("*", 1);
  SetInputBranches_REC(tree, t);

  Int_t Ne = (Int_t)tree->GetEntries();
#ifdef DEBUG
  Ne = 200;
#else
#endif

  /*** DEFINITIONS ***/

  std::vector<Int_t> currentComb;
  currentComb.resize(4);

  std::vector<Int_t> previousComb;
  previousComb.resize(4);

  // init buffer
  TMixingBkgCluster *theCluster = new TMixingBkgCluster(10, 10, 10);

  // define rotated momentum
  TVector3* lastElectron = new TVector3(0, 0, 0);
  std::vector<TVector3 *> rotatedMomentum = {new TVector3(0, 0, 0), new TVector3(0, 0, 0), new TVector3(0, 0, 0), new TVector3(0, 0, 0)};

  // loop in entries
  for (Int_t i = 0; i <= Ne; i++) {
    tree->GetEntry(i);
    theCluster->Add(i, t.evnt, t.pid, t.Q2, t.Nu, currentComb, t.Pex, t.Pey, t.Pez, t.Px, t.Py, t.Pz,
                    lastElectron, rotatedMomentum);

    // prevents repetition (comparison operators for std::vector were removed in C++20)
    if (currentComb != previousComb) {

      /*** FILL MIX ***/

#ifdef DEBUG
      // print current state of candidate vector, commentary
      std::cout << "OMEGA CANDIDATE FOUND : ";
      for (Int_t j = 0; j < 4; j++) std::cout << currentComb[j] << " ";
      std::cout << std::endl;
#else
#endif

      for (Int_t pp = 0; pp < 4; pp++) {  // loop on final state particles
        tree->GetEntry(currentComb[pp]);
        AssignMixVar_REC(t, m, currentComb[pp], pp);  // AssignMixVar_REC(t, m, currentComb[pp], pp)
        // overwrite momentum-dependent variables
        AssignRotatedMixVar_REC(m, pp, lastElectron, rotatedMomentum);  // AssignMixVar_REC(m, pp, pMomentum)
      }
      AssignMoreVar_REC(m, 1, 1, 2, 0);  // AssignMoreVar_REC(m, nPipThisEvent, nPimThisEvent, nGammaThisEvent, number of combination)
      AssignPi0Var_REC(m, pi0);          // AssignPi0Var_REC(m, pi0)
      AssignOmegaVar_REC(m, pi0, w);     // AssignOmegaVar_REC(m, pi0, w)

      tMix->Fill();

      previousComb = currentComb;
    }

  }  // end of loop in entries

  /*** WRITE ***/

  rootFile->Write();
  rootFile->Close();

  std::cout << "This file has been created: " << gOutputFile << std::endl;

#ifdef DEBUG
  // theCluster->Print();
#else
#endif

  return 0;
}
