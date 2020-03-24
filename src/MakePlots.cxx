/**************************************/
/* MakePlots.cxx                      */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TCut.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TCut.h"
#include "TString.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLatex.h"

/*** Global variables ***/

TString proFolder   = "/home/borquez/omegaThesis";
TString inputFolder = proFolder + "/out/filterData";  // default for data
TString outFolder   = proFolder + "/out/MakePlots";
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";

// main options
Int_t   dataFlag = 0;
Int_t   simFlag  = 0;
TString targetOption;
TString observableChosen = "M";
Int_t   binNumberZ = 0; // 0: off | [3-7]: on

// cuts
TCut cutTargType;
TCut cutZ = "";

// names stuff (to be assigned by the options)
TString titleDraw;
TString titleZ = "";
TString sufixZBin = "";
TString titleObservable;
TString titleAxis;
TString outPrefix;
TString toPlotObservable;
TString histProperties;
TString outputPlotName;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // cuts
  TCut cutDIS = "Q2 > 1 && W > 2 && Yb < 0.85";
  TCut cutPi0 = "0.059 < pi0M && pi0M < 0.209";
  TCut cutPipPim = "0.48 > pippimM || 0.51 < pippimM";
  TCut cutAll = cutDIS && cutPipPim && cutPi0 && cutTargType && cutZ;

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  TH1F *theHist;
  treeExtracted->Draw(toPlotObservable + ">>" + outPrefix + histProperties, cutAll && cutTargType && cutZ, "goff");
  theHist = (TH1F *)gROOT->FindObject(outPrefix);
  
  theHist->SetTitleFont(22);
  theHist->SetTitle(titleObservable + targetOption + titleDraw + titleZ);
  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(3);
  theHist->GetXaxis()->SetTitle(titleAxis);
  theHist->GetYaxis()->SetTitle("Counts");
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768); 
  c->SetGrid();
  
  theHist->Draw("E");
  
  c->Print(outputPlotName); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakePlots -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hdst:o:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'd': dataFlag = 1; break;
    case 's': simFlag = 1; break;      
    case 't': targetOption = optarg; break;
    case 'o': observableChosen = optarg; break;
    case 'z': binNumberZ = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakePlots -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << std::endl;
  std::cout << "Executing MakePlots program. Parameters chosen are:" << std::endl;
  std::cout << "  dataFlag         = " << dataFlag << std::endl;
  std::cout << "  simFlag          = " << simFlag << std::endl;
  std::cout << "  targetOption     = " << targetOption << std::endl;
  std::cout << "  toPlotObservable = " << toPlotObservable << std::endl;
  std::cout << "  binNumberZ       = " << binNumberZ << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << std::endl;
  std::cout << "MakePlots program. Usage is:" << std::endl;
  std::cout << "./MakePlots -[options] -[more options]" << std::endl;
  std::cout << "  h         : prints help and exit program" << std::endl;
  std::cout << "  t[target] : select target: D | C | Fe | Pb" << std::endl;
  std::cout << "  d : draw data" << std::endl;
  std::cout << "  s : draw simrec" << std::endl;
  std::cout << "  o[option] : sets observable to draw, it can be: " << std::endl;
  std::cout << "      --> M : omega invariant mass" << std::endl;
  std::cout << "      --> D : omega invariant mass difference" << std::endl;
  std::cout << "      --> Q : Q2" << std::endl;
  std::cout << "      --> N : Nu" << std::endl;
  std::cout << "      --> Z : Z" << std::endl;
  std::cout << "      --> P : PhiPQ" << std::endl;
  std::cout << "      --> T : Pt2" << std::endl;
  std::cout << "  z[3-7]    : turns on binning in Z (off by default) and analyzes that specific bin" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for kind of data
  if (dataFlag) {
    outPrefix = "data";
    titleDraw = " Data ";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = inputFolder + "/C/comb_C-thickD2.root";
      inputFile2 = inputFolder + "/Fe/comb_Fe-thickD2.root";
      inputFile3 = inputFolder + "/Pb/comb_Pb-thinD2.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/C/comb_C-thickD2.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/Fe/comb_Fe-thickD2.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/Pb/comb_Pb-thinD2.root";
    }
  } else if (simFlag) {
    outPrefix = "simrec";
    titleDraw = " Simrec ";
    inputFolder = proFolder + "/filterSim";
  }
  // for Z binning
  Double_t lowEdgeZ, highEdgeZ;
  if (binNumberZ == 3) {
    lowEdgeZ = 0.5;
    highEdgeZ = 0.557;
  } else if (binNumberZ == 4) {
    lowEdgeZ = 0.557;
    highEdgeZ = 0.617;
  } else if (binNumberZ == 5) {
    lowEdgeZ = 0.617;
    highEdgeZ = 0.689;
  } else if (binNumberZ == 6) {
    lowEdgeZ = 0.689;
    highEdgeZ = 0.784;
  } else if (binNumberZ == 7) {
    lowEdgeZ = 0.784;
    highEdgeZ = 1.;
  }
  if (binNumberZ > 0) {
    cutZ = Form("%f < Z && Z < %f", lowEdgeZ, highEdgeZ);
    titleZ = Form(" in (%.02f < Z < %.02f)", lowEdgeZ, highEdgeZ);
    sufixZBin = Form("-z%d", binNumberZ);
  }
  // for observable
  if (observableChosen == "M") {
    toPlotObservable = "wM";
    titleObservable = "IM(#omega) for ";
    titleAxis = "IM (GeV)";
    histProperties = "(250, 0., 2.5.)";
  } else if (observableChosen == "D") {
    toPlotObservable = "wD";
    titleObservable = "IMD(#omega) for ";
    titleAxis = "IMD (GeV)";
    histProperties = "(200, 0., 1.6)";
  } else if (observableChosen == "Q") {
    toPlotObservable = "Q2";
    titleObservable = "Q^{2}";
    titleAxis = "Q^{2}";
    histProperties = "(100, 1., 4.)";  
  } else if (observableChosen == "N") {
    toPlotObservable = "Nu";
    titleObservable = "#nu";
    titleAxis = "#nu";
    histProperties = "(200, 2.2, 4.2)";
  } else if (observableChosen == "Z") {
    toPlotObservable = "Z";
    titleObservable = "Z";
    titleAxis = "Z";
    histProperties = "(100, 0., 1.2)";
  } else if (observableChosen == "P") {
    toPlotObservable = "PhiPQ";
    titleObservable = "#phi_{PQ} ";
    titleAxis = "#phi_{PQ}";
    histProperties = "(100, -180, 180.)";
  } else if (observableChosen == "T") {
    toPlotObservable = "Pt2omega";
    titleObservable = "P_{T}^{2} ";
    titleAxis = "GeV^{2}";
    histProperties = "(100, 0., 1.5)";
  }
  // output name
  outputPlotName = outFolder + "/" + outPrefix + "-" + toPlotObservable + "-" + targetOption + sufixZBin + ".png";
}
