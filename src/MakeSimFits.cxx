/**************************************/
/* MakeSimFits.cxx                    */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// fits peak with a gaussian function and bkg with a 1st order polynomial
// for simrec (for now)

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

TString outDir = proDir + "/out/MakeSimFits";

// target options
TString targetOption;
TString inputFile = "";
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
TString plotName;
TString textName;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // dir structure, just in case
  system("mkdir -p " + outDir);
  
  // cuts
  TCut cutAll = cutDIS_old && cutPipPim_old && cutPi0_old;

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile + "/outdata");

  setAlias_old(treeExtracted);
  
  /*** Fit ***/
  
  // bin x-width = 5 MeV
  Int_t Nbins = 40; // 40
  Double_t fitRangeDown = 0.270; // preMean.getValV() - 5*preSigma.getValV() = 0.268
  Double_t fitRangeUp = 0.470; // preMean.getValV() + 5*preSigma.getValV() = 0.468

  Double_t meanIGV = 0.37;
  Double_t meanRangeDown = 0.36;
  Double_t meanRangeUp = 0.39; // 0.38

  Double_t sigmaIGV = 1.75e-2;
  Double_t sigmaRangeDown = 1.6e-2; // 1.5
  Double_t sigmaRangeUp = 2.4e-2; // 3.5

  TH1F *dataHist;
  treeExtracted->Draw(Form("deltam>>simrec(%d, %f, %f)", Nbins, fitRangeDown, fitRangeUp), cutAll && cutTargType && kinvarCut, "goff");
  dataHist = (TH1F *)gROOT->FindObject("simrec");
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
  RooGaussian conSigma("conSigma", "conSigma", omegaSigma, RooConst(0.02), RooConst(0.002));

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
  
  c->Print(plotName); // output file

  std::cout << "N_d=" << N_d << std::endl;
  std::cout << "N_sum=" << N_sum << std::endl;
  std::cout << "N_omega=" << N_omega << std::endl;
  std::cout << "N_bkg=" << N_bkg << std::endl;

  /*** Save data from fit ***/

  std::cout << "Writing " << textName << " ..." << std::endl;
  std::ofstream outFinalFile(textName, std::ios::out); // output file
  // line 1: omegaMean
  outFinalFile << omegaMean.getValV() << "\t" << omegaMean.getError() << std::endl;
  // line 2: omegaSigma
  outFinalFile << omegaSigma.getValV() << "\t" << omegaSigma.getError() << std::endl;
  // line 3: number of omega particles (directly from parameter)
  outFinalFile << nsig.getValV() << "\t\t" << nsig.getError() << std::endl;
  // line 4: b1
  outFinalFile << b1.getValV() << "\t" << b1.getError() << std::endl;
  // line 5: bkgYields
  outFinalFile << nbkg.getValV() << "\t\t" << nbkg.getError() << std::endl;
  std::cout << "Text file " << textName << " has been created!" << std::endl;
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeSimFits -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:z:q:n:p:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'z': flagZ = 1; binNumber = atoi(optarg); break;
    case 'q': flagQ2 = 1; binNumber = atoi(optarg); break;
    case 'n': flagNu = 1; binNumber = atoi(optarg); break;
    case 'p': flagPt2 = 1; binNumber = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeSimFits -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing MakeSimFits program. Chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  kinvarName   = " << kinvarName << std::endl;
  std::cout << "  binNumber    = " << binNumber << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "MakeSimFits program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeSimFits -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeSimFits -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeSimFits -[kinvar][number]" << std::endl;
  std::cout << "    analyzes respective kinematic variable bin" << std::endl;
  std::cout << "    z[3-7] : analyzes specific Z bin" << std::endl;
  std::cout << "    q[1-5] : analyzes specific Q2 bin" << std::endl;
  std::cout << "    n[1-5] : analyzes specific Nu bin" << std::endl;
  std::cout << "    p[1-5] : analyzes specific Pt2 bin" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for targets, unified D
  if (targetOption == "D") {
    inputFile = simrecDir + "/jlab/D/wout_simrecD.root";
    cutTargType = "TargType == 1";
  } else if (targetOption == "C") {
    inputFile = simrecDir + "/jlab/C/wout_simrecC.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Fe") {
    inputFile = simrecDir + "/jlab/Fe/wout_simrecFe.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Pb") {
    inputFile = simrecDir + "/usm/Pb/wout_simrecPb.root";
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
  // names
  outDir = outDir + "/" + kinvarName;
  plotName = outDir + "/simfit-" + targetOption + kinvarSufix + ".png";
  textName = outDir + "/simfit-" + targetOption + kinvarSufix + ".dat";
}
