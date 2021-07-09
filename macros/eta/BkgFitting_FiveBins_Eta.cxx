#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawHorizontalLine.cxx"
#include "DrawVerticalLine.cxx"

using namespace RooFit;

void BkgFitting_FiveBins_Eta(TString targetOption = "C", TString kinvarOption = "Q2", Int_t fixParams = 0) {

  gROOT->SetBatch(kTRUE);  // prevent output printing

  const Int_t Nbins = 5;

  /*** INPUT ***/

  TString dataFile1, dataFile2, dataFile3;
  TCut CutVertex;
  if (targetOption == "D" || targetOption == "All") {
    CutVertex = gCutLiquid;
    dataFile1 = gDataDir_Eta + "/C/*.root";
    dataFile2 = gDataDir_Eta + "/Fe/*.root";
    dataFile3 = gDataDir_Eta + "/Pb/*.root";
    if (targetOption == "All") CutVertex = gCutLiquid || gCutSolid;
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    dataFile1 = gDataDir_Eta + "/" + targetOption + "/*.root";
  }

  TChain *dataTree = new TChain();
  dataTree->Add(dataFile1 + "/mix");
  if (targetOption == "D" || targetOption == "All") {
    dataTree->Add(dataFile2 + "/mix");
    dataTree->Add(dataFile3 + "/mix");
  }

  Int_t plotNbins = 54;
  Double_t plotMin = 0.26;
  Double_t plotMax = 0.8;
  TString histProperties = Form("(%d, %f, %f)", plotNbins, plotMin, plotMax);

  // set output file
  system("mkdir -p " + gProDir + "/macros/eta-bkg-fitting");  // create dir, just in case
  TFile *RootOutputFile = new TFile(gProDir + "/macros/eta-bkg-fitting/eta-bkg-fitting_binned_" + targetOption + "_" + kinvarOption + ".root", "RECREATE");

  TString kinvarTitle;
  Double_t EdgesKinvar[Nbins + 1];
  if (kinvarOption == "Q2") {
    kinvarTitle = "Q^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesQ2_Eta[i];
  } else if (kinvarOption == "Nu") {
    kinvarTitle = "#nu";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesNu_Eta[i];
  } else if (kinvarOption == "eZ") {
    kinvarTitle = "z_{h}";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesZ_Eta[i];
  } else if (kinvarOption == "ePt2") {
    kinvarTitle = "p_{T}^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesPt2_Eta[i];
  }

  TString auxCut;
  TCut CutBin;

  /*** SET CANVAS, PADS AND HISTOGRAMS ***/

  // set canvas
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  TCanvas *can1 = new TCanvas("eta-bkg-fitting_binned_" + targetOption + "_" + kinvarOption, "eta-bkg-fitting_binned_" + targetOption + "_" + kinvarOption, 1920, 626);
  can1->Divide(Nbins, 1, 0.0001, 0.0001);

  // define pads
  TPad *upperPad[Nbins];
  TPad *lowerPad[Nbins];

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

  // fix parameters, based on "All data" results
  /*
  Double_t meanFix[4][4] = {{0.785, 0.784, 0.782, 0.790}, {0.785, 0.784, 0.787, 0.785}, {0.785, 0.783, 0.783, 0.782}, {0.781, 0.783, 0.781, 0.782}};
  Double_t sigmaFix[4][4] = {{0.024, 0.024, 0.018, 0.021}, {0.024, 0.021, 0.022, 0.023}, {0.022, 0.022, 0.020, 0.021}, {0.019, 0.023, 0.021, 0.022}};
  */

  for (Int_t i = 0; i < Nbins; i++) {  // Nx

    // prepare pads
    upperPad[i] = new TPad(Form("upper_%d", i), Form("upper_%d", i), 0.05, 0.40, 0.95, 0.95, 0, 0, 0);  // x1,y1,x2,y2
    upperPad[i]->SetTopMargin(0.05);
    upperPad[i]->SetBottomMargin(0);
    upperPad[i]->SetLeftMargin(0.15);
    upperPad[i]->SetRightMargin(0.05);

    lowerPad[i] = new TPad(Form("lower_%d", i), Form("lower_%d", i), 0.05, 0.05, 0.95, 0.40, 0, 0, 0);  // x1,y1,x2,y2
    lowerPad[i]->SetTopMargin(0);
    lowerPad[i]->SetBottomMargin(0.15);
    lowerPad[i]->SetLeftMargin(0.15);
    lowerPad[i]->SetRightMargin(0.05);

    // prepare histograms
    auxCut = Form("%f", EdgesKinvar[i]);
    auxCut += " < " + kinvarOption + " && " + kinvarOption + " < ";
    auxCut += Form("%f", EdgesKinvar[i + 1]);
    CutBin = auxCut;

    std::cout << auxCut << std::endl;

    dataTree->Draw(Form("eM>>data_%d", i) + histProperties, gCutDIS && CutBin && CutVertex && gCutPhotonsOpAngle_Eta && gCutRegion_Eta, "goff");
    dataHist[i] = (TH1D *)gROOT->FindObject(Form("data_%d", i));

    // prepare tree
    // auxTree[i] = dataTree->CopyTree(gCutDIS && CutBin && CutVertex && gCutPhotonsOpAngle_Eta && gCutRegion_Eta); // MAXIMUM LIKELIHOOD METHOD

    // define x variable and ranges
    RooRealVar x("eM", "", plotMin, plotMax);

    // define data set
    // RooDataSet data("data", "data", auxTree[i], x);  // MAXIMUM LIKELIHOOD METHOD
    RooDataHist data("data", "data", x, dataHist[i]);

    // define signal function
    RooRealVar mean("#mu(#eta)", "mean of gaussian", 0.500, 0.594);       // 0.547
    RooRealVar sigma("#sigma(#eta)", "width of gaussian", 0.034, 0.074);  // 0.054
    RooGaussian signal("signal", "eta signal", x, mean, sigma);

    // fix parameters
    /*
      if (fixParams) {
      mean.setVal(meanFix[i]);
      mean.setConstant(kTRUE);
      sigma.setVal(sigmaFix[i]);
      sigma.setConstant(kTRUE);
      }
    */

    // define bkg function
    RooRealVar b1("b1", "linear term", -100, 100);
    RooRealVar b2("b2", "quadratic term", -10., 10.);
    RooChebychev bkg("bkg", "background", x, RooArgList(b1, b2));

    // define extended composite model
    RooRealVar nsig("N_{#eta}", "number of eta particles", 0., 1000000);
    RooRealVar nbkg("N_{bkg}", "number of background", 0, 1000000);
    RooAddPdf model("model", "(g+pol2)", RooArgList(bkg, signal), RooArgList(nbkg, nsig));

    upperFrame[i] = x.frame(Name(Form("upper_f_%d", i)));
    lowerFrame[i] = x.frame(Name(Form("lower_f_%d", i)));

    RooFitResult *rf = model.fitTo(data, Minos(kTRUE), Extended(), Save());
    rf->SetName(Form("fit-result_%d", i));

    data.plotOn(upperFrame[i], Name("Data"), Binning(plotNbins, plotMin, plotMax));  // first, mandatory
    model.plotOn(upperFrame[i], Name("Model"));

    // error bands
    /*
      model.plotOn(upperFrame[i], VisualizeError(*rf, 2, kFALSE), FillColor(kYellow-9));
      model.plotOn(upperFrame[i], VisualizeError(*rf, 1, kFALSE), FillColor(kGreen-9));
      model.plotOn(upperFrame[i], Name("Model")); // overlay
      data.plotOn(upperFrame[i], Name("Data"), Binning(plotNbins, plotMin, plotMax)); // overlay
    */

    model.plotOn(upperFrame[i], Name("Bkg"), Components("bkg"), LineColor(kGray + 2), LineStyle(kDashed));
    model.plotOn(upperFrame[i], Name("Signal"), Components("signal"), LineColor(kRed));

    modelHist[i] = (TH1D *)model.createHistogram(Form("model_%d", i), x, Binning(plotNbins, plotMin, plotMax), Extended());
    modelHist[i]->Scale((plotMax - plotMin) / (Double_t)plotNbins);  // bin width

    dataErrHist[i] = new TH1D(Form("dataErrHist_%d", i), Form("dataErrHist_%d", i), plotNbins, plotMin, plotMax);
    for (Int_t k = 1; k <= plotNbins; k++) {
      dataErrHist[i]->SetBinContent(k, dataHist[i]->GetBinError(k));
      dataErrHist[i]->SetBinError(k, 0);
    }

    testHist[i] = new TH1D(Form("testHist_%d", i), Form("testHist_%d", i), plotNbins, plotMin, plotMax);
    testHist[i]->Add(dataHist[i], modelHist[i], 1, -1);
    testHist[i]->Divide(dataErrHist[i]);

    // assign parameters
    NomegaS[i] = Form("N_{#eta} = %.3f #pm %.3f", nsig.getValV(), nsig.getError());
    MeanS[i] = Form("#mu = %.3f #pm %.6f", mean.getValV(), mean.getError());
    SigmaS[i] = Form("#sigma = %.3f #pm %.6f", sigma.getValV(), sigma.getError());
    NbkgS[i] = Form("N_{bkg} = %.3f #pm %.3f", nbkg.getValV(), nbkg.getError());
    PolaS[i] = Form("b1 = %.3f #pm %.6f", b1.getValV(), b1.getError());
    PolbS[i] = Form("b2 = %.3f #pm %.6f", b2.getValV(), b2.getError());

    // to represent as vertical lines
    meanVal[i] = mean.getValV();
    sigmaVal[i] = sigma.getValV();

    rf->Write();
  }

  /*** FIX Y-AXIS ***/

  Double_t MaxRange = 0;
  for (Int_t i = 0; i < Nbins; i++) {
    if (dataHist[i]->GetMaximum() > MaxRange) MaxRange = dataHist[i]->GetMaximum();
  }
  MaxRange += MaxRange * 0.15;

  /*** DRAW ***/

  Int_t counter = 1;
  for (Int_t i = 0; i < Nbins; i++) {  // Nx

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

    upperFrame[i]->GetXaxis()->SetNdivisions(412);

    // style: lower pad
    testHist[i]->SetTitle("");
    testHist[i]->SetFillColor(kMagenta);

    testHist[i]->GetYaxis()->SetRangeUser(-4.5, 4.5);
    testHist[i]->GetYaxis()->SetRangeUser(-4.5, 4.5);
    testHist[i]->GetYaxis()->SetTitle("Pull");
    testHist[i]->GetYaxis()->SetTitleOffset(0.6);
    testHist[i]->GetYaxis()->SetTitleSize(0.065);
    testHist[i]->GetYaxis()->SetLabelSize(0.06);
    testHist[i]->GetYaxis()->SetTickSize(0.02);
    testHist[i]->GetYaxis()->SetNdivisions(210);

    testHist[i]->GetXaxis()->SetTitle("Reconstructed Mass m(#gamma#gamma) [GeV]");
    testHist[i]->GetXaxis()->SetTitleOffset(1.2);
    testHist[i]->GetXaxis()->SetTitleSize(0.06);
    testHist[i]->GetXaxis()->SetNdivisions(412);
    testHist[i]->GetXaxis()->SetTickSize(0.05);
    testHist[i]->GetXaxis()->SetLabelSize(0.06);

    /*** DRAW ***/

    /*** UPPER PAD ***/

    can1->cd(counter);

    lowerPad[i]->Draw();
    upperPad[i]->Draw();

    upperPad[i]->cd();
    upperFrame[i]->Draw();

    // title and parameters
    TPaveText *pav = new TPaveText(0.17, 0.57, 0.42, 0.90, "NDC NB");  // no border
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
    line_range->SetLineColor(kOrange + 2);
    line_range->SetLineWidth(2);
    line_range->SetLineStyle(kDashed);
    line_range->SetNDC();
    line_range->Draw();
    // mu + 3sigma
    x = meanVal[i] + 3 * sigmaVal[i];
    u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    line_range = new TLine(u, 0.00, u, 0.25);
    line_range->SetLineColor(kOrange + 2);
    line_range->SetLineWidth(2);
    line_range->SetLineStyle(kDashed);
    line_range->SetNDC();
    line_range->Draw();
    // mu
    x = meanVal[i];
    u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    line_range = new TLine(u, 0.00, u, 0.95);
    line_range->SetLineColor(kRed);
    line_range->SetLineWidth(2);
    line_range->SetLineStyle(kDashed);
    line_range->SetNDC();
    line_range->Draw();

    // legend
    TLegend *leg = new TLegend(0.75, 0.75, 0.95, 0.88);  // x1,y1,x2,y2
    leg->AddEntry(upperFrame[i]->findObject("Data"), "Data", "lp");
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

    DrawHorizontalLine(3, kRed, kDashed, 2, 1);
    DrawHorizontalLine(0, kBlack, kSolid, 1, 1);
    DrawHorizontalLine(-3, kRed, kDashed, 2, 1);

    can1->Update();

    // save into file
    dataHist[i]->Write();

    counter++;
  }

  can1->Write();

  can1->Print("eta-bkg-fitting/eta-bkg-fitting_binned_" + targetOption + "_" + kinvarOption + ".png");

  // close output file
  RootOutputFile->Close();
}
