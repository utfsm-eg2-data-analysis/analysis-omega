#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawVerticalLine.cxx"

void PPlot_CompareMasses() {
  // This macro plots both Invariant Mass and Invariant Mass Difference.
  
  /*** INPUT ***/

  TCut CutVertex = gCutLiquid || gCutSolid;
  TString inputFile1 = gDataDir + "/C/*.root";
  TString inputFile2 = gDataDir + "/Fe/*.root";
  TString inputFile3 = gDataDir + "/Pb/*.root";

  TString titleAxis = "Reconstructed Mass [GeV]";
  TString histProperties = "(120, 0.4, 2.6)";

  /*** MAIN ***/

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
    
  // necessary for gCutKaons
  SetAliases(treeExtracted);

  TH1D *theHistMassDiff;
  treeExtracted->Draw("wD>>imd" + histProperties, gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  theHistMassDiff = (TH1D *)gROOT->FindObject("imd");

  theHistMassDiff->SetTitle("");
  
  theHistMassDiff->GetXaxis()->SetTitle(titleAxis);
  theHistMassDiff->GetXaxis()->SetTitleSize(0.04);
  theHistMassDiff->GetXaxis()->SetTitleOffset(1.2);

  theHistMassDiff->GetYaxis()->SetTitle("Counts");
  theHistMassDiff->GetYaxis()->SetMaxDigits(3);
  theHistMassDiff->GetYaxis()->SetTitleSize(0.04);
  theHistMassDiff->GetYaxis()->SetTitleOffset(1.2);
  theHistMassDiff->GetYaxis()->SetMaxDigits(3);

  theHistMassDiff->SetFillStyle(0);
  theHistMassDiff->SetLineColor(kRed);
  theHistMassDiff->SetLineWidth(3);

  TH1D *theHistInvMass;
  treeExtracted->Draw("wM>>im" + histProperties, gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  theHistInvMass = (TH1D *)gROOT->FindObject("im");

  theHistInvMass->SetFillStyle(0);
  theHistInvMass->SetLineColor(kBlack);
  theHistInvMass->SetLineStyle(kDashed);
  theHistInvMass->SetLineWidth(3);

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

  TCanvas *c = new TCanvas("pplot-data_mass-comparison", "pplot-data_mass-comparison", 1200, 1200);

  theHistMassDiff->Draw("HIST");
  theHistInvMass->Draw("SAME HIST");

  DrawVerticalLine(0.782, kMagenta, kDashed, 3, 1);
  DrawVerticalLine(0.548, kOrange + 7, kDashed, 3, 1);
  
  TLegend *l = new TLegend(0.5, 0.75, 0.9, 0.9); // x1,y1,x2,y2
  l->AddEntry(theHistInvMass, "m(#pi^{+}#pi^{-}#pi^{0})", "l");
  l->AddEntry(theHistMassDiff, "#Deltam(#pi^{+}#pi^{-}#pi^{0}) = m(#pi^{+}#pi^{-}#pi^{0}) - m(#gamma#gamma) + M(#pi^{0})", "l");
  l->SetFillStyle(0);
  l->SetTextFont(42);
  l->SetTextSize(0.026);
  l->SetBorderSize(0);
  l->Draw();

  c->Draw();
}
