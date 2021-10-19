#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Nkinvars = 4;
const Int_t Ntargets = 4;
const Int_t Nbins = 5;

void Draw_EtaNumbers(TString StoreOption = "") {
  // draw the obtained number of etas after integrating the eta invariant mass signal
  // with the help of the parent id (mc)

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  Double_t fitEta[Nkinvars][Ntargets][Nbins];
  Double_t fitEtaError[Nkinvars][Ntargets][Nbins];

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

  Double_t EdgesKinvar[Nkinvars][Nbins + 1];
  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[0][i] = kEdgesQ2_Eta[i];
    EdgesKinvar[1][i] = kEdgesNu_Eta[i];
    EdgesKinvar[2][i] = kEdgesZ_Eta[i];
    EdgesKinvar[3][i] = kEdgesPt2_Eta[i];
  }

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  TFile *rootInputFile[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      rootInputFile[k][t] = new TFile(gProDir + "/gfx/eta_mc/parent-id_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      // loop over bins
      for (Int_t i = 0; i < Nbins; i++) {
        TH1D *Hist = (TH1D *)rootInputFile[k][t]->Get(Form("hist_%i", i));
        fitEta[k][t][i] = Hist->GetEntries();
        fitEtaError[k][t][i] = TMath::Sqrt(fitEta[k][t][i]);
      }
    }
  }

  /*** GRAPHS ***/

  // creating and filling histograms
  TGraphErrors *etaGraph[Nkinvars][Ntargets];

  // define arrays
  Double_t binCenter[Nkinvars][Nbins];
  Double_t binError[Nkinvars][Nbins];

  // fill arrays

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      binCenter[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      binError[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / TMath::Sqrt(12);
    }
  }

  // set graphs
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      etaGraph[k][t] = new TGraphErrors(Nbins, binCenter[k], fitEta[k][t], binError[k], fitEtaError[k][t]);

      // style
      etaGraph[k][t]->SetTitle("");
      etaGraph[k][t]->SetMarkerColor(targetColor[t]);
      etaGraph[k][t]->SetLineColor(targetColor[t]);
      etaGraph[k][t]->SetLineWidth(3);
      etaGraph[k][t]->SetMarkerStyle(20);
      etaGraph[k][t]->SetMarkerSize(1.5);
    }
  }

  /*** SET Y AXIS ***/

  for (Int_t k = 0; k < Nkinvars; k++) {
    etaGraph[k][0]->GetYaxis()->SetRangeUser(0., 1.2 * TMath::MaxElement(Nbins, etaGraph[k][0]->GetY()));

    etaGraph[k][0]->GetYaxis()->SetTitle("N_{#eta}^{gen}");
    etaGraph[k][0]->GetYaxis()->SetTitleSize(0.06);
    etaGraph[k][0]->GetYaxis()->SetTitleOffset(1.2);
    etaGraph[k][0]->GetYaxis()->SetMaxDigits(3);

    etaGraph[k][0]->GetXaxis()->SetTitle(titleAxis[k]);
    etaGraph[k][0]->GetXaxis()->SetTitleSize(0.06);
  }

  /*** FIX Y-AXIS ***/

  Double_t MaxRangeMC[Nkinvars] = {0, 0, 0, 0};
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      // get the maximum of an array of length Nbins, and compare it with MaxRangeMC
      if (TMath::MaxElement(Nbins, etaGraph[k][t]->GetY()) > MaxRangeMC[k]) {
        MaxRangeMC[k] = TMath::MaxElement(Nbins, etaGraph[k][t]->GetY());
      }
    }
  }

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "eta-numbers_mc";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 2160);
  c->Divide(2, 2, 0.001, 0.001);  // nx, ny, margins

  // set y-axis for all plots
  etaGraph[0][0]->GetYaxis()->SetRangeUser(0., 1.2 * MaxRangeMC[0]);
  etaGraph[1][0]->GetYaxis()->SetRangeUser(0., 1.2 * MaxRangeMC[1]);
  etaGraph[2][0]->GetYaxis()->SetRangeUser(0., 1.2 * MaxRangeMC[2]);
  etaGraph[3][0]->GetYaxis()->SetRangeUser(0., 1.2 * MaxRangeMC[3]);

  c->cd(1);
  etaGraph[0][0]->Draw("AP");
  etaGraph[0][1]->Draw("P");
  etaGraph[0][2]->Draw("P");
  etaGraph[0][3]->Draw("P");

  // legend
  TLegend *legend = new TLegend(0.6, 0.65, 0.85, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(etaGraph[0][0], "D (Sim. Gen.)", "pl");
  legend->AddEntry(etaGraph[0][1], "C (Sim. Gen.)", "pl");
  legend->AddEntry(etaGraph[0][2], "Fe (Sim. Gen.)", "pl");
  legend->AddEntry(etaGraph[0][3], "Pb (Sim. Gen.)", "pl");
  legend->SetFillStyle(0);
  legend->SetTextFont(62);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw();

  c->cd(2);
  etaGraph[1][0]->Draw("AP");
  etaGraph[1][1]->Draw("P");
  etaGraph[1][2]->Draw("P");
  etaGraph[1][3]->Draw("P");

  c->cd(3);
  etaGraph[2][0]->Draw("AP");
  etaGraph[2][1]->Draw("P");
  etaGraph[2][2]->Draw("P");
  etaGraph[2][3]->Draw("P");

  c->cd(4);
  etaGraph[3][0]->Draw("AP");
  etaGraph[3][1]->Draw("P");
  etaGraph[3][2]->Draw("P");
  etaGraph[3][3]->Draw("P");

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_mc";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
