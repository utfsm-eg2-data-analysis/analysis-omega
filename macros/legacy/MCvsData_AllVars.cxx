#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

void MCvsData_AllVars(TString targetOption = "C") {
  // Adapted to all available data and sim. rec., feel free to change it.

  /*** INPUT ***/

  TString dataFile1, dataFile2, dataFile3;
  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
    dataFile1 = gDataDir + "/C/*.root";
    dataFile2 = gDataDir + "/Fe/*.root";
    dataFile3 = gDataDir + "/Pb/*.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    dataFile1 = gDataDir + "/" + targetOption + "/*.root";
  }

  TChain *dataTree = new TChain();
  dataTree->Add(dataFile1 + "/mix");
  if (targetOption == "D") {
    dataTree->Add(dataFile2 + "/mix");
    dataTree->Add(dataFile3 + "/mix");
  }

  TChain *simTree = new TChain();
  if (targetOption == "C") {
    simTree->Add(gWorkDir + "/out/FilterNCombine/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
    simTree->Add(gWorkDir + "/out/FilterNCombine/old/" + targetOption + "/comb" + targetOption + "_*.root/mix");
  } else if (targetOption == "Fe") {
    simTree->Add(gWorkDir + "/out/FilterNCombine/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
    simTree->Add(gWorkDir + "/out/FilterNCombine/old/" + targetOption + "/comb" + targetOption + "_*.root/mix");
  } else if (targetOption == "Pb") {
    simTree->Add(gWorkDir + "/out/FilterNCombine/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
  } else if (targetOption == "D") {
    simTree->Add(gWorkDir + "/out/FilterNCombine/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
    simTree->Add(gWorkDir + "/out/FilterNCombine/jlab/"+ targetOption +"/00/comb" + targetOption + "_*.root/mix");
  }

  // necessary for gCutKaons
  SetAliases(dataTree);
  SetAliases(simTree, 1);

  TString kinvarOption[2][3] = {{"Q2", "Nu", "W"}, {"wZ", "wPt2", "wD"}};
  TString histProperties[2][3] = {{"(100, 1, 4)", "(100, 2.2, 4.2)", "(100, 2, 3.0)"}, {"(100, 0.5, 0.9)", "(100, 0, 1.5)", "(125, 0., 2.5)"}};
  TString histPropertiesMC[2][3] = {{"(200, 1, 4)", "(200, 2.2, 4.2)", "(200, 2, 3.0)"}, {"(200, 0.5, 0.9)", "(200, 0, 1.5)", "(1250, 0., 2.5)"}};
  TString kinvarAxis[2][3] = {{"Q^{2} [GeV^{2}]", "#nu [GeV]", "W [GeV]"}, {"z_{h}", "p_{T}^{2} [GeV^{2}]", "Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]"}};

  const Int_t Nx = 3;
  const Int_t Ny = 2;

  TH1D *dataMassive[Nx][Ny];
  TH1D *simMassive[Nx][Ny];

  for (Int_t i = 0; i < Nx; i++) {    // Nx
    for (Int_t j = 0; j < Ny; j++) {  // Ny

      dataTree->Draw(Form(kinvarOption[j][i] + ">>data_%i_%i" + histProperties[j][i], i, j), gCutDIS && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle,
                     "goff");
      dataMassive[i][j] = (TH1D *)gROOT->FindObject(Form("data_%i_%i", i, j));

      dataMassive[i][j]->SetTitle("");
      dataMassive[i][j]->SetMarkerColor(kBlack);
      dataMassive[i][j]->SetLineColor(kBlack);
      dataMassive[i][j]->SetLineWidth(2);
      dataMassive[i][j]->SetFillStyle(0);

      dataMassive[i][j]->GetYaxis()->SetTitle("Normalized Counts");
      dataMassive[i][j]->GetYaxis()->SetTitleSize(0.04);
      dataMassive[i][j]->GetYaxis()->SetTitleOffset(1.2);
      dataMassive[i][j]->GetYaxis()->SetMaxDigits(3);

      dataMassive[i][j]->GetXaxis()->SetTitle(kinvarAxis[j][i]);
      dataMassive[i][j]->GetXaxis()->SetTitleSize(0.04);
      dataMassive[i][j]->GetXaxis()->SetTitleOffset(1.);

      simTree->Draw(Form("mc_" + kinvarOption[j][i] + ">>sim_%i_%i" + histPropertiesMC[j][i], i, j), gCutDIS_MC && gCutPi0_MC && gCutKaons_MC && gCutPhotonsOpAngle_MC,
                    "goff");
      simMassive[i][j] = (TH1D *)gROOT->FindObject(Form("sim_%i_%i", i, j));

      simMassive[i][j]->SetTitle("");
      simMassive[i][j]->SetMarkerColor(kRed);
      simMassive[i][j]->SetLineColor(kRed);
      simMassive[i][j]->SetLineWidth(2);
      simMassive[i][j]->SetFillStyle(0);
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

  TCanvas *can1 = new TCanvas("mc-vs-data_all-vars", "mc-vs-data_all-vars", 1500, 1000);
  can1->Divide(Nx, Ny, 0.001, 0.001);

  Double_t dataNorm, simNorm;

  Int_t counter = 1;
  for (Int_t j = 0; j < Ny; j++) {
    for (Int_t i = 0; i < Nx; i++) {

      can1->cd(counter);

      // for the invariant mass plot
      if (j + 1 == Ny && i + 1 == Nx) {
        dataMassive[i][j]->Scale(1 / dataMassive[i][j]->GetMaximum());
        simMassive[i][j]->Scale(1 / simMassive[i][j]->GetMaximum());
	dataMassive[i][j]->GetYaxis()->SetRangeUser(0., 1.1);
        dataMassive[i][j]->Draw("E");
        simMassive[i][j]->Draw("E SAME");
      } else {
        dataMassive[i][j]->DrawNormalized("E");
        simMassive[i][j]->DrawNormalized("E SAME");
      }

      // legend
      TLegend *legend = new TLegend(0.75, 0.75, 0.9, 0.9);  // x1,y1,x2,y2
      if (j == 0 && i == 1) {
        legend->SetX1(0.20);
        legend->SetX2(0.45);
      }
      legend->AddEntry(dataMassive[i][j], "Data", "pl");
      legend->AddEntry(simMassive[i][j], "MC", "pl");
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
