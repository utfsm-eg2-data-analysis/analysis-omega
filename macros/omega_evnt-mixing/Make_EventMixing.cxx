#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Nkinvars = 4;
const Int_t Nbins = 4;

void Make_EventMixing(TString targetOption = "C", TString kinvarOption = "Q2", Int_t fixParams = 0, TString StoreOption = "") {
  // 1) Normalize event-mixing bkg to match data
  // 2) Subtract event-mixing bkg to data
  // 3) Fit extracted signal
  // 4) Store fit values

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain = GetThreePionFinderChain(targetOption);
  SetAliases(dataChain);

  TChain *bkgChain = GetEventMixingChain(targetOption);
  SetAliases(bkgChain);

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
  Int_t BinsForNormalization[4];
  BinsForNormalization[0] = 1;
  BinsForNormalization[1] = 5;
  BinsForNormalization[2] = plotNbins - 4;
  BinsForNormalization[3] = plotNbins;
  TString histProperties = Form("(%i, %.3f, %.3f)", plotNbins, plotMin, plotMax);

  TString auxCut;
  TCut CutBin;

  /*** HISTOGRAMS, FUNCTIONS AND PARAMETERS ***/

  TH1D *dataMassive[Nbins];
  TH1D *bkgMassive[Nbins];
  TH1D *subMassive[Nbins];

  Double_t dataNorm, bkgNorm;

  TF1 *Model[Nbins];
  TF1 *Signal[Nbins];
  TF1 *ResidualBkg[Nbins];

  TFitResultPtr FitResult[Nbins];

  // in the case of fix params
  TFile *RootInputFile;
  TF1 *Fit[Nbins];
  Double_t MeanFix[Nbins];
  Double_t SigmaFix[Nbins];
  if (fixParams) {
    // read the bkg-subtracted output file when running on "All" data
    RootInputFile = new TFile(gProDir + "/gfx/omega_evnt-mixing/evnt-mixing_All_" + kinvarOption + ".root");
    // loop over bins
    for (Int_t i = 0; i < Nbins; i++) {
      // get fit function to retrieve parameter's values
      Fit[i] = (TF1 *)RootInputFile->Get(Form("model_%i", i));
      MeanFix[i] = Fit[i]->GetParameter(1);
      SigmaFix[i] = Fit[i]->GetParameter(2);
    }
  }

  // loop over bins
  for (Int_t i = 0; i < Nbins; i++) {
    auxCut = Form("%f", EdgesKinvar[i]);
    auxCut += " < " + kinvarOption + " && " + kinvarOption + " < ";
    auxCut += Form("%f", EdgesKinvar[i + 1]);
    CutBin = auxCut;

    std::cout << auxCut << std::endl;

    // prepare data
    dataChain->Draw(Form("wD>>data_%i", i) + histProperties, gCutDIS && CutVertex && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin,
                    "goff");
    dataMassive[i] = (TH1D *)gROOT->FindObject(Form("data_%i", i));

    dataMassive[i]->SetMarkerColor(myBlack);
    dataMassive[i]->SetMarkerStyle(8);
    dataMassive[i]->SetLineColor(myBlack);
    dataMassive[i]->SetLineWidth(2);
    dataMassive[i]->SetFillStyle(0);

    // prepare bkg
    bkgChain->Draw(Form("wD>>bkg_%i", i) + histProperties, gCutDIS && CutVertex && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin,
                   "goff");
    bkgMassive[i] = (TH1D *)gROOT->FindObject(Form("bkg_%i", i));

    bkgMassive[i]->SetMarkerColor(myRed);
    bkgMassive[i]->SetMarkerStyle(8);
    bkgMassive[i]->SetLineColor(myRed);
    bkgMassive[i]->SetLineWidth(2);
    bkgMassive[i]->SetFillStyle(0);

    /*** NORMALIZATION ***/

    dataNorm = dataMassive[i]->Integral(BinsForNormalization[0], BinsForNormalization[1]) +
               dataMassive[i]->Integral(BinsForNormalization[2], BinsForNormalization[3]);
    std::cout << "dataNorm = " << dataNorm << std::endl;

    bkgNorm = bkgMassive[i]->Integral(BinsForNormalization[0], BinsForNormalization[1]) +
              bkgMassive[i]->Integral(BinsForNormalization[2], BinsForNormalization[3]);
    std::cout << "bkgNorm  = " << bkgNorm << std::endl;
    bkgMassive[i]->Scale(dataNorm / bkgNorm);

    /*** BKG SUBTRACTION ***/

    subMassive[i] = new TH1D(Form("sub_%i", i), "", plotNbins, plotMin, plotMax);
    subMassive[i]->Add(dataMassive[i], bkgMassive[i], 1, -1);

    subMassive[i]->SetMarkerColor(myOrange);
    subMassive[i]->SetMarkerStyle(8);
    subMassive[i]->SetLineColor(myOrange);
    subMassive[i]->SetLineWidth(2);
    subMassive[i]->SetFillStyle(0);

    /*** FIT ***/

    // define parameter's limits and initial guess values
    Double_t MeanIGV = 0.782;
    Double_t MeanLimit = 0.08;
    Double_t SigmaIGV = 0.024;
    Double_t SigmaLimit = 0.011;
    Model[i] = new TF1(Form("model_%i", i), "gaus(0) + pol1(3)", plotMin, plotMax);
    Model[i]->SetParameter(1, MeanIGV);
    Model[i]->SetParameter(2, SigmaIGV);
    Model[i]->SetParLimits(0, 0., 100000);  // force positive values
    Model[i]->SetParLimits(1, MeanIGV - MeanLimit, MeanIGV + MeanLimit);
    Model[i]->SetParLimits(2, SigmaIGV - SigmaLimit, SigmaIGV + SigmaLimit);

    if (fixParams) {
      Model[i]->FixParameter(1, MeanFix[i]);
      Model[i]->FixParameter(2, SigmaFix[i]);
    }

    FitResult[i] = subMassive[i]->Fit(Form("model_%i", i), "BEMSVN");

    Signal[i] = new TF1(Form("signal_%i", i), "gaus", plotMin, plotMax);
    Signal[i]->SetParameter(0, Model[i]->GetParameter(0));
    Signal[i]->SetParameter(1, Model[i]->GetParameter(1));
    Signal[i]->SetParameter(2, Model[i]->GetParameter(2));
    ResidualBkg[i] = new TF1(Form("res-bkg_%i", i), "pol1", plotMin, plotMax);
    ResidualBkg[i]->SetParameter(0, Model[i]->GetParameter(3));
    ResidualBkg[i]->SetParameter(1, Model[i]->GetParameter(4));

    Signal[i]->SetLineWidth(3);
    Signal[i]->SetLineColor(myViolet);

    ResidualBkg[i]->SetLineWidth(3);
    ResidualBkg[i]->SetLineColor(kGray + 2);
    ResidualBkg[i]->SetLineStyle(kDashed);
  }

  /*** FIX Y-AXIS ***/

  Double_t MaxRangeData = 0;
  Double_t MaxRangeSub = 0;
  // loop over bins
  for (Int_t i = 0; i < Nbins; i++) {
    if (dataMassive[i]->GetMaximum() > MaxRangeData) {
      MaxRangeData = dataMassive[i]->GetMaximum();
    }
    if (subMassive[i]->GetMaximum() > MaxRangeSub) {
      MaxRangeSub = subMassive[i]->GetMaximum();
    }
  }

  /*** DRAW ***/

  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  const Int_t Nx = 2;
  const Int_t Ny = 2;

  TString CanvasName = "evnt-mixing_" + targetOption + "_" + kinvarOption;
  TCanvas *can1 = new TCanvas(CanvasName, CanvasName, 1920, 2880);
  can1->Divide(Nx, Ny, 0.0001, 0.0001);

  // define pads
  TPad *upperPad[Nbins];
  TPad *lowerPad[Nbins];

  Int_t counter = 1;
  // loop over bins
  for (Int_t i = 0; i < Nbins; i++) {
    // prepare pads
    upperPad[i] = new TPad(Form("upper_%i", i), Form("upper_%i", i), 0.05, 0.50, 0.95, 0.95, 0, 0, 0);  // x1,y1,x2,y2
    upperPad[i]->SetTopMargin(0.05);
    upperPad[i]->SetBottomMargin(0);
    upperPad[i]->SetLeftMargin(0.15);
    upperPad[i]->SetRightMargin(0.05);

    lowerPad[i] = new TPad(Form("lower_%i", i), Form("lower_%i", i), 0.05, 0.05, 0.95, 0.50, 0, 0, 0);  // x1,y1,x2,y2
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
    dataMassive[i]->SetTitle("");

    dataMassive[i]->GetYaxis()->SetRangeUser(0, 1.2 * MaxRangeData);
    dataMassive[i]->GetYaxis()->SetTitle("Counts");
    dataMassive[i]->GetYaxis()->SetTitleOffset(1.15);
    dataMassive[i]->GetYaxis()->SetTitleSize(0.05);
    dataMassive[i]->GetYaxis()->SetTickSize(0.02);

    dataMassive[i]->GetXaxis()->SetNdivisions(412);

    // style: lower pad
    subMassive[i]->SetTitle("");

    subMassive[i]->GetYaxis()->SetRangeUser(-0.5 * MaxRangeSub, 1.5 * MaxRangeSub);
    subMassive[i]->GetYaxis()->SetTitle("Bkg. Subtracted Counts");
    subMassive[i]->GetYaxis()->SetTitleOffset(1.15);
    subMassive[i]->GetYaxis()->SetTitleSize(0.05);
    subMassive[i]->GetYaxis()->SetTickSize(0.02);

    subMassive[i]->GetXaxis()->SetTitle("Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
    subMassive[i]->GetXaxis()->SetTitleOffset(1.2);
    subMassive[i]->GetXaxis()->SetTitleSize(0.045);
    subMassive[i]->GetXaxis()->SetTickSize(0.05);
    subMassive[i]->GetXaxis()->SetNdivisions(412);

    /*** UPPER PAD ***/

    can1->cd(counter);

    lowerPad[i]->Draw();
    upperPad[i]->Draw();

    upperPad[i]->cd();

    dataMassive[i]->Draw("E");
    bkgMassive[i]->Draw("E SAME");

    // title
    TPaveText *pav = new TPaveText(0.2, 0.82, 0.45, 0.92, "NDC NB");  // no border
    pav->AddText(auxCut);
    ((TText *)pav->GetListOfLines()->Last())->SetTextSize(0.04);
    pav->SetBorderSize(0);
    pav->SetFillStyle(0);
    pav->SetTextAlign(12);
    pav->Draw();

    // legend
    TLegend *leg = new TLegend(0.2, 0.68, 0.5, 0.82);  // x1,y1,x2,y2
    leg->AddEntry(dataMassive[i], "Data", "lp");
    leg->AddEntry(bkgMassive[i], "Mixed Event Bkg", "lp");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetTextFont(62);
    leg->Draw();

    /*** LOWER PAD ***/

    lowerPad[i]->cd();

    subMassive[i]->Draw("E");
    Signal[i]->Draw("SAME");
    ResidualBkg[i]->Draw("SAME");

    DrawHorizontalLine(0, kBlack, kSolid, 1, 1);

    // title
    auxCut = Form("%.2f", EdgesKinvar[i]);
    auxCut += " < " + kinvarTitle + " < ";
    auxCut += Form("%.2f", EdgesKinvar[i + 1]);
    auxCut += ", " + targetOption + " data";
    TPaveText *pav2 = new TPaveText(0.20, 0.86, 0.45, 0.96, "NDC NB");  // no border
    pav2->AddText(auxCut);
    ((TText *)pav2->GetListOfLines()->Last())->SetTextSize(0.04);
    pav2->SetBorderSize(0);
    pav2->SetFillStyle(0);
    pav2->SetTextAlign(12);
    pav2->Draw();

    // legend
    TLegend *leg2 = new TLegend(0.2, 0.64, 0.44, 0.86);  // x1,y1,x2,y2
    leg2->AddEntry(subMassive[i], "Data - Bkg", "lp");
    leg2->AddEntry(Signal[i], "Signal", "l");
    leg2->AddEntry(ResidualBkg[i], "Residual Bkg", "l");
    leg2->SetBorderSize(0);
    leg2->SetFillStyle(0);
    leg2->SetTextFont(62);
    leg2->Draw();

    // parameters
    TPaveText *pav3 = new TPaveText(0.68, 0.63, 0.93, 0.93, "NDC NB");  // no border
    pav3->AddText(Form("#chi^{2}/ndf = %.4f", Model[i]->GetChisquare() / (Double_t)Model[i]->GetNDF()));
    pav3->AddText(Form("A = %.3f #pm %.3f", Model[i]->GetParameter(0), Model[i]->GetParError(0)));
    pav3->AddText(Form("#mu = %.3f #pm %.6f", Model[i]->GetParameter(1), Model[i]->GetParError(1)));
    pav3->AddText(Form("#sigma = %.3f #pm %.6f", Model[i]->GetParameter(2), Model[i]->GetParError(2)));
    pav3->SetBorderSize(0);
    pav3->SetTextAlign(12);
    pav3->SetFillStyle(0);
    pav3->Draw();

    // draw lines
    gPad->Update();  // necessary
    // mu - 3sigma
    Double_t x = Model[i]->GetParameter(1) - 3 * Model[i]->GetParameter(2);
    Double_t u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    TLine *line_range;
    line_range = new TLine(u, 0.15, u, 0.55);
    line_range->SetLineColor(myViolet);
    line_range->SetLineStyle(7);
    line_range->SetLineWidth(3);
    line_range->SetNDC();
    line_range->Draw();
    // mu + 3sigma
    x = Model[i]->GetParameter(1) + 3 * Model[i]->GetParameter(2);
    u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    line_range = new TLine(u, 0.15, u, 0.55);
    line_range->SetLineColor(myViolet);
    line_range->SetLineStyle(7);
    line_range->SetLineWidth(3);
    line_range->SetNDC();
    line_range->Draw();

    can1->Update();

    counter++;
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_evnt-mixing";
    system("mkdir -p " + OutputDir);
    can1->Print(OutputDir + "/" + CanvasName + "." + StoreOption);

    // create output file
    TString OutputFileName = OutputDir + "/" + CanvasName + ".root";
    TFile *RootOutputFile = new TFile(OutputFileName, "RECREATE");

    // loop over bins
    for (Int_t i = 0; i < Nbins; i++) {
      // save into output file
      subMassive[i]->Write();
      Model[i]->Write();
      FitResult[i]->Write();
    }

    // close output file
    RootOutputFile->Close();

    // print output file path
    std::cout << "The following file has been created: " << OutputFileName << std::endl;
  }
}
