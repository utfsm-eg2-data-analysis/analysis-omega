/*********************************************************************************
 *                                                                               *
 *           DEMUX_ROC  "Routines for unscrambling raw SC, EC, EC1,CC  banks"    *
 *                                                                               *
 *  (Later to be extended to DC0 banks also....)                                 *
 *                                                                               *
 *********************************************************************************
 */

/* The following entries define the maxima that can be expected
 * for certain entries in the ROCxx.tab tables.
 * Since different detector components use different names for these
 * entries, it can be a touch confusing. Nomenclature here is related to 
 * the SC package.
 *
 * maximum is actually MAX+1, because of C indexing properties.
 */

#define DEMUX_NUM_SLABS 385      /* Maximum for "slab" enry. */
#define DEMUX_NUM_LAYERS 37      /* Max for Layers           */
#define DEMUX_NUM_SECTORS 7      /* Max for sectors          */
#define DEMUX_NUM_MODULES 26     /* Max for Modules.         */

/* Definitions for reading in files. Maximum string sizes for not 
 * dynamically allocated strings.
 */

#undef PRE_PROCESSOR

#ifndef MAX_STR_LEN
#define MAX_STR_LEN 256
#endif
#ifndef MAX_NUM_TOK
#define MAX_NUM_TOK 11
#endif
#ifndef TOKEN_DEPTH 
#define TOKEN_DEPTH 32       /* Maximum length of one token */
#endif
#ifndef TOKEN_SEP
#define TOKEN_SEP  " (),\t\n" /* Token separator string */
#endif
#ifndef QUOTE_SEP
#define QUOTE_SEP  "\"`\'"     /* Define limiters of "quoted" strings. */
#endif                       /* See read_n_tokens. */

#define MAX_NAME_LEN MAX_STR_LEN /* Maximum length for histogram names. */

typedef struct {       /* A generic class bank, used in decoding. */
  bankHeader_t bank;
  unsigned short entry[1];
} clasG_t;


/* These structure code and decode the RAW (ROC) data to and from BOS types */
/*
 *  ROC_DMUX_t look_dm[crate][slot][channel].sector (.slab .place)
 *  ROC_MUX_t  look_mu[sector][slab][place].crate   (.slot .channel)
 *
 * Here, "place" is the uint16 location int the bosbank: 
 *
 * uint16 idat  = dat&0x7F;        // This is the "raw data" from a TDC channel 
 * uint16 islot = (dat>>27)&0x1f;  //Slot number of module in crate. 
 * uint16 ichan = (lookup[islot].type==0 ?
 *                (dat>>16)&0x3F          :   // Channel number in module, if TDC 
 *                (dat>>17)&0x3F           ); // Channel number in module, if ADC 
 *
 * clasSC_t    SCdat;
 * ROC_DMUX_t  *lookup;                           // Note: you need one per crate. 
 * lookup = malloc(sizeof(ROC_DMUX_t));           // Allow for one crate. 
 * init_decode_roc("ROC13.tab",lookup,NULL);        // Fill lookup table for crate 13
 * SCdat->sc.id = lookup->mod[islot]->ch[ichan].slab;  // Fill bank item.
 * *(&SCdat->sc.tdcl+ lookup->mod[islot]->ch[ichan].place)= idat; 
 *
 * ROC_MUX_t  *delook;
 * islot = delook->sec[sector]->layer[layer]->sl[slab]->slot[place];
 * ichan = delook->sec[sector]->layer[layer]->sl[slab]->chan[place];
 *
 * Fill these with init_decode_roc routine.
 *
 */

typedef struct {
  unsigned short nummod;         /* Number of the modules defined in crate. redundant. */
  unsigned short type;           /* Module type =0 for ADC, =1 for TDC, =2 for DC ADC */
  struct {
    char           bankname[5];  /* Name of bank to store to. */
    unsigned short sector;       /* Sector Column */
    unsigned short layer;        /* sd1 column */
    unsigned short slab;         /* sd2 column */
    unsigned short place;        /* Index into the BOS bank struct, assuming int16's */
  } ch[64];                      /* Allow for 64 channels to a module. */
}ROC_DMUX_MODULE_t;              /* One structure for each module. */

typedef struct {
  unsigned short crate;          /* Crate number. */
  ROC_DMUX_MODULE_t *mod[DEMUX_NUM_MODULES];    /* Array of pointers to modules. =NULL when no module in slot. */
}ROC_DMUX_t;

typedef struct {
  unsigned short *slot;
  unsigned short *chan;
}ROC_MUX_SLAB_t;

typedef struct {
  ROC_MUX_SLAB_t *sl[DEMUX_NUM_SLABS];  
}ROC_MUX_LAYER_t;

typedef struct {
  ROC_MUX_LAYER_t *layer[DEMUX_NUM_LAYERS];
}ROC_MUX_SECTOR_t;

typedef struct {
  ROC_MUX_SECTOR_t *sec[DEMUX_NUM_SECTORS];
}ROC_MUX_t;

/* Structure to store decored raw ADC/TDC information */

typedef struct {
  int islot;
  int ichan;
  int idat;
  int itype;
}RAW_DATA_t;



/* NOTICE !!! Bitwise manipulations like these are ARCHITECTURE DEPENDENT 
 * Linux (pentiums)     is LSB first byte order,
 * SGI, SUN, HP, AIX    is MSB first byte order.
 * Thus for Linux, we just turn these structures "upside-down"
 */

#if defined(__linux) || defined(__Alpha)

typedef struct {
  unsigned count  :  7;
  unsigned empty  : 20;
  unsigned slot   :  5;
}ADC_1881_HEAD;

/*  NO such thing.....
typedef struct {
}TDC_1872_HEAD;
*/

typedef struct {
  unsigned count  : 11;
  unsigned buffer :  3;
  unsigned empty  :  1;
  unsigned parity :  1;
  unsigned empty1 :  8;
  unsigned empty0 :  3;
  unsigned slot   :  5;
} TDC_1877_HEAD;

typedef struct {
  unsigned data    : 14;
  unsigned dummy   :  3;
  unsigned channel :  6;
  unsigned empty   :  1;
  unsigned x       :  3;
  unsigned slot    :  5;
} ADC_1881_DATA;

typedef struct {
  unsigned data    : 12;
  unsigned dummy   :  4;
  unsigned channel :  6;
  unsigned empty   :  2;
  unsigned x       :  3;
  unsigned slot    :  5;
} TDC_1872_DATA;

typedef struct {
  unsigned data    : 16;
  unsigned edge    :  1;
  unsigned channel :  7;
  unsigned type    :  3;
  unsigned slot    :  5;
} TDC_1877_DATA;

#else /* For "normal" CPU that go MSB first. */
      /* All the bitwise structures are just "pside down" */ 
typedef struct {
  unsigned slot   :  5;
  unsigned empty  : 20;
  unsigned count  :  7;
}ADC_1881_HEAD;

/*  NO such thing.....
typedef struct {
}TDC_1872_HEAD;
*/

typedef struct {
  unsigned slot   :  5;
  unsigned empty0 :  3;
  unsigned empty1 :  8;
  unsigned parity :  1;
  unsigned empty  :  1;
  unsigned buffer :  3;
  unsigned count  : 11;
} TDC_1877_HEAD;

typedef struct {
  unsigned slot    :  5;
  unsigned x       :  3;
  unsigned empty   :  1;
  unsigned channel :  6;
  unsigned dummy   :  3;
  unsigned data    : 14;
} ADC_1881_DATA;

typedef struct {
  unsigned slot    :  5;
  unsigned x       :  3;
  unsigned empty   :  2;
  unsigned channel :  6;
  unsigned dummy   :  4;
  unsigned data    : 12;
} TDC_1872_DATA;

typedef struct {
  unsigned slot    :  5;
  unsigned type    :  3;
  unsigned channel :  7;
  unsigned edge    :  1;
  unsigned data    : 16;
} TDC_1877_DATA;

#endif

/* Prototypes of Routines in the Demux package. */

void init_decode_roc(char *rocfile,ROC_DMUX_t *rtab,ROC_MUX_t *dtab);
ROC_DMUX_t *alloc_decode_roc(int mode);
int decode_raw_data(clasRC_t *RC,int n_call,ROC_DMUX_t *RC_look,
		    int tdc_slot_low,int tdc_slot_high,
		    RAW_DATA_t *R);
void decode_raw_banks(BOSbank *BCS,char *bankname,int sect,
                      clasG_t  *Bankout,clasRC_t *Raw,ROC_DMUX_t *rc13_look);
