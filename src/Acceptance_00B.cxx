/**************************************/
/* Acceptance_00B.cxx                 */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

//*** ACCEPTANCE: STAGE 0-B ***//

// plot reconstructed/generated distributions for invariant mass of a pi+ and pi- system
// histograms are written in an output root file

#include "analysisConfig.h"

/*** Global variables ***/

// options
Int_t simrecFlag, gsimFlag;
TString targetOption;
TString runNumber;

// filenames
TString inputFile, outputFile;

// cuts
TCut cutTargType, cutTargType_gen; // depend on chosen target
TCut cutDIS_gen = "mc_Q2 > 1 && mc_W > 2 && mc_Yb < 0.85";
TCut cutPi0_gen = "mc_pi0M > 0.12 && mc_pi0M < 0.15";
TCut cutSIMREC;
TCut cutGSIM;

// hist properties
TString lorentzInv;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // set cuts
  cutGSIM   = cutTargType_gen && cutDIS_gen && cutPi0_gen;
  cutSIMREC = cutTargType && cutDIS && cutStatus;
  if (gsimFlag) cutSIMREC = "";
  
  // extract histogram
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile + "/mix");

  // create histogram
  TH1F *theHist;
  treeExtracted->Draw(lorentzInv + ">>hist(150, 0, 1.5)", cutSIMREC && cutGSIM, "goff"); // 10 MeV per bin
  theHist = (TH1F *)gROOT->FindObject("hist");

  // create file, write hist and close file
  TFile *theFile = new TFile(outputFile, "RECREATE");
  theHist->Write();
  theFile->Close();
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./Acceptance_00B -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hs:g:r:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 's': simrecFlag = 1; gsimFlag = 0; targetOption = optarg; break;
    case 'g': simrecFlag = 0; gsimFlag = 1; targetOption = optarg; break;
    case 'r': runNumber = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./Acceptance_00B -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "Acceptance (Stage 0-B) program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_00B -h" << std::endl;
  std::cout << "  prints help and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_00B -[s,g][target]" << std::endl;
  std::cout << "  selects simulation: s (simrec) or g (generated)" << std::endl;
  std::cout << "  selects target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;  
  std::cout << "./Acceptance_00B -r[rn]" << std::endl;
  std::cout << "  choose run number" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing Acceptance (Stage 0-B) program. The chosen parameters are:" << std::endl;
  std::cout << "  simrecFlag   = " << simrecFlag << std::endl;
  std::cout << "  gsimFlag     = " << gsimFlag << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  runNumber    = " << runNumber << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for targets
  if (targetOption == "D") {
    cutTargType     = "TargType == 1";
    cutTargType_gen = "mc_TargType == 1";
  } else {
    cutTargType     = "TargType == 2";
    cutTargType_gen = "mc_TargType == 2";
  }
  // for variable
  lorentzInv = "pippimM";
  if (gsimFlag) lorentzInv = "mc_pippimM";
  // filenames
  inputFile  = "comb" + targetOption + "_" + runNumber + ".root";
  outputFile = "acc-0BR-" + targetOption + "_" + runNumber + ".root";
  if (gsimFlag) outputFile = "acc-0BG-" + targetOption + "_" + runNumber + ".root";
}
