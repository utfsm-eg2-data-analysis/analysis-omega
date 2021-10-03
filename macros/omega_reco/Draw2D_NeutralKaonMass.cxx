#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

// hardcoded fit results from "DrawFit_NeutralKaonMass.cxx"
const Double_t fitMeanValue = 0.247;   // GeV
const Double_t fitSigmaValue = 0.014;  // GeV

void Draw2D_NeutralKaonMass(TString StoreOption = "") {
  // Draw "some-kind-of" Dalitz plot between m(pi+pi-) and m(pi+pi0)

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain = GetThreePionFinderChain("All", "data");
  TCut CutVertex = gCutSolid || gCutLiquid;
  SetAliases(dataChain);  // define "pippimM" and "pippi0M" as variables

  /*** 2D HISTOGRAM ***/

  TH2D *theDalitzHist;
  dataChain->Draw("pippimM*pippimM:pippi0M*pippi0M>>dalitz(120, 0.0, 1.2, 120, 0.0, 1.2)", gCutDIS && CutVertex && gCutRegion && gCutPi0,
                  "goff");
  theDalitzHist = (TH2D *)gROOT->FindObject("dalitz");

  // style
  SetMy2DHistStyle(theDalitzHist);
  theDalitzHist->GetYaxis()->SetTitle("Reconstructed Mass m^{2}(#pi^{+}#pi^{-}) [GeV^{2}]");
  theDalitzHist->GetXaxis()->SetTitle("Reconstructed Mass m^{2}(#pi^{+}#pi^{0}) [GeV^{2}]");

  /*** DRAW ***/

  SetMy2DStyle();

  TString CanvasName = "2d-kaons-exclusion_data";
  TCanvas *can1 = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  theDalitzHist->Draw("COLZ");

  // customize size of palette axis
  CustomizePaletteSize(theDalitzHist);

  // draw horizontal lines to represent 1sigma cut
  DrawHorizontalLine(fitMeanValue - 1 * fitSigmaValue, myCyan, 9, 4, 0);
  DrawHorizontalLine(fitMeanValue + 1 * fitSigmaValue, myCyan, 9, 4, 0);

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_reco";
    system("mkdir -p " + OutputDir);
    can1->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
