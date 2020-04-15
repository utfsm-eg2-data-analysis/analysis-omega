#ifndef ecH_INCLUDED
#define ecH_INCLUDED

/* ec C header file */

/*number of channels in the u layer over all sectors*/
#define EC_CHANNELS_PER_LAYER 216

/* same number means different things
number of channels u, v, w in each sector*/
#define EC_CHANNELS_PER_SECTOR 216
#define EC_STRIPS 36
#define EC_STRIPS_MAX 108

/*useful macros - to negotiate this morass...*/
#define WHOLE 0
#define INNER 1
#define OUTER 2
#define EC_ORIENTATION 3 /* U V W strips in EC*/
#define EC_LAYERS 3 /* whole inner and outer layers  in EC*/
#define EC_LAYERS_MAX 4 /* whole inner and outer layers  in EC*/

#define U_EC 0
#define V_EC 1
#define W_EC 2

/*ECHB macros....*/
#define TWO_BYTES 65536
#define ECHB_WHOLE 9
#define ECHB_INNER 10
#define ECHB_OUTER 11
#define EC_MAGIC_NUMBER (1.0/0.272) /*conversion of EC energy to gamma energy*/

typedef struct {
  float Inner;
  float Outer;
  float Whole;
} ecHit_t;

/*prototypes defined in ec_maputil.c*/
int ec_begin_run(int runno);
int ec_channel(int index);
int ec_sector(int index);
int ec_index(int sector, int channel);

int layer_string(int layer, char *map_layer);
int orient_string(int orient, char *map_orient);
int ec_item_string(int id, char *strip_id);

int ec_read_ecpeds_map_(int *runno);
int ec_read_ecgain_map_(int *runno);

int ec_read_map(int runno,float ec_common[6][3][3][36], char *subsystem_c, float def_value);
int ec_read_map_(int *runno,float ec_common[6][3][3][36], char *subsystem_f, float *def_value, int string);
int ec_read_adc_map(int runno,float ec_common[6][3][3][36], char *subsystem_c, float def_value);
int ec_read_adc_map_(int *runno,float ec_common[6][3][3][36], char *subsystem_f, float *def_value, int string);
int ec_readmap_(int *runno, float ec_common[6][6][36], char *map_f, int string);
int ec_read_tdc_map(int runno, float ec_common[6][2][3][36], char *subsystem_c, float def_value);
int ec_read_tdc_map_(int *runno, float ec_common[6][2][3][36], char *subsystem_f, float *def_value, int string);
int ec_put_tdc_map_(int *runno, float ec_common[6][2][3][36], char *subsystem_f, int string);
int ec_rem_tdc_map_array(int runno, char *map_c);

/* defined in ec_makebanks.c */
int make_ecca_banks_(int *runno);
int make_ecca_bank(int sector, int runno);

/* defined in ec_makeEC01.c */
int ec_Whole2InOut(echb_t * Whole, echb_t ** Inner, echb_t ** Outer);

vector3_t inner2whole_displacement(vector3_t dir,int sec);

/* prototypes for Fortran routines */
void ec_evnt_(void);
void ec1_evnt_(void);
int ec_set_def_(void);

#endif
