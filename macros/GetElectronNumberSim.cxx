#ifndef GLOBAL_H
#include "Global.h"
#endif

void GetElectronNumberSim(TString setOption, TString targetOption, TString dirOption = "") {
  // Count the number of electrons from simulation reconstructed files.
  // Doesn't need vertex cuts (like data).
  
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

  TCut CutNonNull = "Q2 != -9999";
  TCut CutRegion = "Q2 > 1.0 && Q2 < 4.0 && Nu > 2.2 && Nu < 4.2"; // GST format, there are no omega variables yet
  Int_t eNumber = treeExtracted->Draw("Nu>>simrec(100, 0., 5.)", gCutDIS && CutRegion && CutNonNull, "goff");
  std::cout << "ELECTRON NUMBER(" << targetOption << ") = "
	    << eNumber << std::endl;
  eNumber = 0; // reset
  
  /*** ELECTRON NUMBERS DEPENDING ON ELECTRON VARIABLES ***/

  TCut CutBin;
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) { 
      CutBin = kinvarOption[k] + Form(" > %f && ", EdgesKinvar[k][i]) + kinvarOption[k] + Form(" < %f", EdgesKinvar[k][i+1]);
      eNumber = treeExtracted->Draw("Nu>>simrec2(100, 0., 5.)", gCutDIS && CutBin && CutRegion && CutNonNull, "goff");
      std::cout << "ELECTRON NUMBER(" << targetOption << ", "
		<< Form("%.2f < ", EdgesKinvar[k][i]) + kinvarName[k] + Form(" < %.2f)", EdgesKinvar[k][i+1]) << " = "
		<< eNumber << std::endl;
      eNumber = 0; // reset
    }
  }
  
  std::cout << std::endl;
}
