#ifndef _BIOFUN_

#ifdef	__cplusplus
extern "C" {
#endif

#define	getBOSIO()	(BOSIOptr) MALLOC(sizeof(BOSIO))
#define	getNET()	(Nptr) MALLOC(sizeof(NET))

/* ../src/bosopen.c: */
int bosopen_(char *file, char *flag, int *descriptor, int filen, int fllen);
int bosOpen(char *file, char *flag, int *descriptor);
BOSIOptr  getDEFBOSIO();
BOSIOptr fillDEFBOSIO(BOSIOptr lun); 
char *getSplitFN(char *file);
int bosOPEN(char *file, char *flag, int *descriptor);
#define BOSREOPEN(d) bosOPEN( ((BOSIOptr)d)->finame, ((BOSIOptr)d)->flag, &d)
int fpopen(int descriptor, char *action);
int bosnres(int descriptor, int client, int stream, int mode);
int bosclose_(int *descriptor);
int bosClose(int descriptor);
int bosIoctl(int descriptor, char *option, void *arg);
char *bositoa(int number);      /* integer -> char string */
#define bosGETFNAME(d) ((BOSIOptr)d)->finame

/* ../src/bosread.c: */
int bosread_(int *descriptor, int *jw, char *list, int lilen);
int bosRead(int descriptor, int *jw, char *list);
int bosins(int descriptor, int *jw, char *list);

/* ../src/ddgetlogrec.c: */
int ddGetLogRec(int descriptor, int **bufp, int *evlen, int *freeflag);

/* ../src/bosin.c: */
int bosin(int descriptor, int *ntot);

/* ../src/bosrewin.c: */
int bosrewind_(int *descriptor);
int bosRewind(int descriptor);

/* ../src/boswrite.c: */
int boswrite_(int *descriptor, int *jw, char *list, int lilen);
int bosWrite(int descriptor, int *jw, char *list);

/* ../src/bosout.c: */
int bosout(int descriptor, int *buf);

/* ../src/ddwalk.c: */
int prphrec  (int *p);
int prrechead(int *p);
int prdathead(int *p);
int prdatbody(int *p);
int dumplogrec(int *p, int level);
int ddCheckRec(int *p);
int ddCheckBlock(int * p);

/* ../src/ddwrite.c: */
int ddWrite(int descriptor, int, int *);
int ddFlush(int descriptor);


/* ../src/cget.c: */
int cget(int *lunptr, int *ircn, int *medium, int *ntot, int *buffer);

/* ../src/copen.c: */
int copen(int *stream, char *filename, char *options, int medium, int blksize,
          int *bufptr, int reopen);

/* ../src/cput.c: */
int cput(int stream, int ircn, int ntot, int *buffer, int medium);

/* ../src/cclose.c: */
void cclose(int lunptr, int bufptr, int medium);

/* ../src/closec.c: */
#if defined(IBMMVS) || defined(IBMVM)
void closec(int *iclptr,int *streamptr,int **retptrp);
#else
void closec(int *iclptr,int *streamptr,int *retptr);
#endif

/* ../src/crewnd.c: */
void crewnd(int lunptr, int medium);

/* ../src/fparm.c: */
int  fparm_(char *string, int len);
int  FParm (char *string, int *dsc);
void frbos_(int *jw, int *unit, char *list, int *err, int len); 
void fwbos_(int *jw, int *unit, char *list, int *err, int len); 
void fpstat_();
void fseqr_(char *daname, int *err, int len); 
void fseqw_(char *daname, int len);

void fswap_(int *, int *);

/* ../src/openc.c: */
#if defined(IBMMVS) || defined(IBMVM)
void openc(int **iclptrp,int **strptrp,char *name,char *serv_host,
		   char *options,int *ispc,int *nr1,int *nr2);
#else
void openc(int *iclptr,int *strptr,char *name,char *serv_host,
		   char *options,int *ispc,int *nr1,int *nr2);
#endif

/* ../src/readc.c: */
#if defined(IBMMVS) || defined(IBMVM)
void readc(int *iclptr,int *streamptr,int *skipptr,int *sizeptr,
		   int **bufferp,int **retptrp);
#else
void readc(int *iclptr,int *streamptr,int *skipptr,int *sizeptr,
		   int *buffer,int *retptr);
#endif

/* ../src/rewinc.c: */
#if defined(IBMMVS) || defined(IBMVM)
void rewinc(int *iclptr,int *streamptr,int **retptrp);
#else
void rewinc(int *iclptr,int *streamptr,int *retptr);
#endif

/* ../src/stopsc.c: */
#if defined(IBMMVS) || defined(IBMVM)
void stopsc(int *iclptr, int **retptrp);
#else
void stopsc(int *iclptr, int *retptr);
#endif

/* ../src/writec.c: */
#if defined(IBMMVS) || defined(IBMVM)
void writec(int *iclptr,int *streamptr,int *ibyteptr,int *sizeptr,
			int *buffer,int **retptrp);
#else
void writec(int *iclptr,int *streamptr,int *ibyteptr,int *sizeptr,
			int *buffer,int *retptr);
#endif

#ifdef	__cplusplus
}
#endif

#define _BIOFUN_
#endif










