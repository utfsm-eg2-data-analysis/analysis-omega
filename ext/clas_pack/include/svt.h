#ifndef _SVT_H_
#define _SVT_H_
/* -=======================================================- *
$Id: svt.h,v 1.3 2006/02/04 00:45:28 stepanya Exp $
$Author: stepanya $
$Revision: 1.3 $
$Date: 2006/02/04 00:45:28 $
* -=======================================================- */

#define  SB_SIZE 8192

#include <sys/utsname.h>

typedef struct SVT {
  unsigned long       program, vers;
  char                *pgm_name;
  char                *SourceVersion;
  char                *DateCompiled;
  int                 _trans;
  int                 *stat_result ;
  char                scratchBuffer [SB_SIZE];
  struct utsname      uts;
} SVT;

void Scat_CallTrace ();

#define smodtrace(f) Scat_CallTrace (__FILE__, f, __LINE__);

#endif
