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
const Int_t NbinsPhiPQ = 5;

void Make_BkgFitting_PhiPQ(TString targetOption = "C", Int_t fixParams = 0, TString StoreOption = "") {
  // 1) Fit eta signal and background on PhiPQ binning
  // 2) Store fit values

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain = GetTwoGammaFinderChain(targetOption);
  SetAliasesEta(dataChain);

  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
  } else if (targetOption == "All") {
    CutVertex = gCutSolid || gCutLiquid;
  } else {  // solid targets
    CutVertex = gCutSolid;
  }

  // about kinvar option
  TString kinvarOption = "nPhiPQ";
  TString kinvarTitle = "#phi_{PQ}";
  Double_t EdgesPhiPQ[NbinsPhiPQ + 1] = {-180, -108, -36, 36, 108, 180};

  Int_t plotNbins = 54;
  Double_t plotMin = 0.26;
  Double_t plotMax = 0.8;
  TString histProperties = Form("(%i, %f, %f)", plotNbins, plotMin, plotMax);

  TString auxCut;
  TCut CutBin;

  /*** HISTOGRAMS, FUNCTIONS AND PARAMETERS ***/

  TH1D *signalHist[NbinsPhiPQ];
  TH1D *bkgHist[NbinsPhiPQ];
  TH1D *modelHist[NbinsPhiPQ];
  TH1D *dataHist[NbinsPhiPQ];

  TTree *auxTree[NbinsPhiPQ];

  RooPlot *theFrame[NbinsPhiPQ];

  TString Chi2ndf[NbinsPhiPQ];
  TString Netas[NbinsPhiPQ];
  TString MeanS[NbinsPhiPQ];
  TString SigmaS[NbinsPhiPQ];
  TString NbkgS[NbinsPhiPQ];
  TString PolaS[NbinsPhiPQ];
  TString PolbS[NbinsPhiPQ];

  Double_t meanVal[NbinsPhiPQ];
  Double_t sigmaVal[NbinsPhiPQ];

  RooFitResult *FitResult[NbinsPhiPQ];

  // in the case of fix params
  TFile *RootInputFile;
  RooFitResult *InputFit[NbinsPhiPQ];
  Double_t MeanFix[NbinsPhiPQ];
  Double_t SigmaFix[NbinsPhiPQ];
  if (fixParams) {
    // read the bkg-subtracted output file when running on "All" data
    RootInputFile = new TFile(gProDir + "/gfx/rad-corr_eta/bkg-fitting_All_" + kinvarOption + "_data.root");
    // loop over bins
    for (Int_t i = 0; i < NbinsPhiPQ; i++) {
      // get fit function to retrieve parameter's values
      InputFit[i] = (RooFitResult *)RootInputFile->Get(Form("fit-result_%i", i));
      MeanFix[i] = ((RooRealVar *)InputFit[i]->floatParsFinal().find("#mu(#eta)"))->getValV();
      SigmaFix[i] = ((RooRealVar *)InputFit[i]->floatParsFinal().find("#sigma(#eta)"))->getValV();
    }
  }

  // loop over bins
  for (Int_t i = 0; i < NbinsPhiPQ; i++) {
    // prepare histograms
    auxCut = Form("%f", EdgesPhiPQ[i]);
    auxCut += " < " + kinvarOption + " && " + kinvarOption + " < ";
    auxCut += Form("%f", EdgesPhiPQ[i + 1]);
    CutBin = auxCut;

    std::cout << auxCut << std::endl;

    dataChain->Draw(Form("nM>>data_%i", i) + histProperties, gCutDIS && CutVertex && gCutPhotonsOpAngle && gCutRegion_Eta && CutBin,
                    "goff");
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

    FitResult[i] = model.fitTo(data, Minos(kTRUE), Extended(), Save());
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

  TString CanvasName = "bkg-fitting_" + targetOption + "_" + kinvarOption + "_data";
  TCanvas *can1 = new TCanvas(CanvasName, CanvasName, 3240, 2160);
  can1->Divide(Nx, Ny, 0.0001, 0.0001);

  Int_t counter = 1;
  // loop over bins
  for (Int_t i = 0; i < NbinsPhiPQ; i++) {
    // title
    auxCut = Form("%.0f", EdgesPhiPQ[i]);
    auxCut += " < " + kinvarTitle + " < ";
    auxCut += Form("%.0f", EdgesPhiPQ[i + 1]);
    auxCut += ", " + targetOption + " data";

    // style
    theFrame[i]->SetTitle("");

    theFrame[i]->GetYaxis()->SetRangeUser(0, 1.2 * dataHist[i]->GetMaximum());
    theFrame[i]->GetYaxis()->SetTitle("Counts");
    theFrame[i]->GetYaxis()->SetTitleSize(0.04);
    theFrame[i]->GetYaxis()->SetTickSize(0.02);
    theFrame[i]->GetYaxis()->SetMaxDigits(3);

    theFrame[i]->GetXaxis()->SetTitle("Reconstructed Mass m(#gamma#gamma) [GeV]");
    theFrame[i]->GetXaxis()->SetTitleOffset(1.2);
    theFrame[i]->GetXaxis()->SetTitleSize(0.04);
    theFrame[i]->GetXaxis()->SetTickSize(0.05);
    // theFrame[i]->GetXaxis()->SetLabelSize(0.06);

    theFrame[i]->GetXaxis()->SetNdivisions(412);

    /*** UPPER PAD ***/

    can1->cd(counter);

    theFrame[i]->Draw();

    // title and parameters
    TPaveText *pav = new TPaveText(0.17, 0.57, 0.42, 0.90, "NDC NB");  // no border
    pav->AddText(auxCut);                                              // Title
    ((TText *)pav->GetListOfLines()->Last())->SetTextSize(0.04);
    pav->AddText("");
    pav->AddText(Chi2ndf[i]);
    pav->AddText(Netas[i]);
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
    line_range = new TLine(u, 0.15, u, 0.95);
    line_range->SetLineColor(myRed);
    line_range->SetLineWidth(2);
    line_range->SetLineStyle(7);
    line_range->SetNDC();
    line_range->Draw();

    // legend
    TLegend *leg = new TLegend(0.75, 0.75, 0.95, 0.88);  // x1,y1,x2,y2
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
    TString OutputDir = gProDir + "/gfx/rad-corr_eta";
    system("mkdir -p " + OutputDir);
    can1->Print(OutputDir + "/" + CanvasName + "." + StoreOption);

    // create output file
    TString OutputFileName = OutputDir + "/" + CanvasName + ".root";
    TFile *RootOutputFile = new TFile(OutputFileName, "RECREATE");

    can1->Write();

    // loop over bins
    for (Int_t i = 0; i < NbinsPhiPQ; i++) {
      // save fit result into output file
      FitResult[i]->Write();
    }

    // close output file
    RootOutputFile->Close();

    // print output file path
    std::cout << "The following file has been created: " << OutputFileName << std::endl;
  }
}
