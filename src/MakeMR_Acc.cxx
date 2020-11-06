/**************************************/
/* MakeMR_Acc.cxx                     */
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

TString outputDir    = workDir + "/MakeMR";
TString inputDir     = workDir + "/MakeRooFits";
TString inputDir_ACC = workDir + "/Acceptance/merged";
TString inputDir_EN  = workDir + "/Acceptance_EN/merged";

TString kinvarOption;
const Int_t Nbins = 5; // hardcoded

/*** Declaration of functions ***/

inline void parseCommandLine(int argc, char* argv[]);
void printUsage();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);

  // output files
  TString plotFile  = outputDir + "/MR-ACC-" + kinvarOption + ".png";

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
  
  /***** I. ELECTRON NUMBERS *****/

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

  /***** II. OMEGA NUMBERS *****/
  
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

  for (Int_t t = 0; t < 4; t++) { // target loop
    currentTarget = tarArray[t];
    inputFile = inputDir + "/roofits_" + currentTarget + ".root";
    TFile *rootInputFile = new TFile(inputFile);
    for (Int_t i = 0; i < Nbins; i++) { // bins loop
      // DATA
      currentFitResult = "rfCON_DATA_" + currentTarget + "_" + kinvarOption[0] + Form("%d", i);
      RooFitResult *res_DATA = (RooFitResult *) rootInputFile->Get(currentFitResult);
      RooRealVar   *par_DATA = (RooRealVar *)   res_DATA->floatParsFinal().find("N_{#omega}");
      std::cout << currentFitResult << " = " << par_DATA->getValV() << std::endl;
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

  /***** III. ACCEPTANCE FACTORS *****/

  // [target][bin]
  Double_t nOmega_GSIM[4][5], nOmega_SIMREC[4][5];
  Double_t highError_GSIM[4][5], highError_SIMREC[4][5];
  Double_t lowError_GSIM[4][5], lowError_SIMREC[4][5];
  Double_t nElectrons_GSIM[4][5], nElectrons_SIMREC[4][5];

  TString inputFile_ACC, inputFile_EN;
  
  for (Int_t t = 0; t < 4; t++) { // target loop
    currentTarget = tarArray[t];
    // OMEGAS
    inputFile_ACC = inputDir_ACC + "/fits_" + currentTarget + ".root";
    TFile *rootInputFile = new TFile(inputFile_ACC);
    for (Int_t i = 0; i < 5; i++) { // bins loop
      // GSIM
      currentFitResult = "rfABC_GSIM_" + currentTarget + "_" + kinvarOption[0] + Form("%d", i);
      RooFitResult *res_GSIM = (RooFitResult *) rootInputFile->Get(currentFitResult);
      RooRealVar   *par_GSIM = (RooRealVar *)   res_GSIM->floatParsFinal().find("N_{#omega}");
      std::cout << currentFitResult << " = " << par_GSIM->getValV() << std::endl;
      nOmega_GSIM[t][i]    = par_GSIM->getValV();
      highError_GSIM[t][i] = par_GSIM->getAsymErrorHi();
      lowError_GSIM[t][i]  = par_GSIM->getAsymErrorLo();
      // SIMREC
      currentFitResult = "rfABC_SIMREC_" + currentTarget + "_" + kinvarOption[0] + Form("%d", i);
      RooFitResult *res_SIMREC = (RooFitResult *) rootInputFile->Get(currentFitResult);
      RooRealVar   *par_SIMREC = (RooRealVar *)   res_SIMREC->floatParsFinal().find("N_{#omega}");
      std::cout << currentFitResult << " = " << par_SIMREC->getValV() << std::endl;
      nOmega_SIMREC[t][i]    = par_SIMREC->getValV();
      highError_SIMREC[t][i] = par_SIMREC->getAsymErrorHi();
      lowError_SIMREC[t][i]  = par_SIMREC->getAsymErrorLo();
    }
    rootInputFile->Close();
    // ELECTRONS
    inputFile_EN = inputDir_EN + "/acc-en_" + currentTarget + ".root";
    TFile *rootInputFile_EN = new TFile(inputFile_EN);
    for (Int_t i = 0; i < 5; i++) { // bins loop
      // GSIM
      currentHistName = "GSIM_" + currentTarget + "_" + kinvarOption[0] + Form("%d", i);
      if (kinvarOption == "Z" || kinvarOption == "Pt2") currentHistName = "GSIM_" + currentTarget; // hadronic vars
      TH1F *elec_GSIM = (TH1F *)rootInputFile_EN->Get(currentHistName);
      std::cout << currentHistName << " = " << elec_GSIM->GetEntries() << std::endl;
      nElectrons_GSIM[t][i] = elec_GSIM->GetEntries();
      // SIMREC
      currentHistName = "SIMREC_" + currentTarget + "_" + kinvarOption[0] + Form("%d", i);
      if (kinvarOption == "Z" || kinvarOption == "Pt2") currentHistName = "SIMREC_" + currentTarget; // hadronic vars
      TH1F *elec_SIMREC = (TH1F *)rootInputFile_EN->Get(currentHistName);
      std::cout << currentHistName << " = " << elec_SIMREC->GetEntries() << std::endl;
      nElectrons_SIMREC[t][i] = elec_SIMREC->GetEntries();
    }
    // the end
    rootInputFile_EN->Close();
  }
    
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

  for (Int_t i = 0; i < 5; i++) { // bins loop
    DeutOmegaN_GSIM->SetBinContent(i + 1, nOmega_GSIM[0][i]);
    DeutOmegaN_GSIM->SetBinError(i + 1,   highError_GSIM[0][i]); // high error for now
    DeutOmegaN_SIMREC->SetBinContent(i + 1, nOmega_SIMREC[0][i]);
    DeutOmegaN_SIMREC->SetBinError(i + 1,   highError_SIMREC[0][i]); // for now
    CarbOmegaN_GSIM->SetBinContent(i + 1, nOmega_GSIM[1][i]);
    CarbOmegaN_GSIM->SetBinError(i + 1,   highError_GSIM[1][i]); // high error for now
    CarbOmegaN_SIMREC->SetBinContent(i + 1, nOmega_SIMREC[1][i]);
    CarbOmegaN_SIMREC->SetBinError(i + 1,   highError_SIMREC[1][i]); // for now
    IronOmegaN_GSIM->SetBinContent(i + 1, nOmega_GSIM[2][i]);
    IronOmegaN_GSIM->SetBinError(i + 1,   highError_GSIM[2][i]); // high error for now
    IronOmegaN_SIMREC->SetBinContent(i + 1, nOmega_SIMREC[2][i]);
    IronOmegaN_SIMREC->SetBinError(i + 1,   highError_SIMREC[2][i]); // for now
    LeadOmegaN_GSIM->SetBinContent(i + 1, nOmega_GSIM[3][i]);
    LeadOmegaN_GSIM->SetBinError(i + 1,   highError_GSIM[3][i]); // high error for now
    LeadOmegaN_SIMREC->SetBinContent(i + 1, nOmega_SIMREC[3][i]);
    LeadOmegaN_SIMREC->SetBinError(i + 1,   highError_SIMREC[3][i]); // for now
    DeutElectronN_GSIM->SetBinContent(i + 1, nElectrons_GSIM[0][i]);
    DeutElectronN_GSIM->SetBinError(i + 1,   TMath::Sqrt(nElectrons_GSIM[0][i])); // sqrt(N)
    DeutElectronN_SIMREC->SetBinContent(i + 1, nElectrons_SIMREC[0][i]);
    DeutElectronN_SIMREC->SetBinError(i + 1,   TMath::Sqrt(nElectrons_SIMREC[0][i])); // sqrt(N)
    CarbElectronN_GSIM->SetBinContent(i + 1, nElectrons_GSIM[1][i]);
    CarbElectronN_GSIM->SetBinError(i + 1,   TMath::Sqrt(nElectrons_GSIM[1][i])); // sqrt(N)
    CarbElectronN_SIMREC->SetBinContent(i + 1, nElectrons_SIMREC[1][i]);
    CarbElectronN_SIMREC->SetBinError(i + 1,   TMath::Sqrt(nElectrons_SIMREC[1][i])); // sqrt(N)
    IronElectronN_GSIM->SetBinContent(i + 1, nElectrons_GSIM[2][i]);
    IronElectronN_GSIM->SetBinError(i + 1,   TMath::Sqrt(nElectrons_GSIM[2][i])); // sqrt(N)
    IronElectronN_SIMREC->SetBinContent(i + 1, nElectrons_SIMREC[2][i]);
    IronElectronN_SIMREC->SetBinError(i + 1,   TMath::Sqrt(nElectrons_SIMREC[2][i])); // sqrt(N)
    LeadElectronN_GSIM->SetBinContent(i + 1, nElectrons_GSIM[3][i]);
    LeadElectronN_GSIM->SetBinError(i + 1,   TMath::Sqrt(nElectrons_GSIM[3][i])); // sqrt(N)
    LeadElectronN_SIMREC->SetBinContent(i + 1, nElectrons_SIMREC[3][i]);
    LeadElectronN_SIMREC->SetBinError(i + 1,   TMath::Sqrt(nElectrons_SIMREC[3][i])); // sqrt(N)    
  }

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

  /***** IV. PRIME NUMBERS *****/
  /* N_omega' = N_omega/A_omega && N_electron' = N_electron/A_electron */

  // omegas
  TH1F *DeutOmegaNPrime = new TH1F("DeutOmegaNPrime", "", Nbins, 0.5, 1.);
  DeutOmegaNPrime->Divide(DeutOmegaN_fit, DeutACC);

  TH1F *CarbOmegaNPrime = new TH1F("CarbOmegaNPrime", "", Nbins, 0.5, 1.);
  CarbOmegaNPrime->Divide(CarbOmegaN_fit, CarbACC);

  TH1F *IronOmegaNPrime = new TH1F("IronOmegaNPrime", "", Nbins, 0.5, 1.);
  IronOmegaNPrime->Divide(IronOmegaN_fit, IronACC);

  TH1F *LeadOmegaNPrime = new TH1F("LeadOmegaNPrime", "", Nbins, 0.5, 1.);
  LeadOmegaNPrime->Divide(LeadOmegaN_fit, LeadACC);

  // electrons
  TH1F *DeutElectronNPrime = new TH1F("DeutElectronNPrime", "", Nbins, 0.5, 1.);
  DeutElectronNPrime->Divide(DeutElectronN, DeutACC_EN);

  TH1F *CarbElectronNPrime = new TH1F("CarbElectronNPrime", "", Nbins, 0.5, 1.);
  CarbElectronNPrime->Divide(CarbElectronN, CarbACC_EN);

  TH1F *IronElectronNPrime = new TH1F("IronElectronNPrime", "", Nbins, 0.5, 1.);
  IronElectronNPrime->Divide(IronElectronN, IronACC_EN);

  TH1F *LeadElectronNPrime = new TH1F("LeadElectronNPrime", "", Nbins, 0.5, 1.);
  LeadElectronNPrime->Divide(LeadElectronN, LeadACC_EN);

  /***** V. OMEGA/ELECTRON RATIOS *****/

  TH1F *DeutOEPrime = new TH1F("DeutOEPrime", "", Nbins, 0.5, 1.);
  DeutOEPrime->Divide(DeutOmegaNPrime, DeutElectronNPrime);

  TH1F *CarbOEPrime = new TH1F("CarbOEPrime", "", Nbins, 0.5, 1.);
  CarbOEPrime->Divide(CarbOmegaNPrime, CarbElectronNPrime);

  TH1F *IronOEPrime = new TH1F("IronOEPrime", "", Nbins, 0.5, 1.);
  IronOEPrime->Divide(IronOmegaNPrime, IronElectronNPrime);

  TH1F *LeadOEPrime = new TH1F("LeadOEPrime", "", Nbins, 0.5, 1.);
  LeadOEPrime->Divide(LeadOmegaNPrime, LeadElectronNPrime);
  
  /***** VI. MULTIPLICITY RATIOS WITH ACCEPTANCE CORRECTION *****/
    
  TH1F *CarbMRACC = new TH1F("CarbMRACC", "", Nbins, 0.5, 1.);
  CarbMRACC->Divide(CarbOEPrime, DeutOEPrime);
    
  TH1F *IronMRACC = new TH1F("IronMRACC", "", Nbins, 0.5, 1.);
  IronMRACC->Divide(IronOEPrime, DeutOEPrime);
    
  TH1F *LeadMRACC = new TH1F("LeadMRACC", "", Nbins, 0.5, 1.);
  LeadMRACC->Divide(LeadOEPrime, DeutOEPrime);

  /*** Draw! ***/

  // define arrays
  Double_t empty[Nbins];
  Double_t MR_ACC_x[Nbins];
  Double_t MR_ACC_xerr[Nbins];
  Double_t CarbMR_ACC_y[Nbins];
  Double_t CarbMR_ACC_err[Nbins];
  Double_t IronMR_ACC_y[Nbins];
  Double_t IronMR_ACC_err[Nbins];
  Double_t LeadMR_ACC_y[Nbins];
  Double_t LeadMR_ACC_err[Nbins];

  // fill arrays
  for (Int_t v = 0; v < Nbins; v++) {
    empty[v]          = 0.;
    MR_ACC_x[v]       = (kinvarEdges[v] + kinvarEdges[v+1])/2.;
    MR_ACC_xerr[v]    = (kinvarEdges[v+1] - kinvarEdges[v])/TMath::Sqrt(12);
    CarbMR_ACC_y[v]   = CarbMRACC->GetBinContent(v+1);
    CarbMR_ACC_err[v] = CarbMRACC->GetBinError(v+1);
    IronMR_ACC_y[v]   = IronMRACC->GetBinContent(v+1);
    IronMR_ACC_err[v] = IronMRACC->GetBinError(v+1);
    LeadMR_ACC_y[v]   = LeadMRACC->GetBinContent(v+1);
    LeadMR_ACC_err[v] = LeadMRACC->GetBinError(v+1);
  }

  // define canvas
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
    
  // define graphs
  TGraphErrors *CarbMR_ACC_gr = new TGraphErrors(Nbins, MR_ACC_x, CarbMR_ACC_y, MR_ACC_xerr, CarbMR_ACC_err);
  TGraphErrors *IronMR_ACC_gr = new TGraphErrors(Nbins, MR_ACC_x, IronMR_ACC_y, MR_ACC_xerr, IronMR_ACC_err);
  TGraphErrors *LeadMR_ACC_gr = new TGraphErrors(Nbins, MR_ACC_x, LeadMR_ACC_y, MR_ACC_xerr, LeadMR_ACC_err);

  CarbMR_ACC_gr->SetTitle("Multiplicity Ratio: #omega");
  CarbMR_ACC_gr->GetXaxis()->SetTitle(kinvarTitle);
  CarbMR_ACC_gr->GetXaxis()->CenterTitle();
  CarbMR_ACC_gr->GetXaxis()->SetNdivisions(400 + Nbins, kFALSE);
  CarbMR_ACC_gr->GetXaxis()->SetLimits(kinvarEdges[0], kinvarEdges[Nbins]);
  CarbMR_ACC_gr->GetYaxis()->SetTitle("R_{#omega}");
  CarbMR_ACC_gr->GetYaxis()->CenterTitle();
  CarbMR_ACC_gr->GetYaxis()->SetRangeUser(0., 1.4); // updated

  CarbMR_ACC_gr->SetMarkerStyle(21);
  CarbMR_ACC_gr->SetMarkerSize(1.5);
  CarbMR_ACC_gr->SetMarkerColor(kRed);
  CarbMR_ACC_gr->SetLineColor(kRed);
  CarbMR_ACC_gr->SetLineWidth(3);
    
  CarbMR_ACC_gr->Draw("AP");

  IronMR_ACC_gr->SetMarkerStyle(21);
  IronMR_ACC_gr->SetMarkerSize(1.5);
  IronMR_ACC_gr->SetMarkerColor(kBlue);
  IronMR_ACC_gr->SetLineColor(kBlue);
  IronMR_ACC_gr->SetLineWidth(3);
    
  IronMR_ACC_gr->Draw("P");

  LeadMR_ACC_gr->SetMarkerStyle(21);
  LeadMR_ACC_gr->SetMarkerSize(1.5);
  LeadMR_ACC_gr->SetMarkerColor(kBlack);
  LeadMR_ACC_gr->SetLineColor(kBlack);
  LeadMR_ACC_gr->SetLineWidth(3);
	
  LeadMR_ACC_gr->Draw("P");

  // legend position
  Double_t legendX = 0.8;
  if (kinvarOption == "Nu") legendX = 0.1;
    
  // legend
  TLegend *legend = new TLegend(legendX, 0.75, legendX+0.1, 0.9); // x1,y1,x2,y2
  legend->AddEntry(CarbMR_ACC_gr, "C", "p");
  legend->AddEntry(IronMR_ACC_gr, "Fe", "p");
  legend->AddEntry(LeadMR_ACC_gr, "Pb", "p");
  legend->Draw();

  c->Print(plotFile); // output file

  /***** VII. RATIO BETWEEN MR RESULTS *****/
  /* MR_FACTOR*MR = MR_ACC => MR_FACTOR = MR_ACC/MR */

  TString plotFile1 = outputDir + "/MR-ACC-on-MR-" + kinvarOption + ".png";;
  
  // omega/electron ratio
  TH1F *DeutOE = new TH1F("DeutOE", "", Nbins, 0.5, 1.);
  DeutOE->Divide(DeutOmegaN_fit, DeutElectronN);

  TH1F *CarbOE = new TH1F("CarbOE", "", Nbins, 0.5, 1.);
  CarbOE->Divide(CarbOmegaN_fit, CarbElectronN);

  TH1F *IronOE = new TH1F("IronOE", "", Nbins, 0.5, 1.);
  IronOE->Divide(IronOmegaN_fit, IronElectronN);

  TH1F *LeadOE = new TH1F("LeadOE", "", Nbins, 0.5, 1.);
  LeadOE->Divide(LeadOmegaN_fit, LeadElectronN);

  // MR without Acceptance
  TH1F *CarbMR = new TH1F("CarbMR", "", Nbins, 0.5, 1.);
  CarbMR->Divide(CarbOE, DeutOE);
    
  TH1F *IronMR = new TH1F("IronMR", "", Nbins, 0.5, 1.);
  IronMR->Divide(IronOE, DeutOE);
    
  TH1F *LeadMR = new TH1F("LeadMR", "", Nbins, 0.5, 1.);
  LeadMR->Divide(LeadOE, DeutOE);

  // obtain ratio between MRs!
  TH1F *CarbRatio = new TH1F("CarbRatio", "", Nbins, 0.5, 1.);
  CarbRatio->Divide(CarbMRACC, CarbMR);
    
  TH1F *IronRatio = new TH1F("IronRatio", "", Nbins, 0.5, 1.);
  IronRatio->Divide(IronMRACC, IronMR);
    
  TH1F *LeadRatio = new TH1F("LeadRatio", "", Nbins, 0.5, 1.);
  LeadRatio->Divide(LeadMRACC, LeadMR);
  
  /*** Draw! ***/

  // define new arrays
  Double_t Ratio_x[Nbins];
  Double_t Ratio_xerr[Nbins];
  Double_t CarbRatio_y[Nbins];
  Double_t CarbRatio_err[Nbins];
  Double_t IronRatio_y[Nbins];
  Double_t IronRatio_err[Nbins];
  Double_t LeadRatio_y[Nbins];
  Double_t LeadRatio_err[Nbins];

  // fill arrays
  for (Int_t v = 0; v < Nbins; v++) {
    Ratio_x[v]       = (kinvarEdges[v] + kinvarEdges[v+1])/2.;
    Ratio_xerr[v]    = (kinvarEdges[v+1] - kinvarEdges[v])/TMath::Sqrt(12);
    CarbRatio_y[v]   = CarbRatio->GetBinContent(v+1);
    CarbRatio_err[v] = CarbRatio->GetBinError(v+1);
    IronRatio_y[v]   = IronRatio->GetBinContent(v+1);
    IronRatio_err[v] = IronRatio->GetBinError(v+1);
    LeadRatio_y[v]   = LeadRatio->GetBinContent(v+1);
    LeadRatio_err[v] = LeadRatio->GetBinError(v+1);
  }

  // define a new canvas
  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 1000);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
    
  // define graphs
  TGraphErrors *CarbRatio_gr = new TGraphErrors(Nbins, Ratio_x, CarbRatio_y, Ratio_xerr, CarbRatio_err);
  TGraphErrors *IronRatio_gr = new TGraphErrors(Nbins, Ratio_x, IronRatio_y, Ratio_xerr, IronRatio_err);
  TGraphErrors *LeadRatio_gr = new TGraphErrors(Nbins, Ratio_x, LeadRatio_y, Ratio_xerr, LeadRatio_err);

  CarbRatio_gr->SetTitle("Acceptance Correction Factor for Multiplicity Ratio: #omega");
  CarbRatio_gr->GetXaxis()->SetTitle(kinvarTitle);
  CarbRatio_gr->GetXaxis()->CenterTitle();
  CarbRatio_gr->GetXaxis()->SetNdivisions(400 + Nbins, kFALSE);
  CarbRatio_gr->GetXaxis()->SetLimits(kinvarEdges[0], kinvarEdges[Nbins]);
  CarbRatio_gr->GetYaxis()->SetTitle("A(e#omega)");
  CarbRatio_gr->GetYaxis()->CenterTitle();
  CarbRatio_gr->GetYaxis()->SetRangeUser(0., 2.); // updated

  CarbRatio_gr->SetMarkerStyle(21);
  CarbRatio_gr->SetMarkerSize(1.5);
  CarbRatio_gr->SetMarkerColor(kRed);
  CarbRatio_gr->SetLineColor(kRed);
  CarbRatio_gr->SetLineWidth(3);
    
  CarbRatio_gr->Draw("AP");

  IronRatio_gr->SetMarkerStyle(21);
  IronRatio_gr->SetMarkerSize(1.5);
  IronRatio_gr->SetMarkerColor(kBlue);
  IronRatio_gr->SetLineColor(kBlue);
  IronRatio_gr->SetLineWidth(3);
    
  IronRatio_gr->Draw("P");

  LeadRatio_gr->SetMarkerStyle(21);
  LeadRatio_gr->SetMarkerSize(1.5);
  LeadRatio_gr->SetMarkerColor(kBlack);
  LeadRatio_gr->SetLineColor(kBlack);
  LeadRatio_gr->SetLineWidth(3);
	
  LeadRatio_gr->Draw("P");

  // draw line at 1
  drawHorizontalLine(1, kGray+2);
  
  // update legend position
  legendX = 0.8;
  if (kinvarOption == "Nu") legendX = 0.1;
    
  // legend
  TLegend *legend1 = new TLegend(legendX, 0.75, legendX+0.1, 0.9); // x1,y1,x2,y2
  legend1->AddEntry(CarbRatio_gr, "C", "p");
  legend1->AddEntry(IronRatio_gr, "Fe", "p");
  legend1->AddEntry(LeadRatio_gr, "Pb", "p");
  legend1->Draw();

  c1->Print(plotFile1); // output file

  return 0;
}

inline void parseCommandLine(int argc, char* argv[]) {
Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeMR_Acc -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hk:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'k': kinvarOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeMR_Acc -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "MakeMR_Acc program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR_Acc -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR_Acc -k[kinvar]" << std::endl;
  std::cout << "    selects kinvar: Q2, Nu, Z, Pt2" << std::endl;
  std::cout << std::endl;
}
