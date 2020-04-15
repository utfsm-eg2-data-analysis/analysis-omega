c      include file RTCLMES
c
c_begin_doc
c  RCS ID string
c  $Id: rtclmes.inc,v 1.3 2006/02/04 00:45:02 stepanya Exp $
c
c  Documentation for include file RTCLMES
c
c  Purpose:  holds a character string CTCL_BUFF in common for TCL
c  --------  to look at and modify
c
c  Used in routines:  retcl_mes.F
c  ----------------
c
c  Notes:
c  ------
c
c  Author:   Arne Freyberger      Created:  Wed Oct  2 11:19:34 EDT 1996
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
c  variables for include file RTCLMES:
c  -----------------------------------
c  RCS information: 
      CHARACTER*(132)  CIRTCLMES
      DATA CIRTCLMES/
     1'$Id: rtclmes.inc,v 1.3 2006/02/04 00:45:02 stepanya Exp $'
     2/
c----6----------------------------------------------------------------72
c  
c  Variables contained in RTCLMES common block
c  --------------------------------------------
c
c_end_var
c
c----6----------------------------------------------------------------72

c  CTCL_BUFF*10000   holds a buffer of messages that are  linked to Tcl

       CHARACTER*10000 CTCL_BUFF

       COMMON/RTCLMES/CTCL_BUFF




