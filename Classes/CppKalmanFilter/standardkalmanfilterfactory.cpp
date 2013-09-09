#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "standardkalmanfilterfactory.h"

#include <cassert>
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::kalman::StandardKalmanFilter> ribi::kalman::StandardKalmanFilterFactory::Create(
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


