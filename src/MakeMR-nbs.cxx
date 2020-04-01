/**************************************/
/* MakeMR-nbs.cxx                     */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// From the MakeRooFits results, we obtain mean and sigma for each peak
// With the mean and sigma, we set the edges for a cut around the peak in the root files
// This program calculates MR doing cuts on the peak and then dividing
// updates:
// - use toycombine data
// - uniD
// - can choose obs

#include <iostream>
#include <fstream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TCut.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TF1.h"
#include "TString.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TObjArray.h"

/*** Global variables ***/

TString proFolder = "/home/borquez/omegaThesis";
TString outFolder = proFolder + "/out/MakeMR/nbs";
TString inputRootLocation = proFolder + "/out/filterData";
TString inputTextLocation = proFolder + "/out/MakeRooFits";

Double_t edgesZ[6] = {0.5, 0.554, 0.611, 0.676, 0.760, 0.9}; // updated
Double_t edgesQ2[6] = {1., 1.181, 1.364, 1.598, 1.960, 3.970};
Double_t edgesNu[6] = {2.2, 3.191, 3.504, 3.744, 3.964, 4.2};
Double_t edgesPt2[6] = {0.0, 0.040, 0.090, 0.159, 0.273, 1.5}; // updated

/*** Parameters ***/
Int_t flagZ = 0;
Int_t flagQ2 = 0;
Int_t flagNu = 0;
Int_t flagPt2 = 0;
Int_t Nsigma = 5; // default

/*** Global options ***/
TString sigmaSufix;
TString obsName;
TString obsFolder;
TString obsValue[6];
Int_t   obsConstant = 1; // default for (Q2, Nu, Pt2)
Int_t   obsNbins = 5;    // default for all
Int_t   obsMin = 1; // default for (Q2, Nu, Pt2)
Int_t   obsMax = 5; // default for (Q2, Nu, Pt2)
TString obsSufix;
TString outputFileName;
TString outputPlotName;

/*** Local options ***/
TString  inputFile1;
TString  inputFile2;
TString  inputFile3;
TCut     cutTargType;
Double_t obsLowEdge;
Double_t obsHighEdge;
TCut     obsCut;
TString  obsAuxSufix;
TString  obsTitle;

// from fit results [kinvar bin]
Double_t omegaMean[5];
Double_t omegaSigma[5];
Double_t massLowEdge[5];
Double_t massHighEdge[5];

// from root files [D,C,Fe,Pb][kinvar bin]
Double_t particleNumber[4][5];
Double_t particleError[4][5];

/*** Declaration of functions ***/

inline void parseCommandLine(int argc, char* argv[]);
void assignGlobalOptions();
void printUsage();

void assignOptions(TString targetOption, Int_t binNumber);
void readFitResult(TString targetOption, Int_t binNumber);
void integrateData(TString targetOption, Int_t binNumber);

void printResults(TH1F *CarbonMR2, TH1F *IronMR2, TH1F *LeadMR2);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignGlobalOptions();
  
  for (Int_t i = obsMin; i < (obsMax+1); i++) {
    assignOptions("D", i);
    readFitResult("D", i);
    integrateData("D", i);
    
    assignOptions("C", i);
    // readFitResult("C", i);
    integrateData("C", i);

    assignOptions("Fe", i);
    // readFitResult("Fe", i);
    integrateData("Fe", i);

    assignOptions("Pb", i);
    // readFitResult("Pb", i);
    integrateData("Pb", i);
  }

  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  c->SetGridx(1);
  c->SetGridy(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  // creating and filling histograms
  TH1F *numberDeutHist = new TH1F("numberDeutHist", "", obsNbins, 0.5, 1.);
  TH1F *numberCarbonHist = new TH1F("numberCarbonHist", "", obsNbins, 0.5, 1.);
  TH1F *numberIronHist = new TH1F("numberIronHist", "", obsNbins, 0.5, 1.);
  TH1F *numberLeadHist = new TH1F("numberLeadHist", "", obsNbins, 0.5, 1.);
  
  // creates sumw2 structure before hand
  numberDeutHist->Sumw2();
  numberCarbonHist->Sumw2();
  numberIronHist->Sumw2();  
  numberLeadHist->Sumw2();
  
  // for each bin in kinvar
  for (Int_t cc = 0; cc < obsNbins; cc++) {
    numberDeutHist->SetBinContent(cc + 1, particleNumber[0][cc]);
    numberDeutHist->SetBinError(cc + 1, particleError[0][cc]);
    
    numberCarbonHist->SetBinContent(cc + 1, particleNumber[1][cc]);
    numberCarbonHist->SetBinError(cc + 1, particleError[1][cc]);
    
    numberIronHist->SetBinContent(cc + 1, particleNumber[2][cc]);
    numberIronHist->SetBinError(cc + 1, particleError[2][cc]);
        
    numberLeadHist->SetBinContent(cc + 1, particleNumber[4][cc]);
    numberLeadHist->SetBinError(cc + 1, particleError[4][cc]);
  }
  
  /*** Drawing ***/

  std::cout << "Drawing..." << std::endl;
  TH1F *CarbonMR = new TH1F("CarbonMR", "", obsNbins, 0.5, 1.);
  CarbonMR->SetTitle(Form("#omega MR(" + obsName + ") - No Bkg Subtraction (-%d#sigma, %d#sigma)", Nsigma, Nsigma));
  CarbonMR->GetXaxis()->SetTitle(obsName);
  CarbonMR->GetXaxis()->SetNdivisions(200 + obsNbins, kFALSE);
  CarbonMR->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,obsValue[0]);
  CarbonMR->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,obsValue[1]);
  CarbonMR->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,obsValue[2]);
  CarbonMR->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,obsValue[3]);
  CarbonMR->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,obsValue[4]);
  CarbonMR->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,obsValue[5]);
  CarbonMR->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,obsValue[4]);
  CarbonMR->GetYaxis()->SetTitle("MR");

  CarbonMR->SetMarkerColor(kRed);
  CarbonMR->SetLineColor(kRed);
  CarbonMR->SetLineWidth(3);
  CarbonMR->SetMarkerStyle(21);
  CarbonMR->Divide(numberCarbonHist, numberDeutHist);
  // CarbonMR->Scale(1.08476); // divD
  CarbonMR->Scale(4.6194); // electron normalization, uniD
  
  CarbonMR->SetAxisRange(0., 1.2, "Y"); // range
  CarbonMR->Draw("E");  
  
  TH1F *IronMR = new TH1F("IronMR", "", obsNbins, 0.5, 1.);
  IronMR->SetMarkerColor(kBlue);
  IronMR->SetLineColor(kBlue);
  IronMR->SetLineWidth(3);
  IronMR->SetMarkerStyle(21);
  IronMR->Divide(numberIronHist, numberDeutHist);
  // IronMR->Scale(1.01234); // divD
  IronMR->Scale(2.3966); // electron normalization, uniD
  
  IronMR->Draw("E SAME");

  TH1F *LeadMR = new TH1F("LeadMR", "", obsNbins, 0.5, 1.);
  LeadMR->SetMarkerColor(kBlack);
  LeadMR->SetLineColor(kBlack);
  LeadMR->SetLineWidth(3);
  LeadMR->SetMarkerStyle(21);
  LeadMR->Divide(numberLeadHist, numberDeutHist);
  // LeadMR->Scale(2.12055); // divD
  LeadMR->Scale(6.1780); // electron normalization, uniD
  
  LeadMR->Draw("E SAME");
    
  // legend
  TLegend *legend = new TLegend(0.9, 0.75, 1., 0.9);
  legend->AddEntry(CarbonMR, "Carbon", "pl");
  legend->AddEntry(IronMR, "Iron", "pl");
  legend->AddEntry(LeadMR, "Lead", "pl");
  legend->Draw();

  c->Print(outputPlotName); // output file

  /*** Save results ***/
  
  std::ofstream outFinalFile(outputFileName, std::ios::out); // output file
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
  std::cout << "File " << outputFileName << " created!" << std::endl;
  
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

void assignGlobalOptions() {
  // for sigma
  sigmaSufix = Form("-%dsigma", Nsigma);
  // for kinvar
  if (flagZ) {
    obsName = "Z";
    inputTextLocation = inputTextLocation + "/Z";
    obsConstant = 3;
    obsMin = 3;
    obsMax = 7;
    obsSufix = "-z";
    for (Int_t i = 0; i < (obsNbins+1); i++) obsValue[i] = Form("%.02f", edgesZ[i]);
  } else if (flagQ2) {
    obsName = "Q2";
    inputTextLocation = inputTextLocation + "/Q2";
    obsSufix = "-q";
    for (Int_t i = 0; i < (obsNbins+1); i++) obsValue[i] = Form("%.02f", edgesQ2[i]);
  } else if (flagNu) {
    obsName = "Nu";
    inputTextLocation = inputTextLocation + "/Nu";
    obsSufix = "-n";
    for (Int_t i = 0; i < (obsNbins+1); i++) obsValue[i] = Form("%.02f", edgesNu[i]);
  } else if (flagPt2) {
    obsName = "Pt2";
    inputTextLocation = inputTextLocation + "/Pt2";
    obsSufix = "-p";
    for (Int_t i = 0; i < (obsNbins+1); i++) obsValue[i] = Form("%.02f", edgesPt2[i]);
  }
  // for output files
  outputPlotName = outFolder + "/nbs-MR" + obsSufix + sigmaSufix + ".png";
  outputFileName = outFolder + "/nbs-MR" + obsSufix + sigmaSufix + ".dat";
}

void assignOptions(TString targetOption, Int_t binNumber) {
  // for targets, unified D
  if (targetOption == "D") {
    inputFile1 = inputRootLocation + "/C/comb_C-thickD2.root";
    inputFile2 = inputRootLocation + "/Fe/comb_Fe-thickD2.root";
    inputFile3 = inputRootLocation + "/Pb/comb_Pb-thinD2.root";
    cutTargType = "TargType == 1";
  } else if (targetOption == "C") {
    inputFile1 = inputRootLocation + "/C/comb_C-thickD2.root";
    inputFile2 = "";
    inputFile3 = "";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Fe") {
    inputFile1 = inputRootLocation + "/Fe/comb_Fe-thickD2.root";
    inputFile2 = "";
    inputFile3 = "";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Pb") {
    inputFile1 = inputRootLocation + "/Pb/comb_Pb-thinD2.root";
    inputFile2 = "";
    inputFile3 = "";
    cutTargType = "TargType == 2";
  }
  // for observable
  if (flagZ) {
    obsLowEdge = edgesZ[binNumber-obsConstant];
    obsHighEdge = edgesZ[binNumber+1-obsConstant];
    obsAuxSufix = Form("-z%d", binNumber);
  } else if (flagQ2) {
    obsLowEdge = edgesQ2[binNumber-obsConstant];
    obsHighEdge = edgesQ2[binNumber+1-obsConstant];
    obsAuxSufix = Form("-q%d", binNumber);
  } else if (flagNu) {
    obsLowEdge = edgesNu[binNumber-obsConstant];
    obsHighEdge = edgesNu[binNumber+1-obsConstant];
    obsAuxSufix = Form("-n%d", binNumber);
  } else if (flagPt2) {
    obsLowEdge = edgesPt2[binNumber-obsConstant];
    obsHighEdge = edgesPt2[binNumber+1-obsConstant];
    obsAuxSufix = Form("-p%d", binNumber);
  }
  obsTitle = Form(" (%.02f < ", obsLowEdge) + obsName + Form(" < %.02f)", obsHighEdge);
  obsCut = Form("%f < ", obsLowEdge) + obsName + " && " + obsName + Form(" < %f", obsHighEdge);
}

void integrateData(TString targetOption, Int_t binNumber) {
  
  Int_t index = binNumber - obsConstant;
  Int_t targIndex;

  TCut cutDIS = "Q2 > 1 && W > 2 && Yb < 0.85";
  TCut cutPi0 = "0.059 < pi0M && pi0M < 0.209";
  TCut cutPipPim = "0.48 > pippimM || 0.51 < pippimM";
  TCut cutAll = cutPi0 && cutDIS && cutPipPim; // doesn't consider targType yet

  TCut cutMass = Form("%f < wD && wD < %f", massLowEdge[index], massHighEdge[index]); // here we apply the edges!

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  TCanvas *cw = new TCanvas("cw", "cw", 1000, 1000);
  cw->SetGridx(1);
  cw->SetGridy(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  
  TH1F *dataHist;
  treeExtracted->Draw("wD>>data(20, 0.3, 0.4)", cutAll && obsCut && cutTargType && cutMass, "goff");
  dataHist = (TH1F *)gROOT->FindObject("data");
  
  if (targetOption == "D") targIndex = 0;
  else if (targetOption == "C") targIndex = 1;
  else if (targetOption == "Fe") targIndex = 2;
  else if (targetOption == "Pb") targIndex = 3;
		    
  // save numbers!
  particleNumber[targIndex][index] = dataHist->IntegralAndError(1, 20, particleError[targIndex][index], "");
  std::cout << targetOption << obsAuxSufix << ": " << particleNumber[targIndex][index] << " +/- " << particleError[targIndex][index] << std::endl;
  
  // draw for test!
  dataHist->SetTitle("IMD(#omega) for " + targetOption + " in " + obsTitle);
  dataHist->SetLineColor(kBlue);
  dataHist->SetLineWidth(3);
  dataHist->GetXaxis()->SetTitle("IMD(#omega) (GeV)");
  dataHist->GetYaxis()->SetTitle("Entries");
  dataHist->Draw("E");

  TString outputTestName = outFolder + "hist-" + targetOption + obsAuxSufix + sigmaSufix + ".png";
  cw->Print(outputTestName); // output file
  
  delete cw;
  delete dataHist;
  delete treeExtracted;
}

void readFitResult(TString targetOption, Int_t binNumber) {

  Int_t index = binNumber - obsConstant;
  
  TString textFile = inputTextLocation + "/roofit-" + targetOption + obsAuxSufix + ".dat";
  
  std::ifstream inFile(textFile);
  
  TString auxString1, auxString2;
  Int_t l = 0; // line counter
  while (inFile >> auxString1 >> auxString2) {
    l++;
    if (l == 3) { // third line
      omegaMean[index] = auxString1.Atof();
      std::cout << "Omega Mean for " << targetOption << obsAuxSufix << ": " << omegaMean[index] << std::endl;
    } else if (l == 4) { // fourth line
      omegaSigma[index] = auxString1.Atof();
      std::cout << "Omega Sigma for " << targetOption << obsAuxSufix << ": " << omegaSigma[index] << std::endl;
    }
  }
  inFile.close();

  // assign mass edges!
  massLowEdge[index] = omegaMean[index] - Nsigma*omegaSigma[index];
  massHighEdge[index] = omegaMean[index] + Nsigma*omegaSigma[index];
  std::cout << targetOption << obsAuxSufix << ": [" << massLowEdge[index] << ", " << massHighEdge[index] << "]" << std::endl;
}
