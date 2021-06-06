#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

void SurvivalProb() {

  /*** INPUT ***/

  TCut CutVertex = gCutLiquid || gCutSolid; // all data
  TString inputFile1 = gDataDir + "/C/*.root";
  TString inputFile2 = gDataDir + "/Fe/*.root";
  TString inputFile3 = gDataDir + "/Pb/*.root";

  TString titleAxis = "Reconstructed Mass [GeV]";
  TString histProperties = "(120, 0.4, 2.6)";

  /*** MAIN ***/

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  // necessary for gCutKaons
  SetAliases(treeExtracted);

  /*** 1D HISTS ***/

  TString x; // expression of survival probability

  Int_t max_x0 = 5;
  TH1D *Hist[max_x0]; // each 1D hist corresponds to a different x0 case

  Double_t x0 = 50.7; // 10 fm
  x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
  treeExtracted->Draw(x + ">>hola_0(100, 0., 1.0)", gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  Hist[0] = (TH1D *)gROOT->FindObject("hola_0");
  std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

  x0 = 101.4; // 20 fm
  x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
  treeExtracted->Draw(x + ">>hola_1(100, 0., 1.0)", gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  Hist[1] = (TH1D *)gROOT->FindObject("hola_1");
  std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

  x0 = 152.1; // 30 fm
  x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
  treeExtracted->Draw(x + ">>hola_2(100, 0., 1.0)", gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  Hist[2] = (TH1D *)gROOT->FindObject("hola_2");
  std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

  x0 = 202.8; // 40 fm
  x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
  treeExtracted->Draw(x + ">>hola_3(100, 0., 1.0)", gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  Hist[3] = (TH1D *)gROOT->FindObject("hola_3");
  std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

  x0 = 253.5; // 50 fm
  x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
  treeExtracted->Draw(x + ">>hola_4(100, 0., 1.0)", gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons, "goff");
  Hist[4] = (TH1D *)gROOT->FindObject("hola_4");
  std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

  Hist[0]->SetTitle("");
  
  Hist[0]->GetXaxis()->SetTitle("Survival Probability");
  Hist[0]->GetXaxis()->SetTitleSize(0.04);
  Hist[0]->GetXaxis()->SetTitleOffset(1.2);

  Hist[0]->GetYaxis()->SetTitle("Counts");
  Hist[0]->GetYaxis()->SetMaxDigits(3);
  Hist[0]->GetYaxis()->SetTitleSize(0.04);
  Hist[0]->GetYaxis()->SetTitleOffset(1.2);
  Hist[0]->GetYaxis()->SetMaxDigits(3);
  
  Hist[0]->SetFillStyle(0);
  Hist[1]->SetFillStyle(0);
  Hist[2]->SetFillStyle(0);
  Hist[3]->SetFillStyle(0);
  Hist[4]->SetFillStyle(0);

  Hist[0]->SetLineColor(kBlack);
  Hist[0]->SetLineWidth(2);

  Hist[1]->SetLineColor(kBlue);
  Hist[1]->SetLineWidth(2);

  Hist[2]->SetLineColor(kRed);
  Hist[2]->SetLineWidth(2);  

  Hist[3]->SetLineColor(kMagenta);
  Hist[3]->SetLineWidth(2);

  Hist[4]->SetLineColor(kGreen+2);
  Hist[4]->SetLineWidth(2);
  
  /*** DRAW ***/
  
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gStyle->SetTitleY(0.95);

  gStyle->SetOptStat(0);
  gStyle->SetTitleY(0.95);

  gStyle->SetPadTopMargin(0.15);
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);

  // define canvas
  TCanvas *c = new TCanvas("survival-prob", "survival-prob", 1000, 1000);
  
  c->SetFrameLineWidth(2);

  Hist[0]->Draw("HIST");
  Hist[1]->Draw("HIST SAME");
  Hist[2]->Draw("HIST SAME");
  Hist[3]->Draw("HIST SAME");
  Hist[4]->Draw("HIST SAME");

  TLegend *l = new TLegend(0.15, 0.6, 0.35, 0.85); // x1,y1,x2,y2
  l->AddEntry(Hist[0], "P(x > 10 fm)", "l");
  l->AddEntry(Hist[1], "P(x > 20 fm)", "l");
  l->AddEntry(Hist[2], "P(x > 30 fm)", "l");
  l->AddEntry(Hist[3], "P(x > 40 fm)", "l");
  l->AddEntry(Hist[4], "P(x > 50 fm)", "l");
  l->SetFillStyle(0);
  l->SetTextFont(42);
  l->SetTextSize(0.026);
  l->SetBorderSize(0);
  l->Draw();
}
