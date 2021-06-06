#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

void MakePlots(TString targetOption, TString kinvarOption) {

  /*** INPUT ***/

  TCut CutVertex;
  TString inputFile1, inputFile2, inputFile3;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
    inputFile1 = gDataDir + "/C/*.root";
    inputFile2 = gDataDir + "/Fe/*.root";
    inputFile3 = gDataDir + "/Pb/*.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    inputFile1 = gDataDir + "/" + targetOption + "/comb_data-" + targetOption + ".root";
  }
  
  TString titleAxis, histProperties;
  if (kinvarOption == "wM") {
    titleAxis = "Reconstructed M(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(150, 0., 2.5.)";
  } else if (kinvarOption == "wD") {
    titleAxis = "Reconstructed #Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(150, 0., 2.5)";
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
  } else if (kinvarOption == "pippimM") {
    titleAxis = "Reconstructed M(#pi+#pi-) [GeV]";
    histProperties = "(140, 0, 1.4)";
  }

  /*** MAIN ***/
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  SetAliases(treeExtracted); // necessary for gCutKaons
  
  TH1D *theHist;
  treeExtracted->Draw(kinvarOption + ">>hist" + histProperties, gCutDIS && CutVertex && gCutPi0 && gCutRegion && gCutKaons,
		      "goff");
  theHist = (TH1D *)gROOT->FindObject("hist");
  
  theHist->GetXaxis()->SetTitle(titleAxis);
  theHist->GetXaxis()->CenterTitle();
  theHist->GetYaxis()->SetTitle("Candidates");
  theHist->GetYaxis()->SetMaxDigits(3);
  theHist->GetYaxis()->CenterTitle();

  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(2);
  
  TCanvas *c = new TCanvas("data-" + targetOption + "_" + kinvarOption, "c"); 
  c->SetGrid();
  gStyle->SetOptStat(1110);
  
  theHist->Draw("HIST");

  c->Draw();
}
