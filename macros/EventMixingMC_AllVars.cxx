#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

void EventMixingMC_AllVars(TString targetOption = "C") {

  /*** INPUT ***/

  TChain *mcTree = new TChain();
  if (targetOption == "C") {
    mcTree->Add(gWorkDir + "/out/FilterNCombine/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
    mcTree->Add(gWorkDir + "/out/FilterNCombine/old/" + targetOption + "/comb" + targetOption + "_*.root/mix");
  } else if (targetOption == "Fe") {
    mcTree->Add(gWorkDir + "/out/FilterNCombine/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
    mcTree->Add(gWorkDir + "/out/FilterNCombine/old/" + targetOption + "/comb" + targetOption + "_*.root/mix");
  } else if (targetOption == "Pb") {
    mcTree->Add(gWorkDir + "/out/FilterNCombine/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
  } else if (targetOption == "D") {
    mcTree->Add(gWorkDir + "/out/FilterNCombine/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
    mcTree->Add(gWorkDir + "/out/FilterNCombine/jlab/"+ targetOption +"/00/comb" + targetOption + "_*.root/mix");
  }
  
  TChain *bkgTree = new TChain();
  if (targetOption == "C") {
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPi0.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPi0.root/mix");
  } else if (targetOption == "Fe") {
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPi0.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPi0.root/mix");    
  } else if (targetOption == "Pb") {
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPi0.root/mix");
  } else if (targetOption == "D") {
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_MC_sPi0.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/jlab/" + targetOption + "/00/bkgmix" + targetOption + "_*_red_MC_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/jlab/" + targetOption + "/00/bkgmix" + targetOption + "_*_red_MC_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/jlab/" + targetOption + "/00/bkgmix" + targetOption + "_*_red_MC_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/jlab/" + targetOption + "/00/bkgmix" + targetOption + "_*_red_MC_sPi0.root/mix");
  }

  // necessary for gCutKaons
  SetAliases(mcTree, 1);
  SetAliases(bkgTree, 1);

  TString kinvarOption[2][3] = {{"Q2", "Nu", "W"},
				{"wD", "wZ", "wPt2"}};
  TString histProperties[2][3] = {{"(200, 1, 4)", "(200, 2.2, 4.2)", "(200, 2.0, 3.0)"},
                                  {"(340, 0.66, 1.0)", "(200, 0.5, 0.9)", "(300, 0, 1.5)"}};
  TString kinvarAxis[2][3] = {{"Q^{2} [GeV^{2}]", "#nu [GeV]", "W [GeV]"},
                              {"Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]", "Z_{h}", "p_{T}^{2} [GeV^{2}]"}};

  const Int_t Nx = 3;
  const Int_t Ny = 2;

  TH1D *mcMassive[Nx][Ny];
  TH1D *bkgMassive[Nx][Ny];

  for (Int_t i = 0; i < Nx; i++) {    // Nx
    for (Int_t j = 0; j < Ny; j++) {  // Ny

      mcTree->Draw(Form("mc_" + kinvarOption[j][i] + ">>mc_%i_%i" + histProperties[j][i], i, j), gCutDIS_MC && gCutPi0_MC && gCutKaons_MC && gCutPhotonsOpAngle_MC, "goff");
      mcMassive[i][j] = (TH1D *)gROOT->FindObject(Form("mc_%i_%i", i, j));

      mcMassive[i][j]->SetTitle("");
      mcMassive[i][j]->SetMarkerColor(kBlack);
      mcMassive[i][j]->SetLineColor(kBlack);
      mcMassive[i][j]->SetLineWidth(2);
      mcMassive[i][j]->SetFillStyle(0);

      mcMassive[i][j]->GetYaxis()->SetTitle("Normalized Counts");
      if (i == 0 && j == 1) mcMassive[i][j]->GetYaxis()->SetTitle("Counts");
      mcMassive[i][j]->GetYaxis()->SetTitleSize(0.04);
      mcMassive[i][j]->GetYaxis()->SetTitleOffset(1.2);
      mcMassive[i][j]->GetYaxis()->SetMaxDigits(3);

      mcMassive[i][j]->GetXaxis()->SetTitle(kinvarAxis[j][i]);
      mcMassive[i][j]->GetXaxis()->SetTitleSize(0.04);
      mcMassive[i][j]->GetXaxis()->SetTitleOffset(1.);

      bkgTree->Draw(Form("mc_" + kinvarOption[j][i] + ">>bkg_%i_%i" + histProperties[j][i], i, j), gCutDIS_MC && gCutPi0_MC && gCutKaons_MC && gCutPhotonsOpAngle_MC, "goff");
      bkgMassive[i][j] = (TH1D *)gROOT->FindObject(Form("bkg_%i_%i", i, j));

      bkgMassive[i][j]->SetTitle("");
      bkgMassive[i][j]->SetMarkerColor(kRed);
      bkgMassive[i][j]->SetLineColor(kRed);
      bkgMassive[i][j]->SetLineWidth(2);
      bkgMassive[i][j]->SetFillStyle(0);
    }
  }

  /*** DRAW ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  // set margin sizes
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  
  gStyle->SetOptStat(0);

  TCanvas *can1 = new TCanvas("evnt-mixing_mc_all-vars_" + targetOption, "evnt-mixing_mc_all-vars_" + targetOption, 1500, 1000);
  can1->Divide(Nx, Ny, 0.001, 0.001);

  Double_t mcNorm, bkgNorm;

  Int_t counter = 1;
  for (Int_t j = 0; j < Ny; j++) {
    for (Int_t i = 0; i < Nx; i++) {

      can1->cd(counter);

      if (i == 0 && j == 1) {
        mcNorm = mcMassive[i][j]->Integral(1, 50) + mcMassive[i][j]->Integral(290, 340);
        std::cout << "mcNorm = " << mcNorm << std::endl;

        bkgNorm = bkgMassive[i][j]->Integral(1, 50) + bkgMassive[i][j]->Integral(290, 340);
        std::cout << "bkgNorm  = " << bkgNorm << std::endl;
        bkgMassive[i][j]->Scale(mcNorm / bkgNorm);

        mcMassive[i][j]->Draw("E");
        bkgMassive[i][j]->Draw("E SAME");
      } else {
        mcMassive[i][j]->DrawNormalized("E");
        bkgMassive[i][j]->DrawNormalized("E SAME");
      }

      // legend
      TLegend *legend = new TLegend(0.60, 0.75, 0.85, 0.9);  // x1,y1,x2,y2
      legend->AddEntry(mcMassive[i][j], "MC", "pl");
      if (i == 0 && j == 1) {
	legend->AddEntry(bkgMassive[i][j], "Mixed Event Bkg (Normalized)", "pl");
      }
      else legend->AddEntry(bkgMassive[i][j], "Mixed Event Bkg", "pl");
      legend->SetFillStyle(0);
      legend->SetTextFont(62);
      legend->SetTextSize(0.025);
      legend->SetBorderSize(0);
      legend->Draw();
      
      can1->Update();

      counter++;
    }
  }
}
