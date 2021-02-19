#include "Global.h"
#include "SetAliases.cxx"
#include "DrawHorizontalLine.cxx"

void EventMixing_AllBins(TString targetOption = "D", Int_t CustomNormalization = 0, Int_t BkgSubtraction = 0) {

  /*** INPUT ***/

  TString dataFile1, dataFile2, dataFile3;
  TString bkgFile1, bkgFile2, bkgFile3;
  TString BkgDir = gProDir + "/FilterNCombine_mix/out";
  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = gCutLiquid;
    dataFile1 = gDataDir + "/comb_data-C.root";
    dataFile2 = gDataDir + "/comb_data-Fe.root";
    dataFile3 = gDataDir + "/comb_data-Pb.root";
    bkgFile1 = BkgDir + "/bkgmixC.root";
    bkgFile2 = BkgDir + "/bkgmixFe.root";
    bkgFile3 = BkgDir + "/bkgmixPb.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    CutVertex = gCutSolid;
    dataFile1 = gDataDir + "/comb_data-" + targetOption + ".root";
    bkgFile1 = BkgDir + "/bkgmix" + targetOption + ".root";
  }
  
  TChain *dataTree = new TChain();
  dataTree->Add(dataFile1 + "/mix");
  dataTree->Add(dataFile2 + "/mix");
  dataTree->Add(dataFile3 + "/mix");

  TChain *bkgTree = new TChain();
  bkgTree->Add(bkgFile1 + "/mix");
  bkgTree->Add(bkgFile2 + "/mix");
  bkgTree->Add(bkgFile3 + "/mix");

  // necessary for gCutKaons
  SetAliases(dataTree);
  SetAliases(bkgTree);

  /*** SET OUTPUT FILE ***/

  TFile *RootOutputFile = new TFile(gProDir + "/macros/out/evnt-mixing_binned_" + targetOption + ".root", "RECREATE");

  TString kinvarOption[4] = {"Q2", "Nu", "wZ", "wPt2"};
  Double_t EdgesKinvar[4][5];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[0][i] = kEdgesQ2[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[1][i] = kEdgesNu[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[2][i] = kEdgesZ[i];
  for (Int_t i = 0; i < 5; i++) EdgesKinvar[3][i] = kEdgesPt2[i];

  TString auxCut;
  TCut CutBin;

  /*** SET HIST ***/
  
  const Int_t Nbins = 4;
  const Int_t Nkinvars = 4;

  TH1D *dataMassive[Nbins][Nkinvars];
  TH1D *bkgMassive[Nbins][Nkinvars];
  
  for (Int_t j = 0; j < Nkinvars; j++) { // Ny
    for (Int_t i = 0; i < Nbins; i++) { // Nx

      auxCut = Form("%f", EdgesKinvar[j][i]);
      auxCut += " < " + kinvarOption[j] + " && " + kinvarOption[j] + " < ";
      auxCut += Form("%f", EdgesKinvar[j][i + 1]);
      CutBin = auxCut;

      std::cout << auxCut << std::endl;
      
      dataTree->Draw(Form("wD>>data_%i_%i(25, 0.65, 0.90)", i, j), gCutDIS && CutBin && gCutPi0 && CutVertex && gCutRegion && gCutKaons && gCutPhotonsOpAngle, "goff");
      dataMassive[i][j] = (TH1D *)gROOT->FindObject(Form("data_%i_%i", i, j));

      dataMassive[i][j]->SetMarkerColor(kBlue+3);
      dataMassive[i][j]->SetLineColor(kBlue+3);
      dataMassive[i][j]->SetLineWidth(2);
      dataMassive[i][j]->SetFillStyle(0);

      auxCut = Form("%.2f", EdgesKinvar[j][i]);
      auxCut += " < " + kinvarOption[j] + " < ";
      auxCut += Form("%.2f", EdgesKinvar[j][i + 1]);
      auxCut += ", " + targetOption + " data";

      dataMassive[i][j]->SetTitle(auxCut);
      dataMassive[i][j]->GetXaxis()->SetTitle("Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
      dataMassive[i][j]->GetYaxis()->SetTitle("Counts");

      bkgTree->Draw(Form("wD>>bkg_%i_%i(25, 0.65, 0.90)", i, j), gCutDIS && CutBin && gCutPi0 && CutVertex && gCutRegion && gCutKaons && gCutPhotonsOpAngle, "goff");
      bkgMassive[i][j] = (TH1D *)gROOT->FindObject(Form("bkg_%i_%i", i, j));

      bkgMassive[i][j]->SetMarkerColor(kOrange+7);
      bkgMassive[i][j]->SetLineColor(kOrange+7);
      bkgMassive[i][j]->SetLineWidth(2);
      bkgMassive[i][j]->SetFillStyle(0);
    }
  }

  /*** FIX Y-AXIS ***/
  
  Double_t MaxRange[Nkinvars];
  for (Int_t j = 0; j < Nkinvars; j++) {
    MaxRange[j] = 0;
    for (Int_t i = 0; i < Nbins; i++) {
      if (dataMassive[i][j]->GetMaximum() > MaxRange[j]) MaxRange[j] = dataMassive[i][j]->GetMaximum();
    }
    MaxRange[j] += MaxRange[j]*0.15;
  }

  /*** SET CANVAS ***/
  
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  
  TCanvas *can1 = new TCanvas("bkgmix-all-bins", "", 1200, 1200);
  can1->Divide(Nbins, Nkinvars, 0.001, 0.001);

  Double_t dataNorm, bkgNorm;

  Int_t counter = 1;
  for (Int_t j = 0; j < Nkinvars; j++) { // Ny
    for (Int_t i = 0; i < Nbins; i++) { // Nx

      // set y-axis from before
      dataMassive[i][j]->GetYaxis()->SetRangeUser(0, MaxRange[j]);
      
      /*** NORMALIZATION ***/

      if (CustomNormalization) {
	dataNorm = dataMassive[i][j]->Integral(1, 5) + dataMassive[i][j]->Integral(20, 25);
	std::cout << "dataNorm = " << dataNorm << std::endl;
	
	bkgNorm = bkgMassive[i][j]->Integral(1, 5) + bkgMassive[i][j]->Integral(20, 25);
	std::cout << "bkgNorm  = " << bkgNorm << std::endl;
	bkgMassive[i][j]->Scale(dataNorm / bkgNorm);
      }

      /*** DRAW ***/
      
      can1->cd(counter);

      if (CustomNormalization) {
	dataMassive[i][j]->Draw("E");
	bkgMassive[i][j]->Draw("E SAME");
      } else {
	dataMassive[i][j]->DrawNormalized("E");
	bkgMassive[i][j]->DrawNormalized("E SAME");
      }

      // legend
      TLegend *leg = new TLegend(0.15, 0.64, 0.45, 0.88); // x1,y1,x2,y2
      leg->AddEntry(dataMassive[i][j], "Data", "lp");
      leg->AddEntry(bkgMassive[i][j], "Mixed Event Bkg", "lp");
      leg->SetBorderSize(0);
      leg->SetFillStyle(0);
      leg->Draw();
      
      can1->Update();

      // save into file
      dataMassive[i][j]->Write();
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
	// bkg subtraction needs data and bkg normalization
	subMassive[i][j] = new TH1D(Form("sub_%i_%i", i, j), "", 25, 0.65, 0.90);
	subMassive[i][j]->Add(dataMassive[i][j], bkgMassive[i][j], 1, -1);

	auxCut = Form("%.2f", EdgesKinvar[j][i]);
	auxCut += " < " + kinvarOption[j] + " < ";
	auxCut += Form("%.2f", EdgesKinvar[j][i + 1]);
	auxCut += ", " + targetOption + " data";

	subMassive[i][j]->SetTitle(auxCut);
	subMassive[i][j]->GetXaxis()->SetTitle("Reconstructed Mass #Deltam(#pi^{+}#pi^{-}#pi^{0}) [GeV]");
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
