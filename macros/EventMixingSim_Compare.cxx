#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawHorizontalLine.cxx"

void EventMixingSim_Compare(TString setOption = "old", TString targetOption = "D", TString dirOption = "", TString kinvarOption = "wD", Int_t CustomNormalization = 0) {
  // Compare event-mixing background formed from simulations reconstructed with sim. rec.
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
  bkgTree->Add(BkgDir + "/*_red_sPip.root/mix");
  bkgTree->Add(BkgDir + "/*_red_sPim.root/mix");
  bkgTree->Add(BkgDir + "/*_red_sPi0.root/mix");
  bkgTree->Add(BkgDir + "/*_red_sAll.root/mix");
  
  // necessary for gCutKaons
  SetAliases(simTree);
  SetAliases(bkgTree);
  
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

  TH1D *simHist;
  simTree->Draw(kinvarToPlot + ">>sim" + histProperties, gCutDIS && gCutPi0 && gCutRegion && gCutKaons && gCutPhotonsOpAngle,
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
  bkgTree->Draw(kinvarToPlot + ">>bkg" + histProperties, gCutDIS && gCutPi0 && gCutRegion && gCutKaons && gCutPhotonsOpAngle,
		"goff");
  bkgHist = (TH1D *)gROOT->FindObject("bkg");

  bkgHist->SetMarkerColor(kRed);
  bkgHist->SetLineColor(kRed);
  bkgHist->SetLineWidth(2);
  bkgHist->SetFillStyle(0);
  
  // define canvas  
  TCanvas *c = new TCanvas("evnt-mixing-sim_comparison_" + targetOption, "c");
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
    Double_t simNorm = simHist->Integral(BinsForNormalization[0], BinsForNormalization[1]) + simHist->Integral(BinsForNormalization[2], BinsForNormalization[3]);
    std::cout << "simNorm = " << simNorm << std::endl;

    Double_t bkgNorm = bkgHist->Integral(BinsForNormalization[0], BinsForNormalization[1]) + bkgHist->Integral(BinsForNormalization[2], BinsForNormalization[3]);
    std::cout << "bkgNorm  = " << bkgNorm << std::endl;
    bkgHist->Scale(simNorm / bkgNorm);
        
    simHist->Draw("E");
    bkgHist->Draw("E SAME");
  } else {
    simHist->DrawNormalized("E");
    bkgHist->DrawNormalized("E SAME");
  }

  TLegend *legend0 = new TLegend(0.15, 0.7, 0.35, 0.8); // x1,y1,x2,y2
  legend0->AddEntry(simHist, "Sim. Rec.", "lp");
  legend0->AddEntry(bkgHist, "Event-Mixing Bkg", "lp");
  legend0->SetBorderSize(0);
  legend0->SetFillStyle(0);
  legend0->SetTextFont(62);
  legend0->Draw();
  
  c->Draw();
}
