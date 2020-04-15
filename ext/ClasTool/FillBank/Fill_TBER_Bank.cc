//////////////////////////////////////////////////////////////
//
//   File Fill_TBER_Bank.cc
//
//   This procedure Fills TTBERClass class from BOS Bank 
//
//  Author :  Maurik Holtrop UNH 8/5/05
//
//////////////////////////////////////////////////////////////


#include "TROOT.h"
#include "TTBERClass.h"

#include "clasbanks.h"


// Function Prototype 
void  Fill_TBER_Bank(TTBERClass *gcTBER,TBER *pTBER , int nrow);


void  Fill_TBER_Bank(TTBERClass *gcTBER,TBER *pTBER , int nrow){
  //
  // Fill the TTBERClass from the BOS file. 
  // Note: In the BOS file, only unique elements were kept and since the
  // error matrix is diagonal 5x5 matrix, this saves 0+1+2+3+4=10 floats.
  // We count on compression and ease of use, and store these 10 numbers
  // twice in the root version.
  //
  gcTBER->q_over_p  = pTBER->get_q_over_p(nrow);
  gcTBER->lambda  = pTBER->get_lambda(nrow);
  gcTBER->phi  = pTBER->get_phi(nrow);
  gcTBER->d0  = pTBER->get_d0(nrow); // Mod(3/4/00) MWH - DCPB was changed by Stepan.
  gcTBER->z0  = pTBER->get_z0(nrow);
  gcTBER->chi2  = pTBER->get_chi2(nrow);
  gcTBER->layinfo1  = pTBER->get_layinfo1(nrow);
  gcTBER->layinfo2  = pTBER->get_layinfo2(nrow);

  //
  // Notes: TMatrix documention is best in the "User Guide" section of the
  // root website: http://root.cern.ch/root/doc/RootDoc.html
  // It there recommends to access the matrix elements by column or row. If you
  // try gcTBER->c(0,0) etc the compiler gets confused about what you want.
  //
  // Note also that leaving the 10 duplicate entries zero saves you only about
  // 4.5 MBytes out of roughly 78 MBytes (the TBER component of a single EG2 run file.
  // The same run with TBER is 234 MBytes with the TBER bank and 156 MBytes without.
  // 


  // TMatrixColumn c0(*gcTBER->c,0);
  //   TMatrixColumn c1(*gcTBER->c,1);
  //   TMatrixColumn c2(*gcTBER->c,2);
  //   TMatrixColumn c3(*gcTBER->c,3);
  //   TMatrixColumn c4(*gcTBER->c,4);
  
  //   c0(0) = pTBER->get_c11(nrow);
  //   c0(1) = pTBER->get_c12(nrow);
  //   c0(2) = pTBER->get_c13(nrow);
  //   c0(3) = pTBER->get_c14(nrow);
  //   c0(4) = pTBER->get_c15(nrow);
  //   c1(0) = pTBER->get_c12(nrow);
  //   c1(1) = pTBER->get_c22(nrow);
  //   c1(2) = pTBER->get_c23(nrow);
  //   c1(3) = pTBER->get_c24(nrow);
  //   c1(4) = pTBER->get_c25(nrow);
  //   c2(0) = pTBER->get_c13(nrow);
  //   c2(1) = pTBER->get_c23(nrow);
  //   c2(2) = pTBER->get_c33(nrow);
  //   c2(3) = pTBER->get_c34(nrow);
  //   c2(4) = pTBER->get_c35(nrow);
  //   c3(0) = pTBER->get_c14(nrow);
  //   c3(1) = pTBER->get_c24(nrow);
  //   c3(2) = pTBER->get_c34(nrow);
  //   c3(3) = pTBER->get_c44(nrow);
  //   c3(4) = pTBER->get_c45(nrow);
  //   c4(0) = pTBER->get_c15(nrow);
  //   c4(1) = pTBER->get_c25(nrow);
  //   c4(2) = pTBER->get_c35(nrow);
  //   c4(3) = pTBER->get_c45(nrow);
  //   c4(4) = pTBER->get_c55(nrow);
  
  gcTBER->c11=pTBER->get_c11(nrow);
  gcTBER->c12=pTBER->get_c12(nrow);
  gcTBER->c13=pTBER->get_c13(nrow);
  gcTBER->c14=pTBER->get_c14(nrow);
  gcTBER->c15=pTBER->get_c15(nrow);
  gcTBER->c12=pTBER->get_c12(nrow);
  gcTBER->c22=pTBER->get_c22(nrow);
  gcTBER->c23=pTBER->get_c23(nrow);
  gcTBER->c24=pTBER->get_c24(nrow);
  gcTBER->c25=pTBER->get_c25(nrow);
  gcTBER->c13=pTBER->get_c13(nrow);
  gcTBER->c23=pTBER->get_c23(nrow);
  gcTBER->c33=pTBER->get_c33(nrow);
  gcTBER->c34=pTBER->get_c34(nrow);
  gcTBER->c35=pTBER->get_c35(nrow);
  gcTBER->c14=pTBER->get_c14(nrow);
  gcTBER->c24=pTBER->get_c24(nrow);
  gcTBER->c34=pTBER->get_c34(nrow);
  gcTBER->c44=pTBER->get_c44(nrow);
  gcTBER->c45=pTBER->get_c45(nrow);
  gcTBER->c15=pTBER->get_c15(nrow);
  gcTBER->c25=pTBER->get_c25(nrow);
  gcTBER->c35=pTBER->get_c35(nrow);
  gcTBER->c45=pTBER->get_c45(nrow);
  gcTBER->c55=pTBER->get_c55(nrow);
}
