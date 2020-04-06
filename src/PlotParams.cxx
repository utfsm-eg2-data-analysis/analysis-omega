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
TString outputPlotName;

// [D, C, Fe, Pb][Z bin: 3-7], uniD
Double_t fitMean[4][5], fitWidth[4][5], fitYields[4][5];
Double_t fitMeanError[4][5], fitWidthError[4][5], fitYieldsError[4][5];

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void assignOptions();
void printUsage();

void readTextFiles();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();

  readTextFiles();
  
  TCanvas *c = new TCanvas("c", "c", 1200, 1000);
  c->Divide(1,4,0,0); // nx, ny, margins
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetTitleSize(0.12, "t"); // hist title size
  
  // creating and filling histograms
  TH1F *histMean = new TH1F("histMean", "#mu", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);
  TH1F *histWidth = new TH1F("histWidth", "#sigma", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);
  TH1F *histYields = new TH1F("histYields", "#omega number", 4*kinvarNbins, 0., (Double_t) 4*kinvarNbins);

  for (Int_t t = 0; t < 4; t++) { // uniD
    for (Int_t z = 0; z < kinvarNbins; z++) {
      // mean
      histMean->SetBinContent(kinvarNbins*t + z + 1, fitMean[t][z]);
      histMean->SetBinError(kinvarNbins*t + z + 1, fitMeanError[t][z]);
      // width
      histWidth->SetBinContent(kinvarNbins*t + z + 1, fitWidth[t][z]);
      histWidth->SetBinError(kinvarNbins*t + z + 1, fitWidthError[t][z]);
      // yields
      histYields->SetBinContent(kinvarNbins*t + z + 1, fitYields[t][z]);
      histYields->SetBinError(kinvarNbins*t + z + 1, fitYieldsError[t][z]);
    }
  }

  c->cd(1);
  gPad->SetGridx(1);
  histMean->SetLabelSize(0.1, "Y");
  histMean->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  histMean->GetYaxis()->SetTitle("#mu");
  histMean->GetYaxis()->CenterTitle();
  histMean->SetLineColor(kRed);
  histMean->SetLineWidth(3);

  histMean->Draw("E");

  c->cd(2);
  gPad->SetGridx(1);
  histWidth->SetLabelSize(0.1, "Y");
  histWidth->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  histWidth->GetYaxis()->SetTitle("#sigma");
  histWidth->GetYaxis()->CenterTitle();
  histWidth->SetLineColor(kBlack);
  histWidth->SetLineWidth(3);

  histWidth->Draw("E");

  c->cd(3);
  gPad->SetGridx(1);
  histYields->SetLabelSize(0.1, "Y");
  histYields->GetXaxis()->SetNdivisions(kinvarNbins*100 + 4, kFALSE);
  histYields->GetYaxis()->SetTitle("N_{#omega}");
  histYields->GetYaxis()->CenterTitle();
  histYields->SetLineColor(kMagenta+2);
  histYields->SetLineWidth(3);

  histYields->Draw("E");

  c->Print(outputPlotName); // output file
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
  outputPlotName = outDir + kinvarDir + "/roofit" + functionSufix + kinvarSufix + ".png";
}

void readTextFiles() {
  
  TString textFileName;
  TString kinvarAuxSufix;
  
  for (Int_t tt = 0; tt < 4; tt++) { // uniD
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
	  std::cout << "--mean:   " << fitMean[tt][zz] << " +- " << fitMeanError[tt][zz] << std::endl;
	} else if (l == 2) {
	  fitWidth[tt][zz] = auxString1.Atof();
	  fitWidthError[tt][zz] = auxString2.Atof();
	  std::cout << "--width:  " << fitWidth[tt][zz] << " +- " << fitWidthError[tt][zz] << std::endl;
	} else if (l == 3) {
	  fitYields[tt][zz] = auxString1.Atof();
	  fitYieldsError[tt][zz] = auxString2.Atof();
	  std::cout << "--yields: " << fitYields[tt][zz] << " +- " << fitYieldsError[tt][zz] << std::endl;
	}
      }
      inFile.close();
    }
  }
}
