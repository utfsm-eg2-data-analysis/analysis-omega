/**************************************/
/* MakePlots_old.cxx                  */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// this is the one that works with the old format!!

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir   = proDir + "/out/MakePlots";
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";

// main options
Int_t   dataFlag = 0;
Int_t   simrecFlag  = 0;
TString targetOption;
TString kinvarOption = "M";
Int_t   binNumberZ = 0; // 0: off | [3-7]: on

// cuts
TCut cutTargType;
TCut cutZ = "";

// names stuff (to be assigned by the options)
TString titleDraw;
TString titleZ = "";
TString sufixZBin = "";
TString titleKinvar;
TString titleAxis;
TString outPrefix;
TString toPlotKinvar;
TString histProperties;
TString plotFile;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // cuts
  TCut cutAll = cutDIS_old && cutPipPim_old && cutPi0_old;

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/outdata");
  treeExtracted->Add(inputFile2 + "/outdata");
  treeExtracted->Add(inputFile3 + "/outdata");

  setAlias_old(treeExtracted);
  
  TH1F *theHist;
  treeExtracted->Draw(toPlotKinvar + ">>" + outPrefix + histProperties, cutAll && cutTargType && cutZ, "goff");
  theHist = (TH1F *)gROOT->FindObject(outPrefix);
  
  theHist->SetTitleFont(22);
  theHist->SetTitle(titleKinvar + targetOption + titleDraw + titleZ);
  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(3);
  theHist->GetXaxis()->SetTitle(titleAxis);
  theHist->GetYaxis()->SetTitle("Counts");
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768); 
  c->SetGrid();
  
  theHist->Draw("E");
  
  c->Print(plotFile); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./old_MakePlots -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hdst:k:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'd': dataFlag = 1; break;
    case 's': simrecFlag = 1; break;      
    case 't': targetOption = optarg; break;
    case 'k': kinvarOption = optarg; break;
    case 'z': binNumberZ = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./old_MakePlots -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << std::endl;
  std::cout << "Executing old_MakePlots program. Parameters chosen are:" << std::endl;
  std::cout << "  dataFlag     = " << dataFlag << std::endl;
  std::cout << "  simrecFlag   = " << simrecFlag << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  toPlotKinvar = " << toPlotKinvar << std::endl;
  std::cout << "  binNumberZ   = " << binNumberZ << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << std::endl;
  std::cout << "old_MakePlots program. Usage is:" << std::endl;
  std::cout << "./old_MakePlots -[options] -[more options]" << std::endl;
  std::cout << "  h         : prints help and exit program" << std::endl;
  std::cout << "  t[target] : selects target: D | C | Fe | Pb" << std::endl;
  std::cout << "  d         : draws data" << std::endl;
  std::cout << "  s         : draws simrec" << std::endl;
  std::cout << "  k[kinvar] : sets kinvar to draw, it can be: " << std::endl;
  std::cout << "     --> M  : omega invariant mass" << std::endl;
  std::cout << "     --> D  : omega invariant mass difference" << std::endl;
  std::cout << "     --> Q  : Q2" << std::endl;
  std::cout << "     --> N  : Nu" << std::endl;
  std::cout << "     --> Z  : Z" << std::endl;
  std::cout << "     --> P  : PhiPQ" << std::endl;
  std::cout << "     --> T  : Pt2" << std::endl;
  std::cout << "     --> M0 : pi0 invariant mass" << std::endl;
  std::cout << "  z[3-7]    : turns on binning in Z (off by default) and analyzes that specific bin" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for kind of data
  if (dataFlag) {
    outPrefix = "data";
    titleDraw = " Data ";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = dataDir + "/C/wout_C-thickD2.root";
      inputFile2 = dataDir + "/Fe/wout_Fe-thickD2.root";
      inputFile3 = dataDir + "/Pb/wout_Pb-thinD2.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/C/wout_C-thickD2.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/Fe/wout_Fe-thickD2.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/Pb/wout_Pb-thinD2.root";
    }
  } else if (simrecFlag) {
    outPrefix = "simrec";
    titleDraw = " Simrec ";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = simrecDir + "/jlab/D/wout_simrecD.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = simrecDir + "/jlab/C/wout_simrecC.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = simrecDir + "/jlab/Fe/wout_simrecFe.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = simrecDir + "/usm/Pb/wout_simrecPb.root";
    }
  }
  if (binNumberZ) {
    cutZ = Form("%f < Z && Z < %f", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    titleZ = Form(" in (%.02f < Z < %.02f)", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    sufixZBin = Form("-z%d", binNumberZ);
  }
  // for kinvar
  if (kinvarOption == "M") {
    toPlotKinvar = "momega";
    titleKinvar = "IM(#omega) for ";
    titleAxis = "IM (GeV)";
    histProperties = "(250, 0., 2.5.)";
  } else if (kinvarOption == "D") {
    toPlotKinvar = "deltam";
    titleKinvar = "IMD(#omega) for ";
    titleAxis = "IMD (GeV)";
    histProperties = "(200, 0., 1.6)";
  } else if (kinvarOption == "Q") {
    toPlotKinvar = "Q2";
    titleKinvar = "Q^{2}";
    titleAxis = "Q^{2}";
    histProperties = "(100, 1., 4.)";  
  } else if (kinvarOption == "N") {
    toPlotKinvar = "Nu";
    titleKinvar = "#nu";
    titleAxis = "#nu";
    histProperties = "(200, 2.2, 4.2)";
  } else if (kinvarOption == "Z") {
    toPlotKinvar = "Z";
    titleKinvar = "Z";
    titleAxis = "Z";
    histProperties = "(100, 0., 1.2)";
  } else if (kinvarOption == "P") {
    toPlotKinvar = "PhiPQ";
    titleKinvar = "#phi_{PQ} ";
    titleAxis = "#phi_{PQ}";
    histProperties = "(100, -180, 180.)";
  }
  // output name
  plotFile = outDir + "/old_" + outPrefix + "-" + toPlotKinvar + "-" + targetOption + sufixZBin + ".png";
}
