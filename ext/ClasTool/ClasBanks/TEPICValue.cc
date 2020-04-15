// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TEPICValue.cc,v 1.2 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TEPICValue</h1>
<pre>
Modifications:
           Maurik (7/05) Comments.
</pre>
This class is part of the sytem to access the EPIC data stored in the
(RAW only!) BOS file. See TEPICclass for more detail. This is 
just a sortable container for a name and a value.
<pre>
<!-- ______________________________________________________________________*/ 
// --> End_Html

////////////////////////////////////////////////////////

#include "TEPICValue.h"

ClassImp(TEPICValue)

TEPICValue::TEPICValue(TEPICValue *tmp){
  // Copy constructor.
  fName=tmp->fName;
  fValue=tmp->fValue;
}

void TEPICValue::Print(){
  //
  // Print the name and value.
  // 
  cout << "TEPICValue: Name:" << fName << " Value: " << fValue << endl;
} 

Int_t TEPICValue::Compare(const TObject *obj) const{
  //
  // Compare the name of this TEPICValue with the obj->GetName name 
  // of the object (which can be another TEPICValue).
  //
  return (fName.CompareTo((const char*)obj->GetName()));
}
