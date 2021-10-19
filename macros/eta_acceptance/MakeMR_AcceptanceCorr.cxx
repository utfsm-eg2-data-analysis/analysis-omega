#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#include "EtaElectronNumbers.hxx"
#include "EtaMCElectronNumbers.hxx"
#include "EtaSimElectronNumbers.hxx"

const Int_t Nkinvars = 4;
const Int_t Ntargets = 4;
const Int_t Nbins = 5;

void MakeMR_AcceptanceCorr(TString StoreOption = "") {
  // Calculate and draw MR after background subtraction via event mixing, obtained electron numbers and acceptance corr. factors

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** MAIN ***/

  Double_t fitEta_Data[Nkinvars][Ntargets][Nbins];
  Double_t fitEtaError_Data[Nkinvars][Ntargets][Nbins];

  Double_t fitEta_Sim[Nkinvars][Ntargets][Nbins];
  Double_t fitEtaError_Sim[Nkinvars][Ntargets][Nbins];

  Double_t intEta_MC[Nkinvars][Ntargets][Nbins];
  Double_t intEtaError_MC[Nkinvars][Ntargets][Nbins];

  TString kinvarOption[Nkinvars] = {"Q2", "Nu", "nZ", "nPt2"};
  TString titleAxis[Nkinvars];
  TString histProperties[Nkinvars];
  titleAxis[0] = "Q^{2} [GeV^{2}]";
  histProperties[0] = "(100, 1., 4.1)";
  titleAxis[1] = "#nu [GeV]";
  histProperties[1] = "(100, 2.2, 4.25)";
  titleAxis[2] = "z_{h}";
  histProperties[2] = "(100, 0.5, 1.0)";
  titleAxis[3] = "p_{T}^{2} [GeV^{2}]";
  histProperties[3] = "(100, 0., 1.5)";

  Double_t EdgesKinvar[Nkinvars][Nbins + 1];
  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[0][i] = kEdgesQ2_Eta[i];
    EdgesKinvar[1][i] = kEdgesNu_Eta[i];
    EdgesKinvar[2][i] = kEdgesZ_Eta[i];
    EdgesKinvar[3][i] = kEdgesPt2_Eta[i];
  }

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  TFile *rootInputFile_Data[Nkinvars][Ntargets];
  TFile *rootInputFile_Sim[Nkinvars][Ntargets];
  TFile *rootInputFile_MC[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {

      // open files
      rootInputFile_Data[k][t] =
          new TFile(gProDir + "/gfx/eta_bkg-fitting/bkg-fitting_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      rootInputFile_MC[k][t] = new TFile(gProDir + "/gfx/eta_mc/parent-id_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      rootInputFile_Sim[k][t] = new TFile(gProDir + "/gfx/eta_sim/bkg-fitting_" + targetString[t] + "_" + kinvarOption[k] + ".root");

      // loop over bins
      for (Int_t i = 0; i < Nbins; i++) {

        /*** ETA DATA ***/

        RooFitResult *FitResult_Data = (RooFitResult *)rootInputFile_Data[k][t]->Get(Form("fit-result_%i", i));
        fitEta_Data[k][t][i] = ((RooRealVar *)FitResult_Data->floatParsFinal().find("N_{#eta}"))->getValV();
        fitEtaError_Data[k][t][i] = ((RooRealVar *)FitResult_Data->floatParsFinal().find("N_{#eta}"))->getAsymErrorHi();

        /*** ETA SIMREC ***/

        RooFitResult *FitResult_Sim = (RooFitResult *)rootInputFile_Sim[k][t]->Get(Form("fit-result_%i", i));
        fitEta_Sim[k][t][i] = ((RooRealVar *)FitResult_Sim->floatParsFinal().find("N_{#eta}"))->getValV();
        fitEtaError_Sim[k][t][i] = ((RooRealVar *)FitResult_Sim->floatParsFinal().find("N_{#eta}"))->getAsymErrorHi();

        /*** ETA MC ***/

        TH1D *Hist_MC = (TH1D *)rootInputFile_MC[k][t]->Get(Form("hist_%i", i));

        intEta_MC[k][t][i] = Hist_MC->GetEntries();
        intEtaError_MC[k][t][i] = TMath::Sqrt(intEta_MC[k][t][i]);
      }
    }
  }

  /*** HISTOGRAMS ***/

  TH1D *electronHist_Data[Nkinvars][Ntargets];
  TH1D *etaHist_Data[Nkinvars][Ntargets];

  TH1D *ratioHist_Data[Nkinvars][Ntargets];  // N_h/N_e
  TH1D *MR[Nkinvars][Ntargets];              // R_A/R_D

  TH1D *electronHist_Sim[Nkinvars][Ntargets];
  TH1D *electronHist_MC[Nkinvars][Ntargets];
  TH1D *electronAcceptance[Nkinvars][Ntargets];

  TH1D *etaHist_Sim[Nkinvars][Ntargets];
  TH1D *etaHist_MC[Nkinvars][Ntargets];
  TH1D *etaAcceptance[Nkinvars][Ntargets];

  TH1D *AccCorrFactorsHist[Nkinvars][Ntargets];
  TH1D *AccCorrRatiosHist[Nkinvars][Ntargets];

  TH1D *MRCorr[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {

      /*** ELECTRONS FROM DATA ***/

      electronHist_Data[k][t] =
          new TH1D("electronNumber_Data_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      // fill hists, loop over bins
      for (Int_t i = 0; i < Nbins; i++) {
        if (k == 0) {
          // Q2
          electronHist_Data[k][t]->SetBinContent(i + 1, kNElecQ2_Eta[t][i]);
          electronHist_Data[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_Eta[t][i]));
        } else if (k == 1) {
          // Nu
          electronHist_Data[k][t]->SetBinContent(i + 1, kNElecNu_Eta[t][i]);
          electronHist_Data[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_Eta[t][i]));
        } else {  // k == 2 (wZ) or k == 3 (wPt2)
          electronHist_Data[k][t]->SetBinContent(i + 1, kNElec_Eta[t]);
          electronHist_Data[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElec_Eta[t]));
        }
      }

      /*** ETA FROM DATA ***/

      etaHist_Data[k][t] =
          new TH1D("etaNumber_Data_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      // fill hists, loop over bins
      for (Int_t i = 0; i < Nbins; i++) {
        etaHist_Data[k][t]->SetBinContent(i + 1, fitEta_Data[k][t][i]);
        etaHist_Data[k][t]->SetBinError(i + 1, fitEtaError_Data[k][t][i]);
      }

      /*** ETA/ELECTRONS RATIOS ***/

      // calculate N_h/N_e with standard errors
      ratioHist_Data[k][t] =
          new TH1D("Ratio_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      ratioHist_Data[k][t]->Divide(etaHist_Data[k][t], electronHist_Data[k][t], 1, 1);

      /*** UNCORR. MR ***/

      // calculate multiplicity ratios with standard errors
      MR[k][t] = new TH1D("MR_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      MR[k][t]->Divide(ratioHist_Data[k][t], ratioHist_Data[k][0], 1, 1);

      /*** ELECTRONS ACCEPTANCE ***/

      electronHist_Sim[k][t] =
          new TH1D("electronNumber_Sim_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      electronHist_MC[k][t] =
          new TH1D("electronNumber_MC_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      electronAcceptance[k][t] =
          new TH1D("electronAcceptance_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      // fill hists, loop over bins
      for (Int_t i = 0; i < Nbins; i++) {
        if (k == 0) {
          // Q2
          electronHist_Sim[k][t]->SetBinContent(i + 1, kNElecQ2_EtaSim[t][i]);
          electronHist_Sim[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_EtaSim[t][i]));

          electronHist_MC[k][t]->SetBinContent(i + 1, kNElecQ2_EtaMC[t][i]);
          electronHist_MC[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_EtaMC[t][i]));
        } else if (k == 1) {
          // Nu
          electronHist_Sim[k][t]->SetBinContent(i + 1, kNElecNu_EtaSim[t][i]);
          electronHist_Sim[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_EtaSim[t][i]));

          electronHist_MC[k][t]->SetBinContent(i + 1, kNElecNu_EtaMC[t][i]);
          electronHist_MC[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_EtaMC[t][i]));
        } else {  // k == 2 (wZ) or k == 3 (wPt2)
          electronHist_Sim[k][t]->SetBinContent(i + 1, kNElec_EtaSim[t]);
          electronHist_Sim[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElec_EtaSim[t]));

          electronHist_MC[k][t]->SetBinContent(i + 1, kNElec_EtaMC[t]);
          electronHist_MC[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElec_EtaMC[t]));
        }
      }

      // calculate electrons acceptance with binomial errors
      electronAcceptance[k][t]->Divide(electronHist_Sim[k][t], electronHist_MC[k][t], 1, 1, "B");

      /*** ETA ACCEPTANCE ***/

      etaHist_Sim[k][t] =
          new TH1D("etaNumber_Sim_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      etaHist_MC[k][t] =
          new TH1D("etaNumber_MC_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      etaAcceptance[k][t] =
          new TH1D("etaAcceptance_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      // fill hists, loop over bins
      for (Int_t i = 0; i < Nbins; i++) {
        etaHist_Sim[k][t]->SetBinContent(i + 1, fitEta_Sim[k][t][i]);
        etaHist_Sim[k][t]->SetBinError(i + 1, fitEtaError_Sim[k][t][i]);

        etaHist_MC[k][t]->SetBinContent(i + 1, intEta_MC[k][t][i]);
        etaHist_MC[k][t]->SetBinError(i + 1, intEtaError_MC[k][t][i]);
      }

      // calculate eta acceptance with binomial errors
      etaAcceptance[k][t]->Divide(etaHist_Sim[k][t], etaHist_MC[k][t], 1, 1, "B");

      /*** ELECTRON/ETA ACCEPTANCE ***/

      // calculate acceptance corr factors with standard errors
      AccCorrFactorsHist[k][t] =
          new TH1D("AccCorrFactors_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      AccCorrFactorsHist[k][t]->Divide(electronAcceptance[k][t], etaAcceptance[k][t], 1, 1);

      /*** SOLID/LIQUID ACCEPTANCE ***/
      // calculate solid-to-liquid ratio of acceptance corr factors with standard errors
      AccCorrRatiosHist[k][t] =
          new TH1D("AccCorrRatios_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      AccCorrRatiosHist[k][t]->Divide(AccCorrFactorsHist[k][t], AccCorrFactorsHist[k][0], 1, 1);

      /*** CORRECTED MR ***/

      // calculate acceptance-corrected MR with standard errors
      MRCorr[k][t] = new TH1D("MRCorr_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      MRCorr[k][t]->Multiply(AccCorrRatiosHist[k][t], MR[k][t], 1, 1);
    }
  }

  /*** GRAPHS ***/

  // define arrays
  Double_t binCenter[Nkinvars][Nbins];
  Double_t binError[Nkinvars][Nbins];

  Double_t acceptanceValue[Nkinvars][Ntargets][Nbins];
  Double_t acceptanceError[Nkinvars][Ntargets][Nbins];

  // fill arrays
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      binCenter[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      binError[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / 2;
      // fill acceptance values and errors
      for (Int_t t = 0; t < Ntargets; t++) {
        acceptanceValue[k][t][i] = MRCorr[k][t]->GetBinContent(i + 1);
        acceptanceError[k][t][i] = MRCorr[k][t]->GetBinError(i + 1);
      }
    }
  }

  // set graphs
  TGraphErrors *acceptanceGraph[Nkinvars][Ntargets];
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      acceptanceGraph[k][t] = new TGraphErrors(Nbins, binCenter[k], acceptanceValue[k][t], binError[k], acceptanceError[k][t]);
    }
  }

  // set style
  for (Int_t k = 0; k < Nkinvars; k++) {
    acceptanceGraph[k][1]->SetTitle("");

    acceptanceGraph[k][1]->GetYaxis()->SetTitle("R_{A}^{#eta}");

    // set y-axis
    acceptanceGraph[k][1]->GetYaxis()->SetRangeUser(0., 1.6);
    if (k == 3) {
      acceptanceGraph[k][1]->GetYaxis()->SetRangeUser(0., 2.5);
    }
    acceptanceGraph[k][1]->GetYaxis()->SetTitleSize(0.06);
    acceptanceGraph[k][1]->GetYaxis()->SetMaxDigits(3);

    acceptanceGraph[k][1]->GetXaxis()->SetTitle(titleAxis[k]);
    acceptanceGraph[k][1]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
    acceptanceGraph[k][1]->GetXaxis()->SetTitleSize(0.06);

    for (Int_t t = 0; t < Ntargets; t++) {
      acceptanceGraph[k][t]->SetMarkerStyle(21);
      acceptanceGraph[k][t]->SetMarkerSize(2);
      acceptanceGraph[k][t]->SetMarkerColor(targetColor[t]);
      acceptanceGraph[k][t]->SetLineColor(targetColor[t]);
      acceptanceGraph[k][t]->SetLineWidth(5);
    }
  }

  /*** DRAW ***/

  SetMyStyle();

  // define canvas
  TString CanvasName = "eta-MR_with-acceptance";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 2160);
  c->Divide(2, 2, 0.001, 0.001);  // nx, ny, margins

  for (Int_t k = 0; k < Nkinvars; k++) {
    c->cd(k + 1);
    // draw per kinvar, only solid targets
    acceptanceGraph[k][1]->Draw("AP");
    acceptanceGraph[k][2]->Draw("P");
    acceptanceGraph[k][3]->Draw("P");
    // legend
    if (k == 1) {
      TLegend *legend = new TLegend(0.2, 0.75, 0.45, 0.9);  // x1,y1,x2,y2
      legend->AddEntry(acceptanceGraph[k][1], "C (Acc. Corr.)", "pl");
      legend->AddEntry(acceptanceGraph[k][2], "Fe (Acc. Corr.)", "pl");
      legend->AddEntry(acceptanceGraph[k][3], "Pb (Acc. Corr.)", "pl");
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
