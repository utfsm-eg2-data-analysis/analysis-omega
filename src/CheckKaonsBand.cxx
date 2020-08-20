/**************************************/
/* CheckKaonsBand.cxx                 */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

#include "analysisConfig.h"

// options
TString targetOption;

// dir
TString outDir = proDir + "/out/Acceptance";
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";

TString outFile;

// cuts
TCut cutTargType;
TCut cutAll;

inline int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // make dir, just in case
  system("mkdir -p " + outDir);

  // define cuts
  TCut cutAll = cutDIS && cutStatus && cutPi0;

  // extracting tree
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
    
  // define alias
  treeExtracted->SetAlias("pippimM2", "pippimM*pippimM");

  // define hist
  TH1F *dataHist;
  treeExtracted->Draw("pippimM>>data(150, 0., 1.5)", cutAll && cutTargType, "goff"); // 10 MeV per bin
  dataHist = (TH1F *)gROOT->FindObject("data");
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat(0);

  dataHist->SetTitle("m (#pi^{+} #pi^{-}) plot for " + targetOption);
  dataHist->GetYaxis()->SetMaxDigits(3);
  dataHist->GetXaxis()->SetTitle("Reconstructed Mass [GeV]");
  dataHist->GetXaxis()->CenterTitle();

  dataHist->Draw("HIST");

  drawVerticalLine(kMK0, kRed);
  
  c->Print(outFile);
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckKaonsBand -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckKaonsBand -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "CheckKaonsBand program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckKaonsBand -[options] -[more options]" << std::endl;
  std::cout << "  h           : prints help and exit program" << std::endl;
  std::cout << "  t[target]   : select target: D | C | Fe | Pb" << std::endl;
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
    // out
    outFile = outDir + "/kaons-" + targetOption + ".png";
}

void printOptions() {
  std::cout << "Executing CheckKaonsBand program. The chosen options are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}
