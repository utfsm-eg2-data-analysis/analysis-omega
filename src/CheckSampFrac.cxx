/**************************************/
/* CheckSampFrac.cxx                  */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// plots electron's sampling fraction for data and simulations/reconstructed

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/CheckSampFrac";
TString inputFile1 = "";
TString inputFile2 = "";
TString inputFile3 = "";

// options
TString targetOption;
Int_t dataFlag = 0;
Int_t simrecFlag = 0;
TString runNumber;

TString titleDraw;

TString plotFile;
TString rootFile;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // dir structure, just in case
  system("mkdir -p " + outDir);
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/original");
  treeExtracted->Add(inputFile2 + "/original");
  treeExtracted->Add(inputFile3 + "/original");
  
  // color stuff, smoran
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
  Double_t red[NRGBs]   = {0.00, 0.00, 0.87, 1.00, 0.51};
  Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
  Double_t blue[NRGBs]  = {0.51, 1.00, 0.12, 0.00, 0.00};
  
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  
  TH2F *theHist;
  treeExtracted->Draw("Etote/Pe:Pe>>hist(100, 0., 5, 100, 0.1, 0.4)", statusCuts_electrons, "goff");
  theHist = (TH2F *)gROOT->FindObject("hist");
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 769);
  c->SetTickx(1);
  c->SetTicky(1);
  gStyle->SetOptStat(0);
  gStyle->SetNumberContours(NCont); // colors, smoran
  
  theHist->SetTitle("Sampling Fraction cut for D+" + targetOption + titleDraw);
  theHist->GetYaxis()->SetTitle("Etot/P");
  theHist->GetXaxis()->SetTitle("P");
  theHist->GetYaxis()->CenterTitle();
  theHist->GetXaxis()->CenterTitle();
  theHist->SetContour(99);
  theHist->Draw("COLZ");
  
  c->Print(plotFile); // output file

  // create file, write hist and close file
  if (!dataFlag) {
    TFile *theFile = new TFile(rootFile, "RECREATE");
    theHist->Write();
    theFile->Close();
  }
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckSampFrac -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hs:d:r:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'd': targetOption = optarg; dataFlag = 1; break;
    case 's': targetOption = optarg; simrecFlag = 1; break;
    case 'r': runNumber = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckSampFrac -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "CheckSampFrac program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckSampFrac -h" << std::endl;
  std::cout << "  prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckSampFrac -[d,s][target]" << std::endl;
  std::cout << "  selects target: C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckSampFrac -r[rn]" << std::endl;
  std::cout << "  selects run number" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing CheckSampFrac program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  runNumber    = " << runNumber << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for kind of data
  if (dataFlag) {
    titleDraw = " Data";
    inputFile1 = dataDir + "/" + targetOption + "/comb_data" + targetOption + ".root";
  } else {
    titleDraw = " Simrec";
    inputFile1 = "comb" + targetOption + "_" + runNumber + ".root";
  }
  // for outdir
  if (!dataFlag) outDir = ".";
  // names
  plotFile = outDir + "/samp-frac-" + targetOption + ".png";
  rootFile = outDir + "/samp-frac-" + targetOption + "_" + runNumber + ".root";
}
