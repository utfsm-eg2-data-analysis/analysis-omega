// @(#)ClasTool/TStoreClone:$Name:  $:$Id: TStoreClone.cc,v 1.1 2007/04/05 19:55:26 holtrop Exp $

/****************************************************************************
 * Copyright (C) CopyLeft  This code is freely available to all. *
 *                                                                          *
 * Documentation  : TStoreClone.html                                        *
 *                  (available also at:                                     *
 *                   http://www.physics.unh.edu/maurik/ClasTool)            *
 * Created on     :  04/2/2002 (UNH)                                        *
 * Initial Authors:  Maurik Holtrop (UNH) Gagik Gavalian (UNH)              *
 ***************************************************************************/

// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TStoreClone</h1>
<pre>
  Created:   4/2007   Maurik Holtrop UNH
</pre>
<p>
This class is a sub-class of TClasTool. This class stores a name and a TClonesArray. 
It is constructed in such a way that the class becomes an object that can be stored in
a THashTable or THashList, allow fast lookup. <br>
</p>
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////////////////////////////

#include "TStoreClone.h"

ClassImp(TStoreClone) 
