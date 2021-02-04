#include "Global.h"

void MixingBkg_PlotAllBins(Int_t CustomNormalization = 0) {

  // input
  TString dataFile = gProDir + "/FilterNCombine/out/comb_data-C.root";
  TChain *dataTree = new TChain();
  dataTree->Add(dataFile + "/mix");

  TString bkgFile = gProDir + "/MixingBkg/bin/bkgmixC_42011_red.root";
  // TString bkgFile = gProDir + "/MixingBkg/out/bkgmixC_data_red_v3.root";
  TChain *bkgTree = new TChain();
  bkgTree->Add(bkgFile + "/mix");
  
  TString kinvarOption[4] = {"Q2", "Nu", "wZ", "wPt2"};
  Double_t EdgesKinvar[4][6];
  for (Int_t i = 0; i < 6; i++) EdgesKinvar[0][i] = kEdgesQ2[i];
  for (Int_t i = 0; i < 6; i++) EdgesKinvar[1][i] = kEdgesNu[i];
  for (Int_t i = 0; i < 6; i++) EdgesKinvar[2][i] = kEdgesZ[i];
  for (Int_t i = 0; i < 6; i++) EdgesKinvar[3][i] = kEdgesPt2[i];

  TString auxCut;
  TCut CutBin;

  const Int_t Nx = 5;
  const Int_t Ny = 4;

  TH1D *dataMassive[Nx][Ny];
  TH1D *bkgMassive[Nx][Ny];
 
  for (Int_t i = 0; i < Nx; i++) {
    for (Int_t j = 0; j < Ny; j++) {

      auxCut = Form("%f", EdgesKinvar[j][i]);
      auxCut += " < " + kinvarOption[j] + " && " + kinvarOption[j] + " < ";
      auxCut += Form("%f", EdgesKinvar[j][i + 1]);
      CutBin = auxCut;

      std::cout << auxCut << std::endl;
      
      dataTree->Draw(Form("wD>>data_%i_%i(30, 0.6, 0.9)", i, j), gCutDIS && CutBin && gCutPi0 && "TargType == 2" && gCutRegion, "goff");
      dataMassive[i][j] = (TH1D *)gROOT->FindObject(Form("data_%i_%i", i, j));

      dataMassive[i][j]->SetTitle("");
      dataMassive[i][j]->SetMarkerColor(kBlack);
      dataMassive[i][j]->SetLineColor(kBlack);
      dataMassive[i][j]->SetLineWidth(2);
      dataMassive[i][j]->SetFillStyle(0);

      bkgTree->Draw(Form("wD>>bkg_%i_%i(30, 0.6, 0.9)", i, j), gCutDIS && CutBin && gCutPi0 && "TargType == 2" && gCutRegion, "goff");
      bkgMassive[i][j] = (TH1D *)gROOT->FindObject(Form("bkg_%i_%i", i, j));

      bkgMassive[i][j]->SetTitle("");
      bkgMassive[i][j]->SetMarkerColor(kRed);
      bkgMassive[i][j]->SetLineColor(kRed);
      bkgMassive[i][j]->SetLineWidth(2);
      bkgMassive[i][j]->SetFillStyle(0);
    }
  }

  gStyle->SetOptStat(0);
  
  TCanvas *can1 = new TCanvas("bkgmix-all-bins");
  can1->Divide(Nx, Ny, 0.001, 0.001);

  Double_t dataNorm, bkgNorm;
  
  Int_t counter = 1;
  for (Int_t j = 0; j < Ny; j++) {
    for (Int_t i = 0; i < Nx; i++) {

      /*** NORMALIZATION ***/

      if (CustomNormalization) {
	dataNorm = dataMassive[i][j]->Integral(20, 27); // 41,47
	std::cout << "dataNorm = " << dataNorm << std::endl;
	dataMassive[i][j]->Scale(1. / dataNorm);
	
	bkgNorm = bkgMassive[i][j]->Integral(20, 27);
	std::cout << "bkgNorm  = " << bkgNorm << std::endl;
	bkgMassive[i][j]->Scale(1. / bkgNorm);
      }

      /*** DRAW ***/
      
      can1->cd(counter);

      if (CustomNormalization) {
	dataMassive[i][j]->GetYaxis()->SetRangeUser(0., 0.3); // updated
	bkgMassive[i][j]->GetYaxis()->SetRangeUser(0., 0.3); // updated
	
	bkgMassive[i][j]->Draw("E");
	dataMassive[i][j]->Draw("E SAME");
      } else {
	bkgMassive[i][j]->DrawNormalized("HIST");
	dataMassive[i][j]->DrawNormalized("HIST SAME");
      }
      
      can1->Update();
      
      counter++;
    }
  }  
  
}
