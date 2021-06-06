#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "FitGaussian.cxx"
#include "GausParams.h"

#include "DrawVerticalLine.cxx"

void PPlot_Pi0Mass_mc(TString targetOption = "C") {
  // Particular plot: invariant mass reconstruction and selection of the pi0.

  /*** INPUT ***/

  TChain *mcTree = new TChain();
  //mcTree->Add(gWorkDir + "/out/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
  //if (targetOption == "C" || targetOption == "Fe")
  mcTree->Add(gWorkDir + "/out/FilterNCombine/old/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
  /*
  Int_t maxDir;
  TString auxDir;
  for (Int_t i = 0; i < maxDir; i++) {
    if (i < 10) auxDir = Form("0%d", i);
    else auxDir = Form("%d", i);
    mcTree->Add(gWorkDir + "/out/jlab/" + targetOption +"/" + auxDir + "/comb" + targetOption + "_*.root/mix");
  }
  */  
  TH1D *theHist;
  mcTree->Draw("mc_pi0M>>mchist(200, 0.125, 0.15)", gCutDIS_MC && gCutPhotonsOpAngle_MC, "goff");
  theHist = (TH1D *)gROOT->FindObject("mchist");

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
  TF1 *Fit = new TF1("fit", "gaus", 0.134, 0.136);
  //Fit->SetParameter(1, 0.1354);
  //Fit->SetParameter(2, 0.0185);
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
  gStyle->SetLineWidth(2);
  
  // set margin sizes
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);

  gStyle->SetOptStat(0);

  TCanvas *can1 = new TCanvas("pplot-pi0-mass_mc", "pplot-pi0-mass_mc", 1200, 1200);
  
  theHist->Draw("E");

  // vert lines - cut
  DrawVerticalLine(Parameters.MeanValue - 3 * Parameters.SigmaValue, kRed, kDashed, 3, 1);
  DrawVerticalLine(Parameters.MeanValue + 3 * Parameters.SigmaValue, kRed, kDashed, 3, 1);

  // pave
  //TString Chi2String = Form("#chi^{2}/ndf = %.4f", theHist->GetFunction("fit")->GetChisquare() / (Double_t)theHist->GetFunction("fit")->GetNDF());
  TString MeanString = Form("#mu = %.3f #pm %.6f", Parameters.MeanValue, Parameters.MeanError);
  TString SigmaString = Form("#sigma = %.3f #pm %.6f", Parameters.SigmaValue, Parameters.SigmaError);
  TPaveText *pav = new TPaveText(0.60, 0.50, 0.9, 0.75, "NDC NB");  // no border
  //pav->AddText(Chi2String);
  pav->AddText(MeanString);
  pav->AddText(SigmaString);
  pav->SetFillStyle(0);
  pav->Draw();

  // legend
  TLegend *legend = new TLegend(0.60, 0.75, 0.85, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(theHist, "MC", "pl");
  legend->AddEntry(theHist->GetFunction("fit"), "Fit", "l");
  legend->SetFillStyle(0);
  legend->SetTextFont(62);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw();
}
