#ifndef GLOBAL_H
#define GLOBAL_H

/*** GLOBAL VARIABLES ***/

TString gProDir  = getenv("PRODIR");
TString gWorkDir = getenv("WORKDIR");
TString gDataDir = gProDir + "/FilterNCombine/out";

TCut gCutDIS  = "Q2 > 1. && W > 2. && Yb < 0.85";
TCut gCutPi0  = "0.059 < pi0M && pi0M < 0.203"; // mean=0.131 & sigma=0.024
TCut gCutRegion = "Q2 > 1. && Q2 < 4. && Nu > 2.2 && Nu < 4.2 && wPt2 > 0 && wPt2 < 1.5 && wZ > 0.5 && wZ < 0.9";
TCut gCutSolid = "TargType == 2 && Yec > -1.4 && Yec < 1.4";
TCut gCutLiquid = "TargType == 1 && Yec > -1.4 && Yec < 1.4";
TCut gCutKaons = "0.48 > pippimM || 0.51 < pippimM";
TCut gCutPhotonsOpAngle = "deltaTheta[2] > 10 && deltaTheta[3] > 10";

TCut gCutDIS_GEN = "mc_Q2 > 1 && mc_W > 2 && mc_Yb < 0.85";
TCut gCutPi0_GEN = "0.1333 < mc_pi0M && mc_pi0M < 0.1367"; // mean=0.135 & sigma=5.7e-4

// 5 bins for each kinematic variable, obtained with macros/SetBinning.cxx for Pb (February 2021)
Double_t kEdgesZ[5] = {0.5, 0.557422, 0.623973, 0.71513, 0.9};
Double_t kEdgesQ2[5] = {1., 1.25432, 1.49863, 1.87423, 4.0};
Double_t kEdgesNu[5] = {2.2, 3.23394, 3.57667, 3.8647, 4.2};
Double_t kEdgesPt2[5] = {0., 0.0730263, 0.175764, 0.352527, 1.5};

#endif
