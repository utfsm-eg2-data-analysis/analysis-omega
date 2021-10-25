#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#include "OmegaElectronNumbers.hxx"
#include "OmegaMCElectronNumbers.hxx"
#include "OmegaSimElectronNumbers.hxx"

const Int_t Ntargets = 4;
const Int_t Nkinvars = 4;
const Int_t Nbins = 4;

void MakeMR_AcceptanceCorr(TString StoreOption = "") {
  // Calculate and draw MR after background subtraction via event mixing, electron numbers and acceptance corr. factors

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** MAIN ***/

  TString kinvarOption[Nkinvars] = {"Q2", "Nu", "wZ", "wPt2"};
  TString kinvarTitle[Nkinvars] = {"Q^{2} [GeV^{2}]", "#nu [GeV]", "z_{h}", "p_{T}^{2} [GeV^{2}]"};
  Double_t EdgesKinvar[Nkinvars][Nbins + 1];
  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[0][i] = kEdgesQ2[i];
    EdgesKinvar[1][i] = kEdgesNu[i];
    EdgesKinvar[2][i] = kEdgesZ[i];
    EdgesKinvar[3][i] = kEdgesPt2[i];
  }

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  // declare input files
  TFile *HistFile_Data[Ntargets][Nkinvars];
  TFile *HistFile_MC[Ntargets][Nkinvars];
  TFile *HistFile_Sim[Ntargets][Nkinvars];

  // declare output histograms
  TH1D *NOmega_Data[Ntargets][Nkinvars];
  TH1D *NOmega_MC[Ntargets][Nkinvars];
  TH1D *NOmega_Sim[Ntargets][Nkinvars];
  TH1D *NOmega_Acceptance[Ntargets][Nkinvars];
  TH1D *NOmega_AccCorr[Ntargets][Nkinvars];

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
      HistFile_Data[t][k] = new TFile(gProDir + "/gfx/omega_evnt-mixing/evnt-mixing_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      HistFile_MC[t][k] = new TFile(gProDir + "/gfx/omega_mc/parent-id_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      HistFile_Sim[t][k] = new TFile(gProDir + "/gfx/omega_sim/evnt-mixing_" + targetString[t] + "_" + kinvarOption[k] + ".root");

      // create output histograms
      NOmega_Data[t][k] =
          new TH1D("NOmega_Data_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NOmega_MC[t][k] =
          new TH1D("NOmega_MC_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NOmega_Sim[t][k] =
          new TH1D("NOmega_Sim_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NOmega_Acceptance[t][k] =
          new TH1D("NOmega_Acceptance_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NOmega_AccCorr[t][k] =
          new TH1D("NOmega_AccCorr_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

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

        /*** OMEGA DATA ***/

        TF1 *auxFit_Data = (TF1 *)HistFile_Data[t][k]->Get(Form("model_%i", i));
        TH1D *auxHist_Data = (TH1D *)HistFile_Data[t][k]->Get(Form("sub_%i", i));

        Double_t fitMean_Data = auxFit_Data->GetParameter(1);
        Double_t fitSigma_Data = auxFit_Data->GetParameter(2);

        // remove negative entries
        Double_t auxNOmega_Data = 0;
        Double_t auxNOmegaError_Data = 0;
        for (Int_t s = TMath::Floor((fitMean_Data - 3 * fitSigma_Data - 0.66) / 0.01);
             s <= TMath::Ceil((fitMean_Data + 3 * fitSigma_Data - 0.66) / 0.01); s++) {
          if (auxHist_Data->GetBinContent(s) > 0) {
            auxNOmega_Data += auxHist_Data->GetBinContent(s);
          }
          if (auxHist_Data->GetBinContent(s) > 0) {
            auxNOmegaError_Data += auxHist_Data->GetBinError(s) * auxHist_Data->GetBinError(s);
          }
        }
        auxNOmegaError_Data = TMath::Sqrt(auxNOmegaError_Data);

        // set bin content
        NOmega_Data[t][k]->SetBinContent(i + 1, auxNOmega_Data);
        NOmega_Data[t][k]->SetBinError(i + 1, auxNOmegaError_Data);

        /*** OMEGA MC ***/

        TH1D *auxHist_MC = (TH1D *)HistFile_MC[t][k]->Get(Form("hist_%i", i));

        // set bin content
        NOmega_MC[t][k]->SetBinContent(i + 1, auxHist_MC->GetEntries());
        NOmega_MC[t][k]->SetBinError(i + 1, TMath::Sqrt(auxHist_MC->GetEntries()));

        /*** OMEGA SIMREC ***/

        TF1 *auxFit_Sim = (TF1 *)HistFile_Sim[t][k]->Get(Form("model_%i", i));
        TH1D *auxHist_Sim = (TH1D *)HistFile_Sim[t][k]->Get(Form("sub_%i", i));

        Double_t fitMean_Sim = auxFit_Sim->GetParameter(1);
        Double_t fitSigma_Sim = auxFit_Sim->GetParameter(2);

        // remove negative entries
        Double_t auxNOmega_Sim = 0;
        Double_t auxNOmegaError_Sim = 0;
        for (Int_t s = TMath::Floor((fitMean_Sim - 3 * fitSigma_Sim - 0.66) / 0.01);
             s <= TMath::Ceil((fitMean_Sim + 3 * fitSigma_Sim - 0.66) / 0.01); s++) {
          if (auxHist_Sim->GetBinContent(s) > 0) {
            auxNOmega_Sim += auxHist_Sim->GetBinContent(s);
          }
          if (auxHist_Sim->GetBinContent(s) > 0) {
            auxNOmegaError_Sim += auxHist_Sim->GetBinError(s) * auxHist_Sim->GetBinError(s);
          }
        }
        auxNOmegaError_Sim = TMath::Sqrt(auxNOmegaError_Sim);

        // set bin content
        NOmega_Sim[t][k]->SetBinContent(i + 1, auxNOmega_Sim);
        NOmega_Sim[t][k]->SetBinError(i + 1, auxNOmegaError_Sim);

        /*** ELECTRONS DATA ***/

        if (k == 0) {
          // Q2
          NElectron_Data[t][k]->SetBinContent(i + 1, kNElecQ2_Omega[t][i]);
          NElectron_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_Omega[t][i]));
        } else if (k == 1) {
          // Nu
          NElectron_Data[t][k]->SetBinContent(i + 1, kNElecNu_Omega[t][i]);
          NElectron_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_Omega[t][i]));
        } else {
          // wZ or wPt2
          NElectron_Data[t][k]->SetBinContent(i + 1, kNElec_Omega[t]);
          NElectron_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElec_Omega[t]));
        }

        /*** ELECTRONS MC ***/

        if (k == 0) {
          // Q2
          NElectron_Data[t][k]->SetBinContent(i + 1, kNElecQ2_OmegaMC[t][i]);
          NElectron_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_OmegaMC[t][i]));
        } else if (k == 1) {
          // Nu
          NElectron_Data[t][k]->SetBinContent(i + 1, kNElecNu_OmegaMC[t][i]);
          NElectron_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_OmegaMC[t][i]));
        } else {
          // wZ or wPt2
          NElectron_Data[t][k]->SetBinContent(i + 1, kNElec_OmegaMC[t]);
          NElectron_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElec_OmegaMC[t]));
        }

        /*** ELECTRONS SIMREC ***/

        if (k == 0) {
          // Q2
          NElectron_Data[t][k]->SetBinContent(i + 1, kNElecQ2_OmegaSim[t][i]);
          NElectron_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_OmegaSim[t][i]));
        } else if (k == 1) {
          // Nu
          NElectron_Data[t][k]->SetBinContent(i + 1, kNElecNu_OmegaSim[t][i]);
          NElectron_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_OmegaSim[t][i]));
        } else {
          // wZ or wPt2
          NElectron_Data[t][k]->SetBinContent(i + 1, kNElec_OmegaSim[t]);
          NElectron_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(kNElec_OmegaSim[t]));
        }
      }  // end of loop over bins

      // calculate acceptance of omegas
      NOmega_Acceptance[t][k]->Divide(NOmega_Sim[t][k], NOmega_MC[t][k], 1, 1, "B");

      // correct number of omegas
      NOmega_AccCorr[t][k]->Divide(NOmega_Data[t][k], NOmega_Acceptance[t][k], 1, 1);

      // calculate acceptance of electrons
      NElectron_Acceptance[t][k]->Divide(NElectron_Sim[t][k], NElectron_MC[t][k], 1, 1, "B");

      // correct number of electrons
      NElectron_AccCorr[t][k]->Divide(NElectron_Data[t][k], NElectron_Acceptance[t][k], 1, 1);

      // get Nh/Ne
      Ratio[t][k]->Divide(NOmega_AccCorr[t][k], NElectron_AccCorr[t][k], 1, 1);

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
    }
  }

  // set style
  for (Int_t k = 0; k < Nkinvars; k++) {
    acceptanceGraph[1][k]->SetTitle("");

    acceptanceGraph[1][k]->GetYaxis()->SetTitle("R_{A}^{#omega}");
    acceptanceGraph[1][k]->GetYaxis()->SetRangeUser(0., 1.6);
    acceptanceGraph[1][k]->GetYaxis()->SetTitleSize(0.06);
    acceptanceGraph[1][k]->GetYaxis()->SetMaxDigits(3);

    acceptanceGraph[1][k]->GetXaxis()->SetTitle(kinvarTitle[k]);
    acceptanceGraph[1][k]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
    acceptanceGraph[1][k]->GetXaxis()->SetTitleSize(0.06);

    for (Int_t t = 0; t < Ntargets; t++) {
      acceptanceGraph[t][k]->SetMarkerStyle(21);
      acceptanceGraph[t][k]->SetMarkerSize(2);
      acceptanceGraph[t][k]->SetMarkerColor(targetColor[t]);
      acceptanceGraph[t][k]->SetLineColor(targetColor[t]);
      acceptanceGraph[t][k]->SetLineWidth(5);
    }
  }

  /*** DRAW ***/

  SetMyStyle();

  // define canvas
  TString CanvasName = "omega-MR_with-acceptance";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 2160);
  c->Divide(2, 2, 0.001, 0.001);  // nx, ny, margins

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
    TString OutputDir = gProDir + "/gfx/omega_acceptance";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
