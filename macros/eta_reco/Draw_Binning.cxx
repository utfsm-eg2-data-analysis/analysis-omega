#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Nkinvars = 4;
const Int_t Nbins = 5;

void Draw_Binning(TString targetOption = "Fe", TString StoreOption = "") {
  // Draw hardcoded binning for the eta analysis

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain = GetTwoGammaFinderChain(targetOption);
  SetAliasesEta(dataChain);

  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
  } else {  // if
    CutVertex = gCutSolid;
  }

  /*** MAIN ***/

  TString kinvarOption[4] = {"Q2", "Nu", "nZ", "nPt2"};
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

  Double_t KinvarEdges[Nkinvars][Nbins + 1];
  for (Int_t i = 0; i < Nbins + 1; i++) {
    KinvarEdges[0][i] = kEdgesQ2_Eta[i];
    KinvarEdges[1][i] = kEdgesNu_Eta[i];
    KinvarEdges[2][i] = kEdgesZ_Eta[i];
    KinvarEdges[3][i] = kEdgesPt2_Eta[i];
  }

  TH1D *dataHist[4];

  for (Int_t hh = 0; hh < Nkinvars; hh++) {
    dataChain->Draw(kinvarOption[hh] + ">>hist_" + kinvarOption[hh] + histProperties[hh],
                    gCutDIS && CutVertex && gCutPhotonsOpAngle && gCutRegion_Eta, "goff");
    dataHist[hh] = (TH1D *)gROOT->FindObject("hist_" + kinvarOption[hh]);

    // style
    SetMyHistStyle(dataHist[hh]);
    dataHist[hh]->GetYaxis()->SetTitleOffset(1.35);
    dataHist[hh]->SetLineColor(myBlack);
    dataHist[hh]->GetXaxis()->SetTitle(titleAxis[hh]);
    dataHist[hh]->GetYaxis()->SetTitle("Counts");
  }

  /*** DRAW ***/

  SetMyStyle();

  const Int_t Nx = 2;
  const Int_t Ny = 2;

  TString CanvasName = "eta-binning_";
  CanvasName += Form("%d-bins", Nbins);
  CanvasName += "_" + targetOption + "-data";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 1080, 1080);
  c->Divide(Nx, Ny, 0.001, 0.001);
  // c->SetGrid();

  Int_t counter = 0;
  for (Int_t xx = 0; xx < Nx; xx++) {
    for (Int_t yy = 0; yy < Ny; yy++) {
      counter++;
      c->cd(counter);

      dataHist[counter - 1]->Draw("E");

      for (Int_t i = 0; i < Nbins + 1; i++) {
        DrawVerticalLine(KinvarEdges[counter - 1][i], myRed, 7, 3, 1);
      }

      c->Update();
    }
  }

  c->Draw();

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_reco";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
