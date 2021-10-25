#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Nkinvars = 4;
const Int_t Ntargets = 4;
const Int_t Nbins = 4;

void Make_OmegaAcceptance(TString StoreOption = "") {
  // Calculate and draw acceptance of omegas, depending on all kin. vars.

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

        /*** SIMREC ***/

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

        /*** MC ***/

        TH1D *Hist_MC = (TH1D *)rootInputFile_MC[k][t]->Get(Form("hist_%i", i));

        intOmega_MC[k][t][i] = Hist_MC->GetEntries();
        intOmegaError_MC[k][t][i] = TMath::Sqrt(intOmega_MC[k][t][i]);
      }
    }
  }

  /*** HISTOGRAMS ***/

  TH1D *omegaHist_Sim[Nkinvars][Ntargets];
  TH1D *omegaHist_MC[Nkinvars][Ntargets];
  TH1D *acceptanceHist[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {

      omegaHist_Sim[k][t] =
          new TH1D("omegaNumber_Sim_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      omegaHist_MC[k][t] =
          new TH1D("omegaNumber_MC_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      acceptanceHist[k][t] =
          new TH1D("omegaAcceptance_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      // fill hists, loop over bins
      for (Int_t i = 0; i < Nbins; i++) {
        omegaHist_Sim[k][t]->SetBinContent(i + 1, intOmega_Sim[k][t][i]);
        omegaHist_Sim[k][t]->SetBinError(i + 1, intOmegaError_Sim[k][t][i]);

        omegaHist_MC[k][t]->SetBinContent(i + 1, intOmega_MC[k][t][i]);
        omegaHist_MC[k][t]->SetBinError(i + 1, intOmegaError_MC[k][t][i]);
      }

      // calculate acceptance with binomial errors
      acceptanceHist[k][t]->Divide(omegaHist_Sim[k][t], omegaHist_MC[k][t], 1, 1, "B");
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
    acceptanceGraph[k][0]->GetYaxis()->SetRangeUser(0., 2.5e-3);

    acceptanceGraph[k][0]->GetYaxis()->SetTitle("N^{rec}_{#omega}/N^{gen}_{#omega}");
    acceptanceGraph[k][0]->GetYaxis()->SetTitleSize(0.06);
    acceptanceGraph[k][0]->GetYaxis()->SetTitleOffset(1.);
    acceptanceGraph[k][0]->GetYaxis()->SetMaxDigits(3);

    acceptanceGraph[k][0]->GetXaxis()->SetTitle(titleAxis[k]);
    acceptanceGraph[k][0]->GetXaxis()->SetTitleSize(0.06);
    acceptanceGraph[k][0]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
  }

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "omega-acceptance";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 2160);
  c->Divide(2, 2, 0.001, 0.001);  // nx, ny, margins

  for (Int_t k = 0; k < Nkinvars; k++) {
    c->cd(k + 1);
    // draw per kinvar
    acceptanceGraph[k][0]->Draw("AP");
    acceptanceGraph[k][1]->Draw("P");
    acceptanceGraph[k][2]->Draw("P");
    acceptanceGraph[k][3]->Draw("P");
    // legend
    if (k == 0) {
      TLegend *legend = new TLegend(0.2, 0.7, 0.4, 0.9);  // x1,y1,x2,y2
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

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_acceptance";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
