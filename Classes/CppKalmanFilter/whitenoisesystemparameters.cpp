

#include "whitenoisesystemparameters.h"

#include <cassert>
#include "matrix.h"

ribi::WhiteNoiseSystemParameters::WhiteNoiseSystemParameters(
  const boost::numeric::ublas::matrix<double>& control,
  const boost::numeric::ublas::vector<double>& initial_state,
  const boost::numeric::ublas::vector<double>& real_measurement_noise,
  const boost::numeric::ublas::vector<double>& real_process_noise,
  const boost::numeric::ublas::matrix<double>& state_transition)
  : m_control{control},
    m_initial_state{initial_state},
    m_real_measurement_noise{real_measurement_noise},
    m_real_process_noise{real_process_noise},
    m_state_transition{state_transition}
{
  #ifndef NDEBUG
  //Check for correct dimensionality
  const size_t sz = initial_state.size();
  //assert(sz >= 0); //Inevitable for std::size_t
  assert(m_control.size1() == sz);
  assert(m_control.size2() == sz);
  assert(m_initial_state.size() == sz);
  assert(m_real_measurement_noise.size() == sz);
  assert(m_real_process_noise.size() == sz);
  assert(m_state_transition.size1() == sz);
  assert(m_state_transition.size2() == sz);
  #endif
}

const std::string ribi::WhiteNoiseSystemParameters::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::WhiteNoiseSystemParameters::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-04-28: version 1.0: initial version");
  return v;
}

bool ribi::WhiteNoiseSystemParameters::IsAboutEqual(
  const WhiteNoiseSystemParameters& lhs, const WhiteNoiseSystemParameters& rhs)
{
  return
       Matrix::MatricesAreAboutEqual(lhs.GetControl(),rhs.GetControl())
    && Matrix::VectorsAreAboutEqual(lhs.GetInitialState(),rhs.GetInitialState())
    && Matrix::VectorsAreAboutEqual(lhs.GetMeasurementNoise(),rhs.GetMeasurementNoise())
    && Matrix::VectorsAreAboutEqual(lhs.GetProcessNoise(),rhs.GetProcessNoise())
    && Matrix::MatricesAreAboutEqual(lhs.GetStateTransition(),rhs.GetStateTransition());
}
