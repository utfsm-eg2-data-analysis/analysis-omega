/***************************************/
/*  CheckElectronCut-ECSCTime.cxx      */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// VERSION 1.0
// - Checking the electrons' EC-SC coincidence time cut

#include "analysisConfig.h"

#include "TClasTool.h"
#include "TIdentificator.h"

/*** Global variables ***/

TString outDir = proDir + "/out/CheckElectronCut";
TString inputFile = "/home/borquez/Downloads/clas_42011_00.pass2.root";

int main() {
  
  // dir structure, just in case
  system("mkdir -p " + outDir);

  // init ClasTool
  TClasTool *input = new TClasTool();
  input->InitDSTReader("ROOTDSTR");
  input->Add(inputFile);
  
  // define TIdentificator
  TIdentificator *t = new TIdentificator(input);
  Long_t nEntries = (Long_t) input->GetEntries();
    
  // define histogram and value
  TH1F *theHist = new TH1F("analyser", "Electrons' EC SC coincidence time cut - Analyser", 150, -3, 3);
  TH1F *theHist_b = new TH1F("taya", "Electrons' EC SC coincidence time cut - Taya's approx.", 150, -3, 3);
  TH1F *theHist_b2 = new TH1F("taya2", "Electrons' EC SC coincidence time cut - Taya's Analysis Note", 150, -3, 3);
  TH1F *theHist_c = new TH1F("mike", "Electrons' EC SC coincidence time cut - Mike's suggestion", 150, -3, 3);

  TH1F *theHist_d = new TH1F("centering-factor", "title", 150, 0., 1.);
  
  // start TIdentificator
  input->Next();
 
  // loop around events
  for (Int_t k = 0; k < nEntries; k++) {

    // fill histograms
    theHist->Fill(t->TimeEC(0) - t->TimeSC(0) - (t->PathEC(0) - t->PathSC(0))/30.);      // analyser
    theHist_b->Fill(t->TimeEC(0) - t->TimeSC(0) - 0.7);                                  // taya's approx.
    theHist_b2->Fill(t->TimeEC(0) - (t->TimeSC(0) - (t->PathEC(0) - t->PathSC(0))/30.)); // taya's literal
    theHist_c->Fill(t->TimeEC(0) - t->TimeSC(0));                                        // mike

    theHist_d->Fill((t->PathEC(0) - t->PathSC(0))/30.);                                  // centering-factor
    
    input->Next();
  } // end of loop in events

  theHist->GetXaxis()->SetTitle("(ns)");
  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(3);

  theHist_b->GetXaxis()->SetTitle("(ns)");
  theHist_b->SetLineColor(kBlue);
  theHist_b->SetLineWidth(3);

  theHist_b2->GetXaxis()->SetTitle("(ns)");
  theHist_b2->SetLineColor(kRed);
  theHist_b2->SetLineWidth(3);

  theHist_c->GetXaxis()->SetTitle("(ns)");
  theHist_c->SetLineColor(kGreen+2);
  theHist_c->SetLineWidth(3);
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat("emr");
  /*
  theHist->Draw("HIST"); // analyser
  drawVerticalLine(5*0.35, kBlack, "dash");
  drawVerticalLine(theHist->GetMean(), kBlack, "cont");
  */
  /*
  theHist_b->Draw("HIST"); // taya's approx.
  drawVerticalLine(5*0.35, kBlue, "dash");
  drawVerticalLine(-5*0.35, kBlue, "dash");
  drawVerticalLine(theHist_b->GetMean(), kBlue, "cont");
  */
  /*
  theHist_b2->Draw("HIST"); // taya's literal
  drawVerticalLine(5*0.35, kRed);
  drawVerticalLine(-5*0.35, kRed);
  drawVerticalLine(theHist_b2->GetMean(), kRed, "cont");
  */
  
  theHist_c->Draw("HIST"); // mike's suggestion
  drawVerticalLine(theHist_c->GetMean(), kGreen+2, "cont");
  
  c->Print(outDir + "/test-mike.png"); // output file
    
  return 0;
}
