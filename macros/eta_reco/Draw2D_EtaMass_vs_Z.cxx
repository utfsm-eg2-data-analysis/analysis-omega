#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void Draw2D_EtaMass_vs_Z(TString StoreOption = "") {
  // Draw Eta mass vs Z, to demostrate why z > 0.5

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  TChain *dataChain = GetTwoGammaFinderChain("All");
  SetAliasesEta(dataChain);

  TCut CutVertex = gCutSolid || gCutLiquid;

  /*** HIST 2D ***/

  TH2D *theHist;
  dataChain->Draw("nM:nZ>>hist(100, 0.0, 1., 150, 0.25, 1.25)",
                  gCutDIS && CutVertex && gCutPhotonsOpAngle && "Q2 < 4.1 && Nu > 2.2 && Nu < 4.25 && nPt2 > 0 && nPt2 < 1.5", "goff");
  theHist = (TH2D *)gROOT->FindObject("hist");

  // style
  SetMy2DHistStyle(theHist);
  theHist->GetYaxis()->SetTitle("Reconstructed Mass m(#gamma#gamma) [GeV]");
  theHist->GetXaxis()->SetTitle("z_{h}");

  /*** DRAW ***/

  SetMy2DStyle();
  gStyle->SetOptLogz(1);

  TString CanvasName = "eta-mass_vs_z_data";
  TCanvas *can = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  theHist->Draw("COLZ");

  // customize size of palette axis
  CustomizePaletteSize(theHist);

  DrawVerticalLine(0.5, myCyan, 9, 3, 1);

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_reco";
    system("mkdir -p " + OutputDir);
    can->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
