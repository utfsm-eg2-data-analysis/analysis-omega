/**************************************/
/* old_MakePlots.cxx                  */
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

void setAlias(TTree *treeExtracted); // old

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // cuts
  TCut cutDIS = "Q2 > 1 && W > 2"; // old
  TCut cutPi0 = "0.059 < mpi0 && mpi0 < 0.209"; // old
  TCut cutPipPim = "0.48 > mpippim || 0.51 < mpippim"; // old
  TCut cutAll = cutDIS && cutPipPim && cutPi0 && cutTargType && cutZ;

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/outdata");
  treeExtracted->Add(inputFile2 + "/outdata");
  treeExtracted->Add(inputFile3 + "/outdata");

  setAlias(treeExtracted); // old
  
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
    std::cerr << "Empty command line. Execute ./old_MakePlots -h to print usage." << std::endl;
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
      std::cerr << "Unrecognized argument. Execute ./old_MakePlots -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << std::endl;
  std::cout << "Executing old_MakePlots program. Parameters chosen are:" << std::endl;
  std::cout << "  dataFlag         = " << dataFlag << std::endl;
  std::cout << "  simFlag          = " << simFlag << std::endl;
  std::cout << "  targetOption     = " << targetOption << std::endl;
  std::cout << "  toPlotObservable = " << toPlotObservable << std::endl;
  std::cout << "  binNumberZ       = " << binNumberZ << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << std::endl;
  std::cout << "old_MakePlots program. Usage is:" << std::endl;
  std::cout << "./old_MakePlots -[options] -[more options]" << std::endl;
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
      inputFile1 = inputFolder + "/C/wout_C-thickD2.root"; // old
      inputFile2 = inputFolder + "/Fe/wout_Fe-thickD2.root"; // old
      inputFile3 = inputFolder + "/Pb/wout_Pb-thinD2.root"; // old
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/C/wout_C-thickD2.root"; // old
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/Fe/wout_Fe-thickD2.root"; // old
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/Pb/wout_Pb-thinD2.root"; // old
    }
  } else if (simFlag) {
    outPrefix = "simrec";
    titleDraw = " Simrec ";
    inputFolder = proFolder + "/out/filterSim/simrec";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = inputFolder + "/jlab/D/wout_simrecD.root"; // old
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/jlab/C/wout_simrecC.root"; // old
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/jlab/Fe/wout_simrecFe.root"; // old
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/usm/Pb/wout_simrecPb.root"; // old
    }
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
    toPlotObservable = "momega"; // old
    titleObservable = "IM(#omega) for ";
    titleAxis = "IM (GeV)";
    histProperties = "(250, 0., 2.5.)";
  } else if (observableChosen == "D") {
    toPlotObservable = "deltam"; // old
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
  }
  // output name
  outputPlotName = outFolder + "/old_" + outPrefix + "-" + toPlotObservable + "-" + targetOption + sufixZBin + ".png"; // old
}

void setAlias(TTree *treeExtracted) { // old
  // pip
  treeExtracted->SetAlias("p2pip", "fX[2]*fX[2] + fY[2]*fY[2] + fZ[2]*fZ[2]");
  treeExtracted->SetAlias("E2pip", "p2pip + 0.13957*0.13957");
  treeExtracted->SetAlias("m2pip", "E2pip - p2pip");
  treeExtracted->SetAlias("mpip", "TMath::Sqrt(m2pip)");
  treeExtracted->SetAlias("Epip", "TMath::Sqrt(E2pip)");
  
  // pim
  treeExtracted->SetAlias("p2pim", "fX[3]*fX[3] + fY[3]*fY[3] + fZ[3]*fZ[3]");
  treeExtracted->SetAlias("E2pim", "p2pim + 0.13957*0.13957");
  treeExtracted->SetAlias("m2pim", "E2pim - p2pim");
  treeExtracted->SetAlias("mpim", "TMath::Sqrt(m2pim)");
  treeExtracted->SetAlias("Epim", "TMath::Sqrt(E2pim)");
  
  // pi0
  treeExtracted->SetAlias("Pxpi0", "fX[0] + fX[1]");
  treeExtracted->SetAlias("Pypi0", "fY[0] + fY[1]");
  treeExtracted->SetAlias("Pzpi0", "fZ[0] + fZ[1]");
  treeExtracted->SetAlias("p2pi0", "Pxpi0*Pxpi0 + Pypi0*Pypi0 + Pzpi0*Pzpi0");
  treeExtracted->SetAlias("cos_theta", "(fX[0]*fX[1] + fY[0]*fY[1] + fZ[0]*fZ[1])/(fE[0]*fE[1])"); // original
  treeExtracted->SetAlias("m2pi0", "2*fE[0]*fE[1]*(1 - cos_theta)"); // original
  treeExtracted->SetAlias("mpi0", "TMath::Sqrt(m2pi0)");
  treeExtracted->SetAlias("E2pi0", "m2pi0 + p2pi0");
  treeExtracted->SetAlias("Epi0", "TMath::Sqrt(E2pi0)");
  
  // crossed terms
  treeExtracted->SetAlias("p1p2", "fX[2]*fX[3] + fY[2]*fY[3] + fZ[2]*fZ[3]");
  treeExtracted->SetAlias("E1E2", "TMath::Sqrt(E2pip*E2pim)");
  treeExtracted->SetAlias("p2p3", "fX[3]*Pxpi0 + fY[3]*Pypi0 + fZ[3]*Pzpi0");
  treeExtracted->SetAlias("E2E3", "TMath::Sqrt(E2pim*E2pi0)");
  treeExtracted->SetAlias("p1p3", "fX[2]*Pxpi0 + fY[2]*Pypi0 + fZ[2]*Pzpi0");
  treeExtracted->SetAlias("E1E3", "TMath::Sqrt(E2pip*E2pi0)");

  // dalitz plots!
  treeExtracted->SetAlias("m2pippim", "m2pip + m2pim + 2*(E1E2 - p1p2)");
  treeExtracted->SetAlias("m2pimpi0", "m2pim + m2pi0 + 2*(E2E3 - p2p3)");
  treeExtracted->SetAlias("m2pippi0", "m2pip + m2pi0 + 2*(E1E3 - p1p3)");

  // for the cuts
  treeExtracted->SetAlias("mpippim", "TMath::Sqrt(m2pippim)");
  treeExtracted->SetAlias("mpimpi0", "TMath::Sqrt(m2pimpi0)");
  treeExtracted->SetAlias("mpippi0", "TMath::Sqrt(m2pippi0)");

  // omega
  treeExtracted->SetAlias("Eomega", "Epip + Epim + fE[0] + fE[1]");
  treeExtracted->SetAlias("Pxomega", "fX[0] + fX[1] + fX[2] + fX[3]");
  treeExtracted->SetAlias("Pyomega", "fY[0] + fY[1] + fY[2] + fY[3]");
  treeExtracted->SetAlias("Pzomega", "fZ[0] + fZ[1] + fZ[2] + fZ[3]");
  treeExtracted->SetAlias("p2omega", "Pxomega*Pxomega + Pyomega*Pyomega + Pzomega*Pzomega");
  treeExtracted->SetAlias("momega", "TMath::Sqrt(Eomega*Eomega - Pxomega*Pxomega - Pyomega*Pyomega - Pzomega*Pzomega)");
  treeExtracted->SetAlias("deltam", "momega - mpi0 - mpip - mpim");
}
