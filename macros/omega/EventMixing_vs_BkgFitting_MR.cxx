#ifndef GLOBAL_H
#include "Global.h"
#endif

void EventMixing_vs_BkgFitting_MR() {
  // from fit results and electron numbers, calculate MR

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

  Double_t plotMin = 0.66;
  Double_t plotMax = 0.90;
  Double_t maxMR = 1.6;

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {kGreen + 3, kRed, kBlue, kBlack};

  /*** MAIN ***/

  // evnt mixing
  TFile *rootInputFile[Nkinvars][Ntargets];
  TH1D *omegaHist[Nkinvars][Ntargets];
  TH1D *electronHist[Nkinvars][Ntargets];
  TH1D *ratioHist[Nkinvars][Ntargets];
  TH1D *MR[Nkinvars][Ntargets];

  Double_t intOmega[Nkinvars][Ntargets][Nbins];
  Double_t intOmegaError[Nkinvars][Ntargets][Nbins];

  // bkg fitting
  TFile *FitFile[Nkinvars][Ntargets];
  TH1D *omegaHist_fit[Nkinvars][Ntargets];
  TH1D *ratioHist_fit[Nkinvars][Ntargets];
  TH1D *MR_fit[Nkinvars][Ntargets];

  Double_t fitOmega[Nkinvars][Ntargets][Nbins];
  Double_t fitOmegaError[Nkinvars][Ntargets][Nbins];
  
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {

      /*** EVNT MIXING ***/
      
      // data
      rootInputFile[k][t] = new TFile(gProDir + "/macros/evnt-mixing/evnt-mixing_binned_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      omegaHist[k][t] = new TH1D("omegaNumber_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      electronHist[k][t] = new TH1D("electronNumber_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      ratioHist[k][t] = new TH1D("ratio_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      MR[k][t] = new TH1D("MR_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      for (Int_t i = 0; i < Nbins; i++) {

	TF1 *Fit = rootInputFile[k][t]->Get<TF1>(Form("model_%d", i));      
	TH1D *Hist = rootInputFile[k][t]->Get<TH1D>(Form("sub_%d", i));      

	Double_t fitMean = Fit->GetParameter(1);
	Double_t fitSigma = Fit->GetParameter(2);
	
	// remove negative entries
	intOmega[k][t][i] = 0;
	intOmegaError[k][t][i] = 0;
	for (Int_t s = TMath::Floor((fitMean - 3*fitSigma - 0.66)/0.01); s <= TMath::Ceil((fitMean + 3*fitSigma - 0.66)/0.01); s++) {
	  if (Hist->GetBinContent(s) > 0) intOmega[k][t][i] += Hist->GetBinContent(s);
	  if (Hist->GetBinContent(s) > 0) intOmegaError[k][t][i] += Hist->GetBinError(s)*Hist->GetBinError(s);
	}
	intOmegaError[k][t][i] = TMath::Sqrt(intOmegaError[k][t][i]);

	// fill hist
	omegaHist[k][t]->SetBinContent(i + 1, intOmega[k][t][i]);
	omegaHist[k][t]->SetBinError(i + 1, intOmegaError[k][t][i]);
	// electron hist
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

      /*** BKG FITTING ***/

      // data
      FitFile[k][t] = new TFile(gProDir + "/macros/bkg-fitting/bkg-fitting_binned_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      omegaHist_fit[k][t] = new TH1D("omegaNumber_fit_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      ratioHist_fit[k][t] = new TH1D("ratio_fit_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      MR_fit[k][t] = new TH1D("MR_fit_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      
      for (Int_t i = 0; i < Nbins; i++) {
	RooFitResult* FitResult = FitFile[k][t]->Get<RooFitResult>(Form("fit-result_%d_%d", i, k));
	fitOmega[k][t][i] = ((RooRealVar *) FitResult->floatParsFinal().find("N_{#omega}"))->getValV();
	fitOmegaError[k][t][i] = ((RooRealVar *) FitResult->floatParsFinal().find("N_{#omega}"))->getAsymErrorHi();
	// fill hist
	omegaHist_fit[k][t]->SetBinContent(i + 1, fitOmega[k][t][i]);
	omegaHist_fit[k][t]->SetBinError(i + 1, fitOmegaError[k][t][i]);
      }
      
      // calculate first ratio (normalize by electrons) and divide solid targets with liquid target
      ratioHist_fit[k][t]->Divide(omegaHist_fit[k][t], electronHist[k][t]);
      if (t > 0) MR_fit[k][t]->Divide(ratioHist_fit[k][t], ratioHist_fit[k][0]);
    }
  }
  
  /*** DEFINE GRAPHS ***/

  // define arrays
  Double_t empty[Nkinvars][Nbins];
  Double_t MR_x[Nkinvars][Nbins];
  Double_t MR_xerr[Nkinvars][Nbins];
  Double_t MR_y[Nkinvars][Ntargets][Nbins];
  Double_t MR_yerr[Nkinvars][Ntargets][Nbins];
  Double_t MR_fit_y[Nkinvars][Ntargets][Nbins];
  Double_t MR_fit_yerr[Nkinvars][Ntargets][Nbins];

  // fill arrays
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      empty[k][i] = 0.;
      MR_x[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      MR_xerr[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / 2;
      for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
	MR_y[k][tt][i] = MR[k][tt]->GetBinContent(i + 1);
	MR_yerr[k][tt][i] = MR[k][tt]->GetBinError(i + 1);
	MR_fit_y[k][tt][i] = MR_fit[k][tt]->GetBinContent(i + 1);
	MR_fit_yerr[k][tt][i] = MR_fit[k][tt]->GetBinError(i + 1);
      }
    }
  }
    
  // define graphs
  TGraphErrors *MRgraph[Nkinvars][Ntargets];
  TGraphErrors *MRgraph_fit[Nkinvars][Ntargets];
  
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MRgraph[k][tt] = new TGraphErrors(Nbins, MR_x[k], MR_y[k][tt], MR_xerr[k], MR_yerr[k][tt]);
      MRgraph_fit[k][tt] = new TGraphErrors(Nbins, MR_x[k], MR_fit_y[k][tt], MR_xerr[k], MR_fit_yerr[k][tt]);
    }
    // set style
    MRgraph[k][1]->SetTitle("");

    MRgraph[k][1]->GetXaxis()->SetTitle(kinvarTitle[k]);
    //MRgraph[k][1]->GetXaxis()->SetNdivisions(500 + Nbins, kFALSE);
    MRgraph[k][1]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
    MRgraph[k][1]->GetXaxis()->SetTitleSize(0.04);
    MRgraph[k][1]->GetXaxis()->SetTitleOffset(1.);

    MRgraph[k][1]->GetYaxis()->SetTitle("R_{A}^{#omega}");
    MRgraph[k][1]->GetYaxis()->SetRangeUser(0., maxMR);
    MRgraph[k][1]->GetYaxis()->SetTitleSize(0.04);
    MRgraph[k][1]->GetYaxis()->SetTitleOffset(1.2);
  
    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MRgraph[k][tt]->SetMarkerStyle(21);
      MRgraph[k][tt]->SetMarkerSize(1.5);
      MRgraph[k][tt]->SetMarkerColor(targetColor[tt]);
      MRgraph[k][tt]->SetLineColor(targetColor[tt]);
      MRgraph[k][tt]->SetLineWidth(3);
      
      MRgraph_fit[k][tt]->SetMarkerStyle(24);
      MRgraph_fit[k][tt]->SetMarkerSize(1.5);
      MRgraph_fit[k][tt]->SetMarkerColor(targetColor[tt]);
      MRgraph_fit[k][tt]->SetLineColor(targetColor[tt]);
      MRgraph_fit[k][tt]->SetLineWidth(3);
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
  TCanvas *c = new TCanvas("evnt-mixing_vs_bkg-fitting_MR", "evnt-mixing_vs_bkg-fitting_MR", 1080, 1080);
  c->Divide(2, 2, 0.001, 0.001);

  Int_t counter = 0;
  for (Int_t k = 0; k < Nkinvars; k++) {
    counter++;
    c->cd(counter);
    
    MRgraph[k][1]->Draw("AP");  // Carbon
    MRgraph[k][2]->Draw("P");   // Iron
    MRgraph[k][3]->Draw("P");   // Lead

    MRgraph_fit[k][1]->Draw("P");  // Carbon
    MRgraph_fit[k][2]->Draw("P");   // Iron
    MRgraph_fit[k][3]->Draw("P");   // Lead

    // legend
    TLegend *legend = new TLegend(0.75, 0.7, 0.9, 0.9);  // x1,y1,x2,y2
    legend->AddEntry(MRgraph[k][1], "C (Event Mixing)", "p");
    legend->AddEntry(MRgraph[k][2], "Fe (Event Mixing)", "p");
    legend->AddEntry(MRgraph[k][3], "Pb (Event Mixing)", "p");
    legend->AddEntry(MRgraph_fit[k][1], "C (Bkg. Fitting)", "p");
    legend->AddEntry(MRgraph_fit[k][2], "Fe (Bkg. Fitting)", "p");
    legend->AddEntry(MRgraph_fit[k][3], "Pb (Bkg. Fitting)", "p");
    legend->SetFillStyle(0);
    legend->SetTextFont(62);
    legend->SetTextSize(0.025);
    legend->SetBorderSize(0);
    legend->Draw();

    c->Update();
  }
  /*
  c->Print(plotFile);  // output file
  */
}
