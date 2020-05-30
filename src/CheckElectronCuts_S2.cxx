/***************************************/
/*  CheckElectronCuts_S2.cxx           */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// Checking the electrons' EC-SC coincidence time cut on data
// STAGE 2:
// - after merging all output files from all data (all run numbers) into a "cec-All.root" file
// - this code add all histograms and calculates a final fit

#include "analysisConfig.h"

#include "TClasTool.h"
#include "TIdentificator.h"

/*** Global variables ***/

TString outDir = proDir + "/out/CheckElectronCut";

TString inputFile = outDir + "/cec-All.root";

TString outTitle = "Electrons EC SC coincidence time cut";
TString plotFile = outDir + "/cec-fit.png";

int main() {

  // open root file
  TFile *rootFile = new TFile(inputFile, "READ");
  
  // define histograms and value
  TH1F *theHist_final = new TH1F("tECtSC", "Electrons (t_{EC} - t_{SC}) distribution", 250, -5., 5.);  
  TH1F *tmpHist;
  
  /*** Reading rn files ***/
  TString rnFile;
  
  // 1. carbon
  rnFile = proDir + "/include/C-thickD2rn.txt";
  std::cout << "Reading " << rnFile << " ..." << std::endl;
  std::ifstream inFile_C(rnFile);

  TString rn;

  while (inFile_C >> rn) {
    tmpHist = (TH1F *) gDirectory->Get("tECtSC_" + rn);
    theHist_final->Add(tmpHist);
  }
  inFile_C.close();

  // 2. iron
  rnFile = proDir + "/include/Fe-thickD2rn.txt";
  std::cout << "Reading " << rnFile << " ..." << std::endl;
  std::ifstream inFile_Fe(rnFile);

  while (inFile_Fe >> rn) {
    tmpHist = (TH1F *) gDirectory->Get("tECtSC_" + rn);
    theHist_final->Add(tmpHist);
  }
  inFile_Fe.close();

  // 3. lead
  rnFile = proDir + "/include/Pb-thinD2rn.txt";
  std::cout << "Reading " << rnFile << " ..." << std::endl;
  std::ifstream inFile_Pb(rnFile);

  while (inFile_Pb >> rn) {
    tmpHist = (TH1F *) gDirectory->Get("tECtSC_" + rn);
    theHist_final->Add(tmpHist);
  }
  inFile_Pb.close();

  /*** The fit ***/

  // define observed values
  Double_t obtMean = 0.6775;
  Double_t obtRange[2] = {0., 1.355};

  // define function, its range and initial guess value
  TF1 *theFunction = new TF1("theFunction", "gaus", obtRange[0], obtRange[1]);
  theFunction->SetParameter(1, obtMean);

  // fit!
  theHist_final->Fit("theFunction", "REN0", "goff");

  // gather fit params
  Double_t fitParams[3];
  theFunction->GetParameters(fitParams);
    
  /*** Drawing ***/

  // before anything, define canvas
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat("emr");
  // gStyle->SetOptFit(1);
  // gROOT->ForceStyle();  
  
  // draw hist
  theHist_final->GetXaxis()->SetTitle("(ns)");
  theHist_final->SetLineColor(kGreen+2);
  theHist_final->SetLineWidth(3);

  theHist_final->Draw("HIST");

  // draw function
  theFunction->SetLineWidth(1);
  theFunction->SetNpx(500);
  theFunction->SetLineColor(kBlue+1);

  theFunction->Draw("SAME");
  
  // draw lines: mean and 3sigma range around it
  drawVerticalLine(theHist_final->GetMean(), kGreen+2, "dash"); // just for comparison
  drawVerticalLine(fitParams[1], kBlue+1, "dash");
  drawVerticalLine(fitParams[1] - 5*fitParams[2], kBlue, "cont");
  drawVerticalLine(fitParams[1] - 3*fitParams[2], kBlue+1, "cont");
  drawVerticalLine(fitParams[1] + 3*fitParams[2], kBlue+1, "cont");
  drawVerticalLine(fitParams[1] + 5*fitParams[2], kBlue, "cont");

  // save plot
  c->Print(plotFile);
  
  return 0;
}
