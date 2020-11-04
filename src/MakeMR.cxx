/**************************************/
/* MakeMR.cxx                         */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// November 2020

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

#include "analysisConfig.h"

/*** Global variables ***/

TString outputDir = workDir + "/MakeMR";
TString inputDir  = workDir + "/MakeRooFits";

TString kinvarOption;
const Int_t Nbins = 5; // hardcoded

/*** Declaration of functions ***/

inline void parseCommandLine(int argc, char* argv[]);
void printUsage();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);

  // output files
  TString plotFile0 = outputDir + "/ER-" + kinvarOption + ".png";
  TString plotFile  = outputDir + "/MR-" + kinvarOption + ".png";

  // kinvar options
  Double_t kinvarEdges[6];
  TString  kinvarTitle;
  if (kinvarOption == "Z") {
    kinvarTitle = "Z";
    for (Int_t i = 0; i < (Nbins+1); i++) kinvarEdges[i] = edgesZ[i];
  } else if (kinvarOption == "Q2") {
    kinvarTitle = "Q^{2} (GeV^{2})";
    for (Int_t i = 0; i < (Nbins+1); i++) kinvarEdges[i] = edgesQ2[i];
  } else if (kinvarOption == "Nu") {
    kinvarTitle = "#nu (GeV)";
    for (Int_t i = 0; i < (Nbins+1); i++) kinvarEdges[i] = edgesNu[i];
  } else if (kinvarOption == "Pt2") {
    kinvarTitle = "p_{T}^{2} (GeV^{2})";
    for (Int_t i = 0; i < (Nbins+1); i++) kinvarEdges[i] = edgesPt2[i];
  }
  
  /***** ELECTRON NUMBERS *****/

  // creating and filling histograms
  TH1F *DeutElectronN = new TH1F("DeutElectronN", "", Nbins, 0.5, 1.);
  TH1F *CarbElectronN = new TH1F("CarbElectronN", "", Nbins, 0.5, 1.);
  TH1F *IronElectronN = new TH1F("IronElectronN", "", Nbins, 0.5, 1.);
  TH1F *LeadElectronN = new TH1F("LeadElectronN", "", Nbins, 0.5, 1.);
  
  if (kinvarOption == "Z" || kinvarOption == "Pt2") {
    for (Int_t cc = 0; cc < Nbins; cc++) {
      DeutElectronN->SetBinContent(cc + 1, electronNumber[0]);
      DeutElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumber[0]));      
      CarbElectronN->SetBinContent(cc + 1, electronNumber[1]);
      CarbElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumber[1]));
      IronElectronN->SetBinContent(cc + 1, electronNumber[2]);
      IronElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumber[2]));
      LeadElectronN->SetBinContent(cc + 1, electronNumber[3]);
      LeadElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumber[3]));
    }
  } else if (kinvarOption == "Q2") {
    for (Int_t cc = 0; cc < Nbins; cc++) {
      DeutElectronN->SetBinContent(cc + 1, electronNumberQ2[0][cc]);
      DeutElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberQ2[0][cc]));
      CarbElectronN->SetBinContent(cc + 1, electronNumberQ2[1][cc]);
      CarbElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberQ2[1][cc]));
      IronElectronN->SetBinContent(cc + 1, electronNumberQ2[2][cc]);
      IronElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberQ2[2][cc]));
      LeadElectronN->SetBinContent(cc + 1, electronNumberQ2[3][cc]);
      LeadElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberQ2[3][cc]));
    }
  } else if (kinvarOption == "Nu") { 
    for (Int_t cc = 0; cc < Nbins; cc++) {
      DeutElectronN->SetBinContent(cc + 1, electronNumberNu[0][cc]);
      DeutElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberNu[0][cc]));
      CarbElectronN->SetBinContent(cc + 1, electronNumberNu[1][cc]);
      CarbElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberNu[1][cc]));
      IronElectronN->SetBinContent(cc + 1, electronNumberNu[2][cc]);
      IronElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberNu[2][cc]));
      LeadElectronN->SetBinContent(cc + 1, electronNumberNu[3][cc]);
      LeadElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberNu[3][cc]));
    }
  }

  /*** Plotting Electron ratios ***/

  TH1F *CarbER = new TH1F("CarbER", "", Nbins, 0.5, 1.);
  CarbER->Divide(DeutElectronN, CarbElectronN);
  
  TH1F *IronER = new TH1F("IronER", "", Nbins, 0.5, 1.);
  IronER->Divide(DeutElectronN, IronElectronN);
  
  TH1F *LeadER = new TH1F("LeadER", "", Nbins, 0.5, 1.);
  LeadER->Divide(DeutElectronN, LeadElectronN);

  /*** Draw ***/
  
  // define arrays
  Double_t ER_x[Nbins];
  Double_t ER_xerr[Nbins];
  Double_t CarbER_y[Nbins];
  Double_t CarbER_err[Nbins];
  Double_t IronER_y[Nbins];
  Double_t IronER_err[Nbins];
  Double_t LeadER_y[Nbins];
  Double_t LeadER_err[Nbins];
  
  // fill arrays
  for (Int_t v = 0; v < Nbins; v++) {
    ER_x[v] = (kinvarEdges[v] + kinvarEdges[v+1])/2.;
    ER_xerr[v] = (kinvarEdges[v+1] - kinvarEdges[v])/TMath::Sqrt(12); // new
    CarbER_y[v] = CarbER->GetBinContent(v+1);
    CarbER_err[v] = CarbER->GetBinError(v+1);
    IronER_y[v] = IronER->GetBinContent(v+1);
    IronER_err[v] = IronER->GetBinError(v+1);
    LeadER_y[v] = LeadER->GetBinContent(v+1);
    LeadER_err[v] = LeadER->GetBinError(v+1);
  }
  
  // define canvas
  TCanvas *c0 = new TCanvas("c0", "c0", 1000, 1000);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  
  // define graphs
  TGraphErrors *CarbER_gr = new TGraphErrors(Nbins, ER_x, CarbER_y, ER_xerr, CarbER_err);
  TGraphErrors *IronER_gr = new TGraphErrors(Nbins, ER_x, IronER_y, ER_xerr, IronER_err);
  TGraphErrors *LeadER_gr = new TGraphErrors(Nbins, ER_x, LeadER_y, ER_xerr, LeadER_err);
    
  CarbER_gr->SetTitle("Electron Ratio");
  CarbER_gr->GetXaxis()->SetTitle(kinvarTitle);
  CarbER_gr->GetXaxis()->CenterTitle();
  CarbER_gr->GetXaxis()->SetNdivisions(400 + Nbins, kFALSE);
  CarbER_gr->GetXaxis()->SetLimits(kinvarEdges[0], kinvarEdges[Nbins]);
  CarbER_gr->GetYaxis()->SetTitle("R_{e}^{DIS}");
  CarbER_gr->GetYaxis()->CenterTitle();
  CarbER_gr->GetYaxis()->SetRangeUser(0., 8.); // updated
  
  CarbER_gr->SetMarkerStyle(21);
  CarbER_gr->SetMarkerSize(1.5);
  CarbER_gr->SetMarkerColor(kRed);
  CarbER_gr->SetLineColor(kRed);
  CarbER_gr->SetLineWidth(3);
  
  CarbER_gr->Draw("AP");
  
  IronER_gr->SetMarkerStyle(21);
  IronER_gr->SetMarkerSize(1.5);
  IronER_gr->SetMarkerColor(kBlue);
  IronER_gr->SetLineColor(kBlue);
  IronER_gr->SetLineWidth(3);
  
  IronER_gr->Draw("P");
  
  LeadER_gr->SetMarkerStyle(21);
  LeadER_gr->SetMarkerSize(1.5);
  LeadER_gr->SetMarkerColor(kBlack);
  LeadER_gr->SetLineColor(kBlack);
  LeadER_gr->SetLineWidth(3);
  
  LeadER_gr->Draw("P");
  
  // legend
  TLegend *legend0 = new TLegend(0.8, 0.75, 0.9, 0.9); // x1,y1,x2,y2
  legend0->AddEntry(CarbER_gr, "C", "p");
  legend0->AddEntry(IronER_gr, "Fe", "p");
  legend0->AddEntry(LeadER_gr, "Pb", "p");
  legend0->Draw();
  
  c0->Print(plotFile0); // output file

  /***** OMEGA NUMBERS *****/

  /*** Extract parameters ***/
  
  // obtaining omega numbers [D, C, Fe, Pb][Nbins]
  Double_t omegaNumber_fit[4][5];
  Double_t omegaError_fit[4][5];

  // read file
  TString inputFile;
  TString currentFitResult;
  TString currentHistName;
  
  // targets
  TString tarArray[4] = {"D", "C", "Fe", "Pb"};
  TString currentTarget;
  for (Int_t t = 0; t < 4; t++) {
    currentTarget = tarArray[t];
    inputFile = inputDir + "/roofits_" + currentTarget + ".root";
    TFile *rootInputFile = new TFile(inputFile);
    // bins
    for (Int_t i = 0; i < Nbins; i++) {
      // SIMREC
      currentFitResult = "rfCON_DATA_" + currentTarget + "_" + kinvarOption[0] + Form("%d", i);
      std::cout << currentFitResult << std::endl;
      RooFitResult *res_DATA = (RooFitResult *) rootInputFile->Get(currentFitResult);
      RooRealVar   *par_DATA = (RooRealVar *)   res_DATA->floatParsFinal().find("N_{#omega}");
      omegaNumber_fit[t][i] = par_DATA->getValV();
      omegaError_fit[t][i]  = par_DATA->getAsymErrorHi();
      // omegaError_fit[t][i]  = par_DATA->getAsymErrorLo();
    }
    rootInputFile->Close();
  }
  
  // creating and filling histograms
  TH1F *DeutOmegaN_fit = new TH1F("DeutOmegaN_fit", "", Nbins, 0.5, 1.);
  TH1F *CarbOmegaN_fit = new TH1F("CarbOmegaN_fit", "", Nbins, 0.5, 1.);
  TH1F *IronOmegaN_fit = new TH1F("IronOmegaN_fit", "", Nbins, 0.5, 1.);
  TH1F *LeadOmegaN_fit = new TH1F("LeadOmegaN_fit", "", Nbins, 0.5, 1.);
  
  // for each bin in kinvar
  for (Int_t cc = 0; cc < Nbins; cc++) {
    DeutOmegaN_fit->SetBinContent(cc + 1, omegaNumber_fit[0][cc]);
    DeutOmegaN_fit->SetBinError(cc + 1, omegaError_fit[0][cc]);
    CarbOmegaN_fit->SetBinContent(cc + 1, omegaNumber_fit[1][cc]);
    CarbOmegaN_fit->SetBinError(cc + 1, omegaError_fit[1][cc]);
    IronOmegaN_fit->SetBinContent(cc + 1, omegaNumber_fit[2][cc]);
    IronOmegaN_fit->SetBinError(cc + 1, omegaError_fit[2][cc]);
    LeadOmegaN_fit->SetBinContent(cc + 1, omegaNumber_fit[3][cc]);
    LeadOmegaN_fit->SetBinError(cc + 1, omegaError_fit[3][cc]);
  }
  
  /*** Omega/Electron Ratio ***/

  TH1F *DeutOE = new TH1F("DeutOE", "", Nbins, 0.5, 1.);
  DeutOE->Divide(DeutOmegaN_fit, DeutElectronN);

  TH1F *CarbOE = new TH1F("CarbOE", "", Nbins, 0.5, 1.);
  CarbOE->Divide(CarbOmegaN_fit, CarbElectronN);

  TH1F *IronOE = new TH1F("IronOE", "", Nbins, 0.5, 1.);
  IronOE->Divide(IronOmegaN_fit, IronElectronN);

  TH1F *LeadOE = new TH1F("LeadOE", "", Nbins, 0.5, 1.);
  LeadOE->Divide(LeadOmegaN_fit, LeadElectronN);
    
  /*** Multiplicity Ratios ***/
    
  TH1F *CarbMR = new TH1F("CarbMR", "", Nbins, 0.5, 1.);
  CarbMR->Divide(CarbOE, DeutOE);
    
  TH1F *IronMR = new TH1F("IronMR", "", Nbins, 0.5, 1.);
  IronMR->Divide(IronOE, DeutOE);
    
  TH1F *LeadMR = new TH1F("LeadMR", "", Nbins, 0.5, 1.);
  LeadMR->Divide(LeadOE, DeutOE);

  /*** Draw ***/

  // define arrays
  Double_t empty[Nbins];
  Double_t MR_x[Nbins];
  Double_t MR_xerr[Nbins];
  Double_t CarbMR_y[Nbins];
  Double_t CarbMR_err[Nbins];
  Double_t IronMR_y[Nbins];
  Double_t IronMR_err[Nbins];
  Double_t LeadMR_y[Nbins];
  Double_t LeadMR_err[Nbins];

  // fill arrays
  for (Int_t v = 0; v < Nbins; v++) {
    empty[v] = 0.;
    MR_x[v] = (kinvarEdges[v] + kinvarEdges[v+1])/2.;
    MR_xerr[v] = (kinvarEdges[v+1] - kinvarEdges[v])/TMath::Sqrt(12); // new
    CarbMR_y[v] = CarbMR->GetBinContent(v+1);
    CarbMR_err[v] = CarbMR->GetBinError(v+1);
    IronMR_y[v] = IronMR->GetBinContent(v+1);
    IronMR_err[v] = IronMR->GetBinError(v+1);
    LeadMR_y[v] = LeadMR->GetBinContent(v+1);
    LeadMR_err[v] = LeadMR->GetBinError(v+1);
  }

  // define canvas
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
    
  // define graphs
  TGraphErrors *CarbMR_gr = new TGraphErrors(Nbins, MR_x, CarbMR_y, MR_xerr, CarbMR_err);
  TGraphErrors *IronMR_gr = new TGraphErrors(Nbins, MR_x, IronMR_y, MR_xerr, IronMR_err);
  TGraphErrors *LeadMR_gr = new TGraphErrors(Nbins, MR_x, LeadMR_y, MR_xerr, LeadMR_err);

  CarbMR_gr->SetTitle("Multiplicity Ratio: #omega");
  CarbMR_gr->GetXaxis()->SetTitle(kinvarTitle);
  CarbMR_gr->GetXaxis()->CenterTitle();
  CarbMR_gr->GetXaxis()->SetNdivisions(400 + Nbins, kFALSE);
  CarbMR_gr->GetXaxis()->SetLimits(kinvarEdges[0], kinvarEdges[Nbins]);
  CarbMR_gr->GetYaxis()->SetTitle("R_{#omega}");
  CarbMR_gr->GetYaxis()->CenterTitle();
  CarbMR_gr->GetYaxis()->SetRangeUser(0., 1.4); // updated

  CarbMR_gr->SetMarkerStyle(21);
  CarbMR_gr->SetMarkerSize(1.5);
  CarbMR_gr->SetMarkerColor(kRed);
  CarbMR_gr->SetLineColor(kRed);
  CarbMR_gr->SetLineWidth(3);
    
  CarbMR_gr->Draw("AP");

  IronMR_gr->SetMarkerStyle(21);
  IronMR_gr->SetMarkerSize(1.5);
  IronMR_gr->SetMarkerColor(kBlue);
  IronMR_gr->SetLineColor(kBlue);
  IronMR_gr->SetLineWidth(3);
    
  IronMR_gr->Draw("P");

  LeadMR_gr->SetMarkerStyle(21);
  LeadMR_gr->SetMarkerSize(1.5);
  LeadMR_gr->SetMarkerColor(kBlack);
  LeadMR_gr->SetLineColor(kBlack);
  LeadMR_gr->SetLineWidth(3);
	
  LeadMR_gr->Draw("P");

  // legend position
  Double_t legendX = 0.8;
  if (kinvarOption == "Nu") legendX = 0.1;
    
  // legend
  TLegend *legend = new TLegend(legendX, 0.75, legendX+0.1, 0.9); // x1,y1,x2,y2
  legend->AddEntry(CarbMR_gr, "C", "p");
  legend->AddEntry(IronMR_gr, "Fe", "p");
  legend->AddEntry(LeadMR_gr, "Pb", "p");
  legend->Draw();

  c->Print(plotFile); // output file

  return 0;
}

inline void parseCommandLine(int argc, char* argv[]) {
Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeMR -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hk:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'k': kinvarOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeMR -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "MakeMR program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR -k[kinvar]" << std::endl;
  std::cout << "    selects kinvar: Q2, Nu, Z, Pt2" << std::endl;
  std::cout << std::endl;
}
