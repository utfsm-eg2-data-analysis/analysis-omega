#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "FitGaussian.cxx"
#include "GausParams.h"  // struct

#include "DrawHorizontalLine.cxx"

void EventMixing_FitSub(TString targetOption, TString particleOption = "omega") {
  // This macro fits the subtracted bkg.

  /*** INPUT ***/
  
  TFile *RootInputFile = new TFile(gProDir + "/macros/out/evnt-mixing-" + particleOption + "_binned_" + targetOption + ".root");
  TFile *RootOutputFile = new TFile(gProDir + "/macros/out/evnt-mixing-" + particleOption + "_fit-sub_" + targetOption + ".root", "RECREATE");
   
  /*** MAIN ***/  

  const Int_t Nkinvars = 4;
  const Int_t Nbins = 4;
  
  TString CurrentHistName;
  TH1D *CurrentHist;

  /*** FIT ***/

  GausParams Parameters[Nbins][Nkinvars];

  Double_t auxMean;
  Double_t auxSigma;
  for (Int_t j = 0; j < Nkinvars; j++) {  // Ny
    for (Int_t i = 0; i < Nbins; i++) {   // Nx
      CurrentHistName = Form("sub_%d_%d", i, j);
      CurrentHist = (TH1D *)RootInputFile->Get(CurrentHistName);
      // (TString FitName, TH1D* Hist, GausParams &Parameters, Double_t MeanLimit = 2e-2, Double_t SigmaLimit = 1e-2, Double_t MeanIGV = 0.78, Double_t SigmaIGV = 2e-2, Int_t
      // ForcePositiveValues = 0, Int_t FixParameters = 0)
      if (particleOption == "omega") FitGaussian(Form("fit_%d_%d", i, j), CurrentHist, Parameters[i][j], 2e-2, 1e-2, 0.783, 0.0225, 0, 1); // option 1: obtained previously
      // if (particleOption == "omega") FitGaussian(Form("fit_%d_%d", i, j), CurrentHist, Parameters[i][j], 2e-2, 1e-2, 0.782,
      // 0.024, 0, 1); // option 2: obtained previously, depending on kinvar
      // if (particleOption == "omega") FitGaussian(Form("fit_%d_%d", i, j), CurrentHist, Parameters[i][j], 2e-2, 1e-2, 0.782, 0.024, 0, 1); // option 3: from simrec
      // if (particleOption == "omega") FitGaussian(Form("fit_%d_%d", i, j), CurrentHist, Parameters[i][j]);
      /*
      if (particleOption == "omega") {
        if (j == 0) {
          auxMean = 0.783229;
          auxSigma = 0.0220322;
        } else if (j == 1) {
          auxMean = 0.783878;
          auxSigma = 0.0222954;
        } else if (j == 2) {
          auxMean = 0.783582;
          auxSigma = 0.0227721;
        } else if (j == 3) {
          auxMean = 0.781243;
          auxSigma = 0.0230147;
        }
      FitGaussian(Form("fit_%d_%d", i, j), CurrentHist, Parameters[i][j], 2e-2, 1e-2, auxMean, auxSigma, 0, 1);
      } else if (particleOption == "eta") {
        FitGaussian(Form("fit_%d_%d", i, j), CurrentHist, Parameters[i][j], 3e-2, .5e-2, 0.55, 1e-2, 1);
      }
      */
    }
  }

  /*** SET CANVAS ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  // TCanvas *can3 = new TCanvas("bkgfit-all-bins-" + particleOption + "_" + targetOption, "bkgfit-all-bins-" + particleOption + "_" + targetOption, 1200, 1200);
  TCanvas *can3 = new TCanvas("bkgfit-all-bins_" + targetOption, "bkgfit-all-bins_" + targetOption, 1200, 1200);
  can3->Divide(Nbins, Nkinvars, 0.001, 0.001);

  TString Chi2String, NormString, MeanString, SigmaString;
  
  Int_t counter = 1;  // reset it from before
  for (Int_t j = 0; j < Nkinvars; j++) {
    for (Int_t i = 0; i < Nbins; i++) {

      CurrentHistName = Form("sub_%d_%d", i, j);
      CurrentHist = (TH1D *)RootInputFile->Get(CurrentHistName);

      can3->cd(counter);

      CurrentHist->Draw("E");

      // pave
      Chi2String = Form("#chi^{2}/ndf = %.4f", CurrentHist->GetFunction(Form("fit_%d_%d", i, j))->GetChisquare()/(Double_t)CurrentHist->GetFunction(Form("fit_%d_%d", i, j))->GetNDF());
      NormString = Form("A = %.3f +- %.3f", Parameters[i][j].NormValue, Parameters[i][j].NormError);
      MeanString = Form("#mu = %.3f +- %.6f", Parameters[i][j].MeanValue, Parameters[i][j].MeanError);
      SigmaString = Form("#sigma = %.3f +- %.6f", Parameters[i][j].SigmaValue, Parameters[i][j].SigmaError);
      TPaveText *pav = new TPaveText(0.60, 0.60, 0.88, 0.88, "NDC NB"); // no border
      pav->AddText(Chi2String);
      pav->AddText(NormString);
      pav->AddText(MeanString);
      pav->AddText(SigmaString);
      pav->SetBorderSize(0);
      pav->SetFillStyle(0);
      pav->Draw();
      
      // legend
      TLegend *leg = new TLegend(0.15, 0.64, 0.45, 0.88);  // x1,y1,x2,y2
      leg->AddEntry(CurrentHist, "Bkg Subtracted", "lp");
      leg->AddEntry(CurrentHist->GetFunction(Form("fit_%d_%d", i, j)), "Fit", "l");
      leg->SetBorderSize(0);
      leg->SetFillStyle(0);
      leg->Draw();

      DrawHorizontalLine(0, kBlack, kSolid, 1);

      can3->Update();

      counter++;
    }
  }

  // close files
  RootOutputFile->Close();
}
