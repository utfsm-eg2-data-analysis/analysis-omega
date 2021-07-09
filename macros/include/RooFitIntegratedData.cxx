#include "Global.h"

using namespace RooFit;

void RooFitIntegratedData(TString targetOption) {

  // set i/o
  TChain *treeExtracted = new TChain();
  TCut cutVertex;
  if (targetOption == "D") { // unified D
    treeExtracted->Add(gDataDir + "/comb_data-C.root/mix");
    treeExtracted->Add(gDataDir + "/comb_data-Fe.root/mix");
    treeExtracted->Add(gDataDir + "/comb_data-Pb.root/mix");
  } else {
    treeExtracted->Add(gDataDir + "/comb_data-" + targetOption + ".root/mix");
  }

  TH1D *theHist;
  treeExtracted->Draw("wD>>DATA_" + targetOption + "(100, 0., 2.5)", gCutDIS, "goff");
  theHist = (TH1D *)gROOT->FindObject("DATA_" + targetOption);
  theHist->SetTitle("DATA #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption);
  
  // define initial guess values
  Double_t meanIGV  = 0.8;
  Double_t sigmaIGV = 9.e-2; // 1.75, 3.5

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
  RooRealVar   b2("b2", "quadratic term", -0.1, -10., 0.);
  RooChebychev bkg("bkg", "background", x, RooArgList(b1, b2));

  // define frame
  Double_t binWidth = 25e-2; // in GeV
  Int_t    Nbins  = (Int_t) (((round(100*(plotRangeUp))/100) - (round(100*(plotRangeDown))/100))/binWidth);
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
  
  TCanvas *c0 = new TCanvas("c0", "c0");
  frameA->Draw();
  c0->Draw();
  
  /***** FIT B: GAUSSIAN *****/
  // (the signal)
  
  fitRangeDown  = meanIGV - 3*sigmaIGV;
  fitRangeUp    = meanIGV + 3*sigmaIGV;

  Double_t meanRangeDown = meanIGV - 5e-2;
  Double_t meanRangeUp   = meanIGV + 5e-2;
  
  Double_t sigmaRangeDown = sigmaIGV - 5e-2;
  Double_t sigmaRangeUp   = sigmaIGV + 5e-2;
  
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

  TCanvas *c1 = new TCanvas("c1", "c1");
  frameB->Draw();
  c1->Draw();

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
  
  TCanvas *c2 = new TCanvas("c2", "c2");
  frameC->Draw();
  c2->Draw();
  
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

  TCanvas *c3 = new TCanvas("c3", "c3");
  frameAB->Draw();
  c3->Draw();

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

  TCanvas *c4 = new TCanvas("c4", "c4");
  frameABC->Draw();
  c4->Draw();
  
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
  TCanvas *c5 = new TCanvas("c5", "c5");
  frameCON->Draw();
  c5->Draw();
}
