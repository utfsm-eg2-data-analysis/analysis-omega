#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void Draw2D_VertexCorr(TString StoreOption = "") {
  // Draw z vs PhiLab, and z_corr vs PhiLab to check effect of electron vertex corrections (on C data)

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *InputChain = GetTestsChain("no-vertex");

  // before corr
  TH2D *Hist_Before;
  InputChain->Draw("vze:PhiLab>>hist_before(180, -30., 330., 100, -33, -23.)", "", "goff");
  Hist_Before = (TH2D *)gROOT->FindObject("hist_before");

  // style
  SetMy2DHistStyle(Hist_Before);
  Hist_Before->SetTitle("Before electron vertex correction");
  Hist_Before->GetYaxis()->SetTitle("z [cm]");
  Hist_Before->GetYaxis()->SetLabelSize(0.03);
  Hist_Before->GetXaxis()->SetTitle("#phi_{lab} [deg]");
  Hist_Before->GetXaxis()->SetLabelSize(0.03);

  Hist_Before->GetZaxis()->SetMaxDigits(3);
  Hist_Before->GetZaxis()->SetLabelSize(0.03);

  // after corr
  TH2D *Hist_After;
  InputChain->Draw("vzec:PhiLab>>hist_after(180, -30., 330., 100, -33, -23.)", "", "goff");
  Hist_After = (TH2D *)gROOT->FindObject("hist_after");

  // style
  SetMy2DHistStyle(Hist_After);
  Hist_After->SetTitle("After electron vertex correction");
  Hist_After->GetYaxis()->SetTitle("z^{corr} [cm]");
  Hist_After->GetYaxis()->SetLabelSize(0.03);
  Hist_After->GetXaxis()->SetTitle("#phi_{lab} [deg]");
  Hist_After->GetXaxis()->SetLabelSize(0.03);

  Hist_After->GetZaxis()->SetMaxDigits(3);
  Hist_After->GetZaxis()->SetLabelSize(0.03);

  /*** DRAW ***/

  SetMy2DStyle();
  gStyle->SetTitleFontSize(0.04);

  // define canvas
  const Int_t Nx = 2;
  const Int_t Ny = 1;
  TString CanvasName = "vertex-correction_data";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 1080);
  c->Divide(Nx, Ny, 0.001, 0.001);

  c->SetFrameLineWidth(2);

  c->cd(1);
  Hist_Before->Draw("COLZ");

  CustomizePaletteSize(Hist_Before);

  gPad->RedrawAxis();

  c->cd(2);
  Hist_After->Draw("COLZ");

  CustomizePaletteSize(Hist_After);

  // IMPORTANT: these cuts are only valid for "C" data!!
  DrawHorizontalLine(-31.80, myCyan, 7, 5, 2);
  DrawHorizontalLine(-28.40, myCyan, 7, 5, 2);
  DrawHorizontalLine(-25.33, myCyan, 7, 5, 2);
  DrawHorizontalLine(-24.10, myCyan, 7, 5, 2);

  gPad->RedrawAxis();

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/id_electron";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
