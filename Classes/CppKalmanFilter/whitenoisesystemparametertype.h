#ifndef WHITENOISESYSTEMPARAMETERTYPE_H
#define WHITENOISESYSTEMPARAMETERTYPE_H

namespace ribi {
namespace kalman {

enum class WhiteNoiseSystemParameterType
{
  control,
  initial_state_real,
  measurement_frequency,
  real_measurement_noise,
  real_process_noise,
  state_transition,
  n_parameters
};

bool operator<(const WhiteNoiseSystemParameterType lhs, const WhiteNoiseSystemParameterType rhs);
bool operator==(const WhiteNoiseSystemParameterType lhs, const WhiteNoiseSystemParameterType rhs);
bool operator!=(const WhiteNoiseSystemParameterType lhs, const WhiteNoiseSystemParameterType rhs);

} //~namespace kalman
} //~namespace ribi

#endif // WHITENOISESYSTEMPARAMETERTYPE_H
