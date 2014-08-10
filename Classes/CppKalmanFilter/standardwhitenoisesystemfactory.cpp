#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "standardwhitenoisesystemfactory.h"

#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::kalman::StandardWhiteNoiseSystemFactory::StandardWhiteNoiseSystemFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::kalman::StandardWhiteNoiseSystem>
  ribi::kalman::StandardWhiteNoiseSystemFactory::Create(
    const boost::numeric::ublas::matrix<double>& control,
    const boost::numeric::ublas::vector<double>& initial_state,
    const boost::numeric::ublas::vector<double>& real_measurement_noise,
    const boost::numeric::ublas::vector<double>& real_process_noise,
    const boost::numeric::ublas::matrix<double>& state_transition
  ) const noexcept
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

boost::shared_ptr<ribi::kalman::StandardWhiteNoiseSystem>
  ribi::kalman::StandardWhiteNoiseSystemFactory::Create(
    const boost::shared_ptr<WhiteNoiseSystemParameters>& parameters
  ) const noexcept
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

#ifndef NDEBUG
void ribi::kalman::StandardWhiteNoiseSystemFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    //Matrix();
    //const boost::shared_ptr<LaggedWhiteNoiseSystem> my_system
    //  = LaggedWhiteNoiseSystemFactory().Create(
    //    Matrix::CreateMatrix(1,1, { 1.0 } ), //control
    //    Matrix::CreateVector(     { 0.0 } ), //initial_state,
    //    0,
    //    Matrix::CreateVector(     { 0.0 } ), //real_measurement_noise
    //    Matrix::CreateVector(     { 0.0 } ), //real_process_noise
    //    Matrix::CreateMatrix(1,1, { 1.0 } )  //state_transition
    //);
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
