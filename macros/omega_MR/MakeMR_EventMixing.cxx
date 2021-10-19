#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#include "OmegaElectronNumbers.hxx"

const Int_t Nbins = 4;
const Int_t Ntargets = 4;
const Int_t Nkinvars = 4;

void MakeMR_EventMixing(TString StoreOption = "") {
  // Calculate and draw MR after background subtraction via event mixing and obtained electron numbers

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

  // fix y-axis max range
  Double_t maxMR = 1.5;

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  TFile *HistFile[Nkinvars][Ntargets];
  TH1D *omegaHist[Nkinvars][Ntargets];
  TH1D *electronHist[Nkinvars][Ntargets];
  TH1D *ratioHist[Nkinvars][Ntargets];
  TH1D *MR[Nkinvars][Ntargets];

  Double_t intOmega[Nkinvars][Ntargets][Nbins];
  Double_t intOmegaError[Nkinvars][Ntargets][Nbins];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      // data
      HistFile[k][t] = new TFile(gProDir + "/gfx/omega_evnt-mixing/evnt-mixing_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      omegaHist[k][t] = new TH1D("omegaNumber_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      electronHist[k][t] = new TH1D("electronNumber_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      ratioHist[k][t] = new TH1D("ratio_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      MR[k][t] = new TH1D("MR_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      for (Int_t i = 0; i < Nbins; i++) {

        TF1 *Fit = (TF1 *)HistFile[k][t]->Get(Form("model_%d", i));
        TH1D *Hist = (TH1D *)HistFile[k][t]->Get(Form("sub_%d", i));

        Double_t fitMean = Fit->GetParameter(1);
        Double_t fitSigma = Fit->GetParameter(2);

        // remove negative entries
        intOmega[k][t][i] = 0;
        intOmegaError[k][t][i] = 0;
        for (Int_t s = TMath::Floor((fitMean - 3 * fitSigma - 0.66) / 0.01); s <= TMath::Ceil((fitMean + 3 * fitSigma - 0.66) / 0.01);
             s++) {
          if (Hist->GetBinContent(s) > 0) intOmega[k][t][i] += Hist->GetBinContent(s);
          if (Hist->GetBinContent(s) > 0) intOmegaError[k][t][i] += Hist->GetBinError(s) * Hist->GetBinError(s);
        }
        intOmegaError[k][t][i] = TMath::Sqrt(intOmegaError[k][t][i]);

        // fill hist
        omegaHist[k][t]->SetBinContent(i + 1, intOmega[k][t][i]);
        omegaHist[k][t]->SetBinError(i + 1, intOmegaError[k][t][i]);
        // electron hist
        if (k == 0) {
          electronHist[k][t]->SetBinContent(i + 1, kNElecQ2_Omega[t][i]);
          electronHist[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_Omega[t][i]));
        } else if (k == 1) {
          electronHist[k][t]->SetBinContent(i + 1, kNElecNu_Omega[t][i]);
          electronHist[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_Omega[t][i]));
        } else if (k == 2 || k == 3) {
          electronHist[k][t]->SetBinContent(i + 1, kNElec_Omega[t]);
          electronHist[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElec_Omega[t]));
        }
      }
      // calculate first ratio (normalize by electrons) and divide solid targets with liquid target
      ratioHist[k][t]->Divide(omegaHist[k][t], electronHist[k][t]);
      if (t > 0) MR[k][t]->Divide(ratioHist[k][t], ratioHist[k][0]);
    }
  }

  /*** GRAPHS ***/

  // define arrays
  Double_t MR_x[Nkinvars][Nbins];
  Double_t MR_xerr[Nkinvars][Nbins];
  Double_t MR_y[Nkinvars][Ntargets][Nbins];
  Double_t MR_yerr[Nkinvars][Ntargets][Nbins];

  // fill arrays
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      MR_x[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      MR_xerr[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / 2;
      // loop over solid targets only
      for (Int_t tt = 1; tt < Ntargets; tt++) {
        MR_y[k][tt][i] = MR[k][tt]->GetBinContent(i + 1);
        MR_yerr[k][tt][i] = MR[k][tt]->GetBinError(i + 1);
      }
    }
  }

  // set graphs
  TGraphErrors *MRgraph[Nkinvars][Ntargets];
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      MRgraph[k][t] = new TGraphErrors(Nbins, MR_x[k], MR_y[k][t], MR_xerr[k], MR_yerr[k][t]);
    }
  }

  // set style
  for (Int_t k = 0; k < Nkinvars; k++) {
    MRgraph[k][1]->SetTitle("");

    MRgraph[k][1]->GetYaxis()->SetTitle("R_{A}^{#omega}");
    MRgraph[k][1]->GetYaxis()->SetRangeUser(0., maxMR);
    MRgraph[k][1]->GetYaxis()->SetTitleSize(0.06);

    MRgraph[k][1]->GetXaxis()->SetTitle(kinvarTitle[k]);
    MRgraph[k][1]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
    MRgraph[k][1]->GetXaxis()->SetTitleSize(0.06);

    for (Int_t t = 0; t < Ntargets; t++) {
      MRgraph[k][t]->SetMarkerStyle(21);
      MRgraph[k][t]->SetMarkerSize(2);
      MRgraph[k][t]->SetMarkerColor(targetColor[t]);
      MRgraph[k][t]->SetLineColor(targetColor[t]);
      MRgraph[k][t]->SetLineWidth(5);
    }
  }

  /*** DRAW ***/

  SetMyStyle();

  // define canvas
  TString CanvasName = "omega-MR_evnt-mixing";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 2160);
  c->Divide(2, 2, 0.001, 0.001);  // nx, ny, margins

  Int_t counter = 0;
  for (Int_t k = 0; k < Nkinvars; k++) {
    counter++;
    c->cd(counter);

    MRgraph[k][1]->Draw("AP");  // Carbon
    MRgraph[k][2]->Draw("P");   // Iron
    MRgraph[k][3]->Draw("P");   // Lead

    // legend
    if (k == 1) {
      TLegend *legend = new TLegend(0.2, 0.75, 0.45, 0.9);  // x1,y1,x2,y2
      legend->AddEntry(MRgraph[k][1], "C (No Acc. Corr.)", "lp");
      legend->AddEntry(MRgraph[k][2], "Fe (No Acc. Corr.)", "lp");
      legend->AddEntry(MRgraph[k][3], "Pb (No Acc. Corr.)", "lp");
      legend->SetFillStyle(0);
      legend->SetTextFont(62);
      legend->SetTextSize(0.035);
      legend->SetBorderSize(0);
      legend->Draw();
    }

    c->Update();
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_MR";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
