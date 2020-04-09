/**************************************/
/* SysPi0Diff.cxx                     */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

/*** TASK 4 for Analysis Note ***/

// This program corresponds to an extensive systematics studiy on Pi0 mass
// for each of these MR cases: bs, nbs 3w, nbs 4w, nbs 5w
// we want to plot the max % by changing their pi0 cut (from 3-5sigma)

#include "analysisConfig.h"

/*** Global variables ***/

TString inputDir = proDir + "/out/SystPi0";
TString outDir = inputDir;

// options
Int_t bsFlag = 1;
Int_t omegaN;

TString inputSufix;
TString inputFile_0;
TString inputFile_1;
TString inputFile_2;
TString inputFile_3;
TString inputFile_4;

Double_t MR_a[3][5];
Double_t MR_aE[3][5];

Double_t MR_b[3][5];
Double_t MR_bE[3][5];

Double_t max_diff[5];

// names
TString plotFile;
TString histTitle;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void assignOptions();
void printUsage();

void readTextFiles(TString inputFile_a, TString inputFile_b);

void fillHistograms(Int_t index);
void obtainMaxDiff(TH1F *CarbonDiff2, TH1F *IronDiff2, TH1F *LeadDiff2, Int_t index2);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  
  readTextFiles(inputFile_0, inputFile_0);
  fillHistograms(0);
  
  readTextFiles(inputFile_0, inputFile_1);
  fillHistograms(1);
  
  readTextFiles(inputFile_0, inputFile_2);
  fillHistograms(2);
  
  readTextFiles(inputFile_0, inputFile_3);
  fillHistograms(3);
    
  readTextFiles(inputFile_0, inputFile_4);
  fillHistograms(4);

  /*** Filling histograms ***/

  TH1F *maxDiffHist = new TH1F("maxDiffHist", "", 5, 0.5, 1.);
  
  for (Int_t i = 0; i < 5; i++) {
    std::cout << "max_diff[" << i << "]=" << max_diff[i] << std::endl; // debug
    maxDiffHist->SetBinContent(i+1, max_diff[i]);
  }
  std::cout << std::endl;

  /*** Drawing ***/
   
  TCanvas *ca = new TCanvas("ca", "ca", 1000, 1000);
  ca->SetGridx(0);
  ca->SetGridy(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  maxDiffHist->SetTitle("Progression of max difference in " + histTitle);
  maxDiffHist->GetXaxis()->SetTitle("#sigma");
  maxDiffHist->GetXaxis()->CenterTitle();
  maxDiffHist->GetXaxis()->SetNdivisions(208, kTRUE);
  maxDiffHist->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"3");
  maxDiffHist->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"3.5");
  maxDiffHist->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"4");
  maxDiffHist->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"4.5");
  maxDiffHist->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"5");
  maxDiffHist->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"5.5");
  maxDiffHist->GetYaxis()->SetTitle("diff in %");
  maxDiffHist->GetYaxis()->CenterTitle();
  
  // "special" colors for a
  maxDiffHist->SetFillColor(kOrange+10);
  
  maxDiffHist->SetAxisRange(0, 30, "Y"); // range

  maxDiffHist->Draw("B");

  ca->Print(plotFile);
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./SystPi0Diff -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hbw:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'b': bsFlag = 1; break;
    case 'w': omegaN = atoi(optarg); bsFlag = 0; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./SystPi0Diff -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "SystPi0Diff program. Usage is:" << std::endl;
  std::cout << "./SystPi0Diff -[options] -[more options]" << std::endl;
  std::cout << "  h         : prints help and exit program" << std::endl;
  std::cout << "  b         : compare all 5 results for bs MR" << std::endl;
  std::cout << "  w[int]    : compare all 5 results for nbs [int]w" << std::endl;
}

void assignOptions() {
  // first case
  if (bsFlag) {
    inputDir = inputDir + "/Z";
    inputFile_0 = inputDir + "/3.0sigma/bs-MR-Z.dat";
    inputFile_1 = inputDir + "/3.5sigma/bs-MR-Z.dat";
    inputFile_2 = inputDir + "/4.0sigma/bs-MR-Z.dat";
    inputFile_3 = inputDir + "/4.5sigma/bs-MR-Z.dat";
    inputFile_4 = inputDir + "/5.0sigma/bs-MR-Z.dat";
    histTitle = "BS #omega MR(Z)";
    plotFile = inputDir + "/bs-diff.png";
  } else {
    inputDir = inputDir + "/Z";
    inputSufix = Form("-%dw", omegaN);
    inputFile_0 = inputDir + "/3.0sigma/nbs-MR-Z" + inputSufix + ".dat";
    inputFile_1 = inputDir + "/3.5sigma/nbs-MR-Z" + inputSufix + ".dat";
    inputFile_2 = inputDir + "/4.0sigma/nbs-MR-Z" + inputSufix + ".dat";
    inputFile_3 = inputDir + "/4.5sigma/nbs-MR-Z" + inputSufix + ".dat";
    inputFile_4 = inputDir + "/5.0sigma/nbs-MR-Z" + inputSufix + ".dat";
    plotFile = inputDir + "/nbs" + inputSufix + "-diff.png";
    histTitle = Form("%d", omegaN);
    histTitle = "NBS #omega(" + histTitle + "#sigma) MR(Z)";
  }
}

void readTextFiles(TString inputFile_a, TString inputFile_b) {
    
  // fill MR_a
  std::cout << "Reading " << inputFile_a << "..." << std::endl;
  std::ifstream inFile_a(inputFile_a);

  TString auxString1, auxString2, auxString3, auxString4, auxString5, auxString6;
  Int_t l = 0; // line counter
  while (inFile_a >> auxString1 >> auxString2 >> auxString3 >> auxString4 >> auxString5 >> auxString6) {
    MR_a[0][l] = auxString1.Atof();
    MR_aE[0][l] = auxString2.Atof();
    MR_a[1][l] = auxString3.Atof();
    MR_aE[1][l] = auxString4.Atof();
    MR_a[2][l] = auxString5.Atof();
    MR_aE[2][l] = auxString6.Atof();
    std::cout << auxString1 << " " << auxString2 << " " << auxString3 << " " << auxString4 << " " << auxString5 << " " << auxString6 << std::endl;
    l++;
  }
  inFile_a.close();

  // fill MR_b
  std::cout << "Reading " << inputFile_b << "..." << std::endl;  
  std::ifstream inFile_b(inputFile_b);
  
  l = 0; // reset line counter
  while (inFile_b >> auxString1 >> auxString2 >> auxString3 >> auxString4 >> auxString5 >> auxString6) {
    MR_b[0][l] = auxString1.Atof();
    MR_bE[0][l] = auxString2.Atof();
    MR_b[1][l] = auxString3.Atof();
    MR_bE[1][l] = auxString4.Atof();
    MR_b[2][l] = auxString5.Atof();
    MR_bE[2][l] = auxString6.Atof();
    std::cout << auxString1 << " " << auxString2 << " " << auxString3 << " " << auxString4 << " " << auxString5 << " " << auxString6 << std::endl;
    l++;
  }
  inFile_b.close();
}

void fillHistograms(Int_t index) {

  // creating and filling histograms
  TH1F *CarbonMR_a = new TH1F("CarbonMR_a", "", 5, 0.5, 1.);
  TH1F *IronMR_a = new TH1F("IronMR_a", "", 5, 0.5, 1.);
  TH1F *LeadMR_a = new TH1F("LeadMR_a", "", 5, 0.5, 1.);
  
  TH1F *CarbonMR_b = new TH1F("CarbonMR_b", "", 5, 0.5, 1.);
  TH1F *IronMR_b = new TH1F("IronMR_b", "", 5, 0.5, 1.);
  TH1F *LeadMR_b = new TH1F("LeadMR_b", "", 5, 0.5, 1.);
  
  for (Int_t i = 0; i < 5; i++) {
    // a
    CarbonMR_a->SetBinContent(i+1, MR_a[0][i]);
    CarbonMR_a->SetBinError(i+1, MR_aE[0][i]);
    IronMR_a->SetBinContent(i+1, MR_a[1][i]);
    IronMR_a->SetBinError(i+1, MR_aE[1][i]);
    LeadMR_a->SetBinContent(i+1, MR_a[2][i]);
    LeadMR_a->SetBinError(i+1, MR_aE[2][i]);
    
    // b
    CarbonMR_b->SetBinContent(i+1, MR_b[0][i]);
    CarbonMR_b->SetBinError(i+1, MR_bE[0][i]);
    IronMR_b->SetBinContent(i+1, MR_b[1][i]);
    IronMR_b->SetBinError(i+1, MR_bE[1][i]);
    LeadMR_b->SetBinContent(i+1, MR_b[2][i]);
    LeadMR_b->SetBinError(i+1, MR_bE[2][i]);
  }
  
  // obtain differences
  TH1F *CarbonMRdiff = new TH1F("CarbonMRdiff", "", 5, 0.5, 1.);
  CarbonMRdiff->Add(CarbonMR_a, CarbonMR_b, 1, -1);
  CarbonMRdiff->Divide(CarbonMR_a);
  CarbonMRdiff->Scale(100);
  
  TH1F *IronMRdiff = new TH1F("IronMRdiff", "", 5, 0.5, 1.);
  IronMRdiff->Add(IronMR_a, IronMR_b, 1, -1);
  IronMRdiff->Divide(IronMR_a);
  IronMRdiff->Scale(100);
    
  TH1F *LeadMRdiff = new TH1F("LeadMRdiff", "", 5, 0.5, 1.);
  LeadMRdiff->Add(LeadMR_a, LeadMR_b, 1, -1);
  LeadMRdiff->Divide(LeadMR_a);
  LeadMRdiff->Scale(100);

  // obtain and save max diff
  obtainMaxDiff(CarbonMRdiff, IronMRdiff, LeadMRdiff, index);

  delete CarbonMR_a;
  delete IronMR_a;
  delete LeadMR_a;

  delete CarbonMR_b;
  delete IronMR_b;
  delete LeadMR_b;
  
  delete CarbonMRdiff;
  delete IronMRdiff;
  delete LeadMRdiff;
}

void obtainMaxDiff(TH1F *CarbonDiff2, TH1F *IronDiff2, TH1F *LeadDiff2, Int_t index2) {

  Double_t this_diff;
  max_diff[index2] = 0;

  // Carbon
  for (Int_t zp = 0; zp < 5; zp++) {
    this_diff = TMath::Abs(CarbonDiff2->GetBinContent(zp + 1));
    if (this_diff > max_diff[index2]) {
      max_diff[index2] = this_diff;
    }
  }

  // Iron
  for (Int_t zpp = 0; zpp < 5; zpp++) {
    this_diff = TMath::Abs(IronDiff2->GetBinContent(zpp + 1));
    if (this_diff > max_diff[index2]) {
      max_diff[index2] = this_diff;
    }	
  }
  
  // Lead
  for (Int_t zppp = 0; zppp < 5; zppp++) {
    this_diff = TMath::Abs(LeadDiff2->GetBinContent(zppp + 1));
    if (this_diff > max_diff[index2]) {
      max_diff[index2] = this_diff;
    }
  }

  std::cout << "max_found: "  << max_diff[index2] << std::endl;
  std::cout << std::endl;
}
