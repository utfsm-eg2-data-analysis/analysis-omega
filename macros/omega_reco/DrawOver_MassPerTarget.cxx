#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void DrawOver_MassPerTarget(TString kinvarOption = "wD", TString StoreOption = "") {
  // Draw an overlay of the invariant mass or inv. mass diff. of omega for all targets

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain_D = GetThreePionFinderChain("D");
  SetAliases(dataChain_D);

  TChain *dataChain_C = GetThreePionFinderChain("C");
  SetAliases(dataChain_C);

  TChain *dataChain_Fe = GetThreePionFinderChain("Fe");
  SetAliases(dataChain_Fe);

  TChain *dataChain_Pb = GetThreePionFinderChain("Pb");
  SetAliases(dataChain_Pb);

  TString titleAxis;
  if (kinvarOption == "wD") {
    titleAxis = "Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]";
  } else if (kinvarOption == "wM") {
    titleAxis = "Reconstructed Mass m(#pi^{+}#pi^{-}#pi^{0}) [GeV]";
  }
  TString histProperties = "(150, 0.4, 1.9)";

  /*** MAIN ***/

  TH1D *theHist_D;
  dataChain_D->Draw(kinvarOption + ">>histD" + histProperties, gCutLiquid && gCutDIS && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  theHist_D = (TH1D *)gROOT->FindObject("histD");

  SetMyHistStyle(theHist_D);
  theHist_D->SetLineColor(myGreen);
  theHist_D->SetLineWidth(3);
  theHist_D->GetXaxis()->SetTitle(titleAxis);
  theHist_D->GetYaxis()->SetTitle("Counts");

  TH1F *theHist_Fe;
  dataChain_Fe->Draw(kinvarOption + ">>histFe" + histProperties, gCutSolid && gCutDIS && gCutPi0 && gCutPhotonsOpAngle && gCutKaons,
                     "goff");
  theHist_Fe = (TH1F *)gROOT->FindObject("histFe");

  theHist_Fe->SetFillStyle(0);
  theHist_Fe->SetLineColor(myBlue);
  theHist_Fe->SetLineWidth(3);

  TH1F *theHist_C;
  dataChain_C->Draw(kinvarOption + ">>histC" + histProperties, gCutSolid && gCutDIS && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  theHist_C = (TH1F *)gROOT->FindObject("histC");

  theHist_C->SetFillStyle(0);
  theHist_C->SetLineColor(myRed);
  theHist_C->SetLineWidth(3);

  TH1F *theHist_Pb;
  dataChain_Pb->Draw(kinvarOption + ">>histPb" + histProperties, gCutSolid && gCutDIS && gCutPi0 && gCutPhotonsOpAngle && gCutKaons,
                     "goff");
  theHist_Pb = (TH1F *)gROOT->FindObject("histPb");

  theHist_Pb->SetFillStyle(0);
  theHist_Pb->SetLineColor(myBlack);
  theHist_Pb->SetLineWidth(3);

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "omega-" + kinvarOption + "-all-targets_data";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  theHist_D->Draw("HIST");
  theHist_Fe->Draw("SAME HIST");
  theHist_Pb->Draw("SAME HIST");
  theHist_C->Draw("SAME HIST");

  // draw pdg mass
  DrawVerticalLine(0.782, myViolet, 7, 3, 1);
  DrawVerticalLine(0.548, myOrange, 7, 3, 1);

  TLegend *l = new TLegend(0.75, 0.65, 0.95, 0.85);  // x1,y1,x2,y2
  l->AddEntry(theHist_D, "D", "l");
  l->AddEntry(theHist_Fe, "Fe", "l");
  l->AddEntry(theHist_C, "C", "l");
  l->AddEntry(theHist_Pb, "Pb", "l");
  l->SetFillStyle(0);
  l->SetTextFont(62);
  l->SetTextSize(0.04);
  l->SetBorderSize(0);
  l->Draw();

  c->Draw();

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_reco";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
