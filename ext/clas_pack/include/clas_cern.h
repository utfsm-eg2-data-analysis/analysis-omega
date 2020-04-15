/* 
 * prototypes for c_cern package
 *
 * clas c interface to hbook and hplot
 *
 *  jm, ejw, 8-jan-1998
 *
 */


#ifdef __cplusplus
extern "C" {
#endif


void hlimit(int size);
void hrput(int id, char *file, char *opt);
void hf1(int id,float data,float weight);
void hf1e(int id, float data, float weight, float error);
void hf2(int id,float data1,float data2,float weight);
void hdelet(int id);
void hrin( int id, int icycle , int iofset );
void hfn(int id, float data[]);
void hfnt(int id);
void hfithn(int id, char *chfun, char *chopt, int np, float par[],
        float step[], float pmin[], float pmax[], float sigpar[], float *chi2);
void hunpak(int histo,float contents[],char choice[], int num);
void hidopt( int id, char *chopt);
void hpak(int histo,float contents[]);
void hrget( int id, char *chfile, char *chopt);
void hldir(char dir[],char flag[]);
void hmdir(char dir[],char flag[]);
void hcdir(char dir[],char flag[]);
void hropen(int lun, char *name, char*filename, char*status, int stor,
        int istat);
void hrout(int num, int icycle, char*opt);
void hrend(char*filename);
void hreset(int no, char* opt);
void hbook2(int no, char*name, int xbins, float xmin, float xmax, int ybins,
                 float ymin, float ymax, float weight);
void hbook1(int no, char*name, int nbins, float min, float max, float v);
void hbookn(int id, char *CHTITL,int NVAR, char *CHRZPA,int NWBUFF,char*CHTAGS);
void hbarx(int id);
void hfill(int no, float xvalue, float yvalue, float weight);
void hpake(int id,float errors[]);
void hunpke(int id,float contents[],char choice[],int num);
void hbslix(int id,int slices,float weight);
void hbsliy(int id,int slices,float weight);
void hcopy(int id1,int id2,char title[]);

  /* macros for choice variable*/
#define HSTATI_MEAN 1
#define HSTATI_STDEV 2
#define HSTATI_NEQUIV 3
float hstati_(int *id, int *icase, char *choice, int *num, int choicesize);
float hstati(int id, int icase, char *choice, int num);

float hx_(int *id, float *x);
float hx(int id, float x);
void hxi(int id, float x, int *bin);
float hsum(int id);


  float hrndm1_(int *);
  float hrndm2_(int *,float *,float *);
float hrndm1(int id);
float hrndm2(int id,float *x, float *y);

void hopera(int id1,char *oper,int id2, int id3,float scale1,float scale2);

/* hplot routines located in file clas_hplot.c - Keep these in a separate file!!!! */

void hplint(int no);
void hplego(int no, float theta, float phi);
void hplcon(int histonum, int x, int y);
void hplzon(int x, int y, int num, char *opt);
void hplot(int no, char*chopt, char*chcase, int num);
void iuwk(int num1, int num2);
void hplcap(int unit);
void hplzon(int nx, int ny, int fistplotted, char *option);
void hbnt(int id,char *name,char *opt);
void hbname(int id,char *name,void *variable,char *form);
#ifdef __cplusplus
}
#endif

