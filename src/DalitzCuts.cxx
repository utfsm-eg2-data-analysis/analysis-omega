/**************************************/
/* DalitzCuts.cxx                     */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

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

// Z binning
Int_t binNumberZ; // [3-7]: binning on (none by default)
Double_t lowEdgeZ;
Double_t highEdgeZ;

// Parameters (to be assigned by the options)
TString titleZ; // default, as above
TString sufixZBin;

// targets
TString targetOption;
Int_t targetTypeOption;
TString titleTarget;
TString targetFull;

// for reading file
TString inputFolder = "/home/borquez/omega/EG2Pruned/"; // hardcoded
TString inputRootFile;
TString inputTextFile;
TString outputTextFile;
TString outputPlot;

// cuts
TCut cutDIS = "Q2 > 1 && W > 2";
TCut cutPi0 = "0.059 < mpi0 && mpi0 < 0.209"; // mikewood cut
TCut cutPipPim = "0.48 > mpippim || 0.51 < mpippim"; // mikewood cut
TCut cutZ;
TCut cutTargType; // 1: liquid | 2: solid (none by default)

// constants
Double_t massPionCharged = 0.13957;
Double_t massPionNeutral = 0.135;
Double_t massOmega = 0.782;

void assignOptions();
inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  TH1F *dataHist;
  TFile *File = new TFile(inputFolder + inputRootFile);
  TTree *treeExtracted = (TTree*)File->Get("outdata");
  TCut cutAll = cutPi0 && cutDIS && cutPipPim && cutTargType && cutZ;
  
  /*** Setting alias ***/

  // pip
  treeExtracted->SetAlias("p2pip", "fX[2]*fX[2] + fY[2]*fY[2] + fZ[2]*fZ[2]");
  treeExtracted->SetAlias("E2pip", "p2pip + 0.13957*0.13957");
  treeExtracted->SetAlias("m2pip", "E2pip - p2pip");
  treeExtracted->SetAlias("mpip", "TMath::Sqrt(m2pip)");
  treeExtracted->SetAlias("Epip", "TMath::Sqrt(E2pip)");
  // pim
  treeExtracted->SetAlias("p2pim", "fX[3]*fX[3] + fY[3]*fY[3] + fZ[3]*fZ[3]");
  treeExtracted->SetAlias("E2pim", "p2pim + 0.13957*0.13957");
  treeExtracted->SetAlias("m2pim", "E2pim - p2pim");
  treeExtracted->SetAlias("mpim", "TMath::Sqrt(m2pim)");
  treeExtracted->SetAlias("Epim", "TMath::Sqrt(E2pim)");
  // pi0
  treeExtracted->SetAlias("Pxpi0", "fX[0] + fX[1]");
  treeExtracted->SetAlias("Pypi0", "fY[0] + fY[1]");
  treeExtracted->SetAlias("Pzpi0", "fZ[0] + fZ[1]");
  treeExtracted->SetAlias("p2pi0", "Pxpi0*Pxpi0 + Pypi0*Pypi0 + Pzpi0*Pzpi0");
  treeExtracted->SetAlias("cos_theta", "(fX[0]*fX[1] + fY[0]*fY[1] + fZ[0]*fZ[1])/(fE[0]*fE[1])"); // original
  treeExtracted->SetAlias("m2pi0", "2*fE[0]*fE[1]*(1 - cos_theta)"); // original
  treeExtracted->SetAlias("mpi0", "TMath::Sqrt(m2pi0)");
  treeExtracted->SetAlias("E2pi0", "m2pi0 + p2pi0");
  // crossed terms
  treeExtracted->SetAlias("p1p2", "fX[2]*fX[3] + fY[2]*fY[3] + fZ[2]*fZ[3]");
  treeExtracted->SetAlias("E1E2", "TMath::Sqrt(E2pip*E2pim)");
  treeExtracted->SetAlias("p2p3", "fX[3]*Pxpi0 + fY[3]*Pypi0 + fZ[3]*Pzpi0");
  treeExtracted->SetAlias("E2E3", "TMath::Sqrt(E2pim*E2pi0)");
  treeExtracted->SetAlias("p1p3", "fX[2]*Pxpi0 + fY[2]*Pypi0 + fZ[2]*Pzpi0");
  treeExtracted->SetAlias("E1E3", "TMath::Sqrt(E2pip*E2pi0)");
  // dalitz plots!
  treeExtracted->SetAlias("m2pippim", "m2pip + m2pim + 2*(E1E2 - p1p2)");
  treeExtracted->SetAlias("m2pimpi0", "m2pim + m2pi0 + 2*(E2E3 - p2p3)");
  treeExtracted->SetAlias("m2pippi0", "m2pip + m2pi0 + 2*(E1E3 - p1p3)");
  // for the cuts
  treeExtracted->SetAlias("mpippim", "TMath::Sqrt(m2pippim)");
  treeExtracted->SetAlias("mpimpi0", "TMath::Sqrt(m2pimpi0)");
  treeExtracted->SetAlias("mpippi0", "TMath::Sqrt(m2pippi0)");
  // omega
  treeExtracted->SetAlias("Eomega", "Epip + Epim + fE[0] + fE[1]");
  treeExtracted->SetAlias("Pxomega", "fX[0] + fX[1] + fX[2] + fX[3]");
  treeExtracted->SetAlias("Pyomega", "fY[0] + fY[1] + fY[2] + fY[3]");
  treeExtracted->SetAlias("Pzomega", "fZ[0] + fZ[1] + fZ[2] + fZ[3]");
  treeExtracted->SetAlias("p2omega", "Pxomega*Pxomega + Pyomega*Pyomega + Pzomega*Pzomega");
  treeExtracted->SetAlias("momega", "TMath::Sqrt(Eomega*Eomega - Pxomega*Pxomega - Pyomega*Pyomega - Pzomega*Pzomega)");
  treeExtracted->SetAlias("deltamomega", "momega - mpip - mpim - mpi0");

  /*** Real cuts 1 ***/
  
  Double_t sum23 = massPionCharged + massPionNeutral;
  Double_t sum12 = 2*massPionCharged;
  Double_t difP1 = massOmega - massPionCharged;
  Double_t difP3 = massOmega - massPionNeutral;
  
  TCut cutLeft1 = Form("mpimpi0 > %f", sum23); // (mpim + mpi0)
  TCut cutRight1 = Form("mpimpi0 < %f", difP1); // (momega - mpip)
  TCut cutBottom1 = Form("mpippim > %f", sum12); // (mpip + mpim)
  TCut cutTop1 = Form("mpippim < %f", difP3); // (momega - mpi0)

  TCut cutBox1 = cutLeft1 && cutRight1 && cutBottom1 && cutTop1;
  
  treeExtracted->SetAlias("Estar2", Form("(m2pippim - %f + %f)/2/mpippim", massPionCharged*massPionCharged, massPionCharged*massPionCharged));
  treeExtracted->SetAlias("Estar3", Form("(%f - m2pippim - %f)/2/mpippim", massOmega*massOmega, massPionNeutral*massPionNeutral));
  treeExtracted->SetAlias("Estar23", "Estar2 + Estar3");
  treeExtracted->SetAlias("Estar23Sq", "Estar23*Estar23");

  treeExtracted->SetAlias("Eroot2", Form("TMath::Sqrt(Estar2*Estar2 - %f)", massPionCharged*massPionCharged));
  treeExtracted->SetAlias("Eroot3", Form("TMath::Sqrt(Estar3*Estar3 - %f)", massPionNeutral*massPionNeutral));
  treeExtracted->SetAlias("Edif23", "Eroot2 - Eroot3");
  treeExtracted->SetAlias("Esum23", "Eroot2 + Eroot3");
  treeExtracted->SetAlias("Edif23Sq", "Edif23*Edif23");
  treeExtracted->SetAlias("Esum23Sq", "Esum23*Esum23");

  treeExtracted->SetAlias("Max23", "Estar23Sq - Edif23Sq");
  treeExtracted->SetAlias("Min23", "Estar23Sq - Esum23Sq");
  
  TCut cutDalitz1Up = "m2pimpi0 < Max23";
  TCut cutDalitz1Down = "m2pimpi0 > Min23";

  /*** Real cuts 2 ***/
  
  Double_t sum13 = massPionCharged + massPionNeutral;
  Double_t difP2 = massOmega - massPionCharged;
  
  TCut cutLeft2 = Form("mpippi0 > %f", sum13); // (mpip + mpi0)
  TCut cutRight2 = Form("mpippi0 < %f", difP2); // (momega - mpim)
  TCut cutBottom2 = Form("mpippim > %f", sum12); // (mpip + mpim)
  TCut cutTop2 = Form("mpippim < %f", difP3); // (momega - mpi0)

  TCut cutBox2 = cutLeft2 && cutRight2 && cutBottom2 && cutTop2;

  treeExtracted->SetAlias("Estar6", Form("(m2pippim - %f + %f)/2/mpippim", massPionCharged*massPionCharged, massPionCharged*massPionCharged));
  treeExtracted->SetAlias("Estar7", Form("(%f - m2pippim - %f)/2/mpippim", massOmega*massOmega, massPionNeutral*massPionNeutral));
  treeExtracted->SetAlias("Estar67", "Estar6 + Estar7");
  treeExtracted->SetAlias("Estar67Sq", "Estar67*Estar67");

  treeExtracted->SetAlias("Eroot6", Form("TMath::Sqrt(Estar6*Estar6 - %f)", massPionCharged*massPionCharged));
  treeExtracted->SetAlias("Eroot7", Form("TMath::Sqrt(Estar7*Estar7 - %f)", massPionNeutral*massPionNeutral));
  treeExtracted->SetAlias("Edif67", "Eroot6 - Eroot7");
  treeExtracted->SetAlias("Esum67", "Eroot6 + Eroot7");
  treeExtracted->SetAlias("Edif67Sq", "Edif67*Edif67");
  treeExtracted->SetAlias("Esum67Sq", "Esum67*Esum67");

  treeExtracted->SetAlias("Max67", "Estar67Sq - Edif67Sq");
  treeExtracted->SetAlias("Min67", "Estar67Sq - Esum67Sq");
  
  TCut cutDalitz2Up = "m2pippi0 < Max67";
  TCut cutDalitz2Down = "m2pippi0 > Min67";

  /*** Real cuts 3 ***/

  TCut cutLeft3 = Form("mpimpi0 > %f", sum23); // (mpim + mpi0)
  TCut cutRight3 = Form("mpimpi0 < %f", difP1); // (momega - mpip)
  TCut cutBottom3 = Form("mpippi0 > %f", sum13); // (mpip + mpi0)
  TCut cutTop3 = Form("mpippi0 < %f", difP2); // (momega - mpim)

  TCut cutBox3 = cutLeft3 && cutRight3 && cutBottom3 && cutTop3;

  treeExtracted->SetAlias("Estar4", Form("(m2pippi0 - %f + %f)/2/mpippi0", massPionCharged*massPionCharged, massPionNeutral*massPionNeutral));
  treeExtracted->SetAlias("Estar5", Form("(%f - m2pippi0 - %f)/2/mpippi0", massOmega*massOmega, massPionCharged*massPionCharged));
  treeExtracted->SetAlias("Estar45", "Estar4 + Estar5");
  treeExtracted->SetAlias("Estar45Sq", "Estar45*Estar45");

  treeExtracted->SetAlias("Eroot4", Form("TMath::Sqrt(Estar4*Estar4 - %f)", massPionNeutral*massPionNeutral));
  treeExtracted->SetAlias("Eroot5", Form("TMath::Sqrt(Estar5*Estar5 - %f)", massPionCharged*massPionCharged));
  treeExtracted->SetAlias("Edif45", "Eroot4 - Eroot5");
  treeExtracted->SetAlias("Esum45", "Eroot4 + Eroot5");
  treeExtracted->SetAlias("Edif45Sq", "Edif45*Edif45");
  treeExtracted->SetAlias("Esum45Sq", "Esum45*Esum45");

  treeExtracted->SetAlias("Max45", "Estar45Sq - Edif45Sq");
  treeExtracted->SetAlias("Min45", "Estar45Sq - Esum45Sq");
  
  TCut cutDalitz3Up = "m2pimpi0 < Max45";
  TCut cutDalitz3Down = "m2pimpi0 > Min45";  
  
  /*** Now it's time ***/
  
  TCut fullDalitz = cutBox1 && cutDalitz1Up && cutDalitz1Down && cutBox2 && cutDalitz2Up && cutDalitz2Down && cutBox3 && cutDalitz3Up && cutDalitz3Down;
  
  treeExtracted->Draw("deltamomega>>data(160, 0., 1.6)", cutAll && fullDalitz, "goff");
  dataHist = (TH1F *)gROOT->FindObject("data");

  /*** The drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768);
  c->SetGrid();

  // gStyle->SetOptStat(0);
  
  dataHist->SetTitle("#omega Mass Difference in " + titleTarget + titleZ);
  dataHist->GetXaxis()->SetTitle("GeV");
  dataHist->GetYaxis()->SetTitle("Counts");
  dataHist->SetLineColor(kBlack);
  dataHist->SetFillColor(kMagenta+2);
  dataHist->Draw("B");

  TLatex *t = new TLatex(.02, .95, "#scale[0.70]{M_{#omega} - M_{#pi^{0}} - M_{#pi^{+}} - M_{#pi^{-}}}");
  t->SetTextFont(152);
  t->SetNDC(kTRUE);
  t->Draw();

  c->Print(outputPlot);
  
  /*** Writing results ***/
  
  Int_t omegaNumber = dataHist->GetEntries();
  Double_t omegaError = TMath::Sqrt(omegaNumber);
  
  std::cout << "Writing " << outputTextFile << " ..." << std::endl;  
  std::ofstream outFinalFile(outputTextFile, std::ios::out);
  // first and only line: 
  outFinalFile << omegaNumber << "\t\t" << omegaError << std::endl;
  outFinalFile.close();
  std::cout << "File " << outputTextFile << " created!" << std::endl;
}

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Write -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:T:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'T': targetTypeOption = atoi(optarg); break;    
    case 'z': binNumberZ = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeFits -h to get help." << std::endl;
      exit(0);
      break;
    }
}

void assignOptions() {
  // for target option
  if (targetOption == "C") targetFull = "C-thickD2";
  else if (targetOption == "Fe") targetFull = "Fe-thickD2";
  else if (targetOption == "Pb") targetFull = "Pb-thinD2";
  // for targetType option
  cutTargType = Form("TargType == %d", targetTypeOption);
  if (targetTypeOption == 1) titleTarget = targetOption + "_D";
  else if (targetTypeOption == 2) titleTarget = targetOption + "_" + targetOption;
  // for Z binning
  if (binNumberZ == 3) {
    lowEdgeZ = 0.5;
    highEdgeZ = 0.557;
  } else if (binNumberZ == 4) {
    lowEdgeZ = 0.557;
    highEdgeZ = 0.617;
  } else if (binNumberZ == 5) {
    lowEdgeZ = 0.617;
    highEdgeZ = 0.689;
  } else if (binNumberZ == 6) {
    lowEdgeZ = 0.689;
    highEdgeZ = 0.784;
  } else if (binNumberZ == 7) {
    lowEdgeZ = 0.784;
    highEdgeZ = 1.;
  }
  cutZ = Form("%f < Z && Z < %f", lowEdgeZ, highEdgeZ);
  titleZ = Form(" (%.02f < Z < %.02f)", lowEdgeZ, highEdgeZ);
  sufixZBin = Form("-z%d", binNumberZ);
  // name of input files
  inputRootFile = "/" + targetFull + "/wout_" + targetFull + ".root";
  // name of output files
  outputTextFile = "dalitz-cut-" + titleTarget + sufixZBin + ".dat";
  outputPlot = "dalitz-cut-" + titleTarget + sufixZBin + ".png";
}

void printOptions() {
  std::cout << "titleTarget=" << titleTarget << std::endl;
  std::cout << "binNumberZ=" << binNumberZ << std::endl;
}

void printUsage() {
  std::cout << "DalitzCuts program. Usage is:" << std::endl;
  std::cout << "./DalitzCuts -[options] -[more options]" << std::endl;
  std::cout << "  h             : prints help and exit program" << std::endl;
  std::cout << "  t[target]     : selects target: C | Fe | Pb" << std::endl;
  std::cout << "  T[targetType] : selects targetType: 1 (liquid) | 2 (solid)" << std::endl;
  std::cout << "  z[3-7]        : analyzes that specific bin" << std::endl;
}
