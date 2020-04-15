//$Id: tagruncontrol.h,v 1.9 2008/03/16 04:33:21 fklein Exp $

/* structure of common/tagruncontrol/ */
typedef struct {
  float Beam_energy;
  float PS_current;
  float tager_current;
  float torus_current;
  int tagger_do_t_trans;
  int use_tgtlr;
  int et_map_from_db;
} tagRunControl_t;

extern tagRunControl_t tagruncontrol_; /* common/tagruncontrol/ */
