#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "DrawHorizontalLine.cxx"
#include "DrawVerticalLine.cxx"

void RadCorr_ExternalsBinning() {

  // Custom binning, based on gExternalsDir/Utilities/include/Binning.hxx
  Double_t kEdgesNu_extern[7] = {2.2, 2.58, 2.96, 3.35, 3.68, 3.94, 4.2};
  Double_t kEdgesQ2_extern[6] = {1, 1.25, 1.51, 1.92, 2.96, 4.0};

  const Int_t NedgesNu = (Int_t)(sizeof(kEdgesNu_extern) / sizeof(kEdgesNu_extern[0]));
  const Int_t NedgesQ2 = (Int_t)(sizeof(kEdgesQ2_extern) / sizeof(kEdgesQ2_extern[0]));

  /*** INPUT ***/

  TChain *InputChain = new TChain();
  InputChain->Add(gWorkDir + "/out/GetSimpleTuple/data/Pb/*.root/ntuple_e");

  TH2D *Hist;
  InputChain->Draw("Q2:Nu>>hist(200, 2.2, 4.2, 200, 1., 4.)", "Q2 > 1 && W > 2 && TargType == 2 && vyec > -1.4 && vyec < 1.4", "goff");
  Hist = (TH2D *)gROOT->FindObject("hist");

  Hist->SetTitle("");
  Hist->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
  Hist->GetYaxis()->SetTitleOffset(1.5);
  Hist->GetXaxis()->SetTitle("#nu [GeV]");
  Hist->GetXaxis()->SetTitleOffset(1.5);

  /*** DRAW ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(kDarkBodyRadiator);
  // gStyle->SetTitleY(0.95);
  gStyle->SetNumberContours(255);

/*
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
*/

  // define canvas
  TCanvas *c = new TCanvas("externals_binning", "externals_binning", 1000, 1000);

  c->SetFrameLineWidth(2);

  Hist->Draw("COLZ");

  for (Int_t q = 0; q < NedgesQ2; q++) {
    DrawHorizontalLine(kEdgesQ2_extern[q], kGreen, kSolid, 5);
  }

  for (Int_t n = 0; n < NedgesNu; n++) {
    DrawVerticalLine(kEdgesNu_extern[n], kGreen, kSolid, 5);
  }
}
