#ifndef GLOBAL_H
#include "Global.h"
#endif

void EventMixing_MakeMR_v2(TString kinvarOption, TString particleOption = "omega", Int_t IncludeAcceptance = 0, Int_t OnlyWithAcceptance = 0) {
  // from bkg-subtracted histograms, fit results and electron numbers, calculate MR
  // apply acceptance results if necessary
  // v2: cuts signal from range given by fits

  const Int_t Nbins = 4;
  const Int_t Ntargets = 4;

  Double_t intOmega[Ntargets][Nbins];
  Double_t intOmegaError[Ntargets][Nbins];

  /*** INPUT ***/

  if (OnlyWithAcceptance) IncludeAcceptance = 1;

  Int_t kinvarIndex;
  TString kinvarTitle;
  Double_t EdgesKinvar[Nbins + 1];
  if (kinvarOption == "Q2") {
    kinvarIndex = 0;
    kinvarTitle = "Q^{2} (GeV^{2})";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesQ2[i];
  } else if (kinvarOption == "Nu") {
    kinvarIndex = 1;
    kinvarTitle = "#nu (GeV)";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesNu[i];
  } else if (kinvarOption == "wZ") {
    kinvarIndex = 2;
    kinvarTitle = "Z";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesZ[i];
  } else if (kinvarOption == "wPt2") {
    kinvarIndex = 3;
    kinvarTitle = "p_{T}^{2} (GeV^{2})";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesPt2[i];
  }

  Double_t plotMin, plotMax;
  Double_t maxMR;
  if (particleOption == "omega") {
    plotMin = 0.65;
    plotMax = 0.90;
    maxMR = 1.4;
  } else if (particleOption == "eta") {
    plotMin = 0.45;
    plotMax = 0.65;
    maxMR = 2.0;
  }

  TString targetString[4] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[4] = {kGreen + 3, kRed, kBlue, kBlack};

  /*** MAIN ***/

  TFile *BinnedFile[Ntargets];  // file that containts the bkg-subtracted histograms
  TFile *FitFile[Ntargets];     // fit results
  TH1D *omegaHist[Ntargets];
  TH1D *electronHist[Ntargets];
  TH1D *ratioHist[Ntargets];
  TH1D *MR[Ntargets];

  // acceptance
  TFile *AcceptanceFile[Ntargets];
  TH1D *OmegaACC[Ntargets];
  TH1D *ElectronACC[Ntargets];
  TH1D *RatioACC[Ntargets];
  TH1D *MR_ACC[Ntargets];

  for (Int_t t = 0; t < Ntargets; t++) {
    // data
    BinnedFile[t] = new TFile(gProDir + "/macros/out/evnt-mixing-" + particleOption + "_binned_" + targetString[t] + ".root");
    FitFile[t] = new TFile(gProDir + "/macros/out/evnt-mixing-" + particleOption + "_fit-sub_" + targetString[t] + ".root");
    omegaHist[t] = new TH1D("omegaNumber_" + targetString[t], "", Nbins, EdgesKinvar[0], EdgesKinvar[Nbins]);
    electronHist[t] = new TH1D("electronNumber_" + targetString[t], "", Nbins, EdgesKinvar[0], EdgesKinvar[Nbins]);
    ratioHist[t] = new TH1D("ratio_" + targetString[t], "", Nbins, EdgesKinvar[0], EdgesKinvar[Nbins]);
    MR[t] = new TH1D("MR_" + targetString[t], "", Nbins, EdgesKinvar[0], EdgesKinvar[Nbins]);
    // acceptance
    if (IncludeAcceptance) {
      AcceptanceFile[t] = new TFile(gProDir + "/macros/out/Acceptance_" + kinvarOption + ".root");
      OmegaACC[t] = AcceptanceFile[t]->Get<TH1D>("OmegaACC_" + targetString[t] + "_" + kinvarOption);
      ElectronACC[t] = AcceptanceFile[t]->Get<TH1D>("ElectronACC_" + targetString[t] + "_" + kinvarOption);
      RatioACC[t] = new TH1D("RatioACC_" + targetString[t], "", Nbins, EdgesKinvar[0], EdgesKinvar[Nbins]);
      RatioACC[t]->Divide(ElectronACC[t], OmegaACC[t], 1, 1);  // inverse to data ratios
      MR_ACC[t] = new TH1D("MR_ACC_" + targetString[t], "", Nbins, EdgesKinvar[0], EdgesKinvar[Nbins]);
    }
    for (Int_t i = 0; i < Nbins; i++) {
      // extract bkg-subtracted histograms
      TH1D *Sub = BinnedFile[t]->Get<TH1D>(Form("sub_%d_%d", i, kinvarIndex));
      // extract fit results
      TFitResultPtr FitResult = FitFile[t]->Get<TFitResult>(Form("TFitResult-sub_%d_%d-fit_%d_%d", i, kinvarIndex, i, kinvarIndex));
      std::vector<Double_t> Parameters = FitResult->Parameters();
      intOmega[t][i] = Sub->Integral(Sub->FindBin(Parameters[1] - 3 * Parameters[2]), Sub->FindBin(Parameters[1] + 3 * Parameters[2]));
      ;
      intOmegaError[t][i] = TMath::Sqrt(intOmega[t][i]);
      // fill hist
      omegaHist[t]->SetBinContent(i + 1, intOmega[t][i]);
      omegaHist[t]->SetBinError(i + 1, intOmegaError[t][i]);
      // electron hist
      if (kinvarIndex == 0) {
        electronHist[t]->SetBinContent(i + 1, kNElecQ2[t][i]);
        electronHist[t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2[t][i]));
      } else if (kinvarIndex == 1) {
        electronHist[t]->SetBinContent(i + 1, kNElecNu[t][i]);
        electronHist[t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu[t][i]));
      } else if (kinvarIndex == 2 || kinvarIndex == 3) {
        electronHist[t]->SetBinContent(i + 1, kNElec[t]);
        electronHist[t]->SetBinError(i + 1, TMath::Sqrt(kNElec[t]));
      }
    }
    // calculate first ratio (normalize by electrons) and divide solid targets with liquid target
    ratioHist[t]->Divide(omegaHist[t], electronHist[t]);
    if (t > 0) MR[t]->Divide(ratioHist[t], ratioHist[0]);
    // the same, but now for acceptance
    if (IncludeAcceptance) {
      RatioACC[t]->Multiply(ratioHist[t], RatioACC[t]);
      if (t > 0) MR_ACC[t]->Divide(RatioACC[t], RatioACC[0]);
    }
  }

  /*** DEFINE GRAPHS ***/

  // define arrays
  Double_t empty[Nbins];
  Double_t MR_x[Nbins];
  Double_t MR_xerr[Nbins];
  Double_t MR_y[Ntargets][Nbins];
  Double_t MR_yerr[Ntargets][Nbins];
  Double_t MR_ACC_y[Ntargets][Nbins];
  Double_t MR_ACC_yerr[Ntargets][Nbins];

  // fill arrays
  for (Int_t i = 0; i < Nbins; i++) {
    empty[i] = 0.;
    MR_x[i] = (EdgesKinvar[i] + EdgesKinvar[i + 1]) / 2.;
    MR_xerr[i] = (EdgesKinvar[i + 1] - EdgesKinvar[i]) / TMath::Sqrt(12);
    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MR_y[tt][i] = MR[tt]->GetBinContent(i + 1);
      MR_yerr[tt][i] = MR[tt]->GetBinError(i + 1);
      if (IncludeAcceptance) {
        MR_ACC_y[tt][i] = MR_ACC[tt]->GetBinContent(i + 1);
        MR_ACC_yerr[tt][i] = MR_ACC[tt]->GetBinError(i + 1);
      }
    }
  }

  // define graphs
  TGraphErrors *MRgraph[Ntargets];
  TGraphErrors *MR_ACCgraph[Ntargets];
  for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
    MRgraph[tt] = new TGraphErrors(Nbins, MR_x, MR_y[tt], MR_xerr, MR_yerr[tt]);
    if (IncludeAcceptance) MR_ACCgraph[tt] = new TGraphErrors(Nbins, MR_x, MR_ACC_y[tt], MR_xerr, MR_ACC_yerr[tt]);
  }

  // set style
  MRgraph[1]->SetTitle("Multiplicity Ratio: #" + particleOption);
  MRgraph[1]->GetXaxis()->SetTitle(kinvarTitle);
  MRgraph[1]->GetXaxis()->SetNdivisions(500 + Nbins, kFALSE);
  MRgraph[1]->GetXaxis()->SetLimits(EdgesKinvar[0], EdgesKinvar[Nbins]);
  MRgraph[1]->GetYaxis()->SetTitle("R_{#" + particleOption + "}");
  MRgraph[1]->GetYaxis()->SetRangeUser(0., maxMR);
  if (OnlyWithAcceptance) {
    MR_ACCgraph[1]->SetTitle("Multiplicity Ratio: #" + particleOption);
    MR_ACCgraph[1]->GetXaxis()->SetTitle(kinvarTitle);
    MR_ACCgraph[1]->GetXaxis()->SetNdivisions(500 + Nbins, kFALSE);
    MR_ACCgraph[1]->GetXaxis()->SetLimits(EdgesKinvar[0], EdgesKinvar[Nbins]);
    MR_ACCgraph[1]->GetYaxis()->SetTitle("R_{#" + particleOption + "}");
    MR_ACCgraph[1]->GetYaxis()->SetRangeUser(0., maxMR);
  }

  for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
    MRgraph[tt]->SetMarkerStyle(21);
    MRgraph[tt]->SetMarkerSize(1.5);
    MRgraph[tt]->SetMarkerColor(targetColor[tt]);
    MRgraph[tt]->SetLineColor(targetColor[tt]);
    MRgraph[tt]->SetLineWidth(3);
    if (IncludeAcceptance) {
      MR_ACCgraph[tt]->SetMarkerStyle(26);
      MR_ACCgraph[tt]->SetMarkerSize(1.5);
      MR_ACCgraph[tt]->SetMarkerColor(targetColor[tt]);
      MR_ACCgraph[tt]->SetLineColor(targetColor[tt]);
      MR_ACCgraph[tt]->SetLineWidth(3);
    }
  }

  /*** DRAW ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  // define canvas
  TCanvas *c = new TCanvas("evnt-mixing-" + particleOption + "_MR_" + kinvarOption, "", 1000, 1000);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  if (!OnlyWithAcceptance) {
    MRgraph[1]->Draw("AP");  // Carbon
    MRgraph[2]->Draw("P");   // Iron
    MRgraph[3]->Draw("P");   // Lead
    if (IncludeAcceptance) {
      MR_ACCgraph[1]->Draw("P");  // Carbon
      MR_ACCgraph[2]->Draw("P");  // Iron
      MR_ACCgraph[3]->Draw("P");  // Lead
    }
  }
  if (OnlyWithAcceptance) {
    MR_ACCgraph[1]->Draw("AP");  // Carbon
    MR_ACCgraph[2]->Draw("P");   // Iron
    MR_ACCgraph[3]->Draw("P");   // Lead
  }

  // legend
  TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);  // x1,y1,x2,y2
  if (!OnlyWithAcceptance) {
    legend->AddEntry(MRgraph[1], "Carbon", "p");
    legend->AddEntry(MRgraph[2], "Iron", "p");
    legend->AddEntry(MRgraph[3], "Lead", "p");
  }
  if (IncludeAcceptance) {
    legend->AddEntry(MR_ACCgraph[1], "Carbon + AC", "p");
    legend->AddEntry(MR_ACCgraph[2], "Iron + AC", "p");
    legend->AddEntry(MR_ACCgraph[3], "Lead + AC", "p");
  }
  legend->Draw();

  /*
  c->Print(plotFile);  // output file
  */
}
