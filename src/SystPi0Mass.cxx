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

// main options
TString targetOption;
Int_t   plotFlag = 0;
Int_t   fitFlag  = 0;
Int_t   doMRFlag = 0;
Int_t   Nsigma;
TString kinvarOption;

// cuts
TCut cutDIS = "Q2 > 1 && W > 2 && Yb < 0.85";
TCut cutPi0 = ""; // to be defined
TCut cutPipPim = "0.48 > pippimM || 0.51 < pippimM";
TCut cutAll;
TCut cutKinVar;
TCut cutTargType;

// kinvar options
Int_t    kinvarNbins = 5;
Double_t kinvarValue[6];
Double_t edgesZ[6] = {0.5, 0.557, 0.617, 0.689, 0.784, 1.};
Double_t edgesQ2[6] = {1., 1.181, 1.364, 1.598, 1.960, 3.970};
Double_t edgesNu[6] = {2.2, 3.191, 3.504, 3.744, 3.964, 4.2};
Double_t edgesPt2[6] = {0., 0.04, 0.09, 0.16, 0.273, 1.5};

// MR-related
Double_t particleNumber[4][5];
Double_t particleError[4][5];

// names stuff
TString outPrefix;
TString outputPlotName;
TString outputTextName;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

void drawVerticalLine(Double_t x);
void integrateData(TString targetOption2);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // define canvas
  TCanvas *c = new TCanvas("c", "c", 1366, 768); 
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
    
    integrateData("D");
    integrateData("C");
    integrateData("Fe");
    integrateData("Pb");
    
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
        
      numberLeadHist->SetBinContent(cc + 1, particleNumber[4][cc]);
      numberLeadHist->SetBinError(cc + 1, particleError[4][cc]);
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
  
    CarbonMR->SetAxisRange(0., 2.2, "Y"); // range
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
  while ((c = getopt(argc, argv, "ht:pfm:k:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'p': plotFlag = 1; break;
    case 'f': fitFlag = 1; break;
    case 'm': doMRFlag = 1; Nsigma = atoi(optarg); break;
    case 'k': kinvarOption = optarg; break;      
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
  if (fitFlag)  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  doMRFlag     = " << doMRFlag << std::endl;
  if (doMRFlag) {
    std::cout << "  Nsigma       = " << Nsigma << std::endl;
    std::cout << "  kinvarOption = " << kinvarOption << std::endl;
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
  std::cout << "  m[3,4,5]  : does nbs-MR with n*sigma cut around pi0 peak" << std::endl;
  std::cout << "  k[kinvar] : selects kinvar" << std::endl;
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
  // for process names
  if (plotFlag) {
    outPrefix = "plot-mpi0-" + targetOption;
  } else if (fitFlag) {
    outPrefix = "fit-mpi0-" + targetOption;
  } else if (doMRFlag) {
    outPrefix = "nbs-MR";
    outPrefix = outPrefix + "-mpi0";
    outPrefix = outPrefix + Form("-%ds", Nsigma);
    outputTextName = outFolder + "/" + outPrefix + ".dat";
  }
  // output name
  outputPlotName = outFolder + "/" + outPrefix + ".png";
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

void integrateData(TString targetOption2) {

  /*** Assign Local Options ***/

  // for targets
  if (targetOption2 == "D") {
    cutTargType = "TargType == 1";
    inputFile1 = inputFolder + "/C/comb_C-thickD2.root";
    inputFile2 = inputFolder + "/Fe/comb_Fe-thickD2.root";
    inputFile3 = inputFolder + "/Pb/comb_Pb-thinD2.root";
  } else if (targetOption2 == "C") {
    cutTargType = "TargType == 2";
    inputFile1 = inputFolder + "/C/comb_C-thickD2.root";
  } else if (targetOption2 == "Fe") {
    cutTargType = "TargType == 2";
    inputFile1 = inputFolder + "/Fe/comb_Fe-thickD2.root";
  } else if (targetOption2 == "Pb") {
    cutTargType = "TargType == 2";
    inputFile1 = inputFolder + "/Pb/comb_Pb-thinD2.root";
  }

  // for kinvar
  TString kinvarSufix;
  Int_t   kinvarConstant = 1;
  if (kinvarOption == "Z") {
    kinvarConstant = 3;
    kinvarSufix = "-z";
    for (Int_t z = 0; z <= kinvarNbins; z++) kinvarValue[z] = edgesZ[z];
  } else if (kinvarOption == "Q2") {
    kinvarSufix = "-q";    
    for (Int_t q = 0; q <= kinvarNbins; q++) kinvarValue[q] = edgesQ2[q];
  } else if (kinvarOption == "Nu") {
    kinvarSufix = "-n";
    for (Int_t n = 0; n <= kinvarNbins; n++) kinvarValue[n] = edgesNu[n];
  } else if (kinvarOption == "Pt2") {
    kinvarSufix = "-p";
    for (Int_t p = 0; p <= kinvarNbins; p++) kinvarValue[p] = edgesPt2[p];
  }
  
  // define cuts, the most important part of this program
  pi0LowEdge = obtMean - Nsigma*obtSigma;
  pi0HighEdge = obtMean + Nsigma*obtSigma;
  cutPi0 = Form("%f < pi0M && pi0M < %f", pi0LowEdge, pi0HighEdge);

  /*** Extract data! ***/
  
  TChain *treeExtracted2 = new TChain();
  treeExtracted2->Add(inputFile1 + "/mix");
  treeExtracted2->Add(inputFile2 + "/mix");
  treeExtracted2->Add(inputFile3 + "/mix");

  for (Int_t index = 0; index < kinvarNbins; index++) {

    // define kinvar cut
    cutKinVar = Form("%f < ", kinvarValue[index]) + kinvarOption + " && " + kinvarOption + Form(" < %f", kinvarValue[index+1]);
    
    TH1F *dataHist;
    treeExtracted2->Draw("wD>>data(50, 0.3, 0.4)", cutTargType && cutDIS && cutPipPim && cutPi0 && cutKinVar, "goff");
    dataHist = (TH1F *)gROOT->FindObject("data");
    
    Int_t targIndex;
    if (targetOption2 == "D") targIndex = 0;
    else if (targetOption2 == "C") targIndex = 1;
    else if (targetOption2 == "Fe") targIndex = 2;
    else if (targetOption2 == "Pb") targIndex = 3;
    
    // save numbers!
    particleNumber[targIndex][index] = dataHist->IntegralAndError(1, 50, particleError[targIndex][index], "");

    // print them
    TString kinvarAuxSufix;
    kinvarAuxSufix = kinvarSufix + Form("%d", index + kinvarConstant);
    // std::cout << kinvarValue[index] << " < " << kinvarOption << " < " << kinvarValue[index+1] << std::endl; // for debug
    std::cout << targetOption2 << kinvarAuxSufix << ": " << particleNumber[targIndex][index] << " +/- " << particleError[targIndex][index] << std::endl;
  }
}
