//---------------------------------------------------------------------------
/*
RosindellEtAl2008, refactoring an extension of Rosindel at al., 2008 [1]
Copyright (C) 2015 Richel Bilderbeek
Original version by James Rosindell

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRosindellEtAl2008.htm
//
//Article with original code:
//
// [1] Rosindell, James, Yan Wong, and Rampal S. Etienne.
//     "A coalescence approach to spatial neutral ecology."
//      Ecological Informatics 3.3 (2008): 259-271.
//---------------------------------------------------------------------------
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
    double r2{2.0};
    double xx{0.0};
    double yy{0.0};
    while (r2>1.0)
    {
      xx=2.0*GetRandomFraction()-1.0;
      yy=2.0*GetRandomFraction()-1.0;
      r2=(xx*xx)+(yy*yy);
    }
    const double fac{std::sqrt(-2.0*log(r2)/r2)};
    m_lastresult = xx*fac;
    const double result{yy*fac};
    m_normflag = false;
    return result;
  }
  else
  {
    m_normflag = true;
    return m_lastresult;
  }
}
