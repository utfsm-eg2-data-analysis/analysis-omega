/**************************************/
/* MakeMR-nbs.cxx                     */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// From the MakeRooFits results, we obtain mean and sigma for each omega peak
// With the mean and sigma, we set the edges for a cut around the peak propto sigma
// This program calculates MR doing cuts on the peak and then dividing

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/MakeMR/nbs";
TString fitDir = proDir + "/out/MakeRooFits";

// options
TString kinvarOption;

Int_t Nsigma = 5; // default
TString sigmaSufix;

// for kinvar
TString  kinvarTitle;
Int_t    kinvarConstant = 1; // default for (Q2, Nu, Pt2)
Int_t    kinvarNbins = 5;    // default for all
TString  kinvarSufix;
Double_t kinvarEdges[6];

TString textFile;
TString plotFile;

TString targetName[4] = {"D", "C", "Fe", "Pb"};

// [D, C, Fe, Pb][kinvar]
Double_t omegaMean[4][5];
Double_t omegaSigma[4][5];

Double_t omegaNumber_int[4][5];
Double_t omegaError_int[4][5];

Double_t massEdges[4][5][2];

/*** Declaration of functions ***/

inline void parseCommandLine(int argc, char* argv[]);
void assignOptions();
void printUsage();

void integrateData(TString targetOption);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();

  /*** Read fit results ***/

  for (Int_t targIndex = 0; targIndex < 4; targIndex++) {
    for (Int_t index = 0; index < kinvarNbins; index++) {
      
      TString kinvarAuxSufix = kinvarSufix + Form("%d", index + kinvarConstant);
      
      TString fitFile = fitDir + "/roofit-" + targetName[targIndex] + kinvarAuxSufix + ".dat";
      
      std::cout << "Reading " << fitFile << " ..." << std::endl;
      std::ifstream inFile(fitFile);
      
      TString auxString1, auxString2;
      Int_t l = 0; // line counter
      while (inFile >> auxString1 >> auxString2) {
	l++;
	if (l == 1) { // first line
	  omegaMean[targIndex][index] = auxString1.Atof();
	  std::cout << "  Omega Mean for " << targetName[targIndex] << kinvarAuxSufix << ": " << omegaMean[targIndex][index] << std::endl;
	} else if (l == 2) {
	  omegaSigma[targIndex][index] = auxString1.Atof();
	std::cout << "  Omega Sigma for " << targetName[targIndex] << kinvarAuxSufix << ": " << omegaSigma[targIndex][index] << std::endl;
	}
      }
      inFile.close();

      // assign mass edges!
      massEdges[targIndex][index][0] = omegaMean[targIndex][index] - Nsigma*omegaSigma[targIndex][index];
      massEdges[targIndex][index][1] = omegaMean[targIndex][index] + Nsigma*omegaSigma[targIndex][index];
      std::cout << "  Mass range for " << targetName[targIndex] << kinvarAuxSufix << ": [" << massEdges[targIndex][index][0] << ", " << massEdges[targIndex][index][1] << "]" << std::endl;
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
  if (kinvarOption == "Z" || kinvarOption == "Pt2") {
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
  } else if (kinvarOption == "Q2") {
    // for each bin in kinvar
    for (Int_t cc = 0; cc < kinvarNbins; cc++) {
      DeutElectronN->SetBinContent(cc + 1, electronNumberQ2[0][cc]);
      DeutElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberQ2[0][cc]));
      
      CarbonElectronN->SetBinContent(cc + 1, electronNumberQ2[1][cc]);
      CarbonElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberQ2[1][cc]));
      
      IronElectronN->SetBinContent(cc + 1, electronNumberQ2[2][cc]);
      IronElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberQ2[2][cc]));
      
      LeadElectronN->SetBinContent(cc + 1, electronNumberQ2[3][cc]);
      LeadElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberQ2[3][cc]));
    }
  } else if (kinvarOption == "Nu") { 
    // for each bin in kinvar
    for (Int_t cc = 0; cc < kinvarNbins; cc++) {
      DeutElectronN->SetBinContent(cc + 1, electronNumberNu[0][cc]);
      DeutElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberNu[0][cc]));
      
      CarbonElectronN->SetBinContent(cc + 1, electronNumberNu[1][cc]);
      CarbonElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberNu[1][cc]));
      
      IronElectronN->SetBinContent(cc + 1, electronNumberNu[2][cc]);
      IronElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberNu[2][cc]));
      
      LeadElectronN->SetBinContent(cc + 1, electronNumberNu[3][cc]);
      LeadElectronN->SetBinError(cc + 1, TMath::Sqrt(electronNumberNu[3][cc]));
    }
  }
  
  /*** Integrate data ***/
  
  integrateData("D");
  integrateData("C");
  integrateData("Fe");
  integrateData("Pb");
  
  // creating and filling histograms
  TH1F *DeutOmegaN_int = new TH1F("DeutOmegaN_int", "", kinvarNbins, 0.5, 1.);
  TH1F *CarbonOmegaN_int = new TH1F("CarbonOmegaN_int", "", kinvarNbins, 0.5, 1.);
  TH1F *IronOmegaN_int = new TH1F("IronOmegaN_int", "", kinvarNbins, 0.5, 1.);
  TH1F *LeadOmegaN_int = new TH1F("LeadOmegaN_int", "", kinvarNbins, 0.5, 1.);
    
  // for each bin in kinvar
  for (Int_t cc = 0; cc < kinvarNbins; cc++) {
    DeutOmegaN_int->SetBinContent(cc + 1, omegaNumber_int[0][cc]);
    DeutOmegaN_int->SetBinError(cc + 1, omegaError_int[0][cc]);
    
    CarbonOmegaN_int->SetBinContent(cc + 1, omegaNumber_int[1][cc]);
    CarbonOmegaN_int->SetBinError(cc + 1, omegaError_int[1][cc]);
    
    IronOmegaN_int->SetBinContent(cc + 1, omegaNumber_int[2][cc]);
    IronOmegaN_int->SetBinError(cc + 1, omegaError_int[2][cc]);
        
    LeadOmegaN_int->SetBinContent(cc + 1, omegaNumber_int[3][cc]);
    LeadOmegaN_int->SetBinError(cc + 1, omegaError_int[3][cc]);
  }

  /*** Hadronic Ratios ***/
  
  TH1F *DeutHR = new TH1F("DeutHR", "", kinvarNbins, 0.5, 1.);
  DeutHR->Divide(DeutOmegaN_int, DeutElectronN);
  
  TH1F *CarbonHR = new TH1F("CarbonHR", "", kinvarNbins, 0.5, 1.);
  CarbonHR->Divide(CarbonOmegaN_int, CarbonElectronN);
  
  TH1F *IronHR = new TH1F("IronHR", "", kinvarNbins, 0.5, 1.);
  IronHR->Divide(IronOmegaN_int, IronElectronN);
  
  TH1F *LeadHR = new TH1F("LeadHR", "", kinvarNbins, 0.5, 1.);
  LeadHR->Divide(LeadOmegaN_int, LeadElectronN);

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
  
  CarbonMR_gr->SetTitle("Multiplicity Ratio: #omega - No Bkg Subtraction");
  CarbonMR_gr->GetXaxis()->SetTitle(kinvarTitle);
  CarbonMR_gr->GetXaxis()->CenterTitle();
  CarbonMR_gr->GetXaxis()->SetNdivisions(400 + kinvarNbins, kFALSE);
  CarbonMR_gr->GetXaxis()->SetLimits(kinvarEdges[0], kinvarEdges[kinvarNbins]);
  CarbonMR_gr->GetYaxis()->SetTitle("R_{#omega}");
  CarbonMR_gr->GetYaxis()->CenterTitle();
  CarbonMR_gr->GetYaxis()->SetRangeUser(0., 1.2);
  
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
  
  // legend position
  Double_t legendX = 0.8;
  if (kinvarOption == "Nu") legendX = 0.1;
  
  // legend
  TLegend *legend = new TLegend(legendX, 0.75, legendX+0.1, 0.9); // x1,y1,x2,y2
  legend->AddEntry(CarbonMR_gr, "Carbon", "p");
  legend->AddEntry(IronMR_gr, "Iron", "p");
  legend->AddEntry(LeadMR_gr, "Lead", "p");
  legend->Draw();
  
  c->Print(plotFile); // output file
  
  /*** Save results ***/
  
  std::ofstream outFinalFile(textFile, std::ios::out); // output file
  // first line
  outFinalFile << CarbonMR->GetBinContent(1) << "\t" << CarbonMR->GetBinError(1) << "\t"
	       << IronMR->GetBinContent(1) << "\t" << IronMR->GetBinError(1) << "\t"
	       << LeadMR->GetBinContent(1) << "\t" << LeadMR->GetBinError(1)  << std::endl;
  // second line
  outFinalFile << CarbonMR->GetBinContent(2) << "\t" << CarbonMR->GetBinError(2) << "\t"
	       << IronMR->GetBinContent(2) << "\t" << IronMR->GetBinError(2) << "\t"
	       << LeadMR->GetBinContent(2) << "\t" << LeadMR->GetBinError(2) << std::endl;
  // third line
  outFinalFile << CarbonMR->GetBinContent(3) << "\t" << CarbonMR->GetBinError(3) << "\t"
	       << IronMR->GetBinContent(3) << "\t" << IronMR->GetBinError(3) << "\t"
	       << LeadMR->GetBinContent(3) << "\t" << LeadMR->GetBinError(3) << std::endl;
  // fourth line
  outFinalFile << CarbonMR->GetBinContent(4) << "\t" << CarbonMR->GetBinError(4) << "\t"
	       << IronMR->GetBinContent(4) << "\t" << IronMR->GetBinError(4) << "\t"
	       << LeadMR->GetBinContent(4) << "\t" << LeadMR->GetBinError(4) << std::endl;
  // fifth line
  outFinalFile << CarbonMR->GetBinContent(5) << "\t" << CarbonMR->GetBinError(5) << "\t"
	       << IronMR->GetBinContent(5) << "\t" << IronMR->GetBinError(5) << "\t"
	       << LeadMR->GetBinContent(5) << "\t" << LeadMR->GetBinError(5) << std::endl;
  
  outFinalFile.close();
  std::cout << "File " << textFile << " has been created!" << std::endl;
  
  return 0;
}

/*** Functions ***/

inline void parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeMR-nbs -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hs:k:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 's': Nsigma = atoi(optarg); break;
    case 'k': kinvarOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeMR-nbs -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "MakeMR-nbs program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR-nbs -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR-nbs -k[kinvar]" << std::endl;
  std::cout << "    selects kinvar: Z, Pt2, Q2, Nu" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR-nbs -s[n]" << std::endl;
  std::cout << "    selects range around peak: n*sigma" << std::endl;
  std::cout << "    (default value: n=5)" << std::endl;
}

void assignOptions() {
  // for sigma
  sigmaSufix = Form("-%dsigma", Nsigma);
  // for kinvar
  if (kinvarOption == "Z") {
    kinvarConstant = 3;
    kinvarSufix = "-z";
    kinvarTitle = "Z";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesZ[i];
  } else if (kinvarOption == "Q2") {
    kinvarSufix = "-q";
    kinvarTitle = "Q^{2} (GeV^{2})";    
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesQ2[i];
  } else if (kinvarOption == "Nu") {
    kinvarSufix = "-n";
    kinvarTitle = "#nu (GeV)";    
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesNu[i];
  } else if (kinvarOption == "Pt2") {
    kinvarSufix = "-p";
    kinvarTitle = "p_{T}^{2} (GeV^{2})";    
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesPt2[i];
  }
  // for input
  fitDir = fitDir + "/" + kinvarOption + "/g/b1"; // should update
  // for output files
  plotFile = outDir + "/nbs-MR-" + kinvarOption + sigmaSufix + ".png";
  textFile = outDir + "/nbs-MR-" + kinvarOption + sigmaSufix + ".dat";
}

void integrateData(TString targetOption) {

  TString inputFile1, inputFile2, inputFile3;
  Int_t   targIndex;
  
  TCut cutTargType;
  TCut cutAll = cutPi0 && cutDIS && cutPipPim;
  
  // for targets, unified D
  if (targetOption == "D") {
    inputFile1 = dataDir + "/C/comb_C-thickD2.root";
    inputFile2 = dataDir + "/Fe/comb_Fe-thickD2.root";
    inputFile3 = dataDir + "/Pb/comb_Pb-thinD2.root";
    cutTargType = "TargType == 1";
    targIndex = 0;
    std::cout << "Reading " << inputFile1 << std::endl;
    std::cout << "        " << inputFile2 << std::endl;
    std::cout << "        " << inputFile3 << " ..." << std::endl;
  } else if (targetOption == "C") {
    inputFile1 = dataDir + "/C/comb_C-thickD2.root";
    inputFile2 = "";
    inputFile3 = "";
    cutTargType = "TargType == 2";
    targIndex = 1;
    std::cout << "Reading " << inputFile1 << " ..." << std::endl;
  } else if (targetOption == "Fe") {
    inputFile1 = dataDir + "/Fe/comb_Fe-thickD2.root";
    inputFile2 = "";
    inputFile3 = "";
    cutTargType = "TargType == 2";
    targIndex = 2;
    std::cout << "Reading " << inputFile1 << " ..." << std::endl;
  } else if (targetOption == "Pb") {
    inputFile1 = dataDir + "/Pb/comb_Pb-thinD2.root";
    inputFile2 = "";
    inputFile3 = "";
    cutTargType = "TargType == 2";
    targIndex = 3;
    std::cout << "Reading " << inputFile1 << " ..." << std::endl;
  }

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  for (Int_t index = 0; index < kinvarNbins; index++) {

    TString kinvarAuxSufix = kinvarSufix + Form("%d", index + kinvarConstant);
    
    TCut kinvarCut;
    kinvarCut = Form("%f < ", kinvarEdges[index]) + kinvarOption + " && " + kinvarOption + Form(" < %f", kinvarEdges[index+1]);
    TCut cutMass = Form("%f < wD && wD < %f", massEdges[targIndex][index][0], massEdges[targIndex][index][1]);
    
    TH1F *dataHist;
    treeExtracted->Draw("wD>>data(60, 0.2, 0.5)", cutAll && cutTargType && kinvarCut && cutMass, "goff");
    dataHist = (TH1F *)gROOT->FindObject("data");
    
    // save numbers!
    omegaNumber_int[targIndex][index] = dataHist->IntegralAndError(1, 60, omegaError_int[targIndex][index], "");
    std::cout << "  Omega Number for " << targetOption << kinvarAuxSufix << ": " << omegaNumber_int[targIndex][index] << " +/- " << omegaError_int[targIndex][index] << std::endl;
    
    delete dataHist;
  }
  std::cout << std::endl;

}
