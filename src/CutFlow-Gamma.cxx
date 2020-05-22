/***************************************/
/*  CutFlow-Gamma.cxx                  */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// VERSION 1.0
// - Checking the gammas' cut

#include "analysisConfig.h"

#include "TClasTool.h"
#include "TIdentificator.h"

/*** Global variables ***/

TString outDir = proDir + "/out/CutFlow";

int main() {
  
  // dir structure, just in case
  system("mkdir -p " + outDir);

  // init ClasTool
  TClasTool *input = new TClasTool();
  input->InitDSTReader("ROOTDSTR");

  input->Add("/home/borquez/Downloads/clas_42011_*.pass2.root"); // _*.pass2.root
  
  // define TIdentificator
  TIdentificator *t = new TIdentificator(input);
  Long_t nEntries = (Long_t) input->GetEntries();
      
  // define counters
  Int_t c00 = 0; // no cut, number_ev > 1
  Int_t c01 = 0; // charge
  Int_t c02 = 0; // speed of light
  Int_t c03 = 0; // min energy
  Int_t c04 = 0; // EC fid cuts

  // start TIdentificator
  input->Next();

  // define number of rows, historical
  Int_t number_dc = input->GetNRows("DCPB");
    
  // loop around events
  for (Int_t n = 0; n < nEntries; n++) { // nEntries

    // update number of rows, historical
    number_dc = input->GetNRows("DCPB");

    // k > 0, don't forget that!
    for (Int_t k = 1; k < input->GetNRows("EVNT"); k++) { // IMPORTANT: this condition is equivalent to the number_dc != 0 cut!
      c00++;

      // photons
      TVector3 *ECxyz = new TVector3(t->XEC(k), t->YEC(k), t->ZEC(k));
      TVector3 *ECuvw = t->XYZToUVW(ECxyz);
      
      if (t->Charge(k) == 0) {
	c01++;
	if (t->PathEC(k)/(t->Betta(k)*30) - t->PathEC(k)/30 > -2.2 &&
	    t->PathEC(k)/(t->Betta(k)*30) - t->PathEC(k)/30 < 1.3) {
	  c02++;      
	  if (TMath::Max(t->Etot(k), t->Ein(k)+t->Eout(k))/0.272 > 0.1) {
	    c03++;      
	    if (ECuvw->X() > 40 && ECuvw->X() < 410 &&
		ECuvw->Y() >= 0  && ECuvw->Y() < 370 &&
		ECuvw->Z() >= 0  && ECuvw->Z() < 410) {
	      c04++;
	    }
	  }
	}
      }
    }
    
    input->Next();
  }

  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  // define histogram and value
  TH1F *theHist = new TH1F("cutflow-gamma", "Cut Flow Chart - Gammas' id", 5, 0, 5);
  
  // fill histograms
  theHist->SetBinContent(1, c00);
  theHist->SetBinContent(2, c01);
  theHist->SetBinContent(3, c02);
  theHist->SetBinContent(4, c03);
  theHist->SetBinContent(5, c04);

  theHist->GetXaxis()->CenterLabels();
  theHist->GetXaxis()->SetNdivisions(205, kFALSE);

  gPad->SetGridx(1);
  
  theHist->GetXaxis()->SetTitle("Cut id");
  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(3);
    
  theHist->Draw("HIST");
  
  c->Print(outDir + "/test-gamma.png"); // output file
    
  return 0;
}
