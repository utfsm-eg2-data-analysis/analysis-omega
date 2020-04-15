class pwa_amp{
 public:
  string name;
  complex<double> amp;
  int real_index;
  int img_index;
  int rank;
};

class pwaData{
private:
  integral acc_ni;
  integral raw_ni;
  matrix< double> error_matrix;
public:
  vector< pwa_amp > waves;
  pwaData();
  //pwaData( float likelihood, float low_mass, float high_mass, float low_t, float high_t, vector<string> &names, vector<complex<double> > &amps, matrix<double> &error_matrix,integral &acc_ni, integral &raw_ni);

  integral &raw_norm();
  int n_events;
  //time_t time_written;
  //pwaData(string names, complex *V, matrix<double> error_matrix, integral acc_ni, integral raw_ni);
  ~pwaData();
  pwaData(integral acc_ni, integral raw_ni);
  void print(ostream *os);
  int read(istream *is);
  int findstring(istream *is, string st);
  int read_val(istream *is, string st, float &low, float &high);
  int read_val(istream *is, string st, float &val);
  int read_val(istream *is, string st, int &val);

  float yield(vector<pwa_amp> waves);

  float rank(int waveno);


  float low_range;
  float high_range;
  float low_t;
  float high_t;

  float likelihood;
  int num_V;
  int n_rank;

};

ostream & operator<<(ostream &os, pwaData &data);
