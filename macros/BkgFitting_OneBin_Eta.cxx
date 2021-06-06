#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawHorizontalLine.cxx"
#include "DrawVerticalLine.cxx"

using namespace RooFit;

void BkgFitting_OneBin_Eta(TString targetOption = "C", TString kinvarOption = "Q2", Int_t binNumber = 0, Int_t fixRange = 0) {
  
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

  // histogram properties
  Int_t plotNbins = 54;
  Double_t plotMin = 0.26;
  Double_t plotMax = 0.8;
  TString histProperties = Form("(%d, %f, %f)", plotNbins, plotMin, plotMax);

  TString kinvarTitle;
  Double_t EdgesKinvar[2];
  if (kinvarOption == "Q2") {
    kinvarTitle = "Q^{2}";
    EdgesKinvar[0] = kEdgesQ2_Eta[binNumber];
    EdgesKinvar[1] = kEdgesQ2_Eta[binNumber + 1];
  } else if (kinvarOption == "Nu") {
    kinvarTitle = "#nu";
    EdgesKinvar[0] = kEdgesNu_Eta[binNumber];
    EdgesKinvar[1] = kEdgesNu_Eta[binNumber + 1];
  } else if (kinvarOption == "eZ") {
    kinvarTitle = "z_{h}";
    EdgesKinvar[0] = kEdgesZ_Eta[binNumber];
    EdgesKinvar[1] = kEdgesZ_Eta[binNumber + 1];
  } else if (kinvarOption == "ePt2") {
    kinvarTitle = "p_{T}^{2}";
    EdgesKinvar[0] = kEdgesPt2_Eta[binNumber];
    EdgesKinvar[1] = kEdgesPt2_Eta[binNumber + 1];
  }

  TString auxCut;
  TCut CutBin;

  /*** SET CANVAS, PADS AND HISTOGRAMS ***/

  // set canvas
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  TCanvas *can1 = new TCanvas("eta-bkg-fitting_binned_" + targetOption + "_" + kinvarOption, "eta-bkg-fitting_binned_" + targetOption + "_" + kinvarOption, 660, 1080);

  // define pads
  TPad *upperPad;
  TPad *lowerPad;

  TH1D *signalHist;
  TH1D *bkgHist;
  TH1D *modelHist;
  TH1D *dataHist;
  TH1D *dataErrHist;
  TH1D *testHist;
  
  TTree *auxTree;

  RooPlot *upperFrame;
  RooPlot *lowerFrame;

  TString NomegaS;
  TString MeanS;
  TString SigmaS;
  TString NbkgS;
  TString PolaS;
  TString PolbS;

  Double_t meanVal;
  Double_t sigmaVal;

  // prepare pads
  upperPad = new TPad("upper", "upper", 0.05, 0.40, 0.95, 0.95, 0, 0, 0);  // x1,y1,x2,y2
  upperPad->SetTopMargin(0.05);
  upperPad->SetBottomMargin(0);
  upperPad->SetLeftMargin(0.15);
  upperPad->SetRightMargin(0.05);
      
  lowerPad = new TPad("lower", "lower", 0.05, 0.05, 0.95, 0.40, 0, 0, 0);  // x1,y1,x2,y2
  lowerPad->SetTopMargin(0);
  lowerPad->SetBottomMargin(0.15);
  lowerPad->SetLeftMargin(0.15);
  lowerPad->SetRightMargin(0.05);

  // define cut
  auxCut = Form("%f", EdgesKinvar[0]);
  auxCut += " < " + kinvarOption + " && " + kinvarOption + " < ";
  auxCut += Form("%f", EdgesKinvar[1]);
  CutBin = auxCut;

  std::cout << auxCut << std::endl;

  // prepare histograms
  dataTree->Draw("eM>>data" + histProperties, gCutDIS && CutBin && CutVertex && gCutPhotonsOpAngle_Eta && gCutRegion_Eta, "goff");
  dataHist = (TH1D *)gROOT->FindObject("data");

  std::cout << "ENTRIES = " << dataHist->GetEntries() << std::endl;
  
  // prepare tree
  // auxTree = dataTree->CopyTree(gCutDIS && CutBin && CutVertex && gCutPhotonsOpAngle_Eta && gCutRegion_Eta);  // MAXIMUM LIKELIHOOD METHOD

  // define x variable and ranges
  RooRealVar x("eM", "", plotMin, plotMax);

  // define data set
  // RooDataSet data("data", "data", auxTree, x); // MAXIMUM LIKELIHOOD METHOD
  RooDataHist data("data", "data", x, dataHist);
  
  // define signal function
  RooRealVar mean("#mu(#eta)", "mean of gaussian", 0.500, 0.594); // 0.547, 
  RooRealVar sigma("#sigma(#eta)", "width of gaussian", 0.034, 0.074); // 0.054, 
  RooGaussian signal("signal", "eta signal", x, mean, sigma);
  
  // define bkg function
  RooRealVar b1("b1", "linear term", -100, 100); // 0., 
  RooRealVar b2("b2", "quadratic term", -10., 10.); // -0.1, 
  RooChebychev bkg("bkg", "background", x, RooArgList(b1, b2));
  
  // define extended composite model
  RooRealVar nsig("N_{#eta}", "number of eta particles", 0., 1000000); // 1000, 
  RooRealVar nbkg("N_{bkg}", "number of background", 0, 1000000); // 1000, 
  RooAddPdf model("model", "(g+pol2)", RooArgList(bkg, signal), RooArgList(nbkg, nsig));

  upperFrame = x.frame(Name("upper"));
  lowerFrame = x.frame(Name("lower"));
  
  RooFitResult *rf = model.fitTo(data, Minos(kTRUE), Extended(), Save());
  rf->SetName("fit-result");
  
  data.plotOn(upperFrame, Name("Data"), Binning(plotNbins, plotMin, plotMax)); // first, mandatory
  model.plotOn(upperFrame, Name("Model"));
       
  model.plotOn(upperFrame, Name("Bkg"), Components("bkg"), LineColor(kGray+2), LineStyle(kDashed));
  model.plotOn(upperFrame, Name("Signal"), Components("signal"), LineColor(kRed));

  modelHist = (TH1D *)model.createHistogram("model", x, Binning(plotNbins, plotMin, plotMax), Extended());
  modelHist->Scale((plotMax-plotMin)/(Double_t)plotNbins); // bin width

  dataErrHist = new TH1D("dataErrHist", "dataErrHist", plotNbins, plotMin, plotMax);
  for (Int_t k = 1; k <= plotNbins; k++) {
    dataErrHist->SetBinContent(k, dataHist->GetBinError(k));
    dataErrHist->SetBinError(k, 0);
  }

  testHist = new TH1D("testHist", "testHist", plotNbins, plotMin, plotMax);
  testHist->Add(dataHist, modelHist, 1, -1);
  testHist->Divide(dataErrHist);
  
  // assign parameters
  NomegaS = Form("N_{#eta} = %.3f #pm %.3f", nsig.getValV(), nsig.getError());
  MeanS = Form("#mu = %.3f #pm %.6f", mean.getValV(), mean.getError());
  SigmaS = Form("#sigma = %.3f #pm %.6f", sigma.getValV(), sigma.getError());
  NbkgS = Form("N_{bkg} = %.3f #pm %.3f", nbkg.getValV(), nbkg.getError());
  PolaS = Form("b1 = %.3f #pm %.6f", b1.getValV(), b1.getError());
  PolbS = Form("b2 = %.3f #pm %.6f", b2.getValV(), b2.getError());
  
  // to represent as vertical lines

  meanVal = mean.getValV();
  sigmaVal = sigma.getValV();

  // rf->Write();

  /*** FIX Y-AXIS ***/

  Double_t MaxRange = 1.15*dataHist->GetMaximum();
  if (fixRange) MaxRange = 800; // DEBUG!!

  /*** DRAW ***/

  // title
  auxCut = Form("%.2f", EdgesKinvar[0]);
  auxCut += " < " + kinvarTitle + " < ";
  auxCut += Form("%.2f", EdgesKinvar[1]);
  auxCut += ", " + targetOption + " data";
      
  // style: upper pad
  upperFrame->SetTitle("");
      
  upperFrame->GetYaxis()->SetRangeUser(0, MaxRange); // set y-axis from before
  upperFrame->GetYaxis()->SetTitle("Counts");
  upperFrame->GetYaxis()->SetTitleSize(0.04);
  upperFrame->GetYaxis()->SetTickSize(0.02);
      
  upperFrame->GetXaxis()->SetNdivisions(412);

  // style: lower pad
  testHist->SetTitle("");
  testHist->SetFillColor(kMagenta);
      
  testHist->GetYaxis()->SetRangeUser(-4.5, 4.5);
  testHist->GetYaxis()->SetRangeUser(-4.5, 4.5);
  testHist->GetYaxis()->SetTitle("Pull");
  testHist->GetYaxis()->SetTitleOffset(0.6);
  testHist->GetYaxis()->SetTitleSize(0.065);
  testHist->GetYaxis()->SetLabelSize(0.06);
  testHist->GetYaxis()->SetTickSize(0.02);
  testHist->GetYaxis()->SetNdivisions(210);
      
  testHist->GetXaxis()->SetTitle("Reconstructed Mass m(#gamma#gamma) [GeV]");
  testHist->GetXaxis()->SetTitleOffset(1.2);
  testHist->GetXaxis()->SetTitleSize(0.06);
  testHist->GetXaxis()->SetNdivisions(412);
  testHist->GetXaxis()->SetTickSize(0.05);
  testHist->GetXaxis()->SetLabelSize(0.06);
  
  /*** DRAW ***/

  /*** UPPER PAD ***/

  lowerPad->Draw();
  upperPad->Draw();
      
  upperPad->cd();
  upperFrame->Draw();

  // title and parameters
  TPaveText *pav = new TPaveText(0.17, 0.57, 0.42, 0.9, "NDC NB"); // no border
  pav->AddText(auxCut); // Title
  ((TText*)pav->GetListOfLines()->Last())->SetTextSize(0.04);
  pav->AddText("");
  pav->AddText(NomegaS);
  pav->AddText(MeanS);
  pav->AddText(SigmaS);
  pav->AddText(NbkgS);
  pav->AddText(PolaS);
  pav->AddText(PolbS);
  pav->SetBorderSize(0);
  pav->SetFillStyle(0);
  pav->SetTextAlign(12);
  pav->Draw();

  // draw lines
  gPad->Update(); // necessary
  // mu - 3sigma
  Double_t x0 = meanVal - 3*sigmaVal;
  Double_t u = (x0 - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  TLine *line_range;
  line_range = new TLine(u, 0.00, u, 0.25);
  line_range->SetLineColor(kOrange+2); line_range->SetLineWidth(2); line_range->SetLineStyle(kDashed);
  line_range->SetNDC();
  line_range->Draw();
  // mu + 3sigma
  x0 = meanVal + 3*sigmaVal;                   
  u = (x0 - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  line_range = new TLine(u, 0.00, u, 0.25);
  line_range->SetLineColor(kOrange+2); line_range->SetLineWidth(2); line_range->SetLineStyle(kDashed);
  line_range->SetNDC();
  line_range->Draw();
  // mu
  x0 = meanVal;
  u = (x0 - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  line_range = new TLine(u, 0.00, u, 0.95);
  line_range->SetLineColor(kRed); line_range->SetLineWidth(2); line_range->SetLineStyle(kDashed);
  line_range->SetNDC();
  line_range->Draw();
      
  // legend
  TLegend *leg = new TLegend(0.75, 0.75, 0.95, 0.88);  // x1,y1,x2,y2
  leg->AddEntry(upperFrame->findObject("Data"), "Data", "lp");
  leg->AddEntry(upperFrame->findObject("Model"), "Fit", "l");
  leg->AddEntry(upperFrame->findObject("Bkg"), "Bkg", "l");
  leg->AddEntry(upperFrame->findObject("Signal"), "Signal", "l");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(62);
  leg->Draw();
      
  /*** LOWER PAD ***/
      
  lowerPad->cd();
  testHist->Draw("BAR MIN0 HIST");

  DrawHorizontalLine(3, kRed, kDashed, 2, 1);
  DrawHorizontalLine(0, kBlack, kSolid, 1, 1);
  DrawHorizontalLine(-3, kRed, kDashed, 2, 1);
      
  can1->Update();

  TString binSufix = Form("%d", binNumber);
  can1->Print("eta-bkg-fitting_binned_" + targetOption + "_" + kinvarOption + "_" + binNumber + ".png");
}
