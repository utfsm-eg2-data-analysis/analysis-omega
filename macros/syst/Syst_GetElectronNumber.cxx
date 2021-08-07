#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SYSTEMATICS_H
#include "Systematics.h"
#endif

void Syst_GetElectronNumber(TString targetOption, TString systOption = "omega") {
  // Count the number of electrons from data.

  /*** INPUT ***/

  TChain *treeExtracted = new TChain();
  TCut CutVertex;
  if (targetOption == "D") {  // unified D
    treeExtracted->Add(gWorkDir + "/out/GetSimpleTuple/data/C/*.root/ntuple_e");
    treeExtracted->Add(gWorkDir + "/out/GetSimpleTuple/data/Fe/*.root/ntuple_e");
    treeExtracted->Add(gWorkDir + "/out/GetSimpleTuple/data/Pb/*.root/ntuple_e");
    CutVertex = "TargType == 1 && vyec > -1.4 && vyec < 1.4";  // GST format
  } else {
    treeExtracted->Add(gWorkDir + "/out/GetSimpleTuple/data/" + targetOption + "/*.root/ntuple_e");
    CutVertex = "TargType == 2 && vyec > -1.4 && vyec < 1.4";  // GST format
  }
  TCut gCutRegion_GST = "Q2 > 1. && Q2 < 4. && Nu > 2.2 && Nu < 4.2";  // GST format

  /*** MAIN ***/

  const Int_t Nkinvars = 2;
  Int_t Nbins;
  if (systOption == "3b")
    Nbins = 3;
  else if (systOption == "5b")
    Nbins = 5;

  // define arrays, cut for each bin and hist
  TString kinvarIndex[Nkinvars] = {"Q", "N"};
  TString kinvarName[Nkinvars] = {"Q2", "Nu"};
  TString kinvarOption[Nkinvars] = {"Q2", "Nu"};

  // fill edges arrays
  Double_t EdgesKinvar[Nkinvars][Nbins + 1];

  for (Int_t i = 0; i < Nbins + 1; i++) {
    if (systOption == "3b") {
      EdgesKinvar[0][i] = kEdgesQ2_ThreeBins[i];
      EdgesKinvar[1][i] = kEdgesNu_ThreeBins[i];
    } else if (systOption == "5b") {
      EdgesKinvar[0][i] = kEdgesQ2_FiveBins[i];
      EdgesKinvar[1][i] = kEdgesNu_FiveBins[i];
    }
  }

  /*** ELECTRON NUMBERS IN ENTIRE REGION ***/

  Int_t eNumber = treeExtracted->Draw("Nu>>data(100, 0., 5.)", gCutDIS && CutVertex && gCutRegion_GST, "goff");
  std::cout << "ELECTRON NUMBER(" << targetOption << ") = " << eNumber << std::endl;
  eNumber = 0;  // reset

  /*** ELECTRON NUMBERS DEPENDING ON ELECTRON VARIABLES ***/

  TCut CutBin;
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      CutBin = kinvarOption[k] + Form(" > %f && ", EdgesKinvar[k][i]) + kinvarOption[k] + Form(" < %f", EdgesKinvar[k][i + 1]);
      eNumber = treeExtracted->Draw("Nu>>data2(100, 0., 5.)", gCutDIS && CutVertex && CutBin && gCutRegion_GST, "goff");
      std::cout << "ELECTRON NUMBER(" << targetOption << ", "
                << Form("%.2f < ", EdgesKinvar[k][i]) + kinvarName[k] + Form(" < %.2f)", EdgesKinvar[k][i + 1]) << " = " << eNumber
                << std::endl;
      eNumber = 0;  // reset
    }
  }

  std::cout << std::endl;
}
