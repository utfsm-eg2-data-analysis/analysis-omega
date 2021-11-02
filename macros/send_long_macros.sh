#!/bin/bash

###################################################################
#                                                                 #
#  Script made to send only LONG macros into the                  #
#      JLAB farm, depending on the stage and particle to analyze  #
#                                                                 #
###################################################################

function print_help() {
    echo "SCRIPT: send_long_macros.sh"
    echo "==========================="
    echo "./send_long_macros.sh --kind <data_kind> --stage <stage> --part <part>"
    echo "Where:"
    echo "  <kind>  = selects kind of data (data, sim)"
    echo "  <stage> = selecst stage of analysis (test, ana, ana-fix, radcorr, radcorr-fix)"
    echo "  <part>  = selects particle (eta, omega)"
    echo "Example:"
    echo "  ./send_long_macros.sh --kind data --stage ana --part omega"
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
    echo "SCRIPT: send_long_macros.sh"
    echo "==========================="
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

    ####################################
    # general event selection (7 jobs) #
    ####################################

    # electron id
    ./send_macro.sh --macro id_electron/Draw2D_Eout_vs_Ein.cxx --opt '("png")' --time 2
    ./send_macro.sh --macro id_electron/Draw2D_SampFrac_Cuts.cxx --opt '("png")' --time 2
    ./send_macro.sh --macro id_electron/Draw2D_ThetaLab_vs_PhiLab.cxx --opt '("png")' --time 2
    ./send_macro.sh --macro id_electron/Draw2D_ECY_vs_ECX.cxx --opt '("png")' --time 2

    # photons id
    ./send_macro.sh --macro id_photon/Draw_PhotonOpAngle.cxx --opt '("png")' --time 2

    # vertex cuts
    ./send_macro.sh --macro id_electron/Draw2D_VertexCorr.cxx --opt '("png")' --time 2

    # DIS cuts
    ./send_macro.sh --macro id_electron/Draw2D_DIS_Cuts.cxx --opt '("C", "png")' --time 2
fi

if [[ "${data_kind}" == "data" && "${stage}" == "ana" && "${particle}" == "eta" ]]; then

    ##########################
    # eta analysis (26 jobs) #
    ##########################

    # main plots
    ./send_macro.sh --macro eta_reco/DrawOver_MassPerTarget.cxx --opt '(0, "png")' --time 1
    ./send_macro.sh --macro eta_reco/DrawOver_EffectOfKinCuts.cxx --opt '("png")' --time 1
    ./send_macro.sh --macro eta_reco/DrawOver_MassPerTarget.cxx --opt '(1, "png")' --time 1
    ./send_macro.sh --macro eta_reco/Draw_Binning.cxx --opt '("Fe", "png")' --time 1
    ./send_macro.sh --macro eta_reco/Draw2D_EtaMass_vs_Z.cxx --opt '("png")' --time 1

    # get electron numbers for normalization
    ./send_macro.sh --macro eta_reco/Get_ElectronNumbers.cxx --opt '' --time 2

    # eta background subtraction via bkg fitting
    # do it for each target in data, without fixing params
    for targ in "${targets[@]}"; do
        for var in "${kinvars_eta[@]}"; do
            ./send_macro.sh --macro eta_bkg-fitting/Make_BkgFitting.cxx --opt '("'"${targ}"'", "'"${var}"'", 0, "png")' --time 1
        done
    done
fi

if [[ "${data_kind}" == "data" && "${stage}" == "ana" && "${particle}" == "omega" ]]; then

    ############################
    # omega analysis (49 jobs) #
    ############################

    # main plots
    ./send_macro.sh --macro omega_reco/DrawOver_MassPerTarget.cxx --opt '("wM", "png")' --time 1
    ./send_macro.sh --macro omega_reco/DrawOver_MassDefinitions.cxx --opt '("png")' --time 1
    ./send_macro.sh --macro omega_reco/DrawOver_MassPerTarget.cxx --opt '("wD", "png")' --time 1
    ./send_macro.sh --macro omega_reco/DrawFit_Pi0Mass.cxx --opt '("png")' --time 1
    ./send_macro.sh --macro omega_reco/DrawFit_NeutralKaonMass.cxx --opt '("png")' --time 1
    ./send_macro.sh --macro omega_reco/Make_Binning.cxx --opt '("Pb", 4, "png")' --time 1
    ./send_macro.sh --macro omega_reco/Draw2D_NeutralKaonMass.cxx --opt '("png")' --time 1

    # get and draw electron numbers for normalization
    ./send_macro.sh --macro omega_reco/Get_ElectronNumbers.cxx --opt '' --time 2

    # omega background subtraction via bkg fitting
    # 1) do it for all data
    for var in "${kinvars_omega[@]}"; do
        ./send_macro.sh --macro omega_bkg-fitting/Make_BkgFitting.cxx --opt '("All", "'"${var}"'", 0, "png")' --time 1
    done

    # omega background subtraction via evnt mixing
    # draw comparison between data and evnt mixing
    ./send_macro.sh --macro omega_evnt-mixing/DrawOver_Data_and_EventMixing.cxx --opt '("C", "png")' --time 1
    # 1) do it for all data
    for var in "${kinvars_omega[@]}"; do
        ./send_macro.sh --macro omega_evnt-mixing/Make_EventMixing.cxx --opt '("All", "'"${var}"'", 0, "png")' --time 1
    done
fi

if [[ "${data_kind}" == "data" && "${stage}" == "ana-fix" && "${particle}" == "omega" ]]; then
    # omega background subtraction via bkg fitting
    # 2) do it for each target, fixing params
    for targ in "${targets[@]}"; do
        for var in "${kinvars_omega[@]}"; do
            ./send_macro.sh --macro omega_bkg-fitting/Make_BkgFitting.cxx --opt '("'"${targ}"'", "'"${var}"'", 1, "png")' --time 1
        done
    done

    # omega background subtraction via evnt mixing
    # 2) do it for each target, fixing params
    for targ in "${targets[@]}"; do
        for var in "${kinvars_omega[@]}"; do
            ./send_macro.sh --macro omega_evnt-mixing/Make_EventMixing.cxx --opt '("'"${targ}"'", "'"${var}"'", 1, "png")' --time 1
        done
    done
fi

if [[ "${data_kind}" == "sim" && "${stage}" == "ana" && "${particle}" == "omega" ]]; then

    ########################
    # omega gen. (19 jobs) #
    ########################

    # draw comparison between sim.rec. and data
    ./send_macro.sh --macro omega_mc/DrawOver_MC_and_Data.cxx --opt '("Fe", "png")' --time 2

    # get and draw electron numbers for normalization
    ./send_macro.sh --macro omega_mc/Get_ElectronNumbers.cxx --opt '' --time 4

    # count generated omegas using parent id
    ./send_macro.sh --macro omega_mc/DrawOver_ParentID.cxx --opt '("png")' --time 2
    # do it for each target and kinvar
    for targ in "${targets[@]}"; do
        for var in "${kinvars_omega[@]}"; do
            ./send_macro.sh --macro omega_mc/Make_ParentID.cxx --opt '("'"${targ}"'", "'"${var}"'", "png")' --time 2
        done
    done

    #############################
    # omega sim. rec. (19 jobs) #
    #############################

    # draw comparison between sim.rec. and data
    ./send_macro.sh --macro omega_sim/DrawOver_Sim_and_Data.cxx --opt '("C", "png")' --time 2

    # get and draw electron numbers for normalization
    ./send_macro.sh --macro omega_sim/Get_ElectronNumbers.cxx --opt '' --time 2

    # omega background subtraction via evnt mixing
    # draw comparison between sim.rec. and evnt mixing
    ./send_macro.sh --macro omega_sim/DrawOver_Sim_and_EventMixing.cxx --opt '("C", "png")' --time 2
    # do it for each target, without fixing params
    for targ in "${targets[@]}"; do
        for var in "${kinvars_omega[@]}"; do
            ./send_macro.sh --macro omega_sim/Make_EventMixing.cxx --opt '("'"${targ}"'", "'"${var}"'", 0, "png")' --time 2
        done
    done
fi

if [[ "${data_kind}" == "sim" && "${stage}" == "ana" && "${particle}" == "eta" ]]; then

    ######################
    # eta gen. (18 jobs) #
    ######################

    # draw comparison between sim.rec. and data
    ./send_macro.sh --macro eta_mc/DrawOver_MC_and_Data.cxx --opt '("Fe", "png")' --time 2

    # get and draw electron numbers for normalization
    ./send_macro.sh --macro eta_mc/Get_ElectronNumbers.cxx --opt '' --time 4

    # get eta numbers using parent id for each target and kinvar
    for targ in "${targets[@]}"; do
        for var in "${kinvars_eta[@]}"; do
            ./send_macro.sh --macro eta_mc/Make_ParentID.cxx --opt '("'"${targ}"'", "'"${var}"'", "png")' --time 2
        done
    done

    ###########################
    # eta sim. rec. (18 jobs) #
    ###########################

    # draw comparison between sim.rec. and data
    ./send_macro.sh --macro eta_sim/DrawOver_Sim_and_Data.cxx --opt '("C", "png")' --time 2

    # get and draw electron numbers for normalization
    ./send_macro.sh --macro eta_sim/Get_ElectronNumbers.cxx --opt '' --time 2

    # eta background subtraction via bkg fitting
    # do it for each target, without fixing params
    for targ in "${targets[@]}"; do
        for var in "${kinvars_eta[@]}"; do
            ./send_macro.sh --macro eta_sim/Make_BkgFitting.cxx --opt '("'"${targ}"'", "'"${var}"'", 0, "png")' --time 2
        done
    done
fi

if [[ "${stage}" == "radcorr" && "${particle}" == "omega" ]]; then

    #########################################
    # Fit PhiPQ and Get Centroids (10 jobs) #
    #########################################

    # do background subtraction via evnt-mixing for all data
    ./send_macro.sh --macro rad-corr_omega/Make_EventMixing_PhiPQ.cxx --opt '("All", 0, "png")' --time 1

    # count omega numbers
    ./send_macro.sh --macro rad-corr_omega/Make_ParentID_PhiPQ.cxx --opt '("D", "png")' --time 2
    ./send_macro.sh --macro rad-corr_omega/Make_ParentID_PhiPQ.cxx --opt '("A", "png")' --time 2

    # do background subtraction via evnt-mixing for all sim.rec.
    ./send_macro.sh --macro rad-corr_omega/Make_EventMixing_PhiPQ_Sim.cxx --opt '("All", 0, "png")' --time 2

    # get centroids
    ./send_macro.sh --macro rad-corr_omega/Get_Centroids.cxx --opt '("D")' --time 6
    ./send_macro.sh --macro rad-corr_omega/Get_Centroids.cxx --opt '("A")' --time 6

    # after this, obtain RC Factors with HAPRAD...
fi

if [[ "${stage}" == "radcorr" && "${particle}" == "electron" ]]; then

    # get electron numbers and centroids for each bin in EXTERNALS binning
    # eta
    for targ in "${targets[@]}"; do
        for ((n=0; n<6; n++)); do
            for ((q=0; q<6; q++)); do
                ./send_macro.sh --macro rad-corr_electron/Get_ElectronNumbers.cxx --opt '("eta", "'"${targ}"'", '${n}', '${q}')' --time 8
            done
        done
    done
    # omega
    for targ in "${targets[@]}"; do
        for ((n=0; n<6; n++)); do
            for ((q=0; q<6; q++)); do
                ./send_macro.sh --macro rad-corr_electron/Get_ElectronNumbers.cxx --opt '("omega", "'"${targ}"'", '${n}', '${q}')' --time 8
            done
        done
    done
fi

if [[ "${stage}" == "radcorr-fix" && "${particle}" == "omega" ]]; then
    # do background subtraction via evnt-mixing for data liquid and solid targets, fixing params
    ./send_macro.sh --macro rad-corr_omega/Make_EventMixing_PhiPQ.cxx --opt '("D", 1, "png")' --time 1
    ./send_macro.sh --macro rad-corr_omega/Make_EventMixing_PhiPQ.cxx --opt '("A", 1, "png")' --time 1

    # do background subtraction via evnt-mixing for sim.rec. liquid and solid targets, fixing params
    ./send_macro.sh --macro rad-corr_omega/Make_EventMixing_PhiPQ_Sim.cxx --opt '("D", 1, "png")' --time 2
    ./send_macro.sh --macro rad-corr_omega/Make_EventMixing_PhiPQ_Sim.cxx --opt '("A", 1, "png")' --time 2
fi

if [[ "${stage}" == "radcorr" && "${particle}" == "eta" ]]; then

    #########################################
    # Fit PhiPQ and Get Centroids (18 jobs) #
    #########################################

    # do background subtraction via bkg-fitting for each data target, without fixing
    for targ in "${targets[@]}"; do
        ./send_macro.sh --macro rad-corr_eta/Make_BkgFitting_PhiPQ.cxx --opt '("'"${targ}"'", 0, "png")' --time 1
    done

    # count gen. eta numbers
    for targ in "${targets[@]}"; do
        ./send_macro.sh --macro rad-corr_eta/Make_ParentID_PhiPQ.cxx --opt '("'"${targ}"'", "png")' --time 4
    done

    # do background subtraction via bkg-fitting for each sim.rec. target, without fixing
    for targ in "${targets[@]}"; do
        ./send_macro.sh --macro rad-corr_eta/Make_BkgFitting_PhiPQ_Sim.cxx --opt '("'"${targ}"'", 0, "png")' --time 2
    done

    # get centroids
    for targ in "${targets[@]}"; do
        ./send_macro.sh --macro rad-corr_eta/Get_Centroids.cxx --opt '("'"${targ}"'")' --time 6
    done

    # after this, obtain RC Factors with HAPRAD...
fi
