#ifndef GLOBAL_H
#include "Global.h"
#endif

void RadCorr_PlotElectronNumbers() {

  const Int_t Nkinvars = 2;  // only Q2 and Nu
  const Int_t Ntargets = 4;
  const Int_t Nbins = 4;

  TString titleAxis[2];
  titleAxis[0] = "Q^{2} [GeV^{2}]";
  titleAxis[1] = "#nu [GeV]";

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {kGreen + 1, kRed, kBlue, kBlack};

  /*** DEFINE GRAPHS ***/

  // creating and filling histograms
  TGraphErrors *electronGraph[Nkinvars][Ntargets];
  TGraphErrors *electronGraph_rc[Nkinvars][Ntargets];

  // define arrays
  Double_t binCenter[Nkinvars][Nbins];
  Double_t binError[Nkinvars][Nbins];

  Double_t electronNumber[Nkinvars][Ntargets][Nbins];
  Double_t electronNumberErr[Nkinvars][Ntargets][Nbins];

  // radiative corrections
  Double_t electronNumber_rc[Nkinvars][Ntargets][Nbins];
  Double_t electronNumberErr_rc[Nkinvars][Ntargets][Nbins];

  // define x bins
  for (Int_t i = 0; i < Nbins; i++) {
    binCenter[0][i] = (kEdgesQ2[i] + kEdgesQ2[i + 1]) / 2.;
    binError[0][i] = (kEdgesQ2[i + 1] - kEdgesQ2[i]) / TMath::Sqrt(12);

    binCenter[1][i] = (kEdgesNu[i] + kEdgesNu[i + 1]) / 2.;
    binError[1][i] = (kEdgesNu[i + 1] - kEdgesNu[i]) / TMath::Sqrt(12);
  }

  // define y values and set graphs
  for (Int_t t = 0; t < Ntargets; t++) {
    // define y values
    for (Int_t i = 0; i < Nbins; i++) {
      // fill Q2 arrays
      electronNumber[0][t][i] = kNElecQ2[t][i];
      electronNumberErr[0][t][i] = TMath::Sqrt(electronNumber[0][t][i]);
      // fill Nu arrays
      electronNumber[1][t][i] = kNElecNu[t][i];
      electronNumberErr[1][t][i] = TMath::Sqrt(electronNumber[1][t][i]);

      // fill Q2 arrays (RADIATIVE CORRECTIONS)
      electronNumber_rc[0][t][i] = kNElecQ2_rc[t][i];
      electronNumberErr_rc[0][t][i] = TMath::Sqrt(electronNumber_rc[0][t][i]);
      // fill Nu arrays (RADIATIVE CORRECTIONS)
      electronNumber_rc[1][t][i] = kNElecNu_rc[t][i];
      electronNumberErr_rc[1][t][i] = TMath::Sqrt(electronNumber_rc[1][t][i]);

      std::cout << electronNumberErr[0][t][i] << std::endl;
      std::cout << electronNumberErr[1][t][i] << std::endl;
    }

    // set graphs
    electronGraph[0][t] = new TGraphErrors(Nbins, binCenter[0], electronNumber[0][t], binError[0], electronNumberErr[0][t]);
    electronGraph[1][t] = new TGraphErrors(Nbins, binCenter[1], electronNumber[1][t], binError[1], electronNumberErr[1][t]);
    // set Q2 style
    electronGraph[0][t]->SetTitle("");
    electronGraph[0][t]->SetMarkerColor(targetColor[t]);
    electronGraph[0][t]->SetLineColor(targetColor[t]);
    electronGraph[0][t]->SetLineWidth(2);
    electronGraph[0][t]->SetMarkerStyle(25);
    electronGraph[0][t]->SetMarkerSize(1.5);

    // set Nu style
    electronGraph[1][t]->SetTitle("");
    electronGraph[1][t]->SetMarkerColor(targetColor[t]);
    electronGraph[1][t]->SetLineColor(targetColor[t]);
    electronGraph[1][t]->SetLineWidth(2);
    electronGraph[1][t]->SetMarkerStyle(25);
    electronGraph[1][t]->SetMarkerSize(1.5);

    // set graphs
    electronGraph_rc[0][t] = new TGraphErrors(Nbins, binCenter[0], electronNumber_rc[0][t], binError[0], electronNumberErr_rc[0][t]);
    electronGraph_rc[1][t] = new TGraphErrors(Nbins, binCenter[1], electronNumber_rc[1][t], binError[1], electronNumberErr_rc[1][t]);
    // set Q2 style
    electronGraph_rc[0][t]->SetTitle("");
    electronGraph_rc[0][t]->SetMarkerColor(targetColor[t]);
    electronGraph_rc[0][t]->SetLineColor(targetColor[t]);
    electronGraph_rc[0][t]->SetLineWidth(2);
    electronGraph_rc[0][t]->SetMarkerStyle(20);
    electronGraph_rc[0][t]->SetMarkerSize(1.5);

    // set Nu style
    electronGraph_rc[1][t]->SetTitle("");
    electronGraph_rc[1][t]->SetMarkerColor(targetColor[t]);
    electronGraph_rc[1][t]->SetLineColor(targetColor[t]);
    electronGraph_rc[1][t]->SetLineWidth(2);
    electronGraph_rc[1][t]->SetMarkerStyle(20);
    electronGraph_rc[1][t]->SetMarkerSize(1.5);
  }

  /*** SET Y AXIS ***/

  for (Int_t k = 0; k < Nkinvars; k++) {
    electronGraph[k][0]->GetYaxis()->SetRangeUser(0., 1.2 * TMath::MaxElement(Nbins, electronGraph[k][0]->GetY()));

    electronGraph[k][0]->GetYaxis()->SetTitle("N_{e^{-}}^{DIS}");
    electronGraph[k][0]->GetYaxis()->SetTitleSize(0.06);
    electronGraph[k][0]->GetYaxis()->SetTitleOffset(1.);

    electronGraph[k][0]->GetXaxis()->SetTitle(titleAxis[k]);
    electronGraph[k][0]->GetXaxis()->SetTitleSize(0.06);
  }

  /*** DRAW ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  // set margin sizes
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  // define canvas
  const Int_t Nx = 2;
  const Int_t Ny = 1;
  TCanvas *c = new TCanvas("rad-corr_electron-numbers", "rad-corr_electron-numbers", 1800, 900);
  c->Divide(Nx, Ny, 0.001, 0.001);

  c->SetFrameLineWidth(2);

  // left plot
  c->cd(1);
  electronGraph[0][0]->Draw("AP");
  electronGraph[0][1]->Draw("P");
  electronGraph[0][2]->Draw("P");
  electronGraph[0][3]->Draw("P");

  electronGraph_rc[0][0]->Draw("P");
  electronGraph_rc[0][1]->Draw("P");
  electronGraph_rc[0][2]->Draw("P");
  electronGraph_rc[0][3]->Draw("P");

  // right plot
  c->cd(2);
  electronGraph[1][0]->Draw("AP");
  electronGraph[1][1]->Draw("P");
  electronGraph[1][2]->Draw("P");
  electronGraph[1][3]->Draw("P");

  electronGraph_rc[1][0]->Draw("P");
  electronGraph_rc[1][1]->Draw("P");
  electronGraph_rc[1][2]->Draw("P");
  electronGraph_rc[1][3]->Draw("P");

  // legend
  TLegend *legend = new TLegend(0.75, 0.65, 0.9, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(electronGraph[0][0], "D", "pl");
  legend->AddEntry(electronGraph[0][1], "C", "pl");
  legend->AddEntry(electronGraph[0][2], "Fe", "pl");
  legend->AddEntry(electronGraph[0][3], "Pb", "pl");
  legend->AddEntry(electronGraph_rc[0][0], "D + Rad. Corr.", "pl");
  legend->AddEntry(electronGraph_rc[0][1], "C + Rad. Corr.", "pl");
  legend->AddEntry(electronGraph_rc[0][2], "Fe + Rad. Corr.", "pl");
  legend->AddEntry(electronGraph_rc[0][3], "Pb + Rad. Corr.", "pl");
  legend->SetFillStyle(0);
  legend->SetTextFont(62);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw();
}
