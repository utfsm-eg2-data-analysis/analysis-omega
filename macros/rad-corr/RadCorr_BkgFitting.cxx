#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawHorizontalLine.cxx"
#include "DrawVerticalLine.cxx"

using namespace RooFit;

void RadCorr_BkgFitting(TString targetOption = "D", TString kinvarInput = "Q2", Int_t WithRadCorr = 1) {
  // Plot all bins, comparing event-mixing from data with data.

  gROOT->SetBatch(kTRUE);  // prevent output printing

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
  TCut CutVertex;
  if (targetOption == "D" || targetOption == "All") {
    CutVertex = gCutLiquid;
    dataFile1 = gDataDir + "/C/*.root";
    dataFile2 = gDataDir + "/Fe/*.root";
    dataFile3 = gDataDir + "/Pb/*.root";
    if (targetOption == "All") CutVertex = gCutLiquid || gCutSolid;
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    dataFile1 = gDataDir + "/" + targetOption + "/*.root";
  }

  TChain *dataTree = new TChain();
  dataTree->Add(dataFile1 + "/mix");
  if (targetOption == "D" || targetOption == "All") {
    dataTree->Add(dataFile2 + "/mix");
    dataTree->Add(dataFile3 + "/mix");
  }

  Int_t start = 0;
  if (kinvarInput == "Q2")
    start = 0;
  else if (kinvarInput == "Nu")
    start = 1;
  else if (kinvarInput == "wZ")
    start = 2;
  else if (kinvarInput == "wPt2")
    start = 3;

  // necessary for gCutKaons
  SetAliases(dataTree);

  Int_t plotNbins = 24;
  Double_t plotMin = 0.66;
  Double_t plotMax = 0.90;
  TString histProperties = Form("(%d, %f, %f)", plotNbins, plotMin, plotMax);

  // set output file
  TFile *RootOutputFile = new TFile("bkg-fitting_" + targetOption + "_" + kinvarInput + StringRadCorr + ".root", "RECREATE");

  TString kinvarOption[4] = {"Q2", "Nu", "wZ", "wPt2"};
  TString kinvarTitle[4] = {"Q^{2}", "#nu", "z_{h}", "p_{T}^{2}"};
  Double_t EdgesKinvar[4][5];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[0][i] = kEdgesQ2[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[1][i] = kEdgesNu[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[2][i] = kEdgesZ[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[3][i] = kEdgesPt2[i];

  TString auxCut;
  TCut CutBin;

  /*** SET CANVAS, PADS AND HISTOGRAMS ***/

  const Int_t Nbins = 4;
  const Int_t Nkinvars = 4;

  // set canvas
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  TCanvas *can1 = new TCanvas("bkg-fitting_" + targetOption + "_" + kinvarInput + StringRadCorr, "bkg-fitting_" + targetOption + "_" + kinvarInput + StringRadCorr, 1600, 1800);
  can1->Divide(2, 2, 0.001, 0.001);  // Nkinvars?

  // define pads
  TPad *upperPad[Nbins][Nkinvars];
  TPad *lowerPad[Nbins][Nkinvars];

  TH1D *signalHist[Nbins][Nkinvars];
  TH1D *bkgHist[Nbins][Nkinvars];
  TH1D *modelHist[Nbins][Nkinvars];
  TH1D *dataHist[Nbins][Nkinvars];
  TH1D *dataErrHist[Nbins][Nkinvars];
  TH1D *testHist[Nbins][Nkinvars];

  RooPlot *upperFrame[Nbins][Nkinvars];
  RooPlot *lowerFrame[Nbins][Nkinvars];

  TString NomegaS[Nbins][Nkinvars];
  TString MeanS[Nbins][Nkinvars];
  TString SigmaS[Nbins][Nkinvars];
  TString NbkgS[Nbins][Nkinvars];
  TString PolaS[Nbins][Nkinvars];
  TString PolbS[Nbins][Nkinvars];

  Double_t meanVal[Nbins][Nkinvars];
  Double_t sigmaVal[Nbins][Nkinvars];

  // fix parameters, based on "All data" results
  Double_t meanFix[4][4] = {{0.785, 0.784, 0.782, 0.790}, {0.785, 0.784, 0.787, 0.785}, {0.785, 0.783, 0.783, 0.782}, {0.781, 0.783, 0.781, 0.782}};
  Double_t sigmaFix[4][4] = {{0.024, 0.024, 0.018, 0.021}, {0.024, 0.021, 0.022, 0.023}, {0.022, 0.022, 0.020, 0.021}, {0.019, 0.023, 0.021, 0.022}};

  // radiative corrections
  TH1D *radCorrHist_partial[Nbins][Nkinvars][NbinsPhiPQ];
  TH1D *radCorrHist_factor[Nbins][Nkinvars][NbinsPhiPQ];
  TH1D *radCorrHist_partial_corr[Nbins][Nkinvars][NbinsPhiPQ];

  Double_t MaxPhiPQ = 180.;
  Double_t MinPhiPQ = -180.;
  Double_t DeltaPhiPQ = (MaxPhiPQ - MinPhiPQ) / (Double_t)NbinsPhiPQ;
  Double_t LowEdge, HighEdge;
  TCut CutPhiPQ;

  for (Int_t j = start; j < start + 1; j++) {  // Ny
    for (Int_t i = 0; i < Nbins; i++) {        // Nx

      // prepare pads
      upperPad[i][j] = new TPad(Form("upper_%d_%d", i, j), Form("upper_%d_%d", i, j), 0.05, 0.40, 0.95, 0.95, 0, 0, 0);  // x1,y1,x2,y2
      upperPad[i][j]->SetTopMargin(0.05);
      upperPad[i][j]->SetBottomMargin(0);
      upperPad[i][j]->SetLeftMargin(0.15);
      upperPad[i][j]->SetRightMargin(0.05);

      lowerPad[i][j] = new TPad(Form("lower_%d_%d", i, j), Form("lower_%d_%d", i, j), 0.05, 0.05, 0.95, 0.40, 0, 0, 0);  // x1,y1,x2,y2
      lowerPad[i][j]->SetTopMargin(0);
      lowerPad[i][j]->SetBottomMargin(0.15);
      lowerPad[i][j]->SetLeftMargin(0.15);
      lowerPad[i][j]->SetRightMargin(0.05);

      // prepare histograms
      auxCut = Form("%f", EdgesKinvar[j][i]);
      auxCut += " < " + kinvarOption[j] + " && " + kinvarOption[j] + " < ";
      auxCut += Form("%f", EdgesKinvar[j][i + 1]);
      CutBin = auxCut;

      std::cout << auxCut << std::endl;

      // prepare data
      if (WithRadCorr) {
        for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) {
          // 1. Partial Hist
          LowEdge = MinPhiPQ + DeltaPhiPQ * pp;
          HighEdge = LowEdge + DeltaPhiPQ;
          CutPhiPQ = Form("wPhiPQ > %.2f && wPhiPQ < %.2f", LowEdge, HighEdge);
          dataTree->Draw(Form("wD>>partial_%d_%d_%d", i, j, pp) + histProperties,
                         gCutDIS && CutBin && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && gCutRegion && CutPhiPQ, "goff");
          radCorrHist_partial[i][j][pp] = (TH1D *)gROOT->FindObject(Form("partial_%d_%d_%d", i, j, pp));
          // 2. Histogram for the Rad. Corr. Factors
          // these histograms contain the factors with null error,
          // for later multiplication and keeping the uncorrected error bars unchanged
          radCorrHist_factor[i][j][pp] = new TH1D(Form("corr_factor_%d_%d_%d", i, j, pp), Form("corr_factor_%d_%d_%d", i, j, pp), 24, 0.66, 0.90);  // same as histProperties
          for (Int_t n = 0; n < 24; n++) {                                                                                                          // same as histProperties
            radCorrHist_factor[i][j][pp]->SetBinContent(n + 1, RCFactor_Target[pp]);
            radCorrHist_factor[i][j][pp]->SetBinError(n + 1, 0);
          }
          // 3. Divide Partial Hist with Rad. Corr. Factors
          radCorrHist_partial_corr[i][j][pp] =
              new TH1D(Form("partial_corr_%d_%d_%d", i, j, pp), Form("partial_corr_%d_%d_%d", i, j, pp), 24, 0.66, 0.90);  // same as histProperties
          radCorrHist_partial_corr[i][j][pp]->Divide(radCorrHist_partial[i][j][pp], radCorrHist_factor[i][j][pp]);
        }

        // 4. Create Sum of Partial Hists
        dataHist[i][j] = new TH1D(Form("data_%d_%d", i, j), Form("data_%d_%d", i, j), 24, 0.66, 0.90);  // same as histProperties
        for (Int_t pp = 0; pp < NbinsPhiPQ; pp++) {
          dataHist[i][j]->Add(radCorrHist_partial_corr[i][j][pp]);
        }
      } else {
        dataTree->Draw(Form("wD>>data_%i_%i", i, j) + histProperties, gCutDIS && CutBin && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle && gCutRegion, "goff");
        dataHist[i][j] = (TH1D *)gROOT->FindObject(Form("data_%i_%i", i, j));
      }

      // define x variable and ranges
      RooRealVar x("wD", "", plotMin, plotMax);

      // define data set
      RooDataHist data("data", "data", x, dataHist[i][j]);

      // define signal function
      RooRealVar mean("#mu(#omega)", "mean of gaussian", 0.782, 0.775, 0.790);
      RooRealVar sigma("#sigma(#omega)", "width of gaussian", 0.024, 0.008, 0.035);
      RooGaussian signal("signal", "omega signal", x, mean, sigma);

      // define bkg function
      RooRealVar b1("b1", "linear term", 0., -20, 20);
      RooRealVar b2("b2", "quadratic term", -0.1, -10., 0.);
      RooChebychev bkg("bkg", "background", x, RooArgList(b1, b2));

      // define extended composite model
      RooRealVar nsig("N_{#omega}", "number of omega particles", 1000, 0., 1000000);
      RooRealVar nbkg("N_{bkg}", "number of background", 1000, 0, 1000000);
      RooAddPdf model("model", "(g+pol2)", RooArgList(bkg, signal), RooArgList(nbkg, nsig));

      upperFrame[i][j] = x.frame(Name(Form("upper_f_%d_%d", i, j)));
      lowerFrame[i][j] = x.frame(Name(Form("lower_f_%d_%d", i, j)));

      RooFitResult *rf = model.fitTo(data, Minos(kTRUE), Extended(), Save());
      rf->SetName(Form("fit-result_%d_%d", i, j));

      data.plotOn(upperFrame[i][j], Name("Data"), Binning(plotNbins, plotMin, plotMax));  // first, mandatory
      model.plotOn(upperFrame[i][j], Name("Model"));

      model.plotOn(upperFrame[i][j], Name("Bkg"), Components("bkg"), LineColor(kGray + 2), LineStyle(kDashed));
      model.plotOn(upperFrame[i][j], Name("Signal"), Components("signal"), LineColor(kRed));

      modelHist[i][j] = (TH1D *)model.createHistogram(Form("model_%d_%d", i, j), x, Binning(plotNbins, plotMin, plotMax), Extended());
      modelHist[i][j]->Scale((plotMax - plotMin) / (Double_t)plotNbins);  // bin width

      dataErrHist[i][j] = new TH1D(Form("dataErrHist_%d_%d", i, j), Form("dataErrHist_%d_%d", i, j), plotNbins, plotMin, plotMax);
      for (Int_t k = 1; k <= plotNbins; k++) {
        dataErrHist[i][j]->SetBinContent(k, dataHist[i][j]->GetBinError(k));
        dataErrHist[i][j]->SetBinError(k, 0);
      }

      testHist[i][j] = new TH1D(Form("testHist_%d_%d", i, j), Form("testHist_%d_%d", i, j), plotNbins, plotMin, plotMax);
      testHist[i][j]->Add(dataHist[i][j], modelHist[i][j], 1, -1);
      testHist[i][j]->Divide(dataErrHist[i][j]);

      // assign parameters
      NomegaS[i][j] = Form("N_{#omega} = %.3f #pm %.3f", nsig.getValV(), nsig.getError());
      MeanS[i][j] = Form("#mu = %.3f #pm %.6f", mean.getValV(), mean.getError());
      SigmaS[i][j] = Form("#sigma = %.3f #pm %.6f", sigma.getValV(), sigma.getError());
      NbkgS[i][j] = Form("N_{bkg} = %.3f #pm %.3f", nbkg.getValV(), nbkg.getError());
      PolaS[i][j] = Form("b1 = %.3f #pm %.6f", b1.getValV(), b1.getError());
      PolbS[i][j] = Form("b2 = %.3f #pm %.6f", b2.getValV(), b2.getError());

      // to represent as vertical lines
      meanVal[i][j] = mean.getValV();
      sigmaVal[i][j] = sigma.getValV();

      rf->Write();
    }
  }

  /*** FIX Y-AXIS ***/

  Double_t MaxRange[Nkinvars];
  for (Int_t j = start; j < start + 1; j++) {
    MaxRange[j] = 0;
    for (Int_t i = 0; i < Nbins; i++) {
      if (dataHist[i][j]->GetMaximum() > MaxRange[j]) MaxRange[j] = dataHist[i][j]->GetMaximum();
    }
    MaxRange[j] += MaxRange[j] * 0.15;
  }

  /*** DRAW ***/

  Int_t counter = 1;
  for (Int_t j = start; j < start + 1; j++) {  // Ny
    for (Int_t i = 0; i < Nbins; i++) {        // Nx

      // title
      auxCut = Form("%.2f", EdgesKinvar[j][i]);
      auxCut += " < " + kinvarTitle[j] + " < ";
      auxCut += Form("%.2f", EdgesKinvar[j][i + 1]);
      auxCut += ", " + targetOption + " data";

      // style: upper pad
      upperFrame[i][j]->SetTitle("");

      upperFrame[i][j]->GetYaxis()->SetRangeUser(0, MaxRange[j]);  // set y-axis from before
      upperFrame[i][j]->GetYaxis()->SetTitle("Counts");
      upperFrame[i][j]->GetYaxis()->SetTitleSize(0.04);
      upperFrame[i][j]->GetYaxis()->SetTickSize(0.02);

      upperFrame[i][j]->GetXaxis()->SetNdivisions(412);

      // style: lower pad
      testHist[i][j]->SetTitle("");
      testHist[i][j]->SetFillColor(kMagenta);

      testHist[i][j]->GetYaxis()->SetRangeUser(-4.5, 4.5);
      testHist[i][j]->GetYaxis()->SetRangeUser(-4.5, 4.5);
      testHist[i][j]->GetYaxis()->SetTitle("Pull");
      testHist[i][j]->GetYaxis()->SetTitleOffset(0.6);
      testHist[i][j]->GetYaxis()->SetTitleSize(0.065);
      testHist[i][j]->GetYaxis()->SetLabelSize(0.06);
      testHist[i][j]->GetYaxis()->SetTickSize(0.02);
      testHist[i][j]->GetYaxis()->SetNdivisions(210);

      testHist[i][j]->GetXaxis()->SetTitle("Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
      testHist[i][j]->GetXaxis()->SetTitleOffset(1.2);
      testHist[i][j]->GetXaxis()->SetTitleSize(0.06);
      testHist[i][j]->GetXaxis()->SetNdivisions(412);
      testHist[i][j]->GetXaxis()->SetTickSize(0.05);
      testHist[i][j]->GetXaxis()->SetLabelSize(0.06);

      /*** DRAW ***/

      /*** UPPER PAD ***/

      can1->cd(counter);

      lowerPad[i][j]->Draw();
      upperPad[i][j]->Draw();

      upperPad[i][j]->cd();
      upperFrame[i][j]->Draw();

      // title and parameters
      TPaveText *pav = new TPaveText(0.20, 0.55, 0.45, 0.88, "NDC NB");  // no border
      pav->AddText(auxCut);                                              // Title
      ((TText *)pav->GetListOfLines()->Last())->SetTextSize(0.04);
      pav->AddText("");
      pav->AddText(NomegaS[i][j]);
      pav->AddText(MeanS[i][j]);
      pav->AddText(SigmaS[i][j]);
      pav->AddText(NbkgS[i][j]);
      pav->AddText(PolaS[i][j]);
      pav->AddText(PolbS[i][j]);
      pav->SetBorderSize(0);
      pav->SetFillStyle(0);
      pav->SetTextAlign(12);
      pav->Draw();

      // draw lines
      gPad->Update();  // necessary
      // mu - 3sigma
      Double_t x = meanVal[i][j] - 3 * sigmaVal[i][j];
      Double_t u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
      TLine *line_range;
      line_range = new TLine(u, 0.00, u, 0.25);
      line_range->SetLineColor(kOrange + 2);
      line_range->SetLineWidth(2);
      line_range->SetLineStyle(kDashed);
      line_range->SetNDC();
      line_range->Draw();
      // mu + 3sigma
      x = meanVal[i][j] + 3 * sigmaVal[i][j];
      u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
      line_range = new TLine(u, 0.00, u, 0.25);
      line_range->SetLineColor(kOrange + 2);
      line_range->SetLineWidth(2);
      line_range->SetLineStyle(kDashed);
      line_range->SetNDC();
      line_range->Draw();
      // mu
      x = meanVal[i][j];
      u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
      line_range = new TLine(u, 0.00, u, 0.95);
      line_range->SetLineColor(kRed);
      line_range->SetLineWidth(2);
      line_range->SetLineStyle(kDashed);
      line_range->SetNDC();
      line_range->Draw();

      // legend
      TLegend *leg = new TLegend(0.75, 0.75, 0.95, 0.88);  // x1,y1,x2,y2
      leg->AddEntry(upperFrame[i][j]->findObject("Data"), "Data", "lp");
      leg->AddEntry(upperFrame[i][j]->findObject("Model"), "Fit", "l");
      leg->AddEntry(upperFrame[i][j]->findObject("Bkg"), "Bkg", "l");
      leg->AddEntry(upperFrame[i][j]->findObject("Signal"), "Signal", "l");
      leg->SetBorderSize(0);
      leg->SetFillStyle(0);
      leg->SetTextFont(62);
      leg->Draw();

      /*** LOWER PAD ***/

      lowerPad[i][j]->cd();
      testHist[i][j]->Draw("BAR MIN0 HIST");

      DrawHorizontalLine(3, kRed, kDashed, 2, 1);
      DrawHorizontalLine(0, kBlack, kSolid, 1, 1);
      DrawHorizontalLine(-3, kRed, kDashed, 2, 1);

      can1->Update();

      // save into file
      // dataHist[i][j]->Write();

      counter++;
    }
  }

  can1->Write();

  can1->Print("bkg-fitting_" + targetOption + "_" + kinvarInput + StringRadCorr + ".png");

  // close output file
  RootOutputFile->Close();
}
