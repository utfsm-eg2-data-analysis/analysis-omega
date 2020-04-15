#ifndef utilityH_INCLUDED
#define utilityH_INCLUDED
/* Planes defined for the HDPL bank- see hdpl.ddl */
typedef enum {
VertexPlane,stLegPlane,stNosePlane,CCPlane,scPlane1,scPlane2,scPlane3,scPlane4,
ForwardECPlane,LACPlane } hdplPlane_t;

/* No of rows in the HDPL bank per track*/
#define NoOfPlanesPerTrack 10
#define HBLAPlanesPerTrack 34

#define RAD2DEG (180.0/3.14159)

/* tracking utilities - to negotiate between tracking banks*/
hdpl_t * hbtr2hdpl(hbtr_t  *);
tdpl_t * tbtr2tdpl(tbtr_t  *tb);
tbla_t *tbtr2tbla(tbtr_t *tbtr);
vector4_t btr2vec4(tbtr_t *tbtr, float mass); /*works with both hbtr_t and tbtr_t*/
hbla_t *hbtr2hbla(hbtr_t *hbtr);
trks_t *hbtr2trks(hbtr_t *hbtr);

/* go back from tbid/hbid to tbtr/hbtr */
tbtr_t * tbid2tbtr(tbid_t *tbid);
hbtr_t * hbid2hbtr(hbid_t *hbid);


/*coordinate transformations*/
vector3_t lab2sector(vector3_t lab, int sector);
vector3_t sector2lab(vector3_t sec, int sector);
vector3_t trk2sec(vector3_t trk);
vector3_t sec2trk(vector3_t sec);
vector3_t lab2bogdan(vector3_t lab);


/* replacement for txt2bos*/
int configure_banks(FILE *out, int verbose);

/* CLAS specific 4-vector utilities*/
int get_sector(vector4_t *);
float get_phi(vector4_t *);
float get_theta(vector4_t *);
int on_centerline(vector4_t vec, float cut); /* tells if a particle in pointing towards the center of a chamber or not with a variable cut */

/*ECHB utilities*/
int echb2sector(echb_t *);
int echb2layer(echb_t *);
float dist_echb_tdpl(echb_t *, tdpl_t *);

/* count the number of superlayers on a track */
int NumSL(int trackno);
int numsl_(int *trackno);

/* run control map bank*/


#define ELECTRON_RUN 0
#define PHOTON_RUN   1
#define G7_RUN       2
#define G2B_RUN      3
#define G11_RUN      4


clasRUNC_t *make_RUNC_bank(int runno);
int make_runc_bank_(int *runno);
int set_beam_energy_(float *MeV);
int set_beam_energy(float MeV); /* in MeV!!!!*/
int set_beam_type_(int *type);
int set_beam_type(int type); /* 0 = electron, 1 = photon 2 = g7 */
map_obj_t get_map_obj(char *map, char *subsystem, char *item, int runno);
int get_beam_type_(int *btype);
int get_beam_type();


typedef struct {
  int npart;
  int nelec;
  part_t *elec[10];
  int nprot;
  part_t *prot[10];
  int nPip;
  part_t *Pip[10];
  int nPim;
  part_t *Pim[10];
  int ngam;
  part_t *gam[10];
  int nKp;
  part_t *Kp[10];
  int nKm;
  part_t *Km[10];
  int nneut;
  part_t *neut[10];
  int nDeut;
  part_t *Deut[10];
  int nUnk;
  part_t *Unk[10];
} sortpart_t;

/* an alternative to the above */
typedef struct {
  int Num;
  part_t * Ptr[20];     /* maximum of 20 particles of each type */
} SortPart_t;

int sortpart(clasPART_t *PART, sortpart_t *sortp);

typedef struct {
  int npart;
  int nelec;
  gpid_t *elec[10];
  int npos;
  gpid_t *pos[10];
  int nprot;
  gpid_t *prot[10];
  int nPip;
  gpid_t *Pip[10];
  int nPim;
  gpid_t *Pim[10];
  int ngam;
  gpid_t *gam[10];
  int nKp;
  gpid_t *Kp[10];
  int nKm;
  gpid_t *Km[10];
  int nneut;
  gpid_t *neut[10];
  int nDeut;
  gpid_t *Deut[10];
  int nTrit;
  gpid_t *Trit[10];
  int nantip;
  gpid_t *Antip[10];
  int nUnk;
  gpid_t *Unk[10];
} sortgpid_t;

typedef struct {
  int Num;
  gpid_t * Ptr[20];     /* maximum of 20 particles of each type */
} SortGPID_t;

int sortgpid(clasGPID_t *GPID, sortgpid_t *sortg);

/* gaussian distributions */

float gauss(float mean,float width);

/* Two-dimensional gaussian random number generator */
void gaussRndm2(double mean1,double mean2,double sigma1,double sigma2,double *rnd1,double *rnd2);

float gasdev();
void GaussSet(float mean,float width);

#endif
