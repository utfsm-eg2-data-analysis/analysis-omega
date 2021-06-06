#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

using namespace RooFit;

void EventMixing_OneBin(TString targetOption = "D", TString kinvarOption = "Q2", Int_t BinNumber = 0) {
  // Plot all bins, comparing event-mixing from data with data.

  /*** INPUT ***/

  TString dataFile1, dataFile2, dataFile3;
  TString bkgFile1, bkgFile2, bkgFile3;
  TString BkgDir = gWorkDir + "/out/EventMixing/data";
  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
    dataFile1 = gDataDir + "/C/*.root";
    dataFile2 = gDataDir + "/Fe/*.root";
    dataFile3 = gDataDir + "/Pb/*.root";
    bkgFile1 = BkgDir + "/C/*.root";
    bkgFile2 = BkgDir + "/Fe/*.root";
    bkgFile3 = BkgDir + "/Pb/*.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    dataFile1 = gDataDir + "/" + targetOption + "/*.root";
    bkgFile1 = BkgDir + "/" + targetOption + "/*.root";
  }

  TChain *dataTree = new TChain();
  dataTree->Add(dataFile1 + "/mix");
  if (targetOption == "D") {
    dataTree->Add(dataFile2 + "/mix");
    dataTree->Add(dataFile3 + "/mix");
  }

  TChain *bkgTree = new TChain();
  bkgTree->Add(bkgFile1 + "/mix");
  if (targetOption == "D") {
    bkgTree->Add(bkgFile2 + "/mix");
    bkgTree->Add(bkgFile3 + "/mix");
  }

  // necessary for gCutKaons
  SetAliases(dataTree);
  SetAliases(bkgTree);

  Int_t plotNbins = 21;
  Double_t plotMin = 0.71;
  Double_t plotMax = 0.92;
  TString histProperties = Form("(%d, %f, %f)", plotNbins, plotMin, plotMax);
  Int_t BinsForNormalization[4];
  BinsForNormalization[0] = 1;
  BinsForNormalization[1] = 3;
  BinsForNormalization[2] = plotNbins - 2;
  BinsForNormalization[3] = plotNbins;

  TString kinvarTitle;
  Double_t EdgesKinvar[5];
  if (kinvarOption == "Q2") {
    kinvarTitle = "Q2";
    for (Int_t i = 0; i < 5; i++) EdgesKinvar[i] = kEdgesQ2[i];
  } else if (kinvarOption == "Nu") {
    kinvarTitle = "Nu";
    for (Int_t i = 0; i < 5; i++) EdgesKinvar[i] = kEdgesNu[i];
  } else if (kinvarOption == "wZ") {
    kinvarTitle = "z_{h}";
    for (Int_t i = 0; i < 5; i++) EdgesKinvar[i] = kEdgesZ[i];
  } else if (kinvarOption == "wPt2") {
    kinvarTitle = "p_{T}^{2}";
    for (Int_t i = 0; i < 5; i++) EdgesKinvar[i] = kEdgesPt2[i];
  }

  TString auxCut;
  TCut CutBin;

  /*** SET HISTOGRAMS ***/

  TH1D *dataHist;
  TH1D *bkgHist;
  TH1D *subHist;

  auxCut = Form("%f", EdgesKinvar[BinNumber]);
  auxCut += " < " + kinvarOption + " && " + kinvarOption + " < ";
  auxCut += Form("%f", EdgesKinvar[BinNumber+1]);
  CutBin = auxCut;

  std::cout << auxCut << std::endl;

  // prepare data
  dataTree->Draw("wD>>data" + histProperties, gCutDIS && CutBin && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle, "goff");
  dataHist = (TH1D *)gROOT->FindObject("data");

  dataHist->SetMarkerColor(kBlue + 3);
  dataHist->SetLineColor(kBlue + 3);
  dataHist->SetLineWidth(2);
  dataHist->SetFillStyle(0);

  // prepare bkg
  bkgTree->Draw("wD>>bkg" + histProperties, gCutDIS && CutBin && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle, "goff");
  bkgHist = (TH1D *)gROOT->FindObject("bkg");

  bkgHist->SetMarkerColor(kOrange + 7);
  bkgHist->SetLineColor(kOrange + 7);
  bkgHist->SetLineWidth(2);
  bkgHist->SetFillStyle(0);

  // prepare bkg subtraction
  subHist  = new TH1D("sub", "sub", plotNbins, plotMin, plotMax);

  subHist->SetMarkerColor(kOrange + 3);  // brown
  subHist->SetLineColor(kOrange + 3);    // brown
  subHist->SetLineWidth(2);
  subHist->SetFillStyle(0);
  
  // prepare title
  auxCut = Form("%.2f", EdgesKinvar[BinNumber]);
  auxCut += " < " + kinvarTitle + " < ";
  auxCut += Form("%.2f", EdgesKinvar[BinNumber + 1]);
  auxCut += ", " + targetOption + " data";
  dataHist->SetTitle(auxCut);
  dataHist->GetXaxis()->SetTitle("Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
  dataHist->GetYaxis()->SetTitle("Counts");
  
  // set y-axis
  dataHist->GetYaxis()->SetRangeUser(0 - 0.2*dataHist->GetMaximum(), 1.2*dataHist->GetMaximum());
  
  /*** SET CANVAS ***/
  
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  TCanvas *can1 = new TCanvas("event-mixing_one-bin", "event-mixing_one-bin", 1000, 1000);
  can1->Divide(2,2,0.001,0.001);
  
  // define pads
  TPad *p1[4];
  TPad *p2[4];

  for (Int_t pad_index = 0; pad_index < 4; pad_index++) {
    p1[pad_index]= new TPad(Form("upper%d", pad_index), Form("upper%d", pad_index), 0.1, 0.5, 0.9, 0.9, 0, 0, 0); // x1,y1,x2,y2
    p1[pad_index]->SetTopMargin(0);
    p1[pad_index]->SetBottomMargin(0);

    p2[pad_index] = new TPad(Form("lower%d", pad_index), Form("lower%d", pad_index), 0.1, 0.1, 0.9, 0.5, 0, 0, 0); // x1,y1,x2,y2
    p2[pad_index]->SetTopMargin(0);
  }
  
  /*** NORMALIZATION ***/
  
  Double_t dataNorm;
  dataNorm = dataHist->Integral(BinsForNormalization[0], BinsForNormalization[1]) + dataHist->Integral(BinsForNormalization[2], BinsForNormalization[3]);
  //dataNorm = dataHist->GetEntries();
  std::cout << "dataNorm = " << dataNorm << std::endl;
  
  Double_t bkgNorm;
  bkgNorm = bkgHist->Integral(BinsForNormalization[0], BinsForNormalization[1]) + bkgHist->Integral(BinsForNormalization[2], BinsForNormalization[3]);
  //bkgNorm = bkgHist->GetEntries();
  std::cout << "bkgNorm  = " << bkgNorm << std::endl;
  
  bkgHist->Scale(dataNorm / bkgNorm);

  /*** SUBTRACT ***/

  subHist->Add(dataHist, bkgHist, 1, -1);

  /*** FIT ***/

  // prepare initial guess values
  Double_t MeanIGV = 0.782;
  Double_t SigmaIGV = 0.024;
  
  // define variable
  RooRealVar x("x", "Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]", plotMin, plotMax);
  x.setRange("full", MeanIGV - 5 * SigmaIGV, MeanIGV + 5 * SigmaIGV);

  // define data set
  RooDataHist Data("data", "data", x, dataHist);
  RooDataHist Bkg("bkg", "bkg", x, bkgHist);
  RooDataHist Sub("sub", "sub", x, subHist);

  // define signal function
  RooRealVar mean("#mu(#omega)", "mean of gaussian", MeanIGV);//, 0.72, 0.84);
  RooRealVar sigma("#sigma(#omega)", "width of gaussian", SigmaIGV);//, 0.008, 0.035);
  RooGaussian gaus("signal", "omega signal", x, mean, sigma);
  
  // fix parameters
  mean.setConstant(kTRUE);
  sigma.setConstant(kTRUE);
 
  // define bkg function
  RooRealVar b1("b1", "linear term", 0., -20, 20);
  RooChebychev bkg("bkg", "background", x, RooArgList(b1));

  // model(x) = sig_yield*sig(x) + bkg_yield*bkg(x)
  RooRealVar nsig("N_{#omega}", "omega yields", 0., (Double_t)dataHist->GetEntries());
  RooRealVar nbkg("N_{b}", "bkg yields", 0., (Double_t)dataHist->GetEntries());
  RooAddPdf Model("model", "model", RooArgList(gaus, bkg), RooArgList(nsig, nbkg));

  // perform fit
  RooFitResult *result = Model.fitTo(Sub, Minos(kTRUE), Extended(), Save(), Range("full"));

  /*** DRAW ***/

  RooPlot *Frame = x.frame(Name("top"));
  Data.plotOn(Frame, Name("Data")); // DataError(RooAbsData::SumW2)
  Bkg.plotOn(Frame, Name("Bkg")); // DataError(RooAbsData::SumW2)

  RooPlot *Frame2 = x.frame(Name("bottom"));
  Sub.plotOn(Frame2, Name("Sub")); // DataError(RooAbsData::SumW2)
  Model.plotOn(Frame2, Name("Model"), LineColor(kMagenta));
  Model.plotOn(Frame2, Name("Model"), Components("bkg"), LineColor(kBlue));

  for (Int_t hola = 0; hola < 4; hola++) {
    can1->cd(hola+1);

    p1[hola]->Draw();
    p2[hola]->Draw();
    
    p1[hola]->cd();
    Frame->Draw();
    
    p2[hola]->cd();
    Frame2->Draw();

    can1->Update();
  }
  
  // legend
  TLegend *leg = new TLegend(0.15, 0.68, 0.45, 0.88);  // x1,y1,x2,y2
  leg->AddEntry(dataHist, "Data", "lp");
  leg->AddEntry(bkgHist, "Mixed Event Bkg", "lp");
  leg->AddEntry(subHist, "Bkg Subtracted", "lp");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(62);
  leg->Draw();
}
