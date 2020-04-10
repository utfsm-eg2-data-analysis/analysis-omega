/**************************************/
/* PlotParams.cxx                     */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// plots mean, sigma and omega n obtained from fits

#include "analysisConfig.h"

/*** Global variables ***/

TString textDir = proDir + "/out/MakeRooFits";
TString outDir  = proDir + "/out/MakeRooFits";

TString targetName[4] = {"D", "C", "Fe", "Pb"}; // uniD

/*** Parameters of the program ***/

// kinvar
Int_t flagZ = 0;
Int_t flagQ2 = 0;
Int_t flagNu = 0;
Int_t flagPt2 = 0;
Int_t kinvarNbins = 5; // default for all kinvars
TString kinvarSufix;
TString kinvarDir;
Int_t kinvarConstant = 1; // default for (Q2, Nu, Pt2)

// function
TString functionOption;
TString functionSufix = ""; // default for (Z-gaus, Q2, Nu, Pt2)

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
  meanHist->GetYaxis()->SetMaxDigits(4);
  meanHist->SetLineColor(kRed);
  meanHist->SetLineWidth(3);

  meanHist->Draw("E");

  c->cd(3);
  gPad->SetGridx(1);
  sigmaHist->SetLabelSize(0.1, "Y");
  sigmaHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  sigmaHist->GetYaxis()->CenterTitle();
  sigmaHist->GetYaxis()->SetMaxDigits(2);
  sigmaHist->SetLineColor(kBlack);
  sigmaHist->SetLineWidth(3);

  sigmaHist->Draw("E");

  c->cd(2);
  gPad->SetGridx(1);
  omegaHist->SetLabelSize(0.1, "Y");
  omegaHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  omegaHist->GetYaxis()->CenterTitle();
  omegaHist->SetLineColor(kMagenta+2);
  omegaHist->SetLineWidth(3);

  omegaHist->Draw("E");
  
  c->cd(4);
  gPad->SetGridx(1);
  bkgHist->SetLabelSize(0.1, "Y");
  bkgHist->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  bkgHist->GetYaxis()->CenterTitle();
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

  /*** Test propagation of errors ***/

  Double_t ome_val, ome_err;
  Double_t bkg_val, bkg_err;
  Double_t sn_val, sn_err;
  Double_t cal_err;
  
  for (Int_t t = 1; t <= 5; t++) {

    ome_val=omegaHist->GetBinContent(t);
    ome_err=omegaHist->GetBinError(t);

    bkg_val=bkgHist->GetBinContent(t);
    bkg_err=bkgHist->GetBinError(t);

    sn_val=snHist->GetBinContent(t);

    cal_err=sn_val*TMath::Sqrt(TMath::Power((ome_err/ome_val), 2) + TMath::Power((bkg_err/bkg_val), 2));
    
    std::cout << "cal_err=" << cal_err << std::endl;

    sn_err = snHist->GetBinError(t);
    std::cout << "sn_err=" << sn_err<< std::endl;
    std::cout << "sn_val=" << sn_val<< std::endl;
    std::cout << std::endl;
  }
  
  c->Print(plotFile); // output file
}

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./PlotParams -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hF:zqnp")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'F': functionOption = optarg; break;
    case 'z': flagZ = 1; break;
    case 'q': flagQ2 = 1; break;
    case 'n': flagNu = 1; break;
    case 'p': flagPt2 = 1; break;
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
  std::cout << "    h : prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./PlotParams -[kinvar]" << std::endl;
  std::cout << "    selects kinematic variable" << std::endl;
  std::cout << "    z : Z" << std::endl;
  std::cout << "    q : Q2" << std::endl;
  std::cout << "    n : Nu" << std::endl;
  std::cout << "    p : Pt2" << std::endl;
  std::cout << std::endl;
  std::cout << "./PlotParams -F[function]" << std::endl;
  std::cout << "    (mandatory for Z!)" << std::endl;
  std::cout << "    selects function, which can be" << std::endl;
  std::cout << "    g  : Gaussian" << std::endl;
  std::cout << "    bw : Breit-Wigner" << std::endl;
  std::cout << "    ln : Lognormal" << std::endl;
}

void assignOptions() {
  // for kinvar
  if (flagZ) {
    kinvarSufix = "-z";
    kinvarConstant = 3;
    // for functions
    if (functionOption == "g") {
      kinvarDir = "/Z";
    } else if (functionOption == "bw") {
      kinvarDir = "bw";
      functionSufix = "-bw";
    } else if (functionOption == "ln") {
      kinvarDir = "ln";
      functionSufix = "-ln";
    }
  } else if (flagQ2) {
    kinvarSufix = "-q";
    kinvarDir = "/Q2";
  } else if (flagNu) {
    kinvarSufix = "-n";
    kinvarDir = "/Nu";
  } else if (flagPt2) {
    kinvarSufix = "-p";
    kinvarDir = "/Pt2";
  }
  // name
  plotFile = outDir + kinvarDir + "/roofit" + functionSufix + kinvarSufix + ".png";
}

void readTextFiles() {
  
  TString textFileName;
  TString kinvarAuxSufix;
  
  for (Int_t tt = 0; tt < 4; tt++) {
    for (Int_t zz = 0; zz < kinvarNbins; zz++) {
      kinvarAuxSufix = Form("%d", zz + kinvarConstant);      
      textFileName = kinvarDir + "/roofit" + functionSufix + "-" + targetName[tt] + kinvarSufix + kinvarAuxSufix + ".dat";

      std::cout << "Reading " << textFileName << "..." << std::endl;
      std::ifstream inFile(textDir + textFileName);
      
      TString auxString1, auxString2;
      Int_t l = 0; // line counter
      while (inFile >> auxString1 >> auxString2) {
	l++;
	if (l == 1) { // first line
	  fitMean[tt][zz] = auxString1.Atof();
	  fitMeanError[tt][zz] = auxString2.Atof();
	  std::cout << "--mean : " << fitMean[tt][zz] << " +- " << fitMeanError[tt][zz] << std::endl;
	} else if (l == 2) {
	  fitSigma[tt][zz] = auxString1.Atof();
	  fitSigmaError[tt][zz] = auxString2.Atof();
	  std::cout << "--sigma: " << fitSigma[tt][zz] << " +- " << fitSigmaError[tt][zz] << std::endl;
	} else if (l == 3) {
	  fitOmega[tt][zz] = auxString1.Atof();
	  fitOmegaError[tt][zz] = auxString2.Atof();
	  std::cout << "--omega: " << fitOmega[tt][zz] << " +- " << fitOmegaError[tt][zz] << std::endl;
	} else if (l == 5) {
	  fitBkg[tt][zz] = auxString1.Atof();
	  fitBkgError[tt][zz] = auxString2.Atof();
	  std::cout << "--bkg  : " << fitBkg[tt][zz] << " +- " << fitBkgError[tt][zz] << std::endl;
	}
      }
      inFile.close();
      std::cout << std::endl;
    }
  }
}
