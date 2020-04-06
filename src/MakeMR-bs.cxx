/**************************************/
/* MakeMR-bs.cxx                      */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// From the MakeRooFits results, we obtain different omega and bkg yields
// This program obtains number of omega particles by different methods:
// Only method: obtain the parameter omegaYields directly
// Then, with the ratio of the number of omega particles, obtains MR

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir  = proDir + "/out/MakeMR/bs";
TString textDir = proDir + "/out/MakeRooFits";

TString targetName[4] = {"D", "C", "Fe", "Pb"};

// [D, C, Fe, Pb][Z bin: 3-7]
Int_t particleNumber[4][5];
Int_t particleNumberError[4][5];

/*** Parameters ***/

TString functionOption;
TString functionName = "";
TString functionSufix = "";
TString functionTitle = "";

Int_t flagZ = 0;
Int_t flagQ2 = 0;
Int_t flagNu = 0;
Int_t flagPt2 = 0;

TString kinvarName;
TString kinvarSufix;
TString kinvarValue[6];
Int_t   kinvarConstant = 1;
Int_t   kinvarNbins = 5; // default for all

TString textFile;
TString plotFile;

/*** Declaration of functions ***/

inline void parseCommandLine(int argc, char* argv[]);
void assignOptions();
void printUsage();

void readTextFiles();
void printResults(TH1F *CarbonMR2, TH1F *IronMR2, TH1F *LeadMR2);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  
  readTextFiles();
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  c->SetGridx(1);
  c->SetGridy(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0.5);

  // creating and filling histograms
  TH1F *numberDeutHist = new TH1F("numberDeutHist", "", kinvarNbins, 0.5, 1.);
  TH1F *numberCarbonHist = new TH1F("numberCarbonHist", "", kinvarNbins, 0.5, 1.);
  TH1F *numberIronHist = new TH1F("numberIronHist", "", kinvarNbins, 0.5, 1.);
  TH1F *numberLeadHist = new TH1F("numberLeadHist", "", kinvarNbins, 0.5, 1.);

  numberDeutHist->Sumw2();
  numberCarbonHist->Sumw2(); 
  numberIronHist->Sumw2();
  numberLeadHist->Sumw2();
  
  for (Int_t c = 0; c < kinvarNbins; c++) {
    // D
    numberDeutHist->SetBinContent(c + 1, particleNumber[0][c]);
    numberDeutHist->SetBinError(c + 1, particleNumberError[0][c]);
    // C_C
    numberCarbonHist->SetBinContent(c + 1, particleNumber[1][c]);
    numberCarbonHist->SetBinError(c + 1, particleNumberError[1][c]);
    // Fe_Fe
    numberIronHist->SetBinContent(c + 1, particleNumber[2][c]);
    numberIronHist->SetBinError(c + 1, particleNumberError[2][c]);
    // Pb_Pb
    numberLeadHist->SetBinContent(c + 1, particleNumber[3][c]);
    numberLeadHist->SetBinError(c + 1, particleNumberError[3][c]);
  }
  
  TH1F *CarbonMR = new TH1F("CarbonMR", "", kinvarNbins, 0.5, 1.);
  CarbonMR->SetTitle("#omega MR(" + kinvarName + ") w/ Subtracted Bkg" + functionTitle);
  CarbonMR->GetXaxis()->SetTitle(kinvarName);
  CarbonMR->GetXaxis()->SetNdivisions(200 + kinvarNbins, kFALSE);
  CarbonMR->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,kinvarValue[0]);
  CarbonMR->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,kinvarValue[1]);
  CarbonMR->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,kinvarValue[2]);
  CarbonMR->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,kinvarValue[3]);
  CarbonMR->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,kinvarValue[4]);
  CarbonMR->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,kinvarValue[5]);
  CarbonMR->GetYaxis()->SetTitle("MR");

  CarbonMR->SetMarkerColor(kRed);
  CarbonMR->SetLineColor(kRed);
  CarbonMR->SetLineWidth(3);
  CarbonMR->SetMarkerStyle(21);
  CarbonMR->Divide(numberCarbonHist, numberDeutHist);
  CarbonMR->Scale(4.6194); // electron normalization

  TH1F *IronMR = new TH1F("IronMR", "", kinvarNbins, 0.5, 1.);
  IronMR->SetMarkerColor(kBlue);
  IronMR->SetLineColor(kBlue);
  IronMR->SetLineWidth(3);
  IronMR->SetMarkerStyle(21);
  IronMR->Divide(numberIronHist, numberDeutHist);
  IronMR->Scale(2.3966); // electron normalization

  TH1F *LeadMR = new TH1F("LeadMR", "", kinvarNbins, 0.5, 1.);
  LeadMR->SetMarkerColor(kBlack);
  LeadMR->SetLineColor(kBlack);
  LeadMR->SetLineWidth(3);
  LeadMR->SetMarkerStyle(21);
  LeadMR->Divide(numberLeadHist, numberDeutHist);
  LeadMR->Scale(6.1780); // electron normalization

  // draw already
  CarbonMR->SetAxisRange(0.0, 1.2, "Y"); // range
  CarbonMR->Draw("E1");  
  IronMR->Draw("E1 SAME");
  LeadMR->Draw("E1 SAME");
  
  // legend
  TLegend *legend = new TLegend(0.9, 0.75, 1., 0.9);
  legend->AddEntry(CarbonMR, "Carbon", "pl");
  legend->AddEntry(IronMR, "Iron", "pl");
  legend->AddEntry(LeadMR, "Lead", "pl");
  legend->Draw();

  c->Print(plotFile); // output file

  printResults(CarbonMR, IronMR, LeadMR);

  /*** Saving fit content ***/
  
  std::cout << "Writing " << textFile << " ..." << std::endl;
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

inline void parseCommandLine(int argc, char* argv[]) {
Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeMR-bs -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hF:zqnp")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'z': flagZ = 1; break;
    case 'F': functionOption = optarg; break;
    case 'q': flagQ2 = 1; break;
    case 'n': flagNu = 1; break;
    case 'p': flagPt2 = 1; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeMR-bs -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "MakeMR-bs program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR-bs -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR-bs -[kinvar]" << std::endl;
  std::cout << "    z : Z" << std::endl;
  std::cout << "    q : Q2" << std::endl;
  std::cout << "    n : Nu" << std::endl;
  std::cout << "    p : Pt2" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR-bs -F[g,b,l]" << std::endl;
  std::cout << "    (mandatory when -z)" << std::endl;
  std::cout << "    g  : gaussian" << std::endl;
  std::cout << "    bw : breit-wigner" << std::endl;
  std::cout << "    ln : lognormal" << std::endl;
}

void assignOptions() {
  // kinvarervable option
  if (flagZ) {
    kinvarSufix = "-z";
    kinvarName = "Z";
    kinvarConstant = 3;
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarValue[i] = Form("%.02f", edgesZ[i]);
    // function option
    if (functionOption == "g") {
      functionName = "gaus";
      functionSufix = "";
      functionTitle = " w/ Gaussian";
    } else if (functionOption == "bw") {
      functionName = "bw";
      functionSufix = "bw-";
      functionTitle = " w/ Breit-Wigner";
    } else if (functionOption == "ln") {
      functionName = "ln";
      functionSufix = "ln-";
      functionTitle = " w/ Lognormal";
    }
  } else if (flagQ2) {
    kinvarSufix = "-q";
    kinvarName = "Q2";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarValue[i] = Form("%.02f", edgesQ2[i]);
  } else if (flagNu) {
    kinvarSufix = "-n";
    kinvarName = "Nu";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarValue[i] = Form("%.02f", edgesNu[i]);
  } else if (flagPt2) {
    kinvarSufix = "-p";
    kinvarName = "Pt2";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarValue[i] = Form("%.02f", edgesPt2[i]);
  }
  // input files
  textDir = textDir + "/" + kinvarName;
  // output files
  plotFile = outDir + "/bs-MR" + kinvarSufix + ".png";
  textFile = outDir + "/bs-MR" + kinvarSufix + ".dat";
}

void readTextFiles() {
  
  TString inputFile;
  TString auxKinvarSufix;
  
  for (Int_t tt = 0; tt < 4; tt++) { // target index
    for (Int_t zz = 0; zz < kinvarNbins; zz++) {
      
      auxKinvarSufix = kinvarSufix + Form("%d", zz + kinvarConstant); // crucial
      
      inputFile = textDir + "/roofit-" + targetName[tt] + auxKinvarSufix + ".dat";
      
      std::cout << "Reading " << inputFile << "..." << std::endl;
      std::ifstream inFile(inputFile);
      TString auxString1, auxString2;
      Int_t l = 0; // line counter
      while (inFile >> auxString1 >> auxString2) {
	l++;
	if (l == 3) { // third line
	  particleNumber[tt][zz] = auxString1.Atof();
	  particleNumberError[tt][zz] = auxString2.Atof();
	  std::cout << particleNumber[tt][zz] << "\t" << particleNumberError[tt][zz] << std::endl;
	}
      }
      inFile.close();
    }
  }
}

void printResults(TH1F *CarbonMR2, TH1F *IronMR2, TH1F *LeadMR2) {
  std::cout << std::endl;
  std::cout << "Carbon" << std::endl;
  for (Int_t zp = 0; zp < kinvarNbins; zp++) {
    std::cout << kinvarSufix << (zp+kinvarConstant) << ": "  << CarbonMR2->GetBinContent(zp + 1) << " +/- "  << CarbonMR2->GetBinError(zp + 1) << std::endl;
  }
  
  std::cout << "Iron" << std::endl;
  for (Int_t zpp = 0; zpp < kinvarNbins; zpp++) {
    std::cout << kinvarSufix << (zpp+kinvarConstant) << ": "  << IronMR2->GetBinContent(zpp + 1) << " +/- "  << IronMR2->GetBinError(zpp + 1) << std::endl;
  }

  std::cout << "Lead" << std::endl;
  for (Int_t zppp = 0; zppp < kinvarNbins; zppp++) {
    std::cout << kinvarSufix << (zppp+kinvarConstant) << ": "  << LeadMR2->GetBinContent(zppp + 1) << " +/- "  << LeadMR2->GetBinError(zppp + 1) << std::endl;
  }
  std::cout << std::endl;
}
