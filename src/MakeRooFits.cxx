/**************************************/
/* MakeRooFits.cxx                    */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// fits peak with a gaussian function and bkg with a 1st order polynomial
// - updated to "unified D"     : now we add all deuterium data, independent from which target
//                                to reduce the amount of error from the fits
// - updated to "toycombine.cxx": now we use the data from the ToyCombine filter
// - added kinematic dependence as an option

#include "analysisConfig.h"

#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooPolynomial.h"
#include "RooDataHist.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooAbsReal.h"
#include "RooArgSet.h"

using namespace RooFit;

/*** Global variables ***/

TString inputFolder = proFolder + "/out/filterData";
TString outFolder = proFolder + "/out/MakeRooFits"; // gets modified

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

// extended or not?
Int_t flagExtended = 0;
TString extendedSufix = "";

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

  /*** STAGE 1: Preliminary fit ***/
  /*
  // x-bin width = 5 MeV
  Int_t preNbins = 52;
  Double_t prePlotRangeDown = 0.24; // aprox. 6 omega sigma
  Double_t prePlotRangeUp = 0.50; // aprox. 6 omega sigma

  Double_t preSigmaIGV = 2.5e-2; // initial guess value
  Double_t preSigmaRangeDown = 1.5e-2; // 1.5
  Double_t preSigmaRangeUp = 3.5e-2; // 4

  Double_t preMeanIGV = 0.37; // initial guess value
  Double_t preMeanRangeDown = 0.36;
  Double_t preMeanRangeUp = 0.39; // 0.38

  Double_t preFitRangeDown = 0.34;
  Double_t preFitRangeUp = 0.42;
  
  TH1F *fitPreHist; 
  treeExtracted->Draw(Form("wD>>data4fit(%d, %f, %f)", preNbins, prePlotRangeDown, prePlotRangeUp), cutAll && cutTargType && kinvarCut, "goff");
  fitPreHist = (TH1F *)gROOT->FindObject("data4fit");

  RooRealVar preX("preX", "preX", prePlotRangeDown, prePlotRangeUp);

  RooRealVar preMean("preMean", "Mean of Gaussian", preMeanIGV, preMeanRangeDown, preMeanRangeUp);
  RooRealVar preSigma("preSigma", "Width of Gaussian", preSigmaIGV, preSigmaRangeDown, preSigmaRangeUp);
  RooGaussian pre("pre", "pre peak", preX, preMean, preSigma);

  RooDataHist preData("preData", "my data", preX, fitPreHist);
  pre.fitTo(preData, Range(preFitRangeDown, preFitRangeUp), Save());

  RooPlot *preFrame = preX.frame(Title("preliminary fit"), Bins(preNbins));
  preData.plotOn(preFrame, DataError(RooAbsData::SumW2), Name("preData"));
  pre.plotOn(preFrame, Name("preModel"), LineColor(kMagenta));
  pre.paramOn(preFrame, Layout(0.6, 0.9, 0.9)); // x1, x2, y2
  
  Double_t preChi2 = preFrame->chiSquare("preModel", "preData");

  TCanvas *c0 = new TCanvas("c0", "c0", 1366, 768);
  preFrame->Draw();
  c0->Print(outFolder + "/roofit0-" + targetOption + kinvarSufix + ".png"); // output file
  
  std::cout << "STAGE 1 COMPLETED." << std::endl;
  std::cout << "preMean  = " << preMean.getValV() << std::endl;
  std::cout << "preSigma = " << preSigma.getValV() << std::endl;
  std::cout << "preChi2  = " << preChi2 << std::endl;
  */
  /*** STAGE 0: Fit ***/
  
  // bin x-width = 5 MeV
  Int_t Nbins = 90; // 90
  Double_t plotRangeDown = 0.15; // 0.15
  Double_t plotRangeUp = 0.6; // 0.6

  // values obtained
  Double_t fitRangeDown = 0.368 - 5*0.02; // preMean.getValV() - 5*preSigma.getValV()
  Double_t fitRangeUp = 0.368 + 5*0.02; // preMean.getValV() + 5*preSigma.getValV()

  Double_t meanIGV = 0.37;
  Double_t meanRangeDown = 0.36;
  Double_t meanRangeUp = 0.39; // 0.38

  Double_t sigmaIGV = 1.75e-2;
  Double_t sigmaRangeDown = 1.5e-2; // 1.5
  Double_t sigmaRangeUp = 2e-2; // 3.5

  TH1F *dataHist;
  treeExtracted->Draw(Form("wD>>data(%d, %f, %f)", Nbins, plotRangeDown, plotRangeUp), cutAll && cutTargType && kinvarCut, "goff");
  dataHist = (TH1F *)gROOT->FindObject("data");

  // test
  TH1F *zoomedHist;
  treeExtracted->Draw(Form("wD>>zoomed(%d, %f, %f)", 40, fitRangeDown, fitRangeUp), cutAll && cutTargType && kinvarCut, "goff");
  zoomedHist = (TH1F *)gROOT->FindObject("zoomed");

  // keep their number of entries
  Double_t N_d = dataHist->Integral(1,Nbins);
  Double_t N_z = zoomedHist->Integral(1,40);
  
  /*** RooFit stuff ***/

  RooRealVar x("IMD", "IMD (GeV)", fitRangeDown, fitRangeUp);

  RooRealVar omegaMean("#mu(#omega)", "Mean of Gaussian", meanIGV, meanRangeDown, meanRangeUp);
  RooRealVar omegaSigma("#sigma(#omega)", "Width of Gaussian", sigmaIGV, sigmaRangeDown, sigmaRangeUp);
  RooGaussian omega("omega", "omega peak", x, omegaMean, omegaSigma);  

  RooRealVar b1("b1", "linear term", 0.1, -10, 10);
  // RooRealVar b2("b2", "quadratic term", 0.1, -10, 10);
  RooChebychev bkg("bkg", "background", x, RooArgList(b1));

  // define data
  RooDataHist data("data", "my data", x, dataHist);

  // define frame
  RooPlot *frame = x.frame(Title("IMD(#pi^{+} #pi^{-} #pi^{0}) for " + targetOption + " in" + kinvarTitle),
			   Bins(Nbins));
  
  if (flagExtended) {
    x.setRange("fitRange", fitRangeDown, fitRangeUp);

    // model(x) = sig_yield*sig(x) + bkg_yield*bkg(x)
    RooRealVar nsig("N_{#omega}", "omega yields", 0., zoomedHist->GetEntries());
    RooRealVar nbkg("N_{b}", "bkg yields", 0., zoomedHist->GetEntries());
    RooExtendPdf esig("esig", "esig", omega, nsig);
    RooExtendPdf ebkg("ebkg", "ebkg", bkg, nbkg);
    // RooAddPdf model("model", "model", RooArgList(omega, bkg), RooArgList(nsig, nbkg));
    RooAddPdf model("model", "model", RooArgList(esig, ebkg));

    // fit extended
    model.fitTo(data, Extended(), Save(), Range(fitRangeDown, fitRangeUp));

    // draw data and fit into frame
    data.plotOn(frame, Name("Data")); // DataError(RooAbsData::SumW2)
    model.plotOn(frame, Name("Model"), LineColor(kRed));
    model.plotOn(frame, Components("bkg"), LineStyle(kDashed), LineColor(kBlue));
    
    // add params
    model.paramOn(frame, Layout(0.1, 0.3, 0.9)); // x1, x2, delta-y
    frame->getAttText()->SetTextSize(0.03);

    // check how that integration goes...
    Double_t N_omega = nsig.getValV();
    Double_t N_bkg = nbkg.getValV();
    Double_t N_sum = N_omega + N_bkg;

    // another attempt
    RooArgSet *comps = model.getComponents();
    RooAbsPdf *attempt = comps->find("omega");
    attempt->plotOn(frame, Name("attempt"), LineColor(kMagenta));
    
    RooAbsReal *I_omega = esig.createIntegral(x, Range("fitRange"));
    RooAbsReal *I_bkg = ebkg.createIntegral(x, Range("fitRange"));
    RooAbsReal *I_model = model.createIntegral(x, Range("fitRange"));

    Double_t N_zz = data.sumEntries(0, "fitRange");
    Double_t IN_zz = I_omega->getValV()*N_zz;
    
    std::cout << std::endl;
    std::cout << "I_omega=" << I_omega->getValV() << std::endl;
    std::cout << "I_bkg=" << I_bkg->getValV() << std::endl;
    std::cout << "I_model=" << I_model->getValV() << std::endl;
    std::cout << "N_zz=" << N_zz << std::endl;
    std::cout << "I_omega*N_zz=" << IN_zz << std::endl;
    std::cout << "N_omega=" << N_omega << std::endl;
    std::cout << "N_bkg=" << N_bkg << std::endl;
    std::cout << "N_sum=" << N_sum << std::endl;
    std::cout << "N_z=" << N_z << std::endl;
    std::cout << "N_d=" << N_d << std::endl;
    std::cout << std::endl;    

  } else {
    x.setRange("fitRange", fitRangeDown, fitRangeUp);

    // model(x) = frac*sig(x) + (1-frac)*bkg(x)
    RooRealVar frac("frac", "signal fraction", 0., 1.);
    RooAddPdf model("model", "model", RooArgList(omega, bkg), RooArgList(frac));

    // fit
    model.fitTo(data, Save(), Range(fitRangeDown, fitRangeUp));

    // draw data and fit into frame
    data.plotOn(frame, Name("Data")); // DataError(RooAbsData::SumW2)
    model.plotOn(frame, Name("Model"), LineColor(kRed));
    model.plotOn(frame, Components("bkg"), LineStyle(kDashed), LineColor(kBlue));

    // add params
    model.paramOn(frame, Layout(0.1, 0.3, 0.9)); // x1, x2, delta-y
    frame->getAttText()->SetTextSize(0.03);

    // check how that integration goes
    Double_t frac0 = frac.getValV();
    Double_t poto = N_z*frac0;
    Double_t peo = N_z*(1-frac0);
    Double_t potopoto = N_d*frac0;
    Double_t peopeo = N_d*(1-frac0);
    
    RooAbsReal *I_omega = omega.createIntegral(x);
    RooAbsReal *I_bkg = bkg.createIntegral(x);
    RooAbsReal *I_model = model.createIntegral(x);

    Double_t N_zz = data.sumEntries(0, "fitRange");
    Double_t FN_zz = frac.getValV()*N_zz;
    
    std::cout << std::endl;
    std::cout << "I_omega=" << I_omega->getValV() << std::endl;
    std::cout << "I_bkg=" << I_bkg->getValV() << std::endl;
    std::cout << "I_model=" << I_model->getValV() << std::endl;
    std::cout << "frac=" << frac.getValV() << std::endl;
    std::cout << "N_zz=" << N_zz << std::endl;
    std::cout << "frac*N_zz=" << FN_zz << std::endl;
    std::cout << "N_z=" << N_z << std::endl;
    std::cout << "N_d=" << N_d << std::endl;
    std::cout << "frac*N_z=" << poto << std::endl;
    std::cout << "(1-frac)*N_z=" << peo << std::endl;
    std::cout << "frac*N_d=" << potopoto << std::endl;
    std::cout << "(1-frac)*N_d=" << peopeo << std::endl;
    std::cout << std::endl;
  }

  // draw!
  TCanvas *c = new TCanvas("c", "c", 1366, 768);
  frame->Draw();
  
  // chi2
  Double_t chi2 = frame->chiSquare("Model", "Data");
  TPaveText *textBlock = new TPaveText(0.1, 0.55, 0.3, 0.6, "NDC TL"); // x1, y1, x2, y2
  textBlock->AddText(Form("#chi^{2}/ndf = %.3f", chi2));
  textBlock->SetFillColor(kWhite);
  textBlock->SetShadowColor(kWhite);
  textBlock->SetTextColor(kBlack);
  textBlock->Draw();

  // draw lines
  drawVerticalLineGrayest(omegaMean.getValV() - 3*omegaSigma.getValV());
  drawVerticalLineBlack(omegaMean.getValV());
  drawVerticalLineGrayest(omegaMean.getValV() + 3*omegaSigma.getValV());
  
  c->Print(outFolder + "/roofit0-" + targetOption + kinvarSufix + extendedSufix + ".png"); // output file
 
  /*
  TString outputTextFile = outFolder + "/roofit-" + targetOption + kinvarSufix + ".dat"; // output file
  std::cout << "Writing " << outputTextFile << " ..." << std::endl;
  std::ofstream outFinalFile(outputTextFile, std::ios::out);
  // line 1: b1
  outFinalFile << b1.getValV() << "\t" << b1.getError() << std::endl;
  // line 2: bkgYields
  outFinalFile << bkgYields.getValV() << "\t\t" << bkgYields.getError() << std::endl;
  // line 3: omegaMean
  outFinalFile << omegaMean.getValV() << "\t" << omegaMean.getError() << std::endl;
  // line 4: omegaSigma
  outFinalFile << omegaSigma.getValV() << "\t" << omegaSigma.getError() << std::endl;
  // line 5: omegaYields (directly from parameter) (METHOD 1)
  outFinalFile << omegaYields.getValV() << "\t\t" << omegaYields.getError() << std::endl;
  // line 6: chi2
  outFinalFile << chi2 << "\t\t" << "0" << std::endl;
  
  outFinalFile.close();
  std::cout << "File " << outputTextFile << " has been created!" << std::endl;
  std::cout << "Chi2: " << chi2 << std::endl;
  */

  /*** BEVINGTON PROCEDURE ***/
  /*
  // step 1: define three regions
  
  Double_t limitRegionA[2] = {plotRangeDown, mean0 - 3*sigma0};
  Double_t limitRegionB[2] = {mean0 - 3*sigma0, mean0 + 3*sigma0};
  Double_t limitRegionC[2] = {mean0 + 3*sigma0, plotRangeUp};

  // step 2: fit bkg in all three regions

  RooRealVar c1("c1", "linear term", 1.0, 0.5, 1.5);
  RooChebychev bkg2("bkg2", "background2", x, RooArgList(c1));
  RooRealVar bamp2("bamp2", "bkg amplitude 2", 1);
  RooAddPdf model2("model2", "model2", RooArgList(bkg2), RooArgList(bamp2));
  model2.fitTo(data, Extended(), Save(), Range(limitRegionA[0], limitRegionC[1]));
  //bkg2.fitTo(data, Save(), Range(limitRegionA[0], limitRegionC[1]));
  // draw hist and function to frame
  TCanvas *c2 = new TCanvas("c2", "c2", 1366, 768);
  RooPlot *frame2 = x.frame(Title("IMD(#pi^{+} #pi^{-} #pi^{0}) for " + targetOption + " in" + kinvarTitle),
			    Bins(Nbins));
  data.plotOn(frame2, Name("Data")); // DataError(RooAbsData::SumW2)
  model2.plotOn(frame2, LineStyle(kDashed), LineColor(kBlue));
  model2.paramOn(frame2, Layout(0.1, 0.4, 0.9)); // x1, x2, delta-y

  /*
  RooRealVar t1("t1", "linear term", c1.getValV());
  RooChebychev test("test", "test", x, RooArgList(t1));
  test.plotOn(frame2, LineStyle(kDashed), LineColor(kMagenta));
  */
  /*
  frame2->Draw();

  TH1F *bkgHist = (TH1F *)bkg2.createHistogram("bkgHist", x, Binning(Nbins, plotRangeDown, plotRangeUp), Extended());
  bkgHist->SetLineWidth(2);
  bkgHist->SetLineColor(kBlue);
  bkgHist->Scale(bamp2.getValV());
  bkgHist->Draw("SAME HIST");
  
  c2->Print(outFolder + "/roofit2-" + targetOption + kinvarSufix + ".png"); // output file
  // keep number
  Double_t lin2 = c1.getValV();

  std::cout << std::endl;
  std::cout << "N_d=" << dataHist->Integral(1,Nbins) << std::endl;
  std::cout << "N_b=" << bkgHist->Integral(1,Nbins) << std::endl;
  std::cout << std::endl;
  */
  /*
  // step 3: fit all function in central regions with bkg params fixed
  RooRealVar omegaMean("omegaMean", "Mean of Gaussian", mean0, meanRangeDown, meanRangeUp);
  RooRealVar omegaSigma("omegaSigma", "Width of Gaussian", sigma0, sigmaRangeDown, sigmaRangeUp);
  RooGaussian omega("omega", "omega peak", x, omegaMean, omegaSigma);
  RooRealVar c1("c1", "linear term", 1.0, 0.5, 1.5);
  RooChebychev bkg2("bkg2", "background2", x, RooArgList(c1));
  bkg2.fitTo(data, Save(), Range(limitRegionA[0],
				 limitRegionC[1]));
  
  // draw hist and function to frame
  TCanvas *c2 = new TCanvas("c2", "c2", 1366, 768);
  RooRealVar omegaYields("omegaYields", "omega yields", 0., dataHist->GetEntries());
  RooRealVar bkgYields("bkgYields", "bkg yields", 0., dataHist->GetEntries());

  RooPlot *frame2 = x.frame(Title("IMD(#pi^{+} #pi^{-} #pi^{0}) for " + targetOption + " in" + kinvarTitle),
			    Bins(Nbins));
  data.plotOn(frame2, Name("Data")); // DataError(RooAbsData::SumW2)
  bkg2.plotOn(frame2, LineStyle(kDashed), LineColor(kBlue));
  bkg2.paramOn(frame2, Layout(0.1, 0.4, 0.9)); // x1, x2, delta-y
  frame2->Draw();
  c2->Print(outFolder + "/roofit2-" + targetOption + kinvarSufix + ".png"); // output file
  // keep number
  Double_t lin2 = c2.getValV();

  // model(x) = sig_yield*sig(x) + bkg_yield*bkg(x)
  RooAddPdf model("model", "model", RooArgList(omega, bkg), RooArgList(omegaYields, bkgYields));
  
  // data
  RooDataHist data("data", "my data", x, dataHist);

  // fit
  model.fitTo(data, Extended(), Save(), Range(fitRangeDown, fitRangeUp));
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
  while ((c = getopt(argc, argv, "ht:z:q:n:p:e")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'z': flagZ = 1; binNumber = atoi(optarg); break;
    case 'q': flagQ2 = 1; binNumber = atoi(optarg); break;
    case 'n': flagNu = 1; binNumber = atoi(optarg); break;
    case 'p': flagPt2 = 1; binNumber = atoi(optarg); break;
    case 'e': flagExtended = 1; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeRooFits -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing MakeRooFits program. Chosen parameters are:" << std::endl;
  std::cout << "  targetOption=" << targetOption << std::endl;
  std::cout << "  kinvarName=" << kinvarName << std::endl;
  std::cout << "  binNumber=" << binNumber << std::endl;
  std::cout << "  flagExtended=" << flagExtended << std::endl;
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
  std::cout << "./MakeRooFits -[kinvar][number]" << std::endl;
  std::cout << "    analyzes respective kinematic variable bin" << std::endl;
  std::cout << "    z[3-7] : analyzes specific Z bin" << std::endl;
  std::cout << "    q[1-5] : analyzes specific Q2 bin" << std::endl;
  std::cout << "    n[1-5] : analyzes specific Nu bin" << std::endl;
  std::cout << "    p[1-5] : analyzes specific Pt2 bin" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeRooFits -e" << std::endl;
  std::cout << "    makes an extended fit" << std::endl;
}

void assignOptions() {
  // for targets, unified D
  if (targetOption == "D") {
    inputFile1 = inputFolder + "/C/comb_C-thickD2.root";
    inputFile2 = inputFolder + "/Fe/comb_Fe-thickD2.root";
    inputFile3 = inputFolder + "/Pb/comb_Pb-thinD2.root";
    cutTargType = "TargType == 1";
  } else if (targetOption == "C") {
    inputFile1 = inputFolder + "/C/comb_C-thickD2.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Fe") {
    inputFile1 = inputFolder + "/Fe/comb_Fe-thickD2.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Pb") {
    inputFile1 = inputFolder + "/Pb/comb_Pb-thinD2.root";
    cutTargType = "TargType == 2";
  }
  // for kinvar
  Double_t lowEdge, highEdge;
  if (flagZ) {
    lowEdge = edgesZ[binNumber-3];
    highEdge = edgesZ[binNumber+1-3];
    kinvarSufix = Form("-z%d", binNumber);
    kinvarName = "Z";
    outFolder = outFolder + "/Z";
  } else if (flagQ2) {
    lowEdge = edgesQ2[binNumber-1];
    highEdge = edgesQ2[binNumber+1-1];
    kinvarSufix = Form("-q%d", binNumber);
    kinvarName = "Q2";
    outFolder = outFolder + "/Q2";
  } else if (flagNu) {
    lowEdge = edgesNu[binNumber-1];
    highEdge = edgesNu[binNumber+1-1];
    kinvarSufix = Form("-n%d", binNumber);
    kinvarName = "Nu";
    outFolder = outFolder + "/Nu";
  } else if (flagPt2) {
    lowEdge = edgesPt2[binNumber-1];
    highEdge = edgesPt2[binNumber+1-1];
    kinvarSufix = Form("-p%d", binNumber);
    kinvarName = "Pt2";
    outFolder = outFolder + "/Pt2";
  }
  kinvarCut = Form("%f < ", lowEdge) + kinvarName + " && " + kinvarName + Form(" < %f", highEdge);
  kinvarTitle = Form(" (%.02f < ", lowEdge) + kinvarName + Form(" < %.02f)", highEdge);
  if (flagExtended) extendedSufix = "-ext";
}
