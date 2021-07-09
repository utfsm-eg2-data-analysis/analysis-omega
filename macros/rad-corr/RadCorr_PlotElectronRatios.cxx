#ifndef GLOBAL_H
#include "Global.h"
#endif

void RadCorr_PlotElectronRatios() {
  // UPS!! CORRECT THIS!!!

  const Int_t Nkinvars = 2;  // only Q2 and Nu
  const Int_t Ntargets = 4;
  const Int_t Nbins = 4;

  TString titleAxis[2];
  titleAxis[0] = "Q^{2} [GeV^{2}]";
  titleAxis[1] = "#nu [GeV]";

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {kGreen + 1, kRed, kBlue, kBlack};

  /*** DEFINE GRAPHS ***/

  // creating and filling graphs
  TGraphErrors *electronGraph[Nkinvars][Ntargets];

  // define arrays
  Double_t binCenter[Nkinvars][Nbins];
  Double_t binError[Nkinvars][Nbins];

  // nominal
  Double_t electronRatio[Nkinvars][Ntargets][Nbins];
  Double_t electronRatioErr[Nkinvars][Ntargets][Nbins];

  // radiative corrections
  Double_t electronRatio_rc[Nkinvars][Ntargets][Nbins];
  Double_t electronRatioErr_rc[Nkinvars][Ntargets][Nbins];

  // difference
  Double_t electronDifference[Nkinvars][Ntargets][Nbins];
  Double_t electronDifferenceErr[Nkinvars][Ntargets][Nbins];

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
      electronRatio[0][t][i] = kNElecQ2[0][i] / kNElecQ2[t][i];
      electronRatioErr[0][t][i] = kNElecQ2[0][i] / kNElecQ2[t][i] *
                                  TMath::Sqrt(TMath::Power(TMath::Sqrt(kNElecQ2[0][i]) / kNElecQ2[0][i], 2) +
                                              TMath::Power(TMath::Sqrt(kNElecQ2[t][i]) / kNElecQ2[t][i], 2));
      // fill Nu arrays
      electronRatio[1][t][i] = kNElecNu[0][i] / kNElecNu[t][i];
      electronRatioErr[1][t][i] = kNElecNu[0][i] / kNElecNu[t][i] *
                                  TMath::Sqrt(TMath::Power(TMath::Sqrt(kNElecNu[0][i]) / kNElecNu[0][i], 2) +
                                              TMath::Power(TMath::Sqrt(kNElecNu[t][i]) / kNElecNu[t][i], 2));

      // fill Q2 arrays (RADIATIVE CORRECTIONS)
      electronRatio_rc[0][t][i] = kNElecQ2_rc[0][i] / kNElecQ2_rc[t][i];
      electronRatioErr_rc[0][t][i] = kNElecQ2_rc[0][i] / kNElecQ2_rc[t][i] *
                                     TMath::Sqrt(TMath::Power(TMath::Sqrt(kNElecQ2_rc[0][i]) / kNElecQ2_rc[0][i], 2) +
                                                 TMath::Power(TMath::Sqrt(kNElecQ2_rc[t][i]) / kNElecQ2_rc[t][i], 2));
      // fill Nu arrays (RADIATIVE CORRECTIONS)
      electronRatio_rc[1][t][i] = kNElecNu_rc[0][i] / kNElecNu_rc[t][i];
      electronRatioErr_rc[1][t][i] = kNElecNu_rc[0][i] / kNElecNu_rc[t][i] *
                                     TMath::Sqrt(TMath::Power(TMath::Sqrt(kNElecNu_rc[0][i]) / kNElecNu_rc[0][i], 2) +
                                                 TMath::Power(TMath::Sqrt(kNElecNu_rc[t][i]) / kNElecNu_rc[t][i], 2));

      // fill Q2 arrays (DIFFERENCE)
      electronDifference[0][t][i] = electronRatio[0][t][i] - electronRatio_rc[0][t][i];
      electronDifferenceErr[0][t][i] = TMath::Sqrt(TMath::Power(electronRatioErr[0][t][i], 2) + TMath::Power(electronRatioErr[0][t][i], 2));
      electronDifferenceErr[0][t][i] = electronDifference[0][t][i] / electronRatio[0][t][i] *
                                       TMath::Sqrt(TMath::Power(electronDifferenceErr[0][t][i] / electronDifference[0][t][i], 2) +
                                                   TMath::Power(electronRatioErr[0][t][i] / electronRatio[0][t][i], 2));
      electronDifference[0][t][i] = electronDifference[0][t][i] / electronRatio[0][t][i];

      // fill Nu arrays (DIFFERENCE)
      electronDifference[1][t][i] = electronRatio[1][t][i] - electronRatio_rc[1][t][i];
      electronDifferenceErr[1][t][i] = TMath::Sqrt(TMath::Power(electronRatioErr[1][t][i], 2) + TMath::Power(electronRatioErr_rc[1][t][i], 2));
      electronDifferenceErr[1][t][i] = electronDifference[1][t][i] / electronRatio[1][t][i] *
                                       TMath::Sqrt(TMath::Power(electronDifferenceErr[1][t][i] / electronDifference[1][t][i], 2) +
                                                   TMath::Power(electronRatioErr[1][t][i] / electronRatio[1][t][i], 2));
      electronDifference[1][t][i] = electronDifference[1][t][i] / electronRatio[1][t][i];

      std::cout << electronRatioErr[0][t][i] << std::endl;
      std::cout << electronRatioErr[1][t][i] << std::endl;
    }

    // set graphs
    electronGraph[0][t] = new TGraphErrors(Nbins, binCenter[0], electronDifference[0][t], binError[0], electronDifferenceErr[0][t]);
    electronGraph[1][t] = new TGraphErrors(Nbins, binCenter[1], electronDifference[1][t], binError[1], electronDifferenceErr[1][t]);
    // set Q2 style
    electronGraph[0][t]->SetTitle("");
    electronGraph[0][t]->SetMarkerColor(targetColor[t]);
    electronGraph[0][t]->SetLineColor(targetColor[t]);
    electronGraph[0][t]->SetLineWidth(2);
    electronGraph[0][t]->SetMarkerStyle(20);
    electronGraph[0][t]->SetMarkerSize(1.5);

    // set Nu style
    electronGraph[1][t]->SetTitle("");
    electronGraph[1][t]->SetMarkerColor(targetColor[t]);
    electronGraph[1][t]->SetLineColor(targetColor[t]);
    electronGraph[1][t]->SetLineWidth(2);
    electronGraph[1][t]->SetMarkerStyle(20);
    electronGraph[1][t]->SetMarkerSize(1.5);
  }

  /*** SET Y AXIS ***/

  for (Int_t k = 0; k < Nkinvars; k++) {
    electronGraph[k][3]->GetYaxis()->SetRangeUser(-0.1, 0.1);

    electronGraph[k][3]->GetYaxis()->SetTitle("(R_{e} - R_{e}^{corr}) / R_{e}");
    electronGraph[k][3]->GetYaxis()->SetTitleSize(0.06);
    electronGraph[k][3]->GetYaxis()->SetTitleOffset(1.2);

    electronGraph[k][3]->GetXaxis()->SetTitle(titleAxis[k]);
    electronGraph[k][3]->GetXaxis()->SetTitleSize(0.06);
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
  TCanvas *c = new TCanvas("rad-corr_electron-diff", "rad-corr_electron-diff", 1800, 900);
  c->Divide(Nx, Ny, 0.001, 0.001);

  c->SetFrameLineWidth(2);

  // left plot
  c->cd(1);
  electronGraph[0][3]->Draw("AP");
  electronGraph[0][1]->Draw("P");
  electronGraph[0][2]->Draw("P");

  // legend
  TLegend *legend = new TLegend(0.75, 0.7, 0.9, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(electronGraph[0][1], "C", "pl");
  legend->AddEntry(electronGraph[0][2], "Fe", "pl");
  legend->AddEntry(electronGraph[0][3], "Pb", "pl");
  legend->SetFillStyle(0);
  legend->SetTextFont(62);
  legend->SetTextSize(0.03);
  legend->SetBorderSize(0);
  legend->Draw();

  // right plot
  c->cd(2);
  electronGraph[1][3]->Draw("AP");
  electronGraph[1][1]->Draw("P");
  electronGraph[1][2]->Draw("P");
}
