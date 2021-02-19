#ifndef GAUSPARAMS_H
#include "GausParams.h"
#endif

#ifndef FITGAUSSIAN_CXX
#define FITGAUSSIAN_CXX

void FitGaussian(TString FitName, TH1D* Hist, GausParams &Parameters, Double_t MeanLimit = 2e-2, Double_t SigmaLimit = 1e-2, Double_t MeanIGV = 0.78, Double_t SigmaIGV = 2e-2) {

  TF1 *Fit = new TF1(FitName, "gaus", MeanIGV - 3 * SigmaIGV, MeanIGV + 3 * SigmaIGV);

  // freedom
  Fit->SetParameter(1, MeanIGV);
  Fit->SetParameter(2, SigmaIGV);

  Fit->SetParLimits(1, MeanIGV - MeanLimit, MeanIGV + MeanLimit);
  Fit->SetParLimits(2, SigmaIGV - SigmaLimit, SigmaIGV + SigmaLimit);

  TFitResultPtr FitResult = Hist->Fit(FitName, "BEMS");

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
