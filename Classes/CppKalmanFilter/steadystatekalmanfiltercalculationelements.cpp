#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "steadystatekalmanfiltercalculationelements.h"
#pragma GCC diagnostic pop

#include <cassert>
#include "kalmanfiltercalculationelementsfactory.h"

ribi::kalman::SteadyStateKalmanFilterCalculationElements::SteadyStateKalmanFilterCalculationElements(
  const boost::numeric::ublas::vector<double>& measurement,
  const boost::numeric::ublas::vector<double>& predicted_state,
  const boost::numeric::ublas::vector<double>& previous_state_estimate,
  const boost::numeric::ublas::vector<double>& updated_state)

  : KalmanFilterCalculationElements(
      measurement,
      predicted_state,
      previous_state_estimate,
      updated_state)
{
  //... nothing to check
}

boost::shared_ptr<ribi::kalman::KalmanFilterCalculationElements> ribi::kalman::SteadyStateKalmanFilterCalculationElements::Clone() const
{
  const boost::shared_ptr<KalmanFilterCalculationElements> p {
    new SteadyStateKalmanFilterCalculationElements(
      //Base
      this->GetMeasurement(),
      this->GetPredictedState(),
      this->GetPreviousState(),
      this->GetUpdatedState()
      //Derived class
      //... no additional data members
    )
  };
  assert(p);
  assert(p->GetType() == this->GetType());
  return p;
}

bool ribi::kalman::SteadyStateKalmanFilterCalculationElements::IsComplete() const
{
  const std::size_t sz = GetMeasurement().size();
  return
       sz != 0
    && sz == GetMeasurement().size()
    && sz == GetPreviousState().size()
    && sz == GetUpdatedState().size();
}
