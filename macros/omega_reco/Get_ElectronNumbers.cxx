#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

const Int_t Ntargets = 4;
const Int_t Nkinvars = 2;
const Int_t Nbins = 4;

void Get_ElectronNumbers() {
  // Count the number of electrons from data, according to omega binning

  /*** INPUT ***/

  TChain *electronsChain[Ntargets];
  electronsChain[0] = GetElectronsChain("D");
  electronsChain[1] = GetElectronsChain("C");
  electronsChain[2] = GetElectronsChain("Fe");
  electronsChain[3] = GetElectronsChain("Pb");

  TCut CutVertex[Ntargets];
  CutVertex[0] = "TargType == 1 && vyec > -1.4 && vyec < 1.4";  // GST format
  CutVertex[1] = "TargType == 2 && vyec > -1.4 && vyec < 1.4";  // GST format
  CutVertex[2] = "TargType == 2 && vyec > -1.4 && vyec < 1.4";  // GST format
  CutVertex[3] = "TargType == 2 && vyec > -1.4 && vyec < 1.4";  // GST format

  TCut CutRegion_GST = "Q2 > 1. && Q2 < 4. && Nu > 2.2 && Nu < 4.2";  // GST format

  /*** MAIN ***/

  TString TargetName[Ntargets] = {"D", "C", "Fe", "Pb"};

  // define arrays, cut for each bin and hist
  TString kinvarIndex[Nkinvars] = {"Q", "N"};
  TString kinvarOption[Nkinvars] = {"Q2", "Nu"};

  // fill edges arrays
  Double_t EdgesKinvar[Nkinvars][Nbins + 1];

  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[0][i] = kEdgesQ2[i];
    EdgesKinvar[1][i] = kEdgesNu[i];
  }

  // define integrated and differential number of electrons
  Long_t eNumber_int[Ntargets];
  Long_t eNumber_diff[Ntargets][Nkinvars][Nbins];

  // create output file, write first line and an empty line
  TString OutputFileName = gProDir + "/macros/include/OmegaElectronNumbers.hxx";
  std::ofstream OutputTextFile{OutputFileName, std::ios::out};
  OutputTextFile << "// This library has been created automatically by \"omega_reco/Get_ElectronNumbers.cxx\"" << std::endl;
  OutputTextFile << std::endl;

  // include "Headers.hxx"
  OutputTextFile << "#ifndef HEADERS_HXX" << std::endl;
  OutputTextFile << "#include \"Headers.hxx\"" << std::endl;
  OutputTextFile << "#endif" << std::endl;
  OutputTextFile << std::endl;

  /*** ELECTRON NUMBERS IN ENTIRE REGION ***/

  // loop over targets
  for (Int_t t = 0; t < Ntargets; t++) {
    // get electron numbers
    eNumber_int[t] = electronsChain[t]->Draw("Nu>>data(200, 2.2, 4.2)", gCutDIS && CutVertex[t] && CutRegion_GST, "goff");
    // write them onto output library
    if (t == 0) {
      OutputTextFile << "const Double_t kNElec_Omega[" << Ntargets << "] = {" << eNumber_int[t] << ", ";
    } else if (t + 1 == Ntargets) {
      OutputTextFile << eNumber_int[t] << "};" << std::endl;
    } else {
      OutputTextFile << eNumber_int[t] << ", ";
    }
  }

  /*** ELECTRON NUMBERS DEPENDING ON ELECTRON VARIABLES ***/

  TCut CutBin;
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      for (Int_t i = 0; i < Nbins; i++) {
        // update bin cut
        CutBin = kinvarOption[k] + Form(" > %f && ", EdgesKinvar[k][i]) + kinvarOption[k] + Form(" < %f", EdgesKinvar[k][i + 1]);
        // get electron numbers

        eNumber_diff[t][k][i] =
            electronsChain[t]->Draw("Nu>>data2(200, 2.2, 4.2)", gCutDIS && CutVertex[t] && CutRegion_GST && CutBin, "goff");
        // write them onto output library
        if (i == 0 && t == 0) {
          OutputTextFile << "const Double_t kNElec" << kinvarOption[k] << "_Omega[" << Ntargets << "][" << Nbins << "] = {{"
                         << eNumber_diff[t][k][i] << ", ";
        } else if (i + 1 == Nbins && t + 1 == Ntargets) {
          OutputTextFile << eNumber_diff[t][k][i] << "}}; // " << TargetName[t] << std::endl;
        } else if (i + 1 == Nbins) {
          OutputTextFile << eNumber_diff[t][k][i] << "}, // " << TargetName[t] << std::endl;
          OutputTextFile << "{";
        } else {
          OutputTextFile << eNumber_diff[t][k][i] << ", ";
        }
      }
    }
  }

  // print output file path
  std::cout << "The following file has been created: " << OutputFileName << std::endl;
}
