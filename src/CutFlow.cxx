/***************************************/
/*  CutFlow-Electron.cxx               */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// VERSION 1.0
// - Checking the electrons' cut

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

  input->Add("/home/borquez/Downloads/clas_42011_*.pass2.root"); // _*.pass2
  
  // define TIdentificator
  TIdentificator *t = new TIdentificator(input);
  Long_t nEntries = (Long_t) input->GetEntries();
      
  // define counters
  Int_t c00 = 0; // no cut
  Int_t c01 = 0; // number_xx cut
  Int_t c02 = 0; // all status
  Int_t c03 = 0; // charge
  Int_t c04 = 0; // CC Nphe
  Int_t c05 = 0; // P > 0.64
  Int_t c06 = 0; // Eout > 0 and Ein > 0.06
  Int_t c07 = 0; // SC EC time
  Int_t c08 = 0; // sampling fraction cut
  Int_t c09 = 0; // EC fid cuts
  Int_t c10 = 0; // DC fid cuts
  Int_t c11 = 0; // sampling fraction "band"
  
  // start TIdentificator
  input->Next();

  // define number of rows
  Int_t number_dc = input->GetNRows("DCPB");
  Int_t number_cc = input->GetNRows("CCPB");
  Int_t number_sc = input->GetNRows("SCPB");
  Int_t number_ec = input->GetNRows("ECPB");
  
  // loop around events
  for (Int_t n = 0; n < nEntries; n++) { // nEntries

    // update number of rows!
    number_dc = input->GetNRows("DCPB");
    number_cc = input->GetNRows("CCPB");
    number_sc = input->GetNRows("SCPB");
    number_ec = input->GetNRows("ECPB");
    
    // update electrons' UVW vector
    TVector3 *ECxyz_e = new TVector3(t->XEC(0), t->YEC(0), t->ZEC(0));
    TVector3 *ECuvw_e = t->XYZToUVW(ECxyz_e);

    c00++;

    if (number_dc != 0 && number_cc != 0 &&
	number_ec != 0 && number_sc != 0) {
      c01++;
      if (t->StatCC(0) > 0 && t->StatSC(0) > 0 && t->StatDC(0) > 0 && t->StatEC(0) > 0 &&
	  t->DCStatus(0) > 0 && t->SCStatus(0) == 33) {
	c02++;
	if (t->Charge(0) == -1) {
	  c03++;
	  if (t->Nphe(0) > (t->Sector(0)==0 || t->Sector(0)==1)*25 + (t->Sector(0)==2)*26 + (t->Sector(0)==3)*21 + (t->Sector(0)==4 || t->Sector(0)==5)*28) {
	    c04++;
	    if (t->Momentum(0) > 0.64) {
	      c05++;
	      if (t->Ein(0) > 0.06 && t->Eout(0) > 0) {
		c06++;
		if (t->TimeEC(0) - t->TimeSC(0) - 0.7 > -5*0.35 &&
		    t->TimeEC(0) - t->TimeSC(0) - 0.7 < 5*0.35) {
		  c07++;
		  if (t->SampFracCheck("C")) {
		    c08++;
		    if (ECuvw_e->X() > 40 && ECuvw_e->X() < 400 &&
			ECuvw_e->Y() >= 0 && ECuvw_e->Y() < 360 &&
			ECuvw_e->Z() >= 0 && ECuvw_e->Z() < 390) {
		      c09++;
		      if (t->FidCheckCut()) {
			c10++;
			if (t->Etot(0) / 0.27 / 1.15 + 0.4 > t->Momentum(0) &&
			    t->Etot(0) / 0.27 / 1.15 - 0.2 < t->Momentum(0) &&
			    t->Ein(0) + t->Eout(0) > 0.8 * 0.27 * t->Momentum(0) &&
			    t->Ein(0) + t->Eout(0) < 1.2 * 0.27 * t->Momentum(0)) {
			  c11++;
			}
		      }
		    }
		  }
		}
	      }
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
  TH1F *theHist = new TH1F("cutflow-electrons", "Cut Flow Chart - Electrons' id", 12, 0, 12);
  
  // fill histograms
  theHist->SetBinContent(1, c00);
  theHist->SetBinContent(2, c01);
  theHist->SetBinContent(3, c02);
  theHist->SetBinContent(4, c03);
  theHist->SetBinContent(5, c04);
  theHist->SetBinContent(6, c05);
  theHist->SetBinContent(7, c06);
  theHist->SetBinContent(8, c07);
  theHist->SetBinContent(9, c08);
  theHist->SetBinContent(10, c09);
  theHist->SetBinContent(11, c10);
  theHist->SetBinContent(12, c11);

  theHist->GetXaxis()->CenterLabels();
  theHist->GetXaxis()->SetNdivisions(212, kFALSE);

  gPad->SetGridx(1);
  
  theHist->GetXaxis()->SetTitle("Cut id");
  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(3);
    
  theHist->Draw("HIST");
  
  c->Print(outDir + "/test-electron.png"); // output file
    
  return 0;
}
