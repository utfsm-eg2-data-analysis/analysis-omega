int           Scat_Initialize (char *);
int           Scat_PackedCount ();
int           Scat_Pack (char *, char *, int, int, int, int, int *);
int           Scat_PackInit ();
int           Scat_PackForget ();
int           Scat_InitHandle (char *host, 
			       unsigned long program, 
			       unsigned long vers);
char        * Scat_HandHost (int) ;
unsigned long Scat_HandProgram (int) ;
unsigned long Scat_HandVers (int) ;
char        * Scat_ServerInfo (int svt);
int           Scat_LocateProgram (char *, char *);
void          Scat_StartProgram (char *, char *, char *, int);
char       ** Scat_Probe (char *);
void          Scat_Conn_Uid (char *, char *);
void          Scat_Conn_PgmName (char *, char *);
void          Scat_Conn_NodeName (char *, char *);
unsigned long Scat_Conn_PgmNo (char *);
unsigned long Scat_Conn_VerNo (char *);
void          Scat_Conn_ListName (char *, char *);
int           Scat_Conn_NumNlist (char *);

int           Scat_SendMsgNr (int svt, char *msg);
int           Scat_SendEvtNr (int svt, char *msg);

int           Scat_BrowCreate (char *, unsigned long, unsigned long);
int           Scat_Filter2Bos (int, char *,char *, int *);
void          printSVT(char *);

