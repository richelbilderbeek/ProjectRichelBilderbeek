#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "kalmanfiltercalculationelements.h"

#include <cassert>

KalmanFilterCalculationElements::KalmanFilterCalculationElements(
  const boost::numeric::ublas::vector<double>& measurement,
  const boost::numeric::ublas::vector<double>& predicted_state,
  const boost::numeric::ublas::vector<double>& previous_state_estimate,
  const boost::numeric::ublas::vector<double>& updated_state)
  : m_measurement(measurement),
    m_predicted_state(predicted_state),
    m_previous_state_estimate(previous_state_estimate),
    m_updated_state(updated_state)
{
  //Size may be zero
  #ifndef NDEBUG
  const std::size_t sz = m_measurement.size();
  assert(sz == m_measurement.size());
  assert(sz == m_predicted_state.size());
  assert(sz == m_previous_state_estimate.size());
  assert(sz == m_updated_state.size());
  #endif
}

void KalmanFilterCalculationElements::Clear()
{
  m_measurement = boost::numeric::ublas::vector<double>();
  m_predicted_state = boost::numeric::ublas::vector<double>();
  m_previous_state_estimate = boost::numeric::ublas::vector<double>();
  m_updated_state = boost::numeric::ublas::vector<double>();
  assert(m_measurement.size() == 0);
  assert(!KalmanFilterCalculationElements::IsComplete());
}

const boost::numeric::ublas::vector<double>& KalmanFilterCalculationElements::GetMeasurement() const
{
  return m_measurement;
}

const boost::numeric::ublas::vector<double>& KalmanFilterCalculationElements::GetPredictedState() const
{
  return m_predicted_state;
}

const boost::numeric::ublas::vector<double>& KalmanFilterCalculationElements::GetPreviousState() const
{
  return m_previous_state_estimate;
}

const boost::numeric::ublas::vector<double>& KalmanFilterCalculationElements::GetUpdatedState() const
{
  return m_updated_state;
}

bool KalmanFilterCalculationElements::IsComplete() const
{
  const std::size_t sz = m_measurement.size();
  return sz != 0
    && sz == m_measurement.size()
    && sz == m_predicted_state.size()
    && sz == m_previous_state_estimate.size()
    && sz == m_updated_state.size();
}


void KalmanFilterCalculationElements::SetMeasurement(const boost::numeric::ublas::vector<double>& measurement)
{
  assert(m_measurement.empty());
  m_measurement = measurement;
}

void KalmanFilterCalculationElements::SetPredictedState(const boost::numeric::ublas::vector<double>& predicted_state)
{
  assert(m_predicted_state.empty());
  m_predicted_state = predicted_state;
}

void KalmanFilterCalculationElements::SetPreviousStateEstimate(const boost::numeric::ublas::vector<double>& previous_state_estimate)
{
  assert(m_previous_state_estimate.empty());
  m_previous_state_estimate = previous_state_estimate;
}

void KalmanFilterCalculationElements::SetUpdatedState(const boost::numeric::ublas::vector<double>& updated_state)
{
  assert(m_updated_state.empty());
  m_updated_state = updated_state;
}
