#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Ntargets = 4;
const Int_t Nkinvars = 4;
const Int_t Nbins = 5;

void MakeMR_RadCorr_Eta(TString StoreOption = "") {
  // Calculate and draw MR after background subtraction via bkg fitting, rad. corr. electron numbers and acceptance corr. factors

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** MAIN ***/

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

  // declare input files to get acc. corrected eta numbers
  TFile *rootInputFile_Data[Ntargets][Nkinvars];
  TFile *rootInputFile_Sim[Ntargets][Nkinvars];
  TFile *rootInputFile_MC[Ntargets][Nkinvars];

  // declare output histograms
  TH1D *NEta_Data[Ntargets][Nkinvars];
  TH1D *NEta_Sim[Ntargets][Nkinvars];
  TH1D *NEta_MC[Ntargets][Nkinvars];
  TH1D *NEta_Acceptance[Ntargets][Nkinvars];
  TH1D *NEta_AccCorr[Ntargets][Nkinvars];

  // declare input file to get acc. and rad. corrected electron numbers
  TFile *rootInputFile_ElectronRC = new TFile(gProDir + "/gfx/rad-corr_electron/electron-rad-corr_eta.root");

  // declare output histogram
  TH1D *NElectron_RadCorr[Ntargets][Nkinvars];
  TH1D *Ratio_RadCorr[Ntargets][Nkinvars];  // Nh/Ne

  // declare final histogram
  TH1D *MR[Nkinvars][Ntargets];

  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {

      // open files (read only)
      rootInputFile_Data[t][k] =
          new TFile(gProDir + "/gfx/eta_bkg-fitting/bkg-fitting_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      rootInputFile_MC[t][k] = new TFile(gProDir + "/gfx/eta_mc/parent-id_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      rootInputFile_Sim[t][k] = new TFile(gProDir + "/gfx/eta_sim/bkg-fitting_" + targetString[t] + "_" + kinvarOption[k] + ".root");

      // create output histograms
      NEta_Data[t][k] =
          new TH1D("NEta_Data_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NEta_Sim[t][k] = new TH1D("NEta_Sim_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NEta_MC[t][k] = new TH1D("NEta_MC_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NEta_Acceptance[t][k] =
          new TH1D("NEta_Acceptance_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NEta_AccCorr[t][k] =
          new TH1D("NEta_AccCorr_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      NElectron_RadCorr[t][k] =
          new TH1D("NElectron_RadCorr_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      Ratio_RadCorr[t][k] =
          new TH1D("Ratio_RadCorr_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      MR[t][k] = new TH1D("MR_" + targetString[t] + "_" + kinvarOption[k], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      // loop over bins
      for (Int_t i = 0; i < Nbins; i++) {

        /*** ETA DATA ***/

        RooFitResult *auxFitResult_Data = (RooFitResult *)rootInputFile_Data[t][k]->Get(Form("fit-result_%i", i));
        Double_t auxNEta_Data = ((RooRealVar *)auxFitResult_Data->floatParsFinal().find("N_{#eta}"))->getValV();
        Double_t auxNEtaError_Data = ((RooRealVar *)auxFitResult_Data->floatParsFinal().find("N_{#eta}"))->getAsymErrorHi();

        // set bin content
        NEta_Data[t][k]->SetBinContent(i + 1, auxNEta_Data);
        NEta_Data[t][k]->SetBinError(i + 1, auxNEtaError_Data);

        /*** ETA SIMREC ***/

        RooFitResult *auxFitResult_Sim = (RooFitResult *)rootInputFile_Sim[t][k]->Get(Form("fit-result_%i", i));
        Double_t auxNEta_Sim = ((RooRealVar *)auxFitResult_Sim->floatParsFinal().find("N_{#eta}"))->getValV();
        Double_t auxNEtaError_Sim = ((RooRealVar *)auxFitResult_Sim->floatParsFinal().find("N_{#eta}"))->getAsymErrorHi();

        // set bin content
        NEta_Sim[t][k]->SetBinContent(i + 1, auxNEta_Sim);
        NEta_Sim[t][k]->SetBinError(i + 1, auxNEtaError_Sim);

        /*** ETA MC ***/

        TH1D *auxHist_MC = (TH1D *)rootInputFile_MC[t][k]->Get(Form("hist_%i", i));

        // set bin content
        NEta_MC[t][k]->SetBinContent(i + 1, auxHist_MC->GetEntries());
        NEta_MC[t][k]->SetBinError(i + 1, TMath::Sqrt(auxHist_MC->GetEntries()));

        /*** RAD CORR ELECTRONS ***/

        if (k < 2) {
          // valid for Q2 and Nu
          TH1D *auxHist_ElectronRC = (TH1D *)rootInputFile_ElectronRC->Get("ForMR_rad_corr_" + targetString[t] + "_" + kinvarOption[k]);

          NElectron_RadCorr[t][k]->SetBinContent(i + 1, auxHist_ElectronRC->GetBinContent(i + 1));
          NElectron_RadCorr[t][k]->SetBinError(i + 1, TMath::Sqrt(auxHist_ElectronRC->GetBinContent(i + 1)));  // PENDING!!
        } else {
          // when wZ or wPt2, integrate electron numbers from Q2 (it could also be from Nu)
          NElectron_RadCorr[t][k]->SetBinContent(i + 1, NElectron_RadCorr[t][0]->Integral());
          NElectron_RadCorr[t][k]->SetBinError(i + 1, TMath::Sqrt(NElectron_RadCorr[t][k]->GetBinContent(i + 1)));  // PENDING!!
        }
      }  // end of loop over bins

      // calculate acceptance
      NEta_Acceptance[t][k]->Divide(NEta_Sim[t][k], NEta_MC[t][k], 1, 1, "B");

      // correct number of etas
      NEta_AccCorr[t][k]->Divide(NEta_Data[t][k], NEta_Acceptance[t][k], 1, 1);

      // get Nh/Ne
      Ratio_RadCorr[t][k]->Divide(NEta_AccCorr[t][k], NElectron_RadCorr[t][k], 1, 1);

      // calculate final MR
      MR[t][k]->Divide(Ratio_RadCorr[t][k], Ratio_RadCorr[0][k], 1, 1);
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
  TGraphErrors *acceptanceGraph[Nkinvars][Ntargets];
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      acceptanceGraph[t][k] = new TGraphErrors(Nbins, binCenter[k], acceptanceValue[t][k], binError[k], acceptanceError[t][k]);
    }
  }

  // set style
  for (Int_t k = 0; k < Nkinvars; k++) {
    acceptanceGraph[1][k]->SetTitle("");

    acceptanceGraph[1][k]->GetYaxis()->SetTitle("R_{A}^{#eta}");
    acceptanceGraph[1][k]->GetYaxis()->SetRangeUser(0., 1.6);
    if (k == 3) {
      acceptanceGraph[1][k]->GetYaxis()->SetRangeUser(0., 2.5);
    }
    acceptanceGraph[1][k]->GetYaxis()->SetTitleSize(0.06);
    acceptanceGraph[1][k]->GetYaxis()->SetMaxDigits(3);

    acceptanceGraph[1][k]->GetXaxis()->SetTitle(titleAxis[k]);
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
  TString CanvasName = "eta-MR_with-rad-corr-and-acceptance";
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
      legend->AddEntry(acceptanceGraph[1][k], "C (Rad. + Acc. Corr.)", "pl");
      legend->AddEntry(acceptanceGraph[2][k], "Fe (Rad. + Acc. Corr.)", "pl");
      legend->AddEntry(acceptanceGraph[3][k], "Pb (Rad. + Acc. Corr.)", "pl");
      legend->SetFillStyle(0);
      legend->SetTextFont(62);
      legend->SetTextSize(0.04);
      legend->SetBorderSize(0);
      legend->Draw();
    }
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/rad-corr_electron";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
