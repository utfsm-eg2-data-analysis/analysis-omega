/*
  fswap.c - byte swapping for array IREC(1)...IREC(NC), if NC > 0
            if NC = 0, taken from word 2 (after conversion)
            IREC(3) is the byte swapping controlword
*/

#include <stdio.h>

#define LSHFT(value,bits) ( (value) << (bits) )
#define RSHFT(value,bits) ( (value) >> (bits) )
#define AND(x1,x2)        ( (x1) & (x2) )
#define OR(x1,x2)         ( (x1) | (x2) )

void fswap_(unsigned int *irec, int *nc)
{
  int i, nusedw;
  static unsigned int NB1234, NB3412, NB4321, MASK2, MASK3;
  static int first = 1;

  if(first)
  {
    NB1234 = 1+256*(2+256*(3+256*4));
    NB3412 = 3+256*(4+256*(1+256*2));
    NB4321 = 4+256*(3+256*(2+256*1));
    /* byte masks */
    MASK2 = 255*256;
    MASK3 = 255*256*256;

    first = 0;
  }

  if(irec[2] == NB1234) /* no conversion necessary */
  {
    ;
  }
  else if(irec[2] == NB3412) /* convert first two words */
  {
    irec[0] = OR(LSHFT(irec[0],16),RSHFT(irec[0],16));
    irec[1] = OR(LSHFT(irec[1],16),RSHFT(irec[1],16));
    if(*nc == 0)
    {
      nusedw = irec[1];
    }
    else
    {
      nusedw = *nc;
    }
    /* convert remaining words */
    for(i=3; i<=nusedw; i++)
      irec[i-1] = OR(LSHFT(irec[i-1],16),RSHFT(irec[i-1],16));
  }
  else if(irec[2] == NB4321) /* convert first two words */
  {
    irec[0] =
      OR( OR (LSHFT(irec[0],24), AND(LSHFT(irec[0],8), MASK3) ),
      OR(AND (RSHFT(irec[0], 8),MASK2), RSHFT(irec[0],24) ) );
    irec[1] =
      OR(OR(LSHFT(irec[1],24),AND(LSHFT(irec[1],8),MASK3)),
      OR(AND(RSHFT(irec[1],8),MASK2),RSHFT(irec[1],24)));
    if(*nc == 0)
    {
      nusedw = irec[1];
    }
    else
    {
      nusedw = *nc;
    }
    /* convert remaining words */
    for(i=3; i<=nusedw; i++)
      irec[i-1] =
           OR(  OR(LSHFT(irec[i-1],24), AND(LSHFT(irec[i-1],8),MASK3)),
           OR( AND(RSHFT(irec[i-1],8),MASK2),RSHFT(irec[i-1],24)));
  }

  return;
}
