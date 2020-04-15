/* C prototypes for FORTRAN pdg functions located
   in clasutil*/

/*located in clasutil/geant_to_pdg.F*/
int geant_to_pdg_(int *geantid);

/*located in clasutil/pdg_to_geant.F*/
int pdg_to_geant_(int *pdgid);

/*located in clasutil/pmass.F */
float pmass_(int *pdgid);
float pchrg_(int *pdgid); /* returns a float???*/
float ptlif_(int *pdgid);
float pwidth_(int *pdgid);

/*located in clasutil/geant_util.c */
float gmass(int geant_id);
int gchrg(int geant_id);
float gtlif(int geant_id);
float gwidth(int geant_id);
