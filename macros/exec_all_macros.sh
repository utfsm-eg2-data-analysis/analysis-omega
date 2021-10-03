#!/bin/bash

# these will be an input option, later...
data_kind="data"
stage=1

targets=("D" "C" "Fe" "Pb")
kinvars_eta=("Q2" "Nu" "nZ" "nPt2")
kinvars_omega=("Q2" "Nu" "wZ" "wPt2")

if [[ "${data_kind}" == "data" && "${stage}" == "1" ]]; then

    ######################
    # eta reconstruction #
    ######################

    # main plots
    root -l -b -q 'eta_reco/DrawOver_MassPerTarget.cxx("png")'
    root -l -b -q 'eta_reco/DrawOver_EffectOfKinCuts.cxx("png")'
    root -l -b -q 'eta_reco/Draw_Binning.cxx("Fe", "png")'
    root -l -b -q 'eta_reco/Draw2D_EtaMass_vs_Z.cxx("png")'
    # get electron numbers for normalization
    root -l -b -q 'eta_reco/Get_ElectronNumbers.cxx("D")'
    root -l -b -q 'eta_reco/Get_ElectronNumbers.cxx("C")'
    root -l -b -q 'eta_reco/Get_ElectronNumbers.cxx("Fe")'
    root -l -b -q 'eta_reco/Get_ElectronNumbers.cxx("Pb")'

    ############################################
    # eta background subtraction - bkg fitting #
    ############################################

    for var in "${kinvars_eta[@]}"; do
        root -l -b -q 'eta_bkg-fitting/Make_BkgFitting.cxx("All", ${var}, 0, "png")'
    done

    ########################
    # omega reconstruction #
    ########################

    # main plots
    root -l -b -q 'omega_reco/DrawOver_MassDefinitions.cxx("png")'
    root -l -b -q 'omega_reco/DrawOver_MassPerTarget.cxx("wM", "png")'
    root -l -b -q 'omega_reco/DrawOver_MassPerTarget.cxx("wD", "png")'
    root -l -b -q 'omega_reco/Make_Binning.cxx("Pb", 4, "png")'
    root -l -b -q 'omega_reco/DrawFit_Pi0Mass.cxx("png")'
    root -l -b -q 'omega_reco/DrawFit_NeutralKaonMass.cxx("png")'
    root -l -b -q 'omega_reco/Draw2D_NeutralKaonMass.cxx("png")'

    # get electron numbers for normalization
    root -l -b -q 'omega_reco/Get_ElectronNumbers.cxx("D")'
    root -l -b -q 'omega_reco/Get_ElectronNumbers.cxx("C")'
    root -l -b -q 'omega_reco/Get_ElectronNumbers.cxx("Fe")'
    root -l -b -q 'omega_reco/Get_ElectronNumbers.cxx("Pb")'

    ##############################################
    # omega background subtraction - bkg fitting #
    ##############################################

    for var in "${kinvars_omega[@]}"; do
        root -l -b -q 'omega_bkg-fitting/Make_BkgFitting.cxx("All", "${var}", 0, "png")'
    done

    ##############################################
    # omega background subtraction - evnt mixing #
    ##############################################

    for var in "${kinvars_omega[@]}"; do
        root -l -b -q 'omega_evnt-mixing/Make_EventMixing.cxx("All", "${var}", 0, "png")'
    done

fi

if [[ "${data_kind}" == "data" && "${stage}" == "2" ]]; then

    # draw hardcoded electron numbers
    root -l -b -q 'eta_reco/Draw_ElectronNumbers.cxx("png")'
    root -l -b -q 'omega_reco/Draw_ElectronNumbers.cxx("png")'

    ############################################
    # eta background subtraction - bkg fitting #
    ############################################

    for targ in "${targets[@]}"; do
        for var in "${kinvars_eta[@]}"; do
            root -l -b -q 'eta_bkg-fitting/Make_BkgFitting.cxx("${targ}", "${var}", 1, "png")'
        done
    done

    ##############################################
    # omega background subtraction - bkg fitting #
    ##############################################

    for targ in "${targets[@]}"; do
        for var in "${kinvars_omega[@]}"; do
            root -l -b -q 'omega_bkg-fitting/Make_BkgFitting.cxx("${targ}", "${var}", 1, "png")'
        done
    done

    ##############################################
    # omega background subtraction - evnt mixing #
    ##############################################

    for targ in "${targets[@]}"; do
        for var in "${kinvars_omega[@]}"; do
            root -l -b -q 'omega_evnt-mixing/Make_EventMixing.cxx("${targ}", "${var}", 1, "png")'
        done
    done

fi

if [[ "${data_kind}" == "data" && "${stage}" == "3" ]]; then

    # draw param. results from eta - bkg fitting


    # draw param. results from omega - bkg fitting


    # draw param. results from omega - evnt mixing


fi
