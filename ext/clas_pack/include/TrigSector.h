/*-------------------------- M A C R O S ------------------------------------*/
#define EC_ADC_THLD 0  /*2875*/   /* threshold in adc is 23 channels per mV discriminator threshold */
#define CC_ADC_THLD 0  /*40*/    /* thld in adc is 2* discriminator thld in mV */
#define MIN_CC_TRIG_BIT 0 /* don't consider trigger bits less than this 
			   this should normally be set to zero! */
#define N_CC_TRIG_BITS 8  /* there are this many cc trigger bits */

/* --------------------- S T R U C T U R E S ----------------------------------*/
typedef struct {   
  int sec;   /* sector */
  int adc;   
} pmtHit_t;

int TrigSector(int RunNo);

int sort_pmtHit(const void *pmtHit1, const void *pmtHit2);

int cc_id2TrigBit(int id, int * CCBit1, int * CCBit2);
