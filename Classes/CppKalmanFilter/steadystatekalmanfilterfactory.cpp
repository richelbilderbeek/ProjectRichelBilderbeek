#include "steadystatekalmanfilterfactory.h"

#include <cassert>
#include "kalmanfiltercalculationelementsfactory.h"

const boost::shared_ptr<ribi::SteadyStateKalmanFilter> ribi::SteadyStateKalmanFilterFactory::Create(
  const boost::shared_ptr<const KalmanFilterParameters>& parameters)
{
  assert(parameters);
  assert(parameters->GetType() == KalmanFilterType::steady_state);

  const boost::shared_ptr<KalmanFilterCalculationElements> calculation {
    KalmanFilterCalculationElementsFactory::Create(parameters->GetType())
  };

  assert(calculation);

  const boost::shared_ptr<SteadyStateKalmanFilter> kalman_filter {
    new SteadyStateKalmanFilter(calculation,parameters)
  };

  assert(kalman_filter);
  assert(kalman_filter->GetType() == KalmanFilterType::steady_state);
  return kalman_filter;
}


