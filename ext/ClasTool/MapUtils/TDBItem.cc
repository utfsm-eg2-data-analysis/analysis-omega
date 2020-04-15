// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TDBItem.cc,v 1.3 2007/03/01 22:27:00 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
// TDBItem
//
// This class contains one item from the database.
//


#include "TDBItem.h"

ClassImp(TDBItem)
  
  TDBItem::TDBItem(){
  // Defaulf Constructor
  //
  
}

TDBItem::~TDBItem(){
  // Defualt Destructor
  //
}

void TDBItem::Print(){
  // Prints out Current Item
  //
  cout << " Printing Item " << endl;
  cout << "ItemId  = " << fItemId << endl;
  cout << "fItemName " << fItemName << endl;
  cout << "fSubsystemId " << fSubsystemId << endl;
  cout << "fLength " << fLength << endl;
  cout << "fType " << fType << endl;
  cout << "fDescription " << fDescription << endl;
  cout << endl;
  
}
