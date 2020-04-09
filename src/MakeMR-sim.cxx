/**************************************/
/* MakeMR-sim.cxx                     */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

/*** TASK 2 for Analysis Note ***/

// nbs & bs for simulations, only for Z
// it lacks electron normalization

#include "analysisConfig.h"

#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooDataHist.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooAbsReal.h"

using namespace RooFit;

/*** Global variables ***/

TString outDir   = proDir + "/out/MakeMR/sim";
TString textDir  = proDir + "/out/MakeSimFits/Z";

Double_t massEdges[4][5][2];

// [D, C, Fe, Pb][Z bin: 3-7]
Double_t particleNumber[4][5];
Double_t particleError[4][5];

Int_t Nsigma;
Int_t bsFlag = 0; // nbs by default
Double_t omegaMean[4][5];
Double_t omegaSigma[4][5];

// names stuff
TString targetName[4] = {"D", "C", "Fe", "Pb"};
TString titleMR;
TString plotFile;
TString textFile;

inline void parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();

void integrateData(TString targetOption);

void printResults(TH1F *CarbonMR2, TH1F *IronMR2, TH1F *LeadMR2);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();

  /*** Read fit results ***/
    
  for (Int_t targIndex = 0; targIndex < 4; targIndex++) {
    for (Int_t index = 0; index < 5; index++) {

      TString kinvarAuxSufix = Form("-z%d", index+3); // only z, for now
      TString fitFile = textDir + "/simfit-" + targetName[targIndex] + kinvarAuxSufix + ".dat";

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
      massEdges[targIndex][index][0] = omegaMean[targIndex][index] - Nsigma*omegaSigma[targIndex][index];
      massEdges[targIndex][index][1] = omegaMean[targIndex][index] + Nsigma*omegaSigma[targIndex][index];
      std::cout << "Mass edges for " << targetName[targIndex] << kinvarAuxSufix << ": [" << massEdges[targIndex][index][0] << ", " << massEdges[targIndex][index][1] << "]" << std::endl; 
    }
  }
  
  /*** Integrate data ***/
  // it overwrites the particleNumber and particleError arrays for the nbs case
  
  if (!bsFlag) {
    integrateData("D");
    integrateData("C");
    integrateData("Fe");
    integrateData("Pb");
  }
  
  /*** Fill and draw MR histograms ***/
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  c->SetGridx(0);
  c->SetGridy(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  std::cout << "Creating and filling histograms..." << std::endl;

  TH1F *numberDeutHist = new TH1F("numberDeutHist", "", 5, 0.5, 1.);
  TH1F *numberCarbonHist = new TH1F("numberCarbonHist", "", 5, 0.5, 1.);
  TH1F *numberIronHist = new TH1F("numberIronHist", "", 5, 0.5, 1.);
  TH1F *numberLeadHist = new TH1F("numberLeadHist", "", 5, 0.5, 1.);

  // for each bin in z
  for (Int_t cc = 0; cc < 5; cc++) {
    numberDeutHist->SetBinContent(cc + 1, particleNumber[0][cc]);
    numberDeutHist->SetBinError(cc + 1, particleError[0][cc]);
    
    numberCarbonHist->SetBinContent(cc + 1, particleNumber[1][cc]);
    numberCarbonHist->SetBinError(cc + 1, particleError[1][cc]);
    
    numberIronHist->SetBinContent(cc + 1, particleNumber[2][cc]);
    numberIronHist->SetBinError(cc + 1, particleError[2][cc]);
        
    numberLeadHist->SetBinContent(cc + 1, particleNumber[3][cc]);
    numberLeadHist->SetBinError(cc + 1, particleError[3][cc]);
  }
  
  /*** Drawing ***/
  
  TH1F *CarbonMR = new TH1F("CarbonMR", "", 5, 0.5, 1.);
  CarbonMR->SetTitle(titleMR);
  CarbonMR->GetXaxis()->SetTitle("Z");
  CarbonMR->GetXaxis()->SetNdivisions(205, kFALSE);
  CarbonMR->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,Form("%.02f", edgesZ[0]));
  CarbonMR->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,Form("%.02f", edgesZ[1]));
  CarbonMR->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,Form("%.02f", edgesZ[2]));
  CarbonMR->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,Form("%.02f", edgesZ[3]));
  CarbonMR->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,Form("%.02f", edgesZ[4]));
  CarbonMR->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,Form("%.02f", edgesZ[5]));
  CarbonMR->GetYaxis()->SetTitle("MR");
    
  // for Carbon 
  CarbonMR->SetMarkerColor(kRed);
  CarbonMR->SetLineColor(kRed);
  CarbonMR->SetLineWidth(3);
  CarbonMR->SetMarkerStyle(21);
  CarbonMR->Divide(numberCarbonHist, numberDeutHist);
  // CarbonMR->Scale(1.08476); // electron normalization factor

  // draw already!
  CarbonMR->SetAxisRange(0., 1.8, "Y"); // range
  CarbonMR->Draw("E");  
  
  // for Iron
  TH1F *IronMR = new TH1F("IronMR", "", 5, 0.5, 1.);
  IronMR->SetMarkerColor(kBlue);
  IronMR->SetLineColor(kBlue);
  IronMR->SetLineWidth(3);
  IronMR->SetMarkerStyle(21);
  IronMR->Divide(numberIronHist, numberDeutHist);
  // IronMR->Scale(1.01234); // electron normalization factor
    
  IronMR->Draw("E SAME");

  // for Lead
  TH1F *LeadMR = new TH1F("LeadMR", "", 5, 0.5, 1.);
  LeadMR->SetMarkerColor(kBlack);
  LeadMR->SetLineColor(kBlack);
  LeadMR->SetLineWidth(3);
  LeadMR->SetMarkerStyle(21);
  LeadMR->Divide(numberLeadHist, numberDeutHist);
  // LeadMR->Scale(2.12055); // electron normalization factor
    
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

inline void parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeMR-sim -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hs:b")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 's': Nsigma = atoi(optarg); break;
    case 'b': bsFlag = 1; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeMR-sim -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "MakeMR-sim program. Usage is:" << std::endl;
  std::cout << "./MakeMR-sim -[option]" << std::endl;
  std::cout << "  h        : prints help and exit program" << std::endl;
  std::cout << "  s[n]     : selects range for n*sigma, with n: 3,4,5" << std::endl;
  std::cout << "  b        : obtain bs MR" << std::endl;
}

void assignOptions() {
  if (!bsFlag) {
    titleMR = Form("#omega MR(Z) - No Bkg Subtraction (-%d#sigma, %d#sigma) [Reconstructed]", Nsigma, Nsigma);
    textFile = outDir + Form("/sim-nbs-MR-Z-%dw.dat", Nsigma);
    plotFile = outDir + Form("/sim-nbs-MR-Z-%dw.png", Nsigma);
  } else if (bsFlag) {
    titleMR = "#omega MR(Z) - Bkg Subtraction [Reconstructed]";
    textFile = outDir + "/sim-bs-MR-Z.dat";
    plotFile = outDir + "/sim-bs-MR-Z.png";
  }
}

void integrateData(TString targetOption) {

  // local variables
  TString inputFile;
  TCut cutTargType;
  Int_t targIndex;
  
  // assign local options
  if (targetOption == "D") {
    targIndex = 0;
    inputFile = simrecDir + "/jlab/D/wout_simrecD.root";
    cutTargType = "TargType == 1";
  } else if (targetOption == "C") {
    targIndex = 1;
    inputFile = simrecDir + "/jlab/C/wout_simrecC.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Fe") {
    targIndex = 2;
    inputFile = simrecDir + "/jlab/Fe/wout_simrecFe.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Pb") {
    targIndex = 3;
    inputFile = simrecDir + "/usm/Pb/wout_simrecPb.root";
    cutTargType = "TargType == 2";
  }
  
  TCut cutAll = cutPi0_sim && cutDIS_old && cutPipPim_old;

  TCut cutZ;
  TString titleZ;
  TString auxZSufix;

  TCut cutPeak;
   
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile + "/outdata");
  setAlias_old(treeExtracted);
  
  for (Int_t zz = 0; zz < 5; zz++) { // 0 to 4

    // define z cut
    cutZ = Form("%f < Z && Z < %f", edgesZ[zz], edgesZ[zz+1]);
    titleZ = Form("(%.02f < Z < %.02f)", edgesZ[zz+1], edgesZ[zz+1]);

    // define cut around peak
    cutPeak = Form("%f < deltam && deltam < %f", massEdges[targIndex][zz][0], massEdges[targIndex][zz][1]);

    TH1F *dataHist;
    treeExtracted->Draw(Form("deltam>>data_z%d(52, 0.24, 0.5)", zz), cutAll && cutTargType && cutZ && cutPeak, "goff");
    dataHist = (TH1F *)gROOT->FindObject(Form("data_z%d", zz));

    // keep number
    auxZSufix = Form("-z%d", zz + 3);
    particleNumber[targIndex][zz] = dataHist->IntegralAndError(1, 52, particleError[targIndex][zz], "");
    std::cout << "nbs omega number for " << targetOption << auxZSufix << " = " << particleNumber[targIndex][zz] << " +/- " << particleError[targIndex][zz] << std::endl;

    delete dataHist;
  }
  delete treeExtracted;
}
