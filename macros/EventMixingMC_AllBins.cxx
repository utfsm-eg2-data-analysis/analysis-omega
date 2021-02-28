#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawHorizontalLine.cxx"

void EventMixingMC_AllBins(TString setOption = "old", TString targetOption = "D", TString dirOption = "", Int_t CustomNormalization = 0, Int_t BkgSubtraction = 0, TString particleOption = "omega") {
  // Plot all bins, comparing event-mixing from MC files.
  
  /*** INPUT ***/

  TString SimDir = gWorkDir + "/out/FilterNCombine/" + setOption + "/" + targetOption;
  TString BkgDir = gWorkDir + "/out/EventMixing/" + setOption + "/" + targetOption;
  if (setOption == "jlab") {
    SimDir += "/" + dirOption;
    BkgDir += "/" + dirOption;
  }
  TChain *simTree = new TChain();
  simTree->Add(SimDir + "/*.root/mix");
  
  TChain *bkgTree = new TChain();
  bkgTree->Add(BkgDir + "/*_red_MC_sPip.root/mix");
  bkgTree->Add(BkgDir + "/*_red_MC_sPim.root/mix");
  bkgTree->Add(BkgDir + "/*_red_MC_sPi0.root/mix");
  bkgTree->Add(BkgDir + "/*_red_MC_sAll.root/mix");

  // necessary for gCutKaons
  SetAliases(simTree, 1);
  SetAliases(bkgTree, 1);

  // to choose between eta and omega
  TString histProperties;
  Int_t plotNbins;
  Double_t plotMin, plotMax;
  Int_t BinsForNormalization[4];
  if (particleOption == "omega") {
    histProperties = "(50, 0.65, 0.90)";
    plotNbins = 50;
    plotMin = 0.65;
    plotMax = 0.90;
    BinsForNormalization[0] = 1;
    BinsForNormalization[1] = 15;
    BinsForNormalization[2] = 35;
    BinsForNormalization[3] = 50;
  } else if (particleOption == "eta") {
    histProperties = "(40, 0.45, 0.65)";
    plotNbins = 40;
    plotMin = 0.45;
    plotMax = 0.65;
    BinsForNormalization[0] = 1;
    BinsForNormalization[1] = 15;
    BinsForNormalization[2] = 35;
    BinsForNormalization[3] = 50;
  }
  
  /*** SET OUTPUT FILE ***/

  TFile *RootOutputFile = new TFile(gProDir + "/macros/out/evnt-mixing-mc-" + particleOption + "_binned_" + targetOption + ".root", "RECREATE");

  TString kinvarOption[4] = {"mc_Q2", "mc_Nu", "mc_wZ", "mc_wPt2"};
  TString kinvarTitle[4] = {"Q^{2}", "#nu", "Z", "p_{T}^{2}"};
  Double_t EdgesKinvar[4][5];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[0][i] = kEdgesQ2[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[1][i] = kEdgesNu[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[2][i] = kEdgesZ[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[3][i] = kEdgesPt2[i];

  TString auxCut;
  TCut CutBin_MC;

  /*** SET HIST ***/
  
  const Int_t Nbins = 4;
  const Int_t Nkinvars = 4;

  TH1D *simMassive[Nbins][Nkinvars];
  TH1D *bkgMassive[Nbins][Nkinvars];
  
  for (Int_t j = 0; j < Nkinvars; j++) { // Ny
    for (Int_t i = 0; i < Nbins; i++) { // Nx

      auxCut = Form("%f", EdgesKinvar[j][i]);
      auxCut += " < " + kinvarOption[j] + " && " + kinvarOption[j] + " < ";
      auxCut += Form("%f", EdgesKinvar[j][i + 1]);
      CutBin_MC = auxCut;

      std::cout << auxCut << std::endl;
      
      simTree->Draw(Form("mc_wD>>mc_%i_%i", i, j) + histProperties, gCutDIS_MC && CutBin_MC && gCutPi0_MC && gCutKaons_MC && gCutPhotonsOpAngle_MC, "goff");
      simMassive[i][j] = (TH1D *)gROOT->FindObject(Form("mc_%i_%i", i, j));

      simMassive[i][j]->SetMarkerColor(kBlack);
      simMassive[i][j]->SetLineColor(kBlack);
      simMassive[i][j]->SetLineWidth(2);
      simMassive[i][j]->SetFillStyle(0);

      auxCut = Form("%.2f", EdgesKinvar[j][i]);
      auxCut += " < " + kinvarTitle[j] + " < ";
      auxCut += Form("%.2f", EdgesKinvar[j][i + 1]);
      auxCut += ", " + targetOption + " MC";

      simMassive[i][j]->SetTitle(auxCut);
      simMassive[i][j]->GetXaxis()->SetTitle("#Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
      simMassive[i][j]->GetYaxis()->SetTitle("Counts");

      bkgTree->Draw(Form("mc_wD>>mc2_%i_%i", i, j) + histProperties, gCutDIS_MC && CutBin_MC && gCutPi0_MC && gCutKaons_MC && gCutPhotonsOpAngle_MC, "goff");
      bkgMassive[i][j] = (TH1D *)gROOT->FindObject(Form("mc2_%i_%i", i, j));

      bkgMassive[i][j]->SetMarkerColor(kRed);
      bkgMassive[i][j]->SetLineColor(kRed);
      bkgMassive[i][j]->SetLineWidth(2);
      bkgMassive[i][j]->SetFillStyle(0);
    }
  }

  /*** FIX Y-AXIS ***/
  
  Double_t MaxRange[Nkinvars];
  for (Int_t j = 0; j < Nkinvars; j++) {
    MaxRange[j] = 0;
    for (Int_t i = 0; i < Nbins; i++) {
      if (simMassive[i][j]->GetMaximum() > MaxRange[j]) MaxRange[j] = simMassive[i][j]->GetMaximum();
    }
    MaxRange[j] += MaxRange[j]*0.15;
  }

  /*** SET CANVAS ***/
  
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  TCanvas *can1 = new TCanvas("bkgmix-all-bins", "", 1200, 1200);
  can1->Divide(Nbins, Nkinvars, 0.001, 0.001);

  Double_t simNorm, bkgNorm;

  Int_t counter = 1;
  for (Int_t j = 0; j < Nkinvars; j++) { // Ny
    for (Int_t i = 0; i < Nbins; i++) { // Nx

      // set y-axis from before
      simMassive[i][j]->GetYaxis()->SetRangeUser(0, MaxRange[j]);
      
      /*** NORMALIZATION ***/

      if (CustomNormalization) {
	simNorm = simMassive[i][j]->Integral(BinsForNormalization[0], BinsForNormalization[1]) + simMassive[i][j]->Integral(BinsForNormalization[2], BinsForNormalization[3]);
	std::cout << "simNorm = " << simNorm << std::endl;
	
	bkgNorm = bkgMassive[i][j]->Integral(BinsForNormalization[0], BinsForNormalization[1]) + bkgMassive[i][j]->Integral(BinsForNormalization[2], BinsForNormalization[3]);
	std::cout << "bkgNorm  = " << bkgNorm << std::endl;
	bkgMassive[i][j]->Scale(simNorm / bkgNorm);
      }

      /*** DRAW ***/
      
      can1->cd(counter);

      if (CustomNormalization) {
	simMassive[i][j]->Draw("E");
	bkgMassive[i][j]->Draw("E SAME");
      } else {
	simMassive[i][j]->DrawNormalized("E");
	bkgMassive[i][j]->DrawNormalized("E SAME");
      }

      // legend
      TLegend *leg = new TLegend(0.15, 0.64, 0.45, 0.88); // x1,y1,x2,y2
      leg->AddEntry(simMassive[i][j], "MC", "lp");
      leg->AddEntry(bkgMassive[i][j], "Mixed-Event Bkg", "lp");
      leg->SetBorderSize(0);
      leg->SetFillStyle(0);
      leg->Draw();
      
      can1->Update();

      // save into file
      simMassive[i][j]->Write();
      bkgMassive[i][j]->Write();
      
      counter++;
    }
  }
  
  can1->Write();

  /*** BKG SUBTRACTION ***/
  // custom normalization is mandatory!
  
  if (CustomNormalization && BkgSubtraction) {

    /*** DEFINE HIST ***/
    
    // prepare bkg subtraction
    TH1D *subMassive[Nbins][Nkinvars];
  
    for (Int_t j = 0; j < Nkinvars; j++) {
      for (Int_t i = 0; i < Nbins; i++) {
	// bkg subtraction needs sim and bkg normalization
	subMassive[i][j] = new TH1D(Form("sub_%i_%i", i, j), "", plotNbins, plotMin, plotMax);
	subMassive[i][j]->Add(simMassive[i][j], bkgMassive[i][j], 1, -1);

	auxCut = Form("%.2f", EdgesKinvar[j][i]);
	auxCut += " < " + kinvarTitle[j] + " < ";
	auxCut += Form("%.2f", EdgesKinvar[j][i + 1]);
	auxCut += ", " + targetOption + " MC.";

	subMassive[i][j]->SetTitle(auxCut);
	subMassive[i][j]->GetXaxis()->SetTitle("#Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
	subMassive[i][j]->GetYaxis()->SetTitle("Counts");
	
	subMassive[i][j]->SetMarkerColor(kOrange + 3);  // brown
	subMassive[i][j]->SetLineColor(kOrange + 3);    // brown
	subMassive[i][j]->SetLineWidth(2);
	subMassive[i][j]->SetFillStyle(0);	
      }
    }

    /*** FIX Y-AXIS ***/

    Int_t MinRange[Nkinvars];
    for (Int_t j = 0; j < Nkinvars; j++) {
      MaxRange[j] = 0;
      MinRange[j] = 99999;
      for (Int_t i = 0; i < Nbins; i++) {
	if (subMassive[i][j]->GetMaximum() > MaxRange[j]) MaxRange[j] = subMassive[i][j]->GetMaximum();
	if (subMassive[i][j]->GetMinimum() < MinRange[j]) MinRange[j] = subMassive[i][j]->GetMinimum();
      }
      MaxRange[j] += MaxRange[j]*0.25;
      MinRange[j] -= MaxRange[j]*0.25;
    }

    /*** SET CANVAS ***/
    
    TCanvas *can2 = new TCanvas("bkgsub-all-bins", "bkgsub-all-bins", 1200, 1200);
    can2->Divide(Nbins, Nkinvars, 0.001, 0.001);

    counter = 1; // reset it from before
    for (Int_t j = 0; j < Nkinvars; j++) {
      for (Int_t i = 0; i < Nbins; i++) {
    
	// set y-axis from before
        subMassive[i][j]->GetYaxis()->SetRangeUser(MinRange[j], MaxRange[j]);

	/*** DRAW ***/
      
	can2->cd(counter);

	subMassive[i][j]->Draw("E");

	// legend
	TLegend *leg = new TLegend(0.15, 0.64, 0.45, 0.88); // x1,y1,x2,y2
	leg->AddEntry(subMassive[i][j], "Bkg Subtracted", "lp"); // bkg subtraction
	leg->SetBorderSize(0);
	leg->SetFillStyle(0);
	leg->Draw();

	DrawHorizontalLine(0, kBlack, kSolid, 1);
	
	can2->Update();

	// save into file
	subMassive[i][j]->Write();
      
	counter++;
      }
    }
    can2->Write();  
  } // end of bkg subtraction condition

  // close output file
  RootOutputFile->Close();
}
