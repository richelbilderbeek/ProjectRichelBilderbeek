

#include "standardkalmanfilterfactory.h"

#include <cassert>

const boost::shared_ptr<ribi::StandardKalmanFilter> ribi::StandardKalmanFilterFactory::Create(
  const boost::shared_ptr<const KalmanFilterParameters>& parameters)
{
  assert(parameters);
  assert(parameters->GetType() == KalmanFilterType::standard);

  const boost::shared_ptr<StandardKalmanFilterCalculationElements> calculation{
    new StandardKalmanFilterCalculationElements
  };

  assert(calculation);

  const boost::shared_ptr<StandardKalmanFilter> kalman_filter{
    new StandardKalmanFilter(calculation,parameters)
  };
  assert(kalman_filter);
  assert(kalman_filter->GetType() == KalmanFilterType::standard);
  return kalman_filter;
}


