#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#include "EtaMCElectronNumbers.hxx"
#include "EtaSimElectronNumbers.hxx"

const Int_t Nkinvars = 2;
const Int_t Ntargets = 4;
const Int_t Nbins = 5;

void Make_ElectronAcceptance(TString StoreOption = "") {
  // Calculate and draw acceptance of electrons, depending on Q2 and Nu, based on eta binning

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** MAIN ***/

  TString kinvarOption[Nkinvars] = {"Q2", "Nu"};
  TString titleAxis[Nkinvars];
  TString histProperties[Nkinvars];
  titleAxis[0] = "Q^{2} [GeV^{2}]";
  histProperties[0] = "(100, 1., 4.1)";
  titleAxis[1] = "#nu [GeV]";
  histProperties[1] = "(100, 2.2, 4.25)";

  Double_t EdgesKinvar[Nkinvars][Nbins + 1];
  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[0][i] = kEdgesQ2_Eta[i];
    EdgesKinvar[1][i] = kEdgesNu_Eta[i];
  }

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  /*** HISTOGRAMS ***/

  TH1D *electronHist_Sim[Nkinvars][Ntargets];
  TH1D *electronHist_MC[Nkinvars][Ntargets];
  TH1D *acceptanceHist[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {

      electronHist_Sim[k][t] =
          new TH1D("electronNumber_Sim_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      electronHist_MC[k][t] =
          new TH1D("electronNumber_MC_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      acceptanceHist[k][t] =
          new TH1D("electronAcceptance_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      // fill hists, loop over bins
      for (Int_t i = 0; i < Nbins; i++) {
        if (k == 0) {
          // Q2
          electronHist_Sim[k][t]->SetBinContent(i + 1, kNElecQ2_EtaSim[t][i]);
          electronHist_Sim[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_EtaSim[t][i]));

          electronHist_MC[k][t]->SetBinContent(i + 1, kNElecQ2_EtaMC[t][i]);
          electronHist_MC[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_EtaMC[t][i]));
        } else {  // k == 1
          // Nu
          electronHist_Sim[k][t]->SetBinContent(i + 1, kNElecNu_EtaSim[t][i]);
          electronHist_Sim[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_EtaSim[t][i]));

          electronHist_MC[k][t]->SetBinContent(i + 1, kNElecNu_EtaMC[t][i]);
          electronHist_MC[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_EtaMC[t][i]));
        }
      }

      // calculate acceptance with binomial errors
      acceptanceHist[k][t]->Divide(electronHist_Sim[k][t], electronHist_MC[k][t], 1, 1, "B");
    }
  }

  /*** DEFINE GRAPHS ***/

  // define arrays
  Double_t binCenter[Nkinvars][Nbins];
  Double_t binError[Nkinvars][Nbins];

  Double_t acceptanceValue[Nkinvars][Ntargets][Nbins];
  Double_t acceptanceError[Nkinvars][Ntargets][Nbins];

  // fill arrays
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      binCenter[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      binError[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / TMath::Sqrt(12);

      // fill acceptance values and errors
      for (Int_t t = 0; t < Ntargets; t++) {
        acceptanceValue[k][t][i] = acceptanceHist[k][t]->GetBinContent(i + 1);
        acceptanceError[k][t][i] = acceptanceHist[k][t]->GetBinError(i + 1);
      }
    }
  }

  // set graphs
  TGraphErrors *acceptanceGraph[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      acceptanceGraph[k][t] = new TGraphErrors(Nbins, binCenter[k], acceptanceValue[k][t], binError[k], acceptanceError[k][t]);

      // style
      acceptanceGraph[k][t]->SetTitle("");
      acceptanceGraph[k][t]->SetMarkerColor(targetColor[t]);
      acceptanceGraph[k][t]->SetLineColor(targetColor[t]);
      acceptanceGraph[k][t]->SetLineWidth(3);
      acceptanceGraph[k][t]->SetMarkerStyle(21);
      acceptanceGraph[k][t]->SetMarkerSize(1.5);
    }
  }

  /*** SET Y AXIS ***/

  for (Int_t k = 0; k < Nkinvars; k++) {
    acceptanceGraph[k][0]->GetYaxis()->SetRangeUser(0., 0.6);

    acceptanceGraph[k][0]->GetYaxis()->SetTitle("N^{rec}_{e-}/N^{gen}_{e-}");
    acceptanceGraph[k][0]->GetYaxis()->SetTitleSize(0.06);
    acceptanceGraph[k][0]->GetYaxis()->SetTitleOffset(1.);
    acceptanceGraph[k][0]->GetYaxis()->SetMaxDigits(3);

    acceptanceGraph[k][0]->GetXaxis()->SetTitle(titleAxis[k]);
    acceptanceGraph[k][0]->GetXaxis()->SetTitleSize(0.06);
  }

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "electron-acceptance";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 1080);
  c->Divide(2, 1, 0.001, 0.001);  // nx, ny, margins

  for (Int_t k = 0; k < Nkinvars; k++) {
    c->cd(k + 1);
    // draw per kinvar
    acceptanceGraph[k][0]->Draw("AP");
    acceptanceGraph[k][1]->Draw("P");
    acceptanceGraph[k][2]->Draw("P");
    acceptanceGraph[k][3]->Draw("P");
    // legend
    TLegend *legend = new TLegend(0.8, 0.2, 0.9, 0.4);  // x1,y1,x2,y2
    legend->AddEntry(acceptanceGraph[k][0], "D", "pl");
    legend->AddEntry(acceptanceGraph[k][1], "C", "pl");
    legend->AddEntry(acceptanceGraph[k][2], "Fe", "pl");
    legend->AddEntry(acceptanceGraph[k][3], "Pb", "pl");
    legend->SetFillStyle(0);
    legend->SetTextFont(62);
    legend->SetTextSize(0.04);
    legend->SetBorderSize(0);
    legend->Draw();
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_acceptance";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
