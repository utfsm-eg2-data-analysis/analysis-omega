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
  rec_t dsInput;
  rec_t dsOutput;

  /*** INPUT ***/

  TChain *tInput = new TChain();
  tInput->Add(gInputFile + "/" + gTreeName);
  tInput->SetBranchStatus("*", 1);
  ReadParticleChain_REC(tInput, dsInput);

  /*** OUTPUT ***/
  TFile *rootFile = new TFile(gOutputFile, "RECREATE", gDataDescription);
  TTree *tOutput = new TTree(gTreeName, "Stable particles");
  SetParticleTree_REC(tOutput, dsOutput);

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

#ifdef DEBUG
  nEntries = 10000;
#endif

  /*** START ***/

  Int_t k = 0;  // counter of output entries
  for (Int_t i = 0; i <= nEntries; i++) {
    tInput->GetEntry(i);
    currentEvent = (Int_t)dsInput.evnt;

    // prevents repetition of same event
    if (i > 0) {
      tInput->GetEntry(i - 1);
      previousEvent = (Int_t)dsInput.evnt;
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
      if (currentEvent == (Int_t)dsInput.evnt) {
#ifdef DEBUG
        std::cout << "Current pid:          " << dsInput.pid << std::endl;
#endif
        // count the particles
        if ((Int_t)dsInput.pid == 211) {
          nPip++;
          pospions.push_back(j);
        } else if ((Int_t)dsInput.pid == -211) {
          nPim++;
          negpions.push_back(j);
        } else if ((Int_t)dsInput.pid == 22) {
          nGamma++;
          gammas.push_back(j);
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
      for (Size_t j = 0; j < entries.size(); j++) {
        tInput->GetEntry(entries[j]);  // update all dsInput values
        dsOutput = dsInput;
        tOutput->Fill();
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
