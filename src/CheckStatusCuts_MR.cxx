/**************************************/
/* CSC_MR.cxx                         */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// --- CSC Saga - Background Subtracted MR --- //
//
// OBJECTIVE:
// Calculate MR directly from omega number parameter of CSC_fit

#include "analysisConfig.h"

/*** Global variables ***/

TString theDir = proDir + "/out/CheckStatusCuts";

// options
TString kinvarOption;
TString functionOption;
Int_t bkgOption = 1;
Int_t Nmethod = 1; // default

// [D, C, Fe, Pb][Z bin: 3-7]
Double_t omegaMean[4][5];
Double_t omegaSigma[4][5];

Double_t omegaNumber_fit[4][5];
Double_t omegaError_fit[4][5];

Double_t bkgNumber[4][5];
Double_t bkgError[4][5];

// on kinvar
TString  kinvarSufix;
Int_t    kinvarConstant = 1;
Int_t    kinvarNbins = 5;
Double_t kinvarEdges[6];
TString  kinvarTitle;

TString targetName[4] = {"D", "C", "Fe", "Pb"};

TString textFile;
TString plotFile;

Int_t   pid;
TString particleSufix;

/*** Declaration of functions ***/

inline void parseCommandLine(int argc, char* argv[]);
void assignOptions();
void printUsage();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  
  /*** Read fit results ***/

  for (Int_t targIndex = 0; targIndex < 4; targIndex++) {
    for (Int_t index = 0; index < kinvarNbins; index++) {
      
      TString kinvarAuxSufix = kinvarSufix + Form("%d", index + kinvarConstant);
      
      TString fitFile = theDir + "/fit-" + particleSufix + "-" + targetName[targIndex] + kinvarAuxSufix + ".dat";
      std::cout << "Reading " << fitFile << std::endl;
      std::ifstream inFile(fitFile);
      
      TString auxString1, auxString2;
      Int_t l = 0; // line counter
      while (inFile >> auxString1 >> auxString2) {
	l++;
	if (l == 1) { // first line
	  omegaMean[targIndex][index] = auxString1.Atof();
	  std::cout << "  mean  = " << omegaMean[targIndex][index] << std::endl;
	} else if (l == 2) {
	  omegaSigma[targIndex][index] = auxString1.Atof();
	  std::cout << "  sigma = " << omegaSigma[targIndex][index] << std::endl;
	} else if (l == 3) {
	  omegaNumber_fit[targIndex][index] = auxString1.Atof();
	  omegaError_fit[targIndex][index] = auxString2.Atof();
	  std::cout << "  omega number = " << omegaNumber_fit[targIndex][index] << " +/- " << omegaError_fit[targIndex][index] << std::endl;
	} else if (l == 4) {
	  bkgNumber[targIndex][index] = auxString1.Atof();
	  bkgError[targIndex][index] = auxString2.Atof();
	  std::cout << "  bkg number   = " << bkgNumber[targIndex][index] << " +/- " << bkgError[targIndex][index] << std::endl;
	}
      }
      inFile.close();
      std::cout << std::endl;
    }
  }

  /*** Prepare Electron Numbers ***/

  // creating and filling histograms
  TH1F *DeutElectronN = new TH1F("DeutElectronN", "", kinvarNbins, 0.5, 1.);
  TH1F *CarbonElectronN = new TH1F("CarbonElectronN", "", kinvarNbins, 0.5, 1.);
  TH1F *IronElectronN = new TH1F("IronElectronN", "", kinvarNbins, 0.5, 1.);
  TH1F *LeadElectronN = new TH1F("LeadElectronN", "", kinvarNbins, 0.5, 1.);
  
  // for each bin in kinvar
  for (Int_t cc = 0; cc < kinvarNbins; cc++) {
    DeutElectronN->SetBinContent(cc + 1, electronNumber[0]);
    DeutElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumber[0]));
      
    CarbonElectronN->SetBinContent(cc + 1, electronNumber[1]);
    CarbonElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumber[1]));
      
    IronElectronN->SetBinContent(cc + 1, electronNumber[2]);
    IronElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumber[2]));
      
    LeadElectronN->SetBinContent(cc + 1, electronNumber[3]);
    LeadElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumber[3]));
  }
 
  // creating and filling histograms
  TH1F *DeutOmegaN_fit = new TH1F("DeutOmegaN_fit", "", kinvarNbins, 0.5, 1.);
  TH1F *CarbonOmegaN_fit = new TH1F("CarbonOmegaN_fit", "", kinvarNbins, 0.5, 1.);
  TH1F *IronOmegaN_fit = new TH1F("IronOmegaN_fit", "", kinvarNbins, 0.5, 1.);
  TH1F *LeadOmegaN_fit = new TH1F("LeadOmegaN_fit", "", kinvarNbins, 0.5, 1.);
    
  // for each bin in kinvar
  for (Int_t cc = 0; cc < kinvarNbins; cc++) {
    DeutOmegaN_fit->SetBinContent(cc + 1, omegaNumber_fit[0][cc]);
    DeutOmegaN_fit->SetBinError(cc + 1, omegaError_fit[0][cc]);
      
    CarbonOmegaN_fit->SetBinContent(cc + 1, omegaNumber_fit[1][cc]);
    CarbonOmegaN_fit->SetBinError(cc + 1, omegaError_fit[1][cc]);
      
    IronOmegaN_fit->SetBinContent(cc + 1, omegaNumber_fit[2][cc]);
    IronOmegaN_fit->SetBinError(cc + 1, omegaError_fit[2][cc]);
      
    LeadOmegaN_fit->SetBinContent(cc + 1, omegaNumber_fit[3][cc]);
    LeadOmegaN_fit->SetBinError(cc + 1, omegaError_fit[3][cc]);
  }

  /*** Multiplicities (Hadronic Ratios) ***/

  TH1F *DeutHR = new TH1F("DeutHR", "", kinvarNbins, 0.5, 1.);
  DeutHR->Divide(DeutOmegaN_fit, DeutElectronN);

  TH1F *CarbonHR = new TH1F("CarbonHR", "", kinvarNbins, 0.5, 1.);
  CarbonHR->Divide(CarbonOmegaN_fit, CarbonElectronN);

  TH1F *IronHR = new TH1F("IronHR", "", kinvarNbins, 0.5, 1.);
  IronHR->Divide(IronOmegaN_fit, IronElectronN);

  TH1F *LeadHR = new TH1F("LeadHR", "", kinvarNbins, 0.5, 1.);
  LeadHR->Divide(LeadOmegaN_fit, LeadElectronN);
    
  /*** Multiplicity Ratios ***/
    
  TH1F *CarbonMR = new TH1F("CarbonMR", "", kinvarNbins, 0.5, 1.);
  CarbonMR->Divide(CarbonHR, DeutHR);
    
  TH1F *IronMR = new TH1F("IronMR", "", kinvarNbins, 0.5, 1.);
  IronMR->Divide(IronHR, DeutHR);
    
  TH1F *LeadMR = new TH1F("LeadMR", "", kinvarNbins, 0.5, 1.);
  LeadMR->Divide(LeadHR, DeutHR);

  /*** Draw ***/

  // define arrays
  Double_t empty[kinvarNbins];
  Double_t MR_x[kinvarNbins];
  Double_t MR_xerr[kinvarNbins]; // new!
  Double_t CarbonMR_y[kinvarNbins];
  Double_t CarbonMR_err[kinvarNbins];
  Double_t IronMR_y[kinvarNbins];
  Double_t IronMR_err[kinvarNbins];
  Double_t LeadMR_y[kinvarNbins];
  Double_t LeadMR_err[kinvarNbins];

  // fill arrays
  for (Int_t v = 0; v < kinvarNbins; v++) {
    empty[v] = 0.;
    MR_x[v] = (kinvarEdges[v] + kinvarEdges[v+1])/2.;
    MR_xerr[v] = (kinvarEdges[v+1] - kinvarEdges[v])/TMath::Sqrt(12); // new
    CarbonMR_y[v] = CarbonMR->GetBinContent(v+1);
    CarbonMR_err[v] = CarbonMR->GetBinError(v+1);
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
  TGraphErrors *CarbonMR_gr = new TGraphErrors(kinvarNbins, MR_x, CarbonMR_y, MR_xerr, CarbonMR_err);
  TGraphErrors *IronMR_gr = new TGraphErrors(kinvarNbins, MR_x, IronMR_y, MR_xerr, IronMR_err);
  TGraphErrors *LeadMR_gr = new TGraphErrors(kinvarNbins, MR_x, LeadMR_y, MR_xerr, LeadMR_err);

  CarbonMR_gr->SetTitle("Multiplicity Ratio: #omega");
  CarbonMR_gr->GetXaxis()->SetTitle(kinvarTitle);
  CarbonMR_gr->GetXaxis()->CenterTitle();
  CarbonMR_gr->GetXaxis()->SetNdivisions(400 + kinvarNbins, kFALSE);
  CarbonMR_gr->GetXaxis()->SetLimits(kinvarEdges[0], kinvarEdges[kinvarNbins]);
  CarbonMR_gr->GetYaxis()->SetTitle("R_{#omega}");
  CarbonMR_gr->GetYaxis()->CenterTitle();
  CarbonMR_gr->GetYaxis()->SetRangeUser(0., 1.4); // updated

  CarbonMR_gr->SetMarkerStyle(21);
  CarbonMR_gr->SetMarkerSize(1.5);
  CarbonMR_gr->SetMarkerColor(kRed);
  CarbonMR_gr->SetLineColor(kRed);
  CarbonMR_gr->SetLineWidth(3);
    
  CarbonMR_gr->Draw("AP");

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

  // legend
  TLegend *legend = new TLegend(0.8, 0.75, 0.9, 0.9); // x1,y1,x2,y2
  legend->AddEntry(CarbonMR_gr, "Carbon", "p");
  legend->AddEntry(IronMR_gr, "Iron", "p");
  legend->AddEntry(LeadMR_gr, "Lead", "p");
  legend->Draw();

  c->Print(plotFile); // output file

  // saving content
  std::ofstream outFinalFile(textFile, std::ios::out); // output file
    
  // l = line number
  for (Int_t l = 1; l <= kinvarNbins; l++) {
    outFinalFile << CarbonMR->GetBinContent(l) << "\t" << CarbonMR->GetBinError(l) << "\t"
		 << IronMR->GetBinContent(l) << "\t" << IronMR->GetBinError(l) << "\t"
		 << LeadMR->GetBinContent(l) << "\t" << LeadMR->GetBinError(l)  << std::endl;
  }
  outFinalFile.close();
  std::cout << "Created file: " << textFile << std::endl;
    
  return 0;
}

inline void parseCommandLine(int argc, char* argv[]) {
Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckStatusCuts_MR -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hs:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 's': pid = atoi(optarg); break;	    
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckStatusCuts_MR -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "CheckStatusCuts_MR program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_MR -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_MR -s[pid]" << std::endl;
  std::cout << "    no status cuts  = 0" << std::endl;
  std::cout << "    only pi+ cuts   = 211" << std::endl;
  std::cout << "    all status cuts = 999" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // kinvar option
  kinvarSufix = "-z";
  kinvarConstant = 3;
  kinvarTitle = "Z";
  for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesZ[i];
  // for pid/status
  if (pid == 999) {
    particleSufix = "allstat";
  } else if (pid == 211) {
    particleSufix = "pi+";
  } else if (pid == 00){
    particleSufix = "nostat";
  }
  // output files
  plotFile = theDir + "/bs-MR-Z-" + particleSufix + ".png";
  textFile = theDir + "/bs-MR-Z-" + particleSufix + ".dat";
}
