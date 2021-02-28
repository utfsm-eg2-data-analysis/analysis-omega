#ifndef GLOBAL_H
#define GLOBAL_H

/*** GLOBAL VARIABLES ***/

TString gProDir = getenv("PRODIR");
TString gWorkDir = getenv("WORKDIR");
TString gDataDir = gWorkDir + "/out/FilterNCombine/data";

TCut gCutDIS = "Q2 > 1. && W > 2. && Yb < 0.85";
TCut gCutPi0 = "0.059 < pi0M && pi0M < 0.203";  // mean=0.131 & sigma=0.024
TCut gCutRegion = "Q2 > 1. && Q2 < 4. && Nu > 2.2 && Nu < 4.2 && wPt2 > 0 && wPt2 < 1.5 && wZ > 0.5 && wZ < 0.9";
TCut gCutSolid = "TargType == 2 && Yec > -1.4 && Yec < 1.4";
TCut gCutLiquid = "TargType == 1 && Yec > -1.4 && Yec < 1.4";
TCut gCutKaons = "0.48 > pippimM || 0.51 < pippimM";
TCut gCutPhotonsOpAngle = "deltaTheta[2] > 10. && deltaTheta[3] > 10.";

TCut gCutDIS_MC = "mc_Q2 > 1 && mc_W > 2 && mc_Yb < 0.85";
TCut gCutPi0_MC = "0.1333 < mc_pi0M && mc_pi0M < 0.1367";  // mean=0.135 & sigma=5.7e-4
TCut gCutRegion_MC = "mc_Q2 > 1. && mc_Q2 < 4. && mc_Nu > 2.2 && mc_Nu < 4.2 && mc_wPt2 > 0 && mc_wPt2 < 1.5 && mc_wZ > 0.5 && mc_wZ < 0.9";
TCut gCutKaons_MC = "0.48 > mc_pippimM || 0.51 < mc_pippimM";
TCut gCutPhotonsOpAngle_MC = "mc_deltaTheta[2] > 10. && mc_deltaTheta[3] > 10.";

// 4 bins (5 edges) for each kinematic variable, obtained with macros/SetBinning.cxx for Pb (Feb. 2021)
const Double_t kEdgesZ[5] = {0.5, 0.557422, 0.623973, 0.71513, 0.9};
const Double_t kEdgesQ2[5] = {1., 1.25432, 1.49863, 1.87423, 4.0};
const Double_t kEdgesNu[5] = {2.2, 3.23394, 3.57667, 3.8647, 4.2};
const Double_t kEdgesPt2[5] = {0., 0.0730263, 0.175764, 0.352527, 1.5};

// number of electrons, [target=D,C,Fe,Pb][bins], obtained with macros/GetElectronNumber.cxx (Feb. 2021)
const Double_t kNElec[4] = {50714486, 9810136, 21106557, 7639232};
const Double_t kNElecQ2[4][4] = {{12817179, 11879037, 12380023, 13638247},  // D
                                 {2366152, 2262591, 2425852, 2755541},      // C
                                 {5263698, 4955769, 5247019, 5640071},      // Fe
                                 {1934254, 1811294, 1896111, 1997573}};     // Pb
const Double_t kNElecNu[4][4] = {{18935442, 11470935, 9945049, 10363060},   // D
                                 {3357965, 2228577, 2014258, 2209336},      // C
                                 {7384144, 4798493, 4287820, 4636100},      // Fe
                                 {2630059, 1725088, 1559237, 1724848}};     // Pb

#endif
