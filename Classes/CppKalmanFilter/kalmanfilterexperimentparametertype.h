#ifndef KALMANFILTEREXPERIMENTPARAMETERTYPE_H
#define KALMANFILTEREXPERIMENTPARAMETERTYPE_H

namespace ribi {
namespace kalman {

//#include <vector>

///These parameters overlap
///E: Experiment
///K: Kalman filter
///W: White noise system parameter
enum class KalmanFilterExperimentParameterType
{
  control,                            //E K W
  estimated_measurement_noise,        //E K
  estimated_optimal_kalman_gain,      //E K
  estimated_process_noise_covariance, //E K
  initial_covariance_estimate,        //E K
  initial_state_estimate,             //E K
  initial_state_real,                 //E   W
  measurement_frequency,              //E   W
  real_measurement_noise,             //E   W
  real_process_noise,                 //E   W
  input,                              //E
  observation,                        //E K
  state_names,                        //E
  state_transition,                   //E K W
  n_parameters                        //E
};

bool operator<(const KalmanFilterExperimentParameterType lhs, const KalmanFilterExperimentParameterType rhs);
bool operator==(const KalmanFilterExperimentParameterType lhs, const KalmanFilterExperimentParameterType rhs);
bool operator!=(const KalmanFilterExperimentParameterType lhs, const KalmanFilterExperimentParameterType rhs);

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTEREXPERIMENTPARAMETERTYPE_H
