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
const Int_t Nbins = 5;

void Make_BkgFitting(TString targetOption = "C", TString kinvarOption = "Q2", Int_t fixParams = 0, TString StoreOption = "") {
  // 1) Fit eta signal and background
  // 2) Store fit values

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain = GetTwoGammaFinderChain(targetOption, "sim");
  SetAliasesEta(dataChain);

  // about kinvar option
  TString kinvarTitle;
  Double_t EdgesKinvar[Nbins + 1];
  if (kinvarOption == "Q2") {
    kinvarTitle = "Q^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) {
      EdgesKinvar[i] = kEdgesQ2_Eta[i];
    }
  } else if (kinvarOption == "Nu") {
    kinvarTitle = "#nu";
    for (Int_t i = 0; i < Nbins + 1; i++) {
      EdgesKinvar[i] = kEdgesNu_Eta[i];
    }
  } else if (kinvarOption == "nZ") {
    kinvarTitle = "z_{h}";
    for (Int_t i = 0; i < Nbins + 1; i++) {
      EdgesKinvar[i] = kEdgesZ_Eta[i];
    }
  } else if (kinvarOption == "nPt2") {
    kinvarTitle = "p_{T}^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) {
      EdgesKinvar[i] = kEdgesPt2_Eta[i];
    }
  }

  Int_t plotNbins = 60;
  Double_t plotMin = 0.3;
  Double_t plotMax = 0.9;
  TString histProperties = Form("(%i, %f, %f)", plotNbins, plotMin, plotMax);

  TString auxCut;
  TCut CutBin;

  /*** HISTOGRAMS, FUNCTIONS AND PARAMETERS ***/

  TH1D *signalHist[Nbins];
  TH1D *bkgHist[Nbins];
  TH1D *modelHist[Nbins];
  TH1D *dataHist[Nbins];

  TTree *auxTree[Nbins];

  RooPlot *theFrame[Nbins];

  TString Chi2ndf[Nbins];
  TString Netas[Nbins];
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
    RootInputFile = new TFile(gProDir + "/gfx/eta_sim/bkg-fitting_All_" + kinvarOption + ".root");
    // loop over bins
    for (Int_t i = 0; i < Nbins; i++) {
      // get fit function to retrieve parameter's values
      InputFit[i] = (RooFitResult *)RootInputFile->Get(Form("fit-result_%i", i));
      MeanFix[i] = ((RooRealVar *)InputFit[i]->floatParsFinal().find("#mu(#eta)"))->getValV();
      SigmaFix[i] = ((RooRealVar *)InputFit[i]->floatParsFinal().find("#sigma(#eta)"))->getValV();
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

    dataChain->Draw(Form("nM>>data_%i", i) + histProperties, gCutDIS && gCutPhotonsOpAngle && gCutRegion_Eta && CutBin, "goff");
    dataHist[i] = (TH1D *)gROOT->FindObject(Form("data_%i", i));

    // define x variable and ranges
    RooRealVar x("nM", "", plotMin, plotMax);

    // define data set
    RooDataHist data("data", "data", x, dataHist[i]);

    // define signal function
    RooRealVar mean("#mu(#eta)", "mean of gaussian", 0.500, 0.594);       // 0.547
    RooRealVar sigma("#sigma(#eta)", "width of gaussian", 0.034, 0.074);  // 0.054
    RooGaussian signal("signal", "eta signal", x, mean, sigma);
    // fix parameters
    if (fixParams) {
      mean.setVal(MeanFix[i]);
      mean.setConstant(kTRUE);
      sigma.setVal(SigmaFix[i]);
      sigma.setConstant(kTRUE);
    }

    // define bkg function
    RooRealVar b1("b1", "linear term", -100, 100);
    RooRealVar b2("b2", "quadratic term", -10., 0.);
    RooChebychev bkg("bkg", "background", x, RooArgList(b1, b2));

    // define extended composite model
    RooRealVar nsig("N_{#eta}", "number of eta particles", 0., 1000000);
    RooRealVar nbkg("N_{bkg}", "number of background", 0, 1000000);
    RooAddPdf model("model", "(g+pol2)", RooArgList(bkg, signal), RooArgList(nbkg, nsig));

    theFrame[i] = x.frame(Name(Form("upper_f_%i", i)));

    FitResult[i] = model.chi2FitTo(data, Range(plotMin, plotMax), Minos(kTRUE), Strategy(2), Extended(), Save());
    FitResult[i]->SetName(Form("fit-result_%i", i));

    data.plotOn(theFrame[i], Name("Data"), Binning(plotNbins, plotMin, plotMax), LineColor(myBlack), MarkerColor(myBlack));
    model.plotOn(theFrame[i], Name("Model"), LineColor(myBlue));

    model.plotOn(theFrame[i], Name("Bkg"), Components("bkg"), LineColor(kGray + 2), LineStyle(kDashed));
    model.plotOn(theFrame[i], Name("Signal"), Components("signal"), LineColor(myRed));

    modelHist[i] = (TH1D *)model.createHistogram(Form("model_%i", i), x, Binning(plotNbins, plotMin, plotMax), Extended());
    modelHist[i]->Scale((plotMax - plotMin) / (Double_t)plotNbins);  // bin width

    // assign parameters
    Chi2ndf[i] = Form("#chi^{2}/ndf = %.4f", theFrame[i]->chiSquare("Model", "Data", 6));
    Netas[i] = Form("N_{#eta} = %.3f #pm %.3f", nsig.getValV(), nsig.getError());
    MeanS[i] = Form("#mu = %.3f #pm %.6f", mean.getValV(), mean.getError());
    SigmaS[i] = Form("#sigma = %.3f #pm %.6f", sigma.getValV(), sigma.getError());
    NbkgS[i] = Form("N_{bkg} = %.3f #pm %.3f", nbkg.getValV(), nbkg.getError());
    PolaS[i] = Form("b1 = %.3f #pm %.6f", b1.getValV(), b1.getError());
    PolbS[i] = Form("b2 = %.3f #pm %.6f", b2.getValV(), b2.getError());

    // to represent as vertical lines
    meanVal[i] = mean.getValV();
    sigmaVal[i] = sigma.getValV();
  }

  /*** DRAW ***/

  SetMyStyle();

  const Int_t Nx = 3;
  const Int_t Ny = 2;
  TString CanvasName = "bkg-fitting_" + targetOption + "_" + kinvarOption;
  TCanvas *can1 = new TCanvas(CanvasName, CanvasName, 3240, 2160);
  can1->Divide(Nx, Ny, 0.0001, 0.0001);

  Int_t counter = 1;
  // loop over bins
  for (Int_t i = 0; i < Nbins; i++) {
    // title
    auxCut = Form("%.2f", EdgesKinvar[i]);
    auxCut += " < " + kinvarTitle + " < ";
    auxCut += Form("%.2f", EdgesKinvar[i + 1]);
    auxCut += ", " + targetOption + " Sim. Rec.";

    // style
    theFrame[i]->SetTitle("");

    theFrame[i]->GetYaxis()->SetRangeUser(0, 1.5 * dataHist[i]->GetMaximum());
    theFrame[i]->GetYaxis()->SetTitle("Counts");
    theFrame[i]->GetYaxis()->SetTitleSize(0.04);
    theFrame[i]->GetYaxis()->SetMaxDigits(3);

    theFrame[i]->GetXaxis()->SetTitle("Reconstructed Mass m(#gamma#gamma) [GeV]");
    theFrame[i]->GetXaxis()->SetTitleOffset(1.2);
    theFrame[i]->GetXaxis()->SetTitleSize(0.04);
    theFrame[i]->GetXaxis()->SetNdivisions(412);

    /*** UPPER PAD ***/

    can1->cd(counter);

    theFrame[i]->Draw();

    // set title
    TPaveText *pav = new TPaveText(0.175, 0.85, 0.55, 0.9, "NDC NB");  // no border
    pav->AddText(auxCut);
    pav->SetTextSize(0.04);
    pav->SetBorderSize(0);
    pav->SetFillStyle(0);
    pav->SetTextAlign(12);
    pav->Draw();

    // parameters
    TPaveText *pav2 = new TPaveText(0.6, 0.57, 0.9, 0.82, "NDC NB");
    pav2->AddText(Chi2ndf[i]);
    pav2->AddText(Netas[i]);
    pav2->AddText(MeanS[i]);
    pav2->AddText(SigmaS[i]);
    pav2->AddText(NbkgS[i]);
    pav2->AddText(PolaS[i]);
    pav2->AddText(PolbS[i]);
    pav2->SetBorderSize(0);
    pav2->SetFillStyle(0);
    pav2->SetTextAlign(32);
    pav2->Draw();

    // draw lines
    gPad->Update();  // necessary
    // mu - 3sigma
    Double_t x = meanVal[i] - 3 * sigmaVal[i];
    Double_t u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    TLine *line_range;
    line_range = new TLine(u, 0.15, u, 0.35);
    line_range->SetLineColor(myRed);
    line_range->SetLineWidth(2);
    line_range->SetLineStyle(7);
    line_range->SetNDC();
    line_range->Draw();
    // mu + 3sigma
    x = meanVal[i] + 3 * sigmaVal[i];
    u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    line_range = new TLine(u, 0.15, u, 0.35);
    line_range->SetLineColor(myRed);
    line_range->SetLineWidth(2);
    line_range->SetLineStyle(7);
    line_range->SetNDC();
    line_range->Draw();
    // mu
    x = meanVal[i];
    u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    line_range = new TLine(u, 0.15, u, 0.80);
    line_range->SetLineColor(myRed);
    line_range->SetLineWidth(2);
    line_range->SetLineStyle(7);
    line_range->SetNDC();
    line_range->Draw();

    // legend
    TLegend *leg = new TLegend(0.2, 0.67, 0.35, 0.82);  // x1,y1,x2,y2
    leg->AddEntry(theFrame[i]->findObject("Data"), "Data", "lpe");
    leg->AddEntry(theFrame[i]->findObject("Model"), "Fit", "l");
    leg->AddEntry(theFrame[i]->findObject("Bkg"), "Bkg", "l");
    leg->AddEntry(theFrame[i]->findObject("Signal"), "Signal", "l");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetTextFont(62);
    leg->Draw();

    can1->Update();

    counter++;
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_sim";
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
