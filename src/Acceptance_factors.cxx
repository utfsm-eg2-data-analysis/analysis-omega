/**************************************/
/* Acceptance_factors.cxx             */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// final step: calculation of the Acceptance factors

#include "analysisConfig.h"

#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooGaussian.h"
#include "RooBreitWigner.h"
#include "RooChebychev.h"
#include "RooPolynomial.h"
#include "RooDataHist.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooExtendPdf.h"
#include "RooAbsReal.h"
#include "RooArgSet.h"

using namespace RooFit;

/*** Global variables ***/

TString inputDir    = workDir + "/Acceptance/merged";
TString inputDir_EN = workDir + "/Acceptance_EN/merged";
TString outputDir   = inputDir;

int main() {

  // define arrays
  TString kinVar[4] = {"Q", "N", "Z", "P"};
  TString kinName[4] = {"Q2", "Nu", "Z", "Pt2"};
  TString tarArray[4] = {"D", "C", "Fe", "Pb"};
  
  // read file
  TString currentFitResult;
  TString currentHistName;
  TString targetOption;
  
  // set i/o
  TString inputFile, inputFile_EN, plotFile;

  /*** Extract parameters ***/

  // [target][kinvar][bin]
  Double_t nOmega_GSIM[4][4][5], nOmega_SIMREC[4][4][5];
  Double_t highError_GSIM[4][4][5], highError_SIMREC[4][4][5];
  Double_t lowError_GSIM[4][4][5], lowError_SIMREC[4][4][5];
  Double_t nElectrons_GSIM[4][4][5], nElectrons_SIMREC[4][4][5];
  
  for (Int_t k = 0; k < 4; k++) { // kinvar loop
    plotFile = outputDir + "/factors_" + kinName[k] + ".png";
    for (Int_t t = 0; t < 4; t++) { // target loop
      targetOption = tarArray[t];
      // omega
      inputFile = inputDir + "/fits_" + targetOption + ".root";
      TFile *rootInputFile = new TFile(inputFile);
      for (Int_t i = 0; i < 5; i++) {
	// GSIM
	currentFitResult = "rfABC_GSIM_" + targetOption + "_" + kinVar[k] + Form("%d", i);
	RooFitResult *res_GSIM = (RooFitResult *) rootInputFile->Get(currentFitResult);
	RooRealVar *par_GSIM = (RooRealVar *) res_GSIM->floatParsFinal().find("N_{#omega}");
	std::cout << currentFitResult << " = " << par_GSIM->getValV() << std::endl;
        nOmega_GSIM[t][k][i]    = par_GSIM->getValV();
	highError_GSIM[t][k][i] = par_GSIM->getAsymErrorHi();
	lowError_GSIM[t][k][i]  = par_GSIM->getAsymErrorLo();
	// SIMREC
	currentFitResult = "rfABC_SIMREC_" + targetOption + "_" + kinVar[k] + Form("%d", i);
        RooFitResult *res_SIMREC = (RooFitResult *) rootInputFile->Get(currentFitResult);
	RooRealVar *par_SIMREC = (RooRealVar *) res_SIMREC->floatParsFinal().find("N_{#omega}");
	std::cout << currentFitResult << " = " << par_SIMREC->getValV() << std::endl;
        nOmega_SIMREC[t][k][i]    = par_SIMREC->getValV();
	highError_SIMREC[t][k][i] = par_SIMREC->getAsymErrorHi();
	lowError_SIMREC[t][k][i]  = par_SIMREC->getAsymErrorLo();
      }
      rootInputFile->Close();
      // electrons
      inputFile_EN = inputDir_EN + "/acc-en_" + targetOption + ".root";
      TFile *rootInputFile_EN = new TFile(inputFile_EN);
      for (Int_t i = 0; i < 5; i++) {
	// EN GSIM
	currentHistName = "GSIM_" + targetOption + "_" + kinVar[k] + Form("%d", i);
	if (k == 2 || k == 3) currentHistName = "GSIM_" + targetOption; // hadronic vars
	TH1F *elec_GSIM = (TH1F *)rootInputFile_EN->Get(currentHistName);
	std::cout << currentHistName << " = " << elec_GSIM->GetEntries() << std::endl;
	nElectrons_GSIM[t][k][i] = elec_GSIM->GetEntries();
	// EN SIMREC
	currentHistName = "SIMREC_" + targetOption + "_" + kinVar[k] + Form("%d", i);
	if (k == 2 || k == 3) currentHistName = "SIMREC_" + targetOption; // hadronic vars
	TH1F *elec_SIMREC = (TH1F *)rootInputFile_EN->Get(currentHistName);
	std::cout << currentHistName << " = " << elec_SIMREC->GetEntries() << std::endl;
	nElectrons_SIMREC[t][k][i] = elec_SIMREC->GetEntries();
      }
      // the end
      rootInputFile_EN->Close();
    }

    /*** Prepare Histograms ***/
  
    // creating and filling histograms
    TH1F *DeutOmegaN_GSIM   = new TH1F("DeutOmegaN_GSIM", "", 5, 0.5, 1.);
    TH1F *CarbOmegaN_GSIM   = new TH1F("CarbOmegaN_GSIM", "", 5, 0.5, 1.);
    TH1F *IronOmegaN_GSIM   = new TH1F("IronOmegaN_GSIM", "", 5, 0.5, 1.);
    TH1F *LeadOmegaN_GSIM   = new TH1F("LeadOmegaN_GSIM", "", 5, 0.5, 1.);

    TH1F *DeutOmegaN_SIMREC = new TH1F("DeutOmegaN_SIMREC", "", 5, 0.5, 1.);
    TH1F *CarbOmegaN_SIMREC = new TH1F("CarbOmegaN_SIMREC", "", 5, 0.5, 1.);
    TH1F *IronOmegaN_SIMREC = new TH1F("IronOmegaN_SIMREC", "", 5, 0.5, 1.);
    TH1F *LeadOmegaN_SIMREC = new TH1F("LeadOmegaN_SIMREC", "", 5, 0.5, 1.);
    
    TH1F *DeutElectronN_GSIM   = new TH1F("DeutElectronN_GSIM", "", 5, 0.5, 1.);
    TH1F *CarbElectronN_GSIM   = new TH1F("CarbElectronN_GSIM", "", 5, 0.5, 1.);
    TH1F *IronElectronN_GSIM   = new TH1F("IronElectronN_GSIM", "", 5, 0.5, 1.);
    TH1F *LeadElectronN_GSIM   = new TH1F("LeadElectronN_GSIM", "", 5, 0.5, 1.);

    TH1F *DeutElectronN_SIMREC = new TH1F("DeutElectronN_SIMREC", "", 5, 0.5, 1.);
    TH1F *CarbElectronN_SIMREC = new TH1F("CarbElectronN_SIMREC", "", 5, 0.5, 1.);
    TH1F *IronElectronN_SIMREC = new TH1F("IronElectronN_SIMREC", "", 5, 0.5, 1.);
    TH1F *LeadElectronN_SIMREC = new TH1F("LeadElectronN_SIMREC", "", 5, 0.5, 1.);

    // for each bin in kinvar
    for (Int_t i = 0; i < 5; i++) {
      DeutOmegaN_GSIM->SetBinContent(i + 1, nOmega_GSIM[0][k][i]);
      DeutOmegaN_GSIM->SetBinError(i + 1,   highError_GSIM[0][k][i]); // high error for now
      DeutOmegaN_SIMREC->SetBinContent(i + 1, nOmega_SIMREC[0][k][i]);
      DeutOmegaN_SIMREC->SetBinError(i + 1,   highError_SIMREC[0][k][i]); // for now
      CarbOmegaN_GSIM->SetBinContent(i + 1, nOmega_GSIM[1][k][i]);
      CarbOmegaN_GSIM->SetBinError(i + 1,   highError_GSIM[1][k][i]); // high error for now
      CarbOmegaN_SIMREC->SetBinContent(i + 1, nOmega_SIMREC[1][k][i]);
      CarbOmegaN_SIMREC->SetBinError(i + 1,   highError_SIMREC[1][k][i]); // for now
      IronOmegaN_GSIM->SetBinContent(i + 1, nOmega_GSIM[2][k][i]);
      IronOmegaN_GSIM->SetBinError(i + 1,   highError_GSIM[2][k][i]); // high error for now
      IronOmegaN_SIMREC->SetBinContent(i + 1, nOmega_SIMREC[2][k][i]);
      IronOmegaN_SIMREC->SetBinError(i + 1,   highError_SIMREC[2][k][i]); // for now
      LeadOmegaN_GSIM->SetBinContent(i + 1, nOmega_GSIM[3][k][i]);
      LeadOmegaN_GSIM->SetBinError(i + 1,   highError_GSIM[3][k][i]); // high error for now
      LeadOmegaN_SIMREC->SetBinContent(i + 1, nOmega_SIMREC[3][k][i]);
      LeadOmegaN_SIMREC->SetBinError(i + 1,   highError_SIMREC[3][k][i]); // for now
      DeutElectronN_GSIM->SetBinContent(i + 1, nElectrons_GSIM[0][k][i]);
      DeutElectronN_GSIM->SetBinError(i + 1,   TMath::Sqrt(nElectrons_GSIM[0][k][i])); // sqrt(N)
      DeutElectronN_SIMREC->SetBinContent(i + 1, nElectrons_SIMREC[0][k][i]);
      DeutElectronN_SIMREC->SetBinError(i + 1,   TMath::Sqrt(nElectrons_SIMREC[0][k][i])); // sqrt(N)
      CarbElectronN_GSIM->SetBinContent(i + 1, nElectrons_GSIM[1][k][i]);
      CarbElectronN_GSIM->SetBinError(i + 1,   TMath::Sqrt(nElectrons_GSIM[1][k][i])); // sqrt(N)
      CarbElectronN_SIMREC->SetBinContent(i + 1, nElectrons_SIMREC[1][k][i]);
      CarbElectronN_SIMREC->SetBinError(i + 1,   TMath::Sqrt(nElectrons_SIMREC[1][k][i])); // sqrt(N)
      IronElectronN_GSIM->SetBinContent(i + 1, nElectrons_GSIM[2][k][i]);
      IronElectronN_GSIM->SetBinError(i + 1,   TMath::Sqrt(nElectrons_GSIM[2][k][i])); // sqrt(N)
      IronElectronN_SIMREC->SetBinContent(i + 1, nElectrons_SIMREC[2][k][i]);
      IronElectronN_SIMREC->SetBinError(i + 1,   TMath::Sqrt(nElectrons_SIMREC[2][k][i])); // sqrt(N)
      LeadElectronN_GSIM->SetBinContent(i + 1, nElectrons_GSIM[3][k][i]);
      LeadElectronN_GSIM->SetBinError(i + 1,   TMath::Sqrt(nElectrons_GSIM[3][k][i])); // sqrt(N)
      LeadElectronN_SIMREC->SetBinContent(i + 1, nElectrons_SIMREC[3][k][i]);
      LeadElectronN_SIMREC->SetBinError(i + 1,   TMath::Sqrt(nElectrons_SIMREC[3][k][i])); // sqrt(N)    
    }
        
    /*** Acceptance Correction Factors ***/

    TH1F *DeutACC = new TH1F("DeutACC", "", 5, 0.5, 1.);
    DeutACC->Divide(DeutOmegaN_SIMREC, DeutOmegaN_GSIM, 1, 1, "B"); // binomial errors

    TH1F *CarbACC = new TH1F("CarbACC", "", 5, 0.5, 1.);
    CarbACC->Divide(CarbOmegaN_SIMREC, CarbOmegaN_GSIM, 1, 1, "B");
    
    TH1F *IronACC = new TH1F("IronACC", "", 5, 0.5, 1.);
    IronACC->Divide(IronOmegaN_SIMREC, IronOmegaN_GSIM, 1, 1, "B");
    
    TH1F *LeadACC = new TH1F("LeadACC", "", 5, 0.5, 1.);
    LeadACC->Divide(LeadOmegaN_SIMREC, LeadOmegaN_GSIM, 1, 1, "B");

    TH1F *DeutACC_EN = new TH1F("DeutACC_EN", "", 5, 0.5, 1.);
    DeutACC_EN->Divide(DeutElectronN_SIMREC, DeutElectronN_GSIM, 1, 1, "B"); // binomial errors

    TH1F *CarbACC_EN = new TH1F("CarbACC_EN", "", 5, 0.5, 1.);
    CarbACC_EN->Divide(CarbElectronN_SIMREC, CarbElectronN_GSIM, 1, 1, "B");
    
    TH1F *IronACC_EN = new TH1F("IronACC_EN", "", 5, 0.5, 1.);
    IronACC_EN->Divide(IronElectronN_SIMREC, IronElectronN_GSIM, 1, 1, "B");
    
    TH1F *LeadACC_EN = new TH1F("LeadACC_EN", "", 5, 0.5, 1.);
    LeadACC_EN->Divide(LeadElectronN_SIMREC, LeadElectronN_GSIM, 1, 1, "B");
    
    /*** DRAW ***/

    Double_t kinvarEdges[6];
    if (k == 0) {
      for (Int_t kk = 0; kk < 6; kk++) kinvarEdges[kk] = edgesQ2[kk];
    } else if (k==1) {
      for (Int_t kk = 0; kk < 6; kk++) kinvarEdges[kk] = edgesNu[kk];
    } else if (k==2) {
      for (Int_t kk = 0; kk < 6; kk++) kinvarEdges[kk] = edgesZ[kk];
    } else if (k==3) {
      for (Int_t kk = 0; kk < 6; kk++) kinvarEdges[kk] = edgesPt2[kk];
    }

    // define arrays
    Double_t empty[5];
    Double_t ACC_x[5];
    Double_t ACC_xerr[5];
    
    Double_t DeutACC_y[5];
    Double_t DeutACC_err[5];
    Double_t CarbACC_y[5];
    Double_t CarbACC_err[5];
    Double_t IronACC_y[5];
    Double_t IronACC_err[5];
    Double_t LeadACC_y[5];
    Double_t LeadACC_err[5];
    
    Double_t DeutACC_EN_y[5];
    Double_t DeutACC_EN_err[5];
    Double_t CarbACC_EN_y[5];
    Double_t CarbACC_EN_err[5];
    Double_t IronACC_EN_y[5];
    Double_t IronACC_EN_err[5];
    Double_t LeadACC_EN_y[5];
    Double_t LeadACC_EN_err[5];
    
    // fill arrays
    for (Int_t v = 0; v < 5; v++) {
      empty[v] = 0.;
      ACC_x[v] = (kinvarEdges[v] + kinvarEdges[v+1])/2.;
      ACC_xerr[v] = (kinvarEdges[v+1] - kinvarEdges[v])/TMath::Sqrt(12);
      DeutACC_y[v]   = DeutACC->GetBinContent(v+1);
      DeutACC_err[v] = DeutACC->GetBinError(v+1);
      CarbACC_y[v]   = CarbACC->GetBinContent(v+1);
      CarbACC_err[v] = CarbACC->GetBinError(v+1);
      IronACC_y[v]   = IronACC->GetBinContent(v+1);
      IronACC_err[v] = IronACC->GetBinError(v+1);
      LeadACC_y[v]   = LeadACC->GetBinContent(v+1);
      LeadACC_err[v] = LeadACC->GetBinError(v+1);
      DeutACC_EN_y[v]   = DeutACC_EN->GetBinContent(v+1);
      DeutACC_EN_err[v] = DeutACC_EN->GetBinError(v+1);
      CarbACC_EN_y[v]   = CarbACC_EN->GetBinContent(v+1);
      CarbACC_EN_err[v] = CarbACC_EN->GetBinError(v+1);
      IronACC_EN_y[v]   = IronACC_EN->GetBinContent(v+1);
      IronACC_EN_err[v] = IronACC_EN->GetBinError(v+1);
      LeadACC_EN_y[v]   = LeadACC_EN->GetBinContent(v+1);
      LeadACC_EN_err[v] = LeadACC_EN->GetBinError(v+1);
    }

    // define canvas
    TCanvas *c = new TCanvas("c", "c", 1000, 1000);
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);
    
    // define graphs
    TGraphErrors *DeutACC_gr = new TGraphErrors(5, ACC_x, DeutACC_y, ACC_xerr, DeutACC_err);
    TGraphErrors *CarbACC_gr = new TGraphErrors(5, ACC_x, CarbACC_y, ACC_xerr, CarbACC_err);
    TGraphErrors *IronACC_gr = new TGraphErrors(5, ACC_x, IronACC_y, ACC_xerr, IronACC_err);
    TGraphErrors *LeadACC_gr = new TGraphErrors(5, ACC_x, LeadACC_y, ACC_xerr, LeadACC_err);

    DeutACC_gr->SetTitle("Acceptance Correction Factors: #omega");
    DeutACC_gr->GetXaxis()->SetTitle(kinName[k]);
    DeutACC_gr->GetXaxis()->CenterTitle();
    DeutACC_gr->GetXaxis()->SetNdivisions(400 + 5, kFALSE);
    DeutACC_gr->GetXaxis()->SetLimits(kinvarEdges[0], kinvarEdges[5]);
    DeutACC_gr->GetYaxis()->SetTitle("A(#omega)");
    DeutACC_gr->GetYaxis()->CenterTitle();
    DeutACC_gr->GetYaxis()->SetRangeUser(0.0, 0.01); // updated

    DeutACC_gr->SetMarkerStyle(21);
    DeutACC_gr->SetMarkerSize(1.5);
    DeutACC_gr->SetMarkerColor(kGreen+3);
    DeutACC_gr->SetLineColor(kGreen+3);
    DeutACC_gr->SetLineWidth(3);
    
    DeutACC_gr->Draw("AP");
    
    CarbACC_gr->SetMarkerStyle(21);
    CarbACC_gr->SetMarkerSize(1.5);
    CarbACC_gr->SetMarkerColor(kRed);
    CarbACC_gr->SetLineColor(kRed);
    CarbACC_gr->SetLineWidth(3);
    
    CarbACC_gr->Draw("P");

    IronACC_gr->SetMarkerStyle(21);
    IronACC_gr->SetMarkerSize(1.5);
    IronACC_gr->SetMarkerColor(kBlue);
    IronACC_gr->SetLineColor(kBlue);
    IronACC_gr->SetLineWidth(3);
    
    IronACC_gr->Draw("P");

    LeadACC_gr->SetMarkerStyle(21);
    LeadACC_gr->SetMarkerSize(1.5);
    LeadACC_gr->SetMarkerColor(kBlack);
    LeadACC_gr->SetLineColor(kBlack);
    LeadACC_gr->SetLineWidth(3);
	
    LeadACC_gr->Draw("P");
    // legend position
    Double_t legendX = 0.8;
    if (kinName[k] == "Nu") legendX = 0.1;
    
    // legend
    TLegend *legend = new TLegend(legendX, 0.75, legendX+0.1, 0.9); // x1,y1,x2,y2
    legend->AddEntry(DeutACC_gr, "D", "p");
    legend->AddEntry(CarbACC_gr, "C", "p");
    legend->AddEntry(IronACC_gr, "Fe", "p");
    legend->AddEntry(LeadACC_gr, "Pb", "p");
    legend->Draw();

    c->Print(plotFile); // output file
    
    // define canvas2
    TCanvas *c2 = new TCanvas("c2", "c2", 1000, 1000);
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);
    
    // define graphs
    TGraphErrors *DeutACC_EN_gr = new TGraphErrors(5, ACC_x, DeutACC_EN_y, ACC_xerr, DeutACC_EN_err);
    TGraphErrors *CarbACC_EN_gr = new TGraphErrors(5, ACC_x, CarbACC_EN_y, ACC_xerr, CarbACC_EN_err);
    TGraphErrors *IronACC_EN_gr = new TGraphErrors(5, ACC_x, IronACC_EN_y, ACC_xerr, IronACC_EN_err);
    TGraphErrors *LeadACC_EN_gr = new TGraphErrors(5, ACC_x, LeadACC_EN_y, ACC_xerr, LeadACC_EN_err);

    DeutACC_EN_gr->SetTitle("Acceptance Correction Factors: electrons");
    DeutACC_EN_gr->GetXaxis()->SetTitle(kinName[k]);
    DeutACC_EN_gr->GetXaxis()->CenterTitle();
    DeutACC_EN_gr->GetXaxis()->SetNdivisions(400 + 5, kFALSE);
    DeutACC_EN_gr->GetXaxis()->SetLimits(kinvarEdges[0], kinvarEdges[5]);
    DeutACC_EN_gr->GetYaxis()->SetTitle("A(e)");
    DeutACC_EN_gr->GetYaxis()->CenterTitle();
    DeutACC_EN_gr->GetYaxis()->SetRangeUser(0, 1); // updated

    DeutACC_EN_gr->SetMarkerStyle(21);
    DeutACC_EN_gr->SetMarkerSize(1.5);
    DeutACC_EN_gr->SetMarkerColor(kGreen+3);
    DeutACC_EN_gr->SetLineColor(kGreen+3);
    DeutACC_EN_gr->SetLineWidth(3);
    
    DeutACC_EN_gr->Draw("AP");
    
    CarbACC_EN_gr->SetMarkerStyle(21);
    CarbACC_EN_gr->SetMarkerSize(1.5);
    CarbACC_EN_gr->SetMarkerColor(kRed);
    CarbACC_EN_gr->SetLineColor(kRed);
    CarbACC_EN_gr->SetLineWidth(3);
    
    CarbACC_EN_gr->Draw("P");

    IronACC_EN_gr->SetMarkerStyle(21);
    IronACC_EN_gr->SetMarkerSize(1.5);
    IronACC_EN_gr->SetMarkerColor(kBlue);
    IronACC_EN_gr->SetLineColor(kBlue);
    IronACC_EN_gr->SetLineWidth(3);
    
    IronACC_EN_gr->Draw("P");

    LeadACC_EN_gr->SetMarkerStyle(21);
    LeadACC_EN_gr->SetMarkerSize(1.5);
    LeadACC_EN_gr->SetMarkerColor(kBlack);
    LeadACC_EN_gr->SetLineColor(kBlack);
    LeadACC_EN_gr->SetLineWidth(3);
	
    LeadACC_EN_gr->Draw("P");

    // legend position
    legendX = 0.8;
    if (kinName[k] == "Nu") legendX = 0.1;
    
    // legend
    TLegend *legend2 = new TLegend(legendX, 0.75, legendX+0.1, 0.9); // x1,y1,x2,y2
    legend2->AddEntry(DeutACC_EN_gr, "D", "p");
    legend2->AddEntry(CarbACC_EN_gr, "C", "p");
    legend2->AddEntry(IronACC_EN_gr, "Fe", "p");
    legend2->AddEntry(LeadACC_EN_gr, "Pb", "p");
    legend2->Draw();

    plotFile = outputDir + "/factors_EN_" + kinName[k] + ".png";;
    c2->Print(plotFile); // output file  
  } // end of loop in kinvar
    
  return 0;
}
