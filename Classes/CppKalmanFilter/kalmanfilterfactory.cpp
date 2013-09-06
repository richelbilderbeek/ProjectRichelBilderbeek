

#include "kalmanfilterfactory.h"

#include <cassert>

#include "standardkalmanfilterfactory.h"
#include "steadystatekalmanfilterfactory.h"
#include "fixedlagsmootherkalmanfilterfactory.h"


const boost::shared_ptr<ribi::KalmanFilter> ribi::KalmanFilterFactory::Create(
  const boost::shared_ptr<const KalmanFilterParameters>& parameters)
{
  assert(parameters);

  boost::shared_ptr<KalmanFilter> kalman_filter;

  switch(parameters->GetType())
  {
    case KalmanFilterType::standard:
      kalman_filter = StandardKalmanFilterFactory::Create(parameters);
    break;
    case KalmanFilterType::steady_state:
      kalman_filter = SteadyStateKalmanFilterFactory::Create(parameters);
    break;
    case KalmanFilterType::fixed_lag_smoother:
      kalman_filter = FixedLagSmootherKalmanFilterFactory::Create(parameters);
    break;
    case KalmanFilterType::n_types:
      assert(!"Unimplemented Kalman filter type");
      throw std::logic_error(__func__);
  }

  assert(kalman_filter->GetType() == parameters->GetType());
  return kalman_filter;
}


