#ifndef BWPARAMS_H
#include "BreitWignerParams.h"
#endif

#ifndef FITBW_CXX
#define FITBW_CXX

void FitBreitWigner(TString FitName, TH1D* Hist, BreitWignerParams &Parameters, Double_t MeanLimit = 2e-2, Double_t GammaLimit = 1e-2, Double_t MeanIGV = 0.78, Double_t GammaIGV = 2e-2, Int_t ForcePositiveValues = 0) {

  TF1 *Fit = new TF1(FitName, "[0]*TMath::BreitWigner(x, [1], [2])", MeanIGV - 3 * GammaIGV, MeanIGV + 3 * GammaIGV);

  // freedom
  Fit->SetParameter(1, MeanIGV);
  Fit->SetParameter(2, GammaIGV);

  if (ForcePositiveValues) Fit->SetParLimits(0, 0., 999999);
  Fit->SetParLimits(1, MeanIGV - MeanLimit, MeanIGV + MeanLimit);
  Fit->SetParLimits(2, GammaIGV - GammaLimit, GammaIGV + GammaLimit);

  TFitResultPtr FitResult = Hist->Fit(FitName, "BEMS");

  // save parameters
  Parameters.NormValue = Fit->GetParameter(0);
  Parameters.NormError = Fit->GetParError(0);
  Parameters.MeanValue = Fit->GetParameter(1);
  Parameters.MeanError = Fit->GetParError(1);
  Parameters.GammaValue = Fit->GetParameter(2);
  Parameters.GammaError = Fit->GetParError(2);

  Fit->Write();
  FitResult->Write();
}

#endif
