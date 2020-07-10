/**************************************/
/* CheckBkg_f1.cxx                    */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// (Suggestion of WB)
// This program wants to check if f1(1285) is one of the reasons for the huge bkg
// in the omega invariant mass difference spectrum.

#include "analysisConfig.h"

// main options
TString outDir = proDir + "/out/CheckBkg";

// target option
TString targetOption;
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";
TCut    cutTargType;
TString plotFile;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

/*** Program ***/

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // dir structure, just in case
  system("mkdir -p " + outDir);
  
  // read data
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  // first hist, no cut at all
  TH1F *theHist;
  treeExtracted->Draw("wSD_corr>>theHist(200, 0, 2.5)", cutTargType && cutDIS && cutPipPim && cutPi0 &&
                                                        statusElectron &&
                                                        statusPip && // (statusPip_LE || statusPip_HE) &&
                                                        statusPim, "goff"); // cutBinLimits && cutQuality // && (statusPim_LE || statusPim_HE)
  theHist = (TH1F *)gROOT->FindObject("theHist");
  
  theHist->SetTitle("#Delta m (#gamma #gamma #pi^{+} #pi^{-}) in " + targetOption + " data");
  theHist->SetLineColor(kBlack);
  theHist->SetFillStyle(0);
  theHist->SetLineWidth(3);
  theHist->GetXaxis()->SetTitle("Reconstructed Mass [GeV]");
  theHist->GetXaxis()->CenterTitle();
  theHist->GetYaxis()->SetMaxDigits(3);

  // second hist, exact omegas: omega -> gamma gamma pi+ pi-
  TCut exactOmega = "nGamma == 2 && nPip == 1 && nPim ==2";
  
  TH1F *theHist2;
  treeExtracted->Draw("wSD_corr>>theHist2(200, 0, 2.5)", cutTargType && cutDIS && cutPipPim && cutPi0 &&
		                                         statusElectron &&
		                                         statusPip &&
		                                         statusPim &&
		                                         exactOmega, "goff");
  theHist2 = (TH1F *)gROOT->FindObject("theHist2");
  
  theHist2->SetLineColor(kGreen+2);
  theHist2->SetFillStyle(0);
  theHist2->SetLineWidth(3);

  // third hist, first f1 decay: f1 -> pi0 pi0 pi+ pi-
  TCut f1_decay1 = "nGamma >= 4";
  
  TH1F *theHist3;
  treeExtracted->Draw("wSD_corr>>theHist3(200, 0, 2.5)", cutTargType && cutDIS && cutPipPim && cutPi0 &&
		                                         statusElectron &&
		                                         statusPip &&
		                                         statusPim &&
		                                         f1_decay1, "goff");
  theHist3 = (TH1F *)gROOT->FindObject("theHist3");
  
  theHist3->SetLineColor(kBlue);
  theHist3->SetFillStyle(0);
  theHist3->SetLineWidth(3);

  // fourth hist, checking omega beta
  TH1F *theHist4;
  treeExtracted->Draw("wSD_corr>>theHist4(200, 0, 2.5)", cutTargType && cutDIS && cutPipPim && cutPi0 &&
		                                         statusElectron &&
		                                         statusPip &&
		                                         statusPim &&
		                                         betaOmega, "goff");
  theHist4 = (TH1F *)gROOT->FindObject("theHist4");
  
  theHist4->SetLineColor(kMagenta+7);
  theHist4->SetFillStyle(0);
  theHist4->SetLineWidth(3);

  // fourth hist, checking absence of neutral kaon band and omega beta
  TH1F *theHist5;
  treeExtracted->Draw("wSD_corr>>theHist5(200, 0, 2.5)", cutTargType && cutDIS && cutPi0 &&
		                                         statusElectron &&
		                                         statusPip &&
		                                         statusPim &&
		                                         betaOmega, "goff");
  theHist5 = (TH1F *)gROOT->FindObject("theHist5");
  
  theHist5->SetLineColor(kMagenta+3);
  theHist5->SetFillStyle(0);
  theHist5->SetLineWidth(3);
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 1366);
  gStyle->SetOptStat(0);
  c->SetTickx(1);
  c->SetTicky(1);
  
  theHist->Draw("HIST");
  theHist2->Draw("SAME HIST");
  theHist3->Draw("SAME HIST");
  theHist4->Draw("SAME HIST");
  theHist5->Draw("SAME HIST");
    
  drawVerticalLine(kMeta, kRed); // 547
  drawVerticalLine(kMomega, kRed); // 782
  drawVerticalLine(kMf1, kRed); // 1285
  
  c->Print(plotFile);
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckBkg_f1 -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckBkg_f1 -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing CheckBkg_f1 program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "CheckBkg_f1 program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckBkg_f1 -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckBkg_f1 -t[target]" << std::endl;
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
  // output name
  plotFile = outDir + "/f1-" + targetOption + ".png";
}
