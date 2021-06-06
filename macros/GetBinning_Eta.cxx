#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawVerticalLine.cxx"

void GetBinning_Eta(TString targetOption = "Fe") {

  const Int_t Nkinvars = 4;
  const Int_t Nbins = 5;
  
  /*** INPUT OPTIONS ***/

  TCut CutVertex;
  TString inputFile1, inputFile2, inputFile3;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
    inputFile1 = gDataDir_Eta + "/C/*.root";
    inputFile2 = gDataDir_Eta + "/Fe/*.root";
    inputFile3 = gDataDir_Eta + "/Pb/*.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    inputFile1 = gDataDir_Eta + "/" + targetOption + "/*.root";
  }

  TString kinvarOption[4] = {"Q2", "Nu", "eZ", "ePt2"};
  TString titleAxis[4];
  TString histProperties[4];
  titleAxis[0] = "Q^{2} [GeV^{2}]";
  histProperties[0] = "(100, 1., 4.1)";
  titleAxis[1] = "#nu [GeV]";
  histProperties[1] = "(100, 2.2, 4.25)";
  titleAxis[2] = "z_{h}";
  histProperties[2] = "(100, 0.5, 1.0)";
  titleAxis[3] = "p_{T}^{2} [GeV^{2}]";
  histProperties[3] = "(100, 0., 1.5)";

  Double_t KinvarEdges[Nkinvars][Nbins+1];
  for (Int_t i = 0; i < Nbins+1; i++) {
    KinvarEdges[0][i] = kEdgesQ2_Eta[i];
    KinvarEdges[1][i] = kEdgesNu_Eta[i];
    KinvarEdges[2][i] = kEdgesZ_Eta[i];
    KinvarEdges[3][i] = kEdgesPt2_Eta[i];
  }
  
  /*** MAIN ***/

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  // necessary for gCutKaons
  SetAliases(treeExtracted);

  TH1D *dataHist[4];

  for (Int_t hh = 0; hh < Nkinvars; hh++) {
    treeExtracted->Draw(kinvarOption[hh] + ">>hist_" + kinvarOption[hh] + histProperties[hh], gCutDIS && CutVertex && gCutPhotonsOpAngle_Eta && gCutRegion_Eta, "goff");
    dataHist[hh] = (TH1D *)gROOT->FindObject("hist_" + kinvarOption[hh]);

    dataHist[hh]->SetFillStyle(0);
    dataHist[hh]->SetLineColor(kBlack);
    dataHist[hh]->SetLineWidth(2);

    dataHist[hh]->SetTitle("");
    dataHist[hh]->GetXaxis()->SetTitle(titleAxis[hh]);
    dataHist[hh]->GetYaxis()->SetTitle("Counts");
    dataHist[hh]->GetYaxis()->SetTitleSize(0.04);
    dataHist[hh]->GetYaxis()->SetTitleOffset(1.2);
    dataHist[hh]->GetYaxis()->SetMaxDigits(3);
  }
  
  /*** DRAW ***/

  TString canvasTitle = "eta-bins-";
  canvasTitle += Form("%d", Nbins);
  canvasTitle += "_" + targetOption;

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLineWidth(1);

  // set margin sizes
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  
  gStyle->SetOptStat(0);

  const Int_t Nx = 2;
  const Int_t Ny = 2;
  TCanvas *c = new TCanvas(canvasTitle, "c", 1200, 1200);
  c->Divide(Nx, Ny, 0.001, 0.001);
  // c->SetGrid();
  
  Int_t counter = 0;
  for (Int_t xx = 0; xx < Nx; xx++) {
    for (Int_t yy = 0; yy < Ny; yy++) {
      counter++;
      c->cd(counter);
      
      dataHist[counter-1]->Draw("HIST");
      
      for (Int_t i = 0; i < Nbins+1; i++) DrawVerticalLine(KinvarEdges[counter-1][i], kRed, kSolid, 3, 1);
      
      c->Update();
    }
  }

  c->Draw();
}
