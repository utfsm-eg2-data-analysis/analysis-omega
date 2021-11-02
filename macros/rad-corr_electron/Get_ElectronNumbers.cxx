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

void Get_ElectronNumbers(TString PartOption = "eta", TString targetOption = "D", Int_t binNu = 1, Int_t binQ2 = 1) {
  // get the acceptance corrected number of electrons in a particular bin of the EXTERNALS binning

  /*** INPUT ***/

  TChain *DataChain = GetElectronsChain(targetOption);

  TChain *SimChain = GetElectronsChain(targetOption, "sim");

  // define vertex cuts for data
  TCut CutVertex;
  if (targetOption == "D") {
    CutVertex = "TargType == 1 && vyec > -1.4 && vyec < 1.4";
  } else {  // in case of solid targets: C, Fe, Pb
    CutVertex = "TargType == 2 && vyec > -1.4 && vyec < 1.4";
  }

  /*** GET EDGES & NUMBER OF BINS ***/

  // related to particle option - now, get edges
  Double_t EdgesQ2[2];
  Double_t EdgesNu[2];
  if (PartOption == "omega") {
    EdgesQ2[0] = kEdgesQ2_Externals_Omega[binQ2];
    EdgesQ2[1] = kEdgesQ2_Externals_Omega[binQ2 + 1];
    EdgesNu[0] = kEdgesNu_Externals_Omega[binNu];
    EdgesNu[1] = kEdgesNu_Externals_Omega[binNu + 1];
  } else {  // "eta"
    EdgesQ2[0] = kEdgesQ2_Externals_Eta[binQ2];
    EdgesQ2[1] = kEdgesQ2_Externals_Eta[binQ2 + 1];
    EdgesNu[0] = kEdgesNu_Externals_Eta[binNu];
    EdgesNu[1] = kEdgesNu_Externals_Eta[binNu + 1];
  }

  /*** HISTOGRAMS ***/

  // define data, mc, and sim. rec. histogram
  TH2D *Hist_Data;
  TH2D *Hist_MC;
  TH2D *Hist_Sim;

  // define acceptance and corr hists
  TH2D *Hist_Acceptance;
  TH2D *Hist_Corr;

  // define same hist properties for every hist
  Int_t NbinsPlot = 100;
  TString HistProperties = Form("(%i, %.2f, %.2f, %i, %.2f, %.2f)", NbinsPlot, EdgesNu[0], EdgesNu[1], NbinsPlot, EdgesQ2[0], EdgesQ2[1]);

  TCut CutBin;
  TCut CutBin_MC;

  // check for errors
  if (binNu >= NbinsNu_Externals || binQ2 >= NbinsQ2_Externals) {
    std::cerr << "Selected bin number is greater than limit." << std::endl;
    exit;
  }

  // update cut
  CutBin = Form("Nu > %.2f && Nu < %.2f && Q2 > %.2f && Q2 < %.2f", EdgesNu[0], EdgesNu[1], EdgesQ2[0], EdgesQ2[1]);
  CutBin_MC = Form("mc_Nu > %.2f && mc_Nu < %.2f && mc_Q2 > %.2f && mc_Q2 < %.2f", EdgesNu[0], EdgesNu[1], EdgesQ2[0], EdgesQ2[1]);

  // make data histogram
  DataChain->Draw(Form("Q2:Nu>>data_%i_%i", binNu, binQ2) + HistProperties, gCutDIS && CutVertex && CutBin, "goff");
  Hist_Data = (TH2D *)gROOT->FindObject(Form("data_%i_%i", binNu, binQ2));

  // make sim. rec. histogram
  SimChain->Draw(Form("Q2:Nu>>sim_%i_%i", binNu, binQ2) + HistProperties, gCutDIS && CutBin, "goff");
  Hist_Sim = (TH2D *)gROOT->FindObject(Form("sim_%i_%i", binNu, binQ2));

  // make mc histogram
  SimChain->Draw(Form("mc_Q2:mc_Nu>>mc_%i_%i", binNu, binQ2) + HistProperties, gCutDIS_MC && CutBin_MC, "goff");
  Hist_MC = (TH2D *)gROOT->FindObject(Form("mc_%i_%i", binNu, binQ2));

  // make acceptance
  Hist_Acceptance =
      new TH2D(Form("acc_%i_%i", binNu, binQ2), "", NbinsPlot, EdgesNu[0], EdgesNu[1], NbinsPlot, EdgesQ2[0], EdgesQ2[1]);
  Hist_Acceptance->Divide(Hist_Sim, Hist_MC, 1, 1, "B");

  // correct data
  Hist_Corr =
      new TH2D(Form("corr_%i_%i", binNu, binQ2), "", NbinsPlot, EdgesNu[0], EdgesNu[1], NbinsPlot, EdgesQ2[0], EdgesQ2[1]);
  Hist_Corr->Divide(Hist_Data, Hist_Acceptance, 1, 1);

  /*** OUTPUT ROOT FILE ***/

  TString FilenameSufix = Form("_%i_%i", binNu, binQ2);
  TString OutputRootFilename =
      gProDir + "/gfx/rad-corr_electron/electrons_" + PartOption + "_" + targetOption + "_EXTERNALS" + FilenameSufix + ".root";
  TFile *RootFile = new TFile(OutputRootFilename, "RECREATE");

  Hist_Data->Write();
  Hist_Sim->Write();
  Hist_MC->Write();
  Hist_Acceptance->Write();
  Hist_Corr->Write();

  // print output file path
  std::cout << "The following file has been created: " << OutputRootFilename << std::endl;
}
