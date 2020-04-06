/**************************************/
/* MakeFits-Final.cxx                 */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// bkg-100/bkg-final-fit-A_D-zN.txt files are mandatory!
// It fits the both peaks with a Gaussian/Lorentzian Function

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TCut.h"
#include "TString.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TF1.h"
#include "TLatex.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TPaveText.h"
#include "TFitResult.h"

/*** Global variables ***/

// Zh binning
Int_t binNumberZh; // [3-7]: binning on (none by default)
Double_t maxZh = 1.0;
Double_t minZh = 0.2;
Int_t binsZh = 8; // number of bins in Z!
Double_t stepZh = (maxZh - minZh)/binsZh;
Double_t lowEdgeZh;
Double_t highEdgeZh;

// Parameters (to be assigned by the options)
TString titleZh; // default, as above
TString sufixZhBin;

// inputs
TString inputFolder = "/home/borquez/omega/MakePlots/MyFiles/";
TString inputRootFile;

// targets
TString targetOption;
Int_t targetTypeOption = 0;
TString titleTarget;
TString targetFull;

// for reading file
TString inputTextFile;
TString functionOption;
Int_t functionNPars;

// outputs
TString outputTextFile;
TString outputPlot;

// cuts
TCut cutZh;
TCut cutTargType; // 1: liquid | 2: solid (none by default)
TCut cutDIS = "Q2 > 1 && W > 2";
TCut cutPi0 = "0.059 < mpi0 && mpi0 < 0.209"; // mikewood cut
TCut cutPipPim = "0.48 > mpippim || 0.51 < mpippim"; // mikewood cut

/*** New ranges ***/
// [target][zbin(3-7)][min-max]
Double_t obsOmegaPeaks[6][5][2] = {{{0.3, 0.41}, {0.28, 0.48}, {0.3, 0.45}, {0.35, 0.5}, {0.3, 0.5}},
				   {{0.3, 0.48}, {0.35, 0.50}, {0.3, 0.45}, {0.3, 0.45}, {0.3, 0.47}},
				   {{0.3, 0.45}, {0.3, 0.5}, {0.3, 0.45}, {0.3, 0.48}, {0.3, 0.47}},
				   {{0.3, 0.48}, {0.3, 0.48}, {0.32, 0.45}, {0.31, 0.42}, {0.3, 0.45}},
				   {{0.32, 0.45}, {0.32, 0.48}, {0.28, 0.43}, {0.28, 0.45}, {0.32, 0.46}},
				   {{0.32, 0.50}, {0.3, 0.48}, {0.3, 0.45}, {0.3, 0.48}, {0.3, 0.45}}};

Double_t obsEtaPeaks[6][5][2] = {{{0.1, 0.18}, {0.11, 0.19}, {0., 0.01}, {0.13, 0.18}, {0.1, 0.15}},
				 {{0.1, 0.18}, {0.08, 0.18}, {0.1, 0.16}, {0.1, 0.16}, {0.1, 0.18}},
				 {{0.1, 0.15}, {0.11, 0.17}, {0.09, 0.17}, {0.1, 0.18}, {0.1, 0.17}},
				 {{0.11, 0.15}, {0.11, 0.17}, {0.1, 0.15}, {0.1, 0.18}, {0.1, 0.17}},
				 {{0.12, 0.16}, {0.11, 0.17}, {0.12, 0.18}, {0.09, 0.16}, {0., 0.01}},
				 {{0.12, 0.17}, {0.12, 0.16}, {0.11, 0.2}, {0.1, 0.21}, {0.1, 0.15}}};

// indexes
Int_t indexTarget;
Int_t indexZh;

// peak option
TString peakOption = "g"; // gaussian by default
TString peakOptionShort;

/*** Declaration of functions ***/
void assignOptions();
inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
// Mathematical functions
Double_t thirdPol(Double_t *x, Double_t *par);
Double_t fourthPol(Double_t *x, Double_t *par);
Double_t lorentzianPeak(Double_t *x, Double_t *par);
Double_t gaussianPeak(Double_t *x, Double_t *par);
Double_t bkgFunction(Double_t *x, Double_t *par);
Double_t peakFunction(Double_t *x, Double_t *par);
Double_t globalFunction(Double_t *x, Double_t *par);
Double_t globalFunction_v2(Double_t *x, Double_t *par);
Int_t integrateGaussian(Double_t par0, Double_t par1, Double_t par2);
Int_t firstBin(Double_t par0, Double_t par1, Double_t par2);
Int_t lastBin(Double_t par0, Double_t par1, Double_t par2);
Int_t integrateGaussianInRange(Double_t par0, Double_t par1, Double_t par2, Int_t a, Int_t b);

/*** Begin of program  ***/
int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();

  /*** Reading bkg-fit file ***/
  std::cout << "Reading file " << inputTextFile << "..." << std::endl;
  std::ifstream inFile(inputTextFile);
  TString auxLine;
  Double_t functionParam[10]; // 10 just in case, it should not be more than 8
  while (inFile >> auxLine) {
    // the most simple way to tokenize an string thanks to ROOT
    std::cout << auxLine << std::endl;
    TObjArray *auxArray = auxLine.Tokenize(":");
    functionOption = (((TObjString *)(auxArray->At(0)))->String()); // first string
    functionNPars = auxArray->GetEntries() - 1;
    for (Int_t i = 0; i < functionNPars; i++) {
      functionParam[i] = (((TObjString *)(auxArray->At(i+1)))->String()).Atof(); // i+1 to ignore function name
    }
    break; // after reading first line
  }
  inFile.close();
  std::cout << "Reading file " << inputTextFile << " ended!" << std::endl;

  printOptions();

  TH1F *dataHist;
  TFile *File = new TFile(inputFolder + inputRootFile);
  TTree *treeExtracted = (TTree*)File->Get("outdata");
  TCut cutAll = cutPi0 && cutDIS && cutPipPim && cutTargType && cutZh;
  
  /*** Setting alias ***/
  // pip
  treeExtracted->SetAlias("mpip", "TMath::Sqrt(Epip*Epip - (fX[2]*fX[2] + fY[2]*fY[2] + fZ[2]*fZ[2]))");
  treeExtracted->SetAlias("Epip", "TMath::Sqrt(fX[2]*fX[2] + fY[2]*fY[2] + fZ[2]*fZ[2] + 0.13957*0.13957)");
  treeExtracted->SetAlias("p2pip", "fX[2]*fX[2] + fY[2]*fY[2] + fZ[2]*fZ[2]");
  // pim
  treeExtracted->SetAlias("mpim", "TMath::Sqrt(Epim*Epim - (fX[3]*fX[3] + fY[3]*fY[3] + fZ[3]*fZ[3]))");
  treeExtracted->SetAlias("Epim", "TMath::Sqrt(fX[3]*fX[3] + fY[3]*fY[3] + fZ[3]*fZ[3] + 0.13957*0.13957)");
  treeExtracted->SetAlias("p2pim", "fX[3]*fX[3] + fY[3]*fY[3] + fZ[3]*fZ[3]");
  // (both)
  treeExtracted->SetAlias("mpippim", "mpip + mpim");
  // pi0
  treeExtracted->SetAlias("Pxpi0", "fX[0] + fX[1]");
  treeExtracted->SetAlias("Pypi0", "fY[0] + fY[1]");
  treeExtracted->SetAlias("Pzpi0", "fZ[0] + fZ[1]");
  treeExtracted->SetAlias("p2pi0", "Pxpi0*Pxpi0 + Pypi0*Pypi0 + Pzpi0*Pzpi0");
  treeExtracted->SetAlias("cos_theta", "(fX[0]*fX[1] + fY[0]*fY[1] + fZ[0]*fZ[1])/(fE[0]*fE[1])"); // original
  treeExtracted->SetAlias("mpi0", "TMath::Sqrt(2*fE[0]*fE[1]*(1 - cos_theta))"); // original
  // omega
  treeExtracted->SetAlias("Eomega", "Epip + Epim + fE[0] + fE[1]");
  treeExtracted->SetAlias("Pxomega", "fX[0] + fX[1] + fX[2] + fX[3]");
  treeExtracted->SetAlias("Pyomega", "fY[0] + fY[1] + fY[2] + fY[3]");
  treeExtracted->SetAlias("Pzomega", "fZ[0] + fZ[1] + fZ[2] + fZ[3]");
  treeExtracted->SetAlias("p2omega", "Pxomega*Pxomega + Pyomega*Pyomega + Pzomega*Pzomega");
  treeExtracted->SetAlias("momega", "TMath::Sqrt(Eomega*Eomega - Pxomega*Pxomega - Pyomega*Pyomega - Pzomega*Pzomega)");
  treeExtracted->SetAlias("deltamomega", "momega - mpi0 - mpip - mpim");

  treeExtracted->Draw("deltamomega>>data(100, 0., 1.6)", cutAll, "goff"); // EDITED!

  TCanvas *c = new TCanvas("c", "c", 1366, 768);
  c->SetGrid();

  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  
  dataHist = (TH1F *)gROOT->FindObject("data");
  dataHist->SetTitle("Omega Mass Difference in " + titleTarget + titleZh);
  dataHist->GetXaxis()->SetTitle("GeV");
  dataHist->GetYaxis()->SetTitle("Events");
  dataHist->SetLineColor(kBlack);

  /*** The fitting ***/

  // 1) fitting Eta peak: testFcnA & testParamA
  TF1 *testFcnA = new TF1("testFcnA", "gaus",
			  obsEtaPeaks[indexTarget][indexZh][0], obsEtaPeaks[indexTarget][indexZh][1]);
  // suggestion: set as initial guess value the eta mass mean value
  testFcnA->SetParameter(1, 0.135);
  testFcnA->SetParLimits(2, 2e-2, 4e-2);
  dataHist->Fit("testFcnA", "REN0", "goff");
  Double_t testParamA[3];
  testFcnA->GetParameters(testParamA);

  // 2) fitting Omega peak
  TF1 *testFcn1 = new TF1("testFcn1", "gaus",
			  obsOmegaPeaks[indexTarget][indexZh][0], obsOmegaPeaks[indexTarget][indexZh][1]);
  // suggestion: set as initial guess value the omega mass mean value
  testFcn1->SetParameter(1, 0.37); // new solution method: testFcn1->FixParameter(1, 0.37);
  testFcn1->SetParLimits(2, 2e-2, 4e-2);  
  dataHist->Fit("testFcn1", "REN0", "goff");
  Double_t testParam1[3];
  testFcn1->GetParameters(testParam1);
  
  // 3) fitting everything
  TF1 *testFcn2 = new TF1("testFcn2", globalFunction_v2, 0., 1.6, 3 + 3 + functionNPars);

  for (Int_t ii = 0; ii < (3 + 3 + functionNPars); ii++) {
    if (ii < 3) testFcn2->SetParameter(ii, testParamA[ii]);
    if (peakOptionShort == "gaus") { // omega
      if (ii > 2 && ii < 6) testFcn2->SetParameter(ii, testParam1[ii - 3]);
      else if (ii > 5) testFcn2->SetParameter(ii, functionParam[ii - 3 - 3]);
    } else if (peakOptionShort == "lorentz") {
      if (ii == 3) testFcn2->SetParameter(ii, testParam1[ii - 3]);
      else if (ii == 4) testFcn2->SetParameter(ii + 1, testParam1[ii - 3]);
      else if (ii == 5) testFcn2->SetParameter(ii - 1, testParam1[ii - 3]);
      else if (ii > 5) testFcn2->SetParameter(ii, functionParam[ii - 3 - 3]);
    }
  }

  // setting parameters limits to eta and omega widths
  testFcn2->SetParLimits(2, 2e-2, 4e-2);
  testFcn2->SetParLimits(5, 2e-2, 4e-2);
  
  dataHist->Fit("testFcn2", "REN0", "goff");

  Double_t paramsToSave[6 + functionNPars];
  testFcn2->GetParameters(paramsToSave);
  
  /*** The drawing ***/
  dataHist->Draw("E");  

  TF1 *globalFcn = new TF1("globalFcn", globalFunction_v2, 0., 1.6, 3 + 3 + functionNPars);
  globalFcn->SetLineWidth(3);
  globalFcn->SetNpx(500);
  globalFcn->SetLineColor(kBlue+1);
  globalFcn->SetParameters(paramsToSave);
  globalFcn->Draw("same");

  TF1 *etaFcn = new TF1("etaFcn", gaussianPeak, 0., 1.6, 3); // eta always gaussian
  etaFcn->SetLineWidth(3);
  etaFcn->SetNpx(500);
  etaFcn->SetLineColor(kRed+1);
  etaFcn->SetParameters(paramsToSave);
  etaFcn->Draw("same");

  TF1 *signalFcn = new TF1("signalFcn", peakFunction, 0., 1.6, 3);
  signalFcn->SetLineWidth(3);
  signalFcn->SetNpx(500);
  signalFcn->SetLineColor(kMagenta+3);
  signalFcn->SetParameters(&paramsToSave[3]);
  signalFcn->Draw("same");
  
  TF1 *backFcn = new TF1("backFcn", bkgFunction, 0., 1.6, functionNPars);
  backFcn->SetLineStyle(7);
  backFcn->SetLineWidth(3);
  backFcn->SetLineColor(kGreen+1);
  backFcn->SetParameters(&paramsToSave[6]);
  backFcn->Draw("same");
  
  // legend
  TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
  legend->AddEntry(dataHist, "Data", "le");
  legend->AddEntry(backFcn, "Background", "l");
  legend->AddEntry(etaFcn, "Eta Peak", "l");
  legend->AddEntry(signalFcn, "Omega Peak", "l");
  legend->AddEntry(globalFcn, "Global Fit", "l");
  legend->Draw();
  
  TPaveText *textBlock = new TPaveText(0.7, 0.60, 0.9, 0.68, "NB NDC");
  textBlock->SetShadowColor(kWhite);
  textBlock->AddText(Form("#chi^{2} / ndf = %.03f", testFcn2->GetChisquare()/testFcn2->GetNDF()));
  textBlock->SetTextColor(kBlue+1);
  textBlock->Draw();

  TLatex *t = new TLatex(.02, .95, "#scale[0.70]{M_{#omega} - M_{#pi^{0}} - M_{#pi^{+}} - M_{#pi^{-}}}");
  t->SetTextFont(152);
  t->SetNDC(kTRUE);
  t->Draw();

  c->Print(outputPlot);

  /*** Saving results ***/

  TString Chi2ndf = Form("%.3f", testFcn2->GetChisquare()/testFcn2->GetNDF());
  TString omegaMean = Form("%.2e", testFcn2->GetParameter(4));
  TString omegaMeanError = Form("%.2e", testFcn2->GetParError(4));
  TString omegaWidth = Form("%.2e", testFcn2->GetParameter(5));
  TString omegaWidthError = Form("%.2e", testFcn2->GetParError(5));

  TString etaMean = Form("%.2e", testFcn2->GetParameter(1));
  TString etaMeanError = Form("%.2e", testFcn2->GetParError(1));
  TString etaWidth = Form("%.2e", testFcn2->GetParameter(2));
  TString etaWidthError = Form("%.2e", testFcn2->GetParError(2));
  
  std::cout << "Writing " << outputTextFile << " ..." << std::endl;  
  std::ofstream outFinalFile(outputTextFile, std::ios::out);
  // first line: chi2/ndf
  outFinalFile << Chi2ndf << std::endl;
  // second line: omega mean, error
  outFinalFile << omegaMean << ":" << omegaMeanError << std::endl;
  // third line: omega width, error
  outFinalFile << omegaWidth << ":" << omegaWidthError << std::endl;
  // fourth line: omega number, error
  Int_t omegaNumber = integrateGaussian(testFcn2->GetParameter(3),
					testFcn2->GetParameter(4),
					testFcn2->GetParameter(5));
  outFinalFile << omegaNumber << ":" << 0 << std::endl;
  // fifth line: eta mean, error
  outFinalFile << etaMean << ":" << etaMeanError << std::endl;
  // sixth line: eta width, error
  outFinalFile << etaWidth << ":" << etaWidthError << std::endl;
  // seventh line: eta number, error
  Int_t etaNumber = integrateGaussian(testFcn2->GetParameter(0),
				      testFcn2->GetParameter(1),
				      testFcn2->GetParameter(2));
  outFinalFile << etaNumber << ":" << 0 << std::endl;
  // eighth line: bkg number, error
  Int_t bkgNumber = integrateGaussian(testFcn2->GetParameter(6),
				      testFcn2->GetParameter(7),
				      testFcn2->GetParameter(8));
  outFinalFile << bkgNumber << ":" << 0 << std::endl;
  // ninth line: bkg number in omega range, error (wrong)
  Int_t omegaFirstBin = firstBin(testFcn2->GetParameter(3),
				 testFcn2->GetParameter(4),
				 testFcn2->GetParameter(5));
  Int_t omegaLastBin = lastBin(testFcn2->GetParameter(3),
			       testFcn2->GetParameter(4),
			       testFcn2->GetParameter(5));  
  Int_t bkgInOmegaNumber = integrateGaussianInRange(testFcn2->GetParameter(6),
						    testFcn2->GetParameter(7),
						    testFcn2->GetParameter(8),
						    omegaFirstBin, omegaLastBin);
  outFinalFile << bkgInOmegaNumber << ":" << 0 << std::endl;
  // tenth line: bkg number in eta range, error (wrong)
  Int_t etaFirstBin = firstBin(testFcn2->GetParameter(0),
			       testFcn2->GetParameter(1),
			       testFcn2->GetParameter(2));
  Int_t etaLastBin = lastBin(testFcn2->GetParameter(0),
			     testFcn2->GetParameter(1),
			     testFcn2->GetParameter(2));
  Int_t bkgInEtaNumber = integrateGaussianInRange(testFcn2->GetParameter(6),
						  testFcn2->GetParameter(7),
						  testFcn2->GetParameter(8),
						  etaFirstBin, etaLastBin);
  outFinalFile << bkgInEtaNumber << ":" << 0 << std::endl;
  outFinalFile.close();
  std::cout << "File " << outputTextFile << " created!" << std::endl;  
}

/*** Functions ***/
inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Write -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hz:t:T:F:")) != -1) {
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'z': binNumberZh = atoi(optarg); break;
    case 't': targetOption = optarg; break;
    case 'T': targetTypeOption = atoi(optarg); break;
    case 'F': peakOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeFits-Final -h to get help." << std::endl;
      exit(0);
      break;
    }
  }
}

void assignOptions() {
  // for target option
  if (targetOption == "C") targetFull = "C-thickD2";
  else if (targetOption == "Fe") targetFull = "Fe-thickD2";
  else if (targetOption == "Pb") targetFull = "Pb-thinD2";
  // for targetType option
  if (targetTypeOption > 0) cutTargType = Form("TargType == %d", targetTypeOption);
  if (targetTypeOption == 1) titleTarget = targetOption + "_D";
  else if (targetTypeOption == 2) titleTarget = targetOption + "_" + targetOption;
  // for Zh binning
  if (binNumberZh == 3) {
    lowEdgeZh = 0.5;
    highEdgeZh = 0.557;
  } else if (binNumberZh == 4) {
    lowEdgeZh = 0.557;
    highEdgeZh = 0.617;
  } else if (binNumberZh == 5) {
    lowEdgeZh = 0.617;
    highEdgeZh = 0.689;
  } else if (binNumberZh == 6) {
    lowEdgeZh = 0.689;
    highEdgeZh = 0.784;
  } else if (binNumberZh == 7) {
    lowEdgeZh = 0.784;
    highEdgeZh = 1.;
  }
  cutZh = Form("%f < Z && Z < %f", lowEdgeZh, highEdgeZh);
  titleZh = Form(" (%.02f < Z < %.02f)", lowEdgeZh, highEdgeZh);
  sufixZhBin = Form("-z%d", binNumberZh);
  // name of input files
  inputTextFile = "bkg-100/bkg-final-fit-" + titleTarget + "-z" + binNumberZh + ".txt"; // EDITED!
  inputRootFile = "wout_" + targetFull + ".root";
  // name of output files
  outputTextFile = "final-fit-" + titleTarget + sufixZhBin + ".txt";
  outputPlot = "final-fit-" + titleTarget + sufixZhBin + ".png";
  // indexes
  if (titleTarget == "C_C") indexTarget = 0;
  else if (titleTarget == "C_D") indexTarget = 1;
  else if (titleTarget == "Fe_Fe") indexTarget = 2;
  else if (titleTarget == "Fe_D") indexTarget = 3;
  else if (titleTarget == "Pb_Pb") indexTarget = 4;
  else if (titleTarget == "Pb_D") indexTarget = 5;
  indexZh = binNumberZh - 3;
  // for peak option
  if (peakOption == "g") peakOptionShort = "gaus";
  else if (peakOption == "l") peakOptionShort = "lorentz";
}

void printOptions() {
  std::cout << "Target: " << titleTarget << std::endl;
  std::cout << "Zh bin number: " << binNumberZh << std::endl;
  std::cout << "Range of omega peak: [" << obsOmegaPeaks[indexTarget][indexZh][0] << ", " << obsOmegaPeaks[indexTarget][indexZh][1] << "]" << std::endl;
  std::cout << "Range of eta peak: [" << obsEtaPeaks[indexTarget][indexZh][0] << ", " << obsEtaPeaks[indexTarget][indexZh][1] << "]" << std::endl;
}

void printUsage() {
  std::cout << "MakeFits-Final program. Usage is:" << std::endl;
  std::cout << "\t./MakeFits-Final -[options] -[more options]" << std::endl;
  std::cout << "\t h \t\t prints help and exit program" << std::endl;
  std::cout << "\t t[target] \t selects target: C | Fe | Pb" << std::endl;
  std::cout << "\t T[targetType] \t selects targetType: 1 (liquid) | 2 (solid)" << std::endl;
  std::cout << "\t z[3-7] \t analyzes that specific bin" << std::endl;
  std::cout << "\t F[function] \t fits the peak with different functions: g (gaussian, default) | l (lorentzian)" << std::endl;
}

Double_t thirdPol(Double_t *x, Double_t *par) {
  return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0];
}

Double_t fourthPol(Double_t *x, Double_t *par) {
  return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0] + par[4]*x[0]*x[0]*x[0]*x[0];
}

Double_t lorentzianPeak(Double_t *x, Double_t *par) {
  return (0.5*par[0]*par[1]/TMath::Pi())/TMath::Max(1.e-10, (x[0] - par[2])*(x[0] - par[2]) + .25*par[1]*par[1]);
}

Double_t gaussianPeak(Double_t *x, Double_t *par) {
  return par[0]*TMath::Exp(-0.5*((x[0] - par[1])/par[2])*((x[0] - par[1])/par[2]));
}

Double_t bkgFunction(Double_t *x, Double_t *par) {
  if (functionOption == "gaus") return gaussianPeak(x, par);
  else if (functionOption == "pol3+lorentz") return thirdPol(x, par) + lorentzianPeak(x, &par[4]);
  else if (functionOption == "pol4+lorentz") return fourthPol(x, par) + lorentzianPeak(x, &par[5]);
}

Double_t peakFunction(Double_t *x, Double_t *par) {
  if (peakOption == "g") return gaussianPeak(x, par);
  else if (peakOption == "l") return lorentzianPeak(x, par);
}

Double_t globalFunction(Double_t *x, Double_t *par) {
  return peakFunction(x, par) + bkgFunction(x, &par[3]);
}

Double_t globalFunction_v2(Double_t *x, Double_t *par) {
  return gaussianPeak(x, par) + peakFunction(x, &par[3]) + bkgFunction(x, &par[6]);
}

// based on Integration-Test.cxx
Int_t integrateGaussian(Double_t par0, Double_t par1, Double_t par2) {
  TF1 *function = new TF1("function", "gaus", 0, 1.6);
  function->SetParameters(par0, par1, par2);
  
  TH1F *hist = new TH1F("hist", "", 100, 0, 1.6);
  Int_t maximum = 0;
  while (maximum < par0) {
    hist->FillRandom("function", 1);
    maximum = hist->GetMaximum();
  }
  Int_t integral = hist->Integral();
  delete hist;
  return integral;
}

Int_t firstBin(Double_t par0, Double_t par1, Double_t par2) {
  TF1 *function = new TF1("function", "gaus", 0, 1.6);
  function->SetParameters(par0, par1, par2);
  TH1F *hist = new TH1F("hist", "", 100, 0, 1.6);
  Int_t maximum = 0;
  while (maximum < par0) {
    hist->FillRandom("function", 1);
    maximum = hist->GetMaximum();
  }
  Int_t bin = hist->FindFirstBinAbove();
  delete hist;
  return bin;
}

Int_t lastBin(Double_t par0, Double_t par1, Double_t par2) {
  TF1 *function = new TF1("function", "gaus", 0, 1.6);
  function->SetParameters(par0, par1, par2);
  TH1F *hist = new TH1F("hist", "", 100, 0, 1.6);
  Int_t maximum = 0;
  while (maximum < par0) {
    hist->FillRandom("function", 1);
    maximum = hist->GetMaximum();
  }
  Int_t bin = hist->FindLastBinAbove();
  delete hist;
  return bin;
}

Int_t integrateGaussianInRange(Double_t par0, Double_t par1, Double_t par2, Int_t a, Int_t b) {
  TF1 *function = new TF1("function", "gaus", 0, 1.6);
  function->SetParameters(par0, par1, par2);
  
  TH1F *hist = new TH1F("hist", "", 100, 0, 1.6);
  Int_t maximum = 0;
  while (maximum < par0) {
    hist->FillRandom("function", 1);
    maximum = hist->GetMaximum();
  }
  Int_t integral = hist->Integral(a, b);
  delete hist;
  return integral;
}
