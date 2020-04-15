c      include file BNKFMT
c
c_begin_doc
c  RCS ID string
c  $Id: bnkfmt.inc,v 1.10 2008/03/16 04:33:20 fklein Exp $
c
c  Documentation for include file BNKFMT
c
c  Purpose:  contains an array of ALL the BANK NAMES defined by the ddl file
c  --------  and their associated FORMATS, used to communicate this information
c            to the event store buffer
c
c  Used in routines:
c  ----------------
c
c  Notes:
c  ------
c
c  Author:   Arne Freyberger      Created:  Mon Mar 11 15:32:28 EST 1996
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
c  variables for include file BNKFMT:
c  -----------------------------------
c  RCS information: 
      CHARACTER*(132)  CIBNKFMT
      DATA CIBNKFMT/
     1'$Id: bnkfmt.inc,v 1.10 2008/03/16 04:33:20 fklein Exp $'
     2/
c----6----------------------------------------------------------------72
c  
c  Variables contained in BNKFMT common block
c  --------------------------------------------

      INTEGER MAX_BANK
      PARAMETER (MAX_BANK = 256)
      INTEGER MAX_ELEMENTS
      PARAMETER (MAX_ELEMENTS = 350)
c
      INTEGER NBANK_DISPLAY
      CHARACTER*4 CBANK_DISPLAY, CREATE_NAME
      CHARACTER*8 CREATE_ELEMENTS
      CHARACTER*132 CBANK_FORMAT, CREATE_FORMAT
      CHARACTER*4096 CBANK_DELETE, CBANK_WRITE, 
     1              CBANK_REMOVE
      INTEGER IDELETE, IWRITE, IREMOVE, ICREATE, NCREATE_COL
c
c_end_var
c
       COMMON/BNKFMT/NBANK_DISPLAY, CBANK_DISPLAY(MAX_BANK),
     1               CBANK_FORMAT(MAX_BANK),
     2               CBANK_DELETE, CBANK_WRITE,
     3               IDELETE, IWRITE,
     4               CBANK_REMOVE, IREMOVE,
     5               CREATE_NAME(MAX_BANK), CREATE_FORMAT(MAX_BANK),
     6               NCREATE_COL(MAX_BANK), ICREATE,
     6               CREATE_ELEMENTS(MAX_BANK,MAX_ELEMENTS)
c----6----------------------------------------------------------------72
