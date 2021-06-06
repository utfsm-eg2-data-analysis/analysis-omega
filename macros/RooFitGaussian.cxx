#ifndef GAUSPARAMS_H
#include "GausParams.h"
#endif

#ifndef ROOFITGAUSSIAN_CXX
#define ROOFITGAUSSIAN_CXX

using namespace RooFit;

void RooFitGaussian(TH1D* Hist, GausParams &Parameters, Double_t MeanIGV = 0.78, Double_t SigmaIGV = 2e-2) {

  // define plot range and variable
  Int_t Nbins = Hist->GetXaxis()->GetNbins();
  // Double_t plotRangeDown = Hist->GetXaxis()->GetXmin();
  // Double_t plotRangeUp   = Hist->GetXaxis()->GetXmax();
  Double_t fitRangeDown  = MeanIGV - 2*SigmaIGV; // 0.73
  Double_t fitRangeUp    = MeanIGV + 2*SigmaIGV; // 0.82
  RooRealVar x("x", "Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]", //plotRangeDown, plotRangeUp);
	       fitRangeDown, fitRangeUp);

  // define data
  RooDataHist data("hist", "hist", x, Hist);
  TString HistName = Hist->GetName();

  // freedom
  Double_t MeanRangeDown = MeanIGV - 3e-2;
  Double_t MeanRangeUp   = MeanIGV + 3e-2;
  
  Double_t SigmaRangeDown = SigmaIGV - 1.0e-2;
  Double_t SigmaRangeUp   = SigmaIGV + 1.0e-2;
  
  RooRealVar  Mean("#mu(#omega)", "Mean of Gaussian", MeanIGV, MeanRangeDown, MeanRangeUp);
  RooRealVar  Sigma("#sigma(#omega)", "Sigma of Gaussian", SigmaIGV, SigmaRangeDown, SigmaRangeUp);
  RooGaussian gaussN("gaussN", "omega-g peak", x, Mean, Sigma); // gaussian normalized

  // gauss(x) = Norm*gaussN(x)
  RooRealVar Norm("N_{#omega}", "omega yields", 0., Hist->GetEntries());  // normalization constant
  RooAddPdf gauss("gauss", "gauss", RooArgList(gaussN), RooArgList(Norm));

  // define frame
  RooPlot *Frame = x.frame(Name("fit_" + HistName), Title(Hist->GetTitle()), Bins(Nbins));
  
  // fit the normal way
  gauss.fitTo(data, Minos(kTRUE), Save(), Range(fitRangeDown, fitRangeUp));
  
  // draw
  data.plotOn(Frame, Name("Data")); // DataError(RooAbsData::SumW2)
  gauss.plotOn(Frame, Name("Model"), LineColor(kRed));

  // draw params values
  gauss.paramOn(Frame, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  Frame->getAttText()->SetTextSize(0.025);
  Frame->getAttLine()->SetLineWidth(0);
  Frame->GetYaxis()->SetTitle("Counts");
  
  Frame->Write();

  // save parameters
  Parameters.NormValue = Norm.getValV();
  Parameters.NormError = Norm.getError();
  Parameters.MeanValue = Mean.getValV();
  Parameters.MeanError = Mean.getError();
  Parameters.SigmaValue = Sigma.getValV();
  Parameters.SigmaError = Sigma.getError();
}

#endif
