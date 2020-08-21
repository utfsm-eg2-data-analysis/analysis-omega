/**************************************/
/* Acceptance_02.cxx                  */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

//*** ACCEPTANCE: STAGE 2 ***//

// plots all reconstructed and generated omegas invariant mass difference for every bin
// (PENDING: non-diagonal values of the acceptance matrix!!)

#include "analysisConfig.h"

/*** Global variables ***/

// options
Int_t simrecFlag, gsimFlag;
TString targetOption;
TString runNumber;
Int_t flagZ, flagPt2, flagQ2, flagNu;
Int_t binNumber;

// filenames
TString inputFile, outputFile;

// cuts
TCut cutTargType, cutTargType_gen; // depend on chosen target
TCut cutKinvar,  cutKinvar_gen;
TCut cutDIS_gen = "mc_Q2 > 1 && mc_W > 2 && mc_Yb < 0.85";
TCut cutPi0_gen = "mc_pi0M > 0.12 && mc_pi0M < 0.15";
TCut cutPi0_rec = "0.084 < pi0M_corr && pi0M_corr < 0.186"; // mean = 0.135, width = 0.017 (obtained from Stage 1)
TCut cutSIMREC;
TCut cutGSIM;

// kinvar
TString kinvarName, kinvarName_gen;
TString kinvarSufix;

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
  cutGSIM   = cutTargType_gen && cutDIS_gen && cutPi0_gen && cutKinvar_gen;
  cutSIMREC = cutTargType && cutDIS && cutPi0_rec && cutStatus && cutKinvar;
  if (gsimFlag) cutSIMREC = "";
  
  // extract histogram
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile + "/mix");

  // create histogram
  TH1F *theHist;
  treeExtracted->Draw(lorentzInv + ">>hist(40, 0.68, 0.88)", cutSIMREC && cutGSIM, "goff"); // 5 MeV per bin
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
    std::cerr << "Empty command line. Execute ./Acceptance_02 -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hs:g:r:z:q:n:p:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 's': simrecFlag = 1; gsimFlag = 0; targetOption = optarg; break;
    case 'g': simrecFlag = 0; gsimFlag = 1; targetOption = optarg; break;
    case 'r': runNumber = optarg; break;
    case 'z': flagZ = 1; binNumber = atoi(optarg); break;
    case 'q': flagQ2 = 1; binNumber = atoi(optarg); break;
    case 'n': flagNu = 1; binNumber = atoi(optarg); break;
    case 'p': flagPt2 = 1; binNumber = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./Acceptance_02 -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "Acceptance (Stage 2) program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_02 -h" << std::endl;
  std::cout << "  prints help and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_02 -[s,g][target]" << std::endl;
  std::cout << "  selects simulation: s (simrec) or g (generated)" << std::endl;
  std::cout << "  selects target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_02 -r[rn]" << std::endl;
  std::cout << "  choose run number" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_02 -[kinvar][number]" << std::endl;
  std::cout << "    analyzes respective kinematic variable bin" << std::endl;
  std::cout << "    z[3-7] : analyzes specific Z bin" << std::endl;
  std::cout << "    q[1-5] : analyzes specific Q2 bin" << std::endl;
  std::cout << "    n[1-5] : analyzes specific Nu bin" << std::endl;
  std::cout << "    p[1-5] : analyzes specific Pt2 bin" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing Acceptance (Stage 2) program. The chosen parameters are:" << std::endl;
  std::cout << "  simrecFlag     = " << simrecFlag << std::endl;
  std::cout << "  gsimFlag       = " << gsimFlag << std::endl;
  std::cout << "  targetOption   = " << targetOption << std::endl;
  std::cout << "  runNumber      = " << runNumber << std::endl;
  std::cout << "  kinvarName     = " << kinvarName << std::endl;
  std::cout << "  kinvarName_gen = " << kinvarName_gen << std::endl;
  std::cout << "  binNumber      = " << binNumber << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for targets
  if (targetOption == "D") {
    cutTargType = "TargType == 1";
    cutTargType_gen = "mc_TargType == 1";
  } else {
    cutTargType = "TargType == 2";
    cutTargType_gen = "mc_TargType == 2";
  }
  // for variable
  lorentzInv = "wD_corr";
  if (gsimFlag) lorentzInv = "mc_wD";
  // for kinvar
  Double_t lowEdge, highEdge;
  if (flagZ) {
    lowEdge  = edgesZ[binNumber-3];
    highEdge = edgesZ[binNumber+1-3];
    kinvarSufix = Form("-z%d", binNumber);
    kinvarName  = "wZ_corr";
    kinvarName_gen = "mc_wZ";
  } else if (flagQ2) {
    lowEdge  = edgesQ2[binNumber-1];
    highEdge = edgesQ2[binNumber+1-1];
    kinvarSufix = Form("-q%d", binNumber);
    kinvarName  = "Q2";
    kinvarName_gen = "mc_Q2";
  } else if (flagNu) {
    lowEdge  = edgesNu[binNumber-1];
    highEdge = edgesNu[binNumber+1-1];
    kinvarSufix = Form("-n%d", binNumber);
    kinvarName  = "Nu";
    kinvarName_gen = "mc_Nu";
  } else if (flagPt2) {
    lowEdge  = edgesPt2[binNumber-1];
    highEdge = edgesPt2[binNumber+1-1];
    kinvarSufix = Form("-p%d", binNumber);
    kinvarName  = "wPt2_corr";
    kinvarName_gen = "mc_wPt2";
  }
  cutKinvar = Form("%f < ", lowEdge) + kinvarName + " && " + kinvarName + Form(" < %f", highEdge);
  cutKinvar_gen = Form("%f < ", lowEdge) + kinvarName_gen + " && " + kinvarName_gen + Form(" < %f", highEdge);
  // filenames
  inputFile  = "comb" + targetOption + "_" + runNumber + ".root";
  outputFile = "acc-2R-" + targetOption + "_" + runNumber + kinvarSufix + ".root";
  if (gsimFlag) outputFile = "acc-2G-" + targetOption + "_" + runNumber + kinvarSufix + ".root";
}
