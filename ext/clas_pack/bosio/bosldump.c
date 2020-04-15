/*
   bosldump.c - get list of pointers to banks

       output parameters:

     return - the number of banks
     output -  pointer to bank index array
               for the list of banks; if list '0'
               or '*' - all existing banks
*/


/* BAD - no free() HERE */

#include <stdio.h>
#include <stdlib.h>

#include "bos.h"

int
bosLdump(int *jw, char *list, int **outptr, int **fmtptr)
{
  BOSptr b;
  int *w, i, jls, nls, ils, ind, nami, indcnt, nbanks, *ptr;
  static int buflen=0, *buf, *fmtbuf;

  w = jw-1;
  b = (BOSptr)jw;
  nbanks = 0;

  if(*list == '0' || *list == '*')
  {
    /* first pass */
    for(i=1; i<=w[b->idnam]; i++)
    {
      ind = w[mamind(jw,w[b->idnam+i])];
      if(ind)
      {
        nbanks++;
        while( (ind=w[ind-INXT]) != 0) nbanks++;
      }
    }

    /* allocate memory for output buffer */
    if(buflen == 0)
    {
      buflen = nbanks;
      buf =    (int *) MALLOC(buflen*sizeof(int));
      fmtbuf = (int *) MALLOC(buflen*sizeof(int));
    }
    else if(buflen < nbanks)
    {
      buflen = nbanks;

      ptr = (int *) realloc(buf, buflen*sizeof(int));    
      if(!ptr)
      {
        printf("bosLdump: realloc error, buflen=%d\n",buflen);
        return(-1);
      }
      else
      {
        buf = ptr;
      }

      ptr = (int *) realloc(fmtbuf, buflen*sizeof(int));    
      if(!ptr)
      {
        printf("bosLdump: realloc error, buflen=%d\n",buflen);
        return(-1);
      }
      else
      {
        fmtbuf = ptr;
      }

    }
    *outptr = buf;
    *fmtptr = fmtbuf;

    /* second pass */
    indcnt = 0;
    for(i=1; i<=w[b->idnam]; i++)
    {
      nami = mamind(jw,w[b->idnam+i]);
      ind = w[nami];
      if(ind)
      {
        (*fmtptr)[indcnt] = nami;
        (*outptr)[indcnt++] = ind; /* index a la FORTRAN ! */
        while( (ind=w[ind-INXT]) != 0)
        {
          (*fmtptr)[indcnt] = nami;
          (*outptr)[indcnt++] = ind; /* index a la FORTRAN ! */
        }
      }
    }
  }
  else
  {
    /* first pass */
    listn1(jw,list,&jls,&nls);
    ils = 0;
    while((nami = listn2(jw,list,&ils,&jls,&nls)) > 0)
    {
      ind = nami + 1;
      while((ind = w[ind-INXT]) != 0) nbanks++;
    }

    /* allocate memory for output buffer */
    if(buflen == 0)
    {
      buflen = nbanks;
      buf =    (int *) MALLOC(buflen*sizeof(int));
      fmtbuf = (int *) MALLOC(buflen*sizeof(int));
    }
    else if(buflen < nbanks)
    {
      buflen = nbanks;

      ptr = (int *) realloc(buf, buflen*sizeof(int));    
      if(!ptr)
      {
        printf("bosLdump: realloc error, buflen=%d\n",buflen);
        return(-1);
      }
      else
      {
        buf = ptr;
      }

      ptr = (int *) realloc(fmtbuf, buflen*sizeof(int));    
      if(!ptr)
      {
        printf("bosLdump: realloc error, buflen=%d\n",buflen);
        return(-1);
      }
      else
      {
        fmtbuf = ptr;
      }

    }
    *outptr = buf;
    *fmtptr = fmtbuf;

    /* second pass */
    indcnt = 0;
    listn1(jw,list,&jls,&nls);
    ils = 0;
    while((nami = listn2(jw,list,&ils,&jls,&nls)) > 0)
    {
      ind = nami + 1;
      while((ind = w[ind-INXT]) != 0)
      {
        (*fmtptr)[indcnt] = nami;
        (*outptr)[indcnt++] = ind; /* index a la FORTRAN ! */
      }
    }
  }

  return(nbanks);
}



