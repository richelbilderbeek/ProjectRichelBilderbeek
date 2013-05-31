
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "alphabetagammafilter.h"

#include <cassert>

AlphaBetaGammaFilter::AlphaBetaGammaFilter(
  const double alpha,
  const double beta,
  const double gamma,
  const double dt)
  : m_acceleration(0.0),
    m_alpha(alpha),
    m_beta(beta),
    m_dt(dt),
    m_gamma(gamma),
    m_position(0.0),
    m_velocity(0.0)
{
  assert(m_alpha >= 0.0 && m_alpha <  1.0);
  assert(m_beta  >= 0.0 && m_beta  <= 2.0); //beta > 1.0 amplifies noise
  assert(4.0 - (2.0 * m_alpha - m_beta) > 0.0);
  assert(m_dt != 0.0);
}


double AlphaBetaGammaFilter::Estimate(const double measurement)
{
  const double output_predicted = m_position + ( m_velocity * m_dt );
  const double prediction_error = measurement - output_predicted;
  m_position = output_predicted + (m_alpha * prediction_error);
  m_velocity += (m_beta * prediction_error / m_dt);
  m_acceleration += (m_gamma * 2.0 * prediction_error / (m_dt * m_dt) );
  return m_position;
}

const std::string AlphaBetaGammaFilter::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> AlphaBetaGammaFilter::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-05-25: version 1.0: initial version");
  return v;
}
