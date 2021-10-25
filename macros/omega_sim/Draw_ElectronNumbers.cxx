#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#include "OmegaSimElectronNumbers.hxx"

const Int_t Ntargets = 4;
const Int_t Nkinvars = 2;  // only Q2 and Nu
const Int_t Nbins = 4;

void Draw_ElectronNumbers(TString StoreOption = "") {
  // Draw hardcoded number of electrons

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  TString kinvarTitle[Nkinvars] = {"Q^{2} [GeV^{2}]", "#nu [GeV]"};

  Double_t EdgesKinvar[Nkinvars][Nbins + 1];
  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[0][i] = kEdgesQ2[i];
    EdgesKinvar[1][i] = kEdgesNu[i];
  }

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  /*** GRAPHS ***/

  // create and fill graphs
  TGraphErrors *electronGraph[Nkinvars][Ntargets];

  // define and fill arrays
  Double_t binCenter[Nkinvars][Nbins];
  Double_t binError[Nkinvars][Nbins];
  Double_t electronNumber[Nkinvars][Ntargets][Nbins];
  Double_t electronNumberErr[Nkinvars][Ntargets][Nbins];

  // define x bins
  for (Int_t i = 0; i < Nbins; i++) {
    // Q2
    binCenter[0][i] = (kEdgesQ2[i] + kEdgesQ2[i + 1]) / 2.;
    binError[0][i] = (kEdgesQ2[i + 1] - kEdgesQ2[i]) / TMath::Sqrt(12);
    // Nu
    binCenter[1][i] = (kEdgesNu[i] + kEdgesNu[i + 1]) / 2.;
    binError[1][i] = (kEdgesNu[i + 1] - kEdgesNu[i]) / TMath::Sqrt(12);
  }

  // define y values and set graphs
  for (Int_t t = 0; t < Ntargets; t++) {
    // define y values
    for (Int_t i = 0; i < Nbins; i++) {
      // fill Q2 arrays
      electronNumber[0][t][i] = kNElecQ2_OmegaSim[t][i];
      electronNumberErr[0][t][i] = TMath::Sqrt(electronNumber[0][t][i]);
      // fill Nu arrays
      electronNumber[1][t][i] = kNElecNu_OmegaSim[t][i];
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

  /*** SET AXIS ***/

  for (Int_t k = 0; k < Nkinvars; k++) {
    // set y-axis
    electronGraph[k][0]->GetYaxis()->SetRangeUser(0., 1.2 * TMath::MaxElement(Nbins, electronGraph[k][0]->GetY()));
    electronGraph[k][0]->GetYaxis()->SetTitle("N_{e^{-}}^{gen}");
    electronGraph[k][0]->GetYaxis()->SetTitleSize(0.06);
    electronGraph[k][0]->GetYaxis()->SetTitleOffset(1.);
    // set x-axis
    electronGraph[k][0]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
    electronGraph[k][0]->GetXaxis()->SetTitle(kinvarTitle[k]);
    electronGraph[k][0]->GetXaxis()->SetTitleSize(0.06);
  }

  /*** DRAW ***/

  SetMyStyle();

  // define canvas
  const Int_t Nx = 2;
  const Int_t Ny = 1;
  TString CanvasName = "electron-numbers_sim";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, Nx * 1080, Ny * 1080);
  c->Divide(Nx, Ny, 0.001, 0.001);

  c->SetFrameLineWidth(2);

  for (Int_t k = 0; k < Nkinvars; k++) {
    c->cd(k + 1);
    electronGraph[k][0]->Draw("AP");
    electronGraph[k][1]->Draw("P");
    electronGraph[k][2]->Draw("P");
    electronGraph[k][3]->Draw("P");

    // legend
    if (k == 0) {
      TLegend *legend = new TLegend(0.6, 0.65, 0.85, 0.9);  // x1,y1,x2,y2
      legend->AddEntry(electronGraph[k][0], "D (Sim. Rec.)", "pl");
      legend->AddEntry(electronGraph[k][1], "C (Sim. Rec.)", "pl");
      legend->AddEntry(electronGraph[k][2], "Fe (Sim. Rec.)", "pl");
      legend->AddEntry(electronGraph[k][3], "Pb (Sim. Rec.)", "pl");
      legend->SetFillStyle(0);
      legend->SetTextFont(62);
      legend->SetTextSize(0.04);
      legend->SetBorderSize(0);
      legend->Draw();
    }
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_sim";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
