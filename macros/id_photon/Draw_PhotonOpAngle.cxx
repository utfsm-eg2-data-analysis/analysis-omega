#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void Draw_PhotonOpAngle(TString StoreOption = "") {
  // Draw the opening angle of photons w.r.t. scattered electron

  /*** INPUT ***/

  TCut CutVertex = gCutSolid || gCutLiquid;

  TChain *dataChain = GetTwoGammaFinderChain("All");
  SetAliasesEta(dataChain);

  TH1D *theHist1;
  dataChain->Draw("gamma1_OpAngle>>data1(90, 0, 90)", gCutDIS && CutVertex && gCutRegion_Eta, "goff");
  theHist1 = (TH1D *)gROOT->FindObject("data1");

  // style
  SetMyHistStyle(theHist1);
  theHist1->SetMarkerColor(myBlack);
  theHist1->SetLineColor(myBlack);
  theHist1->SetLineWidth(3);
  theHist1->GetYaxis()->SetTitle("Counts");
  theHist1->GetYaxis()->SetMaxDigits(3);
  theHist1->GetXaxis()->SetTitle("#alpha_{e#gamma} [deg]");

  TH1D *theHist2;
  dataChain->Draw("gamma2_OpAngle>>data2(90, 0, 90)", gCutDIS && CutVertex && gCutRegion_Eta, "goff");
  theHist2 = (TH1D *)gROOT->FindObject("data2");

  // style
  SetMyHistStyle(theHist2);
  theHist2->SetMarkerColor(myRed);
  theHist2->SetLineColor(myRed);
  theHist2->SetLineWidth(3);

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "photons-op-angle_data";
  TCanvas *can1 = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  theHist1->Draw("E");
  theHist2->Draw("E SAME");

  // vert line - cut
  DrawVerticalLine(12, myBlue, 7, 4, 1);

  // legend
  TLegend *legend = new TLegend(0.75, 0.75, 0.9, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(theHist1, "#gamma_{1}", "l");
  legend->AddEntry(theHist2, "#gamma_{2}", "l");
  legend->SetFillStyle(0);
  legend->SetTextFont(62);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw();

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/id_photon";
    system("mkdir -p " + OutputDir);
    can1->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
