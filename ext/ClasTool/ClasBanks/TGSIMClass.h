////////////////////////////////////////////////////////////////////////
// File TGSIMClass.h  
//
// Generation DATE : Tue Nov 23 18:21:36 EST 1999
//
// Modified:
//           Maurik (2/3/00)   Commented variables.
//           Maurik (11/26/01) Add Get functions etc.
//           Maurik (11/27/01) Derive from TVirtualData
//
////////////////////////////////////////////////////////////////////////
#ifndef _TGSIMClass_ 
#define _TGSIMClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TEVNTClass.h"
#include "TGSIMClass_const.h"
#include "TString.h"
#include "TVector3.h"
#include "TMath.h"
#include "TDatabasePDG.h"


const Int_t TGSIMClass__fgGeant_Particle_Id[kG_NParticleTypes]={ 
  kG_Unknown_Id,
  kG_Photon_Id,
  kG_Positron_Id,
  kG_Electron_Id,
  kG_Neutrino_Id,
  kG_Muon_Plus_Id,
  kG_Muon_Minus_Id,
  kG_Pion_Neutral_Id,
  kG_Pion_Plus_Id,
  kG_Pion_Minus_Id,
  kG_Kaon_Long_Id,
  kG_Kaon_Plus_Id,
  kG_Kaon_Minus_Id,
  kG_Neutron_Id,
  kG_Proton_Id,
  kG_AntiProton_Id,
  kG_Kaon_Short_Id,
  kG_Eta_Id,
  kG_Lambda_Id,
  kG_Sigma_Plus_Id,
  kG_Sigma_Neutral_Id,
  kG_Sigma_Minus_Id,
  kG_Cascade_Neut_Id,
  kG_Cascade_Minus_Id,
  kG_Omega_Id,
  kG_Anti_Neutron_Id,
  kG_Anti_Lambda_Id,
  kG_Anti_Sigma_Minus_Id,
  kG_Anti_Sigma_Zero_Id,
  kG_Anti_Sigma_Plus_Id,
  kG_Anti_Cascade_Neut_Id,
  kG_Anti_Cascade_Plus_Id,
  kG_Anti_Omega_Id,
  kG_Anti_Tau_Id, //33
  kG_Tau_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Deuteron_Id,
  kG_Tritium_Id,
  kG_He4_Id,
  kG_Geantino_Id,
  kG_He3_Id};


class TGSIMClass: public TVirtualData{

public:

  TGSIMClass(){};
  TGSIMClass(TGSIMClass *TmpEVNT);
  virtual ~TGSIMClass(){};

  inline Char_t GetDCStat(){return(0);};
  inline Char_t GetCCStat(){return(0);};
  inline Char_t GetSCStat(){return(0);};
  inline Char_t GetECStat(){return(0);};
  inline Char_t GetLCStat(){return(0);};
  inline Char_t GetStat()  {return(0);};
  inline Bool_t  IsGSIM() {return(kTRUE);};
  inline Bool_t  IsEVNT() {return(kFALSE);};
  void 	 Print();
//
//
//
//
 ClassDef(TGSIMClass,1) // Stores EVNT data for GSIM banks, inherit from TVirtualData.
};
#endif


