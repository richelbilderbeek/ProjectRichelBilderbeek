#include "alphabetafilter.h"

#include <cassert>

ribi::AlphaBetaFilter::AlphaBetaFilter(
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


void ribi::AlphaBetaFilter::Update(const double measurement)
{
  const double output_predicted = m_output + ( m_slope * m_dt );
  const double prediction_error = measurement - output_predicted;
  const double output_corrected = output_predicted + (m_alpha * prediction_error);
  m_output = output_corrected;
  m_slope += (m_beta * prediction_error / m_dt);
}

const std::string ribi::AlphaBetaFilter::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::AlphaBetaFilter::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-05-25: version 1.0: initial version");
  v.push_back("2013-06-18: version 1.1: derive from FloatingPointStateObserver");
  return v;
}
