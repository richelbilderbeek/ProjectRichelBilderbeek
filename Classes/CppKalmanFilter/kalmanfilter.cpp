

#include "kalmanfilter.h"

/*
ribi::kalman::KalmanFilter::KalmanFilter(
  const boost::shared_ptr<KalmanFilterCalculationElements>& calculation,
  const boost::shared_ptr<const KalmanFilterParameters>& parameters)
  : m_last_calculation{calculation},
    m_parameters{parameters}
{
  assert(m_last_calculation);
  assert(m_parameters);
  assert(m_last_calculation->GetType() == m_parameters->GetType());

  //NO! DO NOT CALL VIRTUAL FUNCTIONS FROM AN ABC's CONSTRUCTOR!
  //assert(static_cast<int>(this->GetType()) == static_cast<int>(GetParameters()->GetType())
  //  && "Initialize each Kalman filter type with the right type of parameters");
}
*/

const std::string ribi::kalman::KalmanFilter::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::kalman::KalmanFilter::GetVersionHistory()
{
  return {
    "2013-05-06: version 1.0: initial version",
    "2013-09-09: version 1.1: removed data members"
  };
}
