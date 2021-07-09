#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "DrawVerticalLine.cxx"

void RadCorr_MakeMR_Overlap() {
  // from event-mixing with radiative corrections from HAPRAD
  // and electron numbers with radiative corrections from EXTERNALS,
  // calculate the omega MR

  const Int_t Nbins = 4;
  const Int_t Ntargets = 4;
  const Int_t Nkinvars = 4;

  /*** INPUT ***/

  TString kinvarOption[Nkinvars] = {"Q2", "Nu", "wZ", "wPt2"};
  TString kinvarTitle[Nkinvars] = {"Q^{2} [GeV^{2}]", "#nu [GeV]", "z_{h}", "p_{T}^{2} [GeV^{2}]"};
  Double_t EdgesKinvar[Nkinvars][Nbins + 1];
  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[0][i] = kEdgesQ2[i];
    EdgesKinvar[1][i] = kEdgesNu[i];
    EdgesKinvar[2][i] = kEdgesZ[i];
    EdgesKinvar[3][i] = kEdgesPt2[i];
  }

  Double_t maxMR = 1.5;

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {kGreen + 1, kRed, kBlue, kBlack};

  /*** NOMINAL CASE (NO RAD. CORR.) ***/

  TFile *rootInputFile[Nkinvars][Ntargets];
  TH1D *omegaHist[Nkinvars][Ntargets];
  TH1D *electronHist[Nkinvars][Ntargets];
  TH1D *ratioHist[Nkinvars][Ntargets];
  TH1D *MR[Nkinvars][Ntargets];

  Double_t intOmega[Nkinvars][Ntargets][Nbins];
  Double_t intOmegaError[Nkinvars][Ntargets][Nbins];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      // data
      rootInputFile[k][t] =
          new TFile(gProDir + "/macros/omega/evnt-mixing/evnt-mixing_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      omegaHist[k][t] = new TH1D("omegaNumber_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      electronHist[k][t] = new TH1D("electronNumber_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      ratioHist[k][t] = new TH1D("ratio_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      MR[k][t] = new TH1D("MR_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      for (Int_t i = 0; i < Nbins; i++) {

        TF1 *Fit = rootInputFile[k][t]->Get<TF1>(Form("model_%d", i));
        TH1D *Hist = rootInputFile[k][t]->Get<TH1D>(Form("sub_%d", i));

        Double_t fitMean = Fit->GetParameter(1);
        Double_t fitSigma = Fit->GetParameter(2);

        // method 1: include negative entries
        /*
        intOmega[k][t][i] = Hist->IntegralAndError(TMath::Floor((fitMean - 3*fitSigma - 0.66)/0.01), TMath::Ceil((fitMean + 3*fitSigma -
        0.66)/0.01), intOmegaError[k][t][i], "");
        */
        // method 2: remove negative entries

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
        // fill electron hists from macros/include/Global.h
        if (k == 0) {
          electronHist[k][t]->SetBinContent(i + 1, kNElecQ2[t][i]);
          electronHist[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2[t][i]));
        } else if (k == 1) {
          electronHist[k][t]->SetBinContent(i + 1, kNElecNu[t][i]);
          electronHist[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu[t][i]));
        } else if (k == 2 || k == 3) {
          electronHist[k][t]->SetBinContent(i + 1, kNElec[t]);
          electronHist[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElec[t]));
        }
      }
      // calculate first ratio (normalize by electrons) and divide solid targets with liquid target
      ratioHist[k][t]->Divide(omegaHist[k][t], electronHist[k][t]);
      if (t > 0) MR[k][t]->Divide(ratioHist[k][t], ratioHist[k][0]);
    }
  }

  /*** DEFINE GRAPHS ***/

  // define arrays
  Double_t empty[Nkinvars][Nbins];
  Double_t MR_x[Nkinvars][Nbins];
  Double_t MR_xerr[Nkinvars][Nbins];
  Double_t MR_y[Nkinvars][Ntargets][Nbins];
  Double_t MR_yerr[Nkinvars][Ntargets][Nbins];

  // fill arrays
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      empty[k][i] = 0.;
      MR_x[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      MR_xerr[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / 2;
      for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
        MR_y[k][tt][i] = MR[k][tt]->GetBinContent(i + 1);
        MR_yerr[k][tt][i] = MR[k][tt]->GetBinError(i + 1);
      }
    }
  }

  // define graphs
  TGraphErrors *MRgraph[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MRgraph[k][tt] = new TGraphErrors(Nbins, MR_x[k], MR_y[k][tt], MR_xerr[k], MR_yerr[k][tt]);
    }
    // set style
    MRgraph[k][1]->SetTitle("");

    MRgraph[k][1]->GetXaxis()->SetTitle(kinvarTitle[k]);
    // MRgraph[k][1]->GetXaxis()->SetNdivisions(500 + Nbins, kFALSE);
    MRgraph[k][1]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
    MRgraph[k][1]->GetXaxis()->SetTitleSize(0.04);
    MRgraph[k][1]->GetXaxis()->SetTitleOffset(1.);

    MRgraph[k][1]->GetYaxis()->SetTitle("R_{A}^{#omega}");
    MRgraph[k][1]->GetYaxis()->SetRangeUser(0., maxMR);
    MRgraph[k][1]->GetYaxis()->SetTitleSize(0.04);
    MRgraph[k][1]->GetYaxis()->SetTitleOffset(1.2);

    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MRgraph[k][tt]->SetMarkerStyle(25);
      MRgraph[k][tt]->SetMarkerSize(1.2);
      MRgraph[k][tt]->SetMarkerColor(targetColor[tt]);
      MRgraph[k][tt]->SetLineColor(targetColor[tt]);
      MRgraph[k][tt]->SetLineWidth(3);
    }
  }

  /*** READ RADIATIVE CORRECTED ***/

  TFile *rootInputFile_rc[Nkinvars][Ntargets];
  TH1D *omegaHist_rc[Nkinvars][Ntargets];
  TH1D *electronHist_rc[Nkinvars][Ntargets];
  TH1D *ratioHist_rc[Nkinvars][Ntargets];
  TH1D *MR_rc[Nkinvars][Ntargets];

  Double_t intOmega_rc[Nkinvars][Ntargets][Nbins];
  Double_t intOmegaError_rc[Nkinvars][Ntargets][Nbins];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      // data
      rootInputFile_rc[k][t] = new TFile("evnt-mixing_" + targetString[t] + "_" + kinvarOption[k] + "_rc.root");
      omegaHist_rc[k][t] = new TH1D("omegaNumber_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      electronHist_rc[k][t] = new TH1D("electronNumber_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      ratioHist_rc[k][t] = new TH1D("ratio_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      MR_rc[k][t] = new TH1D("MR_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      for (Int_t i = 0; i < Nbins; i++) {

        TF1 *Fit = rootInputFile_rc[k][t]->Get<TF1>(Form("model_%d", i));
        TH1D *Hist = rootInputFile_rc[k][t]->Get<TH1D>(Form("sub_%d", i));

        Double_t fitMean = Fit->GetParameter(1);
        Double_t fitSigma = Fit->GetParameter(2);

        // method 1: include negative entries
        /*
        intOmega[k][t][i] = Hist->IntegralAndError(TMath::Floor((fitMean - 3*fitSigma - 0.66)/0.01), TMath::Ceil((fitMean + 3*fitSigma -
        0.66)/0.01), intOmegaError[k][t][i], "");
        */
        // method 2: remove negative entries

        intOmega_rc[k][t][i] = 0;
        intOmegaError_rc[k][t][i] = 0;
        for (Int_t s = TMath::Floor((fitMean - 3 * fitSigma - 0.66) / 0.01); s <= TMath::Ceil((fitMean + 3 * fitSigma - 0.66) / 0.01);
             s++) {
          if (Hist->GetBinContent(s) > 0) intOmega_rc[k][t][i] += Hist->GetBinContent(s);
          if (Hist->GetBinContent(s) > 0) intOmegaError_rc[k][t][i] += Hist->GetBinError(s) * Hist->GetBinError(s);
        }
        intOmegaError_rc[k][t][i] = TMath::Sqrt(intOmegaError_rc[k][t][i]);

        // fill hist
        omegaHist_rc[k][t]->SetBinContent(i + 1, intOmega_rc[k][t][i]);
        omegaHist_rc[k][t]->SetBinError(i + 1, intOmegaError_rc[k][t][i]);
        // fill electron hists from macros/include/Global.h
        if (k == 0) {
          electronHist_rc[k][t]->SetBinContent(i + 1, kNElecQ2_rc[t][i]);
          electronHist_rc[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_rc[t][i]));
        } else if (k == 1) {
          electronHist_rc[k][t]->SetBinContent(i + 1, kNElecNu_rc[t][i]);
          electronHist_rc[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_rc[t][i]));
        } else if (k == 2 || k == 3) {
          electronHist_rc[k][t]->SetBinContent(i + 1, kNElec_rc[t]);
          electronHist_rc[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElec_rc[t]));
        }
      }
      // calculate first ratio (normalize by electrons) and divide solid targets with liquid target
      ratioHist_rc[k][t]->Divide(omegaHist_rc[k][t], electronHist_rc[k][t]);
      if (t > 0) MR_rc[k][t]->Divide(ratioHist_rc[k][t], ratioHist_rc[k][0]);
    }
  }

  /*** DEFINE GRAPHS ***/

  // define arrays
  Double_t MR_y_rc[Nkinvars][Ntargets][Nbins];
  Double_t MR_yerr_rc[Nkinvars][Ntargets][Nbins];

  // fill arrays
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
        MR_y_rc[k][tt][i] = MR_rc[k][tt]->GetBinContent(i + 1);
        MR_yerr_rc[k][tt][i] = MR_rc[k][tt]->GetBinError(i + 1);
      }
    }
  }

  // define graphs
  TGraphErrors *MRgraph_rc[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MRgraph_rc[k][tt] = new TGraphErrors(Nbins, MR_x[k], MR_y_rc[k][tt], MR_xerr[k], MR_yerr_rc[k][tt]);
    }
    // set style
    MRgraph_rc[k][1]->SetTitle("");

    MRgraph_rc[k][1]->GetXaxis()->SetTitle(kinvarTitle[k]);
    // MRgraph_rc[k][1]->GetXaxis()->SetNdivisions(500 + Nbins, kFALSE);
    MRgraph_rc[k][1]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
    MRgraph_rc[k][1]->GetXaxis()->SetTitleSize(0.04);
    MRgraph_rc[k][1]->GetXaxis()->SetTitleOffset(1.);

    MRgraph_rc[k][1]->GetYaxis()->SetTitle("R_{A}^{#omega}");
    MRgraph_rc[k][1]->GetYaxis()->SetRangeUser(0., maxMR);
    MRgraph_rc[k][1]->GetYaxis()->SetTitleSize(0.04);
    MRgraph_rc[k][1]->GetYaxis()->SetTitleOffset(1.2);

    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MRgraph_rc[k][tt]->SetMarkerStyle(20);
      MRgraph_rc[k][tt]->SetMarkerSize(1.2);
      MRgraph_rc[k][tt]->SetMarkerColor(targetColor[tt]);
      MRgraph_rc[k][tt]->SetLineColor(targetColor[tt]);
      MRgraph_rc[k][tt]->SetLineWidth(3);
    }
  }

  /*** DRAW ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  // gStyle->SetLineWidth(2);

  gStyle->SetOptStat(0);

  // set margin sizes
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);

  // define canvas
  TCanvas *c = new TCanvas("evnt-mixing_MR-overlap", "evnt-mixing_MR-overlap", 1080, 1080);
  c->Divide(2, 2, 0.001, 0.001);

  Int_t counter = 0;
  for (Int_t k = 0; k < Nkinvars; k++) {
    counter++;
    c->cd(counter);

    MRgraph[k][1]->Draw("AP");  // Carbon
    MRgraph[k][2]->Draw("P");   // Iron
    MRgraph[k][3]->Draw("P");   // Lead

    MRgraph_rc[k][1]->Draw("P");  // Carbon
    MRgraph_rc[k][2]->Draw("P");   // Iron
    MRgraph_rc[k][3]->Draw("P");   // Lead

    // legend
    TLegend *legend = new TLegend(0.75, 0.75, 0.9, 0.9);  // x1,y1,x2,y2
    legend->AddEntry(MRgraph[k][1], "C", "p");
    legend->AddEntry(MRgraph[k][2], "Fe", "p");
    legend->AddEntry(MRgraph[k][3], "Pb", "p");
    legend->AddEntry(MRgraph_rc[k][1], "C, Rad. Corr.", "p");
    legend->AddEntry(MRgraph_rc[k][2], "Fe, Rad. Corr.", "p");
    legend->AddEntry(MRgraph_rc[k][3], "Pb, Rad. Corr.", "p");
    legend->SetFillStyle(0);
    legend->SetTextFont(62);
    legend->SetTextSize(0.03);
    legend->SetBorderSize(0);
    legend->Draw();

    c->Update();
  }
  /*
  c->Print(plotFile);  // output file
  */
}
