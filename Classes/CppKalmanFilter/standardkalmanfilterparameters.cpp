#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "standardkalmanfilterparameters.h"
#pragma GCC diagnostic pop

#include <cassert>

#include "matrix.h"

ribi::kalman::StandardKalmanFilterParameters::StandardKalmanFilterParameters(
  const boost::numeric::ublas::matrix<double>& control,
  const boost::numeric::ublas::matrix<double>& estimated_measurement_noise,
  const boost::numeric::ublas::matrix<double>& estimated_process_noise_covariance,
  const boost::numeric::ublas::matrix<double>& initial_covariance_estimate,
  const boost::numeric::ublas::vector<double>& initial_state_estimate,
  const boost::numeric::ublas::matrix<double>& observation,
  const boost::numeric::ublas::matrix<double>& state_transition)
  : KalmanFilterParameters{control,initial_state_estimate,observation,state_transition},
    m_estimated_measurement_noise{estimated_measurement_noise},
    m_estimated_process_noise_covariance{estimated_process_noise_covariance},
    m_initial_covariance_estimate{initial_covariance_estimate}
{
  #ifndef NDEBUG
  //Check for correct dimensionality
  const std::size_t sz = GetInitialStateEstimate().size();
  //assert(sz >= 0); //Inevitable for std::size_t
  assert(GetEstimatedMeasurementNoise().size1() == sz);
  assert(GetEstimatedMeasurementNoise().size2() == sz);
  assert(GetEstimatedProcessNoiseCovariance().size1() == sz);
  assert(GetEstimatedProcessNoiseCovariance().size2() == sz);
  assert(GetInitialCovarianceEstimate().size1() == sz);
  assert(GetInitialCovarianceEstimate().size2() == sz);
  #endif
}

std::string ribi::kalman::StandardKalmanFilterParameters::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::kalman::StandardKalmanFilterParameters::GetVersionHistory() noexcept
{
  return {
    "2013-04-28: version 1.0: initial version",
    "2013-05-03: version 1.1: inhertic from KalmanFilterParameters"
  };
}

bool ribi::kalman::StandardKalmanFilterParameters::HasParameterType(const KalmanFilterParameterType type) noexcept
{
  return
       type == KalmanFilterParameterType::control
    || type == KalmanFilterParameterType::estimated_measurement_noise
    || type == KalmanFilterParameterType::estimated_process_noise_covariance
    || type == KalmanFilterParameterType::initial_covariance_estimate
    || type == KalmanFilterParameterType::initial_state_estimate
    || type == KalmanFilterParameterType::observation
    || type == KalmanFilterParameterType::state_transition;
}

bool ribi::kalman::StandardKalmanFilterParameters::IsAboutEqual(const StandardKalmanFilterParameters& lhs, const StandardKalmanFilterParameters& rhs) noexcept
{
  return
       Matrix::MatricesAreAboutEqual(lhs.GetControl(),rhs.GetControl())
    && Matrix::MatricesAreAboutEqual(lhs.GetEstimatedMeasurementNoise(),rhs.GetEstimatedMeasurementNoise())
    && Matrix::MatricesAreAboutEqual(lhs.GetInitialCovarianceEstimate(),rhs.GetInitialCovarianceEstimate())
    && Matrix::VectorsAreAboutEqual(lhs.GetInitialStateEstimate(),rhs.GetInitialStateEstimate())
    && Matrix::MatricesAreAboutEqual(lhs.GetObservation(),rhs.GetObservation())
    && Matrix::MatricesAreAboutEqual(lhs.GetEstimatedProcessNoiseCovariance(),rhs.GetEstimatedProcessNoiseCovariance())
    && Matrix::MatricesAreAboutEqual(lhs.GetStateTransition(),rhs.GetStateTransition());
}
