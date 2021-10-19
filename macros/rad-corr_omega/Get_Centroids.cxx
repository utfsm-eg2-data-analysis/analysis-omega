#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t NbinsPhiPQ = 4;
const Double_t EdgesPhiPQ[NbinsPhiPQ + 1] = {-180., -90., 0, 90., 180.};
const Int_t Nbins = 4;  // number of bins for each other variable

void Get_Centroids(TString targetOption = "D") {
  // get the acc. corr. 5-dim centroids for each bin in PhiPQ

  TChain *dataChain = GetThreePionFinderChain(targetOption);
  SetAliases(dataChain);

  TChain *simChain = GetThreePionFinderChain(targetOption, "sim");
  SetAliases(simChain);

  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
  } else {  // in case of solid targets: C, Fe, Pb, A
    CutVertex = gCutSolid;
  }

  /*** HISTOGRAMS ***/

  // define data histograms
  TH1D *histQ2_Data[NbinsPhiPQ];
  TH1D *histNu_Data[NbinsPhiPQ];
  TH1D *histZ_Data[NbinsPhiPQ];
  TH1D *histPt2_Data[NbinsPhiPQ];
  TH1D *histPhiPQ_Data[NbinsPhiPQ];

  // define MC generated/thrown histograms
  TH1D *histQ2_MC[NbinsPhiPQ];
  TH1D *histNu_MC[NbinsPhiPQ];
  TH1D *histZ_MC[NbinsPhiPQ];
  TH1D *histPt2_MC[NbinsPhiPQ];
  TH1D *histPhiPQ_MC[NbinsPhiPQ];

  // define simulations reconstructed/accepted histograms
  TH1D *histQ2_Sim[NbinsPhiPQ];
  TH1D *histNu_Sim[NbinsPhiPQ];
  TH1D *histZ_Sim[NbinsPhiPQ];
  TH1D *histPt2_Sim[NbinsPhiPQ];
  TH1D *histPhiPQ_Sim[NbinsPhiPQ];

  // define acceptance histograms
  TH1D *histQ2_Acceptance[NbinsPhiPQ];
  TH1D *histNu_Acceptance[NbinsPhiPQ];
  TH1D *histZ_Acceptance[NbinsPhiPQ];
  TH1D *histPt2_Acceptance[NbinsPhiPQ];
  TH1D *histPhiPQ_Acceptance[NbinsPhiPQ];

  // define corrected data histograms
  TH1D *histQ2_Corr[NbinsPhiPQ];
  TH1D *histNu_Corr[NbinsPhiPQ];
  TH1D *histZ_Corr[NbinsPhiPQ];
  TH1D *histPt2_Corr[NbinsPhiPQ];
  TH1D *histPhiPQ_Corr[NbinsPhiPQ];

  Double_t meanQ2[NbinsPhiPQ];
  Double_t meanNu[NbinsPhiPQ];
  Double_t meanZ[NbinsPhiPQ];
  Double_t meanPt2[NbinsPhiPQ];
  Double_t meanPhiPQ[NbinsPhiPQ];

  TCut CutBin;
  TCut CutBin_MC;

  for (Int_t i = 0; i < NbinsPhiPQ; i++) {

    // set bin for data and sim. rec.
    CutBin = Form(
        "Q2 > %.2f && Q2 < %.2f && Nu > %.2f && Nu < %.2f && wZ > %.2f && wZ < %.2f && wPt2 > %.2f && wPt2 < %.2f && wPhiPQ > %.2f && "
        "wPhiPQ < %.2f",
        kEdgesQ2[0], kEdgesQ2[Nbins], kEdgesNu[0], kEdgesNu[Nbins], kEdgesZ[0], kEdgesZ[Nbins], kEdgesPt2[0], kEdgesPt2[Nbins],
        EdgesPhiPQ[i], EdgesPhiPQ[i + 1]);

    // set bin edges for mc
    CutBin_MC = Form(
        "mc_Q2 > %.2f && mc_Q2 < %.2f && mc_Nu > %.2f && mc_Nu < %.2f && mc_wZ > %.2f && mc_wZ < %.2f && mc_wPt2 > %.2f && mc_wPt2 < %.2f "
        "&& "
        "mc_wPhiPQ > %.2f && "
        "mc_wPhiPQ < %.2f",
        kEdgesQ2[0], kEdgesQ2[Nbins], kEdgesNu[0], kEdgesNu[Nbins], kEdgesZ[0], kEdgesZ[Nbins], kEdgesPt2[0], kEdgesPt2[Nbins],
        EdgesPhiPQ[i], EdgesPhiPQ[i + 1]);

    /*** DATA HISTOGRAMS ***/

    // Q2
    dataChain->Draw(Form("Q2>>data_Q2_%i(100, %.2f, %.2f)", i, kEdgesQ2[0], kEdgesQ2[Nbins]),
                    gCutDIS && CutVertex && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin, "goff");
    histQ2_Data[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("data_Q2_%i", i));
    // Nu
    dataChain->Draw(Form("Nu>>data_Nu_%i(100, %.2f, %.2f)", i, kEdgesNu[0], kEdgesNu[Nbins]),
                    gCutDIS && CutVertex && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin, "goff");
    histNu_Data[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("data_Nu_%i", i));
    // Z
    dataChain->Draw(Form("wZ>>data_Z_%i(100, %.2f, %.2f)", i, kEdgesZ[0], kEdgesZ[Nbins]),
                    gCutDIS && CutVertex && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin, "goff");
    histZ_Data[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("data_Z_%i", i));
    // Pt2
    dataChain->Draw(Form("wPt2>>data_Pt2_%i(100, %.2f, %.2f)", i, kEdgesPt2[0], kEdgesPt2[Nbins]),
                    gCutDIS && CutVertex && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin, "goff");
    histPt2_Data[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("data_Pt2_%i", i));
    // PhiPQ
    dataChain->Draw(Form("wPhiPQ>>data_PhiPQ_%i(36, %.2f, %.2f)", i, EdgesPhiPQ[0], EdgesPhiPQ[NbinsPhiPQ]),
                    gCutDIS && CutVertex && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin, "goff");
    histPhiPQ_Data[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("data_PhiPQ_%i", i));

    /*** MC GEN. HISTOGRAMS ***/

    // Q2
    simChain->Draw(Form("mc_Q2>>mc_Q2_%i(100, %.2f, %.2f)", i, kEdgesQ2[0], kEdgesQ2[Nbins]), gCutDIS_MC && gCutParentID_Omega && CutBin_MC,
                   "goff");
    histQ2_MC[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("mc_Q2_%i", i));
    // Nu
    simChain->Draw(Form("mc_Nu>>mc_Nu_%i(100, %.2f, %.2f)", i, kEdgesNu[0], kEdgesNu[Nbins]), gCutDIS_MC && gCutParentID_Omega && CutBin_MC,
                   "goff");
    histNu_MC[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("mc_Nu_%i", i));
    // Z
    simChain->Draw(Form("mc_wZ>>mc_Z_%i(100, %.2f, %.2f)", i, kEdgesZ[0], kEdgesZ[Nbins]), gCutDIS_MC && gCutParentID_Omega && CutBin_MC,
                   "goff");
    histZ_MC[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("mc_Z_%i", i));
    // Pt2
    simChain->Draw(Form("mc_wPt2>>mc_Pt2_%i(100, %.2f, %.2f)", i, kEdgesPt2[0], kEdgesPt2[Nbins]),
                   gCutDIS_MC && gCutParentID_Omega && CutBin_MC, "goff");
    histPt2_MC[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("mc_Pt2_%i", i));
    // PhiPQ
    simChain->Draw(Form("mc_wPhiPQ>>mc_PhiPQ_%i(36, %.2f, %.2f)", i, EdgesPhiPQ[0], EdgesPhiPQ[NbinsPhiPQ]),
                   gCutDIS_MC && gCutParentID_Omega && CutBin_MC, "goff");
    histPhiPQ_MC[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("mc_PhiPQ_%i", i));

    /*** SIM. REC. HISTOGRAMS ***/

    // Q2
    simChain->Draw(Form("Q2>>sim_Q2_%i(100, %.2f, %.2f)", i, kEdgesQ2[0], kEdgesQ2[Nbins]),
                   gCutDIS && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin, "goff");
    histQ2_Sim[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("sim_Q2_%i", i));
    // Nu
    simChain->Draw(Form("Nu>>sim_Nu_%i(100, %.2f, %.2f)", i, kEdgesNu[0], kEdgesNu[Nbins]),
                   gCutDIS && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin, "goff");
    histNu_Sim[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("sim_Nu_%i", i));
    // Z
    simChain->Draw(Form("wZ>>sim_Z_%i(100, %.2f, %.2f)", i, kEdgesZ[0], kEdgesZ[Nbins]),
                   gCutDIS && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin, "goff");
    histZ_Sim[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("sim_Z_%i", i));
    // Pt2
    simChain->Draw(Form("wPt2>>sim_Pt2_%i(100, %.2f, %.2f)", i, kEdgesPt2[0], kEdgesPt2[Nbins]),
                   gCutDIS && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin, "goff");
    histPt2_Sim[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("sim_Pt2_%i", i));
    // PhiPQ
    simChain->Draw(Form("wPhiPQ>>sim_PhiPQ_%i(36, %.2f, %.2f)", i, EdgesPhiPQ[0], EdgesPhiPQ[NbinsPhiPQ]),
                   gCutDIS && gCutPi0 && gCutKaons && gCutPhotonsOpAngle && CutBin, "goff");
    histPhiPQ_Sim[i] = (TH1D *)gDirectory->GetList()->FindObject(Form("sim_PhiPQ_%i", i));

    /*** CALCULATE ACCEPTANCE ***/

    // Q2
    histQ2_Acceptance[i] = new TH1D(Form("acc_Q2_%i", i), "", 100, kEdgesQ2[0], kEdgesQ2[Nbins]);
    histQ2_Acceptance[i]->Divide(histQ2_Sim[i], histQ2_MC[i], 1, 1, "B");
    // Nu
    histNu_Acceptance[i] = new TH1D(Form("acc_Nu_%i", i), "", 100, kEdgesNu[0], kEdgesNu[Nbins]);
    histNu_Acceptance[i]->Divide(histNu_Sim[i], histNu_MC[i], 1, 1, "B");
    // Z
    histZ_Acceptance[i] = new TH1D(Form("acc_Z_%i", i), "", 100, kEdgesZ[0], kEdgesZ[Nbins]);
    histZ_Acceptance[i]->Divide(histZ_Sim[i], histZ_MC[i], 1, 1, "B");
    // Pt2
    histPt2_Acceptance[i] = new TH1D(Form("acc_Pt2_%i", i), "", 100, kEdgesPt2[0], kEdgesPt2[Nbins]);
    histPt2_Acceptance[i]->Divide(histPt2_Sim[i], histPt2_MC[i], 1, 1, "B");
    // PhiPQ
    histPhiPQ_Acceptance[i] = new TH1D(Form("acc_PhiPQ_%i", i), "", 36, EdgesPhiPQ[0], EdgesPhiPQ[NbinsPhiPQ]);
    histPhiPQ_Acceptance[i]->Divide(histPhiPQ_Sim[i], histPhiPQ_MC[i], 1, 1, "B");

    /*** CORRECT DATA ***/

    // Q2
    histQ2_Corr[i] = new TH1D(Form("corr_Q2_%i", i), "", 100, kEdgesQ2[0], kEdgesQ2[Nbins]);
    histQ2_Corr[i]->Divide(histQ2_Data[i], histQ2_Acceptance[i], 1, 1);
    // Nu
    histNu_Corr[i] = new TH1D(Form("corr_Nu_%i", i), "", 100, kEdgesNu[0], kEdgesNu[Nbins]);
    histNu_Corr[i]->Divide(histNu_Data[i], histNu_Acceptance[i], 1, 1);
    // Z
    histZ_Corr[i] = new TH1D(Form("corr_Z_%i", i), "", 100, kEdgesZ[0], kEdgesZ[Nbins]);
    histZ_Corr[i]->Divide(histZ_Data[i], histZ_Acceptance[i], 1, 1);
    // Pt2
    histPt2_Corr[i] = new TH1D(Form("corr_Pt2_%i", i), "", 100, kEdgesPt2[0], kEdgesPt2[Nbins]);
    histPt2_Corr[i]->Divide(histPt2_Data[i], histPt2_Acceptance[i], 1, 1);
    // PhiPQ
    histPhiPQ_Corr[i] = new TH1D(Form("corr_PhiPQ_%i", i), "", 36, EdgesPhiPQ[0], EdgesPhiPQ[NbinsPhiPQ]);
    histPhiPQ_Corr[i]->Divide(histPhiPQ_Data[i], histPhiPQ_Acceptance[i], 1, 1);

    /*** GET CENTROIDS ***/

    meanQ2[i] = histQ2_Corr[i]->GetMean();
    meanNu[i] = histNu_Corr[i]->GetMean();
    meanZ[i] = histZ_Corr[i]->GetMean();
    meanPt2[i] = histPt2_Corr[i]->GetMean();
    meanPhiPQ[i] = histPhiPQ_Corr[i]->GetMean();
  }

  /*** OUTPUT ***/

  TString OutFileName = gProDir + "/gfx/rad-corr_omega/centroids_omega_" + targetOption + ".csv";
  std::ofstream OutFile(OutFileName, std::ios::out);
  for (Int_t i = 0; i < NbinsPhiPQ; i++) {
    OutFile << meanQ2[i] << "," << meanNu[i] << "," << meanZ[i] << "," << meanPt2[i] << "," << meanPhiPQ[i] << std::endl;
  }

  OutFile.close();
  std::cout << "The following file has been created: " << OutFileName << std::endl;
}
