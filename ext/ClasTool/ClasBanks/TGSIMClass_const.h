#ifndef __TGSIMClass_const__
#define __TGSIMClass_const__
//
// Define a number of constants as enumerated types.
//

enum EGeant_ParticleType {
                    kG_Unknown=0,   
                    kG_Photon,       // 1
                    kG_Positron,     // 2
                    kG_Electron,     // 3
                    kG_Neutrino,     // 4
                    kG_Muon_Plus,    // 5
                    kG_Muon_Minus,   // 6
                    kG_Pion_Neutral, // 7
                    kG_Pion_Plus,    // 8
                    kG_Pion_Minus,   // 9
                    kG_Kaon_Long,    // 10
                    kG_Kaon_Plus,    // 11
                    kG_Kaon_Minus,   // 12
                    kG_Neutron,      // 13
                    kG_Proton,       // 14
                    kG_AntiProton,   // 15
                    kG_Kaon_Short,   // 16
                    kG_Eta,
                    kG_Lambda,
                    kG_Sigma_Plus,
                    kG_Sigma_Neutral, //20
                    kG_Sigma_Minus,
                    kG_Cascade_Neut,
                    kG_Cascade_Minus,
                    kG_Omega,
                    kG_Anti_Neutron,
                    kG_Anti_Lambda,
                    kG_Anti_Sigma_Minus,
                    kG_Anti_Sigma_Zero,
                    kG_Anti_Sigma_Plus,
                    kG_Anti_Cascade_Neut,  //30
                    kG_Anti_Cascade_Plus,
                    kG_Anti_Omega,         // 32
		    kG_Undef_33,
		    kG_Undef_34,
		    kG_Undef_35,
		    kG_Undef_36,
		    kG_Undef_37,
		    kG_Undef_38,
		    kG_Undef_39,
		    kG_Undef_40,
		    kG_Undef_41,
		    kG_Undef_42,
		    kG_Undef_43,
		    kG_Undef_44,
                    kG_Deuteron,
                    kG_Tritium,
                    kG_He4,
                    kG_Geantino,
                    kG_He3,
		    kG_NParticleTypes};      

// PDG particle Id's, which are retured by the SEB package in RECSIS.
//
enum EGeant_ParticleId {
                    kG_Unknown_Id      =   0,
                    kG_Photon_Id       =   22,
		    kG_Positron_Id     =  -11,  
                    kG_Electron_Id     =   11,   
		    kG_Neutrino_Id     =   12,
		    kG_Muon_Plus_Id    =  -13,
		    kG_Muon_Minus_Id   =   13,
		    kG_Pion_Neutral_Id =  111,
		    kG_Pion_Plus_Id    =  211,  
		    kG_Pion_Minus_Id   = -211, 
		    kG_Kaon_Long_Id    =  130,
		    kG_Kaon_Plus_Id    =  321,  
		    kG_Kaon_Minus_Id   = -321,
		    kG_Neutron_Id      = 2112, 		    
		    kG_Proton_Id       = 2212, 
		    kG_AntiProton_Id   =-2212, 
		    kG_Kaon_Short_Id   =  310,
		    kG_Eta_Id          =  221,
		    kG_Lambda_Id       = 3122,
		    kG_Sigma_Plus_Id   = 3222,
		    kG_Sigma_Neutral_Id= 3212,
		    kG_Sigma_Minus_Id  = 3112,
		    kG_Cascade_Neut_Id = 3322,
		    kG_Cascade_Minus_Id= 3312,
		    kG_Omega_Id        = 3334,
		    kG_Anti_Neutron_Id =-2112,
		    kG_Anti_Lambda_Id  =-3122,
		    kG_Anti_Sigma_Minus_Id=-3112,
		    kG_Anti_Sigma_Zero_Id=-3212,
		    kG_Anti_Sigma_Plus_Id=-3222,
		    kG_Anti_Cascade_Neut_Id=-3322,
		    kG_Anti_Cascade_Plus_Id=-3312,
		    kG_Anti_Omega_Id   = -3334,
		    kG_Anti_Tau_Id     = -15,
		    kG_Tau_Id          =  15,
		    kG_Deuteron_Id     =  45,       // These do not have a PDG Equivalent.
		    kG_Tritium_Id      =  46,
		    kG_He4_Id          =  47,
		    kG_Geantino_Id     =  48,
		    kG_He3_Id          =  49};   

#endif
