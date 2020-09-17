/**************************************/
/* Acceptance_00A.cxx                 */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

//*** ACCEPTANCE: STAGE 0-A ***//

// plots pi0 invariant mass of simulations/reconstructed or sim/generated
// histograms are written in an output root file

#include "analysisConfig.h"

/*** Global variables ***/

// options
Int_t simrecFlag = 0;
Int_t gsimFlag   = 0;
TString targetOption;
TString runNumber;

// filenames
TString inputFile, outputFile;

// cuts
// TCut cutQuality_gamma = ""; // ver.0
// TCut cutQuality_gamma = "mc_P[0] > 0.1 && mc_P[1] > 0.1"; // ver.1
TCut cutQuality_gamma = "mc_P[0] > 0.2 && mc_P[1] > 0.2"; // ver.2
TCut cutDIS_gen = "mc_Q2 > 1 && mc_W > 2 && mc_Yb < 0.85";
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
  cutGSIM   = cutDIS_gen && cutQuality_gamma;
  cutSIMREC = cutDIS && cutStatus;
  if (gsimFlag) cutSIMREC = "";
  
  // extract histogram
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile + "/mix");

  // create histogram
  TH1F *theHist;
  treeExtracted->Draw(lorentzInv + ">>hist(100, 0, 0.5)", cutSIMREC && cutGSIM, "goff"); // 5 MeV per bin
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
    std::cerr << "Empty command line. Execute ./Acceptance_00A -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hs:g:r:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 's': simrecFlag = 1; gsimFlag = 0; targetOption = optarg; break;
    case 'g': simrecFlag = 0; gsimFlag = 1; targetOption = optarg; break;
    case 'r': runNumber = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./Acceptance_00A -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "Acceptance (Stage 0-A) program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_00A -h" << std::endl;
  std::cout << "  prints help and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_00A -[s,g][target]" << std::endl;
  std::cout << "  selects simulation: s (simrec) or g (generated)" << std::endl;
  std::cout << "  selects target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;  
  std::cout << "./Acceptance_00A -r[rn]" << std::endl;
  std::cout << "  choose run number" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing Acceptance (Stage 0-A) program. The chosen parameters are:" << std::endl;
  std::cout << "  simrecFlag   = " << simrecFlag << std::endl;
  std::cout << "  gsimFlag     = " << gsimFlag << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  runNumber    = " << runNumber << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for variable
  if (simrecFlag) lorentzInv = "pi0M_corr";
  else if (gsimFlag) lorentzInv = "mc_pi0M";
  // filenames
  inputFile  = "comb" + targetOption + "_" + runNumber + ".root";
  if (simrecFlag) outputFile = "acc-0A-" + targetOption + "_simrec_" + runNumber + ".root";
  else if (gsimFlag) outputFile = "acc-0A-" + targetOption + "_gsim_" + runNumber + ".root";
}
