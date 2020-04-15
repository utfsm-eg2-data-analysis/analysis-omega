#define TRUE 1
#define FALSE 0

#define pawc_1 pawc_
#define PAWmem 4000000

/* Global Variables  */
#define LINLMAX  1400 /* maximum number characters per input line */

/* The following (six) lines must be set properly for each group of data files
   that have the same trigger timing 
   For cos4.dat and friends values are 200, 115, 238, 268, 10.0, 30 */

#define PAD_THRESH 500.0  /* cut for total charge on a single pad */
#define SELF_THRESH 150.0  /* software threshold for self-triggering */
#define MIN_WA_VALUE 20.0  /* minimum ALTRO data value considered significant */
#define NLINE 7  /* Number of ALTRO points at each end of time window to be 
		    used in fitting a straight line for baseline subtraction 
		 CHANGED FROM 10 TO 5 4/14/04 HCF TO ANALYZE PULSER DATA*/
#define BASE_START 15 //starting time bin for calculating baselines

#define NAL_CHAN 640 /* Number of channels of ALTRO data */
#define NAL_SAMP 100 /* Number of time samples from ALTRO */
#define N_FEC 5 //this must be set to the correct number of working FEC's
                //or we get a seg fault - ONLY WHEN USING read_BOS()
#define NAL_KEEP NAL_SAMP /* highest  time bin to record*/
#define NAL_SKIP 0 /* lowest time bin to record */
#define TPC_TMIN 12 /* earliest TPC track data */
#define TPC_TMAX 60 /* latest TPC track data 
		     changed from 17 to 15 4/14/04 hcf to study pulser data*/
                    //11/07/04 changed to min 14 and max 28 to correspond with 
                    //where nkb sees the majority of tracks in histo 2007 (raw t data)
                    //for new altro system changed to 17 and 30 2-28-05
                    // 15 to 35 at TUNL
                    // 5 to 85
#define DPADX 4.0 /* x size of pads */
#define DPADY 5.0 /* y size of pads */
#define GLITCH_MAX_CHAN 12
#define GLITCH_THRESH 30  /* more than GLITCH_MAX_CHAN with this charge
			      at one time = discharge event */

static int first_call_to_pad_neighbors = 1;
/* HBOOK Common Block Declarations */
static int c_b2 = PAWmem;
struct {
  double hmemor[PAWmem];
} pawc_;


typedef struct {
  unsigned raw;
  int tim;
  int edg;
  int chn;
} tdc_type;

typedef char linetype[LINLMAX];

/* Function Prototypes */
void box3d();
void keystone3d();
void draw_3d_event();
//void correlate();
int readkey();
int gem_getpad(int,int);
//these are for the data unpacker
int bit_print(int, int);
int bin2deci(int *, int, int);
int read_line(char *string);
//int read_line(char *, int);//NATES CHANGE
int read_line2(char *);
int unpack();
int read_BOS();

//a single pad length in z (mm)
#define DEL_Z 5.0

//the angular coverage of a single pad (rad)
#define DEL_PHI 0.06442


typedef struct {
  int row;
  int col;
  float phi; //in radians!
  float z; //mm
} coordinates;

#define NODATA -1000 //no signal in time sample marker
#define RESCUT 4 //throw away data w/ res over this number
#define THRESHA 125 //threshold that determines which data from the altro are put into the raw data to fit array
#define GRID_CUT 5000      
#define THRESHB 300 //A is low, B is High
#define TIME_CUTA 20 //number of bins over THRESHA to get into histo 2019
#define DISPLAYTHRESH 100.0 //threshold to look at only the first 16 channels which had some signal and to choose hits for SED
#define PI 3.1415927
#define TIME2DIST 0.91 //converts time axis to distance - found by dividing chamber width (mm) by how many time samples
                       //it takes for a particle to travel all the way through - 9/1/04 I used 20/13 = 1.54
                       //9/28/04 I used 20/12 = 1.67
                       //11/17/04 back to 1.54
                       //3/3/05 for TUNL used 20/22 = 0.91
#define PAD_RAD 69 //this is the radius where the pad plane is located (in mm)
#define GEM_RAD 60 //this is the radius where the first GEM plane is located (in mm)

#define CHAM_THICK 3.0 //the chamber thickness in cm
#define CONVERTER 80.0 //what to divide "charge" by to get energy
                       //this is calculated by normalizing the peak of an iron 55 photon 
                       //run to 5.9 KeV - changed from 81 on 8-25-04
                       //using 26 to match Kuhn's calc at 2 absorbers
#define DENSITY 0.000166 //0.0016 argon density at ~room temp in g/cm^3
                         //0.00016 for helium gas
#define NUM_VALUES 95 //the number of data pts from the energy table
#define FIRST_BINS 10 //tells how many bins to define the beginning of the track
///////////////////////////////////////////////////////////////////////////
 
///////////////////////////FOR KEITH"S TRACKER////////////////////////////////////
//#define NODATA -1000
#define GRIDPHI 50  //changed each from 20 to 5 on 6-28-05
#define GRIDZ 50
#define EVT_TRKS 20
#define EVT_PNTS 5000
#define DATA_PNTS 100000
///////////////////////////////////////////////////////////////////////////
		  
typedef struct {
  float phi;
  float z;
  float s;
  float charge;
} cylindrical; //this is the raw data type

typedef struct {
  float x;
  float y;
  float z;
  float charge;
} cartesian; //this array is needed to measure the residuals

typedef struct {
  float x;
  float y;
  float z;
  float charge;
  int dataFlag;
} xyz; //this data type will hold the weighted data - possibility of 50 different xy combos
       //the z value is retained in the array's index

typedef struct {
  float phi;
  float z;
  float s;
  float charge;
  int dataFlag;
} sphiz; //this data type will hold the initial weighted data in cylindrical coordinates





//these variables are for momentum determination
float e_linefit(int, float[]);
int gem_track(char);

//these variables are for the circle fit routine
void circleFit(int);
void linefit(int);

//these variables are for the true proton position determination
//so that we can visualize tracks and fit circles to the real
//positions - taking Lorentz angle into account

//#define L_ANGLE 0.34906585 //this is 20 degrees - delta V = 1500 and He/DME = 80/20
//#define L_ANGLE 0.912 //this is 52 degrees - delta V = 1000 and Ar/CO2 = 80/20

void variable_defs();

extern int nal_samp; /* VARIABLE number corresponding to the above */
extern int nal_keep;
extern float padx[NAL_CHAN], pady[NAL_CHAN]; /* locations of center of each pad */ 
extern char filename[200];//= "./datafile.dat";
// single[] is not used in the entire GEM scope, conflict of names on SunOS where 'single' is defined in floatingpoint.h
// extern char single[2];  
extern char histfilename[200];
extern int tdc_data_in_file;// = FALSE;
extern int tdc_multi_lines;//=  TRUE;
extern float altro_dat[NAL_SAMP][NAL_CHAN];
extern int  got_data[NAL_CHAN];
extern float altro_ped[NAL_SAMP][NAL_CHAN];
extern int good_altro_data;// = FALSE;
extern tdc_type tdcdat[50];
extern int num_tdc_words;
extern float favored_hit[24]; /* where we store the LAST hit-time for each tdc channel */
extern char ev_date[30];
extern char ev_time[9];
extern int ev_num;
extern int quiet;//=FALSE; /* whether to print out messages */
extern int indicate_dead_channels;//=FALSE; /* whether to indicate hot/non-reporting channels on SED */
extern linetype textline;
//some varibles for the 3D display
extern float tht3d;//=90.0;
extern float phi3d;//=0.0; /* viewing angles for 3D event display */
extern float center_3D[3]; //held as (x,y,z)
extern float delx_3D;//=120.0;
extern float dely_3D;//=120.0;
extern float delz_3D;//=220.0;
extern coordinates padLocs[NAL_CHAN];
extern float temp_phi;
extern float displaythresh;//= DISPLAYTHRESH; 
extern int actual_time,tmin, tmax, dt, newPosition; 
extern int overThresh[16]; //for TUNL3 run, if a pad had charge over TUNL3_THRESH then display it's waveform
extern float biggestSignal;
extern int holder1;
//these variables are for the linefit - z is the ind variable, two fits are 
//determined, one in the zy plane and one in the zx plane
extern int numWPoints; //number of points in weighted array 
extern int numRawPoints; //number of points in Raw data array
extern int nBadPoints; //number of points removed from the raw Data array
extern int hitPad;
extern float m_z[EVT_TRKS], m_x[EVT_TRKS], b_z[EVT_TRKS], b_x[EVT_TRKS]; //line fit parameters
extern float m_s[EVT_TRKS], b_s[EVT_TRKS];
extern float track_theta, track_phi, track_vertex;
extern float intEnergy[NAL_SAMP];
extern float energySum;
extern int pts, includeThis;
//extern float m_e,b_e, proton_mom;

//these variables and prototypes are for Keith's track finding routine
extern cylindrical* event[EVT_TRKS][EVT_PNTS];
extern int gem_ntracks;
extern float x_0[EVT_TRKS], y_0[EVT_TRKS], r_0[EVT_TRKS];
extern float p_perp, p_para, p_tot, p_x, p_y;
extern int doFits;

//for the June 2005 Run Histograms
extern int numAboveA;//number of pads with charge above THRESHA
extern int numAboveB;//number of pads with charge above THRESHB
extern float totIntQ; //total integrated charge
extern float totIntQ_L, totIntQ_R; //left and right of chamber
extern int numTracks, numCellsTrack;
extern float totQTrack, avgQCell;
extern int aboveA, aboveB;

extern cylindrical ePath[NAL_SAMP];
extern int n_pathpts;
extern float electronDist;
extern int ntype[30]; 
//float proton_position;



//these variables are for the energy histos
extern int goodEnergyData, holder;
extern float allSum, protonSum, longSum, fitSum, padSum,trackSum;
extern float allBeginSum, protonBeginSum, longBeginSum;
extern float eMEV1, eMEV2, eMEV3, eMEV4;
extern float dedx1[1], dedx2[1], dedx3[1], dedx4[1]; //FINT needs an array
extern float ipe1, ipe2, ipe3, ipe4; //interpolated incoming energy
extern float de[NUM_VALUES]; //the array of the dE/dx values from the NIST tables
extern float f[1][NUM_VALUES]; //FINT needs a multidim array - the array of the KE values from the NIST tables
extern int num_values[1]; //FINT needs an array
extern float high_table, low_table;
extern int aLast, aCurrent;
extern int num_events, numRawPoints, thisPadWasHit;
extern cylindrical rawCYL[NAL_SAMP][NAL_CHAN]; /*holds the signal data for the first linefit
	                      a NODATA in charge indicates there is no data*/
extern cartesian rawXYZ[NAL_SAMP][NAL_CHAN]; /*holds the signal data for the first linefit
	                      a NODATA in charge indicates there is no data*/

extern float timeToDist[32];
extern int hotPads[NAL_CHAN], endIndex, processPad, done;

extern int doDefault;
extern int tail_cancel;
extern int cm_filter;
extern int base_sub;
extern int tail_clip;
extern int graphics;
extern int doDCcomp;//nkb




// statistics variables
extern int num_events;
extern int hadDataRemoved; //nkb
extern int numCorrelatedEvents; //nkb
extern int badEvents; //nkb
extern int getNextDC; //nkb
extern int numFits; //nkb
extern float rat;
int gem_read_data();
int gem_weed(int);
int make_gem_part_();
void gem_fill_nt_(int *ngem, float *x);
int event_id(int , float , int , int);
