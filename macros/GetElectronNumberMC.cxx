#ifndef GLOBAL_H
#include "Global.h"
#endif

void GetElectronNumberMC(TString setOption, TString targetOption, TString dirOption = "") {
  // Count the number of electrons from MC files.
  // Doesn't need vertex cuts (like data), or demanding non-null-values (like simrec), I'm not sure if it need RegionCuts.
  
  /*** INPUT ***/

  TString InputDir = gWorkDir + "/out/GetSimpleTuple/" + setOption + "/" + targetOption;
  if (setOption == "jlab") InputDir += "/" + dirOption;
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(InputDir + "/*.root/ntuple_e");
  
  /*** MAIN ***/

  const Int_t Nkinvars = 2;
  const Int_t Nbins = 4;

  // define arrays, cut for each bin and hist
  TString kinvarIndex[Nkinvars] = {"Q", "N"};
  TString kinvarName[Nkinvars] = {"Q2", "Nu"};
  TString kinvarOption[Nkinvars] = {"Q2", "Nu"};

  // fill edges array
  Double_t EdgesKinvar[Nkinvars][Nbins+1];
  for (Int_t i = 0; i < Nbins+1; i++) {
    EdgesKinvar[0][i] = kEdgesQ2[i];
    EdgesKinvar[1][i] = kEdgesNu[i];
  }

  /*** ELECTRON NUMBERS IN ENTIRE REGION ***/

  Int_t eNumber = treeExtracted->Draw("mc_Nu>>mc(100, 0., 5.)", gCutDIS_MC, "goff");
  std::cout << "ELECTRON NUMBER(" << targetOption << ") = "
	    << eNumber << std::endl;
  eNumber = 0; // reset
  
  /*** ELECTRON NUMBERS DEPENDING ON ELECTRON VARIABLES ***/

  TCut CutBin_MC;
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) { 
      CutBin_MC = "mc_" + kinvarOption[k] + Form(" > %f && ", EdgesKinvar[k][i]) + "mc_" + kinvarOption[k] + Form(" < %f", EdgesKinvar[k][i+1]);
      eNumber = treeExtracted->Draw("mc_Nu>>mc2(100, 0., 5.)", gCutDIS_MC && CutBin_MC, "goff");
      std::cout << "ELECTRON NUMBER(" << targetOption << ", "
		<< Form("%.2f < mc_", EdgesKinvar[k][i]) + kinvarName[k] + Form(" < %.2f)", EdgesKinvar[k][i+1]) << " = "
		<< eNumber << std::endl;
      eNumber = 0; // reset
    }
  }
  
  std::cout << std::endl;
}
