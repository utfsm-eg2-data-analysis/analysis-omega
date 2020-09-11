/**************************************/
/* SampFrac_points.cxx                */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// final stage: plot points for mean & (mean +- 2.5sigma) depending on momentum bin

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
#include "RooGenericPdf.h" // new!

using namespace RooFit;

/*** Global variables ***/

TString outDir = proDir + "/out/SampFrac";

const Int_t Nbins = 36; // (44-9), for now
Double_t mean[Nbins], mean_error[Nbins];
Double_t sigma[Nbins], sigma_error[Nbins];

TString treeFile = outDir + "/hola.root";
TString plotFile = outDir + "/final.png";
TString plotFile_mean  = outDir + "/final_mean.png";
TString plotFile_sigma = outDir + "/final_sigma.png";
TString textFile = outDir + "/final.dat";

int main() {

  /*** Read data ***/

  TString fitFile;
  
  for (Int_t i = 9; i <= 44; i++) { // 9 to 44, hardcoded for now
    Int_t index = i - 9;
    
    fitFile = outDir + "/hola_" + Form("%d", i) + ".dat";
    std::cout << "Reading " << fitFile << " ..." << std::endl;
    std::ifstream inFile(fitFile);

    TString auxString1, auxString2;
    Int_t l = 0; // line counter
    while (inFile >> auxString1 >> auxString2) {
      l++;
      if (l == 1) { // first line
        mean[index]       = auxString1.Atof();
        mean_error[index] = auxString2.Atof();
	std::cout << "  mean  = " << mean[index] << " +- " << mean_error[index] << std::endl;
      } else if (l == 2) {
        sigma[index]       = auxString1.Atof();
	sigma_error[index] = auxString2.Atof();
	std::cout << "  sigma = " << sigma[index] << " +- " << sigma_error[index] << std::endl;
      }
    }
    inFile.close();
  }
  
  /*** Histograms ***/

  // set hists
  TH1F *meanHist = new TH1F("meanHist", "", Nbins, 0.8, 4.4); // for now
  TH1F *sigmaHist = new TH1F("sigmaHist", "", Nbins, 0.8, 4.4);

  // fill hists
  for (Int_t cc = 0; cc < Nbins; cc++) {
    meanHist->SetBinContent(cc + 1, mean[cc]);
    meanHist->SetBinError(cc + 1, mean_error[cc]);
    
    sigmaHist->SetBinContent(cc + 1, sigma[cc]);
    sigmaHist->SetBinError(cc + 1, sigma_error[cc]);
  }

  TH1F *topHist = new TH1F("topHist", "", Nbins, 0.8, 4.4); // for now
  topHist->Add(meanHist, sigmaHist, 1, 2.5);
  
  TH1F *botHist = new TH1F("botHist", "", Nbins, 0.8, 4.4);
  botHist->Add(meanHist, sigmaHist, 1, -2.5);

  // styles
  topHist->SetFillStyle(0);
  topHist->SetLineColor(kBlack);
  topHist->SetLineWidth(3);
  topHist->GetYaxis()->SetRangeUser(0.1, 0.4);

  meanHist->SetFillStyle(0);
  meanHist->SetLineColor(kBlack);
  meanHist->SetLineWidth(3);

  botHist->SetFillStyle(0);
  botHist->SetLineColor(kBlack);
  botHist->SetLineWidth(3);
  
  /*** RooFit stuff -- MEAN ***/

  RooRealVar x("x", "x", 0.8, 4.4);

  // define data
  RooDataHist data("data", "data", x, meanHist);

  // define function
  RooRealVar a("a", "a", 1e-2, 1e-2, 1e-1);
  RooRealVar b("b", "b", -3.5e-3, -8e-3, -1e-3);
  // RooGenericPdf model("model", "Generic PDF", "a*x+b*x*x", RooArgSet(x, a, b));
  RooPolynomial model("model", "pol", x, RooArgList(a, b));

  // define frame
  RooPlot *frame = x.frame(Title("Sampling Fraction"), Bins(Nbins));
  frame->GetYaxis()->SetTitle("Counts");
  frame->GetXaxis()->SetTitle("Etot/P");
  frame->GetXaxis()->CenterTitle();

  // fit
  model.fitTo(data, Minos(kTRUE), Save(), Range(0.8, 4.4));

  // draw function & overlay data points
  data.plotOn(frame, Name("Data"), DataError(RooAbsData::SumW2));
  model.plotOn(frame, Name("Model"), LineColor(kRed));
  
  // add params
  model.paramOn(frame, Layout(0.13, 0.34, 0.25), Format("NEAU", AutoPrecision(2))); // x1, x2, avg-y
  frame->getAttText()->SetTextSize(0.025);
  frame->getAttLine()->SetLineWidth(0);

  TCanvas *c0 = new TCanvas("c0", "c0", 1000, 1000);
  gStyle->SetOptStat(0);

  frame->Draw();

  c0->Print(plotFile_mean); // output file

  /*** RooFit stuff -- SIGMA ***/
  
  RooRealVar x2("x2", "x2", 0.8, 4.4);

  // define data
  RooDataHist data2("data2", "data2", x2, sigmaHist);

  // define function
  RooRealVar d("d", "d", 8e-3, 1e-3, 1e-1);
  RooRealVar f("f", "f", 1.5e-2, 1e-3, 1e-1);
  RooGenericPdf model2("model2", "Generic PDF", "sqrt(d*d + f*f/sqrt(x2))", RooArgSet(x2, d, f));

  // define frame
  RooPlot *frame2 = x2.frame(Title("Sampling Fraction"), Bins(Nbins));
  frame2->GetYaxis()->SetTitle("Counts");
  frame2->GetXaxis()->SetTitle("Etot/P");
  frame2->GetXaxis()->CenterTitle();

  // fit
  model2.fitTo(data2, Minos(kTRUE), Save(), Range(0.8, 2.6)); // 4.4

  // draw function & overlay data points
  data2.plotOn(frame2, Name("Data"), DataError(RooAbsData::SumW2));
  model2.plotOn(frame2, Name("Model"), LineColor(kRed));
  
  // add params
  model2.paramOn(frame2, Layout(0.13, 0.34, 0.25), Format("NEAU", AutoPrecision(2))); // x1, x2, avg-y
  frame2->getAttText()->SetTextSize(0.025);
  frame2->getAttLine()->SetLineWidth(0);

  TCanvas *c2 = new TCanvas("c2", "c2", 1000, 1000);
  gStyle->SetOptStat(0);

  frame2->Draw();

  c2->Print(plotFile_sigma); // output file
  
  /*** 2D Hist ***/

  // color stuff, smoran
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
  Double_t red[NRGBs]   = {0.00, 0.00, 0.87, 1.00, 0.51};
  Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
  Double_t blue[NRGBs]  = {0.51, 1.00, 0.12, 0.00, 0.00};
  
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);

  // input tree
  TChain *tElectrons = new TChain();
  tElectrons->Add(treeFile + "/ntuple_e");

  TH2F *theHist;
  tElectrons->Draw("Etot/P:P>>hist(100, 0., 5, 100, 0.1, 0.4)", "", "goff");
  theHist = (TH2F *)gROOT->FindObject("hist");
  
  theHist->SetContour(99);
  
  /*** Drawing ***/
      
  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 1000);
  gStyle->SetOptStat(0);
  gStyle->SetNumberContours(NCont); // colors, smoran

  // frame->Draw();
  theHist->Draw("COLZ");
  topHist->Draw("SAME");
  meanHist->Draw("SAME");
  botHist->Draw("SAME");

  c1->Print(plotFile); // output file

  /*** Save data ***/
  /*
  std::ofstream outFinalFile(textFile, std::ios::out); // output file
  // line 1: omegaMean
  outFinalFile << mean.getValV() << "    " << mean.getError() << std::endl;
  // line 2: omegaSigma
  outFinalFile << sigma.getValV() << "    " << sigma.getError() << std::endl;
  std::cout << "Created file: " << textFile << std::endl;
  */
  
  return 0;
}
