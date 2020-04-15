/* 
 *        calib_manager.h: user header for use with MySQL C API routines
 *        Created:         25-MAY-2000 by Riad Suleiman
 * $Id: calib_manager.h,v 1.3 2006/02/04 00:43:12 stepanya Exp $
 */

#define HOST_DEFAULT "clasdb.jlab.org"
#define NAME    "clasuser"
#define PASSWORD_DEFAULT    ""
#define DB_NAME "calib"
#define READ_DB 0
#define WRITE_DB 1
#define DATABASE_MAIN "calib"
#define LEN_AUTHOR 10
#define LEN_VALUE 100000
#define SQL_CMD_SPACE 5000

#define CALIB_NAMELENGTH  16 /* maximum number of characters in names
				including null */
#define CALIB_FILENAMELENGTH  100 /* maximum number of characters in file name
				     inc. null */

#define MAKE_VALUE_TABLE_NAME strcpy(table_name,filename); \
  strcat(table_name,"_"); \
  strcat(table_name,subsystemname); \
  strcat(table_name,"_"); \
  strcat(table_name,itemname);

/* calib_manager error codes */

#define CALIB_OK                    0 /* no errors */

#define CALIB_USER_ERROR_ARGUMENT  -1 /* user supplied arguement incorrect */
#define CALIB_USER_WARN_NOREPEAT   -2 /* previously performed operation is not
					 repeated */
#define CALIB_USER_WARN_NOFIND     -3 /* time not found for item */
#define CALIB_USER_WARN_NOMATCH    -4 /* subsystem or item name not found */
#define CALIB_USER_WARN_NOREPLACE  -5 /* values not replaced for previously
					 filled time */
#define CALIB_USER_WARN_NOVALUE    -6 /* values not found for item */
#define CALIB_USER_ERROR_NOUPPER   -7 /* no upper run boundary found for new
					 values */
#define CALIB_SYSTEM_ERROR_OPEN    -101 /* system error opening calib file */
#define CALIB_SYSTEM_ERROR_IO      -102 /* system file i/o error after opening
					 */
#define CALIB_SYSTEM_ERROR_MEMORY  -103 /* system error
					   allocating/deallocating memory */

/* global variables */

extern MYSQL mysql;
extern int CALDB_VERBOSE;
extern char author[LEN_AUTHOR];
extern char latest[100];

/* function prototypes */

int calib_connect(int writeflag);
int calib_disconnect();

int calib_create(const char filename[]);
int calib_add_item(const char filename[], const char subsystemname[], 
		   const char itemname[], int arraylength, int arraytype);
int calib_stat_item(const char filename[], const char subsystemname[],
		    const char itemname[], int *arraylength, int *arrarytype);

int calib_get_char(const char filename[], const char subsystemname[], 
		   const char itemname[], int arraylength, char carray[], 
		   int atime, int *firsttime, int *olength);
int calib_get_float(const char filename[], const char subsystemname[], 
		    const char itemname[], int arraylength, float farray[], 
		    int atime, int *firsttime);
int calib_get_int(const char filename[], const char subsystemname[], 
		  const char itemname[], int arraylength, int array[], 
		  int atime, int *firsttime);

int calib_put_char(const char filename[], const char subsystemname[], 
		   const char itemname[], int arraylength, 
		   const char carray[], int firsttime);
int calib_put_float(const char filename[], const char subsystemname[], 
		    const char itemname[], int arraylength, 
		    const float farray[], int firsttime);
int calib_put_int(const char filename[], const char subsystemname[], 
		  const char itemname[], int arraylength, const int array[], 
		  int firsttime);
int calib_put(const char filename[], const char subsystemname[], 
	      const char itemname[], const char value[],
	      int firsttime);
