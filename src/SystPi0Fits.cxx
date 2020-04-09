/**************************************/
/* SystPi0Fits.cxx                    */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// fits peak with a gaussian function and bkg with a 1st order polynomial
// - added kinematic dependence as an option

#include "analysisConfig.h"

#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooPolynomial.h"
#include "RooDataHist.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooExtendPdf.h"
#include "RooAbsReal.h"
#include "RooArgSet.h"

using namespace RooFit;

/*** Global variables ***/

TString outDir = proDir + "/out/SystPi0";

// pi0 (make sure those are the same than in analysisConfig.h)
Double_t pi0obtMean = 0.131;
Double_t pi0obtSigma = 0.024;
Double_t pi0Nsigma;
Double_t pi0Range[2]; // to be defined
TString  sigmaName;

// target options
TString targetOption;
TString inputFile1 = "";
TString inputFile2 = "";
TString inputFile3 = "";
TCut    cutTargType;

// kinematic variable options
Int_t flagZ = 0;
Int_t flagQ2 = 0;
Int_t flagNu = 0;
Int_t flagPt2 = 0;

TString kinvarTitle;
TString kinvarName;
TString kinvarSufix;
Int_t   binNumber;
TCut    kinvarCut;

// names
TString plotFile;
TString textFile;

// new!
Int_t    flagNew = 0;
Double_t obtMean;
Double_t obtSigma;
Double_t obtEdges[2] = {0.27, 0.47}; // default
Int_t    obtNbins = 40; // default

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // cuts
  TCut cutAll = cutDIS && cutPipPim && cutPi0;

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  /*** Read previous results ***/

  if (!flagNew) {
    std::cout << std::endl;
    std::cout << "Reading previous file " << textFile << std::endl;
    std::ifstream inFile(textFile);
    
    TString auxString1, auxString2;
    Int_t l = 0; // line counter
    while (inFile >> auxString1 >> auxString2) {
      l++;
      if (l == 1) { // first line
	obtMean = auxString1.Atof();
	std::cout << "Omega Mean for " << targetOption << kinvarSufix << ": " << obtMean << std::endl;
      } else if (l == 2) { // second line
	obtSigma = auxString1.Atof();
	std::cout << "Omega Sigma for " << targetOption << kinvarSufix << ": " << obtSigma << std::endl;
      }
    }
    inFile.close();
    
    // keep fit range
    obtEdges[0] = obtMean - 5*obtSigma;
    obtEdges[1] = obtMean + 5*obtSigma;
    std::cout << "fitRange-" << targetOption << kinvarSufix << " = [" << obtEdges[0] << ", " << obtEdges[1] << "]" << std::endl;
    // round to the 2nd digit
    obtEdges[0] = round(100*(obtEdges[0]))/100;
    obtEdges[1] = round(100*(obtEdges[1]))/100;
    std::cout << "fitRange-" << targetOption << kinvarSufix << " = [" << obtEdges[0] << ", " << obtEdges[1] << "]" << std::endl;
    // number of bins
    obtNbins = (Int_t) ((obtEdges[1] - obtEdges[0])/5e-3);
    std::cout << "obtNbins-" << targetOption << kinvarSufix << " = " << obtNbins << std::endl;
    std::cout << std::endl;
  }

  /*** Fit ***/
  
  // bin x-width = 5 MeV
  Int_t Nbins = obtNbins;
  Double_t fitRangeDown = obtEdges[0]; // preMean.getValV() - 5*preSigma.getValV() = 0.268
  Double_t fitRangeUp = obtEdges[1]; // preMean.getValV() + 5*preSigma.getValV() = 0.468

  Double_t meanIGV = 0.37;
  Double_t meanRangeDown = 0.36;
  Double_t meanRangeUp = 0.39; // 0.38

  Double_t sigmaIGV = 1.75e-2;
  Double_t sigmaRangeDown = 1.6e-2;
  Double_t sigmaRangeUp = 2.3e-2;

  TH1F *dataHist;
  treeExtracted->Draw(Form("wD>>data(%d, %f, %f)", Nbins, fitRangeDown, fitRangeUp), cutAll && cutTargType && kinvarCut, "goff");
  dataHist = (TH1F *)gROOT->FindObject("data");
  Double_t N_d = dataHist->Integral(1,Nbins);
  
  /*** RooFit stuff ***/

  RooRealVar x("IMD", "IMD (GeV)", fitRangeDown, fitRangeUp);

  RooRealVar omegaMean("#mu(#omega)", "Mean of Gaussian", meanIGV, meanRangeDown, meanRangeUp);
  RooRealVar omegaSigma("#sigma(#omega)", "Width of Gaussian", sigmaIGV, sigmaRangeDown, sigmaRangeUp);
  RooGaussian omega("omega", "omega peak", x, omegaMean, omegaSigma);  

  RooRealVar b1("b1", "linear term", 0.1, -10, 10);
  // RooRealVar b2("b2", "quadratic term", 0.1, -10, 10);
  RooChebychev bkg("bkg", "background", x, RooArgList(b1));

  // model(x) = sig_yield*sig(x) + bkg_yield*bkg(x)
  RooRealVar nsig("N_{#omega}", "omega yields", 0., dataHist->GetEntries());
  RooRealVar nbkg("N_{b}", "bkg yields", 0., dataHist->GetEntries());
  RooAddPdf model("model", "model", RooArgList(omega, bkg), RooArgList(nsig, nbkg));
  
  // define data
  RooDataHist data("data", "my data", x, dataHist);

  // define frame
  RooPlot *frame = x.frame(Title("IMD(#pi^{+} #pi^{-} #pi^{0}) for " + targetOption + " in" + kinvarTitle),
			   Bins(Nbins));
  
  // fit the normal way
  RooFitResult *r1 = model.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));

  r1->Print("v");

  // define constraints
  RooGaussian conSigma("conSigma", "conSigma", omegaSigma, RooConst(0.02), RooConst(0.001));

  RooProdPdf cmodel("cmodel", "model with constraint", RooArgSet(model, conSigma));
  
  // fit constraint model
  RooFitResult *r2 = cmodel.fitTo(data, Constrain(conSigma), Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));

  r2->Print("v");
  
  // draw data and fit into frame
  data.plotOn(frame, Name("Data")); // DataError(RooAbsData::SumW2)
  cmodel.plotOn(frame, Name("Model"), LineColor(kRed));
  cmodel.plotOn(frame, Components("bkg"), LineStyle(kDashed), LineColor(kBlue));
  
  // add params
  cmodel.paramOn(frame, Layout(0.1, 0.3, 0.9)); // x1, x2, delta-y
  frame->getAttText()->SetTextSize(0.03);

  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->SetTitle("Counts");
  frame->GetYaxis()->CenterTitle();
  
  // check how that integration goes...
  Double_t N_omega = nsig.getValV();
  Double_t N_bkg = nbkg.getValV();
  Double_t N_sum = N_omega + N_bkg;
    
  // draw!
  TCanvas *c = new TCanvas("c", "c", 1366, 768);
  frame->Draw();
  
  // draw lines
  drawVerticalLineGrayest(omegaMean.getValV() - 3*omegaSigma.getValV());
  drawVerticalLineBlack(omegaMean.getValV());
  drawVerticalLineGrayest(omegaMean.getValV() + 3*omegaSigma.getValV());
  
  c->Print(plotFile); // output file

  /*** Save data from fit ***/

  std::cout << "Writing " << textFile << " ..." << std::endl;
  std::ofstream outFinalFile(textFile, std::ios::out); // output file
  // line 1: omegaMean
  outFinalFile << omegaMean.getValV() << "\t" << omegaMean.getError() << std::endl;
  // line 2: omegaSigma
  outFinalFile << omegaSigma.getValV() << "\t" << omegaSigma.getError() << std::endl;
  // line 3: omegaYields (directly from parameter) (METHOD 1)
  outFinalFile << nsig.getValV() << "\t\t" << nsig.getError() << std::endl;
  // line 4: b1
  outFinalFile << b1.getValV() << "\t" << b1.getError() << std::endl;
  // line 5: bkgYields
  outFinalFile << nbkg.getValV() << "\t\t" << nbkg.getError() << std::endl;
  std::cout << "Text file " << textFile << " has been created!" << std::endl;
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./SystPi0Fits -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:z:q:n:p:Ss:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'z': flagZ = 1; binNumber = atoi(optarg); break;
    case 'q': flagQ2 = 1; binNumber = atoi(optarg); break;
    case 'n': flagNu = 1; binNumber = atoi(optarg); break;
    case 'p': flagPt2 = 1; binNumber = atoi(optarg); break;
    case 'S': flagNew = 1; break;
    case 's': pi0Nsigma = atof(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./SystPi0Fits -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing SystPi0Fits program. Chosen parameters are:" << std::endl;
  std::cout << "  targetOption=" << targetOption << std::endl;
  std::cout << "  kinvarName=" << kinvarName << std::endl;
  std::cout << "  binNumber=" << binNumber << std::endl;
  std::cout << "  flagNew=" << flagNew << std::endl;
  std::cout << "  pi0Nsigma=" << pi0Nsigma << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "SystPi0Fits program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./SystPi0Fits -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./SystPi0Fits -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./SystPi0Fits -[kinvar][number]" << std::endl;
  std::cout << "    analyzes respective kinematic variable bin" << std::endl;
  std::cout << "    z[3-7] : analyzes specific Z bin" << std::endl;
  std::cout << "    q[1-5] : analyzes specific Q2 bin" << std::endl;
  std::cout << "    n[1-5] : analyzes specific Nu bin" << std::endl;
  std::cout << "    p[1-5] : analyzes specific Pt2 bin" << std::endl;
  std::cout << std::endl;
  std::cout << "./SystPi0Fits -S" << std::endl;
  std::cout << "    plots a default 5sigma range" << std::endl;
  std::cout << "    without this option, it sets a new 5sigma range based on previous results" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "./SystPi0Fits -s[3.-5.]" << std::endl;
  std::cout << "    selects sigma range around pi0 peak" << std::endl;
  std::cout << "    number MUST be a double between 3. and 5." << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for targets, unified D
  if (targetOption == "D") {
    inputFile1 = dataDir + "/C/comb_C-thickD2.root";
    inputFile2 = dataDir + "/Fe/comb_Fe-thickD2.root";
    inputFile3 = dataDir + "/Pb/comb_Pb-thinD2.root";
    cutTargType = "TargType == 1";
  } else if (targetOption == "C") {
    inputFile1 = dataDir + "/C/comb_C-thickD2.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Fe") {
    inputFile1 = dataDir + "/Fe/comb_Fe-thickD2.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Pb") {
    inputFile1 = dataDir + "/Pb/comb_Pb-thinD2.root";
    cutTargType = "TargType == 2";
  }
  // for kinvar
  Double_t lowEdge, highEdge;
  if (flagZ) {
    lowEdge = edgesZ[binNumber-3];
    highEdge = edgesZ[binNumber+1-3];
    kinvarSufix = Form("-z%d", binNumber);
    kinvarName = "Z";
  } else if (flagQ2) {
    lowEdge = edgesQ2[binNumber-1];
    highEdge = edgesQ2[binNumber+1-1];
    kinvarSufix = Form("-q%d", binNumber);
    kinvarName = "Q2";
  } else if (flagNu) {
    lowEdge = edgesNu[binNumber-1];
    highEdge = edgesNu[binNumber+1-1];
    kinvarSufix = Form("-n%d", binNumber);
    kinvarName = "Nu";
  } else if (flagPt2) {
    lowEdge = edgesPt2[binNumber-1];
    highEdge = edgesPt2[binNumber+1-1];
    kinvarSufix = Form("-p%d", binNumber);
    kinvarName = "Pt2";
  }
  kinvarCut = Form("%f < ", lowEdge) + kinvarName + " && " + kinvarName + Form(" < %f", highEdge);
  kinvarTitle = Form(" (%.02f < ", lowEdge) + kinvarName + Form(" < %.02f)", highEdge);
  outDir = outDir + "/" + kinvarName;
  // for nsigma
  sigmaName = Form("%.01fsigma", pi0Nsigma);
  outDir = outDir + "/" + sigmaName;
  // for pi0!
  pi0Range[0] = pi0obtMean - pi0Nsigma*pi0obtSigma;
  pi0Range[1] = pi0obtMean + pi0Nsigma*pi0obtSigma;
  cutPi0 = Form("%.03f < pi0M && pi0M < %.03f", pi0Range[0], pi0Range[1]); // overwrite it!
  // names
  plotFile = outDir + "/pi0fit-" + targetOption + kinvarSufix + ".png";
  textFile = outDir + "/pi0fit-" + targetOption + kinvarSufix + ".dat";
}
