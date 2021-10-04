#!/bin/bash

# these will be an input option, later...
data_kind="data"
stage="ana"

targets=("D" "C" "Fe" "Pb")
kinvars_eta=("Q2" "Nu" "nZ" "nPt2")
kinvars_omega=("Q2" "Nu" "wZ" "wPt2")

if [[ "${data_kind}" == "data" && "${stage}" == "test" ]]; then
    ### STAGE 0: PID cuts

    # vertex cuts
    root -l -b -q 'id_electron/Draw2D_VertexCorr.cxx("Fe", "png")'

    # DIS cuts
    root -l -b -q 'id_electron/Draw2D_DIS_Cuts.cxx("Fe", "png")'
fi

if [[ "${data_kind}" == "data" && "${stage}" == "ana" ]]; then

    ################
    # eta analysis #
    ################

    # main plots
    root -l -b -q 'eta_reco/DrawOver_MassPerTarget.cxx(0, "png")'
    root -l -b -q 'eta_reco/DrawOver_EffectOfKinCuts.cxx("png")'
    root -l -b -q 'eta_reco/DrawOver_MassPerTarget.cxx(1, "png")'
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

    ##################
    # omega analysis #
    ##################

    # # main plots
    # root -l -b -q 'omega_reco/DrawOver_MassPerTarget.cxx("wM", "png")'
    # root -l -b -q 'omega_reco/DrawOver_MassDefinitions.cxx("png")'
    # root -l -b -q 'omega_reco/DrawOver_MassPerTarget.cxx("wD", "png")'
    # root -l -b -q 'omega_reco/Make_Binning.cxx("Pb", 4, "png")'
    # root -l -b -q 'omega_reco/DrawFit_Pi0Mass.cxx("png")'
    # root -l -b -q 'omega_reco/DrawFit_NeutralKaonMass.cxx("png")'
    # root -l -b -q 'omega_reco/Draw2D_NeutralKaonMass.cxx("png")'

    # # get and draw electron numbers for normalization
    # root -l -b -q 'omega_reco/Get_ElectronNumbers.cxx'
    # root -l -b -q 'omega_reco/Draw_ElectronNumbers.cxx("png")'

    # # omega background subtraction via bkg fitting #
    # # 1) do it for all data
    # for var in "${kinvars_omega[@]}"; do
    #     root -l -b -q 'omega_bkg-fitting/Make_BkgFitting.cxx("All", "'"${var}"'", 0, "png")'
    # done
    # # 2) do it for each target, fixing params
    # for targ in "${targets[@]}"; do
    #     for var in "${kinvars_omega[@]}"; do
    #         root -l -b -q 'omega_bkg-fitting/Make_BkgFitting.cxx("'"${targ}"'", "'"${var}"'", 1, "png")'
    #     done
    # done
    # # draw obtained parameters
    # root -l -b -q 'omega_bkg-fitting/Draw_OmegaNumbers.cxx("png")'

    # # do MR of omega from bkg fitting
    # root -l -b -q 'omega_MR/MakeMR_BkgFitting.cxx("png")'

    # # omega background subtraction via evnt mixing #
    # # draw comparison between data and evnt mixing
    # root -l -b -q 'omega_evnt-mixing/DrawOver_Data_and_EventMixing.cxx("C", "png")'
    # # 1) do it for all data
    # for var in "${kinvars_omega[@]}"; do
    #     root -l -b -q 'omega_evnt-mixing/Make_EventMixing.cxx("All", "'"${var}"'", 0, "png")'
    # done
    # # 2) do it for each target, fixing params
    # for targ in "${targets[@]}"; do
    #     for var in "${kinvars_omega[@]}"; do
    #         root -l -b -q 'omega_evnt-mixing/Make_EventMixing.cxx("'"${targ}"'", "'"${var}"'", 1, "png")'
    #     done
    # done
    # # draw obtained parameters
    # root -l -b -q 'omega_evnt-mixing/Draw_OmegaNumbers.cxx("png")'

    # # do MR of omega from evnt mixing
    # root -l -b -q 'omega_MR/MakeMR_EventMixing.cxx("png")'

fi
