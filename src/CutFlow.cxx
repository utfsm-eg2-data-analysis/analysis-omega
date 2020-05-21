/***************************************/
/*  CutFlow.cxx                        */
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

TString outDir = proDir + "/out/CutFlow";
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
  TH1F *theHist = new TH1F("analyser", "title", 450, -3, 3);
  TH1F *theHist_b = new TH1F("taya", "title", 450, -3, 3);
  TH1F *theHist_b2 = new TH1F("taya2", "title", 450, -3, 3);
  TH1F *theHist_c = new TH1F("mike", "title", 450, -3, 3);

  TH1F *theHist_d = new TH1F("centering-factor", "title", 150, 0., 1.);
  
  // start TIdentificator
  input->Next();
 
  // loop around events
  for (Int_t k = 0; k < nEntries; k++) {

    // fill histograms
    theHist->Fill(t->TimeEC(0) - t->TimeSC(0) - (t->PathEC(0) - t->PathSC(0))/30.);      // analyser
    theHist_b->Fill(t->TimeEC(0) - t->TimeSC(0) - 0.7);                                  // taya
    theHist_b2->Fill(t->TimeEC(0) - (t->TimeSC(0) - (t->PathEC(0) - t->PathSC(0))/30.)); // taya2
    theHist_c->Fill(t->TimeEC(0) - t->TimeSC(0));                                        // mike

    theHist_d->Fill((t->PathEC(0) - t->PathSC(0))/30.);                                  // centering-factor
    
    input->Next();
  } // end of loop in events
  
  theHist->GetXaxis()->SetTitle("axis title");
  theHist->GetXaxis()->CenterTitle();

  theHist->SetLineColor(kBlack);
  
  theHist_b->SetLineColor(kRed);
  theHist_b2->SetLineColor(kGreen+2);
  
  theHist_c->SetLineColor(kBlue);
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  theHist->Draw("E");
  theHist_b->Draw("SAME E");
  theHist_b2->Draw("SAME E");
  theHist_c->Draw("SAME E");

  // drawVerticalLineRed(5*0.35);
  // drawVerticalLineRed(-5*0.35);

  TLegend *l = new TLegend(0.7, 0.7, 0.9, 0.9);
  l->AddEntry(theHist, "analyser", "l");
  l->AddEntry(theHist_b, "taya", "l");
  l->AddEntry(theHist_b2, "taya2", "l");
  l->AddEntry(theHist_c, "mike", "l");
  l->Draw();

  c->Print(outDir + "/test.png"); // output file

  /*** Print means ***/
  
  std::cout << "analyser mean = " << theHist->GetMean() << std::endl;
  std::cout << "taya mean     = " << theHist_b->GetMean() << std::endl;
  std::cout << "taya2 mean    = " << theHist_b2->GetMean() << std::endl;
  std::cout << "mike mean     = " << theHist_c->GetMean() << std::endl;
  std::cout << "mike - taya   = " << theHist_c->GetMean() - theHist_b->GetMean() << std::endl;
  
  /*** On the centering factor... ***/

  TCanvas *c_d = new TCanvas("c_d", "c_d", 1000, 1000);
  gStyle->SetOptStat(1);
  theHist_d->Draw("E");
  c_d->Print(outDir + "/test2.png"); // output file
  
  return 0;
}
