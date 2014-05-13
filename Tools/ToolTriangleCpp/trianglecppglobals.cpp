#include "trianglecppglobals.h"

//p.first = epsilon
//p.second = splitter
ribi::tricpp::Global::Global(const std::pair<double,double>& p)
  :
    m_ccwerrboundA{( 3.0 +  16.0 * p.first) * p.first},
    m_ccwerrboundB{( 2.0 +  12.0 * p.first) * p.first},
    m_ccwerrboundC{( 9.0 +  64.0 * p.first) * p.first * p.first},
    m_epsilon{p.first},
    m_iccerrboundA{(10.0 +  96.0 * p.first) * p.first},
    m_iccerrboundB{( 4.0 +  48.0 * p.first) * p.first},
    m_iccerrboundC{(44.0 + 576.0 * p.first) * p.first * p.first},
    m_o3derrboundA{( 7.0 +  56.0 * p.first) * p.first},
    m_o3derrboundB{( 3.0 +  28.0 * p.first) * p.first},
    m_o3derrboundC{(26.0 + 288.0 * p.first) * p.first * p.first},
    m_resulterrbound{(3.0 +  8.0 * p.first) * p.first},
    m_splitter{p.second}
{

}

std::pair<double,double> ribi::tricpp::Global::CreateEpsilonAndSplitter() noexcept
{
  double lastcheck = 0.0;
  int every_other = 1;
  double epsilon = 1.0;
  double splitter = 1.0;
  double check = 1.0;
  /* Repeatedly divide `epsilon' by two until it is too small to add to      */
  /*   one without causing roundoff.  (Also check if the sum is equal to     */
  /*   the previous sum, for machines that round up instead of using exact   */
  /*   rounding.  Not that these routines will work on such machines.)       */
  do
  {
    lastcheck = check;
    epsilon *= 0.5;
    if (every_other)
    {
      splitter *= 2.0;
    }
    every_other = !every_other;
    check = 1.0 + epsilon;
  } while ((check != 1.0) && (check != lastcheck));
  splitter += 1.0;

  std::pair<double,double> p = std::make_pair(epsilon,splitter);
  return p;
}

