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

// parameters
Int_t flagZ = 0;
Int_t flagQ2 = 0;
Int_t flagNu = 0;
Int_t flagPt2 = 0;

Int_t Nsigma = 5; // default
TString sigmaSufix;

// for kinvar
TString  kinvarName;
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
	if (l == 1) { // third line
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
  
  /*** Drawing ***/

  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  c->SetGridx(1);
  c->SetGridy(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  TH1F *CarbonMR = new TH1F("CarbonMR", "", kinvarNbins, 0.5, 1.);
  CarbonMR->Divide(CarbonOmegaN_int, DeutOmegaN_int);
  CarbonMR->Scale(4.6194); // electron normalization
  
  CarbonMR->SetTitle(Form("MR(" + kinvarName + ") - No Bkg Subtraction #omega(%d#sigma)", Nsigma));
  CarbonMR->GetXaxis()->SetTitle(kinvarName);
  CarbonMR->GetXaxis()->SetNdivisions(200 + kinvarNbins, kFALSE);
  CarbonMR->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[0]));
  CarbonMR->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[1]));
  CarbonMR->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[2]));
  CarbonMR->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[3]));
  CarbonMR->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[4]));
  CarbonMR->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[5]));
  CarbonMR->GetYaxis()->SetTitle("MR");
  CarbonMR->SetAxisRange(0., 1.2, "Y"); // range
  
  CarbonMR->SetMarkerColor(kRed);
  CarbonMR->SetLineColor(kRed);
  CarbonMR->SetLineWidth(3);
  CarbonMR->SetMarkerStyle(21);
  
  CarbonMR->Draw("E");  
  
  TH1F *IronMR = new TH1F("IronMR", "", kinvarNbins, 0.5, 1.);
  IronMR->Divide(IronOmegaN_int, DeutOmegaN_int);
  IronMR->Scale(2.3966); // electron normalization

  IronMR->SetMarkerColor(kBlue);
  IronMR->SetLineColor(kBlue);
  IronMR->SetLineWidth(3);
  IronMR->SetMarkerStyle(21);
  
  IronMR->Draw("E SAME");

  TH1F *LeadMR = new TH1F("LeadMR", "", kinvarNbins, 0.5, 1.);
  LeadMR->Divide(LeadOmegaN_int, DeutOmegaN_int);
  LeadMR->Scale(6.1780); // electron normalization

  LeadMR->SetMarkerColor(kBlack);
  LeadMR->SetLineColor(kBlack);
  LeadMR->SetLineWidth(3);
  LeadMR->SetMarkerStyle(21);
  
  LeadMR->Draw("E SAME");
    
  // legend
  TLegend *legend = new TLegend(0.9, 0.75, 1., 0.9);
  legend->AddEntry(CarbonMR, "Carbon", "pl");
  legend->AddEntry(IronMR, "Iron", "pl");
  legend->AddEntry(LeadMR, "Lead", "pl");
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
  while ((c = getopt(argc, argv, "hs:zqnp")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 's': Nsigma = atoi(optarg); break;
    case 'z': flagZ = 1; break;
    case 'q': flagQ2 = 1; break;
    case 'n': flagNu = 1; break;
    case 'p': flagPt2 = 1; break;
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
  std::cout << "./MakeMR-nbs -[kinvar]" << std::endl;
  std::cout << "    (exclusive and mandatory)" << std::endl;
  std::cout << "    z : Z" << std::endl;
  std::cout << "    q : Q2" << std::endl;
  std::cout << "    n : Nu" << std::endl;
  std::cout << "    p : Pt2" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR-nbs -s[n]" << std::endl;
  std::cout << "    selects range around peak: n*sigma" << std::endl;
  std::cout << "    (default value: n=5)" << std::endl;
}

void assignOptions() {
  // for sigma
  sigmaSufix = Form("-%dsigma", Nsigma);
  // for kinvar
  if (flagZ) {
    kinvarName = "Z";
    fitDir = fitDir + "/Z";
    kinvarConstant = 3;
    kinvarSufix = "-z";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesZ[i];
  } else if (flagQ2) {
    kinvarName = "Q2";
    fitDir = fitDir + "/Q2";
    kinvarSufix = "-q";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesQ2[i];
  } else if (flagNu) {
    kinvarName = "Nu";
    fitDir = fitDir + "/Nu";
    kinvarSufix = "-n";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesNu[i];
  } else if (flagPt2) {
    kinvarName = "Pt2";
    fitDir = fitDir + "/Pt2";
    kinvarSufix = "-p";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesPt2[i];
  }
  // for output files
  plotFile = outDir + "/nbs-MR-" + kinvarName + sigmaSufix + ".png";
  textFile = outDir + "/nbs-MR-" + kinvarName + sigmaSufix + ".dat";
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
    kinvarCut = Form("%f < ", kinvarEdges[index]) + kinvarName + " && " + kinvarName + Form(" < %f", kinvarEdges[index+1]);
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
