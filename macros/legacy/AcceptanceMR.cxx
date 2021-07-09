#ifndef GLOBAL_H
#include "Global.h"
#endif

void AcceptanceMR() {

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

  TH1D *electronHist_Sim[Nkinvars][Ntargets];
  TH1D *electronHist_MC[Nkinvars][Ntargets];
  
  TH1D *electronAcceptanceHist[Nkinvars][Ntargets];
  TH1D *omegaAcceptanceHist[Nkinvars][Ntargets];
  
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {

      omegaHist_Sim[k][t] = new TH1D("omegaNumber_Sim_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      omegaHist_MC[k][t] = new TH1D("omegaNumber_MC_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      omegaAcceptanceHist[k][t] = new TH1D("omegaAcceptance_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);

      electronHist_Sim[k][t] = new TH1D("electronNumber_Sim_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      electronHist_MC[k][t] = new TH1D("electronNumber_MC_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      electronAcceptanceHist[k][t] = new TH1D("electronAcceptance_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      
      // fill hists
      for (Int_t i = 0; i < Nbins; i++) {  // i for bins
	// electrons
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


	std::cout << "nelectron_MC = " << electronHist_MC[k][t]->GetBinContent(i+1) << std::endl;
	std::cout << "nelectron_Sim = " << electronHist_Sim[k][t]->GetBinContent(i+1) << std::endl;
      }
      
      // calculate acceptance with binomial errors
      omegaAcceptanceHist[k][t]->Divide(omegaHist_Sim[k][t], omegaHist_MC[k][t], 1, 1, "B");
      electronAcceptanceHist[k][t]->Divide(electronHist_Sim[k][t], electronHist_MC[k][t], 1, 1, "B");
    }
  }

  /*** FACTOR HIST ***/
  
  TH1D *targetAcceptanceHist[Nkinvars][Ntargets];
  TH1D *factorAcceptanceHist[Nkinvars][Ntargets]; // only solid targets
  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {
      targetAcceptanceHist[k][t] = new TH1D("targetAcceptance_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      targetAcceptanceHist[k][t]->Divide(electronAcceptanceHist[k][t], omegaAcceptanceHist[k][t]);
    }
  }

  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {
      factorAcceptanceHist[k][t] = new TH1D("factorAcceptance_" + targetString[t], "", Nbins, EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
      factorAcceptanceHist[k][t]->Divide(targetAcceptanceHist[k][t], targetAcceptanceHist[k][0]);
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
	acceptanceValue[k][t][i] = factorAcceptanceHist[k][t]->GetBinContent(i+1);
	acceptanceError[k][t][i] = factorAcceptanceHist[k][t]->GetBinError(i+1);
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
    acceptanceGraph[k][1]->GetYaxis()->SetRangeUser(0.8, 1.2);

    acceptanceGraph[k][1]->GetYaxis()->SetTitle("(A_{e-}/A_{#omega})_{A} / (A_{e-}/A_{#omega})_{D} ");
    acceptanceGraph[k][1]->GetYaxis()->SetTitleSize(0.06);
    acceptanceGraph[k][1]->GetYaxis()->SetTitleOffset(1.);
    acceptanceGraph[k][1]->GetYaxis()->SetMaxDigits(3);

    acceptanceGraph[k][1]->GetXaxis()->SetTitle(titleAxis[k]);
    acceptanceGraph[k][1]->GetXaxis()->SetTitleSize(0.06);
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

    Double_t u;
    gPad->Update(); // necessary
    u = (0. - gPad->GetY1())/(gPad->GetY2() - gPad->GetY1());
    // u = (y - y1)/(y2 - y1);
    TLine *liney = new TLine(0.1, u, 0.9, u);
    liney->SetLineColor(kRed);
    liney->SetLineStyle(kDashed);
    liney->SetLineWidth(3);
    liney->SetX1(0.15);
    liney->SetX2(0.95);    
    liney->SetNDC(kTRUE);
    liney->Draw("SAME");
    
    // draw per kinvar
    acceptanceGraph[k][1]->Draw("AP");
    acceptanceGraph[k][2]->Draw("P");
    acceptanceGraph[k][3]->Draw("P");
    
    // legend
    TLegend *legend = new TLegend(0.75, 0.65, 0.9, 0.9);  // x1,y1,x2,y2
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
