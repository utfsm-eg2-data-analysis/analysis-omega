/**************************************/
/* MakeMR-bs.cxx                      */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// Background Subtracted MR
// --method 1: calculate MR directly from omega number parameter of MakeRooFits
// --method 2: calculate NBS MR but subtracts the bkg number parameter of MakeRooFits
// updated: to new makeroofits directory scheme

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/MakeMR/bs";
TString fitDir = proDir + "/out/MakeRooFits";

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

Double_t omegaNumber_int[4][5];
Double_t omegaError_int[4][5];

Double_t bkgNumber[4][5];
Double_t bkgError[4][5];

Double_t massEdges[4][5][2];

// on kinvar
TString  kinvarSufix;
Int_t    kinvarConstant = 1; // default for all, except Z
Int_t    kinvarNbins = 5;    // default for all -> HARDCODED!
Double_t kinvarEdges[6];

TString targetName[4] = {"D", "C", "Fe", "Pb"};

TString textFile;
TString plotFile;

// new
TString functionSufix;
TString functionDir;
TString bkgSufix;
TString bkgDir;

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

      // assign mass edges!
      massEdges[targIndex][index][0] = omegaMean[targIndex][index] - 5*omegaSigma[targIndex][index];
      massEdges[targIndex][index][1] = omegaMean[targIndex][index] + 5*omegaSigma[targIndex][index];
      std::cout << "  Mass range for " << targetName[targIndex] << kinvarAuxSufix << ": [" << massEdges[targIndex][index][0] << ", " << massEdges[targIndex][index][1] << "]" << std::endl;
      std::cout << std::endl;
    }
  }

  /*** Start Method 1 ***/
  
  if (Nmethod == 1) {

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

    // drawing
    TCanvas *c = new TCanvas("c", "c", 1000, 1000);
    c->SetGridx(1);
    c->SetGridy(1);
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);
  
    TH1F *CarbonMR = new TH1F("CarbonMR", "", kinvarNbins, 0.5, 1.);
    CarbonMR->Divide(CarbonOmegaN_fit, DeutOmegaN_fit);
    CarbonMR->Scale(4.6194); // electron normalization

    CarbonMR->SetTitle("#omega MR(" + kinvarOption + ") - Subtracted Bkg");
    CarbonMR->GetXaxis()->SetTitle(kinvarOption);
    CarbonMR->GetXaxis()->SetNdivisions(200 + kinvarNbins, kFALSE);
    for (Int_t i = 0; i < (kinvarNbins+1); i++) CarbonMR->GetXaxis()->ChangeLabel(i+1,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[i]));
    CarbonMR->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[kinvarNbins]));
    CarbonMR->GetYaxis()->SetTitle("MR");
    CarbonMR->SetAxisRange(0.0, 1.2, "Y"); // range
  
    CarbonMR->SetMarkerColor(kRed);
    CarbonMR->SetLineColor(kRed);
    CarbonMR->SetLineWidth(3);
    CarbonMR->SetMarkerStyle(21);

    CarbonMR->Draw("E1");

    TH1F *IronMR = new TH1F("IronMR", "", kinvarNbins, 0.5, 1.);
    IronMR->Divide(IronOmegaN_fit, DeutOmegaN_fit);
    IronMR->Scale(2.3966); // electron normalization
  
    IronMR->SetMarkerColor(kBlue);
    IronMR->SetLineColor(kBlue);
    IronMR->SetLineWidth(3);
    IronMR->SetMarkerStyle(21);

    IronMR->Draw("E1 SAME");
  
    TH1F *LeadMR = new TH1F("LeadMR", "", kinvarNbins, 0.5, 1.);
    LeadMR->Divide(LeadOmegaN_fit, DeutOmegaN_fit);
    LeadMR->Scale(6.1780); // electron normalization

    LeadMR->SetMarkerColor(kBlack);
    LeadMR->SetLineColor(kBlack);
    LeadMR->SetLineWidth(3);
    LeadMR->SetMarkerStyle(21);
  
    LeadMR->Draw("E1 SAME");
  
    // legend
    TLegend *legend = new TLegend(0.9, 0.75, 1., 0.9);
    legend->AddEntry(CarbonMR, "Carbon", "pl");
    legend->AddEntry(IronMR, "Iron", "pl");
    legend->AddEntry(LeadMR, "Lead", "pl");
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
    std::cout << "File " << textFile << " has been created!" << std::endl;    
    
  } else if (Nmethod == 2) {

    // integrate data, duh
    integrateData("D");
    integrateData("C");
    integrateData("Fe");
    integrateData("Pb");

    // creating and filling histograms
    TH1F *DeutOmegaN_int = new TH1F("DeutOmegaN_int", "", kinvarNbins, 0.5, 1.);
    TH1F *CarbonOmegaN_int = new TH1F("CarbonOmegaN_int", "", kinvarNbins, 0.5, 1.);
    TH1F *IronOmegaN_int = new TH1F("IronOmegaN_int", "", kinvarNbins, 0.5, 1.);
    TH1F *LeadOmegaN_int = new TH1F("LeadOmegaN_int", "", kinvarNbins, 0.5, 1.);
    
    TH1F *DeutBkgN = new TH1F("DeutBkgN", "", kinvarNbins, 0.5, 1.);
    TH1F *CarbonBkgN = new TH1F("CarbonBkgN", "", kinvarNbins, 0.5, 1.);
    TH1F *IronBkgN = new TH1F("IronBkgN", "", kinvarNbins, 0.5, 1.);
    TH1F *LeadBkgN = new TH1F("LeadBkgN", "", kinvarNbins, 0.5, 1.);
    
    // for each bin in kinvar
    for (Int_t cc = 0; cc < kinvarNbins; cc++) {

      // omega
      DeutOmegaN_int->SetBinContent(cc + 1, omegaNumber_int[0][cc]);
      DeutOmegaN_int->SetBinError(cc + 1, omegaError_int[0][cc]);
      CarbonOmegaN_int->SetBinContent(cc + 1, omegaNumber_int[1][cc]);
      CarbonOmegaN_int->SetBinError(cc + 1, omegaError_int[1][cc]);
      IronOmegaN_int->SetBinContent(cc + 1, omegaNumber_int[2][cc]);
      IronOmegaN_int->SetBinError(cc + 1, omegaError_int[2][cc]);
      LeadOmegaN_int->SetBinContent(cc + 1, omegaNumber_int[3][cc]);
      LeadOmegaN_int->SetBinError(cc + 1, omegaError_int[3][cc]);

      // bkg
      DeutBkgN->SetBinContent(cc + 1, bkgNumber[0][cc]);
      DeutBkgN->SetBinError(cc + 1, bkgError[0][cc]);
      CarbonBkgN->SetBinContent(cc + 1, bkgNumber[1][cc]);
      CarbonBkgN->SetBinError(cc + 1, bkgError[1][cc]);
      IronBkgN->SetBinContent(cc + 1, bkgNumber[2][cc]);
      IronBkgN->SetBinError(cc + 1, bkgError[2][cc]);
      LeadBkgN->SetBinContent(cc + 1, bkgNumber[3][cc]);
      LeadBkgN->SetBinError(cc + 1, bkgError[3][cc]);
    }

    // subtract!
    TH1F *DeutOmegaN_corr = new TH1F("DeutOmegaN_corr", "", kinvarNbins, 0.5, 1.);
    DeutOmegaN_corr->Add(DeutOmegaN_int, DeutBkgN, 1, -1);
    for (Int_t p = 1; p <= kinvarNbins; p++) std::cout << DeutOmegaN_corr->GetBinContent(p) << " +/- " << DeutOmegaN_corr->GetBinError(p) << std::endl; // debug
    
    TH1F *CarbonOmegaN_corr = new TH1F("CarbonOmegaN_corr", "", kinvarNbins, 0.5, 1.);
    CarbonOmegaN_corr->Add(CarbonOmegaN_int, CarbonBkgN, 1, -1);
    for (Int_t p = 1; p <= kinvarNbins; p++) std::cout << CarbonOmegaN_corr->GetBinContent(p) << " +/- " << CarbonOmegaN_corr->GetBinError(p) << std::endl; // debug
    
    TH1F *IronOmegaN_corr = new TH1F("IronOmegaN_corr", "", kinvarNbins, 0.5, 1.);
    IronOmegaN_corr->Add(IronOmegaN_int, IronBkgN, 1, -1);

    TH1F *LeadOmegaN_corr = new TH1F("LeadOmegaN_corr", "", kinvarNbins, 0.5, 1.);
    LeadOmegaN_corr->Add(LeadOmegaN_int, LeadBkgN, 1, -1);
    
    // drawing
    TCanvas *c2 = new TCanvas("c2", "c2", 1000, 1000);
    c2->SetGridx(1);
    c2->SetGridy(1);
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);
  
    TH1F *CarbonMR_m2 = new TH1F("CarbonMR_m2", "", kinvarNbins, 0.5, 1.);
    CarbonMR_m2->Divide(CarbonOmegaN_corr, DeutOmegaN_corr);
    CarbonMR_m2->Scale(4.6194); // electron normalization

    CarbonMR_m2->SetTitle("#omega MR(" + kinvarOption + ") - Subtracted Bkg (Method 2)");
    CarbonMR_m2->GetXaxis()->SetTitle(kinvarOption);
    CarbonMR_m2->GetXaxis()->SetNdivisions(200 + kinvarNbins, kFALSE);
    CarbonMR_m2->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[0]));
    CarbonMR_m2->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[1]));
    CarbonMR_m2->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[2]));
    CarbonMR_m2->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[3]));
    CarbonMR_m2->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[4]));
    CarbonMR_m2->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[5]));
    CarbonMR_m2->GetYaxis()->SetTitle("MR");
    CarbonMR_m2->SetAxisRange(0., 1.2, "Y"); // range
  
    CarbonMR_m2->SetMarkerColor(kRed);
    CarbonMR_m2->SetLineColor(kRed);
    CarbonMR_m2->SetLineWidth(3);
    CarbonMR_m2->SetMarkerStyle(21);

    CarbonMR_m2->Draw("E1");

    TH1F *IronMR_m2 = new TH1F("IronMR_m2", "", kinvarNbins, 0.5, 1.);
    IronMR_m2->Divide(IronOmegaN_corr, DeutOmegaN_corr);
    IronMR_m2->Scale(2.3966); // electron normalization
  
    IronMR_m2->SetMarkerColor(kBlue);
    IronMR_m2->SetLineColor(kBlue);
    IronMR_m2->SetLineWidth(3);
    IronMR_m2->SetMarkerStyle(21);

    IronMR_m2->Draw("E1 SAME");
  
    TH1F *LeadMR_m2 = new TH1F("LeadMR_m2", "", kinvarNbins, 0.5, 1.);
    LeadMR_m2->Divide(LeadOmegaN_corr, DeutOmegaN_corr);
    LeadMR_m2->Scale(6.1780); // electron normalization

    LeadMR_m2->SetMarkerColor(kBlack);
    LeadMR_m2->SetLineColor(kBlack);
    LeadMR_m2->SetLineWidth(3);
    LeadMR_m2->SetMarkerStyle(21);
  
    LeadMR_m2->Draw("E1 SAME");
  
    // legend
    TLegend *legend2 = new TLegend(0.9, 0.75, 1., 0.9);
    legend2->AddEntry(CarbonMR_m2, "Carbon", "pl");
    legend2->AddEntry(IronMR_m2, "Iron", "pl");
    legend2->AddEntry(LeadMR_m2, "Lead", "pl");
    legend2->Draw();

    c2->Print(plotFile); // output file

    // saving content
    std::ofstream outFinalFile2(textFile, std::ios::out); // output file
    
    // first line
    outFinalFile2 << CarbonMR_m2->GetBinContent(1) << "\t" << CarbonMR_m2->GetBinError(1) << "\t"
		  << IronMR_m2->GetBinContent(1) << "\t" << IronMR_m2->GetBinError(1) << "\t"
		  << LeadMR_m2->GetBinContent(1) << "\t" << LeadMR_m2->GetBinError(1)  << std::endl;
    // second line
    outFinalFile2 << CarbonMR_m2->GetBinContent(2) << "\t" << CarbonMR_m2->GetBinError(2) << "\t"
		  << IronMR_m2->GetBinContent(2) << "\t" << IronMR_m2->GetBinError(2) << "\t"
		  << LeadMR_m2->GetBinContent(2) << "\t" << LeadMR_m2->GetBinError(2) << std::endl;
    // third line
    outFinalFile2 << CarbonMR_m2->GetBinContent(3) << "\t" << CarbonMR_m2->GetBinError(3) << "\t"
		  << IronMR_m2->GetBinContent(3) << "\t" << IronMR_m2->GetBinError(3) << "\t"
		  << LeadMR_m2->GetBinContent(3) << "\t" << LeadMR_m2->GetBinError(3) << std::endl;
    // fourth line
    outFinalFile2 << CarbonMR_m2->GetBinContent(4) << "\t" << CarbonMR_m2->GetBinError(4) << "\t"
		  << IronMR_m2->GetBinContent(4) << "\t" << IronMR_m2->GetBinError(4) << "\t"
		  << LeadMR_m2->GetBinContent(4) << "\t" << LeadMR_m2->GetBinError(4) << std::endl;
    // fifth line
    outFinalFile2 << CarbonMR_m2->GetBinContent(5) << "\t" << CarbonMR_m2->GetBinError(5) << "\t"
		  << IronMR_m2->GetBinContent(5) << "\t" << IronMR_m2->GetBinError(5) << "\t"
		  << LeadMR_m2->GetBinContent(5) << "\t" << LeadMR_m2->GetBinError(5) << std::endl;
  
    outFinalFile2.close();
    std::cout << "File " << textFile << " has been created!" << std::endl;    
  }
  return 0;
}

inline void parseCommandLine(int argc, char* argv[]) {
Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeMR-bs -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hk:F:b:m:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'k': kinvarOption = optarg; break;
    case 'F': functionOption = optarg; break;
    case 'b': bkgOption = atoi(optarg); break;
    case 'm': Nmethod = atoi(optarg); break;
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
  std::cout << "./MakeMR-bs -k[kinvar]" << std::endl;
  std::cout << "    selects kinvar: Q2, Nu, Z, Pt2" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR-bs -F[g, bw, ln]" << std::endl;
  std::cout << "    selects function: gaussian, breit-wigner, lognormal" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR-bs -b[1,2]" << std::endl;
  std::cout << "    selects bkg: 1st or 2nd order polynomial" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR-bs -m[int]" << std::endl;
  std::cout << "    1 : calculate MR directly from the fit parameter" << std::endl;
  std::cout << "    2 : calculate MR subtracting bkg number to NBS MR" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // kinvar option
  if (kinvarOption == "Z") {
    kinvarSufix = "-z";
    kinvarConstant = 3;
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesZ[i];
  } else if (kinvarOption == "Q2") {
    kinvarSufix = "-q";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesQ2[i];
  } else if (kinvarOption == "Nu") {
    kinvarSufix = "-n";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesNu[i];
  } else if (kinvarOption == "Pt2") {
    kinvarSufix = "-p";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesPt2[i];
  }
  // bkg
  bkgSufix = Form("-b%d", bkgOption);
  bkgDir = Form("/b%d", bkgOption);
  // function
  functionSufix = "-" + functionOption;
  functionDir = "/" + functionOption;  
  // input files
  fitDir = fitDir + "/" + kinvarOption + functionDir + bkgDir; // updated!
  // output files
  if (Nmethod == 1) {
    plotFile = outDir + "/bs-MR-" + kinvarOption + functionSufix + bkgSufix + ".png";
    textFile = outDir + "/bs-MR-" + kinvarOption + functionSufix + bkgSufix + ".dat";
  } else if (Nmethod == 2) {
    plotFile = outDir + "/bs2-MR-" + kinvarOption + ".png";
    textFile = outDir + "/bs2-MR-" + kinvarOption + ".dat";
  }
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
