cc      include file ET
c
c  Purpose:  holds the ET control variables.
c
c  Author:   Gilfoyle 
c  -------
c
c----6----------------------------------------------------------------72
c  
c  Variables contained in ET common block
c  --------------------------------------------
c
c ET_ok      = 1 if et is alive, = 0 is et is dead.
c ET_session - ET session name, usually clasprod.
c ET_host    - for remotely connected system
c ET_station - name of shared memory used to pass data.
c ET_id      - unique name used by IPC to identify process.
c ETout_ok   = -1 if et is alive, = 0 is et is dead.
c ETout_session - ET session name, usually clasprod.
c ETout_host    - for remotely connected system
c application - project/application name for daq monitoring.
c
      integer      ET_ok, ETout_ok
      character*20 ET_id, application, ET_session, ETout_session, ET_station
      character*20 ET_host, ETout_host
      character*512 ET_outbanks

      common /etEVNT/ ET_id, ET_session, ET_host, ET_station, application, ET_ok
     &                ,ET_outbanks,ETout_session,ETout_host,ETout_ok

