#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "kalmanfilterparameters.h"
#pragma GCC diagnostic pop

#include <cassert>
#include "trace.h"

ribi::kalman::KalmanFilterParameters::KalmanFilterParameters(
  const boost::numeric::ublas::matrix<double>& control,
  const boost::numeric::ublas::vector<double>& initial_state_estimate,
  const boost::numeric::ublas::matrix<double>& observation,
  const boost::numeric::ublas::matrix<double>& state_transition)
  : m_control{control},
    m_initial_state_estimate{initial_state_estimate},
    m_observation{observation},
    m_state_transition{state_transition}
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

bool ribi::kalman::KalmanFilterParameters::HasParameterType(const KalmanFilterParameterType type)
{
  return
       type == KalmanFilterParameterType::control
    || type == KalmanFilterParameterType::initial_state_estimate
    || type == KalmanFilterParameterType::observation
    || type == KalmanFilterParameterType::state_transition;
}
