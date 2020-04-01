/**************************************/
/* MakeRooFits.cxx                    */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// fits peak with a gaussian function and bkg with a 1st order polynomial
// - updated to "unified D"     : now we add all deuterium data, independent from which target
//                                to reduce the amount of error from the fits
// - updated to "toycombine.cxx": now we use the data from the ToyCombine filter
// - added kinematic dependence as an option

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TChain.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TString.h"
#include "TStyle.h"
#include "TLine.h"
#include "TPaveText.h"
#include "TLegend.h"

#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooDataHist.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooAbsReal.h"

using namespace RooFit;

/*** Global variables ***/

TString proFolder = "/home/borquez/omegaThesis";
TString inputFolder = proFolder + "/out/filterData";
TString outFolder = proFolder + "/out/MakeRooFits"; // gets modified

// edges obtained from 
Double_t edgesZ[6] = {0.5, 0.554, 0.611, 0.676, 0.760, 0.9}; // updated
Double_t edgesQ2[6] = {1., 1.181, 1.364, 1.598, 1.960, 3.970};
Double_t edgesNu[6] = {2.2, 3.191, 3.504, 3.744, 3.964, 4.2};
Double_t edgesPt2[6] = {0.0, 0.040, 0.090, 0.159, 0.273, 1.5}; // updated

// target options
TString targetOption;
TString inputFile1 = "";
TString inputFile2 = "";
TString inputFile3 = "";
TCut    cutTargType;

// kinematic variable options
Int_t flagZ = 0;
Int_t flagQ2 = 0;
Int_t flagNu = 0;
Int_t flagPt2 = 0;

TString obsTitle;
TString obsName;
TString obsSufix;
Int_t   binNumber;
TCut    obsCut;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

void drawHorizontalLine(Double_t y);
void drawBlackHorizontalLine(Double_t y);
void drawVerticalLineBlack(Double_t x);
void drawVerticalLineGrayest(Double_t x);
void drawVerticalLineGrayer(Double_t x);
void drawVerticalLineGray(Double_t x);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // cuts
  TCut cutDIS = "Q2 > 1 && W > 2 && Yb < 0.85";
  TCut cutPi0 = "0.059 < pi0M && pi0M < 0.209";
  TCut cutPipPim = "0.48 > pippimM || 0.51 < pippimM";
  TCut cutAll = cutDIS && cutPipPim && cutPi0 && cutTargType && obsCut;

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  /*** STAGE 1: Preliminary fit ***/

  // x-bin width = 5 MeV
  Int_t preNbins = 52;
  Double_t prePlotRangeDown = 0.24; // aprox. 6 omega sigma
  Double_t prePlotRangeUp = 0.50; // aprox. 6 omega sigma

  Double_t preSigmaIGV = 2.5e-2; // initial guess value
  Double_t preSigmaRangeDown = 1.5e-2; // 1.5
  Double_t preSigmaRangeUp = 3.5e-2; // 4

  Double_t preMeanIGV = 0.37; // initial guess value
  Double_t preMeanRangeDown = 0.36;
  Double_t preMeanRangeUp = 0.39; // 0.38

  Double_t preFitRangeDown = 0.34;
  Double_t preFitRangeUp = 0.42;
  
  TH1F *fitPreHist; 
  treeExtracted->Draw(Form("wD>>data4fit(%d, %f, %f)", preNbins, prePlotRangeDown, prePlotRangeUp), cutAll, "goff");
  fitPreHist = (TH1F *)gROOT->FindObject("data4fit");

  RooRealVar preX("preX", "preX", prePlotRangeDown, prePlotRangeUp);

  RooRealVar preMean("preMean", "Mean of Gaussian", preMeanIGV, preMeanRangeDown, preMeanRangeUp);
  RooRealVar preSigma("preSigma", "Width of Gaussian", preSigmaIGV, preSigmaRangeDown, preSigmaRangeUp);
  RooGaussian pre("pre", "pre peak", preX, preMean, preSigma);

  RooDataHist preData("preData", "my data", preX, fitPreHist);
  pre.fitTo(preData, Range(preFitRangeDown, preFitRangeUp), Save());

  RooPlot *preFrame = preX.frame(Title("preliminary fit"), Bins(preNbins));
  preData.plotOn(preFrame, DataError(RooAbsData::SumW2), Name("preData"));
  pre.plotOn(preFrame, Name("preModel"), LineColor(kMagenta));
  pre.paramOn(preFrame, Layout(0.6, 0.9, 0.9)); // x1, x2, y2
  
  Double_t preChi2 = preFrame->chiSquare("preModel", "preData");

  TCanvas *c0 = new TCanvas("c0", "c0", 1366, 768);
  preFrame->Draw();
  c0->Print(outFolder + "/roofit0-" + targetOption + obsSufix + ".png"); // output file
  
  std::cout << "STAGE 1 COMPLETED." << std::endl;
  std::cout << "preMean  = " << preMean.getValV() << std::endl;
  std::cout << "preSigma = " << preSigma.getValV() << std::endl;
  std::cout << "preChi2  = " << preChi2 << std::endl;
  
  /*** STAGE 2: Real fit ***/
  
  // bin x-width = 5 MeV
  Int_t Nbins = 90; // 90
  Double_t plotRangeDown = 0.15; // 0.15
  Double_t plotRangeUp = 0.6; // 0.6

  Double_t fitRangeDown = preMean.getValV() - 5*preSigma.getValV();
  Double_t fitRangeUp = preMean.getValV() + 5*preSigma.getValV();
  
  Double_t meanRangeDown = 0.36;
  Double_t meanRangeUp = 0.39; // 0.38
  
  Double_t sigmaRangeDown = 1.5e-2; // 1.5
  Double_t sigmaRangeUp = 2e-2; // 3.5

  TH1F *dataHist;
  treeExtracted->Draw(Form("wD>>data(%d, %f, %f)", Nbins, plotRangeDown, plotRangeUp), cutAll, "goff");
  dataHist = (TH1F *)gROOT->FindObject("data");

  /*** RooFit stuff ***/

  RooRealVar x("IMD", "IMD (GeV)", plotRangeDown, plotRangeUp);

  RooRealVar omegaMean("omegaMean", "Mean of Gaussian", preMean.getValV(), meanRangeDown, meanRangeUp);
  RooRealVar omegaSigma("omegaSigma", "Width of Gaussian", preSigma.getValV(), sigmaRangeDown, sigmaRangeUp);
  RooGaussian omega("omega", "omega peak", x, omegaMean, omegaSigma);  

  RooRealVar b1("b1", "linear term", 0.1, -10, 10);
  RooChebychev bkg("bkg", "background", x, RooArgList(b1));
  
  RooRealVar omegaYields("omegaYields", "omega yields", 0., dataHist->GetEntries());
  RooRealVar bkgYields("bkgYields", "bkg yields", 0., dataHist->GetEntries());

  // model(x) = sig_yield*sig(x) + bkg_yield*bkg(x)
  RooAddPdf model("model", "model", RooArgList(omega, bkg), RooArgList(omegaYields, bkgYields));
  
  // data
  RooDataHist data("data", "my data", x, dataHist);

  // fit
  model.fitTo(data, Extended(), Save(), Range(fitRangeDown, fitRangeUp));

  // draw hist and function to frame
  RooPlot *frame = x.frame(Title(""), Bins(Nbins));
  data.plotOn(frame, DataError(RooAbsData::SumW2), Name("Data"));
  model.plotOn(frame, Name("Model"), LineColor(kRed));
  
  // obtain chi2
  Double_t chi2;
  chi2 = frame->chiSquare("Model", "Data");

  /*** Generating histograms from functions ***/

  TH1F *bkgHist = (TH1F *)bkg.createHistogram("bkgHist", x, Binning(Nbins, plotRangeDown, plotRangeUp), Extended());
  bkgHist->Scale(bkgYields.getValV());
  
  TH1F *omegaHist = (TH1F *)omega.createHistogram("omegaHist", x, Binning(Nbins, plotRangeDown, plotRangeUp), Extended());
  omegaHist->Scale(omegaYields.getValV());
  
  /*** Drawing **/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768);
  model.plotOn(frame, Components("bkg"), LineStyle(kDashed), LineColor(kBlue), Name("Background"));
  
  frame->SetTitle(targetOption + " in" + obsTitle);
  frame->GetXaxis()->SetNdivisions(605, kFALSE); // important!

  // params
  model.paramOn(frame, Layout(0.1, 0.35, 0.9)); // x1, x2, delta-y
  frame->getAttText()->SetTextSize(0.03);
  
  frame->Draw();

  // chi2
  TPaveText *textBlock = new TPaveText(0.1, 0.9, 0.35, 1.0, "NDC TL"); // x1, y1, x2, y2
  textBlock->AddText(Form("#chi^{2}/ndf = %.3f", chi2));
  textBlock->SetFillColor(kWhite);
  textBlock->SetShadowColor(kWhite);
  textBlock->SetTextColor(kBlack);
  textBlock->Draw();

  c->Print(outFolder + "/roofit1-" + targetOption + obsSufix + ".png"); // output file
  
  /*** Method 2: integrate direct histogram from peak fit function ***/

  Double_t omegaMethod2Error;
  Double_t omegaMethod2 = omegaHist->IntegralAndError(1, Nbins, omegaMethod2Error, "");
  
  /*** Method 3: subtract bkgYields to data counts ***/
  
  Double_t omegaMethod3 = dataHist->Integral(1, Nbins) - bkgYields.getValV();
  
  /*** Method 4: subtract bin-by-bin bkg histogram to data, then integrate remaining peak histogram ***/
  
  TCanvas *c2 = new TCanvas("c2", "c2", 1366, 768);
  gStyle->SetOptStat(0);
  
  TH1F *peakHist = new TH1F("peakHist", "peakHist", Nbins, plotRangeDown, plotRangeUp);
  peakHist->Add(dataHist, bkgHist, 1, -1); // the subtraction

  Int_t omegaSum = 0;
  Double_t sigmaxRangeDown = omegaMean.getValV() - 3*omegaSigma.getValV();
  Double_t sigmaxRangeUp = omegaMean.getValV() + 3*omegaSigma.getValV();  

  for (Int_t pp = 1; pp <= Nbins; pp++) {
    if (peakHist->GetBinContent(pp) < 0) peakHist->SetBinContent(pp, 0);
    std::cout << "Bin " << pp << " : " << peakHist->GetBinContent(pp) << std::endl;
    if (peakHist->GetBinLowEdge(pp) > sigmaxRangeDown && (peakHist->GetBinLowEdge(pp) + 0.01) < sigmaxRangeUp) {
      omegaSum += peakHist->GetBinContent(pp);
      std::cout << "...is inside!" << std::endl;
    }
  }
  peakHist->Draw("HIST");

  drawVerticalLineGrayest(omegaMean.getValV() - 3*omegaSigma.getValV());
  drawVerticalLineBlack(omegaMean.getValV());
  drawVerticalLineGrayest(omegaMean.getValV() + 3*omegaSigma.getValV());

  // Double_t omegaNumber = peakHist->Integral(omegaMean.getValV() - 3*omegaSigma.getValV(), omegaMean.getValV() + 3*omegaSigma.getValV());

  // title (?)
  TPaveText *textBlock2 = new TPaveText(0.15, 0.75, 0.35, 0.85, "BR ARC NDC");
  textBlock2->AddText(Form("sum = %d", omegaSum));
  textBlock2->SetTextFont(20); // bold times new roman
  textBlock2->SetTextColor(kBlack);
  textBlock2->Draw();
  c2->Print(outFolder + "/roofit2-" + targetOption + obsSufix + ".png"); // output file

  /*** Saving fit content ***/
  
  TString outputTextFile = outFolder + "/roofit-" + targetOption + obsSufix + ".dat"; // output file
  std::cout << "Writing " << outputTextFile << " ..." << std::endl;
  std::ofstream outFinalFile(outputTextFile, std::ios::out);
  // line 1: b1
  outFinalFile << b1.getValV() << "\t" << b1.getError() << std::endl;
  // line 2: bkgYields
  outFinalFile << bkgYields.getValV() << "\t\t" << bkgYields.getError() << std::endl;
  // line 3: omegaMean
  outFinalFile << omegaMean.getValV() << "\t" << omegaMean.getError() << std::endl;
  // line 4: omegaSigma
  outFinalFile << omegaSigma.getValV() << "\t" << omegaSigma.getError() << std::endl;
  // line 5: omegaYields (directly from parameter) (METHOD 1)
  outFinalFile << omegaYields.getValV() << "\t\t" << omegaYields.getError() << std::endl;
  // line 6: chi2
  outFinalFile << chi2 << "\t\t" << "0" << std::endl;
  
  outFinalFile.close();
  std::cout << "File " << outputTextFile << " has been created!" << std::endl;
  std::cout << "Chi2: " << chi2 << std::endl;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeRooFits -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:z:q:n:p:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'z': flagZ = 1; binNumber = atoi(optarg); break;
    case 'q': flagQ2 = 1; binNumber = atoi(optarg); break;
    case 'n': flagNu = 1; binNumber = atoi(optarg); break;
    case 'p': flagPt2 = 1; binNumber = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeRooFits -h to print help." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "targetOption=" << targetOption << std::endl;
  std::cout << "obsName=" << obsName << std::endl;
  std::cout << "binNumber=" << binNumber << std::endl;
}

void printUsage() {
  std::cout << "MakeRooFits program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -[kinvar][number]" << std::endl;
  std::cout << "    analyzes respective kinematic variable bin" << std::endl;
  std::cout << "    z[3-7] : analyzes specific Z bin" << std::endl;
  std::cout << "    q[1-5] : analyzes specific Q2 bin" << std::endl;
  std::cout << "    n[1-5] : analyzes specific Nu bin" << std::endl;
  std::cout << "    p[1-5] : analyzes specific Pt2 bin" << std::endl;
}

void assignOptions() {
  // for targets, unified D
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
  // for kinvar
  Double_t lowEdge, highEdge;
  if (flagZ) {
    lowEdge = edgesZ[binNumber-3];
    highEdge = edgesZ[binNumber+1-3];
    obsSufix = Form("-z%d", binNumber);
    obsName = "Z";
    outFolder = outFolder + "/Z";
  } else if (flagQ2) {
    lowEdge = edgesQ2[binNumber-1];
    highEdge = edgesQ2[binNumber+1-1];
    obsSufix = Form("-q%d", binNumber);
    obsName = "Q2";
    outFolder = outFolder + "/Q2";
  } else if (flagNu) {
    lowEdge = edgesNu[binNumber-1];
    highEdge = edgesNu[binNumber+1-1];
    obsSufix = Form("-n%d", binNumber);
    obsName = "Nu";
    outFolder = outFolder + "/Nu";
  } else if (flagPt2) {
    lowEdge = edgesPt2[binNumber-1];
    highEdge = edgesPt2[binNumber+1-1];
    obsSufix = Form("-p%d", binNumber);
    obsName = "Pt2";
    outFolder = outFolder + "/Pt2";
  }
  obsCut = Form("%f < ", lowEdge) + obsName + " && " + obsName + Form(" < %f", highEdge);
  obsTitle = Form(" (%.02f < ", lowEdge) + obsName + Form(" < %.02f)", highEdge);
}

void drawHorizontalLine(Double_t y) {
  Double_t u;
  gPad->Update(); // necessary
  u = (y - gPad->GetY1())/(gPad->GetY2() - gPad->GetY1());
  // u = (y - y1)/(y2 - y1);
  TLine *liney = new TLine(0.1, u, 0.9, u);
  liney->SetLineWidth(3);
  liney->SetLineColor(kRed);
  liney->SetLineStyle(2);
  liney->SetNDC(kTRUE);
  liney->Draw();
}

void drawBlackHorizontalLine(Double_t y) {
  Double_t u;
  gPad->Update(); // necessary
  u = (y - gPad->GetY1())/(gPad->GetY2() - gPad->GetY1());
  // u = (y - y1)/(y2 - y1);
  TLine *liney = new TLine(0.1, u, 0.9, u);
  liney->SetLineWidth(3);
  liney->SetLineColor(kBlack);
  liney->SetLineStyle(2);
  liney->SetNDC(kTRUE);
  liney->Draw();
}

void drawVerticalLineBlack(Double_t x) {
  Double_t u;
  gPad->Update(); // necessary
  u = (x - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  // u = (x - x1)/(x2 - x1);
  TLine *linex = new TLine(u, 0.1, u, 0.9);
  linex->SetLineWidth(3);
  linex->SetLineColor(kBlack);
  linex->SetLineStyle(2);
  linex->SetNDC(kTRUE);
  linex->Draw();
}

void drawVerticalLineGrayest(Double_t x) {
  Double_t u;
  gPad->Update(); // necessary
  u = (x - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  // u = (x - x1)/(x2 - x1);
  TLine *linex = new TLine(u, 0.1, u, 0.9);
  linex->SetLineWidth(3);
  linex->SetLineColor(kGray+3);
  linex->SetLineStyle(2);
  linex->SetNDC(kTRUE);
  linex->Draw();
}

void drawVerticalLineGrayer(Double_t x) {
  Double_t u;
  gPad->Update(); // necessary
  u = (x - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  // u = (x - x1)/(x2 - x1);
  TLine *linex = new TLine(u, 0.1, u, 0.9);
  linex->SetLineWidth(3);
  linex->SetLineColor(kGray+2);
  linex->SetLineStyle(2);
  linex->SetNDC(kTRUE);
  linex->Draw();
}

void drawVerticalLineGray(Double_t x) {
  Double_t u;
  gPad->Update(); // necessary
  u = (x - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  // u = (x - x1)/(x2 - x1);
  TLine *linex = new TLine(u, 0.1, u, 0.9);
  linex->SetLineWidth(3);
  linex->SetLineColor(kGray+1);
  linex->SetLineStyle(2);
  linex->SetNDC(kTRUE);
  linex->Draw();
}
