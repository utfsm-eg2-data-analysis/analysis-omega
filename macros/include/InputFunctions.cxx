#ifndef INPUTFUNCTIONS_CXX
#define INPUTFUNCTIONS_CXX

#ifndef GLOBAL_H
#include "Global.h"
#endif

TChain *GetThreePionFinderChain(TString targetOption = "C", TString dataKind = "data") {
  // return a TChain that contains all filtered omega files
  TString dataFiles1, dataFiles2, dataFiles3;
  if (targetOption == "D" || targetOption == "All") {
    dataFiles1 = gThreePionFinderDir + "/C/*.root";
    dataFiles2 = gThreePionFinderDir + "/Fe/*.root";
    dataFiles3 = gThreePionFinderDir + "/Pb/*.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    dataFiles1 = gThreePionFinderDir + "/" + targetOption + "/*.root";
  }
  // define and return chain
  TChain *dataTree = new TChain();
  dataTree->Add(dataFiles1 + "/mix");
  if (targetOption == "D" || targetOption == "All") {
    dataTree->Add(dataFiles2 + "/mix");
    dataTree->Add(dataFiles3 + "/mix");
  }
  return dataTree;
}

TChain *GetElectronsChain(TString targetOption = "C", TString dataKind = "data") {
  // return a TChain that contains all identified scattered electrons
  TString dataFiles1, dataFiles2, dataFiles3;
  if (targetOption == "D" || targetOption == "All") {
    dataFiles1 = gGetSimpleTupleDir + "/C/*.root";
    dataFiles2 = gGetSimpleTupleDir + "/Fe/*.root";
    dataFiles3 = gGetSimpleTupleDir + "/Pb/*.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    dataFiles1 = gGetSimpleTupleDir + "/" + targetOption + "/*.root";
  }
  // define and return chain
  TChain *dataTree = new TChain();
  dataTree->Add(dataFiles1 + "/ntuple_e");
  if (targetOption == "D" || targetOption == "All") {
    dataTree->Add(dataFiles2 + "/ntuple_e");
    dataTree->Add(dataFiles3 + "/ntuple_e");
  }
  return dataTree;
}

TChain *GetTwoGammaFinderChain(TString targetOption = "C", TString dataKind = "data") {
  // return a TChain that contains all filtered eta files
  TString dataFiles1, dataFiles2, dataFiles3;
  if (targetOption == "D" || targetOption == "All") {
    dataFiles1 = gTwoGammaFinderDir + "/C/*.root";
    dataFiles2 = gTwoGammaFinderDir + "/Fe/*.root";
    dataFiles3 = gTwoGammaFinderDir + "/Pb/*.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    dataFiles1 = gTwoGammaFinderDir + "/" + targetOption + "/*.root";
  }
  // define and return chain
  TChain *dataTree = new TChain();
  dataTree->Add(dataFiles1 + "/mix");
  if (targetOption == "D" || targetOption == "All") {
    dataTree->Add(dataFiles2 + "/mix");
    dataTree->Add(dataFiles3 + "/mix");
  }
  return dataTree;
}

TChain *GetEventMixingChain(TString targetOption = "C", TString dataKind = "data") {
  // return a TChain that contains all background files generated via event-mixing for omega background subtraction
  TString bkgFiles1, bkgFiles2, bkgFiles3;
  if (targetOption == "D" || targetOption == "All") {
    bkgFiles1 = gEventMixingDir + "/C/*.root";
    bkgFiles2 = gEventMixingDir + "/Fe/*.root";
    bkgFiles3 = gEventMixingDir + "/Pb/*.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    bkgFiles1 = gEventMixingDir + "/" + targetOption + "/*.root";
  }
  // define and return chain
  TChain *bkgTree = new TChain();
  bkgTree->Add(bkgFiles1 + "/mix");
  if (targetOption == "D" || targetOption == "All") {
    bkgTree->Add(bkgFiles2 + "/mix");
    bkgTree->Add(bkgFiles3 + "/mix");
  }
  return bkgTree;
}

void SetAliases(TChain *treeExtracted) {
  treeExtracted->SetAlias("pippimM",
                          "TMath::Sqrt(2 * 0.13957 * 0.13957 + 2 * E[0] * E[1] - 2 * (Px[0] * Px[1] + Py[0] * Py[1] + Pz[0] * Pz[1]))");
  treeExtracted->SetAlias(
      "pippi0M", "TMath::Sqrt(0.13957 * 0.13957 + pi0M * pi0M + 2 * E[0] * pi0E - 2 * (Px[0] * pi0Px + Py[0] * pi0Py + Pz[0] * pi0Pz))");
  treeExtracted->SetAlias("gamma1_OpAngle", "TMath::ACos((Px[2] * Pex + Py[2] * Pey + Pz[2] * Pez) / Pe / P[2]) * TMath::RadToDeg()");
  treeExtracted->SetAlias("gamma2_OpAngle", "TMath::ACos((Px[3] * Pex + Py[3] * Pey + Pz[3] * Pez) / Pe / P[3]) * TMath::RadToDeg()");
}

void SetAliasesEta(TChain *treeExtracted) {
  treeExtracted->SetAlias("gamma1_OpAngle", "TMath::ACos((Px[0] * Pex + Py[0] * Pey + Pz[0] * Pez) / Pe / P[0]) * TMath::RadToDeg()");
  treeExtracted->SetAlias("gamma2_OpAngle", "TMath::ACos((Px[1] * Pex + Py[1] * Pey + Pz[1] * Pez) / Pe / P[1]) * TMath::RadToDeg()");
}

#endif
