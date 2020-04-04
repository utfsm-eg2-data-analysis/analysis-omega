/**************************************/
/* MakePlots-2D.cxx                   */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// draws different 2D plots
// im interested in: data-Q2:Nu, data-Pt2:Z, simrec-Q2:Nu, simrec-Pt2:Z

#include "analysisConfig.h"

/*** Global variables ***/

TString inputFolder = proFolder +  "/out/filterData";
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";
TString outFolder   = proFolder + "/out/MakePlots";

// options
Int_t dataFlag = 0;
Int_t simFlag = 0;
TString targetOption;
TString XOption;
TString YOption;
Int_t binNumberZ = 0;

// cuts
TCut cutAll;
TCut cutTargType;
TCut cutZ = "";

TString XAxis;
TString YAxis;
TString XHistProp;
TString YHistProp;
TString histProperties;

// name scheme
TString outPrefix;
TString titleDraw;
TString titleZ;
TString sufixZBin;
TString outputPlotName;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // setting cuts
  cutAll = cutDIS_old && cutPi0_old && cutPipPim_old;

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/outdata");
  treeExtracted->Add(inputFile2 + "/outdata");
  treeExtracted->Add(inputFile3 + "/outdata");
  
  setAlias_old(treeExtracted);
  
  TH2F *theHist;
  treeExtracted->Draw(YOption + ":" + XOption + ">>" + outPrefix + histProperties, cutAll && cutTargType && cutZ, "goff");
  theHist = (TH2F *)gROOT->FindObject(outPrefix);
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768);
  c->SetTickx(1);
  c->SetTicky(1);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1, 0);

  theHist->SetTitle(YOption + ":" + XOption + " for " + targetOption + titleDraw + titleZ);
  theHist->GetYaxis()->SetTitle(YAxis);
  theHist->GetXaxis()->SetTitle(XAxis);
  theHist->GetYaxis()->CenterTitle();
  theHist->GetXaxis()->CenterTitle();
  theHist->SetContour(99);
  theHist->Draw("COLZ");
  
  gPad->SetLogz(); // important
  
  c->Print(outputPlotName); // output file
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakePlots-2D -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hdst:x:y:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'd': dataFlag = 1; break;
    case 's': simFlag = 1; break;
    case 't': targetOption = optarg; break;
    case 'x': XOption = optarg; break;
    case 'y': YOption = optarg; break;
    case 'z': binNumberZ = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakePlots-2D -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "MakePlots-2D program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots-2D -[options] -[more options]" << std::endl;
  std::cout << "  h           : prints help and exit program" << std::endl;
  std::cout << "  d           : draw data (default)" << std::endl;
  std::cout << "  s           : draw simrec" << std::endl;
  std::cout << "  t[target]   : selects target: D | C | Fe | Pb" << std::endl;
  std::cout << "  x[kinvar]   : sets kinvar to draw in X axis" << std::endl;
  std::cout << "  y[kinvar]   : sets kinvar to draw in Y axis" << std::endl;
  std::cout << "  z[3-7]      : select Z bin" << std::endl;
  std::cout << std::endl;
  std::cout << "  Variables are:" << std::endl;
  std::cout << "      Q2" << std::endl;
  std::cout << "      Nu" << std::endl;
  std::cout << "      Z" << std::endl;
  std::cout << "      Pt2" << std::endl;
}


void assignOptions() {
  // for kind of data
  if (dataFlag) {
    outPrefix = "data";
    titleDraw = " Data";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = inputFolder + "/C/wout_C-thickD2.root";
      inputFile2 = inputFolder + "/Fe/wout_Fe-thickD2.root";
      inputFile3 = inputFolder + "/Pb/wout_Pb-thinD2.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/C/wout_C-thickD2.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/Fe/wout_Fe-thickD2.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/Pb/wout_Pb-thinD2.root";
    }
  } else if (simFlag) {
    outPrefix = "simrec";
    titleDraw = " Reconstructed";
    inputFolder = proFolder + "/out/filterSim/simrec";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = inputFolder + "/jlab/D/wout_simrecD.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/jlab/C/wout_simrecC.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/jlab/Fe/wout_simrecFe.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = inputFolder + "/usm/Pb/wout_simrecPb.root";
    }
  }
  // x variable
  if (XOption == "Q2") {
    XAxis = "Q^{2} (GeV^{2})";
    XHistProp = "200, 1., 4.";
  } else if (XOption == "Nu") {
    XAxis = "#nu (GeV)";
    XHistProp = "200, 2.2, 4.2";
  } else if (XOption == "Z") {
    XAxis = "Z";
    XHistProp = "200, 0., 1.5";
  } else if (XOption == "Pt2") {
    XAxis = "p_{T}^{2} (GeV^{2})";
    XHistProp = "200, 0., 1.5";
  }
  // y variable
  if (YOption == "Q2") {
    YAxis = "Q^{2} (GeV^{2})";
    YHistProp = "200, 1., 4.";
  } else if (YOption == "Nu") {
    YAxis = "#nu (GeV)";
    YHistProp = "200, 2.2, 4.2";
  } else if (YOption == "Z") {
    YAxis = "Z";
    YHistProp = "200, 0., 1.5";
  } else if (YOption == "Pt2") {
    YAxis = "p_{T}^{2} (GeV^{2})";
    YHistProp = "200, 0., 1.5";
  }
  histProperties = "(" + XHistProp + ", " + YHistProp + ")";
  // for z
  if (binNumberZ) {
    Double_t lowEdgeZ = edgesZ[binNumberZ-3];
    Double_t highEdgeZ = edgesZ[binNumberZ-3+1];
    cutZ = Form("%f < Z && Z < %f", lowEdgeZ, highEdgeZ);
    titleZ = Form(" in (%.02f < Z < %.02f)", lowEdgeZ, highEdgeZ);
    sufixZBin = Form("-z%d", binNumberZ);
  }
  // names
  outputPlotName = outFolder + "/" + outPrefix + "-" + targetOption + "-" + YOption + "_vs_" + XOption + sufixZBin + ".png";
}

void printOptions() {
  std::cout << "Executing MakePlots-2D program. Chosen parameters are:" << std::endl;
  std::cout << "  dataFlag=" << dataFlag << std::endl;
  std::cout << "  simFlag=" << simFlag << std::endl;
  std::cout << "  targetOption=" << targetOption << std::endl;
  std::cout << "  XOption=" << XOption << std::endl;
  std::cout << "  YOption=" << YOption << std::endl;
  if (binNumberZ) std::cout << "  binNumberZ=" << binNumberZ << std::endl;
}
