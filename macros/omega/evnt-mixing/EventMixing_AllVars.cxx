#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

void EventMixing_AllVars(TString targetOption = "D") {

  /*** INPUT ***/

  TString dataFile1, dataFile2, dataFile3;
  TString bkgFile1, bkgFile2, bkgFile3;
  TString BkgDir = gWorkDir + "/out/EventMixing/data";
  TCut CutVertex;
  if (targetOption == "D" || targetOption == "All") {
    CutVertex = gCutLiquid;
    dataFile1 = gDataDir + "/C/*.root";
    dataFile2 = gDataDir + "/Fe/*.root";
    dataFile3 = gDataDir + "/Pb/*.root";
    bkgFile1 = BkgDir + "/C/*.root";
    bkgFile2 = BkgDir + "/Fe/*.root";
    bkgFile3 = BkgDir + "/Pb/*.root";
    if (targetOption == "All") CutVertex = gCutSolid || gCutLiquid;
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    dataFile1 = gDataDir + "/" + targetOption + "/*.root";
    bkgFile1 = BkgDir + "/" + targetOption + "/*.root";
  }

  TChain *dataTree = new TChain();
  dataTree->Add(dataFile1 + "/mix");
  if (targetOption == "D" || targetOption == "All") {
    dataTree->Add(dataFile2 + "/mix");
    dataTree->Add(dataFile3 + "/mix");
  }

  TChain *bkgTree = new TChain();
  bkgTree->Add(bkgFile1 + "/mix");
  if (targetOption == "D" || targetOption == "All") {
    bkgTree->Add(bkgFile2 + "/mix");
    bkgTree->Add(bkgFile3 + "/mix");
  }

  // necessary for gCutKaons
  SetAliases(dataTree);
  SetAliases(bkgTree);

  TString kinvarOption[2][3] = {{"Q2", "Nu", "W"},
				{"wD", "wZ", "wPt2"}};
  TString histProperties[2][3] = {{"(100, 1, 4)", "(100, 2.2, 4.2)", "(100, 2.0, 3.0)"},
                                  {"(24, 0.66, 0.90)", "(80, 0.5, 0.9)", "(75, 0, 1.5)"}};
  TString kinvarAxis[2][3] = {{"Q^{2} [GeV^{2}]", "#nu [GeV]", "W [GeV]"},
                              {"Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]", "Z_{h}", "p_{T}^{2} [GeV^{2}]"}};

  const Int_t Nx = 3;
  const Int_t Ny = 2;

  TH1D *dataMassive[Nx][Ny];
  TH1D *bkgMassive[Nx][Ny];

  for (Int_t i = 0; i < Nx; i++) {    // Nx
    for (Int_t j = 0; j < Ny; j++) {  // Ny

      dataTree->Draw(Form(kinvarOption[j][i] + ">>data_%i_%i" + histProperties[j][i], i, j), gCutDIS && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle, "goff");
      dataMassive[i][j] = (TH1D *)gROOT->FindObject(Form("data_%i_%i", i, j));

      dataMassive[i][j]->SetTitle("");
      dataMassive[i][j]->SetMarkerColor(kBlack);
      dataMassive[i][j]->SetLineColor(kBlack);
      dataMassive[i][j]->SetLineWidth(2);
      dataMassive[i][j]->SetFillStyle(0);

      dataMassive[i][j]->GetYaxis()->SetTitle("Normalized Counts");
      if (i == 0 && j == 1) dataMassive[i][j]->GetYaxis()->SetTitle("Counts");
      dataMassive[i][j]->GetYaxis()->SetTitleSize(0.04);
      dataMassive[i][j]->GetYaxis()->SetTitleOffset(1.2);
      dataMassive[i][j]->GetYaxis()->SetMaxDigits(3);

      dataMassive[i][j]->GetXaxis()->SetTitle(kinvarAxis[j][i]);
      dataMassive[i][j]->GetXaxis()->SetTitleSize(0.04);
      dataMassive[i][j]->GetXaxis()->SetTitleOffset(1.);

      bkgTree->Draw(Form(kinvarOption[j][i] + ">>bkg_%i_%i" + histProperties[j][i], i, j), gCutDIS && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle, "goff");
      bkgMassive[i][j] = (TH1D *)gROOT->FindObject(Form("bkg_%i_%i", i, j));

      bkgMassive[i][j]->SetTitle("");
      bkgMassive[i][j]->SetMarkerColor(kRed);
      bkgMassive[i][j]->SetLineColor(kRed);
      bkgMassive[i][j]->SetLineWidth(2);
      bkgMassive[i][j]->SetFillStyle(0);
    }
  }

  /*** DRAW ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  // set margin sizes
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  
  gStyle->SetOptStat(0);

  TCanvas *can1 = new TCanvas("evnt-mixing_all-vars_" + targetOption, "evnt-mixing_all-vars_" + targetOption, 1500, 1000);
  can1->Divide(Nx, Ny, 0.001, 0.001);

  Double_t dataNorm, bkgNorm;

  Int_t counter = 1;
  for (Int_t j = 0; j < Ny; j++) {
    for (Int_t i = 0; i < Nx; i++) {

      can1->cd(counter);

      if (i == 0 && j == 1) {
        dataNorm = dataMassive[i][j]->Integral(1, 5) + dataMassive[i][j]->Integral(19, 24);
        std::cout << "dataNorm = " << dataNorm << std::endl;

        bkgNorm = bkgMassive[i][j]->Integral(1, 5) + bkgMassive[i][j]->Integral(19, 24);
        std::cout << "bkgNorm  = " << bkgNorm << std::endl;
        bkgMassive[i][j]->Scale(dataNorm / bkgNorm);

        dataMassive[i][j]->Draw("E");
        bkgMassive[i][j]->Draw("E SAME");
      } else {
        dataMassive[i][j]->DrawNormalized("E");
        bkgMassive[i][j]->DrawNormalized("E SAME");
      }

      // legend
      TLegend *legend = new TLegend(0.60, 0.75, 0.85, 0.9);  // x1,y1,x2,y2
      legend->AddEntry(dataMassive[i][j], "Data", "pl");
      if (i == 0 && j == 1) legend->AddEntry(bkgMassive[i][j], "Mixed Event Bkg (Normalized)", "pl");
      else legend->AddEntry(bkgMassive[i][j], "Mixed Event Bkg", "pl");
      legend->SetFillStyle(0);
      legend->SetTextFont(62);
      legend->SetTextSize(0.04);
      legend->SetBorderSize(0);
      legend->Draw();
      
      can1->Update();

      counter++;
    }
  }
}
