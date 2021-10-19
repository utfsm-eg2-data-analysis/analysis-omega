#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void DrawOver_MC_and_Data(TString targetOption = "C", TString StoreOption = "") {
  // Draw 6 variables, to compare MC with data

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain = GetThreePionFinderChain(targetOption);
  SetAliases(dataChain);

  TChain *mcChain = GetThreePionFinderChain(targetOption, "sim");
  SetAliases(mcChain);

  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
  } else if (targetOption == "All") {
    CutVertex = gCutSolid || gCutLiquid;
  } else {  // solid targets
    CutVertex = gCutSolid;
  }

  TString kinvarOption[2][3] = {{"Q2", "Nu", "W"}, {"wD", "wZ", "wPt2"}};
  TString kinvarOption_MC[2][3] = {{"mc_Q2", "mc_Nu", "mc_W"}, {"mc_wD", "mc_wZ", "mc_wPt2"}};
  TString histProperties[2][3] = {{"(100, 1, 4)", "(100, 2.2, 4.2)", "(100, 2.0, 3.0)"},
                                  {"(24, 0.66, 0.90)", "(80, 0.5, 0.9)", "(75, 0, 1.5)"}};
  TString histProperties_MC[2][3] = {{"(200, 1, 4)", "(200, 2.2, 4.2)", "(200, 2.0, 3.0)"},
                                     {"(200, 0.66, 0.90)", "(200, 0.5, 0.9)", "(150, 0, 1.5)"}};
  TString kinvarAxis[2][3] = {{"Q^{2} [GeV^{2}]", "#nu [GeV]", "W [GeV]"},
                              {"Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]", "Z_{h}", "p_{T}^{2} [GeV^{2}]"}};

  const Int_t Nx = 3;
  const Int_t Ny = 2;

  TH1D *dataMassive[Nx][Ny];
  TH1D *mcMassive[Nx][Ny];

  for (Int_t i = 0; i < Nx; i++) {
    for (Int_t j = 0; j < Ny; j++) {

      dataChain->Draw(Form(kinvarOption[j][i] + ">>data_%i_%i" + histProperties[j][i], i, j),
                      gCutDIS && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle, "goff");
      dataMassive[i][j] = (TH1D *)gROOT->FindObject(Form("data_%i_%i", i, j));

      dataMassive[i][j]->SetTitle("");
      dataMassive[i][j]->SetMarkerColor(myBlue);
      dataMassive[i][j]->SetLineColor(myBlue);
      dataMassive[i][j]->SetLineWidth(3);
      dataMassive[i][j]->SetFillStyle(0);

      dataMassive[i][j]->GetYaxis()->SetTitle("Normalized Counts");
      dataMassive[i][j]->GetYaxis()->SetTitleSize(0.04);
      dataMassive[i][j]->GetYaxis()->SetTitleOffset(1.2);
      dataMassive[i][j]->GetYaxis()->SetMaxDigits(3);

      dataMassive[i][j]->GetXaxis()->SetTitle(kinvarAxis[j][i]);
      dataMassive[i][j]->GetXaxis()->SetTitleSize(0.04);
      dataMassive[i][j]->GetXaxis()->SetTitleOffset(1.);

      mcChain->Draw(Form(kinvarOption_MC[j][i] + ">>mc_%i_%i" + histProperties_MC[j][i], i, j), gCutDIS_MC && gCutParentID_Omega, "goff");
      mcMassive[i][j] = (TH1D *)gROOT->FindObject(Form("mc_%i_%i", i, j));

      mcMassive[i][j]->SetTitle("");
      mcMassive[i][j]->SetMarkerColor(myMagenta);
      mcMassive[i][j]->SetLineColor(myMagenta);
      mcMassive[i][j]->SetLineWidth(3);
      mcMassive[i][j]->SetFillStyle(0);
    }
  }

  /*** NORMALIZATION ***/

  for (Int_t i = 0; i < Nx; i++) {
    for (Int_t j = 0; j < Ny; j++) {
      dataMassive[i][j]->Scale(1. / (Double_t)dataMassive[i][j]->GetMaximum());
      mcMassive[i][j]->Scale(1. / (Double_t)mcMassive[i][j]->GetMaximum());
    }
  }

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "mc-and-data_comparison_" + targetOption + "-mc";
  TCanvas *can1 = new TCanvas(CanvasName, CanvasName, 3240, 2160);
  can1->Divide(Nx, Ny, 0.001, 0.001);

  Int_t counter = 1;
  for (Int_t j = 0; j < Ny; j++) {
    for (Int_t i = 0; i < Nx; i++) {

      can1->cd(counter);

      dataMassive[i][j]->GetYaxis()->SetRangeUser(0., 1.2 * dataMassive[i][j]->GetMaximum());

      dataMassive[i][j]->Draw("E");
      mcMassive[i][j]->Draw("E SAME");

      // legend
      if (i == 0 && j == 0) {
        TLegend *legend = new TLegend(0.75, 0.75, 0.9, 0.9);  // x1,y1,x2,y2
        legend->AddEntry(dataMassive[i][j], "Data", "le");
        legend->AddEntry(mcMassive[i][j], "MC", "le");
        legend->SetFillStyle(0);
        legend->SetTextFont(62);
        legend->SetTextSize(0.04);
        legend->SetBorderSize(0);
        legend->Draw();
      }
      can1->Update();

      counter++;
    }
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_mc";
    system("mkdir -p " + OutputDir);
    can1->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
