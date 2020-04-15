////////////////////////////////////////////////////////////////////////
// TTRGSBank
//
// Initial Author: Gagik Gavalian  UNH  11/13/1999 
//
// This file is generated automatically by make_bank_class.pl 
//
// Generation DATE : Tue Nov 23 18:20:38 EST 1999
//
////////////////////////////////////////////////////////////////////////
#ifndef _TTRGSClass_ 
#define _TTRGSClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TString.h"

class TTRGSClass: public TObject{

public:
  UInt_t     Clock_ug;       // Ungated Clock                                         
  UInt_t     Fcup_ug;        // FCUP UNGATED                                          
  UInt_t     Microsec;       // microsecond clock (will overflow during normal run)   
  UInt_t     Mor_st;         // MOR.ST                                                
  UInt_t     Mor_pc;         // MOR.PC                                                
  UInt_t     Mor_ps;         // MOR.PS                                                
  UInt_t     Mor_tac;        // MOR.TAC                                               
  UInt_t     Mor;            // Master OR                                             
  UInt_t     Pc;             // Pair Counter                                          
  UInt_t     Ps;             // Pair Spectrometer                                     
  UInt_t     Tac;            // Total Absorption Counter                              
  UInt_t     St;             // ST                                                    
  UInt_t     Clock_ug_2;     // duplicate of channel 1                                
  UInt_t     Fcup_ug_2;      // duplicate of channel 2                                
  UInt_t     Clock_g1;       // Clock with run gatei                                  
  UInt_t     Fcup_g1;        // FCUP with Run Gate                                    
  UInt_t     Mor_st_rg;      // MOR.ST  with run gate                                 
  UInt_t     Mor_pc_rg;      // MOR.PC with run gate                                  
  UInt_t     Mor_ps_rg;      // MOR.PS with run gate                                  
  UInt_t     Mor_tac_rg;     // MOR.TAC with run gate                                 
  UInt_t     Mor_rg;         // MASTER_OR with run gate                               
  UInt_t     Pc_rg;          // PC with run gate                                      
  UInt_t     Ps_rg;          // PS with run gate                                      
  UInt_t     Tac_rg;         // TAC with run gate                                     
  UInt_t     St_rg;          // ST  with run gate                                     
  UInt_t     Clock_g1_2;     // duplicate of channel 17                               
  UInt_t     Fcup_g1_2;      // duplicate of channel 18                               
  UInt_t     Clock_g2;       // CLOCK with Live gate                                  
  UInt_t     Fcup_g2;        // FCUP with Live gate                                   
  UInt_t     Mor_lg;         // MASTER_OR with Live gate                              
  UInt_t     Clock_g2_2;     // duplicate of channel 33                               
  UInt_t     Fcup_g2_2;      // duplicate of channel 34                               
  UInt_t     Trig1_ug;       // Trigger 1 ungated, prescaled                          
  UInt_t     Trig2_ug;       // Trigger 2 ungated, prescaled                          
  UInt_t     Trig3_ug;       // Trigger 3 ungated, prescaled                          
  UInt_t     Trig4_ug;       // Trigger 4 ungated, prescaled                          
  UInt_t     Trig5_ug;       // Trigger 5 ungated, prescaled                          
  UInt_t     Trig6_ug;       // Trigger 6 ungated, prescaled                          
  UInt_t     Trig7_ug;       // Trigger 7 ungated, prescaled                          
  UInt_t     Trig8_ug;       // Trigger 8 ungated, prescaled                          
  UInt_t     Trig9_ug;       // Trigger 9 ungated, prescaled                          
  UInt_t     Trig10_ug;      // Trigger 10 ungated, prescaled                         
  UInt_t     Trig11_ug;      // Trigger 11 ungated, prescaled                         
  UInt_t     Trig12_ug;      // Trigger 12 ungated, prescaled                         
  UInt_t     Trig_or_ug;     // Trigger OR of 1-12 ungated,                           
  UInt_t     L1accept;       // Level 1 accept                                        
  UInt_t     L2fail;         // Level2 fail                                           
  UInt_t     L2pass;         // Level2 pass                                           
  UInt_t     L2start;        // Level2 start                                          
  UInt_t     L2clear;        // Level2 clear                                          
  UInt_t     L2accept;       // Level2 accept                                         
  UInt_t     L3accept;       // Level3 accept                                         
  
 public:
  TTRGSClass(){};
  TTRGSClass(TTRGSClass *TmpTRGS);
  virtual ~TTRGSClass(){};
  void 	 Print();
  //
  ClassDef(TTRGSClass,1)// Scaler bank TRGS for trigger, MOR and counters.
    };
#endif


