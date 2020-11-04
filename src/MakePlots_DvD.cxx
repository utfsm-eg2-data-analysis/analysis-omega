/**************************************/
/* MakePlots_DvD.cxx                  */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// November 2020

// "Data vs Data"
// * IM(omega) and IMD(omega) for one target
// * IM for all targets
// * IMD for all targets

#include "analysisConfig.h"

/*** Global variables ***/

TString outputDir = workDir + "/MakePlots";
TString inputDir  = workDir + "/FilterNCombine/data";

TString targetOption;
TString kinvarOption;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();

int main(int argc, char **argv) {
  
  parseCommandLine(argc, argv);
  printOptions();
  
  // main options
  Int_t compareMassesFlag  = 0;
  Int_t compareTargetsFlag = 0;
  
  TString titleDraw = " Data";
  TString outPrefix = "data_vs_data";
  
  TString titleKinvar;
  TString titleAxis = "Reconstructed Mass (GeV)";
  TString histProperties = "(250, 0., 2.5)";
  TString titleCase;

  TString plotFile;

  /*** FIRST CASE ***/

  // a target was selected, so plot IM vs IMD
  if (targetOption != "") {
    compareMassesFlag = 1;
    titleCase = "m vs #Deltam for ";
  }
  
  /*** SECOND CASE ***/

  // a kinvar was selected, so plot all four targets together
  if (kinvarOption != "") {
    compareTargetsFlag = 1;
    titleCase = "All Targets";
  }

  // for kinvar
  if (kinvarOption == "wM") {
    titleKinvar = "m(#gamma#gamma#pi^{+}#pi^{-}) for ";
  } else if (kinvarOption == "wD") {
    titleKinvar = "#Deltam(#gamma#gamma#pi^{+}#pi^{-}) for ";
  }

  // output name
  plotFile = outputDir + "/" + outPrefix + "-" + targetOption + "-" + kinvarOption + ".png";
  
  // dir structure, just in case
  system("mkdir -p " + outputDir);
  
  // define canvas
  TCanvas *c = new TCanvas("c", "c", 1366, 768); 
  gStyle->SetOptStat(0);
  c->SetGrid();
  
  /*** FIRST CASE ***/
  
  if (compareMassesFlag) {

    // set i/o
    TChain *treeExtracted = new TChain();
    TCut cutVertex;
    if (targetOption == "D") { // unified D
      treeExtracted->Add(inputDir + "/C/comb_data-C.root/mix");
      treeExtracted->Add(inputDir + "/Fe/comb_data-Fe.root/mix");
      treeExtracted->Add(inputDir + "/Pb/comb_data-Pb.root/mix");
      cutVertex = "TargType == 1 && Yec > -1.4 && Yec < 1.4";
    } else {
      treeExtracted->Add(inputDir + "/" + targetOption + "/comb_data-" + targetOption + ".root/mix");
      cutVertex = "TargType == 2 && Yec > -1.4 && Yec < 1.4";
    }
    TCut cutDATA = cutDIS && cutPi0 && cutPipPim && cutVertex;
    
    // IMD
    TH1F *theHistB;
    treeExtracted->Draw("wD_corr>>imd" + histProperties, cutDATA, "goff");
    theHistB = (TH1F *)gROOT->FindObject("imd");

    theHistB->SetTitle(titleCase + targetOption + titleDraw);
    theHistB->GetXaxis()->SetTitle(titleAxis);
    theHistB->GetYaxis()->SetTitle("Counts");
    theHistB->GetYaxis()->SetMaxDigits(3);
    theHistB->SetTitleFont(22);

    theHistB->SetFillStyle(0);
    theHistB->SetLineColor(kRed);
    theHistB->SetLineWidth(3);

    // IM
    TH1F *theHistA;
    treeExtracted->Draw("wM_corr>>im" + histProperties, cutDATA, "goff");
    theHistA = (TH1F *)gROOT->FindObject("im");
    
    theHistA->SetFillStyle(0);
    theHistA->SetLineColor(kBlack);
    theHistA->SetLineStyle(kDashed);
    theHistA->SetLineWidth(3);
    
    theHistB->Draw("HIST");
    theHistA->Draw("SAME HIST");

    // line!
    drawVerticalLine(kMomega, kMagenta, "dash");
    
    TLegend *l = new TLegend(0.7, 0.7, 0.9, 0.9);
    l->AddEntry(theHistA, "m", "l");
    l->AddEntry(theHistB, "#Deltam", "l");
    l->Draw();
  }
  
  /*** SECOND CASE ***/

  if (compareTargetsFlag) {

    // set i/o
    TCut cutDATA = cutDIS && cutPi0 && cutPipPim;
    TCut cutVertex_sol = "TargType == 1 && Yec > -1.4 && Yec < 1.4";;
    TCut cutVertex_liq = "TargType == 2 && Yec > -1.4 && Yec < 1.4";;

    TChain *treeExtracted0 = new TChain();
    treeExtracted0->Add(inputDir + "/C/comb_data-C.root/mix");
    treeExtracted0->Add(inputDir + "/Fe/comb_data-Fe.root/mix");
    treeExtracted0->Add(inputDir + "/Pb/comb_data-Pb.root/mix");
    
    TChain *treeExtracted1 = new TChain();
    treeExtracted1->Add(inputDir + "/C/comb_data-C.root/mix");
    
    TChain *treeExtracted2 = new TChain();
    treeExtracted2->Add(inputDir + "/Fe/comb_data-Fe.root/mix");
    
    TChain *treeExtracted3 = new TChain();
    treeExtracted3->Add(inputDir + "/Pb/comb_data-Pb.root/mix");
    
    // deuterium
    TH1F *theHist0;
    treeExtracted0->Draw(kinvarOption + ">>hist0" + histProperties, cutDATA && cutVertex_liq, "goff");
    theHist0 = (TH1F *)gROOT->FindObject("hist0");
    
    theHist0->SetTitle(titleKinvar + titleCase);
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
    treeExtracted2->Draw(kinvarOption + ">>hist2" + histProperties, cutDATA && cutVertex_sol, "goff");
    theHist2 = (TH1F *)gROOT->FindObject("hist2");

    theHist2->SetFillStyle(1);
    theHist2->SetLineColor(kBlue);
    theHist2->SetLineWidth(3);

    theHist2->Draw("SAME HIST");

    // carbon
    TH1F *theHist1;
    treeExtracted1->Draw(kinvarOption + ">>hist1" + histProperties, cutDATA && cutVertex_sol, "goff");
    theHist1 = (TH1F *)gROOT->FindObject("hist1");

    theHist1->SetFillStyle(1);
    theHist1->SetLineColor(kRed);
    theHist1->SetLineWidth(3);

    theHist1->Draw("SAME HIST");
    
    // lead
    TH1F *theHist3;
    treeExtracted3->Draw(kinvarOption + ">>hist3" + histProperties, cutDATA && cutVertex_sol, "goff");
    theHist3 = (TH1F *)gROOT->FindObject("hist3");

    theHist3->SetFillStyle(1);
    theHist3->SetLineColor(kBlack);
    theHist3->SetLineWidth(3);

    theHist3->Draw("SAME HIST");

    // line, new!
    drawVerticalLine(kMomega, kMagenta, "dash");
    
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
    std::cerr << "Empty command line. Execute ./MakePlots_DvD -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:k:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'k': kinvarOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakePlots_DvD -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing MakePlots_DvD program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  kinvarOption = " << kinvarOption << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "MakePlots_DvD program. Usage is:" << std::endl;
  std::cout << "- If you choose a kinvar option, all targets will be drawn." << std::endl;
  std::cout << "- If you choose a target option, an IM and IMD comparison will be drawn." << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots_DvD -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots_DvD -t[target]" << std::endl;
  std::cout << "    (exclusive)" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots_DvD -k[kinvar]" << std::endl;
  std::cout << "    (exclusive)" << std::endl;
  std::cout << "    sets kinvar to draw, it can be: " << std::endl;
  std::cout << "    wM : omega invariant mass" << std::endl;
  std::cout << "    wD : shifted omega invariant mass difference" << std::endl;
  std::cout << std::endl;
}
