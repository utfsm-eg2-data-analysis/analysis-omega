c      include file WCS
c
c_begin_doc
c  RCS ID string
c  $Id: wcs.inc,v 1.6 2006/02/04 00:46:13 stepanya Exp $
c
c  Documentation for include file WCS
c
c  Purpose:  Contains the BOS Work Common Space (WCS).  This is 
c  --------  initialize in RECINI
c
c  Used in routines:
c  ----------------
c
c  Notes:
c  ------
c
c  Author:   Arne Freyberger      Created:  Wed Apr  5 09:54:09 EDT 1995
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
c  variables for include file WCS:
c  -----------------------------------
c  RCS information: 
      CHARACTER*(132)  CIWCS
      DATA CIWCS/
     1'$Id: wcs.inc,v 1.6 2006/02/04 00:46:13 stepanya Exp $'
     2/
c  
c  Variables contained in WCS common block
c  --------------------------------------------
c
c_end_var
c
       INTEGER NWBCS
       PARAMETER ( NWBCS = 700000 )

      INTEGER JW, PAD_WCS
      REAL RJW(Nwbcs)
      INTEGER*2 JW16(2*Nwbcs)
      EQUIVALENCE (JW(1),RJW(1),JW16(1))
c 
c JWCOL and JWROW provide a quick way to find the number of columns
c and rows for a particular bank
c
c
      COMMON/WCS/PAD_WCS(5),JW(Nwbcs)
      INTEGER JWROW(Nwbcs), JWCOL(Nwbcs), JWNAME(Nwbcs), JWNR(Nwbcs), 
     1        JWNXT(Nwbcs)
      EQUIVALENCE (JW(1), JWCOL(6))
      EQUIVALENCE (JW(1), JWROW(5))
      EQUIVALENCE (JW(1), JWNAME(4))
      EQUIVALENCE (JW(1), JWNR(3))
      EQUIVALENCE (JW(1), JWNXT(2))
c
c
      save /WCS/
c----6----------------------------------------------------------------72




