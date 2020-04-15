
          integer N_DDL_BANKS 
          parameter ( N_DDL_BANKS = 200 ) 

          integer INDEX_TO_BANKS( N_DDL_BANKS ), INDEX16_TO_BANKS( N_DDL_BANKS ) 

          integer WHICH_ARRAY( N_DDL_BANKS ) 

          character*4 ddl_bank_names( N_DDL_BANKS ) 

        integer  BEAM_ind, BMPR_ind, BREP_ind, CALB_ind
        integer  CALL_ind, CC01_ind, CC1_ind, CC_ind
        integer  CCDI_ind, CCH_ind, CCMT_ind, CCPB_ind
        integer  CCPE_ind, CCRC_ind, CCS_ind, CCT_ind
        integer  CHI2_ind, CL01_ind, CLST_ind, CPED_ind
        integer  CSQL_ind, DC0_ind, DC1_ind, DCDW_ind
        integer  DCGM_ind, DCGW_ind, DCH_ind, DCMN_ind
        integer  DCPB_ind, DCV1_ind, DCV2_ind, DCV3_ind
        integer  DDLY_ind, DGEO_ind, DHCL_ind, DITM_ind
        integer  DOCA_ind, DPCP_ind, DPSP_ind, DSPC_ind
        integer  DSPS_ind, DSTC_ind, DTCP_ind, DTRK_ind
        integer  EC01_ind, EC1_ind, EC1P_ind, EC1R_ind
        integer  ECCA_ind, ECCL_ind, ECCT_ind, EC_ind
        integer  ECDI_ind, ECG_ind, ECHB_ind, ECH_ind
        integer  ECMT_ind, ECP1_ind, ECPB_ind, ECPC_ind
        integer  ECP_ind, ECPE_ind, ECPI_ind, ECPO_ind
        integer  ECRB_ind, ECS_ind, ECT_ind, EID0_ind
        integer  EPIC_ind, EVNT_ind, FBPM_ind, G1SL_ind
        integer  G2SL_ind, G3SL_ind, G4SL_ind, GCPB_ind
        integer  GGEO_ind, GPAR_ind, GPID_ind, GP_X_ind
        integer  GP_Y_ind, HBER_ind, HBID_ind, HBLA_ind
        integer  HBTB_ind, HBTR_ind, HCAL_ind, HDPL_ind
        integer  HEAD_ind, HEVT_ind, HLS_ind, IC_ind
        integer  ICHB_ind, ICPB_ind, KFIT_ind, L1PG_ind
        integer  L2H_ind, L2S_ind, LASR_ind, LCDI_ind
        integer  LCPB_ind, LOWQ_ind, MCEV_ind, MCHD_ind
        integer  MCTK_ind, MCVX_ind, MS1_ind, MTRK_ind
        integer  MVRT_ind, PART_ind, PCO_ind, PHTM_ind
        integer  PID1_ind, PID2_ind, PID3_ind, PID4_ind
        integer  PID5_ind, PID6_ind, PIDT_ind, PRTM_ind
        integer  PSO_ind, PTDB_ind, RCST_ind, REF_ind
        integer  RF_ind, RFT_ind, RGLK_ind, RNLG_ind
        integer  RNPE_ind, RTSL_ind, RUNC_ind, S1ST_ind
        integer  SC1_ind, SCC_ind, SC_ind, SCDI_ind
        integer  SCGD_ind, SCG_ind, SCH_ind, SCMD_ind
        integer  SCMT_ind, SCMW_ind, SCPB_ind, SCP_ind
        integer  SCPE_ind, SCPS_ind, SCRC_ind, SCR_ind
        integer  SCS_ind, SCT_ind, SGMP_ind, SPAR_ind
        integer  SPIN_ind, ST1_ind, ST_ind, STG_ind
        integer  STH_ind, STN0_ind, STN1_ind, STPB_ind
        integer  STPE_ind, STR_ind, STRE_ind, STS_ind
        integer  STSN_ind, SYNC_ind, TACO_ind, TAGE_ind
        integer  TAGI_ind, TAGM_ind, TAGR_ind, TAGT_ind
        integer  TATL_ind, TATR_ind, TBER_ind, TBID_ind
        integer  TBLA_ind, TBTR_ind, TCSB_ind, TCT_ind
        integer  TDPL_ind, TESC_ind, TGBI_ind, TGEO_ind
        integer  TGPB_ind, TGS_ind, TGTL_ind, TGTR_ind
        integer  TLV1_ind, TPC_ind, TPCH_ind, TRCF_ind
        integer  TRGS_ind, TRKS_ind, TRL1_ind, TRPB_ind
        integer  TSPR_ind, TSRG_ind, UNUS_ind, VERT_ind

        integer  BEAM_ind16, BMPR_ind16, BREP_ind16, CALB_ind16
        integer  CALL_ind16, CC01_ind16, CC1_ind16, CC_ind16
        integer  CCDI_ind16, CCH_ind16, CCMT_ind16, CCPB_ind16
        integer  CCPE_ind16, CCRC_ind16, CCS_ind16, CCT_ind16
        integer  CHI2_ind16, CL01_ind16, CLST_ind16, CPED_ind16
        integer  CSQL_ind16, DC0_ind16, DC1_ind16, DCDW_ind16
        integer  DCGM_ind16, DCGW_ind16, DCH_ind16, DCMN_ind16
        integer  DCPB_ind16, DCV1_ind16, DCV2_ind16, DCV3_ind16
        integer  DDLY_ind16, DGEO_ind16, DHCL_ind16, DITM_ind16
        integer  DOCA_ind16, DPCP_ind16, DPSP_ind16, DSPC_ind16
        integer  DSPS_ind16, DSTC_ind16, DTCP_ind16, DTRK_ind16
        integer  EC01_ind16, EC1_ind16, EC1P_ind16, EC1R_ind16
        integer  ECCA_ind16, ECCL_ind16, ECCT_ind16, EC_ind16
        integer  ECDI_ind16, ECG_ind16, ECHB_ind16, ECH_ind16
        integer  ECMT_ind16, ECP1_ind16, ECPB_ind16, ECPC_ind16
        integer  ECP_ind16, ECPE_ind16, ECPI_ind16, ECPO_ind16
        integer  ECRB_ind16, ECS_ind16, ECT_ind16, EID0_ind16
        integer  EPIC_ind16, EVNT_ind16, FBPM_ind16, G1SL_ind16
        integer  G2SL_ind16, G3SL_ind16, G4SL_ind16, GCPB_ind16
        integer  GGEO_ind16, GPAR_ind16, GPID_ind16, GP_X_ind16
        integer  GP_Y_ind16, HBER_ind16, HBID_ind16, HBLA_ind16
        integer  HBTB_ind16, HBTR_ind16, HCAL_ind16, HDPL_ind16
        integer  HEAD_ind16, HEVT_ind16, HLS_ind16, IC_ind16
        integer  ICHB_ind16, ICPB_ind16, KFIT_ind16, L1PG_ind16
        integer  L2H_ind16, L2S_ind16, LASR_ind16, LCDI_ind16
        integer  LCPB_ind16, LOWQ_ind16, MCEV_ind16, MCHD_ind16
        integer  MCTK_ind16, MCVX_ind16, MS1_ind16, MTRK_ind16
        integer  MVRT_ind16, PART_ind16, PCO_ind16, PHTM_ind16
        integer  PID1_ind16, PID2_ind16, PID3_ind16, PID4_ind16
        integer  PID5_ind16, PID6_ind16, PIDT_ind16, PRTM_ind16
        integer  PSO_ind16, PTDB_ind16, RCST_ind16, REF_ind16
        integer  RF_ind16, RFT_ind16, RGLK_ind16, RNLG_ind16
        integer  RNPE_ind16, RTSL_ind16, RUNC_ind16, S1ST_ind16
        integer  SC1_ind16, SCC_ind16, SC_ind16, SCDI_ind16
        integer  SCGD_ind16, SCG_ind16, SCH_ind16, SCMD_ind16
        integer  SCMT_ind16, SCMW_ind16, SCPB_ind16, SCP_ind16
        integer  SCPE_ind16, SCPS_ind16, SCRC_ind16, SCR_ind16
        integer  SCS_ind16, SCT_ind16, SGMP_ind16, SPAR_ind16
        integer  SPIN_ind16, ST1_ind16, ST_ind16, STG_ind16
        integer  STH_ind16, STN0_ind16, STN1_ind16, STPB_ind16
        integer  STPE_ind16, STR_ind16, STRE_ind16, STS_ind16
        integer  STSN_ind16, SYNC_ind16, TACO_ind16, TAGE_ind16
        integer  TAGI_ind16, TAGM_ind16, TAGR_ind16, TAGT_ind16
        integer  TATL_ind16, TATR_ind16, TBER_ind16, TBID_ind16
        integer  TBLA_ind16, TBTR_ind16, TCSB_ind16, TCT_ind16
        integer  TDPL_ind16, TESC_ind16, TGBI_ind16, TGEO_ind16
        integer  TGPB_ind16, TGS_ind16, TGTL_ind16, TGTR_ind16
        integer  TLV1_ind16, TPC_ind16, TPCH_ind16, TRCF_ind16
        integer  TRGS_ind16, TRKS_ind16, TRL1_ind16, TRPB_ind16
        integer  TSPR_ind16, TSRG_ind16, UNUS_ind16, VERT_ind16

        integer  BEAM_array, BMPR_array, BREP_array, CALB_array
        integer  CALL_array, CC01_array, CC1_array, CC_array
        integer  CCDI_array, CCH_array, CCMT_array, CCPB_array
        integer  CCPE_array, CCRC_array, CCS_array, CCT_array
        integer  CHI2_array, CL01_array, CLST_array, CPED_array
        integer  CSQL_array, DC0_array, DC1_array, DCDW_array
        integer  DCGM_array, DCGW_array, DCH_array, DCMN_array
        integer  DCPB_array, DCV1_array, DCV2_array, DCV3_array
        integer  DDLY_array, DGEO_array, DHCL_array, DITM_array
        integer  DOCA_array, DPCP_array, DPSP_array, DSPC_array
        integer  DSPS_array, DSTC_array, DTCP_array, DTRK_array
        integer  EC01_array, EC1_array, EC1P_array, EC1R_array
        integer  ECCA_array, ECCL_array, ECCT_array, EC_array
        integer  ECDI_array, ECG_array, ECHB_array, ECH_array
        integer  ECMT_array, ECP1_array, ECPB_array, ECPC_array
        integer  ECP_array, ECPE_array, ECPI_array, ECPO_array
        integer  ECRB_array, ECS_array, ECT_array, EID0_array
        integer  EPIC_array, EVNT_array, FBPM_array, G1SL_array
        integer  G2SL_array, G3SL_array, G4SL_array, GCPB_array
        integer  GGEO_array, GPAR_array, GPID_array, GP_X_array
        integer  GP_Y_array, HBER_array, HBID_array, HBLA_array
        integer  HBTB_array, HBTR_array, HCAL_array, HDPL_array
        integer  HEAD_array, HEVT_array, HLS_array, IC_array
        integer  ICHB_array, ICPB_array, KFIT_array, L1PG_array
        integer  L2H_array, L2S_array, LASR_array, LCDI_array
        integer  LCPB_array, LOWQ_array, MCEV_array, MCHD_array
        integer  MCTK_array, MCVX_array, MS1_array, MTRK_array
        integer  MVRT_array, PART_array, PCO_array, PHTM_array
        integer  PID1_array, PID2_array, PID3_array, PID4_array
        integer  PID5_array, PID6_array, PIDT_array, PRTM_array
        integer  PSO_array, PTDB_array, RCST_array, REF_array
        integer  RF_array, RFT_array, RGLK_array, RNLG_array
        integer  RNPE_array, RTSL_array, RUNC_array, S1ST_array
        integer  SC1_array, SCC_array, SC_array, SCDI_array
        integer  SCGD_array, SCG_array, SCH_array, SCMD_array
        integer  SCMT_array, SCMW_array, SCPB_array, SCP_array
        integer  SCPE_array, SCPS_array, SCRC_array, SCR_array
        integer  SCS_array, SCT_array, SGMP_array, SPAR_array
        integer  SPIN_array, ST1_array, ST_array, STG_array
        integer  STH_array, STN0_array, STN1_array, STPB_array
        integer  STPE_array, STR_array, STRE_array, STS_array
        integer  STSN_array, SYNC_array, TACO_array, TAGE_array
        integer  TAGI_array, TAGM_array, TAGR_array, TAGT_array
        integer  TATL_array, TATR_array, TBER_array, TBID_array
        integer  TBLA_array, TBTR_array, TCSB_array, TCT_array
        integer  TDPL_array, TESC_array, TGBI_array, TGEO_array
        integer  TGPB_array, TGS_array, TGTL_array, TGTR_array
        integer  TLV1_array, TPC_array, TPCH_array, TRCF_array
        integer  TRGS_array, TRKS_array, TRL1_array, TRPB_array
        integer  TSPR_array, TSRG_array, UNUS_array, VERT_array


C define the COMMON BLOCK 


          common /clas_index/
     +        index_to_banks, index16_to_banks, which_array 

C  Now equivalance the array to the individual names
        EQUIVALENCE (INDEX_TO_BANKS(1) , BEAM_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(2) , BMPR_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(3) , BREP_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(4) , CALB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(5) , CALL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(6) , CC01_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(7) , CC1_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(8) , CC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(9) , CCDI_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(10) , CCH_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(11) , CCMT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(12) , CCPB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(13) , CCPE_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(14) , CCRC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(15) , CCS_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(16) , CCT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(17) , CHI2_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(18) , CL01_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(19) , CLST_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(20) , CPED_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(21) , CSQL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(22) , DC0_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(23) , DC1_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(24) , DCDW_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(25) , DCGM_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(26) , DCGW_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(27) , DCH_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(28) , DCMN_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(29) , DCPB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(30) , DCV1_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(31) , DCV2_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(32) , DCV3_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(33) , DDLY_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(34) , DGEO_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(35) , DHCL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(36) , DITM_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(37) , DOCA_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(38) , DPCP_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(39) , DPSP_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(40) , DSPC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(41) , DSPS_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(42) , DSTC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(43) , DTCP_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(44) , DTRK_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(45) , EC01_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(46) , EC1_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(47) , EC1P_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(48) , EC1R_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(49) , ECCA_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(50) , ECCL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(51) , ECCT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(52) , EC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(53) , ECDI_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(54) , ECG_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(55) , ECHB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(56) , ECH_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(57) , ECMT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(58) , ECP1_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(59) , ECPB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(60) , ECPC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(61) , ECP_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(62) , ECPE_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(63) , ECPI_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(64) , ECPO_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(65) , ECRB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(66) , ECS_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(67) , ECT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(68) , EID0_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(69) , EPIC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(70) , EVNT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(71) , FBPM_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(72) , G1SL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(73) , G2SL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(74) , G3SL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(75) , G4SL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(76) , GCPB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(77) , GGEO_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(78) , GPAR_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(79) , GPID_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(80) , GP_X_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(81) , GP_Y_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(82) , HBER_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(83) , HBID_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(84) , HBLA_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(85) , HBTB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(86) , HBTR_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(87) , HCAL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(88) , HDPL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(89) , HEAD_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(90) , HEVT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(91) , HLS_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(92) , IC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(93) , ICHB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(94) , ICPB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(95) , KFIT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(96) , L1PG_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(97) , L2H_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(98) , L2S_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(99) , LASR_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(100) , LCDI_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(101) , LCPB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(102) , LOWQ_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(103) , MCEV_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(104) , MCHD_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(105) , MCTK_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(106) , MCVX_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(107) , MS1_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(108) , MTRK_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(109) , MVRT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(110) , PART_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(111) , PCO_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(112) , PHTM_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(113) , PID1_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(114) , PID2_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(115) , PID3_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(116) , PID4_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(117) , PID5_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(118) , PID6_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(119) , PIDT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(120) , PRTM_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(121) , PSO_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(122) , PTDB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(123) , RCST_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(124) , REF_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(125) , RF_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(126) , RFT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(127) , RGLK_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(128) , RNLG_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(129) , RNPE_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(130) , RTSL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(131) , RUNC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(132) , S1ST_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(133) , SC1_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(134) , SCC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(135) , SC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(136) , SCDI_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(137) , SCGD_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(138) , SCG_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(139) , SCH_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(140) , SCMD_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(141) , SCMT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(142) , SCMW_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(143) , SCPB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(144) , SCP_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(145) , SCPE_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(146) , SCPS_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(147) , SCRC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(148) , SCR_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(149) , SCS_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(150) , SCT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(151) , SGMP_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(152) , SPAR_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(153) , SPIN_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(154) , ST1_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(155) , ST_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(156) , STG_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(157) , STH_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(158) , STN0_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(159) , STN1_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(160) , STPB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(161) , STPE_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(162) , STR_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(163) , STRE_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(164) , STS_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(165) , STSN_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(166) , SYNC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(167) , TACO_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(168) , TAGE_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(169) , TAGI_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(170) , TAGM_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(171) , TAGR_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(172) , TAGT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(173) , TATL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(174) , TATR_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(175) , TBER_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(176) , TBID_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(177) , TBLA_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(178) , TBTR_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(179) , TCSB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(180) , TCT_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(181) , TDPL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(182) , TESC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(183) , TGBI_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(184) , TGEO_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(185) , TGPB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(186) , TGS_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(187) , TGTL_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(188) , TGTR_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(189) , TLV1_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(190) , TPC_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(191) , TPCH_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(192) , TRCF_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(193) , TRGS_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(194) , TRKS_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(195) , TRL1_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(196) , TRPB_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(197) , TSPR_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(198) , TSRG_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(199) , UNUS_ind) 
        EQUIVALENCE (INDEX_TO_BANKS(200) , VERT_ind) 

C  Now equivalance the array to the individual names for the 16 bit banks
        EQUIVALENCE (INDEX16_TO_BANKS(1) , BEAM_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(2) , BMPR_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(3) , BREP_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(4) , CALB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(5) , CALL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(6) , CC01_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(7) , CC1_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(8) , CC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(9) , CCDI_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(10) , CCH_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(11) , CCMT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(12) , CCPB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(13) , CCPE_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(14) , CCRC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(15) , CCS_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(16) , CCT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(17) , CHI2_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(18) , CL01_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(19) , CLST_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(20) , CPED_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(21) , CSQL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(22) , DC0_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(23) , DC1_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(24) , DCDW_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(25) , DCGM_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(26) , DCGW_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(27) , DCH_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(28) , DCMN_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(29) , DCPB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(30) , DCV1_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(31) , DCV2_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(32) , DCV3_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(33) , DDLY_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(34) , DGEO_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(35) , DHCL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(36) , DITM_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(37) , DOCA_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(38) , DPCP_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(39) , DPSP_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(40) , DSPC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(41) , DSPS_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(42) , DSTC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(43) , DTCP_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(44) , DTRK_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(45) , EC01_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(46) , EC1_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(47) , EC1P_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(48) , EC1R_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(49) , ECCA_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(50) , ECCL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(51) , ECCT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(52) , EC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(53) , ECDI_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(54) , ECG_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(55) , ECHB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(56) , ECH_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(57) , ECMT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(58) , ECP1_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(59) , ECPB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(60) , ECPC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(61) , ECP_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(62) , ECPE_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(63) , ECPI_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(64) , ECPO_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(65) , ECRB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(66) , ECS_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(67) , ECT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(68) , EID0_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(69) , EPIC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(70) , EVNT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(71) , FBPM_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(72) , G1SL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(73) , G2SL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(74) , G3SL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(75) , G4SL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(76) , GCPB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(77) , GGEO_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(78) , GPAR_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(79) , GPID_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(80) , GP_X_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(81) , GP_Y_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(82) , HBER_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(83) , HBID_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(84) , HBLA_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(85) , HBTB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(86) , HBTR_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(87) , HCAL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(88) , HDPL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(89) , HEAD_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(90) , HEVT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(91) , HLS_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(92) , IC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(93) , ICHB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(94) , ICPB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(95) , KFIT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(96) , L1PG_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(97) , L2H_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(98) , L2S_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(99) , LASR_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(100) , LCDI_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(101) , LCPB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(102) , LOWQ_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(103) , MCEV_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(104) , MCHD_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(105) , MCTK_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(106) , MCVX_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(107) , MS1_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(108) , MTRK_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(109) , MVRT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(110) , PART_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(111) , PCO_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(112) , PHTM_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(113) , PID1_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(114) , PID2_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(115) , PID3_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(116) , PID4_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(117) , PID5_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(118) , PID6_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(119) , PIDT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(120) , PRTM_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(121) , PSO_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(122) , PTDB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(123) , RCST_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(124) , REF_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(125) , RF_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(126) , RFT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(127) , RGLK_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(128) , RNLG_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(129) , RNPE_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(130) , RTSL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(131) , RUNC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(132) , S1ST_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(133) , SC1_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(134) , SCC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(135) , SC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(136) , SCDI_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(137) , SCGD_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(138) , SCG_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(139) , SCH_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(140) , SCMD_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(141) , SCMT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(142) , SCMW_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(143) , SCPB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(144) , SCP_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(145) , SCPE_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(146) , SCPS_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(147) , SCRC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(148) , SCR_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(149) , SCS_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(150) , SCT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(151) , SGMP_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(152) , SPAR_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(153) , SPIN_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(154) , ST1_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(155) , ST_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(156) , STG_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(157) , STH_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(158) , STN0_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(159) , STN1_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(160) , STPB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(161) , STPE_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(162) , STR_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(163) , STRE_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(164) , STS_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(165) , STSN_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(166) , SYNC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(167) , TACO_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(168) , TAGE_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(169) , TAGI_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(170) , TAGM_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(171) , TAGR_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(172) , TAGT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(173) , TATL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(174) , TATR_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(175) , TBER_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(176) , TBID_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(177) , TBLA_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(178) , TBTR_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(179) , TCSB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(180) , TCT_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(181) , TDPL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(182) , TESC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(183) , TGBI_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(184) , TGEO_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(185) , TGPB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(186) , TGS_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(187) , TGTL_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(188) , TGTR_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(189) , TLV1_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(190) , TPC_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(191) , TPCH_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(192) , TRCF_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(193) , TRGS_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(194) , TRKS_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(195) , TRL1_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(196) , TRPB_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(197) , TSPR_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(198) , TSRG_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(199) , UNUS_ind16) 
        EQUIVALENCE (INDEX16_TO_BANKS(200) , VERT_ind16) 

C  Now equivalance the array which_bank which is a flag to which
     
C  IW or JW array 
        EQUIVALENCE (WHICH_ARRAY(1) , BEAM_array) 
        EQUIVALENCE (WHICH_ARRAY(2) , BMPR_array) 
        EQUIVALENCE (WHICH_ARRAY(3) , BREP_array) 
        EQUIVALENCE (WHICH_ARRAY(4) , CALB_array) 
        EQUIVALENCE (WHICH_ARRAY(5) , CALL_array) 
        EQUIVALENCE (WHICH_ARRAY(6) , CC01_array) 
        EQUIVALENCE (WHICH_ARRAY(7) , CC1_array) 
        EQUIVALENCE (WHICH_ARRAY(8) , CC_array) 
        EQUIVALENCE (WHICH_ARRAY(9) , CCDI_array) 
        EQUIVALENCE (WHICH_ARRAY(10) , CCH_array) 
        EQUIVALENCE (WHICH_ARRAY(11) , CCMT_array) 
        EQUIVALENCE (WHICH_ARRAY(12) , CCPB_array) 
        EQUIVALENCE (WHICH_ARRAY(13) , CCPE_array) 
        EQUIVALENCE (WHICH_ARRAY(14) , CCRC_array) 
        EQUIVALENCE (WHICH_ARRAY(15) , CCS_array) 
        EQUIVALENCE (WHICH_ARRAY(16) , CCT_array) 
        EQUIVALENCE (WHICH_ARRAY(17) , CHI2_array) 
        EQUIVALENCE (WHICH_ARRAY(18) , CL01_array) 
        EQUIVALENCE (WHICH_ARRAY(19) , CLST_array) 
        EQUIVALENCE (WHICH_ARRAY(20) , CPED_array) 
        EQUIVALENCE (WHICH_ARRAY(21) , CSQL_array) 
        EQUIVALENCE (WHICH_ARRAY(22) , DC0_array) 
        EQUIVALENCE (WHICH_ARRAY(23) , DC1_array) 
        EQUIVALENCE (WHICH_ARRAY(24) , DCDW_array) 
        EQUIVALENCE (WHICH_ARRAY(25) , DCGM_array) 
        EQUIVALENCE (WHICH_ARRAY(26) , DCGW_array) 
        EQUIVALENCE (WHICH_ARRAY(27) , DCH_array) 
        EQUIVALENCE (WHICH_ARRAY(28) , DCMN_array) 
        EQUIVALENCE (WHICH_ARRAY(29) , DCPB_array) 
        EQUIVALENCE (WHICH_ARRAY(30) , DCV1_array) 
        EQUIVALENCE (WHICH_ARRAY(31) , DCV2_array) 
        EQUIVALENCE (WHICH_ARRAY(32) , DCV3_array) 
        EQUIVALENCE (WHICH_ARRAY(33) , DDLY_array) 
        EQUIVALENCE (WHICH_ARRAY(34) , DGEO_array) 
        EQUIVALENCE (WHICH_ARRAY(35) , DHCL_array) 
        EQUIVALENCE (WHICH_ARRAY(36) , DITM_array) 
        EQUIVALENCE (WHICH_ARRAY(37) , DOCA_array) 
        EQUIVALENCE (WHICH_ARRAY(38) , DPCP_array) 
        EQUIVALENCE (WHICH_ARRAY(39) , DPSP_array) 
        EQUIVALENCE (WHICH_ARRAY(40) , DSPC_array) 
        EQUIVALENCE (WHICH_ARRAY(41) , DSPS_array) 
        EQUIVALENCE (WHICH_ARRAY(42) , DSTC_array) 
        EQUIVALENCE (WHICH_ARRAY(43) , DTCP_array) 
        EQUIVALENCE (WHICH_ARRAY(44) , DTRK_array) 
        EQUIVALENCE (WHICH_ARRAY(45) , EC01_array) 
        EQUIVALENCE (WHICH_ARRAY(46) , EC1_array) 
        EQUIVALENCE (WHICH_ARRAY(47) , EC1P_array) 
        EQUIVALENCE (WHICH_ARRAY(48) , EC1R_array) 
        EQUIVALENCE (WHICH_ARRAY(49) , ECCA_array) 
        EQUIVALENCE (WHICH_ARRAY(50) , ECCL_array) 
        EQUIVALENCE (WHICH_ARRAY(51) , ECCT_array) 
        EQUIVALENCE (WHICH_ARRAY(52) , EC_array) 
        EQUIVALENCE (WHICH_ARRAY(53) , ECDI_array) 
        EQUIVALENCE (WHICH_ARRAY(54) , ECG_array) 
        EQUIVALENCE (WHICH_ARRAY(55) , ECHB_array) 
        EQUIVALENCE (WHICH_ARRAY(56) , ECH_array) 
        EQUIVALENCE (WHICH_ARRAY(57) , ECMT_array) 
        EQUIVALENCE (WHICH_ARRAY(58) , ECP1_array) 
        EQUIVALENCE (WHICH_ARRAY(59) , ECPB_array) 
        EQUIVALENCE (WHICH_ARRAY(60) , ECPC_array) 
        EQUIVALENCE (WHICH_ARRAY(61) , ECP_array) 
        EQUIVALENCE (WHICH_ARRAY(62) , ECPE_array) 
        EQUIVALENCE (WHICH_ARRAY(63) , ECPI_array) 
        EQUIVALENCE (WHICH_ARRAY(64) , ECPO_array) 
        EQUIVALENCE (WHICH_ARRAY(65) , ECRB_array) 
        EQUIVALENCE (WHICH_ARRAY(66) , ECS_array) 
        EQUIVALENCE (WHICH_ARRAY(67) , ECT_array) 
        EQUIVALENCE (WHICH_ARRAY(68) , EID0_array) 
        EQUIVALENCE (WHICH_ARRAY(69) , EPIC_array) 
        EQUIVALENCE (WHICH_ARRAY(70) , EVNT_array) 
        EQUIVALENCE (WHICH_ARRAY(71) , FBPM_array) 
        EQUIVALENCE (WHICH_ARRAY(72) , G1SL_array) 
        EQUIVALENCE (WHICH_ARRAY(73) , G2SL_array) 
        EQUIVALENCE (WHICH_ARRAY(74) , G3SL_array) 
        EQUIVALENCE (WHICH_ARRAY(75) , G4SL_array) 
        EQUIVALENCE (WHICH_ARRAY(76) , GCPB_array) 
        EQUIVALENCE (WHICH_ARRAY(77) , GGEO_array) 
        EQUIVALENCE (WHICH_ARRAY(78) , GPAR_array) 
        EQUIVALENCE (WHICH_ARRAY(79) , GPID_array) 
        EQUIVALENCE (WHICH_ARRAY(80) , GP_X_array) 
        EQUIVALENCE (WHICH_ARRAY(81) , GP_Y_array) 
        EQUIVALENCE (WHICH_ARRAY(82) , HBER_array) 
        EQUIVALENCE (WHICH_ARRAY(83) , HBID_array) 
        EQUIVALENCE (WHICH_ARRAY(84) , HBLA_array) 
        EQUIVALENCE (WHICH_ARRAY(85) , HBTB_array) 
        EQUIVALENCE (WHICH_ARRAY(86) , HBTR_array) 
        EQUIVALENCE (WHICH_ARRAY(87) , HCAL_array) 
        EQUIVALENCE (WHICH_ARRAY(88) , HDPL_array) 
        EQUIVALENCE (WHICH_ARRAY(89) , HEAD_array) 
        EQUIVALENCE (WHICH_ARRAY(90) , HEVT_array) 
        EQUIVALENCE (WHICH_ARRAY(91) , HLS_array) 
        EQUIVALENCE (WHICH_ARRAY(92) , IC_array) 
        EQUIVALENCE (WHICH_ARRAY(93) , ICHB_array) 
        EQUIVALENCE (WHICH_ARRAY(94) , ICPB_array) 
        EQUIVALENCE (WHICH_ARRAY(95) , KFIT_array) 
        EQUIVALENCE (WHICH_ARRAY(96) , L1PG_array) 
        EQUIVALENCE (WHICH_ARRAY(97) , L2H_array) 
        EQUIVALENCE (WHICH_ARRAY(98) , L2S_array) 
        EQUIVALENCE (WHICH_ARRAY(99) , LASR_array) 
        EQUIVALENCE (WHICH_ARRAY(100) , LCDI_array) 
        EQUIVALENCE (WHICH_ARRAY(101) , LCPB_array) 
        EQUIVALENCE (WHICH_ARRAY(102) , LOWQ_array) 
        EQUIVALENCE (WHICH_ARRAY(103) , MCEV_array) 
        EQUIVALENCE (WHICH_ARRAY(104) , MCHD_array) 
        EQUIVALENCE (WHICH_ARRAY(105) , MCTK_array) 
        EQUIVALENCE (WHICH_ARRAY(106) , MCVX_array) 
        EQUIVALENCE (WHICH_ARRAY(107) , MS1_array) 
        EQUIVALENCE (WHICH_ARRAY(108) , MTRK_array) 
        EQUIVALENCE (WHICH_ARRAY(109) , MVRT_array) 
        EQUIVALENCE (WHICH_ARRAY(110) , PART_array) 
        EQUIVALENCE (WHICH_ARRAY(111) , PCO_array) 
        EQUIVALENCE (WHICH_ARRAY(112) , PHTM_array) 
        EQUIVALENCE (WHICH_ARRAY(113) , PID1_array) 
        EQUIVALENCE (WHICH_ARRAY(114) , PID2_array) 
        EQUIVALENCE (WHICH_ARRAY(115) , PID3_array) 
        EQUIVALENCE (WHICH_ARRAY(116) , PID4_array) 
        EQUIVALENCE (WHICH_ARRAY(117) , PID5_array) 
        EQUIVALENCE (WHICH_ARRAY(118) , PID6_array) 
        EQUIVALENCE (WHICH_ARRAY(119) , PIDT_array) 
        EQUIVALENCE (WHICH_ARRAY(120) , PRTM_array) 
        EQUIVALENCE (WHICH_ARRAY(121) , PSO_array) 
        EQUIVALENCE (WHICH_ARRAY(122) , PTDB_array) 
        EQUIVALENCE (WHICH_ARRAY(123) , RCST_array) 
        EQUIVALENCE (WHICH_ARRAY(124) , REF_array) 
        EQUIVALENCE (WHICH_ARRAY(125) , RF_array) 
        EQUIVALENCE (WHICH_ARRAY(126) , RFT_array) 
        EQUIVALENCE (WHICH_ARRAY(127) , RGLK_array) 
        EQUIVALENCE (WHICH_ARRAY(128) , RNLG_array) 
        EQUIVALENCE (WHICH_ARRAY(129) , RNPE_array) 
        EQUIVALENCE (WHICH_ARRAY(130) , RTSL_array) 
        EQUIVALENCE (WHICH_ARRAY(131) , RUNC_array) 
        EQUIVALENCE (WHICH_ARRAY(132) , S1ST_array) 
        EQUIVALENCE (WHICH_ARRAY(133) , SC1_array) 
        EQUIVALENCE (WHICH_ARRAY(134) , SCC_array) 
        EQUIVALENCE (WHICH_ARRAY(135) , SC_array) 
        EQUIVALENCE (WHICH_ARRAY(136) , SCDI_array) 
        EQUIVALENCE (WHICH_ARRAY(137) , SCGD_array) 
        EQUIVALENCE (WHICH_ARRAY(138) , SCG_array) 
        EQUIVALENCE (WHICH_ARRAY(139) , SCH_array) 
        EQUIVALENCE (WHICH_ARRAY(140) , SCMD_array) 
        EQUIVALENCE (WHICH_ARRAY(141) , SCMT_array) 
        EQUIVALENCE (WHICH_ARRAY(142) , SCMW_array) 
        EQUIVALENCE (WHICH_ARRAY(143) , SCPB_array) 
        EQUIVALENCE (WHICH_ARRAY(144) , SCP_array) 
        EQUIVALENCE (WHICH_ARRAY(145) , SCPE_array) 
        EQUIVALENCE (WHICH_ARRAY(146) , SCPS_array) 
        EQUIVALENCE (WHICH_ARRAY(147) , SCRC_array) 
        EQUIVALENCE (WHICH_ARRAY(148) , SCR_array) 
        EQUIVALENCE (WHICH_ARRAY(149) , SCS_array) 
        EQUIVALENCE (WHICH_ARRAY(150) , SCT_array) 
        EQUIVALENCE (WHICH_ARRAY(151) , SGMP_array) 
        EQUIVALENCE (WHICH_ARRAY(152) , SPAR_array) 
        EQUIVALENCE (WHICH_ARRAY(153) , SPIN_array) 
        EQUIVALENCE (WHICH_ARRAY(154) , ST1_array) 
        EQUIVALENCE (WHICH_ARRAY(155) , ST_array) 
        EQUIVALENCE (WHICH_ARRAY(156) , STG_array) 
        EQUIVALENCE (WHICH_ARRAY(157) , STH_array) 
        EQUIVALENCE (WHICH_ARRAY(158) , STN0_array) 
        EQUIVALENCE (WHICH_ARRAY(159) , STN1_array) 
        EQUIVALENCE (WHICH_ARRAY(160) , STPB_array) 
        EQUIVALENCE (WHICH_ARRAY(161) , STPE_array) 
        EQUIVALENCE (WHICH_ARRAY(162) , STR_array) 
        EQUIVALENCE (WHICH_ARRAY(163) , STRE_array) 
        EQUIVALENCE (WHICH_ARRAY(164) , STS_array) 
        EQUIVALENCE (WHICH_ARRAY(165) , STSN_array) 
        EQUIVALENCE (WHICH_ARRAY(166) , SYNC_array) 
        EQUIVALENCE (WHICH_ARRAY(167) , TACO_array) 
        EQUIVALENCE (WHICH_ARRAY(168) , TAGE_array) 
        EQUIVALENCE (WHICH_ARRAY(169) , TAGI_array) 
        EQUIVALENCE (WHICH_ARRAY(170) , TAGM_array) 
        EQUIVALENCE (WHICH_ARRAY(171) , TAGR_array) 
        EQUIVALENCE (WHICH_ARRAY(172) , TAGT_array) 
        EQUIVALENCE (WHICH_ARRAY(173) , TATL_array) 
        EQUIVALENCE (WHICH_ARRAY(174) , TATR_array) 
        EQUIVALENCE (WHICH_ARRAY(175) , TBER_array) 
        EQUIVALENCE (WHICH_ARRAY(176) , TBID_array) 
        EQUIVALENCE (WHICH_ARRAY(177) , TBLA_array) 
        EQUIVALENCE (WHICH_ARRAY(178) , TBTR_array) 
        EQUIVALENCE (WHICH_ARRAY(179) , TCSB_array) 
        EQUIVALENCE (WHICH_ARRAY(180) , TCT_array) 
        EQUIVALENCE (WHICH_ARRAY(181) , TDPL_array) 
        EQUIVALENCE (WHICH_ARRAY(182) , TESC_array) 
        EQUIVALENCE (WHICH_ARRAY(183) , TGBI_array) 
        EQUIVALENCE (WHICH_ARRAY(184) , TGEO_array) 
        EQUIVALENCE (WHICH_ARRAY(185) , TGPB_array) 
        EQUIVALENCE (WHICH_ARRAY(186) , TGS_array) 
        EQUIVALENCE (WHICH_ARRAY(187) , TGTL_array) 
        EQUIVALENCE (WHICH_ARRAY(188) , TGTR_array) 
        EQUIVALENCE (WHICH_ARRAY(189) , TLV1_array) 
        EQUIVALENCE (WHICH_ARRAY(190) , TPC_array) 
        EQUIVALENCE (WHICH_ARRAY(191) , TPCH_array) 
        EQUIVALENCE (WHICH_ARRAY(192) , TRCF_array) 
        EQUIVALENCE (WHICH_ARRAY(193) , TRGS_array) 
        EQUIVALENCE (WHICH_ARRAY(194) , TRKS_array) 
        EQUIVALENCE (WHICH_ARRAY(195) , TRL1_array) 
        EQUIVALENCE (WHICH_ARRAY(196) , TRPB_array) 
        EQUIVALENCE (WHICH_ARRAY(197) , TSPR_array) 
        EQUIVALENCE (WHICH_ARRAY(198) , TSRG_array) 
        EQUIVALENCE (WHICH_ARRAY(199) , UNUS_array) 
        EQUIVALENCE (WHICH_ARRAY(200) , VERT_array) 

C  Define the DDL bank names 
         data  DDL_BANK_NAMES(1)/'BEAM'/ 
         data  DDL_BANK_NAMES(2)/'BMPR'/ 
         data  DDL_BANK_NAMES(3)/'BREP'/ 
         data  DDL_BANK_NAMES(4)/'CALB'/ 
         data  DDL_BANK_NAMES(5)/'CALL'/ 
         data  DDL_BANK_NAMES(6)/'CC01'/ 
         data  DDL_BANK_NAMES(7)/'CC1 '/ 
         data  DDL_BANK_NAMES(8)/'CC  '/ 
         data  DDL_BANK_NAMES(9)/'CCDI'/ 
         data  DDL_BANK_NAMES(10)/'CCH '/ 
         data  DDL_BANK_NAMES(11)/'CCMT'/ 
         data  DDL_BANK_NAMES(12)/'CCPB'/ 
         data  DDL_BANK_NAMES(13)/'CCPE'/ 
         data  DDL_BANK_NAMES(14)/'CCRC'/ 
         data  DDL_BANK_NAMES(15)/'CCS '/ 
         data  DDL_BANK_NAMES(16)/'CCT '/ 
         data  DDL_BANK_NAMES(17)/'CHI2'/ 
         data  DDL_BANK_NAMES(18)/'CL01'/ 
         data  DDL_BANK_NAMES(19)/'CLST'/ 
         data  DDL_BANK_NAMES(20)/'CPED'/ 
         data  DDL_BANK_NAMES(21)/'CSQL'/ 
         data  DDL_BANK_NAMES(22)/'DC0 '/ 
         data  DDL_BANK_NAMES(23)/'DC1 '/ 
         data  DDL_BANK_NAMES(24)/'DCDW'/ 
         data  DDL_BANK_NAMES(25)/'DCGM'/ 
         data  DDL_BANK_NAMES(26)/'DCGW'/ 
         data  DDL_BANK_NAMES(27)/'DCH '/ 
         data  DDL_BANK_NAMES(28)/'DCMN'/ 
         data  DDL_BANK_NAMES(29)/'DCPB'/ 
         data  DDL_BANK_NAMES(30)/'DCV1'/ 
         data  DDL_BANK_NAMES(31)/'DCV2'/ 
         data  DDL_BANK_NAMES(32)/'DCV3'/ 
         data  DDL_BANK_NAMES(33)/'DDLY'/ 
         data  DDL_BANK_NAMES(34)/'DGEO'/ 
         data  DDL_BANK_NAMES(35)/'DHCL'/ 
         data  DDL_BANK_NAMES(36)/'DITM'/ 
         data  DDL_BANK_NAMES(37)/'DOCA'/ 
         data  DDL_BANK_NAMES(38)/'DPCP'/ 
         data  DDL_BANK_NAMES(39)/'DPSP'/ 
         data  DDL_BANK_NAMES(40)/'DSPC'/ 
         data  DDL_BANK_NAMES(41)/'DSPS'/ 
         data  DDL_BANK_NAMES(42)/'DSTC'/ 
         data  DDL_BANK_NAMES(43)/'DTCP'/ 
         data  DDL_BANK_NAMES(44)/'DTRK'/ 
         data  DDL_BANK_NAMES(45)/'EC01'/ 
         data  DDL_BANK_NAMES(46)/'EC1 '/ 
         data  DDL_BANK_NAMES(47)/'EC1P'/ 
         data  DDL_BANK_NAMES(48)/'EC1R'/ 
         data  DDL_BANK_NAMES(49)/'ECCA'/ 
         data  DDL_BANK_NAMES(50)/'ECCL'/ 
         data  DDL_BANK_NAMES(51)/'ECCT'/ 
         data  DDL_BANK_NAMES(52)/'EC  '/ 
         data  DDL_BANK_NAMES(53)/'ECDI'/ 
         data  DDL_BANK_NAMES(54)/'ECG '/ 
         data  DDL_BANK_NAMES(55)/'ECHB'/ 
         data  DDL_BANK_NAMES(56)/'ECH '/ 
         data  DDL_BANK_NAMES(57)/'ECMT'/ 
         data  DDL_BANK_NAMES(58)/'ECP1'/ 
         data  DDL_BANK_NAMES(59)/'ECPB'/ 
         data  DDL_BANK_NAMES(60)/'ECPC'/ 
         data  DDL_BANK_NAMES(61)/'ECP '/ 
         data  DDL_BANK_NAMES(62)/'ECPE'/ 
         data  DDL_BANK_NAMES(63)/'ECPI'/ 
         data  DDL_BANK_NAMES(64)/'ECPO'/ 
         data  DDL_BANK_NAMES(65)/'ECRB'/ 
         data  DDL_BANK_NAMES(66)/'ECS '/ 
         data  DDL_BANK_NAMES(67)/'ECT '/ 
         data  DDL_BANK_NAMES(68)/'EID0'/ 
         data  DDL_BANK_NAMES(69)/'EPIC'/ 
         data  DDL_BANK_NAMES(70)/'EVNT'/ 
         data  DDL_BANK_NAMES(71)/'FBPM'/ 
         data  DDL_BANK_NAMES(72)/'G1SL'/ 
         data  DDL_BANK_NAMES(73)/'G2SL'/ 
         data  DDL_BANK_NAMES(74)/'G3SL'/ 
         data  DDL_BANK_NAMES(75)/'G4SL'/ 
         data  DDL_BANK_NAMES(76)/'GCPB'/ 
         data  DDL_BANK_NAMES(77)/'GGEO'/ 
         data  DDL_BANK_NAMES(78)/'GPAR'/ 
         data  DDL_BANK_NAMES(79)/'GPID'/ 
         data  DDL_BANK_NAMES(80)/'GP_X'/ 
         data  DDL_BANK_NAMES(81)/'GP_Y'/ 
         data  DDL_BANK_NAMES(82)/'HBER'/ 
         data  DDL_BANK_NAMES(83)/'HBID'/ 
         data  DDL_BANK_NAMES(84)/'HBLA'/ 
         data  DDL_BANK_NAMES(85)/'HBTB'/ 
         data  DDL_BANK_NAMES(86)/'HBTR'/ 
         data  DDL_BANK_NAMES(87)/'HCAL'/ 
         data  DDL_BANK_NAMES(88)/'HDPL'/ 
         data  DDL_BANK_NAMES(89)/'HEAD'/ 
         data  DDL_BANK_NAMES(90)/'HEVT'/ 
         data  DDL_BANK_NAMES(91)/'HLS '/ 
         data  DDL_BANK_NAMES(92)/'IC  '/ 
         data  DDL_BANK_NAMES(93)/'ICHB'/ 
         data  DDL_BANK_NAMES(94)/'ICPB'/ 
         data  DDL_BANK_NAMES(95)/'KFIT'/ 
         data  DDL_BANK_NAMES(96)/'L1PG'/ 
         data  DDL_BANK_NAMES(97)/'L2H '/ 
         data  DDL_BANK_NAMES(98)/'L2S '/ 
         data  DDL_BANK_NAMES(99)/'LASR'/ 
         data  DDL_BANK_NAMES(100)/'LCDI'/ 
         data  DDL_BANK_NAMES(101)/'LCPB'/ 
         data  DDL_BANK_NAMES(102)/'LOWQ'/ 
         data  DDL_BANK_NAMES(103)/'MCEV'/ 
         data  DDL_BANK_NAMES(104)/'MCHD'/ 
         data  DDL_BANK_NAMES(105)/'MCTK'/ 
         data  DDL_BANK_NAMES(106)/'MCVX'/ 
         data  DDL_BANK_NAMES(107)/'MS1 '/ 
         data  DDL_BANK_NAMES(108)/'MTRK'/ 
         data  DDL_BANK_NAMES(109)/'MVRT'/ 
         data  DDL_BANK_NAMES(110)/'PART'/ 
         data  DDL_BANK_NAMES(111)/'PCO '/ 
         data  DDL_BANK_NAMES(112)/'PHTM'/ 
         data  DDL_BANK_NAMES(113)/'PID1'/ 
         data  DDL_BANK_NAMES(114)/'PID2'/ 
         data  DDL_BANK_NAMES(115)/'PID3'/ 
         data  DDL_BANK_NAMES(116)/'PID4'/ 
         data  DDL_BANK_NAMES(117)/'PID5'/ 
         data  DDL_BANK_NAMES(118)/'PID6'/ 
         data  DDL_BANK_NAMES(119)/'PIDT'/ 
         data  DDL_BANK_NAMES(120)/'PRTM'/ 
         data  DDL_BANK_NAMES(121)/'PSO '/ 
         data  DDL_BANK_NAMES(122)/'PTDB'/ 
         data  DDL_BANK_NAMES(123)/'RCST'/ 
         data  DDL_BANK_NAMES(124)/'REF '/ 
         data  DDL_BANK_NAMES(125)/'RF  '/ 
         data  DDL_BANK_NAMES(126)/'RFT '/ 
         data  DDL_BANK_NAMES(127)/'RGLK'/ 
         data  DDL_BANK_NAMES(128)/'RNLG'/ 
         data  DDL_BANK_NAMES(129)/'RNPE'/ 
         data  DDL_BANK_NAMES(130)/'RTSL'/ 
         data  DDL_BANK_NAMES(131)/'RUNC'/ 
         data  DDL_BANK_NAMES(132)/'S1ST'/ 
         data  DDL_BANK_NAMES(133)/'SC1 '/ 
         data  DDL_BANK_NAMES(134)/'SCC '/ 
         data  DDL_BANK_NAMES(135)/'SC  '/ 
         data  DDL_BANK_NAMES(136)/'SCDI'/ 
         data  DDL_BANK_NAMES(137)/'SCGD'/ 
         data  DDL_BANK_NAMES(138)/'SCG '/ 
         data  DDL_BANK_NAMES(139)/'SCH '/ 
         data  DDL_BANK_NAMES(140)/'SCMD'/ 
         data  DDL_BANK_NAMES(141)/'SCMT'/ 
         data  DDL_BANK_NAMES(142)/'SCMW'/ 
         data  DDL_BANK_NAMES(143)/'SCPB'/ 
         data  DDL_BANK_NAMES(144)/'SCP '/ 
         data  DDL_BANK_NAMES(145)/'SCPE'/ 
         data  DDL_BANK_NAMES(146)/'SCPS'/ 
         data  DDL_BANK_NAMES(147)/'SCRC'/ 
         data  DDL_BANK_NAMES(148)/'SCR '/ 
         data  DDL_BANK_NAMES(149)/'SCS '/ 
         data  DDL_BANK_NAMES(150)/'SCT '/ 
         data  DDL_BANK_NAMES(151)/'SGMP'/ 
         data  DDL_BANK_NAMES(152)/'SPAR'/ 
         data  DDL_BANK_NAMES(153)/'SPIN'/ 
         data  DDL_BANK_NAMES(154)/'ST1 '/ 
         data  DDL_BANK_NAMES(155)/'ST  '/ 
         data  DDL_BANK_NAMES(156)/'STG '/ 
         data  DDL_BANK_NAMES(157)/'STH '/ 
         data  DDL_BANK_NAMES(158)/'STN0'/ 
         data  DDL_BANK_NAMES(159)/'STN1'/ 
         data  DDL_BANK_NAMES(160)/'STPB'/ 
         data  DDL_BANK_NAMES(161)/'STPE'/ 
         data  DDL_BANK_NAMES(162)/'STR '/ 
         data  DDL_BANK_NAMES(163)/'STRE'/ 
         data  DDL_BANK_NAMES(164)/'STS '/ 
         data  DDL_BANK_NAMES(165)/'STSN'/ 
         data  DDL_BANK_NAMES(166)/'SYNC'/ 
         data  DDL_BANK_NAMES(167)/'TACO'/ 
         data  DDL_BANK_NAMES(168)/'TAGE'/ 
         data  DDL_BANK_NAMES(169)/'TAGI'/ 
         data  DDL_BANK_NAMES(170)/'TAGM'/ 
         data  DDL_BANK_NAMES(171)/'TAGR'/ 
         data  DDL_BANK_NAMES(172)/'TAGT'/ 
         data  DDL_BANK_NAMES(173)/'TATL'/ 
         data  DDL_BANK_NAMES(174)/'TATR'/ 
         data  DDL_BANK_NAMES(175)/'TBER'/ 
         data  DDL_BANK_NAMES(176)/'TBID'/ 
         data  DDL_BANK_NAMES(177)/'TBLA'/ 
         data  DDL_BANK_NAMES(178)/'TBTR'/ 
         data  DDL_BANK_NAMES(179)/'TCSB'/ 
         data  DDL_BANK_NAMES(180)/'TCT '/ 
         data  DDL_BANK_NAMES(181)/'TDPL'/ 
         data  DDL_BANK_NAMES(182)/'TESC'/ 
         data  DDL_BANK_NAMES(183)/'TGBI'/ 
         data  DDL_BANK_NAMES(184)/'TGEO'/ 
         data  DDL_BANK_NAMES(185)/'TGPB'/ 
         data  DDL_BANK_NAMES(186)/'TGS '/ 
         data  DDL_BANK_NAMES(187)/'TGTL'/ 
         data  DDL_BANK_NAMES(188)/'TGTR'/ 
         data  DDL_BANK_NAMES(189)/'TLV1'/ 
         data  DDL_BANK_NAMES(190)/'TPC '/ 
         data  DDL_BANK_NAMES(191)/'TPCH'/ 
         data  DDL_BANK_NAMES(192)/'TRCF'/ 
         data  DDL_BANK_NAMES(193)/'TRGS'/ 
         data  DDL_BANK_NAMES(194)/'TRKS'/ 
         data  DDL_BANK_NAMES(195)/'TRL1'/ 
         data  DDL_BANK_NAMES(196)/'TRPB'/ 
         data  DDL_BANK_NAMES(197)/'TSPR'/ 
         data  DDL_BANK_NAMES(198)/'TSRG'/ 
         data  DDL_BANK_NAMES(199)/'UNUS'/ 
         data  DDL_BANK_NAMES(200)/'VERT'/ 
