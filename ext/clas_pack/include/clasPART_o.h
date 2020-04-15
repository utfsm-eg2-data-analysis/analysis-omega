#define NUM_PIDS 100

class part_o{
public:
  part_o();
  int fill_from_BOS(part_t part, int partno);
  void print(FILE *fp); /* C print routine */  
  vector3_o vert;
  vector4_o p;
  part_t part_c();
  //  float sc_energy(int particletype, int number);
  //  float ec_energy(int particletype, int number);
  //  cc01_t *cc_hit(int particletype, int number);
  //  scrc_t *sc_hit(int particletype, int number);
  //  echb_t *ec_hit(int particletype, int number);
  // match_o sc;
  // match_o ec;
  // match_o dc;
  // match_o cc;
private:
  int nchild;
  part_o *child;
  part_t part;
  tbid_t tbid;
};

class clasPID_o{
public:
  clasPID_o(); 
  clasPID_o(int pidno);
  ~clasPID_o();
  void set_default();
  int build_from_BOS(int pidno);
  /* total number of particles in the event */
  int nparticles();
  /* number of particles of that type in the event */
  int num(int particletype); 
  int nchar();
  int nneut();
  vector4_o beam();
  vector4_o target();
  vector3_o vert();
  void print(FILE *fp);
  /* number refers to if it is the first, second etc...
     particle of that type in the event */
  part_o &part(int particletype, int number);
private:
  vector4_o event_beam;
  vector4_o event_target;
  vector3_o event_vertex;
  int good_nums(int particletype, int number);
  int ncharged;
  int nneutral;
  int Num[NUM_PIDS];
  part_o *PartPtr[NUM_PIDS];
};




