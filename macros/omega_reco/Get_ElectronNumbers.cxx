#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

const Int_t Nkinvars = 2;
const Int_t Nbins = 4;

void Get_ElectronNumbers(TString targetOption) {
  // Count the number of electrons from data, according to omega binning

  /*** INPUT ***/

  TChain *electronsChain = GetElectronsChain(targetOption);
  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = "TargType == 1 && vyec > -1.4 && vyec < 1.4";  // GST format
  } else {
    CutVertex = "TargType == 2 && vyec > -1.4 && vyec < 1.4";  // GST format
  }
  TCut CutRegion_GST = "Q2 > 1. && Q2 < 4. && Nu > 2.2 && Nu < 4.2";  // GST format

  /*** MAIN ***/

  // define arrays, cut for each bin and hist
  TString kinvarIndex[Nkinvars] = {"Q", "N"};
  TString kinvarOption[Nkinvars] = {"Q2", "Nu"};

  // fill edges arrays
  Double_t EdgesKinvar[Nkinvars][Nbins + 1];

  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[0][i] = kEdgesQ2[i];
    EdgesKinvar[1][i] = kEdgesNu[i];
  }

  /*** ELECTRON NUMBERS IN ENTIRE REGION ***/

  Int_t eNumber = electronsChain->Draw("Nu>>data(200, 2.2, 4.2)", gCutDIS && CutVertex && CutRegion_GST, "goff");
  std::cout << "ELECTRON NUMBER(" << targetOption << ") = " << eNumber << std::endl;
  eNumber = 0;  // reset

  /*** ELECTRON NUMBERS DEPENDING ON ELECTRON VARIABLES ***/

  TCut CutBin;
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      CutBin = kinvarOption[k] + Form(" > %f && ", EdgesKinvar[k][i]) + kinvarOption[k] + Form(" < %f", EdgesKinvar[k][i + 1]);
      eNumber = electronsChain->Draw("Nu>>data2(200, 2.2, 4.2)", gCutDIS && CutVertex && CutBin && CutRegion_GST, "goff");
      // print results
      if (i == 0) {
        std::cout << "ELECTRON NUMBER(" << targetOption << ", " << kinvarOption[k] << ") = {" << eNumber << ", ";
      } else if (i + 1 == Nbins) {
        std::cout << eNumber << "};" << std::endl;
      } else {
        std::cout << eNumber << ", ";
      }
      eNumber = 0;  // reset
    }
  }

  std::cout << std::endl;
}
