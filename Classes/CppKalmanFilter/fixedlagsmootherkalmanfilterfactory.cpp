#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "fixedlagsmootherkalmanfilterfactory.h"

#include <cassert>
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::kalman::FixedLagSmootherKalmanFilter> ribi::kalman::FixedLagSmootherKalmanFilterFactory::Create(
  const boost::shared_ptr<const KalmanFilterParameters>& parameters)
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


