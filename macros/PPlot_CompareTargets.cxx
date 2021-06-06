#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawVerticalLine.cxx"

void PPlot_CompareTargets(TString kinvarOption = "wD") {

  /*** INPUT ***/

  TChain *treeExtractedD = new TChain();
  treeExtractedD->Add(gDataDir + "/C/*.root/mix");
  treeExtractedD->Add(gDataDir + "/Fe/*.root/mix");
  treeExtractedD->Add(gDataDir + "/Pb/*.root/mix");

  TChain *treeExtractedC = new TChain();
  treeExtractedC->Add(gDataDir + "/C/*.root/mix");

  TChain *treeExtractedFe = new TChain();
  treeExtractedFe->Add(gDataDir + "/Fe/*.root/mix");

  TChain *treeExtractedPb = new TChain();
  treeExtractedPb->Add(gDataDir + "/Pb/*.root/mix");

  // necessary for gCutKaons
  SetAliases(treeExtractedD);
  SetAliases(treeExtractedC);
  SetAliases(treeExtractedFe);
  SetAliases(treeExtractedPb);

  TString titleAxis;
  if (kinvarOption == "wD") titleAxis = "Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]";
  else if (kinvarOption == "wM") titleAxis = "Reconstructed Mass m(#pi^{+}#pi^{-}#pi^{0}) [GeV]";
  TString histProperties = "(150, 0.4, 1.9)";

  /*** MAIN ***/

  TH1D *theHistD;
  treeExtractedD->Draw(kinvarOption + ">>histD" + histProperties, gCutLiquid && gCutDIS && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  theHistD = (TH1D *)gROOT->FindObject("histD");

  theHistD->SetTitle("");
  
  theHistD->GetXaxis()->SetTitle(titleAxis);
  theHistD->GetXaxis()->SetTitleSize(0.04);
  theHistD->GetXaxis()->SetTitleOffset(1.2);

  theHistD->GetYaxis()->SetTitle("Counts");
  theHistD->GetYaxis()->SetMaxDigits(3);
  theHistD->GetYaxis()->SetTitleSize(0.04);
  theHistD->GetYaxis()->SetTitleOffset(1.2);
  theHistD->GetYaxis()->SetMaxDigits(3);

  theHistD->SetFillStyle(0);
  theHistD->SetLineColor(kGreen + 1);
  theHistD->SetLineWidth(3);

  TH1F *theHistFe;
  treeExtractedFe->Draw(kinvarOption + ">>histFe" + histProperties, gCutSolid && gCutDIS && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  theHistFe = (TH1F *)gROOT->FindObject("histFe");

  theHistFe->SetFillStyle(0);
  theHistFe->SetLineColor(kBlue);
  theHistFe->SetLineWidth(3);

  TH1F *theHistC;
  treeExtractedC->Draw(kinvarOption + ">>histC" + histProperties, gCutSolid && gCutDIS && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  theHistC = (TH1F *)gROOT->FindObject("histC");

  theHistC->SetFillStyle(0);
  theHistC->SetLineColor(kRed);
  theHistC->SetLineWidth(3);

  TH1F *theHistPb;
  treeExtractedPb->Draw(kinvarOption + ">>histPb" + histProperties, gCutSolid && gCutDIS && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  theHistPb = (TH1F *)gROOT->FindObject("histPb");

  theHistPb->SetFillStyle(0);
  theHistPb->SetLineColor(kBlack);
  theHistPb->SetLineWidth(3);

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

  TCanvas *c = new TCanvas("pplot-data_target-comparison", "pplot-data_target-comparison", 1200, 1200);

  theHistD->Draw("HIST");
  theHistFe->Draw("SAME HIST");
  theHistPb->Draw("SAME HIST");
  theHistC->Draw("SAME HIST");

  DrawVerticalLine(0.782, kMagenta, kDashed, 3, 1);

  TLegend *l = new TLegend(0.75, 0.65, 0.95, 0.85); // x1,y1,x2,y2
  l->AddEntry(theHistD, "D", "l");
  l->AddEntry(theHistFe, "Fe", "l");
  l->AddEntry(theHistC, "C", "l");
  l->AddEntry(theHistPb, "Pb", "l");
  l->SetFillStyle(0);
  l->SetTextFont(62);
  l->SetTextSize(0.04);
  l->SetBorderSize(0);
  l->Draw();

  c->Draw();
}
