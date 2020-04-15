c
c_begin_doc
c  RCS ID string
c  $Id: bossys.inc,v 1.3 2006/02/04 00:43:06 stepanya Exp $
c
c  Purpose:
c  --------
C      Internal COMMON/BOSSYS/ for BOS system
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
      CHARACTER*(132)  CIBOSSYS
      DATA CIBOSSYS/
     1'$rcsId$'
     2/
c_end_var
C
C     NSYST        NUMBER OF SYSTEM WORDS IN EACH ARRAY
C     NAMES        MAX. NUMBER OF NAMES
C     NPRIM        PRIME NUMBER FOR HASH SEARCH
C     IDNAM        INDEX OF WORK BANK WITH NAMES
C     IDPTR        INDEX OF WORK BANK WITH POINTERS
C     IDFMT        INDEX OF WORK BANK WITH FORMAT INDICES
C     NDUMM        -
C     NRESR        NUMBER OF RESERVED WORDS (WBANK)
C     NLPLM        NUMBER OF BANKS FOR GIVEN NAME WITHOUT LINK BANK
C     NARR         NUMBER OF INITIALIZED ARRAYS
C     IARR(10)     ARRAY ADRESSES
C     IEFMT        ERROR FLAG FOR FORMATS
C     TLEFT        TIME LEFT AT START OF BOS
C     LEPIO        INIT FLAG FOR EPIO PACKAGE
C     NAMI         NAME INDEX
C     INDI         LAST INDEX
C     INDJ         INDEX ORIGIN OF INDI
C     INTA(200)    INTERMEDIATE ARRAY
C
      INTEGER        NSYST,NAMES,NPRIM,IDNAM,IDPTR,IDFMT,NDUMM,NRESR,
     &               NLPLM, NARR,IARR,IEFMT,TLEFT,LEPIO,NAMI,INDI,
     &               INDJ,IBC,DUMMI,INTA,NPTR,NRUN,NEVT,
     &               LUNDAT,LUNSEL,LUNSE2,LUTDAT,MASKR,LMASK,NRE,
     &               NAMERE,NUMMRE,IRUNRE,IEVTRE
      COMMON /SYSBOS/NSYST,NAMES,NPRIM,IDNAM,IDPTR,IDFMT,NDUMM,NRESR,
     &               NLPLM, NARR,IARR(10),IEFMT,TLEFT,LEPIO,NAMI,INDI,
     &               INDJ,IBC,DUMMI(73),INTA(200),NPTR,NRUN,NEVT,
     &               LUNDAT,LUNSEL,LUNSE2,LUTDAT,MASKR,LMASK,NRE,
     &               NAMERE(3),NUMMRE(3),IRUNRE(3),IEVTRE(3)
      SAVE   /SYSBOS/

