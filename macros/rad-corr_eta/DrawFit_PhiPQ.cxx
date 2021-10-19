#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Ntargets = 4;
const Int_t NbinsPhiPQ = 5;

void DrawFit_PhiPQ(TString StoreOption = "") {
  // Draw the acc. corr. PhiPQ distributions of eta mesons and fit them

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};

  TFile *rootInputFile_Data[Ntargets];
  TFile *rootInputFile_MC[Ntargets];
  TFile *rootInputFile_Sim[Ntargets];

  /*** HISTOGRAMS ***/

  Double_t fitEta_Data[Ntargets][NbinsPhiPQ];
  Double_t fitEtaError_Data[Ntargets][NbinsPhiPQ];

  Double_t intEta_MC[Ntargets][NbinsPhiPQ];
  Double_t intEtaError_MC[Ntargets][NbinsPhiPQ];

  Double_t fitEta_Sim[Ntargets][NbinsPhiPQ];
  Double_t fitEtaError_Sim[Ntargets][NbinsPhiPQ];

  TString titleAxis = "#phi_{PQ} [deg]";
  TString histProperties = Form("(%i, -180, 180)", NbinsPhiPQ);

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
    rootInputFile_Data[t] = new TFile(gProDir + "/gfx/rad-corr_eta/bkg-fitting_" + targetString[t] + "_nPhiPQ_data.root");
    rootInputFile_MC[t] = new TFile(gProDir + "/gfx/rad-corr_eta/parent-id_" + targetString[t] + "_nPhiPQ_mc.root");
    rootInputFile_Sim[t] = new TFile(gProDir + "/gfx/rad-corr_eta/bkg-fitting_" + targetString[t] + "_nPhiPQ_sim.root");

    // define histograms
    dataHist[t] = new TH1D("hist_Data_" + targetString[t], "", NbinsPhiPQ, -180, 180);
    mcHist[t] = new TH1D("hist_MC_" + targetString[t], "", NbinsPhiPQ, -180, 180);
    simHist[t] = new TH1D("hist_Sim_" + targetString[t], "", NbinsPhiPQ, -180, 180);

    // loop over bins
    for (Int_t i = 0; i < NbinsPhiPQ; i++) {

      /*** DATA ***/

      RooFitResult *FitResult_Data = (RooFitResult *)rootInputFile_Data[t]->Get(Form("fit-result_%i", i));
      fitEta_Data[t][i] = ((RooRealVar *)FitResult_Data->floatParsFinal().find("N_{#eta}"))->getValV();
      fitEtaError_Data[t][i] = ((RooRealVar *)FitResult_Data->floatParsFinal().find("N_{#eta}"))->getAsymErrorHi();

      // fill hists
      dataHist[t]->SetBinContent(i + 1, fitEta_Data[t][i]);
      dataHist[t]->SetBinError(i + 1, fitEtaError_Data[t][i]);

      /*** MC ***/

      // get eta numbers
      TH1D *auxHist_MC = (TH1D *)rootInputFile_MC[t]->Get(Form("hist_%i", i));
      intEta_MC[t][i] = auxHist_MC->GetEntries();
      intEtaError_MC[t][i] = TMath::Sqrt(intEta_MC[t][i]);

      // fill hists
      mcHist[t]->SetBinContent(i + 1, intEta_MC[t][i]);
      mcHist[t]->SetBinError(i + 1, intEtaError_MC[t][i]);

      /*** SIM. REC. ***/

      RooFitResult *FitResult_Sim = (RooFitResult *)rootInputFile_Sim[t]->Get(Form("fit-result_%i", i));
      fitEta_Sim[t][i] = ((RooRealVar *)FitResult_Sim->floatParsFinal().find("N_{#eta}"))->getValV();
      fitEtaError_Sim[t][i] = ((RooRealVar *)FitResult_Sim->floatParsFinal().find("N_{#eta}"))->getAsymErrorHi();

      // fill hists
      simHist[t]->SetBinContent(i + 1, fitEta_Sim[t][i]);
      simHist[t]->SetBinError(i + 1, fitEtaError_Sim[t][i]);
    }

    /*** ACCEPTANCE ***/

    // acceptance histogram
    accHist[t] = new TH1D("acc_" + targetString[t], "", NbinsPhiPQ, -180., 180.);
    accHist[t]->Divide(simHist[t], mcHist[t], 1, 1, "B");

    // corrected data histogram
    corrHist[t] = new TH1D("corr_" + targetString[t], "", NbinsPhiPQ, -180., 180.);
    corrHist[t]->Divide(dataHist[t], accHist[t], 1, 1);

    // set style
    corrHist[t]->SetTitle("");
    corrHist[t]->SetMarkerColor(myBlack);
    corrHist[t]->SetLineColor(myBlack);
    corrHist[t]->SetLineWidth(5);
    corrHist[t]->SetMarkerStyle(20);
    corrHist[t]->SetMarkerSize(2);

    corrHist[t]->GetYaxis()->SetRangeUser(0., 2 * corrHist[t]->GetMaximum());

    corrHist[t]->GetYaxis()->SetTitle("N_{#eta}");
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
  const Int_t Ny = 2;

  TString CanvasName = "fit-PhiPQ_acc-corr-eta";
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
    pave[t]->AddText("Integrated " + targetString[t] + " data (Bkg. Sub. + Acc. Corr)");
    pave[t]->AddText(Chi2String);
    pave[t]->AddText(A_String);
    pave[t]->AddText(Ac_String);
    pave[t]->AddText(Acc_String);
    pave[t]->SetBorderSize(0);
    pave[t]->SetTextAlign(12);
    pave[t]->SetFillStyle(0);
    pave[t]->Draw();

    std::cout << std::endl;
    std::cout << "Integrated " + targetString[t] + " data (Bkg. Sub. + Acc. Corr)" << std::endl;
    std::cout << Chi2String << std::endl;
    std::cout << A_String << std::endl;
    std::cout << Ac_String << std::endl;
    std::cout << Acc_String << std::endl;

    /*** OUTPUT PARAMS. ***/

    A_String = Form("export PARAM_A=%.3f", theFit[t]->GetParameter(0));
    Ac_String = Form("export PARAM_AC=%.3f", theFit[t]->GetParameter(1));
    Acc_String = Form("export PARAM_ACC=%.3f", theFit[t]->GetParameter(2));

    TString OutFileName = gProDir + "/gfx/rad-corr_eta/fit-results_eta_" + targetString[t] + ".sh";
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
    TString OutputDir = gProDir + "/gfx/rad-corr_eta";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
