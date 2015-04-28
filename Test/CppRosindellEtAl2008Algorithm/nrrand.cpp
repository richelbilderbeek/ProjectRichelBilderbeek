#include "nrrand.h"

#include <cmath>
#include <cstdlib>
#include <boost/numeric/conversion/cast.hpp>
NRrand::NRrand(const int seed) noexcept
{
  std::srand(seed);
  m_normflag = true;
}

double NRrand::GetRandomFraction() noexcept
{
  return(
    static_cast<double>(std::rand())
    /static_cast<double>(RAND_MAX)
  );
}

int NRrand::GetRandomInt(const int max) noexcept
{
  return
    boost::numeric_cast<int>(
      std::floor(GetRandomFraction()*(max+1))
    );
}

double NRrand::GetRandomNormal() noexcept
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
    const double fac=sqrt(-2.0*log(r2)/r2);
    m_lastresult = xx*fac;
    const double result = yy*fac;
    m_normflag = false;
    return result;
  }
  else
  {
    m_normflag = true;
    return m_lastresult;
  }
}
