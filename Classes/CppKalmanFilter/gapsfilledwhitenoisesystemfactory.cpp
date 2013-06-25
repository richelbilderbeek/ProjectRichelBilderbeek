#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "gapsfilledwhitenoisesystemfactory.h"

const boost::shared_ptr<GapsFilledWhiteNoiseSystem> GapsFilledWhiteNoiseSystemFactory::Create(
  const boost::numeric::ublas::matrix<double>& control,
  const int gap,
  const boost::numeric::ublas::vector<double>& initial_state,
  const boost::numeric::ublas::vector<double>& real_measurement_noise,
  const boost::numeric::ublas::vector<double>& real_process_noise,
  const boost::numeric::ublas::matrix<double>& state_transition)
{
  const boost::shared_ptr<const WhiteNoiseSystemParameters> parameters(
    new GapsFilledWhiteNoiseSystemParameters(
      control,
      gap,
      initial_state,
      real_measurement_noise,
      real_process_noise,
      state_transition));
  assert(parameters);

  const boost::shared_ptr<GapsFilledWhiteNoiseSystem> system(
    new GapsFilledWhiteNoiseSystem(parameters));
  assert(system);
  return system;
}

const boost::shared_ptr<GapsFilledWhiteNoiseSystem> GapsFilledWhiteNoiseSystemFactory::Create(
  const boost::shared_ptr<WhiteNoiseSystemParameters>& parameters)
{
  assert(parameters);
  assert(parameters->GetType() == WhiteNoiseSystemType::lagged);
  const boost::shared_ptr<GapsFilledWhiteNoiseSystemParameters> lagged_parameters
    = boost::dynamic_pointer_cast<GapsFilledWhiteNoiseSystemParameters>(parameters);
  assert(lagged_parameters);

  const boost::shared_ptr<GapsFilledWhiteNoiseSystem> my_system
    = Create(
      lagged_parameters->GetControl(),
      lagged_parameters->GetGap(),
      lagged_parameters->GetInitialState(),
      lagged_parameters->GetMeasurementNoise(),
      lagged_parameters->GetProcessNoise(),
      lagged_parameters->GetStateTransition());
  assert(my_system);
  return my_system;
}
