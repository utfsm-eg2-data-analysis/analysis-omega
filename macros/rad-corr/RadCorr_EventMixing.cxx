#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawHorizontalLine.cxx"
#include "DrawVerticalLine.cxx"

void RadCorr_EventMixing(TString targetOption = "D", TString kinvarOption = "Q2", Int_t WithRadCorr = 1, Int_t fixParams = 1) {
  // Plot all bins, comparing event-mixing from data with data.

  gROOT->SetBatch(kTRUE);  // prevent output printing
  const Int_t Nbins = 4;

  /*** FROM HAPRAD RESULTS ***/

  const Int_t NbinsPhiPQ = 36;
  Double_t RCFactor_D[NbinsPhiPQ] = {1.00401,  1.00062,  0.996976, 0.993575, 0.989287, 0.984232, 0.981843, 0.977888, 0.976074, 0.974846, 0.973701, 0.972742,
                                     0.973556, 0.977196, 0.977136, 0.98105,  0.980079, 0.984137, 0.984373, 0.982458, 0.980957, 0.97604,  0.975704, 0.97354,
                                     0.974441, 0.973517, 0.974098, 0.975463, 0.979719, 0.982163, 0.985791, 0.989851, 0.993393, 0.998216, 1.00104,  1.00361};

  Double_t RCFactor_C[NbinsPhiPQ] = {1.00611,  0.999387, 0.999109, 0.996387, 0.990108, 0.990388, 0.980931, 0.979933, 0.976201, 0.976228, 0.973176, 0.972362,
                                     0.972618, 0.976226, 0.974633, 0.974744, 0.976079, 0.981607, 0.978517, 0.974801, 0.977436, 0.975629, 0.979132, 0.97782,
                                     0.971385, 0.972906, 0.974918, 0.973108, 0.979427, 0.984098, 0.985218, 0.985892, 0.994796, 0.999506, 1.00284,  1.00545};

  Double_t RCFactor_Fe[NbinsPhiPQ] = {1.0043,   1.00541,  1.00136,  0.995856, 0.992444, 0.98753,  0.98448,  0.982106, 0.97482,  0.976609, 0.972847, 0.973629,
                                      0.972701, 0.974574, 0.972677, 0.978659, 0.979499, 0.982251, 0.982291, 0.982521, 0.973791, 0.977526, 0.972785, 0.968137,
                                      0.974027, 0.971485, 0.975673, 0.977838, 0.980067, 0.981329, 0.985666, 0.992388, 0.99659,  0.998891, 1.00455,  1.00416};

  Double_t RCFactor_Pb[NbinsPhiPQ] = {1.00429,  1.0047,   1.00255,  0.994605, 0.991352, 0.986609, 0.983351, 0.981668, 0.980889, 0.972566, 0.972924, 0.967351,
                                      0.97149,  0.971786, 0.969123, 0.976616, 0.972771, 0.971643, 0.978628, 0.97994,  0.980028, 0.981809, 0.96969,  0.969394,
                                      0.974774, 0.971849, 0.976992, 0.978449, 0.975794, 0.978614, 0.991422, 0.995656, 0.997792, 1.00198,  1.00308,  1.00606};

  TString StringRadCorr = "";
  if (WithRadCorr) StringRadCorr = "_rc";

  /*** INPUT ***/

  Double_t RCFactor_Target[NbinsPhiPQ];  // according to TargetOption
  if (targetOption == "D") {
    for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) RCFactor_Target[pp] = RCFactor_D[pp];
  } else if (targetOption == "C") {
    for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) RCFactor_Target[pp] = RCFactor_C[pp];
  } else if (targetOption == "Fe") {
    for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) RCFactor_Target[pp] = RCFactor_Fe[pp];
  } else if (targetOption == "Pb") {
    for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) RCFactor_Target[pp] = RCFactor_Pb[pp];
  }

  /*** INPUT ***/

  TString dataFile1, dataFile2, dataFile3;
  TString bkgFile1, bkgFile2, bkgFile3;
  TString BkgDir = gWorkDir + "/out/EventMixing/data";
  TCut CutVertex;
  if (targetOption == "D" || targetOption == "All") {
    CutVertex = gCutLiquid;
    dataFile1 = gDataDir + "/C/*.root";
    dataFile2 = gDataDir + "/Fe/*.root";
    dataFile3 = gDataDir + "/Pb/*.root";
    bkgFile1 = BkgDir + "/C/*.root";
    bkgFile2 = BkgDir + "/Fe/*.root";
    bkgFile3 = BkgDir + "/Pb/*.root";
    if (targetOption == "All") CutVertex = gCutSolid || gCutLiquid;
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    dataFile1 = gDataDir + "/" + targetOption + "/*.root";
    bkgFile1 = BkgDir + "/" + targetOption + "/*.root";
  }

  TChain *dataTree = new TChain();
  dataTree->Add(dataFile1 + "/mix");
  if (targetOption == "D" || targetOption == "All") {
    dataTree->Add(dataFile2 + "/mix");
    dataTree->Add(dataFile3 + "/mix");
  }

  TChain *bkgTree = new TChain();
  bkgTree->Add(bkgFile1 + "/mix");
  if (targetOption == "D" || targetOption == "All") {
    bkgTree->Add(bkgFile2 + "/mix");
    bkgTree->Add(bkgFile3 + "/mix");
  }

  // necessary for gCutKaons
  SetAliases(dataTree);
  SetAliases(bkgTree);

  // about kinvar option
  TString kinvarTitle;
  Double_t EdgesKinvar[Nbins + 1];
  if (kinvarOption == "Q2") {
    kinvarTitle = "Q^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesQ2[i];
  } else if (kinvarOption == "Nu") {
    kinvarTitle = "#nu";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesNu[i];
  } else if (kinvarOption == "wZ") {
    kinvarTitle = "z_{h}";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesZ[i];
  } else if (kinvarOption == "wPt2") {
    kinvarTitle = "p_{T}^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesPt2[i];
  }

  // to choose between eta and omega
  Int_t plotNbins = 24;
  Double_t plotMin = 0.66;
  Double_t plotMax = 0.90;
  Int_t BinsForNormalization[4];
  BinsForNormalization[0] = 1;
  BinsForNormalization[1] = 5;
  BinsForNormalization[2] = plotNbins - 4;
  BinsForNormalization[3] = plotNbins;
  TString histProperties = Form("(%d, %.3f, %.3f)", plotNbins, plotMin, plotMax);

  /*** SET OUTPUT FILE ***/

  TFile *RootOutputFile = new TFile(gProDir + "/macros/rad-corr/evnt-mixing_" + targetOption + "_" + kinvarOption + StringRadCorr + ".root", "RECREATE");

  TString auxCut;
  TCut CutBin;

  /*** SET HISTOGRAMS ***/

  const Int_t Nx = Nbins;
  const Int_t Ny = 1;

  TH1D *dataMassive[Nbins];
  TH1D *bkgMassive[Nbins];
  TH1D *subMassive[Nbins];

  // radiative corrections
  TH1D *data_partial[Nbins][NbinsPhiPQ];
  TH1D *data_factor[Nbins][NbinsPhiPQ];
  TH1D *data_partial_corr[Nbins][NbinsPhiPQ];

  TH1D *bkg_partial[Nbins][NbinsPhiPQ];
  TH1D *bkg_factor[Nbins][NbinsPhiPQ];
  TH1D *bkg_partial_corr[Nbins][NbinsPhiPQ];

  Double_t MaxPhiPQ = 180.;
  Double_t MinPhiPQ = -180.;
  Double_t DeltaPhiPQ = (MaxPhiPQ - MinPhiPQ) / (Double_t)NbinsPhiPQ;
  Double_t LowEdge, HighEdge;
  TCut CutPhiPQ;

  Double_t dataNorm, bkgNorm;

  TF1 *Model[Nbins];
  TF1 *Signal[Nbins];
  TF1 *ResidualBkg[Nbins];
  TFitResult *FitResult[Nbins];

  // fix parameters, based on "All data" results
  const Int_t Ntargets = 4;
  Int_t kinvarIndex = 0 * (kinvarOption == "Q2") + 1 * (kinvarOption == "Nu") + 2 * (kinvarOption == "wZ") + 3 * (kinvarOption == "wPt2");
  Double_t meanFix[Ntargets][Nbins] = {{0.785, 0.785, 0.785, 0.780}, {0.784, 0.783, 0.783, 0.781}, {0.782, 0.787, 0.783, 0.781}, {0.786, 0.784, 0.780, 0.782}};
  Double_t sigmaFix[Ntargets][Nbins] = {{0.025, 0.022, 0.022, 0.022}, {0.023, 0.021, 0.023, 0.022}, {0.020, 0.023, 0.021, 0.022}, {0.021, 0.022, 0.024, 0.023}};

  for (Int_t i = 0; i < Nx; i++) {
    auxCut = Form("%f", EdgesKinvar[i]);
    auxCut += " < " + kinvarOption + " && " + kinvarOption + " < ";
    auxCut += Form("%f", EdgesKinvar[i + 1]);
    CutBin = auxCut;

    std::cout << auxCut << std::endl;

    // prepare data
    if (WithRadCorr) {
      for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) {
        // 1. Partial Hist
        LowEdge = MinPhiPQ + DeltaPhiPQ * pp;
        HighEdge = LowEdge + DeltaPhiPQ;
        CutPhiPQ = Form("wPhiPQ > %.2f && wPhiPQ < %.2f", LowEdge, HighEdge);
        dataTree->Draw(Form("wD>>partial_%d_%d", i, pp) + histProperties, gCutDIS && CutBin && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && gCutRegion && CutPhiPQ,
                       "goff");
        data_partial[i][pp] = (TH1D *)gROOT->FindObject(Form("partial_%d_%d", i, pp));
        // 2. Histogram for the Rad. Corr. Factors
        // these histograms contain the factors with null error,
        // for later multiplication and keeping the uncorrected error bars unchanged
        data_factor[i][pp] = new TH1D(Form("corr_factor_%d_%d", i, pp), Form("corr_factor_%d_%d", i, pp), 24, 0.66, 0.90);  // same as histProperties
        for (Int_t n = 0; n < 24; n++) {                                                                                    // same as histProperties
          data_factor[i][pp]->SetBinContent(n + 1, RCFactor_Target[pp]);
          data_factor[i][pp]->SetBinError(n + 1, 0);
        }
        // 3. Divide Partial Hist with Rad. Corr. Factors
        data_partial_corr[i][pp] = new TH1D(Form("partial_corr_%d_%d", i, pp), Form("partial_corr_%d_%d", i, pp), 24, 0.66, 0.90);  // same as histProperties
        data_partial_corr[i][pp]->Divide(data_partial[i][pp], data_factor[i][pp]);
      }
      // 4. Create Sum of Partial Hists
      dataMassive[i] = new TH1D(Form("data_%d_", i), Form("data_%d_", i), 24, 0.66, 0.90);  // same as histProperties
      for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) {
        dataMassive[i]->Add(data_partial_corr[i][pp]);
      }
    } else {
      dataTree->Draw(Form("wD>>data_%d", i) + histProperties, gCutDIS && CutBin && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle && gCutRegion, "goff");
      dataMassive[i] = (TH1D *)gROOT->FindObject(Form("data_%d", i));
    }

    dataMassive[i]->SetMarkerColor(kBlack);
    dataMassive[i]->SetMarkerStyle(8);
    dataMassive[i]->SetLineColor(kBlack);
    dataMassive[i]->SetLineWidth(2);
    dataMassive[i]->SetFillStyle(0);

    dataMassive[i]->SetTitle("");
    dataMassive[i]->GetXaxis()->SetTitle("Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
    dataMassive[i]->GetXaxis()->SetNdivisions(412);
    dataMassive[i]->GetYaxis()->SetTitle("Counts");
    dataMassive[i]->GetYaxis()->SetTitleOffset(1.2);
    // dataMassive[i]->GetYaxis()->SetTitleSize(0.05);

    // prepare bkg
    if (WithRadCorr) {
      for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) {
        // 1. Partial Hist
        LowEdge = MinPhiPQ + DeltaPhiPQ * pp;
        HighEdge = LowEdge + DeltaPhiPQ;
        CutPhiPQ = Form("wPhiPQ > %.2f && wPhiPQ < %.2f", LowEdge, HighEdge);
        bkgTree->Draw(Form("wD>>partial_bkg_%d_%d", i, pp) + histProperties, gCutDIS && CutBin && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && gCutRegion && CutPhiPQ,
                      "goff");
        bkg_partial[i][pp] = (TH1D *)gROOT->FindObject(Form("partial_bkg_%d_%d", i, pp));
        // 2. Histogram for the Rad. Corr. Factors
        // these histograms contain the factors with null error,
        // for later multiplication and keeping the uncorrected error bars unchanged
        bkg_factor[i][pp] = new TH1D(Form("corr_factor_bkg_%d_%d", i, pp), Form("corr_factor_bkg_%d_%d", i, pp), 24, 0.66, 0.90);  // same as histProperties
        for (Int_t n = 0; n < 24; n++) {                                                                                           // same as histProperties
          bkg_factor[i][pp]->SetBinContent(n + 1, RCFactor_Target[pp]);
          bkg_factor[i][pp]->SetBinError(n + 1, 0);
        }
        // 3. Divide Partial Hist with Rad. Corr. Factors
        bkg_partial_corr[i][pp] = new TH1D(Form("partial_corr_bkg_%d_%d", i, pp), Form("partial_corr_bkg_%d_%d", i, pp), 24, 0.66, 0.90);  // same as histProperties
        bkg_partial_corr[i][pp]->Divide(bkg_partial[i][pp], bkg_factor[i][pp]);
      }
      // 4. Create Sum of Partial Hists
      bkgMassive[i] = new TH1D(Form("bkg_%d", i), Form("bkg_%d", i), 24, 0.66, 0.90);  // same as histProperties
      for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) {
        bkgMassive[i]->Add(bkg_partial_corr[i][pp]);
      }
    } else {
      bkgTree->Draw(Form("wD>>bkg_%d", i) + histProperties, gCutDIS && CutBin && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle && gCutRegion, "goff");
      bkgMassive[i] = (TH1D *)gROOT->FindObject(Form("bkg_%d", i));
    }

    bkgMassive[i]->SetMarkerColor(kRed);
    bkgMassive[i]->SetMarkerStyle(8);
    bkgMassive[i]->SetLineColor(kRed);
    bkgMassive[i]->SetLineWidth(2);
    bkgMassive[i]->SetFillStyle(0);

    /*** NORMALIZATION ***/

    dataNorm = dataMassive[i]->Integral(BinsForNormalization[0], BinsForNormalization[1]) + dataMassive[i]->Integral(BinsForNormalization[2], BinsForNormalization[3]);
    std::cout << "dataNorm = " << dataNorm << std::endl;

    bkgNorm = bkgMassive[i]->Integral(BinsForNormalization[0], BinsForNormalization[1]) + bkgMassive[i]->Integral(BinsForNormalization[2], BinsForNormalization[3]);
    std::cout << "bkgNorm  = " << bkgNorm << std::endl;
    bkgMassive[i]->Scale(dataNorm / bkgNorm);

    /*** BKG SUBTRACTION ***/

    subMassive[i] = new TH1D(Form("sub_%d", i), "", plotNbins, plotMin, plotMax);
    subMassive[i]->Add(dataMassive[i], bkgMassive[i], 1, -1);

    subMassive[i]->SetTitle("");
    subMassive[i]->GetXaxis()->SetTitle("Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
    subMassive[i]->GetXaxis()->SetNdivisions(412);
    subMassive[i]->GetYaxis()->SetTitle("Data - Mixed Event Bkg");
    subMassive[i]->GetYaxis()->SetTitleOffset(1.2);

    subMassive[i]->SetMarkerColor(kOrange + 10);
    subMassive[i]->SetMarkerStyle(8);
    subMassive[i]->SetLineColor(kOrange + 10);
    subMassive[i]->SetLineWidth(2);
    subMassive[i]->SetFillStyle(0);

    /*** FIT ***/

    Double_t MeanIGV = 0.782;
    Double_t MeanLimit = 0.08;
    Double_t SigmaIGV = 0.024;
    Double_t SigmaLimit = 0.011;
    Model[i] = new TF1(Form("model_%d", i), "gaus(0) + pol1(3)", plotMin, plotMax);
    Model[i]->SetParameter(1, MeanIGV);
    Model[i]->SetParameter(2, SigmaIGV);
    Model[i]->SetParLimits(0, 0., 100000);  // force positive values
    Model[i]->SetParLimits(1, MeanIGV - MeanLimit, MeanIGV + MeanLimit);
    Model[i]->SetParLimits(2, SigmaIGV - SigmaLimit, SigmaIGV + SigmaLimit);
    if (fixParams) {
      Model[i]->FixParameter(1, meanFix[kinvarIndex][i]);
      Model[i]->FixParameter(2, sigmaFix[kinvarIndex][i]);
    }

    FitResult[i] = (subMassive[i]->Fit(Form("model_%d", i), "BEMSVN")).Get();

    Signal[i] = new TF1(Form("signal_%d", i), "gaus", plotMin, plotMax);
    Signal[i]->SetParameter(0, Model[i]->GetParameter(0));
    Signal[i]->SetParameter(1, Model[i]->GetParameter(1));
    Signal[i]->SetParameter(2, Model[i]->GetParameter(2));
    ResidualBkg[i] = new TF1(Form("res-bkg_%d", i), "pol1", plotMin, plotMax);
    ResidualBkg[i]->SetParameter(0, Model[i]->GetParameter(3));
    ResidualBkg[i]->SetParameter(1, Model[i]->GetParameter(4));

    Signal[i]->SetLineWidth(3);
    Signal[i]->SetLineColor(kMagenta);

    ResidualBkg[i]->SetLineWidth(3);
    ResidualBkg[i]->SetLineColor(kGray + 2);
    ResidualBkg[i]->SetLineStyle(kDashed);

    // save into output file
    subMassive[i]->Write();
    Model[i]->Write();
    FitResult[i]->Write();
  }

  /*** FIX Y-AXIS ***/

  Double_t MaxRangeData = 0;
  Double_t MaxRangeSub = 0;
  for (Int_t i = 0; i < Nx; i++) {
    if (dataMassive[i]->GetMaximum() > MaxRangeData) MaxRangeData = dataMassive[i]->GetMaximum();
    if (subMassive[i]->GetMaximum() > MaxRangeSub) MaxRangeSub = subMassive[i]->GetMaximum();
  }

  /*** DRAW ***/

  gStyle->SetPadBorderSize(0);

  gStyle->SetLineWidth(1);
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetTitleFontSize(0.06);

  TCanvas *can1 = new TCanvas("evnt-mixing_" + targetOption + "_" + kinvarOption + StringRadCorr, "evnt-mixing_" + targetOption + "_" + kinvarOption + StringRadCorr, 1920, 960);
  can1->Divide(Nx, 2, 0, 0);

  // top
  Int_t counter = 0;
  for (Int_t i = 0; i < Nx; i++) {

    counter++;
    can1->cd(counter);

    // set y-axis from before
    dataMassive[i]->GetYaxis()->SetRangeUser(0, 1.2 * MaxRangeData);
    dataMassive[i]->Draw("E");
    bkgMassive[i]->Draw("E SAME");

    // title
    auxCut = Form("%.2f", EdgesKinvar[i]);
    auxCut += " < " + kinvarTitle + " < ";
    auxCut += Form("%.2f", EdgesKinvar[i + 1]);
    auxCut += ", " + targetOption + " data";
    TPaveText *pav = new TPaveText(0.15, 0.88, 0.40, 0.98, "NDC NB");  // no border
    pav->AddText(auxCut);
    ((TText *)pav->GetListOfLines()->Last())->SetTextSize(0.04);
    pav->SetBorderSize(0);
    pav->SetFillStyle(0);
    pav->SetTextAlign(12);
    if (i > 0) {
      pav->SetX1(0.05);
      pav->SetX2(0.40);
    }
    pav->Draw();

    if (i == 0) {
      TLegend *leg = new TLegend(0.15, 0.74, 0.45, 0.88);  // x1,y1,x2,y2
      leg->AddEntry(dataMassive[i], "Data", "lp");
      leg->AddEntry(bkgMassive[i], "Mixed Event Bkg", "lp");
      leg->SetBorderSize(0);
      leg->SetFillStyle(0);
      leg->SetTextFont(62);
      leg->Draw();
    }

    // debug
    // if (i == Nx-1) DrawVerticalLine(0.9, kBlack, kSolid, 2, 0, 0.0, 1.0);
  }

  // botttom
  TString Chi2String, NormString, MeanString, SigmaString;
  Double_t MeanValue, MeanError, SigmaValue, SigmaError;
  for (Int_t i = 0; i < Nx; i++) {
    counter++;
    can1->cd(counter);

    // set y-axis from before
    subMassive[i]->GetYaxis()->SetRangeUser(-0.5 * MaxRangeSub, 1.5 * MaxRangeSub);
    subMassive[i]->Draw("E");

    Signal[i]->Draw("SAME");
    ResidualBkg[i]->Draw("SAME");

    if (i == 0)
      DrawHorizontalLine(0, kBlack, kSolid, 1, 0, 0.1, 1.0);
    else if (i == 1)
      DrawHorizontalLine(0, kBlack, kSolid, 1, 0, 0., 1.0);
    else if (i == 2)
      DrawHorizontalLine(0, kBlack, kSolid, 1, 0, 0., 1.0);
    else if (i == 3)
      DrawHorizontalLine(0, kBlack, kSolid, 1, 0, 0., 1.0);

    // title
    auxCut = Form("%.2f", EdgesKinvar[i]);
    auxCut += " < " + kinvarTitle + " < ";
    auxCut += Form("%.2f", EdgesKinvar[i + 1]);
    auxCut += ", " + targetOption + " data";
    TPaveText *pav = new TPaveText(0.15, 0.88, 0.40, 0.98, "NDC NB");  // no border
    pav->AddText(auxCut);
    ((TText *)pav->GetListOfLines()->Last())->SetTextSize(0.04);
    pav->SetBorderSize(0);
    pav->SetFillStyle(0);
    pav->SetTextAlign(12);
    if (i > 0) {
      pav->SetX1(0.05);
      pav->SetX2(0.40);
    }
    pav->Draw();

    // legend
    if (i == 0) {
      TLegend *leg = new TLegend(0.15, 0.67, 0.35, 0.88);  // x1,y1,x2,y2
      leg->AddEntry(subMassive[i], "Data - Bkg", "lp");
      leg->AddEntry(Signal[i], "Signal", "l");
      leg->AddEntry(ResidualBkg[i], "Residual Bkg", "l");
      leg->SetBorderSize(0);
      leg->SetFillStyle(0);
      leg->SetTextFont(62);
      leg->Draw();
    }

    // pave
    Chi2String = Form("#chi^{2}/ndf = %.4f", Model[i]->GetChisquare() / (Double_t)Model[i]->GetNDF());
    NormString = Form("A = %.3f #pm %.3f", Model[i]->GetParameter(0), Model[i]->GetParError(0));
    MeanString = Form("#mu = %.3f #pm %.6f", Model[i]->GetParameter(1), Model[i]->GetParError(1));
    SigmaString = Form("#sigma = %.3f #pm %.6f", Model[i]->GetParameter(2), Model[i]->GetParError(2));
    TPaveText *pav2 = new TPaveText(0.70, 0.66, 0.96, 0.96, "NDC NB");  // no border
    pav2->AddText(Chi2String);
    pav2->AddText(NormString);
    pav2->AddText(MeanString);
    pav2->AddText(SigmaString);
    pav2->SetBorderSize(0);
    pav2->SetTextAlign(12);
    pav2->SetFillStyle(0);
    if (i > 0) {
      pav2->SetX1(0.66);
      pav2->SetX2(0.96);
    }
    pav2->Draw();

    // params
    MeanValue = Model[i]->GetParameter(1);
    SigmaValue = Model[i]->GetParameter(2);
    DrawVerticalLine(MeanValue - 3 * SigmaValue, kMagenta, kDashed, 2, 0, 0.2, 0.5);
    DrawVerticalLine(MeanValue + 3 * SigmaValue, kMagenta, kDashed, 2, 0, 0.2, 0.5);

    // debug
    // if (i == Nx-1) DrawVerticalLine(0.9, kBlack, kSolid, 2, 0, 0.1, 1.0);
  }

  can1->Print("evnt-mixing_" + targetOption + "_" + kinvarOption + StringRadCorr + ".png");

  // close output file
  RootOutputFile->Close();
}
