/***************************************/
/*  Reductor.cxx                       */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// February 2021

#include "Reductor.hxx"

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  /*** DATA STRUCTURES ***/

  // sim_p is the same as data_p + gsim variables
  sim_p spInput;
  sim_p spOutput;

  /*** INPUT ***/

  TChain *tInput = new TChain();
  tInput->Add(gInputFile + "/" + gTreeName);
  tInput->SetBranchStatus("*", 1);
  SetParticleBranches_Input(tInput, spInput);

  /*** OUTPUT ***/

  TFile *rootFile = new TFile(gOutputFile, "RECREATE", "Data of particles");
  TTree *tOutput = new TTree(gTreeName, "Stable particles");
  SetParticleBranches_Output(tOutput, spOutput);

  // for gsim
  Int_t iPip, iPim, iPi0;
  TTree *tPip;
  TTree *tPim;
  TTree *tPi0;
  if (gReduceMC) {
    tPip = new TTree("tPip", "Positive Pions");
    tPim = new TTree("tPim", "Negative Pions");
    tPi0 = new TTree("tPi0", "Neutral Pions");
    tPip->Branch("iPip", &iPip);
    tPim->Branch("iPim", &iPim);
    tPi0->Branch("iPi0", &iPi0);
  }

  /*** DECLARATIONS ***/

  // define particle counters
  Int_t nPip = 0;
  Int_t nPim = 0;
  Int_t nGamma = 0;

  // define entries vectors (to sort by pid)
  std::vector<Int_t> pospions;
  std::vector<Int_t> negpions;
  std::vector<Int_t> gammas;
  std::vector<Int_t> entries;

  // loop around events (it says entries, but they are really events)
  Int_t currentEvent, previousEvent;
  Int_t nEntries = tInput->GetEntries();

#ifdef DEBUG
  nEntries = 10000;
#endif

  /*** START ***/

  Int_t k = 0;  // counter of output entries
  for (Int_t i = 0; i <= nEntries; i++) {
    tInput->GetEntry(i);
    currentEvent = (Int_t)spInput.evnt;

    // prevents repetition of same event
    if (i > 0) {
      tInput->GetEntry(i - 1);
      previousEvent = (Int_t)spInput.evnt;
      if (previousEvent == currentEvent) continue;
    }

#ifdef DEBUG
    std::cout << "Current event number: " << currentEvent << std::endl;
    std::cout << "Current entry number: " << i << std::endl;
#endif

    // count particles in the current event
    for (Int_t j = i; j <= nEntries; j++) {
      tInput->GetEntry(j);

      // same-event condition
      if (currentEvent == (Int_t)spInput.evnt) {
#ifdef DEBUG
        if (gReduceSimrec || gDataKind == "data")
          std::cout << "Current pid:          " << spInput.pid << std::endl;
        else if (gReduceMC)
          std::cout << "Current mc_pid:       " << spInput.mc_pid << std::endl;
#endif
        // count the particles
        if (gReduceSimrec || gDataKind == "data") {
          if ((Int_t)spInput.pid == 211) {
            nPip++;
            pospions.push_back(j);
          } else if ((Int_t)spInput.pid == -211) {
            nPim++;
            negpions.push_back(j);
          } else if ((Int_t)spInput.pid == 22) {
            nGamma++;
            gammas.push_back(j);
          }
        } else if (gReduceMC) {
          if ((Int_t)spInput.mc_pid == 211) {
            nPip++;
            pospions.push_back(j);
          } else if ((Int_t)spInput.mc_pid == -211) {
            nPim++;
            negpions.push_back(j);
          } else if ((Int_t)spInput.mc_pid == 22) {
            nGamma++;
            gammas.push_back(j);
          }
        }
      } else {
        break;
      }  // end of same-event condition

    }  // end loop of particles in current event

    // arrange all particles in entries vector
    entries.insert(entries.end(), pospions.begin(), pospions.end());
    entries.insert(entries.end(), negpions.begin(), negpions.end());
    entries.insert(entries.end(), gammas.begin(), gammas.end());

#ifdef DEBUG
    std::cout << "N = (" << nPip << ", " << nPim << ", " << nGamma << ")" << std::endl;
#endif

    /*** MINIMUM SET OF PARTICLES FOUND ***/

    if (nPip >= 1 && nPim >= 1 && nGamma >= 2) {
      Int_t iGamma = 1;
      for (Size_t j = 0; j < entries.size(); j++) {
        tInput->GetEntry(entries[j]);  // update all spInput values
        spOutput = spInput;
        tOutput->Fill();
        // fill the other trees
        if (gReduceMC) {
          if (spInput.mc_pid == 211) {
            iPip = k;
            tPip->Fill();
          } else if (spInput.mc_pid == -211) {
            iPim = k;
            tPim->Fill();
          } else if (spInput.mc_pid == 22 && iGamma < nGamma) {
            iGamma++;
            iPi0 = k;
            tPi0->Fill();
          }
        }
        k++;  // update output entries
      }
    }

#ifdef DEBUG
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
#endif

    // reset particle counters
    nPip = 0;
    nPim = 0;
    nGamma = 0;

    // reset vectors
    pospions.clear();
    negpions.clear();
    gammas.clear();
    entries.clear();
  }  // end of loop in events

  /*** WRITE ***/

  rootFile->Write();
  rootFile->Close();

  std::cout << "File " << gOutputFile << " has been created!" << std::endl;

  return 0;
}
