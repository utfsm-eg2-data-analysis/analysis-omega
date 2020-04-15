c      include file SCAT_CONTROL
c
c_begin_doc
c  RCS ID string
c  $Id: scat_control.inc,v 1.3 2006/02/04 00:45:10 stepanya Exp $
c
c  Documentation for include file SCAT_CONTROL
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
c  Author:   Arne Freyberger      Created:  Fri Mar  8 13:59:37 EST 1996
c  -------
c
c  Major revisions:
c  ----------------
c  JAM - add some comments so I'll know what these vars do.
c
c_end_doc
c
c  Remember NO NESTED INCLUDES
c
c  COMMON BLOCK NAME should be the same as include file name!
c
c_begin_var
c  variables for include file SCAT_CONTROL:
c  -----------------------------------
c  RCS information: 
      CHARACTER*(132)  CISCAT_CONTROL
      DATA CISCAT_CONTROL/
     1'$Id: scat_control.inc,v 1.3 2006/02/04 00:45:10 stepanya Exp $'
     2/
c----6----------------------------------------------------------------72
c  
c  Variables contained in SCAT_CONTROL common block
c  --------------------------------------------
c
c
c
c      scat_host = fill this with the name of the host
c                  you want to send events to. Used in 
c                  Scat_InitHandle.
c      scat_name = this is the unique (If u want) name of the
c                  program u are running. Arne fills this now.
c      scat_handle = use this in all scat calls. Associates this 
c                  program with a one unique comm partner (could
c                  be more than one partner - but for now just one)
c      scat_pgm_no = used internal to scat.
c      scat_ver_no = internal to scat.
c      scat_debug  : set to non-zero for debug output from SCAT
c      lscat       : (default = false) turn on/off communications 
c
       integer nhandle
       parameter (nhandle = 2)
c
       CHARACTER*20 SCAT_HOST
       CHARACTER*132 SCAT_NAME, SCAT_PROG_START, SCAT_QUALIFIER
       INTEGER SCAT_PGM_NO, SCAT_VER _NO, SCAT_HANDLE, scat_debug
       LOGICAL LSCAT
c
c_end_var
c
       COMMON/SCAT_CONTROL/scat_handle(nhandle), scat_pgm_no, 
     1                     scat_ver_no, 
     1                     scat_name, SCAT_PROG_START,
     2                     scat_qualifier, scat_host, scat_debug,
     3                     LSCAT
c----6----------------------------------------------------------------72




