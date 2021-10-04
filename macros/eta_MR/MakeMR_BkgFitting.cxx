#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#include "EtaElectronNumbers.hxx"

const Int_t Nbins = 5;
const Int_t Ntargets = 4;
const Int_t Nkinvars = 4;

void MakeMR_BkgFitting(TString StoreOption = "") {
  // Calculate and draw MR from fit results and electron numbers

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** MAIN ***/

  TString kinvarOption[Nkinvars] = {"Q2", "Nu", "nZ", "nPt2"};
  TString kinvarTitle[Nkinvars] = {"Q^{2} [GeV^{2}]", "#nu [GeV]", "z_{h}", "p_{T}^{2} [GeV^{2}]"};
  Double_t EdgesKinvar[Nkinvars][Nbins + 1];
  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[0][i] = kEdgesQ2_Eta[i];
    EdgesKinvar[1][i] = kEdgesNu_Eta[i];
    EdgesKinvar[2][i] = kEdgesZ_Eta[i];
    EdgesKinvar[3][i] = kEdgesPt2_Eta[i];
  }

  // fix y-axis max range
  Double_t maxMR = 1.4;

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  TFile *FitFile[Nkinvars][Ntargets];
  TH1D *omegaHist[Nkinvars][Ntargets];
  TH1D *electronHist[Nkinvars][Ntargets];
  TH1D *ratioHist[Nkinvars][Ntargets];
  TH1D *MR[Nkinvars][Ntargets];

  Double_t fitOmega[Nkinvars][Ntargets][Nbins];
  Double_t fitOmegaError[Nkinvars][Ntargets][Nbins];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      // data
      FitFile[k][t] = new TFile(gProDir + "/gfx/eta_bkg-fitting/bkg-fitting_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      omegaHist[k][t] = new TH1D("omegaNumber_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      electronHist[k][t] = new TH1D("electronNumber_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      ratioHist[k][t] = new TH1D("ratio_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      MR[k][t] = new TH1D("MR_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      for (Int_t i = 0; i < Nbins; i++) {
        RooFitResult *FitResult = (RooFitResult *)FitFile[k][t]->Get(Form("fit-result_%d", i));
        fitOmega[k][t][i] = ((RooRealVar *)FitResult->floatParsFinal().find("N_{#eta}"))->getValV();
        fitOmegaError[k][t][i] = ((RooRealVar *)FitResult->floatParsFinal().find("N_{#eta}"))->getAsymErrorHi();
        // fill hist
        omegaHist[k][t]->SetBinContent(i + 1, fitOmega[k][t][i]);
        omegaHist[k][t]->SetBinError(i + 1, fitOmegaError[k][t][i]);
        // electron hist
        if (k == 0) {
          electronHist[k][t]->SetBinContent(i + 1, kNElecQ2_Eta[t][i]);
          electronHist[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_Eta[t][i]));
        } else if (k == 1) {
          electronHist[k][t]->SetBinContent(i + 1, kNElecNu_Eta[t][i]);
          electronHist[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_Eta[t][i]));
        } else if (k == 2 || k == 3) {
          electronHist[k][t]->SetBinContent(i + 1, kNElec_Eta[t]);
          electronHist[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElec_Eta[t]));
        }
      }
      // calculate first ratio (normalize by electrons) and divide solid targets with liquid target
      ratioHist[k][t]->Divide(omegaHist[k][t], electronHist[k][t]);
      if (t > 0) MR[k][t]->Divide(ratioHist[k][t], ratioHist[k][0]);
    }
  }

  /*** DEFINE GRAPHS ***/

  // define arrays
  Double_t empty[Nkinvars][Nbins];
  Double_t MR_x[Nkinvars][Nbins];
  Double_t MR_xerr[Nkinvars][Nbins];
  Double_t MR_y[Nkinvars][Ntargets][Nbins];
  Double_t MR_yerr[Nkinvars][Ntargets][Nbins];

  // fill arrays
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      empty[k][i] = 0.;
      MR_x[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      MR_xerr[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / 2;
      // loop over solid targets only
      for (Int_t tt = 1; tt < Ntargets; tt++) {
        MR_y[k][tt][i] = MR[k][tt]->GetBinContent(i + 1);
        MR_yerr[k][tt][i] = MR[k][tt]->GetBinError(i + 1);
      }
    }
  }

  // define graphs
  TGraphErrors *MRgraph[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    // loop over solid targets only
    for (Int_t tt = 1; tt < Ntargets; tt++) {
      MRgraph[k][tt] = new TGraphErrors(Nbins, MR_x[k], MR_y[k][tt], MR_xerr[k], MR_yerr[k][tt]);
    }
    // set style
    MRgraph[k][1]->SetTitle("");

    MRgraph[k][1]->GetXaxis()->SetTitle(kinvarTitle[k]);
    // MRgraph[k][1]->GetXaxis()->SetNdivisions(500 + Nbins, kFALSE);
    MRgraph[k][1]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
    MRgraph[k][1]->GetXaxis()->SetTitleSize(0.04);
    MRgraph[k][1]->GetXaxis()->SetTitleOffset(1.);
    MRgraph[k][1]->GetYaxis()->SetTitleSize(0.04);
    MRgraph[k][1]->GetYaxis()->SetTitleOffset(1.2);

    MRgraph[k][1]->GetYaxis()->SetTitle("R_{A}^{#eta}");

    // set y-axis
    if (k == 3) {
      MRgraph[k][1]->GetYaxis()->SetRangeUser(0., 2.5);
    } else {
      MRgraph[k][1]->GetYaxis()->SetRangeUser(0., maxMR);
    }

    // loop over solid targets only
    for (Int_t tt = 1; tt < Ntargets; tt++) {
      MRgraph[k][tt]->SetLineColor(targetColor[tt]);
      MRgraph[k][tt]->SetLineWidth(3);
      MRgraph[k][tt]->SetMarkerStyle(21);
      MRgraph[k][tt]->SetMarkerColor(targetColor[tt]);
      MRgraph[k][tt]->SetMarkerSize(2);
    }
  }

  /*** DRAW ***/

  SetMyStyle();

  // define canvas
  TString CanvasName = "eta-MR_bkg-fitting";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 2160);
  c->Divide(2, 2, 0.001, 0.001);

  Int_t counter = 0;
  for (Int_t k = 0; k < Nkinvars; k++) {
    counter++;
    c->cd(counter);

    MRgraph[k][1]->Draw("AP");  // Carbon
    MRgraph[k][2]->Draw("P");   // Iron
    MRgraph[k][3]->Draw("P");   // Lead

    // legend
    if (k == 0) {
      TLegend *legend = new TLegend(0.2, 0.75, 0.45, 0.9);  // x1,y1,x2,y2
      legend->AddEntry(MRgraph[k][1], "C (No Acc. Corr.)", "lp");
      legend->AddEntry(MRgraph[k][2], "Fe (No Acc. Corr.)", "lp");
      legend->AddEntry(MRgraph[k][3], "Pb (No Acc. Corr.)", "lp");
      legend->SetFillStyle(0);
      legend->SetTextFont(62);
      legend->SetTextSize(0.035);
      legend->SetBorderSize(0);
      legend->Draw();
    }

    c->Update();
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_MR";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
