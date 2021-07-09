#ifndef GLOBAL_H
#include "Global.h"
#endif

void AcceptanceOmega() {

  const Int_t Nkinvars = 4;
  const Int_t Ntargets = 4;
  const Int_t Nbins = 4;

  Double_t intOmega_Sim[Nkinvars][Ntargets][Nbins];
  Double_t intOmegaError_Sim[Nkinvars][Ntargets][Nbins];

  Double_t intOmega_MC[Nkinvars][Ntargets][Nbins];
  Double_t intOmegaError_MC[Nkinvars][Ntargets][Nbins];
  
  /*** INPUT ***/

  TString kinvarOption[4] = {"Q2", "Nu", "wZ", "wPt2"};
  TString titleAxis[4];
  TString histProperties[4];
  titleAxis[0] = "Q^{2} [GeV^{2}]";
  histProperties[0] = "(100, 1., 4.)";
  titleAxis[1] = "#nu [GeV]";
  histProperties[1] = "(100, 2.2, 4.2)";
  titleAxis[2] = "z_{h}";
  histProperties[2] = "(100, 0.5, 0.9)";
  titleAxis[3] = "p_{T}^{2} [GeV^{2}]";
  histProperties[3] = "(100, 0., 1.5)";

  Double_t EdgesKinvar[Nkinvars][Nbins + 1];
  for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[0][i] = kEdgesQ2[i];
  for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[1][i] = kEdgesNu[i];
  for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[2][i] = kEdgesZ[i];
  for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[3][i] = kEdgesPt2[i];
  
  TString targetString[4] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[4] = {kGreen + 3, kRed, kBlue, kBlack};

  TFile *rootInputFile_Sim[Nkinvars][Ntargets];
  TFile *rootInputFile_MC[Nkinvars][Ntargets];

  Double_t plotMin = 0.66;
  Double_t plotMax = 0.90;
  
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {

      // open files
      rootInputFile_MC[k][t] = new TFile(gProDir + "/macros/evnt-mixing/evnt-mixing_binned_" + targetString[t] + "_mc_" + kinvarOption[k] + ".root");
      rootInputFile_Sim[k][t] = new TFile(gProDir + "/macros/evnt-mixing/evnt-mixing_binned_" + targetString[t] + "_sim_" + kinvarOption[k] + ".root");
      std::cout << targetString[t] << " - " << kinvarOption[k] << std::endl;
      
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
	
	std::cout << "(mu, sigma) = " << fitMean_Sim << " +- " << fitSigma_Sim << std::endl;
	std::cout << "intOmega_Sim = " << intOmega_Sim[k][t][i] << " +- " << intOmegaError_Sim[k][t][i] << std::endl;

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
	
	std::cout << "(mu, sigma) = " << fitMean_MC << " +- " << fitSigma_MC << std::endl;
	std::cout << "intOmega_MC = " << intOmega_MC[k][t][i] << " +- " << intOmegaError_MC[k][t][i] << std::endl;
	
      }
      std::cout << std::endl;
    }
  }

  /*** DEFINE HISTOGRAMS ***/

  TH1D *omegaHist_Sim[Nkinvars][Ntargets];
  TH1D *omegaHist_MC[Nkinvars][Ntargets];
  TH1D *acceptanceHist[Nkinvars][Ntargets];
  
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {

      omegaHist_Sim[k][t] = new TH1D("omegaNumber_Sim_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      omegaHist_MC[k][t] = new TH1D("omegaNumber_MC_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      acceptanceHist[k][t] = new TH1D("acceptance_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      // fill hists
      for (Int_t i = 0; i < Nbins; i++) {  // i for bins
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
	acceptanceValue[k][t][i] = acceptanceHist[k][t]->GetBinContent(i+1);
	acceptanceError[k][t][i] = acceptanceHist[k][t]->GetBinError(i+1);
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
      acceptanceGraph[k][t]->SetLineWidth(2);
      acceptanceGraph[k][t]->SetMarkerStyle(20);
    }
  }

  /*** SET Y AXIS ***/

  for (Int_t k = 0; k < Nkinvars; k++) {
    acceptanceGraph[k][0]->GetYaxis()->SetRangeUser(0., 6.5e-3);

    acceptanceGraph[k][0]->GetYaxis()->SetTitle("A_{#omega} = N^{rec}_{#omega}/N^{gen}_{#omega}");
    acceptanceGraph[k][0]->GetYaxis()->SetTitleSize(0.06);
    acceptanceGraph[k][0]->GetYaxis()->SetTitleOffset(1.);
    acceptanceGraph[k][0]->GetYaxis()->SetMaxDigits(3);

    acceptanceGraph[k][0]->GetXaxis()->SetTitle(titleAxis[k]);
    acceptanceGraph[k][0]->GetXaxis()->SetTitleSize(0.06);
  }
  
  /*** DRAW ***/
  
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLineWidth(2);
 
  // set margin sizes
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
 
  TCanvas *c = new TCanvas("acceptance-omega", "acceptance-omega", 1080, 1080);
  c->Divide(2, 2, 0.01, 0.01);  // nx, ny, margins

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  for (Int_t k = 0; k < Nkinvars; k++) {
    c->cd(k+1);
    // draw per kinvar
    acceptanceGraph[k][0]->Draw("AP");
    acceptanceGraph[k][1]->Draw("P");
    acceptanceGraph[k][2]->Draw("P");
    acceptanceGraph[k][3]->Draw("P");
    // legend
    TLegend *legend = new TLegend(0.75, 0.65, 0.9, 0.9);  // x1,y1,x2,y2
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
