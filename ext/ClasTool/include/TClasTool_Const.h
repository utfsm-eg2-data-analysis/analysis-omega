////////////////////////////////////////////////////////////////////
//
// All CONSTANTS and ENUMERATIONS are listed here.
// 
// This file is included into TE2AnaTool.h. The reason it is
// seperated out is that these constants are also usefull in
// macro scripts, which can not properly load the full
// TE2AnaTool.h file.
//
// I have noticed that sometimes these enumerations dissapear after
// I run through a bunch of events. This seems a CINT problem. When
// I then tried ot reload the constants, the constants come back
// but other items (such as classes) dissapear.
//
// Modified:
//   5/2/2000 Maurik Holtrop (UNH) :: Added EDBG_Codes{ kDBG_... }
//

#ifndef __TClasTool_Const__
#define  __TClasTool_Const__

// for particles identification  purpose. This list is the index into the 
// arrays associated with mass and particle property.
enum EParticleType {kUnknown,             // =0
                    kElectron,            // =1
		    kPositron,            // =2
		    kPhoton, 
		    kPion_Plus, 
		    kPion_Minus, 
		    kKaon_Plus, 
		    kKaon_Minus, 
		    kProton, 
		    kNeutron, 
		    kDeuteron, 
		    kHe3,                // =11
		    kHe4, 
		    kNParticleTypes};    // =13

// PDG particle Id's, which are retured by the SEB package in RECSIS.
enum EParticleId {  kUnknown_Id   =  0,
		    kElectron_Id  =  11,   
		    kPositron_Id  =  -11,  
		    kPhoton_Id    =  22,   
		    kPion_Plus_Id =  211,  
		    kPion_Minus_Id=  -211, 
		    kKaon_Plus_Id =  321,  
		    kKaon_Minus_Id=  -321, 
		    kProton_Id    =  2212, 
		    kNeutron_Id   =  2112, 
		    kDeuteron_Id  =  45,   
		    kHe3_Id       =  49,   
		    kHe4_Id       =  47};  

#endif
