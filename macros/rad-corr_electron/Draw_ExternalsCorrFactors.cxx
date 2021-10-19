#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#ifndef RADIATIVECORRECTIONS_H
#include "RadiativeCorrections.h"
#endif

const Int_t Ntargets = 4;

void Draw_ExternalsCorrFactors(TString PartOption = "omega", TString StoreOption = "") {
  // Plot radiative correction factors for electrons obtained from EXTERNALS

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

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

  /*** MAIN ***/

  // related to target
  TString targetSufix[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[4] = {myGreen, myRed, myBlue, myBlack};

  std::ifstream ExternalsFiles[Ntargets];
  Double_t RadCorrFactor[Ntargets][NbinsQ2_Externals][NbinsNu_Externals];

  // loop over targets
  for (Int_t tt = 0; tt < Ntargets; tt++) {

    ExternalsFiles[tt].open(gProDir + "/gfx/rad-corr_electron/clas_" + PartOption + "_" + targetSufix[tt] + ".out", std::ios::in);

    std::string auxLine;
    TString auxString[13];  // number of columns in the .out files
    Int_t countLine = 0;
    Int_t binInNu;
    Int_t binInQ2;

    while (getline(ExternalsFiles[tt], auxLine)) {
      // given the first line represents the name of the columns
      if (countLine > 0) {
        for (Int_t i = 0; i < 13; i++) {
          auxString[i] = ((TObjString *)(((TString)auxLine).Tokenize("   ")->At(i)))->String();
        }
        binInNu = (countLine - 1) / NbinsQ2_Externals;
        binInQ2 = (countLine - 1) - NbinsQ2_Externals * binInNu;
        // Column 0: Ebeam
        // Column 5: Sig_Born
        // Column 8: Sig_Rad
        RadCorrFactor[tt][binInQ2][binInNu] = auxString[8].Atof() / auxString[5].Atof();  // Sig_Rad / Sig_Born
      }
      countLine++;
    }

    // close input file
    ExternalsFiles[tt].close();
  }

  /*** GRAPHS ***/

  // fill arrays
  Double_t Empty[NbinsNu_Externals];
  Double_t BinGeoCenter[NbinsNu_Externals];  // geometrical center
  for (Int_t n = 0; n < NbinsNu_Externals; n++) {
    Empty[n] = 0;
    BinGeoCenter[n] = (EdgesNu_Externals[n] + EdgesNu_Externals[n + 1]) / 2.;
  }

  // define graphs
  TGraphErrors *RCgraph[Ntargets][NbinsQ2_Externals];
  for (Int_t tt = 0; tt < Ntargets; tt++) {
    for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
      RCgraph[tt][q] = new TGraphErrors(NbinsNu_Externals, BinGeoCenter, RadCorrFactor[tt][q], Empty, Empty);
      // set graphs' titles and axis
      if (tt == 0) {
        RCgraph[tt][q]->SetTitle(Form("%.2f < Q^{2} < %.2f", EdgesQ2_Externals[q], EdgesQ2_Externals[q + 1]));
        RCgraph[tt][q]->GetXaxis()->SetTitle("#nu (GeV)");
        RCgraph[tt][q]->GetYaxis()->SetTitle("#delta^{RC}");
        RCgraph[tt][q]->GetYaxis()->SetRangeUser(1., 1.5);
      }
      // set graphs' style
      RCgraph[tt][q]->SetMarkerStyle(20);
      RCgraph[tt][q]->SetMarkerSize(2);
      RCgraph[tt][q]->SetMarkerColor(targetColor[tt]);
    }
  }

  /*** DRAW ***/

  SetMyStyle();
  gStyle->SetTitleFontSize(0.04);
  gStyle->SetTitleY(1.005);

  const Int_t Nx = 3;
  const Int_t Ny = 2;
  TString CanvasName = "externals-factors_" + PartOption + "-binning";
  TCanvas *can1 = new TCanvas(CanvasName, CanvasName, Nx * 1080, Ny * 1080);
  can1->Divide(Nx, Ny, 0.001, 0.001);

  for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
    can1->cd(q + 1);
    gPad->SetGridy(1);

    RCgraph[0][q]->Draw("AP");
    RCgraph[1][q]->Draw("P");
    RCgraph[2][q]->Draw("P");
    RCgraph[3][q]->Draw("P");

    // legend
    TLegend *legend = new TLegend(0.2, 0.6, 0.3, 0.9);  // x1,y1,x2,y2
    legend->AddEntry(RCgraph[0][q], "D", "p");
    legend->AddEntry(RCgraph[1][q], "C", "p");
    legend->AddEntry(RCgraph[2][q], "Fe", "p");
    legend->AddEntry(RCgraph[3][q], "Pb", "p");
    legend->SetFillStyle(1001);
    legend->SetFillColor(kWhite);
    legend->SetTextFont(62);
    legend->SetTextSize(0.04);
    legend->SetBorderSize(0);
    legend->Draw();
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/rad-corr_electron";
    system("mkdir -p " + OutputDir);
    can1->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
