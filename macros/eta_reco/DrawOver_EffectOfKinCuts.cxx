#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void DrawOver_EffectOfKinCuts(TString StoreOption = "") {
  // Draw an overlay of the invariant mass of eta without and with applying the Kinematical Limits

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *chainData = GetTwoGammaFinderChain("All");
  SetAliasesEta(chainData);

  /*** HISTOGRAM ***/

  TCut CutVertex = gCutLiquid || gCutSolid;

  TString titleAxis = "Reconstructed Mass m(#gamma#gamma) [GeV]";
  TString histProperties = "(150, 0., 1.)";

  TH1D *theHistMassDiff;
  chainData->Draw("nM>>nocut" + histProperties, gCutDIS && CutVertex && gCutPhotonsOpAngle, "goff");
  theHistMassDiff = (TH1D *)gROOT->FindObject("nocut");

  // style
  SetMyHistStyle(theHistMassDiff);
  theHistMassDiff->SetLineWidth(3);
  theHistMassDiff->SetLineColor(myBlack);
  theHistMassDiff->GetXaxis()->SetTitle(titleAxis);
  theHistMassDiff->GetYaxis()->SetTitle("Counts");

  TH1D *theHistInvMass;
  chainData->Draw("nM>>withcut" + histProperties, gCutDIS && CutVertex && gCutPhotonsOpAngle && gCutRegion_Eta, "goff");
  theHistInvMass = (TH1D *)gROOT->FindObject("withcut");

  theHistInvMass->SetFillStyle(0);
  theHistInvMass->SetLineColor(myRed);
  theHistInvMass->SetLineWidth(3);

  TH1D *etaCandidates;
  chainData->Draw("nM>>etas" + histProperties, gCutDIS && CutVertex && gCutPhotonsOpAngle && gCutRegion_Eta && "nM > 0.4 && nM < 0.72",
                  "goff");
  etaCandidates = (TH1D *)gROOT->FindObject("etas");

  etaCandidates->SetLineWidth(0);  // don't appear in empty bins
  etaCandidates->SetFillStyle(1001);
  etaCandidates->SetFillColor(myOrange);
  etaCandidates->SetLineColor(myOrange);

  /*** DRAW ***/

  SetMyStyle();
  gStyle->SetOptLogy(1);

  TString CanvasName = "eta-mass-comparison_data";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  theHistMassDiff->Draw("HIST");
  etaCandidates->Draw("SAME HIST");
  theHistInvMass->Draw("SAME HIST");

  TLegend *l = new TLegend(0.5, 0.75, 0.9, 0.9);  // x1,y1,x2,y2
  l->AddEntry(theHistMassDiff, "All #gamma pairs", "l");
  l->AddEntry(theHistInvMass, "All #gamma pairs with Kinematical Limits", "l");
  l->SetFillStyle(0);
  l->SetTextFont(42);
  l->SetTextSize(0.022);
  l->SetBorderSize(0);
  l->Draw();

  TPaveText *pav = new TPaveText(0.5, 0.2, 0.7, 0.45, "NDC NB");  // no border
  pav->AddText("#eta candidates");
  pav->SetTextColor(kWhite);
  pav->SetFillStyle(0);
  pav->SetLineWidth(0);
  pav->Draw();

  c->Draw();

  // draw axis over solid hist
  gPad->RedrawAxis();

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_reco";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
