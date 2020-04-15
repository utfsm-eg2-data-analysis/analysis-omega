/* 
 *        calib_envir.h: user header for use with MySQL C API connection routines
 *        Created:   H.Avagyan 02.04
*/

#define CALDB_HOST_DEFAULT "clasdb.jlab.org"
#define CALDB_HOST "CALDB_HOST"
#define CALDB_USER_DEFAULT "clasuser"
#define CALDB_USER "CALDB_USER"
#define CALDB_PASS_DEFAULT ""
#define CALDB_PASS "CALDB_PASSWORD"
#define CALDB_DBNAME_DEFAULT "calib"
#define CALDB_DBNAME "CALDB_DBNAME"
#define RUN_INDEX_DEFAULT "RunIndex"
#define RUN_INDEX         "RUN_INDEX"
#define VALUE_INDEX       6             /* index of v_0001 in the value table */
/* access control */
#define OPTIONAL 0
#define REQUIRED 1
#define READ_DB 0
#define WRITE_DB 1
#define SQL_CMD_SPACE 5000
#define SQL_FIELD_SPACE 200
#define ENV_VAR_LENGTH 100

#define CALIB_NAMELENGTH  16 /* maximum number of characters in names including null */
#define CALIB_FILENAMELENGTH  100 /* maximum number of characters in file name inc. null */
#define LEN_VALUE 10000

/*  Macros */
#define MAKE_VALUE_TABLE_NAME(table_name,sysname,sybsysname,item) strcpy(table_name,sysname); \
  strcat(table_name,"_"); \
  strcat(table_name,sybsysname); \
  strcat(table_name,"_"); \
  strcat(table_name,item);

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

/* calib_manager error codes */

#define CALIB_OK                    0 /* no errors */
#define CALIB_USER_WARN_NOMATCH    -4 /* subsystem subsystem or item name not found */
#define CALIB_USER_ERROR_ARGUMENT  -1 /* user supplied arguement incorrect */
#define CALIB_SYSTEM_ERROR_INIT    -100  /* system error mysql_init failed */
#define CALIB_SYSTEM_ERROR_IO      -102 /* system file i/o error after opening */
#define CALIB_SYSTEM_ERROR_MEMORY  -103 /* system error allocating/deallocating memory */

/* global variables */

extern int caldb_verbose;


/* global variables */


typedef struct {
    int length;
    char *type;
    char **item;
} valuestruc;
typedef struct {
    int minRunSource;
    int maxRunSource;
    char *author;
    char *time;
    char *comment;
} commentstruc;

typedef long int itemvalue ;
