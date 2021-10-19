#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#ifndef RADIATIVECORRECTIONS_H
#include "RadiativeCorrections.h"
#endif

void Draw2D_Grid(TString targetOption = "D", TString PartOption = "omega", TString StoreOption = "") {

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *InputChain = GetElectronsChain(targetOption);

  // related to particle option - now, get edges
  Double_t EdgesQ2_Externals[NbinsQ2_Externals + 1];
  Double_t EdgesNu_Externals[NbinsNu_Externals + 1];
  if (PartOption == "omega") {
    for (Int_t q = 0; q < NbinsQ2_Externals + 1; q++) {
      EdgesQ2_Externals[q] = kEdgesQ2_Externals_Omega[q];
    }
    for (Int_t n = 0; n < NbinsNu_Externals + 1; n++) {
      EdgesNu_Externals[n] = kEdgesNu_Externals_Omega[n];
    }
  } else {  // "eta"
    for (Int_t q = 0; q < NbinsQ2_Externals + 1; q++) {
      EdgesQ2_Externals[q] = kEdgesQ2_Externals_Eta[q];
    }
    for (Int_t n = 0; n < NbinsNu_Externals + 1; n++) {
      EdgesNu_Externals[n] = kEdgesNu_Externals_Eta[n];
    }
  }

  // set vertex cuts in GST format
  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = "TargType == 1 && vyec > -1.4 && vyec < 1.4";
  } else if (targetOption == "All") {
    CutVertex = "(TargType == 1 || TargType == 2) && vyec > -1.4 && vyec < 1.4";
  } else {  // solid targets
    CutVertex = "TargType == 2 && vyec > -1.4 && vyec < 1.4";
  }

  // define hist properties
  TString HistProperties = Form("(200, %.2f, %.2f, 200, %.2f, %.2f)", EdgesNu_Externals[0], EdgesNu_Externals[NbinsNu_Externals],
                                EdgesQ2_Externals[0], EdgesQ2_Externals[NbinsQ2_Externals]);

  TH2D *Hist;
  InputChain->Draw("Q2:Nu>>hist" + HistProperties, gCutDIS && CutVertex, "goff");
  Hist = (TH2D *)gROOT->FindObject("hist");

  SetMy2DHistStyle(Hist);
  Hist->GetYaxis()->SetTitle("Q^{2} [GeV^{2}]");
  Hist->GetXaxis()->SetTitle("#nu [GeV]");

  /*** DRAW ***/

  SetMy2DStyle();

  // define canvas
  TString CanvasName = "grid-for-externals_" + PartOption + "-binning";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  c->SetFrameLineWidth(2);

  Hist->Draw("COLZ");

  CustomizePaletteSize(Hist);

  for (Int_t q = 0; q < NbinsQ2_Externals + 1; q++) {
    DrawHorizontalLine(EdgesQ2_Externals[q], myGreen, kSolid, 5, 0);
  }

  for (Int_t n = 0; n < NbinsNu_Externals + 1; n++) {
    DrawVerticalLine(EdgesNu_Externals[n], myGreen, kSolid, 5, 1);
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/rad-corr_electron";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
