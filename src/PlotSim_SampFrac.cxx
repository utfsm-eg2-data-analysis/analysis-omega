/**************************************/
/* PlotSim_SampFrac.cxx               */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// plots electron's sampling fraction for simulations

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/PlotSim";
TString inputFile1 = "";
TString inputFile2 = "";
TString inputFile3 = "";

// options
TString targetOption;
Int_t dataFlag, simrecFlag, gsimFlag;

TString dataOption;
TString titleDraw;

// cuts
TCut cutAll;
TCut cutTargType;

TString outPrefix;
TString plotFile;

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
  
  // setting cuts
  cutAll = cutDIS && cutPi0 && cutPipPim;

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
  treeExtracted->Draw("Etote/Pe:Pe>>hist(100, 0., 5, 100, 0.1, 0.4)", cutTargType && statusCuts_electrons, "goff");
  theHist = (TH2F *)gROOT->FindObject("hist");
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 769);
  c->SetTickx(1);
  c->SetTicky(1);
  gStyle->SetOptStat(0);
  gStyle->SetNumberContours(NCont); // colors, smoran
  
  theHist->SetTitle("Sampling Fraction cut for " + targetOption + titleDraw);
  theHist->GetYaxis()->SetTitle("Etot/P");
  theHist->GetXaxis()->SetTitle("P");
  theHist->GetYaxis()->CenterTitle();
  theHist->GetXaxis()->CenterTitle();
  theHist->SetContour(99);
  theHist->Draw("COLZ");

  // normalization
  // theHist->Scale(1/((Double_t) theHist->GetEntries()));

  // log scale
  // gPad->SetLogz(); // important
  
  c->Print(plotFile); // output file
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./PlotSim_SampFrac -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hg:s:d:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'd': targetOption = optarg; dataFlag = 1; break;
    case 's': targetOption = optarg; simrecFlag = 1; break;
    case 'g': targetOption = optarg; gsimFlag = 1; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./PlotSim_SampFrac -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "PlotSim_SampFrac program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./PlotSim_SampFrac -h" << std::endl;
  std::cout << "  prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./PlotSim_SampFrac -[d,g,s][target]" << std::endl;
  std::cout << "  selects target: D | C | Fe | Pb | All" << std::endl;
  std::cout << std::endl;  
}

void printOptions() {
  std::cout << "Executing PlotSim_SampFrac program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  dataOption   = " << dataOption << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for kind of data
  if (dataFlag) {
    dataOption = "data";
    titleDraw = " Data";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = dataDir + "/C/comb_dataC.root";
      inputFile2 = dataDir + "/Fe/comb_dataFe.root";
      inputFile3 = dataDir + "/Pb/comb_dataPb.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/C/comb_dataC.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/Fe/comb_dataFe.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/Pb/comb_dataPb.root";
    } else if (targetOption == "All") {
      cutTargType = "TargType == 1 || TargType == 2";
      inputFile1 = dataDir + "/C/comb_dataC.root";
      inputFile2 = dataDir + "/Fe/comb_dataFe.root";
      inputFile3 = dataDir + "/Pb/comb_dataPb.root";
    }
  }
  // names
  plotFile = outDir + "/samp-frac-" + targetOption + "_" + dataOption + ".png";
}
