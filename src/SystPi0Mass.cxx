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

TString outDir = proDir + "/out/SystPi0";

TString inputFile1 = "";
TString inputFile2 = "";
TString inputFile3 = "";

// main options
Int_t    plotFlag = 0;
Int_t    fitFlag  = 0;
TString  targetOption;

// cuts
TCut cutTargType = "";

// names stuff
TString outPrefix;
TString plotFile;

// other
Int_t canvasWidth = 1366;
Int_t canvasHeight = 768;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

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
    plotHist->SetTitle("IM(#pi^{0}) for " + targetOption + " Data");
    plotHist->SetLineColor(kBlack);
    plotHist->SetLineWidth(3);
    plotHist->GetXaxis()->SetTitle("IM(#pi^{0}) (GeV)");
    plotHist->GetXaxis()->CenterTitle();
    plotHist->GetYaxis()->SetTitle("Counts");
    plotHist->GetYaxis()->CenterTitle();
    plotHist->GetYaxis()->SetMaxDigits(3);
    
    plotHist->Draw("E");

  } else if (fitFlag) {

    TChain *treeExtracted = new TChain();
    treeExtracted->Add(inputFile1 + "/mix");
    treeExtracted->Add(inputFile2 + "/mix");
    treeExtracted->Add(inputFile3 + "/mix");

    // NOTES
    // best result for D data w/ DIS cut: 500, 0, 1., 2.5e-2, 2.35e-2, 2.65e-2, 0.134, 0.130, 0.140, 0.110, 0.154
    // best result for All data w/ DIS cut: the same
    
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

    RooRealVar x("x", "IM(#pi^{0}) (GeV)", plotRangeDown, plotRangeUp);

    RooRealVar mean("#mu", "Mean of Gaussian", meanIGV, meanRangeDown, meanRangeUp);
    RooRealVar sigma("#sigma", "Width of Gaussian", sigmaIGV, sigmaRangeDown, sigmaRangeUp);
    RooGaussian pi0("pi0", "pi0 peak", x, mean, sigma);

    RooDataHist data("data", "data", x, fitHist);
    pi0.fitTo(data, Range(fitRangeDown, fitRangeUp), Save());

    RooPlot *theFrame = x.frame(Title("IM(#pi^{0}) for " + targetOption + " Data"), Bins(Nbins));
    data.plotOn(theFrame, Name("data"));
    pi0.plotOn(theFrame, Name("model"), LineColor(kRed));
    pi0.paramOn(theFrame, Layout(0.6, 0.9, 0.9)); // x1, x2, delta-y

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
    drawVerticalLine(mean.getValV());
    drawVerticalLine(mean.getValV() - 3*sigma.getValV());
    drawVerticalLine(mean.getValV() + 3*sigma.getValV());
    drawVerticalLineRed(0.059); // MW
    drawVerticalLineRed(0.209); // MW
    
    std::cout << std::endl;
    std::cout << "FIT COMPLETED." << std::endl;
    std::cout << "mean  = " << mean.getValV() << std::endl;
    std::cout << "sigma = " << sigma.getValV() << std::endl;
    std::cout << "chi2  = " << chi2 << std::endl;    
    std::cout << std::endl;
    
  }

  // save plot
  c->Print(plotFile); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./SystPi0Mass -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hp:f:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'p': targetOption = optarg; plotFlag = 1; break;
    case 'f': targetOption = optarg; fitFlag = 1; break;
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
  if (plotFlag) std::cout << "  --targetOption = " << targetOption << std::endl;
  std::cout << "  fitFlag      = " << fitFlag << std::endl;
  if (fitFlag) std::cout << "  --targetOption = " << targetOption << std::endl;
  }
  std::cout << std::endl;
}

void printUsage() {
  std::cout << std::endl;
  std::cout << "SystPi0Mass program. Usage is:" << std::endl;
  std::cout << "./SystPi0Mass -[options] -[more options]" << std::endl;
  std::cout << "  h         : prints usage and exit program" << std::endl;
  std::cout << "  p[target] : plots mpi0 spectrum for target" << std::endl;
  std::cout << "  f[target] : fits mpi0 peak for target" << std::endl;
  std::cout << "    target option can be: D | C | Fe | Pb | All" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for targets
  if (targetOption == "D") {
    cutTargType = "TargType == 1";
    inputFile1 = dataDir + "/C/comb_C-thickD2.root";
    inputFile2 = dataDir + "/Fe/comb_Fe-thickD2.root";
    inputFile3 = dataDir + "/Pb/comb_Pb-thinD2.root";
  } else if (targetOption == "C") {
    cutTargType = "TargType == 2";
    inputFile1 = dataDir + "/C/comb_C-thickD2.root";
  } else if (targetOption == "Fe") {
    cutTargType = "TargType == 2";
    inputFile1 = dataDir + "/Fe/comb_Fe-thickD2.root";
  } else if (targetOption == "Pb") {
    cutTargType = "TargType == 2";
    inputFile1 = dataDir + "/Pb/comb_Pb-thinD2.root";
  } else if (targetOption == "All") {
    inputFile1 = dataDir + "/C/comb_C-thickD2.root";
    inputFile2 = dataDir + "/Fe/comb_Fe-thickD2.root";
    inputFile3 = dataDir + "/Pb/comb_Pb-thinD2.root";
  }
  // for process names
  if (plotFlag) {
    outPrefix = "plot-";
  } else if (fitFlag) {
    outPrefix = "fit-";
  }
  // output name
  plotFile = outDir + "/" + outPrefix + "mpi0-" + targetOption + ".png";
}
