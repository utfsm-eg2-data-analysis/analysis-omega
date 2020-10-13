/**************************************/
/* Acceptance_fit-omega.cxx           */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

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

void MakeSimFit(TFile *theFile, TString histName);

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

  for (Int_t k = 0; k < 4; k++) { // kinvar loop
    for (Int_t i = 0; i < 5; i++) {
      currentHistName = "GSIM_" + targetOption + "_" + kinVar[k] + Form("%d", i);
      std::cout << currentHistName << std::endl;
      MakeSimFit(rootInputFile, currentHistName);
    }
  }

  /*** SIMREC ***/
  for (Int_t k = 0; k < 4; k++) {
    for (Int_t i = 0; i < 5; i++) {
	currentHistName = "SIMREC_" + targetOption + "_" + kinVar[k] + Form("%d", i) + kinVar[k] + Form("%d", i);
	MakeSimFit(rootInputFile, currentHistName);
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
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
}

void MakeSimFit(TFile *theFile, TString histName) {

  TH1F *omegaHist = (TH1F *)theFile->Get(histName); 

  /*** Fit Options ***/
  
  // bin x-width = 5 MeV
  Int_t    Nbins        = omegaHist->GetNbinsX();
  Double_t fitRangeDown = omegaHist->GetXaxis()->GetXmin();
  Double_t fitRangeUp   = omegaHist->GetXaxis()->GetXmax();

  Double_t meanIGV       = omegaHist->GetMean();
  Double_t meanRangeDown = meanIGV - 0.03;
  Double_t meanRangeUp   = meanIGV + 0.03;
  
  Double_t sigmaIGV       = omegaHist->GetRMS();
  Double_t sigmaRangeDown = 0;
  Double_t sigmaRangeUp   = sigmaIGV + 0.3;
  
  /*** RooFit stuff ***/

  RooRealVar x("IMD", "Invariant Mass Difference (GeV)", fitRangeDown, fitRangeUp);

  RooRealVar  omegaMean("#mu(#omega)", "Mean of Gaussian", meanIGV, meanRangeDown, meanRangeUp);
  RooRealVar  omegaSigma("#sigma(#omega)", "Width of Gaussian", sigmaIGV, sigmaRangeDown, sigmaRangeUp);
  // RooGaussian omega("omega", "omega peak", x, omegaMean, omegaSigma);
  RooBreitWigner omega("omega-bw", "omega-bw peak", x, omegaMean, omegaSigma);    

  RooRealVar   b1("b1", "linear term", 0., -20, 20);
  RooChebychev bkg("bkg", "background", x, RooArgList(b1));
  // RooRealVar   b2("b2", "quadratic term", -0.1, -10., 0.); // definition, use it only when bkgOption=2
  // RooChebychev bkg("bkg", "background", x, RooArgList(b1, b2));

  // model(x) = sig_yield*sig(x) + bkg_yield*bkg(x)
  RooRealVar nsig("N_{#omega}", "omega yields", 0., omegaHist->GetEntries());
  RooRealVar nbkg("N_{b}", "bkg yields", 0., omegaHist->GetEntries());
  RooAddPdf  model("model", "model", RooArgList(omega, bkg), RooArgList(nsig, nbkg));
  
  // define data
  RooDataHist data("data", "my data", x, omegaHist);

  // define frame
  RooPlot *frame = x.frame(Name(histName), Title(histName), Bins(Nbins));
  
  // fit the normal way
  RooFitResult *r1 = model.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  r1->Print("v");

  // define constraints
  RooGaussian conSigma("conSigma", "conSigma", omegaSigma, RooConst(0.02), RooConst(0.001));
  RooProdPdf  cmodel("cmodel", "model with constraint", RooArgSet(model, conSigma));
  
  // fit constraint model
  RooFitResult *r2 = cmodel.fitTo(data, Constrain(conSigma), Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  r2->Print("v");
  
  // draw points
  data.plotOn(frame, Name("Data")); // DataError(RooAbsData::SumW2)
  
  // visualize error
  cmodel.plotOn(frame, VisualizeError(*r2, 1, kFALSE), FillColor(kRed-9));                     // FillStyle(3001)
  cmodel.plotOn(frame, Components("bkg"), VisualizeError(*r2, 1, kFALSE), FillColor(kBlue-9)); // DrawOption("L"), LineWidth(2), LineColor(kRed)

  // overlay data points
  data.plotOn(frame, Name("Data"));
  
  // overlay center values
  cmodel.plotOn(frame, Name("Model"), LineColor(kRed));
  
  // add params
  cmodel.paramOn(frame, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frame->getAttText()->SetTextSize(0.025);
  frame->getAttLine()->SetLineWidth(0);
  
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->SetTitle("Counts");
  frame->GetYaxis()->CenterTitle();
  
  // draw!
  cmodel.plotOn(frame, Components("bkg"), LineStyle(kDashed), LineColor(kBlue));
  frame->Write();

  r2->Write("rf" + histName);
}
