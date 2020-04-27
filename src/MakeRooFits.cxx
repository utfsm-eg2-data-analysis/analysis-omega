/*********************************/
/* MakeRooFits.cxx               */
/*                               */
/* Created by Andrés Bórquez     */
/*                               */
/*********************************/

// fits peak with a gaussian function and bkg with a 1st order polynomial
// - added kinematic dependence as an option
// update:
// - added bands of error bars
// - added poly as an option

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

/*** Hardcoded ***/

// 24,2 was the winner for Z
Double_t meanConstraint = 26e-3;
Double_t sigmaConstraint = 1e-3;
Double_t sigmaRangeDown = 2.3e-2;
Double_t sigmaRangeUp = 3.1e-2; // testing for Pt2

/*** Global variables ***/

TString outDir = proDir + "/out/MakeRooFits";

// target options
TString targetOption;
TString inputFile1 = "";
TString inputFile2 = "";
TString inputFile3 = "";
TCut    cutTargType;
Int_t   bkgOption = 1;

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
TString pullFile; // new!

Int_t    flagNew = 0;
Double_t obtMean = 0.37;
Double_t obtSigma = 1.75e-2;
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

  // dir structure, just in case
  system("mkdir -p " + outDir);

  // cuts
  TCut cutAll = cutDIS && cutPipPim && cutPi0;

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  /*** Read previous results ***/

  // if this is an iteration
  if (!flagNew) {
    std::cout << std::endl;
    std::cout << "Reading previous file " << textFile << " ..." << std::endl;
    std::ifstream inFile(textFile);
    
    TString auxString1, auxString2;
    Int_t l = 0; // line counter
    while (inFile >> auxString1 >> auxString2) {
      l++;
      if (l == 1) { // first line
	obtMean = auxString1.Atof();
	std::cout << "  Omega Mean for " << targetOption << kinvarSufix << ": " << obtMean << std::endl;
      } else if (l == 2) { // second line
	obtSigma = auxString1.Atof();
	std::cout << "  Omega Sigma for " << targetOption << kinvarSufix << ": " << obtSigma << std::endl;
      }
    }
    inFile.close();
    
    // keep fit range
    obtEdges[0] = obtMean - 5*obtSigma; // 5
    obtEdges[1] = obtMean + 5*obtSigma; //5
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

  Double_t meanIGV = obtMean;
  Double_t meanRangeDown = 0.34;
  Double_t meanRangeUp = 0.39; // 0.38

  Double_t sigmaIGV = obtSigma;
  // Double_t sigmaRangeDown = 1.8e-2; Double_t sigmaRangeUp = 2.8e-2; // winner for Z
  // Double_t sigmaRangeDown = 3.4e-2; Double_t sigmaRangeUp = 4.2e-2; // testing for Pt2

  TH1F *dataHist;
  treeExtracted->Draw(Form("wD>>data(%d, %f, %f)", Nbins, fitRangeDown, fitRangeUp), cutAll && cutTargType && kinvarCut, "goff");
  dataHist = (TH1F *)gROOT->FindObject("data");
  
  /*** RooFit stuff ***/

  RooRealVar x("IMD", "IMD (GeV)", fitRangeDown, fitRangeUp);

  RooRealVar omegaMean("#mu(#omega)", "Mean of Gaussian", meanIGV, meanRangeDown, meanRangeUp);
  RooRealVar omegaSigma("#sigma(#omega)", "Width of Gaussian", sigmaIGV, sigmaRangeDown, sigmaRangeUp);
  RooGaussian omega("omega", "omega peak", x, omegaMean, omegaSigma);  

  RooRealVar b1("b1", "linear term", 0.1, -10., 10.);
  RooRealVar b2("b2", "quadratic term", -0.1, -10., 0.); // definition, use it only when bkgOption=2

  // bkg list
  RooArgList lbkg(b1);
  if (bkgOption == 2) lbkg.add(b2);
  RooChebychev bkg("bkg", "background", x, lbkg);
  
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

  /*** Constraints! ***/
  
  RooGaussian conSigma("conSigma", "conSigma", omegaSigma, RooConst(meanConstraint), RooConst(sigmaConstraint)); // imposing bias
  RooProdPdf cmodel("cmodel", "model with constraint", RooArgSet(model, conSigma));

  // fit constraint model
  RooFitResult *r2 = cmodel.fitTo(data, Constrain(conSigma), Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  r2->Print("v");

  // draw data points
  data.plotOn(frame, Name("Data")); // DataError(RooAbsData::SumW2)
  
  // visualize error
  cmodel.plotOn(frame, VisualizeError(*r2, 1, kFALSE), FillColor(kRed-9));                     // FillStyle(3001)
  cmodel.plotOn(frame, Components("bkg"), VisualizeError(*r2, 1, kFALSE), FillColor(kBlue-9)); // DrawOption("L"), LineWidth(2), LineColor(kRed)

  // overlay data points
  data.plotOn(frame, Name("Data"));
  
  // overlay center values
  cmodel.plotOn(frame, Name("Model"), LineColor(kRed));
  
  // add params
  cmodel.paramOn(frame, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frame->getAttText()->SetTextSize(0.025);
  frame->getAttLine()->SetLineWidth(0);
  
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->SetTitle("Counts");
  frame->GetYaxis()->CenterTitle();
  
  // draw!
  TCanvas *c = new TCanvas("c", "c", 1360, 1700); // 16:20
  c->Divide(1, 2); // two vertical pads
  
  c->GetPad(1)->SetPad(0., 0.3, 1., 1.); // x1,y1,x2,y2
  c->GetPad(1)->SetTopMargin(0.1);
  c->GetPad(1)->SetBottomMargin(0.1);
  
  c->GetPad(2)->SetPad(0., 0., 1., 0.3); // x1,y1,x2,y2
  c->GetPad(2)->SetTopMargin(0.0);
  c->GetPad(2)->SetBottomMargin(0.1);

  /*** Pull Hist ***/
  
  c->cd(2);
  gPad->SetTickx();
  gPad->SetTicky();
  gStyle->SetOptStat(0);
  
  // define histograms from model
  TH1F *signalHist = (TH1F *) omega.createHistogram("signalHist", x, Binning(Nbins, fitRangeDown, fitRangeUp), Extended());
  signalHist->Scale(nsig.getValV());
  
  TH1F *bkgHist =  (TH1F *) bkg.createHistogram("bkgHist", x, Binning(Nbins, fitRangeDown, fitRangeUp), Extended());
  bkgHist->Scale(nbkg.getValV());
  
  TH1F *modelHist = new TH1F("modelHist", "modelHist", Nbins, fitRangeDown, fitRangeUp);
  modelHist->Add(signalHist, bkgHist);

  TH1F *dataErrHist = new TH1F("dataErrHist", "dataErrHist", Nbins, fitRangeDown, fitRangeUp);
  for (Int_t h = 1; h <= Nbins; h++) {
    dataErrHist->SetBinContent(h, dataHist->GetBinError(h));
    dataErrHist->SetBinError(h, 0);
  }

  TH1F *pullHist = new TH1F("pullHist", "pullHist", Nbins, fitRangeDown, fitRangeUp);
  pullHist->Add(dataHist, modelHist, 1, -1);
  pullHist->Divide(dataErrHist);

  pullHist->SetTitle("");
  pullHist->GetXaxis()->SetTickSize(0.07);
  pullHist->GetXaxis()->SetLabelSize(0.07);
  pullHist->GetXaxis()->SetTitle("");
  pullHist->GetYaxis()->SetLabelSize(0.07);
  pullHist->GetYaxis()->SetTitleSize(0.07);
  pullHist->GetYaxis()->SetTitleOffset(0.375);
  pullHist->GetYaxis()->SetTitle("Pull");
  pullHist->GetYaxis()->CenterTitle();
  pullHist->SetFillColor(kMagenta);
  pullHist->SetAxisRange(-4.5, 4.5, "Y");
  
  pullHist->Draw("HIST B");
    
  drawHorizontalLine(3);
  drawBlackHorizontalLine(0);
  drawHorizontalLine(-3);

  /*** Finish drawing ***/
  
  // going back to first pad
  c->cd(1);
  
  cmodel.plotOn(frame, Components("bkg"), LineStyle(kDashed), LineColor(kBlue));
  frame->Draw();

  /*
    modelHist->SetLineColor(kBlack);
    modelHist->SetLineWidth(5);
    modelHist->Draw("SAME HIST");
  */
  
  // draw lines
  drawVerticalLineGrayest(omegaMean.getValV() - 3*omegaSigma.getValV());
  drawVerticalLineBlack(omegaMean.getValV());
  drawVerticalLineGrayest(omegaMean.getValV() + 3*omegaSigma.getValV());
  
  c->Print(plotFile); // output file

  /*** Integral ***/

  x.setRange("3sigmaRange", omegaMean.getValV() - 3*omegaSigma.getValV(), omegaMean.getValV() + 3*omegaSigma.getValV());
  RooAbsReal *bkg3Sigma = bkg.createIntegral(x, NormSet(x), Range("3sigmaRange"));

  /*** Save data from fit ***/

  std::cout << "Writing " << textFile << " ..." << std::endl;
  std::ofstream outFinalFile(textFile, std::ios::out); // output file
  // line 1: omegaMean
  outFinalFile << omegaMean.getValV() << "\t" << omegaMean.getError() << std::endl;
  // line 2: omegaSigma
  outFinalFile << omegaSigma.getValV() << "\t" << omegaSigma.getError() << std::endl;
  // line 3: number of omega
  outFinalFile << nsig.getValV() << "\t\t" << nsig.getError() << std::endl;
  // line 4: number of bkg
  outFinalFile << bkg3Sigma->getValV() * nbkg.getValV() << "\t\t" << nbkg.getError() << std::endl;
  std::cout << "File " << textFile << " has been created!" << std::endl;
  std::cout << std::endl;

  /*** Pull hist, part 2 ***/
  /*
    TH1F *pullHistY = new TH1F("pullHistY", "pullHistY", 18, -3., 3.);
    for (Int_t y = 1; y <= Nbins; y++) pullHistY->Fill(pullHist->GetBinContent(y));
    
    RooRealVar p("Pull", "Pull", -3., 3.);
    
    RooRealVar pullMean("pullMean", "Mean of Gaussian", 0., -0.5, 0.5);
    RooRealVar pullSigma("pullSigma", "Width of Gaussian", 0.5, 0.01, 1.5);
    RooGaussian pullModel("pullModel", "pullModel", p, pullMean, pullSigma);
    
    RooDataHist pullData("pullData", "pull data", p, pullHistY);
    
    // define frame
    RooPlot *frame2 = p.frame(Title(targetOption + " in" + kinvarTitle), Bins(18));
    
    // fit the normal way
    pullModel.chi2FitTo(pullData);
    
    // draw
    pullData.plotOn(frame2, Name("pullData"));
    pullModel.plotOn(frame2, Name("pullModel"), LineColor(kBlue));
    
    pullModel.paramOn(frame2, Layout(0.11, 0.3, 0.89)); // x1, x2, delta-y
    frame2->getAttText()->SetTextSize(0.025);
    frame2->getAttLine()->SetLineWidth(0);
    
    frame2->GetXaxis()->CenterTitle();
    frame2->GetYaxis()->SetTitle("Counts");
    frame2->GetYaxis()->CenterTitle();
    
    TCanvas *cp = new TCanvas("cp", "cp", 1020, 1020); // 16:20
    
    frame2->Draw();
    
    // chi2
    Double_t pullChi2 = frame2->chiSquare("pullModel", "pullData");
    TPaveText *textBlock = new TPaveText(0.11, 0.68, 0.3, 0.78, "NDC TL"); // x1, y1, x2, y2
    textBlock->AddText(Form("#chi^{2}/ndf = %.3f", pullChi2));
    textBlock->SetFillColor(kWhite);
    textBlock->SetLineColor(kWhite);
    textBlock->SetShadowColor(kWhite);
    textBlock->SetTextColor(kBlack);
    textBlock->Draw();
    
    cp->Print(pullFile);
  */
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeRooFits -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:z:q:n:p:Sb:C:c:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'z': flagZ = 1; binNumber = atoi(optarg); break;
    case 'q': flagQ2 = 1; binNumber = atoi(optarg); break;
    case 'n': flagNu = 1; binNumber = atoi(optarg); break;
    case 'p': flagPt2 = 1; binNumber = atoi(optarg); break;
    case 'S': flagNew = 1; break;
    case 'b': bkgOption = atoi(optarg); break;
    case 'C': meanConstraint = (Double_t) atof(optarg); break;
    case 'c': sigmaConstraint = (Double_t) atof(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeRooFits -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing MakeRooFits program. Chosen parameters are:" << std::endl;
  std::cout << "  targetOption    = " << targetOption << std::endl;
  std::cout << "  kinvarName      = " << kinvarName << std::endl;
  std::cout << "  binNumber       = " << binNumber << std::endl;
  std::cout << "  flagNew         = " << flagNew << std::endl;
  std::cout << "  bkgOption       = " << bkgOption << std::endl;
  std::cout << "  meanConstraint  = " << meanConstraint << std::endl;
  std::cout << "  sigmaConstraint = " << sigmaConstraint << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "MakeRooFits program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -b[1,2]" << std::endl;
  std::cout << "    choose bkg function: 1st order or 2nd order polynomial" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -[kinvar][number]" << std::endl;
  std::cout << "    analyzes respective kinematic variable bin" << std::endl;
  std::cout << "    z[3-7] : analyzes specific Z bin" << std::endl;
  std::cout << "    q[1-5] : analyzes specific Q2 bin" << std::endl;
  std::cout << "    n[1-5] : analyzes specific Nu bin" << std::endl;
  std::cout << "    p[1-5] : analyzes specific Pt2 bin" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -S" << std::endl;
  std::cout << "    plots a default 5sigma range" << std::endl;
  std::cout << "    without this option, it sets a new 5sigma range based on previous results" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -C[float]" << std::endl;
  std::cout << "    (*1e-3) sets mean constraint for sigma parameter" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -c[float]" << std::endl;
  std::cout << "    (*1e-3) sets width constraint for sigma parameter" << std::endl;
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
  // names
  outDir = outDir + "/" + kinvarName + "/g" + "/b" + bkgOption; // only gaussian, for now
  plotFile = outDir + "/roofit-" + targetOption + kinvarSufix + ".png";
  textFile = outDir + "/roofit-" + targetOption + kinvarSufix + ".dat";
  pullFile = outDir + "/roofit-" + targetOption + kinvarSufix + "_pull.png";
  // sigma studies
  meanConstraint *= 1e-3;
  sigmaConstraint *= 1e-3;
  sigmaRangeDown = meanConstraint - 4e-3;
  sigmaRangeUp = meanConstraint + 4e-3;
}
