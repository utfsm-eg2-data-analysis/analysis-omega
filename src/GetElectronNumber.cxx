/**************************************/
/* GetElectronNumber.cxx              */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// November 2020

#include "analysisConfig.h"

/*** Global variables ***/

TString targetOption;

TString inputDir = workDir + "/GetSimpleTuple/data";

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  printOptions();

  // set i/o
  TChain *treeExtracted = new TChain();
  TCut cutVertex;
  if (targetOption == "D") { // unified D
    treeExtracted->Add(inputDir + "/C/prunedC_*.root/ntuple_e");
    treeExtracted->Add(inputDir + "/Fe/prunedFe_*.root/ntuple_e");
    treeExtracted->Add(inputDir + "/Pb/prunedPb_*.root/ntuple_e");
    cutVertex = "TargType == 1 && vyec > -1.4 && vyec < 1.4"; // GST format
  } else {
    treeExtracted->Add(inputDir + "/" + targetOption + "/pruned" + targetOption + "_*.root/ntuple_e");
    cutVertex = "TargType == 2 && vyec > -1.4 && vyec < 1.4"; // GST format
  }
  
  /*** Getting Electron Numbers ***/

  // set cuts
  TCut cutELECTRON = cutDIS && cutVertex; // only electron cuts

  // define arrays, cut for each bin and hist
  TString kinvarIndex[4]  = {"Q", "N"};
  TString kinvarName[4]   = {"Q2", "Nu"};
  TString kinvarOption[4] = {"Q2", "Nu"};

  // fill edges array
  Double_t edgesKinvar[2][6];
  for (Int_t j = 0; j < 6; j++) {
    edgesKinvar[0][j] = edgesQ2[j];
    edgesKinvar[1][j] = edgesNu[j];
  }

  TCut cutBIN;
  Int_t eNumber;

  /*** Big Picture ***/

  eNumber = treeExtracted->Draw("Nu>>data(100, -10., 10.)", cutELECTRON, "goff"); // lazyness
  std::cout << "ELECTRON NUMBER(" << targetOption << ") = "
	    << eNumber << std::endl;
  eNumber = 0; // reset
  
  /*** Electron Variables ***/
  
  // kinvar loop (only Q2 and Nu)
  for (Int_t k = 0; k < 2; k++) {
    // bins loop
    for (Int_t i = 0; i < 5; i++) { 
      cutBIN = kinvarOption[k] + Form(" > %.3f && ", edgesKinvar[k][i]) + kinvarOption[k] + Form(" < %.3f", edgesKinvar[k][i+1]);
      eNumber = treeExtracted->Draw("Nu>>data(100, -10., 10.)", cutELECTRON && cutBIN, "goff"); // lazyness
      std::cout << "ELECTRON NUMBER(" << targetOption << ", "
		<< Form("%.2f < ", edgesKinvar[k][i]) + kinvarName[k] + Form(" < %.2f)", edgesKinvar[k][i+1]) << " = "
		<< eNumber << std::endl;
      eNumber = 0; // reset
    }
  }
  
  std::cout << std::endl;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./GetElectronNumber -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./GetElectronNumber -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing GetElectronNumber program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "GetElectronNumber program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetElectronNumber -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetElectronNumber -t[target]" << std::endl;
  std::cout << "    selects target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;
}
