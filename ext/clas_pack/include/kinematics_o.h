
class vector3_o{
public:
  vector3_o();
  vector3_o(vector3_t vec);
  void init(vector3_t vec);
  vector3_o operator+(vector3_o &vec); // add
  vector3_o operator-(vector3_o &vec); // subtract
  float operator*(vector3_o &vec); // dot product
  vector3_o operator/(vector3_o &vec); // cross product
  float mag();
  float magsq();
  void print(FILE *fp);
  vector3_t v;
private:
};

class vector4_o{
public:
  vector4_o();
  vector4_o(vector4_t vec);
  void init(vector4_t vec);
  vector4_o operator+(vector4_o &vec); // add
  vector4_o operator-(vector4_o &vec); // subtract
  float operator*(vector4_o &vec); // dot product
  float mag();
  float magsq();
  void print(FILE *fp);
  vector4_t vector4_c();
  float t;
  vector3_o space;
private:
};

