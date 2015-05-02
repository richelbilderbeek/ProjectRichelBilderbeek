#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "alphabetafilter.h"

#include <cassert>

AlphaBetaFilter::AlphaBetaFilter(
  const double alpha,
  const double beta,
  const double dt)
  : m_alpha(alpha),
    m_beta(beta),
    m_dt(dt),
    m_hidden(0.0),
    m_output(0.0)
{
  //assert(m_alpha >= 0.0 && m_alpha <  1.0);
  //assert(m_beta  >= 0.0 && m_beta  <= 2.0); //beta > 1.0 amplifies noise
  //assert(4.0 - (2.0 * m_alpha - m_beta) > 0.0);
  assert(m_dt != 0.0);
}


double AlphaBetaFilter::Estimate(const double input)
{
  double new_output = m_output + ( m_hidden * m_dt );
  double new_hidden = m_hidden;

  const double difference = input - new_output;

  new_output += m_alpha * difference;
  new_hidden += m_beta  * difference / m_dt;

  m_output = new_output;
  m_hidden = new_hidden;

  return m_output;
}
