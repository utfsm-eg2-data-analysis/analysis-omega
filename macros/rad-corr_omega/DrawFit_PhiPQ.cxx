#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Ntargets = 2;  // liquid and solid
const Int_t Nbins = 4;

void DrawFit_PhiPQ(TString StoreOption = "") {
  // draw the acc. corr. PhiPQ distributions and fit them

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  TString targetString[Ntargets] = {"D", "A"};
  TString targetDescription[Ntargets] = {"liquid target", "solid targets"};

  TFile *rootInputFile_Data[Ntargets];
  TFile *rootInputFile_MC[Ntargets];
  TFile *rootInputFile_Sim[Ntargets];

  /*** HISTOGRAMS ***/

  Double_t intOmega_Data[Ntargets][Nbins];
  Double_t intOmegaError_Data[Ntargets][Nbins];

  Double_t intOmega_MC[Ntargets][Nbins];
  Double_t intOmegaError_MC[Ntargets][Nbins];

  Double_t intOmega_Sim[Ntargets][Nbins];
  Double_t intOmegaError_Sim[Ntargets][Nbins];

  TString titleAxis = "#phi_{PQ} [deg]";
  TString histProperties = "(4, -180, 180)";

  // define histograms
  TH1D *dataHist[Ntargets];
  TH1D *mcHist[Ntargets];
  TH1D *simHist[Ntargets];
  TH1D *accHist[Ntargets];
  TH1D *corrHist[Ntargets];

  // define fit function
  TF1 *theFit[Ntargets];

  // loop over targets
  for (Int_t t = 0; t < Ntargets; t++) {

    // open files
    rootInputFile_Data[t] = new TFile(gProDir + "/gfx/rad-corr_omega/evnt-mixing_" + targetString[t] + "_wPhiPQ_data.root");
    rootInputFile_MC[t] = new TFile(gProDir + "/gfx/rad-corr_omega/parent-id_" + targetString[t] + "_wPhiPQ_mc.root");
    rootInputFile_Sim[t] = new TFile(gProDir + "/gfx/rad-corr_omega/evnt-mixing_" + targetString[t] + "_wPhiPQ_sim.root");

    // define histograms
    dataHist[t] = new TH1D("hist_Data_" + targetString[t], "", Nbins, -180, 180);
    mcHist[t] = new TH1D("hist_MC_" + targetString[t], "", Nbins, -180, 180);
    simHist[t] = new TH1D("hist_Sim_" + targetString[t], "", Nbins, -180, 180);

    // loop over bins
    for (Int_t i = 0; i < Nbins; i++) {

      /*** DATA ***/

      // get omega numbers
      TF1 *auxFit_Data = (TF1 *)rootInputFile_Data[t]->Get(Form("model_%i", i));
      TH1D *auxHist_Data = (TH1D *)rootInputFile_Data[t]->Get(Form("sub_%i", i));

      Double_t fitMean_Data = auxFit_Data->GetParameter(1);
      Double_t fitSigma_Data = auxFit_Data->GetParameter(2);

      // remove negative entries
      intOmega_Data[t][i] = 0;
      intOmegaError_Data[t][i] = 0;
      for (Int_t s = TMath::Floor((fitMean_Data - 3 * fitSigma_Data - 0.66) / 0.01);
           s <= TMath::Ceil((fitMean_Data + 3 * fitSigma_Data - 0.66) / 0.01); s++) {
        if (auxHist_Data->GetBinContent(s) > 0) intOmega_Data[t][i] += auxHist_Data->GetBinContent(s);
        if (auxHist_Data->GetBinContent(s) > 0) intOmegaError_Data[t][i] += auxHist_Data->GetBinError(s) * auxHist_Data->GetBinError(s);
      }
      intOmegaError_Data[t][i] = TMath::Sqrt(intOmegaError_Data[t][i]);

      // fill hists
      dataHist[t]->SetBinContent(i + 1, intOmega_Data[t][i]);
      dataHist[t]->SetBinError(i + 1, intOmegaError_Data[t][i]);

      /*** MC ***/

      // get omega numbers
      TH1D *auxHist_MC = (TH1D *)rootInputFile_MC[t]->Get(Form("hist_%i", i));
      intOmega_MC[t][i] = auxHist_MC->GetEntries();
      intOmegaError_MC[t][i] = TMath::Sqrt(intOmega_MC[t][i]);

      // fill hists
      mcHist[t]->SetBinContent(i + 1, intOmega_MC[t][i]);
      mcHist[t]->SetBinError(i + 1, intOmegaError_MC[t][i]);

      /*** SIM. REC. ***/

      // get omega numbers
      TF1 *auxFit_Sim = (TF1 *)rootInputFile_Sim[t]->Get(Form("model_%i", i));
      TH1D *auxHist_Sim = (TH1D *)rootInputFile_Sim[t]->Get(Form("sub_%i", i));

      Double_t fitMean_Sim = auxFit_Sim->GetParameter(1);
      Double_t fitSigma_Sim = auxFit_Sim->GetParameter(2);

      // remove negative entries
      intOmega_Sim[t][i] = 0;
      intOmegaError_Sim[t][i] = 0;
      for (Int_t s = TMath::Floor((fitMean_Sim - 3 * fitSigma_Sim - 0.66) / 0.01);
           s <= TMath::Ceil((fitMean_Sim + 3 * fitSigma_Sim - 0.66) / 0.01); s++) {
        if (auxHist_Sim->GetBinContent(s) > 0) intOmega_Sim[t][i] += auxHist_Sim->GetBinContent(s);
        if (auxHist_Sim->GetBinContent(s) > 0) intOmegaError_Sim[t][i] += auxHist_Sim->GetBinError(s) * auxHist_Sim->GetBinError(s);
      }
      intOmegaError_Sim[t][i] = TMath::Sqrt(intOmegaError_Sim[t][i]);

      // fill hists
      simHist[t]->SetBinContent(i + 1, intOmega_Sim[t][i]);
      simHist[t]->SetBinError(i + 1, intOmegaError_Sim[t][i]);
    }

    /*** ACCEPTANCE ***/

    // acceptance histogram
    accHist[t] = new TH1D("acc_" + targetString[t], "", Nbins, -180., 180.);
    accHist[t]->Divide(simHist[t], mcHist[t], 1, 1, "B");

    // corrected data histogram
    corrHist[t] = new TH1D("corr_" + targetString[t], "", Nbins, -180., 180.);
    corrHist[t]->Divide(dataHist[t], accHist[t], 1, 1);

    // set style
    corrHist[t]->SetTitle("");
    corrHist[t]->SetMarkerColor(myBlack);
    corrHist[t]->SetLineColor(myBlack);
    corrHist[t]->SetLineWidth(5);
    corrHist[t]->SetMarkerStyle(20);
    corrHist[t]->SetMarkerSize(2);

    corrHist[t]->GetYaxis()->SetRangeUser(0., 2 * corrHist[t]->GetMaximum());

    corrHist[t]->GetYaxis()->SetTitle("N_{#omega}");
    corrHist[t]->GetYaxis()->SetTitleSize(0.06);
    corrHist[t]->GetYaxis()->SetTitleOffset(1.2);
    corrHist[t]->GetYaxis()->SetMaxDigits(3);

    corrHist[t]->GetXaxis()->SetTitle(titleAxis);
    corrHist[t]->GetXaxis()->SetTitleSize(0.06);

    /*** FIT ***/

    theFit[t] = new TF1("fit_" + targetString[t], "[0]+[1]*TMath::Cos(x*TMath::DegToRad())+[2]*TMath::Cos(2*x*TMath::DegToRad())");
    theFit[t]->SetLineColor(myRed);
    theFit[t]->SetLineWidth(3);
    corrHist[t]->Fit(theFit[t], "Q");
  }

  /*** DRAW ***/

  SetMyStyle();

  const Int_t Nx = 2;
  const Int_t Ny = 1;

  TString CanvasName = "fit-PhiPQ_acc-corr-omega";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, Nx * 1080, Ny * 1080);
  c->Divide(Nx, Ny, 0.001, 0.001);  // nx, ny, margins

  gStyle->SetOptFit(0);

  // define Pad to print obtained parameters from fit
  TPaveText *pave[Ntargets];

  for (Int_t t = 0; t < Ntargets; t++) {
    c->cd(t + 1);
    corrHist[t]->Draw("E");

    // pave
    TString Chi2String = Form("#chi^{2}/ndf = %.4f", theFit[t]->GetChisquare() / (Double_t)theFit[t]->GetNDF());
    TString A_String = Form("A = %.3f #pm %.3f", theFit[t]->GetParameter(0), theFit[t]->GetParError(0));
    TString Ac_String = Form("A_{c} = %.3f #pm %.6f", theFit[t]->GetParameter(1), theFit[t]->GetParError(1));
    TString Acc_String = Form("A_{cc} = %.3f #pm %.6f", theFit[t]->GetParameter(2), theFit[t]->GetParError(2));

    pave[t] = new TPaveText(0.15, 0.62, 0.95, 0.92, "NDC NB");  // x1y1x2y2, NB: no border
    pave[t]->SetTextSize(0.03);
    pave[t]->AddText("Integrated " + targetDescription[t] + " (Bkg. Sub. + Acc. Corr)");
    pave[t]->AddText(Chi2String);
    pave[t]->AddText(A_String);
    pave[t]->AddText(Ac_String);
    pave[t]->AddText(Acc_String);
    pave[t]->SetBorderSize(0);
    pave[t]->SetTextAlign(12);
    pave[t]->SetFillStyle(0);
    pave[t]->Draw();

    std::cout << std::endl;
    std::cout << "Integrated " + targetDescription[t] + " (Bkg. Sub. + Acc. Corr)" << std::endl;
    std::cout << Chi2String << std::endl;
    std::cout << A_String << std::endl;
    std::cout << Ac_String << std::endl;
    std::cout << Acc_String << std::endl;

    /*** OUTPUT PARAMS. ***/

    A_String = Form("export PARAM_A=%.3f", theFit[t]->GetParameter(0));
    Ac_String = Form("export PARAM_AC=%.3f", theFit[t]->GetParameter(1));
    Acc_String = Form("export PARAM_ACC=%.3f", theFit[t]->GetParameter(2));

    TString OutFileName = gProDir + "/gfx/rad-corr_omega/fit-results_omega_" + targetString[t] + ".sh";
    std::ofstream OutFile(OutFileName, std::ios::out);

    OutFile << "#!/bin/bash" << std::endl;
    OutFile << std::endl;
    OutFile << A_String << std::endl;
    OutFile << Ac_String << std::endl;
    OutFile << Acc_String << std::endl;
    OutFile << std::endl;

    OutFile.close();

    std::cout << "The following file has been created: " << OutFileName << std::endl;
  }

  /*** OUTPUT CANVAS ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/rad-corr_omega";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
