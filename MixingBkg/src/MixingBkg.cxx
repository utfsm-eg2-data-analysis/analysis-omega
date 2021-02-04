/*****************************************/
/*  MixingBkg.cxx                        */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// February 2021

#include "MixingBkg_Math.hxx"
#include "MixingBkg_UX.hxx"

#include "RotatedTreeOps.hxx"
#include "TMixingBkgCluster.hxx"
#include "TreeOps.hxx"

#include "TRandom3.h"  // extra

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

  /*** DEFINITIONS ***/

  // these vectors only get edited when an omega candidate is fully formed
  std::vector<Int_t> currentComb;
  currentComb.resize(4);

  std::vector<Int_t> previousComb;
  previousComb.resize(4);

  // init buffer
  TMixingBkgCluster *theCluster = new TMixingBkgCluster(5, 5, 2, 100);

  // define rotated momentum
  TVector3 *lastElectron = new TVector3(0, 0, 0);
  std::vector<TVector3 *> rotatedMomentum = {new TVector3(0, 0, 0), new TVector3(0, 0, 0), new TVector3(0, 0, 0), new TVector3(0, 0, 0)};

  /*** START ***/

  // read all branches
  tree->SetBranchStatus("*", 1);
  SetInputBranches_REC(tree, t);

  Int_t nEntries = tree->GetEntries();
  
  /*** RANDOMNESS ***/

  // ten times the maximum of omega candidates in a run number
  Int_t Scale = 100;
  Int_t omegaCounter = 0;
  Int_t omegaLimit = Scale*nEntries/2.9; // nEntries/2.9 is an approx. number of how many omegas to expect

  TRandom3 r;  // variable to create random event numbers

  // loop in entries
  while (omegaCounter < omegaLimit) {
    
    // insert randomness!
    Int_t j = r.Integer(nEntries + 1);
    tree->GetEntry(j);

    // add particle to the cluster, if all the conditions ared satisfied, currentComb would change
    theCluster->Add(j, t.evnt, t.pid, t.Q2, t.Nu, t.TargType, currentComb, t.Pex, t.Pey, t.Pez, t.Px, t.Py, t.Pz, lastElectron, rotatedMomentum);

    // if currentComb change, there was an artifical omega created
    // also prevents repetition (comparison operators for std::vector were removed in C++20)
    if (currentComb != previousComb) {

      /*** FILL MIX ***/

#ifdef DEBUG
      // print current state of candidate vector, commentary
      std::cout << "OMEGA CANDIDATE FOUND : ";
      for (Int_t i = 0; i < 4; i++) std::cout << currentComb[i] << " ";
      std::cout << std::endl;
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

      omegaCounter++;
    }
  }  // end of loop in entries

  /*** WRITE ***/

  rootFile->Write();
  rootFile->Close();

  std::cout << "This file has been created: " << gOutputFile << std::endl;

#ifdef DEBUG
  // theCluster->Print();
#endif

  return 0;
}
