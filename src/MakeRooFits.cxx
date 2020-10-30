/*********************************/
/* MakeRooFits.cxx               */
/*                               */
/* Andrés Bórquez                */
/*                               */
/*********************************/

// October 2020

#include "analysisConfig.h"

#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooGaussian.h"
#include "RooBreitWigner.h"
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

TString targetOption;

TString inputDir  = proDir + "/out/FilterNCombine/data";
TString outputDir = proDir + "/out/MakeRooFits";

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();

// void MakeRooFit(TTree *treeExtracted, TString histName);

/*** Main ***/

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  printOptions();

  // set i/o
  TChain *treeExtracted = new TChain();
  TCut cutVertex;
  if (targetOption == "D") { // unified D
    // treeExtracted->Add(inputDir + "/C/combC_data.root/mix");
    treeExtracted->Add(inputDir + "/Fe/combFe_data.root/mix");
    // treeExtracted->Add(inputDir + "/Pb/combPb_data.root/mix");
    cutVertex = "TargType == 1 && Yec > -1.4 && Yec < 1.4";
  } else {
    treeExtracted->Add(inputDir + "/" + targetOption + "/comb" + targetOption + "_data.root/mix");
    cutVertex = "TargType == 2 && Yec > -1.4 && Yec < 1.4";
  }

  // create and open output file
  TFile *rootOutputFile = new TFile(outputDir + "/roofits_" + targetOption + ".root", "RECREATE");

  // define array
  TString kinVar[4] = {"Q", "N", "Z", "P"};
  TString currentHistName;

  /*** STEP 1: BIG PICTURE ***/
  
  // set cuts
  TCut cutSeba = "P_corr[0] > 0.2 && P_corr[1] > 0.2";;
  TCut cutWill = "P_corr[2] > 0.2 && P_corr[3] > 0.2";
  TCut cutDATA = cutDIS && cutVertex && cutPi0 && cutSeba && cutWill;
  
  // create histogram
  TH1F *bigHist_DATA;
  treeExtracted->Draw("wD_corr>>DATA_" + targetOption + "(120, 0., 1.6)", cutDATA, "goff");
  bigHist_DATA = (TH1F *)gROOT->FindObject("DATA_" + targetOption);
  bigHist_DATA->SetTitle("DATA #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption);

  // save hist
  bigHist_DATA->Write();
  
  /*** STEP 2: BINNING ***/
  
  TCut binCutDATA;

  TH1F   *binHist;
  TString binHistName;
  
  // Q2
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "DATA_" + targetOption + Form("_Q%d", i);
    binCutDATA = Form("Q2 > %.3f && Q2 < %.3f" , edgesQ2[i], edgesQ2[i+1]);
    // extract
    treeExtracted->Draw("wD_corr>>" + binHistName + "(120, 0., 1.6)", cutDATA && binCutDATA, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("DATA #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < Q2 < %.2f)" , edgesQ2[i], edgesQ2[i+1]));
    // save
    binHist->Write();
  }

  // Nu
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "DATA_" + targetOption + Form("_N%d", i);
    binCutDATA = Form("Nu > %.3f && Nu < %.3f" , edgesNu[i], edgesNu[i+1]);
    // extract
    treeExtracted->Draw("wD_corr>>" + binHistName + "(120, 0., 1.6)", cutDATA && binCutDATA, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("DATA #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < Nu < %.2f)" , edgesNu[i], edgesNu[i+1]));
    // save
    binHist->Write();
  }

  // Pt2
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "DATA_" + targetOption + Form("_P%d", i);
    binCutDATA = Form("wPt2_corr > %.3f && wPt2_corr < %.3f" , edgesPt2[i], edgesPt2[i+1]);
    // extract
    treeExtracted->Draw("wD_corr>>" + binHistName + "(120, 0., 1.6)", cutDATA && binCutDATA, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("DATA #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < Pt2 < %.2f)", edgesPt2[i], edgesPt2[i+1]));
    // save
    binHist->Write();
  }

  // Z
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "DATA_" + targetOption + Form("_Z%d", i);
    binCutDATA = Form("wZ_corr > %.3f && wZ_corr < %.3f" , edgesZ[i], edgesZ[i+1]);
    // extract
    treeExtracted->Draw("wD_corr>>" + binHistName + "(120, 0., 1.6)", cutDATA && binCutDATA, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("DATA #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < Z < %.2f)", edgesZ[i], edgesZ[i+1]));
    // save
    binHist->Write();
  }
  
  /*** STEP 3: FIT ***/
  /*
  // loop on kinvars
  for (Int_t k = 0; k < 4; k++) {
    // loop on bin numbers
    for (Int_t i = 0; i < 5; i++) {
	currentHistName = "DATA-" + targetOption + "_" + kinVar[k] + Form("%d", i);
	MakeRooFit(treeExtracted, currentHistName);
    }
  }
  */
  // close file
  rootOutputFile->Close();
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeRooFits -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeRooFits -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing MakeRooFits program. Chosen parameters are:" << std::endl;
  std::cout << "  targetOption    = " << targetOption << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "MakeRooFits program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -t[target]" << std::endl;
  std::cout << "    selects target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;
}

/*
void MakeRooFit(TTree *treeExtracted, TString histName) {

  // Cuts
  
  TH1F *omegaHist;
  treeExtracted->Draw(Form("wD>>" + histName + "(%d, %f, %f)", Nbins, fitRangeDown, fitRangeUp), cutAll && cutTargType && kinvarCut, "goff");
  omegaHist = (TH1F *)gROOT->FindObject(histName);

  // Fit Options
  
  // bin x-width = 5 MeV
  Int_t    Nbins        = omegaHist->GetNbinsX();
  Double_t fitRangeDown = omegaHist->GetXaxis()->GetXmin();
  Double_t fitRangeUp   = omegaHist->GetXaxis()->GetXmax();

  Double_t meanIGV       = omegaHist->GetMean();
  Double_t meanRangeDown = meanIGV - 0.03;
  Double_t meanRangeUp   = meanIGV + 0.03;
  
  Double_t sigmaIGV       = omegaHist->GetRMS();
  Double_t sigmaRangeDown = 0;
  Double_t sigmaRangeUp   = sigmaIGV + 0.3;
  
  // RooFit stuff

  RooRealVar x("IMD", "Invariant Mass Difference (GeV)", fitRangeDown, fitRangeUp);

  RooRealVar  omegaMean("#mu(#omega)", "Mean of Gaussian", meanIGV, meanRangeDown, meanRangeUp);
  RooRealVar  omegaSigma("#sigma(#omega)", "Width of Gaussian", sigmaIGV, sigmaRangeDown, sigmaRangeUp);
  // RooGaussian omega("omega", "omega peak", x, omegaMean, omegaSigma);
  RooBreitWigner omega("omega-bw", "omega-bw peak", x, omegaMean, omegaSigma);    

  RooRealVar   b1("b1", "linear term", 0., -20, 20);
  RooChebychev bkg("bkg", "background", x, RooArgList(b1));
  // RooRealVar   b2("b2", "quadratic term", -0.1, -10., 0.); // definition, use it only when bkgOption=2
  // RooChebychev bkg("bkg", "background", x, RooArgList(b1, b2));

  // model(x) = sig_yield*sig(x) + bkg_yield*bkg(x)
  RooRealVar nsig("N_{#omega}", "omega yields", 0., omegaHist->GetEntries());
  RooRealVar nbkg("N_{b}", "bkg yields", 0., omegaHist->GetEntries());
  RooAddPdf  model("model", "model", RooArgList(omega, bkg), RooArgList(nsig, nbkg));
  
  // define data
  RooDataHist data("data", "my data", x, omegaHist);

  // define frame
  RooPlot *frame = x.frame(Name(histName), Title(histName), Bins(Nbins));
  
  // fit the normal way
  RooFitResult *r1 = model.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  r1->Print("v");

  // define constraints
  RooGaussian conSigma("conSigma", "conSigma", omegaSigma, RooConst(0.02), RooConst(0.001));
  RooProdPdf  cmodel("cmodel", "model with constraint", RooArgSet(model, conSigma));
  
  // fit constraint model
  RooFitResult *r2 = cmodel.fitTo(data, Constrain(conSigma), Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  r2->Print("v");
  
  // draw points
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
  cmodel.plotOn(frame, Components("bkg"), LineStyle(kDashed), LineColor(kBlue));
  frame->Write();

  r2->Write("rf" + histName);
}
*/

/*
  DEPRECATED STUFF

Double_t meanConstraint = 26e-3;
Double_t sigmaConstraint = 1e-3;
Double_t sigmaRangeDown = meanConstraint - 4e-3;
Double_t sigmaRangeUp = meanConstraint + 4e-3;

Int_t    flagNew = 0;
Double_t obtMean = 0.37;
Double_t obtSigma = 1.75e-2;
Double_t obtEdges[2] = {0.27, 0.47}; // default
Int_t    obtNbins = 40; // default

Int_t meanConstraintFlag = 0;
Int_t sigmaConstraintFlag = 0;
 
  // for kinvar
  Double_t lowEdge, highEdge;
  if (flagZ) {
    lowEdge = edgesZ[binNumber-3];
    highEdge = edgesZ[binNumber+1-3];
    kinvarSufix = Form("-z%d", binNumber);
    kinvarName = "Z";
    // winner values
    if (!meanConstraintFlag) meanConstraint = 24e-3;
    if (!sigmaConstraintFlag) sigmaConstraint = 2e-3;
  } else if (flagQ2) {
    lowEdge = edgesQ2[binNumber-1];
    highEdge = edgesQ2[binNumber+1-1];
    kinvarSufix = Form("-q%d", binNumber);
    kinvarName = "Q2";
    // winner values
    if (!meanConstraintFlag) meanConstraint = 34e-3;
    if (!sigmaConstraintFlag) sigmaConstraint = 1.5e-3;
  } else if (flagNu) {
    lowEdge = edgesNu[binNumber-1];
    highEdge = edgesNu[binNumber+1-1];
    kinvarSufix = Form("-n%d", binNumber);
    kinvarName = "Nu";
    // winner values
    if (!meanConstraintFlag) meanConstraint = 40e-3;
    if (!sigmaConstraintFlag) sigmaConstraint = 1.5e-3;
  } else if (flagPt2) {
    lowEdge = edgesPt2[binNumber-1];
    highEdge = edgesPt2[binNumber+1-1];
    kinvarSufix = Form("-p%d", binNumber);
    kinvarName = "Pt2";
    // winner values
    if (!meanConstraintFlag) meanConstraint = 38e-3;
    if (!sigmaConstraintFlag) sigmaConstraint = 1.5e-3;
  }
  kinvarCut = Form("%f < ", lowEdge) + kinvarName + " && " + kinvarName + Form(" < %f", highEdge);
  kinvarTitle = Form(" (%.02f < ", lowEdge) + kinvarName + Form(" < %.02f)", highEdge);
  // names
  outDir = outDir + "/" + kinvarName + "/" + signalOption + "/b" + bkgOption; // new: added signalOption
  plotFile = outDir + "/roofit-" + targetOption + kinvarSufix + ".png";
  textFile = outDir + "/roofit-" + targetOption + kinvarSufix + ".dat";
  pullFile = outDir + "/roofit-" + targetOption + kinvarSufix + "_pull.png";
  // sigma studies
  if (meanConstraintFlag) meanConstraint *= 1e-3;
  if (sigmaConstraintFlag) sigmaConstraint *= 1e-3;
  // reload variables
  sigmaRangeDown = meanConstraint - 4e-3;
  sigmaRangeUp = meanConstraint + 4e-3;

  
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

  // bin x-width = 5 MeV
  Int_t Nbins = obtNbins;
  Double_t fitRangeDown = obtEdges[0]; // preMean.getValV() - 5*preSigma.getValV() = 0.268
  Double_t fitRangeUp = obtEdges[1]; // preMean.getValV() + 5*preSigma.getValV() = 0.468

  Double_t meanIGV = obtMean;
  Double_t meanRangeDown = 0.34;
  Double_t meanRangeUp = 0.39; // 0.38

  Double_t sigmaIGV = obtSigma;
  
  RooRealVar x("IMD", "IMD (GeV)", fitRangeDown, fitRangeUp);

  // define signal parameters
  RooRealVar omegaMean("#mu(#omega)", "Mean of Gaussian", meanIGV, meanRangeDown, meanRangeUp);
  RooRealVar omegaSigma("#sigma(#omega)", "Width of Gaussian", sigmaIGV, sigmaRangeDown, sigmaRangeUp);

  // define signal functions, use them when corresponds
  RooGaussian omega("omega", "omega peak", x, omegaMean, omegaSigma);
  RooBreitWigner omegaBW("omega-bw", "omega-bw peak", x, omegaMean, omegaSigma);  

  RooRealVar b1("b1", "linear term", 0.1, -10., 10.);
  RooRealVar b2("b2", "quadratic term", -0.1, -10., 0.); // definition, use it only when bkgOption=2

  // bkg list
  RooArgList lbkg(b1);
  if (bkgOption == 2) lbkg.add(b2);
  RooChebychev bkg("bkg", "background", x, lbkg);

  // functions list
  RooArgList lfunctions(bkg);
  if (signalOption == "g") lfunctions.add(omega);
  else if (signalOption == "bw") lfunctions.add(omegaBW);
  
  // model(x) = bkg_yield*bkg(x) + sig_yield*sig(x)
  RooRealVar nsig("N_{#omega}", "omega yields", 0., dataHist->GetEntries());
  RooRealVar nbkg("N_{b}", "bkg yields", 0., dataHist->GetEntries());
  RooAddPdf model("model", "model", lfunctions, RooArgList(nbkg, nsig)); // RooArgList(omega, bkg)
  
  // define data
  RooDataHist data("data", "my data", x, dataHist);

  // define frame
  RooPlot *frame = x.frame(Title("IMD(#pi^{+} #pi^{-} #pi^{0}) for " + targetOption + " in" + kinvarTitle),
			   Bins(Nbins));
  
  // fit the normal way
  RooFitResult *r1 = model.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  r1->Print("v");
  
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
    
  drawHorizontalLine(3, kRed, "dash");
  drawHorizontalLine(0, kBlack, "cont");
  drawHorizontalLine(-3, kRed, "dash");

  // going back to first pad
  c->cd(1);
  
  cmodel.plotOn(frame, Components("bkg"), LineStyle(kDashed), LineColor(kBlue));
  frame->Draw();

    modelHist->SetLineColor(kBlack);
    modelHist->SetLineWidth(5);
    modelHist->Draw("SAME HIST");
  
  // draw lines
  drawVerticalLine(omegaMean.getValV() - 3*omegaSigma.getValV(), kGray+2, "dash");
  drawVerticalLine(omegaMean.getValV(), kBlack, "dash");
  drawVerticalLine(omegaMean.getValV() + 3*omegaSigma.getValV(), kGray+2, "dash");
  
  c->Print(plotFile); // output file

  x.setRange("3sigmaRange", omegaMean.getValV() - 3*omegaSigma.getValV(), omegaMean.getValV() + 3*omegaSigma.getValV());
  RooAbsReal *bkg3Sigma = bkg.createIntegral(x, NormSet(x), Range("3sigmaRange"));

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
