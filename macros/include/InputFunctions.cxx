#ifndef INPUTFUNCTIONS_CXX
#define INPUTFUNCTIONS_CXX

#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef ACCEPTANCE_H
#include "Acceptance.h"
#endif

TChain *GetTestsChain(TString test = "no-ec", TString dataKind = "data") {
  // return a TChain to get PID tests for electrons, after executing GetSimpleTuple on C data, specifically
  TString dataFiles1;
  dataFiles1 = gTestDir + "/C/pruned*_" + test + ".root";
  // define and return chain
  TChain *outputChain = new TChain();
  outputChain->Add(dataFiles1 + "/ntuple_e");
  return outputChain;
}

TChain *GetElectronsChain(TString targetOption = "C", TString dataKind = "data", TString part = "omega") {
  // return a TChain that contains all identified scattered electrons
  TString inputFiles[7];
  TString GetSimpleTupleDir;  // non-global variable
  if (dataKind == "data") {
    // data case: set GSTdir to global var
    GetSimpleTupleDir = gGetSimpleTupleDir;
    // assign dirs
    if (targetOption == "D" || targetOption == "All") {
      inputFiles[0] = GetSimpleTupleDir + "/C/*.root";
      inputFiles[1] = GetSimpleTupleDir + "/Fe/*.root";
      inputFiles[2] = GetSimpleTupleDir + "/Pb/*.root";
    } else {  // if targetOption == "C" || "Fe" || "Pb"
      inputFiles[0] = GetSimpleTupleDir + "/" + targetOption + "/*.root";
    }
  } else {
    // simulations case: set GSTdir according to particle
    if (part == "omega") {
      GetSimpleTupleDir = gGetSimpleTupleDir_OmegaSim;
    } else {  // if part == eta
      GetSimpleTupleDir = gGetSimpleTupleDir_EtaSim;
    }
    // assign dirs
    if (targetOption == "D") {
      inputFiles[0] = GetSimpleTupleDir + "/" + targetOption + "/00/*.root";
      inputFiles[1] = GetSimpleTupleDir + "/" + targetOption + "/01/*.root";
      inputFiles[2] = GetSimpleTupleDir + "/" + targetOption + "/02/*.root";
    } else if (targetOption == "Fe") {
      inputFiles[0] = GetSimpleTupleDir + "/" + targetOption + "/00/*.root";
      inputFiles[1] = GetSimpleTupleDir + "/" + targetOption + "/01/*.root";
    } else if (targetOption == "C" || targetOption == "Pb") {
      inputFiles[0] = GetSimpleTupleDir + "/" + targetOption + "/00/*.root";
    } else {
      inputFiles[0] = GetSimpleTupleDir + "/D/00/*.root";
      inputFiles[1] = GetSimpleTupleDir + "/D/01/*.root";
      inputFiles[2] = GetSimpleTupleDir + "/D/02/*.root";
      inputFiles[5] = GetSimpleTupleDir + "/C/00/*.root";
      inputFiles[3] = GetSimpleTupleDir + "/Fe/00/*.root";
      inputFiles[4] = GetSimpleTupleDir + "/Fe/01/*.root";
      inputFiles[6] = GetSimpleTupleDir + "/Pb/00/*.root";
    }
  }
  // define and return chain
  TChain *outputChain = new TChain();
  if (dataKind == "data") {
    // data case
    outputChain->Add(inputFiles[0] + "/ntuple_e");
    if (targetOption == "D" || targetOption == "All") {
      outputChain->Add(inputFiles[1] + "/ntuple_e");
      outputChain->Add(inputFiles[2] + "/ntuple_e");
    }
  } else {
    // simulations case
    outputChain->Add(inputFiles[0] + "/ntuple_e");
    if (targetOption == "Fe") {
      outputChain->Add(inputFiles[1] + "/ntuple_e");
    } else if (targetOption == "D") {
      outputChain->Add(inputFiles[1] + "/ntuple_e");
      outputChain->Add(inputFiles[2] + "/ntuple_e");
    } else if (targetOption == "All") {
      outputChain->Add(inputFiles[1] + "/ntuple_e");
      outputChain->Add(inputFiles[2] + "/ntuple_e");
      outputChain->Add(inputFiles[3] + "/ntuple_e");
      outputChain->Add(inputFiles[4] + "/ntuple_e");
      outputChain->Add(inputFiles[5] + "/ntuple_e");
      outputChain->Add(inputFiles[6] + "/ntuple_e");
    }
  }
  return outputChain;
}

TChain *GetThreePionFinderChain(TString targetOption = "C", TString dataKind = "data") {
  // return a TChain that contains all filtered omega files
  TString inputFiles[7];
  TString ThreePionFinderDir;  // non-global variable
  if (dataKind == "data") {
    // data case: set TPFdir to global var
    ThreePionFinderDir = gThreePionFinderDir;
    // assign dirs
    if (targetOption == "D" || targetOption == "A" || targetOption == "All") {
      inputFiles[0] = ThreePionFinderDir + "/C/*.root";
      inputFiles[1] = ThreePionFinderDir + "/Fe/*.root";
      inputFiles[2] = ThreePionFinderDir + "/Pb/*.root";
    } else {  // if targetOption == "C" || "Fe" || "Pb"
      inputFiles[0] = ThreePionFinderDir + "/" + targetOption + "/*.root";
    }
  } else {
    // simulations case: set TPFdir according to particle
    ThreePionFinderDir = gThreePionFinderDir_OmegaSim;
    // assign dirs
    if (targetOption == "D") {
      inputFiles[0] = ThreePionFinderDir + "/" + targetOption + "/00/*.root";
      inputFiles[1] = ThreePionFinderDir + "/" + targetOption + "/01/*.root";
      inputFiles[2] = ThreePionFinderDir + "/" + targetOption + "/02/*.root";
    } else if (targetOption == "Fe") {
      inputFiles[0] = ThreePionFinderDir + "/" + targetOption + "/00/*.root";
      inputFiles[1] = ThreePionFinderDir + "/" + targetOption + "/01/*.root";
    } else if (targetOption == "C" || targetOption == "Pb") {
      inputFiles[0] = ThreePionFinderDir + "/" + targetOption + "/00/*.root";
    } else if (targetOption == "A") {  // solid targets
      inputFiles[0] = ThreePionFinderDir + "/C/00/*.root";
      inputFiles[1] = ThreePionFinderDir + "/Fe/00/*.root";
      inputFiles[2] = ThreePionFinderDir + "/Fe/01/*.root";
      inputFiles[3] = ThreePionFinderDir + "/Pb/00/*.root";
    } else {  // all
      inputFiles[0] = ThreePionFinderDir + "/D/00/*.root";
      inputFiles[1] = ThreePionFinderDir + "/D/01/*.root";
      inputFiles[2] = ThreePionFinderDir + "/D/02/*.root";
      inputFiles[3] = ThreePionFinderDir + "/C/00/*.root";
      inputFiles[4] = ThreePionFinderDir + "/Fe/00/*.root";
      inputFiles[5] = ThreePionFinderDir + "/Fe/01/*.root";
      inputFiles[6] = ThreePionFinderDir + "/Pb/00/*.root";
    }
  }
  // define and return chain
  TChain *outputChain = new TChain();
  if (dataKind == "data") {
    // data case
    outputChain->Add(inputFiles[0] + "/mix");
    if (targetOption == "D" || targetOption == "All") {
      outputChain->Add(inputFiles[1] + "/mix");
      outputChain->Add(inputFiles[2] + "/mix");
    }
  } else {
    // simulations case
    outputChain->Add(inputFiles[0] + "/mix");
    if (targetOption == "Fe") {
      outputChain->Add(inputFiles[1] + "/mix");
    } else if (targetOption == "D") {
      outputChain->Add(inputFiles[1] + "/mix");
      outputChain->Add(inputFiles[2] + "/mix");
    } else if (targetOption == "A") {
      outputChain->Add(inputFiles[1] + "/mix");
      outputChain->Add(inputFiles[2] + "/mix");
      outputChain->Add(inputFiles[3] + "/mix");
    } else if (targetOption == "All") {
      outputChain->Add(inputFiles[1] + "/mix");
      outputChain->Add(inputFiles[2] + "/mix");
      outputChain->Add(inputFiles[3] + "/mix");
      outputChain->Add(inputFiles[4] + "/mix");
      outputChain->Add(inputFiles[5] + "/mix");
      outputChain->Add(inputFiles[6] + "/mix");
    }
  }
  return outputChain;
}

TChain *GetTwoGammaFinderChain(TString targetOption = "C", TString dataKind = "data") {
  // return a TChain that contains all filtered eta files
  TString inputFiles[7];
  TString TwoGammaFinderDir;  // non-global variable
  if (dataKind == "data") {
    // data case: set TGFdir to global var
    TwoGammaFinderDir = gTwoGammaFinderDir;
    // assign dirs
    if (targetOption == "D" || targetOption == "A" || targetOption == "All") {
      inputFiles[0] = TwoGammaFinderDir + "/C/*.root";
      inputFiles[1] = TwoGammaFinderDir + "/Fe/*.root";
      inputFiles[2] = TwoGammaFinderDir + "/Pb/*.root";
    } else {  // if targetOption == "C" || "Fe" || "Pb"
      inputFiles[0] = TwoGammaFinderDir + "/" + targetOption + "/*.root";
    }
  } else {
    // simulations case: set TGFdir according to particle
    TwoGammaFinderDir = gTwoGammaFinderDir_EtaSim;
    // assign dirs
    if (targetOption == "D") {
      inputFiles[0] = TwoGammaFinderDir + "/" + targetOption + "/00/*.root";
      inputFiles[1] = TwoGammaFinderDir + "/" + targetOption + "/01/*.root";
      inputFiles[2] = TwoGammaFinderDir + "/" + targetOption + "/02/*.root";
    } else if (targetOption == "Fe") {
      inputFiles[0] = TwoGammaFinderDir + "/" + targetOption + "/00/*.root";
      inputFiles[1] = TwoGammaFinderDir + "/" + targetOption + "/01/*.root";
    } else if (targetOption == "C" || targetOption == "Pb") {
      inputFiles[0] = TwoGammaFinderDir + "/" + targetOption + "/00/*.root";
    } else if (targetOption == "A") {  // solid targets
      inputFiles[0] = TwoGammaFinderDir + "/C/00/*.root";
      inputFiles[1] = TwoGammaFinderDir + "/Fe/00/*.root";
      inputFiles[2] = TwoGammaFinderDir + "/Fe/01/*.root";
      inputFiles[3] = TwoGammaFinderDir + "/Pb/00/*.root";
    } else {
      inputFiles[0] = TwoGammaFinderDir + "/D/00/*.root";
      inputFiles[1] = TwoGammaFinderDir + "/D/01/*.root";
      inputFiles[2] = TwoGammaFinderDir + "/D/02/*.root";
      inputFiles[3] = TwoGammaFinderDir + "/C/00/*.root";
      inputFiles[4] = TwoGammaFinderDir + "/Fe/00/*.root";
      inputFiles[5] = TwoGammaFinderDir + "/Fe/01/*.root";
      inputFiles[6] = TwoGammaFinderDir + "/Pb/00/*.root";
    }
  }
  // define and return chain
  TChain *outputChain = new TChain();
  if (dataKind == "data") {
    // data case
    outputChain->Add(inputFiles[0] + "/mix");
    if (targetOption == "D" || targetOption == "All") {
      outputChain->Add(inputFiles[1] + "/mix");
      outputChain->Add(inputFiles[2] + "/mix");
    }
  } else {
    // simulations case
    outputChain->Add(inputFiles[0] + "/mix");
    if (targetOption == "Fe") {
      outputChain->Add(inputFiles[1] + "/mix");
    } else if (targetOption == "D") {
      outputChain->Add(inputFiles[1] + "/mix");
      outputChain->Add(inputFiles[2] + "/mix");
    } else if (targetOption == "A") {
      outputChain->Add(inputFiles[1] + "/mix");
      outputChain->Add(inputFiles[2] + "/mix");
      outputChain->Add(inputFiles[3] + "/mix");
    } else if (targetOption == "All") {
      outputChain->Add(inputFiles[1] + "/mix");
      outputChain->Add(inputFiles[2] + "/mix");
      outputChain->Add(inputFiles[3] + "/mix");
      outputChain->Add(inputFiles[4] + "/mix");
      outputChain->Add(inputFiles[5] + "/mix");
      outputChain->Add(inputFiles[6] + "/mix");
    }
  }
  return outputChain;
}

TChain *GetEventMixingChain(TString targetOption = "C", TString dataKind = "data") {
  // return a TChain that contains all background files generated via event-mixing for omega background subtraction
  TString inputFiles[7];
  TString EventMixingDir;  // non-global variable
  if (dataKind == "data") {
    // data case: set EVMdir to global var
    EventMixingDir = gEventMixingDir;
    // assign dirs
    if (targetOption == "D" || targetOption == "A" || targetOption == "All") {
      inputFiles[0] = EventMixingDir + "/C/*.root";
      inputFiles[1] = EventMixingDir + "/Fe/*.root";
      inputFiles[2] = EventMixingDir + "/Pb/*.root";
    } else {  // if targetOption == "C" || "Fe" || "Pb"
      inputFiles[0] = EventMixingDir + "/" + targetOption + "/*.root";
    }
  } else {
    // simulations case: set EVMdir according to particle
    EventMixingDir = gEventMixingDir_OmegaSim;
    // assign dirs
    if (targetOption == "D") {
      inputFiles[0] = EventMixingDir + "/" + targetOption + "/00/*.root";
      inputFiles[1] = EventMixingDir + "/" + targetOption + "/01/*.root";
      inputFiles[2] = EventMixingDir + "/" + targetOption + "/02/*.root";
    } else if (targetOption == "Fe") {
      inputFiles[0] = EventMixingDir + "/" + targetOption + "/00/*.root";
      inputFiles[1] = EventMixingDir + "/" + targetOption + "/01/*.root";
    } else if (targetOption == "C" || targetOption == "Pb") {
      inputFiles[0] = EventMixingDir + "/" + targetOption + "/00/*.root";
    } else if (targetOption == "A") {  // solid targets
      inputFiles[0] = EventMixingDir + "/C/00/*.root";
      inputFiles[1] = EventMixingDir + "/Fe/00/*.root";
      inputFiles[2] = EventMixingDir + "/Fe/01/*.root";
      inputFiles[3] = EventMixingDir + "/Pb/00/*.root";
    } else {
      inputFiles[0] = EventMixingDir + "/D/00/*.root";
      inputFiles[1] = EventMixingDir + "/D/01/*.root";
      inputFiles[2] = EventMixingDir + "/D/02/*.root";
      inputFiles[3] = EventMixingDir + "/C/00/*.root";
      inputFiles[4] = EventMixingDir + "/Fe/00/*.root";
      inputFiles[5] = EventMixingDir + "/Fe/01/*.root";
      inputFiles[6] = EventMixingDir + "/Pb/00/*.root";
    }
  }
  // define and return chain
  TChain *outputChain = new TChain();
  if (dataKind == "data") {
    // data case
    outputChain->Add(inputFiles[0] + "/mix");
    if (targetOption == "D" || targetOption == "All") {
      outputChain->Add(inputFiles[1] + "/mix");
      outputChain->Add(inputFiles[2] + "/mix");
    }
  } else {
    // simulations case
    outputChain->Add(inputFiles[0] + "/mix");
    if (targetOption == "Fe") {
      outputChain->Add(inputFiles[1] + "/mix");
    } else if (targetOption == "D") {
      outputChain->Add(inputFiles[1] + "/mix");
      outputChain->Add(inputFiles[2] + "/mix");
    } else if (targetOption == "A") {
      outputChain->Add(inputFiles[1] + "/mix");
      outputChain->Add(inputFiles[2] + "/mix");
      outputChain->Add(inputFiles[3] + "/mix");
    } else if (targetOption == "All") {
      outputChain->Add(inputFiles[1] + "/mix");
      outputChain->Add(inputFiles[2] + "/mix");
      outputChain->Add(inputFiles[3] + "/mix");
      outputChain->Add(inputFiles[4] + "/mix");
      outputChain->Add(inputFiles[5] + "/mix");
      outputChain->Add(inputFiles[6] + "/mix");
    }
  }
  return outputChain;
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
