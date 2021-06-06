#ifndef GLOBAL_H
#include "Global.h"
#endif

void PPlot_DIS(TString targetOption = "C") {
  // Particular plot, DIS phase space in Q2 vs Xb

  TChain *InputChain = new TChain();
  InputChain->Add(gWorkDir + "/out/GetSimpleTuple/data/" + targetOption + "/*.root/ntuple_e");
  
  TH2D *Hist;
  InputChain->Draw("Q2:Xb>>hist(200, 0., 0.7, 200, 0.5, 5.5)", "", "goff");
  Hist = (TH2D *)gROOT->FindObject("hist");

  Hist->SetTitle("");
  Hist->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
  Hist->GetYaxis()->SetTitleOffset(1.5);
  Hist->GetXaxis()->SetTitle("x_{B}");
  Hist->GetXaxis()->SetTitleOffset(1.5);
  
  /*** DRAW ***/
  
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(kDarkBodyRadiator);
  // gStyle->SetTitleY(0.95);
  gStyle->SetNumberContours(255);

  gStyle->SetPadTopMargin(0.15);
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);

  // define canvas
  TCanvas *c = new TCanvas("pplot-DIS", "pplot-DIS", 1000, 1000);
  
  c->SetFrameLineWidth(2);
  
  Hist->Draw("COLZ");

  gPad->Update(); // necessary
  TF1 *Q2Cut = new TF1("Q2Cut", "1", 0.08, 0.35);
  Q2Cut->SetLineColor(kMagenta);
  Q2Cut->SetLineStyle(kSolid);
  Q2Cut->SetLineWidth(5);
  Q2Cut->Draw("SAME");

  gPad->Update(); // necessary
  TF1 *YbCut = new TF1("YbCut", "0.85*2*5.014*0.938*x", 0.1, 0.65);
  YbCut->SetLineColor(kMagenta);
  YbCut->SetLineStyle(kSolid);
  YbCut->SetLineWidth(5);
  YbCut->Draw("SAME");

  gPad->Update(); // necessary
  TF1 *WCut = new TF1("WCut", "(4*x-0.938*0.938*x)/(1-x)", 0.2, 0.63);
  WCut->SetLineColor(kMagenta);
  WCut->SetLineStyle(kSolid);
  WCut->SetLineWidth(5);
  WCut->Draw("SAME");
}
