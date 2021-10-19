#ifndef RADIATIVECORRECTIONS_H
#define RADIATIVECORRECTIONS_H

#ifndef GLOBAL_H
#include "Global.h"
#endif

const Int_t NbinsQ2_Externals = 6;
const Int_t NbinsNu_Externals = 6;

const Double_t kEdgesQ2_Externals_Omega[NbinsQ2_Externals + 1] = {1, 1.26, 1.52, 1.94, 2.63, 3.31, 4.0};
const Double_t kEdgesNu_Externals_Omega[NbinsNu_Externals + 1] = {2.2, 2.59, 2.98, 3.36, 3.67, 3.95, 4.2};

const Double_t kEdgesQ2_Externals_Eta[NbinsQ2_Externals + 1] = {1, 1.33, 1.66, 2.0, 2.5, 3.3, 4.1};
const Double_t kEdgesNu_Externals_Eta[NbinsNu_Externals + 1] = {2.2, 2.53, 2.86, 3.22, 3.58, 3.87, 4.25};

#endif
