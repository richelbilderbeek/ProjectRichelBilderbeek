#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "standardkalmanfiltercalculationelements.h"

#include <cassert>

StandardKalmanFilterCalculationElements::StandardKalmanFilterCalculationElements(
  //Base
  const boost::numeric::ublas::vector<double>& measurement,
  const boost::numeric::ublas::vector<double>& predicted_state,
  const boost::numeric::ublas::vector<double>& previous_state_estimate,
  const boost::numeric::ublas::vector<double>& updated_state,
  //This class
  const boost::numeric::ublas::vector<double>& innovation,
  const boost::numeric::ublas::matrix<double>& innovation_covariance,
  const boost::numeric::ublas::matrix<double>& kalman_gain,
  const boost::numeric::ublas::matrix<double>& predicted_covariance,
  const boost::numeric::ublas::matrix<double>& previous_covariance_estimate,
  const boost::numeric::ublas::matrix<double>& updated_covariance)
  : KalmanFilterCalculationElements(
      measurement,
      predicted_state,
      previous_state_estimate,
      updated_state
    ),
    m_innovation(innovation),
    m_innovation_covariance(innovation_covariance),
    m_kalman_gain(kalman_gain),
    m_predicted_covariance(predicted_covariance),
    m_previous_covariance_estimate(previous_covariance_estimate),
    m_updated_covariance(updated_covariance)
{
  #ifndef NDEBUG
  //size may be zero
  const std::size_t sz = m_innovation.size();
  //Base
  assert(sz == GetMeasurement().size());
  assert(sz == GetPredictedState().size());
  assert(sz == GetPreviousState().size());
  assert(sz == GetUpdatedState().size());
  //This class
  assert(sz == m_innovation.size());
  assert(sz == m_innovation_covariance.size1());
  assert(sz == m_innovation_covariance.size2());
  assert(sz == m_kalman_gain.size1());
  assert(sz == m_kalman_gain.size2());
  assert(sz == m_predicted_covariance.size1());
  assert(sz == m_predicted_covariance.size2());
  assert(sz == m_previous_covariance_estimate.size1());
  assert(sz == m_previous_covariance_estimate.size2());
  assert(sz == m_updated_covariance.size1());
  assert(sz == m_updated_covariance.size2());
  #endif
}

void StandardKalmanFilterCalculationElements::Clear()
{
  KalmanFilterCalculationElements::Clear();
  m_innovation = boost::numeric::ublas::vector<double>();
  assert(m_innovation.empty());
  m_innovation_covariance = boost::numeric::ublas::matrix<double>();
  m_kalman_gain = boost::numeric::ublas::matrix<double>();
  m_predicted_covariance = boost::numeric::ublas::matrix<double>();
  m_previous_covariance_estimate = boost::numeric::ublas::matrix<double>();
  m_updated_covariance = boost::numeric::ublas::matrix<double>();
}

const boost::shared_ptr<KalmanFilterCalculationElements> StandardKalmanFilterCalculationElements::Clone() const
{
  const boost::shared_ptr<KalmanFilterCalculationElements> p(
    new StandardKalmanFilterCalculationElements(
      //Base
      this->GetMeasurement(),
      this->GetPredictedState(),
      this->GetPreviousState(),
      this->GetUpdatedState(),
      //Derived class
      this->GetInnovation(),
      this->GetInnovationCovariance(),
      this->GetKalmanGain(),
      this->GetPredicatedCovariance(),
      this->GetPreviousCovarianceEstimate(),
      this->GetUpdatedCovariance()
    )
  );
  assert(p);
  assert(p->GetType() == this->GetType());
  return p;
}

bool StandardKalmanFilterCalculationElements::IsComplete() const
{
  const std::size_t sz = m_innovation.size();
  return
       //sz != 0
       sz == m_innovation.size()
    && sz == m_innovation_covariance.size1()
    && sz == m_innovation_covariance.size2()
    && sz == m_innovation_covariance.size1()
    && sz == m_innovation_covariance.size2()
    && sz == m_kalman_gain.size1()
    && sz == m_kalman_gain.size2()
    && sz == GetMeasurement().size()
    && sz == m_predicted_covariance.size1()
    && sz == m_predicted_covariance.size2()
    && sz == GetPredictedState().size()
    && sz == m_previous_covariance_estimate.size1()
    && sz == m_previous_covariance_estimate.size2()
    && sz == GetPreviousState().size()
    && sz == m_updated_covariance.size1()
    && sz == m_updated_covariance.size2()
    && sz == GetUpdatedState().size();
}

void StandardKalmanFilterCalculationElements::SetInnovation(const boost::numeric::ublas::vector<double>& innovation)
{
  assert(m_innovation.empty());
  m_innovation = innovation;
}

void StandardKalmanFilterCalculationElements::SetInnovationCovariance(const boost::numeric::ublas::matrix<double>& innovation_covariance)
{
  assert(m_innovation_covariance.size1() == 0);
  assert(m_innovation_covariance.size2() == 0);
  m_innovation_covariance = innovation_covariance;
}

void StandardKalmanFilterCalculationElements::SetKalmanGain(const boost::numeric::ublas::matrix<double>& kalman_gain)
{
  assert(m_kalman_gain.size1() == 0);
  assert(m_kalman_gain.size2() == 0);
  m_kalman_gain = kalman_gain;
}

void StandardKalmanFilterCalculationElements::SetPredictedCovariance(const boost::numeric::ublas::matrix<double>& predicted_covariance)
{
  assert(m_predicted_covariance.size1() == 0);
  assert(m_predicted_covariance.size2() == 0);
  m_predicted_covariance = predicted_covariance;
}

void StandardKalmanFilterCalculationElements::SetPreviousCovarianceEstimate(const boost::numeric::ublas::matrix<double>& previous_covariance_estimate)
{
  assert(m_previous_covariance_estimate.size1() == 0);
  assert(m_previous_covariance_estimate.size2() == 0);
  m_previous_covariance_estimate = previous_covariance_estimate;
}

void StandardKalmanFilterCalculationElements::SetUpdatedCovariance(const boost::numeric::ublas::matrix<double>& updated_covariance)
{
  assert(m_updated_covariance.size1() == 0);
  assert(m_updated_covariance.size2() == 0);
  m_updated_covariance = updated_covariance;
}
