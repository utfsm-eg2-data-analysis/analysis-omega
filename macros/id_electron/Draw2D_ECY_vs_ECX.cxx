#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void Draw2D_ECY_vs_ECX(TString StoreOption = "") {
  // Draw ECY vs ECX to check effect of EC fiducial cuts (on C data)

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  TChain *Chain_Before = GetTestsChain("no-ec");
  TChain *Chain_After = GetElectronsChain("C");

  // before corr
  TH2D *Hist_Before;
  Chain_Before->Draw("YEC:XEC>>hist_before(240, -450., 450., 240, -450., 450.)", "", "goff");
  Hist_Before = (TH2D *)gROOT->FindObject("hist_before");

  SetMy2DHistStyle(Hist_Before);
  Hist_Before->SetTitle("Before EC Fiducial Cuts");
  Hist_Before->GetYaxis()->SetTitle("Y [cm]");
  Hist_Before->GetYaxis()->SetLabelSize(0.03);
  Hist_Before->GetXaxis()->SetTitle("X [cm]");
  Hist_Before->GetXaxis()->SetLabelSize(0.03);
  Hist_Before->GetZaxis()->SetMaxDigits(3);
  Hist_Before->GetZaxis()->SetLabelSize(0.03);

  // after corr
  TH2D *Hist_After;
  Chain_After->Draw("YEC:XEC>>hist_after(240, -450., 450., 240, -450., 450.)", "", "goff");
  Hist_After = (TH2D *)gROOT->FindObject("hist_after");

  SetMy2DHistStyle(Hist_After);
  Hist_After->SetTitle("After EC Fiducial Cuts");
  Hist_After->GetYaxis()->SetTitle("Y [cm]");
  Hist_After->GetYaxis()->SetLabelSize(0.03);
  Hist_After->GetXaxis()->SetTitle("X [cm]");
  Hist_After->GetXaxis()->SetLabelSize(0.03);
  Hist_After->GetZaxis()->SetMaxDigits(3);
  Hist_After->GetZaxis()->SetLabelSize(0.03);

  /*** DRAW ***/

  SetMy2DStyle();
  gStyle->SetTitleFontSize(0.04);
  gStyle->SetTitleY(1.005);

  // define canvas
  const Int_t Nx = 2;
  const Int_t Ny = 1;
  TString CanvasName = "ECY-vs-ECX_data";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 1080);
  c->Divide(Nx, Ny, 0.001, 0.001);

  c->SetFrameLineWidth(2);

  /*** LEFT PLOT ***/

  c->cd(1);

  Hist_Before->Draw("COLZ");

  CustomizePaletteSize(Hist_Before);

  /*** RIGHT PLOT ***/

  c->cd(2);

  Hist_After->Draw("COLZ");

  CustomizePaletteSize(Hist_After);

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/id_electron";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
