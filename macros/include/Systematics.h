#ifndef SYSTEMATICS_H
#define SYSTEMATICS_H

#ifndef GLOBAL_H
#include "Global.h"
#endif

/*** USEFUL VARIABLES FOR THE ESTIMATION OF SYSTEMATIC UNCERTAINTIES ***/

// 3 bins (4 edges) for each kinematic variable
// obtained with macros/omega/SetBinning.cxx for Pb
// (July 2021)
const Double_t kEdgesQ2_ThreeBins[4] = {1, 1.33, 1.75, 4.0};
const Double_t kEdgesNu_ThreeBins[4] = {2.2, 3.41, 3.80, 4.2};
const Double_t kEdgesZ_ThreeBins[4] = {0.5, 0.59, 0.70, 0.9};
const Double_t kEdgesPt2_ThreeBins[4] = {0, 0.11, 0.28, 1.5};

const Double_t kEdgesQ2_FiveBins[6] = {1, 1.20, 1.39, 1.64, 2.03, 4.0};
const Double_t kEdgesNu_FiveBins[6] = {2.2, 3.19, 3.50, 3.73, 3.94, 4.2};
const Double_t kEdgesZ_FiveBins[6] = {0.5, 0.56, 0.61, 0.68, 0.76, 0.9};
const Double_t kEdgesPt2_FiveBins[6] = {0, 0.06, 0.13, 0.24, 0.41, 1.5};

const Double_t kEdgesQ2_FourBinsEW[5] = {1, 1.75, 2.50, 3.25, 4.0};
const Double_t kEdgesNu_FourBinsEW[5] = {2.2, 2.7, 3.2, 3.7, 4.2};
const Double_t kEdgesZ_FourBinsEW[5] = {0.5, 0.6, 0.7, 0.8, 0.9};
const Double_t kEdgesPt2_FourBinsEW[5] = {0, 0.375, 0.75, 1.125, 1.5};

#endif
