#include "CanvasPartition.cxx"
#include "DrawHorizontalLine.cxx"
#include "Global.h"

void CanvasMixingBkg() {
  // Work in progress...

  TString bkgFile = gProDir + "/MixingBkg/out/bkgmixC_42011.root";
  TChain *bkgTree = new TChain();
  bkgTree->Add(bkgFile + "/mix");

  TString dataFile = gProDir + "/FilterNCombine/out/comb_data-C.root";
  TChain *dataTree = new TChain();
  dataTree->Add(dataFile + "/mix");

  TString kinvarOption[4] = {"Q2", "Nu", "wZ", "wPt2"};
  Double_t EdgesKinvar[4][6];
  for (Int_t i = 0; i < 6; i++) EdgesKinvar[0][i] = kEdgesQ2[i];
  for (Int_t i = 0; i < 6; i++) EdgesKinvar[1][i] = kEdgesNu[i];
  for (Int_t i = 0; i < 6; i++) EdgesKinvar[2][i] = kEdgesZ[i];
  for (Int_t i = 0; i < 6; i++) EdgesKinvar[3][i] = kEdgesPt2[i];

  TH1D *dataHist = nullptr;
  TH1D *bkgHist = nullptr;

  gStyle->SetOptStat(0);

  TCanvas *C = (TCanvas *)gROOT->FindObject("C");
  if (C) delete C;
  C = new TCanvas("canvas-mixing-bkg", "C", 1600, 1200);
  C->SetFillStyle(4000);

  // number of pads
  const Int_t Ni = 5;
  const Int_t Nk = 4;

  // margins
  Float_t lMargin = 0.12;
  Float_t rMargin = 0.05;
  Float_t bMargin = 0.15;
  Float_t tMargin = 0.05;

  // canvas setup
  CanvasPartition(C, Ni, Nk, lMargin, rMargin, bMargin, tMargin);

  // define pads
  TPad *pad[Ni][Nk];

  TString auxCut;
  TCut CutBin;
  Int_t counter = 0;  // to move around pads

  Double_t dataNorm, bkgNorm;

  for (Int_t i = 0; i < Ni; i++) {    // ncolumns, on bins
    for (Int_t k = 0; k < Nk; k++) {  // nrows, on kinvars

      C->cd(0);

      auxCut = Form("%f", EdgesKinvar[k][i]);
      auxCut += " < " + kinvarOption[k] + " && " + kinvarOption[k] + " < ";
      auxCut += Form("%f", EdgesKinvar[k][i + 1]);
      CutBin = auxCut;

      // data
      dataTree->Draw("wD>>data(100, 0., 2.5)", gCutDIS && CutBin, "goff");
      dataHist = (TH1D *)gROOT->FindObject("data");
      /*
      dataHist->GetXaxis()->SetTitle("Reconstructed #Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]");
      dataHist->GetXaxis()->CenterTitle();
      dataHist->GetYaxis()->SetTitle("Normalized Candidates");
      dataHist->GetYaxis()->CenterTitle();
      dataHist->GetYaxis()->SetMaxDigits(3);
      */
      dataHist->SetMarkerColor(kBlack);
      dataHist->SetLineColor(kBlack);
      dataHist->SetLineWidth(2);
      dataHist->SetFillStyle(0);

      // mixed bkg
      bkgTree->Draw("wD>>bkg(100, 0., 2.5)", gCutDIS && CutBin, "goff");
      bkgHist = (TH1D *)gROOT->FindObject("bkg");

      bkgHist->SetMarkerColor(kRed);
      bkgHist->SetLineColor(kRed);
      bkgHist->SetLineWidth(2);
      bkgHist->SetFillStyle(0);

      // normalization
      dataNorm = dataHist->Integral(41, 47);
      std::cout << "dataNorm = " << dataNorm << std::endl;
      dataHist->Scale(1. / dataNorm);

      bkgNorm = bkgHist->Integral(41, 47);
      std::cout << "bkgNorm  = " << bkgNorm << std::endl;
      bkgHist->Scale(1. / bkgNorm);

      /*** DRAW ***/

      // get the pads previously created
      char pname[16];
      sprintf(pname, "pad_%i_%i", i, k);
      pad[i][k] = (TPad *)gROOT->FindObject(pname);
      pad[i][k]->Draw();
      pad[i][k]->SetFillStyle(4000);
      pad[i][k]->SetFrameFillStyle(4000);
      pad[i][k]->cd();

      // size factors
      Float_t xFactor = pad[0][0]->GetAbsWNDC() / pad[i][k]->GetAbsWNDC();
      Float_t yFactor = pad[0][0]->GetAbsHNDC() / pad[i][k]->GetAbsHNDC();

      char hname[16];
      sprintf(hname, "h_%i_%i", i, k);
      TH1F *hFrame = (TH1F *)dataHist->Clone(hname);
      hFrame->Reset();
      hFrame->Draw();

      // y axis range
      hFrame->GetYaxis()->SetRangeUser(0.0001, 1.2 * dataHist->GetMaximum());

      // Format for y axis
      hFrame->GetYaxis()->SetLabelFont(43);
      hFrame->GetYaxis()->SetLabelSize(16);
      hFrame->GetYaxis()->SetLabelOffset(0.02);
      hFrame->GetYaxis()->SetTitleFont(43);
      hFrame->GetYaxis()->SetTitleSize(16);
      hFrame->GetYaxis()->SetTitleOffset(5);

      hFrame->GetYaxis()->CenterTitle();
      hFrame->GetYaxis()->SetNdivisions(505);

      // TICKS Y Axis
      hFrame->GetYaxis()->SetTickLength(xFactor * 0.04 / yFactor);

      // Format for x axis
      hFrame->GetXaxis()->SetLabelFont(43);
      hFrame->GetXaxis()->SetLabelSize(16);
      hFrame->GetXaxis()->SetLabelOffset(0.02);
      hFrame->GetXaxis()->SetTitleFont(43);
      hFrame->GetXaxis()->SetTitleSize(16);
      hFrame->GetXaxis()->SetTitleOffset(5);
      hFrame->GetXaxis()->CenterTitle();
      hFrame->GetXaxis()->SetNdivisions(505);

      // TICKS X Axis
      hFrame->GetXaxis()->SetTickLength(yFactor * 0.06 / xFactor);

      // draw
      /*
      c->cd(1);
      std::cout << "counter  = " << counter << std::endl;
      counter++;
      */

      dataHist->Draw("E");
      bkgHist->Draw("E SAME");

      // c->Update();
    }
  }

  C->cd();

  /*
  TLegend *legend0 = new TLegend(0.65, 0.65, 0.8, 0.8); // x1,y1,x2,y2
  legend0->AddEntry(dataHist, "Data", "lp");
  legend0->AddEntry(bkgHist, "Mixed Bkg", "lp");
  legend0->Draw();
  */
}
