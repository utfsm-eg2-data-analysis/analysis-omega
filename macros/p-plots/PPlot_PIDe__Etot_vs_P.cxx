#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "DrawDiagonalLine.cxx"

void PPlot_PIDe__Etot_vs_P() {
  // Particular plot, PID electrons, Eout vs Ein

  TChain *InputChain = new TChain();
  InputChain->Add(gWorkDir + "/out/TestPID/prunedC_*_noec.root/ntuple_e");
  
  TH2D *Hist[6];
  for (Int_t Sector = 0; Sector < 6; Sector++) {
    InputChain->Draw(Form("Etot/0.27:P>>hist_%d(100, 0., 4., 100, 0, 4.)", Sector), Form("Sector == %d && Eout > 0", Sector), "goff");
    Hist[Sector] = (TH2D *)gROOT->FindObject(Form("hist_%d", Sector));

    Hist[Sector]->SetTitle(Form("Sector %d", Sector));
    Hist[Sector]->GetYaxis()->SetTitle("E_{tot}/0.27 [GeV]");
    Hist[Sector]->GetYaxis()->SetTitleOffset(1.5);
    Hist[Sector]->GetXaxis()->SetTitle("P [GeV]");
    Hist[Sector]->GetXaxis()->SetTitleOffset(1.5);
  }
  
  /*** DRAW ***/
  
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(kDarkBodyRadiator);
  gStyle->SetTitleY(0.95);
  gStyle->SetNumberContours(255);

  gStyle->SetPadTopMargin(0.15);
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  
  // define canvas
  const Int_t Nx = 3;
  const Int_t Ny = 2;
  TCanvas *c = new TCanvas("pplot-electron-sp-2", "pplot-electron-sp-2", 1500, 1000);
  c->Divide(Nx, Ny, 0.001, 0.001);
  
  c->SetFrameLineWidth(2);
	
  Double_t Line1_Slope[6] = {1.05, 1.05, 1.11, 1.07, 1.11, 1.11};
  Double_t Line1_Const[6] = {-0.46, -0.46, -0.43, -0.43, -0.43, -0.43};
  Double_t Line2_Slope[6] = {1.05, 1.05, 1.11, 1.07, 1.11, 1.11};
  Double_t Line2_Const[6] = {0.18, 0.18, 0.18, 0.18, 0.18, 0.18};
  
  Int_t counter = 1;
  for (Int_t i = 0; i < Nx; i++) {
    for (Int_t j = 0; j < Ny; j++) {

      c->cd(counter);
      Hist[counter-1]->Draw("COLZ");

      DrawDiagonalLine(Line1_Slope[counter-1], Line1_Const[counter-1], 0., 4., kMagenta, kSolid, 3, Form("f%d", counter-1));
      DrawDiagonalLine(Line2_Slope[counter-1], Line2_Const[counter-1], 0., 4., kMagenta, kSolid, 3, Form("f%d", counter-1));
      
      c->Update();
      counter++;
    }
  }
}
