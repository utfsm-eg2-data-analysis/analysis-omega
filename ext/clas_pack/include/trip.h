//$Id: trip.h,v 1.6 2006/03/15 14:53:17 pasyuk Exp $
/* header file for TRIP */
#ifndef TRIPincluded
#define TRIPincluded

typedef struct{
int scaler_event_counter;
int scaler_current;
int trip;
int first_in_scaler_interval;
int last_in_scaler_interval;
int physics_event_counter;
int scaler_interval;
float diff_average;
float diff_scaler_based;
uint32 last_event_timer;
uint32 current_scaler_timer;
float live_time;
} trip_data_t;

void open_trip_file(char *file_trip);
int TRIP();
int trip_();
#endif








