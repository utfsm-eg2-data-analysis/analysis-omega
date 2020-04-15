
#define ST_TUBES 6


/*the StCal common*/
typedef struct StCal {
  float StCal_values[6][13];
  float StCal_uncs[6][13];
} StCal_t;

/*the StnCal common*/
typedef struct StnCal {
  float StnCal_values[24][15];
  float StnCal_uncs[24][15];
} StnCal_t;

#define VALUES 0

#define UNCERTAINTIES 1

#define TDC_T0 0
#define TDC_T1 1
#define TDC_T2 2
#define WALK0 3
#define WALK1 4
#define WALK2 5
#define M0 6
#define LAMBDA 7
#define ADCMAX 7
#define VEFF_LEG_NEAR 8
#define VEFF_LEG_FAR 9
#define VEFF_NOSE_NEAR 10
#define VEFF_NOSE_FAR 11
#define VEFF_LEG 8
#define VEFF_NOSE 9
#define VEFF_NOSE1 10
#define VEFF_NOSE2 11
#define PEDESTAL 12
#define TDC_MIN 13
#define TDC_MAX 14

/*prototypes*/
int st_read_map(char *map,int runno,char *subsystem, int index,
		float StCal_values[6][13],float StCal_uncs[6][13]);
int stcal_read_map_(int *runno,float StCal_values[6][13],float StCal_uncs[6][13]);
int stncal_read_map_(int *runno,float StnCal_values[24][15],float StnCal_uncs[24][15]);
int st_begin_run(int runno);





/* -------------------------- stgeom ----------------------------*/


/* the stgeom common */

typedef struct {
  float St_Normal_vect[36],St_Rnormal_dist[12];
    int pair_id_2_sect_id[6];
  float leg_x_max,leg_y_min,leg_y_max,leg_z_min,leg_z_max,
     	nose_x_min,nose_x_max,nose_z_min,nose_z_max,
    a_nose,b_nose,c_nose;
} stgeom_t;

/*---------------------------------------------------------------*/
