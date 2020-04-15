
/* etbosio.c - high level interface to handle both BOS arrays and ET buffer */

#include <stdio.h>
#include "bos.h"
#include "etbosio.h"


#define irCODE   9       /* from bosio.h */
#define irNWRD  10       /* from bosio.h */
#define RECHEADLEN 11    /* from bosio.h */

#define IFET if(jw[1] != MAGIC)




int
etOpen(int *jw, int nbcs, ETSYS *sysptr)
{
  ETSYS *sys = sysptr;

  sys->nddl = 0;
  sys->nwords = nbcs - 1;
  sys->indsys = nbcs;
  jw[irCODE] = (int)sys;

  return(0);
}


int
etClose(int *jw)
{
  jw[irCODE] = 0;

  return(0);
}



int
etSysalloc(ETSYS **sysptr)
{
  ETSYS *ptr;

  ptr = (ETSYS *) malloc(sizeof(ETSYS));
  *sysptr = ptr;

  return(0);
}


int
etSysfree(ETSYS *sysptr)
{
  free(sysptr);

  return(0);
}



void 
etinit_(int *jw, int *ndim)
{
  etInit(jw,*ndim);
}

int
etInit(int *jw, int nbcs)
{
  IFET
  {
    printf("etInit: please use etOpen()/etClose() for the ET buffer\n");
    exit(0); /*return(ARRAY_NOT_INITIALIZED);*/
  }
  else
  {
    printf("etInit: call bosInit()\n");
    return(bosInit(jw,nbcs));
  }  

  return(0);
}

void
etnformat_(int *jw, char *name, char *fmt, int lename, int lenfmt)
{
  char *nam, *fm;
 
  nam = (char *) MALLOC(lename+1);
  strncpy(nam,name,lename);
  nam[lename] = '\0';
  fm = (char *) MALLOC(lenfmt+1);
  strncpy(fm,fmt,lenfmt);
  fm[lenfmt] = '\0';
  etNformat(jw,nam,fm);
  FREE(fm);
  FREE(nam);
}

int
etNformat(int *jw, char *name, char *fmt)
{
  IFET
  {
    ETSYS *sys = (ETSYS *) jw[irCODE];
    int i;

    if(strlen(fmt) > STRLEN)
    {
      printf("etNformat: too long format definition len=%d > %d\n",
              strlen(fmt),STRLEN); fflush(stdout);
      return(-1);
    }

    for(i=0; i<sys->nddl; i++)
    {
      if(!strncmp(name,sys->ddl[i].name,sys->ddl[i].nname))
      {
        /* replace old format definition */
        strcpy(sys->ddl[i].fmt,fmt);
        sys->ddl[i].nfmt = strlen(fmt);
/*
printf("etNformat 1: sys->nddl=%d name>%s< fmt>%s<\n",
        sys->nddl,sys->ddl[i].name,sys->ddl[i].fmt); fflush(stdout);
*/
        return(0);
      }
    }

    /* add new format definition */
    if(sys->nddl >= NDDL)
    {
      printf("etNformat: too many bank definitions sys->nddl=%d >= %d\n",
              sys->nddl,NDDL);
      return(-1);
    }

    strcpy(sys->ddl[sys->nddl].name,name);
    strcpy(sys->ddl[sys->nddl].fmt,fmt);
    sys->ddl[sys->nddl].nname = strlen(sys->ddl[sys->nddl].name);
    sys->ddl[sys->nddl].nfmt = strlen(sys->ddl[sys->nddl].fmt);

    if(!strncmp(sys->ddl[sys->nddl].fmt,"B8",2)) sys->ddl[sys->nddl].lfmt = 4;
    else if(!strncmp(sys->ddl[sys->nddl].fmt,"B08",3)) sys->ddl[sys->nddl].lfmt = 4;
    else if(!strncmp(sys->ddl[sys->nddl].fmt,"B16",3)) sys->ddl[sys->nddl].lfmt = 2;
    else sys->ddl[sys->nddl].lfmt = 1;
    
    sys->ddl[sys->nddl].ncol = 0;
/*
printf("etNformat 2: sys->nddl=%d name>%s< fmt>%s<\n",
        sys->nddl,sys->ddl[sys->nddl].name,sys->ddl[sys->nddl].fmt); fflush(stdout);
*/
    sys->nddl ++;

    return(0);
  }
  else
  {
    return(bosNformat(jw, name, fmt));
  }
}


int
etndrop_(int *jw, char *name, int *nr, int lename)
{
  int status;
  char *nam;
 
  nam = (char *) MALLOC(lename+1);
  strncpy(nam,name,lename);
  nam[lename] = '\0';
  status = etNdrop(jw,nam,*nr);
  FREE(nam);
  return(status);
}

int
etNdrop(int *jw, char *name, int nr)
{
  IFET
  {
    ETSYS *sys = (ETSYS *) jw[irCODE];
    FpackheadPtr b;
    int *w, nama, len;
/*
printf("etNdrop reached: name >%4.4s< nr %d\n",name,nr);
*/
    nama = *(int *)name;

    len = jw[irNWRD]+RECHEADLEN;
    w = jw + RECHEADLEN; /* skip record header */
    do
    {
      b = (FpackheadPtr)w;
/*
printf("etNdrop: b->name=%4.4s\n",(char *)&b->name);
printf("etNdrop: b->nr=%d\n",b->nr);
printf("etNdrop: b->ndata=%d\n",b->ndata);
*/
      if(b->name == nama && b->nr == nr)
      {
        b->name = *((unsigned long *)"++++");
/*
printf("etNdrop: droped, new name >%4.4s<\n",&b->name);
*/
        return(0);
      }
      w += b->nhead + b->ndata;
    } while(w < jw + len);

    return(0);
  }
  else
  {
    return(bosNdrop(jw, name, nr));
  }
}


int 
etncreate_(int *jw, char *name, int *nr, int *ncol, int *nrow, int lename)
{
  int status;
  char *nam;
 
  nam = (char *) MALLOC(lename+1);
  strncpy(nam,name,lename);
  nam[lename] = '\0';
  status = etNcreate(jw,nam,*nr,*ncol,*nrow);
  FREE(nam);
  return(status);
}

int
etNcreate(int *jw, char *name, int nr, int ncol, int nrow)
{
  IFET
  {
    ETSYS *sys = (ETSYS *) jw[irCODE];
    FpackheadPtr b;
    int *w, nama, len, i;

/*
printf("NOT IMPLEMENTED YET\n");
return(0);
*/

    /* scan all existing bank to check is that bank exist */

    nama = *(int *)name;
    len = jw[irNWRD]+RECHEADLEN;
    w = jw + RECHEADLEN; /* skip record header */
    do
    {
      b = (FpackheadPtr)w;
      if(b->name == nama && b->nr == nr)
      {
/*
printf("b->name=%4.4s\n",(char *)&b->name);
printf("b->nr=%d\n",b->nr);
printf("b->ndata=%d\n",b->ndata);
*/
        printf("etNcreate: ERROR - bank >%4.4s< exist already\n",name);
        return(0);
        /*return(((int)&b->nhead-(int)jw)/4+b->nhead);*/
      }
      w += b->nhead + b->ndata;
    } while(w < jw + len);


    /* get format */

    for(i=0; i<sys->nddl; i++)
    {
      /*printf(">>> %d >%s< = >%s<  %d\n",i,name,sys->ddl[i].name,sys->ddl[i].nname);*/
      if(!strncmp(name,sys->ddl[i].name,sys->ddl[i].nname))
      {
        /* create bank; 'w' points now to first free word  */
        int j, nwfmt, fmtlen;
        char *ch;

        fmtlen = 4 / sys->ddl[i].lfmt;
        nwfmt = (sys->ddl[i].nfmt + 3) / 4;

        /* check how much space left */
        if(jw[irNWRD] + (9 + nwfmt) + ((ncol*nrow*fmtlen + 3) / 4) > sys->nwords)
        {
/*
          printf("etNcreate: cannot create bank - not enough space\n");
          printf("etNcreate: required length %d for bank >%4.4s<\n",
                                            ((ncol*nrow*fmtlen + 3) / 4),name);
          printf("etNcreate: the number of words left %d\n",sys->nwords-jw[irNWRD]);
*/
          return(0);
        }

        /* fill bank header */
        b = (FpackheadPtr)w;
        b->nhead = 9 + nwfmt; /* the number of long words in a header */
        b->name = nama;                         /* bank name NAME */
        b->namext = *((unsigned long *)"    "); /* name extension NAMEXT */
        b->nr = nr;                             /* bank number NR */
        b->ncol = ncol;                         /* the number of columns NCOL */
        b->nrow = nrow;                         /* the number of rows NROW */
        b->code = 0;                            /* data segment code */
        b->nprev = 0;       /* the number of data long words in previous bank */
        b->ndata = (ncol*nrow*fmtlen + 3) / 4;  /* the number of data long words in this bank NDATA */
        ch = (char *)&b->frmt;                  /* format description */
        strcpy(ch,sys->ddl[i].fmt);
        for(j=sys->ddl[i].nfmt; j<(nwfmt*4); j++) ch[j] = ' ';

        jw[irNWRD] += (b->nhead + b->ndata);

        return(((int)&b->nhead-(int)jw)/4+b->nhead);
      }
    }

    printf("etNcreate: ERROR - format not defined for bank >%4.4s<\n",name);
    return(0);

  }
  else
  {
    return(bosNcreate(jw, name, nr, ncol, nrow)); /* regular BOSIO */
  }

}


int
etnlink_(int *jw, char *name, int *nr, int lename)
{
  int ind;
  char *nam;
 
  nam = (char *) MALLOC(lename+1);
  strncpy(nam,name,lename);
  nam[lename] = '\0';
  ind = etNlink(jw,nam,*nr);
  FREE(nam);
  return(ind);
}

int
etNlink(int *jw, char *name, int nr)
{
  IFET
  {
    ETSYS *sys = (ETSYS *) jw[irCODE];
    FpackheadPtr b;
    int *w, nama, len;
/*
printf("etNlink reached: name >%4.4s< nr %d\n",name,nr);
*/
    nama = *(int *)name;

    len = jw[irNWRD]+RECHEADLEN;
    w = jw + RECHEADLEN; /* skip record header */
    do
    {
      b = (FpackheadPtr)w;
/*
printf("etNlink: b->name=%4.4s\n",(char *)&b->name);
printf("etNlink: b->nr=%d\n",b->nr);
printf("etNlink: b->ndata=%d\n",b->ndata);
*/
      if(b->name == nama && b->nr == nr)
      {
/*
printf("etNlink: found\n");
*/
        return(((int)&b->nhead-(int)jw)/4+b->nhead);
      }
      w += b->nhead + b->ndata;
    } while(w < jw + len);
  }
  else
  {
    return(bosNlink(jw, name, nr)); /* regular BOSIO */
  }

  return(0);
}


int
etnamind_(int *jw, char *name, int lenname)
{
  char *nam;
  int ind;

  nam = (char *) MALLOC(lenname+1);
  strncpy(nam,name,lenname);
  nam[lenname] = '\0';

  ind = etNamind(jw, nam);

  FREE(nam);
  return(ind);
}

int
etNamind(int *jw, char *name)
{
  int nama, ind;

  nama = *(int *)name;

  IFET
  {
    ETSYS *sys = (ETSYS *) jw[irCODE];
    FpackheadPtr b;
    int *w, len, i, nwfmt, nch;
    char *ch;

    len = jw[irNWRD]+RECHEADLEN;
    w = jw + RECHEADLEN; /* skip record header */
    do
    {
      b = (FpackheadPtr)w;
      if(b->name == nama)
      {
        /* store bank pointer to ddl structure */
        for(i=0; i<sys->nddl; i++)
        {
          if(!strncmp(name,sys->ddl[i].name,sys->ddl[i].nname))
          {
            sys->ddl[i].b_save = b;
            ind = ((int)&b->nhead-(int)jw)/4+b->nhead;
            sys->ddl[i].ind_save = ind;
/*
printf("etNamind 1 returns %d\n",ind-1);
*/
            return(ind-1);
          }
        }

        /* if bank does not exist in ddl - put it there */
/*
printf("etNamind: put bank >%4.4s< in to ddl structure.\n",name);
*/
        if(sys->nddl >= NDDL)
        {
          printf("etNamind: ERROR - too many bank definitions sys->nddl=%d >= %d\n",
              sys->nddl,NDDL);
          return(-10);
        }

        strcpy(sys->ddl[sys->nddl].name,name);
        sys->ddl[sys->nddl].nname = strlen(sys->ddl[sys->nddl].name);

        nwfmt = b->nhead - 9;
        nch = nwfmt * sizeof(int);
        ch = (char *)&b->frmt;
        nch--;
        while(ch[nch] == ' ' && nch > 0) nch--;
        strncpy(sys->ddl[sys->nddl].fmt,(char *)&b->frmt,nch+1);
        sys->ddl[sys->nddl].fmt[nch+1] = '\0';
        sys->ddl[sys->nddl].nfmt = strlen(sys->ddl[sys->nddl].fmt);

        if(!strncmp(sys->ddl[sys->nddl].fmt,"B8",2)) sys->ddl[sys->nddl].lfmt = 4;
        else if(!strncmp(sys->ddl[sys->nddl].fmt,"B08",3)) sys->ddl[sys->nddl].lfmt = 4;
        else if(!strncmp(sys->ddl[sys->nddl].fmt,"B16",3)) sys->ddl[sys->nddl].lfmt = 2;
        else sys->ddl[sys->nddl].lfmt = 1;
    
        sys->ddl[sys->nddl].ncol = b->ncol;
/*
printf("etNamind 1: sys->nddl=%d name>%s< fmt>%s<\n",
        sys->nddl,sys->ddl[sys->nddl].name,sys->ddl[sys->nddl].fmt); fflush(stdout);
*/
        sys->ddl[sys->nddl].b_save = b;
        ind = ((int)&b->nhead-(int)jw)/4+b->nhead;
        sys->ddl[sys->nddl].ind_save = ind;

        sys->nddl ++;
/*
printf("etNamind 2 returns %d\n",ind-1);
*/
        return(ind-1);


      }
      w += b->nhead + b->ndata;
    } while(w < jw + len);
  }
  else
  {
    return(bosNamind(jw, name)); /* regular BOSIO */
  }
/*
  printf("etNamind 3 returns %d    b->name >%4.4s<\n",-1,name);
*/
  return(-1);
}


int
etnnext_(int *jw, int *ind)
{
  return(etNnext(jw, *ind));
}

int
etNnext(int *jw, int ind)
{
  IFET
  {
    ETSYS *sys = (ETSYS *) jw[irCODE];
    FpackheadPtr b;
    int *w, len, i;

    if(!ind) return(0); /* if ind==0 return(0) */

    len = jw[irNWRD]+RECHEADLEN;

/*
printf("\n\n\n\n\netNnext reached, ind=%d\n",ind); fflush(stdout);
*/
    /* search for ind in ddl structure */
    for(i=0; i<sys->nddl; i++)
    {
/*
printf("etNnext--->i=%d -> ind=%d sys->ddl[i].ind_save=%d (name >%4.4s<)\n",
           i,ind,sys->ddl[i].ind_save,sys->ddl[i].name); fflush(stdout);
*/
      if(sys->ddl[i].ind_save == ind)
      {
        b = sys->ddl[i].b_save;
/*
printf("0\n"); fflush(stdout);
printf("%d %d %d %d >%4.4s<\n",b->nr,b->ncol,b->nrow,b->ndata,&b->name); fflush(stdout);
*/
        w = (int *)b;
        w += b->nhead + b->ndata; /* next bank */

        while(w < jw + len)
        {
          b = (FpackheadPtr)w;
/*
printf("1\n"); fflush(stdout);
printf("%d %d %d %d >%4.4s<\n",b->nr,b->ncol,b->nrow,b->ndata,&b->name); fflush(stdout);
*/
          if(!strncmp((char *)&b->name,sys->ddl[i].name,sys->ddl[i].nname))
          {
            sys->ddl[i].b_save = b;
            ind = ((int)&b->nhead-(int)jw)/4+b->nhead;
            sys->ddl[i].ind_save = ind;

            return(ind);
          }
          w += b->nhead + b->ndata;
        }

        /* no more banks with that name */
        sys->ddl[i].ind_save = 0;
        return(0);
      }
    }
    printf("etNnext: call etNamind() first !!!\n");
    return(0);
  }
  else
  {
    return(jw[ind-1-INXT]);
  }

}


int
etnnum_(int *jw, int *ind)
{
  return(etNnum(jw, *ind));
}

int
etNnum(int *jw, int ind)
{
  IFET
  {
    FpackheadPtr b;

    b = (FpackheadPtr)&jw[ind-irNWRD];
    return(b->nr);
  }
  else
  {
    return(jw[ind-1-INR]);
  }
}


int
etncol_(int *jw, int *ind)
{
  return(etNcol(jw, *ind));
}

int
etNcol(int *jw, int ind)
{
  IFET
  {
    FpackheadPtr b;

    b = (FpackheadPtr)&jw[ind-irNWRD];
    return(b->ncol);
  }
  else
  {
    return(jw[ind-1-ICOL]);
  }
}


int
etnrow_(int *jw, int *ind)
{
  return(etNrow(jw, *ind));
}

int
etNrow(int *jw, int ind)
{
  IFET
  {
    FpackheadPtr b;

    b = (FpackheadPtr)&jw[ind-irNWRD];
    return(b->nrow);
  }
  else
  {
    return(jw[ind-1-IROW]);
  }
}


int
etndata_(int *jw, int *ind)
{
  return(etNdata(jw, *ind));
}

int
etNdata(int *jw, int ind)
{
  IFET
  {
    FpackheadPtr b;

    b = (FpackheadPtr)&jw[ind-irNWRD];
    return(b->ndata);
  }
  else
  {
    return(jw[ind-1-IDAT]);
  }
}


void
etldrop_(int *jw, char *list, int lenlist)
{
  char *lst;
 
  lst = (char *) MALLOC(lenlist+1);
  strncpy(lst,list,lenlist);
  lst[lenlist] = '\0';
  etLdrop(jw,lst);
  FREE(lst);
}

void
etLdrop(int *jw, char *list)
{
  IFET
  {
    ETSYS *sys = (ETSYS *) jw[irCODE];

    sys->nddl = 0;
  }
  else
  {
    bosLdrop(jw,list);
    bosNgarbage(jw);
  }
  
}


void
etngarb_(int *jw)
{
  etNgarb(jw);
}

void
etNgarb(int *jw)
{
  IFET
  {
    ;
  }
  else
  {
    bosNgarbage(jw);
  }
  
}


void
etlctl_(int *jw, char *opt, char *list, int lenopt, int lenlist)
{
  char *op, *lst;
 
  op = (char *) MALLOC(lenopt+1);
  strncpy(op,opt,lenopt);
  op[lenopt] = '\0';
  lst = (char *) MALLOC(lenlist+1);
  strncpy(lst,list,lenlist);
  lst[lenlist] = '\0';
  etLctl(jw,op,lst);
  FREE(op);
  FREE(lst);
}
 
int
etLctl(int *jw, char *opt, char *list)
{
  IFET
  {
    ;
  }
  else
  {
    bosLctl(jw,opt,list);
  }
  
}


int
etnnama_(int *jw, int *ind)
{
  return(etNnama(jw, *ind));
}

int
etNnama(int *jw, int ind)
{
  printf("etNnama: not implemented yet\n");
  return(0);
}







