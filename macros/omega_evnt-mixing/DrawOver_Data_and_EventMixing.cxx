#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void DrawOver_Data_and_EventMixing(TString targetOption = "C", TString StoreOption = "") {
  // Draw 6 variables, to compare data with normalized mixed-event bkg

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain = GetThreePionFinderChain(targetOption);
  SetAliases(dataChain);

  TChain *bkgChain = GetEventMixingChain(targetOption);
  SetAliases(bkgChain);

  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
  } else if (targetOption == "All") {
    CutVertex = gCutSolid || gCutLiquid;
  } else {  // solid targets
    CutVertex = gCutSolid;
  }

  TString kinvarOption[2][3] = {{"Q2", "Nu", "W"}, {"wD", "wZ", "wPt2"}};
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

      dataChain->Draw(Form(kinvarOption[j][i] + ">>data_%i_%i" + histProperties[j][i], i, j),
                      gCutDIS && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle, "goff");
      dataMassive[i][j] = (TH1D *)gROOT->FindObject(Form("data_%i_%i", i, j));

      dataMassive[i][j]->SetTitle("");
      dataMassive[i][j]->SetMarkerColor(myBlack);
      dataMassive[i][j]->SetLineColor(myBlack);
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

      bkgChain->Draw(Form(kinvarOption[j][i] + ">>bkg_%i_%i" + histProperties[j][i], i, j),
                     gCutDIS && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle, "goff");
      bkgMassive[i][j] = (TH1D *)gROOT->FindObject(Form("bkg_%i_%i", i, j));

      bkgMassive[i][j]->SetTitle("");
      bkgMassive[i][j]->SetMarkerColor(myRed);
      bkgMassive[i][j]->SetLineColor(myRed);
      bkgMassive[i][j]->SetLineWidth(2);
      bkgMassive[i][j]->SetFillStyle(0);
    }
  }

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "data-and-evnt-mixing_comparison_" + targetOption + "-data";
  TCanvas *can1 = new TCanvas(CanvasName, CanvasName, 3240, 2160);
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
      if (i == 0 && j == 0) {
        TLegend *legend = new TLegend(0.5, 0.75, 0.75, 0.9);  // x1,y1,x2,y2
        legend->AddEntry(dataMassive[i][j], "Data", "le");
        legend->AddEntry(bkgMassive[i][j], "Mixed Event Bkg", "le");
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
    TString OutputDir = gProDir + "/gfx/omega_evnt-mixing";
    system("mkdir -p " + OutputDir);
    can1->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
