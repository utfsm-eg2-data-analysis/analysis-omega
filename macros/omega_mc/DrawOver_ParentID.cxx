#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef ACCEPTANCE_H
#include "Acceptance.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void DrawOver_ParentID(TString StoreOption = "") {
  // Draw both Invariant Mass Difference of the generated omegas, with and without parent-id cuts

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *mcChain = GetThreePionFinderChain("C", "sim");

  /*** MAIN ***/

  TString histProperties = "(240, 0.4, 1.6)";

  TH1D *histNoParentID;
  mcChain->Draw("mc_wD>>hist1" + histProperties, gCutDIS_MC, "goff");
  histNoParentID = (TH1D *)gROOT->FindObject("hist1");

  SetMyHistStyle(histNoParentID);
  histNoParentID->SetLineColor(myBlack);
  histNoParentID->SetLineWidth(3);
  histNoParentID->GetYaxis()->SetTitle("Counts");
  histNoParentID->GetYaxis()->SetTitleOffset(1.5);
  histNoParentID->GetXaxis()->SetTitle("#Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");

  TH1D *histWithParentID;
  mcChain->Draw("mc_wD>>hist2" + histProperties, gCutDIS_MC && gCutParentID_Omega, "goff");
  histWithParentID = (TH1D *)gROOT->FindObject("hist2");

  SetMyHistStyle(histWithParentID);
  histWithParentID->SetLineColor(myMagenta);
  histWithParentID->SetLineWidth(3);

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "mc-omega-parent-id";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  histNoParentID->Draw("E");
  histWithParentID->Draw("SAME HIST");

  TLegend *l = new TLegend(0.55, 0.75, 0.9, 0.9);  // x1,y1,x2,y2
  l->AddEntry(histNoParentID, "No Parent ID cuts", "l");
  l->AddEntry(histWithParentID, "With Parent ID cuts", "l");
  l->SetFillStyle(0);
  l->SetTextFont(42);
  l->SetTextSize(0.026);
  l->SetBorderSize(0);
  l->Draw();

  c->Draw();

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_mc";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
