////////////////////////////////////////////////////////////////////////
// TS1STBank.h  
//
// Initial Author: Gagik Gavalian  UNH  11/13/1999 
//
// This file is generated automatically by make_bank_class.pl 
//
// Generation DATE : Tue Nov 23 18:22:12 EST 1999
//
////////////////////////////////////////////////////////////////////////
#ifndef _TS1STClass_ 
#define _TS1STClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TString.h"

class TS1STClass: public TObject{

 public:
  UInt_t     Latch1_bit1_count;     // Count trigger bit 1  latched events            
  UInt_t     Latch1_bit2_count;     // Count trigger bit 2  latched events            
  UInt_t     Latch1_bit3_count;     // Count trigger bit 3  latched events            
  UInt_t     Latch1_bit4_count;     // Count trigger bit 4  latched events            
  UInt_t     Latch1_bit5_count;     // Count trigger bit 5  latched events            
  UInt_t     Latch1_bit6_count;     // Count trigger bit 6  latched events            
  UInt_t     Latch1_bit7_count;     // Count trigger bit 7  latched events            
  UInt_t     Latch1_bit8_count;     // Count trigger bit 8  latched events            
  UInt_t     Latch1_bit9_count;     // Count trigger bit 9  latched events            
  UInt_t     Latch1_bit10_count;    // Count trigger bit 10 latched events            
  UInt_t     Latch1_bit11_count;    // Count trigger bit 11 latched events            
  UInt_t     Latch1_bit12_count;    // Count trigger bit 12 latched events            
  UInt_t     Event_count;           // Latched event count this run                   
  UInt_t     Latch1_zero_count;     // Latch1 zero count (illegal)                    
  UInt_t     Latch1_empty_count;    // Latch1 empty count (illegal)                   
  UInt_t     Latch1_not_empty_count;// Latch1 not empty on sync event (illegal)       
  UInt_t     Latch1_ok_count;       // Latch1 ok                                      
  UInt_t     Level2_sector1;        // Level2 sector1 count                           
  UInt_t     Level2_sector2;        // Level2 sector2 count                           
  UInt_t     Level2_sector3;        // Level2 sector3 count                           
  UInt_t     Level2_sector4;        // Level2 sector4 count                           
  UInt_t     Level2_sector5;        // Level2 sector5 count                           
  UInt_t     Level2_sector6;        // Level2 sector6 count                           
  UInt_t     Level2_pass;           // Level2 pass count                              
  UInt_t     Level2_fail;           // Level2 fail count                              
  UInt_t     Latch2_zero_count;     // Latch2 zero count (illegal)                    
  UInt_t     Latch2_empty_count;    // Latch2 empty count (illegal)                   
  UInt_t     Latch2_not_empty_count;// Latch2 not empty on sync event (illegal)       
  UInt_t     Latch2_ok_count;       // Latch2 ok                                      
  UInt_t     Roc_13_count;          // Roc code 13 count (zero latch)                 
  UInt_t     Roc_15_count;          // Roc code 15 count (illegal)                    
  UInt_t     L1l2_zero_count;       // (latch1==0)&&(latch2==0)                       
  UInt_t     L1zero_13_count;       // (latch1==0)&&(roc_code==13)                    
  UInt_t     L2zero_13_count;       // (latch2==0)&&(roc_code==13)                    
  UInt_t     L1l2zero_13_count;     // (latch1==0)&&(latch2==0)&&(roc_code==13)       
public:
  TS1STClass(){};
  TS1STClass(TS1STClass *TmpS1ST);
  virtual ~TS1STClass(){};
  void     Print();
  //
  ClassDef(TS1STClass,1)//Scaler bank with trigger and latch information
    };
#endif


