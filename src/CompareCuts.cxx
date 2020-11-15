/*********************************/
/* CompareCuts.cxx               */
/*                               */
/* Andrés Bórquez                */
/*                               */
/*********************************/

// Checking the signal/noise ratio by probing different cuts into a basic-filtered dataset
// (November 2020)

#include "analysisConfig.h"

#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooGaussian.h"
#include "RooBreitWigner.h"
#include "RooChebychev.h"
#include "RooPolynomial.h"
#include "RooFFTConvPdf.h"
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

TString inputDir  = workDir + "/FilterNCombine/basic";
TString outputDir = workDir + "/CompareCuts";

/*** Declaration of functions ***/

TCut SelectCut(Int_t n) {
  // define cuts
  TCut cut00 = "";
  TCut cut01 = cutPi0;
  TCut cut02 = cutPipPim;
  TCut cut03 = "Yec > -1.4 && Yec < 1.4";
  TCut cut04 = "StatusEl > 0 && NRowsDCEl != 0 && DCStatusEl > 0 && StatDCEl > 0 && NRowsECEl != 0 && StatECEl > 0 && NRowsSCEl != 0 && SCStatusEl == 33";
  TCut cut05 = "Pe > 0.2 && P_corr[0] > 0.2 && P_corr[1] > 0.2";
  TCut cut06 = "ThetaLabEl < 120. && ThetaLab[0] < 120.";
  TCut cut07 = "Q2 > 1. && Q2 < 4. && Nu > 2.2 && Nu < 4.2 && wZ_corr > 0.5 && wZ_corr < 1.0 && wPt2_corr > 0. && wPt2_corr < 1.5";
  TCut cut08 = "P_corr[2] > 0.2 && P_corr[3] > 0.2";
  TCut cut09 = "P_corr[1] < 5.";
  /*
  TCut cut10 = "";
  TCut cut11 = "";
  TCut cut12 = "";
  TCut cut13 = "";
  TCut cut14 = "";
  TCut cut15 = "";
  TCut cut16 = "";
  TCut cut17 = "";
  TCut cut18 = "";
  TCut cut19 = "";
  TCut cut20 = "";
  */
  // choose cut
  switch (n) {
  case 0: return cut00;
  case 1: return cut01;
  case 2: return cut02;
  case 3: return cut03;
  case 4: return cut04;
  case 5: return cut05;
  case 6: return cut06;
  case 7: return cut07;
  case 8: return cut08;
  case 9: return cut09;
  default: return cut00;
  }
}

void MakeRooFit(TH1F *theHist, Double_t meanIGV, Double_t sigmaIGV, Double_t sigmaLimit);

/*** Main ***/

int main(int argc, char **argv) {

  // just in case
  system("mkdir -p " + outputDir);


  // set i/o
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputDir + "/Fe/comb_basic-Fe.root/mix");

  // create and open output file
  TFile *rootOutputFile = new TFile(outputDir + "/cuts_Fe.root", "RECREATE");

  /*** STEP 1: BIG PICTURE ***/
  
  // set cuts
  TCut cutVertex = "TargType == 2";
  TCut cutDATA   = cutDIS && cutVertex;
  
  // create histogram
  TH1F *bigHist_DATA;
  treeExtracted->Draw("wD_corr>>DATA_Fe(120, 0., 1.6)", cutDATA, "goff");
  bigHist_DATA = (TH1F *)gROOT->FindObject("DATA_Fe");
  bigHist_DATA->SetTitle("DATA #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for Fe");

  // save hist
  bigHist_DATA->Write();
  
  // define initial guess values
  Double_t meanIGV  = 0.782;
  Double_t sigmaIGV = 2.0e-2; // 1.75, 3.5
  
  TCut cutSELECTED;

  TH1F   *binHist;
  TString binHistName;
  
  // cuts loop
  for (Int_t cc = 0; cc < 10; cc++) {

    /*** STEP 2: DRAW SPECTRUM ***/
      
    // update
    binHistName = "DATA_Fe_";
    binHistName += Form("0%d", cc);
    cutSELECTED = SelectCut(cc);
    // extract
    treeExtracted->Draw("wD_corr>>" + binHistName + "(160, 0., 1.6)", cutDATA && cutSELECTED, "goff"); // 10 MeV
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("#Deltam(#gamma #gamma #pi^{+} #pi^{-}) for Fe DATA");
    // save
    binHist->Write();

    /*** STEP 3: FIT ***/

    MakeRooFit(binHist, meanIGV, sigmaIGV, 1.5e-2);
  }
  
  // close file
  rootOutputFile->Close();
  
  return 0;
}

/*** Functions ***/

void MakeRooFit(TH1F *theHist, Double_t meanIGV, Double_t sigmaIGV, Double_t sigmaLimit) {

  // define plot range and variable
  Double_t plotRangeDown = meanIGV - 9*sigmaIGV;
  Double_t plotRangeUp   = meanIGV + 9*sigmaIGV;
  RooRealVar x("IMD", "Reconstructed Mass (GeV)", plotRangeDown, plotRangeUp);

  // define data
  RooDataHist data("data", "my data", x, theHist);
  TString histName = theHist->GetName();
  
  /***** FIT A: BKG *****/
  // (left of the signal)

  Double_t fitRangeDown  = meanIGV - 9*sigmaIGV;
  Double_t fitRangeUp    = meanIGV - 2*sigmaIGV;

  RooRealVar   b1("b1", "linear term", 0., -20, 20);
  RooRealVar   b2("b2", "quadratic term", -0.1, -10., 0.); // definition, use it only when bkgOption=2
  RooChebychev bkg("bkg", "background", x, RooArgList(b1, b2));

  // define frame
  Int_t    Nbins  = (Int_t) (((round(100*(plotRangeUp))/100) - (round(100*(plotRangeDown))/100))/1e-2); // 10 MeV
  RooPlot *frameA = x.frame(Name("fA_" + histName), Title(theHist->GetTitle()), Bins(Nbins));
  
  // fit the normal way
  bkg.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  
  // draw
  data.plotOn(frameA, Name("Data")); // DataError(RooAbsData::SumW2)
  bkg.plotOn(frameA, Name("Model"), LineColor(kBlue));

  // draw params values
  bkg.paramOn(frameA, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frameA->getAttText()->SetTextSize(0.025);
  frameA->getAttLine()->SetLineWidth(0);
  frameA->GetXaxis()->CenterTitle();
  frameA->GetYaxis()->SetTitle("Counts");
  frameA->GetYaxis()->CenterTitle();
  
  frameA->Write();
  
  /***** FIT B: GAUSSIAN *****/
  // (the signal)
  
  fitRangeDown  = meanIGV - 3*sigmaIGV;
  fitRangeUp    = meanIGV + 3*sigmaIGV;

  Double_t meanRangeDown = meanIGV - 5e-2;
  Double_t meanRangeUp   = meanIGV + 5e-2;
  
  Double_t sigmaRangeDown = sigmaIGV - 5e-3;
  Double_t sigmaRangeUp   = sigmaIGV + sigmaLimit;
  
  RooRealVar  mean("#mu(#omega)", "Mean of Gaussian", meanIGV, meanRangeDown, meanRangeUp);
  RooRealVar  sigma("#sigma(#omega)", "Width of Gaussian", sigmaIGV, sigmaRangeDown, sigmaRangeUp);
  RooGaussian gauss("gauss", "omega-g peak", x, mean, sigma);

  // define frame
  RooPlot *frameB = x.frame(Name("fB_" + histName), Title(theHist->GetTitle()), Bins(Nbins));
  
  // fit the normal way
  gauss.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  
  // draw
  data.plotOn(frameB, Name("Data")); // DataError(RooAbsData::SumW2)
  gauss.plotOn(frameB, Name("Model"), LineColor(kRed));

  // draw params values
  gauss.paramOn(frameB, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frameB->getAttText()->SetTextSize(0.025);
  frameB->getAttLine()->SetLineWidth(0);
  frameB->GetXaxis()->CenterTitle();
  frameB->GetYaxis()->SetTitle("Counts");
  frameB->GetYaxis()->CenterTitle();
  
  frameB->Write();

  /***** FIT C: BKG *****/
  // (right of the signal)

  fitRangeDown  = meanIGV + 3*sigmaIGV;
  fitRangeUp    = meanIGV + 9*sigmaIGV;

  RooRealVar   b3("b3", "linear term", 0., -20, 20);
  RooRealVar   b4("b4", "quadratic term", -0.1, -10., 0.);
  RooChebychev bkg2("bkg2", "background2", x, RooArgList(b3, b4));

  // define frame
  RooPlot *frameC = x.frame(Name("fC_" + histName), Title(theHist->GetTitle()), Bins(Nbins));
  
  // fit the normal way
  bkg2.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  
  // draw
  data.plotOn(frameC, Name("Data")); // DataError(RooAbsData::SumW2)
  bkg2.plotOn(frameC, Name("Model"), LineColor(kBlue));

  // draw params values
  bkg2.paramOn(frameC, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frameC->getAttText()->SetTextSize(0.025);
  frameC->getAttLine()->SetLineWidth(0);
  frameC->GetXaxis()->CenterTitle();
  frameC->GetYaxis()->SetTitle("Counts");
  frameC->GetYaxis()->CenterTitle();
  
  frameC->Write();
  
  /***** FIT AB: GAUSSIAN+POL2 *****/
  // (left bkg + signal)

  fitRangeDown  = meanIGV - 9*sigmaIGV;
  fitRangeUp    = meanIGV + 3*sigmaIGV;

  // model(x) = sig_yield*sig(x) + bkg_yield*bkg(x)
  RooRealVar nsig("N_{#omega}", "omega yields", 0., theHist->GetEntries());
  RooRealVar nbkg("N_{b}", "bkg yields", 0., theHist->GetEntries());
  // RooAddPdf  model("model", "model", RooArgList(gxbw, bkg), RooArgList(nsig, nbkg));
  RooAddPdf  modelAB("model", "model", RooArgList(gauss, bkg), RooArgList(nsig, nbkg));

  // define frame
  RooPlot *frameAB = x.frame(Name("fAB_" + histName), Title(theHist->GetTitle()), Bins(Nbins));
  
  // fit the normal way
  modelAB.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  
  // draw
  data.plotOn(frameAB, Name("Data"));
  modelAB.plotOn(frameAB, LineColor(kRed));
  modelAB.plotOn(frameAB, Components("bkg"), LineStyle(kDashed), LineColor(kBlue));

  // draw params values
  modelAB.paramOn(frameAB, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frameAB->getAttText()->SetTextSize(0.025);
  frameAB->getAttLine()->SetLineWidth(0);
  frameAB->GetXaxis()->CenterTitle();
  frameAB->GetYaxis()->SetTitle("Counts");
  frameAB->GetYaxis()->CenterTitle();
  
  frameAB->Write();

  /***** FIT ABC: GAUSSIAN+POL2 *****/
  // (left bkg + signal)

  fitRangeDown  = meanIGV - 9*sigmaIGV;
  fitRangeUp    = meanIGV + 9*sigmaIGV;

  // model(x) = sig_yield*sig(x) + bkg_yield*bkg(x)
  RooAddPdf  modelABC("model", "model", RooArgList(gauss, bkg), RooArgList(nsig, nbkg));

  // define frame
  RooPlot *frameABC = x.frame(Name("fABC_" + histName), Title(theHist->GetTitle()), Bins(Nbins));
  
  // fit the normal way
  modelABC.fitTo(data, Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  
  // draw
  data.plotOn(frameABC, Name("Data"));
  modelABC.plotOn(frameABC, LineColor(kRed));
  modelABC.plotOn(frameABC, Components("bkg"), LineStyle(kDashed), LineColor(kBlue));

  // draw params values
  modelABC.paramOn(frameABC, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frameABC->getAttText()->SetTextSize(0.025);
  frameABC->getAttLine()->SetLineWidth(0);
  frameABC->GetXaxis()->CenterTitle();
  frameABC->GetYaxis()->SetTitle("Counts");
  frameABC->GetYaxis()->CenterTitle();
  
  frameABC->Write();
  
  /*** FIT CONSTRAINED ***/

  // define constraints
  RooGaussian conSigma("conSigma", "conSigma", sigma, RooConst(2.5e-2), RooConst(1e-2));
  RooProdPdf  modelCON("modelCON", "model with constraint", RooArgSet(modelABC, conSigma));

  RooPlot *frameCON = x.frame(Name("fCON_" + histName), Title(theHist->GetTitle()), Bins(Nbins));  
  
  // fit constraint model
  RooFitResult *rCON = modelCON.fitTo(data, Constrain(conSigma), Minos(kTRUE), Extended(), Save(), Range(fitRangeDown, fitRangeUp));
  rCON->Print("v");
  
  // draw
  data.plotOn(frameCON, Name("Data")); // DataError(RooAbsData::SumW2)
  modelCON.plotOn(frameCON, Name("Model"), LineColor(kRed));
  modelCON.plotOn(frameCON, Components("bkg"), LineStyle(kDashed), LineColor(kBlue));
  
  // draw params values
  modelCON.paramOn(frameCON, Layout(0.11, 0.3, 0.89), Format("NEAU", AutoPrecision(2))); // x1, x2, delta-y
  frameCON->getAttText()->SetTextSize(0.025);
  frameCON->getAttLine()->SetLineWidth(0);
  frameCON->GetXaxis()->CenterTitle();
  frameCON->GetYaxis()->SetTitle("Counts");
  frameCON->GetYaxis()->CenterTitle();
  
  // draw and save results
  frameCON->Write();
  rCON->Write("rfCON_" + histName);
}
