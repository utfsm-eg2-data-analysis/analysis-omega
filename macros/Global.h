#ifndef GLOBAL_H
#define GLOBAL_H

/*** GLOBAL VARIABLES ***/

TString gProDir  = getenv("PRODIR");
TString gWorkDir = getenv("WORKDIR");
TString gDataDir = gProDir + "/FilterNCombine/out";

TCut gCutDIS  = "Q2 > 1. && W > 2. && Yb < 0.85";
TCut gCutPi0  = "0.059 < pi0M && pi0M < 0.203"; // mean=0.131 & sigma=0.024
TCut gCutRegion = "Q2 > 1. && Q2 < 4. && Nu > 2.2 && Nu < 4.2 && wPt2 > 0 && wPt2 < 1.5 && wZ > 0.5 && wZ < 0.9";
TCut gCutSolid = "TargType == 2 && Yec > -1.4 && Yec < 1.4";;
TCut gCutLiquid = "TargType == 1 && Yec > -1.4 && Yec < 1.4";;
TCut gCutKaons = "0.48 > pippimM || 0.51 < pippimM";

TCut gCutDIS_GEN = "mc_Q2 > 1 && mc_W > 2 && mc_Yb < 0.85";
TCut gCutPi0_GEN = "0.1333 < mc_pi0M && mc_pi0M < 0.1367"; // mean=0.135 & sigma=5.7e-4
TCut gCutGEN = gCutDIS_GEN && gCutPi0_GEN;

// 5 bins for each kinematic variable, obtained with SetBinning.cxx for Pb (November 2020)
Double_t kEdgesQ2[6]  = {1.000, 1.189, 1.378, 1.614, 2.006, 4.000};
Double_t kEdgesNu[6]  = {2.200, 3.208, 3.527, 3.762, 3.976, 4.200};
Double_t kEdgesZ[6]   = {0.500, 0.547, 0.601, 0.664, 0.759, 1.000};
Double_t kEdgesPt2[6] = {0.000, 0.049, 0.115, 0.208, 0.367, 1.500};

#endif
