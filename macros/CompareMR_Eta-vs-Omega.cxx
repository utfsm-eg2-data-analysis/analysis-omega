#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "DrawVerticalLine.cxx"

void CompareMR_Eta_vs_Omega(TString kinvarOption = "Pt2") {
  // from fit results and electron numbers, calculate MR

  const Int_t Nbins_Eta = 5;
  const Int_t Nbins_Omega = 4;
  const Int_t Ntargets = 4;
  
  /*** INPUT ***/

  TString kinvarTitle;
  Double_t EdgesKinvar_Eta[Nbins_Eta + 1];
  Double_t EdgesKinvar_Omega[Nbins_Omega + 1];
  if (kinvarOption == "Q2") {
    kinvarTitle = "Q^{2} [GeV^{2}]";
    for (Int_t i = 0; i < Nbins_Eta + 1; i++) EdgesKinvar_Eta[i] = kEdgesQ2_Eta[i];
    for (Int_t i = 0; i < Nbins_Omega + 1; i++) EdgesKinvar_Omega[i] = kEdgesQ2[i];
  } else if (kinvarOption == "Nu") {
    kinvarTitle = "#nu [GeV]";
    for (Int_t i = 0; i < Nbins_Eta + 1; i++) EdgesKinvar_Eta[i] = kEdgesNu_Eta[i];
    for (Int_t i = 0; i < Nbins_Omega + 1; i++) EdgesKinvar_Omega[i] = kEdgesNu[i];
  } else if (kinvarOption == "Z") {
    kinvarTitle = "z_{h}";
    for (Int_t i = 0; i < Nbins_Eta + 1; i++) EdgesKinvar_Eta[i] = kEdgesZ_Eta[i];
    for (Int_t i = 0; i < Nbins_Omega + 1; i++) EdgesKinvar_Omega[i] = kEdgesZ[i];
  } else if (kinvarOption == "Pt2") {
    kinvarTitle = "p_{T}^{2} [GeV^{2}]";
    for (Int_t i = 0; i < Nbins_Eta + 1; i++) EdgesKinvar_Eta[i] = kEdgesPt2_Eta[i];
    for (Int_t i = 0; i < Nbins_Omega + 1; i++) EdgesKinvar_Omega[i] = kEdgesPt2[i];
  }

  TString kinvarOption_Eta;
  TString kinvarOption_Omega;
  if (kinvarOption == "Q2" || kinvarOption == "Nu") {
    kinvarOption_Eta = kinvarOption;
    kinvarOption_Omega = kinvarOption;
  } else if (kinvarOption == "Z" || kinvarOption == "Pt2") {
    kinvarOption_Eta = "e" + kinvarOption;
    kinvarOption_Omega = "w" + kinvarOption;    
  }

  // fix y-axis max range
  Double_t maxMR = 1.4;
  if (kinvarOption == "Pt2") maxMR = 2.5;

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {kGreen + 3, kRed, kBlue, kBlack};

  /*** MAIN ***/

  // eta
  TFile *FitFile_Eta[Ntargets];
  TH1D *etaHist[Ntargets];
  TH1D *electronHist_Eta[Ntargets];
  TH1D *ratioHist_Eta[Ntargets];
  TH1D *MR_Eta[Ntargets];

  Double_t fitEta[Ntargets][Nbins_Eta];
  Double_t fitEtaError[Ntargets][Nbins_Eta];

  // omega
  TFile *InputFile_Omega[Ntargets];
  TH1D *omegaHist[Ntargets];
  TH1D *electronHist_Omega[Ntargets];
  TH1D *ratioHist_Omega[Ntargets];
  TH1D *MR_Omega[Ntargets];

  Double_t intOmega[Ntargets][Nbins_Omega];
  Double_t intOmegaError[Ntargets][Nbins_Omega];
  
  for (Int_t t = 0; t < Ntargets; t++) {

    /*** ETA ***/
    
    FitFile_Eta[t] = new TFile(gProDir + "/macros/eta-bkg-fitting/eta-bkg-fitting_binned_" + targetString[t] + "_" + kinvarOption_Eta + ".root");
    etaHist[t] = new TH1D("etaNumber_" + targetString[t], "", Nbins_Eta, EdgesKinvar_Eta[0], EdgesKinvar_Eta[Nbins_Eta]);
    electronHist_Eta[t] = new TH1D("electronNumber_Eta_" + targetString[t], "", Nbins_Eta, EdgesKinvar_Eta[0], EdgesKinvar_Eta[Nbins_Eta]);
    ratioHist_Eta[t] = new TH1D("ratio_Eta_" + targetString[t], "", Nbins_Eta, EdgesKinvar_Eta[0], EdgesKinvar_Eta[Nbins_Eta]);
    MR_Eta[t] = new TH1D("MR_Eta_" + targetString[t], "", Nbins_Eta, EdgesKinvar_Eta[0], EdgesKinvar_Eta[Nbins_Eta]);
    for (Int_t i = 0; i < Nbins_Eta; i++) {
      RooFitResult* FitResult = FitFile_Eta[t]->Get<RooFitResult>(Form("fit-result_%d", i));
      fitEta[t][i] = ((RooRealVar *) FitResult->floatParsFinal().find("N_{#eta}"))->getValV();
      fitEtaError[t][i] = ((RooRealVar *) FitResult->floatParsFinal().find("N_{#eta}"))->getAsymErrorHi();
      // fill hist
      etaHist[t]->SetBinContent(i + 1, fitEta[t][i]);
      etaHist[t]->SetBinError(i + 1, fitEtaError[t][i]);
      // electron hist
      if (kinvarOption == "Q2") {
	electronHist_Eta[t]->SetBinContent(i + 1, kNElecQ2_Eta[t][i]);
	electronHist_Eta[t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_Eta[t][i]));
      } else if (kinvarOption == "Nu") {
	electronHist_Eta[t]->SetBinContent(i + 1, kNElecNu_Eta[t][i]);
	electronHist_Eta[t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_Eta[t][i]));
      } else if (kinvarOption == "Z" || kinvarOption == "Pt2") {
	electronHist_Eta[t]->SetBinContent(i + 1, kNElec_Eta[t]);
	electronHist_Eta[t]->SetBinError(i + 1, TMath::Sqrt(kNElec_Eta[t]));
      }
    }
    // calculate first ratio (normalize by electrons) and divide solid targets with liquid target
    ratioHist_Eta[t]->Divide(etaHist[t], electronHist_Eta[t]);
    if (t > 0) MR_Eta[t]->Divide(ratioHist_Eta[t], ratioHist_Eta[0]);

    /*** OMEGA ***/

    for (Int_t t = 0; t < Ntargets; t++) {
      InputFile_Omega[t] = new TFile(gProDir + "/macros/evnt-mixing/evnt-mixing_binned_" + targetString[t] + "_" + kinvarOption_Omega + ".root");
      omegaHist[t] = new TH1D("omegaNumber_" + targetString[t], "", Nbins_Omega, EdgesKinvar_Omega[0], EdgesKinvar_Omega[Nbins_Omega]);
      electronHist_Omega[t] = new TH1D("electronNumber_Omega_" + targetString[t], "", Nbins_Omega, EdgesKinvar_Omega[0], EdgesKinvar_Omega[Nbins_Omega]);
      ratioHist_Omega[t] = new TH1D("ratio_Omega_" + targetString[t], "", Nbins_Omega, EdgesKinvar_Omega[0], EdgesKinvar_Omega[Nbins_Omega]);
      MR_Omega[t] = new TH1D("MR_Omega_" + targetString[t], "", Nbins_Omega, EdgesKinvar_Omega[0], EdgesKinvar_Omega[Nbins_Omega]);
      
      for (Int_t i = 0; i < Nbins_Omega; i++) {

	TF1 *Fit = InputFile_Omega[t]->Get<TF1>(Form("model_%d", i));      
	TH1D *Hist = InputFile_Omega[t]->Get<TH1D>(Form("sub_%d", i));      

	Double_t fitMean = Fit->GetParameter(1);
	Double_t fitSigma = Fit->GetParameter(2);
	
	// method 1: include negative entries
	/*
	  intOmega[t][i] = Hist->IntegralAndError(TMath::Floor((fitMean - 3*fitSigma - 0.66)/0.01), TMath::Ceil((fitMean + 3*fitSigma - 0.66)/0.01), intOmegaError[t][i], "");
	*/
	// method 2: remove negative entries
	
	intOmega[t][i] = 0;
	intOmegaError[t][i] = 0;
	for (Int_t s = TMath::Floor((fitMean - 3*fitSigma - 0.66)/0.01); s <= TMath::Ceil((fitMean + 3*fitSigma - 0.66)/0.01); s++) {
	  if (Hist->GetBinContent(s) > 0) intOmega[t][i] += Hist->GetBinContent(s);
	  if (Hist->GetBinContent(s) > 0) intOmegaError[t][i] += Hist->GetBinError(s)*Hist->GetBinError(s);
	}
	intOmegaError[t][i] = TMath::Sqrt(intOmegaError[t][i]);

	// fill hist
	omegaHist[t]->SetBinContent(i + 1, intOmega[t][i]);
	omegaHist[t]->SetBinError(i + 1, intOmegaError[t][i]);
	// electron hist
	if (kinvarOption == "Q2") {
	  electronHist_Omega[t]->SetBinContent(i + 1, kNElecQ2[t][i]);
	  electronHist_Omega[t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2[t][i]));
	} else if (kinvarOption == "Nu") {
	  electronHist_Omega[t]->SetBinContent(i + 1, kNElecNu[t][i]);
	  electronHist_Omega[t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu[t][i]));
	} else if (kinvarOption == "Z" || kinvarOption == "Pt2") {
	  electronHist_Omega[t]->SetBinContent(i + 1, kNElec[t]);
	  electronHist_Omega[t]->SetBinError(i + 1, TMath::Sqrt(kNElec[t]));
	}
      }
      // calculate first ratio (normalize by electrons) and divide solid targets with liquid target
      ratioHist_Omega[t]->Divide(omegaHist[t], electronHist_Omega[t]);
      if (t > 0) MR_Omega[t]->Divide(ratioHist_Omega[t], ratioHist_Omega[0]);
    }
  }
  
  /*** DEFINE GRAPHS ***/

  // define arrays
  Double_t MR_x_Eta[Nbins_Eta];
  Double_t MR_xerr_Eta[Nbins_Eta];
  Double_t MR_y_Eta[Ntargets][Nbins_Eta];
  Double_t MR_yerr_Eta[Ntargets][Nbins_Eta];

  Double_t MR_x_Omega[Nbins_Omega];
  Double_t MR_xerr_Omega[Nbins_Omega];
  Double_t MR_y_Omega[Ntargets][Nbins_Omega];
  Double_t MR_yerr_Omega[Ntargets][Nbins_Omega];
  
  // fill arrays
  // eta
  for (Int_t i = 0; i < Nbins_Eta; i++) {
    MR_x_Eta[i] = (EdgesKinvar_Eta[i] + EdgesKinvar_Eta[i + 1]) / 2.;
    MR_xerr_Eta[i] = (EdgesKinvar_Eta[i + 1] - EdgesKinvar_Eta[i]) / 2;
    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MR_y_Eta[tt][i] = MR_Eta[tt]->GetBinContent(i + 1);
      MR_yerr_Eta[tt][i] = MR_Eta[tt]->GetBinError(i + 1);
    }
  }
  // omega
  for (Int_t i = 0; i < Nbins_Omega; i++) {
    MR_x_Omega[i] = (EdgesKinvar_Omega[i] + EdgesKinvar_Omega[i + 1]) / 2.;
    MR_xerr_Omega[i] = (EdgesKinvar_Omega[i + 1] - EdgesKinvar_Omega[i]) / 2;
    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MR_y_Omega[tt][i] = MR_Omega[tt]->GetBinContent(i + 1);
      MR_yerr_Omega[tt][i] = MR_Omega[tt]->GetBinError(i + 1);
    }
  }
    
  // define eta graph
  TGraphErrors *MRgraph_Eta[Ntargets];
  for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
    MRgraph_Eta[tt] = new TGraphErrors(Nbins_Eta, MR_x_Eta, MR_y_Eta[tt], MR_xerr_Eta, MR_yerr_Eta[tt]);
  }
  // set style
  for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
    MRgraph_Eta[tt]->SetTitle("");
    MRgraph_Eta[tt]->GetXaxis()->SetTitle(kinvarTitle);
    //MRgraph[tt]->GetXaxis()->SetNdivisions(500 + Nbins, kFALSE);
    MRgraph_Eta[tt]->GetXaxis()->SetLimits(EdgesKinvar_Eta[0], EdgesKinvar_Eta[Nbins_Eta]);
    MRgraph_Eta[tt]->GetXaxis()->SetTitleSize(0.04);
    MRgraph_Eta[tt]->GetXaxis()->SetTitleOffset(1.);
    MRgraph_Eta[tt]->GetYaxis()->SetTitle("R_{A}^{h}");
    MRgraph_Eta[tt]->GetYaxis()->SetRangeUser(0., maxMR);
    MRgraph_Eta[tt]->GetYaxis()->SetTitleSize(0.04);
    MRgraph_Eta[tt]->GetYaxis()->SetTitleOffset(1.2);  
    MRgraph_Eta[tt]->SetMarkerStyle(24);
    MRgraph_Eta[tt]->SetMarkerSize(1.5);
    MRgraph_Eta[tt]->SetMarkerColor(targetColor[tt]);
    MRgraph_Eta[tt]->SetLineColor(targetColor[tt]);
    MRgraph_Eta[tt]->SetLineWidth(3);
  }

  // define omega graph
  TGraphErrors *MRgraph_Omega[Ntargets];
  for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
    MRgraph_Omega[tt] = new TGraphErrors(Nbins_Omega, MR_x_Omega, MR_y_Omega[tt], MR_xerr_Omega, MR_yerr_Omega[tt]);
  }
  // set style
  for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
    MRgraph_Omega[tt]->SetTitle("");
    MRgraph_Omega[tt]->GetXaxis()->SetTitle(kinvarTitle);
    //MRgraph[tt]->GetXaxis()->SetNdivisions(500 + Nbins, kFALSE);
    MRgraph_Omega[tt]->GetXaxis()->SetLimits(EdgesKinvar_Omega[0], EdgesKinvar_Omega[Nbins_Omega]);
    MRgraph_Omega[tt]->GetXaxis()->SetTitleSize(0.04);
    MRgraph_Omega[tt]->GetXaxis()->SetTitleOffset(1.);
    MRgraph_Omega[tt]->GetYaxis()->SetTitle("R_{A}^{h}");
    MRgraph_Omega[tt]->GetYaxis()->SetRangeUser(0., maxMR);
    MRgraph_Omega[tt]->GetYaxis()->SetTitleSize(0.04);
    MRgraph_Omega[tt]->GetYaxis()->SetTitleOffset(1.2);  
    MRgraph_Omega[tt]->SetMarkerStyle(21);
    MRgraph_Omega[tt]->SetMarkerSize(1.5);
    MRgraph_Omega[tt]->SetMarkerColor(targetColor[tt]);
    MRgraph_Omega[tt]->SetLineColor(targetColor[tt]);
    MRgraph_Omega[tt]->SetLineWidth(3);
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
  TCanvas *c = new TCanvas("MR-comparison_eta-vs-omega_" + kinvarOption, "MR-comparison_eta-vs-omega_" + kinvarOption, 1920, 640);
  c->Divide(3, 1, 0.001, 0.001);

  Int_t counter = 0;
  for (Int_t tt = 1; tt < Ntargets; tt++) {
    counter++;
    c->cd(counter);
    
    MRgraph_Eta[tt]->Draw("AP");
    MRgraph_Omega[tt]->Draw("P");

    // legend
    TLegend *legend = new TLegend(0.75, 0.75, 0.9, 0.9);  // x1,y1,x2,y2
    legend->AddEntry(MRgraph_Eta[tt], "MR(#eta), " + targetString[tt] + ", No Acc. Corr.", "p");
    legend->AddEntry(MRgraph_Omega[tt], "MR(#omega), " + targetString[tt]  + ", Acc. Corr.", "p");
    legend->SetFillStyle(0);
    legend->SetTextFont(62);
    legend->SetTextSize(0.035);
    legend->SetBorderSize(0);
    legend->Draw();

    c->Update();
  }
  /*
  c->Print(plotFile);  // output file
  */
}
