/* ST CPP wrapper routines */

extern "C" {
  extern void st_set_def_();
  extern void st_init_();
  extern void st_bevt_();
  extern void st_evnt_(int*);
  extern int st_begin_run(int);
	   }

int st_set_def();
int st_init();
int st_bevt();
int st_evt(int);



