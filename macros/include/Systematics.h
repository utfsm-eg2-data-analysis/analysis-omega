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

// number of electrons for omega binning, [target=D,C,Fe,Pb][bins=3]
// obtained with macros/syst/Syst_GetElectronNumber.cxx
// (August 2021)
const Double_t kNElec_ThreeBins[4] = {53828344, 10974038, 21420539, 8145290};
const Double_t kNElecQ2_ThreeBins[4][3] = {{18171547, 17848467, 17808326},  // D
                                           {3667826, 3630755, 3675454},     // C
                                           {7357840, 7158209, 6904490},     // Fe
                                           {2851858, 2743294, 2550137}};    // Pb
const Double_t kNElecNu_ThreeBins[4][3] = {{25957524, 14400293, 13470527},  // D
                                           {5166455, 2935474, 2872109},     // C
                                           {9975063, 5809514, 5635962},     // Fe
                                           {3849153, 2164643, 2131494}};    // Pb

// number of electrons for omega binning, [target=D,C,Fe,Pb][bins=5]
// obtained with macros/syst/Syst_GetElectronNumber.cxx
// (August 2021)
const Double_t kNElec_FiveBins[4] = {53828344, 10974038, 21420539, 8145290};
const Double_t kNElecQ2_FiveBins[4][5] = {{10737193, 10593997, 10964735, 10859699, 10672720},  // D
                                          {2164757, 2142131, 2230738, 2220671, 2215741},       // C
                                          {4350942, 4280282, 4396411, 4295580, 4097324},       // Fe
                                          {1688087, 1656935, 1687670, 1616254, 1496344}};      // Pb
const Double_t kNElecNu_FiveBins[4][5] = {{18424444, 10775573, 8543477, 7699875, 8384973},     // D
                                          {3653717, 2169569, 1739954, 1603148, 1807650},       // C
                                          {7012955, 4253318, 3451595, 3167535, 3535130},       // Fe
                                          {2725820, 1608001, 1283065, 1183709, 1344694}};      // Pb

#endif
