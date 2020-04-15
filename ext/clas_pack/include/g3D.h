/*
 * g3D.h  -- virtual 3D graphics library
*/

extern int g3D_noLines;
extern int g3D_noPoints;

void g3D_Line(double x1,double y1,double z1,double x2,double y2,double z2);
void g3D_LineC(int view,double x1,double y1,double z1,double x2,double y2,double z2);
void g3D_LineD(double x,double y,double z,double dx,double dy,double dz);
void g3D_PointC(int View,double x,double y,double z);
void g3D_Point(double x,double y,double z);
void g3D_flush(void);
void g3D_Color(int col);
void g3D_SetColor(const char* colorName);

/* end file */
