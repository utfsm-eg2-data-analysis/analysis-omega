#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

#include "DrawHorizontalLine.cxx"
#include "DrawVerticalLine.cxx"

void EventMixingSim_FourBins(TString targetOption = "C", TString kinvarOption = "Q2") {
  // Plot all bins, comparing event-mixing from simrec with simrec.

  gROOT->SetBatch(kTRUE); // prevent output printing
  const Int_t Nbins = 4;

  system("mkdir -p evnt-mixing"); // just in case
  
  /*** INPUT ***/
  
  TChain *dataTree = new TChain();
  if (targetOption == "C") {
    dataTree->Add(gWorkDir + "/out/FilterNCombine/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
    dataTree->Add(gWorkDir + "/out/FilterNCombine/old/" + targetOption + "/comb" + targetOption + "_*.root/mix");
  } else if (targetOption == "Fe") {
    dataTree->Add(gWorkDir + "/out/FilterNCombine/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
    dataTree->Add(gWorkDir + "/out/FilterNCombine/old/" + targetOption + "/comb" + targetOption + "_*.root/mix");
  } else if (targetOption == "Pb") {
    dataTree->Add(gWorkDir + "/out/FilterNCombine/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
  } else if (targetOption == "D") {
    dataTree->Add(gWorkDir + "/out/FilterNCombine/usm/"+ targetOption +"/comb" + targetOption + "_*.root/mix");
    dataTree->Add(gWorkDir + "/out/FilterNCombine/jlab/"+ targetOption +"/00/comb" + targetOption + "_*.root/mix");
  }
  
  TChain *bkgTree = new TChain();
  if (targetOption == "C") {
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPi0.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPi0.root/mix");
  } else if (targetOption == "Fe") {
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/old/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPi0.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPi0.root/mix");    
  } else if (targetOption == "Pb") {
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPi0.root/mix");
  } else if (targetOption == "D") {
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/usm/" + targetOption + "/bkgmix" + targetOption + "_*_red_sPi0.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/jlab/" + targetOption + "/00/bkgmix" + targetOption + "_*_red_sAll.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/jlab/" + targetOption + "/00/bkgmix" + targetOption + "_*_red_sPip.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/jlab/" + targetOption + "/00/bkgmix" + targetOption + "_*_red_sPim.root/mix");
    bkgTree->Add(gWorkDir + "/out/EventMixing/jlab/" + targetOption + "/00/bkgmix" + targetOption + "_*_red_sPi0.root/mix");
  }

  // necessary for gCutKaons
  SetAliases(dataTree);
  SetAliases(bkgTree);

  // about kinvar option
  TString kinvarTitle;
  Double_t EdgesKinvar[Nbins + 1];  
  if (kinvarOption == "Q2") {
    kinvarTitle = "Q^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesQ2[i];
  } else if (kinvarOption == "Nu") {
    kinvarTitle = "#nu";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesNu[i];
  } else if (kinvarOption == "wZ") {
    kinvarTitle = "z_{h}";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesZ[i];
  } else if (kinvarOption == "wPt2") {
    kinvarTitle = "p_{T}^{2}";
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesPt2[i];
  }
  
  // to choose between eta and omega
  Int_t plotNbins = 24;
  Double_t plotMin = 0.66;
  Double_t plotMax = 0.90;
  Int_t BinsForNormalization[4];
  BinsForNormalization[0] = 1;
  BinsForNormalization[1] = 5;
  BinsForNormalization[2] = plotNbins - 4;
  BinsForNormalization[3] = plotNbins;
  TString histProperties = Form("(%d, %.3f, %.3f)", plotNbins, plotMin, plotMax);
    
  /*** SET OUTPUT FILE ***/

  TFile *RootOutputFile = new TFile(gProDir + "/macros/evnt-mixing/evnt-mixing_binned_" + targetOption + "_sim_" + kinvarOption + ".root", "RECREATE");
  
  TString auxCut;
  TCut CutBin;

  /*** SET HISTOGRAMS ***/

  const Int_t Nx = Nbins;
  const Int_t Ny = 1;

  TH1D *dataMassive[Nbins];
  TH1D *bkgMassive[Nbins];
  TH1D *subMassive[Nbins];
 
  Double_t dataNorm, bkgNorm;

  TF1 *Model[Nbins];
  TF1 *Signal[Nbins];
  TF1 *ResidualBkg[Nbins];
  TFitResultPtr FitResult[Nbins];

  const Int_t Ntargets = 4;
  
  for (Int_t i = 0; i < Nx; i++) {
    auxCut = Form("%f", EdgesKinvar[i]);
    auxCut += " < " + kinvarOption + " && " + kinvarOption + " < ";
    auxCut += Form("%f", EdgesKinvar[i + 1]);
    CutBin = auxCut;
    
    std::cout << auxCut << std::endl;

    // prepare data
    dataTree->Draw(Form("wD>>data_%d", i) + histProperties, gCutDIS && CutBin && gCutPi0 && gCutKaons && gCutPhotonsOpAngle, "goff");
    dataMassive[i] = (TH1D *)gROOT->FindObject(Form("data_%d", i));
    
    dataMassive[i]->SetMarkerColor(kBlack);
    dataMassive[i]->SetMarkerStyle(8);
    dataMassive[i]->SetLineColor(kBlack);
    dataMassive[i]->SetLineWidth(2);
    dataMassive[i]->SetFillStyle(0);
       
    dataMassive[i]->SetTitle("");
    dataMassive[i]->GetXaxis()->SetTitle("Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
    dataMassive[i]->GetXaxis()->SetNdivisions(412);
    dataMassive[i]->GetYaxis()->SetTitleOffset(1.2);
    dataMassive[i]->GetYaxis()->SetMaxDigits(3);
    //dataMassive[i]->GetYaxis()->SetTitleSize(0.05);

    // prepare bkg
    bkgTree->Draw(Form("wD>>bkg_%d", i) + histProperties, gCutDIS && CutBin && gCutPi0 && gCutKaons && gCutPhotonsOpAngle, "goff");
    bkgMassive[i] = (TH1D *)gROOT->FindObject(Form("bkg_%d", i));
    
    bkgMassive[i]->SetMarkerColor(kRed);
    bkgMassive[i]->SetMarkerStyle(8);
    bkgMassive[i]->SetLineColor(kRed);
    bkgMassive[i]->SetLineWidth(2);
    bkgMassive[i]->SetFillStyle(0);

    /*** NORMALIZATION ***/

    dataNorm = dataMassive[i]->Integral(BinsForNormalization[0], BinsForNormalization[1]) + dataMassive[i]->Integral(BinsForNormalization[2], BinsForNormalization[3]);
    std::cout << "dataNorm = " << dataNorm << std::endl;

    bkgNorm = bkgMassive[i]->Integral(BinsForNormalization[0], BinsForNormalization[1]) + bkgMassive[i]->Integral(BinsForNormalization[2], BinsForNormalization[3]);
    std::cout << "bkgNorm  = " << bkgNorm << std::endl;
    bkgMassive[i]->Scale(dataNorm / bkgNorm);

    /*** BKG SUBTRACTION ***/
    
    subMassive[i] = new TH1D(Form("sub_%d", i), "", plotNbins, plotMin, plotMax);
    subMassive[i]->Add(dataMassive[i], bkgMassive[i], 1, -1);

    subMassive[i]->SetTitle("");
    subMassive[i]->GetXaxis()->SetTitle("Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
    subMassive[i]->GetXaxis()->SetNdivisions(412);
    subMassive[i]->GetYaxis()->SetTitleOffset(1.2);
    subMassive[i]->GetYaxis()->SetMaxDigits(3);
    
    subMassive[i]->SetMarkerColor(kOrange+10);
    subMassive[i]->SetMarkerStyle(8);
    subMassive[i]->SetLineColor(kOrange+10);
    subMassive[i]->SetLineWidth(2);
    subMassive[i]->SetFillStyle(0);
    
    /*** FIT ***/

    Double_t MeanIGV = 0.782;
    Double_t MeanLimit = 0.08;    
    Double_t SigmaIGV = 0.024;
    Double_t SigmaLimit = 0.011;    
    Model[i] = new TF1(Form("model_%d", i), "gaus(0) + pol1(3)", plotMin, plotMax);
    Model[i]->SetParameter(1, MeanIGV);
    Model[i]->SetParameter(2, SigmaIGV);
    Model[i]->SetParLimits(0, 0., 100000); // force positive values
    Model[i]->SetParLimits(1, MeanIGV - MeanLimit, MeanIGV + MeanLimit);
    Model[i]->SetParLimits(2, SigmaIGV - SigmaLimit, SigmaIGV + SigmaLimit);
    
    FitResult[i] = subMassive[i]->Fit(Form("model_%d", i), "BEMSVN");

    Signal[i] = new TF1(Form("signal_%d", i), "gaus", plotMin, plotMax);
    Signal[i]->SetParameter(0, Model[i]->GetParameter(0));
    Signal[i]->SetParameter(1, Model[i]->GetParameter(1));
    Signal[i]->SetParameter(2, Model[i]->GetParameter(2));
    ResidualBkg[i] = new TF1(Form("res-bkg_%d", i), "pol1", plotMin, plotMax);
    ResidualBkg[i]->SetParameter(0, Model[i]->GetParameter(3));
    ResidualBkg[i]->SetParameter(1, Model[i]->GetParameter(4));
        
    Signal[i]->SetLineWidth(3);
    Signal[i]->SetLineColor(kMagenta);

    ResidualBkg[i]->SetLineWidth(3);
    ResidualBkg[i]->SetLineColor(kGray+2);
    ResidualBkg[i]->SetLineStyle(kDashed);

    // save into output file
    subMassive[i]->Write();
    Model[i]->Write();
    FitResult[i]->Write();
  }
  
  /*** FIX Y-AXIS ***/

  Double_t MaxRangeData = 0;
  Double_t MaxRangeSub = 0;
  for (Int_t i = 0; i < Nx; i++) {
    if (dataMassive[i]->GetMaximum() > MaxRangeData) MaxRangeData = dataMassive[i]->GetMaximum();
    if (subMassive[i]->GetMaximum() > MaxRangeSub) MaxRangeSub = subMassive[i]->GetMaximum();
  }
  
  /*** DRAW ***/

  gStyle->SetPadBorderSize(0);
  
  gStyle->SetLineWidth(1);
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetTitleFontSize(0.06);

  TCanvas *can1 = new TCanvas("evnt-mixing_binned_" + targetOption + "_sim_" + kinvarOption, "evnt-mixing_binned_" + targetOption + "_sim_" + kinvarOption, 1920, 960); 
  can1->Divide(Nx, 2, 0, 0);

  // top
  Int_t counter = 0;
  for (Int_t i = 0; i < Nx; i++) {
    
    counter++;
    can1->cd(counter);

    // set y-axis from before
    dataMassive[i]->GetYaxis()->SetRangeUser(0, 1.5*MaxRangeData);
    dataMassive[i]->GetYaxis()->SetTitle(Form("Counts (#times 10^{%d})",(Int_t)TMath::Floor(TMath::Log10(1.5*MaxRangeData))));
    
    dataMassive[i]->Draw("E");
    bkgMassive[i]->Draw("E SAME");
    
    // title
    auxCut = Form("%.2f", EdgesKinvar[i]);
    auxCut += " < " + kinvarTitle + " < ";
    auxCut += Form("%.2f", EdgesKinvar[i + 1]);
    auxCut += ", " + targetOption + " Sim. Rec.";
    TPaveText *pav = new TPaveText(0.15, 0.88, 0.40, 0.98, "NDC NB"); // no border
    pav->AddText(auxCut);
    ((TText*)pav->GetListOfLines()->Last())->SetTextSize(0.04);
    pav->SetBorderSize(0);
    pav->SetFillStyle(0);
    pav->SetTextAlign(12);
    if (i > 0) {
      pav->SetX1(0.05);
      pav->SetX2(0.40);
    }
    pav->Draw();
    
    if (i == 0) {
      TLegend *leg = new TLegend(0.15, 0.74, 0.45, 0.88);  // x1,y1,x2,y2
      leg->AddEntry(dataMassive[i], "Sim. Rec.", "lp");
      leg->AddEntry(bkgMassive[i], "Mixed Event Bkg", "lp");
      leg->SetBorderSize(0);
      leg->SetFillStyle(0);
      leg->SetTextFont(62);
      leg->Draw();
    }

    // debug
    // if (i == Nx-1) DrawVerticalLine(0.9, kBlack, kSolid, 2, 0, 0.0, 1.0);
  }

  // botttom
  TString Chi2String, NormString, MeanString, SigmaString;
  Double_t MeanValue, MeanError, SigmaValue, SigmaError;
  for (Int_t i = 0; i < Nx; i++) {
    counter++;
    can1->cd(counter);
    
    // set y-axis from before
    subMassive[i]->GetYaxis()->SetRangeUser(-0.5*MaxRangeSub, 1.5*MaxRangeSub);
    subMassive[i]->GetYaxis()->SetTitle(Form("Sim. Rec. - Mixed Event Bkg (#times 10^{%d})", (Int_t)TMath::Floor(TMath::Log10(1.5*MaxRangeSub))));

    subMassive[i]->Draw("E");

    Signal[i]->Draw("SAME");
    ResidualBkg[i]->Draw("SAME");
    
    if (i == 0) DrawHorizontalLine(0, kBlack, kSolid, 1, 0, 0.1, 1.0);
    else if (i == 1) DrawHorizontalLine(0, kBlack, kSolid, 1, 0, 0., 1.0);
    else if (i == 2) DrawHorizontalLine(0, kBlack, kSolid, 1, 0, 0., 1.0);
    else if (i == 3) DrawHorizontalLine(0, kBlack, kSolid, 1, 0, 0., 1.0);    
        
    // title
    auxCut = Form("%.2f", EdgesKinvar[i]);
    auxCut += " < " + kinvarTitle + " < ";
    auxCut += Form("%.2f", EdgesKinvar[i + 1]);
    auxCut += ", " + targetOption + " Sim. Rec.";
    TPaveText *pav = new TPaveText(0.15, 0.88, 0.40, 0.98, "NDC NB"); // no border
    pav->AddText(auxCut);
    ((TText*)pav->GetListOfLines()->Last())->SetTextSize(0.04);
    pav->SetBorderSize(0);
    pav->SetFillStyle(0);
    pav->SetTextAlign(12);
    if (i > 0) {
      pav->SetX1(0.05);
      pav->SetX2(0.40);
    }
    pav->Draw();

    // legend
    if (i == 0) {
      TLegend *leg = new TLegend(0.15, 0.67, 0.35, 0.88);  // x1,y1,x2,y2
      leg->AddEntry(subMassive[i], "Sim. Rec. - Bkg", "lp");
      leg->AddEntry(Signal[i], "Signal", "l");
      leg->AddEntry(ResidualBkg[i], "Residual Bkg", "l");
      leg->SetBorderSize(0);
      leg->SetFillStyle(0);
      leg->SetTextFont(62);
      leg->Draw();
    }

    // pave
    Chi2String = Form("#chi^{2}/ndf = %.4f", Model[i]->GetChisquare()/(Double_t)Model[i]->GetNDF());
    NormString = Form("A = %.3f #pm %.3f", Model[i]->GetParameter(0), Model[i]->GetParError(0));
    MeanString = Form("#mu = %.3f #pm %.6f", Model[i]->GetParameter(1), Model[i]->GetParError(1));
    SigmaString = Form("#sigma = %.3f #pm %.6f", Model[i]->GetParameter(2), Model[i]->GetParError(2));
    TPaveText *pav2 = new TPaveText(0.70, 0.66, 0.96, 0.96, "NDC NB");  // no border
    pav2->AddText(Chi2String);
    pav2->AddText(NormString);
    pav2->AddText(MeanString);
    pav2->AddText(SigmaString);
    pav2->SetBorderSize(0);
    pav2->SetTextAlign(12);
    pav2->SetFillStyle(0);
    if (i > 0) {
      pav2->SetX1(0.66);
      pav2->SetX2(0.96);
    }
    pav2->Draw();

    // params
    MeanValue = Model[i]->GetParameter(1);
    SigmaValue = Model[i]->GetParameter(2);
    DrawVerticalLine(MeanValue - 3*SigmaValue, kMagenta, kDashed, 2, 0, 0.2, 0.5);
    DrawVerticalLine(MeanValue + 3*SigmaValue, kMagenta, kDashed, 2, 0, 0.2, 0.5);
    
    // debug
    // if (i == Nx-1) DrawVerticalLine(0.9, kBlack, kSolid, 2, 0, 0.1, 1.0);
  }

  can1->Print("evnt-mixing/evnt-mixing_binned_" + targetOption + "_sim_" + kinvarOption + ".png");
  
  // close output file
  RootOutputFile->Close();  
}
