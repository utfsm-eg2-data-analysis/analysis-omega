//////////////////////////////////////////////////////////////
//
//   File Fill_S1ST_Bank.cc
//
//   This procedure Fills TS1STClass class from BOS Bank 
//
//  Author :  Gagik Gavalian   UNH  11/10/1999
//
//
//  This file was automaticaly Generated on : 
//	Tue Nov 23 18:22:12 EST 1999 
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TS1STClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_S1ST_Bank(TS1STClass *gcS1ST,S1ST *pS1ST , int nrow);


void  Fill_S1ST_Bank(TS1STClass *gcS1ST, S1ST *pS1ST , int nrow){
gcS1ST->Latch1_bit1_count  = pS1ST->get_latch1_bit1_count(nrow);
gcS1ST->Latch1_bit2_count  = pS1ST->get_latch1_bit2_count(nrow);
gcS1ST->Latch1_bit3_count  = pS1ST->get_latch1_bit3_count(nrow);
gcS1ST->Latch1_bit4_count  = pS1ST->get_latch1_bit4_count(nrow);
gcS1ST->Latch1_bit5_count  = pS1ST->get_latch1_bit5_count(nrow);
gcS1ST->Latch1_bit6_count  = pS1ST->get_latch1_bit6_count(nrow);
gcS1ST->Latch1_bit7_count  = pS1ST->get_latch1_bit7_count(nrow);
gcS1ST->Latch1_bit8_count  = pS1ST->get_latch1_bit8_count(nrow);
gcS1ST->Latch1_bit9_count  = pS1ST->get_latch1_bit9_count(nrow);
gcS1ST->Latch1_bit10_count  = pS1ST->get_latch1_bit10_count(nrow);
gcS1ST->Latch1_bit11_count  = pS1ST->get_latch1_bit11_count(nrow);
gcS1ST->Latch1_bit12_count  = pS1ST->get_latch1_bit12_count(nrow);
gcS1ST->Event_count  = pS1ST->get_event_count(nrow);
gcS1ST->Latch1_zero_count  = pS1ST->get_latch1_zero_count(nrow);
gcS1ST->Latch1_empty_count  = pS1ST->get_latch1_empty_count(nrow);
gcS1ST->Latch1_not_empty_count  = pS1ST->get_latch1_not_empty_count(nrow);
gcS1ST->Latch1_ok_count  = pS1ST->get_latch1_ok_count(nrow);
gcS1ST->Level2_sector1  = pS1ST->get_level2_sector1(nrow);
gcS1ST->Level2_sector2  = pS1ST->get_level2_sector2(nrow);
gcS1ST->Level2_sector3  = pS1ST->get_level2_sector3(nrow);
gcS1ST->Level2_sector4  = pS1ST->get_level2_sector4(nrow);
gcS1ST->Level2_sector5  = pS1ST->get_level2_sector5(nrow);
gcS1ST->Level2_sector6  = pS1ST->get_level2_sector6(nrow);
gcS1ST->Level2_pass  = pS1ST->get_level2_pass(nrow);
gcS1ST->Level2_fail  = pS1ST->get_level2_fail(nrow);
gcS1ST->Latch2_zero_count  = pS1ST->get_latch2_zero_count(nrow);
gcS1ST->Latch2_empty_count  = pS1ST->get_latch2_empty_count(nrow);
gcS1ST->Latch2_not_empty_count  = pS1ST->get_latch2_not_empty_count(nrow);
gcS1ST->Latch2_ok_count  = pS1ST->get_latch2_ok_count(nrow);
gcS1ST->Roc_13_count  = pS1ST->get_roc_13_count(nrow);
gcS1ST->Roc_15_count  = pS1ST->get_roc_15_count(nrow);
gcS1ST->L1l2_zero_count  = pS1ST->get_l1l2_zero_count(nrow);
gcS1ST->L1zero_13_count  = pS1ST->get_l1zero_13_count(nrow);
gcS1ST->L2zero_13_count  = pS1ST->get_l2zero_13_count(nrow);
gcS1ST->L1l2zero_13_count  = pS1ST->get_l1l2zero_13_count(nrow);

}



////////////////////////////////////////////////////////////////////////////////////////
//     End Of File  Fill_S1ST_Bank.cc
//////////////////////////////////////////////////////////////////////////////////////

