C
C   common block for epics values
C
	integer N_EPICS
	parameter (N_EPICS=400)
	integer tot_epics, epics_last_evt_num, epics_last_run_num
	real epics_value
	character*32 epics_name

	common/EPICS/epics_value(N_EPICS),epics_name(N_EPICS),tot_epics,
     +               epics_last_evt_num, epics_last_run_num

