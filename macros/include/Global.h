#ifndef GLOBAL_H
#define GLOBAL_H

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

/*** GLOBAL VARIABLES ***/

TString gProDir = getenv("PRODIR");
TString gWorkDir = getenv("WORKDIR");

TString gTestDir = gWorkDir + "/out/TestPID/data";
TString gGetSimpleTupleDir = gWorkDir + "/out/GetSimpleTuple/data";
TString gTwoGammaFinderDir = gWorkDir + "/out/TwoGammaFinder/data";
TString gThreePionFinderDir = gWorkDir + "/out/ThreePionFinder/data";
TString gEventMixingDir = gWorkDir + "/out/EventMixing/data";

// electron cuts
TCut gCutDIS = "Q2 > 1. && W > 2. && Yb < 0.85";
TCut gCutSolid = "TargType == 2 && Yec > -1.4 && Yec < 1.4";
TCut gCutLiquid = "TargType == 1 && Yec > -1.4 && Yec < 1.4";
// photons id cut (requires "include/InputFunctions.cxx/SetAliases()")
TCut gCutPhotonsOpAngle = "gamma1_OpAngle > 12. && gamma2_OpAngle > 12.";
// omega reco cuts (gCutKaons requires "include/InputFunctions.cxx/SetAliases()")
TCut gCutPi0 = "0.079 < pi0M && pi0M < 0.193";          // 3sigma cut, mean=0.136 & sigma=0.019 (October 2021)
TCut gCutKaons = "pippimM < 0.484 || pippimM > 0.510";  // 1sigma cut, mean=0.247 & sigma=0.013 (October 2021)

// omega binning: 4 bins (5 edges) for each kinematic variable
// obtained with "omega_reco/Make_Binning.cxx" for Pb
// (last edit: October 2021)
const Double_t kEdgesQ2[5] = {1, 1.26, 1.52, 1.94, 4.0};
const Double_t kEdgesNu[5] = {2.2, 3.36, 3.67, 3.95, 4.2};
const Double_t kEdgesZ[5] = {0.5, 0.57, 0.64, 0.74, 0.9};
const Double_t kEdgesPt2[5] = {0, 0.07, 0.17, 0.34, 1.5};

// kinematical limits for omega (optional cut)
TCut gCutRegion = Form("Q2 > %.2f && Q2 < %.2f && Nu > %.2f && Nu < %.2f && wZ > %.2f && wZ < %.2f && wPt2 > %.2f && wPt2 < %.2f",
                       kEdgesQ2[0], kEdgesQ2[4], kEdgesNu[0], kEdgesNu[4], kEdgesZ[0], kEdgesZ[4], kEdgesPt2[0], kEdgesPt2[4]);

// eta binning: 5 bins (6 edges) for each kinematic variable
// obtained from Orlando's Ph.D. Thesis
const Double_t kEdgesQ2_Eta[6] = {1, 1.33, 1.66, 2.0, 2.5, 4.1};
const Double_t kEdgesNu_Eta[6] = {2.2, 2.86, 3.22, 3.58, 3.87, 4.25};
const Double_t kEdgesZ_Eta[6] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
const Double_t kEdgesPt2_Eta[6] = {0, 0.18, 0.36, 0.54, 0.72, 1.5};

// kinematical limits for eta
TCut gCutRegion_Eta =
    Form("Q2 > %.2f && Q2 < %.2f && Nu > %.2f && Nu < %.2f && nZ > %.2f && nZ < %.2f && nPt2 > %.2f && nPt2 < %.2f", kEdgesQ2_Eta[0],
         kEdgesQ2_Eta[5], kEdgesNu_Eta[0], kEdgesNu_Eta[5], kEdgesZ_Eta[0], kEdgesZ_Eta[5], kEdgesPt2_Eta[0], kEdgesPt2_Eta[5]);

// Radiative Corrections
TString gExternalsDir = getenv("EXTERNALS");
TString gHapradDir = getenv("HAPRAD_CPP");

#endif
