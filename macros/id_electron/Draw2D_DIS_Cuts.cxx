#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void Draw2D_DIS_Cuts(TString targetOption = "C", TString StoreOption = "") {
  // Draw Q2 vs Xb to check DIS phase space

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *InputChain = GetElectronsChain(targetOption);

  TH2D *Hist;
  InputChain->Draw("Q2:Xb>>hist(200, 0., 0.7, 200, 0.5, 5.5)", "", "goff");
  Hist = (TH2D *)gROOT->FindObject("hist");

  // style
  SetMy2DHistStyle(Hist);
  Hist->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
  Hist->GetXaxis()->SetTitle("x_{B}");

  /*** DRAW ***/

  SetMy2DStyle();

  // define canvas
  TString CanvasName = "DIS-cuts_data";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  c->SetFrameLineWidth(2);

  Hist->Draw("COLZ");

  CustomizePaletteSize(Hist);

  gPad->Update();  // necessary
  TF1 *Q2Cut = new TF1("Q2Cut", "1", 0.08, 0.35);
  Q2Cut->SetLineColor(myCyan);
  Q2Cut->SetLineStyle(kSolid);
  Q2Cut->SetLineWidth(5);
  Q2Cut->Draw("SAME");

  gPad->Update();  // necessary
  TF1 *YbCut = new TF1("YbCut", "0.85*2*5.014*0.938*x", 0.1, 0.65);
  YbCut->SetLineColor(myCyan);
  YbCut->SetLineStyle(kSolid);
  YbCut->SetLineWidth(5);
  YbCut->Draw("SAME");

  gPad->Update();  // necessary
  TF1 *WCut = new TF1("WCut", "(4*x-0.938*0.938*x)/(1-x)", 0.2, 0.63);
  WCut->SetLineColor(myCyan);
  WCut->SetLineStyle(kSolid);
  WCut->SetLineWidth(5);
  WCut->Draw("SAME");

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/id_electron";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
