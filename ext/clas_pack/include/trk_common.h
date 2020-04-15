#define MAX_TRACKS 120
#define NPLANES 46
#define PLANE_INFO 12

typedef enum{
  vertex_pl, start1_pl, start2_pl, sl1_1, sl1_2, sl1_3, sl1_4, unu1, unu2, 
    sl2_1, sl2_2, sl2_3, sl2_4, sl2_5, sl2_6,
    sl3_1, sl3_2, sl3_3, sl3_4, sl3_5, sl3_6,
    sl4_1, sl4_2, sl4_3, sl4_4, sl4_5, sl4_6,
    sl5_1, sl5_2, sl5_3, sl5_4, sl5_5, sl5_6,
    sl6_1, sl6_2, sl6_3, sl6_4, sl6_5, sl6_6
} trkpPlane_t;


typedef enum{
  trkp_x, trkp_y, trkp_z, trkp_cx, trkp_cy, trkp_cz, trkp_p, trkp_beta, trkp_q,
    trkp_tlen, trkp_seclvl, trkp_chisq
} trkpInfo_t;

int fill_trkp_(float trkp[MAX_TRACKS][NPLANES][PLANE_INFO]);
int fill_trkp_element(float trkp[MAX_TRACKS][NPLANES][PLANE_INFO], int ntrk,  hbtr_t *hbtr, hdpl_t *hdpl);
int fill_itr_sec_(int itr_sect[MAX_TRACKS]);
