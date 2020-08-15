/**************************************/
/* CheckStatusCuts_pip.cxx            */
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
TString targetOption;

TCut cutTargType;

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

  TCut statusCuts_pip_1 = "Status[2] > 0";
  TCut statusCuts_pip_2 = "StatDC[2] > 0";
  TCut statusCuts_pip_3 = "DCStatus[2] > 0";
  /*
  TCut statusCuts_pip_le = "P_corr[2] < 2.7 && StatSC[2] > 0";
  TCut statusCuts_pip_he = "P_corr[2] >= 2.7 && Nphe[2] > 25 && StatCC[2] > 0 && Chi2CC[2] < 5./57.3";
  */
  
  TH1F *hist1;
  treeExtracted->Draw("P_corr[2]>>hist1" + histProperties, cutDIS && cutPipPim && cutPi0 && cutTargType && statusCuts_pip_1, "goff");
  hist1 = (TH1F *)gROOT->FindObject("hist1");

  hist1->SetTitleFont(22);
  hist1->SetTitle(titleKinvar + targetOption + titleDraw);
  
  hist1->GetXaxis()->SetTitle(titleAxis);
  // hist1->GetYaxis()->SetTitle("Counts");
  hist1->GetYaxis()->SetMaxDigits(3);
  
  TH1F *hist2;
  treeExtracted->Draw("P_corr[2]>>hist2" + histProperties, cutDIS && cutPipPim && cutPi0 && cutTargType && statusCuts_pip_1 && statusCuts_pip_2, "goff");
  hist2 = (TH1F *)gROOT->FindObject("hist2");

  TH1F *hist3;
  treeExtracted->Draw("P_corr[2]>>hist3" + histProperties, cutDIS && cutPipPim && cutPi0 && cutTargType && statusCuts_pip_1 && statusCuts_pip_2 && statusCuts_pip_3, "goff");
  hist3 = (TH1F *)gROOT->FindObject("hist3");
  
  hist1->SetLineColor(kBlack);
  hist1->SetLineWidth(3);
  hist1->SetFillStyle(0);
  
  hist2->SetLineColor(kViolet);
  hist2->SetLineWidth(3);
  hist2->SetFillStyle(0);
  
  hist3->SetLineColor(kBlue);
  hist3->SetLineWidth(3);
  hist3->SetFillStyle(0);
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768);
  gStyle->SetOptStat(0);
  c->SetGrid();
  
  hist1->Draw("HIST");
  hist2->Draw("HIST SAME");
  hist3->Draw("HIST SAME");
      
  c->Print(plotFile); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckStatusCuts_pip -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckStatusCuts_pip -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing CheckStatusCuts_pip program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "CheckStatusCuts_pip program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_pip -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_pip -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
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
  // for kinvar
  titleKinvar = "Momentum (#pi^{+}) for ";
  titleAxis = "Momentum [GeV]";
  histProperties = "(300, 0., 3.0)";
  // output name
  plotFile = outDir + "/P-pip-" + targetOption + ".png";
}
