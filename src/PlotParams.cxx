/*********************************/
/* PlotParams.cxx                */
/*                               */
/* Created by Andrés Bórquez     */
/*                               */
/*********************************/

// plots mean, sigma, omega n, bkg n and sn ratio obtained from fits
// update:
// - style
// - fixed range
// - outdir and filename
// update:
// - added constraint option
// // 24,2 was the winner for Z
// // 38, 1.5 was the winner for Pt2 (not completely sure)

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir  = proDir + "/out/MakeRooFits"; // always!
TString inDir;

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
TString bkgSufix; // new

// name
TString plotFile;

// [D, C, Fe, Pb][Z bin: 3-7]
Double_t fitMean[4][5], fitMeanError[4][5];
Double_t fitSigma[4][5], fitSigmaError[4][5];
Double_t fitOmega[4][5], fitOmegaError[4][5];
Double_t fitBkg[4][5], fitBkgError[4][5];

// sigma studies
Double_t meanConstraint;
Int_t lineFlag;
Double_t sigmaRangeUp;
Double_t sigmaRangeDown;

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
  TH1F *meanHist = new TH1F("meanHist", "#mu (" + kinvarOption + ")", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);
  TH1F *sigmaHist = new TH1F("sigmaHist", "#sigma (" + kinvarOption + ")", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);
  TH1F *omegaHist = new TH1F("omegaHist", "N_{#omega} (" + kinvarOption + ")", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);
  TH1F *bkgHist = new TH1F("bkgHist", "N_{bkg} (" + kinvarOption + ") in (-3#sigma,3#sigma)", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);
  TH1F *snHist = new TH1F("snHist", "SN (" + kinvarOption + ") in (-3#sigma,3#sigma)", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);
  
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

  /*** MEAN ***/
  
  c->cd(1);
  gPad->SetGridx(1);
  meanHist->SetLabelSize(0.1, "X");
  meanHist->GetXaxis()->CenterLabels();
  meanHist->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1, "Deuterium");
  meanHist->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1, "Carbon");
  meanHist->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1, "Iron");
  meanHist->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1, "Lead");
  meanHist->GetXaxis()->ChangeLabel(-1,-1,0);
  meanHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  meanHist->SetLabelSize(0.1, "Y");
  meanHist->SetAxisRange(0.34, 0.39, "Y"); // by obs
  meanHist->SetLineColor(kRed);
  meanHist->SetLineWidth(3);

  meanHist->Draw("E");

  Double_t mean_avg;
  for (Int_t i = 1; i <= (4*kinvarNbins); i++) mean_avg += meanHist->GetBinContent(i);
  mean_avg = mean_avg/(4.*kinvarNbins);
  drawGrayHorizontalLine(mean_avg);

  /*** SIGMA ***/
  
  c->cd(3);
  gPad->SetGridx(1);
  sigmaHist->SetLabelSize(0.1, "X");
  sigmaHist->GetXaxis()->CenterLabels();
  sigmaHist->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1, "Deuterium");
  sigmaHist->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1, "Carbon");
  sigmaHist->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1, "Iron");
  sigmaHist->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1, "Lead");
  sigmaHist->GetXaxis()->ChangeLabel(-1,-1,0);
  sigmaHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  sigmaHist->SetLabelSize(0.1, "Y");
  sigmaHist->GetYaxis()->SetMaxDigits(2);
  // sigmaHist->SetAxisRange(0.020, 0.028, "Y"); // winner for Z
  // sigmaHist->SetAxisRange(0.034, 0.042, "Y"); // testing for Pt2
  sigmaHist->SetAxisRange(sigmaRangeDown, sigmaRangeUp, "Y"); // testing for Nu
  sigmaHist->SetLineColor(kBlack);
  sigmaHist->SetLineWidth(3);

  sigmaHist->Draw("E");

  Double_t sigma_avg;
  for (Int_t i = 1; i <= (4*kinvarNbins); i++) sigma_avg += sigmaHist->GetBinContent(i);
  sigma_avg = sigma_avg/(4.*kinvarNbins);
  drawGrayHorizontalLine(sigma_avg);

  if (lineFlag) drawOrangeHorizontalLine(meanConstraint);

  /*** OMEGA NUMBER ***/
  
  c->cd(2);
  gPad->SetGridx(1);
  omegaHist->SetLabelSize(0.1, "X");
  omegaHist->GetXaxis()->CenterLabels();
  omegaHist->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1, "Deuterium");
  omegaHist->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1, "Carbon");
  omegaHist->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1, "Iron");
  omegaHist->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1, "Lead");
  omegaHist->GetXaxis()->ChangeLabel(-1,-1,0);
  omegaHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  omegaHist->SetLabelSize(0.1, "Y");
  omegaHist->GetYaxis()->SetMaxDigits(3);
  omegaHist->SetLineColor(kMagenta+2);
  omegaHist->SetLineWidth(3);

  omegaHist->Draw("E");

  /*** BKG NUMBER ***/
  
  c->cd(4);
  gPad->SetGridx(1);
  bkgHist->SetLabelSize(0.1, "X");
  bkgHist->GetXaxis()->CenterLabels();
  bkgHist->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1, "Deuterium");
  bkgHist->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1, "Carbon");
  bkgHist->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1, "Iron");
  bkgHist->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1, "Lead");
  bkgHist->GetXaxis()->ChangeLabel(-1,-1,0);  
  bkgHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  bkgHist->SetLabelSize(0.1, "Y");
  bkgHist->GetYaxis()->SetMaxDigits(3);
  bkgHist->SetLineColor(kBlue);
  bkgHist->SetLineWidth(3);

  bkgHist->Draw("E");

  /*** SN ***/
  
  c->cd(6);
  gPad->SetGridx(1);
  snHist->SetLabelSize(0.1, "X");
  snHist->GetXaxis()->CenterLabels();
  snHist->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1, "Deuterium");
  snHist->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1, "Carbon");
  snHist->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1, "Iron");
  snHist->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1, "Lead");
  snHist->GetXaxis()->ChangeLabel(-1,-1,0);
  snHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  snHist->SetLabelSize(0.1, "Y");
  snHist->SetAxisRange(0.0, 1.0, "Y"); // by obs
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
  while ((c = getopt(argc, argv, "hk:F:b:C:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'k': kinvarOption = optarg; break;
    case 'F': signalOption = optarg; break;
    case 'b': bkgOption = atoi(optarg); break;
    case 'C': meanConstraint = (Double_t) atof(optarg); lineFlag = 1; break;
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
  std::cout << "./PlotParams -C[float]" << std::endl;
  std::cout << "    (temporary)" << std::endl;
  std::cout << "    draws orange line around point in the sigma plot" << std::endl;
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
  bkgSufix = Form("-b%d", bkgOption);
  // output
  inDir = outDir + kinvarDir + signalDir + bkgDir;
  plotFile = outDir + "/params-" + kinvarOption + "-g" + bkgSufix + ".png";
  // for sigma plot
  meanConstraint *= 1e-3;
  sigmaRangeUp = meanConstraint + 4e-3;
  sigmaRangeDown = meanConstraint - 4e-3;
}

void readTextFiles() {
  
  TString textFile;
  TString kinvarAuxSufix;
  
  for (Int_t tt = 0; tt < 4; tt++) {
    for (Int_t zz = 0; zz < kinvarNbins; zz++) {
      kinvarAuxSufix = kinvarSufix + Form("%d", zz + kinvarConstant);
      textFile = inDir + "/roofit-" + targetName[tt] + kinvarAuxSufix + ".dat";

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
