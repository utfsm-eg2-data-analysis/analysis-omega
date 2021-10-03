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

void Make_Binning(TString targetOption = "Pb", Int_t Nbins = 4, TString StoreOption = "") {
  // Calculate an equally-distributed binning for the omega analysis, and draw it

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain = GetThreePionFinderChain(targetOption);
  SetAliases(dataChain);

  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
  }

  /*** MAIN ***/

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

  TH1D *dataHist[4];

  for (Int_t hh = 0; hh < 4; hh++) {
    dataChain->Draw(kinvarOption[hh] + ">>hist_" + kinvarOption[hh] + histProperties[hh],
                    gCutDIS && gCutPi0 && CutVertex && gCutKaons && gCutPhotonsOpAngle && gCutRegion, "goff");
    dataHist[hh] = (TH1D *)gROOT->FindObject("hist_" + kinvarOption[hh]);

    // style
    SetMyHistStyle(dataHist[hh]);
    dataHist[hh]->GetYaxis()->SetTitleOffset(1.35);
    dataHist[hh]->SetLineColor(myBlue);
    dataHist[hh]->GetXaxis()->SetTitle(titleAxis[hh]);
    dataHist[hh]->GetYaxis()->SetTitle("Counts");
  }

  /*** DRAW ***/

  SetMyStyle();

  const Int_t Nx = 2;
  const Int_t Ny = 2;

  TString CanvasName = "omega-binning_";
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

      Double_t xq[Nbins];  // percentages
      Double_t yq[Nbins];  // output array

      // draw first line
      DrawVerticalLine(kinvarLimit[counter - 1][0], myOrange, 7, 3, 1);

      for (Int_t i = 0; i < Nbins; i++) {
        xq[i] = (Double_t)(i + 1) / (Double_t)Nbins;
        dataHist[counter - 1]->GetQuantiles(Nbins, yq, xq);
        // print information
        if (i == 0) {
          std::cout << "edges" << kinvarOption[counter - 1] << "[" << (Nbins + 1) << "] = {" << dataHist[counter - 1]->GetBinLowEdge(1)
                    << ", " << yq[i] << ", ";
        } else if (i == (Nbins - 1)) {
          std::cout << yq[i] << "};" << std::endl;
        } else {
          std::cout << yq[i] << ", ";
        }
        // draw lines
        if (i != (Nbins - 1)) {
          DrawVerticalLine(yq[i], myOrange, 7, 3, 1);
        }
        c->Update();
      }

      // draw last line
      DrawVerticalLine(kinvarLimit[counter - 1][1], myOrange, 7, 3, 1);
    }
  }

  c->Draw();

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_reco";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
