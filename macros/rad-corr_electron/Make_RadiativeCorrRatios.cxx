#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef INPUTFUNCTIONS_CXX
#include "InputFunctions.cxx"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

#ifndef RADIATIVECORRECTIONS_H
#include "RadiativeCorrections.h"
#endif

#include "EtaElectronNumbers.hxx"
#include "EtaMCElectronNumbers.hxx"
#include "EtaSimElectronNumbers.hxx"

#include "OmegaElectronNumbers.hxx"
#include "OmegaMCElectronNumbers.hxx"
#include "OmegaSimElectronNumbers.hxx"

const Int_t Ntargets = 4;
const Int_t Nkinvars = 2;  // only Q2 and Nu

void Make_RadiativeCorrRatios(TString PartOption = "eta", TString StoreOption = "") {
  // Plot effect of electron radiative corrections in final MR - with proper MR binning

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** INPUT ***/

  TChain *dataChain[Ntargets];
  dataChain[0] = GetElectronsChain("D");
  dataChain[1] = GetElectronsChain("C");
  dataChain[2] = GetElectronsChain("Fe");
  dataChain[3] = GetElectronsChain("Pb");

  TChain *simChain[Ntargets];
  simChain[0] = GetElectronsChain("D", "sim", PartOption);
  simChain[1] = GetElectronsChain("C", "sim", PartOption);
  simChain[2] = GetElectronsChain("Fe", "sim", PartOption);
  simChain[3] = GetElectronsChain("Pb", "sim", PartOption);

  // define vertex cuts for data
  TCut CutVertex[Ntargets];
  CutVertex[0] = "TargType == 1 && vyec > -1.4 && vyec < 1.4";  // GST format
  CutVertex[1] = "TargType == 2 && vyec > -1.4 && vyec < 1.4";  // GST format
  CutVertex[2] = "TargType == 2 && vyec > -1.4 && vyec < 1.4";  // GST format
  CutVertex[3] = "TargType == 2 && vyec > -1.4 && vyec < 1.4";  // GST format

  // related to targets
  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  // related to kinvars
  TString kinvarOption[Nkinvars] = {"Q2", "Nu"};
  TString kinvarTitle[Nkinvars] = {"Q^{2} [GeV^{2}]", "#nu [GeV]"};

  // related to particle option - now, get edges in EXTERNALS binning
  Double_t EdgesQ2[NbinsQ2_Externals + 1];
  Double_t EdgesNu[NbinsNu_Externals + 1];
  if (PartOption == "omega") {
    for (Int_t q = 0; q < NbinsQ2_Externals + 1; q++) {
      EdgesQ2[q] = kEdgesQ2_Externals_Omega[q];
    }
    for (Int_t n = 0; n < NbinsNu_Externals + 1; n++) {
      EdgesNu[n] = kEdgesNu_Externals_Omega[n];
    }
  } else {  // "eta"
    for (Int_t q = 0; q < NbinsQ2_Externals + 1; q++) {
      EdgesQ2[q] = kEdgesQ2_Externals_Eta[q];
    }
    for (Int_t n = 0; n < NbinsNu_Externals + 1; n++) {
      EdgesNu[n] = kEdgesNu_Externals_Eta[n];
    }
  }

  // related to particle option - number of MR bins
  Int_t Nbins_MR;
  if (PartOption == "omega") {
    Nbins_MR = 4;
  } else {  // "eta"
    Nbins_MR = 5;
  }

  // related to particle option - get edges in MR binning
  Double_t EdgesKinvar[Nkinvars][Nbins_MR + 1];
  if (PartOption == "omega") {
    for (Int_t i = 0; i < Nbins_MR + 1; i++) {
      EdgesKinvar[0][i] = kEdgesQ2[i];
      EdgesKinvar[1][i] = kEdgesNu[i];
    }
  } else {  // "eta"
    for (Int_t i = 0; i < Nbins_MR + 1; i++) {
      EdgesKinvar[0][i] = kEdgesQ2_Eta[i];
      EdgesKinvar[1][i] = kEdgesNu_Eta[i];
    }
  }

  /*** PART 1: get acc. corr. number of electrons in EXTERNALS binning ***/

  // define data, mc, and sim. rec. histogram
  TH2D *Hist_Data[Ntargets][NbinsQ2_Externals][NbinsNu_Externals];
  TH2D *Hist_MC[Ntargets][NbinsQ2_Externals][NbinsNu_Externals];
  TH2D *Hist_Sim[Ntargets][NbinsQ2_Externals][NbinsNu_Externals];

  // define acceptance and corr hists
  TH2D *Hist_Acceptance[Ntargets][NbinsQ2_Externals][NbinsNu_Externals];
  TH2D *Hist_AccCorr[Ntargets][NbinsQ2_Externals][NbinsNu_Externals];

  // define same hist properties for every hist
  Int_t HistBins = 1;
  TString HistProperties = Form("(%i, %.2f, %.2f, %i, %.2f, %.2f)", HistBins, EdgesNu[0], EdgesNu[NbinsNu_Externals], HistBins, EdgesQ2[0],
                                EdgesQ2[NbinsQ2_Externals]);

  TCut CutBin;
  TCut CutBin_MC;

  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
      for (Int_t n = 0; n < NbinsNu_Externals; n++) {
        // update cut
        CutBin = Form("Q2 > %.2f && Q2 < %.2f && Nu > %.2f && Nu < %.2f", EdgesQ2[q], EdgesQ2[q + 1], EdgesNu[n], EdgesNu[n + 1]);
        CutBin_MC =
            Form("mc_Q2 > %.2f && mc_Q2 < %.2f && mc_Nu > %.2f && mc_Nu < %.2f", EdgesQ2[q], EdgesQ2[q + 1], EdgesNu[n], EdgesNu[n + 1]);

        // make data histogram
        dataChain[t]->Draw(Form("Q2:Nu>>data_%i_%i_", q, n) + targetString[t] + HistProperties, gCutDIS && CutVertex[t] && CutBin, "goff");
        Hist_Data[t][q][n] = (TH2D *)gROOT->FindObject(Form("data_%i_%i_", q, n) + targetString[t]);

        // make mc histogram
        simChain[t]->Draw(Form("mc_Q2:mc_Nu>>mc_%i_%i_", q, n) + targetString[t] + HistProperties, gCutDIS_MC && CutBin_MC, "goff");
        Hist_MC[t][q][n] = (TH2D *)gROOT->FindObject(Form("mc_%i_%i_", q, n) + targetString[t]);

        // make sim. rec. histogram
        simChain[t]->Draw(Form("Q2:Nu>>sim_%i_%i_", q, n) + targetString[t] + HistProperties, gCutDIS && CutBin, "goff");
        Hist_Sim[t][q][n] = (TH2D *)gROOT->FindObject(Form("sim_%i_%i_", q, n) + targetString[t]);

        // make acceptance
        Hist_Acceptance[t][q][n] = new TH2D(Form("acc_%i_%i_", q, n) + targetString[t], "", HistBins, EdgesNu[0],
                                            EdgesNu[NbinsNu_Externals], HistBins, EdgesQ2[0], EdgesQ2[NbinsQ2_Externals]);
        Hist_Acceptance[t][q][n]->Divide(Hist_Sim[t][q][n], Hist_MC[t][q][n], 1, 1, "B");

        // correct data
        Hist_AccCorr[t][q][n] = new TH2D(Form("acc_corr_%i_%i_", q, n) + targetString[t], "", HistBins, EdgesNu[0],
                                         EdgesNu[NbinsNu_Externals], HistBins, EdgesQ2[0], EdgesQ2[NbinsQ2_Externals]);
        Hist_AccCorr[t][q][n]->Divide(Hist_Data[t][q][n], Hist_Acceptance[t][q][n], 1, 1);
      }
    }
  }

  std::cout << "PART 1 FINISHED!" << std::endl;

  /*** PART 2: apply rad. corr. factors to acc. corr. electron numbers in EXTERNALS binning ***/

  // declare textfile with rad. corr. factors
  std::ifstream ExternalsFiles[Ntargets];

  // declare some auxiliary variables to read the file
  std::string auxLine;
  TString auxString[13];  // number of columns in the .out files
  Int_t countLine = 0;
  Int_t binInNu = 0;
  Int_t binInQ2 = 0;

  Double_t RadCorrFactor[Ntargets][NbinsQ2_Externals][NbinsNu_Externals];

  TH2D *Hist_RadCorr[Ntargets][NbinsQ2_Externals][NbinsNu_Externals];

  Double_t NElec_RadCorr[Ntargets][NbinsQ2_Externals][NbinsNu_Externals];
  Double_t NElec_RadCorr_Error[Ntargets][NbinsQ2_Externals][NbinsNu_Externals];

  for (Int_t t = 0; t < Ntargets; t++) {
    // open textfile
    ExternalsFiles[t].open(gProDir + "/gfx/rad-corr_electron/clas_" + PartOption + "_" + targetString[t] + ".out", std::ios::in);
    // read each line
    while (getline(ExternalsFiles[t], auxLine)) {
      // given the first line represents the name of the columns
      if (countLine > 0) {
        for (Int_t i = 0; i < 13; i++) {
          auxString[i] = ((TObjString *)(((TString)auxLine).Tokenize("   ")->At(i)))->String();
        }
        binInNu = (countLine - 1) / NbinsQ2_Externals;
        binInQ2 = (countLine - 1) - NbinsQ2_Externals * binInNu;
        // get radiative correction factors (Column 12: C_cor, Column 5: Sig_Born, Column 8: Sig_Rad)
        if (auxString[11] != "NaN") {
          RadCorrFactor[t][binInQ2][binInNu] = auxString[12].Atof() * auxString[5].Atof() / auxString[8].Atof();
        } else {
          RadCorrFactor[t][binInQ2][binInNu] = 1;
        }
        // apply rad. corr. factors to acc. corr. number of electrons
        Hist_RadCorr[t][binInQ2][binInNu] =
            (TH2D *)Hist_AccCorr[t][binInQ2][binInNu]->Clone(Form("rad_corr_%i_%i_", binInQ2, binInNu) + targetString[t]);
        Hist_RadCorr[t][binInQ2][binInNu]->Scale(RadCorrFactor[t][binInQ2][binInNu]);
        // get rad.corr. electron numbers and their error
        NElec_RadCorr[t][binInQ2][binInNu] =
            Hist_RadCorr[t][binInQ2][binInNu]->IntegralAndError(1, HistBins, 1, HistBins, NElec_RadCorr_Error[t][binInQ2][binInNu]);
      }
      countLine++;
    }
    // close input file
    ExternalsFiles[t].close();
    // reset auxiliary variables
    countLine = 0;
    binInNu = 0;
    binInQ2 = 0;
  }

  std::cout << "PART 2 FINISHED!" << std::endl;

  /*** PART 3: sum acc. corr. electron numbers into MR binning - SENSITIVE & TEDIOUS CALCULATIONS ***/

  Double_t NElec_RadCorr_MR[Ntargets][Nkinvars][Nbins_MR];
  Double_t NElec_RadCorr_MR_Error[Ntargets][Nkinvars][Nbins_MR];  // PENDING!!

  if (PartOption == "omega") {
    for (Int_t t = 0; t < Ntargets; t++) {
      // Q2: bin 0
      NElec_RadCorr_MR[t][0][0] = 0;
      for (Int_t n = 0; n < NbinsNu_Externals; n++) {
        NElec_RadCorr_MR[t][0][0] += NElec_RadCorr[t][0][n];
      }
      // Q2: bin 1
      NElec_RadCorr_MR[t][0][1] = 0;
      for (Int_t n = 0; n < NbinsNu_Externals; n++) {
        NElec_RadCorr_MR[t][0][1] += NElec_RadCorr[t][1][n];
      }
      // Q2: bin 2
      NElec_RadCorr_MR[t][0][2] = 0;
      for (Int_t n = 0; n < NbinsNu_Externals; n++) {
        NElec_RadCorr_MR[t][0][2] += NElec_RadCorr[t][2][n];
      }
      // Q2: bin 3
      NElec_RadCorr_MR[t][0][3] = 0;
      for (Int_t n = 0; n < NbinsNu_Externals; n++) {
        NElec_RadCorr_MR[t][0][3] += NElec_RadCorr[t][3][n];
        NElec_RadCorr_MR[t][0][3] += NElec_RadCorr[t][4][n];
        NElec_RadCorr_MR[t][0][3] += NElec_RadCorr[t][5][n];
      }
      // Nu: bin 0
      NElec_RadCorr_MR[t][1][0] = 0;
      for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
        NElec_RadCorr_MR[t][1][0] += NElec_RadCorr[t][q][0];
        NElec_RadCorr_MR[t][1][0] += NElec_RadCorr[t][q][1];
        NElec_RadCorr_MR[t][1][0] += NElec_RadCorr[t][q][2];
      }
      // Nu: bin 1
      NElec_RadCorr_MR[t][1][1] = 0;
      for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
        NElec_RadCorr_MR[t][1][1] += NElec_RadCorr[t][q][3];
      }
      // Nu: bin 2
      NElec_RadCorr_MR[t][1][2] = 0;
      for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
        NElec_RadCorr_MR[t][1][2] += NElec_RadCorr[t][q][4];
      }
      // Nu: bin 3
      NElec_RadCorr_MR[t][1][3] = 0;
      for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
        NElec_RadCorr_MR[t][1][3] += NElec_RadCorr[t][q][5];
      }
    }
  } else {  // PartOption == "eta"
    for (Int_t t = 0; t < Ntargets; t++) {
      // Q2: bin 0
      NElec_RadCorr_MR[t][0][0] = 0;
      for (Int_t n = 0; n < NbinsNu_Externals; n++) {
        NElec_RadCorr_MR[t][0][0] += NElec_RadCorr[t][0][n];
      }
      // Q2: bin 1
      NElec_RadCorr_MR[t][0][1] = 0;
      for (Int_t n = 0; n < NbinsNu_Externals; n++) {
        NElec_RadCorr_MR[t][0][1] += NElec_RadCorr[t][1][n];
      }
      // Q2: bin 2
      NElec_RadCorr_MR[t][0][2] = 0;
      for (Int_t n = 0; n < NbinsNu_Externals; n++) {
        NElec_RadCorr_MR[t][0][2] += NElec_RadCorr[t][2][n];
      }
      // Q2: bin 3
      NElec_RadCorr_MR[t][0][3] = 0;
      for (Int_t n = 0; n < NbinsNu_Externals; n++) {
        NElec_RadCorr_MR[t][0][3] += NElec_RadCorr[t][3][n];
      }
      // Q2: bin 4
      NElec_RadCorr_MR[t][0][4] = 0;
      for (Int_t n = 0; n < NbinsNu_Externals; n++) {
        NElec_RadCorr_MR[t][0][4] += NElec_RadCorr[t][4][n];
        NElec_RadCorr_MR[t][0][4] += NElec_RadCorr[t][5][n];
      }
      // Nu: bin 0
      NElec_RadCorr_MR[t][1][0] = 0;
      for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
        NElec_RadCorr_MR[t][1][0] += NElec_RadCorr[t][q][0];
        NElec_RadCorr_MR[t][1][0] += NElec_RadCorr[t][q][1];
      }
      // Nu: bin 1
      NElec_RadCorr_MR[t][1][1] = 0;
      for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
        NElec_RadCorr_MR[t][1][1] += NElec_RadCorr[t][q][2];
      }
      // Nu: bin 2
      NElec_RadCorr_MR[t][1][2] = 0;
      for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
        NElec_RadCorr_MR[t][1][2] += NElec_RadCorr[t][q][3];
      }
      // Nu: bin 3
      NElec_RadCorr_MR[t][1][3] = 0;
      for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
        NElec_RadCorr_MR[t][1][3] += NElec_RadCorr[t][q][4];
      }
      // Nu: bin 4
      NElec_RadCorr_MR[t][1][4] = 0;
      for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
        NElec_RadCorr_MR[t][1][4] += NElec_RadCorr[t][q][5];
      }
    }
  }

  TH1D *HistForMR_RadCorr[Ntargets][Nkinvars];

  // fill histograms
  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {
      // define histograms
      HistForMR_RadCorr[t][k] =
          new TH1D("ForMR_rad_corr_" + targetString[t] + "_" + kinvarOption[k], "", Nbins_MR, EdgesKinvar[k][0], EdgesKinvar[k][Nbins_MR]);
      // fill histogram
      for (Int_t i = 0; i < Nbins_MR; i++) {
        HistForMR_RadCorr[t][k]->SetBinContent(i + 1, NElec_RadCorr_MR[t][k][i]);
      }
    }
  }

  std::cout << "PART 3 FINISHED!" << std::endl;

  /*** PART 4: get acc. corr. number of electrons in MR binning ***/

  // define calculated number of electrons in MR binning
  Double_t NElec_Data_MR[Ntargets][Nkinvars][Nbins_MR];
  Double_t NElec_MC_MR[Ntargets][Nkinvars][Nbins_MR];
  Double_t NElec_Sim_MR[Ntargets][Nkinvars][Nbins_MR];

  // related to particle option
  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t i = 0; i < Nbins_MR; i++) {
      if (PartOption == "omega") {
        NElec_Data_MR[t][0][i] = kNElecQ2_Omega[t][i];
        NElec_Data_MR[t][1][i] = kNElecNu_Omega[t][i];
        NElec_MC_MR[t][0][i] = kNElecQ2_OmegaMC[t][i];
        NElec_MC_MR[t][1][i] = kNElecNu_OmegaMC[t][i];
        NElec_Sim_MR[t][0][i] = kNElecQ2_OmegaSim[t][i];
        NElec_Sim_MR[t][1][i] = kNElecNu_OmegaSim[t][i];
      } else {  // if "eta"
        NElec_Data_MR[t][0][i] = kNElecQ2_Eta[t][i];
        NElec_Data_MR[t][1][i] = kNElecNu_Eta[t][i];
        NElec_MC_MR[t][0][i] = kNElecQ2_EtaMC[t][i];
        NElec_MC_MR[t][1][i] = kNElecNu_EtaMC[t][i];
        NElec_Sim_MR[t][0][i] = kNElecQ2_EtaSim[t][i];
        NElec_Sim_MR[t][1][i] = kNElecNu_EtaSim[t][i];
      }
    }
  }

  // define histograms
  TH1D *HistForMR_Data[Ntargets][Nkinvars];
  TH1D *HistForMR_MC[Ntargets][Nkinvars];
  TH1D *HistForMR_Sim[Ntargets][Nkinvars];
  TH1D *HistForMR_Acceptance[Ntargets][Nkinvars];
  TH1D *HistForMR_AccCorr[Ntargets][Nkinvars];

  // fill those numbers into histograms
  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {

      // define histograms
      HistForMR_Data[t][k] =
          new TH1D("ForMR_data_" + targetString[t] + "_" + kinvarOption[k], "", Nbins_MR, EdgesKinvar[k][0], EdgesKinvar[k][Nbins_MR]);
      HistForMR_MC[t][k] =
          new TH1D("ForMR_mc_" + targetString[t] + "_" + kinvarOption[k], "", Nbins_MR, EdgesKinvar[k][0], EdgesKinvar[k][Nbins_MR]);
      HistForMR_Sim[t][k] =
          new TH1D("ForMR_sim_" + targetString[t] + "_" + kinvarOption[k], "", Nbins_MR, EdgesKinvar[k][0], EdgesKinvar[k][Nbins_MR]);

      // fill each bin
      for (Int_t i = 0; i < Nbins_MR; i++) {
        // data
        HistForMR_Data[t][k]->SetBinContent(i + 1, NElec_Data_MR[t][k][i]);
        HistForMR_Data[t][k]->SetBinError(i + 1, TMath::Sqrt(NElec_Data_MR[t][k][i]));
        // MC
        HistForMR_MC[t][k]->SetBinContent(i + 1, NElec_MC_MR[t][k][i]);
        HistForMR_MC[t][k]->SetBinError(i + 1, TMath::Sqrt(NElec_MC_MR[t][k][i]));
        // sim
        HistForMR_Sim[t][k]->SetBinContent(i + 1, NElec_Sim_MR[t][k][i]);
        HistForMR_Sim[t][k]->SetBinError(i + 1, TMath::Sqrt(NElec_Sim_MR[t][k][i]));
      }

      // make acceptance
      HistForMR_Acceptance[t][k] =
          new TH1D("ForMR_acc_" + targetString[t] + "_" + kinvarOption[k], "", Nbins_MR, EdgesKinvar[k][0], EdgesKinvar[k][Nbins_MR]);
      HistForMR_Acceptance[t][k]->Divide(HistForMR_Sim[t][k], HistForMR_MC[t][k], 1, 1, "B");

      // correct data
      HistForMR_AccCorr[t][k] =
          new TH1D("ForMR_acc_corr_" + targetString[t] + "_" + kinvarOption[k], "", Nbins_MR, EdgesKinvar[k][0], EdgesKinvar[k][Nbins_MR]);
      HistForMR_AccCorr[t][k]->Divide(HistForMR_Data[t][k], HistForMR_Acceptance[t][k], 1, 1);
    }
  }

  std::cout << "PART 4 FINISHED!" << std::endl;

  /*** PART 5: obtain solid-to-liquid ratios for "acc-only" and "rad+acc", then obtain final ratio! ***/

  TH1D *SolToLiq_AccCorr[Ntargets][Nkinvars];
  TH1D *SolToLiq_RadCorr[Ntargets][Nkinvars];

  TH1D *EffectOfRadCorr[Ntargets][Nkinvars];

  Double_t Ratio_EffectOfRadCorr[Ntargets][Nkinvars][Nbins_MR];

  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {
      // calculate solid-to-liquid ratio for acc-only number of electrons
      SolToLiq_AccCorr[t][k] =
          new TH1D("sol_to_liq_acc_" + targetString[t] + "_" + kinvarOption[k], "", Nbins_MR, EdgesKinvar[k][0], EdgesKinvar[k][Nbins_MR]);
      SolToLiq_AccCorr[t][k]->Divide(HistForMR_AccCorr[t][k], HistForMR_AccCorr[0][k], 1, 1);
      // calculate solid-to-liquid ratio for rad+acc number of electrons
      SolToLiq_RadCorr[t][k] =
          new TH1D("sol_to_liq_rad_" + targetString[t] + "_" + kinvarOption[k], "", Nbins_MR, EdgesKinvar[k][0], EdgesKinvar[k][Nbins_MR]);
      SolToLiq_RadCorr[t][k]->Divide(HistForMR_RadCorr[t][k], HistForMR_RadCorr[0][k], 1, 1);
      // calculate final ratio
      EffectOfRadCorr[t][k] =
          new TH1D("effect_" + targetString[t] + "_" + kinvarOption[k], "", Nbins_MR, EdgesKinvar[k][0], EdgesKinvar[k][Nbins_MR]);
      EffectOfRadCorr[t][k]->Divide(SolToLiq_RadCorr[t][k], SolToLiq_AccCorr[t][k], 1, 1);
      // fill double variable for translating into graphs
      for (Int_t i = 0; i < Nbins_MR; i++) {
        Ratio_EffectOfRadCorr[t][k][i] = EffectOfRadCorr[t][k]->GetBinContent(i + 1);
      }
    }
  }

  std::cout << "PART 5 FINISHED!" << std::endl;

  /*** GRAPHS ***/

  // prepare y axis
  Double_t MaxRange[Nkinvars] = {0, 0};
  Double_t MinRange[Nkinvars] = {999999, 999999};
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      // get the maximum of the hist
      if (EffectOfRadCorr[k][t]->GetMaximum() > MaxRange[k]) {
        MaxRange[k] = EffectOfRadCorr[k][t]->GetMaximum();
      }
      // get the minimum of the hist
      if (EffectOfRadCorr[k][t]->GetMinimum() < MinRange[k]) {
        MinRange[k] = EffectOfRadCorr[k][t]->GetMinimum();
      }
    }
  }

  // fill arrays
  Double_t Empty[Nbins_MR];
  for (Int_t i = 0; i < Nbins_MR; i++) {
    Empty[i] = 0;
  }

  // geometrical center
  Double_t BinGeoCenter[Nkinvars][Nbins_MR];
  Double_t BinGeoWidth[Nkinvars][Nbins_MR];
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins_MR; i++) {
      BinGeoCenter[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      BinGeoWidth[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / TMath::Sqrt(12.);
    }
  }

  // define graphs
  TGraphErrors *Graph_EffectOfRadCorr[Ntargets][Nkinvars];
  for (Int_t t = 0; t < Ntargets; t++) {
    for (Int_t k = 0; k < Nkinvars; k++) {
      Graph_EffectOfRadCorr[t][k] = new TGraphErrors(Nbins_MR, BinGeoCenter[k], Ratio_EffectOfRadCorr[t][k], BinGeoWidth[k], Empty);
      // set graphs' titles and axis
      if (t == 1) {
        Graph_EffectOfRadCorr[t][k]->SetTitle("");
        Graph_EffectOfRadCorr[t][k]->GetXaxis()->SetTitle(kinvarTitle[k]);
        Graph_EffectOfRadCorr[t][k]->GetYaxis()->SetTitleSize(0.06);
        Graph_EffectOfRadCorr[t][k]->GetYaxis()->SetTitleOffset(1.1);
        Graph_EffectOfRadCorr[t][k]->GetYaxis()->SetTitle("R^{#" + PartOption + "}_{RC+AC} / R^{#" + PartOption + "}_{AC}");
        Graph_EffectOfRadCorr[t][k]->GetYaxis()->SetRangeUser(0.85 * MinRange[k], 1.15 * MaxRange[k]);
        Graph_EffectOfRadCorr[t][k]->GetXaxis()->SetTitleSize(0.06);
      }
      // set graphs' style
      Graph_EffectOfRadCorr[t][k]->SetMarkerStyle(20);
      Graph_EffectOfRadCorr[t][k]->SetMarkerSize(2);
      Graph_EffectOfRadCorr[t][k]->SetMarkerColor(targetColor[t]);
      Graph_EffectOfRadCorr[t][k]->SetLineColor(targetColor[t]);
      Graph_EffectOfRadCorr[t][k]->SetLineWidth(3);
    }
  }

  /*** DRAW ***/

  SetMyStyle();

  const Int_t Nx = 2;
  const Int_t Ny = 1;
  TString CanvasName = "electron-rad-corr_" + PartOption;
  TCanvas *c = new TCanvas(CanvasName, CanvasName, Nx * 1080, Ny * 1080);
  c->Divide(Nx, Ny, 0.001, 0.001);

  for (Int_t k = 0; k < Nkinvars; k++) {
    c->cd(k + 1);

    Graph_EffectOfRadCorr[1][k]->Draw("AP");
    Graph_EffectOfRadCorr[2][k]->Draw("P");
    Graph_EffectOfRadCorr[3][k]->Draw("P");

    // legend
    if (k == 1) {
      TLegend *legend = new TLegend(0.75, 0.7, 0.9, 0.9);  // x1,y1,x2,y2
      legend->AddEntry(Graph_EffectOfRadCorr[1][k], "C", "pl");
      legend->AddEntry(Graph_EffectOfRadCorr[2][k], "Fe", "pl");
      legend->AddEntry(Graph_EffectOfRadCorr[3][k], "Pb", "pl");
      legend->SetFillStyle(0);
      legend->SetTextFont(62);
      legend->SetTextSize(0.03);
      legend->SetBorderSize(0);
      legend->Draw();
    }
  }

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/rad-corr_electron";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);

    // create output file
    TString OutputFileName = OutputDir + "/" + CanvasName + ".root";
    TFile *RootOutputFile = new TFile(OutputFileName, "RECREATE");

    // loop over EXTERNALS binning
    for (Int_t t = 0; t < Ntargets; t++) {
      for (Int_t q = 0; q < NbinsQ2_Externals; q++) {
        for (Int_t n = 0; n < NbinsNu_Externals; n++) {
          Hist_Data[t][q][n]->Write();
          Hist_MC[t][q][n]->Write();
          Hist_Sim[t][q][n]->Write();
          Hist_Acceptance[t][q][n]->Write();
          Hist_AccCorr[t][q][n]->Write();
          Hist_RadCorr[t][q][n]->Write();
        }
      }
    }

    // loop over MR binning
    for (Int_t t = 0; t < Ntargets; t++) {
      for (Int_t k = 0; k < Nkinvars; k++) {
        HistForMR_RadCorr[t][k]->Write();
        HistForMR_Data[t][k]->Write();
        HistForMR_MC[t][k]->Write();
        HistForMR_Sim[t][k]->Write();
        HistForMR_Acceptance[t][k]->Write();
        HistForMR_AccCorr[t][k]->Write();
        SolToLiq_AccCorr[t][k]->Write();
        SolToLiq_RadCorr[t][k]->Write();
        EffectOfRadCorr[t][k]->Write();
      }
    }

    // close output file
    RootOutputFile->Close();

    // print output file path
    std::cout << "The following file has been created: " << OutputFileName << std::endl;
  }
}
