/*************************************************/
/*  DiffractiveProcesses.cxx                     */
/*                                               */
/*  Andrés Bórquez, CCTVAL                       */
/*                                               */
/*************************************************/

// An attempt to check Diffractive or Exclusive processes

#include <iostream>

#include "TROOT.h"
#include "TChain.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TCut.h"
#include "TString.h"

/*** Global Variables ***/

// parameters
TString targetOption;
Int_t binNumberZ = 0; // 0: extracts from Z=0.5 to Z=1. | [3-7]: binning on

TString proFolder = "/home/borquez/omegaThesis";
TString inputFolder = proFolder + "/out/filterData";
TString outFolder = proFolder + "/out/DiffractiveProcesses";

TString inputFile1 = "";
TString inputFile2 = "";
TString inputFile3 = "";

TCut cutTargType;
TCut cutZ;
TCut cutsB = "";
TCut cutsC = "";

TString observableB = "";
TString histProperties;
TString titleHist;
TString titleAxis;
TString outputFile;

TString titleZ = "";
TString sufixZBin = "";

// new content!
Int_t stageNumber = 0;
TString sufixStage;

/*** Declaration of Functions ***/

void printUsage();
inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void assignOptions();

void setAlias(TTree *treeExtracted);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();
  
  /*** Init trees ***/
    
  // ToyCombine.cxx
  TChain *t2 = new TChain();
  t2->Add(inputFile1 + "/mix"); // full data
  t2->Add(inputFile2 + "/mix"); // full data
  t2->Add(inputFile3 + "/mix"); // full data

  setAlias(t2); // new!
  
  t2->Draw(observableB + ">>toy_combine" + histProperties, cutsB && cutZ && cutTargType);
  t2->Draw(observableB + ">>toy_combine2" + histProperties, cutsC && cutZ && cutTargType);
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000); 
  gStyle->SetOptStat(0);
  c->SetGrid();

  TH1F *histB;
  TH1F *histC;
  
  histB = (TH1F *)gROOT->FindObject("toy_combine");
  histB->SetTitle(titleHist + titleZ);
  histB->GetXaxis()->SetTitle(titleAxis);
  histB->GetXaxis()->CenterTitle();
  histB->SetFillColor(kRed);
  histB->SetLineColor(kRed);
  histB->SetLineWidth(2);
  histB->Draw("B");
  
  histC = (TH1F *)gROOT->FindObject("toy_combine2");
  histC->SetFillColor(kOrange);
  histC->SetLineColor(kOrange);
  histC->SetLineWidth(2);
  histC->Draw("B SAME");

  TLegend *l = new TLegend(0.65, 0.8, 0.9, 0.9);
  if (stageNumber == 0) {
    l->AddEntry(histB, "all #omega", "f");
    l->AddEntry(histC, "#omega from (1,1,2)", "f");
  } else if (stageNumber == 1) {
    l->AddEntry(histB, "DIS & 0.5 < Z < 1.0", "f");
    l->AddEntry(histC, "DIS & 0.8 < Z < 1.0", "f");  
  } else if (stageNumber == 2) {
    l->AddEntry(histB, "DIS", "f");
    l->AddEntry(histC, "DIS & M_{x} > M_{P} + M_{#omega}", "f");
  } else if (stageNumber == 3) {
    l->AddEntry(histB, "DIS", "f");
    l->AddEntry(histC, "DIS & M_{x} > M_{P} + M_{#omega}", "f");
  }
  l->Draw();
  
  c->Print(outputFile); // output file
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./DiffractiveProcesses -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:z:s:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'z': binNumberZ = atoi(optarg); break;
    case 's': stageNumber = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./DiffractiveProcesses -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "DiffractiveProcesses program. The chosen options were: " << std::endl;
  std::cout << "targetOption="  << targetOption << std::endl;
  std::cout << "binNumberZ="  << binNumberZ << std::endl;
  std::cout << "stageNumber="  << stageNumber << std::endl;  
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "DiffractiveProcesses program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./DiffractiveProcesses -h" << std::endl;
  std::cout << "    prints this message and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./DiffractiveProcesses -t[D, C, Fe, Pb]" << std::endl;
  std::cout << "    filters collection of files for the respective target" << std::endl;
  std::cout << std::endl;
  std::cout << "./DiffractiveProcesses -s[n]" << std::endl;
  std::cout << "    selects stage" << std::endl;
  std::cout << "    0: procedence studies" << std::endl;
  std::cout << "    1: missing mass studies" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // target options
  if (targetOption == "D") {
    inputFile1 = inputFolder + "/C/comb_C-thickD2.root";
    inputFile2 = inputFolder + "/Fe/comb_Fe-thickD2.root";
    inputFile3 = inputFolder + "/Pb/comb_Pb-thinD2.root";
    cutTargType = "TargType == 1";
  } else if (targetOption == "C") {
    inputFile1 = inputFolder + "/C/comb_C-thickD2.root";
    cutTargType = "TargType == 2"; 
  } else if (targetOption == "Fe") {
    inputFile1 = inputFolder + "/Fe/comb_Fe-thickD2.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Pb") {
    inputFile1 = inputFolder + "/Pb/comb_Pb-thinD2.root";
    cutTargType = "TargType == 2";
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
  } else if (binNumberZ == 8) {
    lowEdgeZ = 0.8;
    highEdgeZ = 1.0;
  }
  if (binNumberZ) {
    cutZ = Form("%f < Z && Z < %f", lowEdgeZ, highEdgeZ);
    titleZ = Form(" in (%.02f < Z < %.02f)", lowEdgeZ, highEdgeZ);
    sufixZBin = Form("-z%d", binNumberZ);
  }
  if (stageNumber == 0) {
    observableB = "wM";
    cutsB = "Q2 > 1 && W > 2 && Yb < 0.85 && pi0M > 0.059 && pi0M < 0.209 && (pippimM < 0.48 || pippimM > 0.51)";
    cutsC = "Q2 > 1 && W > 2 && Yb < 0.85 && pi0M > 0.059 && pi0M < 0.209 && (pippimM < 0.48 || pippimM > 0.51) && (nPip == 1 && nPim == 1 && nGamma == 2)";
    histProperties = "(250, 0., 2.5)";
    titleHist = "Procedence of #omega w/ cuts for " + targetOption;
    titleAxis = "IM(#omega) (GeV)";
  } else if (stageNumber == 1) {
    observableB = "Mx";
    cutsB = "Q2 > 1 && W > 2 && Yb < 0.85 && 0.5 < Z && Z < 1.0";
    cutsC = "Q2 > 1 && W > 2 && Yb < 0.85 && 0.8 < Z && Z < 1.0";
    histProperties = "(250, 0., 3)";
    titleHist = "M_{x}(#omega) for " + targetOption;
    titleAxis = "M_{x} (GeV)";
  } else if (stageNumber == 2) {
    observableB = "Z";
    cutsB = "Q2 > 1 && W > 2 && Yb < 0.85";
    cutsC = "Q2 > 1 && W > 2 && Yb < 0.85 && Mx > (0.938272 + wM)";
    histProperties = "(150, 0., 1.5)";
    titleHist = "Z(#omega) for " + targetOption;
    titleAxis = "Z";
  } else if (stageNumber == 3) {
    observableB = "wD";
    cutsB = "Q2 > 1 && W > 2 && Yb < 0.85";
    cutsC = "Q2 > 1 && W > 2 && Yb < 0.85 && Mx > (0.938272 + wM)";
    histProperties = "(200, 0., 2)";
    titleHist = "IMD(#pi^{+} #pi^{-} #pi^{0}) for " + targetOption;
    titleAxis = "IMD (GeV)";
  }
  sufixStage = Form("-s%d", stageNumber);
  outputFile = outFolder + "/missing-mass-t" + targetOption + sufixZBin + sufixStage + ".png";
}


void setAlias(TTree *treeExtracted) {
  treeExtracted->SetAlias("Pl2", "wP2*CosThetaPQ*CosThetaPQ");
  treeExtracted->SetAlias("absQ", "TMath::Sqrt(Nu*Nu + Q2)");
  treeExtracted->SetAlias("Mx2", "W*W + wM*wM - 2*Z*Nu*Nu + 2*TMath::Sqrt(Pl2)*absQ - 2*Z*Nu*0.938272");
  treeExtracted->SetAlias("Mx", "TMath::Sqrt(Mx2)");
}
