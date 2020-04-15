c      include file RHIST
c
c_begin_doc
c  RCS ID string
c  $Id: rhist.inc,v 1.4 2006/02/04 00:44:58 stepanya Exp $
c
c  Documentation for include file RHIST
c
c  Purpose: holds the directory and histogram number that the user
c  -------- wishes to dump out
c
c  Used in routines: RHIST
c  ----------------
c
c  Notes:
c  ------
c
c  Author:   Arne Freyberger      Created:  Thu Mar 21 09:38:39 EST 1996
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
c  variables for include file RHIST:
c  -----------------------------------
c  RCS information: 
      CHARACTER*(132)  CIRHIST
      DATA CIRHIST/
     1'$Id: rhist.inc,v 1.4 2006/02/04 00:44:58 stepanya Exp $'
     2/
c----6----------------------------------------------------------------72
c  
c  Variables contained in RHIST common block
c  --------------------------------------------
c
c_end_var
c
       CHARACTER*132 hist_dir
       INTEGER HIST_ID

       integer max_hist, max_tcl, nhist, nhist_max
       parameter (max_hist = 1000)
       parameter (max_tcl = 99)
       
       character*80 dirhist,  hist_tit, hist_x, hist_y,
     1              cut_hist, hist_cut, hdir, ctcltup, ctclvar
       character*132 chist_filename
       character*4 xbname, ybname, cbnktup, cshared_name
       character*8 cntup
       integer nxchan, nychan, idhist, nbook_stack, nfill_stack
       integer xrec, yrec, xcol, ycol, hid, xrectup, xcoltup
       integer ndimtup, ndim, xfmttup, xfmt, yfmt
       logical lhbook, lhist, lsetvar, lntup, lhbook_init
       real*8 xmin, xmax, ymin, ymax

       COMMON/RHIST/nhist(max_tcl), hist_id(max_tcl), hist_dir(max_tcl), 
     +              nxchan(max_tcl), nychan(max_tcl), 
     +              hist_tit(max_tcl), hist_x(max_tcl), hist_y(max_tcl),
     +              cntup(max_tcl,25),lntup(max_tcl), ctcltup(max_tcl,25),
     +              ndim(max_tcl), ctclvar(max_tcl,25),
     +              nhist_max, nbook_stack, nfill_stack, 
     +              lhbook, lhist, lsetvar, hdir, hid, 
     +              idhist(max_hist),xbname(max_hist),ybname(max_hist),
     +              xrec(max_hist), yrec(max_hist),xcol(max_hist), 
     +              ycol(max_hist),dirhist(max_hist),cut_hist(max_hist), 
     +              hist_cut, cbnktup(max_hist,25), 
     +              xrectup(max_hist,25), xcoltup(max_hist,25), 
     +              ndimtup(max_hist), xfmt(max_hist), yfmt(max_hist),
     +              xfmttup(max_hist,25),
     +              xmin(max_tcl), xmax(max_tcl), ymin(max_tcl), 
     +              ymax(max_tcl), chist_filename, cshared_name,
     +              lhbook_init
c----6----------------------------------------------------------------72




