#include "Global.h"

void MixingBkg_PlotAllVars() {

  // input
  TString dataFile = gProDir + "/FilterNCombine/out/comb_data-C.root";
  TChain *dataTree = new TChain();
  dataTree->Add(dataFile + "/mix");

  TString bkgFile = gProDir + "/MixingBkg/bin/bkgmixC_42011_red.root";
  // TString bkgFile = gProDir + "/MixingBkg/out/bkgmixC_data_red_v2.root";
  TChain *bkgTree = new TChain();
  bkgTree->Add(bkgFile + "/mix");
  
  TString kinvarOption[2][3] = {{"Q2", "Nu", "wD"},
				{"wM", "wZ", "wPt2"}};
  TString histProperties[2][3] = {{"(100, 1, 4)", "(100, 2.2, 4.2)", "(100, 0., 2.5)"}, // 100, 0, 2.5
				  {"(100, 0, 2.5)", "(100, 0, 1.2)", "(100, 0, 1.5)"}};

  const Int_t Nx = 3;
  const Int_t Ny = 2;

  TH1D *dataMassive[Nx][Ny];
  TH1D *bkgMassive[Nx][Ny];
 
  for (Int_t i = 0; i < Nx; i++) {
    for (Int_t j = 0; j < Ny; j++) {
      
      dataTree->Draw(Form(kinvarOption[j][i] + ">>data_%i_%i" + histProperties[j][i], i, j), gCutDIS && gCutPi0 && "TargType == 2" && gCutRegion
		     , "goff");
      dataMassive[i][j] = (TH1D *)gROOT->FindObject(Form("data_%i_%i", i, j));

      dataMassive[i][j]->SetTitle("");
      dataMassive[i][j]->SetMarkerColor(kBlack);
      dataMassive[i][j]->SetLineColor(kBlack);
      dataMassive[i][j]->SetLineWidth(2);
      dataMassive[i][j]->SetFillStyle(0);

      bkgTree->Draw(Form(kinvarOption[j][i] + ">>bkg_%i_%i" + histProperties[j][i], i, j), gCutDIS && gCutPi0 && "TargType == 2" && gCutRegion
		    , "goff");
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
      /*
      dataNorm = dataMassive[i][j]->Integral(41, 47);
      std::cout << "dataNorm = " << dataNorm << std::endl;
      dataMassive[i][j]->Scale(1. / dataNorm);
      
      bkgNorm = bkgMassive[i][j]->Integral(41, 47);
      std::cout << "bkgNorm  = " << bkgNorm << std::endl;
      bkgMassive[i][j]->Scale(1. / bkgNorm);
      */
      /*** DRAW ***/

      can1->cd(counter);
      /*
      dataMassive[i][j]->GetYaxis()->SetRangeUser(0., 0.3); // updated
      bkgMassive[i][j]->GetYaxis()->SetRangeUser(0., 0.3); // updated

      dataMassive[i][j]->Draw("E");
      bkgMassive[i][j]->Draw("E SAME");
      */

      dataMassive[i][j]->DrawNormalized("E");
      bkgMassive[i][j]->DrawNormalized("E SAME");

      can1->Update();
      
      counter++;
    }
  }  
  
}
