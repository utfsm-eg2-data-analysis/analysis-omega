/* defined in PartUtil.c */

/*tbid member functions*/
cc01_t *tbid2cc01(tbid_t *tbid);
scrc_t *tbid2scrc(tbid_t *tbid);
tdpl_t *tbid2tdpl(tbid_t *tdpl);


/* part member functions*/
tbid_t *part2tbid(part_t *part, int GroupNo);
tbtr_t *part2tbtr(part_t *part, int GroupNo);
int ec_get_energy(part_t * , int GroupNo, ecHit_t * ); /*ecHit_t defined in ec.h*/
float sc_get_energy(part_t * , int GroupNo);
float sc_get_tof(part_t * , int GroupNo);
int Accept(part_t *);                     /* crude geometrical acceptance */
int AcceptVB(part_t *Part, int RunNo, float TorusCurrent);
/* PID C wrapper for pseudo_spa.f */

/* convert from seb to part*/
int makePART_from_EVNT(clasEVNT_t *EVNT, int partno);
part_t evnt2part(evnt_t *evnt);
void seb2pid( int partno);
match_t ccpb2match(ccpb_t ccpb);
int ccpb_id2ccrc_id(int scsght);
int ccrc_ind2cc01_ind(int index);
match_t ecpb2match(ecpb_t ecpb, int *sec);

tagr_t *get_photon_tagrEcut(clasTAGR_t *TAGR,clasBID_t *BID,double E0,double E1);










