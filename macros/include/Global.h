#ifndef GLOBAL_H
#define GLOBAL_H

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "TCanvas.h"
#include "TChain.h"
#include "TCut.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitResult.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TLine.h"
#include "TObjString.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TStyle.h"

#include "RooAddPdf.h"
#include "RooChebychev.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooRealVar.h"

/*** GLOBAL VARIABLES ***/

TString gProDir = getenv("PRODIR");
TString gWorkDir = getenv("WORKDIR");
TString gDataDir = gWorkDir + "/out/ThreePionFinder/data";
TString gDataDir_Eta = gWorkDir + "/out/TwoGammaFinder/data";

TCut gCutDIS = "Q2 > 1. && W > 2. && Yb < 0.85";
// TCut gCutPi0 = "0.059 < pi0M && pi0M < 0.203";  // mean=0.131 & sigma=0.024, prev
TCut gCutPi0 = "0.081 < pi0M && pi0M < 0.189";  // mean=0.135 & sigma=0.018 (March. 2021 - Thesis Submission)
TCut gCutRegion = "Q2 > 1. && Q2 < 4. && Nu > 2.2 && Nu < 4.2 && wPt2 > 0 && wPt2 < 1.5 && wZ > 0.5 && wZ < 0.9";
TCut gCutSolid = "TargType == 2 && Yec > -1.4 && Yec < 1.4";
TCut gCutLiquid = "TargType == 1 && Yec > -1.4 && Yec < 1.4";
TCut gCutKaons = "pippimM < 0.483 || pippimM > 0.511";
TCut gCutPhotonsOpAngle = "deltaTheta[2] > 12. && deltaTheta[3] > 12.";
TCut gCutRegion_Eta = "Q2 > 1. && Q2 < 4.1 && Nu > 2.2 && Nu < 4.25 && eZ > 0.5 && eZ < 1.0 && ePt2 > 0 && ePt2 < 1.5";
TCut gCutPhotonsOpAngle_Eta = "deltaTheta[0] > 12. && deltaTheta[1] > 12.";

TCut gCutDIS_MC = "mc_Q2 > 1 && mc_W > 2 && mc_Yb < 0.85";
TCut gCutPi0_MC = "0.134 < mc_pi0M && mc_pi0M < 0.136";  // mean=0.135 & sigma=1e-3
TCut gCutRegion_MC = "mc_Q2 > 1. && mc_Q2 < 4. && mc_Nu > 2.2 && mc_Nu < 4.2 && mc_wPt2 > 0 && mc_wPt2 < 1.5 && mc_wZ > 0.5 && mc_wZ < 0.9";
TCut gCutKaons_MC = "0.48 > mc_pippimM || 0.51 < mc_pippimM";
TCut gCutPhotonsOpAngle_MC = "mc_deltaTheta[2] > 12. && mc_deltaTheta[3] > 12.";

// Radiative Corrections
TString gExternalsDir = getenv("EXTERNALS");
TString gHapradDir = getenv("HAPRAD_CPP");

// omega binning: 4 bins (5 edges) for each kinematic variable
// obtained with macros/omega/SetBinning.cxx for Pb
// (March. 2021 - Thesis Submission)
const Double_t kEdgesQ2[5] = {1, 1.25, 1.51, 1.92, 4.0};
const Double_t kEdgesNu[5] = {2.2, 3.35, 3.68, 3.94, 4.2};
const Double_t kEdgesZ[5] = {0.5, 0.57, 0.64, 0.74, 0.9};
const Double_t kEdgesPt2[5] = {0, 0.07, 0.17, 0.34, 1.5};

// eta binning: 5 bins (6 edges) for each kinematic variable
// obtained from Orlando's Ph.D. Thesis
// (May 2021)
const Double_t kEdgesQ2_Eta[6] = {1, 1.33, 1.66, 2.0, 2.5, 4.1};
const Double_t kEdgesNu_Eta[6] = {2.2, 2.86, 3.22, 3.58, 3.87, 4.25};
const Double_t kEdgesZ_Eta[6] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
const Double_t kEdgesPt2_Eta[6] = {0, 0.18, 0.36, 0.54, 0.72, 1.5};

// pi0 binning: 7 bins (8 edges) for Pt2, just to observe something
// (June 2021)
const Double_t kEdgesPt2_Pi0[8] = {0, 0.1, 0.25, 0.4, 0.55, 0.75, 1.125, 1.5};

// number of electrons for omega binning, [target=D,C,Fe,Pb][bins]
// obtained with macros/omega/GetElectronNumber.cxx
// (March. 2021 - Thesis Submission)
const Double_t kNElec[4] = {54997138, 11287494, 22137224, 8234343};
const Double_t kNElecQ2[4][4] = {{14020161, 13664015, 13935368, 13377318},  // D
                                 {2840221, 2791540, 2862981, 2792575},      // C
                                 {5733158, 5567596, 5613229, 5222991},      // Fe
                                 {2175896, 2102659, 2081392, 1874285}};     // Pb
const Double_t kNElecNu[4][4] = {{23619935, 11921114, 9491474, 8309209},    // D
                                 {4715517, 2429403, 1977116, 1798961},      // C
                                 {9133502, 4820617, 3927577, 3534347},      // Fe
                                 {3452195, 1761730, 1433085, 1314436}};     // Pb

// number of electrons corrected with EXTERNALS and Coulomb Corr. for omega binning, [target=D,C,Fe,Pb][bins]
// obtained with macros/rad-corr/RadCorr_GetElectronNumber.cxx
// (July 2021)
const Double_t kNElec_rc[4] = {4.62665e+07, 9.50037e+06, 1.87942e+07, 7.10454e+06};
const Double_t kNElecQ2_rc[4][4] = {{1.1191e+07, 1.13861e+07, 1.18893e+07, 1.18001e+07},    // D
                                    {2.27233e+06, 2.32539e+06, 2.43716e+06, 2.46548e+06},   // C
                                    {4.62225e+06, 4.67768e+06, 4.82573e+06, 4.66854e+06},   // Fe
                                    {1.78004e+06, 1.79296e+06, 1.82007e+06, 1.71147e+06}};  // Pb
const Double_t kNElecNu_rc[4][4] = {{2.17124e+07, 1.03736e+07, 7.8336e+06, 6.34684e+06},    // D
                                    {4.35037e+06, 2.12152e+06, 1.63971e+06, 1.38878e+06},   // C
                                    {8.49201e+06, 4.24512e+06, 3.29111e+06, 2.76596e+06},   // Fe
                                    {3.25234e+06, 1.57596e+06, 1.2237e+06, 1.05253e+06}};   // Pb

// number of electrons, [target=D,C,Fe,Pb][bins]
// obtained with macros/GetElectronNumberMC.cxx
// (April. 2021 - Thesis Submission)
const Double_t kNElec_MC[4] = {35923569, 16322703, 13388214, 12294220};
const Double_t kNElecQ2_MC[4][4] = {{14360323, 8596802, 6971041, 5937358},  // D
                                    {6616501, 3942508, 3163780, 2580050},   // C
                                    {5434849, 3230935, 2592066, 2113812},   // Fe
                                    {5038618, 2974750, 2374392, 1893253}};  // Pb
const Double_t kNElecNu_MC[4][4] = {{18816907, 6388387, 4874857, 4741118},  // D
                                    {8468100, 3090144, 2292737, 2038300},   // C
                                    {6929631, 2517043, 1891085, 1690547},   // Fe
                                    {6357858, 2353191, 1740728, 1521986}};  // Pb

// number of electrons, [target=D,C,Fe,Pb][bins]
// obtained with macros/GetElectronNumberSim.cxx
// (April. 2021 - Thesis Submission)
const Double_t kNElec_Sim[4] = {11778035, 5365105, 4348846, 3997881};
const Double_t kNElecQ2_Sim[4][4] = {{3065879, 3038123, 3003904, 2670124},  // D
                                     {1425445, 1396207, 1365689, 1177754},  // C
                                     {1161321, 1132447, 1105500, 949563},   // Fe
                                     {1083942, 1046790, 1013869, 853272}};  // Pb
const Double_t kNElecNu_Sim[4][4] = {{5426985, 2538648, 1923278, 1593688},  // D
                                     {2434310, 1214708, 903269, 695020},    // C
                                     {1960218, 980634, 736896, 573225},     // Fe
                                     {1800408, 912755, 679653, 517402}};    // Pb

// number of electrons, [target=D,C,Fe,Pb][bins]
// obtained with macros/GetElectronNumber.cxx
// (May 2021)
const Double_t kNElec_Eta[5] = {54997138, 11287494, 22137224, 8234343};
const Double_t kNElecQ2_Eta[4][5] = {{18629454, 15152710, 9692413, 7271082, 4251469},    // D
                                     {3779910, 3101503, 1997734, 1515942, 892399},       // C
                                     {7619057, 6149401, 3881742, 2854490, 1632527},      // Fe
                                     {2888344, 2311200, 1429370, 1030051, 575377}};      // Pb
const Double_t kNElecNu_Eta[4][5] = {{8598451, 10632029, 12616251, 10699311, 12146209},  // D
                                     {1698627, 2132990, 2556955, 2207906, 2623230},      // C
                                     {3248588, 4146417, 5048012, 4399030, 5161421},      // Fe
                                     {1247187, 1560136, 1858247, 1599572, 1918615}};     // Pb

#endif
