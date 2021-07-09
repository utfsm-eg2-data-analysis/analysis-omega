#ifndef GLOBAL_H
#include "Global.h"
#endif

void PPlot_PIDe__ECY_vs_ECX() {
  // Particular plot, electron identification cuts, effect of EC fiducial cuts

  TChain *Chain_Before = new TChain();
  Chain_Before->Add(gWorkDir + "/out/TestPID/prunedC_*_noec.root/ntuple_e");

  TChain *Chain_After = new TChain();
  Chain_After->Add(gWorkDir + "/out/GetSimpleTuple/data/C/prunedC_*.root/ntuple_e");
  
  // before corr
  TH2D *Hist_Before;
  Chain_Before->Draw("YEC:XEC>>hist_before(240, -450., 450., 240, -450., 450.)", "", "goff");
  Hist_Before = (TH2D *)gROOT->FindObject("hist_before");

  Hist_Before->SetTitle("Before EC Fiducial Cuts");
  Hist_Before->GetYaxis()->SetTitle("Y [cm]");
  Hist_Before->GetYaxis()->SetTitleOffset(1.5);
  Hist_Before->GetXaxis()->SetTitle("X [cm]");
  Hist_Before->GetXaxis()->SetTitleOffset(1.5);

  // after corr
  TH2D *Hist_After;
  Chain_After->Draw("YEC:XEC>>hist_after(240, -450., 450., 240, -450., 450.)", "", "goff");
  Hist_After = (TH2D *)gROOT->FindObject("hist_after");

  Hist_After->SetTitle("After EC Fiducial Cuts");
  Hist_After->GetYaxis()->SetTitle("Y [cm]");
  Hist_After->GetYaxis()->SetTitleOffset(1.5);
  Hist_After->GetXaxis()->SetTitle("X [cm]");
  Hist_After->GetXaxis()->SetTitleOffset(1.5);
  
  /*** DRAW ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gStyle->SetTitleY(0.95);

  gStyle->SetPadTopMargin(0.15);
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);

  // define canvas
  const Int_t Nx = 2;
  const Int_t Ny = 1;
  TCanvas *c = new TCanvas("pplot-uvw-cuts", "pplot-uvw-cuts", 1200, 600);
  c->Divide(Nx, Ny, 0.001, 0.001);

  c->SetFrameLineWidth(2);

  /*** LEFT PLOT ***/

  TH2D *Hist_BeforeLeft = (TH2D*) Hist_Before->Clone("hist_before_left");
  
  c->cd(1);

  Hist_BeforeLeft->Draw("COLZ");
  TExec *ex0 = new TExec("ex0", "gStyle->SetPalette(kDarkBodyRadiator);");
  ex0->Draw();

  Hist_BeforeLeft->SetContour(255);
  Hist_BeforeLeft->Draw("COLZ SAME");

  c->Update();
  
  /*** RIGHT PLOT ***/
  
  Hist_Before->SetTitle("After EC Fiducial Cuts"); // because it is plotted first
  
  c->cd(2);
  
  Hist_Before->Draw("COLZ");
  TExec *ex1 = new TExec("ex1", "gStyle->SetPalette(kAurora);");
  ex1->Draw();

  Hist_Before->SetContour(1);
  Hist_Before->Draw("COLZ SAME");
  
  Hist_After->Draw("COLZ SAME");
  TExec *ex2 = new TExec("ex2", "gStyle->SetPalette(kDarkBodyRadiator);");
  ex2->Draw();

  gStyle->SetNumberContours(255);
  
  Hist_After->Draw("COLZ SAME");

  c->Update();
}
