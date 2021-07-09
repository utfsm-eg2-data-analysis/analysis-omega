#ifndef GLOBAL_H
#include "Global.h"
#endif

void RadCorr_GetElectronNumber(TString targetOption = "C") {
  // Count the number of electrons from data
  // Correct them with EXTERNALS and Coulomb Corr. Factors
  // Sum up corrected number of electrons into bins of interest

  Double_t kEdgesNu_extern[7] = {2.2, 2.58, 2.96, 3.35, 3.68, 3.94, 4.2};
  Double_t kEdgesQ2_extern[6] = {1, 1.25, 1.51, 1.92, 2.96, 4.0};

  const Int_t NbinsNu = (Int_t)(sizeof(kEdgesNu_extern) / sizeof(kEdgesNu_extern[0])) - 1;
  const Int_t NbinsQ2 = (Int_t)(sizeof(kEdgesQ2_extern) / sizeof(kEdgesQ2_extern[0])) - 1;

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

  /*** MAIN ***/

  /*** ELECTRON NUMBERS IN ENTIRE REGION ***/

  Int_t eNumber_total = treeExtracted->Draw("Nu>>data(100, 0., 5.)", gCutDIS && CutVertex, "goff");
  std::cout << std::endl;
  std::cout << "ELECTRON NUMBER(" << targetOption << ") = " << eNumber_total << std::endl;
  Int_t eNumber[NbinsQ2][NbinsNu];  // reset

  /*** ELECTRON NUMBERS DEPENDING ON ELECTRON VARIABLES ***/

  TCut CutBin;
  for (Int_t q = 0; q < NbinsQ2; q++) {
    for (Int_t n = 0; n < NbinsNu; n++) {
      CutBin = Form("Q2 > %.2f && Q2 < %.2f && Nu > %.2f && Nu < %.2f", kEdgesQ2_extern[q], kEdgesQ2_extern[q + 1], kEdgesNu_extern[n],
                    kEdgesNu_extern[n + 1]);
      eNumber[q][n] = treeExtracted->Draw("Nu>>data2(100, 0., 5.)", gCutDIS && CutVertex && CutBin, "goff");
      std::cout << "ELECTRON NUMBER(" << targetOption << ", "
                << Form("%.2f < Q2 < %.2f, %.2f < Nu < %.2f)", kEdgesQ2_extern[q], kEdgesQ2_extern[q + 1], kEdgesNu_extern[n],
                        kEdgesNu_extern[n + 1])
                << " = " << eNumber[q][n] << std::endl;
    }
  }
  std::cout << std::endl;

  /*** READ FROM EXTERNALS ***/

  TString targetSufix;
  if (targetOption == "D") targetSufix = "d2";
  if (targetOption == "C") targetSufix = "C12";
  if (targetOption == "Fe") targetSufix = "Fe56";
  if (targetOption == "Pb") targetSufix = "Pb208";

  std::ifstream ExternalsFile;
  Double_t RadCorrFactor[NbinsQ2][NbinsNu];
  Double_t CoulombCorr[NbinsQ2][NbinsNu];

  ExternalsFile.open(gExternalsDir + "/OUT/clas" + targetSufix + ".out", std::ios::in);

  std::string auxLine;
  TString auxString[13];  // 13 = number of columns in the .out files
  Int_t countLine = 0;
  Int_t binInNu;
  Int_t binInQ2;
  while (getline(ExternalsFile, auxLine)) {
    // std::cout << auxLine << std::endl;
    for (Int_t i = 0; i < 13; i++) {
      if (countLine > 0) {  // given the first line represents the name of the columns
        auxString[i] = ((TObjString *)(((TString)auxLine).Tokenize("   ")->At(i)))->String();
        // std::cout << auxString[i] << std::endl;
      }
    }
    if (countLine > 0) {
      binInNu = (countLine - 1) / NbinsQ2;
      binInQ2 = (countLine - 1) - NbinsQ2 * binInNu;
      // Column 0: Ebeam
      // Column 5: Sig_Born
      // Column 8: Sig_Rad
      RadCorrFactor[binInQ2][binInNu] = auxString[8].Atof() / auxString[5].Atof();  // Sig_Rad / Sig_Born
      CoulombCorr[binInQ2][binInNu] = auxString[12].Atof();
    }
    countLine++;
  }

  for (Int_t q = 0; q < NbinsQ2; q++) {
    for (Int_t n = 0; n < NbinsNu; n++) {
      std::cout << "ELECTRON NUMBER(" << targetOption << ", "
                << Form("%.2f < Q2 < %.2f, %.2f < Nu < %.2f)", kEdgesQ2_extern[q], kEdgesQ2_extern[q + 1], kEdgesNu_extern[n],
                        kEdgesNu_extern[n + 1])
                << " = " << eNumber[q][n] * CoulombCorr[q][n] / RadCorrFactor[q][n] << std::endl;
    }
  }
  std::cout << std::endl;

  /*** SUM REAL BINS ***/
  // going back to 1D: from custom binning 5x6 to just 4

  // Sum of all //
  Double_t eNumberAll_real = 0;

  for (Int_t q = 0; q < NbinsQ2; q++) {
    for (Int_t n = 0; n < NbinsNu; n++) {
      if (q == 3 && n == 0) {
      } else if (q == 4 && n == 0) {
      } else if (q == 4 && n == 1) {
      } else {
        eNumberAll_real += eNumber[q][n] * CoulombCorr[q][n] / RadCorrFactor[q][n];
        std::cout << "(" << q << ", " << n << ") = " << eNumber[q][n] * CoulombCorr[q][n] / RadCorrFactor[q][n] << std::endl;
      }
    }
  }

  // Print All //

  std::cout << "ELECTRON NUMBER(" << targetOption << ") = {" << eNumberAll_real << "};" << std::endl;
  std::cout << std::endl;

  const Int_t Nbins = 4;

  // Q2 //

  Double_t eNumberQ2_real[Nbins];
  // bin 1
  eNumberQ2_real[0] = 0;
  for (Int_t n = 0; n < NbinsNu; n++) eNumberQ2_real[0] += eNumber[0][n] * CoulombCorr[0][n] / RadCorrFactor[0][n];
  // bin 2
  eNumberQ2_real[1] = 0;
  for (Int_t n = 0; n < NbinsNu; n++) eNumberQ2_real[1] += eNumber[1][n] * CoulombCorr[1][n] / RadCorrFactor[1][n];
  // bin 3
  eNumberQ2_real[2] = 0;
  for (Int_t n = 0; n < NbinsNu; n++) eNumberQ2_real[2] += eNumber[2][n] * CoulombCorr[2][n] / RadCorrFactor[2][n];
  // bin 4
  eNumberQ2_real[3] = 0;
  for (Int_t n = 0; n < NbinsNu; n++) {
    if (n != 0) eNumberQ2_real[3] += eNumber[3][n] * CoulombCorr[3][n] / RadCorrFactor[3][n];
    if (n != 0 && n != 1) eNumberQ2_real[3] += eNumber[4][n] * CoulombCorr[4][n] / RadCorrFactor[4][n];
  }

  // Print Q2 //

  for (Int_t q = 0; q < Nbins; q++) {
    if (q == 0)
      std::cout << "ELECTRON NUMBER(" << targetOption << ") = {" << eNumberQ2_real[q] << ", ";
    else if (q + 1 == Nbins)
      std::cout << eNumberQ2_real[q] << "};" << std::endl;
    else
      std::cout << eNumberQ2_real[q] << ", ";
  }
  std::cout << std::endl;

  // Nu //

  Double_t eNumberNu_real[Nbins];
  // bin 1
  eNumberNu_real[0] = 0;
  for (Int_t q = 0; q < NbinsQ2; q++) {
    if (q != 3 && q != 4) eNumberNu_real[0] += eNumber[q][0] * CoulombCorr[q][0] / RadCorrFactor[q][0];
    if (q != 4) eNumberNu_real[0] += eNumber[q][1] * CoulombCorr[q][1] / RadCorrFactor[q][1];
    eNumberNu_real[0] += eNumber[q][2] * CoulombCorr[q][2] / RadCorrFactor[q][2];
  }
  // bin 2
  eNumberNu_real[1] = 0;
  for (Int_t q = 0; q < NbinsQ2; q++) eNumberNu_real[1] += eNumber[q][3] * CoulombCorr[q][3] / RadCorrFactor[q][3];
  // bin 3
  eNumberNu_real[2] = 0;
  for (Int_t q = 0; q < NbinsQ2; q++) eNumberNu_real[2] += eNumber[q][4] * CoulombCorr[q][4] / RadCorrFactor[q][4];
  // bin 4
  eNumberNu_real[3] = 0;
  for (Int_t q = 0; q < NbinsQ2; q++) eNumberNu_real[3] += eNumber[q][5] * CoulombCorr[q][5] / RadCorrFactor[q][5];

  // Print Nu //

  for (Int_t n = 0; n < Nbins; n++) {
    if (n == 0)
      std::cout << "ELECTRON NUMBER(" << targetOption << ") = {" << eNumberNu_real[n] << ", ";
    else if (n + 1 == Nbins)
      std::cout << eNumberNu_real[n] << "};" << std::endl;
    else
      std::cout << eNumberNu_real[n] << ", ";
  }
  std::cout << std::endl;
}
