#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Double_t kCPar[6][5] = {
    {0.252164, 0.0122263, -0.000793937, 9.55113e-03, 3.40672e-02}, {0.278574, 0.0187482, -0.00238217, 1.39889e-02, 3.74682e-02},
    {0.262079, 0.0230685, -0.00354741, 9.32762e-03, 2.90046e-02},  {0.251108, 0.0201568, -0.00332367, 8.21055e-03, 2.98893e-02},
    {0.263396, 0.00955238, -0.00102038, 2.25684e-02, 3.06508e-02}, {0.255245, 0.0232659, -0.00304798, 1.17254e-02, 3.64221e-02}};

void Draw2D_SampFrac_Cuts(TString StoreOption = "") {
  // Draw E/P vs P to represent Sampling Fraction Cut on electrons (on C data)

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  TChain *InputChain = GetTestsChain("no-ec");

  TH2D *Hist[6];
  for (Int_t Sector = 0; Sector < 6; Sector++) {
    InputChain->Draw(Form("TMath::Max(Etot, Eout+Ein)/P:P>>hist_%d(240, 0., 5., 240, 0, 0.5)", Sector), Form("Sector == %d", Sector), "goff");
    Hist[Sector] = (TH2D *)gROOT->FindObject(Form("hist_%d", Sector));

    SetMy2DHistStyle(Hist[Sector]);
    Hist[Sector]->SetTitle(Form("Sector %d", Sector));

    Hist[Sector]->GetYaxis()->SetTitle("E/P");
    Hist[Sector]->GetYaxis()->SetLabelSize(0.03);

    Hist[Sector]->GetXaxis()->SetTitle("P [GeV]");
    Hist[Sector]->GetXaxis()->SetLabelSize(0.03);

    Hist[Sector]->GetZaxis()->SetMaxDigits(3);
    Hist[Sector]->GetZaxis()->SetLabelSize(0.03);
  }

  /*** DRAW ***/

  SetMy2DStyle();
  gStyle->SetTitleFontSize(0.05);
  gStyle->SetTitleY(1.01);

  // define canvas
  const Int_t Nx = 3;
  const Int_t Ny = 2;
  TString CanvasName = "sampling-fraction-cuts_data";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 3240, 2160);
  c->Divide(Nx, Ny, 0.001, 0.001);

  c->SetFrameLineWidth(2);

  Int_t counter = 1;
  for (Int_t i = 0; i < Nx; i++) {
    for (Int_t j = 0; j < Ny; j++) {

      c->cd(counter);
      Hist[counter - 1]->Draw("COLZ");

      CustomizePaletteSize(Hist[counter - 1]);

      gPad->Update();  // necessary
      TF1 *top = new TF1(Form("top_%d%d", i, j),
                         Form("%f + %f*x + %f*x*x + 2.5*TMath::Sqrt(TMath::Power(%f,2) + TMath::Power(%f,2)/x)", kCPar[counter - 1][0],
                              kCPar[counter - 1][1], kCPar[counter - 1][2], kCPar[counter - 1][3], kCPar[counter - 1][4]),
                         0, 5);
      top->SetLineColor(myCyan);
      top->SetLineStyle(kSolid);
      top->SetLineWidth(5);
      top->Draw("SAME");

      gPad->Update();  // necessary
      TF1 *center = new TF1(Form("center_%d%d", i, j),
                            Form("%f + %f*x + %f*x*x", kCPar[counter - 1][0], kCPar[counter - 1][1], kCPar[counter - 1][2]), 0, 5);
      center->SetLineColor(myBlue);
      center->SetLineStyle(kSolid);
      center->SetLineWidth(5);
      center->Draw("SAME");

      gPad->Update();  // necessary
      TF1 *bottom = new TF1(Form("bottom_%d%d", i, j),
                            Form("%f + %f*x + %f*x*x - 2.5*TMath::Sqrt(TMath::Power(%f,2) + TMath::Power(%f,2)/x)", kCPar[counter - 1][0],
                                 kCPar[counter - 1][1], kCPar[counter - 1][2], kCPar[counter - 1][3], kCPar[counter - 1][4]),
                            0, 5);
      bottom->SetLineColor(myCyan);
      bottom->SetLineStyle(kSolid);
      bottom->SetLineWidth(5);
      bottom->Draw("SAME");

      c->Update();
      counter++;
    }
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/id_electron";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
