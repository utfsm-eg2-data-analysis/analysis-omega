#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void Draw2D_Eout_vs_Ein(TString StoreOption = "") {
  // Draw electron's Eout vs Ein (on C data)

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  TChain *InputChain = GetTestsChain("no-ec");

  InputChain->Draw("Eout:Ein>>hist(200, 0., 0.35, 200, 0.00, 0.15)", "Eout > 0", "goff");
  TH2D *Hist = (TH2D *)gROOT->FindObject("hist");

  SetMy2DHistStyle(Hist);
  Hist->GetXaxis()->SetTitle("E_{in} [GeV]");
  Hist->GetXaxis()->SetLabelSize(0.03);
  Hist->GetYaxis()->SetTitle("E_{out} [GeV]");
  Hist->GetYaxis()->SetLabelSize(0.03);

  Hist->GetZaxis()->SetMaxDigits(3);
  Hist->GetZaxis()->SetLabelSize(0.03);

  /*** DRAW ***/

  SetMy2DStyle();

  // define canvas
  TString CanvasName = "Eout-vs-Ein_data";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 1080, 1080);
  c->SetFrameLineWidth(2);

  Hist->Draw("COLZ");

  CustomizePaletteSize(Hist);

  DrawVerticalLine(0.06, myCyan, 7, 5, 1);

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/id_electron";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
