#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "FitGaussian.cxx"
#include "GausParams.h"

#include "DrawVerticalLine.cxx"

void PPlot_Pi0Mass() {
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

  TH1D *theHist;
  dataTree->Draw("pi0M>>data(200, 0, 0.5)", gCutDIS && CutVertex && gCutRegion && gCutPhotonsOpAngle, "goff");
  theHist = (TH1D *)gROOT->FindObject("data");

  // style
  theHist->SetTitle("");
  theHist->SetMarkerColor(kBlack);
  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(2);
  theHist->SetFillStyle(0);

  theHist->GetYaxis()->SetTitle("Counts");
  theHist->GetYaxis()->SetTitleSize(0.04);
  theHist->GetYaxis()->SetTitleOffset(1.2);
  theHist->GetYaxis()->SetMaxDigits(3);

  theHist->GetXaxis()->SetTitle("Reconstructed Mass m(#gamma#gamma) [GeV]");
  theHist->GetXaxis()->SetTitleSize(0.04);
  theHist->GetXaxis()->SetTitleOffset(1.2);

  /*** FIT ***/

  GausParams Parameters;
  TF1 *Fit = new TF1("fit", "gaus", 0.115, 0.155);
  Fit->SetParameter(1, 0.1354);
  Fit->SetParameter(2, 0.0185);
  TFitResultPtr FitResult = theHist->Fit("fit", "SR"); // BEMSVR
  // save parameters
  Parameters.NormValue = FitResult->Parameter(0);
  Parameters.NormError = FitResult->ParError(0);
  Parameters.MeanValue = FitResult->Parameter(1);
  Parameters.MeanError = FitResult->ParError(1);
  Parameters.SigmaValue = FitResult->Parameter(2);
  Parameters.SigmaError = FitResult->ParError(2);

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

  TCanvas *can1 = new TCanvas("pplot-data_pi0-mass", "pplot-data_pi0-mass", 1200, 1200);
  
  theHist->Draw("E");

  // vert lines - cut
  DrawVerticalLine(Parameters.MeanValue - 3 * Parameters.SigmaValue, kRed, kDashed, 3, 1);
  DrawVerticalLine(Parameters.MeanValue + 3 * Parameters.SigmaValue, kRed, kDashed, 3, 1);

  // pave
  TString Chi2String = Form("#chi^{2}/ndf = %.4f", theHist->GetFunction("fit")->GetChisquare() / (Double_t)theHist->GetFunction("fit")->GetNDF());
  TString MeanString = Form("#mu = %.3f #pm %.6f", Parameters.MeanValue, Parameters.MeanError);
  TString SigmaString = Form("#sigma = %.3f #pm %.6f", Parameters.SigmaValue, Parameters.SigmaError);
  TPaveText *pav = new TPaveText(0.60, 0.50, 0.9, 0.75, "NDC NB");  // no border
  pav->AddText(Chi2String);
  pav->AddText(MeanString);
  pav->AddText(SigmaString);
  pav->SetFillStyle(0);
  pav->Draw();

  // legend
  TLegend *legend = new TLegend(0.60, 0.75, 0.85, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(theHist, "Data", "pl");
  legend->AddEntry(theHist->GetFunction("fit"), "Fit", "l");
  legend->SetFillStyle(0);
  legend->SetTextFont(62);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw();
}
