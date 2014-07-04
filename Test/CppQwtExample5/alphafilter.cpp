#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "alphafilter.h"

#include <cassert>

AlphaFilter::AlphaFilter(
  const double alpha,
  const double dt)
  : m_alpha(alpha),
    m_dt(dt),
    m_output(0.0)
{
  //assert(m_alpha >= 0.0 && m_alpha <  1.0);
  //assert(m_beta  >= 0.0 && m_beta  <= 2.0); //beta > 1.0 amplifies noise
  //assert(4.0 - (2.0 * m_alpha - m_beta) > 0.0);
  assert(m_dt != 0.0);
}


double AlphaFilter::Estimate(const double input)
{
  const double difference = input - m_output;

  m_output += m_alpha * difference;

  return m_output;
}
