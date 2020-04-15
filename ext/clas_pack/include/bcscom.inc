c
c_begin_doc
c  RCS ID string
c  $Id: bcscom.inc,v 1.5 2006/08/02 17:31:06 hovanes Exp $
c
c  Purpose:
c  --------
C      main BOS system COMMON block
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
      CHARACTER*(132)  CIBCS
      DATA CIBCS/
     1'$rcsId$'
     2/
c_end_var
      INTEGER          NBCS
      PARAMETER     (  NBCS=700000)
      INTEGER   IW,JUNK
      REAL      RW  (  NBCS)
      INTEGER*2 IW16(2*NBCS)
      BYTE IW08(4*Nbcs)
      COMMON /BCS/ JUNK(5),IW(NBCS)
      EQUIVALENCE (IW(1),RW(1),IW08(1),IW16(1))
      SAVE   /BCS/
