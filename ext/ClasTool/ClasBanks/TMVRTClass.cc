// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TMVRTClass.cc,v 1.2 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TMVRTClass</h1>
<pre>
Modifications:
</pre>
This class is used to access the MVRT bank data written into the ROOT DST by WriteRootDST.
This bank stores a fitted vertex that is derived by a fit to all the
(reasonable?) tracks. This is done in the vertex package, see packages/vertex/
<pre>
______________________________________________________________________*/ 
//End_Html

////////////////////////////////////////////////////////

#include "TMVRTClass.h"

ClassImp(TMVRTClass)

TMVRTClass::TMVRTClass(TMVRTClass *TmpMVRT){
  v_id   = TmpMVRT->v_id;
  ntrk   = TmpMVRT->ntrk;
  x      = TmpMVRT->x;
  y      = TmpMVRT->y;
  z      = TmpMVRT->z;
  chi2   = TmpMVRT->chi2;
  cxx    = TmpMVRT->cxx;
  cxy    = TmpMVRT->cxy;
  cxz    = TmpMVRT->cxz;
  cyy    = TmpMVRT->cyy;
  cyz    = TmpMVRT->cyz;
  czz    = TmpMVRT->czz;
  stat   = TmpMVRT->stat;
}

void   TMVRTClass::Print(){
cout << "v_id   " << v_id    << endl;
cout << "ntrk   " << ntrk    << endl;
cout << "x      " << x       << endl;
cout << "y      " << y       << endl;
cout << "z      " << z       << endl;
cout << "chi2   " << chi2    << endl;
cout << "cxx    " << cxx     << endl;
cout << "cxy    " << cxy     << endl;
cout << "cxz    " << cxz     << endl;
cout << "cyy    " << cyy     << endl;
cout << "cyz    " << cyz     << endl;
cout << "czz    " << czz     << endl;
cout << "stat   " << stat    << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TMVRTClass.cc
////////////////////////////////////////////////////////////////
