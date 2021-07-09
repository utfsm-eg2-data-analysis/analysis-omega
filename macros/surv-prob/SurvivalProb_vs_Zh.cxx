#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

void SurvivalProb_vs_Zh() {

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
  TH1D *Hist[4][max_x0]; // each 1D hist corresponds to a different x0 case

  TCut CutOnZh;
  TString TitleOnZh;
  
  for (Int_t z = 0; z < 4; z++) {

    // set bin in z
    CutOnZh = Form("%.2f < wZ && wZ < %.2f", kEdgesZ[z], kEdgesZ[z+1]);
    TitleOnZh = Form("%.2f < z_{h} < %.2f", kEdgesZ[z], kEdgesZ[z+1]);
    
    Double_t x0 = 50.7; // 10 fm
    x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
    treeExtracted->Draw(x + Form(">>hola_%d_0(100, 0., 1.0)", z), gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && CutOnZh, "goff");
    Hist[z][0] = (TH1D *)gROOT->FindObject(Form("hola_%d_0", z));
    std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

    x0 = 101.4; // 20 fm
    x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
    treeExtracted->Draw(x + Form(">>hola_%d_1(100, 0., 1.0)", z), gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && CutOnZh, "goff");
    Hist[z][1] = (TH1D *)gROOT->FindObject(Form("hola_%d_1", z));
    std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

    x0 = 152.1; // 30 fm
    x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
    treeExtracted->Draw(x + Form(">>hola_%d_2(100, 0., 1.0)", z), gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && CutOnZh, "goff");
    Hist[z][2] = (TH1D *)gROOT->FindObject(Form("hola_%d_2", z));
    std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

    x0 = 202.8; // 40 fm
    x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
    treeExtracted->Draw(x + Form(">>hola_%d_3(100, 0., 1.0)", z), gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && CutOnZh, "goff");
    Hist[z][3] = (TH1D *)gROOT->FindObject(Form("hola_%d_3", z));
    std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

    x0 = 253.5; // 50 fm
    x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
    treeExtracted->Draw(x + Form(">>hola_%d_4(100, 0., 1.0)", z), gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && CutOnZh, "goff");
    Hist[z][4] = (TH1D *)gROOT->FindObject(Form("hola_%d_4", z));
    std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

    Hist[z][0]->SetTitle(TitleOnZh);
  
    Hist[z][0]->GetXaxis()->SetTitle("Survival Probability");
    Hist[z][0]->GetXaxis()->SetTitleSize(0.04);
    Hist[z][0]->GetXaxis()->SetTitleOffset(1.2);

    Hist[z][0]->GetYaxis()->SetTitle("Counts");
    Hist[z][0]->GetYaxis()->SetMaxDigits(3);
    Hist[z][0]->GetYaxis()->SetTitleSize(0.04);
    Hist[z][0]->GetYaxis()->SetTitleOffset(1.2);
    Hist[z][0]->GetYaxis()->SetMaxDigits(3);
    Hist[z][0]->GetYaxis()->SetRangeUser(0, 11000);
  
    Hist[z][0]->SetFillStyle(0);
    Hist[z][1]->SetFillStyle(0);
    Hist[z][2]->SetFillStyle(0);
    Hist[z][3]->SetFillStyle(0);
    Hist[z][4]->SetFillStyle(0);

    Hist[z][0]->SetLineColor(kBlack);
    Hist[z][0]->SetLineWidth(2);

    Hist[z][1]->SetLineColor(kBlue);
    Hist[z][1]->SetLineWidth(2);

    Hist[z][2]->SetLineColor(kRed);
    Hist[z][2]->SetLineWidth(2);  

    Hist[z][3]->SetLineColor(kMagenta);
    Hist[z][3]->SetLineWidth(2);

    Hist[z][4]->SetLineColor(kGreen+2);
    Hist[z][4]->SetLineWidth(2);
  }
  
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
  const Int_t Nx = 4;
  const Int_t Ny = 1;
  TCanvas *c = new TCanvas("survival-prob", "survival-prob", 1000, 1000);
  c->Divide(Nx, Ny, 0.001, 0.001);
  
  c->SetFrameLineWidth(2);

  for (Int_t z = 0; z < 4; z++) {   
    c->cd(z+1);

    Hist[z][0]->Draw("HIST");
    Hist[z][1]->Draw("HIST SAME");
    Hist[z][2]->Draw("HIST SAME");
    Hist[z][3]->Draw("HIST SAME");
    Hist[z][4]->Draw("HIST SAME");

    TLegend *l = new TLegend(0.15, 0.6, 0.35, 0.85); // x1,y1,x2,y2
    l->AddEntry(Hist[z][0], "P(x > 10 fm)", "l");
    l->AddEntry(Hist[z][1], "P(x > 20 fm)", "l");
    l->AddEntry(Hist[z][2], "P(x > 30 fm)", "l");
    l->AddEntry(Hist[z][3], "P(x > 40 fm)", "l");
    l->AddEntry(Hist[z][4], "P(x > 50 fm)", "l");
    l->SetFillStyle(0);
    l->SetTextFont(42);
    l->SetTextSize(0.026);
    l->SetBorderSize(0);
    l->Draw();

    c->Update();
  }
}
