#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Nvars = 5;

void DrawOver_MC_and_Data(TString targetOption = "Fe", TString StoreOption = "") {
  // Draw 5 variables, to compare MC with data

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain = GetTwoGammaFinderChain(targetOption);
  SetAliasesEta(dataChain);

  TChain *mcChain = GetTwoGammaFinderChain(targetOption, "sim");

  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
  } else if (targetOption == "All") {
    CutVertex = gCutSolid || gCutLiquid;
  } else {  // solid targets
    CutVertex = gCutSolid;
  }

  TString kinvarOption[Nvars] = {"Q2", "Nu", "W", "nZ", "nPt2"};
  TString kinvarOption_MC[Nvars] = {"mc_Q2", "mc_Nu", "mc_W", "mc_nZ", "mc_nPt2"};
  TString histProperties[Nvars] = {"(100, 1, 4.1)", "(100, 2.2, 4.25)", "(100, 2.0, 3.0)", "(100, 0.5, 1.0)", "(100, 0, 1.5)"};
  TString histProperties_MC[Nvars] = {"(200, 1, 4.1)", "(200, 2.2, 4.25)", "(200, 2.0, 3.0)", "(200, 0.5, 1.0)", "(200, 0, 1.5)"};
  TString kinvarAxis[Nvars] = {"Q^{2} [GeV^{2}]", "#nu [GeV]", "W [GeV]", "Z_{h}", "p_{T}^{2} [GeV^{2}]"};

  TH1D *dataMassive[Nvars];
  TH1D *mcMassive[Nvars];

  for (Int_t k = 0; k < Nvars; k++) {
    // draw hist
    dataChain->Draw(Form(kinvarOption[k] + ">>data_%i" + histProperties[k], k),
                    gCutDIS && CutVertex && gCutPhotonsOpAngle && gCutRegion_Eta, "goff");
    dataMassive[k] = (TH1D *)gROOT->FindObject(Form("data_%i", k));

    dataMassive[k]->SetTitle("");
    dataMassive[k]->SetMarkerColor(myBlue);
    dataMassive[k]->SetLineColor(myBlue);
    dataMassive[k]->SetLineWidth(3);
    dataMassive[k]->SetFillStyle(0);

    dataMassive[k]->GetYaxis()->SetTitle("Normalized Counts");
    dataMassive[k]->GetYaxis()->SetTitleSize(0.04);
    dataMassive[k]->GetYaxis()->SetTitleOffset(1.2);
    dataMassive[k]->GetYaxis()->SetMaxDigits(3);

    dataMassive[k]->GetXaxis()->SetTitle(kinvarAxis[k]);
    dataMassive[k]->GetXaxis()->SetTitleSize(0.04);
    dataMassive[k]->GetXaxis()->SetTitleOffset(1.);

    // draw hist
    mcChain->Draw(Form(kinvarOption_MC[k] + ">>mc_%i" + histProperties_MC[k], k), gCutDIS_MC && gCutParentID_Eta, "goff");
    mcMassive[k] = (TH1D *)gROOT->FindObject(Form("mc_%i", k));

    mcMassive[k]->SetTitle("");
    mcMassive[k]->SetMarkerColor(myMagenta);
    mcMassive[k]->SetLineColor(myMagenta);
    mcMassive[k]->SetLineWidth(3);
    mcMassive[k]->SetFillStyle(0);

    /*** NORMALIZATION ***/

    dataMassive[k]->Scale(1. / (Double_t)dataMassive[k]->GetMaximum());
    mcMassive[k]->Scale(1. / (Double_t)mcMassive[k]->GetMaximum());
  }

  /*** DRAW ***/

  SetMyStyle();

  const Int_t Nx = 3;
  const Int_t Ny = 2;
  TString CanvasName = "mc-and-data_comparison_" + targetOption + "-mc";
  TCanvas *can1 = new TCanvas(CanvasName, CanvasName, 3240, 2160);
  can1->Divide(Nx, Ny, 0.001, 0.001);

  for (Int_t k = 0; k < Nvars; k++) {

    can1->cd(k + 1);

    dataMassive[k]->GetYaxis()->SetRangeUser(0., 1.2 * dataMassive[k]->GetMaximum());

    dataMassive[k]->Draw("E");
    mcMassive[k]->Draw("E SAME");

    // legend
    if (k == 0) {
      TLegend *legend = new TLegend(0.75, 0.75, 0.9, 0.9);  // x1,y1,x2,y2
      legend->AddEntry(dataMassive[k], "Data", "le");
      legend->AddEntry(mcMassive[k], "MC", "le");
      legend->SetFillStyle(0);
      legend->SetTextFont(62);
      legend->SetTextSize(0.04);
      legend->SetBorderSize(0);
      legend->Draw();
    }

    can1->Update();
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/eta_mc";
    system("mkdir -p " + OutputDir);
    can1->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}
