c      include file CLASMDL
c
c_begin_doc
c  RCS ID string
c  $Id: clasmdl.inc,v 1.9 2006/02/04 00:43:24 stepanya Exp $
c
c  Documentation for include file CLASMDL
c
c  Purpose:  Contains the common block used for steering the job control
c  --------  within CLAS
c
c  Used in routines:
c  ----------------
c
c  Notes:
c  ------
c
c  Author:   Arne Freyberger      Created:  Wed Feb 22 13:12:00 EST 1995
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
c  variables for include file CLASMDL:
c  -----------------------------------
c  RCS information: 
      CHARACTER*(132)  CICLASMDL
      DATA CICLASMDL/
     1'$Id: clasmdl.inc,v 1.9 2006/02/04 00:43:24 stepanya Exp $'
     2/
c  
c  Variables contained in CLASMDL common block
c  --------------------------------------------
c
c_end_var
c
       INTEGER NTRIG
       PARAMETER ( NTRIG = 21 )
c
       LOGICAL BEGJOB, ENDRUN, BEGRUN, REVENT, ENDJOB, OTHDAT,
     1         LINTER, lscaler, lepics
       INTEGER VERSION, LCCRUN,  NCCRUN, NEVENT, EVTIME, EVTYPE
       INTEGER ROCSTAT, EVTWGHT, EVTCLAS,PHYSTYP,
     1         ITALLY, ITALLY_MISSED, TEVENT, TRUN, TREC,
     2         NCREVT, TEVENT_SKIP, TEVENT_SEEN, ITALLY_SKIPED,
     3         prev_event
       REAL CPUSUM
c
       COMMON/CLASMDL/BEGJOB, ENDRUN, BEGRUN,REVENT, ENDJOB, OTHDAT,
     2                VERSION, LCCRUN, NCCRUN, NEVENT, EVTIME, EVTYPE,
     3                ROCSTAT, EVTWGHT, EVTCLAS,
     4                PHYSTYP(NTRIG),ITALLY(NTRIG), CPUSUM(NTRIG+2),
     5                ITALLY_MISSED(NTRIG),TEVENT,TRUN,TREC,NCREVT,
     6                TEVENT_SKIP, TEVENT_SEEN, ITALLY_SKIPED(21),
     7                LINTER, lscaler, lepics, prev_event
       SAVE /CLASMDL/
c
c
c------------------------------------------------------------------------------
