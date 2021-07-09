#ifndef GLOBAL_H
#include "Global.h"
#endif

void EventMixing_MakeMRvsMRACC(Int_t onlyMRACC = 0) {
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

  // data
  TFile *rootInputFile[Nkinvars][Ntargets];
  
  TH1D *omegaHist[Nkinvars][Ntargets];
  TH1D *electronHist[Nkinvars][Ntargets];
  TH1D *ratioHist[Nkinvars][Ntargets];
  
  Double_t intOmega[Nkinvars][Ntargets][Nbins];
  Double_t intOmegaError[Nkinvars][Ntargets][Nbins];

  // acceptance
  TFile *rootInputFile_Sim[Nkinvars][Ntargets];
  TFile *rootInputFile_MC[Nkinvars][Ntargets];

  Double_t intOmega_Sim[Nkinvars][Ntargets][Nbins];
  Double_t intOmegaError_Sim[Nkinvars][Ntargets][Nbins];

  Double_t intOmega_MC[Nkinvars][Ntargets][Nbins];
  Double_t intOmegaError_MC[Nkinvars][Ntargets][Nbins];

  TH1D *omegaHist_Sim[Nkinvars][Ntargets];
  TH1D *omegaHist_MC[Nkinvars][Ntargets];

  TH1D *electronHist_Sim[Nkinvars][Ntargets];
  TH1D *electronHist_MC[Nkinvars][Ntargets];
  
  TH1D *electronAcceptanceHist[Nkinvars][Ntargets];
  TH1D *omegaAcceptanceHist[Nkinvars][Ntargets];

  TH1D *targetAcceptanceHist[Nkinvars][Ntargets];
  TH1D *factorAcceptanceHist[Nkinvars][Ntargets]; // only solid targets

  
  // the finalists
  TH1D *MR[Nkinvars][Ntargets];
  TH1D *MRACC[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      
      /*** DATA ***/
      
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
      MR[k][t]->Divide(ratioHist[k][t], ratioHist[k][0]);

      /*** ACCEPTANCE ***/
      
      // open files
      rootInputFile_MC[k][t] = new TFile(gProDir + "/macros/evnt-mixing/evnt-mixing_binned_" + targetString[t] + "_mc_" + kinvarOption[k] + ".root");
      rootInputFile_Sim[k][t] = new TFile(gProDir + "/macros/evnt-mixing/evnt-mixing_binned_" + targetString[t] + "_sim_" + kinvarOption[k] + ".root");

      omegaHist_Sim[k][t] = new TH1D("omegaNumber_Sim_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      omegaHist_MC[k][t] = new TH1D("omegaNumber_MC_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      omegaAcceptanceHist[k][t] = new TH1D("omegaAcceptance_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      electronHist_Sim[k][t] = new TH1D("electronNumber_Sim_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      electronHist_MC[k][t] = new TH1D("electronNumber_MC_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      electronAcceptanceHist[k][t] = new TH1D("electronAcceptance_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      targetAcceptanceHist[k][t] = new TH1D("targetAcceptance_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      factorAcceptanceHist[k][t] = new TH1D("factorAcceptance_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      MRACC[k][t] = new TH1D("MRACC_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      
      for (Int_t i = 0; i < Nbins; i++) {  // i for bins

	/*** SIMREC ***/
	
	TF1 *Fit_Sim = rootInputFile_Sim[k][t]->Get<TF1>(Form("model_%d", i));      
	TH1D *Hist_Sim = rootInputFile_Sim[k][t]->Get<TH1D>(Form("sub_%d", i));      
	Double_t fitMean_Sim = Fit_Sim->GetParameter(1);
	Double_t fitSigma_Sim = Fit_Sim->GetParameter(2);

	// remove negative entries
	intOmega_Sim[k][t][i] = 0;
	intOmegaError_Sim[k][t][i] = 0;
	for (Int_t s = TMath::Floor((fitMean_Sim - 3*fitSigma_Sim - 0.66)/0.01); s <= TMath::Ceil((fitMean_Sim + 3*fitSigma_Sim - 0.66)/0.01); s++) {
	  if (Hist_Sim->GetBinContent(s) > 0) intOmega_Sim[k][t][i] += Hist_Sim->GetBinContent(s);
	  if (Hist_Sim->GetBinContent(s) > 0) intOmegaError_Sim[k][t][i] += Hist_Sim->GetBinError(s)*Hist_Sim->GetBinError(s);
	}
	intOmegaError_Sim[k][t][i] = TMath::Sqrt(intOmegaError_Sim[k][t][i]);

	/*** MC ***/
	
	TF1 *Fit_MC = rootInputFile_MC[k][t]->Get<TF1>(Form("model_%d", i));      
	TH1D *Hist_MC = rootInputFile_MC[k][t]->Get<TH1D>(Form("sub_%d", i));      
	Double_t fitMean_MC = Fit_MC->GetParameter(1);
	Double_t fitSigma_MC = Fit_MC->GetParameter(2);

	// remove negative entries
	intOmega_MC[k][t][i] = 0;
	intOmegaError_MC[k][t][i] = 0;
	for (Int_t s = TMath::Floor((fitMean_MC - 1.274*fitSigma_MC - 0.66)/0.001); s <= TMath::Ceil((fitMean_MC + 1.274*fitSigma_MC - 0.66)/0.001); s++) {
	  if (Hist_MC->GetBinContent(s) > 0) intOmega_MC[k][t][i] += Hist_MC->GetBinContent(s);
	  if (Hist_MC->GetBinContent(s) > 0) intOmegaError_MC[k][t][i] += Hist_MC->GetBinError(s)*Hist_MC->GetBinError(s);
	}
	intOmegaError_MC[k][t][i] = TMath::Sqrt(intOmegaError_MC[k][t][i]);

	/*** FILL ***/
	
	if (k == 0) { // Q2
	  electronHist_Sim[k][t]->SetBinContent(i + 1, kNElecQ2_Sim[t][i]);
	  electronHist_Sim[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_Sim[t][i]));
	  
	  electronHist_MC[k][t]->SetBinContent(i + 1, kNElecQ2_MC[t][i]);
	  electronHist_MC[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecQ2_MC[t][i]));
	} else if (k == 1) { // Nu
	  electronHist_Sim[k][t]->SetBinContent(i + 1, kNElecNu_Sim[t][i]);
	  electronHist_Sim[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_Sim[t][i]));
	  
	  electronHist_MC[k][t]->SetBinContent(i + 1, kNElecNu_MC[t][i]);
	  electronHist_MC[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElecNu_MC[t][i]));
	} else { // Zh or Pt2
	  electronHist_Sim[k][t]->SetBinContent(i + 1, kNElec_Sim[t]);
	  electronHist_Sim[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElec_Sim[t]));
	  
	  electronHist_MC[k][t]->SetBinContent(i + 1, kNElec_MC[t]);
	  electronHist_MC[k][t]->SetBinError(i + 1, TMath::Sqrt(kNElec_MC[t]));
	}
	
        omegaHist_Sim[k][t]->SetBinContent(i + 1, intOmega_Sim[k][t][i]);
        omegaHist_Sim[k][t]->SetBinError(i + 1, intOmegaError_Sim[k][t][i]);

	omegaHist_MC[k][t]->SetBinContent(i + 1, intOmega_MC[k][t][i]);
        omegaHist_MC[k][t]->SetBinError(i + 1, intOmegaError_MC[k][t][i]);
	
      }

      // calculate acceptance with binomial errors
      omegaAcceptanceHist[k][t]->Divide(omegaHist_Sim[k][t], omegaHist_MC[k][t], 1, 1, "B");
      electronAcceptanceHist[k][t]->Divide(electronHist_Sim[k][t], electronHist_MC[k][t], 1, 1, "B");

      std::cout << std::endl;
    }
  }

  /*** FACTOR HIST ***/
  
  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {
      targetAcceptanceHist[k][t]->Divide(electronAcceptanceHist[k][t], omegaAcceptanceHist[k][t]);
    }
  }

  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {
      factorAcceptanceHist[k][t]->Divide(targetAcceptanceHist[k][t], targetAcceptanceHist[k][0]);
    }
  }

  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {
      MRACC[k][t]->Multiply(MR[k][t], factorAcceptanceHist[k][t]);
    }
  }

  /*** DEFINE GRAPHS ***/

  // define arrays
  Double_t MR_x[Nkinvars][Nbins];
  Double_t MR_xerr[Nkinvars][Nbins];
  
  Double_t MR_y[Nkinvars][Ntargets][Nbins];
  Double_t MR_yerr[Nkinvars][Ntargets][Nbins];
  
  Double_t MRACC_y[Nkinvars][Ntargets][Nbins];
  Double_t MRACC_yerr[Nkinvars][Ntargets][Nbins];

  // fill arrays
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      MR_x[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      MR_xerr[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / 2;
      for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
	MR_y[k][tt][i] = MR[k][tt]->GetBinContent(i + 1);
	MR_yerr[k][tt][i] = MR[k][tt]->GetBinError(i + 1);

	MRACC_y[k][tt][i] = MRACC[k][tt]->GetBinContent(i + 1);
	MRACC_yerr[k][tt][i] = MRACC[k][tt]->GetBinError(i + 1);
      }
    }
  }
    
  // define graphs
  TGraphErrors *MRgraph[Nkinvars][Ntargets];
  TGraphErrors *MRACCgraph[Nkinvars][Ntargets];
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MRgraph[k][tt] = new TGraphErrors(Nbins, MR_x[k], MR_y[k][tt], MR_xerr[k], MR_yerr[k][tt]);
      MRACCgraph[k][tt] = new TGraphErrors(Nbins, MR_x[k], MRACC_y[k][tt], MR_xerr[k], MRACC_yerr[k][tt]);
    }
    // set style
    MRACCgraph[k][1]->SetTitle("");

    MRACCgraph[k][1]->GetXaxis()->SetTitle(kinvarTitle[k]);
    //MRACCgraph[k][1]->GetXaxis()->SetNdivisions(500 + Nbins, kFALSE);
    MRACCgraph[k][1]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
    MRACCgraph[k][1]->GetXaxis()->SetTitleSize(0.04);
    MRACCgraph[k][1]->GetXaxis()->SetTitleOffset(1.);

    MRACCgraph[k][1]->GetYaxis()->SetTitle("R_{A}^{#omega}");
    MRACCgraph[k][1]->GetYaxis()->SetRangeUser(0., maxMR);
    MRACCgraph[k][1]->GetYaxis()->SetTitleSize(0.04);
    MRACCgraph[k][1]->GetYaxis()->SetTitleOffset(1.2);
  
    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MRACCgraph[k][tt]->SetMarkerStyle(21);
      MRACCgraph[k][tt]->SetMarkerSize(1.5);
      MRACCgraph[k][tt]->SetMarkerColor(targetColor[tt]);
      MRACCgraph[k][tt]->SetLineColor(targetColor[tt]);
      MRACCgraph[k][tt]->SetLineWidth(3);

      MRgraph[k][tt]->SetMarkerStyle(24);
      MRgraph[k][tt]->SetMarkerSize(1.5);
      MRgraph[k][tt]->SetMarkerColor(targetColor[tt]);
      MRgraph[k][tt]->SetLineColor(targetColor[tt]);
      MRgraph[k][tt]->SetLineWidth(3);
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
  TCanvas *c = new TCanvas("evnt-mixing_MR_vs_MRACC", "evnt-mixing_MR_vs_MRACC", 1080, 1080);
  c->Divide(2, 2, 0.001, 0.001);

  Int_t counter = 0;
  for (Int_t k = 0; k < Nkinvars; k++) {
    counter++;
    c->cd(counter);
    
    MRACCgraph[k][1]->Draw("AP");  // Carbon
    MRACCgraph[k][2]->Draw("P");   // Iron
    MRACCgraph[k][3]->Draw("P");   // Lead

    if (onlyMRACC == 0) {
      MRgraph[k][1]->Draw("P");  // Carbon
      MRgraph[k][2]->Draw("P");   // Iron
      MRgraph[k][3]->Draw("P");   // Lead
    }
    
    // legend
    TLegend *legend = new TLegend(0.75, 0.7, 0.9, 0.9);  // x1,y1,x2,y2
    legend->AddEntry(MRACCgraph[k][1], "C (Acc. Corr.)", "p");
    legend->AddEntry(MRACCgraph[k][2], "Fe (Acc. Corr.)", "p");
    legend->AddEntry(MRACCgraph[k][3], "Pb (Acc. Corr.)", "p");
    if (onlyMRACC == 0) {       
      legend->AddEntry(MRgraph[k][1], "C", "p");
      legend->AddEntry(MRgraph[k][2], "Fe", "p");
      legend->AddEntry(MRgraph[k][3], "Pb", "p");
    }
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
