#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef ACCEPTANCE_H
#include "Acceptance.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Nkinvars = 4;
const Int_t Nbins = 4;

void Make_ParentID(TString targetOption = "C", TString kinvarOption = "Q2", TString StoreOption = "") {
  // 1) Draw Invariant Mass Difference of generated omegas with parent-id cuts
  // 2) Store histograms

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *mcChain = GetThreePionFinderChain(targetOption, "sim");

  /*** MAIN ***/

  // about kinvar option
  TString kinvarTitle;
  Double_t EdgesKinvar[Nbins + 1];
  if (kinvarOption == "Q2") {
    kinvarTitle = "Q^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) {
      EdgesKinvar[i] = kEdgesQ2[i];
    }
  } else if (kinvarOption == "Nu") {
    kinvarTitle = "#nu";
    for (Int_t i = 0; i < Nbins + 1; i++) {
      EdgesKinvar[i] = kEdgesNu[i];
    }
  } else if (kinvarOption == "wZ") {
    kinvarTitle = "z_{h}";
    for (Int_t i = 0; i < Nbins + 1; i++) {
      EdgesKinvar[i] = kEdgesZ[i];
    }
  } else if (kinvarOption == "wPt2") {
    kinvarTitle = "p_{T}^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) {
      EdgesKinvar[i] = kEdgesPt2[i];
    }
  }

  Int_t plotNbins = 240;
  Double_t plotMin = 0.65;
  Double_t plotMax = 0.91;
  TString histProperties = Form("(%d, %f, %f)", plotNbins, plotMin, plotMax);

  TString auxCut;
  TCut CutBin;

  /*** HISTOGRAMS, FUNCTIONS AND PARAMETERS ***/

  TH1D *mcHist[Nbins];

  // loop over bins
  for (Int_t i = 0; i < Nbins; i++) {
    // prepare histograms
    auxCut = Form("%f", EdgesKinvar[i]);
    auxCut += " < mc_" + kinvarOption + " && mc_" + kinvarOption + " < ";
    auxCut += Form("%f", EdgesKinvar[i + 1]);
    CutBin = auxCut;

    mcChain->Draw(Form("mc_wD>>hist_%i", i) + histProperties, gCutDIS_MC && gCutParentID_Omega && CutBin, "goff");
    mcHist[i] = (TH1D *)gROOT->FindObject(Form("hist_%i", i));

    SetMyHistStyle(mcHist[i]);
    mcHist[i]->SetLineColor(myMagenta);
    mcHist[i]->SetLineWidth(3);
  }

  /*** FIX Y-AXIS ***/

  Double_t MaxRangeMC = 0;
  // loop over bins
  for (Int_t i = 0; i < Nbins; i++) {
    if (mcHist[i]->GetMaximum() > MaxRangeMC) {
      MaxRangeMC = mcHist[i]->GetMaximum();
    }
  }

  /*** DRAW ***/

  SetMyStyle();
  gStyle->SetOptStat(10);

  const Int_t Nx = 2;
  const Int_t Ny = 2;

  TString CanvasName = "parent-id_" + targetOption + "_" + kinvarOption;
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 2160);
  c->Divide(Nx, Ny, 0.0001, 0.0001);

  Int_t counter = 1;
  // loop over bins
  for (Int_t i = 0; i < Nbins; i++) {

    // title
    auxCut = Form("%.2f", EdgesKinvar[i]);
    auxCut += " < " + kinvarTitle + " < ";
    auxCut += Form("%.2f", EdgesKinvar[i + 1]);
    auxCut += ", " + targetOption + " Gen. Sim.";

    // style
    mcHist[i]->SetTitle("");

    mcHist[i]->GetYaxis()->SetRangeUser(0, 1.25 * MaxRangeMC);
    mcHist[i]->GetYaxis()->SetTitle("Counts");
    mcHist[i]->GetYaxis()->SetTitleSize(0.04);
    mcHist[i]->GetYaxis()->SetTickSize(0.02);
    mcHist[i]->GetYaxis()->SetMaxDigits(3);

    mcHist[i]->GetXaxis()->SetTitle("#Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
    mcHist[i]->GetXaxis()->SetTitleOffset(1.2);
    mcHist[i]->GetXaxis()->SetTitleSize(0.04);
    // mcHist[i]->GetXaxis()->SetTickSize(0.05);
    mcHist[i]->GetXaxis()->SetLabelSize(0.03);

    mcHist[i]->GetXaxis()->SetNdivisions(412);

    c->cd(counter);

    mcHist[i]->Draw("HIST");

    // title and parameters
    TPaveText *pav = new TPaveText(0.18, 0.85, 0.43, 0.90, "NDC NB");  // no border
    pav->AddText(auxCut);                                              // Title
    ((TText *)pav->GetListOfLines()->Last())->SetTextSize(0.035);
    pav->SetBorderSize(0);
    pav->SetFillStyle(0);
    pav->SetTextAlign(12);
    pav->Draw();

    gPad->Update();
    TPaveStats *st = (TPaveStats *)mcHist[i]->FindObject("stats");
    st->SetX1NDC(0.68);
    st->SetX2NDC(0.92);
    st->SetY1NDC(0.85);
    st->SetY2NDC(0.90);

    // c->Update();

    counter++;
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_mc";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);

    // create output file
    TString OutputFileName = OutputDir + "/" + CanvasName + ".root";
    TFile *RootOutputFile = new TFile(OutputFileName, "RECREATE");

    c->Write();

    // loop over bins
    for (Int_t i = 0; i < Nbins; i++) {
      // save hist into output file
      mcHist[i]->Write();
    }

    // close output file
    RootOutputFile->Close();

    // print output file path
    std::cout << "The following file has been created: " << OutputFileName << std::endl;
  }
}
