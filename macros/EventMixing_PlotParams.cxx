#include "Global.h"

void EventMixing_PlotParams(TString kinvarOption) {

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
  if (kinvarOption == "Q2") kinvarIndex = 0;
  else if (kinvarOption == "Nu") kinvarIndex = 1;
  else if (kinvarOption == "wZ") kinvarIndex = 2;
  else if (kinvarOption == "wPt2") kinvarIndex = 3;

  TString targetString[4] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[4] = {kGreen+3, kRed, kBlue, kBlack};
  
  TFile *rootInputFile[Ntargets];

  for (Int_t t = 0; t < Ntargets; t++) {
    rootInputFile[t] = new TFile(gProDir + "/macros/out/evnt-mixing_fit-sub_" + targetString[t] + ".root");
    for (Int_t i = 0; i < Nbins; i++) {  // i for bins
      TF1 *Fit = (TF1 *)rootInputFile[t]->Get(Form("fit_%d_%d", i, kinvarIndex));
      TFitResultPtr FitResult = (TFitResult *)rootInputFile[t]->Get(Form("TFitResult-sub_%d_%d-fit_%d_%d", i, kinvarIndex, i, kinvarIndex));
      std::vector<Double_t> Parameters = FitResult->Parameters();
      std::vector<Double_t> Errors = FitResult->Errors();
      fitOmega[t][i] = Fit->Integral(0.65, 0.90)/0.01;
      fitOmegaError[t][i] = Fit->IntegralError(0.65, 0.90, FitResult->GetParams(), FitResult->GetCovarianceMatrix().GetMatrixArray())/0.01;
      fitMean[t][i] = Parameters[1];
      fitMeanError[t][i] = Errors[1];
      fitSigma[t][i] = Parameters[2];
      fitSigmaError[t][i] = Errors[2];
    }
  }

  /*** DRAW ***/
  
  TCanvas *c = new TCanvas("c", "c", 1500, 500);
  c->Divide(3, 1, 0.01, 0.01); // nx, ny, margins
  
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetTitleSize(0.12, "t"); // hist title size
  
  // creating and filling histograms
  TH1F *meanHist[Ntargets]; 
  TH1F *sigmaHist[Ntargets];
  TH1F *omegaHist[Ntargets];

  for (Int_t t = 0; t < Ntargets; t++) { // t for targets
    
    meanHist[t] = new TH1F("meanHist", "#mu (" + kinvarOption + ")", Nbins, 0., Nbins);
    sigmaHist[t] = new TH1F("sigmaHist", "#sigma (" + kinvarOption + ")", Nbins, 0., Nbins);
    omegaHist[t] = new TH1F("omegaHist", "N_{#omega} (" + kinvarOption + ")", Nbins, 0., Nbins);

    for (Int_t i = 0; i < Nbins; i++) { // i for bins
      // omega
      omegaHist[t]->SetBinContent(i + 1, fitOmega[t][i]);
      omegaHist[t]->SetBinError(i + 1, fitOmegaError[t][i]);
      // mean
      meanHist[t]->SetBinContent(i + 1, fitMean[t][i]);
      meanHist[t]->SetBinError(i + 1, fitMeanError[t][i]);
      // width
      sigmaHist[t]->SetBinContent(i + 1, fitSigma[t][i]);
      sigmaHist[t]->SetBinError(i + 1, fitSigmaError[t][i]);
    }

    // hist style
    meanHist[t]->SetMarkerColor(targetColor[t]);
    sigmaHist[t]->SetMarkerColor(targetColor[t]);
    omegaHist[t]->SetMarkerColor(targetColor[t]);

    meanHist[t]->SetLineColor(targetColor[t]);
    sigmaHist[t]->SetLineColor(targetColor[t]);
    omegaHist[t]->SetLineColor(targetColor[t]);

    meanHist[t]->SetLineWidth(2);
    sigmaHist[t]->SetLineWidth(2);
    omegaHist[t]->SetLineWidth(2);

    meanHist[t]->SetMarkerStyle(20);
    sigmaHist[t]->SetMarkerStyle(20);
    omegaHist[t]->SetMarkerStyle(20);      
  }

  // set y-axis
  meanHist[0]->GetYaxis()->SetRangeUser(0.74, 0.82);
  sigmaHist[0]->GetYaxis()->SetRangeUser(0.01, 0.035);
  omegaHist[0]->GetYaxis()->SetRangeUser(0., 2600.);

  meanHist[0]->GetXaxis()->SetTitle("Bin number in " + kinvarOption);
  sigmaHist[0]->GetXaxis()->SetTitle("Bin number in " + kinvarOption);
  omegaHist[0]->GetXaxis()->SetTitle("Bin number in " + kinvarOption);
  
  /*** MEAN ***/
  
  c->cd(1);

  meanHist[0]->Draw("PE");
  meanHist[1]->Draw("SAME PE");
  meanHist[2]->Draw("SAME PE");
  meanHist[3]->Draw("SAME PE");

  /*** SIGMA ***/
  
  c->cd(2);

  sigmaHist[0]->Draw("PE");
  sigmaHist[1]->Draw("SAME PE");
  sigmaHist[2]->Draw("SAME PE");
  sigmaHist[3]->Draw("SAME PE");
  
  /*** OMEGA NUMBER ***/
  
  c->cd(3);

  omegaHist[0]->Draw("PE");
  omegaHist[1]->Draw("SAME PE");
  omegaHist[2]->Draw("SAME PE");
  omegaHist[3]->Draw("SAME PE");

  // close files
  /*
  rootInputFile_D->Close();
  rootInputFile_C->Close();
  rootInputFile_Fe->Close();
  rootInputFile_Pb->Close();
  */
}
