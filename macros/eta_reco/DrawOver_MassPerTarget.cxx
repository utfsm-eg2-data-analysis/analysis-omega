#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

void DrawOver_MassPerTarget(Int_t KinLimits = 1, TString StoreOption = "") {
  // Draw an overlay of the invariant mass of eta for all targets

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *chainData_D = GetTwoGammaFinderChain("D");
  SetAliasesEta(chainData_D);

  TChain *chainData_C = GetTwoGammaFinderChain("C");
  SetAliasesEta(chainData_C);

  TChain *chainData_Fe = GetTwoGammaFinderChain("Fe");
  SetAliasesEta(chainData_Fe);

  TChain *chainData_Pb = GetTwoGammaFinderChain("Pb");
  SetAliasesEta(chainData_Pb);

  TString titleAxis = "Reconstructed Mass m(#gamma#gamma) [GeV]";
  TString histProperties = "(150, 0., 1.)";

  // apply kinematic limits
  TCut CutRegion_Eta = "";
  if (KinLimits) {
    CutRegion_Eta = gCutRegion_Eta;
  }

  /*** MAIN ***/

  TH1D *theHistD;
  chainData_D->Draw("nM>>histD" + histProperties, gCutLiquid && gCutDIS && gCutPhotonsOpAngle && CutRegion_Eta, "goff");
  theHistD = (TH1D *)gROOT->FindObject("histD");

  theHistD->SetTitle("");

  theHistD->GetXaxis()->SetTitle(titleAxis);
  theHistD->GetXaxis()->SetTitleSize(0.04);
  theHistD->GetXaxis()->SetTitleOffset(1.2);

  theHistD->GetYaxis()->SetTitle("Counts");
  theHistD->GetYaxis()->SetMaxDigits(3);
  theHistD->GetYaxis()->SetTitleSize(0.04);
  theHistD->GetYaxis()->SetTitleOffset(1.2);
  theHistD->GetYaxis()->SetMaxDigits(3);

  theHistD->SetFillStyle(0);
  theHistD->SetLineColor(myGreen);
  theHistD->SetLineWidth(3);

  TH1F *theHistFe;
  chainData_Fe->Draw("nM>>histFe" + histProperties, gCutSolid && gCutDIS && gCutPhotonsOpAngle && CutRegion_Eta, "goff");
  theHistFe = (TH1F *)gROOT->FindObject("histFe");

  theHistFe->SetFillStyle(0);
  theHistFe->SetLineColor(myBlue);
  theHistFe->SetLineWidth(3);

  TH1F *theHistC;
  chainData_C->Draw("nM>>histC" + histProperties, gCutSolid && gCutDIS && gCutPhotonsOpAngle && CutRegion_Eta, "goff");
  theHistC = (TH1F *)gROOT->FindObject("histC");

  theHistC->SetFillStyle(0);
  theHistC->SetLineColor(myRed);
  theHistC->SetLineWidth(3);

  TH1F *theHistPb;
  chainData_Pb->Draw("nM>>histPb" + histProperties, gCutSolid && gCutDIS && gCutPhotonsOpAngle && CutRegion_Eta, "goff");
  theHistPb = (TH1F *)gROOT->FindObject("histPb");

  theHistPb->SetFillStyle(0);
  theHistPb->SetLineColor(myBlack);
  theHistPb->SetLineWidth(3);

  /*** DRAW ***/

  SetMyStyle();
  gStyle->SetOptLogy(1);

  TString CanvasName = "eta-nM_all-targets_data";
  if (KinLimits) {
    CanvasName = "eta-nM-with-kin-cuts_all-targets_data";
  }
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  theHistD->Draw("HIST");
  theHistFe->Draw("SAME HIST");
  theHistPb->Draw("SAME HIST");
  theHistC->Draw("SAME HIST");

  DrawVerticalLine(0.548, myOrange, 7, 3, 1);

  TLegend *l = new TLegend(0.8, 0.7, 1., 0.9);  // x1,y1,x2,y2
  l->AddEntry(theHistD, "D", "l");
  l->AddEntry(theHistFe, "Fe", "l");
  l->AddEntry(theHistC, "C", "l");
  l->AddEntry(theHistPb, "Pb", "l");
  l->SetFillStyle(0);
  l->SetTextFont(62);
  l->SetTextSize(0.04);
  l->SetBorderSize(0);
  l->Draw();

  c->Draw();

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_reco";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
