#ifndef DRAWFUNCTIONS_CXX
#define DRAWFUNCTIONS_CXX

#ifndef GLOBAL_H
#include "Global.h"
#endif

Color_t myRed = kRed + 1;
Color_t myGreen = kSpring - 8;
Color_t myBlue = kAzure + 2;
Color_t myOrange = kOrange + 2;
Color_t myViolet = kViolet + 2;
Color_t myYellow = kYellow + 1;
Color_t myCyan = kCyan + 1;
Color_t myMagenta = kPink - 8;
Color_t myBlack = kGray + 3;

void DrawVerticalLine(Double_t x, Color_t color = kBlack, Style_t style = kDashed, Int_t width = 3, Int_t OffsetOn = 0) {
  Double_t u;
  gPad->Update();  // necessary
  u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
  // u = (x - x1)/(x2 - x1);
  TLine *linex = new TLine(u, 0.1, u, 0.9);
  linex->SetLineColor(color);  // kBlack, kBlue, kRed, kGreen+2, kOrange+7, kGray+{1,2,3}
  linex->SetLineStyle(style);  // kSolid, kDashed, kDotted
  linex->SetLineWidth(width);
  if (OffsetOn == 1) {
    linex->SetY1(0.15);
    linex->SetY2(0.95);
  }
  linex->SetNDC(kTRUE);
  linex->Draw();
}

void DrawHorizontalLine(Double_t y, Color_t color = kBlack, Style_t style = kDashed, Int_t width = 3, Int_t OffsetOn = 0) {
  Double_t u;
  gPad->Update();  // necessary
  u = (y - gPad->GetY1()) / (gPad->GetY2() - gPad->GetY1());
  // u = (y - y1)/(y2 - y1);
  TLine *liney = new TLine(0.1, u, 0.9, u);
  liney->SetLineColor(color);  // kBlack, kBlue, kRed, kGreen+2, kOrange+7, kGray+{1,2,3}
  liney->SetLineStyle(style);  // kSolid, kDashed, kDotted
  liney->SetLineWidth(width);
  if (OffsetOn == 1) {
    liney->SetX1(0.15);
    liney->SetX2(0.95);
  }
  liney->SetNDC(kTRUE);
  liney->Draw();
}

void DrawDiagonalLine(Double_t slope, Double_t constant, Double_t x1, Double_t x2, Color_t color = kBlack, Style_t style = kDashed,
                      Int_t width = 3, TString Name = "") {
  gPad->Update();  // necessary
  TF1 *function = new TF1(Name, Form("%f + %f*x", constant, slope), x1, x2);
  function->SetLineColor(color);  // kBlack, kBlue, kRed, kGreen+2, kOrange+7, kGray+{1,2,3}
  function->SetLineStyle(style);  // kSolid, kDashed, kDotted
  function->SetLineWidth(width);
  function->Draw("SAME");
}

/***************************************/
/***   FUNCTIONS FOR 1D HISTOGRAMS   ***/
/***************************************/

void SetMyHistStyle(TH1D *theHist) {
  theHist->SetTitle("");
  theHist->SetLineWidth(2);
  theHist->SetFillStyle(0);
  theHist->GetYaxis()->SetTitleSize(0.04);
  theHist->GetYaxis()->SetTitleOffset(1.2);
  theHist->GetYaxis()->SetMaxDigits(3);
  theHist->GetXaxis()->SetTitleSize(0.04);
  theHist->GetXaxis()->SetTitleOffset(1.2);
}

void SetMyStyle() {
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLineWidth(2);
  // set margin sizes
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetOptStat(0);
}

/***************************************/
/***   FUNCTIONS FOR 2D HISTOGRAMS   ***/
/***************************************/

void SetMy2DHistStyle(TH2D *theHist) {
  theHist->SetTitle("");
  theHist->GetYaxis()->SetTitleSize(0.04);
  theHist->GetYaxis()->SetTitleOffset(1.2);
  theHist->GetXaxis()->SetTitleSize(0.04);
  theHist->GetXaxis()->SetTitleOffset(1.2);
  theHist->GetZaxis()->SetMaxDigits(3);
  theHist->GetZaxis()->SetTickLength(0.02);
}

void SetMy2DStyle() {
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLineWidth(2);
  // only modify bottom and top margins
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetOptStat(0);
  // set palette color
  gStyle->SetPalette(kDarkBodyRadiator);
  gStyle->SetNumberContours(255);
}

void CustomizePaletteSize(TH2D *theHist) {
  gPad->Update();
  TPaletteAxis *palette = (TPaletteAxis *)theHist->GetListOfFunctions()->FindObject("palette");
  palette->SetX1NDC(0.901);
  palette->SetX2NDC(0.926);
}

#endif
