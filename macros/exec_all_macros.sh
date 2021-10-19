#!/bin/bash

########################################################
#                                                      #
#  Script made to execute all macros,                  #
#      depending on the stage and particle to analyze  #
#                                                      #
########################################################

function print_help() {
    echo "SCRIPT: exec_all_macros.sh"
    echo "======================="
    echo "./exec_all_macros.sh --kind <data_kind> --stage <stage> --part <part>"
    echo "Where:"
    echo "  <kind>  = selects kind of data (data, sim)"
    echo "  <stage> = selecst stage of analysis (test, ana, pre-radcorr, radcorr)"
    echo "  <part>  = selects particle (eta, omega)"
    echo "Example:"
    echo "  ./exec_all_macros.sh --kind data --stage ana --part omega"
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
    echo "SCRIPT: exec_all_macros.sh"
    echo "=========================="
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

if [[ "${data_kind}" == "data" && "${stage}" == "test" ]]; then

    ###########################
    # general event selection #
    ###########################

    # electron id
    root -l -b -q 'id_electron/Draw2D_Eout_vs_Ein.cxx("png")'
    root -l -b -q 'id_electron/Draw2D_SampFrac_Cuts.cxx("png")'
    root -l -b -q 'id_electron/Draw2D_ThetaLab_vs_PhiLab.cxx("png")'
    root -l -b -q 'id_electron/Draw2D_ECY_vs_ECX.cxx("png")'

    # photons id
    root -l -b -q 'id_photon/Draw_PhotonOpAngle.cxx("png")'

    # vertex cuts
    root -l -b -q 'id_electron/Draw2D_VertexCorr.cxx("png")'

    # DIS cuts
    root -l -b -q 'id_electron/Draw2D_DIS_Cuts.cxx("C", "png")'
fi

if [[ "${data_kind}" == "data" && "${stage}" == "ana" && "${particle}" == "eta" ]]; then

    ################
    # eta analysis #
    ################

    # main plots
    root -l -b -q 'eta_reco/DrawOver_MassPerTarget.cxx(0, "png")' # need to remove photon's corr ???
    root -l -b -q 'eta_reco/DrawOver_EffectOfKinCuts.cxx("png")'
    root -l -b -q 'eta_reco/DrawOver_MassPerTarget.cxx(1, "png")' # need to remove photon's corr ???
    root -l -b -q 'eta_reco/Draw_Binning.cxx("Fe", "png")'
    root -l -b -q 'eta_reco/Draw2D_EtaMass_vs_Z.cxx("png")'

    # get and draw electron numbers for normalization
    root -l -b -q 'eta_reco/Get_ElectronNumbers.cxx'
    root -l -b -q 'eta_reco/Draw_ElectronNumbers.cxx("png")'

    # eta background subtraction via bkg fitting
    # 1) do it for all data
    for var in "${kinvars_eta[@]}"; do
        root -l -b -q 'eta_bkg-fitting/Make_BkgFitting.cxx("All", "'"${var}"'", 0, "png")'
    done
    # 2) do it for each target, fixing params
    for targ in "${targets[@]}"; do
        for var in "${kinvars_eta[@]}"; do
            root -l -b -q 'eta_bkg-fitting/Make_BkgFitting.cxx("'"${targ}"'", "'"${var}"'", 1, "png")'
        done
    done
    # draw obtained parameters
    root -l -b -q 'eta_bkg-fitting/Draw_EtaNumbers.cxx("png")'

    # do MR of eta
    root -l -b -q 'eta_MR/MakeMR_BkgFitting.cxx("png")'
fi

if [[ "${data_kind}" == "data" && "${stage}" == "ana" && "${particle}" == "omega" ]]; then

    ##################
    # omega analysis #
    ##################

    # main plots
    root -l -b -q 'omega_reco/DrawOver_MassPerTarget.cxx("wM", "png")'
    root -l -b -q 'omega_reco/DrawOver_MassDefinitions.cxx("png")'
    root -l -b -q 'omega_reco/DrawOver_MassPerTarget.cxx("wD", "png")'
    root -l -b -q 'omega_reco/DrawFit_Pi0Mass.cxx("png")' # to be hardcoded
    root -l -b -q 'omega_reco/DrawFit_NeutralKaonMass.cxx("png")' # to be hardcoded
    root -l -b -q 'omega_reco/Make_Binning.cxx("Pb", 4, "png")' # to be hardcoded
    root -l -b -q 'omega_reco/Draw2D_NeutralKaonMass.cxx("png")'

    # get and draw electron numbers for normalization
    root -l -b -q 'omega_reco/Get_ElectronNumbers.cxx'
    root -l -b -q 'omega_reco/Draw_ElectronNumbers.cxx("png")'

    # omega background subtraction via bkg fitting
    # 1) do it for all data
    for var in "${kinvars_omega[@]}"; do
        root -l -b -q 'omega_bkg-fitting/Make_BkgFitting.cxx("All", "'"${var}"'", 0, "png")'
    done
    # 2) do it for each target, fixing params
    for targ in "${targets[@]}"; do
        for var in "${kinvars_omega[@]}"; do
            root -l -b -q 'omega_bkg-fitting/Make_BkgFitting.cxx("'"${targ}"'", "'"${var}"'", 1, "png")'
        done
    done
    # draw obtained parameters
    root -l -b -q 'omega_bkg-fitting/Draw_OmegaNumbers.cxx("png")'

    # do MR of omega from bkg fitting
    root -l -b -q 'omega_MR/MakeMR_BkgFitting.cxx("png")'

    # omega background subtraction via evnt mixing
    # draw comparison between data and evnt mixing
    root -l -b -q 'omega_evnt-mixing/DrawOver_Data_and_EventMixing.cxx("C", "png")'
    # 1) do it for all data
    for var in "${kinvars_omega[@]}"; do
        root -l -b -q 'omega_evnt-mixing/Make_EventMixing.cxx("All", "'"${var}"'", 0, "png")'
    done
    # 2) do it for each target, fixing params
    for targ in "${targets[@]}"; do
        for var in "${kinvars_omega[@]}"; do
            root -l -b -q 'omega_evnt-mixing/Make_EventMixing.cxx("'"${targ}"'", "'"${var}"'", 1, "png")'
        done
    done
    # draw obtained parameters
    root -l -b -q 'omega_evnt-mixing/Draw_OmegaNumbers.cxx("png")'

    # do MR of omega from evnt mixing
    root -l -b -q 'omega_MR/MakeMR_EventMixing.cxx("png")'
fi

if [[ "${data_kind}" == "sim" && "${stage}" == "test" ]]; then

    ###########################
    # general event selection #
    ###########################

    # electron pid plot
    root -l -b -q 'id_sim-electron/Draw2D_SampFrac_Cuts.cxx("png")'
fi

if [[ "${data_kind}" == "sim" && "${stage}" == "ana" && "${particle}" == "omega" ]]; then

    ##############
    # omega gen. #
    ##############

    # draw comparison between sim.rec. and data
    root -l -b -q 'omega_mc/DrawOver_MC_and_Data.cxx("C", "png")'

    # get and draw electron numbers for normalization
    root -l -b -q 'omega_mc/Get_ElectronNumbers.cxx'
    root -l -b -q 'omega_mc/Draw_ElectronNumbers.cxx("png")'

    # count generated omegas using parent id
    root -l -b -q 'omega_mc/DrawOver_ParentID.cxx("png")'
    # do it for each target and kinvar
    for targ in "${targets[@]}"; do
        for var in "${kinvars_omega[@]}"; do
            root -l -b -q 'omega_mc/Make_ParentID.cxx("'"${targ}"'", "'"${var}"'", "png")'
        done
    done
    # draw obtained omega numbers
    root -l -b -q 'omega_mc/Draw_OmegaNumbers.cxx("png")'

    ###################
    # omega sim. rec. #
    ###################

    # draw comparison between sim.rec. and data
    root -l -b -q 'omega_sim/DrawOver_Sim_and_Data.cxx("C", "png")'

    # get and draw electron numbers for normalization
    root -l -b -q 'omega_sim/Get_ElectronNumbers.cxx'
    root -l -b -q 'omega_sim/Draw_ElectronNumbers.cxx("png")'

    # omega background subtraction via evnt mixing
    # draw comparison between sim.rec. and evnt mixing
    root -l -b -q 'omega_sim/DrawOver_Sim_and_EventMixing.cxx("C", "png")'
    # do it for each target, without fixing params
    for targ in "${targets[@]}"; do
        for var in "${kinvars_omega[@]}"; do
            root -l -b -q 'omega_sim/Make_EventMixing.cxx("'"${targ}"'", "'"${var}"'", 0, "png")'
        done
    done
    # draw obtained omega numbers
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

    # draw comparison between sim.rec. and data
    root -l -b -q 'eta_mc/DrawOver_MC_and_Data.cxx("Fe", "png")'

    # get and draw electron numbers for normalization
    root -l -b -q 'eta_mc/Get_ElectronNumbers.cxx'
    root -l -b -q 'eta_mc/Draw_ElectronNumbers.cxx("png")'

    # get eta numbers using parent id for each target and kinvar
    for targ in "${targets[@]}"; do
        for var in "${kinvars_eta[@]}"; do
            root -l -b -q 'eta_mc/Make_ParentID.cxx("'"${targ}"'", "'"${var}"'", "png")'
        done
    done
    # draw obtained eta numbers
    root -l -b -q 'eta_mc/Draw_EtaNumbers.cxx("png")'

    #################
    # eta sim. rec. #
    #################

    # draw comparison between sim.rec. and data
    root -l -b -q 'eta_sim/DrawOver_Sim_and_Data.cxx("C", "png")'

    # get and draw electron numbers for normalization
    root -l -b -q 'eta_sim/Get_ElectronNumbers.cxx'
    root -l -b -q 'eta_sim/Draw_ElectronNumbers.cxx("png")'

    # eta background subtraction via bkg fitting
    # do it for each target, without fixing params
    for targ in "${targets[@]}"; do
        for var in "${kinvars_eta[@]}"; do
            root -l -b -q 'eta_sim/Make_BkgFitting.cxx("'"${targ}"'", "'"${var}"'", 0, "png")'
        done
    done
    # draw obtained eta numbers
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

    # draw grid
    root -l -b -q 'rad-corr_electron/Draw2D_Grid.cxx("D", "eta", "png")'
    root -l -b -q 'rad-corr_electron/Draw2D_Grid.cxx("D", "omega", "png")'

    # draw externals corr factors
    root -l -b -q 'rad-corr_electron/Draw_ExternalsCorrFactors.cxx("eta", "png")'
    root -l -b -q 'rad-corr_electron/Draw_ExternalsCorrFactors.cxx("omega", "png")'

    # draw externals corr ratios
    root -l -b -q 'rad-corr_electron/Draw_ExternalsCorrRatios.cxx("eta", "png")'
    root -l -b -q 'rad-corr_electron/Draw_ExternalsCorrRatios.cxx("omega", "png")'

    # draw coulomb corr factors
    root -l -b -q 'rad-corr_electron/Draw_CoulombCorrFactors.cxx("eta", "png")'
    root -l -b -q 'rad-corr_electron/Draw_CoulombCorrFactors.cxx("omega", "png")'

    # plot effect of rad. corr. on MR
    root -l -b -q 'rad-corr_electron/Make_RadiativeCorrRatios.cxx("eta", "png")'
    root -l -b -q 'rad-corr_electron/Make_RadiativeCorrRatios.cxx("omega", "png")'

    # plot MR of omega
    root -l -b -q 'rad-corr_electron/MakeMR_RadCorr_Omega.cxx("png")'

    # plot MR of eta
    root -l -b -q 'rad-corr_electron/MakeMR_RadCorr_Eta.cxx("png")'
fi

if [[ "${stage}" == "pre-radcorr" && "${particle}" == "omega" ]]; then

    ###############################
    # Fit PhiPQ and Get Centroids #
    ###############################

    # do background subtraction via evnt-mixing for all data
    root -l -b -q 'rad-corr_omega/Make_EventMixing_PhiPQ.cxx("All", 0, "png")'
    # do it for liquid and solid targets, fixing params
    root -l -b -q 'rad-corr_omega/Make_EventMixing_PhiPQ.cxx("D", 1, "png")'
    root -l -b -q 'rad-corr_omega/Make_EventMixing_PhiPQ.cxx("A", 1, "png")'

    # count omega numbers
    root -l -b -q 'rad-corr_omega/Make_ParentID_PhiPQ.cxx("D", "png")'
    root -l -b -q 'rad-corr_omega/Make_ParentID_PhiPQ.cxx("A", "png")'

    # do background subtraction via evnt-mixing for all data
    root -l -b -q 'rad-corr_omega/Make_EventMixing_PhiPQ_Sim.cxx("All", 0, "png")'
    # do background subtraction via evnt-mixing for all sim.rec.
    root -l -b -q 'rad-corr_omega/Make_EventMixing_PhiPQ_Sim.cxx("D", 1, "png")'
    root -l -b -q 'rad-corr_omega/Make_EventMixing_PhiPQ_Sim.cxx("A", 1, "png")'

    # draw and fit acc. corr. PhiPQ distributions
    root -l -b -q 'rad-corr_omega/DrawFit_PhiPQ.cxx("png")'

    # get centroids
    root -l -b -q 'rad-corr_omega/Get_Centroids.cxx("D")'
    root -l -b -q 'rad-corr_omega/Get_Centroids.cxx("A")'

    # after this, obtain RC Factors with HAPRAD...
fi

if [[ "${stage}" == "radcorr" && "${particle}" == "omega" ]]; then

    # after obtaining rad. corr. factors, plot them!
    root -l -b -q 'rad-corr_omega/Draw_RadCorrFactors.cxx("png")'
    root -l -b -q 'rad-corr_omega/Draw_RadCorrRatios.cxx("png")'
fi

if [[ "${stage}" == "pre-radcorr" && "${particle}" == "eta" ]]; then

    ###############################
    # Fit PhiPQ and Get Centroids #
    ###############################

    # do background subtraction via bkg-fitting for all data
    root -l -b -q 'rad-corr_eta/Make_BkgFitting_PhiPQ.cxx("All", 0, "png")'
    # do it for liquid and solid targets, fixing params
    root -l -b -q 'rad-corr_eta/Make_BkgFitting_PhiPQ.cxx("D", 1, "png")'
    root -l -b -q 'rad-corr_eta/Make_BkgFitting_PhiPQ.cxx("C", 1, "png")'
    root -l -b -q 'rad-corr_eta/Make_BkgFitting_PhiPQ.cxx("Fe", 1, "png")'
    root -l -b -q 'rad-corr_eta/Make_BkgFitting_PhiPQ.cxx("Pb", 1, "png")'

    # count eta numbers
    root -l -b -q 'rad-corr_eta/Make_ParentID_PhiPQ.cxx("D", "png")'
    root -l -b -q 'rad-corr_eta/Make_ParentID_PhiPQ.cxx("C", "png")'
    root -l -b -q 'rad-corr_eta/Make_ParentID_PhiPQ.cxx("Fe", "png")'
    root -l -b -q 'rad-corr_eta/Make_ParentID_PhiPQ.cxx("Pb", "png")'

    # do background subtraction via bkg-fitting for all data
    root -l -b -q 'rad-corr_eta/Make_BkgFitting_PhiPQ_Sim.cxx("All", 0, "png")'
    # do background subtraction via bkg-fitting for all sim.rec.
    root -l -b -q 'rad-corr_eta/Make_BkgFitting_PhiPQ_Sim.cxx("D", 1, "png")'
    root -l -b -q 'rad-corr_eta/Make_BkgFitting_PhiPQ_Sim.cxx("C", 1, "png")'
    root -l -b -q 'rad-corr_eta/Make_BkgFitting_PhiPQ_Sim.cxx("Fe", 1, "png")'
    root -l -b -q 'rad-corr_eta/Make_BkgFitting_PhiPQ_Sim.cxx("Pb", 1, "png")'

    # draw and fit acc. corr. PhiPQ distributions
    root -l -b -q 'rad-corr_eta/DrawFit_PhiPQ.cxx("png")'

    # get centroids
    root -l -b -q 'rad-corr_eta/Get_Centroids.cxx("D")'
    root -l -b -q 'rad-corr_eta/Get_Centroids.cxx("C")'
    root -l -b -q 'rad-corr_eta/Get_Centroids.cxx("Fe")'
    root -l -b -q 'rad-corr_eta/Get_Centroids.cxx("Pb")'

    # after this, obtain RC Factors with HAPRAD...
fi

if [[ "${stage}" == "radcorr" && "${particle}" == "eta" ]]; then

    # after obtaining rad. corr. factors, plot them!
    root -l -b -q 'rad-corr_eta/Draw_RadCorrFactors.cxx("png")'
    root -l -b -q 'rad-corr_eta/Draw_RadCorrRatios.cxx("png")'
fi
