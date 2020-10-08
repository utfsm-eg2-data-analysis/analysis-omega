/**************************************/
/* Acceptance_fit-pi0.cxx             */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// fit pi0 invariant mass with a gaussian

#include "analysisConfig.h"

/*** Global variables ***/

Int_t simrecFlag, gsimFlag;
TString targetOption;
TString setOption;
TString nDir;

TString inputDir  = workDir + "/Acceptance/pi0";
TString outputDir = inputDir;

TString inputFile;
TString outputFile;
TString plotFile;

TString histName;
TString nDirSufix;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // read file
  TFile *file = new TFile(inputFile);
  TH1F *pi0Hist = (TH1F *)file->Get(histName); 

  // define function
  TF1 *aGaussian = new TF1("aGaussian", "gaus(0)", 0.134, 0.136); // TEMPORARY for GSIM

  // setting initial guess values
  aGaussian->SetParameter(1, 0.135);

  pi0Hist->Fit("aGaussian", "RF", "goff"); // REN0

  Double_t gaus_params[3];
  aGaussian->GetParameters(gaus_params);
  
  // draw
  TCanvas *c0 = new TCanvas("c0", "c0", 1000, 1000);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(111);

  pi0Hist->GetYaxis()->SetMaxDigits(3);
  pi0Hist->Draw("E");

  gPad->Update();
  TPaveStats *paramsBox = (TPaveStats*) pi0Hist->FindObject("stats");
  paramsBox->SetX1NDC(0.6);
  paramsBox->SetX2NDC(0.9);
  paramsBox->SetY1NDC(0.75);
  paramsBox->SetY2NDC(0.9);
  
  aGaussian->SetLineWidth(3);
  aGaussian->SetLineColor(kRed);
  aGaussian->Draw("SAME");

  drawVerticalLine(gaus_params[1], kBlack);
  drawVerticalLine(gaus_params[1] - 3*gaus_params[2], kBlack);
  drawVerticalLine(gaus_params[1] + 3*gaus_params[2], kBlack);

  std::cout << "PI0 CUT" << std::endl;
  std::cout << "LOWER LIMIT  = " << gaus_params[1] - 3*gaus_params[2] << std::endl;
  std::cout << "HIGHER LIMIT = " << gaus_params[1] + 3*gaus_params[2] << std::endl;
  
  c0->Print(plotFile);  
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./Acceptance_fit-pi0 -h to print usage." << std::endl;
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
      std::cerr << "Unrecognized argument. Execute ./Acceptance_fit-pi0 -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "Acceptance_fit-pi0 program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_fit-pi0 -h" << std::endl;
  std::cout << "  print usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_fit-pi0 -[r,g][target]" << std::endl;
  std::cout << "  select simulation: r (simrec) or g (generated)" << std::endl;
  std::cout << "  select target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;  
  std::cout << "./Acceptance_fit-pi0 -s[set]" << std::endl;
  std::cout << "  choose set: old, usm, jlab" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_fit-pi0 -n[ndir]" << std::endl;
  std::cout << "  if jlab, choose directory number" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing Acceptance_fit-pi0 program. The chosen parameters are:" << std::endl;
  std::cout << "  simrecFlag   = " << simrecFlag << std::endl;
  std::cout << "  gsimFlag     = " << gsimFlag << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  setOption    = " << setOption << std::endl;
  std::cout << "  nDir         = " << nDir << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for set
  if (setOption == "jlab") nDirSufix = "-" + nDir;
  // for type of simulation
  if (simrecFlag) {
    histName = "pi0-" + targetOption + "_SIMREC";
    inputFile  = inputDir + "/mass-pi0_" + setOption + "-" + targetOption + nDirSufix + "_SIMREC.root";
    plotFile   = outputDir + "/fit-pi0_" + setOption + "-" + targetOption + nDirSufix + "_SIMREC.png";
  } else if (gsimFlag) {
    histName = "pi0-" + targetOption + "_GSIM";
    inputFile  = inputDir + "/mass-pi0_" + setOption + "-" + targetOption + nDirSufix + "_GSIM.root";
    plotFile   = outputDir + "/fit-pi0_" + setOption + "-" + targetOption + nDirSufix + "_GSIM.png";
  }
}
