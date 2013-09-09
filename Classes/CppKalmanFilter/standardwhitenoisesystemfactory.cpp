

#include "standardwhitenoisesystemfactory.h"

const boost::shared_ptr<ribi::kalman::StandardWhiteNoiseSystem>
  ribi::kalman::StandardWhiteNoiseSystemFactory::Create(
    const boost::numeric::ublas::matrix<double>& control,
    const boost::numeric::ublas::vector<double>& initial_state,
    const boost::numeric::ublas::vector<double>& real_measurement_noise,
    const boost::numeric::ublas::vector<double>& real_process_noise,
    const boost::numeric::ublas::matrix<double>& state_transition
  )
{
  boost::shared_ptr<const ribi::kalman::StandardWhiteNoiseSystemParameters> parameters{
    new StandardWhiteNoiseSystemParameters(
      control,
      initial_state,
      real_measurement_noise,
      real_process_noise,
      state_transition
    )
  };
  assert(parameters);
  const boost::shared_ptr<StandardWhiteNoiseSystem> system{
    new StandardWhiteNoiseSystem(parameters)
  };
  assert(system);
  return system;
}

const boost::shared_ptr<ribi::kalman::StandardWhiteNoiseSystem>
  ribi::kalman::StandardWhiteNoiseSystemFactory::Create(
    const boost::shared_ptr<WhiteNoiseSystemParameters>& parameters
  )
{
  assert(parameters);
  assert(parameters->GetType() == WhiteNoiseSystemType::standard);
  const boost::shared_ptr<StandardWhiteNoiseSystemParameters> standard_parameters
    = boost::dynamic_pointer_cast<StandardWhiteNoiseSystemParameters>(parameters);
  assert(standard_parameters);
  const boost::shared_ptr<StandardWhiteNoiseSystem> system
    = Create(
      standard_parameters->GetControl(),
      standard_parameters->GetInitialState(),
      standard_parameters->GetMeasurementNoise(),
      standard_parameters->GetProcessNoise(),
      standard_parameters->GetStateTransition());
  assert(system);
  return system;
}
