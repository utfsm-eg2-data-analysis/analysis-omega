#ifndef GLOBAL_H
#include "Global.h"
#endif

const Double_t lines_PiPlus[14][2] = {{-0.70, 0.70}, {-0.70, 0.65},
				      {-0.70, 0.65}, {-0.70, 0.65},
				      {-0.55, 0.55}, {-0.50, 0.55},
				      {-0.50, 0.40}, {-0.48, 0.40},
				      {-0.50, 0.40}, {-0.50, 0.40},
				      {-0.50, 0.40}, {-0.60, 0.45},
				      {-0.60, 0.50}, {-0.60, 0.50}};

const Double_t ranges[14][2] = {{0.00, 0.25}, {0.25, 0.50},
				{0.50, 0.75}, {0.75, 1.00},
				{1.00, 1.25}, {1.25, 1.50},
				{1.50, 1.75}, {1.75, 2.00},
				{2.00, 2.25}, {2.25, 2.50},
				{2.50, 2.70}, {2.70, 3.30},
				{3.30, 3.70}, {3.70, 5.00}};

void PPlot_PIDpp__T4_vs_P_simrec(TString setOption = "old", TString targetOption = "C") {
  // Particular plot, PID of pi+, Delta TOF vs P

  TChain *InputChain = new TChain();
  InputChain->Add(gWorkDir + "/out/GetSimpleTuple/" + setOption + "/" + targetOption + "/pruned" + targetOption + "_*.root/ntuple_sim");
  
  TH2D *Hist;
  InputChain->Draw("T4:P>>hist(200, 0., 5.0, 200, -1.2, 1.2)", "pid == 211", "goff");
  Hist = (TH2D *)gROOT->FindObject("hist");

  Hist->SetTitle("");
  Hist->GetYaxis()->SetTitle("#Delta T [ns]");
  Hist->GetYaxis()->SetTitleOffset(1.5);
  Hist->GetXaxis()->SetTitle("P [GeV]");
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
  TCanvas *c = new TCanvas("pplot-pip-tof", "pplot-pip-tof", 1000, 1000);
  
  c->SetFrameLineWidth(2);
  
  Hist->Draw("COLZ");

  // pave
  TPaveText *pav = new TPaveText(0.75, 0.75, 0.85, 0.85, "NDC NB"); // no border
  pav->AddText("#pi^{+}");
  pav->SetBorderSize(0);
  pav->SetFillStyle(0);
  pav->Draw();
  /*
  TF1 *Line_0[14];
  TF1 *Line_1[14];
  for (Int_t i = 0; i < 14; i++) {
    Line_0[i] = new TF1(Form("Line_0_%d", i), Form("%.2f", lines_PiPlus[i][0]), ranges[i][0], ranges[i][1]);
    Line_1[i] = new TF1(Form("Line_1_%d", i), Form("%.2f", lines_PiPlus[i][1]), ranges[i][0], ranges[i][1]);

    Line_0[i]->SetLineColor(kMagenta);
    Line_0[i]->SetLineStyle(kSolid);
    Line_0[i]->SetLineWidth(5);
    Line_0[i]->Draw("SAME");
    
    Line_1[i]->SetLineColor(kMagenta);
    Line_1[i]->SetLineStyle(kSolid);
    Line_1[i]->SetLineWidth(5);
    Line_1[i]->Draw("SAME");
  }
  */
}
