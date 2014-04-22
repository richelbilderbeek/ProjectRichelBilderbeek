//---------------------------------------------------------------------------

#ifndef UnitRandomH
#define UnitRandomH
//---------------------------------------------------------------------------
#include <math.h>

class rnd
{
  private:
  static long int idum;
  static int MBIG;
  static int MSEED;
  static int MZ;
  static double FAC;


  public:
  //Returns a uniform random value from 0.0 to 1.0
  static double uniform()
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
  }

  static double gasdev()
  {
    static int iset=0;
    static double gset;
    double fac,r,v1,v2;
    //double uniform();
    uniform();
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
    }
    else
    {
      iset=0;
      return gset;
    }
  }
  //Sets the seed for the random number sequence
  static void SetSeed(const int& seed)
  {
    int i;
    idum = long(-std::abs(seed));
    for (i=0; i<100; i++) uniform();
  }
  //Returns a random number from a gaussian distrubution
  static double normal(const double& mean,const double& stdev)
  {
    return gasdev()*stdev + mean;
  }
  //Returns a random integer from 0 to N
  static int RandomNumber(const int& N)
  {
    double x;
    int out;
    x=std::floor(uniform()*N);
    out=int (x);
    return out;
  }
};

#endif
