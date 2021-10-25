#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

// for simrec, TM parameters
const Double_t kPar[5] = {0.2623, 0.0089, -0.0019, 0.0057, 0.0305};

void Draw2D_SampFrac_Cuts(TString StoreOption = "") {
  // Draw Sampling Fraction cuts for sim. rec. electrons

  TChain *InputChain = GetTestsChain("no-ec", "sim");

  TH2D *Hist;
  InputChain->Draw("TMath::Max(Etot, Eout+Ein)/P:P>>hist(80, 0., 5., 80, 0, 0.5)", "", "goff");
  Hist = (TH2D *)gROOT->FindObject("hist");

  SetMy2DHistStyle(Hist);
  Hist->SetTitle("Simulation Reconstructed - Target: D");
  Hist->GetYaxis()->SetTitle("E/P");
  Hist->GetXaxis()->SetTitle("P [GeV]");

  /*** DRAW ***/

  SetMy2DStyle();
  gStyle->SetTitleY(0.95);

  // define canvas
  TString CanvasName = "sampling-fraction-cuts_sim";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  c->SetFrameLineWidth(2);

  // fill parameters
  Double_t Param[5];
  for (Int_t i = 0; i < 5; i++) {
    Param[i] = kPar[i];
  }

  Hist->Draw("COLZ");

  CustomizePaletteSize(Hist);

  gPad->Update();  // necessary
  TF1 *top = new TF1("top",
                     Form("%f + %f*x + %f*x*x + 2.5*TMath::Sqrt(TMath::Power(%f,2) + TMath::Power(%f,2)/x)", Param[0], Param[1], Param[2],
                          Param[3], Param[4]),
                     0, 5);
  top->SetLineColor(kMagenta);
  top->SetLineStyle(kSolid);
  top->SetLineWidth(3);
  top->Draw("SAME");

  gPad->Update();  // necessary
  TF1 *center = new TF1("center", Form("%f + %f*x + %f*x*x", Param[0], Param[1], Param[2]), 0, 5);
  center->SetLineColor(kBlue);
  center->SetLineStyle(kSolid);
  center->SetLineWidth(3);
  center->Draw("SAME");

  gPad->Update();  // necessary
  TF1 *bottom = new TF1("bottom",
                        Form("%f + %f*x + %f*x*x - 2.5*TMath::Sqrt(TMath::Power(%f,2) + TMath::Power(%f,2)/x)", Param[0], Param[1],
                             Param[2], Param[3], Param[4]),
                        0, 5);
  bottom->SetLineColor(kMagenta);
  bottom->SetLineStyle(kSolid);
  bottom->SetLineWidth(3);
  bottom->Draw("SAME");

  c->Update();

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/id_sim-electron";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
