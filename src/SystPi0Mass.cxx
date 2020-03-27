/**************************************/
/* SystPi0Mass.cxx                    */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

/*** TASK 4 for Analysis Note ***/

// This program corresponds to systematics studies on Pi0 mass
// 1. plots IM(pi0) for data
// 2. fits IM(pi0) peak
// 3. defines three propto. sigma cuts {3sigma, 4sigma, 5sigma}
// 4. does nbs-MR(kinvar) from the previous cuts

#include <iostream>
#include <fstream>

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
#include "TPaveText.h"

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

TString proFolder   = "/home/borquez/omegaThesis";
TString inputFolder = proFolder + "/out/filterData";  // default for data
TString outFolder   = proFolder + "/out/SystPi0Mass";
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";

// results obtained previously by this same program
Double_t obtMean  = 0.131;
Double_t obtSigma = 0.024;
Double_t pi0LowEdge;
Double_t pi0HighEdge;
TString  pi0NSigmaSufix;

// main options
Int_t   plotFlag = 0;
Int_t   fitFlag  = 0;
TString targetOption;
Int_t   doMRFlag = 0;
TString kinvarOption;
Int_t   pi0Nsigma;
Int_t   wNsigma;

// cuts
TCut cutDIS = "Q2 > 1 && W > 2 && Yb < 0.85";
TCut cutPi0 = ""; // to be defined
TCut cutPipPim = "0.48 > pippimM || 0.51 < pippimM";
TCut cutAll;
TCut cutKinVar;
TCut cutTargType;
TCut cutOmega;

// kinvar options
Int_t    kinvarNbins = 5;
Double_t kinvarValue[6];
Double_t edgesZ[6] = {0.5, 0.557, 0.617, 0.689, 0.784, 1.};
Double_t edgesQ2[6] = {1., 1.181, 1.364, 1.598, 1.960, 3.970};
Double_t edgesNu[6] = {2.2, 3.191, 3.504, 3.744, 3.964, 4.2};
Double_t edgesPt2[6] = {0., 0.04, 0.09, 0.16, 0.273, 1.5};
TString  kinvarSufix;
TString  kinvarMRSufix;
Int_t    kinvarConstant = 1; // default for (Q2, Nu, Pt2)

// MR-related
Double_t particleNumber[4][5];
Double_t particleError[4][5];

// names stuff
TString outPrefix;
TString outputPlotName;
TString outputTextName;

// other
Int_t canvasWidth = 1366;
Int_t canvasHeight = 768;

// omega fit
TString  wNSigmaSufix;
Double_t wLowEdge[5];
Double_t wHighEdge[5];

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

void drawVerticalLine(Double_t x);
void fitOmegaPeak();
void integrateData(TString targetOption2);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // define canvas
  TCanvas *c = new TCanvas("c", "c", canvasWidth, canvasHeight); 
  c->SetGrid();
  
  if (plotFlag) {

    TChain *treeExtracted = new TChain();
    treeExtracted->Add(inputFile1 + "/mix");
    treeExtracted->Add(inputFile2 + "/mix");
    treeExtracted->Add(inputFile3 + "/mix");
    
    TH1F *plotHist;
    treeExtracted->Draw("pi0M>>" + targetOption + "-data(500, 0., 1.)", cutDIS && cutTargType, "goff");
    plotHist = (TH1F *)gROOT->FindObject(targetOption + "-data");
    
    plotHist->SetTitleFont(22);
    plotHist->SetTitle("IM(#pi0) for " + targetOption + " Data");
    plotHist->SetLineColor(kBlack);
    plotHist->SetLineWidth(3);
    plotHist->GetXaxis()->SetTitle("IM(#pi0) (GeV)");
    plotHist->GetYaxis()->SetTitle("Counts");
    
    plotHist->Draw("E");

  } else if (fitFlag) {

    TChain *treeExtracted = new TChain();
    treeExtracted->Add(inputFile1 + "/mix");
    treeExtracted->Add(inputFile2 + "/mix");
    treeExtracted->Add(inputFile3 + "/mix");
    
    // x-bin width = 2 MeV
    Int_t    Nbins = 500;
    Double_t plotRangeDown = 0.0;
    Double_t plotRangeUp = 1.;

    Double_t sigmaIGV = 2.5e-2; // from MW fit
    Double_t sigmaRangeDown = 2.35e-2;
    Double_t sigmaRangeUp = 2.65e-2;

    Double_t meanIGV = 0.134; // from MW fit
    Double_t meanRangeDown = 0.130;
    Double_t meanRangeUp = 0.140;

    Double_t fitRangeDown = 0.110;
    Double_t fitRangeUp = 0.154;
  
    TH1F *fitHist; 
    treeExtracted->Draw(Form("pi0M>>" + targetOption + "-data(%d, %f, %f)", Nbins, plotRangeDown, plotRangeUp), cutDIS && cutTargType, "goff");
    fitHist = (TH1F *)gROOT->FindObject(targetOption + "-data");

    RooRealVar x("x", "IM(#pi0) (GeV)", plotRangeDown, plotRangeUp);

    RooRealVar mean("#mu", "Mean of Gaussian", meanIGV, meanRangeDown, meanRangeUp);
    RooRealVar sigma("#sigma", "Width of Gaussian", sigmaIGV, sigmaRangeDown, sigmaRangeUp);
    RooGaussian pi0("pi0", "pi0 peak", x, mean, sigma);

    RooDataHist data("data", "data", x, fitHist);
    pi0.fitTo(data, Range(fitRangeDown, fitRangeUp), Save());

    RooPlot *theFrame = x.frame(Title("IM(#pi0) for " + targetOption + " Data"), Bins(Nbins));
    // data.plotOn(theFrame, DataError(RooAbsData::SumW2), Name("data"));
    data.plotOn(theFrame, Name("data"));
    pi0.plotOn(theFrame, Name("model"), LineColor(kRed));
    pi0.paramOn(theFrame, Layout(0.6, 0.9, 0.9)); // x1, x2, delta-y
  
    theFrame->Draw();

    // draw chi2
    Double_t chi2 = theFrame->chiSquare("model", "data");
    TPaveText *textBlock = new TPaveText(0.7, 0.9, 0.9, 1.0, "NDC TL"); // x1, y1, x2, y2
    textBlock->AddText(Form("#chi^{2}/ndf = %.3f", chi2));
    textBlock->SetFillColor(kWhite);
    textBlock->SetShadowColor(kWhite);
    textBlock->SetTextColor(kBlack);
    textBlock->Draw();

    // draw lines
    drawVerticalLine(mean.getValV());
    drawVerticalLine(mean.getValV() - 3*sigma.getValV());
    drawVerticalLine(mean.getValV() + 3*sigma.getValV());
  
    std::cout << std::endl;
    std::cout << "FIT COMPLETED." << std::endl;
    std::cout << "mean  = " << mean.getValV() << std::endl;
    std::cout << "sigma = " << sigma.getValV() << std::endl;
    std::cout << "chi2  = " << chi2 << std::endl;    
    std::cout << std::endl;
    
  } else if (doMRFlag) {

    gStyle->SetOptStat(0);

    // define cuts, the most important part of this program
    pi0LowEdge = obtMean - pi0Nsigma*obtSigma;
    pi0HighEdge = obtMean + pi0Nsigma*obtSigma;
    cutPi0 = Form("%f < pi0M && pi0M < %f", pi0LowEdge, pi0HighEdge);
    
    fitOmegaPeak();
    
    integrateData("D");
    integrateData("C");
    integrateData("Fe");
    integrateData("Pb");

    // go back to main canvas
    c->cd();
    
    // creating and filling histograms
    TH1F *numberDeutHist = new TH1F("numberDeutHist", "", kinvarNbins, 0.5, 1.);
    TH1F *numberCarbonHist = new TH1F("numberCarbonHist", "", kinvarNbins, 0.5, 1.);
    TH1F *numberIronHist = new TH1F("numberIronHist", "", kinvarNbins, 0.5, 1.);
    TH1F *numberLeadHist = new TH1F("numberLeadHist", "", kinvarNbins, 0.5, 1.);
    
    // for each bin in kinvar
    for (Int_t cc = 0; cc < kinvarNbins; cc++) {
      numberDeutHist->SetBinContent(cc + 1, particleNumber[0][cc]);
      numberDeutHist->SetBinError(cc + 1, particleError[0][cc]);
    
      numberCarbonHist->SetBinContent(cc + 1, particleNumber[1][cc]);
      numberCarbonHist->SetBinError(cc + 1, particleError[1][cc]);
    
      numberIronHist->SetBinContent(cc + 1, particleNumber[2][cc]);
      numberIronHist->SetBinError(cc + 1, particleError[2][cc]);
        
      numberLeadHist->SetBinContent(cc + 1, particleNumber[3][cc]);
      numberLeadHist->SetBinError(cc + 1, particleError[3][cc]);
    }
  
    TH1F *CarbonMR = new TH1F("CarbonMR", "", kinvarNbins, 0.5, 1.);
    CarbonMR->SetTitle("#omega NBS MR(" + kinvarOption + ")");
    CarbonMR->GetXaxis()->SetTitle(kinvarOption);
    CarbonMR->GetXaxis()->SetNdivisions(200 + kinvarNbins, kFALSE);
    CarbonMR->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,Form("%.02f", kinvarValue[0]));
    CarbonMR->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,Form("%.02f", kinvarValue[1]));
    CarbonMR->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,Form("%.02f", kinvarValue[2]));
    CarbonMR->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,Form("%.02f", kinvarValue[3]));
    CarbonMR->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,Form("%.02f", kinvarValue[4]));
    CarbonMR->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,Form("%.02f", kinvarValue[5]));
    CarbonMR->GetYaxis()->SetTitle("MR");

    CarbonMR->SetMarkerColor(kRed);
    CarbonMR->SetLineColor(kRed);
    CarbonMR->SetLineWidth(3);
    CarbonMR->SetMarkerStyle(21);
    CarbonMR->Divide(numberCarbonHist, numberDeutHist);
    CarbonMR->Scale(4.6194); // electron normalization, uniD
  
    CarbonMR->SetAxisRange(0., 1.2, "Y"); // range
    CarbonMR->Draw("E");  
  
    TH1F *IronMR = new TH1F("IronMR", "", kinvarNbins, 0.5, 1.);
    IronMR->SetMarkerColor(kBlue);
    IronMR->SetLineColor(kBlue);
    IronMR->SetLineWidth(3);
    IronMR->SetMarkerStyle(21);
    IronMR->Divide(numberIronHist, numberDeutHist);
    IronMR->Scale(2.3966); // electron normalization, uniD
  
    IronMR->Draw("E SAME");

    TH1F *LeadMR = new TH1F("LeadMR", "", kinvarNbins, 0.5, 1.);
    LeadMR->SetMarkerColor(kBlack);
    LeadMR->SetLineColor(kBlack);
    LeadMR->SetLineWidth(3);
    LeadMR->SetMarkerStyle(21);
    LeadMR->Divide(numberLeadHist, numberDeutHist);
    LeadMR->Scale(6.1780); // electron normalization, uniD
  
    LeadMR->Draw("E SAME");
    
    // legend
    TLegend *legend = new TLegend(0.9, 0.75, 1., 0.9);
    legend->AddEntry(CarbonMR, "Carbon", "pl");
    legend->AddEntry(IronMR, "Iron", "pl");
    legend->AddEntry(LeadMR, "Lead", "pl");
    legend->Draw();

    /*** Save results ***/
  
    std::ofstream outFinalFile(outputTextName, std::ios::out); // output file
    // first line
    outFinalFile << CarbonMR->GetBinContent(1) << "\t" << CarbonMR->GetBinError(1) << "\t"
		 << IronMR->GetBinContent(1) << "\t" << IronMR->GetBinError(1) << "\t"
		 << LeadMR->GetBinContent(1) << "\t" << LeadMR->GetBinError(1)  << std::endl;
    // second line
    outFinalFile << CarbonMR->GetBinContent(2) << "\t" << CarbonMR->GetBinError(2) << "\t"
		 << IronMR->GetBinContent(2) << "\t" << IronMR->GetBinError(2) << "\t"
		 << LeadMR->GetBinContent(2) << "\t" << LeadMR->GetBinError(2) << std::endl;
    // third line
    outFinalFile << CarbonMR->GetBinContent(3) << "\t" << CarbonMR->GetBinError(3) << "\t"
		 << IronMR->GetBinContent(3) << "\t" << IronMR->GetBinError(3) << "\t"
		 << LeadMR->GetBinContent(3) << "\t" << LeadMR->GetBinError(3) << std::endl;
    // fourth line
    outFinalFile << CarbonMR->GetBinContent(4) << "\t" << CarbonMR->GetBinError(4) << "\t"
		 << IronMR->GetBinContent(4) << "\t" << IronMR->GetBinError(4) << "\t"
		 << LeadMR->GetBinContent(4) << "\t" << LeadMR->GetBinError(4) << std::endl;
    // fifth line
    outFinalFile << CarbonMR->GetBinContent(5) << "\t" << CarbonMR->GetBinError(5) << "\t"
		 << IronMR->GetBinContent(5) << "\t" << IronMR->GetBinError(5) << "\t"
		 << LeadMR->GetBinContent(5) << "\t" << LeadMR->GetBinError(5) << std::endl;
  
    outFinalFile.close();
    std::cout << "File " << outputTextName << " created!" << std::endl;
  }

  // save plot
  c->Print(outputPlotName); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./SystPi0Mass -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:pfmk:i:w:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'p': plotFlag = 1; break;
    case 'f': fitFlag = 1; break;
    case 'm': doMRFlag = 1; break;
    case 'k': kinvarOption = optarg; break;
    case 'i': pi0Nsigma = atoi(optarg); break;
    case 'w': wNsigma = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./SystPi0Mass -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << std::endl;
  std::cout << "Executing SystPi0Mass program. Parameters chosen are:" << std::endl;
  std::cout << "  plotFlag     = " << plotFlag << std::endl;
  if (plotFlag) std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  fitFlag      = " << fitFlag << std::endl;
  if (fitFlag) std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  doMRFlag     = " << doMRFlag << std::endl;
  if (doMRFlag) {
    std::cout << "  kinvarOption = " << kinvarOption << std::endl;
    std::cout << "  pi0Nsigma    = " << pi0Nsigma << std::endl;
    std::cout << "  wNsigma      = " << wNsigma << std::endl;
  }
  std::cout << std::endl;
}

void printUsage() {
  std::cout << std::endl;
  std::cout << "SystPi0Mass program. Usage is:" << std::endl;
  std::cout << "./SystPi0Mass -[options] -[more options]" << std::endl;
  std::cout << "  h         : prints help and exit program" << std::endl;
  std::cout << "  t[target] : selects target: D | C | Fe | Pb" << std::endl;
  std::cout << "  p         : plots mpi0 spectrum" << std::endl;
  std::cout << "  f         : fits mpi0 peak" << std::endl;
  std::cout << "  m         : does nbs-MR" << std::endl;
  std::cout << "  k[kinvar] : selects kinvar" << std::endl;
  std::cout << "  i[3,4,5]  :  with n*sigma cut around pi0 peak" << std::endl;
  std::cout << "  w[3,4,5]  :  with n*sigma cut around omega peak" << std::endl;  
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
    kinvarConstant = 3;
    kinvarSufix = "-z";
    kinvarMRSufix = "-Z";
    for (Int_t z = 0; z <= kinvarNbins; z++) kinvarValue[z] = edgesZ[z];
  } else if (kinvarOption == "Q2") {
    kinvarSufix = "-q";
    kinvarMRSufix = "-Q2";
    for (Int_t q = 0; q <= kinvarNbins; q++) kinvarValue[q] = edgesQ2[q];
  } else if (kinvarOption == "Nu") {
    kinvarSufix = "-n";
    kinvarMRSufix = "-Nu";
    for (Int_t n = 0; n <= kinvarNbins; n++) kinvarValue[n] = edgesNu[n];
  } else if (kinvarOption == "Pt2") {
    kinvarSufix = "-p";
    kinvarMRSufix = "-Pt2";
    for (Int_t p = 0; p <= kinvarNbins; p++) kinvarValue[p] = edgesPt2[p];
  }
  // more sufix
  wNSigmaSufix = Form("-%dw", wNsigma);
  pi0NSigmaSufix = Form("-%dpi0", pi0Nsigma);
  // for process names
  if (plotFlag) {
    outPrefix = "plot-mpi0-" + targetOption;
  } else if (fitFlag) {
    outPrefix = "fit-mpi0-" + targetOption;
  } else if (doMRFlag) {
    outPrefix = "nbs-MR" + kinvarMRSufix;
    outputTextName = outFolder + "/" + outPrefix + wNSigmaSufix + pi0NSigmaSufix + ".dat";
    canvasWidth = 1200;
    canvasHeight = 1000;
  }
  // output name
  outputPlotName = outFolder + "/" + outPrefix + wNSigmaSufix + pi0NSigmaSufix + ".png";
}

void drawVerticalLine(Double_t x) {
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

void fitOmegaPeak() {
  
  // assign options
  cutTargType = "TargType == 1";
  inputFile1 = inputFolder + "/C/comb_C-thickD2.root";
  inputFile2 = inputFolder + "/Fe/comb_Fe-thickD2.root";
  inputFile3 = inputFolder + "/Pb/comb_Pb-thinD2.root";
  
  // extract data
  TChain *treeExtracted3 = new TChain();
  treeExtracted3->Add(inputFile1 + "/mix");
  treeExtracted3->Add(inputFile2 + "/mix");
  treeExtracted3->Add(inputFile3 + "/mix");
    
  // x-bin width = 2 MeV
  Int_t    wNbins = 130;
  Double_t wPlotRangeDown = 0.24; // aprox. 6 sigma
  Double_t wPlotRangeUp = 0.50; // aprox. 6 sigma
  
  Double_t wSigmaIGV = 2.2e-2;
  Double_t wSigmaRangeDown = 1.8e-2;
  Double_t wSigmaRangeUp = 2.6e-2;
  
  Double_t wMeanIGV = 0.37;
  Double_t wMeanRangeDown = 0.36;
  Double_t wMeanRangeUp = 0.38;
  
  Double_t wFitRangeDown = 0.30;
  Double_t wFitRangeUp = 0.44;

  for (Int_t index2 = 0; index2 < kinvarNbins; index2++) {

    // define kinvar cut
    cutKinVar = Form("%f < ", kinvarValue[index2]) + kinvarOption + " && " + kinvarOption + Form(" < %f", kinvarValue[index2+1]);

    // define canvas for fit
    TCanvas *c4f = new TCanvas("c4f", "c4f", canvasWidth, canvasHeight); 
    c4f->SetGrid();
    
    TH1F *dataHist;
    treeExtracted3->Draw(Form("wD>>data4fit(%d, %f, %f)", wNbins, wPlotRangeDown, wPlotRangeUp), cutTargType && cutDIS && cutPipPim && cutPi0 && cutKinVar, "goff"); // without cut around omega
    dataHist = (TH1F *)gROOT->FindObject("data4fit");
    
    RooRealVar wx("wx", "IMD(#omega) (GeV)", wPlotRangeDown, wPlotRangeUp);
    
    RooRealVar wMean("#mu", "Mean of Gaussian", wMeanIGV, wMeanRangeDown, wMeanRangeUp);
    RooRealVar wSigma("#sigma", "Width of Gaussian", wSigmaIGV, wSigmaRangeDown, wSigmaRangeUp);
    RooGaussian omega("omega", "omega peak", wx, wMean, wSigma);
    
    RooDataHist data4fit("data4fit", "data4fit", wx, dataHist);
    omega.fitTo(data4fit, Range(wFitRangeDown, wFitRangeUp), Save());
    
    RooPlot *wFrame = wx.frame(Title("IMD(#omega) for D Data"), Bins(wNbins));
    data4fit.plotOn(wFrame, Name("wData"));
    omega.plotOn(wFrame, Name("wModel"), LineColor(kMagenta));
    omega.paramOn(wFrame, Layout(0.6, 0.9, 0.9)); // x1, x2, delta-y
    
    wFrame->Draw();
    
    // draw chi2
    Double_t wChi2 = wFrame->chiSquare("wModel", "wData");
    TPaveText *wTextBlock = new TPaveText(0.7, 0.9, 0.9, 1.0, "NDC TL"); // x1, y1, x2, y2
    wTextBlock->AddText(Form("#chi^{2}/ndf = %.3f", wChi2));
    wTextBlock->SetFillColor(kWhite);
    wTextBlock->SetShadowColor(kWhite);
    wTextBlock->SetTextColor(kBlack);
    wTextBlock->Draw();
    
    // draw lines
    drawVerticalLine(wMean.getValV());
    drawVerticalLine(wMean.getValV() - wNsigma*wSigma.getValV());
    drawVerticalLine(wMean.getValV() + wNsigma*wSigma.getValV());
    
    std::cout << std::endl;
    std::cout << "wFIT COMPLETED." << std::endl;
    std::cout << "wMean  = " << wMean.getValV() << std::endl;
    std::cout << "wSigma = " << wSigma.getValV() << std::endl;
    std::cout << "wChi2  = " << wChi2 << std::endl;
    std::cout << std::endl;

    // save edges!
    wLowEdge[index2] = wMean.getValV() - wNsigma*wSigma.getValV();
    wHighEdge[index2] = wMean.getValV() + wNsigma*wSigma.getValV();
    
    TString fKinvarAuxSufix;
    fKinvarAuxSufix = kinvarSufix + Form("%d", index2 + kinvarConstant);

    std::cout << "D" << fKinvarAuxSufix << ": " << wLowEdge[index2] << " < wD < " << wHighEdge[index2] << std::endl;
    std::cout << std::endl;

    // save canvas
    c4f->Print(outFolder + "/wfit-D" + fKinvarAuxSufix + wNSigmaSufix + pi0NSigmaSufix + ".png"); // output file
  }
}

void integrateData(TString targetOption2) {

  // for targets
  Int_t targIndex;
  if (targetOption2 == "D") {
    cutTargType = "TargType == 1";
    inputFile1 = inputFolder + "/C/comb_C-thickD2.root";
    inputFile2 = inputFolder + "/Fe/comb_Fe-thickD2.root";
    inputFile3 = inputFolder + "/Pb/comb_Pb-thinD2.root";
    targIndex = 0;
  } else if (targetOption2 == "C") {
    cutTargType = "TargType == 2";
    inputFile1 = inputFolder + "/C/comb_C-thickD2.root";
    inputFile2 = "";
    inputFile3 = "";
    targIndex = 1;
  } else if (targetOption2 == "Fe") {
    cutTargType = "TargType == 2";
    inputFile1 = inputFolder + "/Fe/comb_Fe-thickD2.root";
    inputFile2 = "";
    inputFile3 = "";
    targIndex = 2;
  } else if (targetOption2 == "Pb") {
    cutTargType = "TargType == 2";
    inputFile1 = inputFolder + "/Pb/comb_Pb-thinD2.root";
    inputFile2 = "";
    inputFile3 = "";
    targIndex = 3;
  }
  
  // extract data
  TChain *treeExtracted2 = new TChain();
  treeExtracted2->Add(inputFile1 + "/mix");
  treeExtracted2->Add(inputFile2 + "/mix");
  treeExtracted2->Add(inputFile3 + "/mix");
  
  for (Int_t index = 0; index < kinvarNbins; index++) {
    
    // define kinvar cut
    cutKinVar = Form("%f < ", kinvarValue[index]) + kinvarOption + " && " + kinvarOption + Form(" < %f", kinvarValue[index+1]);
    
    // define omega cut
    cutOmega = Form("%f < wD && wD < %f", wLowEdge[index], wHighEdge[index]);
    
    /*** Integrate! ***/
    
    TH1F *integratedHist;
    treeExtracted2->Draw("wD>>data(52, 0.24, 0.5)", cutTargType && cutDIS && cutPipPim && cutPi0 && cutKinVar && cutOmega, "goff"); // with cut around omega
    integratedHist = (TH1F *)gROOT->FindObject("data");
    
    // print them
    TString kinvarAuxSufix;
    kinvarAuxSufix = kinvarSufix + Form("%d", index + kinvarConstant);
    // std::cout << kinvarValue[index] << " < " << kinvarOption << " < " << kinvarValue[index+1] << std::endl; // for debug
    particleNumber[targIndex][index] = integratedHist->IntegralAndError(1, 52, particleError[targIndex][index], "");
    std::cout << targetOption2 << kinvarAuxSufix << ": " << particleNumber[targIndex][index] << " +/- " << particleError[targIndex][index] << std::endl;
  }
}
