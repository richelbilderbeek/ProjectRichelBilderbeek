//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "kalmanfilter.h"

KalmanFilter::KalmanFilter(
  const boost::shared_ptr<KalmanFilterCalculationElements>& calculation,
  const boost::shared_ptr<const KalmanFilterParameters>& parameters)
  : m_last_calculation(calculation),
    m_parameters(parameters)
{
  assert(m_last_calculation);
  assert(m_parameters);
  assert(m_last_calculation->GetType() == m_parameters->GetType());

  //NO! DO NOT CALL VIRTUAL FUNCTIONS FROM AN ABC's CONSTRUCTOR!
  //assert(static_cast<int>(this->GetType()) == static_cast<int>(GetParameters()->GetType())
  //  && "Initialize each Kalman filter type with the right type of parameters");
}

const std::string KalmanFilter::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> KalmanFilter::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-05-06: version 1.0: initial version");
  return v;
}
