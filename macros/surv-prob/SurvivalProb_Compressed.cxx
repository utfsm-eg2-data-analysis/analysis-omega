#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

void SurvivalProb_Compressed() {

  // Plot a summary of the Survival Probability plots as a function of Z, in just one plot.

  const Int_t Nbins = 4;
  const Int_t Nhists = 5;
  
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

  TH1D *Hist[Nhists][Nbins]; // each 1D hist corresponds to a different x0 case

  TCut CutOnZh;
  TString TitleOnZh;

  Color_t HistColor[Nhists] = {kBlack, kBlue, kMagenta, kRed, kGreen+2}; 

  Double_t x00 = 5.07; // in GeV, this is equal to 1 fm
  
  for (Int_t z = 0; z < Nbins; z++) {

    // set bin in z
    CutOnZh = Form("%.2f < wZ && wZ < %.2f", kEdgesZ[z], kEdgesZ[z+1]);
    TitleOnZh = Form("%.2f < z_{h} < %.2f", kEdgesZ[z], kEdgesZ[z+1]);

    Double_t x0 = x00; // 1 fm
    x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
    treeExtracted->Draw(x + Form(">>hola_0_%d(100, 0., 1.0)", z), gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && CutOnZh, "goff");
    Hist[0][z] = (TH1D *)gROOT->FindObject(Form("hola_0_%d", z));
    std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

    x0 = 2.5*x00; // 2.5 fm
    x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
    treeExtracted->Draw(x + Form(">>hola_1_%d(100, 0., 1.0)", z), gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && CutOnZh, "goff");
    Hist[1][z] = (TH1D *)gROOT->FindObject(Form("hola_1_%d", z));
    std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

    x0 = 5*x00; // 5 fm
    x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
    treeExtracted->Draw(x + Form(">>hola_2_%d(100, 0., 1.0)", z), gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && CutOnZh, "goff");
    Hist[2][z] = (TH1D *)gROOT->FindObject(Form("hola_2_%d", z));
    std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

    x0 = 7.5*x00; // 7.5 fm
    x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
    treeExtracted->Draw(x + Form(">>hola_3_%d(100, 0., 1.0)", z), gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && CutOnZh, "goff");
    Hist[3][z] = (TH1D *)gROOT->FindObject(Form("hola_3_%d", z));
    std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

    x0 = 10*x00; // 10 fm
    x = Form("TMath::Exp(-0.782*%f*0.00849/wP)", x0);
    treeExtracted->Draw(x + Form(">>hola_4_%d(100, 0., 1.0)", z), gCutDIS && CutVertex && gCutPi0 && gCutPhotonsOpAngle && gCutKaons && CutOnZh, "goff");
    Hist[4][z] = (TH1D *)gROOT->FindObject(Form("hola_4_%d", z));
    std::cout << "Drawing Hist w/ x0 = " << x0 << " GeV^{-1}" << std::endl;

    Hist[0][z]->SetTitle(TitleOnZh);

    Hist[0][z]->GetXaxis()->SetTitle("Survival Probability");
    Hist[0][z]->GetXaxis()->SetTitleSize(0.04);
    Hist[0][z]->GetXaxis()->SetTitleOffset(1.2);

    Hist[0][z]->GetYaxis()->SetTitle("Counts");
    Hist[0][z]->GetYaxis()->SetMaxDigits(3);
    Hist[0][z]->GetYaxis()->SetTitleSize(0.04);
    Hist[0][z]->GetYaxis()->SetTitleOffset(1.2);
    Hist[0][z]->GetYaxis()->SetMaxDigits(3);
    Hist[0][z]->GetYaxis()->SetRangeUser(0, 11000);

    for (Int_t h = 0; h < Nhists; h++) {
      Hist[h][z]->SetFillStyle(0);
      Hist[h][z]->SetLineColor(HistColor[h]);
      Hist[h][z]->SetLineWidth(2);
    }
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

  for (Int_t z = 0; z < Nbins; z++) {   
    c->cd(z+1);

    Hist[0][z]->Draw("HIST");
    Hist[1][z]->Draw("HIST SAME");
    Hist[2][z]->Draw("HIST SAME");
    Hist[3][z]->Draw("HIST SAME");
    Hist[4][z]->Draw("HIST SAME");

    TLegend *l = new TLegend(0.15, 0.6, 0.35, 0.85); // x1,y1,x2,y2
    l->AddEntry(Hist[0][z], "P(x > 1.0 fm)", "l");
    l->AddEntry(Hist[1][z], "P(x > 2.5 fm)", "l");
    l->AddEntry(Hist[2][z], "P(x > 5.0 fm)", "l");
    l->AddEntry(Hist[3][z], "P(x > 7.5 fm)", "l");
    l->AddEntry(Hist[4][z], "P(x > 10.0 fm)", "l");
    l->SetFillStyle(0);
    l->SetTextFont(42);
    l->SetTextSize(0.026);
    l->SetBorderSize(0);
    l->Draw();

    c->Update();
  }

  /*** NEXT STAGE: COMPRESSION ***/
  
  Double_t UpperError[Nhists][Nbins];
  Double_t Mean[Nhists][Nbins];
  Double_t LowerError[Nhists][Nbins];
  
  for (Int_t h = 0; h < Nhists; h++) {
    for (Int_t z = 0; z < Nbins; z++) {
      // get mean of histograms
      Mean[h][z] = Hist[h][z]->GetMean();
      // get first bin with content as lower error
      for (Int_t i = 0; i < Hist[h][z]->GetNbinsX(); i++) {
	if (Hist[h][z]->GetBinContent(i) > 20) {
	  LowerError[h][z] = Hist[h][z]->GetMean() - Hist[h][z]->GetBinLowEdge(i);
	  i = Hist[h][z]->GetNbinsX();
	}
      }
      // get last bin with content as upper error
      for (Int_t j = Hist[h][z]->GetNbinsX(); j > 0; j--) {
	if (Hist[h][z]->GetBinContent(j) > 20) {
	  UpperError[h][z] = Hist[h][z]->GetBinLowEdge(j+1) - Hist[h][z]->GetMean(); // get low edge from next bin, because there is no GetBinHighEdge()...
	  j = 0;
	}
      }
      std::cout << "Hist " << h << ", Bin " << z << ": " << Mean[h][z] << " - " << LowerError[h][z] << " + " << UpperError[h][z] << std::endl;
    }
  }
  
  /*** DEFINE GRAPHS ***/

  // define x-axis as Z
  Double_t MR_x[Nbins];
  Double_t MR_xerr[Nbins];
  for (Int_t z = 0; z < Nbins; z++) {
    MR_x[z] = (kEdgesZ[z] + kEdgesZ[z + 1]) / 2.;
    MR_xerr[z] = (kEdgesZ[z + 1] - kEdgesZ[z]) / 2;
  }
    
  // define graphs
  TGraphAsymmErrors *Graph[Nhists];
  for (Int_t h = 0; h < Nhists; h++) {
    Graph[h] = new TGraphAsymmErrors(Nbins, MR_x, Mean[h], MR_xerr, MR_xerr, LowerError[h], UpperError[h]);
    for (Int_t z = 0; z < Nbins; z++) MR_x[z] += 0.01; // displace each x-center
  }
  
  // set style
  Graph[0]->SetTitle("");
  
  Graph[0]->GetXaxis()->SetTitle("z_h");
  //Graph[0]->GetXaxis()->SetNdivisions(500 + Nbins, kFALSE);
  Graph[0]->GetXaxis()->SetLimits(kEdgesZ[0], kEdgesZ[Nbins]);
  Graph[0]->GetXaxis()->SetTitleSize(0.04);
  Graph[0]->GetXaxis()->SetTitleOffset(1.);

  Graph[0]->GetYaxis()->SetTitle("Survival Probability");
  Graph[0]->GetYaxis()->SetRangeUser(0.5, 1.0);
  Graph[0]->GetYaxis()->SetTitleSize(0.04);
  Graph[0]->GetYaxis()->SetTitleOffset(1.2);
  
  for (Int_t h = 0; h < Nhists; h++) {  // solid targets only
    Graph[h]->SetMarkerStyle(21);
    Graph[h]->SetMarkerSize(1.5);
    Graph[h]->SetMarkerColor(HistColor[h]);
    Graph[h]->SetLineColor(HistColor[h]);
    Graph[h]->SetLineWidth(3);
  }

  /*** DRAW ***/
  
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  // gStyle->SetLineWidth(2);
  
  gStyle->SetOptStat(0);

  // set margin sizes
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  
  // define canvas
  TCanvas *c1 = new TCanvas("survival-prob-comp", "survival-prob-comp", 1000, 1000);
    
  Graph[0]->Draw("AP");
  Graph[1]->Draw("P"); 
  Graph[2]->Draw("P"); 
  Graph[3]->Draw("P"); 
  Graph[4]->Draw("P"); 

  // legend
  TLegend *legend = new TLegend(0.75, 0.75, 0.9, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(Graph[0], "P(x > 1.0 fm)", "l");
  legend->AddEntry(Graph[1], "P(x > 2.5 fm)", "l");
  legend->AddEntry(Graph[2], "P(x > 5.0 fm)", "l");
  legend->AddEntry(Graph[3], "P(x > 7.5 fm)", "l");
  legend->AddEntry(Graph[4], "P(x > 10.0 fm)", "l");
  legend->SetFillStyle(0);
  legend->SetTextFont(62);
  legend->SetTextSize(0.035);
  legend->SetBorderSize(0);
  legend->Draw();
}
