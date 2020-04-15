struct BEAM_row {
  float ENERGY;
  float ITORUS;
  float IMINI;
  float ITAG;
};

class BEAM {
private:
  int nrows;
  struct BEAM_row *row_ptr;
public:
  BEAM(void) {
    return;
  }
  BEAM(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_ENERGY(int row) {
    return ((row_ptr+row)->ENERGY);
  }
  float get_ITORUS(int row) {
    return ((row_ptr+row)->ITORUS);
  }
  float get_IMINI(int row) {
    return ((row_ptr+row)->IMINI);
  }
  float get_ITAG(int row) {
    return ((row_ptr+row)->ITAG);
  }
};

struct BMPR_row {
  float Q_TOT;
  float Q_TOT_LV;
  float TL_TU;
  float CURRENT;
};

class BMPR {
private:
  int nrows;
  struct BMPR_row *row_ptr;
public:
  BMPR(void) {
    return;
  }
  BMPR(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_Q_TOT(int row) {
    return ((row_ptr+row)->Q_TOT);
  }
  float get_Q_TOT_LV(int row) {
    return ((row_ptr+row)->Q_TOT_LV);
  }
  float get_TL_TU(int row) {
    return ((row_ptr+row)->TL_TU);
  }
  float get_CURRENT(int row) {
    return ((row_ptr+row)->CURRENT);
  }
};

struct BREP_row {
  float MBSY2C_energy;
  float IGT0I00BIASET;
  float IGL1I00DAC2;
  float SMRPOSA;
  float SMRPOSB;
  float SMRPOSC;
  float Harp;
  float hallb_sf_xy560;
  float MTSETI;
  float MTIRBCK;
  float MTVRBCK;
  float TMSETI;
  float TMIRBCK;
  float TMVRBCK;
  float Cryo_pressure;
  float Cryo_temperature;
  float Cryo_status;
  float VCG2C24;
  float VCG2H01;
  float scalerS2o;
  float scalerS3o;
  float scalerS4o;
  float scalerS5o;
  float scalerS6o;
  float scalerS7o;
  float scalerS8o;
  float scalerS9o;
  float IPM2H01_XPOS;
  float IPM2H01_YPOS;
  float IPM2H01;
  float IPM2C24A_XPOS;
  float IPM2C24A_YPOS;
  float IPM2C24A;
  float IPM2C22A_XPOS;
  float IPM2C22A_YPOS;
  float IPM2C22A;
};

class BREP {
private:
  int nrows;
  struct BREP_row *row_ptr;
public:
  BREP(void) {
    return;
  }
  BREP(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_MBSY2C_energy(int row) {
    return ((row_ptr+row)->MBSY2C_energy);
  }
  float get_IGT0I00BIASET(int row) {
    return ((row_ptr+row)->IGT0I00BIASET);
  }
  float get_IGL1I00DAC2(int row) {
    return ((row_ptr+row)->IGL1I00DAC2);
  }
  float get_SMRPOSA(int row) {
    return ((row_ptr+row)->SMRPOSA);
  }
  float get_SMRPOSB(int row) {
    return ((row_ptr+row)->SMRPOSB);
  }
  float get_SMRPOSC(int row) {
    return ((row_ptr+row)->SMRPOSC);
  }
  float get_Harp(int row) {
    return ((row_ptr+row)->Harp);
  }
  float get_hallb_sf_xy560(int row) {
    return ((row_ptr+row)->hallb_sf_xy560);
  }
  float get_MTSETI(int row) {
    return ((row_ptr+row)->MTSETI);
  }
  float get_MTIRBCK(int row) {
    return ((row_ptr+row)->MTIRBCK);
  }
  float get_MTVRBCK(int row) {
    return ((row_ptr+row)->MTVRBCK);
  }
  float get_TMSETI(int row) {
    return ((row_ptr+row)->TMSETI);
  }
  float get_TMIRBCK(int row) {
    return ((row_ptr+row)->TMIRBCK);
  }
  float get_TMVRBCK(int row) {
    return ((row_ptr+row)->TMVRBCK);
  }
  float get_Cryo_pressure(int row) {
    return ((row_ptr+row)->Cryo_pressure);
  }
  float get_Cryo_temperature(int row) {
    return ((row_ptr+row)->Cryo_temperature);
  }
  float get_Cryo_status(int row) {
    return ((row_ptr+row)->Cryo_status);
  }
  float get_VCG2C24(int row) {
    return ((row_ptr+row)->VCG2C24);
  }
  float get_VCG2H01(int row) {
    return ((row_ptr+row)->VCG2H01);
  }
  float get_scalerS2o(int row) {
    return ((row_ptr+row)->scalerS2o);
  }
  float get_scalerS3o(int row) {
    return ((row_ptr+row)->scalerS3o);
  }
  float get_scalerS4o(int row) {
    return ((row_ptr+row)->scalerS4o);
  }
  float get_scalerS5o(int row) {
    return ((row_ptr+row)->scalerS5o);
  }
  float get_scalerS6o(int row) {
    return ((row_ptr+row)->scalerS6o);
  }
  float get_scalerS7o(int row) {
    return ((row_ptr+row)->scalerS7o);
  }
  float get_scalerS8o(int row) {
    return ((row_ptr+row)->scalerS8o);
  }
  float get_scalerS9o(int row) {
    return ((row_ptr+row)->scalerS9o);
  }
  float get_IPM2H01_XPOS(int row) {
    return ((row_ptr+row)->IPM2H01_XPOS);
  }
  float get_IPM2H01_YPOS(int row) {
    return ((row_ptr+row)->IPM2H01_YPOS);
  }
  float get_IPM2H01(int row) {
    return ((row_ptr+row)->IPM2H01);
  }
  float get_IPM2C24A_XPOS(int row) {
    return ((row_ptr+row)->IPM2C24A_XPOS);
  }
  float get_IPM2C24A_YPOS(int row) {
    return ((row_ptr+row)->IPM2C24A_YPOS);
  }
  float get_IPM2C24A(int row) {
    return ((row_ptr+row)->IPM2C24A);
  }
  float get_IPM2C22A_XPOS(int row) {
    return ((row_ptr+row)->IPM2C22A_XPOS);
  }
  float get_IPM2C22A_YPOS(int row) {
    return ((row_ptr+row)->IPM2C22A_YPOS);
  }
  float get_IPM2C22A(int row) {
    return ((row_ptr+row)->IPM2C22A);
  }
};

struct CALB_row {
  float meanRFe;
  float sigmaRFe;
  float sigmaRFh;
  float sigmaECt;
  float SFECe;
  float sigmaSF;
  float ResSL1;
  float ResSL2;
  float ResSL3;
  float ResSL4;
  float ResSL5;
  float ResSL6;
};

class CALB {
private:
  int nrows;
  struct CALB_row *row_ptr;
public:
  CALB(void) {
    return;
  }
  CALB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_meanRFe(int row) {
    return ((row_ptr+row)->meanRFe);
  }
  float get_sigmaRFe(int row) {
    return ((row_ptr+row)->sigmaRFe);
  }
  float get_sigmaRFh(int row) {
    return ((row_ptr+row)->sigmaRFh);
  }
  float get_sigmaECt(int row) {
    return ((row_ptr+row)->sigmaECt);
  }
  float get_SFECe(int row) {
    return ((row_ptr+row)->SFECe);
  }
  float get_sigmaSF(int row) {
    return ((row_ptr+row)->sigmaSF);
  }
  float get_ResSL1(int row) {
    return ((row_ptr+row)->ResSL1);
  }
  float get_ResSL2(int row) {
    return ((row_ptr+row)->ResSL2);
  }
  float get_ResSL3(int row) {
    return ((row_ptr+row)->ResSL3);
  }
  float get_ResSL4(int row) {
    return ((row_ptr+row)->ResSL4);
  }
  float get_ResSL5(int row) {
    return ((row_ptr+row)->ResSL5);
  }
  float get_ResSL6(int row) {
    return ((row_ptr+row)->ResSL6);
  }
};

struct CALL_row {
  short ID;
  short TDC;
  short ADC;
};

class CALL {
private:
  int nrows;
  struct CALL_row *row_ptr;
public:
  CALL(void) {
    return;
  }
  CALL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
  short get_ADC(int row) {
    return ((row_ptr+row)->ADC);
  }
};

struct CC01_row {
  int id;
  float time;
  float n_pe;
};

class CC01 {
private:
  int nrows;
  struct CC01_row *row_ptr;
public:
  CC01(void) {
    return;
  }
  CC01(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  float get_time(int row) {
    return ((row_ptr+row)->time);
  }
  float get_n_pe(int row) {
    return ((row_ptr+row)->n_pe);
  }
};

struct CC1_row {
  short ID;
  short TDC;
  short ADC;
};

class CC1 {
private:
  int nrows;
  struct CC1_row *row_ptr;
public:
  CC1(void) {
    return;
  }
  CC1(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
  short get_ADC(int row) {
    return ((row_ptr+row)->ADC);
  }
};

struct CC_row {
  short ID;
  short TDC;
  short ADC;
};

class CC {
private:
  int nrows;
  struct CC_row *row_ptr;
public:
  CC(void) {
    return;
  }
  CC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
  short get_ADC(int row) {
    return ((row_ptr+row)->ADC);
  }
};

struct CCDI_row {
  int crate;
  int slot;
  int mask;
  int threshold;
  int width;
};

class CCDI {
private:
  int nrows;
  struct CCDI_row *row_ptr;
public:
  CCDI(void) {
    return;
  }
  CCDI(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_crate(int row) {
    return ((row_ptr+row)->crate);
  }
  int get_slot(int row) {
    return ((row_ptr+row)->slot);
  }
  int get_mask(int row) {
    return ((row_ptr+row)->mask);
  }
  int get_threshold(int row) {
    return ((row_ptr+row)->threshold);
  }
  int get_width(int row) {
    return ((row_ptr+row)->width);
  }
};

struct CCH_row {
  int tknum;
  int id;
  int nhits;
  int sector;
  int segment;
  int pmom;
  float xin;
  float yin;
  float zin;
  float xout;
  float yout;
  float zout;
};

class CCH {
private:
  int nrows;
  struct CCH_row *row_ptr;
public:
  CCH(void) {
    return;
  }
  CCH(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_tknum(int row) {
    return ((row_ptr+row)->tknum);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  int get_nhits(int row) {
    return ((row_ptr+row)->nhits);
  }
  int get_sector(int row) {
    return ((row_ptr+row)->sector);
  }
  int get_segment(int row) {
    return ((row_ptr+row)->segment);
  }
  int get_pmom(int row) {
    return ((row_ptr+row)->pmom);
  }
  float get_xin(int row) {
    return ((row_ptr+row)->xin);
  }
  float get_yin(int row) {
    return ((row_ptr+row)->yin);
  }
  float get_zin(int row) {
    return ((row_ptr+row)->zin);
  }
  float get_xout(int row) {
    return ((row_ptr+row)->xout);
  }
  float get_yout(int row) {
    return ((row_ptr+row)->yout);
  }
  float get_zout(int row) {
    return ((row_ptr+row)->zout);
  }
};

struct CCMT_row {
  int mean_high;
  int mean_lo;
};

class CCMT {
private:
  int nrows;
  struct CCMT_row *row_ptr;
public:
  CCMT(void) {
    return;
  }
  CCMT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_mean_high(int row) {
    return ((row_ptr+row)->mean_high);
  }
  int get_mean_lo(int row) {
    return ((row_ptr+row)->mean_lo);
  }
};

struct CCPB_row {
  int ScSgHt;
  float Nphe;
  float Time;
  float Path;
  float Chi2CC;
  int Status;
};

class CCPB {
private:
  int nrows;
  struct CCPB_row *row_ptr;
public:
  CCPB(void) {
    return;
  }
  CCPB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ScSgHt(int row) {
    return ((row_ptr+row)->ScSgHt);
  }
  float get_Nphe(int row) {
    return ((row_ptr+row)->Nphe);
  }
  float get_Time(int row) {
    return ((row_ptr+row)->Time);
  }
  float get_Path(int row) {
    return ((row_ptr+row)->Path);
  }
  float get_Chi2CC(int row) {
    return ((row_ptr+row)->Chi2CC);
  }
  int get_Status(int row) {
    return ((row_ptr+row)->Status);
  }
};

struct CCPE_row {
  int ID;
  int mean;
  int sigma;
};

class CCPE {
private:
  int nrows;
  struct CCPE_row *row_ptr;
public:
  CCPE(void) {
    return;
  }
  CCPE(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_mean(int row) {
    return ((row_ptr+row)->mean);
  }
  int get_sigma(int row) {
    return ((row_ptr+row)->sigma);
  }
};

struct CCRC_row {
  int nrsect;
  int nrsegm;
  int nrsegm_p;
  int nrsegm_m;
  int nrphe;
  int nrtime;
  int nrthet;
  int nrdthet;
  int nrphy;
  int nriec;
  int nrdiec;
  int nrstat;
};

class CCRC {
private:
  int nrows;
  struct CCRC_row *row_ptr;
public:
  CCRC(void) {
    return;
  }
  CCRC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_nrsect(int row) {
    return ((row_ptr+row)->nrsect);
  }
  int get_nrsegm(int row) {
    return ((row_ptr+row)->nrsegm);
  }
  int get_nrsegm_p(int row) {
    return ((row_ptr+row)->nrsegm_p);
  }
  int get_nrsegm_m(int row) {
    return ((row_ptr+row)->nrsegm_m);
  }
  int get_nrphe(int row) {
    return ((row_ptr+row)->nrphe);
  }
  int get_nrtime(int row) {
    return ((row_ptr+row)->nrtime);
  }
  int get_nrthet(int row) {
    return ((row_ptr+row)->nrthet);
  }
  int get_nrdthet(int row) {
    return ((row_ptr+row)->nrdthet);
  }
  int get_nrphy(int row) {
    return ((row_ptr+row)->nrphy);
  }
  int get_nriec(int row) {
    return ((row_ptr+row)->nriec);
  }
  int get_nrdiec(int row) {
    return ((row_ptr+row)->nrdiec);
  }
  int get_nrstat(int row) {
    return ((row_ptr+row)->nrstat);
  }
};

struct CCS_row {
  int CCS1;
  int CCS2;
  int CCS3;
  int CCS4;
  int CCS5;
  int CCS6;
  int CCS7;
  int CCS8;
  int CCS9;
  int CCS10;
  int CCS11;
  int CCS12;
  int CCS13;
  int CCS14;
  int CCS15;
  int CCS16;
  int CCS17;
  int CCS18;
  int CCS19;
  int CCS20;
  int CCS21;
  int CCS22;
  int CCS23;
  int CCS24;
  int CCS25;
  int CCS26;
  int CCS27;
  int CCS28;
  int CCS29;
  int CCS30;
  int CCS31;
  int CCS32;
  int CCS33;
  int CCS34;
  int CCS35;
  int CCS36;
  int CCS37;
  int CCS38;
  int CCS39;
  int CCS40;
  int CCS41;
  int CCS42;
  int CCS43;
  int CCS44;
  int CCS45;
  int CCS46;
  int CCS47;
  int CCS48;
  int CCS49;
  int CCS50;
  int CCS51;
  int CCS52;
  int CCS53;
  int CCS54;
  int CCS55;
  int CCS56;
  int CCS57;
  int CCS58;
  int CCS59;
  int CCS60;
  int CCS61;
  int CCS62;
  int CCS63;
  int CCS64;
  int CCS65;
  int CCS66;
  int CCS67;
  int CCS68;
  int CCS69;
  int CCS70;
  int CCS71;
  int CCS72;
  int CCS73;
  int CCS74;
  int CCS75;
  int CCS76;
  int CCS77;
  int CCS78;
  int CCS79;
  int CCS80;
  int CCS81;
  int CCS82;
  int CCS83;
  int CCS84;
  int CCS85;
  int CCS86;
  int CCS87;
  int CCS88;
  int CCS89;
  int CCS90;
  int CCS91;
  int CCS92;
  int CCS93;
  int CCS94;
  int CCS95;
  int CCS96;
};

class CCS {
private:
  int nrows;
  struct CCS_row *row_ptr;
public:
  CCS(void) {
    return;
  }
  CCS(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_CCS1(int row) {
    return ((row_ptr+row)->CCS1);
  }
  int get_CCS2(int row) {
    return ((row_ptr+row)->CCS2);
  }
  int get_CCS3(int row) {
    return ((row_ptr+row)->CCS3);
  }
  int get_CCS4(int row) {
    return ((row_ptr+row)->CCS4);
  }
  int get_CCS5(int row) {
    return ((row_ptr+row)->CCS5);
  }
  int get_CCS6(int row) {
    return ((row_ptr+row)->CCS6);
  }
  int get_CCS7(int row) {
    return ((row_ptr+row)->CCS7);
  }
  int get_CCS8(int row) {
    return ((row_ptr+row)->CCS8);
  }
  int get_CCS9(int row) {
    return ((row_ptr+row)->CCS9);
  }
  int get_CCS10(int row) {
    return ((row_ptr+row)->CCS10);
  }
  int get_CCS11(int row) {
    return ((row_ptr+row)->CCS11);
  }
  int get_CCS12(int row) {
    return ((row_ptr+row)->CCS12);
  }
  int get_CCS13(int row) {
    return ((row_ptr+row)->CCS13);
  }
  int get_CCS14(int row) {
    return ((row_ptr+row)->CCS14);
  }
  int get_CCS15(int row) {
    return ((row_ptr+row)->CCS15);
  }
  int get_CCS16(int row) {
    return ((row_ptr+row)->CCS16);
  }
  int get_CCS17(int row) {
    return ((row_ptr+row)->CCS17);
  }
  int get_CCS18(int row) {
    return ((row_ptr+row)->CCS18);
  }
  int get_CCS19(int row) {
    return ((row_ptr+row)->CCS19);
  }
  int get_CCS20(int row) {
    return ((row_ptr+row)->CCS20);
  }
  int get_CCS21(int row) {
    return ((row_ptr+row)->CCS21);
  }
  int get_CCS22(int row) {
    return ((row_ptr+row)->CCS22);
  }
  int get_CCS23(int row) {
    return ((row_ptr+row)->CCS23);
  }
  int get_CCS24(int row) {
    return ((row_ptr+row)->CCS24);
  }
  int get_CCS25(int row) {
    return ((row_ptr+row)->CCS25);
  }
  int get_CCS26(int row) {
    return ((row_ptr+row)->CCS26);
  }
  int get_CCS27(int row) {
    return ((row_ptr+row)->CCS27);
  }
  int get_CCS28(int row) {
    return ((row_ptr+row)->CCS28);
  }
  int get_CCS29(int row) {
    return ((row_ptr+row)->CCS29);
  }
  int get_CCS30(int row) {
    return ((row_ptr+row)->CCS30);
  }
  int get_CCS31(int row) {
    return ((row_ptr+row)->CCS31);
  }
  int get_CCS32(int row) {
    return ((row_ptr+row)->CCS32);
  }
  int get_CCS33(int row) {
    return ((row_ptr+row)->CCS33);
  }
  int get_CCS34(int row) {
    return ((row_ptr+row)->CCS34);
  }
  int get_CCS35(int row) {
    return ((row_ptr+row)->CCS35);
  }
  int get_CCS36(int row) {
    return ((row_ptr+row)->CCS36);
  }
  int get_CCS37(int row) {
    return ((row_ptr+row)->CCS37);
  }
  int get_CCS38(int row) {
    return ((row_ptr+row)->CCS38);
  }
  int get_CCS39(int row) {
    return ((row_ptr+row)->CCS39);
  }
  int get_CCS40(int row) {
    return ((row_ptr+row)->CCS40);
  }
  int get_CCS41(int row) {
    return ((row_ptr+row)->CCS41);
  }
  int get_CCS42(int row) {
    return ((row_ptr+row)->CCS42);
  }
  int get_CCS43(int row) {
    return ((row_ptr+row)->CCS43);
  }
  int get_CCS44(int row) {
    return ((row_ptr+row)->CCS44);
  }
  int get_CCS45(int row) {
    return ((row_ptr+row)->CCS45);
  }
  int get_CCS46(int row) {
    return ((row_ptr+row)->CCS46);
  }
  int get_CCS47(int row) {
    return ((row_ptr+row)->CCS47);
  }
  int get_CCS48(int row) {
    return ((row_ptr+row)->CCS48);
  }
  int get_CCS49(int row) {
    return ((row_ptr+row)->CCS49);
  }
  int get_CCS50(int row) {
    return ((row_ptr+row)->CCS50);
  }
  int get_CCS51(int row) {
    return ((row_ptr+row)->CCS51);
  }
  int get_CCS52(int row) {
    return ((row_ptr+row)->CCS52);
  }
  int get_CCS53(int row) {
    return ((row_ptr+row)->CCS53);
  }
  int get_CCS54(int row) {
    return ((row_ptr+row)->CCS54);
  }
  int get_CCS55(int row) {
    return ((row_ptr+row)->CCS55);
  }
  int get_CCS56(int row) {
    return ((row_ptr+row)->CCS56);
  }
  int get_CCS57(int row) {
    return ((row_ptr+row)->CCS57);
  }
  int get_CCS58(int row) {
    return ((row_ptr+row)->CCS58);
  }
  int get_CCS59(int row) {
    return ((row_ptr+row)->CCS59);
  }
  int get_CCS60(int row) {
    return ((row_ptr+row)->CCS60);
  }
  int get_CCS61(int row) {
    return ((row_ptr+row)->CCS61);
  }
  int get_CCS62(int row) {
    return ((row_ptr+row)->CCS62);
  }
  int get_CCS63(int row) {
    return ((row_ptr+row)->CCS63);
  }
  int get_CCS64(int row) {
    return ((row_ptr+row)->CCS64);
  }
  int get_CCS65(int row) {
    return ((row_ptr+row)->CCS65);
  }
  int get_CCS66(int row) {
    return ((row_ptr+row)->CCS66);
  }
  int get_CCS67(int row) {
    return ((row_ptr+row)->CCS67);
  }
  int get_CCS68(int row) {
    return ((row_ptr+row)->CCS68);
  }
  int get_CCS69(int row) {
    return ((row_ptr+row)->CCS69);
  }
  int get_CCS70(int row) {
    return ((row_ptr+row)->CCS70);
  }
  int get_CCS71(int row) {
    return ((row_ptr+row)->CCS71);
  }
  int get_CCS72(int row) {
    return ((row_ptr+row)->CCS72);
  }
  int get_CCS73(int row) {
    return ((row_ptr+row)->CCS73);
  }
  int get_CCS74(int row) {
    return ((row_ptr+row)->CCS74);
  }
  int get_CCS75(int row) {
    return ((row_ptr+row)->CCS75);
  }
  int get_CCS76(int row) {
    return ((row_ptr+row)->CCS76);
  }
  int get_CCS77(int row) {
    return ((row_ptr+row)->CCS77);
  }
  int get_CCS78(int row) {
    return ((row_ptr+row)->CCS78);
  }
  int get_CCS79(int row) {
    return ((row_ptr+row)->CCS79);
  }
  int get_CCS80(int row) {
    return ((row_ptr+row)->CCS80);
  }
  int get_CCS81(int row) {
    return ((row_ptr+row)->CCS81);
  }
  int get_CCS82(int row) {
    return ((row_ptr+row)->CCS82);
  }
  int get_CCS83(int row) {
    return ((row_ptr+row)->CCS83);
  }
  int get_CCS84(int row) {
    return ((row_ptr+row)->CCS84);
  }
  int get_CCS85(int row) {
    return ((row_ptr+row)->CCS85);
  }
  int get_CCS86(int row) {
    return ((row_ptr+row)->CCS86);
  }
  int get_CCS87(int row) {
    return ((row_ptr+row)->CCS87);
  }
  int get_CCS88(int row) {
    return ((row_ptr+row)->CCS88);
  }
  int get_CCS89(int row) {
    return ((row_ptr+row)->CCS89);
  }
  int get_CCS90(int row) {
    return ((row_ptr+row)->CCS90);
  }
  int get_CCS91(int row) {
    return ((row_ptr+row)->CCS91);
  }
  int get_CCS92(int row) {
    return ((row_ptr+row)->CCS92);
  }
  int get_CCS93(int row) {
    return ((row_ptr+row)->CCS93);
  }
  int get_CCS94(int row) {
    return ((row_ptr+row)->CCS94);
  }
  int get_CCS95(int row) {
    return ((row_ptr+row)->CCS95);
  }
  int get_CCS96(int row) {
    return ((row_ptr+row)->CCS96);
  }
};

struct CCT_row {
  short ID;
  short TDC;
};

class CCT {
private:
  int nrows;
  struct CCT_row *row_ptr;
public:
  CCT(void) {
    return;
  }
  CCT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct CHI2_row {
  float chi2;
  float cl;
  int ndf;
  int iter;
};

class CHI2 {
private:
  int nrows;
  struct CHI2_row *row_ptr;
public:
  CHI2(void) {
    return;
  }
  CHI2(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_chi2(int row) {
    return ((row_ptr+row)->chi2);
  }
  float get_cl(int row) {
    return ((row_ptr+row)->cl);
  }
  int get_ndf(int row) {
    return ((row_ptr+row)->ndf);
  }
  int get_iter(int row) {
    return ((row_ptr+row)->iter);
  }
};

struct CL01_row {
  int ac_amp;
  int fc_diode_amp;
  float fc_diode_t;
  int nc_diode_amp;
  float nc_diode_t;
  int sc_diode_amp;
  float sc_diode_t;
  int sf_diode_amp;
  float sf_diode_t;
  float rf1;
  float rf2;
  float rf;
};

class CL01 {
private:
  int nrows;
  struct CL01_row *row_ptr;
public:
  CL01(void) {
    return;
  }
  CL01(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ac_amp(int row) {
    return ((row_ptr+row)->ac_amp);
  }
  int get_fc_diode_amp(int row) {
    return ((row_ptr+row)->fc_diode_amp);
  }
  float get_fc_diode_t(int row) {
    return ((row_ptr+row)->fc_diode_t);
  }
  int get_nc_diode_amp(int row) {
    return ((row_ptr+row)->nc_diode_amp);
  }
  float get_nc_diode_t(int row) {
    return ((row_ptr+row)->nc_diode_t);
  }
  int get_sc_diode_amp(int row) {
    return ((row_ptr+row)->sc_diode_amp);
  }
  float get_sc_diode_t(int row) {
    return ((row_ptr+row)->sc_diode_t);
  }
  int get_sf_diode_amp(int row) {
    return ((row_ptr+row)->sf_diode_amp);
  }
  float get_sf_diode_t(int row) {
    return ((row_ptr+row)->sf_diode_t);
  }
  float get_rf1(int row) {
    return ((row_ptr+row)->rf1);
  }
  float get_rf2(int row) {
    return ((row_ptr+row)->rf2);
  }
  float get_rf(int row) {
    return ((row_ptr+row)->rf);
  }
};

struct CLST_row {
  int Clust;
};

class CLST {
private:
  int nrows;
  struct CLST_row *row_ptr;
public:
  CLST(void) {
    return;
  }
  CLST(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_Clust(int row) {
    return ((row_ptr+row)->Clust);
  }
};

struct CPED_row {
  int slot;
  int channel;
  int mean;
  float sigma;
  int offset;
};

class CPED {
private:
  int nrows;
  struct CPED_row *row_ptr;
public:
  CPED(void) {
    return;
  }
  CPED(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_slot(int row) {
    return ((row_ptr+row)->slot);
  }
  int get_channel(int row) {
    return ((row_ptr+row)->channel);
  }
  int get_mean(int row) {
    return ((row_ptr+row)->mean);
  }
  float get_sigma(int row) {
    return ((row_ptr+row)->sigma);
  }
  int get_offset(int row) {
    return ((row_ptr+row)->offset);
  }
};

struct CSQL_row {
  int EVID;
  int NPROC;
  float CPU;
  float FC;
  float FCG;
  float TG;
  float IBEAM;
  int NeS1;
  int NeS2;
  int NeS3;
  int NeS4;
  int NeS5;
  int NeS6;
  int Nhb;
  int Ntb;
  int Nprot;
  int Npip;
  int Ndeut;
  int Nphot;
  int Nelhp;
  int Nelhn;
};

class CSQL {
private:
  int nrows;
  struct CSQL_row *row_ptr;
public:
  CSQL(void) {
    return;
  }
  CSQL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_EVID(int row) {
    return ((row_ptr+row)->EVID);
  }
  int get_NPROC(int row) {
    return ((row_ptr+row)->NPROC);
  }
  float get_CPU(int row) {
    return ((row_ptr+row)->CPU);
  }
  float get_FC(int row) {
    return ((row_ptr+row)->FC);
  }
  float get_FCG(int row) {
    return ((row_ptr+row)->FCG);
  }
  float get_TG(int row) {
    return ((row_ptr+row)->TG);
  }
  float get_IBEAM(int row) {
    return ((row_ptr+row)->IBEAM);
  }
  int get_NeS1(int row) {
    return ((row_ptr+row)->NeS1);
  }
  int get_NeS2(int row) {
    return ((row_ptr+row)->NeS2);
  }
  int get_NeS3(int row) {
    return ((row_ptr+row)->NeS3);
  }
  int get_NeS4(int row) {
    return ((row_ptr+row)->NeS4);
  }
  int get_NeS5(int row) {
    return ((row_ptr+row)->NeS5);
  }
  int get_NeS6(int row) {
    return ((row_ptr+row)->NeS6);
  }
  int get_Nhb(int row) {
    return ((row_ptr+row)->Nhb);
  }
  int get_Ntb(int row) {
    return ((row_ptr+row)->Ntb);
  }
  int get_Nprot(int row) {
    return ((row_ptr+row)->Nprot);
  }
  int get_Npip(int row) {
    return ((row_ptr+row)->Npip);
  }
  int get_Ndeut(int row) {
    return ((row_ptr+row)->Ndeut);
  }
  int get_Nphot(int row) {
    return ((row_ptr+row)->Nphot);
  }
  int get_Nelhp(int row) {
    return ((row_ptr+row)->Nelhp);
  }
  int get_Nelhn(int row) {
    return ((row_ptr+row)->Nelhn);
  }
};

struct DC0_row {
  short ID;
  short TDC;
};

class DC0 {
private:
  int nrows;
  struct DC0_row *row_ptr;
public:
  DC0(void) {
    return;
  }
  DC0(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct DC1_row {
  int ID;
  float time;
};

class DC1 {
private:
  int nrows;
  struct DC1_row *row_ptr;
public:
  DC1(void) {
    return;
  }
  DC1(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  float get_time(int row) {
    return ((row_ptr+row)->time);
  }
};

struct DCDW_row {
  int ID;
  float TIDLY;
  int STAT;
};

class DCDW {
private:
  int nrows;
  struct DCDW_row *row_ptr;
public:
  DCDW(void) {
    return;
  }
  DCDW(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  float get_TIDLY(int row) {
    return ((row_ptr+row)->TIDLY);
  }
  int get_STAT(int row) {
    return ((row_ptr+row)->STAT);
  }
};

struct DCGM_row {
  float x_curve;
  float y_curve;
  float z_curve;
  float r_curve;
  float theta_start;
  float d_theta;
  float x_nmid;
  float y_nmid;
  float z_nmid;
  float theta_min;
  float theta_max;
  int min_wire;
  int max_wire;
  float stereo;
  float cell_size;
  float x_norm;
  float y_norm;
  float z_norm;
  float p_dist;
  float p_sep;
  int max_cylw;
};

class DCGM {
private:
  int nrows;
  struct DCGM_row *row_ptr;
public:
  DCGM(void) {
    return;
  }
  DCGM(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_x_curve(int row) {
    return ((row_ptr+row)->x_curve);
  }
  float get_y_curve(int row) {
    return ((row_ptr+row)->y_curve);
  }
  float get_z_curve(int row) {
    return ((row_ptr+row)->z_curve);
  }
  float get_r_curve(int row) {
    return ((row_ptr+row)->r_curve);
  }
  float get_theta_start(int row) {
    return ((row_ptr+row)->theta_start);
  }
  float get_d_theta(int row) {
    return ((row_ptr+row)->d_theta);
  }
  float get_x_nmid(int row) {
    return ((row_ptr+row)->x_nmid);
  }
  float get_y_nmid(int row) {
    return ((row_ptr+row)->y_nmid);
  }
  float get_z_nmid(int row) {
    return ((row_ptr+row)->z_nmid);
  }
  float get_theta_min(int row) {
    return ((row_ptr+row)->theta_min);
  }
  float get_theta_max(int row) {
    return ((row_ptr+row)->theta_max);
  }
  int get_min_wire(int row) {
    return ((row_ptr+row)->min_wire);
  }
  int get_max_wire(int row) {
    return ((row_ptr+row)->max_wire);
  }
  float get_stereo(int row) {
    return ((row_ptr+row)->stereo);
  }
  float get_cell_size(int row) {
    return ((row_ptr+row)->cell_size);
  }
  float get_x_norm(int row) {
    return ((row_ptr+row)->x_norm);
  }
  float get_y_norm(int row) {
    return ((row_ptr+row)->y_norm);
  }
  float get_z_norm(int row) {
    return ((row_ptr+row)->z_norm);
  }
  float get_p_dist(int row) {
    return ((row_ptr+row)->p_dist);
  }
  float get_p_sep(int row) {
    return ((row_ptr+row)->p_sep);
  }
  int get_max_cylw(int row) {
    return ((row_ptr+row)->max_cylw);
  }
};

struct DCGW_row {
  float x_mid;
  float y_mid;
  float z_mid;
  float x_dir;
  float y_dir;
  float z_dir;
  float w_len;
  float w_len_hv;
};

class DCGW {
private:
  int nrows;
  struct DCGW_row *row_ptr;
public:
  DCGW(void) {
    return;
  }
  DCGW(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_x_mid(int row) {
    return ((row_ptr+row)->x_mid);
  }
  float get_y_mid(int row) {
    return ((row_ptr+row)->y_mid);
  }
  float get_z_mid(int row) {
    return ((row_ptr+row)->z_mid);
  }
  float get_x_dir(int row) {
    return ((row_ptr+row)->x_dir);
  }
  float get_y_dir(int row) {
    return ((row_ptr+row)->y_dir);
  }
  float get_z_dir(int row) {
    return ((row_ptr+row)->z_dir);
  }
  float get_w_len(int row) {
    return ((row_ptr+row)->w_len);
  }
  float get_w_len_hv(int row) {
    return ((row_ptr+row)->w_len_hv);
  }
};

struct DCH_row {
  float x;
  float y;
  float z;
  float step;
  float dedx;
  float pmom;
  float time;
  float cx;
  float cy;
  float cz;
  int track;
  int id;
  int layer;
};

class DCH {
private:
  int nrows;
  struct DCH_row *row_ptr;
public:
  DCH(void) {
    return;
  }
  DCH(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_step(int row) {
    return ((row_ptr+row)->step);
  }
  float get_dedx(int row) {
    return ((row_ptr+row)->dedx);
  }
  float get_pmom(int row) {
    return ((row_ptr+row)->pmom);
  }
  float get_time(int row) {
    return ((row_ptr+row)->time);
  }
  float get_cx(int row) {
    return ((row_ptr+row)->cx);
  }
  float get_cy(int row) {
    return ((row_ptr+row)->cy);
  }
  float get_cz(int row) {
    return ((row_ptr+row)->cz);
  }
  int get_track(int row) {
    return ((row_ptr+row)->track);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  int get_layer(int row) {
    return ((row_ptr+row)->layer);
  }
};

struct DCMN_row {
  float HBT_evt_1;
  float TBT_evt_1;
  float HBT_evt_2;
  float TBT_evt_2;
  float HBT_evt_3;
  float TBT_evt_3;
  float HBT_evt_4;
  float TBT_evt_4;
  float HBT_evt_5;
  float TBT_evt_5;
  float HBT_evt_6;
  float TBT_evt_6;
  float HBT_evt_all;
  float TBT_evt_all;
  float Res_s1_sl1;
  float Res_s1_sl2;
  float Res_s1_sl3;
  float Res_s1_sl4;
  float Res_s1_sl5;
  float Res_s1_sl6;
  float Res_s2_sl1;
  float Res_s2_sl2;
  float Res_s2_sl3;
  float Res_s2_sl4;
  float Res_s2_sl5;
  float Res_s2_sl6;
  float Res_s3_sl1;
  float Res_s3_sl2;
  float Res_s3_sl3;
  float Res_s3_sl4;
  float Res_s3_sl5;
  float Res_s3_sl6;
  float Res_s4_sl1;
  float Res_s4_sl2;
  float Res_s4_sl3;
  float Res_s4_sl4;
  float Res_s4_sl5;
  float Res_s4_sl6;
  float Res_s5_sl1;
  float Res_s5_sl2;
  float Res_s5_sl3;
  float Res_s5_sl4;
  float Res_s5_sl5;
  float Res_s5_sl6;
  float Res_s6_sl1;
  float Res_s6_sl2;
  float Res_s6_sl3;
  float Res_s6_sl4;
  float Res_s6_sl5;
  float Res_s6_sl6;
};

class DCMN {
private:
  int nrows;
  struct DCMN_row *row_ptr;
public:
  DCMN(void) {
    return;
  }
  DCMN(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_HBT_evt_1(int row) {
    return ((row_ptr+row)->HBT_evt_1);
  }
  float get_TBT_evt_1(int row) {
    return ((row_ptr+row)->TBT_evt_1);
  }
  float get_HBT_evt_2(int row) {
    return ((row_ptr+row)->HBT_evt_2);
  }
  float get_TBT_evt_2(int row) {
    return ((row_ptr+row)->TBT_evt_2);
  }
  float get_HBT_evt_3(int row) {
    return ((row_ptr+row)->HBT_evt_3);
  }
  float get_TBT_evt_3(int row) {
    return ((row_ptr+row)->TBT_evt_3);
  }
  float get_HBT_evt_4(int row) {
    return ((row_ptr+row)->HBT_evt_4);
  }
  float get_TBT_evt_4(int row) {
    return ((row_ptr+row)->TBT_evt_4);
  }
  float get_HBT_evt_5(int row) {
    return ((row_ptr+row)->HBT_evt_5);
  }
  float get_TBT_evt_5(int row) {
    return ((row_ptr+row)->TBT_evt_5);
  }
  float get_HBT_evt_6(int row) {
    return ((row_ptr+row)->HBT_evt_6);
  }
  float get_TBT_evt_6(int row) {
    return ((row_ptr+row)->TBT_evt_6);
  }
  float get_HBT_evt_all(int row) {
    return ((row_ptr+row)->HBT_evt_all);
  }
  float get_TBT_evt_all(int row) {
    return ((row_ptr+row)->TBT_evt_all);
  }
  float get_Res_s1_sl1(int row) {
    return ((row_ptr+row)->Res_s1_sl1);
  }
  float get_Res_s1_sl2(int row) {
    return ((row_ptr+row)->Res_s1_sl2);
  }
  float get_Res_s1_sl3(int row) {
    return ((row_ptr+row)->Res_s1_sl3);
  }
  float get_Res_s1_sl4(int row) {
    return ((row_ptr+row)->Res_s1_sl4);
  }
  float get_Res_s1_sl5(int row) {
    return ((row_ptr+row)->Res_s1_sl5);
  }
  float get_Res_s1_sl6(int row) {
    return ((row_ptr+row)->Res_s1_sl6);
  }
  float get_Res_s2_sl1(int row) {
    return ((row_ptr+row)->Res_s2_sl1);
  }
  float get_Res_s2_sl2(int row) {
    return ((row_ptr+row)->Res_s2_sl2);
  }
  float get_Res_s2_sl3(int row) {
    return ((row_ptr+row)->Res_s2_sl3);
  }
  float get_Res_s2_sl4(int row) {
    return ((row_ptr+row)->Res_s2_sl4);
  }
  float get_Res_s2_sl5(int row) {
    return ((row_ptr+row)->Res_s2_sl5);
  }
  float get_Res_s2_sl6(int row) {
    return ((row_ptr+row)->Res_s2_sl6);
  }
  float get_Res_s3_sl1(int row) {
    return ((row_ptr+row)->Res_s3_sl1);
  }
  float get_Res_s3_sl2(int row) {
    return ((row_ptr+row)->Res_s3_sl2);
  }
  float get_Res_s3_sl3(int row) {
    return ((row_ptr+row)->Res_s3_sl3);
  }
  float get_Res_s3_sl4(int row) {
    return ((row_ptr+row)->Res_s3_sl4);
  }
  float get_Res_s3_sl5(int row) {
    return ((row_ptr+row)->Res_s3_sl5);
  }
  float get_Res_s3_sl6(int row) {
    return ((row_ptr+row)->Res_s3_sl6);
  }
  float get_Res_s4_sl1(int row) {
    return ((row_ptr+row)->Res_s4_sl1);
  }
  float get_Res_s4_sl2(int row) {
    return ((row_ptr+row)->Res_s4_sl2);
  }
  float get_Res_s4_sl3(int row) {
    return ((row_ptr+row)->Res_s4_sl3);
  }
  float get_Res_s4_sl4(int row) {
    return ((row_ptr+row)->Res_s4_sl4);
  }
  float get_Res_s4_sl5(int row) {
    return ((row_ptr+row)->Res_s4_sl5);
  }
  float get_Res_s4_sl6(int row) {
    return ((row_ptr+row)->Res_s4_sl6);
  }
  float get_Res_s5_sl1(int row) {
    return ((row_ptr+row)->Res_s5_sl1);
  }
  float get_Res_s5_sl2(int row) {
    return ((row_ptr+row)->Res_s5_sl2);
  }
  float get_Res_s5_sl3(int row) {
    return ((row_ptr+row)->Res_s5_sl3);
  }
  float get_Res_s5_sl4(int row) {
    return ((row_ptr+row)->Res_s5_sl4);
  }
  float get_Res_s5_sl5(int row) {
    return ((row_ptr+row)->Res_s5_sl5);
  }
  float get_Res_s5_sl6(int row) {
    return ((row_ptr+row)->Res_s5_sl6);
  }
  float get_Res_s6_sl1(int row) {
    return ((row_ptr+row)->Res_s6_sl1);
  }
  float get_Res_s6_sl2(int row) {
    return ((row_ptr+row)->Res_s6_sl2);
  }
  float get_Res_s6_sl3(int row) {
    return ((row_ptr+row)->Res_s6_sl3);
  }
  float get_Res_s6_sl4(int row) {
    return ((row_ptr+row)->Res_s6_sl4);
  }
  float get_Res_s6_sl5(int row) {
    return ((row_ptr+row)->Res_s6_sl5);
  }
  float get_Res_s6_sl6(int row) {
    return ((row_ptr+row)->Res_s6_sl6);
  }
};

struct DCPB_row {
  int ScTr;
  float x_SC;
  float y_SC;
  float z_SC;
  float CX_SC;
  float CY_SC;
  float CZ_SC;
  float X_v;
  float Y_v;
  float Z_v;
  float R_v;
  float Chi2;
  int Status;
};

class DCPB {
private:
  int nrows;
  struct DCPB_row *row_ptr;
public:
  DCPB(void) {
    return;
  }
  DCPB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ScTr(int row) {
    return ((row_ptr+row)->ScTr);
  }
  float get_x_SC(int row) {
    return ((row_ptr+row)->x_SC);
  }
  float get_y_SC(int row) {
    return ((row_ptr+row)->y_SC);
  }
  float get_z_SC(int row) {
    return ((row_ptr+row)->z_SC);
  }
  float get_CX_SC(int row) {
    return ((row_ptr+row)->CX_SC);
  }
  float get_CY_SC(int row) {
    return ((row_ptr+row)->CY_SC);
  }
  float get_CZ_SC(int row) {
    return ((row_ptr+row)->CZ_SC);
  }
  float get_X_v(int row) {
    return ((row_ptr+row)->X_v);
  }
  float get_Y_v(int row) {
    return ((row_ptr+row)->Y_v);
  }
  float get_Z_v(int row) {
    return ((row_ptr+row)->Z_v);
  }
  float get_R_v(int row) {
    return ((row_ptr+row)->R_v);
  }
  float get_Chi2(int row) {
    return ((row_ptr+row)->Chi2);
  }
  int get_Status(int row) {
    return ((row_ptr+row)->Status);
  }
};

struct DCV1_row {
  float TsR1;
  float V0R1;
  float TmR1;
  float sp1R1;
  float sp2R1;
};

class DCV1 {
private:
  int nrows;
  struct DCV1_row *row_ptr;
public:
  DCV1(void) {
    return;
  }
  DCV1(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_TsR1(int row) {
    return ((row_ptr+row)->TsR1);
  }
  float get_V0R1(int row) {
    return ((row_ptr+row)->V0R1);
  }
  float get_TmR1(int row) {
    return ((row_ptr+row)->TmR1);
  }
  float get_sp1R1(int row) {
    return ((row_ptr+row)->sp1R1);
  }
  float get_sp2R1(int row) {
    return ((row_ptr+row)->sp2R1);
  }
};

struct DCV2_row {
  float Ts1R2;
  float V01R2;
  float VA1R2;
  float VB1R2;
  float Tm1R2;
  float TA1R2;
  float TB1R2;
  float Ts2R2;
  float V02R2;
  float VA2R2;
  float VB2R2;
  float Tm2R2;
  float TA2R2;
  float TB2R2;
};

class DCV2 {
private:
  int nrows;
  struct DCV2_row *row_ptr;
public:
  DCV2(void) {
    return;
  }
  DCV2(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_Ts1R2(int row) {
    return ((row_ptr+row)->Ts1R2);
  }
  float get_V01R2(int row) {
    return ((row_ptr+row)->V01R2);
  }
  float get_VA1R2(int row) {
    return ((row_ptr+row)->VA1R2);
  }
  float get_VB1R2(int row) {
    return ((row_ptr+row)->VB1R2);
  }
  float get_Tm1R2(int row) {
    return ((row_ptr+row)->Tm1R2);
  }
  float get_TA1R2(int row) {
    return ((row_ptr+row)->TA1R2);
  }
  float get_TB1R2(int row) {
    return ((row_ptr+row)->TB1R2);
  }
  float get_Ts2R2(int row) {
    return ((row_ptr+row)->Ts2R2);
  }
  float get_V02R2(int row) {
    return ((row_ptr+row)->V02R2);
  }
  float get_VA2R2(int row) {
    return ((row_ptr+row)->VA2R2);
  }
  float get_VB2R2(int row) {
    return ((row_ptr+row)->VB2R2);
  }
  float get_Tm2R2(int row) {
    return ((row_ptr+row)->Tm2R2);
  }
  float get_TA2R2(int row) {
    return ((row_ptr+row)->TA2R2);
  }
  float get_TB2R2(int row) {
    return ((row_ptr+row)->TB2R2);
  }
};

struct DCV3_row {
  float TsR3;
  float V0R3;
  float TmR3;
  float sp1R3;
  float sp2R3;
};

class DCV3 {
private:
  int nrows;
  struct DCV3_row *row_ptr;
public:
  DCV3(void) {
    return;
  }
  DCV3(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_TsR3(int row) {
    return ((row_ptr+row)->TsR3);
  }
  float get_V0R3(int row) {
    return ((row_ptr+row)->V0R3);
  }
  float get_TmR3(int row) {
    return ((row_ptr+row)->TmR3);
  }
  float get_sp1R3(int row) {
    return ((row_ptr+row)->sp1R3);
  }
  float get_sp2R3(int row) {
    return ((row_ptr+row)->sp2R3);
  }
};

struct DDLY_row {
  int ID;
  float TIDLY;
  int STAT;
};

class DDLY {
private:
  int nrows;
  struct DDLY_row *row_ptr;
public:
  DDLY(void) {
    return;
  }
  DDLY(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  float get_TIDLY(int row) {
    return ((row_ptr+row)->TIDLY);
  }
  int get_STAT(int row) {
    return ((row_ptr+row)->STAT);
  }
};

struct DGEO_row {
  int ID_sec;
  int ID_reg;
  float xpos;
  float ypos;
  float zpos;
  float sxpos;
  float sypos;
  float szpos;
};

class DGEO {
private:
  int nrows;
  struct DGEO_row *row_ptr;
public:
  DGEO(void) {
    return;
  }
  DGEO(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID_sec(int row) {
    return ((row_ptr+row)->ID_sec);
  }
  int get_ID_reg(int row) {
    return ((row_ptr+row)->ID_reg);
  }
  float get_xpos(int row) {
    return ((row_ptr+row)->xpos);
  }
  float get_ypos(int row) {
    return ((row_ptr+row)->ypos);
  }
  float get_zpos(int row) {
    return ((row_ptr+row)->zpos);
  }
  float get_sxpos(int row) {
    return ((row_ptr+row)->sxpos);
  }
  float get_sypos(int row) {
    return ((row_ptr+row)->sypos);
  }
  float get_szpos(int row) {
    return ((row_ptr+row)->szpos);
  }
};

struct DHCL_row {
  int SLY;
  int BTRK;
  int TRKS1;
  int TRKS2;
  int WIRE1;
  int BWIR1;
  int WIRE2;
  int BWIR2;
  int WIRE3;
  int BWIR3;
  int WIRE4;
  int BWIR4;
  int WIRE5;
  int BWIR5;
  int WIRE6;
  int BWIR6;
};

class DHCL {
private:
  int nrows;
  struct DHCL_row *row_ptr;
public:
  DHCL(void) {
    return;
  }
  DHCL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_SLY(int row) {
    return ((row_ptr+row)->SLY);
  }
  int get_BTRK(int row) {
    return ((row_ptr+row)->BTRK);
  }
  int get_TRKS1(int row) {
    return ((row_ptr+row)->TRKS1);
  }
  int get_TRKS2(int row) {
    return ((row_ptr+row)->TRKS2);
  }
  int get_WIRE1(int row) {
    return ((row_ptr+row)->WIRE1);
  }
  int get_BWIR1(int row) {
    return ((row_ptr+row)->BWIR1);
  }
  int get_WIRE2(int row) {
    return ((row_ptr+row)->WIRE2);
  }
  int get_BWIR2(int row) {
    return ((row_ptr+row)->BWIR2);
  }
  int get_WIRE3(int row) {
    return ((row_ptr+row)->WIRE3);
  }
  int get_BWIR3(int row) {
    return ((row_ptr+row)->BWIR3);
  }
  int get_WIRE4(int row) {
    return ((row_ptr+row)->WIRE4);
  }
  int get_BWIR4(int row) {
    return ((row_ptr+row)->BWIR4);
  }
  int get_WIRE5(int row) {
    return ((row_ptr+row)->WIRE5);
  }
  int get_BWIR5(int row) {
    return ((row_ptr+row)->BWIR5);
  }
  int get_WIRE6(int row) {
    return ((row_ptr+row)->WIRE6);
  }
  int get_BWIR6(int row) {
    return ((row_ptr+row)->BWIR6);
  }
};

struct DITM_row {
  int time;
};

class DITM {
private:
  int nrows;
  struct DITM_row *row_ptr;
public:
  DITM(void) {
    return;
  }
  DITM(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_time(int row) {
    return ((row_ptr+row)->time);
  }
};

struct DOCA_row {
  short ID;
  short DOCA;
};

class DOCA {
private:
  int nrows;
  struct DOCA_row *row_ptr;
public:
  DOCA(void) {
    return;
  }
  DOCA(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_DOCA(int row) {
    return ((row_ptr+row)->DOCA);
  }
};

struct DPCP_row {
  int ID;
  int MN_mean;
  float MN_sigma;
  int LT_mean;
  float LT_sigma;
  int RB_mean;
  float RB_sigma;
  int LB_mean;
  float LB_sigma;
  int RT_mean;
  float RT_sigma;
  int VT_mean;
  float VT_sigma;
};

class DPCP {
private:
  int nrows;
  struct DPCP_row *row_ptr;
public:
  DPCP(void) {
    return;
  }
  DPCP(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_MN_mean(int row) {
    return ((row_ptr+row)->MN_mean);
  }
  float get_MN_sigma(int row) {
    return ((row_ptr+row)->MN_sigma);
  }
  int get_LT_mean(int row) {
    return ((row_ptr+row)->LT_mean);
  }
  float get_LT_sigma(int row) {
    return ((row_ptr+row)->LT_sigma);
  }
  int get_RB_mean(int row) {
    return ((row_ptr+row)->RB_mean);
  }
  float get_RB_sigma(int row) {
    return ((row_ptr+row)->RB_sigma);
  }
  int get_LB_mean(int row) {
    return ((row_ptr+row)->LB_mean);
  }
  float get_LB_sigma(int row) {
    return ((row_ptr+row)->LB_sigma);
  }
  int get_RT_mean(int row) {
    return ((row_ptr+row)->RT_mean);
  }
  float get_RT_sigma(int row) {
    return ((row_ptr+row)->RT_sigma);
  }
  int get_VT_mean(int row) {
    return ((row_ptr+row)->VT_mean);
  }
  float get_VT_sigma(int row) {
    return ((row_ptr+row)->VT_sigma);
  }
};

struct DPSP_row {
  int ID;
  int mean;
  float sigma;
};

class DPSP {
private:
  int nrows;
  struct DPSP_row *row_ptr;
public:
  DPSP(void) {
    return;
  }
  DPSP(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_mean(int row) {
    return ((row_ptr+row)->mean);
  }
  float get_sigma(int row) {
    return ((row_ptr+row)->sigma);
  }
};

struct DSPC_row {
  short PCID;
  short TDCPC;
  short ADCMN;
  short ADCLT;
  short ADCRB;
  short ADCLB;
  short ADCRT;
  short ADCVE;
};

class DSPC {
private:
  int nrows;
  struct DSPC_row *row_ptr;
public:
  DSPC(void) {
    return;
  }
  DSPC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_PCID(int row) {
    return ((row_ptr+row)->PCID);
  }
  short get_TDCPC(int row) {
    return ((row_ptr+row)->TDCPC);
  }
  short get_ADCMN(int row) {
    return ((row_ptr+row)->ADCMN);
  }
  short get_ADCLT(int row) {
    return ((row_ptr+row)->ADCLT);
  }
  short get_ADCRB(int row) {
    return ((row_ptr+row)->ADCRB);
  }
  short get_ADCLB(int row) {
    return ((row_ptr+row)->ADCLB);
  }
  short get_ADCRT(int row) {
    return ((row_ptr+row)->ADCRT);
  }
  short get_ADCVE(int row) {
    return ((row_ptr+row)->ADCVE);
  }
};

struct DSPS_row {
  short ID;
  short TDC;
  short ADC;
};

class DSPS {
private:
  int nrows;
  struct DSPS_row *row_ptr;
public:
  DSPS(void) {
    return;
  }
  DSPS(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
  short get_ADC(int row) {
    return ((row_ptr+row)->ADC);
  }
};

struct DSTC_row {
  short TACID;
  short TDCTAC;
  short ADCLT;
  short ADCRT;
  short ADCLB;
  short ADCRB;
  short ADCSUM1;
  short ADCSUM2;
  short ADCSUM3;
};

class DSTC {
private:
  int nrows;
  struct DSTC_row *row_ptr;
public:
  DSTC(void) {
    return;
  }
  DSTC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_TACID(int row) {
    return ((row_ptr+row)->TACID);
  }
  short get_TDCTAC(int row) {
    return ((row_ptr+row)->TDCTAC);
  }
  short get_ADCLT(int row) {
    return ((row_ptr+row)->ADCLT);
  }
  short get_ADCRT(int row) {
    return ((row_ptr+row)->ADCRT);
  }
  short get_ADCLB(int row) {
    return ((row_ptr+row)->ADCLB);
  }
  short get_ADCRB(int row) {
    return ((row_ptr+row)->ADCRB);
  }
  short get_ADCSUM1(int row) {
    return ((row_ptr+row)->ADCSUM1);
  }
  short get_ADCSUM2(int row) {
    return ((row_ptr+row)->ADCSUM2);
  }
  short get_ADCSUM3(int row) {
    return ((row_ptr+row)->ADCSUM3);
  }
};

struct DTCP_row {
  int ID;
  int LT_mean;
  float LT_sigma;
  int RT_mean;
  float RT_sigma;
  int LB_mean;
  float LB_sigma;
  int RB_mean;
  float RB_sigma;
  int sum1_mean;
  float sum1_sigma;
  int sum2_mean;
  float sum2_sigma;
  int sum3_mean;
  float sum3_sigma;
};

class DTCP {
private:
  int nrows;
  struct DTCP_row *row_ptr;
public:
  DTCP(void) {
    return;
  }
  DTCP(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_LT_mean(int row) {
    return ((row_ptr+row)->LT_mean);
  }
  float get_LT_sigma(int row) {
    return ((row_ptr+row)->LT_sigma);
  }
  int get_RT_mean(int row) {
    return ((row_ptr+row)->RT_mean);
  }
  float get_RT_sigma(int row) {
    return ((row_ptr+row)->RT_sigma);
  }
  int get_LB_mean(int row) {
    return ((row_ptr+row)->LB_mean);
  }
  float get_LB_sigma(int row) {
    return ((row_ptr+row)->LB_sigma);
  }
  int get_RB_mean(int row) {
    return ((row_ptr+row)->RB_mean);
  }
  float get_RB_sigma(int row) {
    return ((row_ptr+row)->RB_sigma);
  }
  int get_sum1_mean(int row) {
    return ((row_ptr+row)->sum1_mean);
  }
  float get_sum1_sigma(int row) {
    return ((row_ptr+row)->sum1_sigma);
  }
  int get_sum2_mean(int row) {
    return ((row_ptr+row)->sum2_mean);
  }
  float get_sum2_sigma(int row) {
    return ((row_ptr+row)->sum2_sigma);
  }
  int get_sum3_mean(int row) {
    return ((row_ptr+row)->sum3_mean);
  }
  float get_sum3_sigma(int row) {
    return ((row_ptr+row)->sum3_sigma);
  }
};

struct DTRK_row {
  float X;
  float Y;
  float Z;
};

class DTRK {
private:
  int nrows;
  struct DTRK_row *row_ptr;
public:
  DTRK(void) {
    return;
  }
  DTRK(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_X(int row) {
    return ((row_ptr+row)->X);
  }
  float get_Y(int row) {
    return ((row_ptr+row)->Y);
  }
  float get_Z(int row) {
    return ((row_ptr+row)->Z);
  }
};

struct EC01_row {
  int ID;
  float time;
  float energy;
};

class EC01 {
private:
  int nrows;
  struct EC01_row *row_ptr;
public:
  EC01(void) {
    return;
  }
  EC01(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  float get_time(int row) {
    return ((row_ptr+row)->time);
  }
  float get_energy(int row) {
    return ((row_ptr+row)->energy);
  }
};

struct EC1_row {
  short ID;
  short TDCL;
  short ADCL;
  short TDCR;
  short ADCR;
};

class EC1 {
private:
  int nrows;
  struct EC1_row *row_ptr;
public:
  EC1(void) {
    return;
  }
  EC1(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDCL(int row) {
    return ((row_ptr+row)->TDCL);
  }
  short get_ADCL(int row) {
    return ((row_ptr+row)->ADCL);
  }
  short get_TDCR(int row) {
    return ((row_ptr+row)->TDCR);
  }
  short get_ADCR(int row) {
    return ((row_ptr+row)->ADCR);
  }
};

struct EC1P_row {
  float N1x;
  float N1y;
  float N1z;
  float R1n;
};

class EC1P {
private:
  int nrows;
  struct EC1P_row *row_ptr;
public:
  EC1P(void) {
    return;
  }
  EC1P(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_N1x(int row) {
    return ((row_ptr+row)->N1x);
  }
  float get_N1y(int row) {
    return ((row_ptr+row)->N1y);
  }
  float get_N1z(int row) {
    return ((row_ptr+row)->N1z);
  }
  float get_R1n(int row) {
    return ((row_ptr+row)->R1n);
  }
};

struct EC1R_row {
  float E_tot;
  float dE_tot;
  float t_tot;
  float dt_tot;
  float x_m;
  float y_m;
  float z_m;
  float dx_m;
  float dy_m;
  float dz_m;
  float E_in;
  float t_in;
  float x_in;
  float y_in;
  float x_out;
  float y_out;
  float x2_in_l;
  float x2_in_r;
  float y2_in_l;
  float y2_in_r;
  float x2_out_l;
  float x2_out_r;
  float y2_out_l;
  float y2_out_r;
  int i_in;
  int j_in;
  int i_out;
  int j_out;
  float a_in_xl;
  float a_in_xr;
  float a_in_yl;
  float a_in_yr;
  float a_out_xl;
  float a_out_xr;
  float a_out_yl;
  float a_out_yr;
  float t_in_xs;
  float t_in_xd;
  float t_in_ys;
  float t_in_yd;
  float t_out_xs;
  float t_out_xd;
  float t_out_ys;
  float t_out_yd;
  int ibl;
  int ncluster;
  int pmtfired;
  float z_in;
  float z_out;
  int istat;
};

class EC1R {
private:
  int nrows;
  struct EC1R_row *row_ptr;
public:
  EC1R(void) {
    return;
  }
  EC1R(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_E_tot(int row) {
    return ((row_ptr+row)->E_tot);
  }
  float get_dE_tot(int row) {
    return ((row_ptr+row)->dE_tot);
  }
  float get_t_tot(int row) {
    return ((row_ptr+row)->t_tot);
  }
  float get_dt_tot(int row) {
    return ((row_ptr+row)->dt_tot);
  }
  float get_x_m(int row) {
    return ((row_ptr+row)->x_m);
  }
  float get_y_m(int row) {
    return ((row_ptr+row)->y_m);
  }
  float get_z_m(int row) {
    return ((row_ptr+row)->z_m);
  }
  float get_dx_m(int row) {
    return ((row_ptr+row)->dx_m);
  }
  float get_dy_m(int row) {
    return ((row_ptr+row)->dy_m);
  }
  float get_dz_m(int row) {
    return ((row_ptr+row)->dz_m);
  }
  float get_E_in(int row) {
    return ((row_ptr+row)->E_in);
  }
  float get_t_in(int row) {
    return ((row_ptr+row)->t_in);
  }
  float get_x_in(int row) {
    return ((row_ptr+row)->x_in);
  }
  float get_y_in(int row) {
    return ((row_ptr+row)->y_in);
  }
  float get_x_out(int row) {
    return ((row_ptr+row)->x_out);
  }
  float get_y_out(int row) {
    return ((row_ptr+row)->y_out);
  }
  float get_x2_in_l(int row) {
    return ((row_ptr+row)->x2_in_l);
  }
  float get_x2_in_r(int row) {
    return ((row_ptr+row)->x2_in_r);
  }
  float get_y2_in_l(int row) {
    return ((row_ptr+row)->y2_in_l);
  }
  float get_y2_in_r(int row) {
    return ((row_ptr+row)->y2_in_r);
  }
  float get_x2_out_l(int row) {
    return ((row_ptr+row)->x2_out_l);
  }
  float get_x2_out_r(int row) {
    return ((row_ptr+row)->x2_out_r);
  }
  float get_y2_out_l(int row) {
    return ((row_ptr+row)->y2_out_l);
  }
  float get_y2_out_r(int row) {
    return ((row_ptr+row)->y2_out_r);
  }
  int get_i_in(int row) {
    return ((row_ptr+row)->i_in);
  }
  int get_j_in(int row) {
    return ((row_ptr+row)->j_in);
  }
  int get_i_out(int row) {
    return ((row_ptr+row)->i_out);
  }
  int get_j_out(int row) {
    return ((row_ptr+row)->j_out);
  }
  float get_a_in_xl(int row) {
    return ((row_ptr+row)->a_in_xl);
  }
  float get_a_in_xr(int row) {
    return ((row_ptr+row)->a_in_xr);
  }
  float get_a_in_yl(int row) {
    return ((row_ptr+row)->a_in_yl);
  }
  float get_a_in_yr(int row) {
    return ((row_ptr+row)->a_in_yr);
  }
  float get_a_out_xl(int row) {
    return ((row_ptr+row)->a_out_xl);
  }
  float get_a_out_xr(int row) {
    return ((row_ptr+row)->a_out_xr);
  }
  float get_a_out_yl(int row) {
    return ((row_ptr+row)->a_out_yl);
  }
  float get_a_out_yr(int row) {
    return ((row_ptr+row)->a_out_yr);
  }
  float get_t_in_xs(int row) {
    return ((row_ptr+row)->t_in_xs);
  }
  float get_t_in_xd(int row) {
    return ((row_ptr+row)->t_in_xd);
  }
  float get_t_in_ys(int row) {
    return ((row_ptr+row)->t_in_ys);
  }
  float get_t_in_yd(int row) {
    return ((row_ptr+row)->t_in_yd);
  }
  float get_t_out_xs(int row) {
    return ((row_ptr+row)->t_out_xs);
  }
  float get_t_out_xd(int row) {
    return ((row_ptr+row)->t_out_xd);
  }
  float get_t_out_ys(int row) {
    return ((row_ptr+row)->t_out_ys);
  }
  float get_t_out_yd(int row) {
    return ((row_ptr+row)->t_out_yd);
  }
  int get_ibl(int row) {
    return ((row_ptr+row)->ibl);
  }
  int get_ncluster(int row) {
    return ((row_ptr+row)->ncluster);
  }
  int get_pmtfired(int row) {
    return ((row_ptr+row)->pmtfired);
  }
  float get_z_in(int row) {
    return ((row_ptr+row)->z_in);
  }
  float get_z_out(int row) {
    return ((row_ptr+row)->z_out);
  }
  int get_istat(int row) {
    return ((row_ptr+row)->istat);
  }
};

struct ECCA_row {
  int id;
  float aPED;
  float aSIG;
  float aMIP;
  float aMIPu;
  float aSHR;
  float aSHRu;
  int stat;
};

class ECCA {
private:
  int nrows;
  struct ECCA_row *row_ptr;
public:
  ECCA(void) {
    return;
  }
  ECCA(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  float get_aPED(int row) {
    return ((row_ptr+row)->aPED);
  }
  float get_aSIG(int row) {
    return ((row_ptr+row)->aSIG);
  }
  float get_aMIP(int row) {
    return ((row_ptr+row)->aMIP);
  }
  float get_aMIPu(int row) {
    return ((row_ptr+row)->aMIPu);
  }
  float get_aSHR(int row) {
    return ((row_ptr+row)->aSHR);
  }
  float get_aSHRu(int row) {
    return ((row_ptr+row)->aSHRu);
  }
  int get_stat(int row) {
    return ((row_ptr+row)->stat);
  }
};

struct ECCL_row {
  int id;
  float lDB;
  float lDBu;
  float lMIP;
  float lMIPu;
  float lSHR;
  float lSHRu;
  int stat;
};

class ECCL {
private:
  int nrows;
  struct ECCL_row *row_ptr;
public:
  ECCL(void) {
    return;
  }
  ECCL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  float get_lDB(int row) {
    return ((row_ptr+row)->lDB);
  }
  float get_lDBu(int row) {
    return ((row_ptr+row)->lDBu);
  }
  float get_lMIP(int row) {
    return ((row_ptr+row)->lMIP);
  }
  float get_lMIPu(int row) {
    return ((row_ptr+row)->lMIPu);
  }
  float get_lSHR(int row) {
    return ((row_ptr+row)->lSHR);
  }
  float get_lSHRu(int row) {
    return ((row_ptr+row)->lSHRu);
  }
  int get_stat(int row) {
    return ((row_ptr+row)->stat);
  }
};

struct ECCT_row {
  int id;
  float tOFF;
  float tOFFu;
  float tGAIN;
  float tGAINu;
  float tW0;
  float tW0u;
  float tW1;
  float tW1u;
  float tVEF;
  float tVEFu;
  int stat;
};

class ECCT {
private:
  int nrows;
  struct ECCT_row *row_ptr;
public:
  ECCT(void) {
    return;
  }
  ECCT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  float get_tOFF(int row) {
    return ((row_ptr+row)->tOFF);
  }
  float get_tOFFu(int row) {
    return ((row_ptr+row)->tOFFu);
  }
  float get_tGAIN(int row) {
    return ((row_ptr+row)->tGAIN);
  }
  float get_tGAINu(int row) {
    return ((row_ptr+row)->tGAINu);
  }
  float get_tW0(int row) {
    return ((row_ptr+row)->tW0);
  }
  float get_tW0u(int row) {
    return ((row_ptr+row)->tW0u);
  }
  float get_tW1(int row) {
    return ((row_ptr+row)->tW1);
  }
  float get_tW1u(int row) {
    return ((row_ptr+row)->tW1u);
  }
  float get_tVEF(int row) {
    return ((row_ptr+row)->tVEF);
  }
  float get_tVEFu(int row) {
    return ((row_ptr+row)->tVEFu);
  }
  int get_stat(int row) {
    return ((row_ptr+row)->stat);
  }
};

struct EC_row {
  short ID;
  short TDC;
  short ADC;
};

class EC {
private:
  int nrows;
  struct EC_row *row_ptr;
public:
  EC(void) {
    return;
  }
  EC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
  short get_ADC(int row) {
    return ((row_ptr+row)->ADC);
  }
};

struct ECDI_row {
  int crate;
  int slot;
  int mask;
  int threshold;
  int width;
};

class ECDI {
private:
  int nrows;
  struct ECDI_row *row_ptr;
public:
  ECDI(void) {
    return;
  }
  ECDI(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_crate(int row) {
    return ((row_ptr+row)->crate);
  }
  int get_slot(int row) {
    return ((row_ptr+row)->slot);
  }
  int get_mask(int row) {
    return ((row_ptr+row)->mask);
  }
  int get_threshold(int row) {
    return ((row_ptr+row)->threshold);
  }
  int get_width(int row) {
    return ((row_ptr+row)->width);
  }
};

struct ECG_row {
  float L0;
  float THE0;
  float YLOW;
  float YHI;
  float DYLOW;
  float DYHI;
  float LRTH;
  float TANGR;
  int SECTOR;
  float PHISEC;
  float X0OFF;
  float Y0OFF;
  float Z0OFF;
  float ROTM11;
  float ROTM12;
  float ROTM13;
  float ROTM21;
  float ROTM22;
  float ROTM23;
  float ROTM31;
  float ROTM32;
  float ROTM33;
};

class ECG {
private:
  int nrows;
  struct ECG_row *row_ptr;
public:
  ECG(void) {
    return;
  }
  ECG(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_L0(int row) {
    return ((row_ptr+row)->L0);
  }
  float get_THE0(int row) {
    return ((row_ptr+row)->THE0);
  }
  float get_YLOW(int row) {
    return ((row_ptr+row)->YLOW);
  }
  float get_YHI(int row) {
    return ((row_ptr+row)->YHI);
  }
  float get_DYLOW(int row) {
    return ((row_ptr+row)->DYLOW);
  }
  float get_DYHI(int row) {
    return ((row_ptr+row)->DYHI);
  }
  float get_LRTH(int row) {
    return ((row_ptr+row)->LRTH);
  }
  float get_TANGR(int row) {
    return ((row_ptr+row)->TANGR);
  }
  int get_SECTOR(int row) {
    return ((row_ptr+row)->SECTOR);
  }
  float get_PHISEC(int row) {
    return ((row_ptr+row)->PHISEC);
  }
  float get_X0OFF(int row) {
    return ((row_ptr+row)->X0OFF);
  }
  float get_Y0OFF(int row) {
    return ((row_ptr+row)->Y0OFF);
  }
  float get_Z0OFF(int row) {
    return ((row_ptr+row)->Z0OFF);
  }
  float get_ROTM11(int row) {
    return ((row_ptr+row)->ROTM11);
  }
  float get_ROTM12(int row) {
    return ((row_ptr+row)->ROTM12);
  }
  float get_ROTM13(int row) {
    return ((row_ptr+row)->ROTM13);
  }
  float get_ROTM21(int row) {
    return ((row_ptr+row)->ROTM21);
  }
  float get_ROTM22(int row) {
    return ((row_ptr+row)->ROTM22);
  }
  float get_ROTM23(int row) {
    return ((row_ptr+row)->ROTM23);
  }
  float get_ROTM31(int row) {
    return ((row_ptr+row)->ROTM31);
  }
  float get_ROTM32(int row) {
    return ((row_ptr+row)->ROTM32);
  }
  float get_ROTM33(int row) {
    return ((row_ptr+row)->ROTM33);
  }
};

struct ECHB_row {
  int Sect;
  float E__hit;
  float dE_hit;
  float t_hit;
  float dt_hi;
  float i_hit;
  float j_hit;
  float di_hit;
  float dj_hit;
  float x_hit;
  float y_hit;
  float z_hit;
  float dx_hit;
  float dy_hit;
  float dz_hit;
  float u2_hit;
  float v2_hit;
  float w2_hit;
  float u3_hit;
  float v3_hit;
  float w3_hit;
  float u4_hit;
  float v4_hit;
  float w4_hit;
  float centr_U;
  float centr_V;
  float centr_W;
  float path_U;
  float path_V;
  float path_W;
  int Nstrp_U;
  int Nstrp_V;
  int Nstrp_W;
  int MatchID1;
  float CH21;
  int MatchID2;
  float CH22;
  int istat;
};

class ECHB {
private:
  int nrows;
  struct ECHB_row *row_ptr;
public:
  ECHB(void) {
    return;
  }
  ECHB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_Sect(int row) {
    return ((row_ptr+row)->Sect);
  }
  float get_E__hit(int row) {
    return ((row_ptr+row)->E__hit);
  }
  float get_dE_hit(int row) {
    return ((row_ptr+row)->dE_hit);
  }
  float get_t_hit(int row) {
    return ((row_ptr+row)->t_hit);
  }
  float get_dt_hi(int row) {
    return ((row_ptr+row)->dt_hi);
  }
  float get_i_hit(int row) {
    return ((row_ptr+row)->i_hit);
  }
  float get_j_hit(int row) {
    return ((row_ptr+row)->j_hit);
  }
  float get_di_hit(int row) {
    return ((row_ptr+row)->di_hit);
  }
  float get_dj_hit(int row) {
    return ((row_ptr+row)->dj_hit);
  }
  float get_x_hit(int row) {
    return ((row_ptr+row)->x_hit);
  }
  float get_y_hit(int row) {
    return ((row_ptr+row)->y_hit);
  }
  float get_z_hit(int row) {
    return ((row_ptr+row)->z_hit);
  }
  float get_dx_hit(int row) {
    return ((row_ptr+row)->dx_hit);
  }
  float get_dy_hit(int row) {
    return ((row_ptr+row)->dy_hit);
  }
  float get_dz_hit(int row) {
    return ((row_ptr+row)->dz_hit);
  }
  float get_u2_hit(int row) {
    return ((row_ptr+row)->u2_hit);
  }
  float get_v2_hit(int row) {
    return ((row_ptr+row)->v2_hit);
  }
  float get_w2_hit(int row) {
    return ((row_ptr+row)->w2_hit);
  }
  float get_u3_hit(int row) {
    return ((row_ptr+row)->u3_hit);
  }
  float get_v3_hit(int row) {
    return ((row_ptr+row)->v3_hit);
  }
  float get_w3_hit(int row) {
    return ((row_ptr+row)->w3_hit);
  }
  float get_u4_hit(int row) {
    return ((row_ptr+row)->u4_hit);
  }
  float get_v4_hit(int row) {
    return ((row_ptr+row)->v4_hit);
  }
  float get_w4_hit(int row) {
    return ((row_ptr+row)->w4_hit);
  }
  float get_centr_U(int row) {
    return ((row_ptr+row)->centr_U);
  }
  float get_centr_V(int row) {
    return ((row_ptr+row)->centr_V);
  }
  float get_centr_W(int row) {
    return ((row_ptr+row)->centr_W);
  }
  float get_path_U(int row) {
    return ((row_ptr+row)->path_U);
  }
  float get_path_V(int row) {
    return ((row_ptr+row)->path_V);
  }
  float get_path_W(int row) {
    return ((row_ptr+row)->path_W);
  }
  int get_Nstrp_U(int row) {
    return ((row_ptr+row)->Nstrp_U);
  }
  int get_Nstrp_V(int row) {
    return ((row_ptr+row)->Nstrp_V);
  }
  int get_Nstrp_W(int row) {
    return ((row_ptr+row)->Nstrp_W);
  }
  int get_MatchID1(int row) {
    return ((row_ptr+row)->MatchID1);
  }
  float get_CH21(int row) {
    return ((row_ptr+row)->CH21);
  }
  int get_MatchID2(int row) {
    return ((row_ptr+row)->MatchID2);
  }
  float get_CH22(int row) {
    return ((row_ptr+row)->CH22);
  }
  int get_istat(int row) {
    return ((row_ptr+row)->istat);
  }
};

struct ECH_row {
  float x;
  float y;
  float z;
  float cx;
  float cy;
  float cz;
  float pmom;
  int id;
  float tof;
  float edepin;
  float edepout;
};

class ECH {
private:
  int nrows;
  struct ECH_row *row_ptr;
public:
  ECH(void) {
    return;
  }
  ECH(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_cx(int row) {
    return ((row_ptr+row)->cx);
  }
  float get_cy(int row) {
    return ((row_ptr+row)->cy);
  }
  float get_cz(int row) {
    return ((row_ptr+row)->cz);
  }
  float get_pmom(int row) {
    return ((row_ptr+row)->pmom);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  float get_tof(int row) {
    return ((row_ptr+row)->tof);
  }
  float get_edepin(int row) {
    return ((row_ptr+row)->edepin);
  }
  float get_edepout(int row) {
    return ((row_ptr+row)->edepout);
  }
};

struct ECMT_row {
  int in_high;
  int out_high;
  int total_high;
  int in_lo;
  int out_lo;
  int total_lo;
};

class ECMT {
private:
  int nrows;
  struct ECMT_row *row_ptr;
public:
  ECMT(void) {
    return;
  }
  ECMT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_in_high(int row) {
    return ((row_ptr+row)->in_high);
  }
  int get_out_high(int row) {
    return ((row_ptr+row)->out_high);
  }
  int get_total_high(int row) {
    return ((row_ptr+row)->total_high);
  }
  int get_in_lo(int row) {
    return ((row_ptr+row)->in_lo);
  }
  int get_out_lo(int row) {
    return ((row_ptr+row)->out_lo);
  }
  int get_total_lo(int row) {
    return ((row_ptr+row)->total_lo);
  }
};

struct ECP1_row {
  int ID;
  int mean_left;
  float sigma_left;
  int mean_right;
  float sigma_right;
};

class ECP1 {
private:
  int nrows;
  struct ECP1_row *row_ptr;
public:
  ECP1(void) {
    return;
  }
  ECP1(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_mean_left(int row) {
    return ((row_ptr+row)->mean_left);
  }
  float get_sigma_left(int row) {
    return ((row_ptr+row)->sigma_left);
  }
  int get_mean_right(int row) {
    return ((row_ptr+row)->mean_right);
  }
  float get_sigma_right(int row) {
    return ((row_ptr+row)->sigma_right);
  }
};

struct ECPB_row {
  int ScHt;
  float Etot;
  float Ein;
  float Eout;
  float Time;
  float Path;
  float X;
  float Y;
  float Z;
  float M2_hit;
  float M3_hit;
  float M4_hit;
  int InnStr;
  int OutStr;
  float Chi2EC;
  int Status;
};

class ECPB {
private:
  int nrows;
  struct ECPB_row *row_ptr;
public:
  ECPB(void) {
    return;
  }
  ECPB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ScHt(int row) {
    return ((row_ptr+row)->ScHt);
  }
  float get_Etot(int row) {
    return ((row_ptr+row)->Etot);
  }
  float get_Ein(int row) {
    return ((row_ptr+row)->Ein);
  }
  float get_Eout(int row) {
    return ((row_ptr+row)->Eout);
  }
  float get_Time(int row) {
    return ((row_ptr+row)->Time);
  }
  float get_Path(int row) {
    return ((row_ptr+row)->Path);
  }
  float get_X(int row) {
    return ((row_ptr+row)->X);
  }
  float get_Y(int row) {
    return ((row_ptr+row)->Y);
  }
  float get_Z(int row) {
    return ((row_ptr+row)->Z);
  }
  float get_M2_hit(int row) {
    return ((row_ptr+row)->M2_hit);
  }
  float get_M3_hit(int row) {
    return ((row_ptr+row)->M3_hit);
  }
  float get_M4_hit(int row) {
    return ((row_ptr+row)->M4_hit);
  }
  int get_InnStr(int row) {
    return ((row_ptr+row)->InnStr);
  }
  int get_OutStr(int row) {
    return ((row_ptr+row)->OutStr);
  }
  float get_Chi2EC(int row) {
    return ((row_ptr+row)->Chi2EC);
  }
  int get_Status(int row) {
    return ((row_ptr+row)->Status);
  }
};

struct ECPC_row {
  int ID;
  float TDC;
  float ADC;
};

class ECPC {
private:
  int nrows;
  struct ECPC_row *row_ptr;
public:
  ECPC(void) {
    return;
  }
  ECPC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  float get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
  float get_ADC(int row) {
    return ((row_ptr+row)->ADC);
  }
};

struct ECP_row {
  float N1x;
  float N1y;
  float N1z;
  float R1n;
  float PlW;
  float PlI;
  float PlO;
};

class ECP {
private:
  int nrows;
  struct ECP_row *row_ptr;
public:
  ECP(void) {
    return;
  }
  ECP(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_N1x(int row) {
    return ((row_ptr+row)->N1x);
  }
  float get_N1y(int row) {
    return ((row_ptr+row)->N1y);
  }
  float get_N1z(int row) {
    return ((row_ptr+row)->N1z);
  }
  float get_R1n(int row) {
    return ((row_ptr+row)->R1n);
  }
  float get_PlW(int row) {
    return ((row_ptr+row)->PlW);
  }
  float get_PlI(int row) {
    return ((row_ptr+row)->PlI);
  }
  float get_PlO(int row) {
    return ((row_ptr+row)->PlO);
  }
};

struct ECPE_row {
  int ID;
  int mean;
  float sigma;
};

class ECPE {
private:
  int nrows;
  struct ECPE_row *row_ptr;
public:
  ECPE(void) {
    return;
  }
  ECPE(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_mean(int row) {
    return ((row_ptr+row)->mean);
  }
  float get_sigma(int row) {
    return ((row_ptr+row)->sigma);
  }
};

struct ECPI_row {
  int ID;
  int Layer;
  int HITID;
  float iloc;
  float jloc;
  float diloc;
  float djloc;
  float R;
  float E;
};

class ECPI {
private:
  int nrows;
  struct ECPI_row *row_ptr;
public:
  ECPI(void) {
    return;
  }
  ECPI(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_Layer(int row) {
    return ((row_ptr+row)->Layer);
  }
  int get_HITID(int row) {
    return ((row_ptr+row)->HITID);
  }
  float get_iloc(int row) {
    return ((row_ptr+row)->iloc);
  }
  float get_jloc(int row) {
    return ((row_ptr+row)->jloc);
  }
  float get_diloc(int row) {
    return ((row_ptr+row)->diloc);
  }
  float get_djloc(int row) {
    return ((row_ptr+row)->djloc);
  }
  float get_R(int row) {
    return ((row_ptr+row)->R);
  }
  float get_E(int row) {
    return ((row_ptr+row)->E);
  }
};

struct ECPO_row {
  int UID1;
  int UID2;
  int VID1;
  int VID2;
  int WID1;
  int WID2;
  int SLH;
};

class ECPO {
private:
  int nrows;
  struct ECPO_row *row_ptr;
public:
  ECPO(void) {
    return;
  }
  ECPO(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_UID1(int row) {
    return ((row_ptr+row)->UID1);
  }
  int get_UID2(int row) {
    return ((row_ptr+row)->UID2);
  }
  int get_VID1(int row) {
    return ((row_ptr+row)->VID1);
  }
  int get_VID2(int row) {
    return ((row_ptr+row)->VID2);
  }
  int get_WID1(int row) {
    return ((row_ptr+row)->WID1);
  }
  int get_WID2(int row) {
    return ((row_ptr+row)->WID2);
  }
  int get_SLH(int row) {
    return ((row_ptr+row)->SLH);
  }
};

struct ECRB_row {
  float E_in;
  float E_out;
  float dE_in;
  float dE_out;
  float t_in;
  float t_out;
  float dt_in;
  float dt_out;
  float i_in;
  float j_in;
  float i_out;
  float j_out;
  float di_in;
  float dj_in;
  float di_out;
  float dj_out;
  float x_in;
  float y_in;
  float z_in;
  float x_out;
  float y_out;
  float z_out;
  float dx_in;
  float dy_in;
  float dz_in;
  float dx_out;
  float dy_out;
  float dz_out;
  float u2_in;
  float v2_in;
  float w2_in;
  float u2_out;
  float v2_out;
  float w2_out;
  float u3_in;
  float v3_in;
  float w3_in;
  float u3_out;
  float v3_out;
  float w3_out;
  float i2;
  float j2;
  float i3;
  float j3;
  float spare1;
  float spare2;
  float spare3;
  float spare4;
  int istat;
};

class ECRB {
private:
  int nrows;
  struct ECRB_row *row_ptr;
public:
  ECRB(void) {
    return;
  }
  ECRB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_E_in(int row) {
    return ((row_ptr+row)->E_in);
  }
  float get_E_out(int row) {
    return ((row_ptr+row)->E_out);
  }
  float get_dE_in(int row) {
    return ((row_ptr+row)->dE_in);
  }
  float get_dE_out(int row) {
    return ((row_ptr+row)->dE_out);
  }
  float get_t_in(int row) {
    return ((row_ptr+row)->t_in);
  }
  float get_t_out(int row) {
    return ((row_ptr+row)->t_out);
  }
  float get_dt_in(int row) {
    return ((row_ptr+row)->dt_in);
  }
  float get_dt_out(int row) {
    return ((row_ptr+row)->dt_out);
  }
  float get_i_in(int row) {
    return ((row_ptr+row)->i_in);
  }
  float get_j_in(int row) {
    return ((row_ptr+row)->j_in);
  }
  float get_i_out(int row) {
    return ((row_ptr+row)->i_out);
  }
  float get_j_out(int row) {
    return ((row_ptr+row)->j_out);
  }
  float get_di_in(int row) {
    return ((row_ptr+row)->di_in);
  }
  float get_dj_in(int row) {
    return ((row_ptr+row)->dj_in);
  }
  float get_di_out(int row) {
    return ((row_ptr+row)->di_out);
  }
  float get_dj_out(int row) {
    return ((row_ptr+row)->dj_out);
  }
  float get_x_in(int row) {
    return ((row_ptr+row)->x_in);
  }
  float get_y_in(int row) {
    return ((row_ptr+row)->y_in);
  }
  float get_z_in(int row) {
    return ((row_ptr+row)->z_in);
  }
  float get_x_out(int row) {
    return ((row_ptr+row)->x_out);
  }
  float get_y_out(int row) {
    return ((row_ptr+row)->y_out);
  }
  float get_z_out(int row) {
    return ((row_ptr+row)->z_out);
  }
  float get_dx_in(int row) {
    return ((row_ptr+row)->dx_in);
  }
  float get_dy_in(int row) {
    return ((row_ptr+row)->dy_in);
  }
  float get_dz_in(int row) {
    return ((row_ptr+row)->dz_in);
  }
  float get_dx_out(int row) {
    return ((row_ptr+row)->dx_out);
  }
  float get_dy_out(int row) {
    return ((row_ptr+row)->dy_out);
  }
  float get_dz_out(int row) {
    return ((row_ptr+row)->dz_out);
  }
  float get_u2_in(int row) {
    return ((row_ptr+row)->u2_in);
  }
  float get_v2_in(int row) {
    return ((row_ptr+row)->v2_in);
  }
  float get_w2_in(int row) {
    return ((row_ptr+row)->w2_in);
  }
  float get_u2_out(int row) {
    return ((row_ptr+row)->u2_out);
  }
  float get_v2_out(int row) {
    return ((row_ptr+row)->v2_out);
  }
  float get_w2_out(int row) {
    return ((row_ptr+row)->w2_out);
  }
  float get_u3_in(int row) {
    return ((row_ptr+row)->u3_in);
  }
  float get_v3_in(int row) {
    return ((row_ptr+row)->v3_in);
  }
  float get_w3_in(int row) {
    return ((row_ptr+row)->w3_in);
  }
  float get_u3_out(int row) {
    return ((row_ptr+row)->u3_out);
  }
  float get_v3_out(int row) {
    return ((row_ptr+row)->v3_out);
  }
  float get_w3_out(int row) {
    return ((row_ptr+row)->w3_out);
  }
  float get_i2(int row) {
    return ((row_ptr+row)->i2);
  }
  float get_j2(int row) {
    return ((row_ptr+row)->j2);
  }
  float get_i3(int row) {
    return ((row_ptr+row)->i3);
  }
  float get_j3(int row) {
    return ((row_ptr+row)->j3);
  }
  float get_spare1(int row) {
    return ((row_ptr+row)->spare1);
  }
  float get_spare2(int row) {
    return ((row_ptr+row)->spare2);
  }
  float get_spare3(int row) {
    return ((row_ptr+row)->spare3);
  }
  float get_spare4(int row) {
    return ((row_ptr+row)->spare4);
  }
  int get_istat(int row) {
    return ((row_ptr+row)->istat);
  }
};

struct ECS_row {
  int ECS1;
  int ECS2;
  int ECS3;
  int ECS4;
  int ECS5;
  int ECS6;
  int ECS7;
  int ECS8;
  int ECS9;
  int ECS10;
  int ECS11;
  int ECS12;
  int ECS13;
  int ECS14;
  int ECS15;
  int ECS16;
  int ECS17;
  int ECS18;
  int ECS19;
  int ECS20;
  int ECS21;
  int ECS22;
  int ECS23;
  int ECS24;
  int ECS25;
  int ECS26;
  int ECS27;
  int ECS28;
  int ECS29;
  int ECS30;
  int ECS31;
  int ECS32;
  int ECS33;
  int ECS34;
  int ECS35;
  int ECS36;
  int ECS37;
  int ECS38;
  int ECS39;
  int ECS40;
  int ECS41;
  int ECS42;
  int ECS43;
  int ECS44;
  int ECS45;
  int ECS46;
  int ECS47;
  int ECS48;
  int ECS49;
  int ECS50;
  int ECS51;
  int ECS52;
  int ECS53;
  int ECS54;
  int ECS55;
  int ECS56;
  int ECS57;
  int ECS58;
  int ECS59;
  int ECS60;
  int ECS61;
  int ECS62;
  int ECS63;
  int ECS64;
  int ECS65;
  int ECS66;
  int ECS67;
  int ECS68;
  int ECS69;
  int ECS70;
  int ECS71;
  int ECS72;
  int ECS73;
  int ECS74;
  int ECS75;
  int ECS76;
  int ECS77;
  int ECS78;
  int ECS79;
  int ECS80;
  int ECS81;
  int ECS82;
  int ECS83;
  int ECS84;
  int ECS85;
  int ECS86;
  int ECS87;
  int ECS88;
  int ECS89;
  int ECS90;
  int ECS91;
  int ECS92;
  int ECS93;
  int ECS94;
  int ECS95;
  int ECS96;
};

class ECS {
private:
  int nrows;
  struct ECS_row *row_ptr;
public:
  ECS(void) {
    return;
  }
  ECS(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ECS1(int row) {
    return ((row_ptr+row)->ECS1);
  }
  int get_ECS2(int row) {
    return ((row_ptr+row)->ECS2);
  }
  int get_ECS3(int row) {
    return ((row_ptr+row)->ECS3);
  }
  int get_ECS4(int row) {
    return ((row_ptr+row)->ECS4);
  }
  int get_ECS5(int row) {
    return ((row_ptr+row)->ECS5);
  }
  int get_ECS6(int row) {
    return ((row_ptr+row)->ECS6);
  }
  int get_ECS7(int row) {
    return ((row_ptr+row)->ECS7);
  }
  int get_ECS8(int row) {
    return ((row_ptr+row)->ECS8);
  }
  int get_ECS9(int row) {
    return ((row_ptr+row)->ECS9);
  }
  int get_ECS10(int row) {
    return ((row_ptr+row)->ECS10);
  }
  int get_ECS11(int row) {
    return ((row_ptr+row)->ECS11);
  }
  int get_ECS12(int row) {
    return ((row_ptr+row)->ECS12);
  }
  int get_ECS13(int row) {
    return ((row_ptr+row)->ECS13);
  }
  int get_ECS14(int row) {
    return ((row_ptr+row)->ECS14);
  }
  int get_ECS15(int row) {
    return ((row_ptr+row)->ECS15);
  }
  int get_ECS16(int row) {
    return ((row_ptr+row)->ECS16);
  }
  int get_ECS17(int row) {
    return ((row_ptr+row)->ECS17);
  }
  int get_ECS18(int row) {
    return ((row_ptr+row)->ECS18);
  }
  int get_ECS19(int row) {
    return ((row_ptr+row)->ECS19);
  }
  int get_ECS20(int row) {
    return ((row_ptr+row)->ECS20);
  }
  int get_ECS21(int row) {
    return ((row_ptr+row)->ECS21);
  }
  int get_ECS22(int row) {
    return ((row_ptr+row)->ECS22);
  }
  int get_ECS23(int row) {
    return ((row_ptr+row)->ECS23);
  }
  int get_ECS24(int row) {
    return ((row_ptr+row)->ECS24);
  }
  int get_ECS25(int row) {
    return ((row_ptr+row)->ECS25);
  }
  int get_ECS26(int row) {
    return ((row_ptr+row)->ECS26);
  }
  int get_ECS27(int row) {
    return ((row_ptr+row)->ECS27);
  }
  int get_ECS28(int row) {
    return ((row_ptr+row)->ECS28);
  }
  int get_ECS29(int row) {
    return ((row_ptr+row)->ECS29);
  }
  int get_ECS30(int row) {
    return ((row_ptr+row)->ECS30);
  }
  int get_ECS31(int row) {
    return ((row_ptr+row)->ECS31);
  }
  int get_ECS32(int row) {
    return ((row_ptr+row)->ECS32);
  }
  int get_ECS33(int row) {
    return ((row_ptr+row)->ECS33);
  }
  int get_ECS34(int row) {
    return ((row_ptr+row)->ECS34);
  }
  int get_ECS35(int row) {
    return ((row_ptr+row)->ECS35);
  }
  int get_ECS36(int row) {
    return ((row_ptr+row)->ECS36);
  }
  int get_ECS37(int row) {
    return ((row_ptr+row)->ECS37);
  }
  int get_ECS38(int row) {
    return ((row_ptr+row)->ECS38);
  }
  int get_ECS39(int row) {
    return ((row_ptr+row)->ECS39);
  }
  int get_ECS40(int row) {
    return ((row_ptr+row)->ECS40);
  }
  int get_ECS41(int row) {
    return ((row_ptr+row)->ECS41);
  }
  int get_ECS42(int row) {
    return ((row_ptr+row)->ECS42);
  }
  int get_ECS43(int row) {
    return ((row_ptr+row)->ECS43);
  }
  int get_ECS44(int row) {
    return ((row_ptr+row)->ECS44);
  }
  int get_ECS45(int row) {
    return ((row_ptr+row)->ECS45);
  }
  int get_ECS46(int row) {
    return ((row_ptr+row)->ECS46);
  }
  int get_ECS47(int row) {
    return ((row_ptr+row)->ECS47);
  }
  int get_ECS48(int row) {
    return ((row_ptr+row)->ECS48);
  }
  int get_ECS49(int row) {
    return ((row_ptr+row)->ECS49);
  }
  int get_ECS50(int row) {
    return ((row_ptr+row)->ECS50);
  }
  int get_ECS51(int row) {
    return ((row_ptr+row)->ECS51);
  }
  int get_ECS52(int row) {
    return ((row_ptr+row)->ECS52);
  }
  int get_ECS53(int row) {
    return ((row_ptr+row)->ECS53);
  }
  int get_ECS54(int row) {
    return ((row_ptr+row)->ECS54);
  }
  int get_ECS55(int row) {
    return ((row_ptr+row)->ECS55);
  }
  int get_ECS56(int row) {
    return ((row_ptr+row)->ECS56);
  }
  int get_ECS57(int row) {
    return ((row_ptr+row)->ECS57);
  }
  int get_ECS58(int row) {
    return ((row_ptr+row)->ECS58);
  }
  int get_ECS59(int row) {
    return ((row_ptr+row)->ECS59);
  }
  int get_ECS60(int row) {
    return ((row_ptr+row)->ECS60);
  }
  int get_ECS61(int row) {
    return ((row_ptr+row)->ECS61);
  }
  int get_ECS62(int row) {
    return ((row_ptr+row)->ECS62);
  }
  int get_ECS63(int row) {
    return ((row_ptr+row)->ECS63);
  }
  int get_ECS64(int row) {
    return ((row_ptr+row)->ECS64);
  }
  int get_ECS65(int row) {
    return ((row_ptr+row)->ECS65);
  }
  int get_ECS66(int row) {
    return ((row_ptr+row)->ECS66);
  }
  int get_ECS67(int row) {
    return ((row_ptr+row)->ECS67);
  }
  int get_ECS68(int row) {
    return ((row_ptr+row)->ECS68);
  }
  int get_ECS69(int row) {
    return ((row_ptr+row)->ECS69);
  }
  int get_ECS70(int row) {
    return ((row_ptr+row)->ECS70);
  }
  int get_ECS71(int row) {
    return ((row_ptr+row)->ECS71);
  }
  int get_ECS72(int row) {
    return ((row_ptr+row)->ECS72);
  }
  int get_ECS73(int row) {
    return ((row_ptr+row)->ECS73);
  }
  int get_ECS74(int row) {
    return ((row_ptr+row)->ECS74);
  }
  int get_ECS75(int row) {
    return ((row_ptr+row)->ECS75);
  }
  int get_ECS76(int row) {
    return ((row_ptr+row)->ECS76);
  }
  int get_ECS77(int row) {
    return ((row_ptr+row)->ECS77);
  }
  int get_ECS78(int row) {
    return ((row_ptr+row)->ECS78);
  }
  int get_ECS79(int row) {
    return ((row_ptr+row)->ECS79);
  }
  int get_ECS80(int row) {
    return ((row_ptr+row)->ECS80);
  }
  int get_ECS81(int row) {
    return ((row_ptr+row)->ECS81);
  }
  int get_ECS82(int row) {
    return ((row_ptr+row)->ECS82);
  }
  int get_ECS83(int row) {
    return ((row_ptr+row)->ECS83);
  }
  int get_ECS84(int row) {
    return ((row_ptr+row)->ECS84);
  }
  int get_ECS85(int row) {
    return ((row_ptr+row)->ECS85);
  }
  int get_ECS86(int row) {
    return ((row_ptr+row)->ECS86);
  }
  int get_ECS87(int row) {
    return ((row_ptr+row)->ECS87);
  }
  int get_ECS88(int row) {
    return ((row_ptr+row)->ECS88);
  }
  int get_ECS89(int row) {
    return ((row_ptr+row)->ECS89);
  }
  int get_ECS90(int row) {
    return ((row_ptr+row)->ECS90);
  }
  int get_ECS91(int row) {
    return ((row_ptr+row)->ECS91);
  }
  int get_ECS92(int row) {
    return ((row_ptr+row)->ECS92);
  }
  int get_ECS93(int row) {
    return ((row_ptr+row)->ECS93);
  }
  int get_ECS94(int row) {
    return ((row_ptr+row)->ECS94);
  }
  int get_ECS95(int row) {
    return ((row_ptr+row)->ECS95);
  }
  int get_ECS96(int row) {
    return ((row_ptr+row)->ECS96);
  }
};

struct ECT_row {
  short ID;
  short TDC;
};

class ECT {
private:
  int nrows;
  struct ECT_row *row_ptr;
public:
  ECT(void) {
    return;
  }
  ECT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct EID0_row {
  int jeid0sec;
  int jeid0cc;
  int jeid0ec;
  int jeid0sc;
};

class EID0 {
private:
  int nrows;
  struct EID0_row *row_ptr;
public:
  EID0(void) {
    return;
  }
  EID0(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_jeid0sec(int row) {
    return ((row_ptr+row)->jeid0sec);
  }
  int get_jeid0cc(int row) {
    return ((row_ptr+row)->jeid0cc);
  }
  int get_jeid0ec(int row) {
    return ((row_ptr+row)->jeid0ec);
  }
  int get_jeid0sc(int row) {
    return ((row_ptr+row)->jeid0sc);
  }
};

struct EPIC_row {
  float value;
  char char1[4];
  char char2[4];
  char char3[4];
  char char4[4];
  char char5[4];
  char char6[4];
  char char7[4];
  char char8[4];
};

class EPIC {
private:
  int nrows;
  struct EPIC_row *row_ptr;
public:
  EPIC(void) {
    return;
  }
  EPIC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_value(int row) {
    return ((row_ptr+row)->value);
  }
  char *get_char1(int row) {
    return ((row_ptr+row)->char1);
  }
  char *get_char2(int row) {
    return ((row_ptr+row)->char2);
  }
  char *get_char3(int row) {
    return ((row_ptr+row)->char3);
  }
  char *get_char4(int row) {
    return ((row_ptr+row)->char4);
  }
  char *get_char5(int row) {
    return ((row_ptr+row)->char5);
  }
  char *get_char6(int row) {
    return ((row_ptr+row)->char6);
  }
  char *get_char7(int row) {
    return ((row_ptr+row)->char7);
  }
  char *get_char8(int row) {
    return ((row_ptr+row)->char8);
  }
};

struct EVNT_row {
  int ID;
  float Pmom;
  float Mass;
  int Charge;
  float Betta;
  float Cx;
  float cy;
  float cz;
  float X;
  float Y;
  float Z;
  int DCstat;
  int CCstat;
  int SCstat;
  int ECstat;
  int LCstat;
  int STstat;
  int Status;
};

class EVNT {
private:
  int nrows;
  struct EVNT_row *row_ptr;
public:
  EVNT(void) {
    return;
  }
  EVNT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  float get_Pmom(int row) {
    return ((row_ptr+row)->Pmom);
  }
  float get_Mass(int row) {
    return ((row_ptr+row)->Mass);
  }
  int get_Charge(int row) {
    return ((row_ptr+row)->Charge);
  }
  float get_Betta(int row) {
    return ((row_ptr+row)->Betta);
  }
  float get_Cx(int row) {
    return ((row_ptr+row)->Cx);
  }
  float get_cy(int row) {
    return ((row_ptr+row)->cy);
  }
  float get_cz(int row) {
    return ((row_ptr+row)->cz);
  }
  float get_X(int row) {
    return ((row_ptr+row)->X);
  }
  float get_Y(int row) {
    return ((row_ptr+row)->Y);
  }
  float get_Z(int row) {
    return ((row_ptr+row)->Z);
  }
  int get_DCstat(int row) {
    return ((row_ptr+row)->DCstat);
  }
  int get_CCstat(int row) {
    return ((row_ptr+row)->CCstat);
  }
  int get_SCstat(int row) {
    return ((row_ptr+row)->SCstat);
  }
  int get_ECstat(int row) {
    return ((row_ptr+row)->ECstat);
  }
  int get_LCstat(int row) {
    return ((row_ptr+row)->LCstat);
  }
  int get_STstat(int row) {
    return ((row_ptr+row)->STstat);
  }
  int get_Status(int row) {
    return ((row_ptr+row)->Status);
  }
};

struct FBPM_row {
  short ID;
  short TDC;
  short ADC;
};

class FBPM {
private:
  int nrows;
  struct FBPM_row *row_ptr;
public:
  FBPM(void) {
    return;
  }
  FBPM(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
  short get_ADC(int row) {
    return ((row_ptr+row)->ADC);
  }
};

struct G1SL_row {
  int G1T1;
  int G1T2;
  int G1T3;
  int G1T4;
  int G1T5;
  int G1T6;
  int G1T7;
  int G1T8;
  int G1T9;
  int G1T10;
  int G1T11;
  int G1T12;
  int G1T13;
  int G1T14;
  int G1T15;
  int G1T16;
  int G1T17;
  int G1T18;
  int G1T19;
  int G1T20;
  int G1T21;
  int G1T22;
  int G1T23;
  int G1T24;
  int G1T25;
  int G1T26;
  int G1T27;
  int G1T28;
  int G1T29;
  int G1T30;
  int G1T31;
  int G1T32;
  int G1T33;
  int G1T34;
  int G1T35;
  int G1T36;
  int G1T37;
  int G1T38;
  int G1T39;
  int G1T40;
  int G1T41;
  int G1T42;
  int G1T43;
  int G1T44;
  int G1T45;
  int G1T46;
  int G1T47;
  int G1T48;
  int G1T49;
  int G1T50;
  int G1T51;
  int G1T52;
  int G1T53;
  int G1T54;
  int G1T55;
  int G1T56;
  int G1T57;
  int G1T58;
  int G1T59;
  int G1T60;
  int G1T61;
  int G1T62;
  int G1T63;
  int G1T64;
};

class G1SL {
private:
  int nrows;
  struct G1SL_row *row_ptr;
public:
  G1SL(void) {
    return;
  }
  G1SL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_G1T1(int row) {
    return ((row_ptr+row)->G1T1);
  }
  int get_G1T2(int row) {
    return ((row_ptr+row)->G1T2);
  }
  int get_G1T3(int row) {
    return ((row_ptr+row)->G1T3);
  }
  int get_G1T4(int row) {
    return ((row_ptr+row)->G1T4);
  }
  int get_G1T5(int row) {
    return ((row_ptr+row)->G1T5);
  }
  int get_G1T6(int row) {
    return ((row_ptr+row)->G1T6);
  }
  int get_G1T7(int row) {
    return ((row_ptr+row)->G1T7);
  }
  int get_G1T8(int row) {
    return ((row_ptr+row)->G1T8);
  }
  int get_G1T9(int row) {
    return ((row_ptr+row)->G1T9);
  }
  int get_G1T10(int row) {
    return ((row_ptr+row)->G1T10);
  }
  int get_G1T11(int row) {
    return ((row_ptr+row)->G1T11);
  }
  int get_G1T12(int row) {
    return ((row_ptr+row)->G1T12);
  }
  int get_G1T13(int row) {
    return ((row_ptr+row)->G1T13);
  }
  int get_G1T14(int row) {
    return ((row_ptr+row)->G1T14);
  }
  int get_G1T15(int row) {
    return ((row_ptr+row)->G1T15);
  }
  int get_G1T16(int row) {
    return ((row_ptr+row)->G1T16);
  }
  int get_G1T17(int row) {
    return ((row_ptr+row)->G1T17);
  }
  int get_G1T18(int row) {
    return ((row_ptr+row)->G1T18);
  }
  int get_G1T19(int row) {
    return ((row_ptr+row)->G1T19);
  }
  int get_G1T20(int row) {
    return ((row_ptr+row)->G1T20);
  }
  int get_G1T21(int row) {
    return ((row_ptr+row)->G1T21);
  }
  int get_G1T22(int row) {
    return ((row_ptr+row)->G1T22);
  }
  int get_G1T23(int row) {
    return ((row_ptr+row)->G1T23);
  }
  int get_G1T24(int row) {
    return ((row_ptr+row)->G1T24);
  }
  int get_G1T25(int row) {
    return ((row_ptr+row)->G1T25);
  }
  int get_G1T26(int row) {
    return ((row_ptr+row)->G1T26);
  }
  int get_G1T27(int row) {
    return ((row_ptr+row)->G1T27);
  }
  int get_G1T28(int row) {
    return ((row_ptr+row)->G1T28);
  }
  int get_G1T29(int row) {
    return ((row_ptr+row)->G1T29);
  }
  int get_G1T30(int row) {
    return ((row_ptr+row)->G1T30);
  }
  int get_G1T31(int row) {
    return ((row_ptr+row)->G1T31);
  }
  int get_G1T32(int row) {
    return ((row_ptr+row)->G1T32);
  }
  int get_G1T33(int row) {
    return ((row_ptr+row)->G1T33);
  }
  int get_G1T34(int row) {
    return ((row_ptr+row)->G1T34);
  }
  int get_G1T35(int row) {
    return ((row_ptr+row)->G1T35);
  }
  int get_G1T36(int row) {
    return ((row_ptr+row)->G1T36);
  }
  int get_G1T37(int row) {
    return ((row_ptr+row)->G1T37);
  }
  int get_G1T38(int row) {
    return ((row_ptr+row)->G1T38);
  }
  int get_G1T39(int row) {
    return ((row_ptr+row)->G1T39);
  }
  int get_G1T40(int row) {
    return ((row_ptr+row)->G1T40);
  }
  int get_G1T41(int row) {
    return ((row_ptr+row)->G1T41);
  }
  int get_G1T42(int row) {
    return ((row_ptr+row)->G1T42);
  }
  int get_G1T43(int row) {
    return ((row_ptr+row)->G1T43);
  }
  int get_G1T44(int row) {
    return ((row_ptr+row)->G1T44);
  }
  int get_G1T45(int row) {
    return ((row_ptr+row)->G1T45);
  }
  int get_G1T46(int row) {
    return ((row_ptr+row)->G1T46);
  }
  int get_G1T47(int row) {
    return ((row_ptr+row)->G1T47);
  }
  int get_G1T48(int row) {
    return ((row_ptr+row)->G1T48);
  }
  int get_G1T49(int row) {
    return ((row_ptr+row)->G1T49);
  }
  int get_G1T50(int row) {
    return ((row_ptr+row)->G1T50);
  }
  int get_G1T51(int row) {
    return ((row_ptr+row)->G1T51);
  }
  int get_G1T52(int row) {
    return ((row_ptr+row)->G1T52);
  }
  int get_G1T53(int row) {
    return ((row_ptr+row)->G1T53);
  }
  int get_G1T54(int row) {
    return ((row_ptr+row)->G1T54);
  }
  int get_G1T55(int row) {
    return ((row_ptr+row)->G1T55);
  }
  int get_G1T56(int row) {
    return ((row_ptr+row)->G1T56);
  }
  int get_G1T57(int row) {
    return ((row_ptr+row)->G1T57);
  }
  int get_G1T58(int row) {
    return ((row_ptr+row)->G1T58);
  }
  int get_G1T59(int row) {
    return ((row_ptr+row)->G1T59);
  }
  int get_G1T60(int row) {
    return ((row_ptr+row)->G1T60);
  }
  int get_G1T61(int row) {
    return ((row_ptr+row)->G1T61);
  }
  int get_G1T62(int row) {
    return ((row_ptr+row)->G1T62);
  }
  int get_G1T63(int row) {
    return ((row_ptr+row)->G1T63);
  }
  int get_G1T64(int row) {
    return ((row_ptr+row)->G1T64);
  }
};

struct G2SL_row {
  int G2T1;
  int G2T2;
  int G2T3;
  int G2T4;
  int G2T5;
  int G2T6;
  int G2T7;
  int G2T8;
  int G2T9;
  int G2T10;
  int G2T11;
  int G2T12;
  int G2T13;
  int G2T14;
  int G2T15;
  int G2T16;
  int G2T17;
  int G2T18;
  int G2T19;
  int G2T20;
  int G2T21;
  int G2T22;
  int G2T23;
  int G2T24;
  int G2T25;
  int G2T26;
  int G2T27;
  int G2T28;
  int G2T29;
  int G2T30;
  int G2T31;
  int G2T32;
  int G2T33;
  int G2T34;
  int G2T35;
  int G2T36;
  int G2T37;
  int G2T38;
  int G2T39;
  int G2T40;
  int G2T41;
  int G2T42;
  int G2T43;
  int G2T44;
  int G2T45;
  int G2T46;
  int G2T47;
  int G2T48;
  int G2T49;
  int G2T50;
  int G2T51;
  int G2T52;
  int G2T53;
  int G2T54;
  int G2T55;
  int G2T56;
  int G2T57;
  int G2T58;
  int G2T59;
  int G2T60;
  int G2T61;
  int G2T62;
  int G2T63;
  int G2T64;
};

class G2SL {
private:
  int nrows;
  struct G2SL_row *row_ptr;
public:
  G2SL(void) {
    return;
  }
  G2SL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_G2T1(int row) {
    return ((row_ptr+row)->G2T1);
  }
  int get_G2T2(int row) {
    return ((row_ptr+row)->G2T2);
  }
  int get_G2T3(int row) {
    return ((row_ptr+row)->G2T3);
  }
  int get_G2T4(int row) {
    return ((row_ptr+row)->G2T4);
  }
  int get_G2T5(int row) {
    return ((row_ptr+row)->G2T5);
  }
  int get_G2T6(int row) {
    return ((row_ptr+row)->G2T6);
  }
  int get_G2T7(int row) {
    return ((row_ptr+row)->G2T7);
  }
  int get_G2T8(int row) {
    return ((row_ptr+row)->G2T8);
  }
  int get_G2T9(int row) {
    return ((row_ptr+row)->G2T9);
  }
  int get_G2T10(int row) {
    return ((row_ptr+row)->G2T10);
  }
  int get_G2T11(int row) {
    return ((row_ptr+row)->G2T11);
  }
  int get_G2T12(int row) {
    return ((row_ptr+row)->G2T12);
  }
  int get_G2T13(int row) {
    return ((row_ptr+row)->G2T13);
  }
  int get_G2T14(int row) {
    return ((row_ptr+row)->G2T14);
  }
  int get_G2T15(int row) {
    return ((row_ptr+row)->G2T15);
  }
  int get_G2T16(int row) {
    return ((row_ptr+row)->G2T16);
  }
  int get_G2T17(int row) {
    return ((row_ptr+row)->G2T17);
  }
  int get_G2T18(int row) {
    return ((row_ptr+row)->G2T18);
  }
  int get_G2T19(int row) {
    return ((row_ptr+row)->G2T19);
  }
  int get_G2T20(int row) {
    return ((row_ptr+row)->G2T20);
  }
  int get_G2T21(int row) {
    return ((row_ptr+row)->G2T21);
  }
  int get_G2T22(int row) {
    return ((row_ptr+row)->G2T22);
  }
  int get_G2T23(int row) {
    return ((row_ptr+row)->G2T23);
  }
  int get_G2T24(int row) {
    return ((row_ptr+row)->G2T24);
  }
  int get_G2T25(int row) {
    return ((row_ptr+row)->G2T25);
  }
  int get_G2T26(int row) {
    return ((row_ptr+row)->G2T26);
  }
  int get_G2T27(int row) {
    return ((row_ptr+row)->G2T27);
  }
  int get_G2T28(int row) {
    return ((row_ptr+row)->G2T28);
  }
  int get_G2T29(int row) {
    return ((row_ptr+row)->G2T29);
  }
  int get_G2T30(int row) {
    return ((row_ptr+row)->G2T30);
  }
  int get_G2T31(int row) {
    return ((row_ptr+row)->G2T31);
  }
  int get_G2T32(int row) {
    return ((row_ptr+row)->G2T32);
  }
  int get_G2T33(int row) {
    return ((row_ptr+row)->G2T33);
  }
  int get_G2T34(int row) {
    return ((row_ptr+row)->G2T34);
  }
  int get_G2T35(int row) {
    return ((row_ptr+row)->G2T35);
  }
  int get_G2T36(int row) {
    return ((row_ptr+row)->G2T36);
  }
  int get_G2T37(int row) {
    return ((row_ptr+row)->G2T37);
  }
  int get_G2T38(int row) {
    return ((row_ptr+row)->G2T38);
  }
  int get_G2T39(int row) {
    return ((row_ptr+row)->G2T39);
  }
  int get_G2T40(int row) {
    return ((row_ptr+row)->G2T40);
  }
  int get_G2T41(int row) {
    return ((row_ptr+row)->G2T41);
  }
  int get_G2T42(int row) {
    return ((row_ptr+row)->G2T42);
  }
  int get_G2T43(int row) {
    return ((row_ptr+row)->G2T43);
  }
  int get_G2T44(int row) {
    return ((row_ptr+row)->G2T44);
  }
  int get_G2T45(int row) {
    return ((row_ptr+row)->G2T45);
  }
  int get_G2T46(int row) {
    return ((row_ptr+row)->G2T46);
  }
  int get_G2T47(int row) {
    return ((row_ptr+row)->G2T47);
  }
  int get_G2T48(int row) {
    return ((row_ptr+row)->G2T48);
  }
  int get_G2T49(int row) {
    return ((row_ptr+row)->G2T49);
  }
  int get_G2T50(int row) {
    return ((row_ptr+row)->G2T50);
  }
  int get_G2T51(int row) {
    return ((row_ptr+row)->G2T51);
  }
  int get_G2T52(int row) {
    return ((row_ptr+row)->G2T52);
  }
  int get_G2T53(int row) {
    return ((row_ptr+row)->G2T53);
  }
  int get_G2T54(int row) {
    return ((row_ptr+row)->G2T54);
  }
  int get_G2T55(int row) {
    return ((row_ptr+row)->G2T55);
  }
  int get_G2T56(int row) {
    return ((row_ptr+row)->G2T56);
  }
  int get_G2T57(int row) {
    return ((row_ptr+row)->G2T57);
  }
  int get_G2T58(int row) {
    return ((row_ptr+row)->G2T58);
  }
  int get_G2T59(int row) {
    return ((row_ptr+row)->G2T59);
  }
  int get_G2T60(int row) {
    return ((row_ptr+row)->G2T60);
  }
  int get_G2T61(int row) {
    return ((row_ptr+row)->G2T61);
  }
  int get_G2T62(int row) {
    return ((row_ptr+row)->G2T62);
  }
  int get_G2T63(int row) {
    return ((row_ptr+row)->G2T63);
  }
  int get_G2T64(int row) {
    return ((row_ptr+row)->G2T64);
  }
};

struct G3SL_row {
  int G3T1;
  int G3T2;
  int G3T3;
  int G3T4;
  int G3T5;
  int G3T6;
  int G3T7;
  int G3T8;
  int G3T9;
  int G3T10;
  int G3T11;
  int G3T12;
  int G3T13;
  int G3T14;
  int G3T15;
  int G3T16;
  int G3T17;
  int G3T18;
  int G3T19;
  int G3T20;
  int G3T21;
  int G3T22;
  int G3T23;
  int G3T24;
  int G3T25;
  int G3T26;
  int G3T27;
  int G3T28;
  int G3T29;
  int G3T30;
  int G3T31;
  int G3T32;
  int G3T33;
  int G3T34;
  int G3T35;
  int G3T36;
  int G3T37;
  int G3T38;
  int G3T39;
  int G3T40;
  int G3T41;
  int G3T42;
  int G3T43;
  int G3T44;
  int G3T45;
  int G3T46;
  int G3T47;
  int G3T48;
  int G3T49;
  int G3T50;
  int G3T51;
  int G3T52;
  int G3T53;
  int G3T54;
  int G3T55;
  int G3T56;
  int G3T57;
  int G3T58;
  int G3T59;
  int G3T60;
  int G3T61;
  int G3T62;
  int G3T63;
  int G3T64;
};

class G3SL {
private:
  int nrows;
  struct G3SL_row *row_ptr;
public:
  G3SL(void) {
    return;
  }
  G3SL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_G3T1(int row) {
    return ((row_ptr+row)->G3T1);
  }
  int get_G3T2(int row) {
    return ((row_ptr+row)->G3T2);
  }
  int get_G3T3(int row) {
    return ((row_ptr+row)->G3T3);
  }
  int get_G3T4(int row) {
    return ((row_ptr+row)->G3T4);
  }
  int get_G3T5(int row) {
    return ((row_ptr+row)->G3T5);
  }
  int get_G3T6(int row) {
    return ((row_ptr+row)->G3T6);
  }
  int get_G3T7(int row) {
    return ((row_ptr+row)->G3T7);
  }
  int get_G3T8(int row) {
    return ((row_ptr+row)->G3T8);
  }
  int get_G3T9(int row) {
    return ((row_ptr+row)->G3T9);
  }
  int get_G3T10(int row) {
    return ((row_ptr+row)->G3T10);
  }
  int get_G3T11(int row) {
    return ((row_ptr+row)->G3T11);
  }
  int get_G3T12(int row) {
    return ((row_ptr+row)->G3T12);
  }
  int get_G3T13(int row) {
    return ((row_ptr+row)->G3T13);
  }
  int get_G3T14(int row) {
    return ((row_ptr+row)->G3T14);
  }
  int get_G3T15(int row) {
    return ((row_ptr+row)->G3T15);
  }
  int get_G3T16(int row) {
    return ((row_ptr+row)->G3T16);
  }
  int get_G3T17(int row) {
    return ((row_ptr+row)->G3T17);
  }
  int get_G3T18(int row) {
    return ((row_ptr+row)->G3T18);
  }
  int get_G3T19(int row) {
    return ((row_ptr+row)->G3T19);
  }
  int get_G3T20(int row) {
    return ((row_ptr+row)->G3T20);
  }
  int get_G3T21(int row) {
    return ((row_ptr+row)->G3T21);
  }
  int get_G3T22(int row) {
    return ((row_ptr+row)->G3T22);
  }
  int get_G3T23(int row) {
    return ((row_ptr+row)->G3T23);
  }
  int get_G3T24(int row) {
    return ((row_ptr+row)->G3T24);
  }
  int get_G3T25(int row) {
    return ((row_ptr+row)->G3T25);
  }
  int get_G3T26(int row) {
    return ((row_ptr+row)->G3T26);
  }
  int get_G3T27(int row) {
    return ((row_ptr+row)->G3T27);
  }
  int get_G3T28(int row) {
    return ((row_ptr+row)->G3T28);
  }
  int get_G3T29(int row) {
    return ((row_ptr+row)->G3T29);
  }
  int get_G3T30(int row) {
    return ((row_ptr+row)->G3T30);
  }
  int get_G3T31(int row) {
    return ((row_ptr+row)->G3T31);
  }
  int get_G3T32(int row) {
    return ((row_ptr+row)->G3T32);
  }
  int get_G3T33(int row) {
    return ((row_ptr+row)->G3T33);
  }
  int get_G3T34(int row) {
    return ((row_ptr+row)->G3T34);
  }
  int get_G3T35(int row) {
    return ((row_ptr+row)->G3T35);
  }
  int get_G3T36(int row) {
    return ((row_ptr+row)->G3T36);
  }
  int get_G3T37(int row) {
    return ((row_ptr+row)->G3T37);
  }
  int get_G3T38(int row) {
    return ((row_ptr+row)->G3T38);
  }
  int get_G3T39(int row) {
    return ((row_ptr+row)->G3T39);
  }
  int get_G3T40(int row) {
    return ((row_ptr+row)->G3T40);
  }
  int get_G3T41(int row) {
    return ((row_ptr+row)->G3T41);
  }
  int get_G3T42(int row) {
    return ((row_ptr+row)->G3T42);
  }
  int get_G3T43(int row) {
    return ((row_ptr+row)->G3T43);
  }
  int get_G3T44(int row) {
    return ((row_ptr+row)->G3T44);
  }
  int get_G3T45(int row) {
    return ((row_ptr+row)->G3T45);
  }
  int get_G3T46(int row) {
    return ((row_ptr+row)->G3T46);
  }
  int get_G3T47(int row) {
    return ((row_ptr+row)->G3T47);
  }
  int get_G3T48(int row) {
    return ((row_ptr+row)->G3T48);
  }
  int get_G3T49(int row) {
    return ((row_ptr+row)->G3T49);
  }
  int get_G3T50(int row) {
    return ((row_ptr+row)->G3T50);
  }
  int get_G3T51(int row) {
    return ((row_ptr+row)->G3T51);
  }
  int get_G3T52(int row) {
    return ((row_ptr+row)->G3T52);
  }
  int get_G3T53(int row) {
    return ((row_ptr+row)->G3T53);
  }
  int get_G3T54(int row) {
    return ((row_ptr+row)->G3T54);
  }
  int get_G3T55(int row) {
    return ((row_ptr+row)->G3T55);
  }
  int get_G3T56(int row) {
    return ((row_ptr+row)->G3T56);
  }
  int get_G3T57(int row) {
    return ((row_ptr+row)->G3T57);
  }
  int get_G3T58(int row) {
    return ((row_ptr+row)->G3T58);
  }
  int get_G3T59(int row) {
    return ((row_ptr+row)->G3T59);
  }
  int get_G3T60(int row) {
    return ((row_ptr+row)->G3T60);
  }
  int get_G3T61(int row) {
    return ((row_ptr+row)->G3T61);
  }
  int get_G3T62(int row) {
    return ((row_ptr+row)->G3T62);
  }
  int get_G3T63(int row) {
    return ((row_ptr+row)->G3T63);
  }
  int get_G3T64(int row) {
    return ((row_ptr+row)->G3T64);
  }
};

struct G4SL_row {
  int G4T1;
  int G4T2;
  int G4T3;
  int G4T4;
  int G4T5;
  int G4T6;
  int G4T7;
  int G4T8;
  int G4T9;
  int G4T10;
  int G4T11;
  int G4T12;
  int G4T13;
  int G4T14;
  int G4T15;
  int G4T16;
  int G4T17;
  int G4T18;
  int G4T19;
  int G4T20;
  int G4T21;
  int G4T22;
  int G4T23;
  int G4T24;
  int G4T25;
  int G4T26;
  int G4T27;
  int G4T28;
  int G4T29;
  int G4T30;
  int G4T31;
  int G4T32;
  int G4T33;
  int G4T34;
  int G4T35;
  int G4T36;
  int G4T37;
  int G4T38;
  int G4T39;
  int G4T40;
  int G4T41;
  int G4T42;
  int G4T43;
  int G4T44;
  int G4T45;
  int G4T46;
  int G4T47;
  int G4T48;
  int G4T49;
  int G4T50;
  int G4T51;
  int G4T52;
  int G4T53;
  int G4T54;
  int G4T55;
  int G4T56;
  int G4T57;
  int G4T58;
  int G4T59;
  int G4T60;
  int G4T61;
  int G4T62;
  int G4T63;
  int G4T64;
};

class G4SL {
private:
  int nrows;
  struct G4SL_row *row_ptr;
public:
  G4SL(void) {
    return;
  }
  G4SL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_G4T1(int row) {
    return ((row_ptr+row)->G4T1);
  }
  int get_G4T2(int row) {
    return ((row_ptr+row)->G4T2);
  }
  int get_G4T3(int row) {
    return ((row_ptr+row)->G4T3);
  }
  int get_G4T4(int row) {
    return ((row_ptr+row)->G4T4);
  }
  int get_G4T5(int row) {
    return ((row_ptr+row)->G4T5);
  }
  int get_G4T6(int row) {
    return ((row_ptr+row)->G4T6);
  }
  int get_G4T7(int row) {
    return ((row_ptr+row)->G4T7);
  }
  int get_G4T8(int row) {
    return ((row_ptr+row)->G4T8);
  }
  int get_G4T9(int row) {
    return ((row_ptr+row)->G4T9);
  }
  int get_G4T10(int row) {
    return ((row_ptr+row)->G4T10);
  }
  int get_G4T11(int row) {
    return ((row_ptr+row)->G4T11);
  }
  int get_G4T12(int row) {
    return ((row_ptr+row)->G4T12);
  }
  int get_G4T13(int row) {
    return ((row_ptr+row)->G4T13);
  }
  int get_G4T14(int row) {
    return ((row_ptr+row)->G4T14);
  }
  int get_G4T15(int row) {
    return ((row_ptr+row)->G4T15);
  }
  int get_G4T16(int row) {
    return ((row_ptr+row)->G4T16);
  }
  int get_G4T17(int row) {
    return ((row_ptr+row)->G4T17);
  }
  int get_G4T18(int row) {
    return ((row_ptr+row)->G4T18);
  }
  int get_G4T19(int row) {
    return ((row_ptr+row)->G4T19);
  }
  int get_G4T20(int row) {
    return ((row_ptr+row)->G4T20);
  }
  int get_G4T21(int row) {
    return ((row_ptr+row)->G4T21);
  }
  int get_G4T22(int row) {
    return ((row_ptr+row)->G4T22);
  }
  int get_G4T23(int row) {
    return ((row_ptr+row)->G4T23);
  }
  int get_G4T24(int row) {
    return ((row_ptr+row)->G4T24);
  }
  int get_G4T25(int row) {
    return ((row_ptr+row)->G4T25);
  }
  int get_G4T26(int row) {
    return ((row_ptr+row)->G4T26);
  }
  int get_G4T27(int row) {
    return ((row_ptr+row)->G4T27);
  }
  int get_G4T28(int row) {
    return ((row_ptr+row)->G4T28);
  }
  int get_G4T29(int row) {
    return ((row_ptr+row)->G4T29);
  }
  int get_G4T30(int row) {
    return ((row_ptr+row)->G4T30);
  }
  int get_G4T31(int row) {
    return ((row_ptr+row)->G4T31);
  }
  int get_G4T32(int row) {
    return ((row_ptr+row)->G4T32);
  }
  int get_G4T33(int row) {
    return ((row_ptr+row)->G4T33);
  }
  int get_G4T34(int row) {
    return ((row_ptr+row)->G4T34);
  }
  int get_G4T35(int row) {
    return ((row_ptr+row)->G4T35);
  }
  int get_G4T36(int row) {
    return ((row_ptr+row)->G4T36);
  }
  int get_G4T37(int row) {
    return ((row_ptr+row)->G4T37);
  }
  int get_G4T38(int row) {
    return ((row_ptr+row)->G4T38);
  }
  int get_G4T39(int row) {
    return ((row_ptr+row)->G4T39);
  }
  int get_G4T40(int row) {
    return ((row_ptr+row)->G4T40);
  }
  int get_G4T41(int row) {
    return ((row_ptr+row)->G4T41);
  }
  int get_G4T42(int row) {
    return ((row_ptr+row)->G4T42);
  }
  int get_G4T43(int row) {
    return ((row_ptr+row)->G4T43);
  }
  int get_G4T44(int row) {
    return ((row_ptr+row)->G4T44);
  }
  int get_G4T45(int row) {
    return ((row_ptr+row)->G4T45);
  }
  int get_G4T46(int row) {
    return ((row_ptr+row)->G4T46);
  }
  int get_G4T47(int row) {
    return ((row_ptr+row)->G4T47);
  }
  int get_G4T48(int row) {
    return ((row_ptr+row)->G4T48);
  }
  int get_G4T49(int row) {
    return ((row_ptr+row)->G4T49);
  }
  int get_G4T50(int row) {
    return ((row_ptr+row)->G4T50);
  }
  int get_G4T51(int row) {
    return ((row_ptr+row)->G4T51);
  }
  int get_G4T52(int row) {
    return ((row_ptr+row)->G4T52);
  }
  int get_G4T53(int row) {
    return ((row_ptr+row)->G4T53);
  }
  int get_G4T54(int row) {
    return ((row_ptr+row)->G4T54);
  }
  int get_G4T55(int row) {
    return ((row_ptr+row)->G4T55);
  }
  int get_G4T56(int row) {
    return ((row_ptr+row)->G4T56);
  }
  int get_G4T57(int row) {
    return ((row_ptr+row)->G4T57);
  }
  int get_G4T58(int row) {
    return ((row_ptr+row)->G4T58);
  }
  int get_G4T59(int row) {
    return ((row_ptr+row)->G4T59);
  }
  int get_G4T60(int row) {
    return ((row_ptr+row)->G4T60);
  }
  int get_G4T61(int row) {
    return ((row_ptr+row)->G4T61);
  }
  int get_G4T62(int row) {
    return ((row_ptr+row)->G4T62);
  }
  int get_G4T63(int row) {
    return ((row_ptr+row)->G4T63);
  }
  int get_G4T64(int row) {
    return ((row_ptr+row)->G4T64);
  }
};

struct GCPB_row {
  int pid;
  float x;
  float y;
  float z;
  float dEdx;
  float px;
  float py;
  float pz;
  float dt;
  float time;
  float path;
  float q;
  float r;
  int index;
};

class GCPB {
private:
  int nrows;
  struct GCPB_row *row_ptr;
public:
  GCPB(void) {
    return;
  }
  GCPB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_pid(int row) {
    return ((row_ptr+row)->pid);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_dEdx(int row) {
    return ((row_ptr+row)->dEdx);
  }
  float get_px(int row) {
    return ((row_ptr+row)->px);
  }
  float get_py(int row) {
    return ((row_ptr+row)->py);
  }
  float get_pz(int row) {
    return ((row_ptr+row)->pz);
  }
  float get_dt(int row) {
    return ((row_ptr+row)->dt);
  }
  float get_time(int row) {
    return ((row_ptr+row)->time);
  }
  float get_path(int row) {
    return ((row_ptr+row)->path);
  }
  float get_q(int row) {
    return ((row_ptr+row)->q);
  }
  float get_r(int row) {
    return ((row_ptr+row)->r);
  }
  int get_index(int row) {
    return ((row_ptr+row)->index);
  }
};

struct GGEO_row {
  int ID_half;
  float xpos;
  float ypos;
  float zpos;
  float sxpos;
  float sypos;
  float szpos;
};

class GGEO {
private:
  int nrows;
  struct GGEO_row *row_ptr;
public:
  GGEO(void) {
    return;
  }
  GGEO(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID_half(int row) {
    return ((row_ptr+row)->ID_half);
  }
  float get_xpos(int row) {
    return ((row_ptr+row)->xpos);
  }
  float get_ypos(int row) {
    return ((row_ptr+row)->ypos);
  }
  float get_zpos(int row) {
    return ((row_ptr+row)->zpos);
  }
  float get_sxpos(int row) {
    return ((row_ptr+row)->sxpos);
  }
  float get_sypos(int row) {
    return ((row_ptr+row)->sypos);
  }
  float get_szpos(int row) {
    return ((row_ptr+row)->szpos);
  }
};

struct GPAR_row {
  float fval;
  int ival;
  char char1[4];
  char char2[4];
  char char3[4];
  char char4[4];
  char char5[4];
};

class GPAR {
private:
  int nrows;
  struct GPAR_row *row_ptr;
public:
  GPAR(void) {
    return;
  }
  GPAR(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_fval(int row) {
    return ((row_ptr+row)->fval);
  }
  int get_ival(int row) {
    return ((row_ptr+row)->ival);
  }
  char *get_char1(int row) {
    return ((row_ptr+row)->char1);
  }
  char *get_char2(int row) {
    return ((row_ptr+row)->char2);
  }
  char *get_char3(int row) {
    return ((row_ptr+row)->char3);
  }
  char *get_char4(int row) {
    return ((row_ptr+row)->char4);
  }
  char *get_char5(int row) {
    return ((row_ptr+row)->char5);
  }
};

struct GPID_row {
  int pid;
  float x;
  float y;
  float z;
  float E;
  float px;
  float py;
  float pz;
  int q;
  int trkid;
  int sec;
  int paddle;
  float dedx;
  float beta;
  int sc_stat;
  float sc_time;
  float sc_len;
  int st_stat;
  float st_time;
  float st_len;
  float mass;
  int mass_ref;
  float betam;
  float epho;
  float tpho;
  int tagrid;
  int ngrf;
  int ppid;
};

class GPID {
private:
  int nrows;
  struct GPID_row *row_ptr;
public:
  GPID(void) {
    return;
  }
  GPID(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_pid(int row) {
    return ((row_ptr+row)->pid);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_E(int row) {
    return ((row_ptr+row)->E);
  }
  float get_px(int row) {
    return ((row_ptr+row)->px);
  }
  float get_py(int row) {
    return ((row_ptr+row)->py);
  }
  float get_pz(int row) {
    return ((row_ptr+row)->pz);
  }
  int get_q(int row) {
    return ((row_ptr+row)->q);
  }
  int get_trkid(int row) {
    return ((row_ptr+row)->trkid);
  }
  int get_sec(int row) {
    return ((row_ptr+row)->sec);
  }
  int get_paddle(int row) {
    return ((row_ptr+row)->paddle);
  }
  float get_dedx(int row) {
    return ((row_ptr+row)->dedx);
  }
  float get_beta(int row) {
    return ((row_ptr+row)->beta);
  }
  int get_sc_stat(int row) {
    return ((row_ptr+row)->sc_stat);
  }
  float get_sc_time(int row) {
    return ((row_ptr+row)->sc_time);
  }
  float get_sc_len(int row) {
    return ((row_ptr+row)->sc_len);
  }
  int get_st_stat(int row) {
    return ((row_ptr+row)->st_stat);
  }
  float get_st_time(int row) {
    return ((row_ptr+row)->st_time);
  }
  float get_st_len(int row) {
    return ((row_ptr+row)->st_len);
  }
  float get_mass(int row) {
    return ((row_ptr+row)->mass);
  }
  int get_mass_ref(int row) {
    return ((row_ptr+row)->mass_ref);
  }
  float get_betam(int row) {
    return ((row_ptr+row)->betam);
  }
  float get_epho(int row) {
    return ((row_ptr+row)->epho);
  }
  float get_tpho(int row) {
    return ((row_ptr+row)->tpho);
  }
  int get_tagrid(int row) {
    return ((row_ptr+row)->tagrid);
  }
  int get_ngrf(int row) {
    return ((row_ptr+row)->ngrf);
  }
  int get_ppid(int row) {
    return ((row_ptr+row)->ppid);
  }
};

struct GP_X_row {
  float value;
};

class GP_X {
private:
  int nrows;
  struct GP_X_row *row_ptr;
public:
  GP_X(void) {
    return;
  }
  GP_X(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_value(int row) {
    return ((row_ptr+row)->value);
  }
};

struct GP_Y_row {
  float value;
};

class GP_Y {
private:
  int nrows;
  struct GP_Y_row *row_ptr;
public:
  GP_Y(void) {
    return;
  }
  GP_Y(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_value(int row) {
    return ((row_ptr+row)->value);
  }
};

struct HBER_row {
  float q_over_p;
  float lambda;
  float phi;
  float d0;
  float z0;
  float c11;
  float c12;
  float c13;
  float c14;
  float c15;
  float c22;
  float c23;
  float c24;
  float c25;
  float c33;
  float c34;
  float c35;
  float c44;
  float c45;
  float c55;
  float chi2;
  int layinfo1;
  int layinfo2;
};

class HBER {
private:
  int nrows;
  struct HBER_row *row_ptr;
public:
  HBER(void) {
    return;
  }
  HBER(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_q_over_p(int row) {
    return ((row_ptr+row)->q_over_p);
  }
  float get_lambda(int row) {
    return ((row_ptr+row)->lambda);
  }
  float get_phi(int row) {
    return ((row_ptr+row)->phi);
  }
  float get_d0(int row) {
    return ((row_ptr+row)->d0);
  }
  float get_z0(int row) {
    return ((row_ptr+row)->z0);
  }
  float get_c11(int row) {
    return ((row_ptr+row)->c11);
  }
  float get_c12(int row) {
    return ((row_ptr+row)->c12);
  }
  float get_c13(int row) {
    return ((row_ptr+row)->c13);
  }
  float get_c14(int row) {
    return ((row_ptr+row)->c14);
  }
  float get_c15(int row) {
    return ((row_ptr+row)->c15);
  }
  float get_c22(int row) {
    return ((row_ptr+row)->c22);
  }
  float get_c23(int row) {
    return ((row_ptr+row)->c23);
  }
  float get_c24(int row) {
    return ((row_ptr+row)->c24);
  }
  float get_c25(int row) {
    return ((row_ptr+row)->c25);
  }
  float get_c33(int row) {
    return ((row_ptr+row)->c33);
  }
  float get_c34(int row) {
    return ((row_ptr+row)->c34);
  }
  float get_c35(int row) {
    return ((row_ptr+row)->c35);
  }
  float get_c44(int row) {
    return ((row_ptr+row)->c44);
  }
  float get_c45(int row) {
    return ((row_ptr+row)->c45);
  }
  float get_c55(int row) {
    return ((row_ptr+row)->c55);
  }
  float get_chi2(int row) {
    return ((row_ptr+row)->chi2);
  }
  int get_layinfo1(int row) {
    return ((row_ptr+row)->layinfo1);
  }
  int get_layinfo2(int row) {
    return ((row_ptr+row)->layinfo2);
  }
};

struct HBID_row {
  int track;
  int sec;
  float beta;
  float vtime;
  int sc_stat;
  int sc_id;
  float sc_time;
  float sc_qual;
  float sc_vtime;
  float sc_beta;
  int cc_stat;
  int cc_id;
  float cc_time;
  float cc_qual;
  float cc_vtime;
  float cc_beta;
  int ec_stat;
  int ec_id;
  float ec_time;
  float ec_qual;
  float ec_vtime;
  float ec_beta;
  int st_stat;
  int st_id;
  float st_time;
  float st_qual;
  float st_vtime;
  float st_beta;
  int lac_stat;
  int lac_id;
  float lac_time;
  float lac_qual;
  float lac_vtime;
  float lac_beta;
};

class HBID {
private:
  int nrows;
  struct HBID_row *row_ptr;
public:
  HBID(void) {
    return;
  }
  HBID(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_track(int row) {
    return ((row_ptr+row)->track);
  }
  int get_sec(int row) {
    return ((row_ptr+row)->sec);
  }
  float get_beta(int row) {
    return ((row_ptr+row)->beta);
  }
  float get_vtime(int row) {
    return ((row_ptr+row)->vtime);
  }
  int get_sc_stat(int row) {
    return ((row_ptr+row)->sc_stat);
  }
  int get_sc_id(int row) {
    return ((row_ptr+row)->sc_id);
  }
  float get_sc_time(int row) {
    return ((row_ptr+row)->sc_time);
  }
  float get_sc_qual(int row) {
    return ((row_ptr+row)->sc_qual);
  }
  float get_sc_vtime(int row) {
    return ((row_ptr+row)->sc_vtime);
  }
  float get_sc_beta(int row) {
    return ((row_ptr+row)->sc_beta);
  }
  int get_cc_stat(int row) {
    return ((row_ptr+row)->cc_stat);
  }
  int get_cc_id(int row) {
    return ((row_ptr+row)->cc_id);
  }
  float get_cc_time(int row) {
    return ((row_ptr+row)->cc_time);
  }
  float get_cc_qual(int row) {
    return ((row_ptr+row)->cc_qual);
  }
  float get_cc_vtime(int row) {
    return ((row_ptr+row)->cc_vtime);
  }
  float get_cc_beta(int row) {
    return ((row_ptr+row)->cc_beta);
  }
  int get_ec_stat(int row) {
    return ((row_ptr+row)->ec_stat);
  }
  int get_ec_id(int row) {
    return ((row_ptr+row)->ec_id);
  }
  float get_ec_time(int row) {
    return ((row_ptr+row)->ec_time);
  }
  float get_ec_qual(int row) {
    return ((row_ptr+row)->ec_qual);
  }
  float get_ec_vtime(int row) {
    return ((row_ptr+row)->ec_vtime);
  }
  float get_ec_beta(int row) {
    return ((row_ptr+row)->ec_beta);
  }
  int get_st_stat(int row) {
    return ((row_ptr+row)->st_stat);
  }
  int get_st_id(int row) {
    return ((row_ptr+row)->st_id);
  }
  float get_st_time(int row) {
    return ((row_ptr+row)->st_time);
  }
  float get_st_qual(int row) {
    return ((row_ptr+row)->st_qual);
  }
  float get_st_vtime(int row) {
    return ((row_ptr+row)->st_vtime);
  }
  float get_st_beta(int row) {
    return ((row_ptr+row)->st_beta);
  }
  int get_lac_stat(int row) {
    return ((row_ptr+row)->lac_stat);
  }
  int get_lac_id(int row) {
    return ((row_ptr+row)->lac_id);
  }
  float get_lac_time(int row) {
    return ((row_ptr+row)->lac_time);
  }
  float get_lac_qual(int row) {
    return ((row_ptr+row)->lac_qual);
  }
  float get_lac_vtime(int row) {
    return ((row_ptr+row)->lac_vtime);
  }
  float get_lac_beta(int row) {
    return ((row_ptr+row)->lac_beta);
  }
};

struct HBLA_row {
  int trk_pln;
  float x;
  float y;
  float z;
  float Bx;
  float By;
  float Bz;
  float tlen;
  int dc1;
  int stat;
  int wire;
  float dtime;
  float alpha;
  float wlen;
  float sgdoca;
  float fitdoca;
};

class HBLA {
private:
  int nrows;
  struct HBLA_row *row_ptr;
public:
  HBLA(void) {
    return;
  }
  HBLA(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_trk_pln(int row) {
    return ((row_ptr+row)->trk_pln);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_Bx(int row) {
    return ((row_ptr+row)->Bx);
  }
  float get_By(int row) {
    return ((row_ptr+row)->By);
  }
  float get_Bz(int row) {
    return ((row_ptr+row)->Bz);
  }
  float get_tlen(int row) {
    return ((row_ptr+row)->tlen);
  }
  int get_dc1(int row) {
    return ((row_ptr+row)->dc1);
  }
  int get_stat(int row) {
    return ((row_ptr+row)->stat);
  }
  int get_wire(int row) {
    return ((row_ptr+row)->wire);
  }
  float get_dtime(int row) {
    return ((row_ptr+row)->dtime);
  }
  float get_alpha(int row) {
    return ((row_ptr+row)->alpha);
  }
  float get_wlen(int row) {
    return ((row_ptr+row)->wlen);
  }
  float get_sgdoca(int row) {
    return ((row_ptr+row)->sgdoca);
  }
  float get_fitdoca(int row) {
    return ((row_ptr+row)->fitdoca);
  }
};

struct HBTB_row {
  int trk;
  int sly;
  int icl;
  int isg;
  int id1;
  int id2;
  int id3;
  int id4;
  int id5;
  int id6;
};

class HBTB {
private:
  int nrows;
  struct HBTB_row *row_ptr;
public:
  HBTB(void) {
    return;
  }
  HBTB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_trk(int row) {
    return ((row_ptr+row)->trk);
  }
  int get_sly(int row) {
    return ((row_ptr+row)->sly);
  }
  int get_icl(int row) {
    return ((row_ptr+row)->icl);
  }
  int get_isg(int row) {
    return ((row_ptr+row)->isg);
  }
  int get_id1(int row) {
    return ((row_ptr+row)->id1);
  }
  int get_id2(int row) {
    return ((row_ptr+row)->id2);
  }
  int get_id3(int row) {
    return ((row_ptr+row)->id3);
  }
  int get_id4(int row) {
    return ((row_ptr+row)->id4);
  }
  int get_id5(int row) {
    return ((row_ptr+row)->id5);
  }
  int get_id6(int row) {
    return ((row_ptr+row)->id6);
  }
};

struct HBTR_row {
  float x;
  float y;
  float z;
  float px;
  float py;
  float pz;
  float q;
  float chi2;
  int itr_sec;
};

class HBTR {
private:
  int nrows;
  struct HBTR_row *row_ptr;
public:
  HBTR(void) {
    return;
  }
  HBTR(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_px(int row) {
    return ((row_ptr+row)->px);
  }
  float get_py(int row) {
    return ((row_ptr+row)->py);
  }
  float get_pz(int row) {
    return ((row_ptr+row)->pz);
  }
  float get_q(int row) {
    return ((row_ptr+row)->q);
  }
  float get_chi2(int row) {
    return ((row_ptr+row)->chi2);
  }
  int get_itr_sec(int row) {
    return ((row_ptr+row)->itr_sec);
  }
};

struct HCAL_row {
  int VERSION;
  int RUN_LOW;
  int RUN_HIGH;
  int CATIME;
  int ROCCA;
};

class HCAL {
private:
  int nrows;
  struct HCAL_row *row_ptr;
public:
  HCAL(void) {
    return;
  }
  HCAL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_VERSION(int row) {
    return ((row_ptr+row)->VERSION);
  }
  int get_RUN_LOW(int row) {
    return ((row_ptr+row)->RUN_LOW);
  }
  int get_RUN_HIGH(int row) {
    return ((row_ptr+row)->RUN_HIGH);
  }
  int get_CATIME(int row) {
    return ((row_ptr+row)->CATIME);
  }
  int get_ROCCA(int row) {
    return ((row_ptr+row)->ROCCA);
  }
};

struct HDPL_row {
  int trk_pln;
  float x;
  float y;
  float z;
  float cx;
  float cy;
  float cz;
  float tlen;
};

class HDPL {
private:
  int nrows;
  struct HDPL_row *row_ptr;
public:
  HDPL(void) {
    return;
  }
  HDPL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_trk_pln(int row) {
    return ((row_ptr+row)->trk_pln);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_cx(int row) {
    return ((row_ptr+row)->cx);
  }
  float get_cy(int row) {
    return ((row_ptr+row)->cy);
  }
  float get_cz(int row) {
    return ((row_ptr+row)->cz);
  }
  float get_tlen(int row) {
    return ((row_ptr+row)->tlen);
  }
};

struct HEAD_row {
  int VERSION;
  int NRUN;
  int NEVENT;
  int TIME;
  int TYPE;
  int ROC;
  int EVTCLASS;
  int TRIGBITS;
};

class HEAD {
private:
  int nrows;
  struct HEAD_row *row_ptr;
public:
  HEAD(void) {
    return;
  }
  HEAD(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_VERSION(int row) {
    return ((row_ptr+row)->VERSION);
  }
  int get_NRUN(int row) {
    return ((row_ptr+row)->NRUN);
  }
  int get_NEVENT(int row) {
    return ((row_ptr+row)->NEVENT);
  }
  int get_TIME(int row) {
    return ((row_ptr+row)->TIME);
  }
  int get_TYPE(int row) {
    return ((row_ptr+row)->TYPE);
  }
  int get_ROC(int row) {
    return ((row_ptr+row)->ROC);
  }
  int get_EVTCLASS(int row) {
    return ((row_ptr+row)->EVTCLASS);
  }
  int get_TRIGBITS(int row) {
    return ((row_ptr+row)->TRIGBITS);
  }
};

struct HEVT_row {
  int ESTATUS;
  int NRUN;
  int NEVENT;
  int TYPE;
  int NPGP;
  int TRGPRS;
  float FC;
  float FCG;
  float TG;
  float STT;
  float RF1;
  float RF2;
  float CON1;
  float CON2;
  float CON3;
  int PTIME;
};

class HEVT {
private:
  int nrows;
  struct HEVT_row *row_ptr;
public:
  HEVT(void) {
    return;
  }
  HEVT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ESTATUS(int row) {
    return ((row_ptr+row)->ESTATUS);
  }
  int get_NRUN(int row) {
    return ((row_ptr+row)->NRUN);
  }
  int get_NEVENT(int row) {
    return ((row_ptr+row)->NEVENT);
  }
  int get_TYPE(int row) {
    return ((row_ptr+row)->TYPE);
  }
  int get_NPGP(int row) {
    return ((row_ptr+row)->NPGP);
  }
  int get_TRGPRS(int row) {
    return ((row_ptr+row)->TRGPRS);
  }
  float get_FC(int row) {
    return ((row_ptr+row)->FC);
  }
  float get_FCG(int row) {
    return ((row_ptr+row)->FCG);
  }
  float get_TG(int row) {
    return ((row_ptr+row)->TG);
  }
  float get_STT(int row) {
    return ((row_ptr+row)->STT);
  }
  float get_RF1(int row) {
    return ((row_ptr+row)->RF1);
  }
  float get_RF2(int row) {
    return ((row_ptr+row)->RF2);
  }
  float get_CON1(int row) {
    return ((row_ptr+row)->CON1);
  }
  float get_CON2(int row) {
    return ((row_ptr+row)->CON2);
  }
  float get_CON3(int row) {
    return ((row_ptr+row)->CON3);
  }
  int get_PTIME(int row) {
    return ((row_ptr+row)->PTIME);
  }
};

struct HLS_row {
  int S1;
  int S2;
  int S3;
  int S4;
  int S5;
  int S6;
  int S7;
  int S8;
  int S9;
  int S10;
  int S11;
  int S12;
  int S13;
  int S14;
  int S15;
  int S16;
};

class HLS {
private:
  int nrows;
  struct HLS_row *row_ptr;
public:
  HLS(void) {
    return;
  }
  HLS(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_S1(int row) {
    return ((row_ptr+row)->S1);
  }
  int get_S2(int row) {
    return ((row_ptr+row)->S2);
  }
  int get_S3(int row) {
    return ((row_ptr+row)->S3);
  }
  int get_S4(int row) {
    return ((row_ptr+row)->S4);
  }
  int get_S5(int row) {
    return ((row_ptr+row)->S5);
  }
  int get_S6(int row) {
    return ((row_ptr+row)->S6);
  }
  int get_S7(int row) {
    return ((row_ptr+row)->S7);
  }
  int get_S8(int row) {
    return ((row_ptr+row)->S8);
  }
  int get_S9(int row) {
    return ((row_ptr+row)->S9);
  }
  int get_S10(int row) {
    return ((row_ptr+row)->S10);
  }
  int get_S11(int row) {
    return ((row_ptr+row)->S11);
  }
  int get_S12(int row) {
    return ((row_ptr+row)->S12);
  }
  int get_S13(int row) {
    return ((row_ptr+row)->S13);
  }
  int get_S14(int row) {
    return ((row_ptr+row)->S14);
  }
  int get_S15(int row) {
    return ((row_ptr+row)->S15);
  }
  int get_S16(int row) {
    return ((row_ptr+row)->S16);
  }
};

struct IC_row {
  short ID;
  short TDC;
  short ADC;
};

class IC {
private:
  int nrows;
  struct IC_row *row_ptr;
public:
  IC(void) {
    return;
  }
  IC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
  short get_ADC(int row) {
    return ((row_ptr+row)->ADC);
  }
};

struct ICHB_row {
  float Eclust;
  float Eclmax;
  float Tclust;
  float T_next;
  float xclust;
  float yclust;
  float zclust;
  float xclmax;
  float yclmax;
  float M2_x;
  float M2_y;
  float M3_x;
  float M3_y;
  int ncryst;
};

class ICHB {
private:
  int nrows;
  struct ICHB_row *row_ptr;
public:
  ICHB(void) {
    return;
  }
  ICHB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_Eclust(int row) {
    return ((row_ptr+row)->Eclust);
  }
  float get_Eclmax(int row) {
    return ((row_ptr+row)->Eclmax);
  }
  float get_Tclust(int row) {
    return ((row_ptr+row)->Tclust);
  }
  float get_T_next(int row) {
    return ((row_ptr+row)->T_next);
  }
  float get_xclust(int row) {
    return ((row_ptr+row)->xclust);
  }
  float get_yclust(int row) {
    return ((row_ptr+row)->yclust);
  }
  float get_zclust(int row) {
    return ((row_ptr+row)->zclust);
  }
  float get_xclmax(int row) {
    return ((row_ptr+row)->xclmax);
  }
  float get_yclmax(int row) {
    return ((row_ptr+row)->yclmax);
  }
  float get_M2_x(int row) {
    return ((row_ptr+row)->M2_x);
  }
  float get_M2_y(int row) {
    return ((row_ptr+row)->M2_y);
  }
  float get_M3_x(int row) {
    return ((row_ptr+row)->M3_x);
  }
  float get_M3_y(int row) {
    return ((row_ptr+row)->M3_y);
  }
  int get_ncryst(int row) {
    return ((row_ptr+row)->ncryst);
  }
};

struct ICPB_row {
  float Etot;
  float Ecen;
  float Time;
  float T_next;
  float X;
  float Y;
  float Z;
  float M2_hit;
  float M3_hit;
  int Status;
};

class ICPB {
private:
  int nrows;
  struct ICPB_row *row_ptr;
public:
  ICPB(void) {
    return;
  }
  ICPB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_Etot(int row) {
    return ((row_ptr+row)->Etot);
  }
  float get_Ecen(int row) {
    return ((row_ptr+row)->Ecen);
  }
  float get_Time(int row) {
    return ((row_ptr+row)->Time);
  }
  float get_T_next(int row) {
    return ((row_ptr+row)->T_next);
  }
  float get_X(int row) {
    return ((row_ptr+row)->X);
  }
  float get_Y(int row) {
    return ((row_ptr+row)->Y);
  }
  float get_Z(int row) {
    return ((row_ptr+row)->Z);
  }
  float get_M2_hit(int row) {
    return ((row_ptr+row)->M2_hit);
  }
  float get_M3_hit(int row) {
    return ((row_ptr+row)->M3_hit);
  }
  int get_Status(int row) {
    return ((row_ptr+row)->Status);
  }
};

struct KFIT_row {
  float momenta_f;
  float lambda_f;
  float phi_f;
  float d0_f;
  float z0_f;
  float sigma11;
  float sigma12;
  float sigma13;
  float sigma14;
  float sigma15;
  float sigma22;
  float sigma23;
  float sigma24;
  float sigma25;
  float sigma33;
  float sigma34;
  float sigma35;
  float sigma44;
  float sigma45;
  float sigma55;
  float cov11;
  float cov12;
  float cov13;
  float cov14;
  float cov15;
  float cov21;
  float cov22;
  float cov23;
  float cov24;
  float cov25;
  float cov31;
  float cov32;
  float cov33;
  float cov34;
  float cov35;
  float cov41;
  float cov42;
  float cov43;
  float cov44;
  float cov45;
  float cov51;
  float cov52;
  float cov53;
  float cov54;
  float cov55;
  float chi2piece;
};

class KFIT {
private:
  int nrows;
  struct KFIT_row *row_ptr;
public:
  KFIT(void) {
    return;
  }
  KFIT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_momenta_f(int row) {
    return ((row_ptr+row)->momenta_f);
  }
  float get_lambda_f(int row) {
    return ((row_ptr+row)->lambda_f);
  }
  float get_phi_f(int row) {
    return ((row_ptr+row)->phi_f);
  }
  float get_d0_f(int row) {
    return ((row_ptr+row)->d0_f);
  }
  float get_z0_f(int row) {
    return ((row_ptr+row)->z0_f);
  }
  float get_sigma11(int row) {
    return ((row_ptr+row)->sigma11);
  }
  float get_sigma12(int row) {
    return ((row_ptr+row)->sigma12);
  }
  float get_sigma13(int row) {
    return ((row_ptr+row)->sigma13);
  }
  float get_sigma14(int row) {
    return ((row_ptr+row)->sigma14);
  }
  float get_sigma15(int row) {
    return ((row_ptr+row)->sigma15);
  }
  float get_sigma22(int row) {
    return ((row_ptr+row)->sigma22);
  }
  float get_sigma23(int row) {
    return ((row_ptr+row)->sigma23);
  }
  float get_sigma24(int row) {
    return ((row_ptr+row)->sigma24);
  }
  float get_sigma25(int row) {
    return ((row_ptr+row)->sigma25);
  }
  float get_sigma33(int row) {
    return ((row_ptr+row)->sigma33);
  }
  float get_sigma34(int row) {
    return ((row_ptr+row)->sigma34);
  }
  float get_sigma35(int row) {
    return ((row_ptr+row)->sigma35);
  }
  float get_sigma44(int row) {
    return ((row_ptr+row)->sigma44);
  }
  float get_sigma45(int row) {
    return ((row_ptr+row)->sigma45);
  }
  float get_sigma55(int row) {
    return ((row_ptr+row)->sigma55);
  }
  float get_cov11(int row) {
    return ((row_ptr+row)->cov11);
  }
  float get_cov12(int row) {
    return ((row_ptr+row)->cov12);
  }
  float get_cov13(int row) {
    return ((row_ptr+row)->cov13);
  }
  float get_cov14(int row) {
    return ((row_ptr+row)->cov14);
  }
  float get_cov15(int row) {
    return ((row_ptr+row)->cov15);
  }
  float get_cov21(int row) {
    return ((row_ptr+row)->cov21);
  }
  float get_cov22(int row) {
    return ((row_ptr+row)->cov22);
  }
  float get_cov23(int row) {
    return ((row_ptr+row)->cov23);
  }
  float get_cov24(int row) {
    return ((row_ptr+row)->cov24);
  }
  float get_cov25(int row) {
    return ((row_ptr+row)->cov25);
  }
  float get_cov31(int row) {
    return ((row_ptr+row)->cov31);
  }
  float get_cov32(int row) {
    return ((row_ptr+row)->cov32);
  }
  float get_cov33(int row) {
    return ((row_ptr+row)->cov33);
  }
  float get_cov34(int row) {
    return ((row_ptr+row)->cov34);
  }
  float get_cov35(int row) {
    return ((row_ptr+row)->cov35);
  }
  float get_cov41(int row) {
    return ((row_ptr+row)->cov41);
  }
  float get_cov42(int row) {
    return ((row_ptr+row)->cov42);
  }
  float get_cov43(int row) {
    return ((row_ptr+row)->cov43);
  }
  float get_cov44(int row) {
    return ((row_ptr+row)->cov44);
  }
  float get_cov45(int row) {
    return ((row_ptr+row)->cov45);
  }
  float get_cov51(int row) {
    return ((row_ptr+row)->cov51);
  }
  float get_cov52(int row) {
    return ((row_ptr+row)->cov52);
  }
  float get_cov53(int row) {
    return ((row_ptr+row)->cov53);
  }
  float get_cov54(int row) {
    return ((row_ptr+row)->cov54);
  }
  float get_cov55(int row) {
    return ((row_ptr+row)->cov55);
  }
  float get_chi2piece(int row) {
    return ((row_ptr+row)->chi2piece);
  }
};

struct L1PG_row {
  char l1prog[4];
};

class L1PG {
private:
  int nrows;
  struct L1PG_row *row_ptr;
public:
  L1PG(void) {
    return;
  }
  L1PG(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  char *get_l1prog(int row) {
    return ((row_ptr+row)->l1prog);
  }
};

struct L2H_row {
  short ID;
  short TDC;
};

class L2H {
private:
  int nrows;
  struct L2H_row *row_ptr;
public:
  L2H(void) {
    return;
  }
  L2H(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct L2S_row {
  short ID;
  short TDC;
};

class L2S {
private:
  int nrows;
  struct L2S_row *row_ptr;
public:
  L2S(void) {
    return;
  }
  L2S(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct LASR_row {
  int ID;
  int stat1;
  int stat2;
  int stat3;
};

class LASR {
private:
  int nrows;
  struct LASR_row *row_ptr;
public:
  LASR(void) {
    return;
  }
  LASR(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_stat1(int row) {
    return ((row_ptr+row)->stat1);
  }
  int get_stat2(int row) {
    return ((row_ptr+row)->stat2);
  }
  int get_stat3(int row) {
    return ((row_ptr+row)->stat3);
  }
};

struct LCDI_row {
  int crate;
  int slot;
  int mask;
  int threshold;
};

class LCDI {
private:
  int nrows;
  struct LCDI_row *row_ptr;
public:
  LCDI(void) {
    return;
  }
  LCDI(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_crate(int row) {
    return ((row_ptr+row)->crate);
  }
  int get_slot(int row) {
    return ((row_ptr+row)->slot);
  }
  int get_mask(int row) {
    return ((row_ptr+row)->mask);
  }
  int get_threshold(int row) {
    return ((row_ptr+row)->threshold);
  }
};

struct LCPB_row {
  int ScHt;
  float Etot;
  float Time;
  float Path;
  float X;
  float Y;
  float Z;
  float Chi2LC;
  int Status;
  float Ein;
};

class LCPB {
private:
  int nrows;
  struct LCPB_row *row_ptr;
public:
  LCPB(void) {
    return;
  }
  LCPB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ScHt(int row) {
    return ((row_ptr+row)->ScHt);
  }
  float get_Etot(int row) {
    return ((row_ptr+row)->Etot);
  }
  float get_Time(int row) {
    return ((row_ptr+row)->Time);
  }
  float get_Path(int row) {
    return ((row_ptr+row)->Path);
  }
  float get_X(int row) {
    return ((row_ptr+row)->X);
  }
  float get_Y(int row) {
    return ((row_ptr+row)->Y);
  }
  float get_Z(int row) {
    return ((row_ptr+row)->Z);
  }
  float get_Chi2LC(int row) {
    return ((row_ptr+row)->Chi2LC);
  }
  int get_Status(int row) {
    return ((row_ptr+row)->Status);
  }
  float get_Ein(int row) {
    return ((row_ptr+row)->Ein);
  }
};

struct LOWQ_row {
  int pid;
  float x;
  float y;
  float z;
  float E;
  float px;
  float py;
  float pz;
  float q;
  float qpid;
  float qtrk;
  int flags;
};

class LOWQ {
private:
  int nrows;
  struct LOWQ_row *row_ptr;
public:
  LOWQ(void) {
    return;
  }
  LOWQ(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_pid(int row) {
    return ((row_ptr+row)->pid);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_E(int row) {
    return ((row_ptr+row)->E);
  }
  float get_px(int row) {
    return ((row_ptr+row)->px);
  }
  float get_py(int row) {
    return ((row_ptr+row)->py);
  }
  float get_pz(int row) {
    return ((row_ptr+row)->pz);
  }
  float get_q(int row) {
    return ((row_ptr+row)->q);
  }
  float get_qpid(int row) {
    return ((row_ptr+row)->qpid);
  }
  float get_qtrk(int row) {
    return ((row_ptr+row)->qtrk);
  }
  int get_flags(int row) {
    return ((row_ptr+row)->flags);
  }
};

struct MCEV_row {
  int I1;
  int i2;
};

class MCEV {
private:
  int nrows;
  struct MCEV_row *row_ptr;
public:
  MCEV(void) {
    return;
  }
  MCEV(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_I1(int row) {
    return ((row_ptr+row)->I1);
  }
  int get_i2(int row) {
    return ((row_ptr+row)->i2);
  }
};

struct MCHD_row {
  int NRUN;
  int NEVENT;
  int TIME;
  int TYPE;
  int REACTYPE;
  float WEIGHT;
  float W;
  float Q2;
  float E_PHOT;
  float PX_PHOT;
  float PY_PHOT;
  float PZ_PHOT;
  float E_TARG;
  float PX_TARG;
  float PY_TARG;
  float PZ_TARG;
};

class MCHD {
private:
  int nrows;
  struct MCHD_row *row_ptr;
public:
  MCHD(void) {
    return;
  }
  MCHD(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_NRUN(int row) {
    return ((row_ptr+row)->NRUN);
  }
  int get_NEVENT(int row) {
    return ((row_ptr+row)->NEVENT);
  }
  int get_TIME(int row) {
    return ((row_ptr+row)->TIME);
  }
  int get_TYPE(int row) {
    return ((row_ptr+row)->TYPE);
  }
  int get_REACTYPE(int row) {
    return ((row_ptr+row)->REACTYPE);
  }
  float get_WEIGHT(int row) {
    return ((row_ptr+row)->WEIGHT);
  }
  float get_W(int row) {
    return ((row_ptr+row)->W);
  }
  float get_Q2(int row) {
    return ((row_ptr+row)->Q2);
  }
  float get_E_PHOT(int row) {
    return ((row_ptr+row)->E_PHOT);
  }
  float get_PX_PHOT(int row) {
    return ((row_ptr+row)->PX_PHOT);
  }
  float get_PY_PHOT(int row) {
    return ((row_ptr+row)->PY_PHOT);
  }
  float get_PZ_PHOT(int row) {
    return ((row_ptr+row)->PZ_PHOT);
  }
  float get_E_TARG(int row) {
    return ((row_ptr+row)->E_TARG);
  }
  float get_PX_TARG(int row) {
    return ((row_ptr+row)->PX_TARG);
  }
  float get_PY_TARG(int row) {
    return ((row_ptr+row)->PY_TARG);
  }
  float get_PZ_TARG(int row) {
    return ((row_ptr+row)->PZ_TARG);
  }
};

struct MCTK_row {
  float cx;
  float cy;
  float cz;
  float pmom;
  float mass;
  float charge;
  int id;
  int flag;
  int beg_vtx;
  int end_vtx;
  int parent;
};

class MCTK {
private:
  int nrows;
  struct MCTK_row *row_ptr;
public:
  MCTK(void) {
    return;
  }
  MCTK(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_cx(int row) {
    return ((row_ptr+row)->cx);
  }
  float get_cy(int row) {
    return ((row_ptr+row)->cy);
  }
  float get_cz(int row) {
    return ((row_ptr+row)->cz);
  }
  float get_pmom(int row) {
    return ((row_ptr+row)->pmom);
  }
  float get_mass(int row) {
    return ((row_ptr+row)->mass);
  }
  float get_charge(int row) {
    return ((row_ptr+row)->charge);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  int get_flag(int row) {
    return ((row_ptr+row)->flag);
  }
  int get_beg_vtx(int row) {
    return ((row_ptr+row)->beg_vtx);
  }
  int get_end_vtx(int row) {
    return ((row_ptr+row)->end_vtx);
  }
  int get_parent(int row) {
    return ((row_ptr+row)->parent);
  }
};

struct MCVX_row {
  float x;
  float y;
  float z;
  float tof;
  int flag;
};

class MCVX {
private:
  int nrows;
  struct MCVX_row *row_ptr;
public:
  MCVX(void) {
    return;
  }
  MCVX(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_tof(int row) {
    return ((row_ptr+row)->tof);
  }
  int get_flag(int row) {
    return ((row_ptr+row)->flag);
  }
};

struct MS1_row {
  short ID;
  short ADC;
};

class MS1 {
private:
  int nrows;
  struct MS1_row *row_ptr;
public:
  MS1(void) {
    return;
  }
  MS1(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_ADC(int row) {
    return ((row_ptr+row)->ADC);
  }
};

struct MTRK_row {
  int sect;
  int trkl1;
  int trkl2;
  int trkl3;
  int trkl4;
  int trkl5;
  int trkl6;
};

class MTRK {
private:
  int nrows;
  struct MTRK_row *row_ptr;
public:
  MTRK(void) {
    return;
  }
  MTRK(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_sect(int row) {
    return ((row_ptr+row)->sect);
  }
  int get_trkl1(int row) {
    return ((row_ptr+row)->trkl1);
  }
  int get_trkl2(int row) {
    return ((row_ptr+row)->trkl2);
  }
  int get_trkl3(int row) {
    return ((row_ptr+row)->trkl3);
  }
  int get_trkl4(int row) {
    return ((row_ptr+row)->trkl4);
  }
  int get_trkl5(int row) {
    return ((row_ptr+row)->trkl5);
  }
  int get_trkl6(int row) {
    return ((row_ptr+row)->trkl6);
  }
};

struct MVRT_row {
  int v_id;
  float ntrk;
  float x;
  float y;
  float z;
  float chi2;
  float cxx;
  float cxy;
  float cxz;
  float cyy;
  float cyz;
  float czz;
  int stat;
};

class MVRT {
private:
  int nrows;
  struct MVRT_row *row_ptr;
public:
  MVRT(void) {
    return;
  }
  MVRT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_v_id(int row) {
    return ((row_ptr+row)->v_id);
  }
  float get_ntrk(int row) {
    return ((row_ptr+row)->ntrk);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_chi2(int row) {
    return ((row_ptr+row)->chi2);
  }
  float get_cxx(int row) {
    return ((row_ptr+row)->cxx);
  }
  float get_cxy(int row) {
    return ((row_ptr+row)->cxy);
  }
  float get_cxz(int row) {
    return ((row_ptr+row)->cxz);
  }
  float get_cyy(int row) {
    return ((row_ptr+row)->cyy);
  }
  float get_cyz(int row) {
    return ((row_ptr+row)->cyz);
  }
  float get_czz(int row) {
    return ((row_ptr+row)->czz);
  }
  int get_stat(int row) {
    return ((row_ptr+row)->stat);
  }
};

struct PART_row {
  int pid;
  float x;
  float y;
  float z;
  float E;
  float px;
  float py;
  float pz;
  float q;
  int trkid;
  float qpid;
  float qtrk;
  int flags;
};

class PART {
private:
  int nrows;
  struct PART_row *row_ptr;
public:
  PART(void) {
    return;
  }
  PART(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_pid(int row) {
    return ((row_ptr+row)->pid);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_E(int row) {
    return ((row_ptr+row)->E);
  }
  float get_px(int row) {
    return ((row_ptr+row)->px);
  }
  float get_py(int row) {
    return ((row_ptr+row)->py);
  }
  float get_pz(int row) {
    return ((row_ptr+row)->pz);
  }
  float get_q(int row) {
    return ((row_ptr+row)->q);
  }
  int get_trkid(int row) {
    return ((row_ptr+row)->trkid);
  }
  float get_qpid(int row) {
    return ((row_ptr+row)->qpid);
  }
  float get_qtrk(int row) {
    return ((row_ptr+row)->qtrk);
  }
  int get_flags(int row) {
    return ((row_ptr+row)->flags);
  }
};

struct PCO_row {
  float TIME;
  float ELT;
  float ERB;
  float ELB;
  float ERT;
  float EMAIN;
  float EVETO;
  int TID;
};

class PCO {
private:
  int nrows;
  struct PCO_row *row_ptr;
public:
  PCO(void) {
    return;
  }
  PCO(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_TIME(int row) {
    return ((row_ptr+row)->TIME);
  }
  float get_ELT(int row) {
    return ((row_ptr+row)->ELT);
  }
  float get_ERB(int row) {
    return ((row_ptr+row)->ERB);
  }
  float get_ELB(int row) {
    return ((row_ptr+row)->ELB);
  }
  float get_ERT(int row) {
    return ((row_ptr+row)->ERT);
  }
  float get_EMAIN(int row) {
    return ((row_ptr+row)->EMAIN);
  }
  float get_EVETO(int row) {
    return ((row_ptr+row)->EVETO);
  }
  int get_TID(int row) {
    return ((row_ptr+row)->TID);
  }
};

struct PHTM_row {
  int EVID;
  int Nsprot;
  int Npip;
  int Npim;
  int Nppippim;
  int Nppip;
  int Npippim;
  int Nppim;
  int Nkp;
  int Npkp;
  float tag_pi_v;
};

class PHTM {
private:
  int nrows;
  struct PHTM_row *row_ptr;
public:
  PHTM(void) {
    return;
  }
  PHTM(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_EVID(int row) {
    return ((row_ptr+row)->EVID);
  }
  int get_Nsprot(int row) {
    return ((row_ptr+row)->Nsprot);
  }
  int get_Npip(int row) {
    return ((row_ptr+row)->Npip);
  }
  int get_Npim(int row) {
    return ((row_ptr+row)->Npim);
  }
  int get_Nppippim(int row) {
    return ((row_ptr+row)->Nppippim);
  }
  int get_Nppip(int row) {
    return ((row_ptr+row)->Nppip);
  }
  int get_Npippim(int row) {
    return ((row_ptr+row)->Npippim);
  }
  int get_Nppim(int row) {
    return ((row_ptr+row)->Nppim);
  }
  int get_Nkp(int row) {
    return ((row_ptr+row)->Nkp);
  }
  int get_Npkp(int row) {
    return ((row_ptr+row)->Npkp);
  }
  float get_tag_pi_v(int row) {
    return ((row_ptr+row)->tag_pi_v);
  }
};

struct PID1_row {
  int NHBpos_1;
  int NHBneg_1;
  int NTBpos_1;
  int NTBneg_1;
  float chi2pos_1;
  float chi2neg_1;
  int Nunknown_1;
  int Ngamma_1;
  int Nelec_1;
  int Npiplus_1;
  int Npiminus_1;
  int Nprot_1;
  int Nkplus_1;
  int Nkminus_1;
  int Ndeuteron_1;
  int Nneutron_1;
};

class PID1 {
private:
  int nrows;
  struct PID1_row *row_ptr;
public:
  PID1(void) {
    return;
  }
  PID1(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_NHBpos_1(int row) {
    return ((row_ptr+row)->NHBpos_1);
  }
  int get_NHBneg_1(int row) {
    return ((row_ptr+row)->NHBneg_1);
  }
  int get_NTBpos_1(int row) {
    return ((row_ptr+row)->NTBpos_1);
  }
  int get_NTBneg_1(int row) {
    return ((row_ptr+row)->NTBneg_1);
  }
  float get_chi2pos_1(int row) {
    return ((row_ptr+row)->chi2pos_1);
  }
  float get_chi2neg_1(int row) {
    return ((row_ptr+row)->chi2neg_1);
  }
  int get_Nunknown_1(int row) {
    return ((row_ptr+row)->Nunknown_1);
  }
  int get_Ngamma_1(int row) {
    return ((row_ptr+row)->Ngamma_1);
  }
  int get_Nelec_1(int row) {
    return ((row_ptr+row)->Nelec_1);
  }
  int get_Npiplus_1(int row) {
    return ((row_ptr+row)->Npiplus_1);
  }
  int get_Npiminus_1(int row) {
    return ((row_ptr+row)->Npiminus_1);
  }
  int get_Nprot_1(int row) {
    return ((row_ptr+row)->Nprot_1);
  }
  int get_Nkplus_1(int row) {
    return ((row_ptr+row)->Nkplus_1);
  }
  int get_Nkminus_1(int row) {
    return ((row_ptr+row)->Nkminus_1);
  }
  int get_Ndeuteron_1(int row) {
    return ((row_ptr+row)->Ndeuteron_1);
  }
  int get_Nneutron_1(int row) {
    return ((row_ptr+row)->Nneutron_1);
  }
};

struct PID2_row {
  int NHBpos_2;
  int NHBneg_2;
  int NTBpos_2;
  int NTBneg_2;
  float chi2pos_2;
  float chi2neg_2;
  int Nunknown_2;
  int Ngamma_2;
  int Nelec_2;
  int Npiplus_2;
  int Npiminus_2;
  int Nprot_2;
  int Nkplus_2;
  int Nkminus_2;
  int Ndeuteron_2;
  int Nneutron_2;
};

class PID2 {
private:
  int nrows;
  struct PID2_row *row_ptr;
public:
  PID2(void) {
    return;
  }
  PID2(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_NHBpos_2(int row) {
    return ((row_ptr+row)->NHBpos_2);
  }
  int get_NHBneg_2(int row) {
    return ((row_ptr+row)->NHBneg_2);
  }
  int get_NTBpos_2(int row) {
    return ((row_ptr+row)->NTBpos_2);
  }
  int get_NTBneg_2(int row) {
    return ((row_ptr+row)->NTBneg_2);
  }
  float get_chi2pos_2(int row) {
    return ((row_ptr+row)->chi2pos_2);
  }
  float get_chi2neg_2(int row) {
    return ((row_ptr+row)->chi2neg_2);
  }
  int get_Nunknown_2(int row) {
    return ((row_ptr+row)->Nunknown_2);
  }
  int get_Ngamma_2(int row) {
    return ((row_ptr+row)->Ngamma_2);
  }
  int get_Nelec_2(int row) {
    return ((row_ptr+row)->Nelec_2);
  }
  int get_Npiplus_2(int row) {
    return ((row_ptr+row)->Npiplus_2);
  }
  int get_Npiminus_2(int row) {
    return ((row_ptr+row)->Npiminus_2);
  }
  int get_Nprot_2(int row) {
    return ((row_ptr+row)->Nprot_2);
  }
  int get_Nkplus_2(int row) {
    return ((row_ptr+row)->Nkplus_2);
  }
  int get_Nkminus_2(int row) {
    return ((row_ptr+row)->Nkminus_2);
  }
  int get_Ndeuteron_2(int row) {
    return ((row_ptr+row)->Ndeuteron_2);
  }
  int get_Nneutron_2(int row) {
    return ((row_ptr+row)->Nneutron_2);
  }
};

struct PID3_row {
  int NHBpos_3;
  int NHBneg_3;
  int NTBpos_3;
  int NTBneg_3;
  float chi2pos_3;
  float chi2neg_3;
  int Nunknown_3;
  int Ngamma_3;
  int Nelec_3;
  int Npiplus_3;
  int Npiminus_3;
  int Nprot_3;
  int Nkplus_3;
  int Nkminus_3;
  int Ndeuteron_3;
  int Nneutron_3;
};

class PID3 {
private:
  int nrows;
  struct PID3_row *row_ptr;
public:
  PID3(void) {
    return;
  }
  PID3(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_NHBpos_3(int row) {
    return ((row_ptr+row)->NHBpos_3);
  }
  int get_NHBneg_3(int row) {
    return ((row_ptr+row)->NHBneg_3);
  }
  int get_NTBpos_3(int row) {
    return ((row_ptr+row)->NTBpos_3);
  }
  int get_NTBneg_3(int row) {
    return ((row_ptr+row)->NTBneg_3);
  }
  float get_chi2pos_3(int row) {
    return ((row_ptr+row)->chi2pos_3);
  }
  float get_chi2neg_3(int row) {
    return ((row_ptr+row)->chi2neg_3);
  }
  int get_Nunknown_3(int row) {
    return ((row_ptr+row)->Nunknown_3);
  }
  int get_Ngamma_3(int row) {
    return ((row_ptr+row)->Ngamma_3);
  }
  int get_Nelec_3(int row) {
    return ((row_ptr+row)->Nelec_3);
  }
  int get_Npiplus_3(int row) {
    return ((row_ptr+row)->Npiplus_3);
  }
  int get_Npiminus_3(int row) {
    return ((row_ptr+row)->Npiminus_3);
  }
  int get_Nprot_3(int row) {
    return ((row_ptr+row)->Nprot_3);
  }
  int get_Nkplus_3(int row) {
    return ((row_ptr+row)->Nkplus_3);
  }
  int get_Nkminus_3(int row) {
    return ((row_ptr+row)->Nkminus_3);
  }
  int get_Ndeuteron_3(int row) {
    return ((row_ptr+row)->Ndeuteron_3);
  }
  int get_Nneutron_3(int row) {
    return ((row_ptr+row)->Nneutron_3);
  }
};

struct PID4_row {
  int NHBpos_4;
  int NHBneg_4;
  int NTBpos_4;
  int NTBneg_4;
  float chi2pos_4;
  float chi2neg_4;
  int Nunknown_4;
  int Ngamma_4;
  int Nelec_4;
  int Npiplus_4;
  int Npiminus_4;
  int Nprot_4;
  int Nkplus_4;
  int Nkminus_4;
  int Ndeuteron_4;
  int Nneutron_4;
};

class PID4 {
private:
  int nrows;
  struct PID4_row *row_ptr;
public:
  PID4(void) {
    return;
  }
  PID4(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_NHBpos_4(int row) {
    return ((row_ptr+row)->NHBpos_4);
  }
  int get_NHBneg_4(int row) {
    return ((row_ptr+row)->NHBneg_4);
  }
  int get_NTBpos_4(int row) {
    return ((row_ptr+row)->NTBpos_4);
  }
  int get_NTBneg_4(int row) {
    return ((row_ptr+row)->NTBneg_4);
  }
  float get_chi2pos_4(int row) {
    return ((row_ptr+row)->chi2pos_4);
  }
  float get_chi2neg_4(int row) {
    return ((row_ptr+row)->chi2neg_4);
  }
  int get_Nunknown_4(int row) {
    return ((row_ptr+row)->Nunknown_4);
  }
  int get_Ngamma_4(int row) {
    return ((row_ptr+row)->Ngamma_4);
  }
  int get_Nelec_4(int row) {
    return ((row_ptr+row)->Nelec_4);
  }
  int get_Npiplus_4(int row) {
    return ((row_ptr+row)->Npiplus_4);
  }
  int get_Npiminus_4(int row) {
    return ((row_ptr+row)->Npiminus_4);
  }
  int get_Nprot_4(int row) {
    return ((row_ptr+row)->Nprot_4);
  }
  int get_Nkplus_4(int row) {
    return ((row_ptr+row)->Nkplus_4);
  }
  int get_Nkminus_4(int row) {
    return ((row_ptr+row)->Nkminus_4);
  }
  int get_Ndeuteron_4(int row) {
    return ((row_ptr+row)->Ndeuteron_4);
  }
  int get_Nneutron_4(int row) {
    return ((row_ptr+row)->Nneutron_4);
  }
};

struct PID5_row {
  int NHBpos_5;
  int NHBneg_5;
  int NTBpos_5;
  int NTBneg_5;
  float chi2pos_5;
  float chi2neg_5;
  int Nunknown_5;
  int Ngamma_5;
  int Nelec_5;
  int Npiplus_5;
  int Npiminus_5;
  int Nprot_5;
  int Nkplus_5;
  int Nkminus_5;
  int Ndeuteron_5;
  int Nneutron_5;
};

class PID5 {
private:
  int nrows;
  struct PID5_row *row_ptr;
public:
  PID5(void) {
    return;
  }
  PID5(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_NHBpos_5(int row) {
    return ((row_ptr+row)->NHBpos_5);
  }
  int get_NHBneg_5(int row) {
    return ((row_ptr+row)->NHBneg_5);
  }
  int get_NTBpos_5(int row) {
    return ((row_ptr+row)->NTBpos_5);
  }
  int get_NTBneg_5(int row) {
    return ((row_ptr+row)->NTBneg_5);
  }
  float get_chi2pos_5(int row) {
    return ((row_ptr+row)->chi2pos_5);
  }
  float get_chi2neg_5(int row) {
    return ((row_ptr+row)->chi2neg_5);
  }
  int get_Nunknown_5(int row) {
    return ((row_ptr+row)->Nunknown_5);
  }
  int get_Ngamma_5(int row) {
    return ((row_ptr+row)->Ngamma_5);
  }
  int get_Nelec_5(int row) {
    return ((row_ptr+row)->Nelec_5);
  }
  int get_Npiplus_5(int row) {
    return ((row_ptr+row)->Npiplus_5);
  }
  int get_Npiminus_5(int row) {
    return ((row_ptr+row)->Npiminus_5);
  }
  int get_Nprot_5(int row) {
    return ((row_ptr+row)->Nprot_5);
  }
  int get_Nkplus_5(int row) {
    return ((row_ptr+row)->Nkplus_5);
  }
  int get_Nkminus_5(int row) {
    return ((row_ptr+row)->Nkminus_5);
  }
  int get_Ndeuteron_5(int row) {
    return ((row_ptr+row)->Ndeuteron_5);
  }
  int get_Nneutron_5(int row) {
    return ((row_ptr+row)->Nneutron_5);
  }
};

struct PID6_row {
  int NHBpos_6;
  int NHBneg_6;
  int NTBpos_6;
  int NTBneg_6;
  float chi2pos_6;
  float chi2neg_6;
  int Nunknown_6;
  int Ngamma_6;
  int Nelec_6;
  int Npiplus_6;
  int Npiminus_6;
  int Nprot_6;
  int Nkplus_6;
  int Nkminus_6;
  int Ndeuteron_6;
  int Nneutron_6;
};

class PID6 {
private:
  int nrows;
  struct PID6_row *row_ptr;
public:
  PID6(void) {
    return;
  }
  PID6(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_NHBpos_6(int row) {
    return ((row_ptr+row)->NHBpos_6);
  }
  int get_NHBneg_6(int row) {
    return ((row_ptr+row)->NHBneg_6);
  }
  int get_NTBpos_6(int row) {
    return ((row_ptr+row)->NTBpos_6);
  }
  int get_NTBneg_6(int row) {
    return ((row_ptr+row)->NTBneg_6);
  }
  float get_chi2pos_6(int row) {
    return ((row_ptr+row)->chi2pos_6);
  }
  float get_chi2neg_6(int row) {
    return ((row_ptr+row)->chi2neg_6);
  }
  int get_Nunknown_6(int row) {
    return ((row_ptr+row)->Nunknown_6);
  }
  int get_Ngamma_6(int row) {
    return ((row_ptr+row)->Ngamma_6);
  }
  int get_Nelec_6(int row) {
    return ((row_ptr+row)->Nelec_6);
  }
  int get_Npiplus_6(int row) {
    return ((row_ptr+row)->Npiplus_6);
  }
  int get_Npiminus_6(int row) {
    return ((row_ptr+row)->Npiminus_6);
  }
  int get_Nprot_6(int row) {
    return ((row_ptr+row)->Nprot_6);
  }
  int get_Nkplus_6(int row) {
    return ((row_ptr+row)->Nkplus_6);
  }
  int get_Nkminus_6(int row) {
    return ((row_ptr+row)->Nkminus_6);
  }
  int get_Ndeuteron_6(int row) {
    return ((row_ptr+row)->Ndeuteron_6);
  }
  int get_Nneutron_6(int row) {
    return ((row_ptr+row)->Nneutron_6);
  }
};

struct PIDT_row {
  int Nunknown;
  int Ngamma;
  int Nelec;
  int Npiplus;
  int Npiminus;
  int Nprot;
  int Nkplus;
  int Nkminus;
  int Ndeuteron;
  int Nneutron;
};

class PIDT {
private:
  int nrows;
  struct PIDT_row *row_ptr;
public:
  PIDT(void) {
    return;
  }
  PIDT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_Nunknown(int row) {
    return ((row_ptr+row)->Nunknown);
  }
  int get_Ngamma(int row) {
    return ((row_ptr+row)->Ngamma);
  }
  int get_Nelec(int row) {
    return ((row_ptr+row)->Nelec);
  }
  int get_Npiplus(int row) {
    return ((row_ptr+row)->Npiplus);
  }
  int get_Npiminus(int row) {
    return ((row_ptr+row)->Npiminus);
  }
  int get_Nprot(int row) {
    return ((row_ptr+row)->Nprot);
  }
  int get_Nkplus(int row) {
    return ((row_ptr+row)->Nkplus);
  }
  int get_Nkminus(int row) {
    return ((row_ptr+row)->Nkminus);
  }
  int get_Ndeuteron(int row) {
    return ((row_ptr+row)->Ndeuteron);
  }
  int get_Nneutron(int row) {
    return ((row_ptr+row)->Nneutron);
  }
};

struct PRTM_row {
  int time;
};

class PRTM {
private:
  int nrows;
  struct PRTM_row *row_ptr;
public:
  PRTM(void) {
    return;
  }
  PRTM(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_time(int row) {
    return ((row_ptr+row)->time);
  }
};

struct PSO_row {
  int ID;
  float TIME;
  float ENER;
  int TID;
};

class PSO {
private:
  int nrows;
  struct PSO_row *row_ptr;
public:
  PSO(void) {
    return;
  }
  PSO(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  float get_TIME(int row) {
    return ((row_ptr+row)->TIME);
  }
  float get_ENER(int row) {
    return ((row_ptr+row)->ENER);
  }
  int get_TID(int row) {
    return ((row_ptr+row)->TID);
  }
};

struct PTDB_row {
  int PBeam;
  int PB_DATE;
  int TTYPE;
  int B_TARG;
  int PTarg;
  int PT_time;
  int HE_Level;
  int EIOF;
  int TTempH;
  int TTempC;
  int AnealT;
};

class PTDB {
private:
  int nrows;
  struct PTDB_row *row_ptr;
public:
  PTDB(void) {
    return;
  }
  PTDB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_PBeam(int row) {
    return ((row_ptr+row)->PBeam);
  }
  int get_PB_DATE(int row) {
    return ((row_ptr+row)->PB_DATE);
  }
  int get_TTYPE(int row) {
    return ((row_ptr+row)->TTYPE);
  }
  int get_B_TARG(int row) {
    return ((row_ptr+row)->B_TARG);
  }
  int get_PTarg(int row) {
    return ((row_ptr+row)->PTarg);
  }
  int get_PT_time(int row) {
    return ((row_ptr+row)->PT_time);
  }
  int get_HE_Level(int row) {
    return ((row_ptr+row)->HE_Level);
  }
  int get_EIOF(int row) {
    return ((row_ptr+row)->EIOF);
  }
  int get_TTempH(int row) {
    return ((row_ptr+row)->TTempH);
  }
  int get_TTempC(int row) {
    return ((row_ptr+row)->TTempC);
  }
  int get_AnealT(int row) {
    return ((row_ptr+row)->AnealT);
  }
};

struct RCST_row {
  int down_count;
  int prestart_count;
  int go_count;
  int trig_count;
  int event_count;
  int sync_count;
  int run_trig_count;
  int run_event_count;
  int run_sync_count;
  int pause_count;
  int end_count;
  int illegal_count;
  int run_illegal_count;
  int phys_sync_count;
  int run_phys_sync_count;
};

class RCST {
private:
  int nrows;
  struct RCST_row *row_ptr;
public:
  RCST(void) {
    return;
  }
  RCST(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_down_count(int row) {
    return ((row_ptr+row)->down_count);
  }
  int get_prestart_count(int row) {
    return ((row_ptr+row)->prestart_count);
  }
  int get_go_count(int row) {
    return ((row_ptr+row)->go_count);
  }
  int get_trig_count(int row) {
    return ((row_ptr+row)->trig_count);
  }
  int get_event_count(int row) {
    return ((row_ptr+row)->event_count);
  }
  int get_sync_count(int row) {
    return ((row_ptr+row)->sync_count);
  }
  int get_run_trig_count(int row) {
    return ((row_ptr+row)->run_trig_count);
  }
  int get_run_event_count(int row) {
    return ((row_ptr+row)->run_event_count);
  }
  int get_run_sync_count(int row) {
    return ((row_ptr+row)->run_sync_count);
  }
  int get_pause_count(int row) {
    return ((row_ptr+row)->pause_count);
  }
  int get_end_count(int row) {
    return ((row_ptr+row)->end_count);
  }
  int get_illegal_count(int row) {
    return ((row_ptr+row)->illegal_count);
  }
  int get_run_illegal_count(int row) {
    return ((row_ptr+row)->run_illegal_count);
  }
  int get_phys_sync_count(int row) {
    return ((row_ptr+row)->phys_sync_count);
  }
  int get_run_phys_sync_count(int row) {
    return ((row_ptr+row)->run_phys_sync_count);
  }
};

struct REF_row {
  short ID;
  short TDC;
};

class REF {
private:
  int nrows;
  struct REF_row *row_ptr;
public:
  REF(void) {
    return;
  }
  REF(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct RF_row {
  float RF;
  float RF1;
  float RF2;
};

class RF {
private:
  int nrows;
  struct RF_row *row_ptr;
public:
  RF(void) {
    return;
  }
  RF(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_RF(int row) {
    return ((row_ptr+row)->RF);
  }
  float get_RF1(int row) {
    return ((row_ptr+row)->RF1);
  }
  float get_RF2(int row) {
    return ((row_ptr+row)->RF2);
  }
};

struct RFT_row {
  short ID;
  short TDC;
};

class RFT {
private:
  int nrows;
  struct RFT_row *row_ptr;
public:
  RFT(void) {
    return;
  }
  RFT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct RGLK_row {
  int IREGION;
  float X;
  float Y;
  float Z;
  float THETA0;
  float PHI0;
  float RTHETA;
  float RPHI;
  float CHI2;
  int STATUS;
};

class RGLK {
private:
  int nrows;
  struct RGLK_row *row_ptr;
public:
  RGLK(void) {
    return;
  }
  RGLK(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_IREGION(int row) {
    return ((row_ptr+row)->IREGION);
  }
  float get_X(int row) {
    return ((row_ptr+row)->X);
  }
  float get_Y(int row) {
    return ((row_ptr+row)->Y);
  }
  float get_Z(int row) {
    return ((row_ptr+row)->Z);
  }
  float get_THETA0(int row) {
    return ((row_ptr+row)->THETA0);
  }
  float get_PHI0(int row) {
    return ((row_ptr+row)->PHI0);
  }
  float get_RTHETA(int row) {
    return ((row_ptr+row)->RTHETA);
  }
  float get_RPHI(int row) {
    return ((row_ptr+row)->RPHI);
  }
  float get_CHI2(int row) {
    return ((row_ptr+row)->CHI2);
  }
  int get_STATUS(int row) {
    return ((row_ptr+row)->STATUS);
  }
};

struct RNLG_row {
  char sql[4];
};

class RNLG {
private:
  int nrows;
  struct RNLG_row *row_ptr;
public:
  RNLG(void) {
    return;
  }
  RNLG(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  char *get_sql(int row) {
    return ((row_ptr+row)->sql);
  }
};

struct RNPE_row {
  int run;
  char bank[4];
};

class RNPE {
private:
  int nrows;
  struct RNPE_row *row_ptr;
public:
  RNPE(void) {
    return;
  }
  RNPE(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_run(int row) {
    return ((row_ptr+row)->run);
  }
  char *get_bank(int row) {
    return ((row_ptr+row)->bank);
  }
};

struct RTSL_row {
  int RAWT1;
  int RAWT2;
  int RAWT3;
  int RAWT4;
  int RAWT5;
  int RAWT6;
  int RAWT7;
  int RAWT8;
  int RAWT9;
  int RAWT10;
  int RAWT11;
  int RAWT12;
  int RAWT13;
  int RAWT14;
  int RAWT15;
  int RAWT16;
  int RAWT17;
  int RAWT18;
  int RAWT19;
  int RAWT20;
  int RAWT21;
  int RAWT22;
  int RAWT23;
  int RAWT24;
  int RAWT25;
  int RAWT26;
  int RAWT27;
  int RAWT28;
  int RAWT29;
  int RAWT30;
  int RAWT31;
  int RAWT32;
  int RAWT33;
  int RAWT34;
  int RAWT35;
  int RAWT36;
  int RAWT37;
  int RAWT38;
  int RAWT39;
  int RAWT40;
  int RAWT41;
  int RAWT42;
  int RAWT43;
  int RAWT44;
  int RAWT45;
  int RAWT46;
  int RAWT47;
  int RAWT48;
  int RAWT49;
  int RAWT50;
  int RAWT51;
  int RAWT52;
  int RAWT53;
  int RAWT54;
  int RAWT55;
  int RAWT56;
  int RAWT57;
  int RAWT58;
  int RAWT59;
  int RAWT60;
  int RAWT61;
  int RAWT62;
  int RAWT63;
  int RAWT64;
};

class RTSL {
private:
  int nrows;
  struct RTSL_row *row_ptr;
public:
  RTSL(void) {
    return;
  }
  RTSL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_RAWT1(int row) {
    return ((row_ptr+row)->RAWT1);
  }
  int get_RAWT2(int row) {
    return ((row_ptr+row)->RAWT2);
  }
  int get_RAWT3(int row) {
    return ((row_ptr+row)->RAWT3);
  }
  int get_RAWT4(int row) {
    return ((row_ptr+row)->RAWT4);
  }
  int get_RAWT5(int row) {
    return ((row_ptr+row)->RAWT5);
  }
  int get_RAWT6(int row) {
    return ((row_ptr+row)->RAWT6);
  }
  int get_RAWT7(int row) {
    return ((row_ptr+row)->RAWT7);
  }
  int get_RAWT8(int row) {
    return ((row_ptr+row)->RAWT8);
  }
  int get_RAWT9(int row) {
    return ((row_ptr+row)->RAWT9);
  }
  int get_RAWT10(int row) {
    return ((row_ptr+row)->RAWT10);
  }
  int get_RAWT11(int row) {
    return ((row_ptr+row)->RAWT11);
  }
  int get_RAWT12(int row) {
    return ((row_ptr+row)->RAWT12);
  }
  int get_RAWT13(int row) {
    return ((row_ptr+row)->RAWT13);
  }
  int get_RAWT14(int row) {
    return ((row_ptr+row)->RAWT14);
  }
  int get_RAWT15(int row) {
    return ((row_ptr+row)->RAWT15);
  }
  int get_RAWT16(int row) {
    return ((row_ptr+row)->RAWT16);
  }
  int get_RAWT17(int row) {
    return ((row_ptr+row)->RAWT17);
  }
  int get_RAWT18(int row) {
    return ((row_ptr+row)->RAWT18);
  }
  int get_RAWT19(int row) {
    return ((row_ptr+row)->RAWT19);
  }
  int get_RAWT20(int row) {
    return ((row_ptr+row)->RAWT20);
  }
  int get_RAWT21(int row) {
    return ((row_ptr+row)->RAWT21);
  }
  int get_RAWT22(int row) {
    return ((row_ptr+row)->RAWT22);
  }
  int get_RAWT23(int row) {
    return ((row_ptr+row)->RAWT23);
  }
  int get_RAWT24(int row) {
    return ((row_ptr+row)->RAWT24);
  }
  int get_RAWT25(int row) {
    return ((row_ptr+row)->RAWT25);
  }
  int get_RAWT26(int row) {
    return ((row_ptr+row)->RAWT26);
  }
  int get_RAWT27(int row) {
    return ((row_ptr+row)->RAWT27);
  }
  int get_RAWT28(int row) {
    return ((row_ptr+row)->RAWT28);
  }
  int get_RAWT29(int row) {
    return ((row_ptr+row)->RAWT29);
  }
  int get_RAWT30(int row) {
    return ((row_ptr+row)->RAWT30);
  }
  int get_RAWT31(int row) {
    return ((row_ptr+row)->RAWT31);
  }
  int get_RAWT32(int row) {
    return ((row_ptr+row)->RAWT32);
  }
  int get_RAWT33(int row) {
    return ((row_ptr+row)->RAWT33);
  }
  int get_RAWT34(int row) {
    return ((row_ptr+row)->RAWT34);
  }
  int get_RAWT35(int row) {
    return ((row_ptr+row)->RAWT35);
  }
  int get_RAWT36(int row) {
    return ((row_ptr+row)->RAWT36);
  }
  int get_RAWT37(int row) {
    return ((row_ptr+row)->RAWT37);
  }
  int get_RAWT38(int row) {
    return ((row_ptr+row)->RAWT38);
  }
  int get_RAWT39(int row) {
    return ((row_ptr+row)->RAWT39);
  }
  int get_RAWT40(int row) {
    return ((row_ptr+row)->RAWT40);
  }
  int get_RAWT41(int row) {
    return ((row_ptr+row)->RAWT41);
  }
  int get_RAWT42(int row) {
    return ((row_ptr+row)->RAWT42);
  }
  int get_RAWT43(int row) {
    return ((row_ptr+row)->RAWT43);
  }
  int get_RAWT44(int row) {
    return ((row_ptr+row)->RAWT44);
  }
  int get_RAWT45(int row) {
    return ((row_ptr+row)->RAWT45);
  }
  int get_RAWT46(int row) {
    return ((row_ptr+row)->RAWT46);
  }
  int get_RAWT47(int row) {
    return ((row_ptr+row)->RAWT47);
  }
  int get_RAWT48(int row) {
    return ((row_ptr+row)->RAWT48);
  }
  int get_RAWT49(int row) {
    return ((row_ptr+row)->RAWT49);
  }
  int get_RAWT50(int row) {
    return ((row_ptr+row)->RAWT50);
  }
  int get_RAWT51(int row) {
    return ((row_ptr+row)->RAWT51);
  }
  int get_RAWT52(int row) {
    return ((row_ptr+row)->RAWT52);
  }
  int get_RAWT53(int row) {
    return ((row_ptr+row)->RAWT53);
  }
  int get_RAWT54(int row) {
    return ((row_ptr+row)->RAWT54);
  }
  int get_RAWT55(int row) {
    return ((row_ptr+row)->RAWT55);
  }
  int get_RAWT56(int row) {
    return ((row_ptr+row)->RAWT56);
  }
  int get_RAWT57(int row) {
    return ((row_ptr+row)->RAWT57);
  }
  int get_RAWT58(int row) {
    return ((row_ptr+row)->RAWT58);
  }
  int get_RAWT59(int row) {
    return ((row_ptr+row)->RAWT59);
  }
  int get_RAWT60(int row) {
    return ((row_ptr+row)->RAWT60);
  }
  int get_RAWT61(int row) {
    return ((row_ptr+row)->RAWT61);
  }
  int get_RAWT62(int row) {
    return ((row_ptr+row)->RAWT62);
  }
  int get_RAWT63(int row) {
    return ((row_ptr+row)->RAWT63);
  }
  int get_RAWT64(int row) {
    return ((row_ptr+row)->RAWT64);
  }
};

struct RUNC_row {
  int runno;
  float beam_e;
  int b_first;
  float q_live;
  int ql_first;
  float q_all;
  int qa_first;
  float tor_curr;
  int t_first;
  float mtor_curr;
  int mt_first;
  float tag_curr;
  int tag_first;
};

class RUNC {
private:
  int nrows;
  struct RUNC_row *row_ptr;
public:
  RUNC(void) {
    return;
  }
  RUNC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_runno(int row) {
    return ((row_ptr+row)->runno);
  }
  float get_beam_e(int row) {
    return ((row_ptr+row)->beam_e);
  }
  int get_b_first(int row) {
    return ((row_ptr+row)->b_first);
  }
  float get_q_live(int row) {
    return ((row_ptr+row)->q_live);
  }
  int get_ql_first(int row) {
    return ((row_ptr+row)->ql_first);
  }
  float get_q_all(int row) {
    return ((row_ptr+row)->q_all);
  }
  int get_qa_first(int row) {
    return ((row_ptr+row)->qa_first);
  }
  float get_tor_curr(int row) {
    return ((row_ptr+row)->tor_curr);
  }
  int get_t_first(int row) {
    return ((row_ptr+row)->t_first);
  }
  float get_mtor_curr(int row) {
    return ((row_ptr+row)->mtor_curr);
  }
  int get_mt_first(int row) {
    return ((row_ptr+row)->mt_first);
  }
  float get_tag_curr(int row) {
    return ((row_ptr+row)->tag_curr);
  }
  int get_tag_first(int row) {
    return ((row_ptr+row)->tag_first);
  }
};

struct S1ST_row {
  int latch1_bit1_count;
  int latch1_bit2_count;
  int latch1_bit3_count;
  int latch1_bit4_count;
  int latch1_bit5_count;
  int latch1_bit6_count;
  int latch1_bit7_count;
  int latch1_bit8_count;
  int latch1_bit9_count;
  int latch1_bit10_count;
  int latch1_bit11_count;
  int latch1_bit12_count;
  int event_count;
  int latch1_zero_count;
  int latch1_empty_count;
  int latch1_not_empty_count;
  int latch1_ok_count;
  int level2_sector1;
  int level2_sector2;
  int level2_sector3;
  int level2_sector4;
  int level2_sector5;
  int level2_sector6;
  int level2_pass;
  int level2_fail;
  int latch2_zero_count;
  int latch2_empty_count;
  int latch2_not_empty_count;
  int latch2_ok_count;
  int roc_13_count;
  int roc_15_count;
  int l1l2_zero_count;
  int l1zero_13_count;
  int l2zero_13_count;
  int l1l2zero_13_count;
};

class S1ST {
private:
  int nrows;
  struct S1ST_row *row_ptr;
public:
  S1ST(void) {
    return;
  }
  S1ST(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_latch1_bit1_count(int row) {
    return ((row_ptr+row)->latch1_bit1_count);
  }
  int get_latch1_bit2_count(int row) {
    return ((row_ptr+row)->latch1_bit2_count);
  }
  int get_latch1_bit3_count(int row) {
    return ((row_ptr+row)->latch1_bit3_count);
  }
  int get_latch1_bit4_count(int row) {
    return ((row_ptr+row)->latch1_bit4_count);
  }
  int get_latch1_bit5_count(int row) {
    return ((row_ptr+row)->latch1_bit5_count);
  }
  int get_latch1_bit6_count(int row) {
    return ((row_ptr+row)->latch1_bit6_count);
  }
  int get_latch1_bit7_count(int row) {
    return ((row_ptr+row)->latch1_bit7_count);
  }
  int get_latch1_bit8_count(int row) {
    return ((row_ptr+row)->latch1_bit8_count);
  }
  int get_latch1_bit9_count(int row) {
    return ((row_ptr+row)->latch1_bit9_count);
  }
  int get_latch1_bit10_count(int row) {
    return ((row_ptr+row)->latch1_bit10_count);
  }
  int get_latch1_bit11_count(int row) {
    return ((row_ptr+row)->latch1_bit11_count);
  }
  int get_latch1_bit12_count(int row) {
    return ((row_ptr+row)->latch1_bit12_count);
  }
  int get_event_count(int row) {
    return ((row_ptr+row)->event_count);
  }
  int get_latch1_zero_count(int row) {
    return ((row_ptr+row)->latch1_zero_count);
  }
  int get_latch1_empty_count(int row) {
    return ((row_ptr+row)->latch1_empty_count);
  }
  int get_latch1_not_empty_count(int row) {
    return ((row_ptr+row)->latch1_not_empty_count);
  }
  int get_latch1_ok_count(int row) {
    return ((row_ptr+row)->latch1_ok_count);
  }
  int get_level2_sector1(int row) {
    return ((row_ptr+row)->level2_sector1);
  }
  int get_level2_sector2(int row) {
    return ((row_ptr+row)->level2_sector2);
  }
  int get_level2_sector3(int row) {
    return ((row_ptr+row)->level2_sector3);
  }
  int get_level2_sector4(int row) {
    return ((row_ptr+row)->level2_sector4);
  }
  int get_level2_sector5(int row) {
    return ((row_ptr+row)->level2_sector5);
  }
  int get_level2_sector6(int row) {
    return ((row_ptr+row)->level2_sector6);
  }
  int get_level2_pass(int row) {
    return ((row_ptr+row)->level2_pass);
  }
  int get_level2_fail(int row) {
    return ((row_ptr+row)->level2_fail);
  }
  int get_latch2_zero_count(int row) {
    return ((row_ptr+row)->latch2_zero_count);
  }
  int get_latch2_empty_count(int row) {
    return ((row_ptr+row)->latch2_empty_count);
  }
  int get_latch2_not_empty_count(int row) {
    return ((row_ptr+row)->latch2_not_empty_count);
  }
  int get_latch2_ok_count(int row) {
    return ((row_ptr+row)->latch2_ok_count);
  }
  int get_roc_13_count(int row) {
    return ((row_ptr+row)->roc_13_count);
  }
  int get_roc_15_count(int row) {
    return ((row_ptr+row)->roc_15_count);
  }
  int get_l1l2_zero_count(int row) {
    return ((row_ptr+row)->l1l2_zero_count);
  }
  int get_l1zero_13_count(int row) {
    return ((row_ptr+row)->l1zero_13_count);
  }
  int get_l2zero_13_count(int row) {
    return ((row_ptr+row)->l2zero_13_count);
  }
  int get_l1l2zero_13_count(int row) {
    return ((row_ptr+row)->l1l2zero_13_count);
  }
};

struct SC1_row {
  int ID;
  float time_l;
  float energy_l;
  float time_r;
  float energy_r;
  float dtime_l;
  float denergy_l;
  float dtime_r;
  float denergy_r;
};

class SC1 {
private:
  int nrows;
  struct SC1_row *row_ptr;
public:
  SC1(void) {
    return;
  }
  SC1(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  float get_time_l(int row) {
    return ((row_ptr+row)->time_l);
  }
  float get_energy_l(int row) {
    return ((row_ptr+row)->energy_l);
  }
  float get_time_r(int row) {
    return ((row_ptr+row)->time_r);
  }
  float get_energy_r(int row) {
    return ((row_ptr+row)->energy_r);
  }
  float get_dtime_l(int row) {
    return ((row_ptr+row)->dtime_l);
  }
  float get_denergy_l(int row) {
    return ((row_ptr+row)->denergy_l);
  }
  float get_dtime_r(int row) {
    return ((row_ptr+row)->dtime_r);
  }
  float get_denergy_r(int row) {
    return ((row_ptr+row)->denergy_r);
  }
};

struct SCC_row {
  int id;
  int date;
  int version;
  int status;
  float TD0L;
  float TD0Lu;
  float TD0R;
  float TD0Ru;
  float TD1L;
  float TD1Lu;
  float TD1R;
  float TD1Ru;
  float TD2L;
  float TD2Lu;
  float TD2R;
  float TD2Ru;
  float TW0L;
  float TW0Lu;
  float TW0R;
  float TW0Ru;
  float TW1L;
  float TW1Lu;
  float TW1R;
  float TW1Ru;
  float TW2L;
  float TW2Lu;
  float TW2R;
  float TW2Ru;
  float ADPL;
  float ADPLu;
  float ADPR;
  float ADPRu;
  float M0L;
  float M0Lu;
  float M0R;
  float M0Ru;
  float VEFL;
  float VEFLu;
  float VEFR;
  float VEFRu;
  float ATNL;
  float ATNLu;
  float ATNR;
  float ATNRu;
  float TSIG0L;
  float TSIG0R;
  float TSIG1L;
  float TSIG1R;
};

class SCC {
private:
  int nrows;
  struct SCC_row *row_ptr;
public:
  SCC(void) {
    return;
  }
  SCC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  int get_date(int row) {
    return ((row_ptr+row)->date);
  }
  int get_version(int row) {
    return ((row_ptr+row)->version);
  }
  int get_status(int row) {
    return ((row_ptr+row)->status);
  }
  float get_TD0L(int row) {
    return ((row_ptr+row)->TD0L);
  }
  float get_TD0Lu(int row) {
    return ((row_ptr+row)->TD0Lu);
  }
  float get_TD0R(int row) {
    return ((row_ptr+row)->TD0R);
  }
  float get_TD0Ru(int row) {
    return ((row_ptr+row)->TD0Ru);
  }
  float get_TD1L(int row) {
    return ((row_ptr+row)->TD1L);
  }
  float get_TD1Lu(int row) {
    return ((row_ptr+row)->TD1Lu);
  }
  float get_TD1R(int row) {
    return ((row_ptr+row)->TD1R);
  }
  float get_TD1Ru(int row) {
    return ((row_ptr+row)->TD1Ru);
  }
  float get_TD2L(int row) {
    return ((row_ptr+row)->TD2L);
  }
  float get_TD2Lu(int row) {
    return ((row_ptr+row)->TD2Lu);
  }
  float get_TD2R(int row) {
    return ((row_ptr+row)->TD2R);
  }
  float get_TD2Ru(int row) {
    return ((row_ptr+row)->TD2Ru);
  }
  float get_TW0L(int row) {
    return ((row_ptr+row)->TW0L);
  }
  float get_TW0Lu(int row) {
    return ((row_ptr+row)->TW0Lu);
  }
  float get_TW0R(int row) {
    return ((row_ptr+row)->TW0R);
  }
  float get_TW0Ru(int row) {
    return ((row_ptr+row)->TW0Ru);
  }
  float get_TW1L(int row) {
    return ((row_ptr+row)->TW1L);
  }
  float get_TW1Lu(int row) {
    return ((row_ptr+row)->TW1Lu);
  }
  float get_TW1R(int row) {
    return ((row_ptr+row)->TW1R);
  }
  float get_TW1Ru(int row) {
    return ((row_ptr+row)->TW1Ru);
  }
  float get_TW2L(int row) {
    return ((row_ptr+row)->TW2L);
  }
  float get_TW2Lu(int row) {
    return ((row_ptr+row)->TW2Lu);
  }
  float get_TW2R(int row) {
    return ((row_ptr+row)->TW2R);
  }
  float get_TW2Ru(int row) {
    return ((row_ptr+row)->TW2Ru);
  }
  float get_ADPL(int row) {
    return ((row_ptr+row)->ADPL);
  }
  float get_ADPLu(int row) {
    return ((row_ptr+row)->ADPLu);
  }
  float get_ADPR(int row) {
    return ((row_ptr+row)->ADPR);
  }
  float get_ADPRu(int row) {
    return ((row_ptr+row)->ADPRu);
  }
  float get_M0L(int row) {
    return ((row_ptr+row)->M0L);
  }
  float get_M0Lu(int row) {
    return ((row_ptr+row)->M0Lu);
  }
  float get_M0R(int row) {
    return ((row_ptr+row)->M0R);
  }
  float get_M0Ru(int row) {
    return ((row_ptr+row)->M0Ru);
  }
  float get_VEFL(int row) {
    return ((row_ptr+row)->VEFL);
  }
  float get_VEFLu(int row) {
    return ((row_ptr+row)->VEFLu);
  }
  float get_VEFR(int row) {
    return ((row_ptr+row)->VEFR);
  }
  float get_VEFRu(int row) {
    return ((row_ptr+row)->VEFRu);
  }
  float get_ATNL(int row) {
    return ((row_ptr+row)->ATNL);
  }
  float get_ATNLu(int row) {
    return ((row_ptr+row)->ATNLu);
  }
  float get_ATNR(int row) {
    return ((row_ptr+row)->ATNR);
  }
  float get_ATNRu(int row) {
    return ((row_ptr+row)->ATNRu);
  }
  float get_TSIG0L(int row) {
    return ((row_ptr+row)->TSIG0L);
  }
  float get_TSIG0R(int row) {
    return ((row_ptr+row)->TSIG0R);
  }
  float get_TSIG1L(int row) {
    return ((row_ptr+row)->TSIG1L);
  }
  float get_TSIG1R(int row) {
    return ((row_ptr+row)->TSIG1R);
  }
};

struct SC_row {
  short ID;
  short TDCL;
  short ADCL;
  short TDCR;
  short ADCR;
};

class SC {
private:
  int nrows;
  struct SC_row *row_ptr;
public:
  SC(void) {
    return;
  }
  SC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDCL(int row) {
    return ((row_ptr+row)->TDCL);
  }
  short get_ADCL(int row) {
    return ((row_ptr+row)->ADCL);
  }
  short get_TDCR(int row) {
    return ((row_ptr+row)->TDCR);
  }
  short get_ADCR(int row) {
    return ((row_ptr+row)->ADCR);
  }
};

struct SCDI_row {
  int crate;
  int slot;
  int mask;
  int threshold;
  int width;
};

class SCDI {
private:
  int nrows;
  struct SCDI_row *row_ptr;
public:
  SCDI(void) {
    return;
  }
  SCDI(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_crate(int row) {
    return ((row_ptr+row)->crate);
  }
  int get_slot(int row) {
    return ((row_ptr+row)->slot);
  }
  int get_mask(int row) {
    return ((row_ptr+row)->mask);
  }
  int get_threshold(int row) {
    return ((row_ptr+row)->threshold);
  }
  int get_width(int row) {
    return ((row_ptr+row)->width);
  }
};

struct SCGD_row {
  int ID;
  float NORM_Z;
  float NORM_X;
  float NORM_D;
  float ALON_Z;
  float ALON_X;
  float BEG_PD;
  float END_PD;
  float PDL_SH;
  float R_BEAM;
};

class SCGD {
private:
  int nrows;
  struct SCGD_row *row_ptr;
public:
  SCGD(void) {
    return;
  }
  SCGD(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  float get_NORM_Z(int row) {
    return ((row_ptr+row)->NORM_Z);
  }
  float get_NORM_X(int row) {
    return ((row_ptr+row)->NORM_X);
  }
  float get_NORM_D(int row) {
    return ((row_ptr+row)->NORM_D);
  }
  float get_ALON_Z(int row) {
    return ((row_ptr+row)->ALON_Z);
  }
  float get_ALON_X(int row) {
    return ((row_ptr+row)->ALON_X);
  }
  float get_BEG_PD(int row) {
    return ((row_ptr+row)->BEG_PD);
  }
  float get_END_PD(int row) {
    return ((row_ptr+row)->END_PD);
  }
  float get_PDL_SH(int row) {
    return ((row_ptr+row)->PDL_SH);
  }
  float get_R_BEAM(int row) {
    return ((row_ptr+row)->R_BEAM);
  }
};

struct SCG_row {
  int id;
  int panel;
  float Xccw;
  float Yccw;
  float Zccw;
  float Xcw;
  float Ycw;
  float Zcw;
  float WIDTH;
  float THICK;
  float DELTA;
};

class SCG {
private:
  int nrows;
  struct SCG_row *row_ptr;
public:
  SCG(void) {
    return;
  }
  SCG(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  int get_panel(int row) {
    return ((row_ptr+row)->panel);
  }
  float get_Xccw(int row) {
    return ((row_ptr+row)->Xccw);
  }
  float get_Yccw(int row) {
    return ((row_ptr+row)->Yccw);
  }
  float get_Zccw(int row) {
    return ((row_ptr+row)->Zccw);
  }
  float get_Xcw(int row) {
    return ((row_ptr+row)->Xcw);
  }
  float get_Ycw(int row) {
    return ((row_ptr+row)->Ycw);
  }
  float get_Zcw(int row) {
    return ((row_ptr+row)->Zcw);
  }
  float get_WIDTH(int row) {
    return ((row_ptr+row)->WIDTH);
  }
  float get_THICK(int row) {
    return ((row_ptr+row)->THICK);
  }
  float get_DELTA(int row) {
    return ((row_ptr+row)->DELTA);
  }
};

struct SCH_row {
  float x;
  float y;
  float z;
  float cx;
  float cy;
  float cz;
  float pmom;
  int track;
  int id;
};

class SCH {
private:
  int nrows;
  struct SCH_row *row_ptr;
public:
  SCH(void) {
    return;
  }
  SCH(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_cx(int row) {
    return ((row_ptr+row)->cx);
  }
  float get_cy(int row) {
    return ((row_ptr+row)->cy);
  }
  float get_cz(int row) {
    return ((row_ptr+row)->cz);
  }
  float get_pmom(int row) {
    return ((row_ptr+row)->pmom);
  }
  int get_track(int row) {
    return ((row_ptr+row)->track);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
};

struct SCMD_row {
  int ID;
  int STATUS;
  float X_NORM;
  float Y_NORM;
  float D_NORM;
  float X_PANEL;
  float Y_PANEL;
  float B_PAD;
  float E_PAD;
  float TOF;
  float EDP;
  float P_TIME;
  float P_ATLN;
};

class SCMD {
private:
  int nrows;
  struct SCMD_row *row_ptr;
public:
  SCMD(void) {
    return;
  }
  SCMD(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_STATUS(int row) {
    return ((row_ptr+row)->STATUS);
  }
  float get_X_NORM(int row) {
    return ((row_ptr+row)->X_NORM);
  }
  float get_Y_NORM(int row) {
    return ((row_ptr+row)->Y_NORM);
  }
  float get_D_NORM(int row) {
    return ((row_ptr+row)->D_NORM);
  }
  float get_X_PANEL(int row) {
    return ((row_ptr+row)->X_PANEL);
  }
  float get_Y_PANEL(int row) {
    return ((row_ptr+row)->Y_PANEL);
  }
  float get_B_PAD(int row) {
    return ((row_ptr+row)->B_PAD);
  }
  float get_E_PAD(int row) {
    return ((row_ptr+row)->E_PAD);
  }
  float get_TOF(int row) {
    return ((row_ptr+row)->TOF);
  }
  float get_EDP(int row) {
    return ((row_ptr+row)->EDP);
  }
  float get_P_TIME(int row) {
    return ((row_ptr+row)->P_TIME);
  }
  float get_P_ATLN(int row) {
    return ((row_ptr+row)->P_ATLN);
  }
};

struct SCMT_row {
  int mean_thr;
};

class SCMT {
private:
  int nrows;
  struct SCMT_row *row_ptr;
public:
  SCMT(void) {
    return;
  }
  SCMT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_mean_thr(int row) {
    return ((row_ptr+row)->mean_thr);
  }
};

struct SCMW_row {
  int mean_width;
};

class SCMW {
private:
  int nrows;
  struct SCMW_row *row_ptr;
public:
  SCMW(void) {
    return;
  }
  SCMW(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_mean_width(int row) {
    return ((row_ptr+row)->mean_width);
  }
};

struct SCPB_row {
  int ScPdHt;
  float Edep;
  float Time;
  float Path;
  float Chi2SC;
  int Status;
};

class SCPB {
private:
  int nrows;
  struct SCPB_row *row_ptr;
public:
  SCPB(void) {
    return;
  }
  SCPB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ScPdHt(int row) {
    return ((row_ptr+row)->ScPdHt);
  }
  float get_Edep(int row) {
    return ((row_ptr+row)->Edep);
  }
  float get_Time(int row) {
    return ((row_ptr+row)->Time);
  }
  float get_Path(int row) {
    return ((row_ptr+row)->Path);
  }
  float get_Chi2SC(int row) {
    return ((row_ptr+row)->Chi2SC);
  }
  int get_Status(int row) {
    return ((row_ptr+row)->Status);
  }
};

struct SCP_row {
  float N1x;
  float N1y;
  float N1z;
  float R1n;
  float N2x;
  float N2y;
  float N2z;
  float R2n;
  float N3x;
  float N3y;
  float N3z;
  float R3n;
  float N4x;
  float N4y;
  float N4z;
  float R4n;
};

class SCP {
private:
  int nrows;
  struct SCP_row *row_ptr;
public:
  SCP(void) {
    return;
  }
  SCP(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_N1x(int row) {
    return ((row_ptr+row)->N1x);
  }
  float get_N1y(int row) {
    return ((row_ptr+row)->N1y);
  }
  float get_N1z(int row) {
    return ((row_ptr+row)->N1z);
  }
  float get_R1n(int row) {
    return ((row_ptr+row)->R1n);
  }
  float get_N2x(int row) {
    return ((row_ptr+row)->N2x);
  }
  float get_N2y(int row) {
    return ((row_ptr+row)->N2y);
  }
  float get_N2z(int row) {
    return ((row_ptr+row)->N2z);
  }
  float get_R2n(int row) {
    return ((row_ptr+row)->R2n);
  }
  float get_N3x(int row) {
    return ((row_ptr+row)->N3x);
  }
  float get_N3y(int row) {
    return ((row_ptr+row)->N3y);
  }
  float get_N3z(int row) {
    return ((row_ptr+row)->N3z);
  }
  float get_R3n(int row) {
    return ((row_ptr+row)->R3n);
  }
  float get_N4x(int row) {
    return ((row_ptr+row)->N4x);
  }
  float get_N4y(int row) {
    return ((row_ptr+row)->N4y);
  }
  float get_N4z(int row) {
    return ((row_ptr+row)->N4z);
  }
  float get_R4n(int row) {
    return ((row_ptr+row)->R4n);
  }
};

struct SCPE_row {
  int ID;
  int mean_left;
  float sigma_left;
  int mean_right;
  float sigma_right;
};

class SCPE {
private:
  int nrows;
  struct SCPE_row *row_ptr;
public:
  SCPE(void) {
    return;
  }
  SCPE(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_mean_left(int row) {
    return ((row_ptr+row)->mean_left);
  }
  float get_sigma_left(int row) {
    return ((row_ptr+row)->sigma_left);
  }
  int get_mean_right(int row) {
    return ((row_ptr+row)->mean_right);
  }
  float get_sigma_right(int row) {
    return ((row_ptr+row)->sigma_right);
  }
};

struct SCPS_row {
  int ID;
  int FIRSTPNUM;
  int LASTPNUM;
  float DISTANCE;
  float BEGALONSHFT;
  float ENDALONSHFT;
  float LENGTHSHFT;
  float ALONGIDX;
  float ALONGIDY;
  float ALONGIDZ;
  float SLENGTHX;
  float SLENGTHY;
  float SLENGTHZ;
  float UNORMALX;
  float UNORMALY;
  float UNORMALZ;
};

class SCPS {
private:
  int nrows;
  struct SCPS_row *row_ptr;
public:
  SCPS(void) {
    return;
  }
  SCPS(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_FIRSTPNUM(int row) {
    return ((row_ptr+row)->FIRSTPNUM);
  }
  int get_LASTPNUM(int row) {
    return ((row_ptr+row)->LASTPNUM);
  }
  float get_DISTANCE(int row) {
    return ((row_ptr+row)->DISTANCE);
  }
  float get_BEGALONSHFT(int row) {
    return ((row_ptr+row)->BEGALONSHFT);
  }
  float get_ENDALONSHFT(int row) {
    return ((row_ptr+row)->ENDALONSHFT);
  }
  float get_LENGTHSHFT(int row) {
    return ((row_ptr+row)->LENGTHSHFT);
  }
  float get_ALONGIDX(int row) {
    return ((row_ptr+row)->ALONGIDX);
  }
  float get_ALONGIDY(int row) {
    return ((row_ptr+row)->ALONGIDY);
  }
  float get_ALONGIDZ(int row) {
    return ((row_ptr+row)->ALONGIDZ);
  }
  float get_SLENGTHX(int row) {
    return ((row_ptr+row)->SLENGTHX);
  }
  float get_SLENGTHY(int row) {
    return ((row_ptr+row)->SLENGTHY);
  }
  float get_SLENGTHZ(int row) {
    return ((row_ptr+row)->SLENGTHZ);
  }
  float get_UNORMALX(int row) {
    return ((row_ptr+row)->UNORMALX);
  }
  float get_UNORMALY(int row) {
    return ((row_ptr+row)->UNORMALY);
  }
  float get_UNORMALZ(int row) {
    return ((row_ptr+row)->UNORMALZ);
  }
};

struct SCRC_row {
  int id;
  float energy;
  float denergy;
  float time;
  float dtime;
  float x;
  float y;
  float z;
  float dx;
  float dy;
  float dz;
  int status;
};

class SCRC {
private:
  int nrows;
  struct SCRC_row *row_ptr;
public:
  SCRC(void) {
    return;
  }
  SCRC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  float get_energy(int row) {
    return ((row_ptr+row)->energy);
  }
  float get_denergy(int row) {
    return ((row_ptr+row)->denergy);
  }
  float get_time(int row) {
    return ((row_ptr+row)->time);
  }
  float get_dtime(int row) {
    return ((row_ptr+row)->dtime);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_dx(int row) {
    return ((row_ptr+row)->dx);
  }
  float get_dy(int row) {
    return ((row_ptr+row)->dy);
  }
  float get_dz(int row) {
    return ((row_ptr+row)->dz);
  }
  int get_status(int row) {
    return ((row_ptr+row)->status);
  }
};

struct SCR_row {
  int id;
  float energy;
  float time;
  float x;
  float y;
  float z;
  float dx;
  float dy;
  float dz;
  int status;
  float denergy;
  float dtime;
};

class SCR {
private:
  int nrows;
  struct SCR_row *row_ptr;
public:
  SCR(void) {
    return;
  }
  SCR(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  float get_energy(int row) {
    return ((row_ptr+row)->energy);
  }
  float get_time(int row) {
    return ((row_ptr+row)->time);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_dx(int row) {
    return ((row_ptr+row)->dx);
  }
  float get_dy(int row) {
    return ((row_ptr+row)->dy);
  }
  float get_dz(int row) {
    return ((row_ptr+row)->dz);
  }
  int get_status(int row) {
    return ((row_ptr+row)->status);
  }
  float get_denergy(int row) {
    return ((row_ptr+row)->denergy);
  }
  float get_dtime(int row) {
    return ((row_ptr+row)->dtime);
  }
};

struct SCS_row {
  int SCS1;
  int SCS2;
  int SCS3;
  int SCS4;
  int SCS5;
  int SCS6;
  int SCS7;
  int SCS8;
  int SCS9;
  int SCS10;
  int SCS11;
  int SCS12;
  int SCS13;
  int SCS14;
  int SCS15;
  int SCS16;
  int SCS17;
  int SCS18;
  int SCS19;
  int SCS20;
  int SCS21;
  int SCS22;
  int SCS23;
  int SCS24;
  int SCS25;
  int SCS26;
  int SCS27;
  int SCS28;
  int SCS29;
  int SCS30;
  int SCS31;
  int SCS32;
  int SCS33;
  int SCS34;
  int SCS35;
  int SCS36;
  int SCS37;
  int SCS38;
  int SCS39;
  int SCS40;
  int SCS41;
  int SCS42;
  int SCS43;
  int SCS44;
  int SCS45;
  int SCS46;
  int SCS47;
  int SCS48;
  int SCS49;
  int SCS50;
  int SCS51;
  int SCS52;
  int SCS53;
  int SCS54;
  int SCS55;
  int SCS56;
  int SCS57;
  int SCS58;
  int SCS59;
  int SCS60;
  int SCS61;
  int SCS62;
  int SCS63;
  int SCS64;
  int SCS65;
  int SCS66;
  int SCS67;
  int SCS68;
  int SCS69;
  int SCS70;
  int SCS71;
  int SCS72;
  int SCS73;
  int SCS74;
  int SCS75;
  int SCS76;
  int SCS77;
  int SCS78;
  int SCS79;
  int SCS80;
  int SCS81;
  int SCS82;
  int SCS83;
  int SCS84;
  int SCS85;
  int SCS86;
  int SCS87;
  int SCS88;
  int SCS89;
  int SCS90;
  int SCS91;
  int SCS92;
  int SCS93;
  int SCS94;
  int SCS95;
  int SCS96;
  int SCS97;
  int SCS98;
  int SCS99;
  int SCS100;
  int SCS101;
  int SCS102;
  int SCS103;
  int SCS104;
  int SCS105;
  int SCS106;
  int SCS107;
  int SCS108;
  int SCS109;
  int SCS110;
  int SCS111;
  int SCS112;
  int SCS113;
  int SCS114;
  int SCS115;
  int SCS116;
  int SCS117;
  int SCS118;
  int SCS119;
  int SCS120;
  int SCS121;
  int SCS122;
  int SCS123;
  int SCS124;
  int SCS125;
  int SCS126;
  int SCS127;
  int SCS128;
  int SCS129;
  int SCS130;
  int SCS131;
  int SCS132;
  int SCS133;
  int SCS134;
  int SCS135;
  int SCS136;
  int SCS137;
  int SCS138;
  int SCS139;
  int SCS140;
  int SCS141;
  int SCS142;
  int SCS143;
  int SCS144;
  int SCS145;
  int SCS146;
  int SCS147;
  int SCS148;
  int SCS149;
  int SCS150;
  int SCS151;
  int SCS152;
  int SCS153;
  int SCS154;
  int SCS155;
  int SCS156;
  int SCS157;
  int SCS158;
  int SCS159;
  int SCS160;
  int SCS161;
  int SCS162;
  int SCS163;
  int SCS164;
  int SCS165;
  int SCS166;
  int SCS167;
  int SCS168;
  int SCS169;
  int SCS170;
  int SCS171;
  int SCS172;
  int SCS173;
  int SCS174;
  int SCS175;
  int SCS176;
  int SCS177;
  int SCS178;
  int SCS179;
  int SCS180;
  int SCS181;
  int SCS182;
  int SCS183;
  int SCS184;
  int SCS185;
  int SCS186;
  int SCS187;
  int SCS188;
  int SCS189;
  int SCS190;
  int SCS191;
  int SCS192;
};

class SCS {
private:
  int nrows;
  struct SCS_row *row_ptr;
public:
  SCS(void) {
    return;
  }
  SCS(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_SCS1(int row) {
    return ((row_ptr+row)->SCS1);
  }
  int get_SCS2(int row) {
    return ((row_ptr+row)->SCS2);
  }
  int get_SCS3(int row) {
    return ((row_ptr+row)->SCS3);
  }
  int get_SCS4(int row) {
    return ((row_ptr+row)->SCS4);
  }
  int get_SCS5(int row) {
    return ((row_ptr+row)->SCS5);
  }
  int get_SCS6(int row) {
    return ((row_ptr+row)->SCS6);
  }
  int get_SCS7(int row) {
    return ((row_ptr+row)->SCS7);
  }
  int get_SCS8(int row) {
    return ((row_ptr+row)->SCS8);
  }
  int get_SCS9(int row) {
    return ((row_ptr+row)->SCS9);
  }
  int get_SCS10(int row) {
    return ((row_ptr+row)->SCS10);
  }
  int get_SCS11(int row) {
    return ((row_ptr+row)->SCS11);
  }
  int get_SCS12(int row) {
    return ((row_ptr+row)->SCS12);
  }
  int get_SCS13(int row) {
    return ((row_ptr+row)->SCS13);
  }
  int get_SCS14(int row) {
    return ((row_ptr+row)->SCS14);
  }
  int get_SCS15(int row) {
    return ((row_ptr+row)->SCS15);
  }
  int get_SCS16(int row) {
    return ((row_ptr+row)->SCS16);
  }
  int get_SCS17(int row) {
    return ((row_ptr+row)->SCS17);
  }
  int get_SCS18(int row) {
    return ((row_ptr+row)->SCS18);
  }
  int get_SCS19(int row) {
    return ((row_ptr+row)->SCS19);
  }
  int get_SCS20(int row) {
    return ((row_ptr+row)->SCS20);
  }
  int get_SCS21(int row) {
    return ((row_ptr+row)->SCS21);
  }
  int get_SCS22(int row) {
    return ((row_ptr+row)->SCS22);
  }
  int get_SCS23(int row) {
    return ((row_ptr+row)->SCS23);
  }
  int get_SCS24(int row) {
    return ((row_ptr+row)->SCS24);
  }
  int get_SCS25(int row) {
    return ((row_ptr+row)->SCS25);
  }
  int get_SCS26(int row) {
    return ((row_ptr+row)->SCS26);
  }
  int get_SCS27(int row) {
    return ((row_ptr+row)->SCS27);
  }
  int get_SCS28(int row) {
    return ((row_ptr+row)->SCS28);
  }
  int get_SCS29(int row) {
    return ((row_ptr+row)->SCS29);
  }
  int get_SCS30(int row) {
    return ((row_ptr+row)->SCS30);
  }
  int get_SCS31(int row) {
    return ((row_ptr+row)->SCS31);
  }
  int get_SCS32(int row) {
    return ((row_ptr+row)->SCS32);
  }
  int get_SCS33(int row) {
    return ((row_ptr+row)->SCS33);
  }
  int get_SCS34(int row) {
    return ((row_ptr+row)->SCS34);
  }
  int get_SCS35(int row) {
    return ((row_ptr+row)->SCS35);
  }
  int get_SCS36(int row) {
    return ((row_ptr+row)->SCS36);
  }
  int get_SCS37(int row) {
    return ((row_ptr+row)->SCS37);
  }
  int get_SCS38(int row) {
    return ((row_ptr+row)->SCS38);
  }
  int get_SCS39(int row) {
    return ((row_ptr+row)->SCS39);
  }
  int get_SCS40(int row) {
    return ((row_ptr+row)->SCS40);
  }
  int get_SCS41(int row) {
    return ((row_ptr+row)->SCS41);
  }
  int get_SCS42(int row) {
    return ((row_ptr+row)->SCS42);
  }
  int get_SCS43(int row) {
    return ((row_ptr+row)->SCS43);
  }
  int get_SCS44(int row) {
    return ((row_ptr+row)->SCS44);
  }
  int get_SCS45(int row) {
    return ((row_ptr+row)->SCS45);
  }
  int get_SCS46(int row) {
    return ((row_ptr+row)->SCS46);
  }
  int get_SCS47(int row) {
    return ((row_ptr+row)->SCS47);
  }
  int get_SCS48(int row) {
    return ((row_ptr+row)->SCS48);
  }
  int get_SCS49(int row) {
    return ((row_ptr+row)->SCS49);
  }
  int get_SCS50(int row) {
    return ((row_ptr+row)->SCS50);
  }
  int get_SCS51(int row) {
    return ((row_ptr+row)->SCS51);
  }
  int get_SCS52(int row) {
    return ((row_ptr+row)->SCS52);
  }
  int get_SCS53(int row) {
    return ((row_ptr+row)->SCS53);
  }
  int get_SCS54(int row) {
    return ((row_ptr+row)->SCS54);
  }
  int get_SCS55(int row) {
    return ((row_ptr+row)->SCS55);
  }
  int get_SCS56(int row) {
    return ((row_ptr+row)->SCS56);
  }
  int get_SCS57(int row) {
    return ((row_ptr+row)->SCS57);
  }
  int get_SCS58(int row) {
    return ((row_ptr+row)->SCS58);
  }
  int get_SCS59(int row) {
    return ((row_ptr+row)->SCS59);
  }
  int get_SCS60(int row) {
    return ((row_ptr+row)->SCS60);
  }
  int get_SCS61(int row) {
    return ((row_ptr+row)->SCS61);
  }
  int get_SCS62(int row) {
    return ((row_ptr+row)->SCS62);
  }
  int get_SCS63(int row) {
    return ((row_ptr+row)->SCS63);
  }
  int get_SCS64(int row) {
    return ((row_ptr+row)->SCS64);
  }
  int get_SCS65(int row) {
    return ((row_ptr+row)->SCS65);
  }
  int get_SCS66(int row) {
    return ((row_ptr+row)->SCS66);
  }
  int get_SCS67(int row) {
    return ((row_ptr+row)->SCS67);
  }
  int get_SCS68(int row) {
    return ((row_ptr+row)->SCS68);
  }
  int get_SCS69(int row) {
    return ((row_ptr+row)->SCS69);
  }
  int get_SCS70(int row) {
    return ((row_ptr+row)->SCS70);
  }
  int get_SCS71(int row) {
    return ((row_ptr+row)->SCS71);
  }
  int get_SCS72(int row) {
    return ((row_ptr+row)->SCS72);
  }
  int get_SCS73(int row) {
    return ((row_ptr+row)->SCS73);
  }
  int get_SCS74(int row) {
    return ((row_ptr+row)->SCS74);
  }
  int get_SCS75(int row) {
    return ((row_ptr+row)->SCS75);
  }
  int get_SCS76(int row) {
    return ((row_ptr+row)->SCS76);
  }
  int get_SCS77(int row) {
    return ((row_ptr+row)->SCS77);
  }
  int get_SCS78(int row) {
    return ((row_ptr+row)->SCS78);
  }
  int get_SCS79(int row) {
    return ((row_ptr+row)->SCS79);
  }
  int get_SCS80(int row) {
    return ((row_ptr+row)->SCS80);
  }
  int get_SCS81(int row) {
    return ((row_ptr+row)->SCS81);
  }
  int get_SCS82(int row) {
    return ((row_ptr+row)->SCS82);
  }
  int get_SCS83(int row) {
    return ((row_ptr+row)->SCS83);
  }
  int get_SCS84(int row) {
    return ((row_ptr+row)->SCS84);
  }
  int get_SCS85(int row) {
    return ((row_ptr+row)->SCS85);
  }
  int get_SCS86(int row) {
    return ((row_ptr+row)->SCS86);
  }
  int get_SCS87(int row) {
    return ((row_ptr+row)->SCS87);
  }
  int get_SCS88(int row) {
    return ((row_ptr+row)->SCS88);
  }
  int get_SCS89(int row) {
    return ((row_ptr+row)->SCS89);
  }
  int get_SCS90(int row) {
    return ((row_ptr+row)->SCS90);
  }
  int get_SCS91(int row) {
    return ((row_ptr+row)->SCS91);
  }
  int get_SCS92(int row) {
    return ((row_ptr+row)->SCS92);
  }
  int get_SCS93(int row) {
    return ((row_ptr+row)->SCS93);
  }
  int get_SCS94(int row) {
    return ((row_ptr+row)->SCS94);
  }
  int get_SCS95(int row) {
    return ((row_ptr+row)->SCS95);
  }
  int get_SCS96(int row) {
    return ((row_ptr+row)->SCS96);
  }
  int get_SCS97(int row) {
    return ((row_ptr+row)->SCS97);
  }
  int get_SCS98(int row) {
    return ((row_ptr+row)->SCS98);
  }
  int get_SCS99(int row) {
    return ((row_ptr+row)->SCS99);
  }
  int get_SCS100(int row) {
    return ((row_ptr+row)->SCS100);
  }
  int get_SCS101(int row) {
    return ((row_ptr+row)->SCS101);
  }
  int get_SCS102(int row) {
    return ((row_ptr+row)->SCS102);
  }
  int get_SCS103(int row) {
    return ((row_ptr+row)->SCS103);
  }
  int get_SCS104(int row) {
    return ((row_ptr+row)->SCS104);
  }
  int get_SCS105(int row) {
    return ((row_ptr+row)->SCS105);
  }
  int get_SCS106(int row) {
    return ((row_ptr+row)->SCS106);
  }
  int get_SCS107(int row) {
    return ((row_ptr+row)->SCS107);
  }
  int get_SCS108(int row) {
    return ((row_ptr+row)->SCS108);
  }
  int get_SCS109(int row) {
    return ((row_ptr+row)->SCS109);
  }
  int get_SCS110(int row) {
    return ((row_ptr+row)->SCS110);
  }
  int get_SCS111(int row) {
    return ((row_ptr+row)->SCS111);
  }
  int get_SCS112(int row) {
    return ((row_ptr+row)->SCS112);
  }
  int get_SCS113(int row) {
    return ((row_ptr+row)->SCS113);
  }
  int get_SCS114(int row) {
    return ((row_ptr+row)->SCS114);
  }
  int get_SCS115(int row) {
    return ((row_ptr+row)->SCS115);
  }
  int get_SCS116(int row) {
    return ((row_ptr+row)->SCS116);
  }
  int get_SCS117(int row) {
    return ((row_ptr+row)->SCS117);
  }
  int get_SCS118(int row) {
    return ((row_ptr+row)->SCS118);
  }
  int get_SCS119(int row) {
    return ((row_ptr+row)->SCS119);
  }
  int get_SCS120(int row) {
    return ((row_ptr+row)->SCS120);
  }
  int get_SCS121(int row) {
    return ((row_ptr+row)->SCS121);
  }
  int get_SCS122(int row) {
    return ((row_ptr+row)->SCS122);
  }
  int get_SCS123(int row) {
    return ((row_ptr+row)->SCS123);
  }
  int get_SCS124(int row) {
    return ((row_ptr+row)->SCS124);
  }
  int get_SCS125(int row) {
    return ((row_ptr+row)->SCS125);
  }
  int get_SCS126(int row) {
    return ((row_ptr+row)->SCS126);
  }
  int get_SCS127(int row) {
    return ((row_ptr+row)->SCS127);
  }
  int get_SCS128(int row) {
    return ((row_ptr+row)->SCS128);
  }
  int get_SCS129(int row) {
    return ((row_ptr+row)->SCS129);
  }
  int get_SCS130(int row) {
    return ((row_ptr+row)->SCS130);
  }
  int get_SCS131(int row) {
    return ((row_ptr+row)->SCS131);
  }
  int get_SCS132(int row) {
    return ((row_ptr+row)->SCS132);
  }
  int get_SCS133(int row) {
    return ((row_ptr+row)->SCS133);
  }
  int get_SCS134(int row) {
    return ((row_ptr+row)->SCS134);
  }
  int get_SCS135(int row) {
    return ((row_ptr+row)->SCS135);
  }
  int get_SCS136(int row) {
    return ((row_ptr+row)->SCS136);
  }
  int get_SCS137(int row) {
    return ((row_ptr+row)->SCS137);
  }
  int get_SCS138(int row) {
    return ((row_ptr+row)->SCS138);
  }
  int get_SCS139(int row) {
    return ((row_ptr+row)->SCS139);
  }
  int get_SCS140(int row) {
    return ((row_ptr+row)->SCS140);
  }
  int get_SCS141(int row) {
    return ((row_ptr+row)->SCS141);
  }
  int get_SCS142(int row) {
    return ((row_ptr+row)->SCS142);
  }
  int get_SCS143(int row) {
    return ((row_ptr+row)->SCS143);
  }
  int get_SCS144(int row) {
    return ((row_ptr+row)->SCS144);
  }
  int get_SCS145(int row) {
    return ((row_ptr+row)->SCS145);
  }
  int get_SCS146(int row) {
    return ((row_ptr+row)->SCS146);
  }
  int get_SCS147(int row) {
    return ((row_ptr+row)->SCS147);
  }
  int get_SCS148(int row) {
    return ((row_ptr+row)->SCS148);
  }
  int get_SCS149(int row) {
    return ((row_ptr+row)->SCS149);
  }
  int get_SCS150(int row) {
    return ((row_ptr+row)->SCS150);
  }
  int get_SCS151(int row) {
    return ((row_ptr+row)->SCS151);
  }
  int get_SCS152(int row) {
    return ((row_ptr+row)->SCS152);
  }
  int get_SCS153(int row) {
    return ((row_ptr+row)->SCS153);
  }
  int get_SCS154(int row) {
    return ((row_ptr+row)->SCS154);
  }
  int get_SCS155(int row) {
    return ((row_ptr+row)->SCS155);
  }
  int get_SCS156(int row) {
    return ((row_ptr+row)->SCS156);
  }
  int get_SCS157(int row) {
    return ((row_ptr+row)->SCS157);
  }
  int get_SCS158(int row) {
    return ((row_ptr+row)->SCS158);
  }
  int get_SCS159(int row) {
    return ((row_ptr+row)->SCS159);
  }
  int get_SCS160(int row) {
    return ((row_ptr+row)->SCS160);
  }
  int get_SCS161(int row) {
    return ((row_ptr+row)->SCS161);
  }
  int get_SCS162(int row) {
    return ((row_ptr+row)->SCS162);
  }
  int get_SCS163(int row) {
    return ((row_ptr+row)->SCS163);
  }
  int get_SCS164(int row) {
    return ((row_ptr+row)->SCS164);
  }
  int get_SCS165(int row) {
    return ((row_ptr+row)->SCS165);
  }
  int get_SCS166(int row) {
    return ((row_ptr+row)->SCS166);
  }
  int get_SCS167(int row) {
    return ((row_ptr+row)->SCS167);
  }
  int get_SCS168(int row) {
    return ((row_ptr+row)->SCS168);
  }
  int get_SCS169(int row) {
    return ((row_ptr+row)->SCS169);
  }
  int get_SCS170(int row) {
    return ((row_ptr+row)->SCS170);
  }
  int get_SCS171(int row) {
    return ((row_ptr+row)->SCS171);
  }
  int get_SCS172(int row) {
    return ((row_ptr+row)->SCS172);
  }
  int get_SCS173(int row) {
    return ((row_ptr+row)->SCS173);
  }
  int get_SCS174(int row) {
    return ((row_ptr+row)->SCS174);
  }
  int get_SCS175(int row) {
    return ((row_ptr+row)->SCS175);
  }
  int get_SCS176(int row) {
    return ((row_ptr+row)->SCS176);
  }
  int get_SCS177(int row) {
    return ((row_ptr+row)->SCS177);
  }
  int get_SCS178(int row) {
    return ((row_ptr+row)->SCS178);
  }
  int get_SCS179(int row) {
    return ((row_ptr+row)->SCS179);
  }
  int get_SCS180(int row) {
    return ((row_ptr+row)->SCS180);
  }
  int get_SCS181(int row) {
    return ((row_ptr+row)->SCS181);
  }
  int get_SCS182(int row) {
    return ((row_ptr+row)->SCS182);
  }
  int get_SCS183(int row) {
    return ((row_ptr+row)->SCS183);
  }
  int get_SCS184(int row) {
    return ((row_ptr+row)->SCS184);
  }
  int get_SCS185(int row) {
    return ((row_ptr+row)->SCS185);
  }
  int get_SCS186(int row) {
    return ((row_ptr+row)->SCS186);
  }
  int get_SCS187(int row) {
    return ((row_ptr+row)->SCS187);
  }
  int get_SCS188(int row) {
    return ((row_ptr+row)->SCS188);
  }
  int get_SCS189(int row) {
    return ((row_ptr+row)->SCS189);
  }
  int get_SCS190(int row) {
    return ((row_ptr+row)->SCS190);
  }
  int get_SCS191(int row) {
    return ((row_ptr+row)->SCS191);
  }
  int get_SCS192(int row) {
    return ((row_ptr+row)->SCS192);
  }
};

struct SCT_row {
  short ID;
  short TDC;
};

class SCT {
private:
  int nrows;
  struct SCT_row *row_ptr;
public:
  SCT(void) {
    return;
  }
  SCT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct SGMP_row {
  int is;
  int sgm1;
  int sgm2;
  int sgm3;
  int sgm4;
  int sgm5;
  int sgm6;
};

class SGMP {
private:
  int nrows;
  struct SGMP_row *row_ptr;
public:
  SGMP(void) {
    return;
  }
  SGMP(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_is(int row) {
    return ((row_ptr+row)->is);
  }
  int get_sgm1(int row) {
    return ((row_ptr+row)->sgm1);
  }
  int get_sgm2(int row) {
    return ((row_ptr+row)->sgm2);
  }
  int get_sgm3(int row) {
    return ((row_ptr+row)->sgm3);
  }
  int get_sgm4(int row) {
    return ((row_ptr+row)->sgm4);
  }
  int get_sgm5(int row) {
    return ((row_ptr+row)->sgm5);
  }
  int get_sgm6(int row) {
    return ((row_ptr+row)->sgm6);
  }
};

struct SPAR_row {
  int slot;
  int channel;
  int spar;
  int pedmean;
};

class SPAR {
private:
  int nrows;
  struct SPAR_row *row_ptr;
public:
  SPAR(void) {
    return;
  }
  SPAR(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_slot(int row) {
    return ((row_ptr+row)->slot);
  }
  int get_channel(int row) {
    return ((row_ptr+row)->channel);
  }
  int get_spar(int row) {
    return ((row_ptr+row)->spar);
  }
  int get_pedmean(int row) {
    return ((row_ptr+row)->pedmean);
  }
};

struct SPIN_row {
  int xspin;
  int yspin;
  int zspin;
};

class SPIN {
private:
  int nrows;
  struct SPIN_row *row_ptr;
public:
  SPIN(void) {
    return;
  }
  SPIN(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_xspin(int row) {
    return ((row_ptr+row)->xspin);
  }
  int get_yspin(int row) {
    return ((row_ptr+row)->yspin);
  }
  int get_zspin(int row) {
    return ((row_ptr+row)->zspin);
  }
};

struct ST1_row {
  int ID;
  int status;
  float TIME_1;
  float ADC_1;
  float TIME_2;
  float ADC_2;
};

class ST1 {
private:
  int nrows;
  struct ST1_row *row_ptr;
public:
  ST1(void) {
    return;
  }
  ST1(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_status(int row) {
    return ((row_ptr+row)->status);
  }
  float get_TIME_1(int row) {
    return ((row_ptr+row)->TIME_1);
  }
  float get_ADC_1(int row) {
    return ((row_ptr+row)->ADC_1);
  }
  float get_TIME_2(int row) {
    return ((row_ptr+row)->TIME_2);
  }
  float get_ADC_2(int row) {
    return ((row_ptr+row)->ADC_2);
  }
};

struct ST_row {
  short ID;
  short TDC;
  short ADC;
};

class ST {
private:
  int nrows;
  struct ST_row *row_ptr;
public:
  ST(void) {
    return;
  }
  ST(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
  short get_ADC(int row) {
    return ((row_ptr+row)->ADC);
  }
};

struct STG_row {
  int id;
  float leg_x_max;
  float leg_x_min;
  float leg_y_max;
  float leg_y_min;
  float leg_z_max;
  float let_z_min;
  float nose_x_max;
  float nose_x_min;
  float nose_y_max;
  float nose_y_min;
  float nose_z_max;
  float nose_z_min;
  float noseAngle;
  float lleg;
  float lnose;
};

class STG {
private:
  int nrows;
  struct STG_row *row_ptr;
public:
  STG(void) {
    return;
  }
  STG(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  float get_leg_x_max(int row) {
    return ((row_ptr+row)->leg_x_max);
  }
  float get_leg_x_min(int row) {
    return ((row_ptr+row)->leg_x_min);
  }
  float get_leg_y_max(int row) {
    return ((row_ptr+row)->leg_y_max);
  }
  float get_leg_y_min(int row) {
    return ((row_ptr+row)->leg_y_min);
  }
  float get_leg_z_max(int row) {
    return ((row_ptr+row)->leg_z_max);
  }
  float get_let_z_min(int row) {
    return ((row_ptr+row)->let_z_min);
  }
  float get_nose_x_max(int row) {
    return ((row_ptr+row)->nose_x_max);
  }
  float get_nose_x_min(int row) {
    return ((row_ptr+row)->nose_x_min);
  }
  float get_nose_y_max(int row) {
    return ((row_ptr+row)->nose_y_max);
  }
  float get_nose_y_min(int row) {
    return ((row_ptr+row)->nose_y_min);
  }
  float get_nose_z_max(int row) {
    return ((row_ptr+row)->nose_z_max);
  }
  float get_nose_z_min(int row) {
    return ((row_ptr+row)->nose_z_min);
  }
  float get_noseAngle(int row) {
    return ((row_ptr+row)->noseAngle);
  }
  float get_lleg(int row) {
    return ((row_ptr+row)->lleg);
  }
  float get_lnose(int row) {
    return ((row_ptr+row)->lnose);
  }
};

struct STH_row {
  float x;
  float y;
  float z;
  float cx;
  float cy;
  float cz;
  float pmom;
  int track;
  int id;
  float tof;
};

class STH {
private:
  int nrows;
  struct STH_row *row_ptr;
public:
  STH(void) {
    return;
  }
  STH(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_cx(int row) {
    return ((row_ptr+row)->cx);
  }
  float get_cy(int row) {
    return ((row_ptr+row)->cy);
  }
  float get_cz(int row) {
    return ((row_ptr+row)->cz);
  }
  float get_pmom(int row) {
    return ((row_ptr+row)->pmom);
  }
  int get_track(int row) {
    return ((row_ptr+row)->track);
  }
  int get_id(int row) {
    return ((row_ptr+row)->id);
  }
  float get_tof(int row) {
    return ((row_ptr+row)->tof);
  }
};

struct STN0_row {
  short ID;
  short TDC;
};

class STN0 {
private:
  int nrows;
  struct STN0_row *row_ptr;
public:
  STN0(void) {
    return;
  }
  STN0(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct STN1_row {
  short ID;
  short ADC;
};

class STN1 {
private:
  int nrows;
  struct STN1_row *row_ptr;
public:
  STN1(void) {
    return;
  }
  STN1(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_ADC(int row) {
    return ((row_ptr+row)->ADC);
  }
};

struct STPB_row {
  int SThid;
  float Time;
  float Path;
  int charge;
  int Status;
};

class STPB {
private:
  int nrows;
  struct STPB_row *row_ptr;
public:
  STPB(void) {
    return;
  }
  STPB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_SThid(int row) {
    return ((row_ptr+row)->SThid);
  }
  float get_Time(int row) {
    return ((row_ptr+row)->Time);
  }
  float get_Path(int row) {
    return ((row_ptr+row)->Path);
  }
  int get_charge(int row) {
    return ((row_ptr+row)->charge);
  }
  int get_Status(int row) {
    return ((row_ptr+row)->Status);
  }
};

struct STPE_row {
  int ID;
  int mean;
  float sigma;
};

class STPE {
private:
  int nrows;
  struct STPE_row *row_ptr;
public:
  STPE(void) {
    return;
  }
  STPE(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_mean(int row) {
    return ((row_ptr+row)->mean);
  }
  float get_sigma(int row) {
    return ((row_ptr+row)->sigma);
  }
};

struct STR_row {
  int ID;
  int Trk_no;
  float ST_TIME;
  float ST_L;
  float st_pos;
  int status;
};

class STR {
private:
  int nrows;
  struct STR_row *row_ptr;
public:
  STR(void) {
    return;
  }
  STR(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_Trk_no(int row) {
    return ((row_ptr+row)->Trk_no);
  }
  float get_ST_TIME(int row) {
    return ((row_ptr+row)->ST_TIME);
  }
  float get_ST_L(int row) {
    return ((row_ptr+row)->ST_L);
  }
  float get_st_pos(int row) {
    return ((row_ptr+row)->st_pos);
  }
  int get_status(int row) {
    return ((row_ptr+row)->status);
  }
};

struct STRE_row {
  int ID;
  int Trk_no;
  float ST_TIME;
  float ST_L;
  float st_pos;
  int status;
  float st_edep;
  float st_corr;
};

class STRE {
private:
  int nrows;
  struct STRE_row *row_ptr;
public:
  STRE(void) {
    return;
  }
  STRE(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_Trk_no(int row) {
    return ((row_ptr+row)->Trk_no);
  }
  float get_ST_TIME(int row) {
    return ((row_ptr+row)->ST_TIME);
  }
  float get_ST_L(int row) {
    return ((row_ptr+row)->ST_L);
  }
  float get_st_pos(int row) {
    return ((row_ptr+row)->st_pos);
  }
  int get_status(int row) {
    return ((row_ptr+row)->status);
  }
  float get_st_edep(int row) {
    return ((row_ptr+row)->st_edep);
  }
  float get_st_corr(int row) {
    return ((row_ptr+row)->st_corr);
  }
};

struct STS_row {
  int STS1;
  int STS2;
  int STS3;
  int STS4;
  int STS5;
  int STS6;
  int STS7;
  int STS8;
  int STS9;
  int STS10;
  int STS11;
  int STS12;
  int STS13;
  int STS14;
  int STS15;
  int STS16;
};

class STS {
private:
  int nrows;
  struct STS_row *row_ptr;
public:
  STS(void) {
    return;
  }
  STS(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_STS1(int row) {
    return ((row_ptr+row)->STS1);
  }
  int get_STS2(int row) {
    return ((row_ptr+row)->STS2);
  }
  int get_STS3(int row) {
    return ((row_ptr+row)->STS3);
  }
  int get_STS4(int row) {
    return ((row_ptr+row)->STS4);
  }
  int get_STS5(int row) {
    return ((row_ptr+row)->STS5);
  }
  int get_STS6(int row) {
    return ((row_ptr+row)->STS6);
  }
  int get_STS7(int row) {
    return ((row_ptr+row)->STS7);
  }
  int get_STS8(int row) {
    return ((row_ptr+row)->STS8);
  }
  int get_STS9(int row) {
    return ((row_ptr+row)->STS9);
  }
  int get_STS10(int row) {
    return ((row_ptr+row)->STS10);
  }
  int get_STS11(int row) {
    return ((row_ptr+row)->STS11);
  }
  int get_STS12(int row) {
    return ((row_ptr+row)->STS12);
  }
  int get_STS13(int row) {
    return ((row_ptr+row)->STS13);
  }
  int get_STS14(int row) {
    return ((row_ptr+row)->STS14);
  }
  int get_STS15(int row) {
    return ((row_ptr+row)->STS15);
  }
  int get_STS16(int row) {
    return ((row_ptr+row)->STS16);
  }
};

struct STSN_row {
  int STSN1;
  int STSN2;
  int STSN3;
  int STSN4;
  int STSN5;
  int STSN6;
  int STSN7;
  int STSN8;
  int STSN9;
  int STSN10;
  int STSN11;
  int STSN12;
  int STSN13;
  int STSN14;
  int STSN15;
  int STSN16;
  int STSN17;
  int STSN18;
  int STSN19;
  int STSN20;
  int STSN21;
  int STSN22;
  int STSN23;
  int STSN24;
  int STOR;
  int STMULT;
  int STANDMOR;
  int MULTANDMOR;
  int RES1;
  int RES2;
  int RES3;
  int RES4;
};

class STSN {
private:
  int nrows;
  struct STSN_row *row_ptr;
public:
  STSN(void) {
    return;
  }
  STSN(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_STSN1(int row) {
    return ((row_ptr+row)->STSN1);
  }
  int get_STSN2(int row) {
    return ((row_ptr+row)->STSN2);
  }
  int get_STSN3(int row) {
    return ((row_ptr+row)->STSN3);
  }
  int get_STSN4(int row) {
    return ((row_ptr+row)->STSN4);
  }
  int get_STSN5(int row) {
    return ((row_ptr+row)->STSN5);
  }
  int get_STSN6(int row) {
    return ((row_ptr+row)->STSN6);
  }
  int get_STSN7(int row) {
    return ((row_ptr+row)->STSN7);
  }
  int get_STSN8(int row) {
    return ((row_ptr+row)->STSN8);
  }
  int get_STSN9(int row) {
    return ((row_ptr+row)->STSN9);
  }
  int get_STSN10(int row) {
    return ((row_ptr+row)->STSN10);
  }
  int get_STSN11(int row) {
    return ((row_ptr+row)->STSN11);
  }
  int get_STSN12(int row) {
    return ((row_ptr+row)->STSN12);
  }
  int get_STSN13(int row) {
    return ((row_ptr+row)->STSN13);
  }
  int get_STSN14(int row) {
    return ((row_ptr+row)->STSN14);
  }
  int get_STSN15(int row) {
    return ((row_ptr+row)->STSN15);
  }
  int get_STSN16(int row) {
    return ((row_ptr+row)->STSN16);
  }
  int get_STSN17(int row) {
    return ((row_ptr+row)->STSN17);
  }
  int get_STSN18(int row) {
    return ((row_ptr+row)->STSN18);
  }
  int get_STSN19(int row) {
    return ((row_ptr+row)->STSN19);
  }
  int get_STSN20(int row) {
    return ((row_ptr+row)->STSN20);
  }
  int get_STSN21(int row) {
    return ((row_ptr+row)->STSN21);
  }
  int get_STSN22(int row) {
    return ((row_ptr+row)->STSN22);
  }
  int get_STSN23(int row) {
    return ((row_ptr+row)->STSN23);
  }
  int get_STSN24(int row) {
    return ((row_ptr+row)->STSN24);
  }
  int get_STOR(int row) {
    return ((row_ptr+row)->STOR);
  }
  int get_STMULT(int row) {
    return ((row_ptr+row)->STMULT);
  }
  int get_STANDMOR(int row) {
    return ((row_ptr+row)->STANDMOR);
  }
  int get_MULTANDMOR(int row) {
    return ((row_ptr+row)->MULTANDMOR);
  }
  int get_RES1(int row) {
    return ((row_ptr+row)->RES1);
  }
  int get_RES2(int row) {
    return ((row_ptr+row)->RES2);
  }
  int get_RES3(int row) {
    return ((row_ptr+row)->RES3);
  }
  int get_RES4(int row) {
    return ((row_ptr+row)->RES4);
  }
};

struct SYNC_row {
  short ID;
  short TDCL;
  short ADCL;
};

class SYNC {
private:
  int nrows;
  struct SYNC_row *row_ptr;
public:
  SYNC(void) {
    return;
  }
  SYNC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDCL(int row) {
    return ((row_ptr+row)->TDCL);
  }
  short get_ADCL(int row) {
    return ((row_ptr+row)->ADCL);
  }
};

struct TACO_row {
  int ID;
  float TIME;
  float ELT;
  float ERT;
  float ELB;
  float ERB;
  float ESUM;
  float ESUM2;
  float ESUM3;
  int TID;
};

class TACO {
private:
  int nrows;
  struct TACO_row *row_ptr;
public:
  TACO(void) {
    return;
  }
  TACO(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  float get_TIME(int row) {
    return ((row_ptr+row)->TIME);
  }
  float get_ELT(int row) {
    return ((row_ptr+row)->ELT);
  }
  float get_ERT(int row) {
    return ((row_ptr+row)->ERT);
  }
  float get_ELB(int row) {
    return ((row_ptr+row)->ELB);
  }
  float get_ERB(int row) {
    return ((row_ptr+row)->ERB);
  }
  float get_ESUM(int row) {
    return ((row_ptr+row)->ESUM);
  }
  float get_ESUM2(int row) {
    return ((row_ptr+row)->ESUM2);
  }
  float get_ESUM3(int row) {
    return ((row_ptr+row)->ESUM3);
  }
  int get_TID(int row) {
    return ((row_ptr+row)->TID);
  }
};

struct TAGE_row {
  short ID;
  short TDC;
};

class TAGE {
private:
  int nrows;
  struct TAGE_row *row_ptr;
public:
  TAGE(void) {
    return;
  }
  TAGE(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct TAGI_row {
  int IDT;
  float TIMEL;
  float TIMER;
  int IDE;
  float TIMEE;
  float TIMEMEAN;
  float TRF;
  float NEXTTIME;
};

class TAGI {
private:
  int nrows;
  struct TAGI_row *row_ptr;
public:
  TAGI(void) {
    return;
  }
  TAGI(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_IDT(int row) {
    return ((row_ptr+row)->IDT);
  }
  float get_TIMEL(int row) {
    return ((row_ptr+row)->TIMEL);
  }
  float get_TIMER(int row) {
    return ((row_ptr+row)->TIMER);
  }
  int get_IDE(int row) {
    return ((row_ptr+row)->IDE);
  }
  float get_TIMEE(int row) {
    return ((row_ptr+row)->TIMEE);
  }
  float get_TIMEMEAN(int row) {
    return ((row_ptr+row)->TIMEMEAN);
  }
  float get_TRF(int row) {
    return ((row_ptr+row)->TRF);
  }
  float get_NEXTTIME(int row) {
    return ((row_ptr+row)->NEXTTIME);
  }
};

struct TAGM_row {
  float energy;
  float t;
  float e_t;
  int status;
  int tid;
  int eid;
};

class TAGM {
private:
  int nrows;
  struct TAGM_row *row_ptr;
public:
  TAGM(void) {
    return;
  }
  TAGM(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_energy(int row) {
    return ((row_ptr+row)->energy);
  }
  float get_t(int row) {
    return ((row_ptr+row)->t);
  }
  float get_e_t(int row) {
    return ((row_ptr+row)->e_t);
  }
  int get_status(int row) {
    return ((row_ptr+row)->status);
  }
  int get_tid(int row) {
    return ((row_ptr+row)->tid);
  }
  int get_eid(int row) {
    return ((row_ptr+row)->eid);
  }
};

struct TAGR_row {
  float ERG;
  float TTAG;
  float TPHO;
  int STAT;
  int T_id;
  int E_id;
};

class TAGR {
private:
  int nrows;
  struct TAGR_row *row_ptr;
public:
  TAGR(void) {
    return;
  }
  TAGR(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_ERG(int row) {
    return ((row_ptr+row)->ERG);
  }
  float get_TTAG(int row) {
    return ((row_ptr+row)->TTAG);
  }
  float get_TPHO(int row) {
    return ((row_ptr+row)->TPHO);
  }
  int get_STAT(int row) {
    return ((row_ptr+row)->STAT);
  }
  int get_T_id(int row) {
    return ((row_ptr+row)->T_id);
  }
  int get_E_id(int row) {
    return ((row_ptr+row)->E_id);
  }
};

struct TAGT_row {
  short ID;
  short TDCL;
  short TDCR;
};

class TAGT {
private:
  int nrows;
  struct TAGT_row *row_ptr;
public:
  TAGT(void) {
    return;
  }
  TAGT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDCL(int row) {
    return ((row_ptr+row)->TDCL);
  }
  short get_TDCR(int row) {
    return ((row_ptr+row)->TDCR);
  }
};

struct TATL_row {
  int ID;
  int TDC;
};

class TATL {
private:
  int nrows;
  struct TATL_row *row_ptr;
public:
  TATL(void) {
    return;
  }
  TATL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct TATR_row {
  int ID;
  int TDC;
};

class TATR {
private:
  int nrows;
  struct TATR_row *row_ptr;
public:
  TATR(void) {
    return;
  }
  TATR(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  int get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct TBER_row {
  float q_over_p;
  float lambda;
  float phi;
  float d0;
  float z0;
  float c11;
  float c12;
  float c13;
  float c14;
  float c15;
  float c22;
  float c23;
  float c24;
  float c25;
  float c33;
  float c34;
  float c35;
  float c44;
  float c45;
  float c55;
  float chi2;
  int layinfo1;
  int layinfo2;
};

class TBER {
private:
  int nrows;
  struct TBER_row *row_ptr;
public:
  TBER(void) {
    return;
  }
  TBER(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_q_over_p(int row) {
    return ((row_ptr+row)->q_over_p);
  }
  float get_lambda(int row) {
    return ((row_ptr+row)->lambda);
  }
  float get_phi(int row) {
    return ((row_ptr+row)->phi);
  }
  float get_d0(int row) {
    return ((row_ptr+row)->d0);
  }
  float get_z0(int row) {
    return ((row_ptr+row)->z0);
  }
  float get_c11(int row) {
    return ((row_ptr+row)->c11);
  }
  float get_c12(int row) {
    return ((row_ptr+row)->c12);
  }
  float get_c13(int row) {
    return ((row_ptr+row)->c13);
  }
  float get_c14(int row) {
    return ((row_ptr+row)->c14);
  }
  float get_c15(int row) {
    return ((row_ptr+row)->c15);
  }
  float get_c22(int row) {
    return ((row_ptr+row)->c22);
  }
  float get_c23(int row) {
    return ((row_ptr+row)->c23);
  }
  float get_c24(int row) {
    return ((row_ptr+row)->c24);
  }
  float get_c25(int row) {
    return ((row_ptr+row)->c25);
  }
  float get_c33(int row) {
    return ((row_ptr+row)->c33);
  }
  float get_c34(int row) {
    return ((row_ptr+row)->c34);
  }
  float get_c35(int row) {
    return ((row_ptr+row)->c35);
  }
  float get_c44(int row) {
    return ((row_ptr+row)->c44);
  }
  float get_c45(int row) {
    return ((row_ptr+row)->c45);
  }
  float get_c55(int row) {
    return ((row_ptr+row)->c55);
  }
  float get_chi2(int row) {
    return ((row_ptr+row)->chi2);
  }
  int get_layinfo1(int row) {
    return ((row_ptr+row)->layinfo1);
  }
  int get_layinfo2(int row) {
    return ((row_ptr+row)->layinfo2);
  }
};

struct TBID_row {
  int track;
  int sec;
  float beta;
  float vtime;
  int sc_stat;
  int sc_id;
  float sc_time;
  float sc_qual;
  float sc_vtime;
  float sc_beta;
  int cc_stat;
  int cc_id;
  float cc_time;
  float cc_qual;
  float cc_vtime;
  float cc_beta;
  int ec_stat;
  int ec_id;
  float ec_time;
  float ec_qual;
  float ec_vtime;
  float ec_beta;
  int st_stat;
  int st_id;
  float st_time;
  float st_qual;
  float st_vtime;
  float st_beta;
  int lac_stat;
  int lac_id;
  float lac_time;
  float lac_qual;
  float lac_vtime;
  float lac_beta;
};

class TBID {
private:
  int nrows;
  struct TBID_row *row_ptr;
public:
  TBID(void) {
    return;
  }
  TBID(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_track(int row) {
    return ((row_ptr+row)->track);
  }
  int get_sec(int row) {
    return ((row_ptr+row)->sec);
  }
  float get_beta(int row) {
    return ((row_ptr+row)->beta);
  }
  float get_vtime(int row) {
    return ((row_ptr+row)->vtime);
  }
  int get_sc_stat(int row) {
    return ((row_ptr+row)->sc_stat);
  }
  int get_sc_id(int row) {
    return ((row_ptr+row)->sc_id);
  }
  float get_sc_time(int row) {
    return ((row_ptr+row)->sc_time);
  }
  float get_sc_qual(int row) {
    return ((row_ptr+row)->sc_qual);
  }
  float get_sc_vtime(int row) {
    return ((row_ptr+row)->sc_vtime);
  }
  float get_sc_beta(int row) {
    return ((row_ptr+row)->sc_beta);
  }
  int get_cc_stat(int row) {
    return ((row_ptr+row)->cc_stat);
  }
  int get_cc_id(int row) {
    return ((row_ptr+row)->cc_id);
  }
  float get_cc_time(int row) {
    return ((row_ptr+row)->cc_time);
  }
  float get_cc_qual(int row) {
    return ((row_ptr+row)->cc_qual);
  }
  float get_cc_vtime(int row) {
    return ((row_ptr+row)->cc_vtime);
  }
  float get_cc_beta(int row) {
    return ((row_ptr+row)->cc_beta);
  }
  int get_ec_stat(int row) {
    return ((row_ptr+row)->ec_stat);
  }
  int get_ec_id(int row) {
    return ((row_ptr+row)->ec_id);
  }
  float get_ec_time(int row) {
    return ((row_ptr+row)->ec_time);
  }
  float get_ec_qual(int row) {
    return ((row_ptr+row)->ec_qual);
  }
  float get_ec_vtime(int row) {
    return ((row_ptr+row)->ec_vtime);
  }
  float get_ec_beta(int row) {
    return ((row_ptr+row)->ec_beta);
  }
  int get_st_stat(int row) {
    return ((row_ptr+row)->st_stat);
  }
  int get_st_id(int row) {
    return ((row_ptr+row)->st_id);
  }
  float get_st_time(int row) {
    return ((row_ptr+row)->st_time);
  }
  float get_st_qual(int row) {
    return ((row_ptr+row)->st_qual);
  }
  float get_st_vtime(int row) {
    return ((row_ptr+row)->st_vtime);
  }
  float get_st_beta(int row) {
    return ((row_ptr+row)->st_beta);
  }
  int get_lac_stat(int row) {
    return ((row_ptr+row)->lac_stat);
  }
  int get_lac_id(int row) {
    return ((row_ptr+row)->lac_id);
  }
  float get_lac_time(int row) {
    return ((row_ptr+row)->lac_time);
  }
  float get_lac_qual(int row) {
    return ((row_ptr+row)->lac_qual);
  }
  float get_lac_vtime(int row) {
    return ((row_ptr+row)->lac_vtime);
  }
  float get_lac_beta(int row) {
    return ((row_ptr+row)->lac_beta);
  }
};

struct TBLA_row {
  int trk_pln;
  float x;
  float y;
  float z;
  float Bx;
  float By;
  float Bz;
  float tlen;
  int dc1;
  int stat;
  int wire;
  float dtime;
  float alpha;
  float wlen;
  float sgdoca;
  float fitdoca;
  float calcdoca;
};

class TBLA {
private:
  int nrows;
  struct TBLA_row *row_ptr;
public:
  TBLA(void) {
    return;
  }
  TBLA(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_trk_pln(int row) {
    return ((row_ptr+row)->trk_pln);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_Bx(int row) {
    return ((row_ptr+row)->Bx);
  }
  float get_By(int row) {
    return ((row_ptr+row)->By);
  }
  float get_Bz(int row) {
    return ((row_ptr+row)->Bz);
  }
  float get_tlen(int row) {
    return ((row_ptr+row)->tlen);
  }
  int get_dc1(int row) {
    return ((row_ptr+row)->dc1);
  }
  int get_stat(int row) {
    return ((row_ptr+row)->stat);
  }
  int get_wire(int row) {
    return ((row_ptr+row)->wire);
  }
  float get_dtime(int row) {
    return ((row_ptr+row)->dtime);
  }
  float get_alpha(int row) {
    return ((row_ptr+row)->alpha);
  }
  float get_wlen(int row) {
    return ((row_ptr+row)->wlen);
  }
  float get_sgdoca(int row) {
    return ((row_ptr+row)->sgdoca);
  }
  float get_fitdoca(int row) {
    return ((row_ptr+row)->fitdoca);
  }
  float get_calcdoca(int row) {
    return ((row_ptr+row)->calcdoca);
  }
};

struct TBTR_row {
  float x;
  float y;
  float z;
  float px;
  float py;
  float pz;
  float q;
  float chi2;
  int itr_sec;
  int itr_hbt;
};

class TBTR {
private:
  int nrows;
  struct TBTR_row *row_ptr;
public:
  TBTR(void) {
    return;
  }
  TBTR(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_px(int row) {
    return ((row_ptr+row)->px);
  }
  float get_py(int row) {
    return ((row_ptr+row)->py);
  }
  float get_pz(int row) {
    return ((row_ptr+row)->pz);
  }
  float get_q(int row) {
    return ((row_ptr+row)->q);
  }
  float get_chi2(int row) {
    return ((row_ptr+row)->chi2);
  }
  int get_itr_sec(int row) {
    return ((row_ptr+row)->itr_sec);
  }
  int get_itr_hbt(int row) {
    return ((row_ptr+row)->itr_hbt);
  }
};

struct TCSB_row {
  float xpos;
  float ypos;
  float zpos;
  float sxpos;
  float sypos;
  float szpos;
};

class TCSB {
private:
  int nrows;
  struct TCSB_row *row_ptr;
public:
  TCSB(void) {
    return;
  }
  TCSB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_xpos(int row) {
    return ((row_ptr+row)->xpos);
  }
  float get_ypos(int row) {
    return ((row_ptr+row)->ypos);
  }
  float get_zpos(int row) {
    return ((row_ptr+row)->zpos);
  }
  float get_sxpos(int row) {
    return ((row_ptr+row)->sxpos);
  }
  float get_sypos(int row) {
    return ((row_ptr+row)->sypos);
  }
  float get_szpos(int row) {
    return ((row_ptr+row)->szpos);
  }
};

struct TCT_row {
  short ID;
  short TDC;
};

class TCT {
private:
  int nrows;
  struct TCT_row *row_ptr;
public:
  TCT(void) {
    return;
  }
  TCT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct TDPL_row {
  int trk_pln;
  float x;
  float y;
  float z;
  float cx;
  float cy;
  float cz;
  float tlen;
};

class TDPL {
private:
  int nrows;
  struct TDPL_row *row_ptr;
public:
  TDPL(void) {
    return;
  }
  TDPL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_trk_pln(int row) {
    return ((row_ptr+row)->trk_pln);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_cx(int row) {
    return ((row_ptr+row)->cx);
  }
  float get_cy(int row) {
    return ((row_ptr+row)->cy);
  }
  float get_cz(int row) {
    return ((row_ptr+row)->cz);
  }
  float get_tlen(int row) {
    return ((row_ptr+row)->tlen);
  }
};

struct TESC_row {
  float value;
};

class TESC {
private:
  int nrows;
  struct TESC_row *row_ptr;
public:
  TESC(void) {
    return;
  }
  TESC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_value(int row) {
    return ((row_ptr+row)->value);
  }
};

struct TGBI_row {
  int latch1;
  int helicity_scaler;
  int interrupt_time;
  int latch2;
  int level3;
};

class TGBI {
private:
  int nrows;
  struct TGBI_row *row_ptr;
public:
  TGBI(void) {
    return;
  }
  TGBI(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_latch1(int row) {
    return ((row_ptr+row)->latch1);
  }
  int get_helicity_scaler(int row) {
    return ((row_ptr+row)->helicity_scaler);
  }
  int get_interrupt_time(int row) {
    return ((row_ptr+row)->interrupt_time);
  }
  int get_latch2(int row) {
    return ((row_ptr+row)->latch2);
  }
  int get_level3(int row) {
    return ((row_ptr+row)->level3);
  }
};

struct TGEO_row {
  float x;
  float y;
  float z;
  float radius;
  float lenght;
  int material;
};

class TGEO {
private:
  int nrows;
  struct TGEO_row *row_ptr;
public:
  TGEO(void) {
    return;
  }
  TGEO(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_radius(int row) {
    return ((row_ptr+row)->radius);
  }
  float get_lenght(int row) {
    return ((row_ptr+row)->lenght);
  }
  int get_material(int row) {
    return ((row_ptr+row)->material);
  }
};

struct TGPB_row {
  int pointer;
  float Time;
  float Energy;
  float dt;
};

class TGPB {
private:
  int nrows;
  struct TGPB_row *row_ptr;
public:
  TGPB(void) {
    return;
  }
  TGPB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_pointer(int row) {
    return ((row_ptr+row)->pointer);
  }
  float get_Time(int row) {
    return ((row_ptr+row)->Time);
  }
  float get_Energy(int row) {
    return ((row_ptr+row)->Energy);
  }
  float get_dt(int row) {
    return ((row_ptr+row)->dt);
  }
};

struct TGS_row {
  int RAWT1;
  int RAWT2;
  int RAWT3;
  int RAWT4;
  int RAWT5;
  int RAWT6;
  int RAWT7;
  int RAWT8;
  int RAWT9;
  int RAWT10;
  int RAWT11;
  int RAWT12;
  int RAWT13;
  int RAWT14;
  int RAWT15;
  int RAWT16;
  int RAWT17;
  int RAWT18;
  int RAWT19;
  int RAWT20;
  int RAWT21;
  int RAWT22;
  int RAWT23;
  int RAWT24;
  int RAWT25;
  int RAWT26;
  int RAWT27;
  int RAWT28;
  int RAWT29;
  int RAWT30;
  int RAWT31;
  int RAWT32;
  int RAWT33;
  int RAWT34;
  int RAWT35;
  int RAWT36;
  int RAWT37;
  int RAWT38;
  int RAWT39;
  int RAWT40;
  int RAWT41;
  int RAWT42;
  int RAWT43;
  int RAWT44;
  int RAWT45;
  int RAWT46;
  int RAWT47;
  int RAWT48;
  int RAWT49;
  int RAWT50;
  int RAWT51;
  int RAWT52;
  int RAWT53;
  int RAWT54;
  int RAWT55;
  int RAWT56;
  int RAWT57;
  int RAWT58;
  int RAWT59;
  int RAWT60;
  int RAWT61;
  int notused62;
  int notused63;
  int notused64;
  int BNK1T1;
  int BNK1T2;
  int BNK1T3;
  int BNK1T4;
  int BNK1T5;
  int BNK1T6;
  int BNK1T7;
  int BNK1T8;
  int BNK1T9;
  int BNK1T10;
  int BNK1T11;
  int BNK1T12;
  int BNK1T13;
  int BNK1T14;
  int BNK1T15;
  int BNK1T16;
  int BNK1T17;
  int BNK1T18;
  int BNK1T19;
  int BNK1T20;
  int BNK1T21;
  int BNK1T22;
  int BNK1T23;
  int BNK1T24;
  int BNK1T25;
  int BNK1T26;
  int BNK1T27;
  int BNK1T28;
  int BNK1T29;
  int BNK1T30;
  int BNK1T31;
  int BNK1T32;
  int BNK1T33;
  int BNK1T34;
  int BNK1T35;
  int BNK1T36;
  int BNK1T37;
  int BNK1T38;
  int BNK1T39;
  int BNK1T40;
  int BNK1T41;
  int BNK1T42;
  int BNK1T43;
  int BNK1T44;
  int BNK1T45;
  int BNK1T46;
  int BNK1T47;
  int BNK1T48;
  int BNK1T49;
  int BNK1T50;
  int BNK1T51;
  int BNK1T52;
  int BNK1T53;
  int BNK1T54;
  int BNK1T55;
  int BNK1T56;
  int BNK1T57;
  int BNK1T58;
  int BNK1T59;
  int BNK1T60;
  int BNK1T61;
  int notused126;
  int notused127;
  int notused128;
  int BNK2T1;
  int BNK2T2;
  int BNK2T3;
  int BNK2T4;
  int BNK2T5;
  int BNK2T6;
  int BNK2T7;
  int BNK2T8;
  int BNK2T9;
  int BNK2T10;
  int BNK2T11;
  int BNK2T12;
  int BNK2T13;
  int BNK2T14;
  int BNK2T15;
  int BNK2T16;
  int BNK2T17;
  int BNK2T18;
  int BNK2T19;
  int BNK2T20;
  int BNK2T21;
  int BNK2T22;
  int BNK2T23;
  int BNK2T24;
  int BNK2T25;
  int BNK2T26;
  int BNK2T27;
  int BNK2T28;
  int BNK2T29;
  int BNK2T30;
  int BNK2T31;
  int BNK2T32;
  int BNK2T33;
  int BNK2T34;
  int BNK2T35;
  int BNK2T36;
  int BNK2T37;
  int BNK2T38;
  int BNK2T39;
  int BNK2T40;
  int BNK2T41;
  int BNK2T42;
  int BNK2T43;
  int BNK2T44;
  int BNK2T45;
  int BNK2T46;
  int BNK2T47;
  int BNK2T48;
  int BNK2T49;
  int BNK2T50;
  int BNK2T51;
  int BNK2T52;
  int BNK2T53;
  int BNK2T54;
  int BNK2T55;
  int BNK2T56;
  int BNK2T57;
  int BNK2T58;
  int BNK2T59;
  int BNK2T60;
  int BNK2T61;
  int notused190;
  int notused191;
  int notused192;
};

class TGS {
private:
  int nrows;
  struct TGS_row *row_ptr;
public:
  TGS(void) {
    return;
  }
  TGS(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_RAWT1(int row) {
    return ((row_ptr+row)->RAWT1);
  }
  int get_RAWT2(int row) {
    return ((row_ptr+row)->RAWT2);
  }
  int get_RAWT3(int row) {
    return ((row_ptr+row)->RAWT3);
  }
  int get_RAWT4(int row) {
    return ((row_ptr+row)->RAWT4);
  }
  int get_RAWT5(int row) {
    return ((row_ptr+row)->RAWT5);
  }
  int get_RAWT6(int row) {
    return ((row_ptr+row)->RAWT6);
  }
  int get_RAWT7(int row) {
    return ((row_ptr+row)->RAWT7);
  }
  int get_RAWT8(int row) {
    return ((row_ptr+row)->RAWT8);
  }
  int get_RAWT9(int row) {
    return ((row_ptr+row)->RAWT9);
  }
  int get_RAWT10(int row) {
    return ((row_ptr+row)->RAWT10);
  }
  int get_RAWT11(int row) {
    return ((row_ptr+row)->RAWT11);
  }
  int get_RAWT12(int row) {
    return ((row_ptr+row)->RAWT12);
  }
  int get_RAWT13(int row) {
    return ((row_ptr+row)->RAWT13);
  }
  int get_RAWT14(int row) {
    return ((row_ptr+row)->RAWT14);
  }
  int get_RAWT15(int row) {
    return ((row_ptr+row)->RAWT15);
  }
  int get_RAWT16(int row) {
    return ((row_ptr+row)->RAWT16);
  }
  int get_RAWT17(int row) {
    return ((row_ptr+row)->RAWT17);
  }
  int get_RAWT18(int row) {
    return ((row_ptr+row)->RAWT18);
  }
  int get_RAWT19(int row) {
    return ((row_ptr+row)->RAWT19);
  }
  int get_RAWT20(int row) {
    return ((row_ptr+row)->RAWT20);
  }
  int get_RAWT21(int row) {
    return ((row_ptr+row)->RAWT21);
  }
  int get_RAWT22(int row) {
    return ((row_ptr+row)->RAWT22);
  }
  int get_RAWT23(int row) {
    return ((row_ptr+row)->RAWT23);
  }
  int get_RAWT24(int row) {
    return ((row_ptr+row)->RAWT24);
  }
  int get_RAWT25(int row) {
    return ((row_ptr+row)->RAWT25);
  }
  int get_RAWT26(int row) {
    return ((row_ptr+row)->RAWT26);
  }
  int get_RAWT27(int row) {
    return ((row_ptr+row)->RAWT27);
  }
  int get_RAWT28(int row) {
    return ((row_ptr+row)->RAWT28);
  }
  int get_RAWT29(int row) {
    return ((row_ptr+row)->RAWT29);
  }
  int get_RAWT30(int row) {
    return ((row_ptr+row)->RAWT30);
  }
  int get_RAWT31(int row) {
    return ((row_ptr+row)->RAWT31);
  }
  int get_RAWT32(int row) {
    return ((row_ptr+row)->RAWT32);
  }
  int get_RAWT33(int row) {
    return ((row_ptr+row)->RAWT33);
  }
  int get_RAWT34(int row) {
    return ((row_ptr+row)->RAWT34);
  }
  int get_RAWT35(int row) {
    return ((row_ptr+row)->RAWT35);
  }
  int get_RAWT36(int row) {
    return ((row_ptr+row)->RAWT36);
  }
  int get_RAWT37(int row) {
    return ((row_ptr+row)->RAWT37);
  }
  int get_RAWT38(int row) {
    return ((row_ptr+row)->RAWT38);
  }
  int get_RAWT39(int row) {
    return ((row_ptr+row)->RAWT39);
  }
  int get_RAWT40(int row) {
    return ((row_ptr+row)->RAWT40);
  }
  int get_RAWT41(int row) {
    return ((row_ptr+row)->RAWT41);
  }
  int get_RAWT42(int row) {
    return ((row_ptr+row)->RAWT42);
  }
  int get_RAWT43(int row) {
    return ((row_ptr+row)->RAWT43);
  }
  int get_RAWT44(int row) {
    return ((row_ptr+row)->RAWT44);
  }
  int get_RAWT45(int row) {
    return ((row_ptr+row)->RAWT45);
  }
  int get_RAWT46(int row) {
    return ((row_ptr+row)->RAWT46);
  }
  int get_RAWT47(int row) {
    return ((row_ptr+row)->RAWT47);
  }
  int get_RAWT48(int row) {
    return ((row_ptr+row)->RAWT48);
  }
  int get_RAWT49(int row) {
    return ((row_ptr+row)->RAWT49);
  }
  int get_RAWT50(int row) {
    return ((row_ptr+row)->RAWT50);
  }
  int get_RAWT51(int row) {
    return ((row_ptr+row)->RAWT51);
  }
  int get_RAWT52(int row) {
    return ((row_ptr+row)->RAWT52);
  }
  int get_RAWT53(int row) {
    return ((row_ptr+row)->RAWT53);
  }
  int get_RAWT54(int row) {
    return ((row_ptr+row)->RAWT54);
  }
  int get_RAWT55(int row) {
    return ((row_ptr+row)->RAWT55);
  }
  int get_RAWT56(int row) {
    return ((row_ptr+row)->RAWT56);
  }
  int get_RAWT57(int row) {
    return ((row_ptr+row)->RAWT57);
  }
  int get_RAWT58(int row) {
    return ((row_ptr+row)->RAWT58);
  }
  int get_RAWT59(int row) {
    return ((row_ptr+row)->RAWT59);
  }
  int get_RAWT60(int row) {
    return ((row_ptr+row)->RAWT60);
  }
  int get_RAWT61(int row) {
    return ((row_ptr+row)->RAWT61);
  }
  int get_notused62(int row) {
    return ((row_ptr+row)->notused62);
  }
  int get_notused63(int row) {
    return ((row_ptr+row)->notused63);
  }
  int get_notused64(int row) {
    return ((row_ptr+row)->notused64);
  }
  int get_BNK1T1(int row) {
    return ((row_ptr+row)->BNK1T1);
  }
  int get_BNK1T2(int row) {
    return ((row_ptr+row)->BNK1T2);
  }
  int get_BNK1T3(int row) {
    return ((row_ptr+row)->BNK1T3);
  }
  int get_BNK1T4(int row) {
    return ((row_ptr+row)->BNK1T4);
  }
  int get_BNK1T5(int row) {
    return ((row_ptr+row)->BNK1T5);
  }
  int get_BNK1T6(int row) {
    return ((row_ptr+row)->BNK1T6);
  }
  int get_BNK1T7(int row) {
    return ((row_ptr+row)->BNK1T7);
  }
  int get_BNK1T8(int row) {
    return ((row_ptr+row)->BNK1T8);
  }
  int get_BNK1T9(int row) {
    return ((row_ptr+row)->BNK1T9);
  }
  int get_BNK1T10(int row) {
    return ((row_ptr+row)->BNK1T10);
  }
  int get_BNK1T11(int row) {
    return ((row_ptr+row)->BNK1T11);
  }
  int get_BNK1T12(int row) {
    return ((row_ptr+row)->BNK1T12);
  }
  int get_BNK1T13(int row) {
    return ((row_ptr+row)->BNK1T13);
  }
  int get_BNK1T14(int row) {
    return ((row_ptr+row)->BNK1T14);
  }
  int get_BNK1T15(int row) {
    return ((row_ptr+row)->BNK1T15);
  }
  int get_BNK1T16(int row) {
    return ((row_ptr+row)->BNK1T16);
  }
  int get_BNK1T17(int row) {
    return ((row_ptr+row)->BNK1T17);
  }
  int get_BNK1T18(int row) {
    return ((row_ptr+row)->BNK1T18);
  }
  int get_BNK1T19(int row) {
    return ((row_ptr+row)->BNK1T19);
  }
  int get_BNK1T20(int row) {
    return ((row_ptr+row)->BNK1T20);
  }
  int get_BNK1T21(int row) {
    return ((row_ptr+row)->BNK1T21);
  }
  int get_BNK1T22(int row) {
    return ((row_ptr+row)->BNK1T22);
  }
  int get_BNK1T23(int row) {
    return ((row_ptr+row)->BNK1T23);
  }
  int get_BNK1T24(int row) {
    return ((row_ptr+row)->BNK1T24);
  }
  int get_BNK1T25(int row) {
    return ((row_ptr+row)->BNK1T25);
  }
  int get_BNK1T26(int row) {
    return ((row_ptr+row)->BNK1T26);
  }
  int get_BNK1T27(int row) {
    return ((row_ptr+row)->BNK1T27);
  }
  int get_BNK1T28(int row) {
    return ((row_ptr+row)->BNK1T28);
  }
  int get_BNK1T29(int row) {
    return ((row_ptr+row)->BNK1T29);
  }
  int get_BNK1T30(int row) {
    return ((row_ptr+row)->BNK1T30);
  }
  int get_BNK1T31(int row) {
    return ((row_ptr+row)->BNK1T31);
  }
  int get_BNK1T32(int row) {
    return ((row_ptr+row)->BNK1T32);
  }
  int get_BNK1T33(int row) {
    return ((row_ptr+row)->BNK1T33);
  }
  int get_BNK1T34(int row) {
    return ((row_ptr+row)->BNK1T34);
  }
  int get_BNK1T35(int row) {
    return ((row_ptr+row)->BNK1T35);
  }
  int get_BNK1T36(int row) {
    return ((row_ptr+row)->BNK1T36);
  }
  int get_BNK1T37(int row) {
    return ((row_ptr+row)->BNK1T37);
  }
  int get_BNK1T38(int row) {
    return ((row_ptr+row)->BNK1T38);
  }
  int get_BNK1T39(int row) {
    return ((row_ptr+row)->BNK1T39);
  }
  int get_BNK1T40(int row) {
    return ((row_ptr+row)->BNK1T40);
  }
  int get_BNK1T41(int row) {
    return ((row_ptr+row)->BNK1T41);
  }
  int get_BNK1T42(int row) {
    return ((row_ptr+row)->BNK1T42);
  }
  int get_BNK1T43(int row) {
    return ((row_ptr+row)->BNK1T43);
  }
  int get_BNK1T44(int row) {
    return ((row_ptr+row)->BNK1T44);
  }
  int get_BNK1T45(int row) {
    return ((row_ptr+row)->BNK1T45);
  }
  int get_BNK1T46(int row) {
    return ((row_ptr+row)->BNK1T46);
  }
  int get_BNK1T47(int row) {
    return ((row_ptr+row)->BNK1T47);
  }
  int get_BNK1T48(int row) {
    return ((row_ptr+row)->BNK1T48);
  }
  int get_BNK1T49(int row) {
    return ((row_ptr+row)->BNK1T49);
  }
  int get_BNK1T50(int row) {
    return ((row_ptr+row)->BNK1T50);
  }
  int get_BNK1T51(int row) {
    return ((row_ptr+row)->BNK1T51);
  }
  int get_BNK1T52(int row) {
    return ((row_ptr+row)->BNK1T52);
  }
  int get_BNK1T53(int row) {
    return ((row_ptr+row)->BNK1T53);
  }
  int get_BNK1T54(int row) {
    return ((row_ptr+row)->BNK1T54);
  }
  int get_BNK1T55(int row) {
    return ((row_ptr+row)->BNK1T55);
  }
  int get_BNK1T56(int row) {
    return ((row_ptr+row)->BNK1T56);
  }
  int get_BNK1T57(int row) {
    return ((row_ptr+row)->BNK1T57);
  }
  int get_BNK1T58(int row) {
    return ((row_ptr+row)->BNK1T58);
  }
  int get_BNK1T59(int row) {
    return ((row_ptr+row)->BNK1T59);
  }
  int get_BNK1T60(int row) {
    return ((row_ptr+row)->BNK1T60);
  }
  int get_BNK1T61(int row) {
    return ((row_ptr+row)->BNK1T61);
  }
  int get_notused126(int row) {
    return ((row_ptr+row)->notused126);
  }
  int get_notused127(int row) {
    return ((row_ptr+row)->notused127);
  }
  int get_notused128(int row) {
    return ((row_ptr+row)->notused128);
  }
  int get_BNK2T1(int row) {
    return ((row_ptr+row)->BNK2T1);
  }
  int get_BNK2T2(int row) {
    return ((row_ptr+row)->BNK2T2);
  }
  int get_BNK2T3(int row) {
    return ((row_ptr+row)->BNK2T3);
  }
  int get_BNK2T4(int row) {
    return ((row_ptr+row)->BNK2T4);
  }
  int get_BNK2T5(int row) {
    return ((row_ptr+row)->BNK2T5);
  }
  int get_BNK2T6(int row) {
    return ((row_ptr+row)->BNK2T6);
  }
  int get_BNK2T7(int row) {
    return ((row_ptr+row)->BNK2T7);
  }
  int get_BNK2T8(int row) {
    return ((row_ptr+row)->BNK2T8);
  }
  int get_BNK2T9(int row) {
    return ((row_ptr+row)->BNK2T9);
  }
  int get_BNK2T10(int row) {
    return ((row_ptr+row)->BNK2T10);
  }
  int get_BNK2T11(int row) {
    return ((row_ptr+row)->BNK2T11);
  }
  int get_BNK2T12(int row) {
    return ((row_ptr+row)->BNK2T12);
  }
  int get_BNK2T13(int row) {
    return ((row_ptr+row)->BNK2T13);
  }
  int get_BNK2T14(int row) {
    return ((row_ptr+row)->BNK2T14);
  }
  int get_BNK2T15(int row) {
    return ((row_ptr+row)->BNK2T15);
  }
  int get_BNK2T16(int row) {
    return ((row_ptr+row)->BNK2T16);
  }
  int get_BNK2T17(int row) {
    return ((row_ptr+row)->BNK2T17);
  }
  int get_BNK2T18(int row) {
    return ((row_ptr+row)->BNK2T18);
  }
  int get_BNK2T19(int row) {
    return ((row_ptr+row)->BNK2T19);
  }
  int get_BNK2T20(int row) {
    return ((row_ptr+row)->BNK2T20);
  }
  int get_BNK2T21(int row) {
    return ((row_ptr+row)->BNK2T21);
  }
  int get_BNK2T22(int row) {
    return ((row_ptr+row)->BNK2T22);
  }
  int get_BNK2T23(int row) {
    return ((row_ptr+row)->BNK2T23);
  }
  int get_BNK2T24(int row) {
    return ((row_ptr+row)->BNK2T24);
  }
  int get_BNK2T25(int row) {
    return ((row_ptr+row)->BNK2T25);
  }
  int get_BNK2T26(int row) {
    return ((row_ptr+row)->BNK2T26);
  }
  int get_BNK2T27(int row) {
    return ((row_ptr+row)->BNK2T27);
  }
  int get_BNK2T28(int row) {
    return ((row_ptr+row)->BNK2T28);
  }
  int get_BNK2T29(int row) {
    return ((row_ptr+row)->BNK2T29);
  }
  int get_BNK2T30(int row) {
    return ((row_ptr+row)->BNK2T30);
  }
  int get_BNK2T31(int row) {
    return ((row_ptr+row)->BNK2T31);
  }
  int get_BNK2T32(int row) {
    return ((row_ptr+row)->BNK2T32);
  }
  int get_BNK2T33(int row) {
    return ((row_ptr+row)->BNK2T33);
  }
  int get_BNK2T34(int row) {
    return ((row_ptr+row)->BNK2T34);
  }
  int get_BNK2T35(int row) {
    return ((row_ptr+row)->BNK2T35);
  }
  int get_BNK2T36(int row) {
    return ((row_ptr+row)->BNK2T36);
  }
  int get_BNK2T37(int row) {
    return ((row_ptr+row)->BNK2T37);
  }
  int get_BNK2T38(int row) {
    return ((row_ptr+row)->BNK2T38);
  }
  int get_BNK2T39(int row) {
    return ((row_ptr+row)->BNK2T39);
  }
  int get_BNK2T40(int row) {
    return ((row_ptr+row)->BNK2T40);
  }
  int get_BNK2T41(int row) {
    return ((row_ptr+row)->BNK2T41);
  }
  int get_BNK2T42(int row) {
    return ((row_ptr+row)->BNK2T42);
  }
  int get_BNK2T43(int row) {
    return ((row_ptr+row)->BNK2T43);
  }
  int get_BNK2T44(int row) {
    return ((row_ptr+row)->BNK2T44);
  }
  int get_BNK2T45(int row) {
    return ((row_ptr+row)->BNK2T45);
  }
  int get_BNK2T46(int row) {
    return ((row_ptr+row)->BNK2T46);
  }
  int get_BNK2T47(int row) {
    return ((row_ptr+row)->BNK2T47);
  }
  int get_BNK2T48(int row) {
    return ((row_ptr+row)->BNK2T48);
  }
  int get_BNK2T49(int row) {
    return ((row_ptr+row)->BNK2T49);
  }
  int get_BNK2T50(int row) {
    return ((row_ptr+row)->BNK2T50);
  }
  int get_BNK2T51(int row) {
    return ((row_ptr+row)->BNK2T51);
  }
  int get_BNK2T52(int row) {
    return ((row_ptr+row)->BNK2T52);
  }
  int get_BNK2T53(int row) {
    return ((row_ptr+row)->BNK2T53);
  }
  int get_BNK2T54(int row) {
    return ((row_ptr+row)->BNK2T54);
  }
  int get_BNK2T55(int row) {
    return ((row_ptr+row)->BNK2T55);
  }
  int get_BNK2T56(int row) {
    return ((row_ptr+row)->BNK2T56);
  }
  int get_BNK2T57(int row) {
    return ((row_ptr+row)->BNK2T57);
  }
  int get_BNK2T58(int row) {
    return ((row_ptr+row)->BNK2T58);
  }
  int get_BNK2T59(int row) {
    return ((row_ptr+row)->BNK2T59);
  }
  int get_BNK2T60(int row) {
    return ((row_ptr+row)->BNK2T60);
  }
  int get_BNK2T61(int row) {
    return ((row_ptr+row)->BNK2T61);
  }
  int get_notused190(int row) {
    return ((row_ptr+row)->notused190);
  }
  int get_notused191(int row) {
    return ((row_ptr+row)->notused191);
  }
  int get_notused192(int row) {
    return ((row_ptr+row)->notused192);
  }
};

struct TGTL_row {
  short ID;
  short TDC;
};

class TGTL {
private:
  int nrows;
  struct TGTL_row *row_ptr;
public:
  TGTL(void) {
    return;
  }
  TGTL(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct TGTR_row {
  short ID;
  short TDC;
};

class TGTR {
private:
  int nrows;
  struct TGTR_row *row_ptr;
public:
  TGTR(void) {
    return;
  }
  TGTR(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
};

struct TLV1_row {
  int ID;
  float time;
};

class TLV1 {
private:
  int nrows;
  struct TLV1_row *row_ptr;
public:
  TLV1(void) {
    return;
  }
  TLV1(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  float get_time(int row) {
    return ((row_ptr+row)->time);
  }
};

struct TPC_row {
  short ID;
  short TDC;
  short ADC;
};

class TPC {
private:
  int nrows;
  struct TPC_row *row_ptr;
public:
  TPC(void) {
    return;
  }
  TPC(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  short get_ID(int row) {
    return ((row_ptr+row)->ID);
  }
  short get_TDC(int row) {
    return ((row_ptr+row)->TDC);
  }
  short get_ADC(int row) {
    return ((row_ptr+row)->ADC);
  }
};

struct TPCH_row {
  int NEVENT;
  int TIME;
  int NTPC;
};

class TPCH {
private:
  int nrows;
  struct TPCH_row *row_ptr;
public:
  TPCH(void) {
    return;
  }
  TPCH(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_NEVENT(int row) {
    return ((row_ptr+row)->NEVENT);
  }
  int get_TIME(int row) {
    return ((row_ptr+row)->TIME);
  }
  int get_NTPC(int row) {
    return ((row_ptr+row)->NTPC);
  }
};

struct TRCF_row {
  char trigcfg[4];
};

class TRCF {
private:
  int nrows;
  struct TRCF_row *row_ptr;
public:
  TRCF(void) {
    return;
  }
  TRCF(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  char *get_trigcfg(int row) {
    return ((row_ptr+row)->trigcfg);
  }
};

struct TRGS_row {
  int CLOCK_UG;
  int FCUP_UG;
  int Microsec;
  int random_ug;
  int MOR_ST;
  int MOR_PC;
  int MOR_PS;
  int MOR_TAC;
  int MOR;
  int PC;
  int PS;
  int TAC;
  int ST;
  int hel_sync;
  int clock_ug_2;
  int fcup_ug_2;
  int CLOCK_G1;
  int FCUP_G1;
  int NotUsed19;
  int random_g1;
  int MOR_ST_rg;
  int MOR_PC_rg;
  int MOR_PS_rg;
  int MOR_TAC_rg;
  int MOR_rg;
  int PC_rg;
  int PS_rg;
  int TAC_rg;
  int ST_rg;
  int random_g1_2;
  int clock_g1_2;
  int fcup_g1_2;
  int CLOCK_G2;
  int FCUP_G2;
  int trig_or_g2;
  int random_g2;
  int NotUsed37;
  int NotUsed38;
  int NotUsed39;
  int NotUsed40;
  int MOR_lg;
  int NotUsed42;
  int NotUsed43;
  int NotUsed44;
  int NotUsed45;
  int random_g2_2;
  int clock_g2_2;
  int fcup_g2_2;
  int trig1_ug;
  int trig2_ug;
  int trig3_ug;
  int trig4_ug;
  int trig5_ug;
  int trig6_ug;
  int trig7_ug;
  int trig8_ug;
  int trig9_ug;
  int trig10_ug;
  int trig11_ug;
  int trig12_ug;
  int trig_or_ug;
  int l1accept;
  int notused63;
  int notused64;
  int l2fail;
  int l2pass;
  int l2start;
  int l2clear;
  int l2accept;
  int l3accept;
  int notused71;
  int notused72;
  int l2sec1_g;
  int l2sec2_g;
  int l2sec3_g;
  int l2sec4_g;
  int l2sec5_g;
  int l2sec6_g;
  int l2_or_g;
  int l2_ok_g;
  int trig1_lg;
  int trig2_lg;
  int trig3_lg;
  int trig4_lg;
  int trig5_lg;
  int trig6_lg;
  int trig7_lg;
  int trig8_lg;
  int trig9_lg;
  int trig10_lg;
  int trig11_lg;
  int trig12_lg;
  int notused93;
  int notused94;
  int ignore95;
  int ignore96;
};

class TRGS {
private:
  int nrows;
  struct TRGS_row *row_ptr;
public:
  TRGS(void) {
    return;
  }
  TRGS(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_CLOCK_UG(int row) {
    return ((row_ptr+row)->CLOCK_UG);
  }
  int get_FCUP_UG(int row) {
    return ((row_ptr+row)->FCUP_UG);
  }
  int get_Microsec(int row) {
    return ((row_ptr+row)->Microsec);
  }
  int get_random_ug(int row) {
    return ((row_ptr+row)->random_ug);
  }
  int get_MOR_ST(int row) {
    return ((row_ptr+row)->MOR_ST);
  }
  int get_MOR_PC(int row) {
    return ((row_ptr+row)->MOR_PC);
  }
  int get_MOR_PS(int row) {
    return ((row_ptr+row)->MOR_PS);
  }
  int get_MOR_TAC(int row) {
    return ((row_ptr+row)->MOR_TAC);
  }
  int get_MOR(int row) {
    return ((row_ptr+row)->MOR);
  }
  int get_PC(int row) {
    return ((row_ptr+row)->PC);
  }
  int get_PS(int row) {
    return ((row_ptr+row)->PS);
  }
  int get_TAC(int row) {
    return ((row_ptr+row)->TAC);
  }
  int get_ST(int row) {
    return ((row_ptr+row)->ST);
  }
  int get_hel_sync(int row) {
    return ((row_ptr+row)->hel_sync);
  }
  int get_clock_ug_2(int row) {
    return ((row_ptr+row)->clock_ug_2);
  }
  int get_fcup_ug_2(int row) {
    return ((row_ptr+row)->fcup_ug_2);
  }
  int get_CLOCK_G1(int row) {
    return ((row_ptr+row)->CLOCK_G1);
  }
  int get_FCUP_G1(int row) {
    return ((row_ptr+row)->FCUP_G1);
  }
  int get_NotUsed19(int row) {
    return ((row_ptr+row)->NotUsed19);
  }
  int get_random_g1(int row) {
    return ((row_ptr+row)->random_g1);
  }
  int get_MOR_ST_rg(int row) {
    return ((row_ptr+row)->MOR_ST_rg);
  }
  int get_MOR_PC_rg(int row) {
    return ((row_ptr+row)->MOR_PC_rg);
  }
  int get_MOR_PS_rg(int row) {
    return ((row_ptr+row)->MOR_PS_rg);
  }
  int get_MOR_TAC_rg(int row) {
    return ((row_ptr+row)->MOR_TAC_rg);
  }
  int get_MOR_rg(int row) {
    return ((row_ptr+row)->MOR_rg);
  }
  int get_PC_rg(int row) {
    return ((row_ptr+row)->PC_rg);
  }
  int get_PS_rg(int row) {
    return ((row_ptr+row)->PS_rg);
  }
  int get_TAC_rg(int row) {
    return ((row_ptr+row)->TAC_rg);
  }
  int get_ST_rg(int row) {
    return ((row_ptr+row)->ST_rg);
  }
  int get_random_g1_2(int row) {
    return ((row_ptr+row)->random_g1_2);
  }
  int get_clock_g1_2(int row) {
    return ((row_ptr+row)->clock_g1_2);
  }
  int get_fcup_g1_2(int row) {
    return ((row_ptr+row)->fcup_g1_2);
  }
  int get_CLOCK_G2(int row) {
    return ((row_ptr+row)->CLOCK_G2);
  }
  int get_FCUP_G2(int row) {
    return ((row_ptr+row)->FCUP_G2);
  }
  int get_trig_or_g2(int row) {
    return ((row_ptr+row)->trig_or_g2);
  }
  int get_random_g2(int row) {
    return ((row_ptr+row)->random_g2);
  }
  int get_NotUsed37(int row) {
    return ((row_ptr+row)->NotUsed37);
  }
  int get_NotUsed38(int row) {
    return ((row_ptr+row)->NotUsed38);
  }
  int get_NotUsed39(int row) {
    return ((row_ptr+row)->NotUsed39);
  }
  int get_NotUsed40(int row) {
    return ((row_ptr+row)->NotUsed40);
  }
  int get_MOR_lg(int row) {
    return ((row_ptr+row)->MOR_lg);
  }
  int get_NotUsed42(int row) {
    return ((row_ptr+row)->NotUsed42);
  }
  int get_NotUsed43(int row) {
    return ((row_ptr+row)->NotUsed43);
  }
  int get_NotUsed44(int row) {
    return ((row_ptr+row)->NotUsed44);
  }
  int get_NotUsed45(int row) {
    return ((row_ptr+row)->NotUsed45);
  }
  int get_random_g2_2(int row) {
    return ((row_ptr+row)->random_g2_2);
  }
  int get_clock_g2_2(int row) {
    return ((row_ptr+row)->clock_g2_2);
  }
  int get_fcup_g2_2(int row) {
    return ((row_ptr+row)->fcup_g2_2);
  }
  int get_trig1_ug(int row) {
    return ((row_ptr+row)->trig1_ug);
  }
  int get_trig2_ug(int row) {
    return ((row_ptr+row)->trig2_ug);
  }
  int get_trig3_ug(int row) {
    return ((row_ptr+row)->trig3_ug);
  }
  int get_trig4_ug(int row) {
    return ((row_ptr+row)->trig4_ug);
  }
  int get_trig5_ug(int row) {
    return ((row_ptr+row)->trig5_ug);
  }
  int get_trig6_ug(int row) {
    return ((row_ptr+row)->trig6_ug);
  }
  int get_trig7_ug(int row) {
    return ((row_ptr+row)->trig7_ug);
  }
  int get_trig8_ug(int row) {
    return ((row_ptr+row)->trig8_ug);
  }
  int get_trig9_ug(int row) {
    return ((row_ptr+row)->trig9_ug);
  }
  int get_trig10_ug(int row) {
    return ((row_ptr+row)->trig10_ug);
  }
  int get_trig11_ug(int row) {
    return ((row_ptr+row)->trig11_ug);
  }
  int get_trig12_ug(int row) {
    return ((row_ptr+row)->trig12_ug);
  }
  int get_trig_or_ug(int row) {
    return ((row_ptr+row)->trig_or_ug);
  }
  int get_l1accept(int row) {
    return ((row_ptr+row)->l1accept);
  }
  int get_notused63(int row) {
    return ((row_ptr+row)->notused63);
  }
  int get_notused64(int row) {
    return ((row_ptr+row)->notused64);
  }
  int get_l2fail(int row) {
    return ((row_ptr+row)->l2fail);
  }
  int get_l2pass(int row) {
    return ((row_ptr+row)->l2pass);
  }
  int get_l2start(int row) {
    return ((row_ptr+row)->l2start);
  }
  int get_l2clear(int row) {
    return ((row_ptr+row)->l2clear);
  }
  int get_l2accept(int row) {
    return ((row_ptr+row)->l2accept);
  }
  int get_l3accept(int row) {
    return ((row_ptr+row)->l3accept);
  }
  int get_notused71(int row) {
    return ((row_ptr+row)->notused71);
  }
  int get_notused72(int row) {
    return ((row_ptr+row)->notused72);
  }
  int get_l2sec1_g(int row) {
    return ((row_ptr+row)->l2sec1_g);
  }
  int get_l2sec2_g(int row) {
    return ((row_ptr+row)->l2sec2_g);
  }
  int get_l2sec3_g(int row) {
    return ((row_ptr+row)->l2sec3_g);
  }
  int get_l2sec4_g(int row) {
    return ((row_ptr+row)->l2sec4_g);
  }
  int get_l2sec5_g(int row) {
    return ((row_ptr+row)->l2sec5_g);
  }
  int get_l2sec6_g(int row) {
    return ((row_ptr+row)->l2sec6_g);
  }
  int get_l2_or_g(int row) {
    return ((row_ptr+row)->l2_or_g);
  }
  int get_l2_ok_g(int row) {
    return ((row_ptr+row)->l2_ok_g);
  }
  int get_trig1_lg(int row) {
    return ((row_ptr+row)->trig1_lg);
  }
  int get_trig2_lg(int row) {
    return ((row_ptr+row)->trig2_lg);
  }
  int get_trig3_lg(int row) {
    return ((row_ptr+row)->trig3_lg);
  }
  int get_trig4_lg(int row) {
    return ((row_ptr+row)->trig4_lg);
  }
  int get_trig5_lg(int row) {
    return ((row_ptr+row)->trig5_lg);
  }
  int get_trig6_lg(int row) {
    return ((row_ptr+row)->trig6_lg);
  }
  int get_trig7_lg(int row) {
    return ((row_ptr+row)->trig7_lg);
  }
  int get_trig8_lg(int row) {
    return ((row_ptr+row)->trig8_lg);
  }
  int get_trig9_lg(int row) {
    return ((row_ptr+row)->trig9_lg);
  }
  int get_trig10_lg(int row) {
    return ((row_ptr+row)->trig10_lg);
  }
  int get_trig11_lg(int row) {
    return ((row_ptr+row)->trig11_lg);
  }
  int get_trig12_lg(int row) {
    return ((row_ptr+row)->trig12_lg);
  }
  int get_notused93(int row) {
    return ((row_ptr+row)->notused93);
  }
  int get_notused94(int row) {
    return ((row_ptr+row)->notused94);
  }
  int get_ignore95(int row) {
    return ((row_ptr+row)->ignore95);
  }
  int get_ignore96(int row) {
    return ((row_ptr+row)->ignore96);
  }
};

struct TRKS_row {
  int trk_lev;
  float beta;
  float st_time;
  float cc_time;
  float sc_time;
  float ec_time;
  int st_id;
  int cc_id;
  int sc_id;
  int ec_id;
};

class TRKS {
private:
  int nrows;
  struct TRKS_row *row_ptr;
public:
  TRKS(void) {
    return;
  }
  TRKS(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_trk_lev(int row) {
    return ((row_ptr+row)->trk_lev);
  }
  float get_beta(int row) {
    return ((row_ptr+row)->beta);
  }
  float get_st_time(int row) {
    return ((row_ptr+row)->st_time);
  }
  float get_cc_time(int row) {
    return ((row_ptr+row)->cc_time);
  }
  float get_sc_time(int row) {
    return ((row_ptr+row)->sc_time);
  }
  float get_ec_time(int row) {
    return ((row_ptr+row)->ec_time);
  }
  int get_st_id(int row) {
    return ((row_ptr+row)->st_id);
  }
  int get_cc_id(int row) {
    return ((row_ptr+row)->cc_id);
  }
  int get_sc_id(int row) {
    return ((row_ptr+row)->sc_id);
  }
  int get_ec_id(int row) {
    return ((row_ptr+row)->ec_id);
  }
};

struct TRL1_row {
  int fit_flags;
  int hits_hbt;
  int hits_tbt;
  float x;
  float y;
  float z;
  float cx;
  float cy;
  float cz;
  float tlen;
};

class TRL1 {
private:
  int nrows;
  struct TRL1_row *row_ptr;
public:
  TRL1(void) {
    return;
  }
  TRL1(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_fit_flags(int row) {
    return ((row_ptr+row)->fit_flags);
  }
  int get_hits_hbt(int row) {
    return ((row_ptr+row)->hits_hbt);
  }
  int get_hits_tbt(int row) {
    return ((row_ptr+row)->hits_tbt);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_cx(int row) {
    return ((row_ptr+row)->cx);
  }
  float get_cy(int row) {
    return ((row_ptr+row)->cy);
  }
  float get_cz(int row) {
    return ((row_ptr+row)->cz);
  }
  float get_tlen(int row) {
    return ((row_ptr+row)->tlen);
  }
};

struct TRPB_row {
  int hits_tbt;
  float x;
  float y;
  float z;
  float cx;
  float cy;
  float cz;
  float tlen;
};

class TRPB {
private:
  int nrows;
  struct TRPB_row *row_ptr;
public:
  TRPB(void) {
    return;
  }
  TRPB(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_hits_tbt(int row) {
    return ((row_ptr+row)->hits_tbt);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_cx(int row) {
    return ((row_ptr+row)->cx);
  }
  float get_cy(int row) {
    return ((row_ptr+row)->cy);
  }
  float get_cz(int row) {
    return ((row_ptr+row)->cz);
  }
  float get_tlen(int row) {
    return ((row_ptr+row)->tlen);
  }
};

struct UNUS_row {
  int NDCUN;
  int IDCUN;
  int NSCUN;
  int ISCUN;
  int NCCUN;
  int ICCUN;
  int NECUN;
  int IECUN;
};

class UNUS {
private:
  int nrows;
  struct UNUS_row *row_ptr;
public:
  UNUS(void) {
    return;
  }
  UNUS(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_NDCUN(int row) {
    return ((row_ptr+row)->NDCUN);
  }
  int get_IDCUN(int row) {
    return ((row_ptr+row)->IDCUN);
  }
  int get_NSCUN(int row) {
    return ((row_ptr+row)->NSCUN);
  }
  int get_ISCUN(int row) {
    return ((row_ptr+row)->ISCUN);
  }
  int get_NCCUN(int row) {
    return ((row_ptr+row)->NCCUN);
  }
  int get_ICCUN(int row) {
    return ((row_ptr+row)->ICCUN);
  }
  int get_NECUN(int row) {
    return ((row_ptr+row)->NECUN);
  }
  int get_IECUN(int row) {
    return ((row_ptr+row)->IECUN);
  }
};

struct VERT_row {
  int vertex;
  int trk1;
  int trk2;
  float x;
  float y;
  float z;
  float sepd;
};

class VERT {
private:
  int nrows;
  struct VERT_row *row_ptr;
public:
  VERT(void) {
    return;
  }
  VERT(int bank_index);
  int get_nrows(void) {
    return(nrows);
  }
  int get_vertex(int row) {
    return ((row_ptr+row)->vertex);
  }
  int get_trk1(int row) {
    return ((row_ptr+row)->trk1);
  }
  int get_trk2(int row) {
    return ((row_ptr+row)->trk2);
  }
  float get_x(int row) {
    return ((row_ptr+row)->x);
  }
  float get_y(int row) {
    return ((row_ptr+row)->y);
  }
  float get_z(int row) {
    return ((row_ptr+row)->z);
  }
  float get_sepd(int row) {
    return ((row_ptr+row)->sepd);
  }
};

