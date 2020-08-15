/**************************************/
/* CheckBkg_f1.cxx                    */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// (Suggestion of WB)
// This program wants to check if f1(1285) is one of the reasons for the huge bkg
// in the omega invariant mass difference spectrum.

#include "analysisConfig.h"

// main options
TString outDir = proDir + "/out/CheckBkg";

// target option
TString targetOption;
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";
TCut    cutTargType;
TString plotFile;

Int_t   caseOption;
TString caseTitle;
TString caseSufix;
Color_t caseColor;
TCut    f1_decay;

TCut    kinvarCut;
Int_t   binNumberZ;
TString kinvarSufix;
TString kinvarTitle;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

/*** Program ***/

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // dir structure, just in case
  system("mkdir -p " + outDir);
  
  // read data
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  // second hist
  TH1F *theHist2;
  treeExtracted->Draw("wM_corr>>theHist2(200, 0, 2.5)", cutTargType && cutDIS && f1_decay && kinvarCut, "goff");
  theHist2 = (TH1F *)gROOT->FindObject("theHist2");
  
  theHist2->SetTitle("m (#gamma #gamma #pi^{+} #pi^{-}) in " + targetOption + " data" + kinvarTitle);

  theHist2->SetLineColor(caseColor);
  theHist2->SetFillStyle(1);
  theHist2->SetFillColor(caseColor);

  theHist2->GetXaxis()->SetTitle("Reconstructed Mass [GeV]");
  theHist2->GetXaxis()->CenterTitle();
  theHist2->GetYaxis()->SetMaxDigits(3);
  
  theHist2->SetLineWidth(3);
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 1366);
  gStyle->SetOptStat(0);
  c->SetTickx(1);
  c->SetTicky(1);
  
  theHist2->Draw("HIST");
  
  drawVerticalLine(kMeta, kRed);
  drawVerticalLine(kMomega, kRed); // 782 MeV
  drawVerticalLine(kMf1, kRed); // f1 pdg mass

  /*** Legend ***/

  TLegend *l = new TLegend(0.55, 0.7, 0.9, 0.9); //x1,y1,x2,y2
  l->AddEntry(theHist2, caseTitle, "f");
  
  l->Draw();
  
  c->Print(plotFile);
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckBkg_f1 -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:c:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'c': caseOption = atoi(optarg); break;
    case 'z': binNumberZ = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckBkg_f1 -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing CheckBkg_f1 program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "CheckBkg_f1 program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckBkg_f1 -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckBkg_f1 -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckBkg_f1 -c[case]" << std::endl;
  std::cout << "    selects case: 1 | 4 | 5" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
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
  }
  // for cases
  if (caseOption == 1) {
    f1_decay = "nGamma == 4 && nPip == 1 && nPim == 1";
    caseColor = kOrange;
    caseTitle = "nGamma == 4 && nPip == 1 && nPim == 1";
  } else if (caseOption == 4) {
    f1_decay = "nGamma == 2 && nPip == 2 && nPim == 2";
    caseColor = kGreen;
    caseTitle = "nGamma == 2 && nPip == 2 && nPim == 2";
  } else if (caseOption == 5) {
    f1_decay = "nGamma == 6 && nPip == 1 && nPim == 1";
    caseColor = kCyan;
    caseTitle = "nGamma == 6 && nPip == 1 && nPim == 1";    
  }
  caseSufix = Form("-case%d", caseOption);
  // for Z
  kinvarSufix = Form("-z%d", binNumberZ);
  kinvarCut = Form("%f < wZ_corr && wZ_corr < %f", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
  kinvarTitle = Form(" (%.02f < Z < %.02f)", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
  // output name
  plotFile = outDir + "/f1-" + targetOption + caseSufix + kinvarSufix + ".png";
}
