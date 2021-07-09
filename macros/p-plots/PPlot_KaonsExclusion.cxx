#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "FitGaussian.cxx"
#include "GausParams.h"

#include "DrawHorizontalLine.cxx"
#include "DrawVerticalLine.cxx"

void PPlot_KaonsExclusion() {
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

  /*** HIST 1D ***/

  TH1D *theHist;
  dataTree->Draw("pippimM*pippimM>>data(120, 0.16, 0.64)", gCutDIS && CutVertex && gCutRegion, "goff");  // 0.4, 0.8
  theHist = (TH1D *)gROOT->FindObject("data");

  theHist->SetTitle("");
  theHist->GetYaxis()->SetTitle("Counts");
  theHist->GetYaxis()->SetTitleSize(0.04);
  theHist->GetYaxis()->SetTitleOffset(1.2);
  theHist->GetYaxis()->SetMaxDigits(3);

  theHist->GetXaxis()->SetTitle("Reconstructed Mass m^{2}(#pi^{+}#pi^{-}) [GeV]");
  theHist->GetXaxis()->SetTitleSize(0.04);
  theHist->GetXaxis()->SetTitleOffset(1.2);

  // style
  theHist->SetMarkerColor(kBlack);
  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(2);
  theHist->SetFillStyle(0);

  /*** HIST 2D ***/

  TH2D *theDalitzHist;
  dataTree->Draw("pippimM*pippimM:pippi0M*pippi0M>>dalitz(120, 0.0, 1.2, 120, 0.0, 1.2)", gCutDIS && CutVertex && gCutRegion && gCutPi0, "goff");
  theDalitzHist = (TH2D *)gROOT->FindObject("dalitz");

  theDalitzHist->SetTitle("");
  theDalitzHist->GetYaxis()->SetTitle("Reconstructed Mass m^{2}(#pi^{+}#pi^{-}) [GeV]");
  theDalitzHist->GetYaxis()->SetTitleSize(0.04);
  theDalitzHist->GetYaxis()->SetTitleOffset(1.2);

  theDalitzHist->GetXaxis()->SetTitle("Reconstructed Mass m^{2}(#pi^{+}#pi^{0}) [GeV]");
  theDalitzHist->GetXaxis()->SetTitleSize(0.04);
  theDalitzHist->GetXaxis()->SetTitleOffset(1.2);

  /*** FIT ***/

  GausParams Parameters;
  TF1 *Fit = new TF1("fit", "gaus", 0.240, 0.255);
  Fit->SetParameter(1, 2.47e-1);
  Fit->SetParameter(2, 1.5e-2);
  Fit->SetLineColor(kOrange + 10);
  TFitResultPtr FitResult = theHist->Fit("fit", "BEMSVR");
  // save parameters
  Parameters.NormValue = Fit->GetParameter(0);
  Parameters.NormError = Fit->GetParError(0);
  Parameters.MeanValue = Fit->GetParameter(1);
  Parameters.MeanError = Fit->GetParError(1);
  Parameters.SigmaValue = Fit->GetParameter(2);
  Parameters.SigmaError = Fit->GetParError(2);

  /*** DRAW ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  //gStyle->SetLineWidth(2);

  // set margin sizes
  /*
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  */
  gStyle->SetOptStat(0);

  const Int_t Nx = 2;
  const Int_t Ny = 1;
  TCanvas *can1 = new TCanvas("pplot-data_kaons-exclusion", "pplot-data_kaons-exclusion", 1080, 540);
  can1->Divide(Nx, Ny, 0.001, 0.001);

  // left hist
  can1->cd(1);

  theHist->Draw("E");

  // vert line - cut
  DrawVerticalLine(Parameters.MeanValue - 1 * Parameters.SigmaValue, kOrange + 10, kDashed, 3, 0);
  DrawVerticalLine(Parameters.MeanValue + 1 * Parameters.SigmaValue, kOrange + 10, kDashed, 3, 0);

  // pave
  TString Chi2String = Form("#chi^{2}/ndf = %.4f", theHist->GetFunction("fit")->GetChisquare() / (Double_t)theHist->GetFunction("fit")->GetNDF());
  TString MeanString = Form("#mu = %.3f +- %.6f", Parameters.MeanValue, Parameters.MeanError);
  TString SigmaString = Form("#sigma = %.3f +- %.6f", Parameters.SigmaValue, Parameters.SigmaError);
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

  can1->Update();

  // right hist
  can1->cd(2);

  can1->SetLogz();
  
  gStyle->SetPalette(kDarkBodyRadiator);
  gStyle->SetNumberContours(255);

  theDalitzHist->Draw("COLZ");

  DrawHorizontalLine(Parameters.MeanValue - 1 * Parameters.SigmaValue, kMagenta, kDashed, 3, 0);
  DrawHorizontalLine(Parameters.MeanValue + 1 * Parameters.SigmaValue, kMagenta, kDashed, 3, 0);

  can1->Update();
}
