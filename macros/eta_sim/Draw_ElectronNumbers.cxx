#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#include "EtaSimElectronNumbers.hxx"

const Int_t Nkinvars = 2;  // only Q2 and Nu
const Int_t Ntargets = 4;
const Int_t Nbins = 5;

void Draw_ElectronNumbers(TString StoreOption = "") {
  // Draw hardcoded number of electrons

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  TString titleAxis[Nkinvars];
  titleAxis[0] = "Q^{2} [GeV^{2}]";
  titleAxis[1] = "#nu [GeV]";

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  /*** GRAPHS ***/

  // creating and filling histograms
  TGraphErrors *electronGraph[Nkinvars][Ntargets];

  // define arrays
  Double_t binCenter[Nkinvars][Nbins];
  Double_t binError[Nkinvars][Nbins];
  Double_t electronNumber[Nkinvars][Ntargets][Nbins];
  Double_t electronNumberErr[Nkinvars][Ntargets][Nbins];

  // define x bins
  for (Int_t i = 0; i < Nbins; i++) {
    // Q2
    binCenter[0][i] = (kEdgesQ2_Eta[i] + kEdgesQ2_Eta[i + 1]) / 2.;
    binError[0][i] = (kEdgesQ2_Eta[i + 1] - kEdgesQ2_Eta[i]) / TMath::Sqrt(12);
    // Nu
    binCenter[1][i] = (kEdgesNu_Eta[i] + kEdgesNu_Eta[i + 1]) / 2.;
    binError[1][i] = (kEdgesNu_Eta[i + 1] - kEdgesNu_Eta[i]) / TMath::Sqrt(12);
  }

  // define y values and set graphs
  for (Int_t t = 0; t < Ntargets; t++) {
    // define y values
    for (Int_t i = 0; i < Nbins; i++) {
      // fill Q2 arrays
      electronNumber[0][t][i] = kNElecQ2_EtaSim[t][i];
      electronNumberErr[0][t][i] = TMath::Sqrt(electronNumber[0][t][i]);
      // fill Nu arrays
      electronNumber[1][t][i] = kNElecNu_EtaSim[t][i];
      electronNumberErr[1][t][i] = TMath::Sqrt(electronNumber[1][t][i]);
    }
    // set graphs
    electronGraph[0][t] = new TGraphErrors(Nbins, binCenter[0], electronNumber[0][t], binError[0], electronNumberErr[0][t]);
    electronGraph[1][t] = new TGraphErrors(Nbins, binCenter[1], electronNumber[1][t], binError[1], electronNumberErr[1][t]);
    // set Q2 style
    electronGraph[0][t]->SetTitle("");
    electronGraph[0][t]->SetMarkerColor(targetColor[t]);
    electronGraph[0][t]->SetLineColor(targetColor[t]);
    electronGraph[0][t]->SetLineWidth(3);
    electronGraph[0][t]->SetMarkerStyle(20);
    electronGraph[0][t]->SetMarkerSize(1.5);
    // set Nu style
    electronGraph[1][t]->SetTitle("");
    electronGraph[1][t]->SetMarkerColor(targetColor[t]);
    electronGraph[1][t]->SetLineColor(targetColor[t]);
    electronGraph[1][t]->SetLineWidth(3);
    electronGraph[1][t]->SetMarkerStyle(20);
    electronGraph[1][t]->SetMarkerSize(1.5);
  }

  // prepare y-axis
  for (Int_t k = 0; k < Nkinvars; k++) {
    electronGraph[k][0]->GetYaxis()->SetTitle("N_{e^{-}}^{rec}");
    electronGraph[k][0]->GetYaxis()->SetTitleSize(0.06);
    electronGraph[k][0]->GetYaxis()->SetTitleOffset(1.);
    electronGraph[k][0]->GetYaxis()->SetMaxDigits(3);

    electronGraph[k][0]->GetXaxis()->SetTitle(titleAxis[k]);
    electronGraph[k][0]->GetXaxis()->SetTitleSize(0.06);
  }

  /*** FIX Y-AXIS ***/

  Double_t MaxRangeSim[Nkinvars] = {0, 0};
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      // get the maximum of an array of length Nbins, and compare it with MaxRangeSim
      if (TMath::MaxElement(Nbins, electronGraph[k][t]->GetY()) > MaxRangeSim[k]) {
        MaxRangeSim[k] = TMath::MaxElement(Nbins, electronGraph[k][t]->GetY());
      }
    }
  }
  /*** DRAW ***/

  SetMyStyle();

  // define canvas
  const Int_t Nx = 2;
  const Int_t Ny = 1;
  TString CanvasName = "electron-numbers_sim";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 1080);
  c->Divide(Nx, Ny, 0.001, 0.001);

  c->SetFrameLineWidth(2);

  // set y-axis
  electronGraph[0][0]->GetYaxis()->SetRangeUser(0., 1.2 * MaxRangeSim[0]);
  electronGraph[1][0]->GetYaxis()->SetRangeUser(0., 1.2 * MaxRangeSim[1]);

  // left plot
  c->cd(1);
  electronGraph[0][0]->Draw("AP");
  electronGraph[0][1]->Draw("P");
  electronGraph[0][2]->Draw("P");
  electronGraph[0][3]->Draw("P");

  // legend
  TLegend *legend = new TLegend(0.6, 0.65, 0.85, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(electronGraph[0][0], "D (Sim. Rec.)", "pl");
  legend->AddEntry(electronGraph[0][1], "C (Sim. Rec.)", "pl");
  legend->AddEntry(electronGraph[0][2], "Fe (Sim. Rec.)", "pl");
  legend->AddEntry(electronGraph[0][3], "Pb (Sim. Rec.)", "pl");
  legend->SetFillStyle(0);
  legend->SetTextFont(62);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw();

  // right plot
  c->cd(2);
  electronGraph[1][0]->Draw("AP");
  electronGraph[1][1]->Draw("P");
  electronGraph[1][2]->Draw("P");
  electronGraph[1][3]->Draw("P");

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_sim";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
