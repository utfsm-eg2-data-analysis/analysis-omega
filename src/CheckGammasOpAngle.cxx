/**************************************/
/* CheckGammasOpAngle.cxx             */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// plots gammas opening angle vs mass of pi0
// for data, simrec and generated

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/CheckGammasOpAngle";
TString inputFile1 = "";
TString inputFile2 = "";
TString inputFile3 = "";

// options
TString targetOption;
Int_t dataFlag = 0;
Int_t simrecFlag = 0;
Int_t gsimFlag = 0;
TString runNumber;

TString titleDraw;
TString massExpr, angleExpr;

TString plotFile;
TString rootFile;

// cuts
TCut cutDIS_gen = "mc_Q2 > 1 && mc_W > 2 && mc_Yb < 0.85";
TCut cutSIMREC;
TCut cutGSIM;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // set cuts
  cutGSIM   = cutDIS_gen;
  cutSIMREC = cutDIS && cutStatus;
  if (gsimFlag) cutSIMREC = "";
  if (dataFlag) cutGSIM = "";
  
  // dir structure, just in case
  system("mkdir -p " + outDir);
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  // color stuff, smoran
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
  Double_t red[NRGBs]   = {0.00, 0.00, 0.87, 1.00, 0.51};
  Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
  Double_t blue[NRGBs]  = {0.51, 1.00, 0.12, 0.00, 0.00};
  
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  
  TH2F *theHist;
  treeExtracted->Draw(massExpr + ":" + angleExpr + ">>hist(90, 0., 90., 100, 0., 0.5)", cutGSIM && cutSIMREC, "goff");
  theHist = (TH2F *)gROOT->FindObject("hist");
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 769);
  c->SetTickx(1);
  c->SetTicky(1);
  gStyle->SetOptStat(0);
  gStyle->SetNumberContours(NCont); // colors, smoran
  
  theHist->SetTitle("m(#gamma#gamma) vs #theta_{#gamma#gamma} for " + titleDraw);
  theHist->GetYaxis()->SetTitle("m(#gamma#gamma) (GeV)");
  theHist->GetXaxis()->SetTitle("#theta_{#gamma#gamma} (deg)");
  theHist->GetYaxis()->CenterTitle();
  theHist->GetXaxis()->CenterTitle();
  theHist->SetContour(99);
  theHist->Draw("COLZ");
  
  c->Print(plotFile); // output file

  // create file, write hist and close file
  if (!dataFlag) {
    TFile *theFile = new TFile(rootFile, "RECREATE");
    theHist->Write();
    theFile->Close();
  }
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckGammasOpAngle -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hs:d:g:r:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'd': targetOption = optarg; dataFlag = 1; break;
    case 's': targetOption = optarg; simrecFlag = 1; break;
    case 'g': targetOption = optarg; gsimFlag = 1; break;
    case 'r': runNumber = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckGammasOpAngle -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "CheckGammasOpAngle program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckGammasOpAngle -h" << std::endl;
  std::cout << "  prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckGammasOpAngle -[d,s,g][target]" << std::endl;
  std::cout << "  selects target: C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckGammasOpAngle -r[rn]" << std::endl;
  std::cout << "  selects run number" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing CheckGammasOpAngle program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  dataFlag     = " << dataFlag << std::endl;
  std::cout << "  simrecFlag   = " << simrecFlag << std::endl;
  std::cout << "  gsimFlag     = " << gsimFlag << std::endl;
  std::cout << "  runNumber    = " << runNumber << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for kind of data
  if (dataFlag) {
    titleDraw = targetOption + " Data";
    massExpr  = "pi0M_corr";
    angleExpr = "pi0Theta_corr";
    if (targetOption == "D") {
      inputFile1 = dataDir + "/C/comb_dataC.root";
      inputFile2 = dataDir + "/Fe/comb_dataFe.root";
      inputFile3 = dataDir + "/Pb/comb_dataPb.root";
    } else {
      inputFile1 = dataDir + "/" + targetOption + "/comb_data" + targetOption + ".root";
    }
  } else if (simrecFlag) {
    titleDraw = "Sim/Reconstructed";
    massExpr  = "pi0M_corr";
    angleExpr = "pi0Theta_corr";
    inputFile1 = "comb" + targetOption + "_" + runNumber + ".root";
  } else if (gsimFlag) {
    titleDraw = "Sim/Generated";
    massExpr  = "mc_pi0M";
    angleExpr = "mc_pi0Theta";
    inputFile1 = "comb" + targetOption + "_" + runNumber + ".root";
  }
  // for outdir
  if (!dataFlag) outDir = ".";
  // names
  plotFile = outDir + "/gammas-op-angle-" + targetOption + ".png";
  rootFile = outDir + "/gammas-op-angle-" + targetOption + "_" + runNumber + ".root";
}
