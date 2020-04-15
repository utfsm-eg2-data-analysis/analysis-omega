/* General */
#define NSECTOR 6

/* DC STATUS */
#define DC_NOT_SET    -1
#define DC_DNE        -2    /* this wire does not physically exist */
#define DC_GOOD_WIRE   0    
#define DC_DEAD_WIRE   1    /*   1 -  99 are reserved for dead and dim */
#define DC_HOT_WIRE  100    /* 100 - 199 are reserved for hot          */
#define CHANNELS 6912
#define WIRES_PER_LAYER 192

/* SC STATUS */
#define BAD_SC 1
#define GOOD_SC 0
#define NPADDLES 48
#define SC_LR 2
#define SC_ATS 2
#define SC_ADC 0
#define SC_TDC 1
#define SC_L 0
#define SC_R 1
