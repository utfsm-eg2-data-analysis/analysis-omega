// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TVERTClass.cc,v 1.2 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TVERTClass</h1>
<pre>
Modifications:
           Maurik (3/6/05) Comments.

</pre>
<p>This class is used to access the VERT bank data written into the ROOT DST by WriteRootDST.
The VERT bank contains a calculated vertex. The calculation uses 
the midpoint of the shortest line segment between 2 straigt tracks
as the vertex. The DOCA (distance of closest approach, or separation
distance) is the length of that line segment.</p>
<p>More information of how this can be calculated is found
in <a href="http://physics.unh.edu/~maurik/ClasTool/Vertex.html>my writeup </a></p>
which includes a derivation of the formulas.</p>
Note: A track index of 0 indicates that this is the BEAM.
<pre>
______________________________________________________________________*/ 
//End_Html

////////////////////////////////////////////////////////

#include "TVERTClass.h"

ClassImp(TVERTClass)

TVERTClass::TVERTClass(TVERTClass *TmpVERT){
vertex   =   TmpVERT->vertex;
trk1   =   TmpVERT->trk1;
trk2   =   TmpVERT->trk2;
x      =   TmpVERT->x;
y      =   TmpVERT->y;
z      =   TmpVERT->z;
sepd   =   TmpVERT->sepd;
}

void   TVERTClass::Print(){
cout << "vertex " << vertex  << endl;
cout << "trk1   " << trk1    << endl;
cout << "trk2   " << trk2    << endl;
cout << "x      " << x       << endl;
cout << "y      " << y       << endl;
cout << "z      " << z       << endl;
cout << "sepd   " << sepd    << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TVERTClass.cc
////////////////////////////////////////////////////////////////
