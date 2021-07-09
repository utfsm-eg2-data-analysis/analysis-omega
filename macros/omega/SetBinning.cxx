#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawVerticalLine.cxx"

void SetBinning(TString targetOption = "Pb", Int_t Nbins = 4) {

  const Int_t Nkinvars = 4;
  
  /*** INPUT OPTIONS ***/

  TCut CutVertex;
  TString inputFile1, inputFile2, inputFile3;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
    inputFile1 = gDataDir + "/C/*.root";
    inputFile2 = gDataDir + "/Fe/*.root";
    inputFile3 = gDataDir + "/Pb/*.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    inputFile1 = gDataDir + "/" + targetOption + "/*.root";
  }

  TString kinvarOption[Nkinvars] = {"Q2", "Nu", "wZ", "wPt2"};
  TString titleAxis[Nkinvars];
  TString histProperties[Nkinvars];
  titleAxis[0] = "Q^{2} [GeV^{2}]";
  histProperties[0] = "(100, 1., 4.)";
  titleAxis[1] = "#nu [GeV]";
  histProperties[1] = "(100, 2.2, 4.2)";
  titleAxis[2] = "z_{h}";
  histProperties[2] = "(100, 0.5, 0.9)";
  titleAxis[3] = "p_{T}^{2} [GeV^{2}]";
  histProperties[3] = "(100, 0., 1.5)";

  Double_t kinvarLimit[Nkinvars][2];
  kinvarLimit[0][0] = 1.0;  // Q2
  kinvarLimit[0][1] = 4.0;
  kinvarLimit[1][0] = 2.2;  // Nu
  kinvarLimit[1][1] = 4.2;
  kinvarLimit[2][0] = 0.5;  // Z
  kinvarLimit[2][1] = 0.9;
  kinvarLimit[3][0] = 0.0;  // Pt2
  kinvarLimit[3][1] = 1.5;

  /*** MAIN ***/

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  // necessary for gCutKaons
  SetAliases(treeExtracted);

  TH1D *dataHist[4];

  for (Int_t hh = 0; hh < 4; hh++) {
    treeExtracted->Draw(kinvarOption[hh] + ">>hist_" + kinvarOption[hh] + histProperties[hh], gCutDIS && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle, "goff");
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

  TString canvasTitle = "set-bins-";
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
      
      Double_t xq[Nbins];  // percentages
      Double_t yq[Nbins];  // output array

      // draw first line
      DrawVerticalLine(kinvarLimit[counter-1][0], kBlue, kSolid, 3, 1);
      
      for (Int_t i = 0; i < Nbins; i++) {
	xq[i] = (Double_t)(i + 1) / (Double_t)Nbins;
	dataHist[counter-1]->GetQuantiles(Nbins, yq, xq);
	
	// print information
	if (i == 0)
	  std::cout << "edges" << kinvarOption[counter-1] << "[" << (Nbins + 1) << "] = {" << dataHist[counter-1]->GetBinLowEdge(1) << ", " << yq[i] << ", ";
	else if (i == (Nbins - 1))
	  std::cout << yq[i] << "};" << std::endl;
	else
	  std::cout << yq[i] << ", ";
	
	// draw lines
	if (i != (Nbins - 1))
	  DrawVerticalLine(yq[i], kBlue, kSolid, 3, 1);
	
	c->Update();
      }

      // draw last line
      DrawVerticalLine(kinvarLimit[counter-1][1], kBlue, kSolid, 3, 1);
    }
  }

  c->Draw();
}
