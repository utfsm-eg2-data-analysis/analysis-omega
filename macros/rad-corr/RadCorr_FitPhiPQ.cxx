#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

void RadCorr_FitPhiPQ(TString targetOption = "C") {
  // Radiative corrections: fit eta or omega PhiPQ distributions

  /*** INPUT ***/

  TString dataFile1, dataFile2, dataFile3;
  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
    dataFile1 = gDataDir + "/C/*.root";
    dataFile2 = gDataDir + "/Fe/*.root";
    dataFile3 = gDataDir + "/Pb/*.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    dataFile1 = gDataDir + "/" + targetOption + "/*.root";
  }

  TChain *dataTree = new TChain();
  dataTree->Add(dataFile1 + "/mix");
  if (targetOption == "D" || targetOption == "All") {
    dataTree->Add(dataFile2 + "/mix");
    dataTree->Add(dataFile3 + "/mix");
  }

  // necessary for gCutKaons
  SetAliases(dataTree);

  TH1D *theHist1;
  dataTree->Draw("wPhiPQ>>data1(36, -180, 180)", gCutDIS && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle && gCutRegion, "goff");
  theHist1 = (TH1D *)gROOT->FindObject("data1");

  theHist1->SetTitle("");
  theHist1->GetYaxis()->SetTitle("Counts");
  theHist1->GetYaxis()->SetTitleSize(0.04);
  theHist1->GetYaxis()->SetTitleOffset(1.2);
  theHist1->GetYaxis()->SetMaxDigits(3);

  theHist1->GetXaxis()->SetTitle("#phi_{PQ} [deg]");
  theHist1->GetXaxis()->SetTitleSize(0.04);
  theHist1->GetXaxis()->SetTitleOffset(1.2);

  // style
  theHist1->SetMarkerColor(kBlack);
  theHist1->SetLineColor(kBlack);
  theHist1->SetLineWidth(2);
  theHist1->SetFillStyle(0);

  /*** CANVAS ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLineWidth(2);

  // set margin sizes
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);

  gStyle->SetOptStat(0);

  TCanvas *can1 = new TCanvas("rc_phi-pq_" + targetOption, "rc_phi-pq_" + targetOption, 1000, 1000);

  /*** FIT & DRAW ***/

  TF1 *func = new TF1("fit", "[0]+[1]*TMath::Cos(x*TMath::DegToRad())+[2]*TMath::Cos(2*x*TMath::DegToRad())");
  theHist1->Fit(func, "Q");
  theHist1->Draw("E");

  // pave
  TString Chi2String = Form("#chi^{2}/ndf = %.4f", func->GetChisquare() / (Double_t)func->GetNDF());
  TString A_String = Form("A = %.3f #pm %.3f", func->GetParameter(0), func->GetParError(0));
  TString Ac_String = Form("A_{c} = %.3f #pm %.6f", func->GetParameter(1), func->GetParError(1));
  TString Acc_String = Form("A_{cc} = %.3f #pm %.6f", func->GetParameter(2), func->GetParError(2));
  TPaveText *pav2 = new TPaveText(0.70, 0.66, 0.96, 0.96, "NDC NB");  // no border
  pav2->AddText("Fit on integrated " + targetOption + " data");
  pav2->AddText(Chi2String);
  pav2->AddText(A_String);
  pav2->AddText(Ac_String);
  pav2->AddText(Acc_String);
  pav2->SetBorderSize(0);
  pav2->SetTextAlign(12);
  pav2->SetFillStyle(0);
  pav2->Draw();
}
