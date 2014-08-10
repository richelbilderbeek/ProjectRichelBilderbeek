#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "gapsfilledwhitenoisesystemfactory.h"

#include "matrix.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::kalman::GapsFilledWhiteNoiseSystemFactory::GapsFilledWhiteNoiseSystemFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::kalman::GapsFilledWhiteNoiseSystem> ribi::kalman::GapsFilledWhiteNoiseSystemFactory::Create(
  const boost::numeric::ublas::matrix<double>& control,
  const boost::numeric::ublas::vector<double>& initial_state,
  const boost::numeric::ublas::vector<int>& measurement_frequency,
  const boost::numeric::ublas::vector<double>& real_measurement_noise,
  const boost::numeric::ublas::vector<double>& real_process_noise,
  const boost::numeric::ublas::matrix<double>& state_transition
) const noexcept
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
  const boost::shared_ptr<WhiteNoiseSystemParameters>& general_parameters) const noexcept
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
#ifndef NDEBUG
void ribi::kalman::GapsFilledWhiteNoiseSystemFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Matrix();
    GapsFilledWhiteNoiseSystemFactory().Create(
      Matrix::CreateMatrix(1,1, { 1.0 } ), //control
      Matrix::CreateVector(     { 0.0 } ), //initial_state,
      Matrix::CreateVector(     {   1 } ), //measurement frequencies
      Matrix::CreateVector(     { 0.0000001 } ), //real_measurement_noise
      Matrix::CreateVector(     { 0.0000001 } ), //real_process_noise
      Matrix::CreateMatrix(1,1, { 1.0 } )  //state_transition
    );
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
