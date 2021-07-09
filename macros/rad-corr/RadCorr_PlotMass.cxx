#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawVerticalLine.cxx"

void RadCorr_PlotMass(TString TargetOption = "C") {
  // This macro plots both Invariant Mass and Invariant Mass Difference.

  /*** FROM HAPRAD RESULTS ***/

  const Int_t NbinsPhiPQ = 36;
  Double_t RCFactor_D[NbinsPhiPQ] = {1.00401,  1.00062,  0.996976, 0.993575, 0.989287, 0.984232, 0.981843, 0.977888, 0.976074, 0.974846, 0.973701, 0.972742,
                                     0.973556, 0.977196, 0.977136, 0.98105,  0.980079, 0.984137, 0.984373, 0.982458, 0.980957, 0.97604,  0.975704, 0.97354,
                                     0.974441, 0.973517, 0.974098, 0.975463, 0.979719, 0.982163, 0.985791, 0.989851, 0.993393, 0.998216, 1.00104,  1.00361};

  Double_t RCFactor_C[NbinsPhiPQ] = {1.00611,  0.999387, 0.999109, 0.996387, 0.990108, 0.990388, 0.980931, 0.979933, 0.976201, 0.976228, 0.973176, 0.972362,
                                     0.972618, 0.976226, 0.974633, 0.974744, 0.976079, 0.981607, 0.978517, 0.974801, 0.977436, 0.975629, 0.979132, 0.97782,
                                     0.971385, 0.972906, 0.974918, 0.973108, 0.979427, 0.984098, 0.985218, 0.985892, 0.994796, 0.999506, 1.00284,  1.00545};

  Double_t RCFactor_Fe[NbinsPhiPQ] = {1.0043,   1.00541,  1.00136,  0.995856, 0.992444, 0.98753,  0.98448,  0.982106, 0.97482,  0.976609, 0.972847, 0.973629,
                                      0.972701, 0.974574, 0.972677, 0.978659, 0.979499, 0.982251, 0.982291, 0.982521, 0.973791, 0.977526, 0.972785, 0.968137,
                                      0.974027, 0.971485, 0.975673, 0.977838, 0.980067, 0.981329, 0.985666, 0.992388, 0.99659,  0.998891, 1.00455,  1.00416};

  Double_t RCFactor_Pb[NbinsPhiPQ] = {1.00429,  1.0047,   1.00255,  0.994605, 0.991352, 0.986609, 0.983351, 0.981668, 0.980889, 0.972566, 0.972924, 0.967351,
                                      0.97149,  0.971786, 0.969123, 0.976616, 0.972771, 0.971643, 0.978628, 0.97994,  0.980028, 0.981809, 0.96969,  0.969394,
                                      0.974774, 0.971849, 0.976992, 0.978449, 0.975794, 0.978614, 0.991422, 0.995656, 0.997792, 1.00198,  1.00308,  1.00606};

  /*** INPUT ***/

  Double_t RCFactor_Target[NbinsPhiPQ];  // according to TargetOption
  if (TargetOption == "D") {
    for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) RCFactor_Target[pp] = RCFactor_D[pp];
  } else if (TargetOption == "C") {
    for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) RCFactor_Target[pp] = RCFactor_C[pp];
  } else if (TargetOption == "Fe") {
    for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) RCFactor_Target[pp] = RCFactor_Fe[pp];
  } else if (TargetOption == "Pb") {
    for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) RCFactor_Target[pp] = RCFactor_Pb[pp];
  }

  TCut CutVertex;
  TChain *treeExtracted = new TChain();
  if (TargetOption == "D") {
    CutVertex = gCutLiquid;
    treeExtracted->Add(gDataDir + "/C/*.root/mix");
    treeExtracted->Add(gDataDir + "/Fe/*.root/mix");
    treeExtracted->Add(gDataDir + "/Pb/*.root/mix");
  } else if (TargetOption == "C" || TargetOption == "Fe" || TargetOption == "Pb") {
    CutVertex = gCutSolid;
    treeExtracted->Add(gDataDir + "/" + TargetOption + "/*.root/mix");
  }
  SetAliases(treeExtracted);  // necessary for gCutKaons

  /*** MAIN ***/

  TString titleAxis = "Reconstructed Mass [GeV]";
  TString histProperties = "(120, 0.4, 2.6)";

  TH1D *theHistMassDiff;
  treeExtracted->Draw("wD>>imd" + histProperties, gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && gCutRegion, "goff");
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

  /*** DRAW PARTIAL HISTS ***/

  TH1D *partial[NbinsPhiPQ];
  Double_t MaxPhiPQ = 180.;
  Double_t MinPhiPQ = -180.;
  Double_t DeltaPhiPQ = (MaxPhiPQ - MinPhiPQ) / (Double_t)NbinsPhiPQ;
  Double_t LowEdge, HighEdge;
  TCut CutPhiPQ;
  for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) {
    LowEdge = MinPhiPQ + DeltaPhiPQ * pp;
    HighEdge = LowEdge + DeltaPhiPQ;
    CutPhiPQ = Form("wPhiPQ > %.2f && wPhiPQ < %.2f", LowEdge, HighEdge);
    treeExtracted->Draw(Form("wD>>partial_%d", pp) + histProperties, gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && gCutRegion && CutPhiPQ, "goff");
    partial[pp] = (TH1D *)gROOT->FindObject(Form("partial_%d", pp));
  }

  /*** CORRECT PARTIAL HISTS ***/

  // these histograms contain the factors with null error,
  // for later multiplication and keeping the uncorrected error bars unchanged
  TH1D *corr_factor[NbinsPhiPQ];
  for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) {
    corr_factor[pp] = new TH1D(Form("corr_factor_%d", pp), Form("corr_factor_%d", pp), 120, 0.4, 2.6);
    for (Int_t i = 0; i < 120; i++) {
      corr_factor[pp]->SetBinContent(i + 1, RCFactor_Target[pp]);
      corr_factor[pp]->SetBinError(i + 1, 0);
    }
  }

  TH1D *partial_corr[NbinsPhiPQ];
  for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) {
    partial_corr[pp] = new TH1D(Form("partial_corr_%d", pp), Form("partial_corr_%d", pp), 120, 0.4, 2.6);
    partial_corr[pp]->Divide(partial[pp], corr_factor[pp]);
  }

  /*** SUM PARTIAL HISTS ***/

  TH1D *sum = new TH1D("sum", "sum", 120, 0.4, 2.6);  // same as histProperties
  for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) {
    sum->Add(partial_corr[pp]);
  }

  sum->SetFillStyle(0);
  sum->SetLineColor(kBlack);
  sum->SetLineStyle(kDashed);
  sum->SetLineWidth(3);

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

  TCanvas *c = new TCanvas("rc-mass_haprad_" + TargetOption, "rc-mass_haprad_" + TargetOption, 1200, 1200);

  theHistMassDiff->Draw("HIST");
  sum->Draw("SAME HIST");

  DrawVerticalLine(0.782, kMagenta, kDashed, 3, 1);
  DrawVerticalLine(0.548, kOrange + 7, kDashed, 3, 1);

  TLegend *l = new TLegend(0.5, 0.75, 0.9, 0.9);  // x1,y1,x2,y2
  l->SetHeader("#omega candidates, " + TargetOption + " data", "C");
  l->AddEntry(theHistMassDiff, "#Deltam(#pi^{+}#pi^{-}#pi^{0}), Uncorr.", "l");
  l->AddEntry(sum, "#Deltam(#pi^{+}#pi^{-}#pi^{0}), Rad. Corr.", "l");
  l->SetFillStyle(0);
  l->SetTextFont(42);
  l->SetTextSize(0.026);
  l->SetBorderSize(0);
  l->Draw();

  c->Draw();
}
