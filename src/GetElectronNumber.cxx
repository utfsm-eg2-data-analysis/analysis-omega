/**************************************/
/* GetElectronNumber.cxx              */
/*                                    */
/* Created by Andrés Bórquez          */
/*                                    */
/**************************************/

// Exclusive for UTFSM cluster, because there is the pruned data

#include "analysisConfig.h"

/*** Global variables ***/

TString targetOption;

Int_t flagQ2 = 0;
Int_t flagNu = 0;

TCut cutTargType;
TCut kinvarCut;

TString kinvarName;
TString kinvarSufix;
Int_t binNumber;

TString textFile;
TString inputDir1 = proDir + "/out/prunedData/C";
TString inputDir2 = proDir + "/out/prunedData/Fe";
TString inputDir3 = proDir + "/out/prunedData/Pb";

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  
  /*** Read RN file ***/
  
  std::ifstream inFile(textFile);
  
  TString auxLine;
  TString currentRN; 
  TString rootFile;
  TString currentDir;  

  Int_t eNumber = 0;
  Int_t i = 0; // counter
  
  while (inFile >> auxLine) {
    i++;
    currentRN = auxLine;

    /*** Reading root files ***/

    if (targetOption == "D") {
      if (i < (runNumbersC+1)) currentDir = inputDir1;
      else if (i > (runNumbersC) && i < (runNumbersC+runNumbersFe+1)) currentDir = inputDir2;
      else if (i > (runNumbersC+runNumbersFe)) currentDir = inputDir3;
    } else if (targetOption == "C") {
      currentDir = inputDir1;
    } else if (targetOption == "Fe") {
      currentDir = inputDir2;
    } else if (targetOption == "Pb") {
      currentDir = inputDir3;
    }
    
    /*** Summing Electron Numbers ***/

    rootFile = currentDir + "prune_data_" + currentRN + ".root";
    std::cout << "Reading file (" << i << ") " << rootFile << " ..." << std::endl;
    TFile *File = new TFile(rootFile);
    
    TTree *treeExtracted = (TTree *)File->Get("e_rec");
    eNumber += treeExtracted->Draw("Nu>>data(100, -10., 10.)", cutDIS_old && cutTargType && kinvarCut, "goff"); // lazyness

    File->Close();
  }
  inFile.close();
  
  // print final result!
  std::cout << "eN (" << targetOption << kinvarSufix << ") = " << eNumber << std::endl;
  std::cout << std::endl;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./GetElectronNumber -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:q:n:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'q': flagQ2 = 1; binNumber = atoi(optarg); break;
    case 'n': flagNu = 1; binNumber = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./GetElectronNumber -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing GetElectronNumber program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  kinvarName   = " << kinvarName << std::endl;
  std::cout << "  binNumber    = " << binNumber << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "GetElectronNumber program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetElectronNumber -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetElectronNumber -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetElectronNumber -[kinvar][number]" << std::endl;
  std::cout << "    analyzes respective kinematic variable bin" << std::endl;
  std::cout << "    q[1-5] : analyzes specific Q2 bin" << std::endl;
  std::cout << "    n[1-5] : analyzes specific Nu bin" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // rn files
  if (targetOption == "D") {
    textFile = proDir + "/include/D-onlyD2rn.txt";
    cutTargType = "TargType == 1";
  } else if (targetOption == "C") {
    textFile = proDir + "/include/C-thickD2rn.txt";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Fe") {
    textFile = proDir + "/include/Fe-thickD2rn.txt";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Pb") {
    textFile = proDir + "/include/Pb-thinD2rn.txt";
    cutTargType = "TargType == 2";
  }
  // for kinvar
  Double_t lowEdge, highEdge;
  if (flagQ2) {
    lowEdge = edgesQ2[binNumber-1];
    highEdge = edgesQ2[binNumber+1-1];
    kinvarSufix = Form("-q%d", binNumber);
    kinvarName = "Q2";
  } else if (flagNu) {
    lowEdge = edgesNu[binNumber-1];
    highEdge = edgesNu[binNumber+1-1];
    kinvarSufix = Form("-n%d", binNumber);
    kinvarName = "Nu";
  }
  kinvarCut = Form("%f < ", lowEdge) + kinvarName + " && " + kinvarName + Form(" < %f", highEdge);
}
