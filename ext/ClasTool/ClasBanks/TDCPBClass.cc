// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TDCPBClass.cc,v 1.4 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TDCPBClass</h1>
<pre>
Modifications:
           Maurik (2/3/00) Comments.
           Maurik (3/4/00) Changed the variables and comments according to 
           the changes to the comments and var name in DCPB Stepan.

</pre>
This class is used to access the DCPB 
bank data written into the ROOT DST by WriteRootDST.
It was generated automatically from the ddl file in 
packages/bankdefs/dcpb.ddl
and later hand edited to provide comments and additional modifications.
The details on how exactly each variable is defined have to be extraced
from the RECSIS code.

<pre>
______________________________________________________________________*/ 
//End_Html

////////////////////////////////////////////////////////

#include "TDCPBClass.h"

ClassImp(TDCPBClass)

TDCPBClass::TDCPBClass(TDCPBClass *TmpDCPB){
Sctr   =   TmpDCPB->Sctr;
X_sc   =   TmpDCPB->X_sc;
Y_sc   =   TmpDCPB->Y_sc;
Z_sc   =   TmpDCPB->Z_sc;
Cx_sc   =   TmpDCPB->Cx_sc;
Cy_sc   =   TmpDCPB->Cy_sc;
Cz_sc   =   TmpDCPB->Cz_sc;
X_ec   =   TmpDCPB->X_ec;
Y_ec   =   TmpDCPB->Y_ec;
Z_ec   =   TmpDCPB->Z_ec;
Th_cc   =   TmpDCPB->Th_cc;
Chi2   =   TmpDCPB->Chi2;
Status   =   TmpDCPB->Status;
}

void   TDCPBClass::Print(){
cout << "ScTr      " <<  Sctr  << endl;
cout << "x_SC      " <<  X_sc  << endl;
cout << "y_SC      " <<  Y_sc  << endl;
cout << "z_SC      " <<  Z_sc  << endl;
cout << "CX_SC     " <<  Cx_sc  << endl;
cout << "CY_SC     " <<  Cy_sc  << endl;
cout << "CZ_SC     " <<  Cz_sc  << endl;
cout << "X_v (X_ec)" <<  X_ec  << endl;
cout << "Y_v (Y_ec)" <<  Y_ec  << endl;
cout << "Z_v (Z_ec)" <<  Z_ec  << endl;
cout << "R_v(Th_cc)" <<  Th_cc  << endl;
cout << "Chi2      " <<  Chi2  << endl;
cout << "Status    " <<  Status  << endl;
}


////////////////////////////////////////////////////////////////
//
//  End of File  TDCPBClass.cc
////////////////////////////////////////////////////////////////
