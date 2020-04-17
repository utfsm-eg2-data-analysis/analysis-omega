/**************************************/
/* PlotParams.cxx                     */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// plots mean, sigma and omega n obtained from fits

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir  = proDir + "/out/MakeRooFits";

TString targetName[4] = {"D", "C", "Fe", "Pb"};

/*** Parameters of the program ***/

// kinvar
TString kinvarOption;
Int_t   kinvarNbins = 5; // default for all kinvars --> HARDCODED
TString kinvarSufix;
TString kinvarDir;
Int_t   kinvarConstant = 1; // default for (Q2, Nu, Pt2)

// function
TString signalOption;
TString signalDir;

// bkg
Int_t bkgOption = 1; // default
TString bkgDir;

// name
TString plotFile;

// [D, C, Fe, Pb][Z bin: 3-7]
Double_t fitMean[4][5], fitMeanError[4][5];
Double_t fitSigma[4][5], fitSigmaError[4][5];
Double_t fitOmega[4][5], fitOmegaError[4][5];
Double_t fitBkg[4][5], fitBkgError[4][5];

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void assignOptions();
void printUsage();

void readTextFiles();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();

  readTextFiles();
  
  TCanvas *c = new TCanvas("c", "c", 1368, 768);
  c->Divide(2,3,0.01,0.01); // nx, ny, margins
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetTitleSize(0.12, "t"); // hist title size
  
  // creating and filling histograms
  TH1F *meanHist = new TH1F("meanHist", "#mu", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);
  TH1F *sigmaHist = new TH1F("sigmaHist", "#sigma", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);
  TH1F *omegaHist = new TH1F("omegaHist", "N_{#omega}", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);
  TH1F *bkgHist = new TH1F("bkgHist", "N_{b}", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);
  TH1F *snHist = new TH1F("snHist", "SN", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);
  
  for (Int_t t = 0; t < 4; t++) {
    for (Int_t z = 0; z < kinvarNbins; z++) {
      // mean
      meanHist->SetBinContent(kinvarNbins*t + z + 1, fitMean[t][z]);
      meanHist->SetBinError(kinvarNbins*t + z + 1, fitMeanError[t][z]);
      // width
      sigmaHist->SetBinContent(kinvarNbins*t + z + 1, fitSigma[t][z]);
      sigmaHist->SetBinError(kinvarNbins*t + z + 1, fitSigmaError[t][z]);
      // omega
      omegaHist->SetBinContent(kinvarNbins*t + z + 1, fitOmega[t][z]);
      omegaHist->SetBinError(kinvarNbins*t + z + 1, fitOmegaError[t][z]);
      // bkg
      bkgHist->SetBinContent(kinvarNbins*t + z + 1, fitBkg[t][z]);
      bkgHist->SetBinError(kinvarNbins*t + z + 1, fitBkgError[t][z]);
    }
  }
  // sn ratio
  snHist->Divide(omegaHist, bkgHist);

  c->cd(1);
  gPad->SetGridx(1);
  meanHist->SetLabelSize(0.1, "Y");
  meanHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  meanHist->GetYaxis()->CenterTitle();
  meanHist->SetLineColor(kRed);
  meanHist->SetLineWidth(3);

  meanHist->Draw("E");

  Double_t mean_avg;
  for (Int_t i = 1; i <= (4*kinvarNbins); i++) mean_avg += meanHist->GetBinContent(i);
  mean_avg = mean_avg/(4.*kinvarNbins);
  drawBlackHorizontalLine(mean_avg);
  
  c->cd(3);
  gPad->SetGridx(1);
  sigmaHist->SetLabelSize(0.1, "Y");
  sigmaHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  sigmaHist->GetYaxis()->CenterTitle();
  sigmaHist->GetYaxis()->SetMaxDigits(2);
  sigmaHist->SetLineColor(kBlack);
  sigmaHist->SetLineWidth(3);

  sigmaHist->Draw("E");

  Double_t sigma_avg;
  for (Int_t i = 1; i <= (4*kinvarNbins); i++) sigma_avg += sigmaHist->GetBinContent(i);
  sigma_avg = sigma_avg/(4.*kinvarNbins);
  drawBlackHorizontalLine(sigma_avg);
      
  c->cd(2);
  gPad->SetGridx(1);
  omegaHist->SetLabelSize(0.1, "Y");
  omegaHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  omegaHist->GetYaxis()->CenterTitle();
  omegaHist->GetYaxis()->SetMaxDigits(3);
  omegaHist->SetLineColor(kMagenta+2);
  omegaHist->SetLineWidth(3);

  omegaHist->Draw("E");
  
  c->cd(4);
  gPad->SetGridx(1);
  bkgHist->SetLabelSize(0.1, "Y");
  bkgHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  bkgHist->GetYaxis()->CenterTitle();
  bkgHist->GetYaxis()->SetMaxDigits(3);
  bkgHist->SetLineColor(kBlue);
  bkgHist->SetLineWidth(3);

  bkgHist->Draw("E");

  c->cd(6);
  gPad->SetGridx(1);
  snHist->SetLabelSize(0.1, "Y");
  snHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  snHist->GetYaxis()->CenterTitle();
  snHist->SetLineColor(kGreen+2);
  snHist->SetLineWidth(3);

  snHist->Draw("E");

  c->Print(plotFile); // output file
  std::cout << std::endl;

  // print errors
  Double_t mean_avg_err;
  Double_t sigma_avg_err;
  for (Int_t i = 1; i <= (4*kinvarNbins); i++) {
    mean_avg_err += meanHist->GetBinError(i);
    sigma_avg_err += sigmaHist->GetBinError(i);
  }
  mean_avg_err = mean_avg_err/(4.*kinvarNbins);
  sigma_avg_err = sigma_avg_err/(4.*kinvarNbins);
  
  std::cout << "  mean_avg      = " << mean_avg << std::endl;
  std::cout << "  mean_avg_err  = " << mean_avg_err << std::endl;
  std::cout << "  sigma_avg     = " << sigma_avg << std::endl;
  std::cout << "  sigma_avg_err = " << sigma_avg_err << std::endl;
  std::cout << std::endl;
}

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./PlotParams -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hk:F:b:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'k': kinvarOption = optarg; break;
    case 'F': signalOption = optarg; break;
    case 'b': bkgOption = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./PlotParams -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "PlotParams program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./PlotParams -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./PlotParams -k[kinvar]" << std::endl;
  std::cout << "    selects kinematic variable: Q2, Nu, Z, Pt2" << std::endl;
  std::cout << std::endl;
  std::cout << "./PlotParams -F[function]" << std::endl;
  std::cout << "    selects function, which can be" << std::endl;
  std::cout << "    g  : Gaussian (default)" << std::endl;
  std::cout << "    bw : Breit-Wigner" << std::endl;
  std::cout << "    ln : Lognormal" << std::endl;
  std::cout << std::endl;
  std::cout << "./PlotParams -b[1,2]" << std::endl;
  std::cout << "    choose bkg function: 1st order or 2nd order polynomial" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for kinvar
  if (kinvarOption == "Q2") {
    kinvarSufix = "-q";
  } else if (kinvarOption == "Nu") {
    kinvarSufix = "-n";
  } else if (kinvarOption == "Z") {
    kinvarSufix = "-z";
    kinvarConstant = 3;
  } else if (kinvarOption == "Pt2") {
    kinvarSufix = "-p";
  }
  // setting the directories
  kinvarDir = "/" + kinvarOption;
  signalDir = "/" + signalOption;
  bkgDir = Form("/b%d", bkgOption);
  // output
  outDir = outDir + kinvarDir + signalDir + bkgDir;
  plotFile = outDir + "/params-" + kinvarOption + ".png";
}

void readTextFiles() {
  
  TString textFile;
  TString kinvarAuxSufix;
  
  for (Int_t tt = 0; tt < 4; tt++) {
    for (Int_t zz = 0; zz < kinvarNbins; zz++) {
      kinvarAuxSufix = kinvarSufix + Form("%d", zz + kinvarConstant);
      textFile = outDir + "/roofit-" + targetName[tt] + kinvarAuxSufix + ".dat";

      std::cout << "Reading " << textFile << " ..." << std::endl;
      std::ifstream inFile(textFile);
      
      TString auxString1, auxString2;
      Int_t l = 0; // line counter
      while (inFile >> auxString1 >> auxString2) {
	l++;
	if (l == 1) { // first line
	  fitMean[tt][zz] = auxString1.Atof();
	  fitMeanError[tt][zz] = auxString2.Atof();
	  std::cout << "  mean  = " << fitMean[tt][zz] << " +- " << fitMeanError[tt][zz] << std::endl;
	} else if (l == 2) {
	  fitSigma[tt][zz] = auxString1.Atof();
	  fitSigmaError[tt][zz] = auxString2.Atof();
	  std::cout << "  sigma = " << fitSigma[tt][zz] << " +- " << fitSigmaError[tt][zz] << std::endl;
	} else if (l == 3) {
	  fitOmega[tt][zz] = auxString1.Atof();
	  fitOmegaError[tt][zz] = auxString2.Atof();
	  std::cout << "  omega = " << fitOmega[tt][zz] << " +- " << fitOmegaError[tt][zz] << std::endl;
	} else if (l == 4) {
	  fitBkg[tt][zz] = auxString1.Atof();
	  fitBkgError[tt][zz] = auxString2.Atof();
	  std::cout << "  bkg   = " << fitBkg[tt][zz] << " +- " << fitBkgError[tt][zz] << std::endl;
	}
      }
      inFile.close();
      std::cout << std::endl;
    }
  }
}
