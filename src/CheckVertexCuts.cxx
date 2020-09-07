/**************************************/
/* CheckVertexCuts.cxx                */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// plots electron's vertex for simulations
// for data, there are two different cuts
// - HH cuts, which are sector dependent and are applied on uncorr vertex
// - TM cuts, which depend on target and are applied on corr vertex

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/CheckVertexCuts";
TString inputFile1 = "";
TString inputFile2 = "";
TString inputFile3 = "";

// options
TString targetOption;
Int_t dataFlag, simrecFlag, gsimFlag;
Int_t nSector = -1; // default
TString runNumber;

TString dataOption;
TString sufixSector = "";

// titles
TString titleDraw;
TString titleSector = "";

// cuts
TCut cutAll;
TCut cutTargType = "";
TCut cutSector = "";

// variables
TString varVertex;
TString varAxisTitle;

TString plotFile;
TString rootFile;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // dir structure, just in case
  system("mkdir -p " + outDir);

  // setting HH vertex cuts (taken from ext/Analyser/src/TIdentificator.cxx)
  // - they're sector dependent but target independent -
  Double_t ele_liq_lim_HH[6][2];
  ele_liq_lim_HH[0][0] = -32.5;
  ele_liq_lim_HH[0][1] = -28;
  ele_liq_lim_HH[1][0] = -32.5;
  ele_liq_lim_HH[1][1] = -27.5;
  ele_liq_lim_HH[2][0] = -32;
  ele_liq_lim_HH[2][1] = -27.25;
  ele_liq_lim_HH[3][0] = -32;
  ele_liq_lim_HH[3][1] = -27.75;
  ele_liq_lim_HH[4][0] = -32.5;
  ele_liq_lim_HH[4][1] = -28.35;
  ele_liq_lim_HH[5][0] = -33.5;
  ele_liq_lim_HH[5][1] = -28.75;

  Double_t ele_sol_low_HH[6];
  ele_sol_low_HH[0] = -26.5;
  ele_sol_low_HH[1] = -26.;
  ele_sol_low_HH[2] = -25.65;
  ele_sol_low_HH[3] = -25.85;
  ele_sol_low_HH[4] = -26.65;
  ele_sol_low_HH[5] = -27.15;
  
  Double_t ele_sol_high_HH = -20;

  // setting TM vertex cuts (taken from ext/write_tree/write_tree_sm.cxx)
  // - they're target dependent but sector independent -  
  Double_t ele_liq_lim_TM[2];
  Double_t ele_sol_lim_TM[2];
  if (targetOption == "C") {
    ele_liq_lim_TM[0] = -31.8;
    ele_liq_lim_TM[1] = -28.4;
    ele_sol_lim_TM[0] = -25.33;
    ele_sol_lim_TM[1] = -24.10;
  } else if (targetOption == "Fe") {
    ele_liq_lim_TM[0] = -31.8;
    ele_liq_lim_TM[1] = -28.4;
    ele_sol_lim_TM[0] = -25.65;
    ele_sol_lim_TM[1] = -24.26;
  } else if (targetOption == "Pb") {
    ele_liq_lim_TM[0] = -31.8;
    ele_liq_lim_TM[1] = -28.4;
    ele_sol_lim_TM[0] = -25.54;
    ele_sol_lim_TM[1] = -24.36;
  }

  // setting cuts
  cutAll = cutDIS && cutPi0 && cutPipPim;

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/original");
  treeExtracted->Add(inputFile2 + "/original");
  treeExtracted->Add(inputFile3 + "/original");
    
  TH1F *theHist;
  treeExtracted->Draw(varVertex + ">>hist(300, -35., -20.)", cutSector, "goff");
  theHist = (TH1F *)gROOT->FindObject("hist");
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 769);
  c->SetTickx(1);
  c->SetTicky(1);
  gStyle->SetOptStat(0);
  
  theHist->SetTitle("Electron Vertex for " + targetOption + titleDraw + titleSector);
  theHist->GetYaxis()->SetTitle("Counts");
  theHist->GetYaxis()->SetMaxDigits(3);
  theHist->GetXaxis()->SetTitle(varAxisTitle);
  theHist->GetXaxis()->CenterTitle();
  theHist->SetContour(99);

  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(2);
  theHist->SetFillStyle(0);
  
  theHist->Draw("HIST");

  // show vertex cuts
  // if ((dataFlag && nSector > -1 && targetOption == "All") || (!dataFlag && nSector > -1)) {
  if ((dataFlag && nSector > -1) || (!dataFlag && nSector > -1)) {
    drawVerticalLine(ele_liq_lim_HH[nSector][0], kRed);
    drawVerticalLine(ele_liq_lim_HH[nSector][1], kRed);
    drawVerticalLine(ele_sol_low_HH[nSector], kRed);
    drawVerticalLine(ele_sol_high_HH, kRed);
  } else if (nSector == -1 && targetOption != "All") {
    drawVerticalLine(ele_liq_lim_TM[0], kRed);
    drawVerticalLine(ele_liq_lim_TM[1], kRed);
    drawVerticalLine(ele_sol_lim_TM[0], kRed);
    drawVerticalLine(ele_sol_lim_TM[1], kRed);
  }
  
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
    std::cerr << "Empty command line. Execute ./CheckVertexCuts -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hg:s:d:S:r:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'd': targetOption = optarg; dataFlag = 1; break;
    case 's': targetOption = optarg; simrecFlag = 1; break;
    case 'g': targetOption = optarg; gsimFlag = 1; break;
    case 'S': nSector = atoi(optarg); break;
    case 'r': runNumber = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckVertexCuts -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "PlotSim_Vertex program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./PlotSim_Vertex -h" << std::endl;
  std::cout << "  prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./PlotSim_Vertex -[d,g,s][target]" << std::endl;
  std::cout << "  selects target: D | C | Fe | Pb | All" << std::endl;
  std::cout << std::endl;  
  std::cout << "./PlotSim_Vertex -S[sector]" << std::endl;
  std::cout << "  selects sector: (0 - 5)" << std::endl;
  std::cout << std::endl;  
  std::cout << "./PlotSim_Vertex -r[rn]" << std::endl;
  std::cout << "  selects run number" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing PlotSim_Vertex program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  dataOption   = " << dataOption << std::endl;
  std::cout << "  nSector      = " << nSector << std::endl;
  std::cout << "  runNumber    = " << runNumber << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for kind of data
  if (dataFlag) {
    dataOption = "data";
    titleDraw = " Data";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = dataDir + "/C/comb_dataC.root";
      inputFile2 = dataDir + "/Fe/comb_dataFe.root";
      inputFile3 = dataDir + "/Pb/comb_dataPb.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/C/comb_dataC.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/Fe/comb_dataFe.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/Pb/comb_dataPb.root";
    } else if (targetOption == "All") {
      cutTargType = "TargType == 1 || TargType == 2";
      inputFile1 = dataDir + "/C/comb_dataC.root";
      inputFile2 = dataDir + "/Fe/comb_dataFe.root";
      inputFile3 = dataDir + "/Pb/comb_dataPb.root";
    }
  } else if (simrecFlag) {
    dataOption = "simrec";
    titleDraw = " Simrec";
    inputFile1 = "comb" + targetOption + "_" + runNumber + ".root";
  } else if (gsimFlag) {
    dataOption = "gsim";
    titleDraw = " Gsim";
    inputFile1 = "comb" + targetOption + "_" + runNumber + ".root";
  }
  // for variables
  if (dataFlag || simrecFlag) {
    if (nSector > -1) {
      varVertex = "Ze";
      varAxisTitle = "Z (cm)";      
    } else {
      varVertex = "Zec";
      varAxisTitle = "Z_corr (cm)";
    }
  } else if (gsimFlag) {
    varVertex = "mc_Ze";
    varAxisTitle = "Z (cm)";
  }
  // sector
  if (nSector > -1) {
    sufixSector = Form("_sector%d", nSector);
    titleSector = Form(" (Sector = %d)", nSector);
    if (dataFlag || simrecFlag) cutSector = Form("SectorEl == %d", nSector);
    else if (gsimFlag) cutSector = Form("mc_SectorEl == %d", nSector);
  }
  // for outdir
  if (!dataFlag) outDir = ".";
  // names
  plotFile = outDir + "/vertex-" + targetOption + "_" + dataOption + sufixSector + ".png";
  rootFile = outDir + "/vertex-" + targetOption + "_" + dataOption + sufixSector + "_" + runNumber + ".root";
}
