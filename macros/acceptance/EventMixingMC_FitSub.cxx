#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "FitBreitWigner.cxx"
#include "BreitWignerParams.h"  // struct

#include "DrawHorizontalLine.cxx"

// void EventMixingMC_FitSub(TString targetOption, TString particleOption = "omega") { // this is how it should be
void EventMixingMC_FitSub(TString setOption, TString targetOption, TString dirOption = "", TString particleOption = "omega") {

  // This macro fits the subtracted bkg.

  /*** INPUT ***/
  TString InputFileName = "evnt-mixing-mc-" + particleOption + "_binned_" + setOption + "-" + targetOption;
  if (setOption == "jlab") InputFileName += "-" + dirOption;
  TFile *RootInputFile = new TFile(gProDir + "/macros/out/" + InputFileName + ".root", "READ");

  /*** OUTPUT ***/

  TString OutputFileName = "evnt-mixing-mc-" + particleOption + "_fit-sub_" + setOption + "-" + targetOption;
  if (setOption == "jlab") OutputFileName += "-" + dirOption;  
  TFile *RootOutputFile = new TFile(gProDir + "/macros/out/" + OutputFileName + ".root", "RECREATE");
   
  /*** MAIN ***/  

  const Int_t Nkinvars = 4;
  const Int_t Nbins = 4;
  
  TString CurrentHistName;
  TH1D *CurrentHist;

  /*** FIT ***/

  BreitWignerParams Parameters[Nbins][Nkinvars];
  
  for (Int_t j = 0; j < Nkinvars; j++) {  // Ny
    for (Int_t i = 0; i < Nbins; i++) {   // Nx
      CurrentHistName = Form("sub_%d_%d", i, j);
      CurrentHist = (TH1D *)RootInputFile->Get(CurrentHistName);

      if (particleOption == "omega") FitBreitWigner(Form("fit_%d_%d", i, j), CurrentHist, Parameters[i][j], 2e-2, 2e-2, 0.78, 2.5e-2);
      else if (particleOption == "eta") FitBreitWigner(Form("fit_%d_%d", i, j), CurrentHist, Parameters[i][j], 3e-2, .5e-2, 0.55, 1e-2, 1);
    }
  }

  /*** SET CANVAS ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  TCanvas *can3 = new TCanvas("bkgfit-all-bins", "bkgfit-all-bins", 1200, 1200);
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
      SigmaString = Form("#sigma = %.3f +- %.6f", Parameters[i][j].GammaValue, Parameters[i][j].GammaError); // gamma or sigma
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
