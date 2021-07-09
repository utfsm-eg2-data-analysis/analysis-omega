#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "DrawVerticalLine.cxx"

void PPlot_PIDe__Eout_vs_Ein() {
  // Particular plot, PID electrons, Eout vs Ein

  TChain *InputChain = new TChain();
  InputChain->Add(gWorkDir + "/out/TestPID/prunedC_*_noec.root/ntuple_e");
  
  InputChain->Draw("Eout:Ein>>hist(100, 0., 0.35, 100, 0.00, 0.15)", "Eout > 0", "goff");
  TH2D *Hist = (TH2D *)gROOT->FindObject("hist");

  Hist->SetTitle("");
  Hist->GetXaxis()->SetTitle("E_{in} [GeV]");
  Hist->GetXaxis()->SetTitleOffset(1.5);
  Hist->GetYaxis()->SetTitle("E_{out} [GeV]");
  Hist->GetYaxis()->SetTitleOffset(2.0);
  
  /*** DRAW ***/
  
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(kDarkBodyRadiator);
  gStyle->SetNumberContours(255);
    
  // define canvas
  TCanvas *c = new TCanvas("pplot-eine", "pplot-eine", 1000, 1000);
  c->SetFrameLineWidth(2);
  c->SetLeftMargin(0.15);
  c->SetBottomMargin(0.15);
  c->SetTopMargin(0.15);
  c->SetRightMargin(0.15);
  
  Hist->Draw("COLZ");
  
  DrawVerticalLine(0.06, kMagenta, kDashed, 4, 2);
}
