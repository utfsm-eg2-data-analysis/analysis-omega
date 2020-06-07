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
TString inputFile = "/home/borquez/analysis-omega/out/ToyGST/data/C/prunedC_42011.root";
// TString outFile = outDir + "/hola.png"; // e
// TString outFile = outDir + "/hola-pim.png"; // pi-
// TString outFile = outDir + "/hola-pip.png"; // pi+
TString outFile = outDir + "/hola-pip-Zh.png"; // pi+, Z

int main() {
  
  // dir structure, just in case
  system("mkdir -p " + outDir);
  
  TChain *treeExtracted = new TChain();
  // treeExtracted->Add(inputFile + "/ntuple_e"); // e
  treeExtracted->Add(inputFile + "/ntuple_data"); // pi-, pi+
  
  // define cuts
  // TCut statusCuts = "Status > 0 && Status < 100 && StatCC > 0 && StatSC > 0 && StatDC > 0 && StatEC > 0 && DCStatus > 0 && SCStatus == 33"; // e
  // TCut statusCuts = "pid == -211 && Status > 0 && Status < 100 && StatDC > 0 && DCStatus > 0"; // pi-
  TCut statusCuts = "pid == 211 && Status > 0 && Status < 100 && StatDC > 0 && DCStatus > 0 && ((P > 2.7 && StatCC > 0 && Chi2CC < 5/57.3) || (P < 2.7 && StatSC > 0))"; // pi+
  
  TH1F *theHist_nc;
  // treeExtracted->Draw("Q2>>h_nc(300, 1., 4.)", "", "goff"); // nc: no cuts, e
  // treeExtracted->Draw("P>>h_nc(300, 0., 3.)", "pid == -211", "goff"); // nc: no cuts, pi-
  // treeExtracted->Draw("P>>h_nc(300, 0., 3.)", "pid == 211", "goff"); // nc: no cuts, pi+
  treeExtracted->Draw("Zh>>h_nc(200, 0., 1.)", "pid == 211", "goff"); // nc: no cuts, pi+, Z
  theHist_nc = (TH1F *)gROOT->FindObject("h_nc");
  
  TH1F *theHist_wc;
  // treeExtracted->Draw("Q2>>h_wc(300, 1., 4.)", statusCuts, "goff"); // wc: with cuts, e
  // treeExtracted->Draw("P>>h_wc(300, 0., 3.)", statusCuts, "goff"); // wc: no cuts, pi-, pi+
  treeExtracted->Draw("Zh>>h_wc(200, 0., 1.)", statusCuts, "goff"); // wc: no cuts, pi+, Z
  theHist_wc = (TH1F *)gROOT->FindObject("h_wc");
    
  // define histogram and value
  // theHist_nc->SetTitle("P (#pi^{-})"); // pi-
  // theHist_nc->SetTitle("P (#pi^{+})"); // pi+
  theHist_nc->SetTitle("Z (#pi^{+})"); // pi+, Z
  // theHist_nc->GetXaxis()->SetTitle("Q^{2} (GeV^{2})"); // e
  // theHist_nc->GetXaxis()->SetTitle("P (GeV)"); // pi-, pi+
  theHist_nc->GetXaxis()->SetTitle("Z");
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
