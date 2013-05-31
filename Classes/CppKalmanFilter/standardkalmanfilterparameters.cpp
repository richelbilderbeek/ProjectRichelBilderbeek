#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "standardkalmanfilterparameters.h"

#include <cassert>

#include "matrix.h"

StandardKalmanFilterParameters::StandardKalmanFilterParameters(
  const boost::numeric::ublas::matrix<double>& control,
  const boost::numeric::ublas::matrix<double>& estimated_measurement_noise,
  const boost::numeric::ublas::matrix<double>& estimated_process_noise_covariance,
  const boost::numeric::ublas::matrix<double>& initial_covariance_estimate,
  const boost::numeric::ublas::vector<double>& initial_state_estimate,
  const boost::numeric::ublas::matrix<double>& observation,
  const boost::numeric::ublas::matrix<double>& state_transition)
  : KalmanFilterParameters(control,initial_state_estimate,observation,state_transition),
    m_estimated_measurement_noise(estimated_measurement_noise),
    m_estimated_process_noise_covariance(estimated_process_noise_covariance),
    m_initial_covariance_estimate(initial_covariance_estimate)
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

const std::string StandardKalmanFilterParameters::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> StandardKalmanFilterParameters::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-04-28: version 1.0: initial version");
  v.push_back("2013-05-03: version 1.1: inhertic from KalmanFilterParameters");
  return v;
}

bool StandardKalmanFilterParameters::HasParameterType(const KalmanFilterParameterType type)
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

bool StandardKalmanFilterParameters::IsAboutEqual(const StandardKalmanFilterParameters& lhs, const StandardKalmanFilterParameters& rhs)
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
