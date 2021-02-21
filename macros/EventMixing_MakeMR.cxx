#include "Global.h"

// from FitSub.cxx results

void EventMixing_MakeMR(TString kinvarOption, TString particleOption = "omega") {

  const Int_t Nbins = 4;
  const Int_t Ntargets = 4;

  Double_t fitOmega[Ntargets][Nbins];
  Double_t fitOmegaError[Ntargets][Nbins];

  /*** INPUT ***/

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

  TFile *rootInputFile[Ntargets];
  TH1D *omegaHist[Ntargets];
  TH1D *electronHist[Ntargets];
  TH1D *ratioHist[Ntargets];
  TH1D *omegaMR[Ntargets];

  for (Int_t t = 0; t < Ntargets; t++) {
    rootInputFile[t] = new TFile(gProDir + "/macros/out/evnt-mixing-" + particleOption + "_fit-sub_" + targetString[t] + ".root");
    omegaHist[t] = new TH1D("omegaNumber_" + targetString[t], "", Nbins, EdgesKinvar[0], EdgesKinvar[Nbins]);
    electronHist[t] = new TH1D("electronNumber_" + targetString[t], "", Nbins, EdgesKinvar[0], EdgesKinvar[Nbins]);
    ratioHist[t] = new TH1D("ratio_" + targetString[t], "", Nbins, EdgesKinvar[0], EdgesKinvar[Nbins]);
    omegaMR[t] = new TH1D("omegaMR_" + targetString[t], "", Nbins, EdgesKinvar[0], EdgesKinvar[Nbins]);
    for (Int_t i = 0; i < Nbins; i++) {
      TF1 *Fit = (TF1 *)rootInputFile[t]->Get(Form("fit_%d_%d", i, kinvarIndex));
      TFitResultPtr FitResult = (TFitResult *)rootInputFile[t]->Get(Form("TFitResult-sub_%d_%d-fit_%d_%d", i, kinvarIndex, i, kinvarIndex));
      std::vector<Double_t> Parameters = FitResult->Parameters();
      std::vector<Double_t> Errors = FitResult->Errors();
      fitOmega[t][i] = Fit->Integral(plotMin, plotMax) / 0.01;
      fitOmegaError[t][i] = Fit->IntegralError(plotMin, plotMax, FitResult->GetParams(), FitResult->GetCovarianceMatrix().GetMatrixArray(), 1e-1) / 0.01;
      // fill hist
      omegaHist[t]->SetBinContent(i + 1, fitOmega[t][i]);
      omegaHist[t]->SetBinError(i + 1, fitOmegaError[t][i]);
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
      ratioHist[t]->Divide(omegaHist[t], electronHist[t]);
      // divide solid targets with liquid target
      if (t > 0) omegaMR[t]->Divide(ratioHist[t], ratioHist[0]);
    }
  }

  /*** DEFINE GRAPHS ***/

  // define arrays
  Double_t empty[Nbins];
  Double_t MR_x[Nbins];
  Double_t MR_xerr[Nbins];
  Double_t MR_y[Ntargets][Nbins];
  Double_t MR_yerr[Ntargets][Nbins];

  // fill arrays
  for (Int_t i = 0; i < Nbins; i++) {
    empty[i] = 0.;
    MR_x[i] = (EdgesKinvar[i] + EdgesKinvar[i + 1]) / 2.;
    MR_xerr[i] = (EdgesKinvar[i + 1] - EdgesKinvar[i]) / TMath::Sqrt(12);
    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MR_y[tt][i] = omegaMR[tt]->GetBinContent(i + 1);
      MR_yerr[tt][i] = omegaMR[tt]->GetBinError(i + 1);
    }
  }

  // define graphs
  TGraphErrors *MRgraph[Ntargets];
  for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
    MRgraph[tt] = new TGraphErrors(Nbins, MR_x, MR_y[tt], MR_xerr, MR_yerr[tt]);
  }

  // set style
  MRgraph[1]->SetTitle("Multiplicity Ratio: #" + particleOption);
  MRgraph[1]->GetXaxis()->SetTitle(kinvarTitle);
  MRgraph[1]->GetXaxis()->SetNdivisions(500 + Nbins, kFALSE);
  MRgraph[1]->GetXaxis()->SetLimits(EdgesKinvar[0], EdgesKinvar[Nbins]);
  MRgraph[1]->GetYaxis()->SetTitle("R_{#" + particleOption + "}");
  MRgraph[1]->GetYaxis()->SetRangeUser(0., maxMR);

  for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
    MRgraph[tt]->SetMarkerStyle(21);
    MRgraph[tt]->SetMarkerSize(1.5);
    MRgraph[tt]->SetMarkerColor(targetColor[tt]);
    MRgraph[tt]->SetLineColor(targetColor[tt]);
    MRgraph[tt]->SetLineWidth(3);
  }

  /*** DRAW ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  // define canvas
  TCanvas *c = new TCanvas("evnt-mixing_MR_" + kinvarOption, "", 1000, 1000);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  MRgraph[1]->Draw("AP");  // Carbon
  MRgraph[2]->Draw("P");   // Iron
  MRgraph[3]->Draw("P");   // Lead

  // legend
  TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(MRgraph[1], "Carbon", "p");
  legend->AddEntry(MRgraph[2], "Iron", "p");
  legend->AddEntry(MRgraph[3], "Lead", "p");
  legend->Draw();
  
  /*
  c->Print(plotFile);  // output file
  */
}
