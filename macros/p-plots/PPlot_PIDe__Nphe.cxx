#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "DrawVerticalLine.cxx"

void PPlot_PIDe__Nphe() {
  // Particular plot, PID electrons, number of photoelectrons

  TChain *InputChain = new TChain();
  InputChain->Add(gWorkDir + "/out/TestPID/prunedC_*_nophe.root/ntuple_e");
  
  TH1D *Hist[6];
  for (Int_t Sector = 0; Sector < 6; Sector++) {
    InputChain->Draw(Form("Nphe>>hist_%d(75, 0., 300.)", Sector), Form("Sector == %d", Sector), "goff");
    Hist[Sector] = (TH1D *)gROOT->FindObject(Form("hist_%d", Sector));

    Hist[Sector]->SetTitle("");
    Hist[Sector]->GetYaxis()->SetTitle("Counts");
    Hist[Sector]->GetYaxis()->SetTitleOffset(1.75);
    Hist[Sector]->GetYaxis()->SetMaxDigits(3);
    Hist[Sector]->GetXaxis()->SetTitle("10 #times N_{phe}");
    Hist[Sector]->GetXaxis()->SetTitleOffset(1.5);

    Hist[Sector]->SetLineColor(kBlack);
    Hist[Sector]->SetLineWidth(2);
  }
  
  /*** DRAW ***/
  
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  // gStyle->SetTitleY(0.95);
  gStyle->SetOptStat(0);

  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  
  // define canvas
  const Int_t Nx = 3;
  const Int_t Ny = 2;
  TCanvas *c = new TCanvas("pplot-electron-nphe", "pplot-electron-nphe", 500*Nx, 500*Ny);
  c->Divide(Nx, Ny, 0.001, 0.001);
  
  c->SetFrameLineWidth(2);

  // nphe cut for each sector
  Int_t NpheCut[6] = {25, 25, 26, 21, 28, 28};
  
  Int_t counter = 1;
  for (Int_t i = 0; i < Nx; i++) {
    for (Int_t j = 0; j < Ny; j++) {

      c->cd(counter);
      Hist[counter-1]->Draw("HIST");

      DrawVerticalLine((Double_t)NpheCut[counter-1], kBlue, kSolid, 3, 1);

      // pave
      TPaveText *pav = new TPaveText(0.60, 0.60, 0.88, 0.88, "NDC NB"); // no border
      pav->AddText(Form("Sector %d", counter-1));
      pav->AddText(Form("10 #times N_{phe} > %d", NpheCut[counter-1]));
      pav->SetBorderSize(0);
      pav->SetFillStyle(0);
      pav->Draw();

      c->Update();
      counter++;
    }
  }
}
