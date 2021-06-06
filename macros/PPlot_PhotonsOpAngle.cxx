#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawVerticalLine.cxx"

void PPlot_PhotonsOpAngle() {
  // Particular plot: invariant mass reconstruction and selection of the pi0.

  /*** INPUT ***/

  TString dataFile1, dataFile2, dataFile3;
  TCut CutVertex = gCutSolid || gCutLiquid;
  dataFile1 = gDataDir + "/C/*.root";
  dataFile2 = gDataDir + "/Fe/*.root";
  dataFile3 = gDataDir + "/Pb/*.root";

  TChain *dataTree = new TChain();
  dataTree->Add(dataFile1 + "/mix");
  dataTree->Add(dataFile2 + "/mix");
  dataTree->Add(dataFile3 + "/mix");

  // necessary for gCutKaons
  SetAliases(dataTree);

  TH1D *theHist1;
  dataTree->Draw("deltaTheta[2]>>data1(120, 0, 90)", gCutDIS && CutVertex && gCutRegion, "goff");
  theHist1 = (TH1D *)gROOT->FindObject("data1");

  TH1D *theHist2;
  dataTree->Draw("deltaTheta[3]>>data2(120, 0, 90)", gCutDIS && CutVertex && gCutRegion, "goff");
  theHist2 = (TH1D *)gROOT->FindObject("data2");
  
  theHist1->SetTitle("");
  theHist1->GetYaxis()->SetTitle("Counts");
  theHist1->GetYaxis()->SetTitleSize(0.04);
  theHist1->GetYaxis()->SetTitleOffset(1.2);
  theHist1->GetYaxis()->SetMaxDigits(3);

  theHist1->GetXaxis()->SetTitle("#alpha_{e#gamma} [deg]");
  theHist1->GetXaxis()->SetTitleSize(0.04);
  theHist1->GetXaxis()->SetTitleOffset(1.2);

  // style
  theHist1->SetMarkerColor(kBlack);
  theHist1->SetLineColor(kBlack);
  theHist1->SetLineWidth(2);
  theHist1->SetFillStyle(0);

  theHist2->SetMarkerColor(kBlue);
  theHist2->SetLineColor(kBlue);
  theHist2->SetLineWidth(2);
  theHist2->SetFillStyle(0);
  
  /*** DRAW ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLineWidth(2);
  
  // set margin sizes
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);

  gStyle->SetOptStat(0);

  TCanvas *can1 = new TCanvas("pplot-data_photons-op-angle", "pplot-data_photons-op-angle", 1200, 1200);

  theHist1->Draw("E");
  theHist2->Draw("E SAME");

  // vert line - cut
  DrawVerticalLine(12, kRed, kDashed, 3, 1);

  // legend
  TLegend *legend = new TLegend(0.60, 0.75, 0.85, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(theHist1, "#gamma_{1}", "pl");
  legend->AddEntry(theHist2, "#gamma_{2}", "pl");
  legend->SetFillStyle(0);
  legend->SetTextFont(62);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw();
}
