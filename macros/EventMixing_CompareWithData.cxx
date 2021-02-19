#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawHorizontalLine.cxx"
#include "LoadStyle.cxx"

void EventMixing_CompareWithData(TString targetOption = "D", TString kinvarOption = "wD", Int_t CustomNormalization = 0) {

  /*** INPUT ***/

  TString dataFile1, dataFile2, dataFile3;
  TString bkgFile1, bkgFile2, bkgFile3;
  TString BkgDir = gProDir + "/FilterNCombine_mix/out";
  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
    dataFile1 = gDataDir + "/comb_data-C.root";
    dataFile2 = gDataDir + "/comb_data-Fe.root";
    dataFile3 = gDataDir + "/comb_data-Pb.root";
    bkgFile1 = BkgDir + "/bkgmixC.root";
    bkgFile2 = BkgDir + "/bkgmixFe.root";
    bkgFile3 = BkgDir + "/bkgmixPb.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    dataFile1 = gDataDir + "/comb_data-" + targetOption + ".root";
    bkgFile1 = BkgDir + "/bkgmix" + targetOption + ".root";
  }

  TChain *dataTree = new TChain();
  dataTree->Add(dataFile1 + "/mix");
  dataTree->Add(dataFile2 + "/mix");
  dataTree->Add(dataFile3 + "/mix");
  
  TChain *bkgTree = new TChain();
  bkgTree->Add(bkgFile1 + "/mix");
  bkgTree->Add(bkgFile2 + "/mix");
  bkgTree->Add(bkgFile3 + "/mix");
  
  // necessary for gCutKaons
  SetAliases(dataTree);
  SetAliases(bkgTree);
  
  LoadStyle();

  TString titleAxis;
  TString histProperties;
  TString kinvarToPlot = kinvarOption;
  if (kinvarOption == "wM") {
    titleAxis = "Reconstructed M(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(150, 0., 2.5.)";
  } else if (kinvarOption == "wD") { // zoom over omegas
    titleAxis = "Reconstructed #Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(25, 0.65, 0.90)";
  } else if (kinvarOption == "wD-e") { // zoom over etas
    kinvarToPlot = "wD";
    titleAxis = "Reconstructed #Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(20, 0.45, 0.65)";
  } else if (kinvarOption == "wD-f") { // full spectrum
    kinvarToPlot = "wD";
    titleAxis = "Reconstructed #Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(250, 0., 2.5)";
  } else if (kinvarOption == "Q2") {
    titleAxis = "Q^{2} [GeV^{2}]";
    histProperties = "(200, 1., 4.)";  
  } else if (kinvarOption == "Nu") {
    titleAxis = "#nu [GeV]";
    histProperties = "(200, 2.2, 4.2)";
  } else if (kinvarOption == "wZ") {
    titleAxis = "Z_{h}";
    histProperties = "(100, 0.4, 0.9)";
  } else if (kinvarOption == "wPt2") {
    titleAxis = "p_{T}^{2} [GeV^{2}]";
    histProperties = "(150, 0., 1.5)";
  } else if (kinvarOption == "wPhiPQ") {
    titleAxis = "#phi_{PQ} (degrees)";
    histProperties = "(120, -180, 180.)";
  } else if (kinvarOption == "pi0M") {
    titleAxis = "Reconstructed M(#gamma#gamma) [GeV]";
    histProperties = "(160, 0, 1.6)";
  }

  /*** MAIN ***/

  TH1D *dataHist;
  dataTree->Draw(kinvarToPlot + ">>data" + histProperties, gCutDIS && gCutPi0 && CutVertex && gCutRegion && gCutKaons && gCutPhotonsOpAngle,
		 "goff");
  dataHist = (TH1D *)gROOT->FindObject("data");

  dataHist->GetXaxis()->SetTitle(titleAxis);
  dataHist->GetXaxis()->CenterTitle();
  dataHist->GetYaxis()->SetTitle("Normalized Candidates");
  dataHist->GetYaxis()->CenterTitle();
  dataHist->GetYaxis()->SetMaxDigits(3);

  dataHist->SetMarkerColor(kBlack);
  dataHist->SetLineColor(kBlack);
  dataHist->SetLineWidth(2);
  dataHist->SetFillStyle(0);
  
  TH1D *bkgHist;
  bkgTree->Draw(kinvarToPlot + ">>bkg" + histProperties, gCutDIS && gCutPi0 && CutVertex && gCutRegion && gCutKaons && gCutPhotonsOpAngle,
		"goff");
  bkgHist = (TH1D *)gROOT->FindObject("bkg");

  bkgHist->SetMarkerColor(kRed); // kOrange+7);
  bkgHist->SetLineColor(kRed); // kOrange+7);
  bkgHist->SetLineWidth(2);
  bkgHist->SetFillStyle(0);
  
  // define canvas  
  TCanvas *c = new TCanvas("evnt-mixing_comparison_" + targetOption, "c");
  gStyle->SetOptStat(0);
  c->SetGrid();

  /*** NORMALIZATION ***/

  Int_t BinsForNormalization[4];
  if (kinvarOption == "wD") {
    BinsForNormalization[0] = 1;
    BinsForNormalization[1] = 5;
    BinsForNormalization[2] = 20;
    BinsForNormalization[3] = 25;
  } else if (kinvarOption == "wD-f") {
    BinsForNormalization[0] = 60;
    BinsForNormalization[1] = 73;
    BinsForNormalization[2] = 87;
    BinsForNormalization[3] = 97;
  } else if (kinvarOption == "wD-e") {
    BinsForNormalization[0] = 1;
    BinsForNormalization[1] = 5;
    BinsForNormalization[2] = 15;
    BinsForNormalization[3] = 20;
  }

  if (CustomNormalization) {    
    Double_t dataNorm = dataHist->Integral(BinsForNormalization[0], BinsForNormalization[1]) + dataHist->Integral(BinsForNormalization[2], BinsForNormalization[3]);
    std::cout << "dataNorm = " << dataNorm << std::endl;

    Double_t bkgNorm = bkgHist->Integral(BinsForNormalization[0], BinsForNormalization[1]) + bkgHist->Integral(BinsForNormalization[2], BinsForNormalization[3]);
    std::cout << "bkgNorm  = " << bkgNorm << std::endl;
    bkgHist->Scale(dataNorm / bkgNorm);
        
    dataHist->Draw("E");
    bkgHist->Draw("E SAME");
  } else {
    dataHist->DrawNormalized("E");
    bkgHist->DrawNormalized("E SAME");
  }

  TLegend *legend0 = new TLegend(0.6, 0.6, 0.8, 0.9); // x1,y1,x2,y2
  legend0->AddEntry(dataHist, "Data", "lp");
  legend0->AddEntry(bkgHist, "Bkg", "lp");
  legend0->Draw();
  
  c->Draw();
}
