// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TMiniDSTClass.cc,v 1.4 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
// TMiniDSTClass
//
// Specific to Gagik's Analysis.
//



#include "TMiniDSTClass.h"

ClassImp(TMiniDSTClass)


  //
TMiniDSTClass::TMiniDSTClass()
{
  Zero();
}

TMiniDSTClass::~TMiniDSTClass(){}

void TMiniDSTClass::Zero(){
  fPartID = 0;
  fStatus = 0;
  fPq = 0.;
  fPb = 0.;
  fPx = 0.;
  fPy = 0.;
  fPz = 0.;
  fVxp = 0.;
  fVyp = 0.;
  fVzp = 0.;
  fThL = 0.;
  fPhL = 0.;
  fXiec = 0.;
  fYiec = 0.;
  fEff = 0.;
  fEdp = 0.;
}

TMiniDSTClass::TMiniDSTClass(TMiniDSTClass *inst_class)
{
  fPartID = inst_class->GetPartID() ;
  fStatus = inst_class->GetStatus() ;
  fPq = inst_class->GetPq() ;
  fPb = inst_class->GetPb() ;
  fPx = inst_class->GetPx() ;
  fPy = inst_class->GetPy() ;
  fPz = inst_class->GetPz() ;
  fVxp = inst_class->GetVxp() ;
  fVyp = inst_class->GetVyp() ;
  fVzp = inst_class->GetVzp() ;
  fThL = inst_class->GetThL() ;
  fPhL = inst_class->GetPhL() ;
  fEff = inst_class->GetEff() ;
  fEdp = inst_class->GetEdp() ;
}

void   TMiniDSTClass::CopyFrom(TMiniDSTClass *inst_class)
{
  fPartID = inst_class->GetPartID() ;
  fStatus = inst_class->GetStatus() ;
  fPq = inst_class->GetPq() ;
  fPb = inst_class->GetPb() ;
  fPx = inst_class->GetPx() ;
  fPy = inst_class->GetPy() ;
  fPz = inst_class->GetPz() ;
  fVxp = inst_class->GetVxp() ;
  fVyp = inst_class->GetVyp() ;
  fVzp = inst_class->GetVzp() ;
  fThL = inst_class->GetThL() ;
  fPhL = inst_class->GetPhL() ;
  fEff = inst_class->GetEff() ;
  fEdp = inst_class->GetEdp() ;
}

void   TMiniDSTClass::SetFromArray(void *array)
{
  int    *int_ptr;
  float  *float_ptr;

  int_ptr    = (int *) array;
  float_ptr  = (float *) array;
  float_ptr++;
  float_ptr++;

  fPartID = (int) *int_ptr; int_ptr++;
  fStatus = (int) *int_ptr; int_ptr++;
  
  fPq  = (float) *float_ptr; float_ptr++;
  fPb  = (float) *float_ptr; float_ptr++;
  fPx  = (float) *float_ptr; float_ptr++;
  fPy  = (float) *float_ptr; float_ptr++;
  fPz  = (float) *float_ptr; float_ptr++;
  fVxp = (float) *float_ptr; float_ptr++;
  fVyp = (float) *float_ptr; float_ptr++;
  fVzp = (float) *float_ptr; float_ptr++;
  fThL = (float) *float_ptr; float_ptr++;
  fPhL = (float) *float_ptr; float_ptr++;
  fEff = (float) *float_ptr; float_ptr++;
  fEdp = (float) *float_ptr; float_ptr++;
}

void   TMiniDSTClass::GetArray(void *array)
{
  
  int    *int_ptr;
  float  *float_ptr;

  int_ptr    = (int *) array;
  float_ptr  = (float *) array;
  float_ptr++;
  float_ptr++;

  *int_ptr = (int) fPartID ; int_ptr++;
  *int_ptr = (int) fStatus; int_ptr++;
  
  *float_ptr  =  fPq ; float_ptr++;
  *float_ptr  =  fPb ; float_ptr++;
  *float_ptr  =  fPx; float_ptr++;
  *float_ptr  =  fPy; float_ptr++;
  *float_ptr  =  fPz; float_ptr++;
  *float_ptr  =  fVxp; float_ptr++;
  *float_ptr  =  fVyp; float_ptr++;
  *float_ptr  =  fVzp ; float_ptr++;
  *float_ptr  =  fThL; float_ptr++;
  *float_ptr  =  fPhL; float_ptr++;
  *float_ptr  =  fEff; float_ptr++;
  *float_ptr  =  fEdp; float_ptr++;
  
}


Int_t    TMiniDSTClass::GetPartID(){ return fPartID;}
Int_t    TMiniDSTClass::GetStatus(){return fStatus;}
Float_t  TMiniDSTClass::GetPq()    {return fPq;}
Float_t  TMiniDSTClass::GetPb()    {return fPb;}
Float_t  TMiniDSTClass::GetPx()    {return fPx;}
Float_t  TMiniDSTClass::GetPy()    {return fPy;}
Float_t  TMiniDSTClass::GetPz()    {return fPz;}
Float_t  TMiniDSTClass::GetVxp()   {return fVxp;}
Float_t  TMiniDSTClass::GetVyp()   {return fVyp;}
Float_t  TMiniDSTClass::GetVzp()   {return fVzp;}
Float_t  TMiniDSTClass::GetThL()   {return fThL;}
Float_t  TMiniDSTClass::GetPhL()   {return fPhL;}
Float_t  TMiniDSTClass::GetEff()   {return fEff;}
Float_t  TMiniDSTClass::GetEdp()   {return fEdp;}
Float_t  TMiniDSTClass::GetXiec(){ return fXiec; }
Float_t  TMiniDSTClass::GetYiec(){ return fYiec;}


void   TMiniDSTClass::Print()
{
  cout << setw(5) << "PartID : " << setw(8) <<  fPartID << endl ;
  cout << setw(5) << "Status : " << setw(8) << fStatus << endl;
  cout << setw(5) << "    Pq : " << setw(8) << fPq<< endl;
  cout << setw(5) << "    Pb : " << setw(8) << fPb<< endl;
  cout << setw(5) << "    Px : " << setw(8) << fPx << endl;
  cout << setw(5) << "    Py : " << setw(8) << fPy<< endl;
  cout << setw(5) << "    Pz : " << setw(8) << fPz<< endl;
  cout << setw(5) << "   Vxp : " << setw(8) << fVxp<< endl;
  cout << setw(5) << "   Vyp : " << setw(8) << fVyp<< endl;
  cout << setw(5) << "   Vzp : " << setw(8) << fVzp << endl;
  cout << setw(5) << "   ThL : " << setw(8) << fThL<< endl;
  cout << setw(5) << "   PhL : " << setw(8) << fPhL<< endl;
  cout << setw(5) << "   Eff : " << setw(8) << fEff<< endl;
  cout << setw(5) << "   Edp : " << setw(8) << fEdp << endl;  
}

TVector3  TMiniDSTClass::Get3Vector()
{
  TVector3 vect;
  vect.SetXYZ(fPx,fPy,fPz);
  return vect;
}

Float_t   TMiniDSTClass::GetP2()
{
  return (fPx*fPx + fPy*fPy + fPz*fPz );
}
Float_t   TMiniDSTClass::GetP()
{
  return sqrt(GetP2());
}
