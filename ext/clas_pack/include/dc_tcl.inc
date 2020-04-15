c      include file DC_tcl
c
c_begin_doc
c  RCS ID string
c  $Id: dc_tcl.inc,v 1.8 2006/02/04 00:43:38 stepanya Exp $
c
c  Documentation for include file DC_TCL
c
c  Purpose:
c  --------
c  Contains tcl variables for dc.
c
c  Used in routines:
c  ----------------
c  dc_tcl_init
c  dc_getcal_geom
c  dc_xvst_get_doca
c  dc_xvst_get_tdrift
c  Notes:
c  ------
c
c  Author:   Francois Roudot      Created:  Tue May 20 12:00:00 EDT 1997
c  -------
c
c  Major revisions:  Nov.1997  F.Klein : some more tracking related tcl params.
c  ----------------
c
c_end_doc
c
c_begin_var
c  variables for include file DC_TCL:
c  -----------------------------------
c  RCS information: 
      CHARACTER*(132)  CIDC_TCL
      DATA CIDC_TCL/
     1'$Id: dc_tcl.inc,v 1.8 2006/02/04 00:43:38 stepanya Exp $'
     2/

c  
c  Variables contained in DC_TCL common block
c  ------------------------------------------

C  dc_Sigma_doca(isly)         Drift Chamber Resolution [cm] for each superlayer
C           (def.=0.04,0.04,0.05,0.05,0.07,0.07)
C  dc_efficiency               Drift Chamber Cell Efficiency (in %)
C           (def.=0.98)
C  dc_trig_time                adjustment of time delays between DC & SC
C           (def.=0)   
C  dc_reg_pulser_time          adjustment of pulser time delays of three regions
C           (def.=0,0,10)   
C  dc_vel_prop                 propagation velocity along the wire [cm/nsec]
C           (def.=16.)
C  dc_mult_Sigma(isly)         Drift Chamber Resolution MULTIPLIER for each superlayer
C           (def.=1.,1.,1.,1.,1.,1.)
c slope in case of no curve and power of t/tmax controled via tcl. fr 05/05/97
      real*8    dc_xvst_default_slope, dc_xvst_n_power, dc_xvst_m_power
      real*8    dc_Sigma_doca(6), dc_efficiency, dc_trig_time
      real*8    dc_reg_pulser_time(3)
      real*8    dc_vel_prop
      integer   dc_xvst_choice
      real*8    dc_mult_Sigma(6)
c_end_var      
      COMMON/DC_TCL/ dc_xvst_default_slope,dc_xvst_n_power,dc_xvst_m_power,
     &               dc_sigma_doca,dc_efficiency,dc_trig_time,
     &               dc_reg_pulser_time,dc_vel_prop,
     &               dc_xvst_choice,dc_mult_sigma
      save /dc_tcl/
c----6----------------------------------------------------------------72



















