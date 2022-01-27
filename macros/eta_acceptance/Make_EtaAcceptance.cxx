#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Nkinvars = 4;
const Int_t Ntargets = 4;
const Int_t Nbins = 5;

void Make_EtaAcceptance(TString StoreOption = "") {
  // Calculate and draw acceptance of etas, depending on all kin. vars.

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** MAIN ***/

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

  TFile *rootInputFile_Sim[Nkinvars][Ntargets];
  TFile *rootInputFile_MC[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {

      // open files
      rootInputFile_MC[k][t] = new TFile(gProDir + "/gfx/eta_mc/parent-id_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      rootInputFile_Sim[k][t] = new TFile(gProDir + "/gfx/eta_sim/bkg-fitting_" + targetString[t] + "_" + kinvarOption[k] + ".root");

      // loop over bins
      for (Int_t i = 0; i < Nbins; i++) {

        /*** SIMREC ***/

        RooFitResult *FitResult = (RooFitResult *)rootInputFile_Sim[k][t]->Get(Form("fit-result_%i", i));
        fitEta_Sim[k][t][i] = ((RooRealVar *)FitResult->floatParsFinal().find("N_{#eta}"))->getValV();
        fitEtaError_Sim[k][t][i] = ((RooRealVar *)FitResult->floatParsFinal().find("N_{#eta}"))->getAsymErrorHi();

        /*** MC ***/

        TH1D *Hist_MC = (TH1D *)rootInputFile_MC[k][t]->Get(Form("hist_%i", i));

        intEta_MC[k][t][i] = Hist_MC->GetEntries();
        intEtaError_MC[k][t][i] = TMath::Sqrt(intEta_MC[k][t][i]);
      }
    }
  }

  /*** HISTOGRAMS ***/

  TH1D *etaHist_Sim[Nkinvars][Ntargets];
  TH1D *etaHist_MC[Nkinvars][Ntargets];
  TH1D *acceptanceHist[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {

      etaHist_Sim[k][t] =
          new TH1D("etaNumber_Sim_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      etaHist_MC[k][t] =
          new TH1D("etaNumber_MC_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      acceptanceHist[k][t] =
          new TH1D("etaAcceptance_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      // fill hists, loop over bins
      for (Int_t i = 0; i < Nbins; i++) {
        etaHist_Sim[k][t]->SetBinContent(i + 1, fitEta_Sim[k][t][i]);
        etaHist_Sim[k][t]->SetBinError(i + 1, fitEtaError_Sim[k][t][i]);

        etaHist_MC[k][t]->SetBinContent(i + 1, intEta_MC[k][t][i]);
        etaHist_MC[k][t]->SetBinError(i + 1, intEtaError_MC[k][t][i]);
      }

      // calculate acceptance with binomial errors
      acceptanceHist[k][t]->Divide(etaHist_Sim[k][t], etaHist_MC[k][t], 1, 1, "B");
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

    acceptanceGraph[k][0]->GetYaxis()->SetRangeUser(0., 1.2 * MaxRange[k]);
    acceptanceGraph[k][0]->GetYaxis()->SetTitle("N^{rec}_{#eta}/N^{gen}_{#eta}");
    acceptanceGraph[k][0]->GetYaxis()->SetTitleSize(0.06);
    acceptanceGraph[k][0]->GetYaxis()->SetTitleOffset(1.);
    acceptanceGraph[k][0]->GetYaxis()->SetMaxDigits(3);

    acceptanceGraph[k][0]->GetXaxis()->SetTitle(titleAxis[k]);
    acceptanceGraph[k][0]->GetXaxis()->SetTitleSize(0.06);
    acceptanceGraph[k][0]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
  }

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "eta-acceptance";
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
    TString OutputDir = gProDir + "/gfx/eta_acceptance";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}