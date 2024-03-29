#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

using namespace RooFit;

const Int_t Nkinvars = 4;
const Int_t Nbins = 4;

void Make_BkgFitting(TString targetOption = "C", TString kinvarOption = "Q2", Int_t fixParams = 0, TString StoreOption = "") {
  // 1) Fit omega signal and background
  // 2) Store fit values

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain = GetThreePionFinderChain(targetOption);
  SetAliases(dataChain);

  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
  } else if (targetOption == "All") {
    CutVertex = gCutSolid || gCutLiquid;
  } else {  // solid targets
    CutVertex = gCutSolid;
  }

  // about kinvar option
  TString kinvarTitle;
  Double_t EdgesKinvar[Nbins + 1];
  if (kinvarOption == "Q2") {
    kinvarTitle = "Q^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) {
      EdgesKinvar[i] = kEdgesQ2[i];
    }
  } else if (kinvarOption == "Nu") {
    kinvarTitle = "#nu";
    for (Int_t i = 0; i < Nbins + 1; i++) {
      EdgesKinvar[i] = kEdgesNu[i];
    }
  } else if (kinvarOption == "wZ") {
    kinvarTitle = "z_{h}";
    for (Int_t i = 0; i < Nbins + 1; i++) {
      EdgesKinvar[i] = kEdgesZ[i];
    }
  } else if (kinvarOption == "wPt2") {
    kinvarTitle = "p_{T}^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) {
      EdgesKinvar[i] = kEdgesPt2[i];
    }
  }

  Int_t plotNbins = 24;
  Double_t plotMin = 0.66;
  Double_t plotMax = 0.90;
  TString histProperties = Form("(%i, %f, %f)", plotNbins, plotMin, plotMax);

  TString auxCut;
  TCut CutBin;

  /*** HISTOGRAMS, FUNCTIONS AND PARAMETERS ***/

  TH1D *signalHist[Nbins];
  TH1D *bkgHist[Nbins];
  TH1D *modelHist[Nbins];
  TH1D *dataHist[Nbins];
  TH1D *dataErrHist[Nbins];
  TH1D *testHist[Nbins];

  TTree *auxTree[Nbins];

  RooPlot *upperFrame[Nbins];
  RooPlot *lowerFrame[Nbins];

  TString NomegaS[Nbins];
  TString MeanS[Nbins];
  TString SigmaS[Nbins];
  TString NbkgS[Nbins];
  TString PolaS[Nbins];
  TString PolbS[Nbins];

  Double_t meanVal[Nbins];
  Double_t sigmaVal[Nbins];

  RooFitResult *FitResult[Nbins];

  // in the case of fix params
  TFile *RootInputFile;
  RooFitResult *InputFit[Nbins];
  Double_t MeanFix[Nbins];
  Double_t SigmaFix[Nbins];
  if (fixParams) {
    // read the bkg-subtracted output file when running on "All" data
    RootInputFile = new TFile(gProDir + "/gfx/omega_bkg-fitting/bkg-fitting_All_" + kinvarOption + ".root");
    // loop over bins
    for (Int_t i = 0; i < Nbins; i++) {
      // get fit function to retrieve parameter's values
      InputFit[i] = (RooFitResult *)RootInputFile->Get(Form("fit-result_%i", i));
      MeanFix[i] = ((RooRealVar *)InputFit[i]->floatParsFinal().find("#mu(#omega)"))->getValV();
      SigmaFix[i] = ((RooRealVar *)InputFit[i]->floatParsFinal().find("#sigma(#omega)"))->getValV();
    }
  }

  // loop over bins
  for (Int_t i = 0; i < Nbins; i++) {
    // prepare histograms
    auxCut = Form("%f", EdgesKinvar[i]);
    auxCut += " < " + kinvarOption + " && " + kinvarOption + " < ";
    auxCut += Form("%f", EdgesKinvar[i + 1]);
    CutBin = auxCut;

    std::cout << auxCut << std::endl;

    dataChain->Draw(Form("wD>>data_%i", i) + histProperties, gCutDIS && CutVertex && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin,
                    "goff");
    dataHist[i] = (TH1D *)gROOT->FindObject(Form("data_%i", i));

    // prepare tree
    auxTree[i] = dataChain->CopyTree(gCutDIS && CutVertex && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin);

    // define x variable and ranges
    RooRealVar x("wD", "", plotMin, plotMax);

    // define data set (maximum-likelihood)
    RooDataSet data("data", "data", auxTree[i], x);

    // define signal function
    RooRealVar mean("#mu(#omega)", "mean of gaussian", 0.782, 0.775, 0.790);
    RooRealVar sigma("#sigma(#omega)", "width of gaussian", 0.024, 0.008, 0.035);
    RooGaussian signal("signal", "omega signal", x, mean, sigma);

    // fix parameters
    if (fixParams) {
      mean.setVal(MeanFix[i]);
      mean.setConstant(kTRUE);
      sigma.setVal(SigmaFix[i]);
      sigma.setConstant(kTRUE);
    }

    // define bkg function
    RooRealVar b1("b1", "linear term", 0., -20, 20);
    RooRealVar b2("b2", "quadratic term", -0.1, -10., 0.);
    RooChebychev bkg("bkg", "background", x, RooArgList(b1, b2));

    // define extended composite model
    RooRealVar nsig("N_{#omega}", "number of omega particles", 1000, 0., 1000000);
    RooRealVar nbkg("N_{bkg}", "number of background", 1000, 0, 1000000);
    RooAddPdf model("model", "(g+pol2)", RooArgList(bkg, signal), RooArgList(nbkg, nsig));

    upperFrame[i] = x.frame(Name(Form("upper_f_%i", i)));
    lowerFrame[i] = x.frame(Name(Form("lower_f_%i", i)));

    FitResult[i] = model.fitTo(data, Minos(kTRUE), Extended(), Save());
    FitResult[i]->SetName(Form("fit-result_%i", i));

    data.plotOn(upperFrame[i], Name("Data"), Binning(plotNbins, plotMin, plotMax), LineColor(myBlack), MarkerColor(myBlack));
    model.plotOn(upperFrame[i], Name("Model"), LineColor(myBlue));

    model.plotOn(upperFrame[i], Name("Bkg"), Components("bkg"), LineColor(kGray + 2), LineStyle(kDashed));
    model.plotOn(upperFrame[i], Name("Signal"), Components("signal"), LineColor(myRed));

    modelHist[i] = (TH1D *)model.createHistogram(Form("model_%i", i), x, Binning(plotNbins, plotMin, plotMax), Extended());
    modelHist[i]->Scale((plotMax - plotMin) / (Double_t)plotNbins);  // bin width

    dataErrHist[i] = new TH1D(Form("dataErrHist_%i", i), Form("dataErrHist_%i", i), plotNbins, plotMin, plotMax);
    for (Int_t k = 1; k <= plotNbins; k++) {
      dataErrHist[i]->SetBinContent(k, dataHist[i]->GetBinError(k));
      dataErrHist[i]->SetBinError(k, 0);
    }

    testHist[i] = new TH1D(Form("testHist_%i", i), Form("testHist_%i", i), plotNbins, plotMin, plotMax);
    testHist[i]->Add(dataHist[i], modelHist[i], 1, -1);
    testHist[i]->Divide(dataErrHist[i]);

    // assign parameters
    NomegaS[i] = Form("N_{#omega} = %.3f #pm %.3f", nsig.getValV(), nsig.getError());
    MeanS[i] = Form("#mu = %.3f #pm %.6f", mean.getValV(), mean.getError());
    SigmaS[i] = Form("#sigma = %.3f #pm %.6f", sigma.getValV(), sigma.getError());
    NbkgS[i] = Form("N_{bkg} = %.3f #pm %.3f", nbkg.getValV(), nbkg.getError());
    PolaS[i] = Form("b1 = %.3f #pm %.6f", b1.getValV(), b1.getError());
    PolbS[i] = Form("b2 = %.3f #pm %.6f", b2.getValV(), b2.getError());

    // to represent as vertical lines
    meanVal[i] = mean.getValV();
    sigmaVal[i] = sigma.getValV();
  }

  /*** FIX Y-AXIS ***/

  Double_t MaxRange = 0;
  for (Int_t i = 0; i < Nbins; i++) {
    if (dataHist[i]->GetMaximum() > MaxRange) {
      MaxRange = dataHist[i]->GetMaximum();
    }
  }
  MaxRange += MaxRange * 0.15;

  /*** DRAW ***/

  // set canvas
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  const Int_t Nx = 2;
  const Int_t Ny = 2;

  TString CanvasName = "bkg-fitting_" + targetOption + "_" + kinvarOption;
  TCanvas *can1 = new TCanvas(CanvasName, CanvasName, 1920, 2880);
  can1->Divide(Nx, Ny, 0.0001, 0.0001);

  // define pads
  TPad *upperPad[Nbins];
  TPad *lowerPad[Nbins];

  Int_t counter = 1;
  // loop over bins
  for (Int_t i = 0; i < Nbins; i++) {
    // prepare pads
    upperPad[i] = new TPad(Form("upper_%i", i), Form("upper_%i", i), 0.05, 0.40, 0.95, 0.95, 0, 0, 0);  // x1,y1,x2,y2
    upperPad[i]->SetTopMargin(0.05);
    upperPad[i]->SetBottomMargin(0);
    upperPad[i]->SetLeftMargin(0.15);
    upperPad[i]->SetRightMargin(0.05);

    lowerPad[i] = new TPad(Form("lower_%i", i), Form("lower_%i", i), 0.05, 0.05, 0.95, 0.40, 0, 0, 0);  // x1,y1,x2,y2
    lowerPad[i]->SetTopMargin(0);
    lowerPad[i]->SetBottomMargin(0.15);
    lowerPad[i]->SetLeftMargin(0.15);
    lowerPad[i]->SetRightMargin(0.05);

    // title
    auxCut = Form("%.2f", EdgesKinvar[i]);
    auxCut += " < " + kinvarTitle + " < ";
    auxCut += Form("%.2f", EdgesKinvar[i + 1]);
    auxCut += ", " + targetOption + " data";

    // style: upper pad
    upperFrame[i]->SetTitle("");

    upperFrame[i]->GetYaxis()->SetRangeUser(0, MaxRange);  // set y-axis from before
    upperFrame[i]->GetYaxis()->SetTitle("Counts");
    upperFrame[i]->GetYaxis()->SetTitleSize(0.04);
    upperFrame[i]->GetYaxis()->SetTickSize(0.02);
    upperFrame[i]->GetYaxis()->SetMaxDigits(3);

    upperFrame[i]->GetXaxis()->SetNdivisions(412);

    // style: lower pad
    testHist[i]->SetTitle("");
    testHist[i]->SetFillColor(myViolet);

    testHist[i]->GetYaxis()->SetRangeUser(-4.5, 4.5);
    testHist[i]->GetYaxis()->SetRangeUser(-4.5, 4.5);
    testHist[i]->GetYaxis()->SetTitle("Pull");
    testHist[i]->GetYaxis()->SetTitleOffset(0.6);
    testHist[i]->GetYaxis()->SetTitleSize(0.065);
    testHist[i]->GetYaxis()->SetLabelSize(0.06);
    testHist[i]->GetYaxis()->SetTickSize(0.02);
    testHist[i]->GetYaxis()->SetNdivisions(210);

    testHist[i]->GetXaxis()->SetTitle("Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
    testHist[i]->GetXaxis()->SetTitleOffset(1.2);
    testHist[i]->GetXaxis()->SetTitleSize(0.06);
    testHist[i]->GetXaxis()->SetNdivisions(412);
    testHist[i]->GetXaxis()->SetTickSize(0.05);
    testHist[i]->GetXaxis()->SetLabelSize(0.06);

    /*** UPPER PAD ***/

    can1->cd(counter);

    lowerPad[i]->Draw();
    upperPad[i]->Draw();

    upperPad[i]->cd();
    upperFrame[i]->Draw();

    // title and parameters
    TPaveText *pav = new TPaveText(0.20, 0.55, 0.45, 0.88, "NDC NB");  // no border
    pav->AddText(auxCut);                                              // Title
    ((TText *)pav->GetListOfLines()->Last())->SetTextSize(0.04);
    pav->AddText("");
    pav->AddText(NomegaS[i]);
    pav->AddText(MeanS[i]);
    pav->AddText(SigmaS[i]);
    pav->AddText(NbkgS[i]);
    pav->AddText(PolaS[i]);
    pav->AddText(PolbS[i]);
    pav->SetBorderSize(0);
    pav->SetFillStyle(0);
    pav->SetTextAlign(12);
    pav->Draw();

    // draw lines
    gPad->Update();  // necessary
    // mu - 3sigma
    Double_t x = meanVal[i] - 3 * sigmaVal[i];
    Double_t u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    TLine *line_range;
    line_range = new TLine(u, 0.00, u, 0.25);
    line_range->SetLineColor(myRed);
    line_range->SetLineWidth(2);
    line_range->SetLineStyle(7);
    line_range->SetNDC();
    line_range->Draw();
    // mu + 3sigma
    x = meanVal[i] + 3 * sigmaVal[i];
    u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    line_range = new TLine(u, 0.00, u, 0.25);
    line_range->SetLineColor(myRed);
    line_range->SetLineWidth(2);
    line_range->SetLineStyle(7);
    line_range->SetNDC();
    line_range->Draw();
    // mu
    x = meanVal[i];
    u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    line_range = new TLine(u, 0.00, u, 0.95);
    line_range->SetLineColor(myRed);
    line_range->SetLineWidth(2);
    line_range->SetLineStyle(7);
    line_range->SetNDC();
    line_range->Draw();

    // legend
    TLegend *leg = new TLegend(0.75, 0.75, 0.95, 0.88);  // x1,y1,x2,y2
    leg->AddEntry(upperFrame[i]->findObject("Data"), "Data", "lpe");
    leg->AddEntry(upperFrame[i]->findObject("Model"), "Fit", "l");
    leg->AddEntry(upperFrame[i]->findObject("Bkg"), "Bkg", "l");
    leg->AddEntry(upperFrame[i]->findObject("Signal"), "Signal", "l");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetTextFont(62);
    leg->Draw();

    /*** LOWER PAD ***/

    lowerPad[i]->cd();
    testHist[i]->Draw("BAR MIN0 HIST");

    DrawHorizontalLine(3, myOrange, 7, 2, 1);
    DrawHorizontalLine(0, kBlack, kSolid, 1, 1);
    DrawHorizontalLine(-3, myOrange, 7, 2, 1);

    can1->Update();

    counter++;
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_bkg-fitting";
    system("mkdir -p " + OutputDir);
    can1->Print(OutputDir + "/" + CanvasName + "." + StoreOption);

    // create output file
    TString OutputFileName = OutputDir + "/" + CanvasName + ".root";
    TFile *RootOutputFile = new TFile(OutputFileName, "RECREATE");

    can1->Write();

    // loop over bins
    for (Int_t i = 0; i < Nbins; i++) {
      // save fit result into output file
      FitResult[i]->Write();
    }

    // close output file
    RootOutputFile->Close();

    // print output file path
    std::cout << "The following file has been created: " << OutputFileName << std::endl;
  }
}
