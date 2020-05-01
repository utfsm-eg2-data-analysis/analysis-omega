/**************************************/
/* MakePlots.cxx                      */
/*                                    */
/* Created by Andrés Bórquez          */
/*                                    */
/**************************************/

// Plots different kinvar spectrums, such as:
//   {IM(omega), IMD(omega),
//    Q2, Z, Nu, Pt2, PhiPQ, pi0M}
// For different sets of targets: D, C, Fe, Pb
// For data only (for now)

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir      = proDir + "/out/MakePlots";
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";

// main options
Int_t   dataFlag   = 0;
Int_t   simrecFlag = 0;
Int_t   gsimFlag   = 0;
TString targetOption;
TString kinvarOption = "wM";
Int_t   binNumberZ = 0; // 0: off | [3-7]: on

TCut cutTargType;

TCut cutZ = "";
TString titleZ = "";
TString sufixZBin = "";

TString titleDraw;

TString titleKinvar;
TString titleAxis;
TString histProperties;

TString outPrefix;
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

  // dir structure, just in case
  system("mkdir -p " + outDir);
  
  TCut cutAll = cutDIS && cutPipPim && cutPi0;

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  TH1F *theHist;
  treeExtracted->Draw(kinvarOption + ">>" + outPrefix + histProperties, cutAll && cutTargType && cutZ, "goff");
  theHist = (TH1F *)gROOT->FindObject(outPrefix);
  
  theHist->SetTitleFont(22);
  theHist->SetTitle(titleKinvar + targetOption + titleDraw + titleZ);
  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(3);
  theHist->GetXaxis()->SetTitle(titleAxis);
  theHist->GetYaxis()->SetTitle("Counts");
  theHist->GetYaxis()->SetMaxDigits(3);
  
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
    std::cerr << "Empty command line. Execute ./MakePlots -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hdsgt:k:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'd': dataFlag = 1; break;
    case 's': simrecFlag = 1; break;
    case 'g': gsimFlag = 1; break;
    case 't': targetOption = optarg; break;
    case 'k': kinvarOption = optarg; break;
    case 'z': binNumberZ = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakePlots -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing MakePlots program. The chosen parameters are:" << std::endl;
  std::cout << "  dataFlag     = " << dataFlag << std::endl;
  std::cout << "  simrecFlag   = " << simrecFlag << std::endl;
  std::cout << "  gsimFlag     = " << gsimFlag << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  kinvarOption = " << kinvarOption << std::endl;
  std::cout << "  binNumberZ   = " << binNumberZ << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "MakePlots program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -d" << std::endl;
  std::cout << "    draws data" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -s" << std::endl;
  std::cout << "    draws simrec" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -g" << std::endl;
  std::cout << "    draws gsim" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -k[kinvar]" << std::endl;
  std::cout << "    sets kinvar to draw, it can be: " << std::endl;
  std::cout << "    wM (omega invariant mass)" << std::endl;
  std::cout << "    wD (omega invariant mass difference)" << std::endl;
  std::cout << "    Q2" << std::endl;
  std::cout << "    Nu" << std::endl;
  std::cout << "    Z" << std::endl;
  std::cout << "    Pt2" << std::endl;
  std::cout << "    PhiPQ" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -z[3-7]" << std::endl;
  std::cout << "    turns on binning in Z (off by default) and analyzes that specific bin" << std::endl;
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
  } else if (simrecFlag) {
    outPrefix = "simrec";
    titleDraw = " Reconstructed ";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = simDir + "/jlab/D/comb_simrecD.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = simDir + "/jlab/C/comb_simrecC.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = simDir + "/jlab/Fe/comb_simrecFe.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = simDir + "/usm/Pb/comb_simrecPb.root";
    }
  } else if (gsimFlag) {
    outPrefix = "gsim";
    titleDraw = " Generated ";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = simDir + "/jlab/D/comb_gsimD.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = simDir + "/jlab/C/comb_gsimC.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = simDir + "/jlab/Fe/comb_gsimFe.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = simDir + "/usm/Pb/comb_gsimPb.root";
    }
  }
  // for Z binning
  if (binNumberZ) {
    cutZ = Form("%f < Z && Z < %f", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    titleZ = Form("in (%.02f < Z < %.02f)", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    sufixZBin = Form("-z%d", binNumberZ);
  }
  // for kinvar
  if (kinvarOption == "wM") {
    titleKinvar = "IM(#pi^{+} #pi^{-} #pi^{0}) for ";
    titleAxis = "IM (GeV)";
    histProperties = "(250, 0., 2.5.)";
  } else if (kinvarOption == "wD") {
    titleKinvar = "IMD(#pi^{+} #pi^{-} #pi^{0}) for ";
    titleAxis = "IMD (GeV)";
    histProperties = "(200, 0., 1.6)";
  } else if (kinvarOption == "Q2") {
    titleKinvar = "Q^{2} for ";
    titleAxis = "Q^{2} (GeV^{2})";
    histProperties = "(100, 1., 4.)";  
  } else if (kinvarOption == "Nu") {
    titleKinvar = "#nu for ";
    titleAxis = "#nu (GeV)";
    histProperties = "(200, 2.2, 4.2)";
  } else if (kinvarOption == "Z") {
    titleKinvar = "Z for ";
    titleAxis = "Z";
    histProperties = "(100, 0., 1.2)";
  } else if (kinvarOption == "Pt2") {
    titleKinvar = "p_{T}^{2} for ";
    titleAxis = "p_{T}^{2} (GeV^{2})";
    histProperties = "(100, 0., 1.5)";
  } else if (kinvarOption == "PhiPQ") {
    titleKinvar = "#phi_{PQ} for ";
    titleAxis = "#phi_{PQ} (degrees)";
    histProperties = "(100, -180, 180.)";
  } else if (kinvarOption == "pi0M") {
    titleKinvar = "IM(#gamma #gamma) for ";
    titleAxis = "IM (GeV)";
    histProperties = "(100, 0, 1.6)";
  } 
  // output name
  plotFile = outDir + "/" + outPrefix + "-" + targetOption + "-" + kinvarOption + sufixZBin + ".png";
}
