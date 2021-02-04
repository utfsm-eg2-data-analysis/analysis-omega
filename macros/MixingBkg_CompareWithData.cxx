#include "Global.h"
#include "DrawHorizontalLine.cxx"
#include "LoadStyle.cxx"

void MixingBkg_CompareWithData(TString kinvarOption = "wD") {
  // Work in progress...

  /*** INPUT OPTIONS ***/
  
  TString bkgFile = gProDir + "/MixingBkg/bin/bkgmixC_42011_red.root";
  // TString bkgFile = gProDir + "/MixingBkg/out/bkgmixC_data_red_v2.root";
  TChain *bkgTree = new TChain();
  bkgTree->Add(bkgFile + "/mix");

  TString dataFile = gProDir + "/FilterNCombine/out/comb_data-C.root";
  TChain *dataTree = new TChain();
  dataTree->Add(dataFile + "/mix");

  LoadStyle();

  TString titleAxis;
  TString histProperties;
  if (kinvarOption == "wM") {
    titleAxis = "Reconstructed M(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(150, 0., 2.5.)";
  } else if (kinvarOption == "wD") {
    titleAxis = "Reconstructed #Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(250, 0., 2.5)";
    // histProperties = "(32, 0.7, 0.86)";
    // histProperties = "(80, 0.6, 1.0)";
  } else if (kinvarOption == "Q2") {
    titleAxis = "Q^{2} [GeV^{2}]";
    histProperties = "(200, 1., 4.)";  
  } else if (kinvarOption == "Nu") {
    titleAxis = "#nu [GeV]";
    histProperties = "(200, 2.2, 4.2)";
  } else if (kinvarOption == "wZ") {
    titleAxis = "Z_{h}";
    histProperties = "(120, 0., 1.2)";
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
  dataTree->Draw(kinvarOption + ">>data" + histProperties, gCutDIS && gCutPi0 && "TargType == 2" && gCutRegion,
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
  bkgTree->Draw(kinvarOption + ">>bkg" + histProperties, gCutDIS && gCutPi0 && "TargType == 2" && gCutRegion,
		"goff");
  bkgHist = (TH1D *)gROOT->FindObject("bkg");

  bkgHist->SetMarkerColor(kRed);
  bkgHist->SetLineColor(kRed);
  bkgHist->SetLineWidth(2);
  bkgHist->SetFillStyle(0);

  TCanvas *c = new TCanvas("comparison-mixing-bkg", "c");
  gStyle->SetOptStat(0);
  c->SetGrid();

  /*** Normalization ***/

  Double_t dataNorm = dataHist->Integral(85, 100);
  std::cout << "dataNorm = " << dataNorm << std::endl;
  dataHist->Scale(1./dataNorm);
  
  Double_t bkgNorm = bkgHist->Integral(85, 100);
  std::cout << "bkgNorm  = " << bkgNorm << std::endl;
  bkgHist->Scale(1./bkgNorm);
  
  dataHist->Draw("E");
  bkgHist->Draw("E SAME");
  /*
  dataHist->DrawNormalized("E");
  bkgHist->DrawNormalized("E SAME");
  */
  TLegend *legend0 = new TLegend(0.65, 0.65, 0.8, 0.8); // x1,y1,x2,y2
  legend0->AddEntry(dataHist, "Data", "lp");
  legend0->AddEntry(bkgHist, "Mixed Bkg", "lp");
  legend0->Draw();
  
  c->Draw();
  
  /*** Subtraction ***/
  /*
  TH1D *signalHist = new TH1D("signal", "signal", 100, 0., 2.5);
  signalHist->Add(dataHist, bkgHist, 1, -1);
  signalHist->Scale(dataNorm);

  signalHist->GetXaxis()->SetTitle("Reconstructed #Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]");
  signalHist->GetXaxis()->CenterTitle();
  signalHist->GetYaxis()->SetTitle("Candidates");
  signalHist->GetYaxis()->CenterTitle();
  signalHist->GetYaxis()->SetMaxDigits(3);
  
  TCanvas *c1 = new TCanvas("subtract-mixing-bkg", "c1");
  c1->SetGrid();
  
  signalHist->SetMarkerColor(kOrange+7);
  signalHist->SetLineColor(kOrange+7);
  signalHist->SetLineWidth(2);
  signalHist->SetFillStyle(0);
  
  signalHist->Draw("E");

  DrawHorizontalLine(0.);

  TLegend *legend1 = new TLegend(0.65, 0.65, 0.8, 0.8); // x1,y1,x2,y2
  legend1->AddEntry(signalHist, "Data - Mixed Bkg", "lp");
  legend1->Draw();
  
  c1->Draw();
  
  Double_t omegaNumber = signalHist->Integral(27, 36);
  std::cout << "omegaNumber = " << omegaNumber << std::endl;
  */
}
