// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TTBERClass.cc,v 1.5 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TTBERClass</h1>
<p>Use this class for accessing the error matrix provided by the tracking system
in RECSIS. As far as I know the only reason you would want this is for fancy fitting 
routines.
</p>
<pre>
<!-- ______________________________________________________________________*/ 
// --> End_Html
//
////////////////////////////////////////////////////////

#include "TTBERClass.h"

ClassImp(TTBERClass)


TTBERClass::TTBERClass(TTBERClass *TmpTBER)
{
  // Copy constructor
  // c=new TMatrixF( *TmpTBER->c);
  //
  q_over_p= TmpTBER->q_over_p;
  lambda  = TmpTBER->lambda  ;
  phi     = TmpTBER->phi     ;
  d0      = TmpTBER->d0      ;
  z0      = TmpTBER->z0      ;
  chi2    = TmpTBER->chi2    ;
  layinfo1= TmpTBER->layinfo1;
  layinfo2= TmpTBER->layinfo2;

  c11 = TmpTBER->c11;
  c12 = TmpTBER->c12;
  c13 = TmpTBER->c13;
  c14 = TmpTBER->c14;
  c15 = TmpTBER->c15;
  c22 = TmpTBER->c22;
  c23 = TmpTBER->c23;
  c24 = TmpTBER->c24;
  c25 = TmpTBER->c25;
  c33 = TmpTBER->c33;
  c34 = TmpTBER->c34;
  c35 = TmpTBER->c35;
  c44 = TmpTBER->c44;
  c45 = TmpTBER->c45;
  c55 = TmpTBER->c55;

}

    
TMatrixF TTBERClass::Get_ErrMatrix(){
  //
  // Creates a TMatrixF, fills it with the error matrix
  // and then returns a reference to the new matrix.
  //
  //
  // NOTE: This can be quite inefficient! Consider useing the
  // other forms of Get_ErrMatrix which fill but don't create
  // an new Matrix!
  //  
  TMatrixF c(5,5);
  Get_ErrMatrix(&c);
  return(c);
}

void TTBERClass::Get_ErrMatrix(TMatrixF *f){
  // Fill the matrix being pointed to with the tracking 
  // error information. Note that locally this information
  // is NOT stored as a Matrix, to save storage space.
  // So the contends is copied over.
#define M (*f)
  M(0,0) = c11;
  M(0,1) = c12;
  M(0,2) = c13;
  M(0,3) = c14;
  M(0,4) = c15;

  M(1,0) = c12;
  M(1,1) = c22;
  M(1,2) = c23;
  M(1,3) = c24;
  M(1,4) = c25;

  M(2,0) = c13;
  M(2,1) = c23;
  M(2,2) = c33;
  M(2,3) = c34;
  M(2,4) = c35;

  M(3,0) = c14;
  M(3,1) = c24;
  M(3,2) = c34;
  M(3,3) = c44;
  M(3,4) = c45;

  M(4,0) = c15;
  M(4,1) = c25;
  M(4,2) = c35;
  M(4,3) = c45;
  M(4,4) = c55;
}

void TTBERClass::Get_ErrMatrix(TMatrixF &f){
  // Fill the matrix being referenced to with the tracking 
  // error information. Note that locally this information
  // is NOT stored as a Matrix, to save storage space.
  // So the contends is copied over.
  //
  // Note: This just calls Get_ErrMatrix(TMatrix *f).

  Get_ErrMatrix(&f);
}


void TTBERClass::Print(void)
{
  // Print information about the contents of this class.
  //

  cout << "TTBERClass ::" << endl;
  cout << "q_over_p   = " << q_over_p << endl;
  cout << "lambda     = " << lambda  << endl;
  cout << "phi        = " << phi     << endl;
  cout << "d0         = " << d0      << endl;
  cout << "z0         = " << z0      << endl;
  cout << "chi2       = " << chi2    << endl;
  cout << "layinfo1   = " << layinfo1<< endl;
  cout << "layinfo2   = " << layinfo2<< endl;
  cout << "Error Matrix:" << endl;
  TMatrixF c(5,5);
  Get_ErrMatrix(&c);
  c.Print();
}
