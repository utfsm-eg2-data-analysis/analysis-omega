/**************************************/
/* GetQuantiles.cxx                   */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/GetQuantiles";

TString inputFile1;
TString inputFile2;
TString inputFile3;

// parameters
TString targetOption;
TString kinvarOption;
Int_t   Nquantiles;

// cuts
TCut cutAll = cutDIS && cutPipPim && cutPi0;
TCut cutTargType;

TString dataPrefix;
TString kinvarTitle;
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

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  TH1F *dataHist;
  treeExtracted->Draw(kinvarOption + ">>data" + histProperties, cutAll && cutTargType, "goff");
  dataHist = (TH1F *)gROOT->FindObject("data");

  dataHist->SetTitle(kinvarTitle + targetOption);
  dataHist->SetLineColor(kBlack);
  dataHist->SetLineWidth(2);
  dataHist->GetXaxis()->SetTitle(kinvarOption);
  dataHist->GetXaxis()->CenterTitle();
  dataHist->GetYaxis()->SetTitle("Counts");
  dataHist->GetYaxis()->CenterTitle();
  dataHist->GetYaxis()->SetMaxDigits(3);
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768); 
  c->SetGrid();

  // because Nu is special...
  if (kinvarOption == "Nu") {
    gStyle->SetStatX(0.30);
    gStyle->SetStatY(0.85);
  }
  
  dataHist->Draw();

  /*** Quantile stuff ***/
  
  Double_t xq[Nquantiles]; // percentages
  Double_t yq[Nquantiles]; // output array
  for (Int_t i = 0; i < Nquantiles; i++) {
    xq[i] = Double_t(i+1)/Nquantiles;
    dataHist->GetQuantiles(Nquantiles, yq, xq);
    // print information --> IMPORTANT
    if (i == 0) std::cout << "Edges: " << dataHist->GetBinLowEdge(1) << ", " << yq[i] << ", ";
    else if (i == (Nquantiles - 1)) std::cout << yq[i] << std::endl;
    else std::cout << yq[i] << ", ";
    // draw line
    if (i != (Nquantiles - 1)) drawVerticalLine(yq[i], kRed, "dash");
  }

  c->Print(plotFile); // output file
  
  delete c;
  delete dataHist;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./GetQuantiles -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:k:q:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'k': kinvarOption = optarg; break;
    case 'q': Nquantiles = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./GetQuantiles -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing GetQuantiles program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  kinvarOption = " << kinvarOption << std::endl;
  std::cout << "  Nquantiles   = " << Nquantiles << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "GetQuantiles program. This program obtains binning. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetQuantiles -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetQuantiles -t[target]" << std::endl;
  std::cout << "    selects target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetQuantiles -k[kinvar]" << std::endl;
  std::cout << "    selects kinvar: Q2, Nu, Z, Pt2" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetQuantiles -q[number]" << std::endl;
  std::cout << "    sets the number of quantiles" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
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
  // for kinvar
  if (kinvarOption == "Z") {
    histProperties = "(100, 0.5, 1.0)";
  } else if (kinvarOption == "Pt2") {
    histProperties = "(100, 0.0, 1.5)";
  } else if (kinvarOption == "Q2") {
    histProperties = "(100, 1.0, 4.0)";
  } else if (kinvarOption == "Nu") {
    histProperties = "(100, 2.2, 4.2)";
  }
  kinvarTitle = kinvarOption + " binning for ";
  // name
  plotFile = outDir + Form("/q%d-", Nquantiles) + kinvarOption + "-" + targetOption + ".png";
}
