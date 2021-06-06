#ifndef GLOBAL_H
#include "Global.h"
#endif

// for simrec, TM parameters
const Double_t kPar[5] = {0.2623 , 0.0089, -0.0019, 0.0057, 0.0305};
			  
void PPlot_PIDe__SampFrac_simrec() {
  // Particular plot, PID electrons, Sampling Fraction Cut

  TChain *InputChain = new TChain();
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0001_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0002_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0003_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0004_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0005_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0006_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0007_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0008_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0009_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0010_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0011_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0012_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0013_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0014_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0015_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0016_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0017_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0018_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0019_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0020_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0021_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0022_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0023_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0024_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0025_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0026_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0027_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0028_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0029_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0030_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0031_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0032_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0033_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0034_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0035_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0036_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0037_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0038_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0039_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0040_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0041_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0042_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0043_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0044_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0045_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0046_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0047_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0048_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0049_noec.root/ntuple_e");
  InputChain->Add(gWorkDir + "/out/TestPID/sim/prunedD_0050_noec.root/ntuple_e");
  
  TH2D *Hist;
  InputChain->Draw("TMath::Max(Etot, Eout+Ein)/P:P>>hist(80, 0., 5., 80, 0, 0.5)", "", "goff");
  Hist = (TH2D *)gROOT->FindObject("hist");

  Hist->SetTitle("Simulation Reconstructed - Target: D");
  Hist->GetYaxis()->SetTitle("E/P");
  Hist->GetYaxis()->SetTitleOffset(1.5);
  Hist->GetXaxis()->SetTitle("P [GeV]");
  Hist->GetXaxis()->SetTitleOffset(1.5);
  
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
  TCanvas *c = new TCanvas("pplot-samp-frac_sim", "pplot-samp-frac_sim", 1000, 1000);
  
  c->SetFrameLineWidth(2);

  // fill parameters
  Double_t Param[5];
  for (Int_t i = 0; i < 5; i++) Param[i] = kPar[i];
  
  Hist->Draw("COLZ");
      
  gPad->Update(); // necessary
  TF1 *top = new TF1("top", Form("%f + %f*x + %f*x*x + 2.5*TMath::Sqrt(TMath::Power(%f,2) + TMath::Power(%f,2)/x)", Param[0], Param[1], Param[2], Param[3], Param[4]), 0, 5);
  top->SetLineColor(kMagenta);
  top->SetLineStyle(kSolid);
  top->SetLineWidth(3);
  top->Draw("SAME");

  gPad->Update(); // necessary
  TF1 *center = new TF1("center", Form("%f + %f*x + %f*x*x", Param[0], Param[1], Param[2]), 0, 5);
  center->SetLineColor(kBlue);
  center->SetLineStyle(kSolid);
  center->SetLineWidth(3);
  center->Draw("SAME");

  gPad->Update(); // necessary
  TF1 *bottom = new TF1("bottom", Form("%f + %f*x + %f*x*x - 2.5*TMath::Sqrt(TMath::Power(%f,2) + TMath::Power(%f,2)/x)", Param[0], Param[1], Param[2], Param[3], Param[4]), 0, 5);
  bottom->SetLineColor(kMagenta);
  bottom->SetLineStyle(kSolid);
  bottom->SetLineWidth(3);
  bottom->Draw("SAME");
      
  c->Update();
}
