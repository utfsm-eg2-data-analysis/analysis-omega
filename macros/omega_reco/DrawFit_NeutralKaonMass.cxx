#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void DrawFit_NeutralKaonMass(TString StoreOption = "") {
  // Draw invariant mass reconstruction of the K0, and fit its signal (data)

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
  dataChain->Draw("pippimM*pippimM>>data(120, 0.16, 0.64)", gCutDIS && CutVertex && gCutRegion, "goff");  // 0.4, 0.8
  theHist = (TH1D *)gROOT->FindObject("data");

  // style
  SetMyHistStyle(theHist);
  theHist->SetMarkerColor(myBlack);
  theHist->SetLineColor(myBlack);
  theHist->GetYaxis()->SetTitle("Counts");
  theHist->GetXaxis()->SetTitle("Reconstructed Mass m^{2}(#pi^{+}#pi^{-}) [GeV^{2}]");

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
  TF1 *Fit = new TF1("fit", "gaus", 0.240, 0.255);
  Fit->SetParameter(1, 2.47e-1);
  Fit->SetParameter(2, 1.5e-2);
  Fit->SetLineColor(myCyan);
  Fit->SetLineWidth(2);
  TFitResultPtr FitResult = theHist->Fit("fit", "BEMSVR");
  // save parameters
  Parameters.NormValue = Fit->GetParameter(0);
  Parameters.NormError = Fit->GetParError(0);
  Parameters.MeanValue = Fit->GetParameter(1);
  Parameters.MeanError = Fit->GetParError(1);
  Parameters.SigmaValue = Fit->GetParameter(2);
  Parameters.SigmaError = Fit->GetParError(2);

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "kaons-exclusion_data";
  TCanvas *can1 = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  theHist->Draw("E");

  // draw vertical lines to represent 1sigma cut
  DrawVerticalLine(Parameters.MeanValue - 1 * Parameters.SigmaValue, myCyan, 9, 3, 1);
  DrawVerticalLine(Parameters.MeanValue + 1 * Parameters.SigmaValue, myCyan, 9, 3, 1);

  // draw fit results
  TPaveText *pav = new TPaveText(0.60, 0.50, 0.9, 0.75, "NDC NB");  // no border
  pav->AddText(Form("#chi^{2}/ndf = %.4f", theHist->GetFunction("fit")->GetChisquare() / (Double_t)theHist->GetFunction("fit")->GetNDF()));
  pav->AddText(Form("#mu = %.3f +- %.6f", Parameters.MeanValue, Parameters.MeanError));
  pav->AddText(Form("#sigma = %.3f +- %.6f", Parameters.SigmaValue, Parameters.SigmaError));
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
