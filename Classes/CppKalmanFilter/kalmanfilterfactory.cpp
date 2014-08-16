#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "kalmanfilterfactory.h"
#pragma GCC diagnostic pop

#include <cassert>

#include "standardkalmanfilterfactory.h"
#include "steadystatekalmanfilterfactory.h"
#include "fixedlagsmootherkalmanfilterfactory.h"
#include "testtimer.h"

ribi::kalman::KalmanFilterFactory::KalmanFilterFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::kalman::KalmanFilter> ribi::kalman::KalmanFilterFactory::Create(
  const boost::shared_ptr<const KalmanFilterParameters>& parameters
) const noexcept
{
  assert(parameters);

  boost::shared_ptr<KalmanFilter> kalman_filter;

  switch(parameters->GetType())
  {
    case KalmanFilterType::standard:
      kalman_filter = StandardKalmanFilterFactory().Create(parameters);
    break;
    case KalmanFilterType::steady_state:
      kalman_filter = SteadyStateKalmanFilterFactory().Create(parameters);
    break;
    case KalmanFilterType::fixed_lag_smoother:
      kalman_filter = FixedLagSmootherKalmanFilterFactory().Create(parameters);
    break;
    case KalmanFilterType::n_types:
      assert(!"Unimplemented Kalman filter type");
      throw std::logic_error(__func__);
  }

  assert(kalman_filter->GetType() == parameters->GetType());
  return kalman_filter;
}

#ifndef NDEBUG
void ribi::kalman::KalmanFilterFactory::Test() noexcept
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
