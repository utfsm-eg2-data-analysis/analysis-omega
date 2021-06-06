#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

void MakePlots_AllBins() {

  /*** INPUT ***/

  TString dataFile1 = gDataDir + "/C/comb_data-C.root";
  TString dataFile2 = gDataDir + "/Fe/comb_data-Fe.root";
  TString dataFile3 = gDataDir + "/Pb/comb_data-Pb.root";

  TChain *dataTree_D = new TChain();
  dataTree_D->Add(dataFile1 + "/mix");
  dataTree_D->Add(dataFile2 + "/mix");
  dataTree_D->Add(dataFile3 + "/mix");

  TChain *dataTree_C = new TChain();
  dataTree_C->Add(dataFile1 + "/mix");

  TChain *dataTree_Fe = new TChain();
  dataTree_Fe->Add(dataFile2 + "/mix");

  TChain *dataTree_Pb = new TChain();
  dataTree_Pb->Add(dataFile3 + "/mix");
  
  // necessary for gCutKaons
  SetAliases(dataTree_D);
  SetAliases(dataTree_C);
  SetAliases(dataTree_Fe);
  SetAliases(dataTree_Pb);
  
  TString kinvarOption[4] = {"Q2", "Nu", "wZ", "wPt2"};
  // Double_t EdgesKinvar[4][6];
  Double_t EdgesKinvar[4][5];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[0][i] = kEdgesQ2[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[1][i] = kEdgesNu[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[2][i] = kEdgesZ[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[3][i] = kEdgesPt2[i];

  TString auxCut;
  TCut CutBin;

  const Int_t Nx = 4; // 4
  const Int_t Ny = 4; // 4

  TH1D *dataMassive_D[Nx][Ny];
  TH1D *dataMassive_C[Nx][Ny];
  TH1D *dataMassive_Fe[Nx][Ny];
  TH1D *dataMassive_Pb[Nx][Ny];
  
  for (Int_t i = 0; i < Nx; i++) {
    for (Int_t j = 0; j < Ny; j++) {

      auxCut = Form("%f", EdgesKinvar[j][i]);
      auxCut += " < " + kinvarOption[j] + " && " + kinvarOption[j] + " < ";
      auxCut += Form("%f", EdgesKinvar[j][i + 1]);
      CutBin = auxCut;

      std::cout << auxCut << std::endl;
      
      dataTree_D->Draw(Form("wD>>data_d_%i_%i(25, 0.65, 0.90)", i, j), gCutDIS && CutBin && gCutPi0 && gCutLiquid && gCutRegion && gCutKaons, "goff");
      dataMassive_D[i][j] = (TH1D *)gROOT->FindObject(Form("data_d_%i_%i", i, j));

      dataTree_C->Draw(Form("wD>>data_c_%i_%i(25, 0.65, 0.90)", i, j), gCutDIS && CutBin && gCutPi0 && gCutSolid && gCutRegion && gCutKaons, "goff");
      dataMassive_C[i][j] = (TH1D *)gROOT->FindObject(Form("data_c_%i_%i", i, j));

      dataTree_Fe->Draw(Form("wD>>data_fe_%i_%i(25, 0.65, 0.90)", i, j), gCutDIS && CutBin && gCutPi0 && gCutSolid && gCutRegion && gCutKaons, "goff");
      dataMassive_Fe[i][j] = (TH1D *)gROOT->FindObject(Form("data_fe_%i_%i", i, j));
      
      dataTree_Pb->Draw(Form("wD>>data_pb_%i_%i(25, 0.65, 0.90)", i, j), gCutDIS && CutBin && gCutPi0 && gCutSolid && gCutRegion && gCutKaons, "goff");
      dataMassive_Pb[i][j] = (TH1D *)gROOT->FindObject(Form("data_pb_%i_%i", i, j));
      
      dataMassive_D[i][j]->SetTitle(auxCut);
      dataMassive_D[i][j]->GetXaxis()->SetTitle("#Deltam(#pi+#pi-#gamma#gamma)");
      dataMassive_D[i][j]->GetYaxis()->SetTitle("Counts)");

      dataMassive_D[i][j]->SetMarkerColor(kGreen+1);
      dataMassive_D[i][j]->SetLineColor(kGreen+1);
      dataMassive_D[i][j]->SetLineWidth(2);
      dataMassive_D[i][j]->SetFillStyle(0);

      dataMassive_C[i][j]->SetMarkerColor(kRed);
      dataMassive_C[i][j]->SetLineColor(kRed);
      dataMassive_C[i][j]->SetLineWidth(2);
      dataMassive_C[i][j]->SetFillStyle(0);

      dataMassive_Fe[i][j]->SetMarkerColor(kBlue);
      dataMassive_Fe[i][j]->SetLineColor(kBlue);
      dataMassive_Fe[i][j]->SetLineWidth(2);
      dataMassive_Fe[i][j]->SetFillStyle(0);
      
      dataMassive_Pb[i][j]->SetMarkerColor(kBlack);
      dataMassive_Pb[i][j]->SetLineColor(kBlack);
      dataMassive_Pb[i][j]->SetLineWidth(2);
      dataMassive_Pb[i][j]->SetFillStyle(0);
    }
  }

  gStyle->SetOptStat(0);

  /*** DRAW ***/
  
  TCanvas *can1 = new TCanvas("data-all-bins-all-targets");
  can1->Divide(Nx, Ny, 0.001, 0.001);

  Double_t dataNorm;
  
  Int_t counter = 1;
  for (Int_t j = 0; j < Ny; j++) {
    for (Int_t i = 0; i < Nx; i++) {
      
      can1->cd(counter);

      dataMassive_D[i][j]->DrawNormalized("HIST");
      dataMassive_C[i][j]->DrawNormalized("HIST SAME");
      dataMassive_Fe[i][j]->DrawNormalized("HIST SAME");
      dataMassive_Pb[i][j]->DrawNormalized("HIST SAME");
      
      can1->Update();
      
      counter++;
    }
  }  
  
}
