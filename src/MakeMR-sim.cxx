/**************************************/
/* MakeMR-sim.cxx                     */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

/*** TASK 2 for Analysis Note ***/

// nbs for simulations

#include <iostream>
#include <fstream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TChain.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TF1.h"
#include "TString.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TObjArray.h"
#include "TLine.h"
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

TString proDir = "/home/borquez/omegaThesis";
TString inDir  = proDir + "/out/filterSim";
TString ouDir  = proDir + "/out/MakeMR/sim";

Double_t lowEdge[4][5];
Double_t highEdge[4][5];

// [D, C, Fe, Pb][Z bin: 3-7]
Double_t particleNumber[4][5];
Double_t particleError[4][5];

Int_t Nsigma;
Double_t omegaMean[4][5];
Double_t omegaSigma[4][5];

// names stuff
TString outputPlotName;
TString outputTextName;

inline void parseOpt(int argc, char* argv[]);
void printUsage();
void assignOptions();

void setAlias(TTree *treeExtracted);
void fitRootFiles(TString targetOption);
void integrateRootFiles(TString targetOption);
void drawVerticalLine(Double_t x);

void printResults(TH1F *CarbonMR2, TH1F *IronMR2, TH1F *LeadMR2);

int main(int argc, char **argv) {

  parseOpt(argc, argv);
  assignOptions();

  fitRootFiles("D");
  fitRootFiles("C");
  fitRootFiles("Fe");
  fitRootFiles("Pb");
  
  integrateRootFiles("D");
  integrateRootFiles("C");
  integrateRootFiles("Fe");
  integrateRootFiles("Pb");

  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  c->SetGridx(0);
  c->SetGridy(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
    
  // creating and filling histograms
  std::cout << "Creating and filling histograms." << std::endl;

  TH1F *numberDeutHist = new TH1F("numberDeutHist", "", 5, 0.5, 1.);
  TH1F *numberCarbonHist = new TH1F("numberCarbonHist", "", 5, 0.5, 1.);
  TH1F *numberIronHist = new TH1F("numberIronHist", "", 5, 0.5, 1.);
  TH1F *numberLeadHist = new TH1F("numberLeadHist", "", 5, 0.5, 1.);

  // for each bin in z
  for (Int_t cc = 0; cc < 5; cc++) {
    numberDeutHist->SetBinContent(cc + 1, particleNumber[0][cc]);
    numberDeutHist->SetBinError(cc + 1, particleError[0][cc]);
    
    numberCarbonHist->SetBinContent(cc + 1, particleNumber[1][cc]);
    numberCarbonHist->SetBinError(cc + 1, particleError[1][cc]);
    
    numberIronHist->SetBinContent(cc + 1, particleNumber[2][cc]);
    numberIronHist->SetBinError(cc + 1, particleError[2][cc]);
        
    numberLeadHist->SetBinContent(cc + 1, particleNumber[3][cc]);
    numberLeadHist->SetBinError(cc + 1, particleError[3][cc]);
  }
  
  /*** Drawing ***/
  
  TH1F *CarbonMR = new TH1F("CarbonMR", "", 5, 0.5, 1.);
  CarbonMR->SetTitle(Form("#omega MR(Z) - No Bkg Subtraction (-%d#sigma, %d#sigma)", Nsigma, Nsigma));
  CarbonMR->GetXaxis()->SetTitle("Z");
  CarbonMR->GetXaxis()->SetNdivisions(205, kFALSE);
  CarbonMR->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0.5");
  CarbonMR->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"0.56");
  CarbonMR->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"0.62");
  CarbonMR->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"0.69");
  CarbonMR->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"0.78");
  CarbonMR->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1.0");
  CarbonMR->GetYaxis()->SetTitle("MR");
    
  // for Carbon 
  CarbonMR->SetMarkerColor(kRed);
  CarbonMR->SetLineColor(kRed);
  CarbonMR->SetLineWidth(3);
  CarbonMR->SetMarkerStyle(21);
  CarbonMR->Divide(numberCarbonHist, numberDeutHist);
  // CarbonMR->Scale(1.08476); // electron normalization factor

  // draw already!
  CarbonMR->SetAxisRange(0., 1.2, "Y"); // range
  CarbonMR->Draw("E");  
  
  // for Iron
  TH1F *IronMR = new TH1F("IronMR", "", 5, 0.5, 1.);
  IronMR->SetMarkerColor(kBlue);
  IronMR->SetLineColor(kBlue);
  IronMR->SetLineWidth(3);
  IronMR->SetMarkerStyle(21);
  IronMR->Divide(numberIronHist, numberDeutHist);
  // IronMR->Scale(1.01234); // electron normalization factor
    
  IronMR->Draw("E SAME");

  // for Lead
  TH1F *LeadMR = new TH1F("LeadMR", "", 5, 0.5, 1.);
  LeadMR->SetMarkerColor(kBlack);
  LeadMR->SetLineColor(kBlack);
  LeadMR->SetLineWidth(3);
  LeadMR->SetMarkerStyle(21);
  LeadMR->Divide(numberLeadHist, numberDeutHist);
  // LeadMR->Scale(2.12055); // electron normalization factor
    
  LeadMR->Draw("E SAME");
    
  // legend
  TLegend *legend = new TLegend(0.9, 0.75, 1., 0.9);
  legend->AddEntry(CarbonMR, "Carbon", "pl");
  legend->AddEntry(IronMR, "Iron", "pl");
  legend->AddEntry(LeadMR, "Lead", "pl");
  legend->Draw();
    
  c->Print(outputPlotName); // output file

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
  
  return 0;
}

inline void parseOpt(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeMR-sim -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hs:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 's': Nsigma = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeMR-sim -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "MakeMR-sim program. Usage is:" << std::endl;
  std::cout << "./MakeMR-sim -[option]" << std::endl;
  std::cout << "  h        : prints help and exit program" << std::endl;
  std::cout << "  s[n]     : selects range for n*sigma, with n: 3,4,5" << std::endl;
}

void assignOptions() {
  // name stuff
  outputTextName = ouDir + Form("sim-MR-Z-%dw.dat", Nsigma);
  outputPlotName = ouDir + Form("sim-MR-Z-%dw.png", Nsigma);
}

void fitRootFiles(TString targetOption) {

  // local variables
  TString inputFile;
  TCut cutTargType;
  Int_t targIndex;
  
  // assign local options
  if (targetOption == "D") {
    targIndex = 0;
    inputFile = inDir + "/simrec/jlab/D/wout_simrecD.root";
    cutTargType = "TargType == 1";
  } else if (targetOption == "C") {
    targIndex = 1;
    inputFile = inDir + "/simrec/jlab/C/wout_simrecC.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Fe") {
    targIndex = 2;
    inputFile = inDir + "/simrec/jlab/Fe/wout_simrecFe.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Pb") {
    targIndex = 3;
    inputFile = inDir + "/simrec/usm/Pb/wout_simrecPb.root";
    cutTargType = "TargType == 2";
  }
  
  TCut cutDIS = "Q2 > 1 && W > 2";
  TCut cutPi0 = "0.059 < mpi0 && mpi0 < 0.209"; // mikewood cut
  TCut cutPipPim = "0.48 > mpippim || 0.51 < mpippim"; // mikewood cut
  TCut cutAll = cutPi0 && cutDIS && cutPipPim;

  TCut cutZ;
  TString titleZ;
  Double_t lowEdgeZ[5] = {0.5, 0.557, 0.617, 0.689, 0.784};
  Double_t highEdgeZ[5] = {0.557, 0.617, 0.689, 0.784, 1.};
  TString auxZSufix;

  TString NSigmaSufix = Form("-%dw", Nsigma);

  // extractin'
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile + "/outdata");
  setAlias(treeExtracted);

  for (Int_t index = 0; index < 5; index++) { // 0 to 4

    // define z cut
    cutZ = Form("%f < Z && Z < %f", lowEdgeZ[index], highEdgeZ[index]);
    titleZ = Form("(%.02f < Z < %.02f)", lowEdgeZ[index], highEdgeZ[index]);
    
    // x-bin width = 5 MeV
    Int_t    wNbins = 52;
    Double_t wPlotRangeDown = 0.24; // aprox. 6 sigma
    Double_t wPlotRangeUp = 0.50; // aprox. 6 sigma
    
    Double_t wSigmaIGV = 2.2e-2;
    Double_t wSigmaRangeDown = 1.8e-2;
    Double_t wSigmaRangeUp = 2.6e-2;
    
    Double_t wMeanIGV = 0.37;
    Double_t wMeanRangeDown = 0.36;
    Double_t wMeanRangeUp = 0.38;
    
    Double_t wFitRangeDown = 0.32;
    Double_t wFitRangeUp = 0.41;
        
    // define canvas for fit
    TCanvas *c4f = new TCanvas("c4f", "c4f", 1200, 1000); 
    c4f->SetGrid();

    TH1F *dataHist;
    treeExtracted->Draw(Form("deltamomega>>data_z%d(52, 0.24, 0.5)", index+3), cutAll && cutTargType && cutZ, "goff");
    dataHist = (TH1F *)gROOT->FindObject(Form("data_z%d", index+3));
    
    RooRealVar wx("wx", "IMD(#omega) (GeV)", wPlotRangeDown, wPlotRangeUp);
    
    RooRealVar wMean("#mu", "Mean of Gaussian", wMeanIGV, wMeanRangeDown, wMeanRangeUp);
    RooRealVar wSigma("#sigma", "Width of Gaussian", wSigmaIGV, wSigmaRangeDown, wSigmaRangeUp);
    RooGaussian omega("omega", "omega peak", wx, wMean, wSigma);
    
    RooDataHist data4fit("data4fit", "data4fit", wx, dataHist);
    omega.fitTo(data4fit, Range(wFitRangeDown, wFitRangeUp), Save());
    
    RooPlot *wFrame = wx.frame(Title("IMD(#omega) for " + targetOption + " Sim"), Bins(wNbins));
    data4fit.plotOn(wFrame, Name("wData"));
    omega.plotOn(wFrame, Name("wModel"), LineColor(kOrange+7));
    omega.paramOn(wFrame, Layout(0.1, 0.4, 0.9)); // x1, x2, delta-y
    
    wFrame->Draw();
    
    // draw chi2
    Double_t wChi2 = wFrame->chiSquare("wModel", "wData");
    TPaveText *wTextBlock = new TPaveText(0.1, 0.9, 0.4, 1.0, "NDC TL"); // x1, y1, x2, y2
    wTextBlock->AddText(Form("#chi^{2}/ndf = %.3f", wChi2));
    wTextBlock->SetFillColor(kWhite);
    wTextBlock->SetShadowColor(kWhite);
    wTextBlock->SetTextColor(kBlack);
    wTextBlock->Draw();
    
    // draw lines
    drawVerticalLine(wMean.getValV());
    drawVerticalLine(wMean.getValV() - Nsigma*wSigma.getValV());
    drawVerticalLine(wMean.getValV() + Nsigma*wSigma.getValV());
    
    std::cout << std::endl;
    std::cout << "wFIT COMPLETED." << std::endl;
    std::cout << "wMean  = " << wMean.getValV() << std::endl;
    std::cout << "wSigma = " << wSigma.getValV() << std::endl;
    std::cout << "wChi2  = " << wChi2 << std::endl;
    std::cout << std::endl;

    auxZSufix = Form("-z%d", index + 3);
    
    // save canvas
    c4f->Print(ouDir + "/fit-" + targetOption + auxZSufix + NSigmaSufix + ".png"); // output file

    // keep numbers!
    lowEdge[targIndex][index] = wMean.getValV() - Nsigma*wSigma.getValV();
    highEdge[targIndex][index] = wMean.getValV() + Nsigma*wSigma.getValV();
    std::cout << targetOption << auxZSufix << ": "<< lowEdge[targIndex][index] << " < deltamomega < " << highEdge[targIndex][index] << std::endl;
    std::cout << std::endl;
    
    delete dataHist;
  }
  delete treeExtracted;
}

void integrateRootFiles(TString targetOption) {

  // local variables
  TString inputFile;
  TCut cutTargType;
  Int_t targIndex;
  
  // assign local options
  if (targetOption == "D") {
    targIndex = 0;
    inputFile = inDir + "/simrec/jlab/D/wout_simrecD.root";
    cutTargType = "TargType == 1";
  } else if (targetOption == "C") {
    targIndex = 1;
    inputFile = inDir + "/simrec/jlab/C/wout_simrecC.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Fe") {
    targIndex = 2;
    inputFile = inDir + "/simrec/jlab/Fe/wout_simrecFe.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Pb") {
    targIndex = 3;
    inputFile = inDir + "/simrec/usm/Pb/wout_simrecPb.root";
    cutTargType = "TargType == 2";
  }
  
  TCut cutDIS = "Q2 > 1 && W > 2";
  TCut cutPi0 = "0.059 < mpi0 && mpi0 < 0.209"; // mikewood cut
  TCut cutPipPim = "0.48 > mpippim || 0.51 < mpippim"; // mikewood cut
  TCut cutAll = cutPi0 && cutDIS && cutPipPim;

  TCut cutZ;
  TString titleZ;
  Double_t lowEdgeZ[5] = {0.5, 0.557, 0.617, 0.689, 0.784};
  Double_t highEdgeZ[5] = {0.557, 0.617, 0.689, 0.784, 1.};
  TString auxZSufix;

  TCut cutPeak;
   
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile + "/outdata");
  setAlias(treeExtracted);
  
  for (Int_t zz = 0; zz < 5; zz++) { // 0 to 4

    // define z cut
    cutZ = Form("%f < Z && Z < %f", lowEdgeZ[zz], highEdgeZ[zz]);
    titleZ = Form("(%.02f < Z < %.02f)", lowEdgeZ[zz], highEdgeZ[zz]);

    // define cut around peak
    cutPeak = Form("%f < deltamomega && deltamomega < %f", lowEdge[targIndex][zz], highEdge[targIndex][zz]);

    TH1F *dataHist;
    treeExtracted->Draw(Form("deltamomega>>data_z%d(52, 0.24, 0.5)", zz), cutAll && cutTargType && cutZ && cutPeak, "goff");
    dataHist = (TH1F *)gROOT->FindObject(Form("data_z%d", zz));

    // keep number
    auxZSufix = Form("-z%d", zz + 3);
    particleNumber[targIndex][zz] = dataHist->IntegralAndError(1, 52, particleError[targIndex][zz], "");
    std::cout << targetOption << auxZSufix << ": " << particleNumber[targIndex][zz] << " +/- " << particleError[targIndex][zz] << std::endl;

    delete dataHist;
  }
  delete treeExtracted;
}

void setAlias(TTree *treeExtracted) {
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
  // omega!
  treeExtracted->SetAlias("Eomega", "Epip + Epim + fE[0] + fE[1]");
  treeExtracted->SetAlias("Pxomega", "fX[0] + fX[1] + fX[2] + fX[3]");
  treeExtracted->SetAlias("Pyomega", "fY[0] + fY[1] + fY[2] + fY[3]");
  treeExtracted->SetAlias("Pzomega", "fZ[0] + fZ[1] + fZ[2] + fZ[3]");
  treeExtracted->SetAlias("momega", "TMath::Sqrt(Eomega*Eomega - Pxomega*Pxomega - Pyomega*Pyomega - Pzomega*Pzomega)");
  treeExtracted->SetAlias("deltamomega", "momega - mpi0 - mpip - mpim");
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
