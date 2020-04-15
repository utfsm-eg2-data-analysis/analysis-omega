//$Id: tagtnorm.h,v 1.6 2006/03/15 14:53:17 pasyuk Exp $

typedef struct {
  int Nb_Tn;
  int Tn_ID[2000];
  float Tn_L_val[2][2000];
  float Tn_R_val[2][2000];
  float Mean_Tn_val[2][2000];
  float Diff_Tn_val[2][2000];
  float Tn_time[2][2000];
} tagtnorm_t;

extern tagtnorm_t tagtnorm_;

