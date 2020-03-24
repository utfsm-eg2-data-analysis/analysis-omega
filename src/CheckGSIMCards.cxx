/**************************************/
/* CheckGSIMCards.cxx                 */
/*                                    */
/* Created by Andrés Bórquez          */
/*                                    */
/**************************************/

/*** TASK 1 for Analysis Note ***/

// This program compares different spectrums of different GSIM card options:
//   - bad/Pb  <-> (1, 208)  <-> A
//   - jlab/D  <-> (1, 2)    <-> B
//   - jlab/Pb <-> (2, 208)  <-> C

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
TString outFolder = proFolder + "/out/CheckGSIMCards";
TString inFolder  = proFolder + "/out/filterSim/simrec";
//TString inputDataFile;
TString inputSimrecFileA = inFolder + "/bad/Pb/wout_simrecPb.root";
TString inputSimrecFileB = inFolder + "/jlab/D/wout_simrecD.root";
TString inputSimrecFileC = inFolder + "/jlab/Pb/wout_simrecPb.root";

// main option
TString observableChosen = "M"; // M: mass difference | Q: Q2 | N: nu | Z: Z | P: phiPQ | T: Pt2

// cuts
TCut cutDIS = "Q2 > 1 && W > 2";
TCut cutPi0 = "0.059 < mpi0 && mpi0 < 0.209"; // mikewood cut
TCut cutPipPim = "0.48 > mpippim || 0.51 < mpippim"; // mikewood cut
TCut cutAll = cutPi0 && cutDIS && cutPipPim;
TCut cutLiquid = "TargType == 1";
TCut cutSolid = "TargType == 2";

// names stuff (to be assigned by the options)
TString titleObservable;
TString titleAxis;
TString outPrefix;
TString toPlotObservable;
TString histProperties = "";
TString outputPlotName;

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
  /*
  TChain *tData = new TChain();
  tData->Add(inputDataFile + "/outdata");
  setAlias(tData);
  
  TH1F *dataHist;
  tData->Draw(toPlotObservable + ">>data" + histProperties, cutAll && cutTargType && cutZ, "goff");
  dataHist = (TH1F *)gROOT->FindObject("data");
  
  dataHist->SetTitleFont(22);
  dataHist->SetTitle(titleObservable + titleTarget + titleZ);
  dataHist->SetLineColor(kBlack);
  dataHist->SetLineWidth(3);
  dataHist->GetXaxis()->SetTitle(titleAxis);
  dataHist->GetYaxis()->SetTitle("Entries");
  */

  /*** Reconstructed ***/

  // input wout_simrec root files
  TChain *tSimrecA = new TChain();
  tSimrecA->Add(inputSimrecFileA + "/outdata");
  setAlias(tSimrecA);

  TChain *tSimrecB = new TChain();
  tSimrecB->Add(inputSimrecFileB + "/outdata");
  setAlias(tSimrecB);

  TChain *tSimrecC = new TChain();
  tSimrecC->Add(inputSimrecFileC + "/outdata");
  setAlias(tSimrecC);

  // extract histograms
  TH1F *simrecHistA;
  tSimrecA->Draw(toPlotObservable + ">>simrecA" + histProperties, cutAll && cutLiquid, "goff");
  simrecHistA = (TH1F *)gROOT->FindObject("simrecA");

  TH1F *simrecHistB;
  tSimrecB->Draw(toPlotObservable + ">>simrecB" + histProperties, cutAll && cutLiquid, "goff");
  simrecHistB = (TH1F *)gROOT->FindObject("simrecB");

  TH1F *simrecHistC;
  tSimrecC->Draw(toPlotObservable + ">>simrecC" + histProperties, cutAll && cutSolid, "goff");
  simrecHistC = (TH1F *)gROOT->FindObject("simrecC");

  /*** Drawing ***/
  
  simrecHistA->SetTitleFont(22);
  simrecHistA->SetTitle(titleObservable);
  simrecHistA->SetLineColor(kBlack);
  simrecHistA->SetLineWidth(3);
  simrecHistA->SetFillStyle(0);
  simrecHistA->GetXaxis()->SetTitle(titleAxis);
  simrecHistA->GetYaxis()->SetTitle("Entries");

  simrecHistB->SetFillStyle(0);
  simrecHistB->SetLineColor(kBlue);
  simrecHistB->SetLineWidth(3);

  simrecHistC->SetFillStyle(0);
  simrecHistC->SetLineColor(kRed);
  simrecHistC->SetLineWidth(3);

  TCanvas *c = new TCanvas("c", "c", 1200, 1000); 
  gStyle->SetOptStat(0);
  c->SetGrid();

  // my own normalization
  simrecHistA->Draw("HIST");
  c->Update();
  //scale hint1 to the pad coordinates
  Float_t rightmax = 1.1*simrecHistB->GetMaximum();
  Float_t scale = gPad->GetUymax()/rightmax;
  simrecHistB->Scale(scale);
  simrecHistB->Draw("SAME HIST");
  //draw an axis on the right side
  TGaxis *axis = new TGaxis(gPad->GetUxmax(), gPad->GetUymin(),
			    gPad->GetUxmax(), gPad->GetUymax(),
			    0, rightmax, 510, "+L");
  axis->SetLineColor(kBlue);
  axis->SetLabelColor(kBlue);
  axis->Draw();
  
  // simrecHistA->DrawNormalized("HIST");
  // simrecHistB->DrawNormalized("HIST SAME");
  // simrecHistC->DrawNormalized("HIST SAME");
  
  // legend
  TLegend *l = new TLegend(0.7, 0.9, 0.9, 1.0);
  // l->AddEntry(dataHist, "data", "l");
  l->AddEntry(simrecHistA, "(1, 208)", "l");
  l->AddEntry(simrecHistB, "(1, 2)", "l");
  // l->AddEntry(simrecHistC, "(2, 208)", "l");
  l->Draw();
  
  c->Print(outputPlotName); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckGSIMCards -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ho:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'o': observableChosen = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckGSIMCards -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "toPlotObservable=" << toPlotObservable << std::endl;
}

void printUsage() {
  std::cout << "CheckGSIMCards program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckGSIMCards -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckGSIMCards -o[option]" << std::endl;
  std::cout << "    sets observable to draw, which can be: " << std::endl;
  std::cout << "    M : omega invariant mass difference" << std::endl;
  std::cout << "    Q : Q2" << std::endl;
  std::cout << "    N : Nu" << std::endl;
  std::cout << "    Z : Z" << std::endl;
  std::cout << "    X : Xb" << std::endl;
  std::cout << "    P : PhiPQ" << std::endl;
  std::cout << "    T : Pt2" << std::endl;
  std::cout << "    W : W" << std::endl;
  std::cout << "    0 : P(pi0)" << std::endl;
  std::cout << "    1 : P(pi+)" << std::endl;
  std::cout << "    2 : P(pi-)" << std::endl;
  std::cout << "    3 : P(omega)" << std::endl;
}

void assignOptions() {
  // for observable
  if (observableChosen == "M") {
    toPlotObservable = "deltam";
    titleObservable = "IMD(#omega)";
    titleAxis = "IMD (GeV)";
    histProperties = "(160, 0., 1.6)";
  } else if (observableChosen == "Q") {
    toPlotObservable = "Q2";
    titleObservable = "Q^{2}(#omega)";
    titleAxis = "Q^{2}";
  } else if (observableChosen == "N") {
    toPlotObservable = "Nu";
    titleObservable = "#nu(#omega)";
    titleAxis = "#nu (GeV)";
    histProperties = "(200, 2.2, 4.2)";
  } else if (observableChosen == "Z") {
    toPlotObservable = "Z";
    titleObservable = "Z(#omega)";
    titleAxis = "Z";
    histProperties = "(220, 0.1, 1.2)";
  } else if (observableChosen == "X") {
    toPlotObservable = "Xb";
    titleObservable = "Xb(#omega)";
    titleAxis = "Xb";
    // histProperties = "";
  } else if (observableChosen == "P") {
    toPlotObservable = "PhiPQ";
    titleObservable = "#phi_{PQ}(#omega)";
    titleAxis = "#phi_{PQ}";
  } else if (observableChosen == "W") {
    toPlotObservable = "W";
    titleObservable = "W(#omega)";
    titleAxis = "W";
  } else if (observableChosen == "T") {
    toPlotObservable = "Pt2";
    titleObservable = "P_{T}^{2}(#omega)";
    titleAxis = "GeV^{2}";
    histProperties = "(150, 0., 1.5)";
  } else if (observableChosen == "0") {
    toPlotObservable = "Ppi0";
    titleObservable = "P(#pi0)";
    titleAxis = "P (GeV)";
    histProperties = "(150, 0., 3.)";
  } else if (observableChosen == "1") {
    toPlotObservable = "Ppip";
    titleObservable = "P(#pi+)";
    titleAxis = "P (GeV)";
    histProperties = "(150, 0., 3.)";
  } else if (observableChosen == "2") {
    toPlotObservable = "Ppim";
    titleObservable = "P(#pi-)";
    titleAxis = "P (GeV)";
    histProperties = "(150, 0., 3.)";
  } else if (observableChosen == "3") {
    toPlotObservable = "Pomega";
    titleObservable = "P(#omega)";
    titleAxis = "P (GeV)";
    histProperties = "(250, 0., 5.)";
  }
  // name
  outputPlotName = outFolder + "/gsim-cards-" + toPlotObservable + ".png";
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
  treeExtracted->SetAlias("cos_theta", "(fX[0]*fX[1] + fY[0]*fY[1] + fZ[0]*fZ[1])/(fE[0]*fE[1])");
  treeExtracted->SetAlias("m2pi0", "2*fE[0]*fE[1]*(1 - cos_theta)");
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
