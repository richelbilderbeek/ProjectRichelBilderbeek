#ifndef KALMANFILTERPARAMETERS_H
#define KALMANFILTERPARAMETERS_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/noncopyable.hpp>

#include "kalmanfiltertype.h"
#include "kalmanfilterparametertype.h"

///ABC for the parameters every Kalman filter needs at least
struct KalmanFilterParameters : public boost::noncopyable
{
  ///ABC must have public virtual destructor
  // * Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules, guidelines, and best practices.
  //   ISBN: 0-32-111358-6. Item 50: 'Make base class destructors public and virtual, or protected and nonvirtual'
  virtual ~KalmanFilterParameters() {}

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
  KalmanFilterParameters(
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

};

#endif // KALMANFILTERPARAMETERS_H
