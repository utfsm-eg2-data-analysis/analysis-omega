/**************************************/
/* GetQuantiles.cxx                   */
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
#include "TLine.h"
#include "TF1.h"

/*** Global variables ***/

TString proFolder   = "/home/borquez/omegaThesis";
TString inputFolder = proFolder + "/out/filterData";
TString outFolder   = proFolder + "/out/GetQuantiles";

// parameters
TString targetOption;
TString kinvarOption;
Int_t   Nquantiles;

// cuts
TCut cutDIS = "Q2 > 1 && W > 2 && Yb < 0.85";
TCut cutPi0 = "0.059 < pi0M && pi0M < 0.209"; // mikewood cut
TCut cutPipPim = "0.48 > pippimM || 0.51 < pippimM"; // mikewood cut
TCut cutAll = cutDIS && cutPipPim && cutPi0;
TCut cutTargType;

// to be assigned by the parameters
TString inputFile1;
TString inputFile2;
TString inputFile3;

TString dataPrefix;
TString toPlotKinvar;
TString kinvarTitle;
TString histProperties;

TString outputPlotName;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

void drawVerticalLine(Double_t x);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  TH1F *dataHist;
  treeExtracted->Draw(toPlotKinvar + ">>data" + histProperties, cutAll && cutTargType, "goff");
  dataHist = (TH1F *)gROOT->FindObject("data");

  dataHist->SetTitle(kinvarTitle + targetOption);
  dataHist->SetLineColor(kBlack);
  dataHist->SetLineWidth(2);
  dataHist->GetXaxis()->SetTitle(toPlotKinvar);
  dataHist->GetYaxis()->SetTitle("Events");
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768); 
  c->SetGrid();

  // because Nu is special...
  if (toPlotKinvar == "Nu") {
    gStyle->SetStatX(0.30);
    gStyle->SetStatY(0.85);
  }
  
  dataHist->Draw();

  /*** Quantile stuff ***/
  
  Double_t xq[Nquantiles]; // percentages
  Double_t yq[Nquantiles]; // output array
  for (Int_t i = 0; i < Nquantiles; i++) {
    xq[i] = Double_t(i+1)/Nquantiles;
    dataHist->GetQuantiles(Nquantiles, yq, xq);
    // print information --> IMPORTANT
    if (i == 0) std::cout << "Edges: " << dataHist->GetBinLowEdge(1) << ", " << yq[i] << ", ";
    else if (i == (Nquantiles - 1)) std::cout << yq[i] << std::endl;
    else std::cout << yq[i] << ", ";
    // draw line
    if (i != (Nquantiles - 1)) drawVerticalLine(yq[i]);
  }

  c->Print(outputPlotName); // output file
  
  delete c;
  delete dataHist;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./GetQuantiles -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:k:q:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'k': kinvarOption = optarg; break;
    case 'q': Nquantiles = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./GetQuantiles -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << std::endl;
  std::cout << "Executing GetQuantiles program. Parameters chosen are:" << std::endl;
  std::cout << "  targetOption=" << targetOption << std::endl;
  std::cout << "  toPlotKinvar=" << toPlotKinvar << std::endl;
  std::cout << "  Nquantiles=" << Nquantiles << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << std::endl;
  std::cout << "GetQuantiles program. This program obtains the edges for each quantile. Usage is:" << std::endl;
  std::cout << "./GetQuantiles -[options] -[more options]" << std::endl;
  std::cout << "  h          : prints help and exit program" << std::endl;
  std::cout << "  t[target]  : selects target: D | C | Fe | Pb" << std::endl;
  std::cout << "  k[Z,P,Q,N] : sets kinvar to draw, it can be: Z, Q2, Nu or Pt2" << std::endl;
  std::cout << "  q[number]  : sets the number of quantiles" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
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
  // for kinvar
  if (kinvarOption == "Z") {
    toPlotKinvar = "Z";
    kinvarTitle = "Z in ";
    histProperties = "(100, 0.5, 1.0)";
  } else if (kinvarOption == "P") {
    toPlotKinvar = "Pt2";
    kinvarTitle = "Pt2 in ";
    histProperties = "(100, 0.0, 1.5)";
  } else if (kinvarOption == "Q") {
    toPlotKinvar = "Q2";
    kinvarTitle = "Q2 in ";
    histProperties = "(100, 1.0, 4.0)";
  } else if (kinvarOption == "N") {
    toPlotKinvar = "Nu";
    kinvarTitle = "Nu in ";
    histProperties = "(100, 2.2, 4.2)";
  }
  // name
  outputPlotName = outFolder + Form("/q%d-", Nquantiles) + toPlotKinvar + "-" + targetOption + ".png";
}

void drawVerticalLine(Double_t x) {
  Double_t u;
  gPad->Update(); // necessary
  u = (x - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  TLine *linex = new TLine(u, 0.1, u, 0.9);
  linex->SetLineWidth(2);
  linex->SetNDC(kTRUE);
  linex->Draw();
}
