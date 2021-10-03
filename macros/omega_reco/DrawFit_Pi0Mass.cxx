#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void DrawFit_Pi0Mass(TString StoreOption = "") {
  // Draw reconstructed invariant mass of the pi0, and fit its signal (data)

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain = GetThreePionFinderChain("All", "data");
  TCut CutVertex = gCutSolid || gCutLiquid;
  SetAliases(dataChain);

  /*** HISTOGRAM ***/

  TH1D *theHist;
  dataChain->Draw("pi0M>>data(200, 0, 0.5)", gCutDIS && CutVertex && gCutRegion && gCutPhotonsOpAngle, "goff");
  theHist = (TH1D *)gROOT->FindObject("data");

  // style
  SetMyHistStyle(theHist);
  theHist->SetMarkerColor(myBlack);
  theHist->SetLineColor(myBlack);
  theHist->GetYaxis()->SetTitle("Counts");
  theHist->GetXaxis()->SetTitle("Reconstructed Mass m(#gamma#gamma) [GeV]");

  /*** FIT ***/

  struct GausParams {
    Double_t NormValue;
    Double_t MeanValue;
    Double_t SigmaValue;

    Double_t NormError;
    Double_t MeanError;
    Double_t SigmaError;
  };

  GausParams Parameters;
  TF1 *Fit = new TF1("fit", "gaus", 0.115, 0.155);
  Fit->SetParameter(1, 0.1354);
  Fit->SetParameter(2, 0.0185);
  // style
  Fit->SetLineWidth(2);
  Fit->SetLineColor(myRed);
  TFitResultPtr FitResult = theHist->Fit("fit", "SR");  // BEMSVR
  // save parameters
  Parameters.NormValue = FitResult->Parameter(0);
  Parameters.NormError = FitResult->ParError(0);
  Parameters.MeanValue = FitResult->Parameter(1);
  Parameters.MeanError = FitResult->ParError(1);
  Parameters.SigmaValue = FitResult->Parameter(2);
  Parameters.SigmaError = FitResult->ParError(2);

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "pi0-mass_data";
  TCanvas *can1 = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  theHist->Draw("E");

  // draw vertical lines to represent 3sigma cut
  DrawVerticalLine(Parameters.MeanValue - 3 * Parameters.SigmaValue, myRed, 7, 3, 1);
  DrawVerticalLine(Parameters.MeanValue + 3 * Parameters.SigmaValue, myRed, 7, 3, 1);

  // draw fit results
  TPaveText *pav = new TPaveText(0.60, 0.50, 0.9, 0.75, "NDC NB");  // no border
  pav->AddText(Form("#chi^{2}/ndf = %.4f", theHist->GetFunction("fit")->GetChisquare() / (Double_t)theHist->GetFunction("fit")->GetNDF()));
  pav->AddText(Form("#mu = %.3f #pm %.6f", Parameters.MeanValue, Parameters.MeanError));
  pav->AddText(Form("#sigma = %.3f #pm %.6f", Parameters.SigmaValue, Parameters.SigmaError));
  pav->SetFillStyle(0);
  pav->Draw();

  // legend
  TLegend *legend = new TLegend(0.60, 0.75, 0.85, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(theHist, "Data", "le");
  legend->AddEntry(theHist->GetFunction("fit"), "Fit", "l");
  legend->SetFillStyle(0);
  legend->SetTextFont(62);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw();

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_reco";
    system("mkdir -p " + OutputDir);
    can1->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
