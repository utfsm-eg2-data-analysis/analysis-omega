#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#include "EtaElectronNumbers.hxx"

const Int_t Ntargets = 4;
const Int_t Nkinvars = 4;
const Int_t Nbins = 5;

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

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  // declare input files
  TFile *FitFile[Ntargets][Nkinvars];

  // declare output histograms
  TH1D *NEta[Ntargets][Nkinvars];
  TH1D *NElectron[Ntargets][Nkinvars];
  TH1D *Ratio[Ntargets][Nkinvars];  // Nh/Ne
  TH1D *MR[Ntargets][Nkinvars];

  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {

      // open files (read only)
      FitFile[t][k] = new TFile(gProDir + "/gfx/eta_bkg-fitting/bkg-fitting_" + targetString[t] + "_" + kinvarOption[k] + ".root");

      // create output histograms
      NEta[t][k] = new TH1D("NEta_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NElectron[t][k] = new TH1D("NElectron_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      Ratio[t][k] = new TH1D("Ratio_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      MR[t][k] = new TH1D("MR_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      // loop over bins
      for (Int_t i = 0; i < Nbins; i++) {

        /*** ETA DATA ***/

        RooFitResult *auxFitResult = (RooFitResult *)FitFile[t][k]->Get(Form("fit-result_%i", i));
        Double_t auxNEta = ((RooRealVar *)auxFitResult->floatParsFinal().find("N_{#eta}"))->getValV();
        Double_t auxNEtaError = ((RooRealVar *)auxFitResult->floatParsFinal().find("N_{#eta}"))->getAsymErrorHi();

        // set bin content
        NEta[t][k]->SetBinContent(i + 1, auxNEta);
        NEta[t][k]->SetBinError(i + 1, auxNEtaError);

        /*** ELECTRONS ***/

        if (k == 0) {
          NElectron[t][k]->SetBinContent(i + 1, kNElecQ2_Eta[t][i]);
          NElectron[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_Eta[t][i]));
        } else if (k == 1) {
          NElectron[t][k]->SetBinContent(i + 1, kNElecNu_Eta[t][i]);
          NElectron[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_Eta[t][i]));
        } else {
          NElectron[t][k]->SetBinContent(i + 1, kNElec_Eta[t]);
          NElectron[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElec_Eta[t]));
        }
      }

      // normalize by electrons
      Ratio[t][k]->Divide(NEta[t][k], NElectron[t][k], 1, 1);

      // calculate MR
      MR[t][k]->Divide(Ratio[t][k], Ratio[0][k], 1, 1);
    }
  }

  /*** GRAPHS ***/

  // define arrays
  Double_t MR_x[Nkinvars][Nbins];
  Double_t MR_xerr[Nkinvars][Nbins];
  Double_t MR_y[Ntargets][Nkinvars][Nbins];
  Double_t MR_yerr[Ntargets][Nkinvars][Nbins];

  // fill arrays
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      MR_x[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      MR_xerr[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / 2;
      // loop over solid targets only
      for (Int_t t = 0; t < Ntargets; t++) {
        MR_y[t][k][i] = MR[t][k]->GetBinContent(i + 1);
        MR_yerr[t][k][i] = MR[t][k]->GetBinError(i + 1);
      }
    }
  }

  // set graphs
  TGraphErrors *MRgraph[Ntargets][Nkinvars];
  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {
      MRgraph[t][k] = new TGraphErrors(Nbins, MR_x[k], MR_y[t][k], MR_xerr[k], MR_yerr[t][k]);
    }
  }

  // set style
  for (Int_t k = 0; k < Nkinvars; k++) {
    MRgraph[1][k]->SetTitle("");

    MRgraph[1][k]->GetYaxis()->SetTitle("R_{A}^{#eta}");
    MRgraph[1][k]->GetYaxis()->SetRangeUser(0., 1.6);
    if (k == 3) {
      MRgraph[1][k]->GetYaxis()->SetRangeUser(0., 2.5);
    }
    MRgraph[1][k]->GetYaxis()->SetTitleSize(0.06);

    MRgraph[1][k]->GetXaxis()->SetTitle(kinvarTitle[k]);
    MRgraph[1][k]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
    MRgraph[1][k]->GetXaxis()->SetTitleSize(0.06);

    for (Int_t t = 0; t < Ntargets; t++) {
      MRgraph[t][k]->SetMarkerStyle(21);
      MRgraph[t][k]->SetMarkerSize(2);
      MRgraph[t][k]->SetMarkerColor(targetColor[t]);
      MRgraph[t][k]->SetLineColor(targetColor[t]);
      MRgraph[t][k]->SetLineWidth(5);
    }
  }

  /*** DRAW ***/

  SetMyStyle();

  // define canvas
  TString CanvasName = "eta-MR";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 2160);
  c->Divide(2, 2, 0.001, 0.001);  // nx, ny, margins

  for (Int_t k = 0; k < Nkinvars; k++) {
    c->cd(k + 1);

    // draw per kinvar, only solid targets
    MRgraph[1][k]->Draw("AP");
    MRgraph[2][k]->Draw("P");
    MRgraph[3][k]->Draw("P");

    // legend
    if (k == 0) {
      TLegend *legend = new TLegend(0.2, 0.75, 0.45, 0.9);  // x1,y1,x2,y2
      legend->AddEntry(MRgraph[1][k], "C (No Acc. Corr.)", "lp");
      legend->AddEntry(MRgraph[2][k], "Fe (No Acc. Corr.)", "lp");
      legend->AddEntry(MRgraph[3][k], "Pb (No Acc. Corr.)", "lp");
      legend->SetFillStyle(0);
      legend->SetTextFont(62);
      legend->SetTextSize(0.035);
      legend->SetBorderSize(0);
      legend->Draw();
    }
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_bkg-fitting";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
