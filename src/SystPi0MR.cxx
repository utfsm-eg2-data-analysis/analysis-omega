/**************************************/
/* SystPi0Mass.cxx                    */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

/*** TASK 4 for Analysis Note ***/

// This program corresponds to systematics studies on Pi0 mass
// 1. defines five propto. sigma cuts {3sigma, 3.5sigma, 4sigma, 4.5sigma, 5sigma}
// 2. does nbs-MR(kinvar) and bs-MR(kinvar) from the previous cuts

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/SystPi0";
TString textDir;

TString inputFile1 = "";
TString inputFile2 = "";
TString inputFile3 = "";

// results obtained previously by this same program
Double_t obtMean  = 0.131;
Double_t obtSigma = 0.024;
Double_t pi0LowEdge;
Double_t pi0HighEdge;
TString  pi0Nsufix;

// main options
Int_t    bsFlag = 1;
TString  kinvarOption;
Double_t pi0N;
Int_t    omegaN = 3; // by default

// cuts
TCut cutAll;
TCut cutKinVar;
TCut cutTargType = "";
TCut cutOmega;

// kinvar options
Int_t    kinvarNbins = 5;
Double_t kinvarValue[6];
TString  kinvarSufix;
TString  kinvarMRSufix;
Int_t    kinvarConstant = 1; // default for (Q2, Nu, Pt2)

// MR-related
Double_t particleNumber[4][5];
Double_t particleError[4][5];

// names stuff
TString outPrefix;
TString plotFile;
TString textFile;

TString  omegaNsufix;

// new!
TString targetName[4] = {"D", "C", "Fe", "Pb"};
Double_t omegaMean[4][5];
Double_t omegaSigma[4][5];
Double_t massEdges[4][5][2];

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

void fitOmegaPeak();
void integrateData(TString targetOption);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  /*** Read fit results ***/
    
  for (Int_t targIndex = 0; targIndex < 4; targIndex++) {
    for (Int_t index = 0; index < 5; index++) {

      TString kinvarAuxSufix = kinvarSufix + Form("%d", index + kinvarConstant);
      TString fitFile = textDir + "/pi0fit-" + targetName[targIndex] + kinvarAuxSufix + ".dat";

      std::cout << "Reading file " << fitFile << std::endl;
      std::ifstream inFile(fitFile);
      
      TString auxString1, auxString2;
      Int_t l = 0; // line counter
      while (inFile >> auxString1 >> auxString2) {
	l++;
	if (l == 1) { // first line
	  omegaMean[targIndex][index] = auxString1.Atof();
	  std::cout << "Omega Mean for " << targetName[targIndex] << kinvarAuxSufix << ": " << omegaMean[targIndex][index] << std::endl;
	} else if (l == 2) { // second line
	  omegaSigma[targIndex][index] = auxString1.Atof();
	  std::cout << "Omega Sigma for " << targetName[targIndex] << kinvarAuxSufix << ": " << omegaSigma[targIndex][index] << std::endl;
	} else if (l == 3) { // third line
	  particleNumber[targIndex][index] = auxString1.Atof();
	  particleError[targIndex][index] = auxString2.Atof();
	  std::cout << "Omega Number for " << targetName[targIndex] << kinvarAuxSufix << ": " << particleNumber[targIndex][index]
		    << " +/- " << particleError[targIndex][index] << std::endl;
	}
      }
      inFile.close();
      
      // assign mass edges for nbs
      massEdges[targIndex][index][0] = omegaMean[targIndex][index] - omegaN*omegaSigma[targIndex][index];
      massEdges[targIndex][index][1] = omegaMean[targIndex][index] + omegaN*omegaSigma[targIndex][index];
      std::cout << "Mass edges for " << targetName[targIndex] << kinvarAuxSufix << ": [" << massEdges[targIndex][index][0] << ", " << massEdges[targIndex][index][1] << "]" << std::endl; 
    }
  }

  // define cuts, the most important part of this program
  pi0LowEdge = obtMean - pi0N*obtSigma;
  pi0HighEdge = obtMean + pi0N*obtSigma;
  cutPi0 = Form("%f < pi0M && pi0M < %f", pi0LowEdge, pi0HighEdge); // overwrite!
  
  /*** Integrate data ***/
  // it overwrites the particleNumber and particleError arrays for the nbs case
  
  if (!bsFlag) {
    integrateData("D");
    integrateData("C");
    integrateData("Fe");
    integrateData("Pb");
  }
  
  // define canvas
  TCanvas *c = new TCanvas("c", "c", 1000, 1000); 
  c->SetGrid();
  
  gStyle->SetOptStat(0);
    
  // creating and filling histograms
  TH1F *numberDeutHist = new TH1F("numberDeutHist", "", kinvarNbins, 0.5, 1.);
  TH1F *numberCarbonHist = new TH1F("numberCarbonHist", "", kinvarNbins, 0.5, 1.);
  TH1F *numberIronHist = new TH1F("numberIronHist", "", kinvarNbins, 0.5, 1.);
  TH1F *numberLeadHist = new TH1F("numberLeadHist", "", kinvarNbins, 0.5, 1.);
    
  // for each bin in kinvar
  for (Int_t cc = 0; cc < kinvarNbins; cc++) {
    numberDeutHist->SetBinContent(cc + 1, particleNumber[0][cc]);
    numberDeutHist->SetBinError(cc + 1, particleError[0][cc]);
    
    numberCarbonHist->SetBinContent(cc + 1, particleNumber[1][cc]);
    numberCarbonHist->SetBinError(cc + 1, particleError[1][cc]);
    
    numberIronHist->SetBinContent(cc + 1, particleNumber[2][cc]);
    numberIronHist->SetBinError(cc + 1, particleError[2][cc]);
        
    numberLeadHist->SetBinContent(cc + 1, particleNumber[3][cc]);
    numberLeadHist->SetBinError(cc + 1, particleError[3][cc]);
  }
    
  TH1F *CarbonMR = new TH1F("CarbonMR", "", kinvarNbins, 0.5, 1.);
  CarbonMR->SetTitle("#omega NBS MR(" + kinvarOption + ")");
  CarbonMR->GetXaxis()->SetTitle(kinvarOption);
  CarbonMR->GetXaxis()->SetNdivisions(200 + kinvarNbins, kFALSE);
  CarbonMR->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,Form("%.02f", kinvarValue[0]));
  CarbonMR->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,Form("%.02f", kinvarValue[1]));
  CarbonMR->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,Form("%.02f", kinvarValue[2]));
  CarbonMR->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,Form("%.02f", kinvarValue[3]));
  CarbonMR->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,Form("%.02f", kinvarValue[4]));
  CarbonMR->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,Form("%.02f", kinvarValue[5]));
  CarbonMR->GetYaxis()->SetTitle("MR");

  CarbonMR->SetMarkerColor(kRed);
  CarbonMR->SetLineColor(kRed);
  CarbonMR->SetLineWidth(3);
  CarbonMR->SetMarkerStyle(21);
  CarbonMR->Divide(numberCarbonHist, numberDeutHist);
  CarbonMR->Scale(4.6194); // electron normalization, uniD
  
  CarbonMR->SetAxisRange(0., 1.2, "Y"); // range
  CarbonMR->Draw("E");  
  
  TH1F *IronMR = new TH1F("IronMR", "", kinvarNbins, 0.5, 1.);
  IronMR->SetMarkerColor(kBlue);
  IronMR->SetLineColor(kBlue);
  IronMR->SetLineWidth(3);
  IronMR->SetMarkerStyle(21);
  IronMR->Divide(numberIronHist, numberDeutHist);
  IronMR->Scale(2.3966); // electron normalization, uniD
  
  IronMR->Draw("E SAME");

  TH1F *LeadMR = new TH1F("LeadMR", "", kinvarNbins, 0.5, 1.);
  LeadMR->SetMarkerColor(kBlack);
  LeadMR->SetLineColor(kBlack);
  LeadMR->SetLineWidth(3);
  LeadMR->SetMarkerStyle(21);
  LeadMR->Divide(numberLeadHist, numberDeutHist);
  LeadMR->Scale(6.1780); // electron normalization, uniD
  
  LeadMR->Draw("E SAME");
    
  // legend
  TLegend *legend = new TLegend(0.9, 0.75, 1., 0.9);
  legend->AddEntry(CarbonMR, "Carbon", "pl");
  legend->AddEntry(IronMR, "Iron", "pl");
  legend->AddEntry(LeadMR, "Lead", "pl");
  legend->Draw();

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

  // save plot
  c->Print(plotFile); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./SystPi0MR -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hk:i:w:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'k': kinvarOption = optarg; break;
    case 'i': pi0N = atof(optarg); break;
    case 'w': omegaN = atoi(optarg); bsFlag = 0; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./SystPi0MR -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << std::endl;
  std::cout << "Executing SystPi0MR program. Parameters chosen are:" << std::endl;
  std::cout << "  kinvarOption = " << kinvarOption << std::endl;
  std::cout << "  pi0N         = " << pi0N << std::endl;
  std::cout << "  omegaN       = " << omegaN << std::endl;
  std::cout << "  bsFlag       = " << bsFlag << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << std::endl;
  std::cout << "SystPi0MR program. Usage is:" << std::endl;
  std::cout << "./SystPi0MR -[options] -[more options]" << std::endl;
  std::cout << "  h         : prints usage and exit program" << std::endl;
  std::cout << "  k[kinvar] : selects kinvar: Z, Pt2, Nu, Q2" << std::endl;
  std::cout << "  i[double] : with [3-5]*sigma cut around pi0 peak" << std::endl;
  std::cout << "  w[int]    : with [3,4,5]*sigma cut around omega peak (enables nbs!)" << std::endl;  
  std::cout << std::endl;
}

void assignOptions() {
  // for kinvar
  if (kinvarOption == "Z") {
    kinvarConstant = 3;
    kinvarSufix = "-z";
    kinvarMRSufix = "-Z";
    for (Int_t z = 0; z <= kinvarNbins; z++) kinvarValue[z] = edgesZ[z];
  } else if (kinvarOption == "Q2") {
    kinvarSufix = "-q";
    kinvarMRSufix = "-Q2";
    for (Int_t q = 0; q <= kinvarNbins; q++) kinvarValue[q] = edgesQ2[q];
  } else if (kinvarOption == "Nu") {
    kinvarSufix = "-n";
    kinvarMRSufix = "-Nu";
    for (Int_t n = 0; n <= kinvarNbins; n++) kinvarValue[n] = edgesNu[n];
  } else if (kinvarOption == "Pt2") {
    kinvarSufix = "-p";
    kinvarMRSufix = "-Pt2";
    for (Int_t p = 0; p <= kinvarNbins; p++) kinvarValue[p] = edgesPt2[p];
  }
  outDir = outDir + "/" + kinvarOption;
  // for Nsigma
  omegaNsufix = Form("-%dw", omegaN);
  pi0Nsufix = Form("%.01f", pi0N);
  outDir = outDir + "/" + pi0Nsufix + "sigma";
  textDir = outDir;
  // for MR option
  if (bsFlag) outPrefix = "bs-MR" + kinvarMRSufix;
  else outPrefix = "nbs-MR" + kinvarMRSufix + omegaNsufix;
  // output name
  textFile = outDir + "/" + outPrefix + ".dat";
  plotFile = outDir + "/" + outPrefix + ".png";
}

void integrateData(TString targetOption) {
  // for targets
  Int_t targIndex;
  if (targetOption == "D") {
    cutTargType = "TargType == 1";
    inputFile1 = dataDir + "/C/comb_C-thickD2.root";
    inputFile2 = dataDir + "/Fe/comb_Fe-thickD2.root";
    inputFile3 = dataDir + "/Pb/comb_Pb-thinD2.root";
    targIndex = 0;
  } else if (targetOption == "C") {
    cutTargType = "TargType == 2";
    inputFile1 = dataDir + "/C/comb_C-thickD2.root";
    inputFile2 = "";
    inputFile3 = "";
    targIndex = 1;
  } else if (targetOption == "Fe") {
    cutTargType = "TargType == 2";
    inputFile1 = dataDir + "/Fe/comb_Fe-thickD2.root";
    inputFile2 = "";
    inputFile3 = "";
    targIndex = 2;
  } else if (targetOption == "Pb") {
    cutTargType = "TargType == 2";
    inputFile1 = dataDir + "/Pb/comb_Pb-thinD2.root";
    inputFile2 = "";
    inputFile3 = "";
    targIndex = 3;
  }
  
  // extract data
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  for (Int_t index = 0; index < kinvarNbins; index++) {
    
    // define kinvar cut
    cutKinVar = Form("%f < ", kinvarValue[index]) + kinvarOption + " && " + kinvarOption + Form(" < %f", kinvarValue[index+1]);
    
    // define omega cut
    cutOmega = Form("%f < wD && wD < %f", massEdges[targIndex][index][0], massEdges[targIndex][index][1]);
    
    // draw hist
    TH1F *integratedHist; // x-bin width = 5 MeV
    treeExtracted->Draw("wD>>data(52, 0.24, 0.5)", cutTargType && cutDIS && cutPipPim && cutPi0 && cutKinVar && cutOmega, "goff"); // with cut around omega
    integratedHist = (TH1F *)gROOT->FindObject("data");

    // integrate!
    particleNumber[targIndex][index] = integratedHist->IntegralAndError(1, 52, particleError[targIndex][index], "");
    
    // print them
    TString kinvarAuxSufix;
    kinvarAuxSufix = kinvarSufix + Form("%d", index + kinvarConstant);
    
    std::cout << "nbs-" << targetOption << kinvarAuxSufix << " = " << particleNumber[targIndex][index] << " +/- " << particleError[targIndex][index] << std::endl;
  }
}
