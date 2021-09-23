/***************************************/
/*  Reductor.cxx                       */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// September 2021

#include "Reductor.hxx"

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  /*** DATA STRUCTURES ***/

  // same data structure
  elec_t elec_in, elec_out;
  part_t part_in, part_out;

  /*** INPUT ***/

  TChain *tInput = new TChain();
  tInput->Add(gInputFile + "/" + gTreeName);
  tInput->SetBranchStatus("*", 1);
  ReadInputChain_REC(tInput, elec_in, part_in);

  /*** OUTPUT ***/
  TFile *rootFile = new TFile(gOutputFile, "RECREATE", gDataDescription);
  TTree *tOutput = new TTree(gTreeName, "Stable particles");
  SetOutputTree_REC(tOutput, elec_out, part_out);

  /*** DECLARATIONS ***/

  // define particle counters
  Int_t nPip = 0;
  Int_t nPim = 0;
  Int_t nGamma = 0;

  // define entries vectors (to sort by pid later)
  std::vector<Int_t> pospions;
  std::vector<Int_t> negpions;
  std::vector<Int_t> gammas;
  std::vector<Int_t> entries;

  // loop around events (it says entries, but they are really events)
  Int_t currentEvent, previousEvent;
  Int_t nEntries = tInput->GetEntries();

  /*** START ***/

  for (Int_t i = 0; i < nEntries; i++) {
    tInput->GetEntry(i);
    currentEvent = (Int_t)elec_in.evnt;

    // prevents repetition of same event
    if (i > 0) {
      tInput->GetEntry(i - 1);
      previousEvent = (Int_t)elec_in.evnt;
      if (previousEvent == currentEvent) {
        continue;
      }
    }

    // count particles in the current event
    for (Int_t j = i; j < nEntries; j++) {
      tInput->GetEntry(j);

      // same-event condition
      if (currentEvent == (Int_t)elec_in.evnt) {
        // count the particles
        if ((Int_t)part_in.pid == 211) {
          nPip++;
          pospions.push_back(j);
        } else if ((Int_t)part_in.pid == -211) {
          nPim++;
          negpions.push_back(j);
        } else if ((Int_t)part_in.pid == 22) {
          nGamma++;
          gammas.push_back(j);
        }
      } else {
        break;
      }  // end of same-event condition

    }  // end loop of particles in current event

    // sort by particle type in a new vector called "entries"
    entries.insert(entries.end(), pospions.begin(), pospions.end());
    entries.insert(entries.end(), negpions.begin(), negpions.end());
    entries.insert(entries.end(), gammas.begin(), gammas.end());

    /*** MINIMUM SET OF PARTICLES FOUND ***/

    if (nPip >= 1 && nPim >= 1 && nGamma >= 2) {
      for (Size_t j = 0; j < entries.size(); j++) {
        // update all input vars and write them into output tree
        tInput->GetEntry(entries[j]);
        elec_out = elec_in;
        part_out = part_in;
        tOutput->Fill();
      }
    }

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

  std::cout << "This file has been created: " << gOutputFile << std::endl;

  return 0;
}
