/**************************************/
/* CheckVertexCorr_imd.cxx            */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// Plots invariant mass difference for different vertex cuts

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir      = proDir + "/out/CheckVertexCorr";
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";

// target
TString targetOption;

// kinvar binning options
Int_t binNumber = 0; // 0: off | [3-7]: on
Int_t flagZ = 0;
Int_t flagQ2 = 0;
Int_t flagNu = 0;
Int_t flagPt2 = 0;

TCut cutTargType_old;
TCut cutTargType_new;

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

  /*** OLD ***/
  
  TChain *treeAll = new TChain();
  treeAll->Add(inputFile1 + "/mix");
  treeAll->Add(inputFile2 + "/mix");
  treeAll->Add(inputFile3 + "/mix");

  TH1F *histAll;
  treeAll->Draw("wSD_corr>>old(250, 0.0, 2.5)", cutAll && cutStatus && cutTargType_old, "goff");
  histAll = (TH1F *)gROOT->FindObject("old");
  
  histAll->SetTitle("#Delta m(#gamma #gamma #pi^{+} #pi^{-}) in " + targetOption + " Data");
  histAll->GetXaxis()->SetTitle("Reconstructed Mass (GeV)");
  histAll->GetXaxis()->CenterTitle();
  histAll->GetYaxis()->SetTitle("Counts");
  histAll->GetYaxis()->SetMaxDigits(3);

  histAll->SetLineColor(kBlack);
  histAll->SetLineWidth(3);
  histAll->SetFillStyle(0);

  /*** NEW ***/
  
  TH1F *histNew;
  treeAll->Draw("wSD_corr>>new(250, 0.0, 2.5)", cutAll && cutStatus && cutTargType_new, "goff");
  histNew = (TH1F *)gROOT->FindObject("new");
  
  histNew->SetLineColor(kBlue);
  histNew->SetLineWidth(3);
  histNew->SetFillStyle(0);
  
  /*** DRAW ***/
  
  TCanvas *c0 = new TCanvas("c0", "c0", 1366, 768); 
  c0->SetGrid();
  gStyle->SetOptStat(0);
  
  histAll->Draw("HIST");
  histNew->Draw("HIST SAME");

  drawVerticalLine(0.782, kRed);

  c0->Print(plotFile); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckVertexCorr_imd -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:z:q:n:p:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'z': binNumber = atoi(optarg); flagZ = 1; break;
    case 'q': binNumber = atoi(optarg); flagQ2 = 1; break;
    case 'n': binNumber = atoi(optarg); flagNu = 1; break;
    case 'p': binNumber = atoi(optarg); flagPt2 = 1; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckVertexCorr_imd -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing MakePlots program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  binNumber    = " << binNumber << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "MakePlots program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -[z,q,n,p][n]" << std::endl;
  std::cout << "    turns on binning in Z, Q2, Nu or Pt2 and analyzes the specific bin number n" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for targets
  if (targetOption == "D") {
    cutTargType_old = "TargType == 1";
    inputFile1   = dataDir + "/C/comb_dataC.root";
    inputFile2   = dataDir + "/Fe/comb_dataFe.root";
    inputFile3   = dataDir + "/Pb/comb_dataPb.root";
    cutTargType_new = cutTargType_D;
  } else if (targetOption == "C") {
    cutTargType_old = "TargType == 2";
    inputFile1 = dataDir + "/C/comb_dataC.root";
    cutTargType_new = cutTargType_C;
  } else if (targetOption == "Fe") {
    cutTargType_old = "TargType == 2";
    inputFile1 = dataDir + "/Fe/comb_dataFe.root";
    cutTargType_new = cutTargType_Fe;
  } else if (targetOption == "Pb") {
    cutTargType_old = "TargType == 2";
    inputFile1 = dataDir + "/Pb/comb_dataPb.root";
    cutTargType_new = cutTargType_Pb;
  }
  // output name
  plotFile = outDir + "/imd-with-diff-vertexcuts-" + targetOption + ".png";
}
