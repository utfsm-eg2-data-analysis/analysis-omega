#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawVerticalLine.cxx"

void PPlot_CompareMasses_Eta() {
  // This macro plots Invariant Mass and Invariant Mass with Kin. Region cuts.
  
  /*** INPUT ***/

  TCut CutVertex = gCutLiquid || gCutSolid;
  TString inputFile1 = gDataDir_Eta + "/C/*.root";
  TString inputFile2 = gDataDir_Eta + "/Fe/*.root";
  TString inputFile3 = gDataDir_Eta + "/Pb/*.root";

  TString titleAxis = "Reconstructed Mass m(#gamma#gamma) [GeV]";
  TString histProperties = "(150, 0., 1.)";

  /*** MAIN ***/

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
    
  // necessary for gCutKaons
  SetAliases(treeExtracted);

  TH1D *theHistMassDiff;
  treeExtracted->Draw("eM>>nocut" + histProperties, gCutDIS && CutVertex && gCutPhotonsOpAngle_Eta, "goff");
  theHistMassDiff = (TH1D *)gROOT->FindObject("nocut");

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
  theHistMassDiff->SetLineColor(kBlack);
  theHistMassDiff->SetLineWidth(3);

  TH1D *theHistInvMass;
  treeExtracted->Draw("eM>>withcut" + histProperties, gCutDIS && CutVertex && gCutPhotonsOpAngle_Eta && gCutRegion_Eta, "goff");
  theHistInvMass = (TH1D *)gROOT->FindObject("withcut");

  theHistInvMass->SetFillStyle(0);
  theHistInvMass->SetLineColor(kBlue);
  theHistInvMass->SetLineWidth(3);

  TH1D *etaCandidates;
  treeExtracted->Draw("eM>>etas" + histProperties, gCutDIS && CutVertex && gCutPhotonsOpAngle_Eta && gCutRegion_Eta && "eM > 0.4 && eM < 0.72", "goff");
  etaCandidates = (TH1D *)gROOT->FindObject("etas");

  etaCandidates->SetFillStyle(1);
  etaCandidates->SetFillColor(kRed);
  etaCandidates->SetLineColor(kRed);
  
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

  TCanvas *c = new TCanvas("pplot-data_eta-mass-comparison", "pplot-data_eta-mass-comparison", 1200, 1200);

  theHistMassDiff->Draw("HIST");
  etaCandidates->Draw("SAME HIST");
  theHistInvMass->Draw("SAME HIST");

  // DrawVerticalLine(0.782, kMagenta, kDashed, 3, 1);
  // DrawVerticalLine(0.548, kOrange + 7, kDashed, 3, 1);
  
  TLegend *l = new TLegend(0.5, 0.75, 0.9, 0.9); // x1,y1,x2,y2
  l->AddEntry(theHistMassDiff, "All #gamma pairs", "l");
  l->AddEntry(theHistInvMass, "All #gamma pairs with Kinematical Limits", "l");
  l->SetFillStyle(0);
  l->SetTextFont(42);
  l->SetTextSize(0.026);
  l->SetBorderSize(0);
  l->Draw();

  c->Draw();
}
