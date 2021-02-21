#include "Global.h"

void EventMixing_PlotParams(TString kinvarOption, TString particleOption = "omega") {

  const Int_t Nbins = 4;
  const Int_t Ntargets = 4;
  
  Double_t fitMean[Ntargets][Nbins];
  Double_t fitMeanError[Ntargets][Nbins];
  Double_t fitSigma[Ntargets][Nbins];
  Double_t fitSigmaError[Ntargets][Nbins];
  Double_t fitOmega[Ntargets][Nbins];
  Double_t fitOmegaError[Ntargets][Nbins]; 
  
  /*** INPUT ***/

  Int_t kinvarIndex;
  TString kinvarTitle;
  Double_t EdgesKinvar[Nbins + 1];
  if (kinvarOption == "Q2") {
    kinvarIndex = 0;
    kinvarTitle = "Q^{2} [GeV^{2}]";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesQ2[i];
  } else if (kinvarOption == "Nu") {
    kinvarIndex = 1;
    kinvarTitle = "#nu [GeV]";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesNu[i];
  } else if (kinvarOption == "wZ") {
    kinvarIndex = 2;
    kinvarTitle = "Z";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesZ[i];
  } else if (kinvarOption == "wPt2") {
    kinvarIndex = 3;
    kinvarTitle = "p_{T}^{2} [GeV^{2}]";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesPt2[i];
  }

  TString targetString[4] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[4] = {kGreen+3, kRed, kBlue, kBlack};
  
  TFile *rootInputFile[Ntargets];

  Double_t plotMin, plotMax;
  if (particleOption == "omega") {
    plotMin = 0.65;
    plotMax = 0.90;
  } else if (particleOption == "eta") {
    plotMin = 0.45;
    plotMax = 0.65;
  }

  for (Int_t t = 0; t < Ntargets; t++) {
    rootInputFile[t] = new TFile(gProDir + "/macros/out/evnt-mixing-" + particleOption + "_fit-sub_" + targetString[t] + ".root");
    for (Int_t i = 0; i < Nbins; i++) {  // i for bins
      TF1 *Fit = (TF1 *)rootInputFile[t]->Get(Form("fit_%d_%d", i, kinvarIndex));
      TFitResultPtr FitResult = (TFitResult *)rootInputFile[t]->Get(Form("TFitResult-sub_%d_%d-fit_%d_%d", i, kinvarIndex, i, kinvarIndex));
      std::vector<Double_t> Parameters = FitResult->Parameters();
      std::vector<Double_t> Errors = FitResult->Errors();
      fitOmega[t][i] = Fit->Integral(plotMin, plotMax)/0.01;
      fitOmegaError[t][i] = Fit->IntegralError(plotMin, plotMax, FitResult->GetParams(), FitResult->GetCovarianceMatrix().GetMatrixArray(), 1e-1)/0.01;
      fitMean[t][i] = Parameters[1];
      fitMeanError[t][i] = Errors[1];
      fitSigma[t][i] = Parameters[2];
      fitSigmaError[t][i] = Errors[2];
    }
  }

  /*** DEFINE GRAPHS ***/
  
  // creating and filling histograms
  TGraphErrors *meanGraph[Ntargets]; 
  TGraphErrors *sigmaGraph[Ntargets];
  TGraphErrors *omegaGraph[Ntargets];

  // define arrays
  Double_t binCenter[Nbins];
  Double_t binError[Nbins];

  // fill arrays
  for (Int_t i = 0; i < Nbins; i++) {
    binCenter[i] = (EdgesKinvar[i] + EdgesKinvar[i + 1]) / 2.;
    binError[i] = (EdgesKinvar[i + 1] - EdgesKinvar[i]) / TMath::Sqrt(12);
  }

  // set graphs
  for (Int_t t = 0; t < Ntargets; t++) {
    meanGraph[t] = new TGraphErrors(Nbins, binCenter, fitMean[t], binError, fitMeanError[t]);
    sigmaGraph[t] = new TGraphErrors(Nbins, binCenter, fitSigma[t], binError, fitSigmaError[t]);
    omegaGraph[t] = new TGraphErrors(Nbins, binCenter, fitOmega[t], binError, fitOmegaError[t]);

    meanGraph[t]->SetTitle("");
    sigmaGraph[t]->SetTitle("");
    omegaGraph[t]->SetTitle("");
    
    // style
    meanGraph[t]->SetMarkerColor(targetColor[t]);
    sigmaGraph[t]->SetMarkerColor(targetColor[t]);
    omegaGraph[t]->SetMarkerColor(targetColor[t]);

    meanGraph[t]->SetLineColor(targetColor[t]);
    sigmaGraph[t]->SetLineColor(targetColor[t]);
    omegaGraph[t]->SetLineColor(targetColor[t]);

    meanGraph[t]->SetLineWidth(2);
    sigmaGraph[t]->SetLineWidth(2);
    omegaGraph[t]->SetLineWidth(2);

    meanGraph[t]->SetMarkerStyle(20);
    sigmaGraph[t]->SetMarkerStyle(20);
    omegaGraph[t]->SetMarkerStyle(20);      
  }

  /*** SET Y AXIS ***/
  
  Double_t MaxRangeMean = 0;
  Double_t MinRangeMean = 9999;
  Double_t MaxRangeSigma = 0;
  Double_t MinRangeSigma = 9999;
  for (Int_t t = 0; t < Ntargets; t++) {
    // mean
    if (TMath::MaxElement(Nbins, meanGraph[t]->GetY()) > MaxRangeMean)
      MaxRangeMean = TMath::MaxElement(Nbins, meanGraph[t]->GetY());
    if (TMath::MinElement(Nbins, meanGraph[t]->GetY()) < MinRangeMean)
      MinRangeMean = TMath::MinElement(Nbins, meanGraph[t]->GetY());
    // sigma
    if (TMath::MaxElement(Nbins, sigmaGraph[t]->GetY()) > MaxRangeSigma)
      MaxRangeSigma = TMath::MaxElement(Nbins, sigmaGraph[t]->GetY());
    if (TMath::MinElement(Nbins, sigmaGraph[t]->GetY()) < MinRangeSigma)
      MinRangeSigma = TMath::MinElement(Nbins, sigmaGraph[t]->GetY());
  }

  meanGraph[0]->GetYaxis()->SetRangeUser(0.98*MinRangeMean, 1.02*MaxRangeMean);
  sigmaGraph[0]->GetYaxis()->SetRangeUser(0., 1.9*MaxRangeSigma);
  omegaGraph[0]->GetYaxis()->SetRangeUser(0., 1.2*TMath::MaxElement(Nbins, omegaGraph[0]->GetY()));

  meanGraph[0]->GetYaxis()->SetTitle("#mu [GeV]");
  meanGraph[0]->GetYaxis()->SetTitleSize(0.06);
  meanGraph[0]->GetYaxis()->SetTitleOffset(1.0);

  sigmaGraph[0]->GetYaxis()->SetTitle("#sigma [GeV]");
  sigmaGraph[0]->GetYaxis()->SetTitleSize(0.06);
  sigmaGraph[0]->GetYaxis()->SetTitleOffset(1.0);
  
  omegaGraph[0]->GetYaxis()->SetTitle("N_{#" + particleOption + "}");
  omegaGraph[0]->GetYaxis()->SetTitleSize(0.06);
  omegaGraph[0]->GetYaxis()->SetTitleOffset(1.0);

  meanGraph[0]->GetXaxis()->SetTitle(kinvarTitle);
  meanGraph[0]->GetXaxis()->SetTitleSize(0.06);
  
  sigmaGraph[0]->GetXaxis()->SetTitle(kinvarTitle);
  sigmaGraph[0]->GetXaxis()->SetTitleSize(0.06);
    
  omegaGraph[0]->GetXaxis()->SetTitle(kinvarTitle);
  omegaGraph[0]->GetXaxis()->SetTitleSize(0.06);
  
  /*** DRAW ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  TCanvas *c = new TCanvas("c", "c", 1500, 500);
  c->Divide(3, 1, 0.01, 0.01); // nx, ny, margins
  
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  // mean
  c->cd(1);
  
  meanGraph[0]->Draw("AP");
  meanGraph[1]->Draw("P");
  meanGraph[2]->Draw("P");
  meanGraph[3]->Draw("P");

  // legend
  TLegend *legend = new TLegend(0.75, 0.75, 0.9, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(meanGraph[0], "Deuterium", "pl");
  legend->AddEntry(meanGraph[1], "Carbon", "pl");
  legend->AddEntry(meanGraph[2], "Iron", "pl");
  legend->AddEntry(meanGraph[3], "Lead", "pl");
  legend->Draw();
  
  // sigma
  c->cd(2);

  sigmaGraph[0]->Draw("AP");
  sigmaGraph[1]->Draw("P");
  sigmaGraph[2]->Draw("P");
  sigmaGraph[3]->Draw("P");
  
  // omega/eta number
  c->cd(3);

  omegaGraph[0]->Draw("AP");
  omegaGraph[1]->Draw("P");
  omegaGraph[2]->Draw("P");
  omegaGraph[3]->Draw("P");

  

  // close files
  /*
  rootInputFile_D->Close();
  rootInputFile_C->Close();
  rootInputFile_Fe->Close();
  rootInputFile_Pb->Close();
  */
}
