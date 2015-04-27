#include "nrrand.h"

#include <cmath>
#include <cstdlib>
#include <boost/numeric/conversion/cast.hpp>
NRrand::NRrand(const int seed)
{
  std::srand(seed);
  m_normflag = true;
}

// returns a uniform random number in (0,1)
double NRrand::GetRandomFraction()
{
  return(
    static_cast<double>(std::rand())
    /static_cast<double>(RAND_MAX)
  );
}

// returns an integer between 0 and max
int NRrand::GetRandomInt(const int max)
{
  return
    boost::numeric_cast<int>(
      std::floor(GetRandomFraction()*(max+1))
    );
}

// returns normal deviates
double NRrand::GetRandomNormal()
{
    if (m_normflag)
    {
        double r2 = 2;
        double xx;double yy;
        while (r2>1)
        {
            xx=2.0*GetRandomFraction()-1.0;
            yy=2.0*GetRandomFraction()-1.0;
            r2=(xx*xx)+(yy*yy);
        }
        double fac=sqrt(-2.0*log(r2)/r2);
        m_lastresult = xx*fac;
        double result = yy*fac;
        m_normflag = false;
        return result;
    }
    else
    {
        m_normflag = true;
        return m_lastresult;
    }
}
