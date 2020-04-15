////////////////////////////////////////////////////////////////////////
// File TEPICClass.h  
//
// Initial Author: Will Morrison  UNH  20/05/05
//
// Modified:
//
////////////////////////////////////////////////////////////////////////

#ifndef _TEPICClass_ 
#define _TEPICClass_ 
#include <iostream>
using namespace std;
#include "TObject.h"
#include "TString.h"
#include "TVector3.h"
#include "TMath.h"
#include "TEPICValue.h"
#include "TClonesArray.h"

class TEPICClass: public TObject{

 public:
  
  TClonesArray *EPIC;     //a TClonesArray containing the names and values

  Int_t First_Phys;       //the event number of the first physics event after the previous EPIC event
  Int_t Last_Phys;        //the event number of the last physics event before this EPIC event
  Int_t runno;            //the run number of this EPIC event

  Int_t First_Phys_time;  //the time of the first physics event after the previous EPIC event
  Int_t Last_Phys_time;   //the time of the last physics event before this EPIC event
  Int_t Evt_time;         //the time of this EPIC event
 


 public:
  
  TEPICClass()
    {
    EPIC=new TClonesArray("TEPICValue",146); // We expect a 146 objects.
    First_Phys=0;
    Last_Phys=0;
    runno=0;
    First_Phys_time=0;
    Last_Phys_time=0;
    Evt_time=0;
    };
  TEPICClass(TEPICClass *TmpEPIC);
  virtual ~TEPICClass(){
    EPIC->Delete();
    delete EPIC;
  };
  void AddEPIC(TEPICValue *ep);               //Only for adding a TEPICValue to the EPIC array
  void AddEPICAt(TEPICValue *ep,Int_t place); //Only for TEPICValue
  void SetFirst_Phys(Int_t First){First_Phys = First;};
  void SetLast_Phys(Int_t Last){Last_Phys = Last;};
  void Setrunno(Int_t run){runno = run;};
  void SetFirst_Phys_time(Int_t First){First_Phys_time = First;};
  void SetLast_Phys_time(Int_t Last){Last_Phys_time = Last;};
  void SetEvt_time(Int_t Evt){Evt_time = Evt;};
  void Clear(){
    EPIC->Clear();
  };

  Int_t   GetValueIndex(TString member); //This function is for use in combination with
  Float_t GetValue(Int_t ind);           // GetValue(Int_t) when looping over many events
  Float_t GetValue(TString member);
  TString GetName(Int_t ind);
  void    Print();
 
  //
  ClassDef(TEPICClass,1) // Class for accessing the EPIC bank, Beam information
    
    };

#endif

    /*                          A List of 148 members of the EPIC Bank, this was current as of 7/19/05 
      Arc1_dpp
      Arc2_dpp
      HLB:bta_60hz_rms
      HallProbe2_val
      IBC1H03AAVG
      IBC2C21AISENrbstr.STR1
      IBC2C24AISENrbstr.STR1
      IBC2C24AVG
      IBC2H01ISENrbstr.STR1
      IBC3H00AVG
      IGL1I00DAC0
      IGL1I00DAC2
      IGL1I00DAC4
      IGL1I00DIOFHRD
      IGL1I00HALLADF
      IGL1I00HALLBDF
      IGL1I00HALLCDF
      IGL1I00OD16_16.RVAL
      IGT0I00BIASET
      IPM2C21A
      IPM2C21A.IKMF
      IPM2C21A.XKMF
      IPM2C21A.XPOS
      IPM2C21A.YKMF
      IPM2C21A.YPOS
      IPM2C21AXSENrbstr.STR1
      IPM2C21AYSENrbstr.STR1
      IPM2C24A
      IPM2C24A.IKMF
      IPM2C24A.XKMF
      IPM2C24A.XPOS
      IPM2C24A.YKMF
      IPM2C24A.YPOS
      IPM2C24AXSENrbstr.STR1
      IPM2C24AYSENrbstr.STR1
      IPM2H01
      IPM2H01.IKMF
      IPM2H01.XKMF
      IPM2H01.XPOS
      IPM2H01.YKMF
      IPM2H01.YPOS
      IPM2H01XSENrbstr.STR1
      IPM2H01YSENrbstr.STR1
      LL8240
      LL8245
      MBSY1C_energy
      MBSY2C_energy
      MBSY3C_energy
      MTIRBCK
      MTSETI
      MTVRBCK
      PSPECIRBCK
      RASTCYCLETIME
      RASTPATSIZEX
      RASTPATSIZEY
      RASTSETPATTERNX
      RASTSETPATTERNY
      RASTSETXOFFSET
      RASTSETYOFFSET
      RASTXOFFSET
      RASTYOFFSET
      SMRPOSA
      SMRPOSB
      SMRPOSC
      TMIRBCK
      TMSETI
      TMVRBCK
      VCG2C21
      VCG2C24
      VCG2H01
      VIP2H01DI
      VIP2H01DV
      VMP2C24SPD
      beam_polarization
      beam_polarization_error
      brem_motor_t.HOPR
      brem_motor_t.RBV
      brem_motor_u.HOPR
      brem_motor_u.RBV
      brem_motor_v.HOPR
      brem_motor_v.RBV
      brem_motor_x.HOPR
      brem_motor_x.RBV
      brem_motor_y.HOPR
      brem_motor_y.RBV
      brem_motor_z.HOPR
      brem_motor_z.RBV
      cc_o2_ref
      cc_o2_sig
      e2_target_a_status
      e2_target_b_status
      e2_target_c_status
      frwd_scalerS5b
      frwd_scalerS6b
      frwd_scalerS7b
      halla_MeV
      halla_dpp
      halla_dppBpm
      halla_dppCorr
      hallb_sf_xy560_0_10
      hallb_sf_xy560_0_11
      hallb_sf_xy560_0_12
      hallb_sf_xy560_0_14
      hallb_sf_xy560_0_18
      hallb_sf_xy560_0_19
      hallb_sf_xy560_0_6
      hallb_sf_xy560_0_7
      hallb_sf_xy560_0_8
      hallb_sf_xy560_0_9
      hallbptcal
      hallbptcur
      hallbptdt
      hallbptenc
      hallbptindex
      hallbptpol
      hallc_dpp
      hallc_dppBpm
      hallc_dppCorr
      harp.DRBV
      moeller_target.RBV
      pspec_logic_1
      pspec_logic_2
      pspec_logic_3
      pspec_logic_4
      pspec_logic_5
      raster_status_ttl.RVAL
      scalerS1o
      scalerS2o
      scalerS3o
      scalerS4o
      scalerS5o
      scalerS6o
      scalerS7o
      scalerS8o
      scalerS9o
      scaler_calc1
      scaler_dS14b
      scaler_dS16a
      scaler_dS2b
      scaler_dS3b
      scaler_dS4b
      scaler_dS5b
      scaler_dS6b
      torus_current
      torus_current_probe
      torus_polarity
      unknown
      unknown
    */      
