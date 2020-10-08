/**************************************/
/* Acceptance_pi0.cxx                 */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// plot pi0 invariant mass of sim/reconstructed or sim/generated
// histograms are written in an output root file

#include "analysisConfig.h"

/*** Global variables ***/

// options
Int_t simrecFlag = 0;
Int_t gsimFlag   = 0;
TString targetOption;
TString setOption;
TString nDir;

// filenames
TString inputDir;
TString outputDir;
TString outputFile;
TString nDirSufix = "";

// cuts
TCut cutSIMREC;
TCut cutGSIM;

// hist properties
TString varName;
TString histName;
TString histProperties;

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
  cutGSIM   = cutDIS_gsim;
  cutSIMREC = cutDIS_simrec && cutStatus_simrec;
  if (gsimFlag) cutSIMREC = "";

  // extract histograms
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputDir + "/comb" + targetOption + "_*.root/mix");

  // create histogram
  TH1F *theHist;
  treeExtracted->Draw(varName + ">>" + histName + histProperties, cutSIMREC && cutGSIM, "goff");
  theHist = (TH1F *)gROOT->FindObject(histName);

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
    std::cerr << "Empty command line. Execute ./Acceptance_pi0 -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hs:g:r:n:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'r': simrecFlag = 1; gsimFlag = 0; targetOption = optarg; break;
    case 'g': simrecFlag = 0; gsimFlag = 1; targetOption = optarg; break;
    case 's': setOption = optarg; break;
    case 'n': nDir      = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./Acceptance_pi0 -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "Acceptance_pi0 program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_pi0 -h" << std::endl;
  std::cout << "  print usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_pi0 -[r,g][target]" << std::endl;
  std::cout << "  select simulation: r (simrec) or g (generated)" << std::endl;
  std::cout << "  select target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;  
  std::cout << "./Acceptance_pi0 -s[set]" << std::endl;
  std::cout << "  choose set: old, usm, jlab - all" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_pi0 -n[ndir]" << std::endl;
  std::cout << "  if jlab, choose directory number" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing Acceptance_pi0 program. The chosen parameters are:" << std::endl;
  std::cout << "  simrecFlag   = " << simrecFlag << std::endl;
  std::cout << "  gsimFlag     = " << gsimFlag << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  setOption    = " << setOption << std::endl;
  std::cout << "  nDir         = " << nDir << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for set
  if (setOption == "jlab") {
    nDirSufix = "-" + nDir;
    inputDir = workDir + "/FilterNCombine/" + setOption + "/" + targetOption + "/" + nDir;
  } else {
    inputDir = workDir + "/FilterNCombine/" + setOption + "/" + targetOption;
  }
  outputDir = workDir + "/Acceptance/pi0";
  system("mkdir -p " + outputDir);
  // for type of sim
  if (simrecFlag) {
    varName = "pi0M_corr";
    histProperties = "(100, 0, 0.5)";
    histName = "pi0-" + targetOption + "_SIMREC";
    outputFile  = outputDir + "/mass-pi0_" + setOption + "-" + targetOption + nDirSufix + "_SIMREC.root";
   } else if (gsimFlag) {
    varName = "mc_pi0M";
    histProperties = "(600, 0.12, 0.15)";
    histName = "pi0-" + targetOption + "_GSIM";
    outputFile  = outputDir + "/mass-pi0_" + setOption + "-" + targetOption + nDirSufix + "_GSIM.root";
  }
}
