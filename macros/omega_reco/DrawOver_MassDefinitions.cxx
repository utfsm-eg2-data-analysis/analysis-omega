#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void DrawOver_MassDefinitions(TString StoreOption = "") {
  // Draw both Invariant Mass and Invariant Mass Difference of the reconstructed omega

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain = GetThreePionFinderChain("All", "data");
  TCut CutVertex = gCutLiquid || gCutSolid;
  SetAliases(dataChain);

  /*** MAIN ***/

  // define the same properties for both histograms
  TString histProperties = "(120, 0.4, 2.6)";

  TH1D *theHistMassDiff;
  dataChain->Draw("wD>>imd" + histProperties, gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  theHistMassDiff = (TH1D *)gROOT->FindObject("imd");

  // style
  SetMyHistStyle(theHistMassDiff);
  theHistMassDiff->SetLineColor(myRed);
  theHistMassDiff->SetLineWidth(3);
  theHistMassDiff->GetYaxis()->SetTitle("Counts");
  theHistMassDiff->GetXaxis()->SetTitle("Reconstructed Mass [GeV]");

  TH1D *theHistInvMass;
  dataChain->Draw("wM>>im" + histProperties, gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  theHistInvMass = (TH1D *)gROOT->FindObject("im");

  // style
  SetMyHistStyle(theHistInvMass);
  theHistInvMass->SetLineColor(myBlack);
  theHistInvMass->SetLineWidth(3);

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "omega-mass-definitions_data";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  theHistMassDiff->Draw("HIST");
  theHistInvMass->Draw("SAME E");

  // draw pdg mass
  DrawVerticalLine(0.782, myViolet, 7, 3, 1);
  DrawVerticalLine(0.548, myOrange, 7, 3, 1);

  TLegend *l = new TLegend(0.45, 0.75, 0.85, 0.9);  // x1,y1,x2,y2
  l->AddEntry(theHistInvMass, "m(#pi^{+}#pi^{-}#pi^{0})", "le");
  l->AddEntry(theHistMassDiff, "#Deltam(#pi^{+}#pi^{-}#pi^{0}) = m(#pi^{+}#pi^{-}#pi^{0}) - m(#gamma#gamma) + M(#pi^{0})", "l");
  l->SetFillStyle(0);
  l->SetTextFont(42);
  l->SetTextSize(0.022);
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
