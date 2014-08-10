#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "fixedlagsmootherkalmanfilterfactory.h"

#include <cassert>

#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::kalman::FixedLagSmootherKalmanFilterFactory::FixedLagSmootherKalmanFilterFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::kalman::FixedLagSmootherKalmanFilter> ribi::kalman::FixedLagSmootherKalmanFilterFactory::Create(
  const boost::shared_ptr<const KalmanFilterParameters>& parameters) const noexcept
{
  assert(parameters);
  assert(parameters->GetType() == KalmanFilterType::fixed_lag_smoother);

  const boost::shared_ptr<FixedLagSmootherKalmanFilterCalculationElements> calculation {
    new FixedLagSmootherKalmanFilterCalculationElements
  };

  assert(calculation);

  const boost::shared_ptr<FixedLagSmootherKalmanFilter> kalman_filter {
    new FixedLagSmootherKalmanFilter(calculation,parameters)
  };
  assert(kalman_filter);
  assert(kalman_filter->GetType() == KalmanFilterType::fixed_lag_smoother);
  return kalman_filter;
}

#ifndef NDEBUG
void ribi::kalman::FixedLagSmootherKalmanFilterFactory::Test() noexcept
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
