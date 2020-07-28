/**************************************/
/* CheckStatusCuts_ratio.cxx          */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// --- CSC Saga - Final Chapter --- //
//
// OBJECTIVE:
// Fit the omega signal and obtain two numbers:
// 1) signal/bkg ratio
// 2) signal+bkg

#include "analysisConfig.h"

#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooGaussian.h"
#include "RooBreitWigner.h"
#include "RooChebychev.h"
#include "RooPolynomial.h"
#include "RooDataHist.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooExtendPdf.h"
#include "RooAbsReal.h"
#include "RooArgSet.h"

using namespace RooFit;

/*** Hardcoded ***/

// Winner parameters (meanConstraint, sigmaConstraint):
//  Q2  = (34, 1.5)
//  Nu  = (40, 1.5)
//  Z   = (24, 2)
//  Pt2 = (38, 1.5)
Double_t meanConstraint = 24e-3;
Double_t sigmaConstraint = 2e-3;
Double_t sigmaRangeDown = meanConstraint - 4e-3;
Double_t sigmaRangeUp = meanConstraint + 4e-3;

/*** Global variables ***/

TString outDir      = proDir + "/out/CheckStatusCuts";
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";

// main options
Int_t   dataFlag   = 0;
TString targetOption;
Int_t   binNumberZ = 0; // 0: off | [3-7]: on
Int_t   pid;

TCut cutTargType;
TCut cutZ = "";

// ""                 : sc0
// "SCStatusEl > 0"   : sc1
// "SCStatusEl == 33" : sc2

TCut statusCuts_default = "";
TCut statusCuts = "";
TCut statusCuts_electrons = "StatusEl > 0 && DCStatusEl > 0";
TCut statusCuts_pip       = "Status[2] > 0 && StatDC[2] > 0 && DCStatus[2] > 0";
TCut statusCuts_pim       = "Status[3] > 0 && StatDC[3] > 0 && DCStatus[3] > 0";
TCut statusCuts_gamma     = "Status[0] > 0 && Status[1] > 0";

TString titleZ = "";
TString sufixZBin = "";

TString titleDraw;

TString titleKinvar;
TString titleAxis;
TString histProperties;

TString outPrefix;
TString plotFile;

TString particleSufix;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

int main(int argc, char **argv) {
  
  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // dir structure, just in case
  system("mkdir -p " + outDir);
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
    
  /*** Fit ***/
  
  Int_t Nbins = 40; // bin x-width = 5 MeV
  Double_t fitRangeDown = 0.68; // preMean.getValV() - 5*preSigma.getValV() = 0.268
  Double_t fitRangeUp   = 0.88; // preMean.getValV() + 5*preSigma.getValV() = 0.468

  Double_t meanIGV = 0.78;
  Double_t meanRangeDown = meanIGV - 0.02;
  Double_t meanRangeUp   = meanIGV + 0.02; // 0.38

  Double_t sigmaIGV = 0.04;

  histProperties = Form("(%d, %.2f, %.2f)", Nbins, fitRangeDown, fitRangeUp);
  
  TH1F *theHist;
  treeExtracted->Draw("wSD_corr>>histo" + histProperties, cutDIS && cutPipPim && cutPi0 && cutTargType && statusCuts_default && statusCuts, "goff"); // && cutZ
  theHist = (TH1F *)gROOT->FindObject("histo");
  
  /*** RooFit stuff ***/

  RooRealVar x("IMD", "Reconstructed Mass [GeV]", fitRangeDown, fitRangeUp);

  // define signal parameters
  RooRealVar omegaMean("#mu(#omega)", "Mean of Gaussian", meanIGV, meanRangeDown, meanRangeUp);
  RooRealVar omegaSigma("#sigma(#omega)", "Width of Gaussian", sigmaIGV, sigmaRangeDown, sigmaRangeUp);

  // define signal functions, use them when corresponds
  RooGaussian omega("omega", "omega peak", x, omegaMean, omegaSigma);
  RooBreitWigner omegaBW("omega-bw", "omega-bw peak", x, omegaMean, omegaSigma);

  RooRealVar b1("b1", "linear term", 0.1, -10., 10.);
  
  // bkg list
  RooArgList lbkg(b1);
  RooChebychev bkg("bkg", "background", x, lbkg);

  // functions list
  RooArgList lfunctions(bkg);
  lfunctions.add(omega);
  
  // model(x) = bkg_yield*bkg(x) + sig_yield*sig(x)
  RooRealVar nsig("N_{#omega}", "omega yields", 0., theHist->GetEntries());
  RooRealVar nbkg("N_{b}", "bkg yields", 0., theHist->GetEntries());
  RooAddPdf model("model", "model", lfunctions, RooArgList(nbkg, nsig)); // RooArgList(omega, bkg)
  
  // define data
  RooDataHist data("data", "my data", x, theHist);

  
  // fit the normal way
  RooFitResult *r1 = model.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp), DataError(RooAbsData::SumW2));
  r1->Print("v");

  /*** Constraints! ***/
  
  RooGaussian conSigma("conSigma", "conSigma", omegaSigma, RooConst(meanConstraint), RooConst(sigmaConstraint)); // imposing bias
  RooProdPdf cmodel("cmodel", "model with constraint", RooArgSet(model, conSigma));

  // fit constraint model
  RooFitResult *r2 = cmodel.fitTo(data, Constrain(conSigma), Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  r2->Print("v");
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768);
  gStyle->SetOptStat(0);
  c->SetGrid();
  
  // define frame
  RooPlot *frame = x.frame(Title(titleKinvar + targetOption + titleDraw + titleZ), Bins(Nbins));
  data.plotOn(frame, Name("Data"), DataError(RooAbsData::SumW2));
  cmodel.plotOn(frame, Components("bkg"), LineStyle(kDashed), LineColor(kBlue));
  cmodel.plotOn(frame, Name("Model"), LineColor(kRed));
    
  // add params
  cmodel.paramOn(frame, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frame->getAttText()->SetTextSize(0.025);
  frame->getAttLine()->SetLineWidth(0);
  
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->SetTitle("Counts");
  frame->GetYaxis()->CenterTitle();

  frame->Draw();
  
  // draw lines
  drawVerticalLine(omegaMean.getValV() - 3*omegaSigma.getValV(), kGray+2, "dash");
  drawVerticalLine(omegaMean.getValV(), kBlack, "dash");
  drawVerticalLine(omegaMean.getValV() + 3*omegaSigma.getValV(), kGray+2, "dash");
  
  c->Print(plotFile); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckStatusCuts_ratio -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:z:s:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'z': binNumberZ = atoi(optarg); break;
    case 's': pid = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckStatusCuts_ratio -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing CheckStatusCuts_ratio program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  binNumberZ   = " << binNumberZ << std::endl;
  std::cout << "  pid   = " << pid << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "CheckStatusCuts_ratio program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_ratio -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_ratio -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_ratio -z[3-7]" << std::endl;
  std::cout << "    turns on binning in Z (off by default) and analyzes that specific bin" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_ratio -s[pid]" << std::endl;
  std::cout << "    turn on particular Status cuts for the respective pid (11, 22, 211, -211)" << std::endl;
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
  // for Z binning
  if (binNumberZ) {
    cutZ = Form("%f < wZ_corr && wZ_corr < %f", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    titleZ = Form(" in (%.02f < wZ_corr < %.02f)", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    sufixZBin = Form("-z%d", binNumberZ);
  }
  // for kinvar
  titleKinvar = "#Delta m(#pi^{+} #pi^{-} #pi^{0}) for ";
  titleAxis = "Reconstructed Mass [GeV]";
  // for pid/status
  if (pid == 11) {
    statusCuts = statusCuts_electrons;
  } else if (pid == 211) {
    statusCuts = statusCuts_pip;    
  } else if (pid == -211) {
    statusCuts = statusCuts_pim;
  } else if (pid == 22) {
    statusCuts = statusCuts_gamma;
  } else if (pid == 999) {
    statusCuts = statusCuts_electrons && statusCuts_pip && statusCuts_pim;
  }
  if (pid == 999) {
    particleSufix = "allstat";
  } else if (pid > 0 && pid < 999) {
    particleSufix = particleName(pid);
  } else {
    particleSufix = "nostat";
  }
  // output name
  plotFile = outDir + "/fit-" + particleSufix + "-" + targetOption + sufixZBin + ".png";
}
