#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Ntargets = 4;
const Int_t NbinsPhiPQ = 5;

void Draw_RadCorrFactors(TString StoreOption = "") {
  // Draw the obtained Radiative Correction Factors obtained for all targets, in PhiPQ binning

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** MAIN ***/

  Double_t RadCorrFactor[Ntargets][NbinsPhiPQ];

  TString titleAxis = "#phi_{PQ} [deg]";
  Double_t EdgesPhiPQ[NbinsPhiPQ + 1] = {-180., -108., -36., 36., 108., 180.};
  TString histProperties = Form("(%i, %.2f, %.2f)", NbinsPhiPQ, EdgesPhiPQ[0], EdgesPhiPQ[NbinsPhiPQ]);

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  std::ifstream InputFile[Ntargets];

  // loop over targets
  for (Int_t t = 0; t < Ntargets; t++) {

    InputFile[t].open(gProDir + "/gfx/rad-corr_eta/RCFactor_eta_" + targetString[t] + ".txt", std::ios::in);

    std::string auxLine;
    TString auxString[7];  // number of columns in the .txt file
    Int_t countLine = 0;
    Int_t binInPhiPQ;
    TObjString *auxObjString;

    while (getline(InputFile[t], auxLine)) {
      // ignore the first line that represents the name of the columns
      if (countLine > 0) {
        // retrieve each column
        for (Int_t i = 0; i < 7; i++) {
          auxObjString = (TObjString *)(((TString)auxLine).Tokenize("\t")->At(i));
          auxString[i] = auxObjString->String();
        }
        // store variables of interest
        // Column 0: BinInPhiPQ
        binInPhiPQ = auxString[0].Atoi();
        // Column 6 or 7: Rad Corr Factor
        RadCorrFactor[t][binInPhiPQ] = auxString[6].Atof();
      }
      countLine++;
    }
  }

  /*** GRAPHS ***/

  // define arrays
  Double_t binCenter[NbinsPhiPQ];
  Double_t binError[NbinsPhiPQ];
  Double_t empty[NbinsPhiPQ];

  // fill arrays
  for (Int_t i = 0; i < NbinsPhiPQ; i++) {
    empty[i] = 0;
    binCenter[i] = (EdgesPhiPQ[i] + EdgesPhiPQ[i + 1]) / 2.;
    binError[i] = (EdgesPhiPQ[i + 1] - EdgesPhiPQ[i]) / TMath::Sqrt(12);
  }

  // set graphs
  TGraphErrors *RadCorrGraph[Ntargets];

  for (Int_t t = 0; t < Ntargets; t++) {
    RadCorrGraph[t] = new TGraphErrors(NbinsPhiPQ, binCenter, RadCorrFactor[t], binError, empty);

    // style
    RadCorrGraph[t]->SetTitle("");
    RadCorrGraph[t]->SetMarkerColor(targetColor[t]);
    RadCorrGraph[t]->SetLineColor(targetColor[t]);
    RadCorrGraph[t]->SetLineWidth(3);
    RadCorrGraph[t]->SetMarkerStyle(20);
    RadCorrGraph[t]->SetMarkerSize(1.5);
  }

  // set y-axis
  RadCorrGraph[0]->GetYaxis()->SetRangeUser(0.9, 1.0);
  RadCorrGraph[0]->GetYaxis()->SetTitle("#delta^{RC}");
  RadCorrGraph[0]->GetYaxis()->SetTitleSize(0.05);
  RadCorrGraph[0]->GetYaxis()->SetTitleOffset(1.4);
  RadCorrGraph[0]->GetYaxis()->SetMaxDigits(3);

  // set x-axis
  RadCorrGraph[0]->GetXaxis()->SetLimits(EdgesPhiPQ[0], EdgesPhiPQ[NbinsPhiPQ]);
  RadCorrGraph[0]->GetXaxis()->SetTitle(titleAxis);
  RadCorrGraph[0]->GetXaxis()->SetTitleSize(0.05);

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "rad-corr-factors";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  RadCorrGraph[0]->Draw("AP");
  RadCorrGraph[1]->Draw("P");
  RadCorrGraph[2]->Draw("P");
  RadCorrGraph[3]->Draw("P");

  // legend
  TLegend *legend = new TLegend(0.2, 0.65, 0.4, 0.9);  // x1,y1,x2,y2
  legend->SetTextFont(62);
  legend->SetTextSize(0.04);
  legend->SetHeader("Radiative Correction Factors by HAPRAD");
  legend->AddEntry(RadCorrGraph[0], "D", "pl");
  legend->AddEntry(RadCorrGraph[1], "C", "pl");
  legend->AddEntry(RadCorrGraph[2], "Fe", "pl");
  legend->AddEntry(RadCorrGraph[3], "Pb", "pl");
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->Draw();

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/rad-corr_eta";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
