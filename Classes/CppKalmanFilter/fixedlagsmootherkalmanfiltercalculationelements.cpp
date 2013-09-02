//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "fixedlagsmootherkalmanfiltercalculationelements.h"

#include <cassert>

#include "standardkalmanfiltercalculationelements.h"

FixedLagSmootherKalmanFilterCalculationElements::FixedLagSmootherKalmanFilterCalculationElements(
  const boost::numeric::ublas::vector<double>& measurement,
  const boost::numeric::ublas::vector<double>& predicted_state,
  const boost::numeric::ublas::vector<double>& previous_state_estimate,
  const boost::numeric::ublas::vector<double>& updated_state)
  : KalmanFilterCalculationElements(
      measurement,
      predicted_state,
      previous_state_estimate,
      updated_state
    )
{
  //... nothing to check left
}

void FixedLagSmootherKalmanFilterCalculationElements::Clear()
{
  KalmanFilterCalculationElements::Clear();

  //Others, e.g.
  //m_updated_covariance = boost::numeric::ublas::matrix<double>();
}

const boost::shared_ptr<KalmanFilterCalculationElements> FixedLagSmootherKalmanFilterCalculationElements::Clone() const
{
  boost::shared_ptr<KalmanFilterCalculationElements> p;
  assert(p);
  return p;
}


bool FixedLagSmootherKalmanFilterCalculationElements::IsComplete() const
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

void FixedLagSmootherKalmanFilterCalculationElements::SetStandardCalculationElement(const boost::shared_ptr<StandardKalmanFilterCalculationElements>& standard_calculation)
{
  assert(!m_standard_calculation);
  assert(standard_calculation);
  m_standard_calculation = standard_calculation;
  assert(m_standard_calculation);
}
