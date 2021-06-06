#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawHorizontalLine.cxx"

void SimVsData_AllBins(TString setOption = "old", TString targetOption = "C", TString dirOption = "") {
  // Compare data vs sim.rec.
  
  /*** INPUT ***/

  TString dataFile1, dataFile2, dataFile3;
  TString SimDir = gWorkDir + "/out/FilterNCombine/" + setOption + "/" + targetOption;
  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
    dataFile1 = gDataDir + "/C/comb_data-C.root";
    dataFile2 = gDataDir + "/Fe/comb_data-Fe.root";
    dataFile3 = gDataDir + "/Pb/comb_data-Pb.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    dataFile1 = gDataDir + "/" + targetOption + "/comb_data-" + targetOption + ".root";
  }
  
  TChain *dataTree = new TChain();
  dataTree->Add(dataFile1 + "/mix");
  dataTree->Add(dataFile2 + "/mix");
  dataTree->Add(dataFile3 + "/mix");

  TChain *simTree = new TChain();
  simTree->Add(SimDir + "/comb" + targetOption + "_*.root/mix");
  
  // necessary for gCutKaons
  SetAliases(dataTree);
  SetAliases(simTree, 1);

  // keep this just in case I want to generalize
  TString histProperties = "(25, 0.65, 0.90)";
  TString histProperties_MC = "(50, 0.65, 0.90)";
  Int_t plotNbins = 25;
  Double_t plotMin = 0.65;
  Double_t plotMax = 0.90;
  Int_t BinsForNormalization[2];
  BinsForNormalization[0] = 10;
  BinsForNormalization[1] = 15;
  
  /*** SET OUTPUT FILE ***/

  TFile *RootOutputFile = new TFile(gProDir + "/macros/out/acceptance_binned_" + setOption + "-" + targetOption + ".root", "RECREATE");

  TString kinvarOption[4] = {"Q2", "Nu", "wZ", "wPt2"};
  TString kinvarTitle[4] = {"Q^{2}", "#nu", "Z", "p_{T}^{2}"};
  Double_t EdgesKinvar[4][5];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[0][i] = kEdgesQ2[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[1][i] = kEdgesNu[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[2][i] = kEdgesZ[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[3][i] = kEdgesPt2[i];

  TString auxCut, auxCut_MC;
  TCut CutBin, CutBin_MC;

  /*** SET HIST ***/
  
  const Int_t Nbins = 4;
  const Int_t Nkinvars = 4;

  TH1D *dataMassive[Nbins][Nkinvars];
  TH1D *simMassive[Nbins][Nkinvars];
  TH1D *genMassive[Nbins][Nkinvars]; // MC
  
  for (Int_t j = 0; j < Nkinvars; j++) { // Ny
    for (Int_t i = 0; i < Nbins; i++) { // Nx

      // data and simrec
      auxCut = Form("%f", EdgesKinvar[j][i]);
      auxCut += " < " + kinvarOption[j] + " && " + kinvarOption[j] + " < ";
      auxCut += Form("%f", EdgesKinvar[j][i + 1]);
      CutBin = auxCut;

      std::cout << auxCut << std::endl;
      
      dataTree->Draw(Form("wD>>data_%i_%i", i, j) + histProperties, gCutDIS && CutBin && gCutPi0 && CutVertex && gCutRegion && gCutKaons && gCutPhotonsOpAngle, "goff");
      dataMassive[i][j] = (TH1D *)gROOT->FindObject(Form("data_%i_%i", i, j));

      dataMassive[i][j]->SetMarkerColor(kBlue);
      dataMassive[i][j]->SetLineColor(kBlue);
      dataMassive[i][j]->SetLineWidth(2);
      dataMassive[i][j]->SetFillStyle(0);

      auxCut = Form("%.2f", EdgesKinvar[j][i]);
      auxCut += " < " + kinvarTitle[j] + " < ";
      auxCut += Form("%.2f", EdgesKinvar[j][i + 1]);
      auxCut += ", " + targetOption;

      dataMassive[i][j]->SetTitle(auxCut);
      dataMassive[i][j]->GetXaxis()->SetTitle("Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
      dataMassive[i][j]->GetYaxis()->SetTitle("Normalized Counts");

      // simrec doesn't need vertex cuts
      simTree->Draw(Form("wD>>sim_%i_%i", i, j) + histProperties, gCutDIS && CutBin && gCutPi0 && gCutRegion && gCutKaons && gCutPhotonsOpAngle, "goff");
      simMassive[i][j] = (TH1D *)gROOT->FindObject(Form("sim_%i_%i", i, j));

      simMassive[i][j]->SetMarkerColor(kMagenta + 1);
      simMassive[i][j]->SetLineColor(kMagenta + 1);
      simMassive[i][j]->SetLineWidth(2);
      simMassive[i][j]->SetFillStyle(0);

      // gen
      auxCut_MC = Form("%f", EdgesKinvar[j][i]);
      auxCut_MC += " < mc_" + kinvarOption[j] + " && mc_" + kinvarOption[j] + " < ";
      auxCut_MC += Form("%f", EdgesKinvar[j][i + 1]);
      CutBin_MC = auxCut_MC;

      std::cout << auxCut_MC << std::endl;

      // gsim doesn't need vertex cuts either
      simTree->Draw(Form("mc_wD>>gen_%i_%i", i, j) + histProperties_MC, gCutDIS_MC && CutBin_MC && gCutPi0_MC && gCutRegion_MC && gCutKaons_MC && gCutPhotonsOpAngle_MC, "goff");
      genMassive[i][j] = (TH1D *)gROOT->FindObject(Form("gen_%i_%i", i, j));

      genMassive[i][j]->SetMarkerColor(kBlack);
      genMassive[i][j]->SetLineColor(kBlack);
      genMassive[i][j]->SetLineWidth(2);
      genMassive[i][j]->SetFillStyle(0);

      auxCut_MC = Form("%.2f", EdgesKinvar[j][i]);
      auxCut_MC += " < " + kinvarTitle[j] + " < ";
      auxCut_MC += Form("%.2f", EdgesKinvar[j][i + 1]);
      auxCut_MC += ", " + targetOption;

      genMassive[i][j]->SetTitle(auxCut_MC);
      genMassive[i][j]->GetXaxis()->SetTitle("Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
      genMassive[i][j]->GetYaxis()->SetTitle("Normalized Counts");
      
      // save into file
      dataMassive[i][j]->Write();
      simMassive[i][j]->Write();
      genMassive[i][j]->Write();
    }
  }

  /*** FIX Y-AXIS FOR DATA ***/

  Double_t MaxRange[Nkinvars];
  for (Int_t j = 0; j < Nkinvars; j++) {
    MaxRange[j] = 0;
    for (Int_t i = 0; i < Nbins; i++) {
      if (dataMassive[i][j]->GetMaximum() > MaxRange[j]) MaxRange[j] = dataMassive[i][j]->GetMaximum();
    }
    MaxRange[j] += MaxRange[j]*0.25;
  }

  /*** SET CANVAS: DATA VS SIMREC ***/
  
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  TCanvas *can1 = new TCanvas("data-simrec_all-bins", "", 1200, 1200);
  can1->Divide(Nbins, Nkinvars, 0.001, 0.001);
  
  gStyle->SetOptStat(0);
  
  // normalization
  Double_t dataNorm, simNorm;
  
  Int_t counter = 1;
  for (Int_t j = 0; j < Nkinvars; j++) { // Ny
    for (Int_t i = 0; i < Nbins; i++) { // Nx

      // set y-axis from before
      dataMassive[i][j]->GetYaxis()->SetRangeUser(0, MaxRange[j]);

      /*** Normalization ***/

      dataNorm = dataMassive[i][j]->GetMaximum();
      std::cout << "dataNorm = " << dataNorm << std::endl;
      dataMassive[i][j]->Scale(dataNorm);
      
      simNorm = simMassive[i][j]->GetMaximum();
      std::cout << "simNorm  = " << simNorm << std::endl;
      simMassive[i][j]->Scale(simNorm);
      
      /*** DRAW ***/
      
      can1->cd(counter);
      
      dataMassive[i][j]->Draw("E");
      simMassive[i][j]->Draw("E SAME");

      // legend
      TLegend *leg = new TLegend(0.15, 0.64, 0.45, 0.88); // x1,y1,x2,y2
      leg->AddEntry(dataMassive[i][j], "Data", "lp");
      leg->AddEntry(simMassive[i][j], "Sim. Rec.", "lp");
      leg->SetBorderSize(0);
      leg->SetFillStyle(0);
      leg->Draw();
      
      can1->Update();

      counter++;
    }
  }
  
  can1->Write();

  /*** FIX Y-AXIS FOR GEN. ***/

  for (Int_t j = 0; j < Nkinvars; j++) {
    MaxRange[j] = 0;
    for (Int_t i = 0; i < Nbins; i++) {
      if (genMassive[i][j]->GetMaximum() > MaxRange[j]) MaxRange[j] = genMassive[i][j]->GetMaximum();
    }
    MaxRange[j] += MaxRange[j]*0.25;
  }
  
  /*** SET CANVAS: SIMREC VS GENERATED ***/
  
  TCanvas *can2 = new TCanvas("simrec-gen_all-bins", "", 1200, 1200);
  can2->Divide(Nbins, Nkinvars, 0.001, 0.001);
  
  gStyle->SetOptStat(0);
  
  // normalization
  Double_t genNorm;
  
  counter = 1;
  for (Int_t j = 0; j < Nkinvars; j++) { // Ny
    for (Int_t i = 0; i < Nbins; i++) { // Nx

      // set y-axis from before
      genMassive[i][j]->GetYaxis()->SetRangeUser(0, MaxRange[j]);

      /*** Normalization ***/

      genNorm = genMassive[i][j]->GetMaximum();
      std::cout << "genNorm = " << genNorm << std::endl;
      genMassive[i][j]->Scale(genNorm);
      
      simNorm = simMassive[i][j]->GetMaximum();
      std::cout << "simNorm  = " << simNorm << std::endl;
      simMassive[i][j]->Scale(simNorm);

      /*** DRAW ***/
      
      can2->cd(counter);
      
      genMassive[i][j]->Draw("E");
      simMassive[i][j]->Draw("E SAME");

      // legend
      TLegend *leg = new TLegend(0.15, 0.64, 0.45, 0.88); // x1,y1,x2,y2
      leg->AddEntry(genMassive[i][j], "MC", "lp");
      leg->AddEntry(simMassive[i][j], "Sim. Rec.", "lp");
      leg->SetBorderSize(0);
      leg->SetFillStyle(0);
      leg->Draw();
      
      can2->Update();
      
      counter++;
    }
  }
  
  can2->Write();

  // close output file
  RootOutputFile->Close();
}
