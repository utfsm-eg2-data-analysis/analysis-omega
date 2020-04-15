c      include file BCSPARM
c
c_begin_doc
c  RCS ID string
c  $Id: bcsparm.inc,v 1.5 2006/02/04 00:42:56 stepanya Exp $
c
c  Documentation for include file BCSPARM
c
c  Purpose:
c  --------
c
c  Used in routines:
c  ----------------
c
c  Notes:
c  ------
c
c  Author:   Arne Freyberger      Created:  Fri Apr  7 10:41:53 EDT 1995
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
c  variables for include file BCSPARM:
c  -----------------------------------
c  RCS information: 
      CHARACTER*132 CIBCSPARM
      DATA CIBCSPARM/
     1'$Id: bcsparm.inc,v 1.5 2006/02/04 00:42:56 stepanya Exp $'
     2/
c  
c  Variables contained in BCSPARM common block
c  --------------------------------------------
c
       CHARACTER*4 HEAD_NAME
       INTEGER HEAD_REC, HEAD_RUN, HEAD_EVT
       PARAMETER ( HEAD_NAME='HEAD' )
       PARAMETER ( HEAD_REC = 0 )
       PARAMETER ( HEAD_RUN = 2 )
       PARAMETER ( HEAD_EVT = 3 )
c
       INTEGER NSECSAV, NRECLIM
       PARAMETER ( NSECSAV = 5 )
       PARAMETER ( NRECLIM = 0 )
c
       INTEGER FPACKIN, FPACKOUT
       CHARACTER*100 FCLASIN, FCLASOUT
       PARAMETER ( FPACKIN = 1)
       PARAMETER ( FPACKOUT = 2 )
       PARAMETER ( FCLASIN = 'CLASINPUT' )
       PARAMETER ( FCLASOUT = 'CLASOUTPUT' )

       INTEGER NBNAMES
       PARAMETER (NBNAMES = 1000)
c_end_var
c------------------------------------------------------------------------------




