#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#include "EtaElectronNumbers.hxx"
#include "EtaMCElectronNumbers.hxx"
#include "EtaSimElectronNumbers.hxx"

const Int_t Ntargets = 4;
const Int_t Nkinvars = 4;
const Int_t Nbins = 5;

void MakeMR_AcceptanceCorr(TString StoreOption = "") {
  // Calculate and draw MR from fit results, electron numbers and acceptance corr. factors

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
  TFile *FitFile_Data[Ntargets][Nkinvars];
  TFile *HistFile_MC[Ntargets][Nkinvars];
  TFile *FitFile_Sim[Ntargets][Nkinvars];

  // declare output histograms
  TH1D *NEta_Data[Ntargets][Nkinvars];
  TH1D *NEta_MC[Ntargets][Nkinvars];
  TH1D *NEta_Sim[Ntargets][Nkinvars];
  TH1D *NEta_Acceptance[Ntargets][Nkinvars];
  TH1D *NEta_AccCorr[Ntargets][Nkinvars];

  TH1D *NElectron_Data[Ntargets][Nkinvars];
  TH1D *NElectron_MC[Ntargets][Nkinvars];
  TH1D *NElectron_Sim[Ntargets][Nkinvars];
  TH1D *NElectron_Acceptance[Ntargets][Nkinvars];
  TH1D *NElectron_AccCorr[Ntargets][Nkinvars];

  TH1D *Ratio[Ntargets][Nkinvars];  // N_h/N_e
  TH1D *MR[Ntargets][Nkinvars];     // R_A/R_D

  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {

      // open files (read only)
      FitFile_Data[t][k] =
          new TFile(gProDir + "/gfx/eta_bkg-fitting/bkg-fitting_" + targetString[t] + "_" + kinvarOption[k] + ".root", "READ");
      HistFile_MC[t][k] = new TFile(gProDir + "/gfx/eta_mc/parent-id_" + targetString[t] + "_" + kinvarOption[k] + ".root", "READ");
      FitFile_Sim[t][k] = new TFile(gProDir + "/gfx/eta_sim/bkg-fitting_" + targetString[t] + "_" + kinvarOption[k] + ".root", "READ");

      // create output histograms
      NEta_Data[t][k] =
          new TH1D("NEta_Data_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NEta_MC[t][k] = new TH1D("NEta_MC_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NEta_Sim[t][k] = new TH1D("NEta_Sim_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NEta_Acceptance[t][k] =
          new TH1D("NEta_Acceptance_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NEta_AccCorr[t][k] =
          new TH1D("NEta_AccCorr_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      NElectron_Data[t][k] =
          new TH1D("NElectron_Data_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NElectron_MC[t][k] =
          new TH1D("NElectron_MC_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NElectron_Sim[t][k] =
          new TH1D("NElectron_Sim_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NElectron_Acceptance[t][k] =
          new TH1D("NElectron_Acceptance_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NElectron_AccCorr[t][k] =
          new TH1D("NElectron_AccCorr_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      Ratio[t][k] = new TH1D("Ratio_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      MR[t][k] = new TH1D("MR_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      // loop over bins
      for (Int_t i = 0; i < Nbins; i++) {

        /*** ETA DATA ***/

        RooFitResult *auxFitResult_Data = (RooFitResult *)FitFile_Data[t][k]->Get(Form("fit-result_%i", i));
        Double_t auxNEta_Data = ((RooRealVar *)auxFitResult_Data->floatParsFinal().find("N_{#eta}"))->getValV();
        Double_t auxNEtaError_Data = ((RooRealVar *)auxFitResult_Data->floatParsFinal().find("N_{#eta}"))->getAsymErrorHi();

        // set bin content
        NEta_Data[t][k]->SetBinContent(i + 1, auxNEta_Data);
        NEta_Data[t][k]->SetBinError(i + 1, auxNEtaError_Data);

        /*** ETA MC ***/

        TH1D *auxHist_MC = (TH1D *)HistFile_MC[t][k]->Get(Form("hist_%i", i));

        // set bin content
        NEta_MC[t][k]->SetBinContent(i + 1, auxHist_MC->GetEntries());
        NEta_MC[t][k]->SetBinError(i + 1, TMath::Sqrt(auxHist_MC->GetEntries()));

        /*** ETA SIMREC ***/

        RooFitResult *auxFitResult_Sim = (RooFitResult *)FitFile_Sim[t][k]->Get(Form("fit-result_%i", i));
        Double_t auxNEta_Sim = ((RooRealVar *)auxFitResult_Sim->floatParsFinal().find("N_{#eta}"))->getValV();
        Double_t auxNEtaError_Sim = ((RooRealVar *)auxFitResult_Sim->floatParsFinal().find("N_{#eta}"))->getAsymErrorHi();

        // set bin content
        NEta_Sim[t][k]->SetBinContent(i + 1, auxNEta_Sim);
        NEta_Sim[t][k]->SetBinError(i + 1, auxNEtaError_Sim);

        /*** ELECTRONS DATA ***/

        if (k == 0) {
          // Q2
          NElectron_Data[t][k]->SetBinContent(i + 1, kNElecQ2_Eta[t][i]);
          NElectron_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_Eta[t][i]));
        } else if (k == 1) {
          // Nu
          NElectron_Data[t][k]->SetBinContent(i + 1, kNElecNu_Eta[t][i]);
          NElectron_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_Eta[t][i]));
        } else {
          // wZ or wPt2
          NElectron_Data[t][k]->SetBinContent(i + 1, kNElec_Eta[t]);
          NElectron_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElec_Eta[t]));
        }

        /*** ELECTRONS MC ***/

        if (k == 0) {
          // Q2
          NElectron_MC[t][k]->SetBinContent(i + 1, kNElecQ2_EtaMC[t][i]);
          NElectron_MC[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_EtaMC[t][i]));
        } else if (k == 1) {
          // Nu
          NElectron_MC[t][k]->SetBinContent(i + 1, kNElecNu_EtaMC[t][i]);
          NElectron_MC[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_EtaMC[t][i]));
        } else {
          // wZ or wPt2
          NElectron_MC[t][k]->SetBinContent(i + 1, kNElec_EtaMC[t]);
          NElectron_MC[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElec_EtaMC[t]));
        }

        /*** ELECTRONS SIMREC ***/

        if (k == 0) {
          // Q2
          NElectron_Sim[t][k]->SetBinContent(i + 1, kNElecQ2_EtaSim[t][i]);
          NElectron_Sim[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_EtaSim[t][i]));
        } else if (k == 1) {
          // Nu
          NElectron_Sim[t][k]->SetBinContent(i + 1, kNElecNu_EtaSim[t][i]);
          NElectron_Sim[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_EtaSim[t][i]));
        } else {
          // wZ or wPt2
          NElectron_Sim[t][k]->SetBinContent(i + 1, kNElec_EtaSim[t]);
          NElectron_Sim[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElec_EtaSim[t]));
        }
      }  // end of loop over bins

      // calculate acceptance of etas
      NEta_Acceptance[t][k]->Divide(NEta_Sim[t][k], NEta_MC[t][k], 1, 1, "B");

      // correct number of etas
      NEta_AccCorr[t][k]->Divide(NEta_Data[t][k], NEta_Acceptance[t][k], 1, 1);

      // calculate acceptance of electrons
      NElectron_Acceptance[t][k]->Divide(NElectron_Sim[t][k], NElectron_MC[t][k], 1, 1, "B");

      // correct number of electrons
      NElectron_AccCorr[t][k]->Divide(NElectron_Data[t][k], NElectron_Acceptance[t][k], 1, 1);

      // get Nh/Ne
      Ratio[t][k]->Divide(NEta_AccCorr[t][k], NElectron_AccCorr[t][k], 1, 1);

      // calculate final MR
      MR[t][k]->Divide(Ratio[t][k], Ratio[0][k], 1, 1);
    }
  }

  /*** GRAPHS ***/

  // define arrays
  Double_t binCenter[Nkinvars][Nbins];
  Double_t binError[Nkinvars][Nbins];

  Double_t acceptanceValue[Ntargets][Nkinvars][Nbins];
  Double_t acceptanceError[Ntargets][Nkinvars][Nbins];

  // fill arrays
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      binCenter[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      binError[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / 2;
      // fill acceptance values and errors
      for (Int_t t = 0; t < Ntargets; t++) {
        acceptanceValue[t][k][i] = MR[t][k]->GetBinContent(i + 1);
        acceptanceError[t][k][i] = MR[t][k]->GetBinError(i + 1);
      }
    }
  }

  // set graphs
  TGraphErrors *acceptanceGraph[Ntargets][Nkinvars];
  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {
      acceptanceGraph[t][k] = new TGraphErrors(Nbins, binCenter[k], acceptanceValue[t][k], binError[k], acceptanceError[t][k]);
      // set style
      acceptanceGraph[t][k]->SetTitle("");
      acceptanceGraph[t][k]->SetMarkerStyle(21);
      acceptanceGraph[t][k]->SetMarkerSize(2);
      acceptanceGraph[t][k]->SetMarkerColor(targetColor[t]);
      acceptanceGraph[t][k]->SetLineColor(targetColor[t]);
      acceptanceGraph[t][k]->SetLineWidth(5);
    }
  }

  for (Int_t k = 0; k < Nkinvars; k++) {
    // set y-axis
    acceptanceGraph[1][k]->GetYaxis()->SetRangeUser(0., 1.6);
    if (k == 3) {
      acceptanceGraph[1][k]->GetYaxis()->SetRangeUser(0., 2.5);
    }
    acceptanceGraph[1][k]->GetYaxis()->SetTitle("R_{A}^{#eta}");
    acceptanceGraph[1][k]->GetYaxis()->SetTitleSize(0.06);
    acceptanceGraph[1][k]->GetYaxis()->SetMaxDigits(3);
    // set x-axis
    acceptanceGraph[1][k]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
    acceptanceGraph[1][k]->GetXaxis()->SetTitle(kinvarTitle[k]);
    acceptanceGraph[1][k]->GetXaxis()->SetTitleSize(0.06);
  }

  /*** DRAW ***/

  SetMyStyle();

  // define canvas
  TString CanvasName = "eta-MR_with-acceptance";
  Int_t Nx = 2;
  Int_t Ny = 2;
  TCanvas *c = new TCanvas(CanvasName, CanvasName, Nx * 1080, Ny * 1080);
  c->Divide(Nx, Ny, 0.001, 0.001);  // nx, ny, margins

  for (Int_t k = 0; k < Nkinvars; k++) {
    c->cd(k + 1);

    // draw per kinvar, only solid targets
    acceptanceGraph[1][k]->Draw("AP");
    acceptanceGraph[2][k]->Draw("P");
    acceptanceGraph[3][k]->Draw("P");

    // legend
    if (k == 1) {
      TLegend *legend = new TLegend(0.2, 0.75, 0.45, 0.9);  // x1,y1,x2,y2
      legend->AddEntry(acceptanceGraph[1][k], "C (Acc. Corr.)", "pl");
      legend->AddEntry(acceptanceGraph[2][k], "Fe (Acc. Corr.)", "pl");
      legend->AddEntry(acceptanceGraph[3][k], "Pb (Acc. Corr.)", "pl");
      legend->SetFillStyle(0);
      legend->SetTextFont(62);
      legend->SetTextSize(0.04);
      legend->SetBorderSize(0);
      legend->Draw();
    }
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_acceptance";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
