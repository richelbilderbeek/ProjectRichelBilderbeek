//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "steadystatekalmanfilterfactory.h"

#include <cassert>
#include "kalmanfiltercalculationelementsfactory.h"

const boost::shared_ptr<SteadyStateKalmanFilter> SteadyStateKalmanFilterFactory::Create(
  const boost::shared_ptr<const KalmanFilterParameters>& parameters)
{
  assert(parameters);
  assert(parameters->GetType() == KalmanFilterType::steady_state);

  const boost::shared_ptr<KalmanFilterCalculationElements> calculation
    = KalmanFilterCalculationElementsFactory::Create(parameters->GetType());

  assert(calculation);

  const boost::shared_ptr<SteadyStateKalmanFilter> kalman_filter(
    new SteadyStateKalmanFilter(calculation,parameters));

  assert(kalman_filter);
  assert(kalman_filter->GetType() == KalmanFilterType::steady_state);
  return kalman_filter;
}


