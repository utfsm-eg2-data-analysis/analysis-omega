#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#include "OmegaMCElectronNumbers.hxx"
#include "OmegaSimElectronNumbers.hxx"

const Int_t Nkinvars = 4;
const Int_t Ntargets = 4;
const Int_t Nbins = 4;

void Make_AcceptanceCorrRatios(TString StoreOption = "") {
  // Calculate and draw solid-to-liquid ratio of acceptance corrections factors

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** MAIN ***/

  Double_t intOmega_Sim[Nkinvars][Ntargets][Nbins];
  Double_t intOmegaError_Sim[Nkinvars][Ntargets][Nbins];

  Double_t intOmega_MC[Nkinvars][Ntargets][Nbins];
  Double_t intOmegaError_MC[Nkinvars][Ntargets][Nbins];

  TString kinvarOption[Nkinvars] = {"Q2", "Nu", "wZ", "wPt2"};
  TString titleAxis[Nkinvars];
  TString histProperties[Nkinvars];
  titleAxis[0] = "Q^{2} [GeV^{2}]";
  histProperties[0] = "(100, 1., 4.)";
  titleAxis[1] = "#nu [GeV]";
  histProperties[1] = "(100, 2.2, 4.2)";
  titleAxis[2] = "z_{h}";
  histProperties[2] = "(100, 0.5, 0.9)";
  titleAxis[3] = "p_{T}^{2} [GeV^{2}]";
  histProperties[3] = "(100, 0., 1.5)";

  Double_t EdgesKinvar[Nkinvars][Nbins + 1];
  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[0][i] = kEdgesQ2[i];
    EdgesKinvar[1][i] = kEdgesNu[i];
    EdgesKinvar[2][i] = kEdgesZ[i];
    EdgesKinvar[3][i] = kEdgesPt2[i];
  }

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  TFile *rootInputFile_Sim[Nkinvars][Ntargets];
  TFile *rootInputFile_MC[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {

      // open files
      rootInputFile_MC[k][t] = new TFile(gProDir + "/gfx/omega_mc/parent-id_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      rootInputFile_Sim[k][t] = new TFile(gProDir + "/gfx/omega_sim/evnt-mixing_" + targetString[t] + "_" + kinvarOption[k] + ".root");

      // loop over bins
      for (Int_t i = 0; i < Nbins; i++) {

        /*** OMEGA SIMREC ***/

        TF1 *Fit_Sim = (TF1 *)rootInputFile_Sim[k][t]->Get(Form("model_%i", i));
        TH1D *Hist_Sim = (TH1D *)rootInputFile_Sim[k][t]->Get(Form("sub_%i", i));

        Double_t fitMean_Sim = Fit_Sim->GetParameter(1);
        Double_t fitSigma_Sim = Fit_Sim->GetParameter(2);

        // remove negative entries
        intOmega_Sim[k][t][i] = 0;
        intOmegaError_Sim[k][t][i] = 0;
        for (Int_t s = TMath::Floor((fitMean_Sim - 3 * fitSigma_Sim - 0.66) / 0.01);
             s <= TMath::Ceil((fitMean_Sim + 3 * fitSigma_Sim - 0.66) / 0.01); s++) {
          if (Hist_Sim->GetBinContent(s) > 0) intOmega_Sim[k][t][i] += Hist_Sim->GetBinContent(s);
          if (Hist_Sim->GetBinContent(s) > 0) intOmegaError_Sim[k][t][i] += Hist_Sim->GetBinError(s) * Hist_Sim->GetBinError(s);
        }
        intOmegaError_Sim[k][t][i] = TMath::Sqrt(intOmegaError_Sim[k][t][i]);

        /*** OMEGA MC ***/

        TH1D *Hist_MC = (TH1D *)rootInputFile_MC[k][t]->Get(Form("hist_%i", i));

        intOmega_MC[k][t][i] = Hist_MC->GetEntries();
        intOmegaError_MC[k][t][i] = TMath::Sqrt(intOmega_MC[k][t][i]);
      }
    }
  }

  /*** HISTOGRAMS ***/

  TH1D *electronHist_Sim[Nkinvars][Ntargets];
  TH1D *electronHist_MC[Nkinvars][Ntargets];
  TH1D *electronAcceptance[Nkinvars][Ntargets];

  TH1D *omegaHist_Sim[Nkinvars][Ntargets];
  TH1D *omegaHist_MC[Nkinvars][Ntargets];
  TH1D *omegaAcceptance[Nkinvars][Ntargets];

  TH1D *AccCorrFactorsHist[Nkinvars][Ntargets];
  TH1D *AccCorrRatiosHist[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {

      /*** ELECTRONS ***/

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
          electronHist_Sim[k][t]->SetBinContent(i + 1, kNElecQ2_OmegaSim[t][i]);
          electronHist_Sim[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_OmegaSim[t][i]));

          electronHist_MC[k][t]->SetBinContent(i + 1, kNElecQ2_OmegaMC[t][i]);
          electronHist_MC[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_OmegaMC[t][i]));
        } else if (k == 1) {
          // Nu
          electronHist_Sim[k][t]->SetBinContent(i + 1, kNElecNu_OmegaSim[t][i]);
          electronHist_Sim[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_OmegaSim[t][i]));

          electronHist_MC[k][t]->SetBinContent(i + 1, kNElecNu_OmegaMC[t][i]);
          electronHist_MC[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_OmegaMC[t][i]));
        } else {  // k == 2 (wZ) or k == 3 (wPt2)
          electronHist_Sim[k][t]->SetBinContent(i + 1, kNElec_OmegaSim[t]);
          electronHist_Sim[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElec_OmegaSim[t]));

          electronHist_MC[k][t]->SetBinContent(i + 1, kNElec_OmegaMC[t]);
          electronHist_MC[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElec_OmegaMC[t]));
        }
      }

      // calculate electrons acceptance with binomial errors
      electronAcceptance[k][t]->Divide(electronHist_Sim[k][t], electronHist_MC[k][t], 1, 1, "B");

      /*** OMEGA ***/

      omegaHist_Sim[k][t] =
          new TH1D("omegaNumber_Sim_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      omegaHist_MC[k][t] =
          new TH1D("omegaNumber_MC_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      omegaAcceptance[k][t] =
          new TH1D("omegaAcceptance_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      // fill hists, loop over bins
      for (Int_t i = 0; i < Nbins; i++) {
        omegaHist_Sim[k][t]->SetBinContent(i + 1, intOmega_Sim[k][t][i]);
        omegaHist_Sim[k][t]->SetBinError(i + 1, intOmegaError_Sim[k][t][i]);

        omegaHist_MC[k][t]->SetBinContent(i + 1, intOmega_MC[k][t][i]);
        omegaHist_MC[k][t]->SetBinError(i + 1, intOmegaError_MC[k][t][i]);
      }

      // calculate omega acceptance with binomial errors
      omegaAcceptance[k][t]->Divide(omegaHist_Sim[k][t], omegaHist_MC[k][t], 1, 1, "B");

      /*** ELECTRON/OMEGA ***/

      // calculate acceptance corr factors with standard errors
      AccCorrFactorsHist[k][t] =
          new TH1D("AccCorrFactors_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      AccCorrFactorsHist[k][t]->Divide(electronAcceptance[k][t], omegaAcceptance[k][t], 1, 1);

      /*** SOLID/LIQUID ***/

      // calculate solid-to-liquid ratio of acceptance corr factors with standard errors
      AccCorrRatiosHist[k][t] =
          new TH1D("AccCorrRatios_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      AccCorrRatiosHist[k][t]->Divide(AccCorrFactorsHist[k][t], AccCorrFactorsHist[k][0], 1, 1);
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
        acceptanceValue[k][t][i] = AccCorrRatiosHist[k][t]->GetBinContent(i + 1);
        acceptanceError[k][t][i] = AccCorrRatiosHist[k][t]->GetBinError(i + 1);
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

  Double_t MaxRange[Nkinvars] = {0, 0, 0, 0};
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      // get the maximum of an array of length Nbins, and compare it with MaxRange
      if (TMath::MaxElement(Nbins, acceptanceGraph[k][t]->GetY()) > MaxRange[k]) {
        MaxRange[k] = TMath::MaxElement(Nbins, acceptanceGraph[k][t]->GetY());
      }
    }
  }

  for (Int_t k = 0; k < Nkinvars; k++) {
    acceptanceGraph[k][1]->GetYaxis()->SetRangeUser(0., 1.5 * MaxRange[k]);

    acceptanceGraph[k][1]->GetYaxis()->SetTitle("R_{A, corr}^{#omega} / R_{A, uncorr}^{#omega}");
    acceptanceGraph[k][1]->GetYaxis()->SetTitleSize(0.06);
    acceptanceGraph[k][1]->GetYaxis()->SetTitleOffset(1.);
    acceptanceGraph[k][1]->GetYaxis()->SetMaxDigits(3);

    acceptanceGraph[k][1]->GetXaxis()->SetTitle(titleAxis[k]);
    acceptanceGraph[k][1]->GetXaxis()->SetTitleSize(0.06);
  }

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "acceptance-corr-ratios";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 2160);
  c->Divide(2, 2, 0.001, 0.001);  // nx, ny, margins

  for (Int_t k = 0; k < Nkinvars; k++) {
    c->cd(k + 1);
    // draw per kinvar, only solid targets
    acceptanceGraph[k][1]->Draw("AP");
    acceptanceGraph[k][2]->Draw("P");
    acceptanceGraph[k][3]->Draw("P");
    // legend
    if (k == 0) {
      TLegend *legend = new TLegend(0.8, 0.75, 0.9, 0.9);  // x1,y1,x2,y2
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

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_acceptance";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
