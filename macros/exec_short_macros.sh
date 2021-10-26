#!/bin/bash

########################################################
#                                                      #
#  Script made to execute only SHORT macros,           #
#      depending on the stage and particle to analyze  #
#                                                      #
########################################################

function print_help() {
    echo "SCRIPT: exec_short_macros.sh"
    echo "============================"
    echo "./exec_short_macros.sh --kind <data_kind> --stage <stage> --part <part>"
    echo "Where:"
    echo "  <kind>  = selects kind of data (data, sim)"
    echo "  <stage> = selecst stage of analysis (ana, pre-radcorr, radcorr)"
    echo "  <part>  = selects particle (eta, omega)"
    echo "Example:"
    echo "  ./exec_short_macros.sh --kind data --stage ana --part omega"
    exit
}

function process_args() {
    arr=("$@")
    ic=0
    while [[ $ic -le $((${#arr[@]}-1)) ]]; do
        if [[ "${arr[$ic]}" == "--part" ]]; then
            particle=${arr[$((ic+1))]}
        elif [[ "${arr[$ic]}" == "--stage" ]]; then
            stage=${arr[$((ic+1))]}
        elif [[ "${arr[$ic]}" == "--kind" ]]; then
            data_kind=${arr[$((ic+1))]}
        else
            echo "ERROR: unrecognized argument: ${arr[$((ic))]}.";
            print_help;
        fi
        ((ic+=2))
    done
}

function print_args() {
    echo "SCRIPT: exec_short_macros.sh"
    echo "============================"
    echo "kind  = ${data_kind}"
    echo "stage = ${stage}"
    echo "part  = ${particle}"
    echo ""
}

################
###   Main   ###
################

if [[ -z "${WORKDIR}" ]]; then
    echo "ERROR: variable WORKDIR is unset."
    exit 1
fi

if [[ -z "${PRODIR}" ]]; then
    echo "ERROR: variable PRODIR is unset."
    exit 1
fi

if [[ ${#} -ne 4 && ${#} -ne 6 ]]; then
    echo "ERROR: ${#} arguments were provided, they should be 4 or 6."
    print_help
fi

argArray=("$@")
process_args "${argArray[@]}"
print_args

# define important arrays
targets=("D" "C" "Fe" "Pb")
kinvars_eta=("Q2" "Nu" "nZ" "nPt2")
kinvars_omega=("Q2" "Nu" "wZ" "wPt2")

if [[ "${data_kind}" == "data" && "${stage}" == "ana" && "${particle}" == "eta" ]]; then

    ################
    # eta analysis #
    ################

    # draw electron numbers for normalization
    root -l -b -q 'eta_reco/Draw_ElectronNumbers.cxx("png")'

    # draw obtained eta numbers
    root -l -b -q 'eta_bkg-fitting/Draw_EtaNumbers.cxx("png")'

    # do MR of eta
    root -l -b -q 'eta_bkg-fitting/MakeMR_BkgFitting.cxx("png")'
fi

if [[ "${data_kind}" == "data" && "${stage}" == "ana" && "${particle}" == "omega" ]]; then

    ##################
    # omega analysis #
    ##################

    # draw electron numbers for normalization
    root -l -b -q 'omega_reco/Draw_ElectronNumbers.cxx("png")'

    # draw obtained number of omega after bkg fitting
    root -l -b -q 'omega_bkg-fitting/Draw_OmegaNumbers.cxx("png")'

    # do MR of omega from bkg fitting
    root -l -b -q 'omega_bkg-fitting/MakeMR_BkgFitting.cxx("png")'

    # draw obtained number of omega after bkg subtraction via evnt mixing
    root -l -b -q 'omega_evnt-mixing/Draw_OmegaNumbers.cxx("png")'

    # do MR of omega from evnt mixing
    root -l -b -q 'omega_evnt-mixing/MakeMR_EventMixing.cxx("png")'
fi

if [[ "${data_kind}" == "sim" && "${stage}" == "ana" && "${particle}" == "omega" ]]; then

    ##############
    # omega gen. #
    ##############

    # draw gen. electron numbers for normalization
    root -l -b -q 'omega_mc/Draw_ElectronNumbers.cxx("png")'

    # draw obtained gen. omega numbers after counting with parent id
    root -l -b -q 'omega_mc/Draw_OmegaNumbers.cxx("png")'

    ###################
    # omega sim. rec. #
    ###################

    # draw sim. rec. electron numbers for normalization
    root -l -b -q 'omega_sim/Draw_ElectronNumbers.cxx("png")'

    # draw obtained sim. rec. omega numbers after bkg subtraction via evnt mixing
    root -l -b -q 'omega_sim/Draw_OmegaNumbers.cxx("png")'

    ####################
    # omega acceptance #
    ####################

    # electron acceptance
    root -l -b -q 'omega_acceptance/Make_ElectronAcceptance.cxx("png")'
    # omega acceptance
    root -l -b -q 'omega_acceptance/Make_OmegaAcceptance.cxx("png")'
    # acceptance corr factors
    root -l -b -q 'omega_acceptance/Make_AcceptanceCorrFactors.cxx("png")'
    # acceptance corr ratios
    root -l -b -q 'omega_acceptance/Make_AcceptanceCorrRatios.cxx("png")'
    # do MR with acceptance
    root -l -b -q 'omega_acceptance/MakeMR_AcceptanceCorr.cxx("png")'
fi

if [[ "${data_kind}" == "sim" && "${stage}" == "ana" && "${particle}" == "eta" ]]; then

    ############
    # eta gen. #
    ############

    # draw gen. electron numbers for normalization
    root -l -b -q 'eta_mc/Draw_ElectronNumbers.cxx("png")'

    # draw obtained gen. eta numbers
    root -l -b -q 'eta_mc/Draw_EtaNumbers.cxx("png")'

    #################
    # eta sim. rec. #
    #################

    # draw sim.rec. electron numbers for normalization
    root -l -b -q 'eta_sim/Draw_ElectronNumbers.cxx("png")'

    # draw obtained sim.rec. eta numbers
    root -l -b -q 'eta_sim/Draw_EtaNumbers.cxx("png")'

    ##################
    # eta acceptance #
    ##################

    # electron acceptance
    root -l -b -q 'eta_acceptance/Make_ElectronAcceptance.cxx("png")'
    # eta acceptance
    root -l -b -q 'eta_acceptance/Make_EtaAcceptance.cxx("png")'
    # acceptance corr factors
    root -l -b -q 'eta_acceptance/Make_AcceptanceCorrFactors.cxx("png")'
    # acceptance corr ratios
    root -l -b -q 'eta_acceptance/Make_AcceptanceCorrRatios.cxx("png")'
    # do MR with acceptance
    root -l -b -q 'eta_acceptance/MakeMR_AcceptanceCorr.cxx("png")'
fi

if [[ "${stage}" == "radcorr" && "${particle}" == "electron" ]]; then

    # draw externals corr factors
    root -l -b -q 'rad-corr_electron/Draw_ExternalsCorrFactors.cxx("eta", "png")'
    root -l -b -q 'rad-corr_electron/Draw_ExternalsCorrFactors.cxx("omega", "png")'

    # draw externals corr ratios
    root -l -b -q 'rad-corr_electron/Draw_ExternalsCorrRatios.cxx("eta", "png")'
    root -l -b -q 'rad-corr_electron/Draw_ExternalsCorrRatios.cxx("omega", "png")'

    # draw coulomb corr factors
    root -l -b -q 'rad-corr_electron/Draw_CoulombCorrFactors.cxx("eta", "png")'
    root -l -b -q 'rad-corr_electron/Draw_CoulombCorrFactors.cxx("omega", "png")'

    # plot MR of omega
    root -l -b -q 'rad-corr_electron/MakeMR_RadCorr_Omega.cxx("png")'

    # plot MR of eta
    root -l -b -q 'rad-corr_electron/MakeMR_RadCorr_Eta.cxx("png")'
fi

if [[ "${stage}" == "pre-radcorr" && "${particle}" == "omega" ]]; then

    # draw and fit acc. corr. PhiPQ distributions
    root -l -b -q 'rad-corr_omega/DrawFit_PhiPQ.cxx("png")'

    # after this, obtain RC Factors with HAPRAD...
fi

if [[ "${stage}" == "radcorr" && "${particle}" == "omega" ]]; then

    # after obtaining rad. corr. factors, plot them!
    root -l -b -q 'rad-corr_omega/Draw_RadCorrFactors.cxx("png")'
    root -l -b -q 'rad-corr_omega/Draw_RadCorrRatios.cxx("png")'
fi

if [[ "${stage}" == "pre-radcorr" && "${particle}" == "eta" ]]; then

    # draw and fit acc. corr. PhiPQ distributions
    root -l -b -q 'rad-corr_eta/DrawFit_PhiPQ.cxx("png")'

    # after this, obtain RC Factors with HAPRAD...
fi

if [[ "${stage}" == "radcorr" && "${particle}" == "eta" ]]; then

    # after obtaining rad. corr. factors, plot them!
    root -l -b -q 'rad-corr_eta/Draw_RadCorrFactors.cxx("png")'
    root -l -b -q 'rad-corr_eta/Draw_RadCorrRatios.cxx("png")'
fi
