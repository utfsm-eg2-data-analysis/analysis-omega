#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawHorizontalLine.cxx"

void EventMixingMC_Compare(TString setOption = "old", TString targetOption = "D", TString dirOption = "", TString kinvarOption = "mc_wD", Int_t CustomNormalization = 0) {
  // Compare event-mixing background formed from MC with MC.
  // kinvarOption can be wD, wD-f, wD-e
  
  /*** INPUT ***/

  TString SimDir = gWorkDir + "/out/FilterNCombine/" + setOption + "/" + targetOption;
  TString BkgDir = gWorkDir + "/out/EventMixing/" + setOption + "/" + targetOption;
  if (setOption == "jlab") {
    SimDir += "/" + dirOption;
    BkgDir += "/" + dirOption;
  }
  TChain *simTree = new TChain();
  simTree->Add(SimDir + "/*.root/mix");
  
  TChain *bkgTree = new TChain();
  bkgTree->Add(BkgDir + "/*_red_MC_sPip.root/mix");
  bkgTree->Add(BkgDir + "/*_red_MC_sPim.root/mix");
  bkgTree->Add(BkgDir + "/*_red_MC_sPi0.root/mix");
  bkgTree->Add(BkgDir + "/*_red_MC_sAll.root/mix");

  // necessary for gCutKaons
  SetAliases(simTree, 1);
  SetAliases(bkgTree, 1);
  
  TString titleAxis;
  TString histProperties;
  TString kinvarToPlot = kinvarOption;
  if (kinvarOption == "mc_wD") { // zoom over omegas
    titleAxis = "#Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(50, 0.65, 0.90)";
  } else if (kinvarOption == "mc_wD-e") { // zoom over etas
    kinvarToPlot = "mc_wD";
    titleAxis = "#Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(40, 0.45, 0.65)";
  } else if (kinvarOption == "mc_wD-f") { // full spectrum
    kinvarToPlot = "mc_wD";
    titleAxis = "#Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(500, 0., 2.5)";
  }
  
  /*** MAIN ***/

  TH1D *simHist;
  simTree->Draw(kinvarToPlot + ">>sim" + histProperties, gCutDIS_MC && gCutPi0_MC && gCutKaons_MC && gCutPhotonsOpAngle_MC,
		 "goff");
  simHist = (TH1D *)gROOT->FindObject("sim");

  simHist->GetXaxis()->SetTitle(titleAxis);
  simHist->GetXaxis()->CenterTitle();
  simHist->GetYaxis()->SetTitle("Counts");
  simHist->GetYaxis()->CenterTitle();
  simHist->GetYaxis()->SetMaxDigits(3);

  simHist->SetMarkerColor(kBlack);
  simHist->SetLineColor(kBlack);
  simHist->SetLineWidth(2);
  simHist->SetFillStyle(0);
  
  TH1D *bkgHist;
  bkgTree->Draw(kinvarToPlot + ">>bkg" + histProperties, gCutDIS_MC && gCutPi0_MC && gCutKaons_MC && gCutPhotonsOpAngle_MC,
		"goff");
  bkgHist = (TH1D *)gROOT->FindObject("bkg");

  bkgHist->SetMarkerColor(kRed);
  bkgHist->SetLineColor(kRed);
  bkgHist->SetLineWidth(2);
  bkgHist->SetFillStyle(0);
  
  // define canvas  
  TCanvas *c = new TCanvas("evnt-mixing-mc_comparison_" + targetOption, "c");
  gStyle->SetOptStat(0);
  c->SetGrid();

  /*** NORMALIZATION ***/

  Int_t BinsForNormalization[4];
  if (kinvarOption == "mc_wD") {
    BinsForNormalization[0] = 1;
    BinsForNormalization[1] = 15;
    BinsForNormalization[2] = 35;
    BinsForNormalization[3] = 50;
  } else if (kinvarOption == "mc_wD-f") {
    BinsForNormalization[0] = 60;
    BinsForNormalization[1] = 73;
    BinsForNormalization[2] = 87;
    BinsForNormalization[3] = 97;
  } else if (kinvarOption == "mc_wD-e") {
    BinsForNormalization[0] = 1;
    BinsForNormalization[1] = 5;
    BinsForNormalization[2] = 15;
    BinsForNormalization[3] = 20;
  }

  if (CustomNormalization) {    
    Double_t simNorm = simHist->Integral(BinsForNormalization[0], BinsForNormalization[1]) + simHist->Integral(BinsForNormalization[2], BinsForNormalization[3]);
    std::cout << "simNorm = " << simNorm << std::endl;

    Double_t bkgNorm = bkgHist->Integral(BinsForNormalization[0], BinsForNormalization[1]) + bkgHist->Integral(BinsForNormalization[2], BinsForNormalization[3]);
    std::cout << "bkgNorm  = " << bkgNorm << std::endl;
    bkgHist->Scale((Double_t)simNorm / (Double_t)bkgNorm);

    simHist->Draw("E");
    bkgHist->Draw("E SAME");
  } else {
    simHist->DrawNormalized("E");
    bkgHist->DrawNormalized("E SAME");
  }

  TLegend *legend0 = new TLegend(0.15, 0.7, 0.35, 0.8); // x1,y1,x2,y2
  legend0->AddEntry(simHist, "MC", "lp");
  legend0->AddEntry(bkgHist, "Event-Mixing Bkg.", "lp");
  legend0->SetBorderSize(0);
  legend0->SetFillStyle(0);
  legend0->SetTextFont(62);
  legend0->Draw();
  
  c->Draw();
}
