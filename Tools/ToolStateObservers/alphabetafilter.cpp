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
    m_slope(0.0),
    m_output(0.0)
{
  assert(m_alpha >= 0.0 && m_alpha <  1.0);
  assert(m_beta  >= 0.0 && m_beta  <= 2.0); //beta > 1.0 amplifies noise
  assert(4.0 - (2.0 * m_alpha - m_beta) > 0.0);
  assert(m_dt != 0.0);
}


double AlphaBetaFilter::Estimate(const double measurement)
{
  const double output_predicted = m_output + ( m_slope * m_dt );
  const double prediction_error = measurement - output_predicted;
  const double output_corrected = output_predicted + (m_alpha * prediction_error);
  m_output = output_corrected;
  m_slope += (m_beta * prediction_error / m_dt);
  return m_output;
}
