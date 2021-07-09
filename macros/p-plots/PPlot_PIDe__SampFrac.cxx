#ifndef GLOBAL_H
#include "Global.h"
#endif

// for data
const Double_t kCPar[6][5] = {{0.252164, 0.0122263 , -0.000793937, 9.55113e-03, 3.40672e-02},
			      {0.278574, 0.0187482 , -0.00238217 , 1.39889e-02, 3.74682e-02},
			      {0.262079, 0.0230685 , -0.00354741 , 9.32762e-03, 2.90046e-02},
			      {0.251108, 0.0201568 , -0.00332367 , 8.21055e-03, 2.98893e-02},
			      {0.263396, 0.00955238, -0.00102038 , 2.25684e-02, 3.06508e-02},
			      {0.255245, 0.0232659 , -0.00304798 , 1.17254e-02, 3.64221e-02}};

const Double_t kFePar[6][5] = {{0.222404, 0.0222688, -0.0024153 , 9.23027e-03, 2.98343e-02},
			       {0.234623, 0.0194985, -0.00208357, 8.66367e-03, 3.08858e-02},
			       {0.252287, 0.024248 , -0.00338846, 1.07826e-02, 2.63854e-02},
			       {0.250946, 0.0208409, -0.00326824, 7.22581e-03, 2.98809e-02},
			       {0.271956, 0.0118487, -0.00187084, 1.84073e-02, 3.48029e-02},
			       {0.252613, 0.022819 , -0.00311242, 4.11461e-03, 3.55081e-02}};

const Double_t kPbPar[6][5] = {{0.253431, 0.0138251, -0.00140160, 7.67408e-03, 3.54391e-02},
			       {0.249059, 0.0147784, -0.00148693, 7.52798e-03, 3.38371e-02},
			       {0.254573, 0.0225890, -0.00305686, 8.13241e-03, 2.77300e-02},
			       {0.255589, 0.0190419, -0.00305263, 7.20303e-03, 3.03627e-02},
			       {0.276739, 0.0111585, -0.00175784, 1.80841e-02, 3.53020e-02},
			       {0.262587, 0.0191659, -0.0026264 , 1.99220e-03, 3.76172e-02}};


void PPlot_PIDe__SampFrac(TString targetOption = "C") {
  // Particular plot, PID electrons, Sampling Fraction Cut

  TChain *InputChain = new TChain();
  InputChain->Add(gWorkDir + "/out/TestPID/pruned" + targetOption + "_*_noec.root/ntuple_e");
  
  TH2D *Hist[6];
  for (Int_t Sector = 0; Sector < 6; Sector++) {
    InputChain->Draw(Form("TMath::Max(Etot, Eout+Ein)/P:P>>hist_%d(80, 0., 5., 80, 0, 0.5)", Sector), Form("Sector == %d", Sector), "goff");
    Hist[Sector] = (TH2D *)gROOT->FindObject(Form("hist_%d", Sector));

    Hist[Sector]->SetTitle(Form("Sector %d", Sector));
    Hist[Sector]->GetYaxis()->SetTitle("E/P");
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
  TCanvas *c = new TCanvas("pplot-samp-frac", "pplot-samp-frac", 1500, 1000);
  c->Divide(Nx, Ny, 0.001, 0.001);
  
  c->SetFrameLineWidth(2);

  // fill parameters
  Double_t Param[6][5];
  if (targetOption == "C") {
    for (Int_t i = 0; i < 6; i++) for (Int_t j = 0; j < 5; j++) Param[i][j] = kCPar[i][j];
  } else if (targetOption == "Fe") {
    for (Int_t i = 0; i < 6; i++) for (Int_t j = 0; j < 5; j++) Param[i][j] = kFePar[i][j];
  } else if (targetOption == "Pb") {
    for (Int_t i = 0; i < 6; i++) for (Int_t j = 0; j < 5; j++) Param[i][j] = kPbPar[i][j];
  }
  
  Int_t counter = 1;
  for (Int_t i = 0; i < Nx; i++) {
    for (Int_t j = 0; j < Ny; j++) {

      c->cd(counter);
      Hist[counter-1]->Draw("COLZ");

      gPad->Update(); // necessary
      TF1 *top = new TF1(Form("top_%d%d", i, j), Form("%f + %f*x + %f*x*x + 2.5*TMath::Sqrt(TMath::Power(%f,2) + TMath::Power(%f,2)/x)", Param[counter-1][0], Param[counter-1][1], Param[counter-1][2], Param[counter-1][3], Param[counter-1][4]), 0, 5);
      top->SetLineColor(kMagenta);
      top->SetLineStyle(kSolid);
      top->SetLineWidth(3);
      top->Draw("SAME");

      gPad->Update(); // necessary
      TF1 *center = new TF1(Form("center_%d%d",i,j), Form("%f + %f*x + %f*x*x", Param[counter-1][0], Param[counter-1][1], Param[counter-1][2]), 0, 5);
      center->SetLineColor(kBlue);
      center->SetLineStyle(kSolid);
      center->SetLineWidth(3);
      center->Draw("SAME");

      gPad->Update(); // necessary
      TF1 *bottom = new TF1(Form("bottom_%d%d",i,j), Form("%f + %f*x + %f*x*x - 2.5*TMath::Sqrt(TMath::Power(%f,2) + TMath::Power(%f,2)/x)", Param[counter-1][0], Param[counter-1][1], Param[counter-1][2], Param[counter-1][3], Param[counter-1][4]), 0, 5);
      bottom->SetLineColor(kMagenta);
      bottom->SetLineStyle(kSolid);
      bottom->SetLineWidth(3);
      bottom->Draw("SAME");

      c->Update();
      counter++;
    }
  }
}
