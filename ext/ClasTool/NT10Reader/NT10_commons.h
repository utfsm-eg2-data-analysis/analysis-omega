// This file defines the structure of the HBOOK Ntuple common 
// block. It is needed to get the data from the ntuple.
//
// This version should work for E2b, EG2, EG3 test.
// 
// Unfortunately the NT10 ntuple definition is not always the
// same, so for different versions of the cooking code a 
// different common block interface is needed. 
// If the NT10 ntuple has more information that you want access
// to in root, you will also need to update the FILL routines,
// and maybe add to the ClasBanks (to create a place to put the
// info.) If you do this be really careful!
//
// To create this type of common block file do the following.
//
// Start paw: "paw"
// Type:
// filecase keep
// his/file 1 nt442210_00.hbook
// nt/uwfunc 10 new_common.inc
// quit
//
// This will give you the top part of this file. You then 
// add a comment, comment out the FORTRAN code and 
// translate it into a "C" structure. 
// Remember to add the #ifndef __CINT__ enclosure and the
// #define I_VERSION.
//
//
//*********************************************************
//*
//*     Ntuple Id:      10   
//*     Ntuple Title:   All_out
//*     Creation:       18/07/2003 16.51.48
//*
//*********************************************************
//*
//      LOGICAL         CHAIN
//      CHARACTER*128   CFILE
//      INTEGER         IDNEVT,NCHEVT,ICHEVT
//      REAL            OBS(13)
//*
//      COMMON /PAWIDN/ IDNEVT,OBS
//      COMMON /PAWCHN/ CHAIN, NCHEVT, ICHEVT
//      COMMON /PAWCHC/ CFILE
//*
//*--   Ntuple Variable Declarations
//*
//      REAL q_l,t_l,tr_time,rf_time,p(20),m(20),b(20),cx(20),cy(20)
//     + ,cz(20),vx(20),vy(20),vz(20),dc_xsc(20),dc_ysc(20),dc_zsc(20)
//     + ,dc_cxsc(20),dc_cysc(20),dc_czsc(20),dc_vx(20),dc_vy(20)
//     + ,dc_vz(20),dc_vr(20),tl1_cx(20),tl1_cy(20),tl1_cz(20),tl1_x(20)
//     + ,tl1_y(20),tl1_z(20),tl1_r(20),dc_c2(20),etot(20),ec_ei(20)
//     + ,ec_eo(20),ec_t(20),ec_r(20),ech_x(20),ech_y(20),ech_z(20)
//     + ,ec_m2(20),ec_m3(20),ec_m4(20),ec_c2(20),edep(20),sc_t(20)
//     + ,sc_r(20),sc_c2(20),cc_t(20),cc_r(20),cc_c2(20),lec_etot(20)
//     + ,lec_ein(20),lec_t(20),lec_r(20),lec_x(20),lec_y(20),lec_z(20)
//     + ,lec_c2(20)
//      INTEGER npart,evstat,evntid,evntype,evntclas,l2bit,l3bit,hlsc,intt
//     + ,gpart,id(20),stat(20),dc(20),cc(20),sc(20),ec(20),lec(20),st(20)
//     + ,q(20),dc_part,dc_sect(20),dc_trk(20),dc_stat(20),tb_st(20)
//     + ,ec_part,ec_stat(20),ec_sect(20),ec_whol(20),ec_inst(20)
//     + ,ec_oust(20),sc_part,sc_sect(20),sc_hit(20),sc_pd(20),sc_stat(20)
//     + ,cc_part,cc_sect(20),cc_hit(20),cc_segm(20),nphe(20),lac_part
//     + ,lec_sect(20),lec_hit(20),lec_stat(20)
//*
//      COMMON /PAWCR4/ npart,evstat,evntid,evntype,evntclas,q_l,t_l
//     + ,tr_time,rf_time,l2bit,l3bit,hlsc,intt,gpart,id,stat,dc,cc,sc,ec
//     + ,lec,st,p,m,q,b,cx,cy,cz,vx,vy,vz,dc_part,dc_sect,dc_trk,dc_stat
//     + ,tb_st,dc_xsc,dc_ysc,dc_zsc,dc_cxsc,dc_cysc,dc_czsc,dc_vx,dc_vy
//     + ,dc_vz,dc_vr,tl1_cx,tl1_cy,tl1_cz,tl1_x,tl1_y,tl1_z,tl1_r,dc_c2
//     + ,ec_part,ec_stat,ec_sect,ec_whol,ec_inst,ec_oust,etot,ec_ei,ec_eo
//     + ,ec_t,ec_r,ech_x,ech_y,ech_z,ec_m2,ec_m3,ec_m4,ec_c2,sc_part
//     + ,sc_sect,sc_hit,sc_pd,sc_stat,edep,sc_t,sc_r,sc_c2,cc_part
//     + ,cc_sect,cc_hit,cc_segm,nphe,cc_t,cc_r,cc_c2,lac_part,lec_sect
//     + ,lec_hit,lec_stat,lec_etot,lec_ein,lec_t,lec_r,lec_x,lec_y,lec_z
//     + ,lec_c2

#define I_VERSION "Common, E2b, EG2, EG3"

#ifndef __CINT__
extern "C" {
  struct __NT10 {
    int npart;
    int evstat;
    int evntid;
    int evntype;
    int evntclas;
    float q_l;
    float t_l;
    float tr_time;
    float rf_time;
    int   l2bit;
    int   l3bit;
    int   hlsc;
    int   intt;
    int   gpart;
    int   id[20];
    int   stat[20];
    int   dc[20];
    int   cc[20];
    int   sc[20];
    int   ec[20];
    int   lec[20];
    int   st[20];
    float p[20];
    float m[20];
    int   q[20];
    float b[20];
    float cx[20];
    float cy[20];
    float cz[20];
    float vx[20];
    float vy[20];
    float vz[20];
    int   dc_part;
    int   dc_sect[20];
    int   dc_trk[20];
    int   dc_stat[20];
    int   tb_st[20];
    float dc_xsc[20];
    float dc_ysc[20];
    float dc_zsc[20];
    float dc_cxsc[20];
    float dc_cysc[20];
    float dc_czsc[20];
    float dc_vx[20];
    float dc_vy[20];
    float dc_vz[20];
    float dc_vr[20];
    float tl1_cx[20];
    float tl1_cy[20];
    float tl1_cz[20];
    float tl1_x[20];
    float tl1_y[20];
    float tl1_z[20];
    float tl1_r[20];
    float dc_c2[20];
    int   ec_part;
    int   ec_stat[20];
    int   ec_sect[20];
    int   ec_whol[20];
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
    float ec_m3[20];
    float ec_m4[20];
    float ec_c2[20];
    int   sc_part;
    int   sc_sect[20];
    int   sc_hit[20];
    int   sc_pd[20];
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
    int   lac_part;
    int   lec_sect[20];
    int   lec_hit[20];
    int   lec_stat[20];
    float lec_etot[20];
    float lec_ein[20];
    float lec_t[20];
    float lec_r[20];
    float lec_x[20];
    float lec_y[20];
    float lec_z[20];
    float lec_c2[20];
  };
  
  __NT10 nt10;
}
#endif
