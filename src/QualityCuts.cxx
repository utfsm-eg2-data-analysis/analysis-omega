/**************************************/
/* QualityCuts.cxx                    */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/QualityCuts";
TString inputFile1 = "";
TString inputFile2 = "";
TString inputFile3 = "";

// options
Int_t numberOption;
TString targetOption;
TString XOption;
TString YOption;
Int_t binNumberZ = 0;

// cuts
TCut cutAll;
TCut cutTargType;
TCut cutZ = "";

TString XVar;
TString YVar;
TString XAxis;
TString YAxis;
TString XHistProp;
TString YHistProp;
TString histProperties;

// name scheme
TString titleDraw;
TString titleZ;
TString sufixZBin;

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
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  // color stuff, smoran
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
  Double_t red[NRGBs]   = {0.00, 0.00, 0.87, 1.00, 0.51};
  Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
  Double_t blue[NRGBs]  = {0.51, 1.00, 0.12, 0.00, 0.00};
  
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  
  TH2F *theHist;
  treeExtracted->Draw(YVar + ":" + XVar + ">>" + outPrefix + histProperties, cutAll && cutTargType && cutZ, "goff");
  theHist = (TH2F *)gROOT->FindObject(outPrefix);
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 1366);
  c->SetTickx(1);
  c->SetTicky(1);
  gStyle->SetOptStat(0);
  gStyle->SetNumberContours(NCont); // colors, smoran
  
  theHist->SetTitle(YOption + ":" + XOption + " for " + targetOption + titleDraw + titleZ);
  theHist->GetYaxis()->SetTitle(YAxis);
  theHist->GetXaxis()->SetTitle(XAxis);
  theHist->GetYaxis()->CenterTitle();
  theHist->GetXaxis()->CenterTitle();
  theHist->SetContour(99);
  theHist->Draw("COLZ");

  drawVerticalLine(0.15, kRed, "cont");

  // normalization
  // theHist->Scale(1/((Double_t) theHist->GetEntries()));

  // log
  gPad->SetLogz();
  
  c->Print(plotFile); // output file
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./QualityCuts -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hn:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'n': numberOption = atoi(optarg); break;
    case 'z': binNumberZ = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./QualityCuts -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "QualityCuts program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./QualityCuts -h" << std::endl;
  std::cout << "  prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./QualityCuts -n[int]" << std::endl;
  std::cout << "  selects option: (0,1,2) = (im vs p(pi+), im vs p(pi-), im vs p(pi0))" << std::endl;
  std::cout << std::endl;  
}

void printOptions() {
  std::cout << "Executing QualityCuts program. The chosen parameters are:" << std::endl;
  std::cout << "  numberOption = " << numberOption << std::endl;
  std::cout << "  binNumberZ   = " << binNumberZ << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for kind of data
  outPrefix = "data";
  titleDraw = " Data";
  cutTargType = "TargType == 1";
  inputFile1 = dataDir + "/C/comb_C-thickD2.root";
  inputFile2 = dataDir + "/Fe/comb_Fe-thickD2.root";
  inputFile3 = dataDir + "/Pb/comb_Pb-thinD2.root";
  if (numberOption == 0) {
    // y
    YOption = "wM";
    YVar = YOption;
    YAxis = "IM(#pi^{+} #pi^{-} #gamma #gamma) (GeV)";
    YHistProp = "250, 0., 2.5";
    // x
    XOption = "pipP";
    XVar = "TMath::Sqrt(pipP2)";
    XAxis = "P(#pi^{+}) (GeV)";
    XHistProp = "300, 0., 3.";
  } else if (numberOption == 1) {
    // y
    YOption = "wM";
    YVar = YOption;
    YAxis = "IM(#pi^{+} #pi^{-} #gamma #gamma) (GeV)";
    YHistProp = "250, 0., 2.5";
    // x
    XOption = "pimP";
    XVar = "TMath::Sqrt(pimP2)";
    XAxis = "P(#pi^{-}) (GeV)";
    XHistProp = "300, 0., 3.";
  } else if (numberOption == 2) {
    // y
    YOption = "wM";
    YVar = YOption;
    YAxis = "IM(#pi^{+} #pi^{-} #gamma #gamma) (GeV)";
    YHistProp = "250, 0., 2.5";
    // x
    XOption = "pi0P";
    XVar = "TMath::Sqrt(pi0P2)";
    XAxis = "P(#pi^{0}) (GeV)";
    XHistProp = "300, 0., 3.";
  }
  // any option
  histProperties = "(" + XHistProp + ", " + YHistProp + ")";
  // for z
  if (binNumberZ) {
    cutZ = Form("%f < Z && Z < %f", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    titleZ = Form(" in (%.02f < Z < %.02f)", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    sufixZBin = Form("-z%d", binNumberZ);
  }
  // outfile
  plotFile = outDir + Form("/test-%d-z%d.png", numberOption, binNumberZ);  
 }
