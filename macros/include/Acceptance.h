#ifndef ACCEPTANCE_H
#define ACCEPTANCE_H

#ifndef GLOBAL_H
#include "Global.h"
#endif

/*** GLOBAL VARIABLES ***/

TString gTestDir_Sim = gWorkDir + "/out/TestPID/omega-sim";

TString gGetSimpleTupleDir_EtaSim = gWorkDir + "/out/GetSimpleTuple/eta-sim";
TString gGetSimpleTupleDir_OmegaSim = gWorkDir + "/out/GetSimpleTuple/omega-sim";

TString gTwoGammaFinderDir_EtaSim = gWorkDir + "/out/TwoGammaFinder/eta-sim";

TString gThreePionFinderDir_OmegaSim = gWorkDir + "/out/ThreePionFinder/omega-sim";
TString gEventMixingDir_OmegaSim = gWorkDir + "/out/EventMixing/omega-sim";

TCut gCutDIS_MC = "mc_Q2 > 1. && mc_W > 2. && mc_Yb < 0.85";
TCut gCutParentID_Eta = "mc_ParentID[0] == 221 && mc_ParentID[1] == 221 && mc_Eta2GG == 1";
TCut gCutParentID_Omega =
    "mc_ParentID[0] == 223 && mc_ParentID[1] == 223 && mc_ParentID[2] == 223 && mc_ParentID[3] == 223 && mc_Omega2PPGG == 1";

#endif
