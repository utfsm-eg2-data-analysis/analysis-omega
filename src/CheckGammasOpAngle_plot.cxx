/**************************************/
/* CheckGammasOpAngle_plot.cxx        */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// exclusive for simulations/generated
// plots

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

TString inputFile = "";

// main options
TString targetOption;
TString runNumber;

// cuts
TCut cutDIS_gen = "mc_Q2 > 1 && mc_W > 2 && mc_Yb < 0.85";
TCut cutPi0_gen = "mc_pi0M > 0.13 && mc_pi0M < 0.14";
TCut cutGSIM;

// names stuff
TString plotFile;
TString rootFile;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // set cuts
  cutGSIM = cutDIS_gen && cutPi0_gen;
  
  // define canvas
  TCanvas *c = new TCanvas("c", "c", 1366, 769);
  c->SetTickx(1);
  c->SetTicky(1);
  gStyle->SetOptStat(0);
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile + "/mix");
    
  /*** true ***/
  TH1F *plotHist;
  treeExtracted->Draw("mc_pi0Theta>>hist(180, 0., 90.)", cutGSIM, "goff");
  plotHist = (TH1F *)gROOT->FindObject("hist");
  
  plotHist->SetLineColor(kBlue);
  plotHist->SetLineWidth(3);
  plotHist->SetFillStyle(0);
    
  // draw everything
  plotHist->Draw("HIST");

  // save plot
  c->Print(plotFile); // output file

  // create file, write hist and close file
  TFile *theFile = new TFile(rootFile, "RECREATE");
  plotHist->Write();
  theFile->Close();

  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckGammasOpAngle_plot -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hg:r:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'g': targetOption = optarg; break;
    case 'r': runNumber = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckGammasOpAngle_plot -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing CheckGammasOpAngle_plot program. Parameters chosen are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  runNumber    = " << runNumber << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "CheckGammasOpAngle_plot program. Usage is:" << std::endl;
  std::cout << "./CheckGammasOpAngle_plot -[options] -[more options]" << std::endl;
  std::cout << std::endl;
  std::cout << "  h         : prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "  g[target] : selects target" << std::endl;
  std::cout << std::endl;
  std::cout << "  r[rn]     : selects run number" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for targets
  inputFile = "comb" + targetOption + "_" + runNumber + ".root";
  // output name
  plotFile = "plot-gammas-op-angle-" + targetOption + "_" + runNumber + ".png";
  rootFile = "plot-gammas-op-angle-" + targetOption + "_" + runNumber + ".root";
}
