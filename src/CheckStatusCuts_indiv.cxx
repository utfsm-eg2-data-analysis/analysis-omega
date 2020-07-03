/**************************************/
/* CheckStatusCuts_indiv.cxx          */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir      = proDir + "/out/CheckStatusCuts";
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";

// main options
Int_t   dataFlag   = 0;
Int_t   simrecFlag = 0;
Int_t   gsimFlag   = 0;
TString targetOption;
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
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  TH1F *theHist;
  treeExtracted->Draw("wSD_corr>>hist" + histProperties, cutDIS && cutPipPim && cutPi0 && cutTargType && cutZ, "goff");
  theHist = (TH1F *)gROOT->FindObject("hist");
  
  theHist->SetTitleFont(22);
  theHist->SetTitle(titleKinvar + targetOption + titleDraw + titleZ);
  theHist->SetLineColor(kOrange+3);
  theHist->SetLineWidth(3);
  
  theHist->GetXaxis()->SetTitle(titleAxis);
  // theHist->GetYaxis()->SetTitle("Counts");
  theHist->GetYaxis()->SetMaxDigits(3);
  
  TCut statusCuts_electrons = "StatusEl > 0 && StatCCEl > 0 && StatSCEl > 0 && StatDCEl > 0 && StatECEl > 0 && DCStatusEl > 0 && SCStatusEl == 33";

  TCut statusCuts_pip = "Status[2] > 0 && Status[2] < 100 && StatDC[2] > 0 && DCStatus[2] > 0";
  TCut statusCuts_pip_le = "P_corr[2] < 2.7 && StatSC[2] > 0";
  TCut statusCuts_pip_he = "P_corr[2] >= 2.7 && Nphe[2] > 25 && StatCC[2] > 0 && Chi2CC[2] < 5./57.3";

  TCut statusCuts_pim = "Status[3] > 0 && Status[3] < 100 && StatDC[3] > 0 && DCStatus[3] > 0";
  TCut statusCuts_pim_le = "P_corr[3] <= 2.5 && !(StatCC[3] > 0 && Nphe[3] > 25)";
  TCut statusCuts_pim_he = "P_corr[3] > 2.5";

  TH1F *hist1;
  treeExtracted->Draw("wSD_corr>>hist1" + histProperties, cutDIS && cutPipPim && cutPi0 && cutTargType && cutZ &&
		                                          statusCuts_electrons, "goff"); // +elstat
  hist1 = (TH1F *)gROOT->FindObject("hist1");

  TH1F *hist2;
  treeExtracted->Draw("wSD_corr>>hist2" + histProperties, cutDIS && cutPipPim && cutPi0 && cutTargType && cutZ &&
		                                          statusCuts_electrons &&
		                                          statusCuts_pip && (statusCuts_pip_le || statusCuts_pip_he), "goff"); // +ppstat
  hist2 = (TH1F *)gROOT->FindObject("hist2");
  

  TH1F *hist3;
  treeExtracted->Draw("wSD_corr>>hist3" + histProperties, cutDIS && cutPipPim && cutPi0 && cutTargType && cutZ &&
		                                          statusCuts_pim && (statusCuts_pim_le || statusCuts_pim_he) &&
   		                                          statusCuts_pip && (statusCuts_pip_le || statusCuts_pip_he) &&
  		                                          statusCuts_electrons, "goff"); // +pmstat
  hist3 = (TH1F *)gROOT->FindObject("hist3");

  
  hist1->SetLineColor(kOrange+7); // +elstat
  hist1->SetLineWidth(3);
  
  hist2->SetLineColor(kOrange+10); // +ppstat
  hist2->SetLineWidth(3);
  
  hist3->SetLineColor(kRed); // +pmstat
  hist3->SetLineWidth(3);

  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768);
  gStyle->SetOptStat(0);
  c->SetGrid();
  
  theHist->Draw("HIST");

  hist1->Draw("HIST SAME");
  hist2->Draw("HIST SAME");
  hist3->Draw("HIST SAME");
    
  drawVerticalLine(0.782, kRed);
  
  c->Print(plotFile); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckStatusCuts_indiv -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'z': binNumberZ = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckStatusCuts_indiv -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing CheckStatusCuts_indiv program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  binNumberZ   = " << binNumberZ << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "CheckStatusCuts_indiv program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_indiv -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_indiv -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_indiv -z[3-7]" << std::endl;
  std::cout << "    turns on binning in Z (off by default) and analyzes that specific bin" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
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
  }
  // for Z binning
  if (binNumberZ) {
    cutZ = Form("%f < wZ_corr && wZ_corr < %f", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);

    titleZ = Form("in (%.02f < wZ_corr < %.02f)", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    sufixZBin = Form("-z%d", binNumberZ);
  }
  // for kinvar
  titleKinvar = "#Delta m(#pi^{+} #pi^{-} #pi^{0}) for ";
  titleAxis = "Reconstructed Mass [GeV]";
  histProperties = "(200, 0., 1.6)";
  // output name
  plotFile = outDir + "/deltam-" + targetOption + sufixZBin + ".png";
}
