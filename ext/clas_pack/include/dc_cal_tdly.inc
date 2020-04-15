c      include file dc_cal_tdly
c
c_begin_doc
c  RCS ID string
c  $Id: dc_cal_tdly.inc,v 1.9 2006/02/04 00:43:32 stepanya Exp $
c
c  Documentation for include file DC_CAL_TDLY
c
c  Purpose:  Contains the Dridt Chamber Time DeLaY Calibration Parameter for
c  --------  each wire and the valide run range for this parameter.
c
c  Used in routines: DC_GETCAL_TDLY
c  ----------------
c
c  Notes:
c  ------
c
c  Author:   Francois Roudot      Created:  Mon May  6 14:44:00 EST 1996
c  -------
c
c  Major revisions: F.R 11-14-1996 modified t0 array to improve memory space (?)
c  ----------------  Nov.1997  F.Klein:
c-->read from Map:   T_delay_trig(isec)        overall Time_delay (DC->Trigger),
c               dc_V_signal(region,isec)  velocity of signal propagation along a wire [cm/ns]
c               dc_Tslope                 Slope for TDCs (1 TDCcnt=500psec)
c_end_doc
c               TDC_cut(Min:Max,region)   TDC_cut on DC0 data in order to keep only
c                                         TDC values within max.drift time in Region
c
c  Remember NO NESTED INCLUDES
c
c  COMMON BLOCK NAME should be the same as include file name!
c
c_begin_var
c  variables for include file DC_CAL_TDLY:
c  ---------------------------------------
c  RCS information: 
      CHARACTER*(132)  CIDC_CAL_TDLY
      DATA CIDC_CAL_TDLY/
     1'$Id: dc_cal_tdly.inc,v 1.9 2006/02/04 00:43:32 stepanya Exp $'
     2/
c----6----------------------------------------------------------------72
c  
c  Variables contained in DC_CAL_TDLY common block
c  -----------------------------------------------
      INTEGER MAX_SECTOR
      INTEGER MAX_LAYER
      INTEGER MAX_WIRE
      PARAMETER (MAX_SECTOR = 6)
      PARAMETER (MAX_LAYER = 36)
      PARAMETER (MAX_WIRE = 192)

! Difference: T_realdata_delay - T_pulser_delay + global_offset(=2700 nsec)

      real  dc_V_signal
      real  DC_Tslope

c      PARAMETER (dc_V_signal = 19.0)
c  changed 11/19/98: measured by Mac Mestayer
      PARAMETER (dc_V_signal = 23.0)
      PARAMETER (DC_Tslope = 2.0)
c
      INTEGER ILOW_RUN_TDLY
      INTEGER IHIG_RUN_TDLY
      REAL T0(MAX_WIRE,MAX_LAYER,MAX_SECTOR)	
      INTEGER STAT(MAX_WIRE,MAX_LAYER,MAX_SECTOR)	
      REAL TDC_cut_min(3), TDC_cut_max(3)
c
c_end_var
c
      COMMON /DC_CAL_TDLY/ ILOW_RUN_TDLY, IHIG_RUN_TDLY,
     &                     T0, STAT, TDC_cut_min, TDC_cut_max

c----6----------------------------------------------------------------72




