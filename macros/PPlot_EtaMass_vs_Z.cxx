#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "DrawHorizontalLine.cxx"
#include "DrawVerticalLine.cxx"

void PPlot_EtaMass_vs_Z() {
  // Particular plot, Eta mass vs Z, to demostrate why z > 0.5

  TString dataFile1, dataFile2, dataFile3;
  TCut CutVertex = gCutSolid || gCutLiquid;
  dataFile1 = gDataDir_Eta + "/C/*.root";
  dataFile2 = gDataDir_Eta + "/Fe/*.root";
  dataFile3 = gDataDir_Eta + "/Pb/*.root";

  TChain *dataTree = new TChain();
  dataTree->Add(dataFile1 + "/mix");
  dataTree->Add(dataFile2 + "/mix");
  dataTree->Add(dataFile3 + "/mix");
  
  /*** HIST 2D ***/

  TH2D *theHist;
  dataTree->Draw("eM:eZ>>hist(100, 0.0, 1., 150, 0.25, 1.25)", gCutDIS && CutVertex && "Q2 < 4.1 && Nu > 2.2 && Nu < 4.25 && ePt2 > 0 && ePt2 < 1.5", "goff");
  theHist = (TH2D *)gROOT->FindObject("hist");

  theHist->SetTitle("");
  theHist->GetYaxis()->SetTitle("Reconstructed Mass m(#gamma#gamma) [GeV]");
  theHist->GetYaxis()->SetTitleSize(0.04);
  theHist->GetYaxis()->SetTitleOffset(1.2);

  theHist->GetXaxis()->SetTitle("z_{h}");
  theHist->GetXaxis()->SetTitleSize(0.04);
  theHist->GetXaxis()->SetTitleOffset(1.2);

  /*** DRAW ***/

  TCanvas *can = new TCanvas("pplot-data_eta-mass_vs_z", "pplot-data_eta-mass_vs_z", 1080, 1080);

  gStyle->SetPalette(kDarkBodyRadiator);
  gStyle->SetNumberContours(255);
  
  theHist->Draw("COLZ");

  // lines
  DrawVerticalLine(0.5, kMagenta, kDashed, 3, 0);
}
