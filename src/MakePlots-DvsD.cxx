/**************************************/
/* MakePlots-DvsD.cxx                 */
/*                                    */
/* Created by Andrés Bórquez          */
/*                                    */
/**************************************/

// "data vs data"
// I want to plot simulations:
//   IM(omega) and shifted IMD(omega) for one target
//   IM for all targets
//   IMD for all targets

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir     = proDir + "/out/MakePlots";
TString inputFile1 = dataDir + "/C/comb_C-thickD2.root";
TString inputFile2 = dataDir + "/Fe/comb_Fe-thickD2.root";
TString inputFile3 = dataDir + "/Pb/comb_Pb-thinD2.root";

// main options
Int_t   compareMassesFlag  = 0;
Int_t   compareTargetsFlag = 0;
TString targetOption = "";
TString kinvarOption = "";
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

  // define canvas
  TCanvas *c = new TCanvas("c", "c", 1366, 768); 
  gStyle->SetOptStat(0);
  c->SetGrid();
  
  /*** FIRST CASE ***/
  
  if (compareMassesFlag) {

    TChain *treeExtracted = new TChain();
    treeExtracted->Add(inputFile1 + "/mix");
    treeExtracted->Add(inputFile2 + "/mix");
    treeExtracted->Add(inputFile3 + "/mix");
    
    setAlias(treeExtracted);
    
    // IMD
    TH1F *theHistB;
    treeExtracted->Draw("swD>>imd" + histProperties, cutAll && cutTargType && cutZ, "goff");
    theHistB = (TH1F *)gROOT->FindObject("imd");

    theHistB->SetTitle(titleCase + targetOption + titleDraw + titleZ);
    theHistB->GetXaxis()->SetTitle(titleAxis);
    theHistB->GetYaxis()->SetTitle("Counts");
    theHistB->GetYaxis()->SetMaxDigits(3);
    theHistB->SetTitleFont(22);

    theHistB->SetFillStyle(1);
    theHistB->SetLineColor(kRed);
    theHistB->SetLineWidth(3);

    // IM
    TH1F *theHistA;
    treeExtracted->Draw("wM>>im" + histProperties, cutAll && cutTargType && cutZ, "goff");
    theHistA = (TH1F *)gROOT->FindObject("im");
    
    theHistA->SetFillStyle(0);
    theHistA->SetLineColor(kBlack);
    theHistA->SetLineWidth(3);
    
    theHistB->Draw("HIST");
    theHistA->Draw("SAME HIST");

    // line!
    drawVerticalLineRed(kMomega);
    
    TLegend *l = new TLegend(0.7, 0.7, 0.9, 0.9);
    l->AddEntry(theHistA, "IM", "l");
    l->AddEntry(theHistB, "IMD", "l");
    l->Draw();
  }
  
  /*** SECOND CASE ***/

  if (compareTargetsFlag) {

    TChain *treeExtracted0 = new TChain();
    treeExtracted0->Add(inputFile1 + "/mix");
    treeExtracted0->Add(inputFile2 + "/mix");
    treeExtracted0->Add(inputFile3 + "/mix");
    
    TChain *treeExtracted1 = new TChain();
    treeExtracted1->Add(inputFile1 + "/mix");
    
    TChain *treeExtracted2 = new TChain();
    treeExtracted2->Add(inputFile2 + "/mix");
    
    TChain *treeExtracted3 = new TChain();
    treeExtracted3->Add(inputFile3 + "/mix");

    // set alias for all trees
    setAlias(treeExtracted0);
    setAlias(treeExtracted1);
    setAlias(treeExtracted2);
    setAlias(treeExtracted3);
    
    // deuterium
    TH1F *theHist0;
    treeExtracted0->Draw(kinvarOption + ">>hist0" + histProperties, cutAll && cutTargType && cutZ, "goff");
    theHist0 = (TH1F *)gROOT->FindObject("hist0");
    
    theHist0->SetTitle(titleKinvar + titleCase + titleZ);
    theHist0->GetXaxis()->SetTitle(titleAxis);
    theHist0->GetYaxis()->SetTitle("Counts");
    theHist0->GetYaxis()->SetMaxDigits(3);
    theHist0->SetTitleFont(22);

    theHist0->SetFillStyle(1);
    theHist0->SetLineColor(kGreen+2);
    theHist0->SetLineWidth(3);
    
    theHist0->Draw("HIST");

    // iron
    TH1F *theHist2;
    treeExtracted2->Draw(kinvarOption + ">>hist2" + histProperties, cutAll && cutTargType && cutZ, "goff");
    theHist2 = (TH1F *)gROOT->FindObject("hist2");

    theHist2->SetFillStyle(1);
    theHist2->SetLineColor(kBlue);
    theHist2->SetLineWidth(3);

    theHist2->Draw("SAME HIST");

    // carbon
    TH1F *theHist1;
    treeExtracted1->Draw(kinvarOption + ">>hist1" + histProperties, cutAll && cutTargType && cutZ, "goff");
    theHist1 = (TH1F *)gROOT->FindObject("hist1");

    theHist1->SetFillStyle(1);
    theHist1->SetLineColor(kRed);
    theHist1->SetLineWidth(3);

    theHist1->Draw("SAME HIST");
    
    // lead
    TH1F *theHist3;
    treeExtracted3->Draw(kinvarOption + ">>hist3" + histProperties, cutAll && cutTargType && cutZ, "goff");
    theHist3 = (TH1F *)gROOT->FindObject("hist3");

    theHist3->SetFillStyle(1);
    theHist3->SetLineColor(kBlack);
    theHist3->SetLineWidth(3);

    theHist3->Draw("SAME HIST");

    // line, new!
    drawVerticalLineRed(kMomega);
    
    TLegend *l = new TLegend(0.7, 0.7, 0.85, 0.85);
    l->AddEntry(theHist0, "Deuterium", "l");
    l->AddEntry(theHist2, "Iron", "l");
    l->AddEntry(theHist1, "Carbon", "l");
    l->AddEntry(theHist3, "Lead", "l");
    l->Draw();
  }

  // save file
  c->Print(plotFile); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakePlots-DvsD -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:k:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'k': kinvarOption = optarg; break;
    case 'z': binNumberZ = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakePlots-DvsD -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing MakePlots-DvsD program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  kinvarOption = " << kinvarOption << std::endl;
  std::cout << "  binNumberZ   = " << binNumberZ << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "MakePlots-DvsD program. Usage is:" << std::endl;
  std::cout << "If you choose a kinvar option, all targets will be drawn." << std::endl;
  std::cout << "If you choose a target option, an IM and IMD comparison will be drawn." << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots-DvsD -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots-DvsD -t[target]" << std::endl;
  std::cout << "    (exclusive)" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots-DvsD -k[kinvar]" << std::endl;
  std::cout << "    (exclusive)" << std::endl;
  std::cout << "    sets kinvar to draw, it can be: " << std::endl;
  std::cout << "    wM  : omega invariant mass" << std::endl;
  std::cout << "    wD  : omega invariant mass difference" << std::endl;
  std::cout << "    swD : shifted omega invariant mass difference" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots-DvsD -z[3-7]" << std::endl;
  std::cout << "    turns on binning in Z (off by default) and analyzes that specific bin" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // data
  outPrefix = "data_vs_data";
  titleDraw = " Data";

  /*** FIRST CASE ***/

  // a target was selected, so plot IM vs IMD
  if (targetOption != "") {
    compareMassesFlag = 1;
    titleCase = "IM vs IMD for ";
    titleAxis = "(GeV)";
    histProperties = "(250, 0., 2.5)";
  }
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
  
  /*** SECOND CASE ***/

  // a kinvar was selected, so plot all four targets together
  if (kinvarOption != "") {
    compareTargetsFlag = 1;
    titleCase = "All Targets";
    // all files
    inputFile1 = dataDir + "/C/comb_C-thickD2.root";
    inputFile2 = dataDir + "/Fe/comb_Fe-thickD2.root";
    inputFile3 = dataDir + "/Pb/comb_Pb-thinD2.root";
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
  } else if (kinvarOption == "swD") {
    titleKinvar = "IMD(#pi^{+} #pi^{-} #pi^{0}) for ";
    titleAxis = "IMD (GeV)";
    histProperties = "(250, 0., 2.5)";
  }

  // for Z binning
  if (binNumberZ) {
    cutZ = Form("%f < Z && Z < %f", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    titleZ = Form(" in (%.02f < Z < %.02f)", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    sufixZBin = Form("-z%d", binNumberZ);
  }
  // output name
  plotFile = outDir + "/" + outPrefix + "-" + targetOption + "-" + kinvarOption + sufixZBin + ".png";
}
