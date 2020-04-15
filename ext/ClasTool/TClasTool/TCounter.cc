// @(#)ClasTool/TCounter:$Name:  $:$Id: TCounter.cc,v 1.2 2007/03/01 22:27:00 holtrop Exp $
// Author: Maurik Holtrop <http://www.physics.unh.edu/~maurik>

/****************************************************************************
 * Copyright (C) CopyLeft  This code is freely available to all. *
 *                                                                          *
 * Documentation  : TCounter.html                                           *
 *                  (available also at:                                     *
 *                   http://www.physics.unh.edu/maurik/ClasTool)            *
 * Created on     :  1999 (UNH)                                             *
 * Initial Authors:  Maurik Holtrop (UNH)                                   *
 ***************************************************************************/

// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
</pre><H1> TCounter </H1>
<p>Created at UNH by <b><i><a href="http://www.physics.unh.edu/~maurik">Maurik Holtrop</a></b></i>.
<p>
This class is a simple counter, that helps you keep track of the various cuts you make
in your data analysis. Sure, there are other ways to count, but this can simplify your 
code.</p>
Ideally you actually use the TCounterCol class, which maintains a collection of counters and
facilitates an easy way to print out the resulting counts of your cuts, and allows you to
neatly store all the counts together with your histograms in a root file. Ultimately, the 
ease of storing the results is what makes this worth using.</p>
<p>
Additional information about this package, including an overview, can be found at the
<a href="http://www.physics.unh.edu/~maurik/ClasTool">ClasTool Documentation</a> web pages.
</p>
<pre> 
<!-- */ 
// --> End_Html   

#include "TCounter.h"

ClassImp(TCounter)
  // OK, all of it is done in the header!

