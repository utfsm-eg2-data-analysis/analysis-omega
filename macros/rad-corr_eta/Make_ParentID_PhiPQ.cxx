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
const Int_t NbinsPhiPQ = 5;

void Make_ParentID_PhiPQ(TString targetOption = "C", TString StoreOption = "") {
  // 1) Draw Invariant Mass Difference of generated etas with parent-id cuts on PhiPQ binning
  // 2) Store histograms

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *mcChain = GetTwoGammaFinderChain(targetOption, "sim");

  /*** MAIN ***/

  // about kinvar option
  TString kinvarOption = "nPhiPQ";
  TString kinvarTitle = "#phi_{PQ}";
  Double_t EdgesPhiPQ[NbinsPhiPQ + 1] = {-180, -108, -36, 36, 108, 180};

  Int_t plotNbins = 200;
  Double_t plotMin = 0.26;
  Double_t plotMax = 0.8;
  TString histProperties = Form("(%i, %f, %f)", plotNbins, plotMin, plotMax);

  TString auxCut;
  TCut CutBin;

  /*** HISTOGRAMS, FUNCTIONS AND PARAMETERS ***/

  TH1D *mcHist[NbinsPhiPQ];

  // loop over bins
  for (Int_t i = 0; i < NbinsPhiPQ; i++) {
    // prepare histograms
    auxCut = Form("%f", EdgesPhiPQ[i]);
    auxCut += " < mc_" + kinvarOption + " && mc_" + kinvarOption + " < ";
    auxCut += Form("%f", EdgesPhiPQ[i + 1]);
    CutBin = auxCut;

    mcChain->Draw(Form("mc_nM>>hist_%i", i) + histProperties, gCutDIS_MC && gCutParentID_Eta && CutBin, "goff");
    mcHist[i] = (TH1D *)gROOT->FindObject(Form("hist_%i", i));

    SetMyHistStyle(mcHist[i]);
    mcHist[i]->SetLineColor(myMagenta);
    mcHist[i]->SetLineWidth(3);
  }

  /*** FIX Y-AXIS ***/

  Double_t MaxRangeMC = 0;
  // loop over bins
  for (Int_t i = 0; i < NbinsPhiPQ; i++) {
    if (mcHist[i]->GetMaximum() > MaxRangeMC) {
      MaxRangeMC = mcHist[i]->GetMaximum();
    }
  }

  /*** DRAW ***/

  SetMyStyle();
  gStyle->SetOptStat(10);

  const Int_t Nx = 3;
  const Int_t Ny = 2;

  TString CanvasName = "parent-id_" + targetOption + "_" + kinvarOption + "_mc";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 3240, 2160);
  c->Divide(Nx, Ny, 0.0001, 0.0001);

  Int_t counter = 1;
  // loop over bins
  for (Int_t i = 0; i < NbinsPhiPQ; i++) {

    // title
    auxCut = Form("%.0f", EdgesPhiPQ[i]);
    auxCut += " < " + kinvarTitle + " < ";
    auxCut += Form("%.0f", EdgesPhiPQ[i + 1]);
    auxCut += ", " + targetOption + " gen. sim.";

    // style
    mcHist[i]->SetTitle("");

    mcHist[i]->GetYaxis()->SetRangeUser(0, 1.25 * MaxRangeMC);
    mcHist[i]->GetYaxis()->SetTitle("Counts");
    mcHist[i]->GetYaxis()->SetTitleSize(0.04);
    mcHist[i]->GetYaxis()->SetTickSize(0.02);
    mcHist[i]->GetYaxis()->SetMaxDigits(3);

    mcHist[i]->GetXaxis()->SetTitle("m(#gamma#gamma) [GeV]");
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
    TString OutputDir = gProDir + "/gfx/rad-corr_eta";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);

    // create output file
    TString OutputFileName = OutputDir + "/" + CanvasName + ".root";
    TFile *RootOutputFile = new TFile(OutputFileName, "RECREATE");

    c->Write();

    // loop over bins
    for (Int_t i = 0; i < NbinsPhiPQ; i++) {
      // save hist into output file
      mcHist[i]->Write();
    }

    // close output file
    RootOutputFile->Close();

    // print output file path
    std::cout << "The following file has been created: " << OutputFileName << std::endl;
  }
}
