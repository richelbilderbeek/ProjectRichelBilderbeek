//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "kalmanfilterparameters.h"

#include <cassert>
#include "trace.h"

KalmanFilterParameters::KalmanFilterParameters(
  const boost::numeric::ublas::matrix<double>& control,
  const boost::numeric::ublas::vector<double>& initial_state_estimate,
  const boost::numeric::ublas::matrix<double>& observation,
  const boost::numeric::ublas::matrix<double>& state_transition)
  : m_control(control),
    m_initial_state_estimate(initial_state_estimate),
    m_observation(observation),
    m_state_transition(state_transition)
{
  #ifndef NDEBUG
  //Check for correct dimensionality
  const std::size_t sz = GetInitialStateEstimate().size();
  //assert(sz >= 0); //Inevitable for std::size_t
  assert(GetControl().size1() == sz);
  assert(GetControl().size2() == sz);
  assert(GetObservation().size1() == sz);
  assert(GetObservation().size2() == sz);
  assert(GetStateTransition().size1() == sz);
  assert(GetStateTransition().size2() == sz);
  assert(GetInitialStateEstimate().size() == sz);
  #endif
}

bool KalmanFilterParameters::HasParameterType(const KalmanFilterParameterType type)
{
  return
       type == KalmanFilterParameterType::control
    || type == KalmanFilterParameterType::initial_state_estimate
    || type == KalmanFilterParameterType::observation
    || type == KalmanFilterParameterType::state_transition;
}
