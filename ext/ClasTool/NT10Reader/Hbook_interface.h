//////////////////////////////////////////////////////////////////////////
//
// This is directly copied from the THbookFile.cxx class definition,
// part of the ROOT system.
//
// There will be difficulty if you define this class, and ALSO define a
// copy of the THbookFile class, since the FORTRAN namespaces will collide.
//
//////////////////////////////////////////////////////////////////////////

#define PAWC_SIZE 2000000

//  Define the names of the Fortran common blocks for the different OSs

#ifndef WIN32
#  define pawc pawc_
#  define quest quest_
#  define hcbits hcbits_
#  define hcbook hcbook_
#  define rzcl rzcl_
int pawc[PAWC_SIZE];
int quest[100];
int hcbits[37];
int hcbook[51];
int rzcl[11];
#else
#  define pawc   PAWC
#  define quest  QUEST
#  define hcbits HCBITS
#  define hcbook HCBOOK
#  define rzcl   RZCL
extern "C" int pawc[PAWC_SIZE];
extern "C" int quest[100];
extern "C" int hcbits[37];
extern "C" int hcbook[51];
extern "C" int rzcl[11];
#endif

// int *iq, *lq;
// float *q;
// char idname[128];
// int nentries;
// char chtitl[128];
// int ncx,ncy,nwt,idb;
// int lcont, lcid, lcdir, ltab;
// float xmin,xmax,ymin,ymax;
// const Int_t kNRH  = 6;
// const Int_t kMIN1 = 7;
// const Int_t kMAX1 = 8;

// static Int_t lastentry = -1;

//  Define the names of the Fortran subroutine and functions for the different OSs

#ifndef WIN32
# define hlimit  hlimit_
# define hldir   hldir_
# define hropen  hropen_
# define hrend   hrend_
# define hrin    hrin_
# define hnoent  hnoent_
# define hgive   hgive_
# define hgiven  hgiven_
# define hgnpar  hgnpar_
# define hgnf    hgnf_
# define hgnt    hgnt_
# define hgntf   hgntf_
# define hgnt1   hgnt1_
# define rzink   rzink_
# define hdcofl  hdcofl_
# define hmaxim  hmaxim_
# define hminim  hminim_
# define hdelet  hdelet_
# define hntvar2 hntvar2_
# define hntvar3 hntvar3_
# define hbname  hbname_
# define hbnamc  hbnamc_
# define hbnam   hbnam_
# define hi      hi_
# define hie     hie_
# define hif     hif_
# define hij     hij_
# define hix     hix_
# define hijxy   hijxy_
# define hije    hije_
# define hcdir   hcdir_
# define hprnt   hprnt_

# define type_of_call
# define DEFCHAR  const char*
# define PASSCHAR(string) string
#else
# define hlimit  HLIMIT
# define hldir   HLDIR
# define hropen  HROPEN
# define hrend   HREND
# define hrin    HRIN
# define hnoent  HNOENT
# define hgive   HGIVE
# define hgiven  HGIVEN
# define hgnpar  HGNPAR
# define hgnf    HGNF
# define hgnt    HGNT
# define hgntf   HGNTF
# define hgnt1   HGNT1
# define rzink   RZINK
# define hdcofl  HDCOFL
# define hmaxim  HMAXIM
# define hminim  HMINIM
# define hdelet  HDELET
# define hntvar2 HNTVAR2
# define hntvar3 HNTVAR3
# define hbname  HBNAME
# define hbnamc  HBNAMC
# define hbnam   HBNAM
# define hi      HI
# define hie     HIE
# define hif     HIF
# define hij     HIJ
# define hix     HIX
# define hijxy   HIJXY
# define hije    HIJE
# define hcdir   HCDIR
# define hprnt   HPRNT

# define type_of_call  _stdcall
# define DEFCHAR  const char*, const int
# define PASSCHAR(string) string, strlen(string)
#endif

extern "C" void  type_of_call hlimit(const int&);
#ifndef WIN32
extern "C" void  type_of_call hropen(const int&,DEFCHAR,DEFCHAR,DEFCHAR,
                        const int&,const int&,const int,const int,const int);
extern "C" void  type_of_call hrend(DEFCHAR,const int);
#else
extern "C" void  type_of_call hropen(const int&,DEFCHAR,DEFCHAR,DEFCHAR,
                        const int&,const int&);
extern "C" void  type_of_call hrend(DEFCHAR);
#endif

extern "C" void  type_of_call hrin(const int&,const int&,const int&);
extern "C" void  type_of_call hnoent(const int&,const int&);
#ifndef WIN32
extern "C" void  type_of_call hgive(const int&,DEFCHAR,const int&,const float&,const float&,
   const int&,const float&,const float&,const int&,const int&,const int);
#else
extern "C" void  type_of_call hgive(const int&,DEFCHAR,const int&,const float&,const float&,
   const int&,const float&,const float&,const int&,const int&);
#endif

  //SUBROUTINE HGNT1(IDD,BLKNA1,VAR,IOFFST,NVAR,IDNEVT,IERROR)
#ifndef WIN32
extern "C" void  type_of_call hgiven(const int&,DEFCHAR,const int&,DEFCHAR,
   const float&,const float&,const int,const int);
extern "C" void  type_of_call hgnt1(const int&,DEFCHAR,DEFCHAR,const int&,const int&,const int&,const int&,const int,const int);
#else
extern "C" void  type_of_call hgiven(const int&,DEFCHAR,const int&,DEFCHAR,
   const float&,const float&);
extern "C" void  type_of_call hgnt1(const int&,DEFCHAR,DEFCHAR,const int&,const int&,const int&,const int&);
#endif

#ifndef WIN32
extern "C" void  type_of_call hntvar2(const int&,const int&,DEFCHAR,DEFCHAR,DEFCHAR,int&,int&,int&,int&,const int,const int, const int);
extern "C" void  type_of_call hntvar3(const int&,const int&,DEFCHAR, const int);
#else
extern "C" void  type_of_call hntvar2(const int&,const int&,DEFCHAR,DEFCHAR,DEFCHAR,int&,int&,int&,int&);
extern "C" void  type_of_call hntvar3(const int&,const int&,DEFCHAR);
#endif

#ifndef WIN32
extern "C" void  type_of_call hbnam(const int&,DEFCHAR,const int&,DEFCHAR,const int&,const int, const int);
extern "C" void  type_of_call hbname(const int&,DEFCHAR,const int&,DEFCHAR,const int, const int);
#else
extern "C" void  type_of_call hbnam(const int&,DEFCHAR,const int&,DEFCHAR,const int&);
extern "C" void  type_of_call hbname(const int&,DEFCHAR,const int&,DEFCHAR);
#endif

extern "C" void  type_of_call hgnpar(const int&,const char *,const int);
extern "C" void  type_of_call hgnf(const int&,const int&,const float&,const int&);
extern "C" void  type_of_call hgnt(const int&,const int&,const int&);
extern "C" void  type_of_call hgntf(const int&,const int&,const int&);
extern "C" void  type_of_call rzink(const int&,const int&,const char *,const int);
extern "C" void  type_of_call hdcofl();
extern "C" void  type_of_call hmaxim(const int&,const float&);
extern "C" void  type_of_call hminim(const int&,const float&);
extern "C" void  type_of_call hdelet(const int&);
extern "C" float type_of_call hi(const int&,const int&);
extern "C" float type_of_call hie(const int&,const int&);
extern "C" float type_of_call hif(const int&,const int&);
extern "C" float type_of_call hij(const int&,const int&,const int&);
extern "C" void  type_of_call hix(const int&,const int&,const float&);
extern "C" void  type_of_call hijxy(const int&,const int&,const int&,const float&,const float&);
extern "C" float type_of_call hije(const int&,const int&,const int&);
#ifndef WIN32
extern "C" void  type_of_call hcdir(DEFCHAR,DEFCHAR ,const int,const int);
extern "C" void  type_of_call hldir(DEFCHAR,DEFCHAR ,const int,const int);
#else
extern "C" void  type_of_call hcdir(DEFCHAR,DEFCHAR);
extern "C" void  type_of_call hldir(DEFCHAR,DEFCHAR);
#endif
extern "C" void  type_of_call hprnt(const int&);

