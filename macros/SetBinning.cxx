#ifndef GLOBAL_H
#include "Global.h"
#endif

#include "SetAliases.cxx"
#include "DrawVerticalLine.cxx"

void SetBinning(TString targetOption = "Pb", TString kinvarOption = "wZ", Int_t NBins = 5) {

  /*** INPUT OPTIONS ***/

  TCut CutVertex;
  TString inputFile1, inputFile2, inputFile3;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
    inputFile1 = gDataDir + "/comb_data-C.root";
    inputFile2 = gDataDir + "/comb_data-Fe.root";
    inputFile3 = gDataDir + "/comb_data-Pb.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    inputFile1 = gDataDir + "/comb_data-" + targetOption + ".root";
  }

  TString titleAxis, histProperties;
  if (kinvarOption == "Q2") {
    titleAxis = "Q^{2} [GeV^{2}]";
    histProperties = "(200, 1., 4.)";  
  } else if (kinvarOption == "Nu") {
    titleAxis = "#nu [GeV]";
    histProperties = "(200, 2.2, 4.2)";
  } else if (kinvarOption == "wZ") {
    titleAxis = "Z_{h}";
    histProperties = "(100, 0.5, 0.9)";
  } else if (kinvarOption == "wPt2") {
    titleAxis = "p_{T}^{2} [GeV^{2}]";
    histProperties = "(150, 0., 1.5)";
  }
  
  /*** MAIN ***/

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  SetAliases(treeExtracted); // for gCutKaons
  
  TH1D *dataHist;
  treeExtracted->Draw(kinvarOption + ">>hist" + histProperties, gCutDIS && gCutPi0 && gCutRegion && CutVertex && gCutKaons,
		      "goff");
  dataHist = (TH1D *)gROOT->FindObject("hist");

  dataHist->SetLineColor(kBlack);
  dataHist->SetLineWidth(2);

  dataHist->GetXaxis()->SetTitle(titleAxis);
  dataHist->GetXaxis()->CenterTitle();
  dataHist->GetYaxis()->SetTitle("Candidates");
  dataHist->GetYaxis()->CenterTitle();
  dataHist->GetYaxis()->SetMaxDigits(3);

  /*** Quantile stuff ***/

  TString canvasTitle = "set-bins-"; 
  canvasTitle += Form("%d", NBins);
  canvasTitle += "_" + targetOption + "_" +  kinvarOption;
  TCanvas *c = new TCanvas(canvasTitle, "c"); 
  c->SetGrid();

  dataHist->Draw("HIST");
    
  Double_t xq[NBins]; // percentages
  Double_t yq[NBins]; // output array
  for (Int_t i = 0; i < NBins; i++) {
    xq[i] = Double_t(i+1)/NBins;
    dataHist->GetQuantiles(NBins, yq, xq);
    // print information
    if (i == 0) std::cout << "edges" << kinvarOption << "[" << (NBins+1) << "] = {" << dataHist->GetBinLowEdge(1) << ", " << yq[i] << ", ";
    else if (i == (NBins - 1)) std::cout << yq[i] << "};" << std::endl;
    else std::cout << yq[i] << ", ";
    // draw line
    if (i != (NBins - 1)) DrawVerticalLine(yq[i], kRed, kDashed);
  }

  c->Draw();
}
