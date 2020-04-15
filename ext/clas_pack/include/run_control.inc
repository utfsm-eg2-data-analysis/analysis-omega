cc      include file RUN_CONTROL
c
c_begin_doc
c  RCS ID string
c  $Id: run_control.inc,v 1.37 2008/04/23 08:11:44 claseg4 Exp $
c
c  Documentation for include file RUN_CONTROL
c
c  Purpose:  holds the RECSIS control variables for communication with
c  --------  TCL script
c
c  Used in routines:
c  ----------------
c
c  Notes:
c  ------
c
c  Author:   Arne Freyberger      Created:  Tue Nov 21 10:11:52 EST 1995
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
c  variables for include file RUN_CONTROL:
c  -----------------------------------
c  RCS information: 
      CHARACTER*(132)  CIRUN_CONTROL
      DATA CIRUN_CONTROL/
     1'$rcsId$'
     2/
c----6----------------------------------------------------------------72
c  
c  Variables contained in RUN_CONTROL common block
c  --------------------------------------------
c
c_end_var
c
c  NTCL_check  how often will recsis check the TCL-SCAT socket, default is 10
c  ITCL_CATCH is an integer used for TCL to pass error flags into FORTRAN
c
       integer ntcl_check, itcl_catch, nstamp
c
c  recsis will analyses NEVT_TO_PROCESS events and then pause, NEVT_COUNT is 
c  the number of events processed since the last LPAUSE
c
       INTEGER NEVT_TO_PROCESS
c
c  NEVT_TO_SKIP, recsis will skip NEVT_TO_SKIP events and then resume
c  processing.
c
       INTEGER NEVT_TO_SKIP
c
c  NRUN_TO_SKIP, recsis will skip NRUN_TO_SKIP runs and their events
c  and then resume processing.
c
       INTEGER NRUN_TO_PROCESS
c
c  NRUN_TO_SKIP, recsis will skip NRUN_TO_SKIP runs and their events
c  and then resume processing.
c
       INTEGER NRUN_TO_SKIP
c
c   LSTAT set to true causes the recsis status to be dumped to screen
c   and log file.
c
       LOGICAL LSTAT
c
c  The LEVENT_CLASS logicals control which event class to process.  The USER
c  can select a specific event class by turning event class 1-15 off and then
c  select the specific class desired.  By default all event classes are turned
c  on
c
       LOGICAL LEVENT_CLASS
c
c  The following logicals are used to control calling various packages
c  LDC_DO    TRUE -> perform tracking
c  LEGN_DO   TRUE -> perform calorimeter reconstruction
c  LCC_DO    TRUE -> perform cherenkov reconstruction
c  LTOF_DO    TRUE -> perform TOF reconstruction
c  LST_DO     TRUE -> perform start counter reconstruction
c  LUSR0_DO   FALSE -> perform USER code BEFORE event processing
c  LUSR1_DO   TRUE -> perform USER code after EVENT processing
c  LUSR2_DO   FALSE -> extra flag
c  LTIME_DO   TRUE -> perform event time analysis
c  LTAGGER_DO TRUE -> perform tagger stuff
c  LEC1_DO    TRUE -> perform large angle calorimeter
c  LSEB_DO    TRUE -> perform Simple Event Builder
c  LHBID_DO   TRUE -> Hit Based particle ID for PID package
c  LTBID_DO   TRUE -> Time Based particle ID for PID package
c  LCALL_DO   TRUE -> use Catch-All bank data
c  LRF_DO     TRUE -> generates the RF bank rf
c  LREG1_DO   TRUE -> perform track reconstruction in region 1 (def=.false.)
c  LPID_MAKE_TRKS   FALSE -> TRKS filled by PID
c  LIC_DO    FALS -> perform Inner calorimeter reconstruction
c  LGPID_DO  FALSE -> make GPID
c  LTBID_NOST_DO FALSE  -> make second TBID/PART ignoring ST (a la g2b) 
c  LPIPLTDC  FALSE -> get SC,EC,CC TDC from pipeline TDC rather than from 1872
c  LGEM_DO   TRUE  -> perform BONUS GEM reconstruction
c  LCC_EG4   FALSE -> use new low q2 cherenkov for sector 6

c  Start_tb  0=FALSE; 1=TRUE -> reconstruction starts from the point when 
c                      time based tracking is done. Rebuild other 
c                      detector baks and high level particle/event banks.
c
       LOGICAL LTRK_DO,   LEGN_DO,  LCC_DO,   LTOF_DO,  LST_DO, 
     1         LUSR0_DO, LUSR1_DO, LUSR2_DO, LTIME_DO, 
     2         LTAGGER_DO, LEC1_DO, LSEB_DO, LCALL_DO, LHBID_DO, LTBID_DO,
     3         LRF_DO,LREG1_DO,LPID_MAKE_TRKS,LIC_DO,START_TB,
     4         LGPID_DO, LTBID_NOST_DO, LPIPLTDC, LGEM_DO, LCC_EG4
c
c  set LDISPLAY true to call CED on the end of the event, LDISPLAY is toggled
c  OFF after sending the event and is used for selected events for the 
c  event display.  LDISPLAY_ALL will send EVERY event to the event DISPLAY
c
       LOGICAL LDISPLAY, LDISPLAY_ALL
c
c  unsure what this logical does
c
       LOGICAL LEVENT_ALL
c
c  the character strings 
c  FCK_FILE contains the name of the initial  FPACK control file 
c  TCL_INIT contains the name of the initial TCL script
c  REC_INPUT contains the name of the input file
c  REC_OUTPUT contains the name of the output file
c  arg_rec_input contains the command line input file name
c  arg_rec_output contains the output file name entered on the command line
c  arg_fpk_init contains the fpack control file entered on the command line
c
	INTEGER NCMD, IFPACK
       	PARAMETER (NCMD = 20)
c
	INTEGER REC_STRING
	PARAMETER (REC_STRING = 1024)
       	CHARACTER*(REC_STRING) FPK_FILE, TCL_INIT, REC_OUTPUT,
     1               arg_fpk_init, arg_rec_output,
     2               rec_prompt, ddl_file
       	CHARACTER*4096 rec_input, arg_rec_input, FPK_CMD
c
c  log_file name is the name of the recsis log file
c
	character*132 log_file_name
c
c  the following logicals perfrom some run_control functions
c  LPAUSE       : if TRUE suspend event loop
c  LPAUSE_EXIT : if TRUE pause at END of DATA, if FALSE exit RECSIS
c                 without pausing
c  LNEVER_PAUSE : if TRUE recsis will NEVER pause, used for batch processing
c  LEXIT        : if TRUE calls FSEQE and exits program after writing the event
c  LEXIT_PEND   : if TRUE calls FSEQE and exits program after exiting event
c                 loop
c  LQUIT        : if TRUE immediate EXIT
c  FSTAT        : if TRUE calls FPSTAT for FPACK info
c  LEOF         : set to TRUE when End Of File is reached
c  LPAR         : if TRUE will "pause" RECSIS AFTER RECONSTRUCTION 
c                 has been performed
       	LOGICAL LPAUSE, LEXIT, LEXIT_PEND, LQUIT, FSTAT, LCLOSE, LPAUSE_EXIT, 
     1  	       LEOF, LPAR, LNEVER_PAUSE
c
c  The following variables allow interactive access to the BOS banks
c
c  LBNKDMP  : L : if true a BOS BANK DUMP of CBNAME is performed
c  LNAMDMP  : L : if true the NAMES of the BOS BANKS in the current event
c                are printed to the screen and log file
c  LEVTDMP  : L : if true ALL the BOS banks for the current event are DUMPED
c  LBNKEDT  : L : if true modify BANK cbname (nrow,ncol) = rnew_value
c  CBNAME   :C*4: The individual BOS BANK name
c  NROW_TCL : I : Pointer into the BOS bank, points to the ROW
c  NCOL_TCL : I :                                           Column
c  NREC_TCL : I :                                           Sector
c  rnew_value : R*8 : the value to be deposited into BOS BANK 
c                      (nROW_tcl,nCOL_tcl)
c  ibos_array: I : 1=IW array 2=JW array
c  ncol_screen:I : number of columns for formating to the screen
c  mapmanager: I : turn on or off the mapmanager 1 = on 0 = off (def. is on)
c  read_et   :L:   if true, data will be read from the et chain instead of a
c                  a data file. this only applies to the online version of
c                  recsis. the default is off/false.
c  rec_rate: rate of events being read in and processed.
c  ipc_name:C*20: name used by online inter-process communication (ipc)

       character*20 ipc_name
       logical lbnkdmp, lnamdmp, levtdmp, lbnkedt
       character*4 cbname
       integer nrow_tcl, ncol_tcl, nrec_tcl, ibos_array, ncol_screen
       real*8 rnew_value, rec_rate
       integer mapmanager
       integer number_events_read
       logical read_et

c---------------------------------------------
       COMMON/RUN_CONTROL/rnew_value,
     &                    NEVT_TO_PROCESS,
     &                    NEVT_TO_SKIP,
     &                    NRUN_TO_PROCESS,
     &                    NRUN_TO_SKIP, NSTAMP,
     &                    LSTAT,
     &                    LEVENT_CLASS(21),
     &         LTRK_DO,   LEGN_DO,  LCC_DO,   LTOF_DO,  LST_DO, 
     &         LUSR0_DO,  LUSR1_DO, LUSR2_DO, LTIME_DO, LTAGGER_DO,
     &         LRF_DO,LREG1_DO, LIC_DO,
     &         LDISPLAY, LEVENT_ALL, FPK_FILE, TCL_INIT, REC_INPUT,
     &         REC_OUTPUT, arg_fpk_init, arg_rec_input, arg_rec_output,
     &         rec_prompt, lclose,LCALL_DO, 
     &         lpause, lexit, lquit, FSTAT, fpk_cmd(ncmd), lnever_pause,
     &         ldisplay_all, ddl_file, ntcl_check, lpause_exit,
     &         itcl_catch, leof, LEC1_DO, lbnkdmp, cbname,
     &         lpar, lnamdmp, levtdmp, nrow_tcl, ncol_tcl, nrec_tcl,
     &         lbnkedt, ibos_array, ncol_screen, IFPACK, 
     &         LSEB_DO, mapmanager, 
     &         read_et, number_events_read, LHBID_DO, 
     &         lexit_pend, log_file_name, rec_rate, ipc_name,
     &         LPID_MAKE_TRKS,
     &         START_TB, LTBID_DO, LGPID_DO,  LTBID_NOST_DO, LPIPLTDC,
     &         LGEM_DO, LCC_EG4
c
c----6----------------------------------------------------------------72















