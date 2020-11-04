/**************************************/
/* Acceptance_fit-omega.cxx           */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// November 2020

// fits omega invariant mass difference with
// gaussian function for the signal
// 1st order polynomial for the bkg

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

TString targetOption;

TString inputDir  = workDir + "/Acceptance/merged";
TString outputDir = inputDir;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();

void MakeSimFit(TFile *theFile, TString histName, TString type);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  printOptions();

  // set i/o
  TString inputFile  = inputDir + "/acceptance_" + targetOption + ".root";
  TString outputFile = outputDir + "/fits_" + targetOption + ".root";

  // read file
  TFile *rootInputFile = new TFile(inputFile);

  // create and open output file
  TFile *rootOutputFile = new TFile(outputFile, "RECREATE");

  // define array
  TString kinVar[4] = {"Q", "N", "Z", "P"};
  TString currentHistName;
  
  /*** GSIM ***/

  for (Int_t k = 0; k < 4; k++) {
    for (Int_t i = 0; i < 5; i++) {
      currentHistName = "GSIM_" + targetOption + "_" + kinVar[k] + Form("%d", i);
      std::cout << currentHistName << std::endl;
      MakeSimFit(rootInputFile, currentHistName, "GSIM");
    }
  }

  /*** SIMREC ***/

  for (Int_t k = 0; k < 4; k++) {
    for (Int_t i = 0; i < 5; i++) {
      currentHistName = "SIMREC_" + targetOption + "_" + kinVar[k] + Form("%d", i);
      MakeSimFit(rootInputFile, currentHistName, "SIMREC");
    }
  }
  
  // close file
  rootOutputFile->Close();
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./Acceptance_fit-omega -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./Acceptance_fit-omega -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing Acceptance_fit-omega program. Chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "Acceptance_fit-omega program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_fit-omega -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_fit-omega -t[target]" << std::endl;
  std::cout << "    selects target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;
}

void MakeSimFit(TFile *theFile, TString histName, TString type) {

  // define hist
  TH1F *omegaHist = (TH1F *)theFile->Get(histName);

  /*** Fit Options ***/

  Double_t plotRangeDown = 0.56;
  Double_t plotRangeUp   = 1.00;
  Int_t Nbins = (Int_t) (((round(100*(plotRangeUp))/100) - (round(100*(plotRangeDown))/100))/5e-3); // 5 MeV

  Double_t meanIGV       = omegaHist->GetMean();
  Double_t meanRangeDown = meanIGV - 0.3;
  Double_t meanRangeUp   = meanIGV + 0.3;
  
  Double_t sigmaIGV       = omegaHist->GetRMS();
  Double_t sigmaRangeDown = 0;
  Double_t sigmaRangeUp   = sigmaIGV + 0.3;
  
  // define variable and data
  RooRealVar x("IMD", "Invariant Mass Difference (GeV)", plotRangeDown, plotRangeUp);
  RooDataHist data("data", "my data", x, omegaHist);

  /*** FIT A: BKG ***/
  // (left region)
  
  // starting values
  Double_t fitRangeDown = 0.56;
  Double_t fitRangeUp   = 0.65;
  
  RooRealVar   b1("b1", "linear term", 0., -20, 20);
  RooRealVar   b2("b2", "quadratic term", -0.1, -10., 0.); // definition, use it only when bkgOption=2
  RooChebychev bkg("bkg", "background", x, RooArgList(b1, b2));

  // fit the normal way
  RooFitResult *rA = bkg.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  rA->Print("v");

  // define frame
  RooPlot *frameA = x.frame(Name("fA_" + histName), Title(histName), Bins(Nbins));
  
  // draw!
  data.plotOn(frameA, Name("Data"));
  bkg.plotOn(frameA, Name("Bkg"), LineStyle(kDashed), LineColor(kBlue));

  // add params
  bkg.paramOn(frameA, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frameA->getAttText()->SetTextSize(0.025);
  frameA->getAttLine()->SetLineWidth(0);
  
  frameA->GetXaxis()->CenterTitle();
  frameA->GetYaxis()->SetTitle("Counts");
  frameA->GetYaxis()->CenterTitle();
  
  // draw!
  frameA->Write();
  rA->Write("rfA_" + histName);
  
  /*** FIT B: SIGNAL ***/
  // (center region)
  
  if (type == "GSIM") {
    fitRangeDown = 0.75;
    fitRangeUp   = 0.81;
  } else if (type == "SIMREC") {
    fitRangeDown = 0.70;
    fitRangeUp   = 0.86;
  }
  
  RooRealVar omegaMean("#mu(#omega)", "Mean of Gaussian", meanIGV, meanRangeDown, meanRangeUp);
  RooRealVar omegaSigma("#sigma(#omega)", "Width of Gaussian", sigmaIGV, sigmaRangeDown, sigmaRangeUp);
  RooBreitWigner omega("omega-bw", "omega-bw peak", x, omegaMean, omegaSigma);    

  // fit the normal way
  RooFitResult *rB = omega.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  rB->Print("v");

  // define frame
  RooPlot *frameB = x.frame(Name("fB_" + histName), Title(histName), Bins(Nbins));
  
  // draw!
  data.plotOn(frameB, Name("Data"));
  omega.plotOn(frameB, Name("Model"), LineColor(kRed));

  // add params
  omega.paramOn(frameB, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frameB->getAttText()->SetTextSize(0.025);
  frameB->getAttLine()->SetLineWidth(0);
  
  frameB->GetXaxis()->CenterTitle();
  frameB->GetYaxis()->SetTitle("Counts");
  frameB->GetYaxis()->CenterTitle();
  
  // draw!
  frameB->Write();
  rB->Write("rfB_" + histName);

  /*** FIT ABC: SIGNAL ***/

  if (type == "GSIM") {
    fitRangeDown = 0.70;
    fitRangeUp   = 0.86;
  } else if (type == "SIMREC") {
    fitRangeDown = 0.56;
    fitRangeUp   = 1.00;
  }  
  
  // model(x) = sig_yield*sig(x) + bkg_yield*bkg(x)
  RooRealVar nsig("N_{#omega}", "omega yields", 0., omegaHist->GetEntries());
  RooRealVar nbkg("N_{b}", "bkg yields", 0., omegaHist->GetEntries());
  RooAddPdf  model("model", "model", RooArgList(omega, bkg), RooArgList(nsig, nbkg));
  
  // fit the normal way
  RooFitResult *r1 = model.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  r1->Print("v");

  // define frame
  RooPlot *frame = x.frame(Name("fABC_" + histName), Title(histName), Bins(Nbins));
  
  // draw!
  data.plotOn(frame, Name("Data"));
  model.plotOn(frame, Name("Model"), LineColor(kRed));
  model.plotOn(frame, Components("bkg"), LineStyle(kDashed), LineColor(kBlue));
  
  // add params
  model.paramOn(frame, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frame->getAttText()->SetTextSize(0.025);
  frame->getAttLine()->SetLineWidth(0);
  
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->SetTitle("Counts");
  frame->GetYaxis()->CenterTitle();
  
  // draw!
  frame->Write();

  r1->Write("rfABC_" + histName);
}
