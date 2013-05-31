/*
 *  Random.cpp
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Tue May 24 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 *  Obtained from Sander van Doorn
 *
 *
 */
//----------------------------------------------------------------------------------
#include "Random.h"
long int idum;
#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)
//----------------------------------------------------------------------------------
double uniform()
  {
  static int inext,inextp;
  static long ma[56];
  static int iff=0;
  long mj,mk;
  int i,ii,k;
  if (idum < 0 || iff == 0) 
    {
    iff=1;
    mj=MSEED-(idum < 0 ? -idum : idum);
    mj %= MBIG;
    ma[55]=mj;
    mk=1;
    for (i=1;i<=54;i++) 
      {
      ii=(21*i) % 55;
      ma[ii]=mk;
      mk=mj-mk;
      if (mk < MZ) mk += MBIG;
      mj=ma[ii];
      }
    for (k=1;k<=4;k++)
      for (i=1;i<=55;i++) 
        {
        ma[i] -= ma[1+(i+30) % 55];
        if (ma[i] < MZ) ma[i] += MBIG;
        }
    inext=0;
    inextp=31;
    idum=1;
    }
  if (++inext == 56) inext=1;
  if (++inextp == 56) inextp=1;
  mj=ma[inext]-ma[inextp];
  if (mj < MZ) mj += MBIG;
  ma[inext]=mj;
  return mj*FAC;
  } //End of: double Uniform(void)

#undef MBIG
#undef MSEED
#undef MZ
#undef FAC
//----------------------------------------------------------------------------------
double gasdev()
  {
  static int iset=0;
  static double gset;
  double fac,r,v1,v2;
  double uniform();
  if  (iset == 0) 
    {
    do 
      {
      v1=2.0*uniform()-1.0;
      v2=2.0*uniform()-1.0;
      r=v1*v1+v2*v2;
      } 
    while (r >= 1.0);

    fac=sqrt(-2.0*log(r)/r);
    gset=v1*fac;
    iset=1;
    return v2*fac;
    } //End of: if (iset == 0) 
    else 
    {
    iset=0;
    return gset;
    } //End of: if (iset == 0) ELSE-part
  } //End of: double gasdev(void)
//----------------------------------------------------------------------------------
void setSeed(const int& seed) 
  { 
  idum = long(-abs(seed));
  for (int i=0; i<100; i++) uniform();
  return;
  } 
//----------------------------------------------------------------------------------
double normal(const double& mean,const double& stdev)
  {
  return gasdev()*stdev + mean;
  } 
//----------------------------------------------------------------------------------
int randomNumber(const int& N)
  {	
  double x;
  int out;
  x=floor(uniform()*N);
  out=int (x);
  return out;
  } 
//----------------------------------------------------------------------------------
int rando(const int& N)
  {	
  double x;
  int out;
  x=floor(uniform()*N);
  out=int (x);
  return out;
  } 
//----------------------------------------------------------------------------------
