#ifndef KALMANFILTERPARAMETERS_H
#define KALMANFILTERPARAMETERS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#pragma GCC diagnostic pop

#include "kalmanfiltertype.h"
#include "kalmanfilterparametertype.h"

namespace ribi {
namespace kalman {

///ABC for the parameters every Kalman filter needs at least
struct KalmanFilterParameters
{
  KalmanFilterParameters(const KalmanFilterParameters&) = delete;
  KalmanFilterParameters& operator=(const KalmanFilterParameters&) = delete;
  virtual ~KalmanFilterParameters() noexcept {}

  ///Obtain the Kalman filter type as an enum
  virtual KalmanFilterType GetType() const = 0;

  ///Obtain the control matrix ('B'): the effect of inputs on the current states
  const boost::numeric::ublas::matrix<double>& GetControl() const
    { return m_control; }

  ///x: The initial state estimate
  const boost::numeric::ublas::vector<double>& GetInitialStateEstimate() const
    { return m_initial_state_estimate; }

  ///Obtain how the states are observed ('H')
  const boost::numeric::ublas::matrix<double>& GetObservation() const
    { return m_observation; }

  ///Obtain the state transition matrix ('F'), containing the physics of the system
  const boost::numeric::ublas::matrix<double>& GetStateTransition() const { return m_state_transition; }

  ///Check if this parameter set has a certain type of KalmanFilterParameter
  static bool HasParameterType(const KalmanFilterParameterType type);

  protected:
  ///An ABC can only be constructed by derived classes
  explicit KalmanFilterParameters(
    const boost::numeric::ublas::matrix<double>& control,
    const boost::numeric::ublas::vector<double>& initial_state_estimate,
    const boost::numeric::ublas::matrix<double>& observation,
    const boost::numeric::ublas::matrix<double>& state_transition
  );

  private:
  ///B: control matrix: the effect of inputs on the current states
  const boost::numeric::ublas::matrix<double> m_control;

  ///x: The initial state estimate
  const boost::numeric::ublas::vector<double> m_initial_state_estimate;

  ///H: How the states are observed
  const boost::numeric::ublas::matrix<double> m_observation;

  ///F: state transition matrix, containing the physics of the system
  const boost::numeric::ublas::matrix<double> m_state_transition;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTERPARAMETERS_H
