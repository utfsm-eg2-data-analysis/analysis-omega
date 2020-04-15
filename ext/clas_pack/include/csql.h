/*
  The new CSQL Library.
 
  The CSQL Library is designed to be an easy interface
  to mySQL. It provides tools to create tables according to ddl files
  commonly used in CLAS callabaration, and fill them from the BOS banks.
  To get more information about BOS visit www.jlab.org.

  The PostScript Documentation for this Library will be availeble on the web
  soon (http://claspc15.jlab.org/Docs).

  Have Fun.....
 */

#ifndef __CSQLINCLUDE__
#define __CSQLINCLUDE__

#include "mysql.h"

#define MAX_GROUPS   20
#define MAX_COLUMNS  400
/* #define MAX_COLUMNS  200 */

#define  COL_NOT_USE     -1

#define  COL_C_TBL        1
#define  COL_CW_TBL       2
#define  COL_PRIKEY       3
#define  COL_PRIKEY_AUTO  4
#define  COL_TYPE_INT     1
#define  COL_TYPE_FLOAT   3

  MYSQL       mysql;
  MYSQL_ROW   mysql_row;
  MYSQL_RES  *mysql_res;

typedef struct{
  char  name[ 64];
  char  type[ 64];
  char  value[256];
  int   itype;
  int   index;
  int   mode; /* if -1 - do not include to table when creating one 
	         if  1 - include when creating table but skip when inserting 
	                 values into table
	         if  2 - create table with and insert values
		 if  3 - use this column as a Primary key
	         default mode is 2 when adding column, use set_column_mode 
	         to change this value */
} column_t;

typedef struct{
char name[5];
int  maxcolumns;
int  ncolumns;
int  isActive;
column_t  fColumns[MAX_COLUMNS];
} group_t;

/* GROUPS */

group_t CSQL_Groups[MAX_GROUPS];

/* Default parameters */

char   *def_tablename;
char   *proc_hostname;

/* Process assotiated variables */

char    PROC_username[16];
char    PROC_hostname[64];
int     PROC_id;

/* Database assotiated variables */

char    CSQL_Hostname[128];
char    CSQL_Username[32];
char    CSQL_Database[32];
char    CSQL_Password[32];
char    CSQL_MonTable[32];
char    CSQL_DefTable[32];
char    CSQL_DDLFile[256];
char    CSQL_CALIBHost[64];
char    CSQL_RunIndex[64];
char    CSQL_TimeStamp[64];


char    DB_hostname[128];
char    DB_username[32];
char    DB_database[32];
char    DB_password[16];
char    DB_endtable[64];

int     PASS_mode;

char    CALIB_Host_Name[64];
char    CALIB_RunIndex[32];
char    CALIB_Timestamp[32];

char    DDL_FileName[256];

int     fNGroups;
int     fDebugMode;
/* Procedure prototypes */


/* Init Procedures */

void  init_csql();
void  init_env();
void  init_clas_def();
void  init_csql_clas();
void  csql_init_();
void  set_database(char *hostname,char *username, char *password,char *DB_name);
void  set_database_(char *hostname,char *username, char *password,char *DB_name, int hlen, int ulen, int plen, int dlen);
void init_clas(int runno, int runext, const char *jobname);
/*  Group Manipulation Procedures */

void  reset_group(group_t *grp);
void  add_group(const char *name);
int   get_next_available();
int   find_group_byname(const char *name);
void  print_all_groups();
void print_group(char *grpname);
/* Column manipulation procedures */

void  add_column(const char *group, const char *colname);
int   find_column_byname(int grp_indx, const char *colname);
void  init_column(const char *group, const char *colname, const char *type, int itype, int mode);
int   find_column(group_t group, const char *name);

void  set_column_int(const char *group, const char *col, int value);
void  set_column_float(const char *group, const char *col, float value);
void  set_column_char(const char *group, const char *col, const char *value);

/* String Procedures */

void string_shift(char *line, int npos,int max);
void string_space_clean(char *line,int maxlen);
void string_get_token(char *line,int ntoken,char *dst);
int  string_get_int_token(char *line,int ntoken);
int  string_cmp_token(char *line, int ntoken,const char *exp);
int  string_get_ntokens(char *line);
void string_append(char *line, const char *str);


/* MYSQL Procedures */

int   connect_mSQL_server(MYSQL *mysql,char *DB_hostname, char *DB_username,char *DB_name,char *DB_passwd);
void  disconnect_mSQL_server(MYSQL *mysql);
int   is_table(const char *tablename);
void  get_table_columns(group_t *tbl_col,const char *tablename);
void  fill_table(const char *tablename,const char *group_list);
void  delete_table(const char *tablename);

MYSQL_RES  *execute_query(const char *query_str);

#endif






