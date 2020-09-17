/**************************************/
/* SampFrac_fit.cxx                   */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// stage 3: plot and fit projections (Etot/P distributions) for certain P bins
// recommended bins: 7 - 44

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

/*** Global variables ***/

TString outDir = proDir + "/out/SampFrac";

// options
TString setOption;
TString targetOption;
Int_t   binMomentum;

TCut cutMomentum;

TString titleMomentum;
TString treeFile;
TString plotFile;
TString textFile;

int main(int argc, char **argv) {

  /*** Parse Command Line ***/

  if (argc != 4) {
    std::cout << "Three arguments <set> <option> <bin in momentum> are required." << std::endl;
    exit(0);
  } else {
    setOption    = argv[1];
    targetOption = argv[2];
    binMomentum  = atoi(argv[3]);
    // set filenames
    treeFile = outDir + "/samp-frac_" + setOption + "-" + targetOption + ".root";
    plotFile = outDir + "/samp-frac-fit_" + setOption + "-" + targetOption + "_" + Form("%d", binMomentum) + ".png";
    textFile = outDir + "/samp-frac-fit_" + setOption + "-" + targetOption + "_" + Form("%d", binMomentum) + ".dat";
  }
  
  // assign cut
  Int_t Nbins = 50; // 100 MeV momentum resolution
  Double_t upperLimit = 5.0;
  Double_t lowerLimit = 0.0;
  Double_t delta = (upperLimit - lowerLimit)/((Double_t) Nbins);
  Double_t lowerEdge = lowerLimit + (binMomentum-1)*delta;
  Double_t upperEdge = lowerLimit + (binMomentum-1+1)*delta;
  cutMomentum = Form("%f < P && P < %f", lowerEdge, upperEdge);
  titleMomentum = Form(" (%.2f < P < %.2f)", lowerEdge, upperEdge);
  
  // just in case
  system("mkdir -p " + outDir);
    
  /*** Histograms ***/

  // input tree
  TChain *tElectrons = new TChain();
  tElectrons->Add(treeFile + "/ntuple_e");
  
  TH1F *theHist;
  tElectrons->Draw("Etot/P>>hist(100, 0.1, 0.4)", cutMomentum, "goff");
  theHist = (TH1F *)gROOT->FindObject("hist");

  Double_t histMean = theHist->GetMean();
  Double_t histRMS = theHist->GetRMS();

  /*** RooFit stuff ***/

  RooRealVar x("Etot/P", "Etot/P", 0.1, 0.4);

  // define data
  RooDataHist data("data", "data", x, theHist);
  
  // define signal
  RooRealVar mean("#mu", "Mean of Gaussian", histMean, histMean - 0.01, histMean + 0.01);
  RooRealVar sigma("#sigma", "Width of Gaussian", histRMS, 0.0, histRMS);
  RooGaussian model("gaussian", "gaussian", x, mean, sigma);

  // define frame
  RooPlot *frame = x.frame(Title("Sampling Fraction" + titleMomentum), Bins(100));
  frame->GetYaxis()->SetTitle("Counts");
  frame->GetXaxis()->SetTitle("Etot/P");
  frame->GetXaxis()->CenterTitle();

  // fit
  model.fitTo(data, Minos(kTRUE), Save(), Range(histMean - TMath::Sqrt(2)*histRMS, histMean + TMath::Sqrt(2)*histRMS));

  // draw function & overlay data points
  data.plotOn(frame, Name("Data"), DataError(RooAbsData::SumW2));
  model.plotOn(frame, Name("Model"), LineColor(kRed));
  
  // add params
  model.paramOn(frame, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frame->getAttText()->SetTextSize(0.025);
  frame->getAttLine()->SetLineWidth(0);
    
  /*** Drawing ***/
      
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  // gStyle->SetOptStat(0);

  frame->Draw();

  c->Print(plotFile); // output file

  /*** Save data ***/

  std::ofstream outFinalFile(textFile, std::ios::out); // output file
  // line 1: omegaMean
  outFinalFile << mean.getValV() << "    " << mean.getError() << std::endl;
  // line 2: omegaSigma
  outFinalFile << sigma.getValV() << "    " << sigma.getError() << std::endl;
  std::cout << "Created file: " << textFile << std::endl;

  return 0;
}
