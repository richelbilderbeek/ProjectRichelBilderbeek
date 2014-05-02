#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "fixedlagsmootherkalmanfilterparameters.h"
#pragma GCC diagnostic pop

#include <cassert>

#include "standardkalmanfilterparameters.h"

ribi::kalman::FixedLagSmootherKalmanFilterParameters::FixedLagSmootherKalmanFilterParameters(
  const boost::shared_ptr<StandardKalmanFilterParameters>& standard_parameters,
  const int lag)
  : KalmanFilterParameters(
      standard_parameters->GetControl(),
      standard_parameters->GetInitialStateEstimate(),
      standard_parameters->GetObservation(),
      standard_parameters->GetStateTransition()),
    m_lag{lag},
    m_standard_parameters{standard_parameters}
{
  assert(lag >= 0);
  assert(m_standard_parameters);
}

bool ribi::kalman::FixedLagSmootherKalmanFilterParameters::HasParameterType(const KalmanFilterParameterType type)
{
  return StandardKalmanFilterParameters::HasParameterType(type);
}
