////////////////////////////////////////////////////////////////////////// 
//                                                                      //
//  PAWC Common Block and Ntuple-10 common block definitions.           //
//                                                                      //
//  This header sets up all the common block space needed for           //
//  PAW and sets up the structure for the Ntuple-10 common              //
//  block.                                                              //
//                                                                      //
////////////////////////////////////////////////////////////////////////// 


extern "C" {

// The Ntuple 10 structure. This is found with the PAW call to UWFUN 

/*       REAL q_l,t_l,tr_time,rf_time,p(20),b(20),cx(20),cy(20),cz(20) */
/*       + ,vx(20),vy(20),vz(20),dc_xsc(20),dc_ysc(20),dc_zsc(20) */
/*       + ,dc_cxsc(20),dc_cysc(20),dc_czsc(20),dc_vr(20),dc_c2(20) */
/*       + ,tl1_cx(20),tl1_cy(20),tl1_cz(20),tl1_x(20),tl1_y(20),tl1_z(20) */
/*       + ,tl1_r(20),etot(20),ec_ei(20),ec_eo(20),ec_t(20),ec_r(20) */
/*       + ,ech_x(20),ech_y(20),ech_z(20),ec_m2(20),ec_c2(20),edep(20) */
/*       + ,sc_t(20),sc_r(20),sc_c2(20),cc_t(20),cc_r(20),cc_c2(20) */
/*        INTEGER npart,evntid,evntclas,lt1,hlsc,intt,rstr1,rstr2,gpart */
/*       + ,id(20),stat(20),dc(20),sc(20),ec(20),cc(20),lec(20),st(20),q(20) */
/*       + ,dc_part,dc_stat(20),ec_part,ec_stat(20),ec_inst(20),ec_oust(20) */
/*       + ,sc_part,sc_stat(20),cc_part,cc_sect(20),cc_hit(20),cc_segm(20) */
/*       + ,nphe(20) */
/*  * */
/*        COMMON /PAWCR4/ npart,evntid,evntclas,q_l,t_l,tr_time,rf_time,lt1 */
/*       + ,hlsc,intt,rstr1,rstr2,gpart,id,stat,dc,sc,ec,cc,lec,st,p,q,b,cx */
/*       + ,cy,cz,vx,vy,vz,dc_part,dc_stat,dc_xsc,dc_ysc,dc_zsc,dc_cxsc */
/*       + ,dc_cysc,dc_czsc,dc_vr,dc_c2,tl1_cx,tl1_cy,tl1_cz,tl1_x,tl1_y */
/*       + ,tl1_z,tl1_r,ec_part,ec_stat,ec_inst,ec_oust,etot,ec_ei,ec_eo */
/*       + ,ec_t,ec_r,ech_x,ech_y,ech_z,ec_m2,ec_c2,sc_part,sc_stat,edep */
/*       + ,sc_t,sc_r,sc_c2,cc_part,cc_sect,cc_hit,cc_segm,nphe,cc_t,cc_r */
/*       + ,cc_c2 */

      struct __NT10 {
	int npart;
	int evntid;
	int evntclas;
	float q_l;
	float t_l;
	float tr_time;
	float rf_time;
	int   lt1;
	int   hlsc;
	int   intt;
	int   rstr1;
	int   rstr2;
	int   gpart;
	int   id[20];
	int   stat[20];
	int   dc[20];
	int   sc[20];
	int   ec[20];
	int   cc[20];
	int   lec[20];
	int   st[20];
	float p[20];
	int   q[20];
	float b[20];
	float cx[20];
	float cy[20];
        float cz[20];
	float vx[20];
	float vy[20];
	float vz[20];
	int   dc_part;
	int   dc_stat[20];
	float dc_xsc[20];
	float dc_ysc[20];
	float dc_zsc[20];
	float dc_cxsc[20];
	float dc_cysc[20];
	float dc_czsc[20];
	float dc_vr[20];
	float dc_c2[20];
	float tl1_cx[20];
	float tl1_cy[20];
	float tl1_cz[20];
	float tl1_x[20];
	float tl1_y[20];
	float tl1_z[20];
	float tl1_r[20];
	int   ec_part;
	int   ec_stat[20];
	int   ec_inst[20];
	int   ec_oust[20];
	float etot[20];
	float ec_ei[20];
	float ec_eo[20];
	float ec_t[20];
	float ec_r[20];
	float ech_x[20];
	float ech_y[20];
	float ech_z[20];
	float ec_m2[20];
	float ec_c2[20];
	int   sc_part;
	int   sc_stat[20];
	float edep[20];
	float sc_t[20];
	float sc_r[20];
	float sc_c2[20];
	int   cc_part;
	int   cc_sect[20];
	int   cc_hit[20];
	int   cc_segm[20];
	int   nphe[20];
	float cc_t[20];
	float cc_r[20];
	float cc_c2[20];
      };

  __NT10 nt10;
}





