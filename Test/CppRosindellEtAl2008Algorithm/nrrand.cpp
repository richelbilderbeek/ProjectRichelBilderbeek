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
  //Avoid using std::rand:
  // [1] Bjarne Stroustrup. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. 40.8[15]: 'Prefer a random number class for a particular distribution over direct use of rand()'
  // [2] Stephan T. Lavavej. 'rand() Considered Harmful'. 2013. GoingNative 2013
  // [3] Bjarne Stroustrup. The C++ Programming Language (4th edition). 2013. ISBN: 978-0-321-56384-2. 40.7.4: 'Producing a random number generator isn't easy, and unfortunately not all systems deliver a good rand()'
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
