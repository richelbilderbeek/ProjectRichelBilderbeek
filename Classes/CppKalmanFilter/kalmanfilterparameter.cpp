#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "kalmanfilterparameter.h"

#include <cassert>
#include <stdexcept>
#include <boost/numeric/conversion/cast.hpp>
#pragma GCC diagnostic pop

const std::vector<ribi::kalman::KalmanFilterParameterType> ribi::kalman::KalmanFilterParameter::GetAll()
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

bool ribi::kalman::KalmanFilterParameter::IsMatrix(const KalmanFilterParameterType type)
{
  return !ribi::kalman::KalmanFilterParameter::IsVector(type);
}

bool ribi::kalman::KalmanFilterParameter::IsVector(const KalmanFilterParameterType type)
{
  return type == KalmanFilterParameterType::initial_state_estimate;
}

const std::string ribi::kalman::KalmanFilterParameter::ToDescription(const KalmanFilterParameterType type)
{
  switch (type)
  {
    case KalmanFilterParameterType::control:
      return "Matrix for converting input to state change";
    case KalmanFilterParameterType::estimated_measurement_noise:
      return "Matrix that has an estimated measurement noise covariance";
    case KalmanFilterParameterType::estimated_optimal_kalman_gain:
      return "Matrix with the estimated optimal Kalman gain";
    case KalmanFilterParameterType::estimated_process_noise_covariance:
      return "Matrix with the estimated process noise covariance";
    case KalmanFilterParameterType::initial_covariance_estimate:
      return "Matrix with the initial covariance estimate";
    case KalmanFilterParameterType::initial_state_estimate:
      return "Vector with the initial state estimate";
    case KalmanFilterParameterType::observation:
      return "Matrix that with effect of a measurement on a state change";
    case KalmanFilterParameterType::state_transition:
      return "Matrix that contains the internal physics of the system; the effect of current state on the next state";
    case KalmanFilterParameterType::n_parameters:
      assert(!"Unimplemented type of KalmanFilterParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of KalmanFilterParameterType");
  throw std::logic_error(__func__);
}

const std::string ribi::kalman::KalmanFilterParameter::ToName(const KalmanFilterParameterType type)
{
  switch (type)
  {
    case KalmanFilterParameterType::control:
      return "Control";
    case KalmanFilterParameterType::estimated_measurement_noise:
      return "Estimated measurement error covariance";
    case KalmanFilterParameterType::estimated_optimal_kalman_gain:
      return "Estimated optimal Kalman gain";
    case KalmanFilterParameterType::estimated_process_noise_covariance:
      return "Estimated process noise covariance";
    case KalmanFilterParameterType::initial_covariance_estimate:
      return "Initial covariance estimate";
    case KalmanFilterParameterType::initial_state_estimate:
      return "Initial state estimate";
    case KalmanFilterParameterType::observation:
      return "Observation";
    case KalmanFilterParameterType::state_transition:
      return "State transition";
    case KalmanFilterParameterType::n_parameters:
      assert(!"Unimplemented type of KalmanFilterParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of KalmanFilterParameterType");
  throw std::logic_error(__func__);
}

const std::string ribi::kalman::KalmanFilterParameter::ToSymbol(const KalmanFilterParameterType type)
{
  switch (type)
  {
    case KalmanFilterParameterType::control:
      return "B";
    case KalmanFilterParameterType::estimated_measurement_noise:
      return "R";
    case KalmanFilterParameterType::estimated_optimal_kalman_gain:
      return "K";
    case KalmanFilterParameterType::estimated_process_noise_covariance:
      return "Q";
    case KalmanFilterParameterType::initial_covariance_estimate:
      return "P";
    case KalmanFilterParameterType::initial_state_estimate:
      return "x";
    case KalmanFilterParameterType::observation:
      return "H";
    case KalmanFilterParameterType::state_transition:
      return "A";
    case KalmanFilterParameterType::n_parameters:
      assert(!"Unimplemented type of KalmanFilterParameterType");
      throw std::logic_error(__func__);
  }
  assert(!"Unimplemented type of KalmanFilterParameterType");
  throw std::logic_error(__func__);
}
