#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "standardwhitenoisesystemparameters.h"
#pragma GCC diagnostic pop

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

std::string ribi::kalman::StandardWhiteNoiseSystemParameters::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::kalman::StandardWhiteNoiseSystemParameters::GetVersionHistory() noexcept
{
  return {
    "2013-04-28: version 1.0: initial version"
  };
}

bool ribi::kalman::StandardWhiteNoiseSystemParameters::IsAboutEqual(
  const StandardWhiteNoiseSystemParameters& lhs, const StandardWhiteNoiseSystemParameters& rhs) noexcept
{
  return
       Matrix::MatricesAreAboutEqual(lhs.GetControl(),rhs.GetControl())
    && Matrix::VectorsAreAboutEqual(lhs.GetInitialState(),rhs.GetInitialState())
    && Matrix::VectorsAreAboutEqual(lhs.GetMeasurementNoise(),rhs.GetMeasurementNoise())
    && Matrix::VectorsAreAboutEqual(lhs.GetProcessNoise(),rhs.GetProcessNoise())
    && Matrix::MatricesAreAboutEqual(lhs.GetStateTransition(),rhs.GetStateTransition());
}
