

#include "kalmanfilterparameter.h"

#include <cassert>
#include <stdexcept>
#include <boost/numeric/conversion/cast.hpp>

const std::vector<ribi::KalmanFilterParameterType> ribi::KalmanFilterParameter::GetAll()
{
  const std::vector<KalmanFilterParameterType> v {
    KalmanFilterParameterType::control,
    KalmanFilterParameterType::estimated_measurement_noise,
    KalmanFilterParameterType::estimated_optimal_kalman_gain,
    KalmanFilterParameterType::estimated_process_noise_covariance,
    KalmanFilterParameterType::initial_covariance_estimate,
    KalmanFilterParameterType::initial_state_estimate,
    KalmanFilterParameterType::observation,
    KalmanFilterParameterType::state_transition
  };

  assert(boost::numeric_cast<int>(v.size()) == static_cast<int>(KalmanFilterParameterType::n_parameters)
    && "All parameters must be in");
  return v;
}

bool ribi::KalmanFilterParameter::IsMatrix(const KalmanFilterParameterType type)
{
  return !ribi::KalmanFilterParameter::IsVector(type);
}

bool ribi::KalmanFilterParameter::IsVector(const KalmanFilterParameterType type)
{
  return type == KalmanFilterParameterType::initial_state_estimate;
}

const std::string ribi::KalmanFilterParameter::ToDescription(const KalmanFilterParameterType type)
{
  switch (type)
  {
    case KalmanFilterParameterType::control:
      return std::string("Matrix for converting input to state change");
    case KalmanFilterParameterType::estimated_measurement_noise:
      return std::string("Matrix that has an estimated measurement noise covariance");
    case KalmanFilterParameterType::estimated_optimal_kalman_gain:
      return std::string("Matrix with the estimated optimal Kalman gain");
    case KalmanFilterParameterType::estimated_process_noise_covariance:
      return std::string("Matrix with the estimated process noise covariance");
    case KalmanFilterParameterType::initial_covariance_estimate:
      return std::string("Matrix with the initial covariance estimate");
    case KalmanFilterParameterType::initial_state_estimate:
      return std::string("Vector with the initial state estimate");
    case KalmanFilterParameterType::observation:
      return std::string("Matrix that with effect of a measurement on a state change");
    case KalmanFilterParameterType::state_transition:
      return std::string("Matrix that contains the internal physics of the system; the effect of current state on the next state");
    case KalmanFilterParameterType::n_parameters:
      assert(!"Unimplemented type of KalmanFilterParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of KalmanFilterParameterType");
  throw std::logic_error(__func__);
}

const std::string ribi::KalmanFilterParameter::ToName(const KalmanFilterParameterType type)
{
  switch (type)
  {
    case KalmanFilterParameterType::control:
      return std::string("Control");
    case KalmanFilterParameterType::estimated_measurement_noise:
      return std::string("Estimated measurement error covariance");
    case KalmanFilterParameterType::estimated_optimal_kalman_gain:
      return std::string("Estimated optimal Kalman gain");
    case KalmanFilterParameterType::estimated_process_noise_covariance:
      return std::string("Estimated process noise covariance");
    case KalmanFilterParameterType::initial_covariance_estimate:
      return std::string("Initial covariance estimate");
    case KalmanFilterParameterType::initial_state_estimate:
      return std::string("Initial state estimate");
    case KalmanFilterParameterType::observation:
      return std::string("Observation");
    case KalmanFilterParameterType::state_transition:
      return std::string("State transition");
    case KalmanFilterParameterType::n_parameters:
      assert(!"Unimplemented type of KalmanFilterParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of KalmanFilterParameterType");
  throw std::logic_error(__func__);
}

const std::string ribi::KalmanFilterParameter::ToSymbol(const KalmanFilterParameterType type)
{
  switch (type)
  {
    case KalmanFilterParameterType::control:
      return std::string("B");
    case KalmanFilterParameterType::estimated_measurement_noise:
      return std::string("R");
    case KalmanFilterParameterType::estimated_optimal_kalman_gain:
      return std::string("K");
    case KalmanFilterParameterType::estimated_process_noise_covariance:
      return std::string("Q");
    case KalmanFilterParameterType::initial_covariance_estimate:
      return std::string("P");
    case KalmanFilterParameterType::initial_state_estimate:
      return std::string("x");
    case KalmanFilterParameterType::observation:
      return std::string("H");
    case KalmanFilterParameterType::state_transition:
      return std::string("A");
    case KalmanFilterParameterType::n_parameters:
      assert(!"Unimplemented type of KalmanFilterParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of KalmanFilterParameterType");
  throw std::logic_error(__func__);
}
