/***************************************/
/*  Reductor.cxx                       */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// February 2021

#include "Headers.hxx"
#include "UX.hxx"

#include "GSTtree.h"
#include "Reductor.hxx"

/*** Declaration of functions ***/

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  /*** INPUT ***/

  // define data structure
  data_p dpInput;

  // define tree
  TChain *tInput = new TChain();
  tInput->Add(gInputFile + "/ntuple_data");
  tInput->SetBranchStatus("*", 1);
  SetParticleBranches_Input(tInput, dpInput);
  
  /*** OUTPUT ***/

  // define file
  TFile *rootFile = new TFile(gOutputFile, "RECREATE", "Data of particles");

  // define data structure
  data_p dpOutput;
  
  // define tree
  TTree *tOutput = new TTree("ntuple_data", "Stable particles");
  SetParticleBranches_Output(tOutput, dpOutput);
  
  /*** START ***/

  // define particle counters
  Int_t nPip = 0;
  Int_t nPim = 0;
  Int_t nGamma = 0;

  // define entries vector
  std::vector<Int_t> entries;

  // loop around events (it says entries, but they are really events)
  Int_t currentEvent, previousEvent;
  Int_t nEntries = tInput->GetEntries();
  
#ifdef DEBUG
  nEntries = 10000;
#endif
  
  for (Int_t i = 0; i <= nEntries; i++) {
    tInput->GetEntry(i);
    currentEvent = (Int_t)dpInput.evnt;

    // prevents repetition of same event
    if (i > 0) {
      tInput->GetEntry(i - 1);
      previousEvent = (Int_t)dpInput.evnt;
      if (previousEvent == currentEvent) continue;
    }
    
#ifdef DEBUG
    std::cout << "Current event number: " << currentEvent << std::endl;
    std::cout << "Current entry number: " << i << std::endl;
#endif

    // count particles in the current event
    for (Int_t j = i; j <= nEntries; j++) {
      tInput->GetEntry(j);
      
      if (currentEvent == (Int_t)dpInput.evnt) {
#ifdef DEBUG
	std::cout << "Current pid:          " << dpInput.pid << std::endl;
#endif
        // count the particles
        if ((Int_t)dpInput.pid == 22) {
	  nGamma++;
	  entries.push_back(j);
        } else if ((Int_t)dpInput.pid == 211) {
          nPip++;
	  entries.push_back(j);
	} else if ((Int_t)dpInput.pid == -211) {
          nPim++;
	  entries.push_back(j);
	}
      } else {
        break;
      } // end of same-event condition
      
    } // end loop of particles in current event
    
#ifdef DEBUG
    std::cout << "N = (" << nPip << ", " << nPim << ", " << nGamma << ")" << std::endl;
#endif
    
    /*** MINIMUM SET OF PARTICLES FOUND ***/

    if (nPip >= 1 && nPim >= 1 && nGamma >= 2) {
      for (Size_t j = 0; j < entries.size(); j++) {
	tInput->GetEntry(entries[j]); // update all dpInput values
	dpOutput = dpInput;
	tOutput->Fill();
      }
    }
    
#ifdef DEBUG
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
#endif

    
    // reset particle counters
    nPip = 0;
    nPim = 0;
    nGamma = 0;

    // reset vector
    entries.clear();
  } // end of loop in events

  /*** WRITE ***/
  
  rootFile->Write();
  rootFile->Close();
  
  std::cout << "File " << gOutputFile << " has been created!" << std::endl;

  return 0;
}

