#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "gapsfilledwhitenoisesystemfactory.h"
#pragma GCC diagnostic pop

boost::shared_ptr<ribi::kalman::GapsFilledWhiteNoiseSystem> ribi::kalman::GapsFilledWhiteNoiseSystemFactory::Create(
  const boost::numeric::ublas::matrix<double>& control,
  const boost::numeric::ublas::vector<double>& initial_state,
  const boost::numeric::ublas::vector<int>& measurement_frequency,
  const boost::numeric::ublas::vector<double>& real_measurement_noise,
  const boost::numeric::ublas::vector<double>& real_process_noise,
  const boost::numeric::ublas::matrix<double>& state_transition)
{
  const boost::shared_ptr<const WhiteNoiseSystemParameters> parameters(
    new GapsFilledWhiteNoiseSystemParameters(
      control,
      initial_state,
      measurement_frequency,
      real_measurement_noise,
      real_process_noise,
      state_transition));
  assert(parameters);
  assert(parameters->GetType() == WhiteNoiseSystemType::gaps_filled);

  const boost::shared_ptr<GapsFilledWhiteNoiseSystem> system(
    new GapsFilledWhiteNoiseSystem(parameters));
  assert(system);
  assert(system->GetType() == WhiteNoiseSystemType::gaps_filled);
  return system;
}

boost::shared_ptr<ribi::kalman::GapsFilledWhiteNoiseSystem> ribi::kalman::GapsFilledWhiteNoiseSystemFactory::Create(
  const boost::shared_ptr<WhiteNoiseSystemParameters>& general_parameters)
{
  assert(general_parameters);
  assert(general_parameters->GetType() == WhiteNoiseSystemType::gaps_filled);
  const boost::shared_ptr<GapsFilledWhiteNoiseSystemParameters> parameters
    = boost::dynamic_pointer_cast<GapsFilledWhiteNoiseSystemParameters>(general_parameters);
  assert(parameters);
  assert(parameters->GetType() == WhiteNoiseSystemType::gaps_filled);

  const boost::shared_ptr<GapsFilledWhiteNoiseSystem> my_system
    = Create(
      parameters->GetControl(),
      parameters->GetInitialState(),
      parameters->GetMeasurementFrequency(),
      parameters->GetMeasurementNoise(),
      parameters->GetProcessNoise(),
      parameters->GetStateTransition());
  assert(my_system);
  assert(my_system->GetType() == WhiteNoiseSystemType::gaps_filled);

  return my_system;
}
