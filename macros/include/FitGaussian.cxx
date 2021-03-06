#ifndef GAUSPARAMS_H
#include "GausParams.h"
#endif

#ifndef FITGAUSSIAN_CXX
#define FITGAUSSIAN_CXX

void FitGaussian(TString FitName, TH1D* Hist, GausParams &Parameters, Double_t MeanLimit = 2e-2, Double_t SigmaLimit = 1e-2, Double_t MeanIGV = 0.78, Double_t SigmaIGV = 2e-2, Int_t ForcePositiveValues = 0, Int_t FixParameters = 0) {

  TF1 *Fit = new TF1(FitName, "gaus", MeanIGV - 3 * SigmaIGV, MeanIGV + 3 * SigmaIGV);

  // freedom
  if (!FixParameters) {
    Fit->SetParameter(1, MeanIGV);
    Fit->SetParameter(2, SigmaIGV);
    if (ForcePositiveValues) Fit->SetParLimits(0, 0., 999999);
    Fit->SetParLimits(1, MeanIGV - MeanLimit, MeanIGV + MeanLimit);
    Fit->SetParLimits(2, SigmaIGV - SigmaLimit, SigmaIGV + SigmaLimit);
  } else {
    Fit->FixParameter(1, MeanIGV);
    Fit->FixParameter(2, SigmaIGV);
  }

  TFitResultPtr FitResult = Hist->Fit(FitName, "BEMSV");

  // save parameters
  Parameters.NormValue = Fit->GetParameter(0);
  Parameters.NormError = Fit->GetParError(0);
  Parameters.MeanValue = Fit->GetParameter(1);
  Parameters.MeanError = Fit->GetParError(1);
  Parameters.SigmaValue = Fit->GetParameter(2);
  Parameters.SigmaError = Fit->GetParError(2);

  Fit->Write();
  FitResult->Write();
}

#endif
