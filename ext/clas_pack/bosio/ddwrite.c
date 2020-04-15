/*DECK ID>, DDWRITE.

  len - in words

 */

#include "fpack.h"
#include "ioincl.h"

/* #define COND_DEBUG  */
/* #define DEBUG */
#include "dbgpr.h"


#define min(a,b) (a<b)?a:b
#define max(a,b) (a>b)?a:b

#define START_NEW_PHYSREC_ \
  bufout[0]=BIOS_RECL/sizeof(int);\
  bufout[1]=IP=ifree=2;\
  BIOS_NPHYSREC++;\
  BIOS_NSEGM=1;

#define WRITE_BUF_TO_DISK_ \
  error=bosout(descriptor,bufout);\
  if(error!=0){\
    printf("ddWrite: error writing to disk : %i\n",error);\
    fflush(stdout);return error;\
  };

static char  *rune = "RUNE", *vent = "VENT";

/******************************************************/
/*     DD -> FPACK file                               */
/******************************************************/

int ddWrite(int descriptor, int len, int *ev)
{
  BOSIOptr BIOstream;
  int *bufout;
  int ifree,error,lenh,lenb,ncop,nfopen,lrlen;
  int ip,jp,kp; /* Ukazatel` na record segment header i data header v DD bufere */
  int dathead[70]; /* intermediate buffers */
  char *fmt, *ch;
  int i;

  DPR("\nSTART OF ddWrite >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");


  BIOstream = (BOSIOptr)descriptor;	/* set pointers */
  bufout       = BIOS_BUFP;
  error     = nfopen = 0;
  lrlen     = ev[irNWRD]+RECHEADLEN;
  if (len < lrlen)
  {
    printf("ddWrite: FIFO length (%i) < Event length (%i) -> Corrupted\nReturn EBIO_CORREVENT\n",
           len,ev[irNWRD]+RECHEADLEN);
    return EBIO_CORREVENT;
  }
  DPR(">>> Got following event ============================================================\n");
  PRLR(ev);
  DPR(">>> ================================================================================\n");
  
  DPR1(">>> At the beginning IP=%i\n",IP);
  if(IP == 0)	/* allocate output buffer */
  {
    DPR1(">>> First time writing -> allocate I/O buffer RECL=%i\n",BIOS_RECL);
    bufout = BIOS_BUFP = (int *)malloc(BIOS_RECL);
    BIOS_NPHYSREC = 0;
    BIOS_NLOGREC = 0;
    START_NEW_PHYSREC_
  }

/*********************
 * check unit status *
 *********************/

  CHECK_OUTPUT_UNIT(descriptor);
   
/*********************
 * add record header *
 *********************/
 
  if(bufout[1]+81 > bufout[0])	/* we don't know data header length, let 70 */
  { /* output buffer to disk and start new one  */
    DPR(">>> Has no space for 2 headers for new logical record -> start new physical record\n");
    PRPR(bufout);
    WRITE_BUF_TO_DISK_
    START_NEW_PHYSREC_
/*     BIOS_NSEGM--; */
  }

 
  BIOS_NSEGM++;
  BIOS_NLOGREC++;

  /* Ok. there is space in I/O buffer for this whole record */

  DPR(">>> Making Record header\n");
  /* copiruem record header iz sobytiya ... */
  bcopy((char *)ev, (char *)BIOS_RECHEAD, RECHEADLEN*sizeof(int));
  /* ... i modificiruem ego */
  BIOS_RECHEAD[irPTRN ] = SWAP;	          /* the pattern to recognize byte swapping     */
  BIOS_RECHEAD[irFORG ] = LOCAL*16;        /* format code: 1-IEEE,2-IBM,3-VAX,4-DEC      */
  BIOS_RECHEAD[irNRSG ] = 100*(BIOS_NPHYSREC+0)+(BIOS_NSEGM-1); /* #logrec*100 + #segment*/
/*BIOS_RECHEAD[irNAME1] = *((int *)rune);*//* event name - part 1                        */
/*BIOS_RECHEAD[irNAME2] = *((int *)vent);*//* event name - part 2                        */
/*BIOS_RECHEAD[irNRUN ] =  ; */            /* run number                                 */
/*BIOS_RECHEAD[irNEVNT] =  ; */            /* event number                               */
  BIOS_RECHEAD[irNPHYS] = 0;               /* # of several phys. records in one logical  */
/*BIOS_RECHEAD[irTRIG ] =  ; */            /* Trig pattern                               */
/*BIOS_RECHEAD[irCODE ] = 0; */            /* segment code: 0-complete segment,1-first,..*/
  BIOS_RECHEAD[irNWRD ] = 0;               /* the number of words in this record segment */
  /* copiruem vzad */

  DPR1(">>> Add Record header to I/O buffer at %i index\n",IP);
/****************** ADD FIRST RECHEAD *********************/
  bcopy((char *)BIOS_RECHEAD, (char *)&bufout[IP], RECHEADLEN*sizeof(int));
  bufout[1] = bufout[1] + RECHEADLEN;	/* update physrec length info               */
  JP     = IP + RECHEADLEN;     /* set data header pointer in I/O buffer    */
  jp     =  0 + RECHEADLEN;     /* set data header pointer in DD  buffer    */
  ifree  = JP;                  /* Ukazatel` na pervoe svobodnoe slovo v I/O bufere */
/****************** ADD FIRST RECHEAD *********************/


/*****************
 * loop on banks *
 *****************/
 
  /* loop for banks in DD buffer  nextjp(jp)*/
  DPR(">>> Start loop for banks in DD buffer\n");
  do
  {
    if ( (jp < lrlen) && (jp > lrlen-10) )
    {
      printf("ddWrite : Trailing %i garbage words detected -> skipped\n",
             lrlen-jp);
	  error = EBIO_SKIPTRAILGARB;
      break;
    }
	if ( jp >= lrlen ) {
	  printf (">>>>>>>>> END OF LOGICAL RECORD jp=%d lrlen=%d\n",jp,lrlen);
	  break;
	}
    /*******************
     * add data header *
     *******************/
    lenh = ev[jp];          /* Dlina headera dannyh */
    lenb = ev[jp+idDATA];   /* Dlina dannyh         */
	  JP = ifree;           /* Nachalo headera      */
	  KP = JP + lenh;       /* Nachalo dannyh       */
	  DPR7(">>> Processing bank at ev[%i] : lenh=%i lenb=%i ifree=%i bufout[0]=%i recl=%i\n JP=%i"
           ,jp,lenh,lenb,ifree,bufout[0],BIOS_RECL,JP);
      PRDH(&ev[jp]);
	  DPR2(">>> %i words of free space left in I/O buffer, we need at least %i\n",
           bufout[0]-ifree,lenh+1);

      if( (ifree+lenh+1) > bufout[0] ) /* there is no space for data header */
      { /* */
        /* Update record segment header and write to disk this buffer */
        DPR(">>> There is no space for data header -> Start new I/O buffer\n");
        if(bufout[IP+irCODE] <= 1) 
          bufout[IP+irCODE]++;                     /* update record segment code */
        bufout[IP+irNWRD] = ifree-(IP+RECHEADLEN); /* update # of words in the record segment */
        BIOS_RECHEAD[irCODE] = bufout[IP+irCODE];       /* save   record segment code */
        PRPR(bufout);
        WRITE_BUF_TO_DISK_
        START_NEW_PHYSREC_
        /* Update record segment header */
        BIOS_RECHEAD[irNRSG] = 100*(BIOS_NPHYSREC+0)+(BIOS_NSEGM-1);
        BIOS_RECHEAD[irNPHYS]++;      /* # of several phys. records in one logical */
        BIOS_RECHEAD[irNWRD] = 0;     /* the number of words in this record segment */
        /* copy record segment header to I/O buffer */
        bcopy((char *)BIOS_RECHEAD, (char *)&bufout[IP], RECHEADLEN*sizeof(int)); 
 
        bufout[1] = bufout[1] + RECHEADLEN;   /* update length info */
        JP = IP + RECHEADLEN;           /* set data header pointer in I/O buffer */
        ifree  = JP;            /* Ukazatel` na pervoe svobodnoe slovo v I/O bufere */
 
      }
      DPR1(">>> Coping data header to the I/O buffer to bufout[%i]\n",JP);
      /* copiruem data header */
	  ncop = ev[jp];

	if ( jp >= lrlen-3 ) {
	  printf (">>>>>>>>> END OF LOGICAL RECORD jp=%d lrlen=%d <<<<<<<<\n",jp,lrlen);
	  break;
	}
	  if (ncop < 10 || ncop > 11) {
		printf("BAD BANK !!! =========================================================\n");
		printf("Call bcopy(%8.8X,%8.8X,%d) headsize %d words JP=%d jp=%d lrlen=%d\n",
			   (char *)&ev[jp], (char *)&bufout[JP], ncop*sizeof(int), ncop ,JP,jp,lrlen);
		printf("BAD BANK !!! =========================================================\n");
		prdathead(&ev[jp]);
		printf("BAD BANK !!! =========================================================\n");
		prlogrec(ev);
		printf("BAD BANK !!! =========================================================\n");
	  }
      bcopy ( (char *)&ev[jp], (char *)&bufout[JP], ncop*sizeof(int) ); 

      bufout[1]         += ncop; /* update physical record length info */
      bufout[IP+irNWRD] += ncop; /* update number of words in this record segment */
      kp = jp + ncop;         /* set data pointer v  DD bufere */
      KP = JP + ncop;         /* set data pointer v I/O bufere */
      ifree  = KP;            /* Ukazatel` na pervoe svobodnoe slovo v I/O bufere */
 
      /************
       * add data *
       ************/
      DPR(">>> Start adding data to the I/O buffer\n");
      do
      { /*  */
        /* copy as many data as possible */
        ncop = min(lenb,(bufout[0]-ifree)); 
        bcopy((char *)&ev[kp], (char *)&bufout[KP], ncop<<2); /* copy data */
        DPR4(">>> Copied %i words from ev[%i] to bufout[%i] ; left %i words\n",ncop,kp,KP,lenb-ncop);
        bufout[1]         += ncop; /* update physical record length info               */
        bufout[IP+irNWRD] += ncop; /* update number of words in this record segment    */
        kp             += ncop; /* set data pointer v  DD bufere                    */
        KP             += ncop; /* set data pointer v I/O bufere                    */
        ifree          += ncop; /* Ukazatel` na pervoe svobodnoe slovo v I/O bufere */
		lenb           -= ncop; /* Ostalos` skopirovat` dannyh iz etogo banka       */
        /* bufout[JP+(8-1)] = 0; *//* words in previous datasegments                   */
        bufout[JP+idDATA]   = ncop; /* words in this datasegment                        */
        
        if(lenb<0)
          {
            printf("ddWrite : impossible things happens : lenb<0\n");
			return EBIO_INTERNAL;
          }
        if(lenb==0)             /* Vsya li data umestilas` ?                     */
          { /* --- Da ! --- perehodim k sleduyuschemu banku -------------------  */
            DPR(">>> All data copied -> goto next bank\n");
            if (bufout[JP+idCODE]!=0) bufout[JP+idCODE]=3; /* kol` ne polny to posledniy */
            JP = ifree ;                       /* ukazatel` na sleduyuschiy bank */
            jp = nextjp(jp);                   /* ukazatel` na sleduyuschiy bank */
            break;                             /* all data are written           */
          }
        

        /* if data are left, write both headers again and next piece of data     */
        DPR(">>> Some data left but space in the I/O buffer exhosts -> goto next I/O buffer\n");
        if (bufout[JP+idCODE] <= 1) bufout[JP+idCODE]++; /* update data segment code   */
        dathead[idCODE]=bufout[JP+idCODE];
        if (bufout[IP+irCODE] <= 1) bufout[IP+irCODE]++; /* update record segment code */
        BIOS_RECHEAD[irCODE]=bufout[IP+irCODE];
        DPR(">>> Write to disk filled I/O buffer\n");
        PRPR(bufout);
        /* zapomnim dataheader */
        bcopy ( (char *)&bufout[JP], (char *)dathead, lenh*sizeof(int)); /* BUG WAS HERE: *sizeof(int) was missed */
        /* i otkorrektiruem ego */
        dathead[idNPREV] = kp - (jp+ev[jp]);      /* words in previous datasegments  */
        dathead[idDATA]  = 0;                     /* zapisano dannyh v etom segmente */
        
        WRITE_BUF_TO_DISK_
        START_NEW_PHYSREC_
        /* Update record segment header */
        BIOS_RECHEAD[irNRSG] = 100*(BIOS_NPHYSREC+0)+(BIOS_NSEGM-1);
        BIOS_RECHEAD[irNPHYS]++;         /* # of several phys. records in one logical */
        BIOS_RECHEAD[irNWRD] = 0;        /* the number of words in this record segment */
        /* copy record segment header to I/O buffer */
        DPR(">>> Copy Record segment header to I/O buffer\n");
        bcopy((char *)BIOS_RECHEAD, (char *)&bufout[IP], RECHEADLEN*sizeof(int)); 
 
        bufout[1] = bufout[1] + RECHEADLEN;   /* update length info */
        JP = IP + RECHEADLEN;           /* set data header pointer in I/O buffer */
        ifree  = JP;            /* Ukazatel` na pervoe svobodnoe slovo v I/O bufere */

        /* copy data segment header to I/O buffer                                   */
        DPR(">>> Copy Data segment header to I/O buffer\n");
        bcopy((char *)dathead, (char *)&bufout[ifree], lenh*sizeof(int));
        bufout[1]         += lenh; /* update length info in physrecord                 */
        bufout[IP+irNWRD] += lenh; /* update number of words in this record segment    */
        ifree          += lenh; /* ukazatel` na svobodnoe mesto                     */
        KP      = ifree;        /* set data pointer v I/O bufere                    */
        /*  */ 
      } 
      while(1 == 1);       /* end of add data loop */
      DPR3(">>> Finish processing This bank; jp=%i len=%i nextip=%i\n"
        ,jp,len,ev[irNWRD]+RECHEADLEN);
  } 
  while (jp < lrlen); /* end of loop for banks in DD buffer */
  DPR(">>> All banks are copied to I/O buffer\n");

  if (bufout[IP+irCODE] != 0) bufout[IP+irCODE]=3; /* kol` ne polny to posledniy */
  PRLR(&bufout[IP]);
  /* Ustanovim ukazateli na konec zapisi */
  bufout[1] = IP  = ifree;

  DPR1(">>> At end IP=%i\n",IP);
  DPR("END OF ddWrite <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");

  if (nfopen) return EBIO_NEWFILEOPEN;
  return(error);
}

 
/******************************************************/
/*                                                    */
/******************************************************/
 
int ddFlush(int descriptor)
{ 
  int error=0, *bufout, ifree;
  BOSIOptr BIOstream; 

  BIOstream = (BOSIOptr)descriptor; 	/* set pointers */ 
  bufout = BIOS_BUFP;

  if(IP == 0)	/* allocate output buffer */
  {
    DPR1(">>> First time writing -> allocate I/O buffer RECL=%i\n",BIOS_RECL);
    bufout = BIOS_BUFP = (int *)malloc(BIOS_RECL);
    bufout[0] = BIOS_RECL/sizeof(int);
    bufout[1] = 2;
    IP = 2;
    BIOS_NPHYSREC = 0;
    BIOS_NLOGREC = 0;
    BIOS_NSEGM = 1;
  }
 
 
/*********************
 * check unit status *
 *********************/
 
  if(BIOS_CURSTA == 0 || BIOS_CURSTA == 5) /* undef or rewind - switch to write */
  {
    BIOS_CURSTA  = 3;
    BIOS_RECFMTW = 0;
    BIOS_OUTNUM  = 0;
  }
  else if (BIOS_CURSTA == 3)
  {
    ;
  }
  else
  {
    printf("ddFlush: Reading of the next record are stopped\n");
    BIOS_CURSTA = 2;  /* force stop of reading if writing is not more possible */
    return(EBIO_EOF);
  }
  WRITE_BUF_TO_DISK_
  START_NEW_PHYSREC_
  return(error);
}
