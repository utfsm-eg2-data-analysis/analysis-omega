#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Ntargets = 4;
const Int_t Nkinvars = 4;
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
  TString kinvarTitle[4] = {"Q^{2} [GeV^{2}]", "#nu [GeV]", "z_{h}", "p_{T}^{2} [GeV^{2}]"};

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

  // define and fill arrays
  Double_t binCenter[Nkinvars][Nbins];
  Double_t binError[Nkinvars][Nbins];
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      binCenter[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      binError[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / TMath::Sqrt(12);
    }
  }

  // create and fill graphs
  TGraphErrors *etaGraph[Nkinvars][Ntargets];
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

  /*** SET AXIS ***/

  for (Int_t k = 0; k < Nkinvars; k++) {
    // set y-axis
    etaGraph[k][0]->GetYaxis()->SetRangeUser(0., 1.2 * TMath::MaxElement(Nbins, etaGraph[k][0]->GetY()));
    etaGraph[k][0]->GetYaxis()->SetTitle("N_{#eta}^{gen}");
    etaGraph[k][0]->GetYaxis()->SetTitleSize(0.06);
    etaGraph[k][0]->GetYaxis()->SetTitleOffset(1.2);
    etaGraph[k][0]->GetYaxis()->SetMaxDigits(3);
    // set x-axis
    etaGraph[k][0]->GetXaxis()->SetLimits(EdgesKinvar[k][0], EdgesKinvar[k][Nbins]);
    etaGraph[k][0]->GetXaxis()->SetTitle(kinvarTitle[k]);
    etaGraph[k][0]->GetXaxis()->SetTitleSize(0.06);
  }

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "eta-numbers_mc";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 2160);
  c->Divide(2, 2, 0.001, 0.001);  // nx, ny, margins
  for (Int_t k = 0; k < Nkinvars; k++) {

    c->cd(k + 1);
    etaGraph[k][0]->Draw("AP");
    etaGraph[k][1]->Draw("P");
    etaGraph[k][2]->Draw("P");
    etaGraph[k][3]->Draw("P");

    // legend
    if (k == 0) {
      TLegend *legend = new TLegend(0.6, 0.65, 0.85, 0.9);  // x1,y1,x2,y2
      legend->AddEntry(etaGraph[k][0], "D (Sim. Gen.)", "pl");
      legend->AddEntry(etaGraph[k][1], "C (Sim. Gen.)", "pl");
      legend->AddEntry(etaGraph[k][2], "Fe (Sim. Gen.)", "pl");
      legend->AddEntry(etaGraph[k][3], "Pb (Sim. Gen.)", "pl");
      legend->SetFillStyle(0);
      legend->SetTextFont(62);
      legend->SetTextSize(0.04);
      legend->SetBorderSize(0);
      legend->Draw();
    }
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_mc";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
