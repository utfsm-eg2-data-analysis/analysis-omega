/**************************************/
/* QuickFit.cxx                       */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// I want to fit:
//   IM(omega) vs shifted IMD(omega) for one target

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

TString outDir     = proDir + "/out/QuickFit";
TString inputFile1 = dataDir + "/C/comb_C-thickD2.root";
TString inputFile2 = dataDir + "/Fe/comb_Fe-thickD2.root";
TString inputFile3 = dataDir + "/Pb/comb_Pb-thinD2.root";

// main options
TString targetOption = "";

TCut cutTargType;

TString titleDraw;

TString titleKinvar;
TString titleAxis;
TString histProperties;

TString outPrefix;
TString plotFile;

TString titleCase; // new!

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

int main(int argc, char **argv) {
  
  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // dir structure, just in case
  system("mkdir -p " + outDir);
  
  TCut cutAll = cutDIS && cutPipPim && cutPi0;
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
    
  setAlias(treeExtracted);
    
  TH1F *theHist;
  
  // treeExtracted->Draw("swD>>imd" + histProperties, cutAll && cutTargType, "goff");
  // theHist = (TH1F *)gROOT->FindObject("imd");

  treeExtracted->Draw("wM>>im" + histProperties, cutAll && cutTargType, "goff");
  theHist = (TH1F *)gROOT->FindObject("im");
  
  /*
  theHist->SetTitle(titleCase + targetOption + titleDraw);
  theHist->GetXaxis()->SetTitle(titleAxis);
  theHist->GetYaxis()->SetTitle("Counts");
  theHist->GetYaxis()->SetMaxDigits(3);
  theHist->SetTitleFont(22);

  theHist->SetFillStyle(1);
  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(3);

  theHist->Draw("HIST");
  */
  
  /*** the fit ***/

  RooRealVar x("mass", "(GeV)", 0, 2.5);

  // define signal parameters
  // RooRealVar omegaMean("#mu(#omega)", "Mean of Gaussian", 0.7829, 0.76, 0.82);
  // RooRealVar omegaSigma("#sigma(#omega)", "Width of Gaussian", 0.010, 0.002, 0.045);
  RooRealVar omegaMean("#mu(#omega)", "Mean of Gaussian", 0.7829, 0.76, 0.84);
  RooRealVar omegaSigma("#sigma(#omega)", "Width of Gaussian", 0.010, 0.002, 0.075);

  // define signal functions, use them when corresponds
  RooGaussian omega("omega", "omega peak", x, omegaMean, omegaSigma);
  
  // define data
  RooDataHist data("data", "my data", x, theHist);

  // define frame
  RooPlot *frame = x.frame(Title("IMD(#pi^{+} #pi^{-} #pi^{0}) for " + targetOption),
			   Bins(250));
  
  // fit the normal way
  omega.fitTo(data, Minos(kTRUE), Extended(), Range(0.76, 0.84));
  
  // draw data points
  data.plotOn(frame, Name("Data")); // DataError(RooAbsData::SumW2)
  omega.plotOn(frame, Name("Omega"), LineColor(kRed));

    // add params
  omega.paramOn(frame, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frame->getAttText()->SetTextSize(0.025);
  frame->getAttLine()->SetLineWidth(0);
  
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->SetTitle("Counts");
  frame->GetYaxis()->CenterTitle();

  /*** Draw! ***/
  
  // define canvas
  TCanvas *c = new TCanvas("c", "c", 1366, 768); 
  gStyle->SetOptStat(0);
  c->SetGrid();

  frame->Draw();

  // save file
  c->Print(plotFile); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./QuickFit -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./QuickFit -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing QuickFit program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "QuickFit program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./QuickFit -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./QuickFit -t[target]" << std::endl;
  std::cout << "    (exclusive)" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // data
  titleDraw = " Data";
  titleCase = "IM vs IMD for ";
  titleAxis = "(GeV)";
  histProperties = "(250, 0., 2.5)";
  
  // for target
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
  }
  
  // output name
  plotFile = outDir + "/quick-fit-" + targetOption + ".png";
}
