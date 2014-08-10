#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "laggedwhitenoisesystemfactory.h"
#include "testtimer.h"
#include "matrix.h"
#pragma GCC diagnostic pop

ribi::kalman::LaggedWhiteNoiseSystemFactory::LaggedWhiteNoiseSystemFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::kalman::LaggedWhiteNoiseSystem>
  ribi::kalman::LaggedWhiteNoiseSystemFactory::Create(
  const boost::numeric::ublas::matrix<double>& control,
  const boost::numeric::ublas::vector<double>& initial_state,
  const int lag,
  const boost::numeric::ublas::vector<double>& real_measurement_noise,
  const boost::numeric::ublas::vector<double>& real_process_noise,
  const boost::numeric::ublas::matrix<double>& state_transition
) const noexcept
{
  const boost::shared_ptr<const WhiteNoiseSystemParameters> parameters{
    new LaggedWhiteNoiseSystemParameters(
      control,
      initial_state,
      lag,
      real_measurement_noise,
      real_process_noise,
      state_transition)
  };
  assert(parameters);

  const boost::shared_ptr<LaggedWhiteNoiseSystem> system{
    new LaggedWhiteNoiseSystem(parameters)
  };
  assert(system);
  return system;
}

boost::shared_ptr<ribi::kalman::LaggedWhiteNoiseSystem> ribi::kalman::LaggedWhiteNoiseSystemFactory::Create(
  const boost::shared_ptr<WhiteNoiseSystemParameters>& parameters
) const noexcept
{
  assert(parameters);
  assert(parameters->GetType() == WhiteNoiseSystemType::lagged);
  const boost::shared_ptr<LaggedWhiteNoiseSystemParameters> lagged_parameters
    = boost::dynamic_pointer_cast<LaggedWhiteNoiseSystemParameters>(parameters);
  assert(lagged_parameters);

  const boost::shared_ptr<LaggedWhiteNoiseSystem> my_system
    = Create(
      lagged_parameters->GetControl(),
      lagged_parameters->GetInitialState(),
      lagged_parameters->GetLag(),
      lagged_parameters->GetMeasurementNoise(),
      lagged_parameters->GetProcessNoise(),
      lagged_parameters->GetStateTransition());
  assert(my_system);
  return my_system;
}


#ifndef NDEBUG
void ribi::kalman::LaggedWhiteNoiseSystemFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Matrix();
    const boost::shared_ptr<LaggedWhiteNoiseSystem> my_system
      = LaggedWhiteNoiseSystemFactory().Create(
        Matrix::CreateMatrix(1,1, { 1.0 } ), //control
        Matrix::CreateVector(     { 0.0 } ), //initial_state,
        0,
        Matrix::CreateVector(     { 0.0 } ), //real_measurement_noise
        Matrix::CreateVector(     { 0.0 } ), //real_process_noise
        Matrix::CreateMatrix(1,1, { 1.0 } )  //state_transition
    );
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
