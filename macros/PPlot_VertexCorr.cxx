#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "DrawHorizontalLine.cxx"

void PPlot_VertexCorr(TString targetOption = "C") {
  // Particular plot, effect of electron vertex corr.

  TChain *InputChain = new TChain();
  InputChain->Add(gWorkDir + "/out/GetSimpleTuple/data/" + targetOption + "/*.root/ntuple_e");

  // before corr
  TH2D *Hist_Before;
  InputChain->Draw("vze:PhiLab>>hist_before(180, -30., 330., 100, -33, -23.)", "", "goff");
  Hist_Before = (TH2D *)gROOT->FindObject("hist_before");

  Hist_Before->SetTitle("Before electron vertex correction");
  Hist_Before->GetYaxis()->SetTitle("z [cm]");
  Hist_Before->GetYaxis()->SetTitleOffset(1.5);
  Hist_Before->GetXaxis()->SetTitle("#phi_{lab} [deg]");
  Hist_Before->GetXaxis()->SetTitleOffset(1.5);

  // after corr
  TH2D *Hist_After;
  InputChain->Draw("vzec:PhiLab>>hist_after(180, -30., 330., 100, -33, -23.)", "", "goff");
  Hist_After = (TH2D *)gROOT->FindObject("hist_after");

  Hist_After->SetTitle("After electron vertex correction");
  Hist_After->GetYaxis()->SetTitle("z^{corr} [cm]");
  Hist_After->GetYaxis()->SetTitleOffset(1.5);
  Hist_After->GetXaxis()->SetTitle("#phi_{lab} [deg]");
  Hist_After->GetXaxis()->SetTitleOffset(1.5);
  
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
  const Int_t Nx = 2;
  const Int_t Ny = 1;
  TCanvas *c = new TCanvas("pplot-vertex-corr", "pplot-vertex-corr", 1200, 600);
  c->Divide(Nx, Ny, 0.001, 0.001);

  c->SetFrameLineWidth(2);

  c->cd(1);
  Hist_Before->Draw("COLZ");
  c->Update();

  c->cd(2);
  Hist_After->Draw("COLZ");

  DrawHorizontalLine(-31.80, kMagenta, kDashed, 3, 2);
  DrawHorizontalLine(-28.40, kMagenta, kDashed, 3, 2);
  DrawHorizontalLine(-25.33, kMagenta, kDashed, 3, 2);
  DrawHorizontalLine(-24.10, kMagenta, kDashed, 3, 2);
  
  c->Update();
}
