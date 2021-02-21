#include "DrawHorizontalLine.cxx"
#include "FitGaussian.cxx"
#include "GausParams.h"  // struct
#include "Global.h"

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
  for (Int_t j = 0; j < Nkinvars; j++) {  // Ny
    for (Int_t i = 0; i < Nbins; i++) {   // Nx
      CurrentHistName = Form("sub_%d_%d", i, j);
      CurrentHist = (TH1D *)RootInputFile->Get(CurrentHistName);

      if (particleOption == "omega") FitGaussian(Form("fit_%d_%d", i, j), CurrentHist, Parameters[i][j]);
      else if (particleOption == "eta") FitGaussian(Form("fit_%d_%d", i, j), CurrentHist, Parameters[i][j], 3e-2, .5e-2, 0.55, 1e-2, 1);
    }
  }

  /*** SET CANVAS ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  TCanvas *can3 = new TCanvas("bkgfit-all-bins", "bkgfit-all-bins", 1200, 1200);
  can3->Divide(Nbins, Nkinvars, 0.001, 0.001);

  Int_t counter = 1;  // reset it from before
  for (Int_t j = 0; j < Nkinvars; j++) {
    for (Int_t i = 0; i < Nbins; i++) {

      CurrentHistName = Form("sub_%d_%d", i, j);
      CurrentHist = (TH1D *)RootInputFile->Get(CurrentHistName);

      can3->cd(counter);

      CurrentHist->Draw("E");

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
