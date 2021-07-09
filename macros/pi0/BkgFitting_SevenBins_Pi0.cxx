#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "DrawHorizontalLine.cxx"
#include "DrawVerticalLine.cxx"

using namespace RooFit;

void BkgFitting_SevenBins_Pi0(TString targetOption = "C") {
  // Plot and fit invariant mass of pi0->2gamma candidates with a g+pol2 model
  // for each bin in Pt2, according to O. Soto thesis

  gROOT->SetBatch(kTRUE);  // prevent output printing

  TString kinvarOption = "ePt2";
  const Int_t Nbins = 7;

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

  Int_t plotNbins = 40;
  Double_t plotMin = 0.05;
  Double_t plotMax = 0.25;
  TString histProperties = Form("(%d, %f, %f)", plotNbins, plotMin, plotMax);

  // set output file
  TFile *RootOutputFile = new TFile(gProDir + "/macros/pi0/pi0-bkg-fitting_binned_" + targetOption + "_" + kinvarOption + ".root", "RECREATE");

  TString kinvarTitle;
  Double_t EdgesKinvar[Nbins + 1];
  if (kinvarOption == "ePt2") {
    kinvarTitle = "p_{T}^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesPt2_Pi0[i];
  }

  TString auxCut;
  TCut CutBin;

  /*** SET CANVAS, PADS AND HISTOGRAMS ***/

  // set canvas
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);

  TCanvas *can1 = new TCanvas("pi0-bkg-fitting_binned_" + targetOption + "_" + kinvarOption, "pi0-bkg-fitting_binned_" + targetOption + "_" + kinvarOption, 640 * Nbins, 640);
  can1->Divide(Nbins, 1, 0.0001, 0.0001);

  TH1D *signalHist[Nbins];
  TH1D *bkgHist[Nbins];
  TH1D *modelHist[Nbins];
  TH1D *dataHist[Nbins];

  TTree *auxTree[Nbins];

  RooPlot *upperFrame[Nbins];

  TString ChiSquare[Nbins];
  TString NomegaS[Nbins];
  TString MeanS[Nbins];
  TString SigmaS[Nbins];
  TString NbkgS[Nbins];
  TString PolaS[Nbins];
  TString PolbS[Nbins];

  Double_t meanVal[Nbins];
  Double_t sigmaVal[Nbins];

  for (Int_t i = 0; i < Nbins; i++) {  // Nx

    // prepare histograms
    auxCut = Form("%f", EdgesKinvar[i]);
    auxCut += " < " + kinvarOption + " && " + kinvarOption + " < ";
    auxCut += Form("%f", EdgesKinvar[i + 1]);
    CutBin = auxCut;

    std::cout << auxCut << std::endl;

    dataTree->Draw(Form("eM>>data_%d", i) + histProperties, gCutDIS && CutBin && CutVertex && gCutPhotonsOpAngle_Eta && gCutRegion_Eta, "goff");
    dataHist[i] = (TH1D *)gROOT->FindObject(Form("data_%d", i));

    // define x variable and ranges
    RooRealVar x("eM", "", plotMin, plotMax);

    // define data set
    RooDataHist data("data", "data", x, dataHist[i]);

    // define signal function
    RooRealVar mean("#mu(#pi^{0})", "mean of gaussian", 0.130, 0.147);       // 0.135
    RooRealVar sigma("#sigma(#pi^{0})", "width of gaussian", 0.010, 0.034);  // 0.017
    RooGaussian signal("signal", "pi0 signal", x, mean, sigma);

    // define bkg function
    RooRealVar b1("b1", "linear term", -100, 100);
    RooRealVar b2("b2", "quadratic term", -10., 10.);
    RooChebychev bkg("bkg", "background", x, RooArgList(b1, b2));

    // define extended composite model
    RooRealVar nsig("N_{#pi^{0}}", "number of pi0 particles", 0., 1000000);
    RooRealVar nbkg("N_{bkg}", "number of background", 0, 1000000);
    RooAddPdf model("model", "(g+pol2)", RooArgList(bkg, signal), RooArgList(nbkg, nsig));

    upperFrame[i] = x.frame(Name(Form("upper_f_%d", i)));

    RooFitResult *rf = model.fitTo(data, Minos(kTRUE), Extended(), Save());
    rf->SetName(Form("fit-result_%d", i));

    data.plotOn(upperFrame[i], Name("Data"), Binning(plotNbins, plotMin, plotMax));  // first, mandatory
    model.plotOn(upperFrame[i], Name("Model"));

    model.plotOn(upperFrame[i], Name("Bkg"), Components("bkg"), LineColor(kGray + 2), LineStyle(kDashed));
    model.plotOn(upperFrame[i], Name("Signal"), Components("signal"), LineColor(kRed));

    modelHist[i] = (TH1D *)model.createHistogram(Form("model_%d", i), x, Binning(plotNbins, plotMin, plotMax), Extended());
    modelHist[i]->Scale((plotMax - plotMin) / (Double_t)plotNbins);  // bin width

    // assign parameters
    ChiSquare[i] = Form("#chi^{2}/ndf = %.5f", upperFrame[i]->chiSquare("Model", "Data"));
    NomegaS[i] = Form("N_{#pi^{0}} = %.3f #pm %.3f", nsig.getValV(), nsig.getError());
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
    upperFrame[i]->GetXaxis()->SetTitle("Reconstructed Mass m(#gamma#gamma) [GeV]");

    upperFrame[i]->GetXaxis()->SetNdivisions(412);

    /*** DRAW ***/

    can1->cd(counter);

    upperFrame[i]->Draw();

    // title and parameters
    TPaveText *pav = new TPaveText(0.17, 0.57, 0.42, 0.90, "NDC NB");  // no border
    pav->AddText(auxCut);                                              // Title
    ((TText *)pav->GetListOfLines()->Last())->SetTextSize(0.04);
    pav->AddText("");
    pav->AddText(ChiSquare[i]);
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
    line_range = new TLine(u, 0.15, u, 0.40);
    line_range->SetLineColor(kOrange + 2);
    line_range->SetLineWidth(2);
    line_range->SetLineStyle(kDashed);
    line_range->SetNDC();
    line_range->Draw();
    // mu + 3sigma
    x = meanVal[i] + 3 * sigmaVal[i];
    u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    line_range = new TLine(u, 0.15, u, 0.40);
    line_range->SetLineColor(kOrange + 2);
    line_range->SetLineWidth(2);
    line_range->SetLineStyle(kDashed);
    line_range->SetNDC();
    line_range->Draw();
    // mu
    x = meanVal[i];
    u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    line_range = new TLine(u, 0.15, u, 0.95);
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

    // save into file
    dataHist[i]->Write();

    counter++;
  }

  can1->Write();

  can1->Print(gProDir + "/macros/pi0/pi0-bkg-fitting_binned_" + targetOption + "_" + kinvarOption + ".png");

  // debug
  /*
    for (Int_t ff = 0; ff < Nbins; ff++) {
      std::cout << "Chi2/ndf of bin " << ff << ": " << upperFrame[ff]->chiSquare("Model", "Data") << std::endl;
    }
  */

  // close output file
  RootOutputFile->Close();
}
