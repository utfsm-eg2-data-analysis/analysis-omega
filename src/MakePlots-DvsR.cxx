/**************************************/
/* MakePlots-DvsR.cxx                 */
/*                                    */
/* Created by Andrés Bórquez          */
/*                                    */
/**************************************/

// Offers a comparison between data and simrec

#include <iostream>

#include "TROOT.h"
#include "TChain.h"
#include "TTree.h"
#include "TCut.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TCut.h"
#include "TString.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TGaxis.h"

/*** Global variables ***/

TString proFolder = "/home/borquez/omegaThesis";
TString topDataFolder = proFolder +  "/out/filterData";
TString topSimFolder = proFolder +  "/out/filterSim/simrec";
TString outFolder = proFolder + "/out/MakePlots";

TString inputDataFile1 = "";
TString inputDataFile2 = "";
TString inputDataFile3 = "";
TString inputSimrecFile;

// main options
TString targetOption; // C: Carbon | Fe: Iron | Pb: Lead (none by default)
TString kinvarChosen = "M"; // M: mass difference | Q: Q2 | N: nu | Z: Z | P: phiPQ | T: Pt2
Int_t binNumberZ = 0; // 0: extracts from Z=0.5 to Z=1. | [3-7]: binning on

// cuts
TCut cutDIS = "Q2 > 1 && W > 2";
TCut cutPi0 = "0.059 < mpi0 && mpi0 < 0.209"; // mikewood cut
TCut cutPipPim = "0.48 > mpippim || 0.51 < mpippim"; // mikewood cut
TCut cutAll = cutPi0 && cutDIS && cutPipPim;
TCut cutTargType;
TCut cutZ;

// names stuff (to be assigned by the options)
TString titleZ = "";
TString titleKinvar;
TString titleXAxis;
TString titleYAxis = "Normalized Counts = Entries^{-1}";
TString outPrefix;
TString toPlotKinvar;
TString sufixZBin = "";
TString histProperties;

Double_t normSimrec = 1;
Double_t normData = 1;

TString outPlotName;

// default values for legend position
Double_t legendY1 = 0.8;
Double_t legendY2 = 0.9;
Double_t legendX1 = 0.65;
Double_t legendX2 = 0.85;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

void setAlias(TTree *treeExtracted);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  /*** Data ***/
  
  TChain *tData = new TChain();
  tData->Add(inputDataFile1 + "/outdata");
  tData->Add(inputDataFile2 + "/outdata");
  tData->Add(inputDataFile3 + "/outdata");

  setAlias(tData);
  
  TH1F *dataHist;
  tData->Draw(toPlotKinvar + ">>data" + histProperties, cutAll && cutTargType && cutZ, "goff");
  dataHist = (TH1F *)gROOT->FindObject("data");
  
  dataHist->SetTitleFont(22);
  dataHist->SetTitle(titleKinvar + targetOption + titleZ);
  dataHist->SetLineColor(kBlack);
  dataHist->SetLineWidth(3);
  dataHist->GetXaxis()->SetTitle(titleXAxis);
  dataHist->GetYaxis()->SetTitle(titleYAxis);
  dataHist->GetXaxis()->CenterTitle();
  dataHist->GetYaxis()->CenterTitle();
  
  /*** Reconstructed ***/
  
  TChain *tSimrec = new TChain();
  tSimrec->Add(inputSimrecFile + "/outdata");

  setAlias(tSimrec);
  
  TH1F *simrecHist;
  tSimrec->Draw(toPlotKinvar + ">>simrec" + histProperties, cutAll && cutTargType && cutZ, "goff");
  simrecHist = (TH1F *)gROOT->FindObject("simrec");

  simrecHist->SetTitleFont(22);
  simrecHist->SetLineColor(kBlue);
  simrecHist->SetLineWidth(3);
    
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768); 
  gStyle->SetOptStat(0);
  c->SetGrid();

  // normalization

  if (kinvarChosen == "M" || kinvarChosen == "N") {
    normData = (Double_t) dataHist->GetBinContent(dataHist->GetMaximumBin());
    normSimrec = (Double_t) simrecHist->GetBinContent(simrecHist->GetMaximumBin());
  } else {
    normData = (Double_t) dataHist->GetEntries();
    normSimrec = (Double_t) simrecHist->GetEntries();
  }
  
  dataHist->Scale(1/normData);
  simrecHist->Scale(1/normSimrec);
  
  dataHist->Draw();
  simrecHist->Draw("SAME");
    
  TLegend *l = new TLegend(legendX1, legendY1, legendX2, legendY2);
  l->AddEntry(dataHist, "data", "l");
  l->AddEntry(simrecHist, "reconstructed", "l");
  l->Draw();
  
  c->Print(outPlotName); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakePlots-DvsR -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:k:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'k': kinvarChosen = optarg; break;
    case 'z': binNumberZ = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakePlots-DvsR -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "targetOption=" << targetOption << std::endl;
  std::cout << "toPlotKinvar=" << toPlotKinvar << std::endl;
  std::cout << "binNumberZ=" << binNumberZ << std::endl;
}

void printUsage() {
  std::cout << "MakePlots-DvsR program. Usage is:" << std::endl;
  std::cout << "./MakePlots-DvsR -[options] -[more options]" << std::endl;
  std::cout << "  h         : prints help and exit program" << std::endl;
  std::cout << "  t[target] : select target: D | C | Fe | Pb" << std::endl;
  std::cout << "  k[kinvar] : sets kinvar to draw, it can be: " << std::endl;
  std::cout << "      --> M : IMD (pi+, pi-, pi0)" << std::endl;
  std::cout << "      --> Q : Q2" << std::endl;
  std::cout << "      --> P : PhiPQ" << std::endl;
  std::cout << "      --> T : Pt2" << std::endl;
  std::cout << "      --> 0 : P(pi0)" << std::endl;
  std::cout << "      --> 1 : P(pi+)" << std::endl;
  std::cout << "      --> 2 : P(pi-)" << std::endl;
  std::cout << "      --> 3 : P(omega)" << std::endl;
  std::cout << "  z[3-7]    : turns on binning in Z (off by default) and analyzes that specific bin" << std::endl;
}

void assignOptions() {
  // for targets
  if (targetOption == "D") {
    inputDataFile1 = topDataFolder + "/C/wout_C-thickD2.root";
    inputDataFile2 = topDataFolder + "/Fe/wout_Fe-thickD2.root";
    inputDataFile3 = topDataFolder + "/Pb/wout_Pb-thinD2.root";
    inputSimrecFile = topSimFolder + "/jlab/D/wout_simrecD.root";
    cutTargType = "TargType == 1";
  } else if (targetOption == "C") {
    inputDataFile1 = topDataFolder + "/C/wout_C-thickD2.root";
    inputSimrecFile = topSimFolder + "/jlab/C/wout_simrecC.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Fe") {
    inputDataFile1 = topDataFolder + "/Fe/wout_Fe-thickD2.root";
    inputSimrecFile = topSimFolder + "/jlab/Fe/wout_simrecFe.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Pb") {
    inputDataFile1 = topDataFolder + "/Pb/wout_Pb-thinD2.root";
    inputSimrecFile = topSimFolder + "/usm/Pb/wout_simrecPb.root";
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
  } else if (binNumberZ == 0) {
    lowEdgeZ = 0.5;
    highEdgeZ = 1.;
  }
  cutZ = Form("%f < Z && Z < %f", lowEdgeZ, highEdgeZ);
  if (binNumberZ) titleZ = Form(" in (%.02f < Z < %.02f)", lowEdgeZ, highEdgeZ);
  sufixZBin = Form("-z%d", binNumberZ);
  // for kinvar
  if (kinvarChosen == "M") {
    toPlotKinvar = "deltam";
    titleKinvar = "IMD(#pi^{+} #pi^{-} #pi^{0}) for ";
    titleXAxis = "IMD (GeV)";
    titleYAxis = "Normalized Counts = Max Height^{-1}";
    histProperties = "(200, 0., 1.6)";
  } else if (kinvarChosen == "Q") {
    toPlotKinvar = "Q2";
    titleKinvar = "Q^{2} for ";
    titleXAxis = "Q^{2}";
    histProperties = "(200, 1., 4.)";
  } else if (kinvarChosen == "N") {
    toPlotKinvar = "Nu";
    titleKinvar = "#nu for ";
    titleXAxis = "#nu (GeV)";
    titleYAxis = "Normalized Counts = Max Height^{-1}";
    histProperties = "(200, 2.2, 4.2)";
    legendX1 = 0.15;
    legendX2 = 0.35;
  }  else if (kinvarChosen == "P") {
    toPlotKinvar = "PhiPQ";
    titleKinvar = "#phi_{PQ}(#omega) for ";
    titleXAxis = "#phi_{PQ}";
    histProperties = "";
    legendY1 = 0.3;
    legendY2 = 0.4;
  } else if (kinvarChosen == "W") {
    toPlotKinvar = "W";
    titleKinvar = "W(#omega) for ";
    titleXAxis = "W";
    histProperties = "(200, 2., 3.)";
  } else if (kinvarChosen == "T") {
    toPlotKinvar = "Pt2";
    titleKinvar = "p_{T}^{2}(#pi^{+} #pi^{-} #pi^{0}) for ";
    titleXAxis = "GeV^{2}";
    histProperties = "(150, 0., 1.5)";
  } else if (kinvarChosen == "0") {
    toPlotKinvar = "Ppi0";
    titleKinvar = "P(#pi^{0}) for ";
    titleXAxis = "P (GeV)";
    histProperties = "";
  } else if (kinvarChosen == "1") {
    toPlotKinvar = "Ppip";
    titleKinvar = "P(#pi^{+}) for ";
    titleXAxis = "P (GeV)";
    histProperties = "";
  } else if (kinvarChosen == "2") {
    toPlotKinvar = "Ppim";
    titleKinvar = "P(#pi^{-}) for ";
    titleXAxis = "P (GeV)";
    histProperties = "";
  } else if (kinvarChosen == "3") {
    toPlotKinvar = "Pomega";
    titleKinvar = "P(#pi^{+} #pi^{-} #pi^{0}) for ";
    titleXAxis = "P (GeV)";
    histProperties = "";
  }
  // names
  outPlotName = outFolder + "/data_vs_simrec-" + targetOption + sufixZBin + "-" + toPlotKinvar + ".png";
}

void setAlias(TTree *treeExtracted) {
  // pip
  treeExtracted->SetAlias("p2pip", "fX[2]*fX[2] + fY[2]*fY[2] + fZ[2]*fZ[2]");
  treeExtracted->SetAlias("E2pip", "p2pip + 0.13957*0.13957");
  treeExtracted->SetAlias("m2pip", "E2pip - p2pip");
  treeExtracted->SetAlias("mpip", "TMath::Sqrt(m2pip)");
  treeExtracted->SetAlias("Epip", "TMath::Sqrt(E2pip)");
  treeExtracted->SetAlias("Ppip", "TMath::Sqrt(p2pip)"); // new!
  
  // pim
  treeExtracted->SetAlias("p2pim", "fX[3]*fX[3] + fY[3]*fY[3] + fZ[3]*fZ[3]");
  treeExtracted->SetAlias("E2pim", "p2pim + 0.13957*0.13957");
  treeExtracted->SetAlias("m2pim", "E2pim - p2pim");
  treeExtracted->SetAlias("mpim", "TMath::Sqrt(m2pim)");
  treeExtracted->SetAlias("Epim", "TMath::Sqrt(E2pim)");
  treeExtracted->SetAlias("Ppim", "TMath::Sqrt(p2pim)"); // new!
  
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
  treeExtracted->SetAlias("Ppi0", "TMath::Sqrt(p2pi0)"); // new!
  
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
  treeExtracted->SetAlias("Pomega", "TMath::Sqrt(p2omega)"); // new!
}
