

#include "standardwhitenoisesystemparameters.h"

#include <cassert>
#include "matrix.h"

ribi::kalman::StandardWhiteNoiseSystemParameters::StandardWhiteNoiseSystemParameters(
  const boost::numeric::ublas::matrix<double>& control,
  const boost::numeric::ublas::vector<double>& initial_state,
  const boost::numeric::ublas::vector<double>& real_measurement_noise,
  const boost::numeric::ublas::vector<double>& real_process_noise,
  const boost::numeric::ublas::matrix<double>& state_transition)
  : WhiteNoiseSystemParameters(
      control,
      initial_state,
      real_measurement_noise,
      real_process_noise,
      state_transition)
{
  #ifndef NDEBUG
  #endif

}

const std::string ribi::kalman::StandardWhiteNoiseSystemParameters::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::kalman::StandardWhiteNoiseSystemParameters::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-04-28: version 1.0: initial version");
  return v;
}

bool ribi::kalman::StandardWhiteNoiseSystemParameters::IsAboutEqual(
  const StandardWhiteNoiseSystemParameters& lhs, const StandardWhiteNoiseSystemParameters& rhs)
{
  return
       Matrix::MatricesAreAboutEqual(lhs.GetControl(),rhs.GetControl())
    && Matrix::VectorsAreAboutEqual(lhs.GetInitialState(),rhs.GetInitialState())
    && Matrix::VectorsAreAboutEqual(lhs.GetMeasurementNoise(),rhs.GetMeasurementNoise())
    && Matrix::VectorsAreAboutEqual(lhs.GetProcessNoise(),rhs.GetProcessNoise())
    && Matrix::MatricesAreAboutEqual(lhs.GetStateTransition(),rhs.GetStateTransition());
}
