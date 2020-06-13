/***************************************/
/*  CheckStatusCuts.cxx                */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

#include "analysisConfig.h"

#include "TClasTool.h"
#include "TIdentificator.h"

/*** Global variables ***/

TString outDir = proDir + "/out/CheckStatusCut";
TString inputFile;

// options
Int_t simFlag;
Int_t nOption;

TCut pidCut;
TCut statusCuts;
TString treeName;
TString outSufix;
TString outFile;
TString ncHistProperties;
TString wcHistProperties;
TString titleHist;
TString titleAxis;

/*** Declaration of functions ***/

int parseCommandLine(int argc, char* argv[]);
void printUsage();
void printOptions();
void assignOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();
  
  // dir structure, just in case
  system("mkdir -p " + outDir);
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile + "/" + treeName);
  
  TH1F *theHist_nc;
  treeExtracted->Draw(ncHistProperties, pidCut, "goff"); // nc: no cuts
  theHist_nc = (TH1F *)gROOT->FindObject("h_nc");
  
  TH1F *theHist_wc;
  treeExtracted->Draw(wcHistProperties, pidCut && statusCuts, "goff"); // wc: with cuts
  theHist_wc = (TH1F *)gROOT->FindObject("h_wc");
    
  // define histogram and value
  theHist_nc->SetTitle(titleHist); // E
  theHist_nc->GetXaxis()->SetTitle(titleAxis); // gamma, E
  theHist_nc->GetXaxis()->CenterTitle();

  // hist attributes
  theHist_wc->SetFillStyle(0);
  theHist_wc->SetLineColor(kBlue);
  theHist_wc->SetLineWidth(3);

  theHist_nc->SetFillStyle(0);
  theHist_nc->SetLineColor(kRed);
  theHist_nc->SetLineWidth(3);
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  // draw hists
  theHist_nc->Draw("HIST");
  theHist_wc->Draw("HIST SAME");
  
  // legend
  TLegend *legend = new TLegend(0.6, 0.7, 0.8, 0.8); // x1,y1,x2,y2
  legend->AddEntry(theHist_nc, "no cuts", "l");
  legend->AddEntry(theHist_wc, "with Status cuts", "l");
  legend->Draw();
  
  c->Print(outFile);

  // report results
  std::cout << "nEntries nc = " << theHist_nc->GetEntries() << std::endl;
  std::cout << "nEntries wc = " << theHist_wc->GetEntries() << std::endl;
  
  return 0;
}

/*** Functions ***/


inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckStatusCuts -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hn:ds")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'n': nOption = atoi(optarg); break;
    case 'd': simFlag = 0; break;
    case 's': simFlag = 1; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckStatusCuts -h to print help." << std::endl;
      exit(0);
      break;
    }
}

void assignOptions() {
  // data type
  if (!simFlag) {
    outSufix = "data";
    inputFile = "/home/borquez/analysis-omega/out/ToyGST/data/C/prunedC_42011.root";
  } else {
    outSufix = "simrec";
    inputFile = "/home/borquez/analysis-omega/out/ToyGST/old/Fe/prunedFe_00.root";
  }
  // plot option
  if (nOption == 0) { // Q2
    treeName = "ntuple_e";
    statusCuts = "Status > 0 && Status < 100 && StatCC > 0 && StatSC > 0 && StatDC > 0 && StatEC > 0 && DCStatus > 0 && SCStatus == 33";
    pidCut = "Q2 > 1. && Q2 < 4.";
    ncHistProperties = "Q2>>h_nc(300, 1., 4.)";
    wcHistProperties = "Q2>>h_wc(300, 1., 4.)";
    titleAxis = "Q^{2} (GeV^{2})";
    titleHist = "Q^{2}";
    outFile = outDir + "/csc-" + outSufix + "-Q2.png";
  } else if (nOption == 1) { // P(pi+)
    statusCuts = "Status > 0 && Status < 100 && StatDC > 0 && DCStatus > 0 && ((P > 2.7 && StatCC > 0 && Chi2CC < 5/57.3) || (P < 2.7 && StatSC > 0))";
    pidCut = "pid == 211 && P > 0. && P < 3.";
    ncHistProperties = "P>>h_nc(300, 0., 3.)";
    wcHistProperties = "P>>h_wc(300, 0., 3.)";
    titleAxis = "P (GeV) && P > 0. && P < 3.";
    titleHist = "P(#pi^{+})"; 
    outFile = outDir + "/csc-" + outSufix + "-P-pip.png";
  } else if (nOption == 2) { // P(pi-)
    statusCuts = "Status > 0 && Status < 100 && StatDC > 0 && DCStatus > 0";
    pidCut = "pid == -211 && P > 0. && P < 3.";
    ncHistProperties = "P>>h_nc(300, 0., 3.)";
    wcHistProperties = "P>>h_wc(300, 0., 3.)";
    titleAxis = "P (GeV)";
    titleHist = "P(#pi^{-})"; 
    outFile = outDir + "/csc-" + outSufix + "-P-pim.png";
  } else if (nOption == 3) { // P(gamma)
    statusCuts = "ECStatus > 0 && StatEC > 0";
    pidCut = "pid == 22 && P > 0. && P < 3.";
    ncHistProperties = "P>>h_nc(300, 0., 3.)";
    wcHistProperties = "P>>h_wc(300, 0., 3.)";
    titleAxis = "P (GeV)";
    titleHist = "P(#gamma)"; 
    outFile = outDir + "/csc-" + outSufix + "-P-gamma.png";
  } else if (nOption == 4) { // Etrue(gamma)
    statusCuts = "ECStatus > 0 && StatEC > 0";
    pidCut = "pid == 22 && (TMath::Max(Etot, Ein+Eout)/0.272) > 0. && (TMath::Max(Etot, Ein+Eout)/0.272) < 3.";
    ncHistProperties = "(TMath::Max(Etot, Ein+Eout)/0.272)>>h_nc(300, 0., 3.)";
    wcHistProperties = "(TMath::Max(Etot, Ein+Eout)/0.272)>>h_wc(300, 0., 3.)";
    titleAxis = "E_{true} (GeV)";
    titleHist = "E_{true} (#gamma)";
    outFile = outDir + "/csc-" + outSufix + "-Etrue-gamma.png";
  }else if (nOption == 5) { // P(gamma)
    statusCuts = "Status > 0 && Status < 100 && ECStatus > 0 && StatEC > 0";
    pidCut = "pid == 22 && P > 0. && P < 3.";
    ncHistProperties = "P>>h_nc(300, 0., 3.)";
    wcHistProperties = "P>>h_wc(300, 0., 3.)";
    titleAxis = "P (GeV)";
    titleHist = "P(#gamma)"; 
    outFile = outDir + "/csc-" + outSufix + "-P-gamma_v2.png";
  } else if (nOption == 6) { // Etrue(gamma)
    statusCuts = "Status > 0 && Status < 100 && ECStatus > 0 && StatEC > 0";
    pidCut = "pid == 22 && (TMath::Max(Etot, Ein+Eout)/0.272) > 0. && (TMath::Max(Etot, Ein+Eout)/0.272) < 3.";
    ncHistProperties = "(TMath::Max(Etot, Ein+Eout)/0.272)>>h_nc(300, 0., 3.)";
    wcHistProperties = "(TMath::Max(Etot, Ein+Eout)/0.272)>>h_wc(300, 0., 3.)";
    titleAxis = "E_{true} (GeV)";
    titleHist = "E_{true} (#gamma)";
    outFile = outDir + "/csc-" + outSufix + "-Etrue-gamma_v2.png";
  }
  // overwrite
  if (nOption > 0) {
    if (simFlag) treeName = "ntuple_sim";
    else treeName = "ntuple_data";
  }
}

void printUsage() {
  std::cout << "CheckStatusCuts program." << std::endl;
  std::cout << "Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -h" << std::endl;
  std::cout << "    prints this message and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -n(0,1,2,3,4)" << std::endl;
  std::cout << "    plots different comparisons" << std::endl;
  std::cout << "    0 : Q2" << std::endl;
  std::cout << "    1 : P(pi-)" << std::endl;
  std::cout << "    2 : P(pi+)" << std::endl;
  std::cout << "    3 : P(gamma)" << std::endl;
  std::cout << "    4 : Etrue(gamma)" << std::endl;
  std::cout << "    5 : P(gamma)_v2" << std::endl;
  std::cout << "    6 : Etrue(gamma)_v2" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -d" << std::endl;
  std::cout << "    plots data" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -s" << std::endl;
  std::cout << "    plots reconstructed" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing FilterNCombine program. The chosen parameters are: " << std::endl;
  std::cout << "  nOption = " << nOption << std::endl;
  std::cout << "  simFlag = " << simFlag << std::endl;
  std::cout << std::endl;
}
