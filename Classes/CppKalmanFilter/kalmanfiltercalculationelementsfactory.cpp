

#include "kalmanfiltercalculationelementsfactory.h"

#include <cassert>

#include "standardkalmanfiltercalculationelements.h"
#include "steadystatekalmanfiltercalculationelements.h"
#include "fixedlagsmootherkalmanfiltercalculationelements.h"


const boost::shared_ptr<ribi::kalman::KalmanFilterCalculationElements>
  ribi::kalman::KalmanFilterCalculationElementsFactory::Create(
  const KalmanFilterType type)
{
  boost::shared_ptr<KalmanFilterCalculationElements> p;
  switch (type)
  {
    case KalmanFilterType::fixed_lag_smoother:
      p.reset(new FixedLagSmootherKalmanFilterCalculationElements);
    break;
    case KalmanFilterType::standard:
      p.reset(new StandardKalmanFilterCalculationElements);
    break;
    case KalmanFilterType::steady_state:
      p.reset(new SteadyStateKalmanFilterCalculationElements);
    break;
    case KalmanFilterType::n_types:
      assert(!"Unimplemented KalmanFilterType");
  }
  assert(p);
  assert(p->GetType() == type);
  return p;
}

const boost::shared_ptr<ribi::kalman::KalmanFilterCalculationElements> ribi::kalman::KalmanFilterCalculationElementsFactory::DeepCopy(
  const boost::shared_ptr<KalmanFilterCalculationElements>& original)
{
  assert(original);

  const boost::shared_ptr<KalmanFilterCalculationElements> my_copy = original->Clone();

  assert(my_copy);
  assert(original->GetType() == my_copy->GetType());

  return my_copy;
}
