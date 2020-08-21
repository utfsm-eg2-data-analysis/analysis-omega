/**************************************/
/* Acceptance_01.cxx                  */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

//*** ACCEPTANCE: STAGE 1 ***//

// fit pi0 invariant mass from the sum of all reconstructed events
// this routine is straightforward

#include "analysisConfig.h"

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

TString accDir = proDir + "/out/Acceptance";
TString plotFile = accDir + "/acc-fit-pi0.png";

TString inputFile = accDir + "/acc-0AR.root";

int main() {

  // define canvas
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat(0);
      
  // x-bin width = 5 MeV
  Int_t    Nbins = 500;
  Double_t plotRangeDown = 0.0;
  Double_t plotRangeUp = 2.5;

  Double_t sigmaIGV = 2.e-2;
  Double_t sigmaRangeDown = 1.8e-2;
  Double_t sigmaRangeUp = 2.2e-2;

  Double_t meanIGV = 0.131;
  Double_t meanRangeDown = 0.127;
  Double_t meanRangeUp = 0.137;

  Double_t fitRangeDown = 0.11;
  Double_t fitRangeUp = 0.16;

  // opening file
  TFile *file = new TFile(inputFile);
  TH1F *fitHist = (TH1F *)file->Get("hist"); 

  RooRealVar x("x", "Reconstructed Mass [GeV]", plotRangeDown, plotRangeUp);

  RooRealVar mean("#mu", "Mean of Gaussian", meanIGV, meanRangeDown, meanRangeUp);
  RooRealVar sigma("#sigma", "Width of Gaussian", sigmaIGV, sigmaRangeDown, sigmaRangeUp);
  RooGaussian pi0("pi0", "pi0 peak", x, mean, sigma);

  RooDataHist data("data", "data", x, fitHist);
  pi0.fitTo(data, Range(fitRangeDown, fitRangeUp), Save());

  RooPlot *theFrame = x.frame(Title("m(#pi^{0}) in simrec"), Bins(Nbins));
  data.plotOn(theFrame, Name("data"));
  pi0.plotOn(theFrame, Name("model"), LineColor(kRed));
  pi0.paramOn(theFrame, Layout(0.45, 0.9, 0.9)); // x1, x2, mean-y

  theFrame->GetXaxis()->CenterTitle();
  theFrame->GetYaxis()->CenterTitle();
  theFrame->GetYaxis()->SetMaxDigits(3);
    
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
  drawVerticalLine(mean.getValV(), kRed, "dash");
  drawVerticalLine(mean.getValV() - 3*sigma.getValV(), kRed, "dash");
  drawVerticalLine(mean.getValV() + 3*sigma.getValV(), kRed, "dash");
  // drawVerticalLineRed(0.059); // MW
  // drawVerticalLineRed(0.209); // MW
    
  std::cout << std::endl;
  std::cout << "FIT COMPLETED." << std::endl;
  std::cout << "mean  = " << mean.getValV() << std::endl;
  std::cout << "sigma = " << sigma.getValV() << std::endl;
  std::cout << "chi2  = " << chi2 << std::endl;    
  std::cout << std::endl;

  // save plot
  c->Print(plotFile); // output file
}
