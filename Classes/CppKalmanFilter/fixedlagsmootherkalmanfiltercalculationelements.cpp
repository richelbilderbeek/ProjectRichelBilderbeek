#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "fixedlagsmootherkalmanfiltercalculationelements.h"
#pragma GCC diagnostic pop

#include <cassert>

#include "standardkalmanfiltercalculationelements.h"

ribi::kalman::FixedLagSmootherKalmanFilterCalculationElements::FixedLagSmootherKalmanFilterCalculationElements(
  const boost::numeric::ublas::vector<double>& measurement,
  const boost::numeric::ublas::vector<double>& predicted_state,
  const boost::numeric::ublas::vector<double>& previous_state_estimate,
  const boost::numeric::ublas::vector<double>& updated_state)
  : KalmanFilterCalculationElements(
      measurement,
      predicted_state,
      previous_state_estimate,
      updated_state
    ),
    m_standard_calculation{}
{
  //... nothing to check left
}

void ribi::kalman::FixedLagSmootherKalmanFilterCalculationElements::Clear()
{
  KalmanFilterCalculationElements::Clear();

  //Others, e.g.
  //m_updated_covariance = boost::numeric::ublas::matrix<double>();
}

boost::shared_ptr<ribi::kalman::KalmanFilterCalculationElements> ribi::kalman::FixedLagSmootherKalmanFilterCalculationElements::Clone() const
{
  boost::shared_ptr<KalmanFilterCalculationElements> p;
  assert(p);
  return p;
}


bool ribi::kalman::FixedLagSmootherKalmanFilterCalculationElements::IsComplete() const
{
  const std::size_t sz = GetMeasurement().size();
  return
       sz != 0
    //Others, e.g.
    //&& sz == m_innovation.size()
    //&& sz == m_innovation_covariance.size1()
    //&& sz == m_innovation_covariance.size2()
    //&& sz == m_innovation_covariance.size1()
    && sz == GetMeasurement().size()
    && sz == GetPredictedState().size()
    && sz == GetPreviousState().size();
}

void ribi::kalman::FixedLagSmootherKalmanFilterCalculationElements::SetStandardCalculationElement(
  const boost::shared_ptr<StandardKalmanFilterCalculationElements>& standard_calculation)
{
  assert(!m_standard_calculation);
  assert(standard_calculation);
  m_standard_calculation = standard_calculation;
  assert(m_standard_calculation);
}
