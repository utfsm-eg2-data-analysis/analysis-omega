#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#ifndef RADIATIVECORRECTIONS_H
#include "RadiativeCorrections.h"
#endif

void Get_Centroids(TString partOption = "eta", TString targetOption = "D") {
  // get the centroids of acceptance corrected (Nu, Q2) bins based on EXTERNALS binning

  /*** INPUT ***/

  /*** HISTOGRAMS ***/

  TFile *InputFile[NbinsNu_Externals][NbinsQ2_Externals];

  TH2D *Hist_Corr[NbinsNu_Externals][NbinsQ2_Externals];

  Double_t meanX[NbinsNu_Externals][NbinsQ2_Externals];
  Double_t meanY[NbinsNu_Externals][NbinsQ2_Externals];

  // loop over listed bins in file
  for (Int_t n = 0; n < NbinsNu_Externals; n++) {
    for (Int_t q = 0; q < NbinsQ2_Externals; q++) {

      // open files (read only)
      TString auxSufix = Form("_%i_%i", n, q);
      TString InputFilename =
          gProDir + "/gfx/rad-corr_electron/electrons_" + partOption + "_" + targetOption + "_EXTERNALS" + auxSufix + ".root";
      InputFile[n][q] = new TFile(InputFilename);

      std::cout << "Reading file: " << InputFilename << std::endl;

      Hist_Corr[n][q] = (TH2D *)InputFile[n][q]->Get(Form("corr_%i_%i", n, q));

      // get 2D centroids
      meanX[n][q] = Hist_Corr[n][q]->GetMean(1);
      meanY[n][q] = Hist_Corr[n][q]->GetMean(2);
    }
  }

  /*** OUTPUT TEXT FILE ***/

  TString OutputTextFilename = gProDir + "/gfx/rad-corr_electron/centroids_" + partOption + "_" + targetOption + ".txt";
  std::ofstream OutFile(OutputTextFilename, std::ios::out);

  OutFile << "('Nu','Q2') (";
  for (Int_t n = 0; n < NbinsNu_Externals; n++) {
    for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
      OutFile << "(" << meanX[n][q] << "," << meanY[n][q] << ")";
      if (n + 1 == NbinsNu_Externals && q + 1 == NbinsQ2_Externals) {
        OutFile << ")";
      } else {
        OutFile << ",";
      }
    }
  }
  OutFile.close();

  std::cout << "The following file has been created: " << OutputTextFilename << std::endl;
}
