c      include file REVERSION
c
c_begin_doc
c  RCS ID string
c  $Id: reversion.inc,v 1.3 2006/02/04 00:44:56 stepanya Exp $
c
c  Documentation for include file REVERSION
c
c  Purpose:  contains the data bank information for retaining job information
c  --------
c
c  Used in routines: revers.F and revini.F
c  ----------------
c
c  Notes:  A call to revini.F sets the package name and version number
c  ------  A call to revers.F creates the DBBK bos bank
c
c  Author:   Arne Freyberger      Created:  Tue Apr 11 09:50:53 EDT 1995
c  -------
c
c  Major revisions:
c  ----------------
c
c_end_doc
c
c
c  Remember NO NESTED INCLUDES
c
c  COMMON BLOCK NAME should be the same as include file name!
c
c_begin_var
c  variables for include file REVERSION:
c  -----------------------------------
c  RCS information: 
      CHARACTER*(132)  CIREVERSION
      DATA CIREVERSION/
     1'$Id: reversion.inc,v 1.3 2006/02/04 00:44:56 stepanya Exp $'
     2/
c  
c  Variables contained in REVERSION common block
c  --------------------------------------------
c
c_end_var
       INTEGER MAXPACK
       PARAMETER ( MAXPACK = 30 )
       CHARACTER*8 JOBUSRNM, JOBEXE, JOBMACH, GLOBVER
       CHARACTER*40 INPUTDEV, OUTPUTDEV, JOBSCRIPT
       CHARACTER*4 CPACK, VPACK
       CHARACTER*16 JOBDATE
       CHARACTER*20 DPACK
       INTEGER NPACKAGES, NSEQ
       COMMON/REVERSION/JOBDATE, JOBUSRNM, JOBEXE, JOBMACH, GLOBVER,
     1                  INPUTDEV, OUTPUTDEV, JOBSCRIPT, 
     2                  NPACKAGES, NSEQ,
     3                  VPACK(MAXPACK), CPACK(MAXPACK), DPACK(MAXPACK)
       SAVE/REVERSION/
c------------------------------------------------------------------------------
















