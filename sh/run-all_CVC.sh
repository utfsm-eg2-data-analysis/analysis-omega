#!/bin/bash

# run all available CheckVertexCuts routines!

# old C
sh $PRODIR/sh/run_CVC.sh old C gsim
sh $PRODIR/sh/run_CVC.sh old C simrec
sh $PRODIR/sh/run_CVC.sh old C simrec 0  
sh $PRODIR/sh/run_CVC.sh old C simrec 1  
sh $PRODIR/sh/run_CVC.sh old C simrec 2  
sh $PRODIR/sh/run_CVC.sh old C simrec 3  
sh $PRODIR/sh/run_CVC.sh old C simrec 4  
sh $PRODIR/sh/run_CVC.sh old C simrec 5 

# old Fe
sh $PRODIR/sh/run_CVC.sh old Fe gsim
sh $PRODIR/sh/run_CVC.sh old Fe simrec
sh $PRODIR/sh/run_CVC.sh old Fe simrec 0  
sh $PRODIR/sh/run_CVC.sh old Fe simrec 1  
sh $PRODIR/sh/run_CVC.sh old Fe simrec 2  
sh $PRODIR/sh/run_CVC.sh old Fe simrec 3  
sh $PRODIR/sh/run_CVC.sh old Fe simrec 4  
sh $PRODIR/sh/run_CVC.sh old Fe simrec 5 

# usm D
sh $PRODIR/sh/run_CVC.sh usm D gsim
sh $PRODIR/sh/run_CVC.sh usm D simrec
sh $PRODIR/sh/run_CVC.sh usm D simrec 0  
sh $PRODIR/sh/run_CVC.sh usm D simrec 1  
sh $PRODIR/sh/run_CVC.sh usm D simrec 2  
sh $PRODIR/sh/run_CVC.sh usm D simrec 3  
sh $PRODIR/sh/run_CVC.sh usm D simrec 4  
sh $PRODIR/sh/run_CVC.sh usm D simrec 5 

# usm C
sh $PRODIR/sh/run_CVC.sh usm C gsim
sh $PRODIR/sh/run_CVC.sh usm C simrec
sh $PRODIR/sh/run_CVC.sh usm C simrec 0  
sh $PRODIR/sh/run_CVC.sh usm C simrec 1  
sh $PRODIR/sh/run_CVC.sh usm C simrec 2  
sh $PRODIR/sh/run_CVC.sh usm C simrec 3  
sh $PRODIR/sh/run_CVC.sh usm C simrec 4  
sh $PRODIR/sh/run_CVC.sh usm C simrec 5 

# usm Fe
sh $PRODIR/sh/run_CVC.sh usm Fe gsim
sh $PRODIR/sh/run_CVC.sh usm Fe simrec
sh $PRODIR/sh/run_CVC.sh usm Fe simrec 0  
sh $PRODIR/sh/run_CVC.sh usm Fe simrec 1  
sh $PRODIR/sh/run_CVC.sh usm Fe simrec 2  
sh $PRODIR/sh/run_CVC.sh usm Fe simrec 3  
sh $PRODIR/sh/run_CVC.sh usm Fe simrec 4  
sh $PRODIR/sh/run_CVC.sh usm Fe simrec 5 

# usm Pb
sh $PRODIR/sh/run_CVC.sh usm Pb gsim
sh $PRODIR/sh/run_CVC.sh usm Pb simrec
sh $PRODIR/sh/run_CVC.sh usm Pb simrec 0  
sh $PRODIR/sh/run_CVC.sh usm Pb simrec 1  
sh $PRODIR/sh/run_CVC.sh usm Pb simrec 2  
sh $PRODIR/sh/run_CVC.sh usm Pb simrec 3  
sh $PRODIR/sh/run_CVC.sh usm Pb simrec 4  
sh $PRODIR/sh/run_CVC.sh usm Pb simrec 5 
