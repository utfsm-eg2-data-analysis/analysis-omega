#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "DrawDiagonalLine.cxx"

void PPlot_PIDe__EnergyDepo_simrec(TString setOption = "old", TString targetOption = "C") {
  // Particular plot, PID electrons, Eout vs Ein

  TChain *InputChain = new TChain();
  InputChain->Add(gWorkDir + "/out/GetSimpleTuple/" + setOption + "/" + targetOption + "/pruned" + targetOption + "_*.root/ntuple_e");
  
  TH2D *HistLeft;
  InputChain->Draw("Eout/0.27/P:Ein/0.27/P>>hist_left(120, 0., 1.2, 120, 0, 1.2)", "Eout > 0", "goff");
  HistLeft = (TH2D *)gROOT->FindObject("hist_left");

  HistLeft->SetTitle("");
  HistLeft->GetYaxis()->SetTitle("E_{out}/0.27/P");
  HistLeft->GetYaxis()->SetTitleOffset(1.5);
  HistLeft->GetXaxis()->SetTitle("E_{in}/0.27/P");
  HistLeft->GetXaxis()->SetTitleOffset(1.5);
  
  TH2D *HistRight;
  InputChain->Draw("Etot/0.27:P>>hist_right(120, 0., 4., 120, 0, 4.)", "Eout > 0", "goff");
  HistRight = (TH2D *)gROOT->FindObject("hist_right");

  HistRight->SetTitle("");
  HistRight->GetYaxis()->SetTitle("E_{tot}/0.27 [GeV]");
  HistRight->GetYaxis()->SetTitleOffset(1.5);
  HistRight->GetXaxis()->SetTitle("P [GeV]");
  HistRight->GetXaxis()->SetTitleOffset(1.5);
  
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
  TCanvas *c = new TCanvas("pplot-electron-ps", "pplot-electron-ps", 1200, 600);
  c->Divide(Nx, Ny, 0.001, 0.001);
  
  c->SetFrameLineWidth(2);
	
  Double_t LineLeft_Slope[2] = {-1, -1};
  Double_t LineLeft_Const[2] = {0.8, 1.2};
  Double_t LineRight_Slope[2] = {1.15, 1.15};
  Double_t LineRight_Const[2] = {-0.46, 0.23};

  c->cd(1);
  HistLeft->Draw("COLZ");
  
  // DrawDiagonalLine(LineLeft_Slope[0], LineLeft_Const[0], 0., 1.2, kMagenta, kSolid, 3, "f0");
  // DrawDiagonalLine(LineLeft_Slope[1], LineLeft_Const[1], 0., 1.2, kMagenta, kSolid, 3, "f1");
      
  c->Update();

  c->cd(2);
  HistRight->Draw("COLZ");
  
  // DrawDiagonalLine(LineRight_Slope[0], LineRight_Const[0], 0., 4., kMagenta, kSolid, 3, "f2");
  // DrawDiagonalLine(LineRight_Slope[1], LineRight_Const[1], 0., 4., kMagenta, kSolid, 3, "f3");
      
  c->Update();
}
