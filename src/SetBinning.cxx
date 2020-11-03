/**************************************/
/* SetBinning.cxx                     */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// November 2020

#include "analysisConfig.h"

/*** Global variables ***/

TString inputDir  = workDir + "/FilterNCombine/data";
TString outputDir = workDir + "/SetBinning";

TString targetOption;
Int_t   Nbins;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();

int main(int argc, char **argv) {
  
  parseCommandLine(argc, argv);
  printOptions();

  // just in case
  system("mkdir -p " + outputDir);
  
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

  // create and open output file
  TString outputFile = outputDir + "/binning_data-" + targetOption + "_" + Form("%d", Nbins) + "bins.root";
  TFile *rootOutputFile = new TFile(outputFile, "RECREATE");

  /*** CUTS DEFINITION ***/
  
  TCut cutDATA = cutDIS && cutPi0 && cutPipPim && cutVertex;

  // define arrays and hist
  TString kinvarIndex[4]    = {"Q", "N", "Z", "P"};
  TString kinvarName[4]     = {"Q2", "Nu", "Z", "Pt2"};
  TString kinvarOption[4]   = {"Q2", "Nu", "wZ_corr", "wPt2_corr"};
  TString histProperties[4] = {"(100, 1.0, 4.0)", "(100, 2.2, 4.2)", "(100, 0.5, 1.0)", "(100, 0.0, 1.5)"};
  TString currentHistName;
  TH1F   *dataHist;

  // iterate on the kinematic variables
  for (Int_t k = 0; k < 4; k++) {

    currentHistName = "BINNING_" + targetOption + "_" + kinvarIndex[k];
    treeExtracted->Draw(kinvarOption[k] + ">>" + currentHistName + histProperties[k], cutDATA, "goff");
    dataHist = (TH1F *)gROOT->FindObject(currentHistName);

    // hist config
    dataHist->SetTitle("Binning for " + kinvarName[k] + " in " + targetOption + " DATA");
    dataHist->SetLineColor(kBlack);
    dataHist->SetLineWidth(2);
    dataHist->GetXaxis()->SetTitle(kinvarName[k]);
    dataHist->GetXaxis()->CenterTitle();
    dataHist->GetYaxis()->SetTitle("Counts");
    dataHist->GetYaxis()->CenterTitle();
    dataHist->GetYaxis()->SetMaxDigits(3);
    
    dataHist->Write();
    
    /*** Quantile stuff ***/
    
    TCanvas *c = new TCanvas(currentHistName + ".c", currentHistName + ".c", 1000, 1000); 
    c->SetGrid();

    dataHist->Draw("HIST");
    
    Double_t xq[Nbins]; // percentages
    Double_t yq[Nbins]; // output array
    for (Int_t i = 0; i < Nbins; i++) {
      xq[i] = Double_t(i+1)/Nbins;
      dataHist->GetQuantiles(Nbins, yq, xq);
      // print information
      if (i == 0) std::cout << "Edges: " << dataHist->GetBinLowEdge(1) << ", " << yq[i] << ", ";
      else if (i == (Nbins - 1)) std::cout << yq[i] << std::endl;
      else std::cout << yq[i] << ", ";
      // draw line
      if (i != (Nbins - 1)) drawVerticalLine(yq[i], kRed, "dash");
    }

    c->Write();
  } // end of loop in kinvars
  
  // close file
  rootOutputFile->Close();

  std::cout << std::endl;
  std::cout << "This file has been created: " << outputFile << std::endl;
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./SetBinning -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:n:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'n': Nbins = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./SetBinning -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing SetBinning program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  Nbins        = " << Nbins << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "SetBinning program. This program sets the binning. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./SetBinning -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./SetBinning -t[target]" << std::endl;
  std::cout << "    selects target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./SetBinning -n[number]" << std::endl;
  std::cout << "    sets number of bins" << std::endl;
  std::cout << std::endl;
}
