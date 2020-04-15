c
c_begin_doc
c  RCS ID string
c  $Id: boscom.inc,v 1.3 2006/02/04 00:43:04 stepanya Exp $
c
c  Purpose:
c  --------
C      Internal COMMON/BCS/ for BOS system
c
c  Author:
c  -------
c     Volker Blobel          xxx Apr 15 15:00:00 EDT 1994
c
c  Major revisions:
c  ----------------
c     Serguei Boiarinov      Created:  Thu Oct 12 12:23:13 EDT 1995
c
c_end_doc
c_begin_var
c  variables for include file:
c  ---------------------------
c  RCS information:
      CHARACTER*(132)  CIBOSCOM
      DATA CIBOSCOM/
     1'$rcsId$'
     2/
c_end_var
      INTEGER     IW,JUNK
      COMMON /BCS/JUNK(5),IW(1000)
      SAVE   /BCS/

