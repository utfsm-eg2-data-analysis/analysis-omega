#ifndef GLOBAL_H
#include "Global.h"
#endif

void AcceptanceElectron() {

  const Int_t Nkinvars = 2;
  const Int_t Ntargets = 4;
  const Int_t Nbins = 4;
  
  /*** INPUT ***/

  TString kinvarOption[2] = {"Q2", "Nu"};
  TString titleAxis[2];
  TString histProperties[2];
  titleAxis[0] = "Q^{2} [GeV^{2}]";
  histProperties[0] = "(100, 1., 4.)";
  titleAxis[1] = "#nu [GeV]";
  histProperties[1] = "(100, 2.2, 4.2)";

  Double_t EdgesKinvar[Nkinvars][Nbins + 1];
  for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[0][i] = kEdgesQ2[i];
  for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[1][i] = kEdgesNu[i];
  
  TString targetString[4] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[4] = {kGreen + 3, kRed, kBlue, kBlack};

  TFile *rootInputFile_Sim[Nkinvars][Ntargets];
  TFile *rootInputFile_MC[Nkinvars][Ntargets];

  Double_t plotMin = 0.66;
  Double_t plotMax = 0.90;
  
  /*** DEFINE HISTOGRAMS ***/

  TH1D *electronHist_Sim[Nkinvars][Ntargets];
  TH1D *electronHist_MC[Nkinvars][Ntargets];
  TH1D *acceptanceHist[Nkinvars][Ntargets];
  
  for (Int_t t = 0; t < Ntargets; t++) {

    electronHist_Sim[0][t] = new TH1D("electronNumberQ2_Sim_" + targetString[t], "", Nbins, EdgesKinvar[0][0], EdgesKinvar[0][Nbins]);
    electronHist_MC[0][t] = new TH1D("electronNumberQ2_MC_" + targetString[t], "", Nbins, EdgesKinvar[0][0], EdgesKinvar[0][Nbins]);
    acceptanceHist[0][t] = new TH1D("acceptanceQ2_" + targetString[t], "", Nbins, EdgesKinvar[0][0], EdgesKinvar[0][Nbins]);

    electronHist_Sim[1][t] = new TH1D("electronNumberNu_Sim_" + targetString[t], "", Nbins, EdgesKinvar[1][0], EdgesKinvar[1][Nbins]);
    electronHist_MC[1][t] = new TH1D("electronNumberNu_MC_" + targetString[t], "", Nbins, EdgesKinvar[1][0], EdgesKinvar[1][Nbins]);
    acceptanceHist[1][t] = new TH1D("acceptanceNu_" + targetString[t], "", Nbins, EdgesKinvar[1][0], EdgesKinvar[1][Nbins]);
    
    // fill hists
    for (Int_t i = 0; i < Nbins; i++) {  // i for bins
      // Q2
      electronHist_Sim[0][t]->SetBinContent(i + 1, kNElecQ2_Sim[t][i]);
      electronHist_Sim[0][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_Sim[t][i]));

      electronHist_MC[0][t]->SetBinContent(i + 1, kNElecQ2_MC[t][i]);
      electronHist_MC[0][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_MC[t][i]));

      // Nu
      electronHist_Sim[1][t]->SetBinContent(i + 1, kNElecNu_Sim[t][i]);
      electronHist_Sim[1][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_Sim[t][i]));

      electronHist_MC[1][t]->SetBinContent(i + 1, kNElecNu_MC[t][i]);
      electronHist_MC[1][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_MC[t][i]));
    }
      
    // calculate acceptance with binomial errors
    acceptanceHist[0][t]->Divide(electronHist_Sim[0][t], electronHist_MC[0][t], 1, 1, "B");
    acceptanceHist[1][t]->Divide(electronHist_Sim[1][t], electronHist_MC[1][t], 1, 1, "B");
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
	acceptanceValue[k][t][i] = acceptanceHist[k][t]->GetBinContent(i+1);
	acceptanceError[k][t][i] = acceptanceHist[k][t]->GetBinError(i+1);
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
      acceptanceGraph[k][t]->SetLineWidth(2);
      acceptanceGraph[k][t]->SetMarkerStyle(20);
    }
  }

  /*** SET Y AXIS ***/

  for (Int_t k = 0; k < Nkinvars; k++) {
    acceptanceGraph[k][0]->GetYaxis()->SetRangeUser(0., 0.6);

    acceptanceGraph[k][0]->GetYaxis()->SetTitle("A_{e-} = N^{rec}_{e-}/N^{gen}_{e-}");
    acceptanceGraph[k][0]->GetYaxis()->SetTitleSize(0.06);
    acceptanceGraph[k][0]->GetYaxis()->SetTitleOffset(1.);
    acceptanceGraph[k][0]->GetYaxis()->SetMaxDigits(3);

    acceptanceGraph[k][0]->GetXaxis()->SetTitle(titleAxis[k]);
    acceptanceGraph[k][0]->GetXaxis()->SetTitleSize(0.06);
  }
  
  /*** DRAW ***/
  
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLineWidth(2);
 
  // set margin sizes
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
 
  TCanvas *c = new TCanvas("acceptance-electron", "acceptance-electron", 1080, 540);
  c->Divide(2, 1, 0.01, 0.01);  // nx, ny, margins

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  for (Int_t k = 0; k < Nkinvars; k++) {
    c->cd(k+1);
    // draw per kinvar
    acceptanceGraph[k][0]->Draw("AP");
    acceptanceGraph[k][1]->Draw("P");
    acceptanceGraph[k][2]->Draw("P");
    acceptanceGraph[k][3]->Draw("P");
    // legend
    TLegend *legend = new TLegend(0.75, 0.65, 0.9, 0.9);  // x1,y1,x2,y2
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

}
