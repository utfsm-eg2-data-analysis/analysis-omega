/**************************************/
/* analysisConfig.h                   */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include "TROOT.h"
#include "TString.h"
#include "TCut.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLine.h"
#include "TPaveText.h"
#include "TLegend.h"

/*** Global variables ***/

TString proFolder = "/home/borquez/omegaThesis";

TCut cutDIS = "Q2 > 1 && W > 2 && Yb < 0.85";
TCut cutPi0 = "0.059 < pi0M && pi0M < 0.209";
TCut cutPipPim = "0.48 > pippimM || 0.51 < pippimM";

// these cuts are for the files filtered with old OS programs
TCut cutDIS_old = "Q2 > 1 && W > 2";
TCut cutPi0_old = "0.059 < pi0M && pi0M < 0.209";
TCut cutPipPim_old = "0.48 > pippimM || 0.51 < pippimM";

// edges obtained with GetQuantiles.cxx
const Double_t edgesQ2[6] = {1., 1.181, 1.364, 1.598, 1.960, 3.970};
const Double_t edgesNu[6] = {2.2, 3.191, 3.504, 3.744, 3.964, 4.2};
const Double_t edgesZ[6] = {0.5, 0.554, 0.611, 0.676, 0.760, 0.9};
const Double_t edgesPt2[6] = {0.0, 0.040, 0.090, 0.159, 0.273, 1.5};

void drawHorizontalLine(Double_t y) {
  Double_t u;
  gPad->Update(); // necessary
  u = (y - gPad->GetY1())/(gPad->GetY2() - gPad->GetY1());
  // u = (y - y1)/(y2 - y1);
  TLine *liney = new TLine(0.1, u, 0.9, u);
  liney->SetLineWidth(3);
  liney->SetLineColor(kRed);
  liney->SetLineStyle(2);
  liney->SetNDC(kTRUE);
  liney->Draw();
}

void drawBlackHorizontalLine(Double_t y) {
  Double_t u;
  gPad->Update(); // necessary
  u = (y - gPad->GetY1())/(gPad->GetY2() - gPad->GetY1());
  // u = (y - y1)/(y2 - y1);
  TLine *liney = new TLine(0.1, u, 0.9, u);
  liney->SetLineWidth(3);
  liney->SetLineColor(kBlack);
  liney->SetLineStyle(2);
  liney->SetNDC(kTRUE);
  liney->Draw();
}

void drawVerticalLineBlack(Double_t x) {
  Double_t u;
  gPad->Update(); // necessary
  u = (x - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  // u = (x - x1)/(x2 - x1);
  TLine *linex = new TLine(u, 0.1, u, 0.9);
  linex->SetLineWidth(3);
  linex->SetLineColor(kBlack);
  linex->SetLineStyle(2);
  linex->SetNDC(kTRUE);
  linex->Draw();
}

void drawVerticalLineGrayest(Double_t x) {
  Double_t u;
  gPad->Update(); // necessary
  u = (x - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  // u = (x - x1)/(x2 - x1);
  TLine *linex = new TLine(u, 0.1, u, 0.9);
  linex->SetLineWidth(3);
  linex->SetLineColor(kGray+3);
  linex->SetLineStyle(2);
  linex->SetNDC(kTRUE);
  linex->Draw();
}

void drawVerticalLineGrayer(Double_t x) {
  Double_t u;
  gPad->Update(); // necessary
  u = (x - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  // u = (x - x1)/(x2 - x1);
  TLine *linex = new TLine(u, 0.1, u, 0.9);
  linex->SetLineWidth(3);
  linex->SetLineColor(kGray+2);
  linex->SetLineStyle(2);
  linex->SetNDC(kTRUE);
  linex->Draw();
}

void drawVerticalLineGray(Double_t x) {
  Double_t u;
  gPad->Update(); // necessary
  u = (x - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  // u = (x - x1)/(x2 - x1);
  TLine *linex = new TLine(u, 0.1, u, 0.9);
  linex->SetLineWidth(3);
  linex->SetLineColor(kGray+1);
  linex->SetLineStyle(2);
  linex->SetNDC(kTRUE);
  linex->Draw();
}














/*
    // my own normalization
    simrecHistA->Draw("HIST");
    c->Update();
    //scale hint1 to the pad coordinates
    Float_t rightmax2 = 1.1*simrecHistC->GetMaximum();
    Float_t scale2 = gPad->GetUymax()/rightmax2;
    simrecHistC->Scale(scale2);
    simrecHistC->Draw("SAME HIST");
    //draw an axis on the right side
    TGaxis *axis2 = new TGaxis(gPad->GetUxmax(), gPad->GetUymin(),
			       gPad->GetUxmax(), gPad->GetUymax(),
			       0, rightmax2, 510, "+L");
    axis2->SetLineColor(kRed);
    axis2->SetLabelColor(kRed);
    axis2->Draw();
*/
