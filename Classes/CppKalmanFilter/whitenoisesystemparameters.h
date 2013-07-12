#ifndef WHITENOISESYSTEMPARAMETERS_H
#define WHITENOISESYSTEMPARAMETERS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/noncopyable.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include "whitenoisesystemtype.h"

#pragma GCC diagnostic pop

///ABC of the parameters of a white noise system
struct WhiteNoiseSystemParameters : public boost::noncopyable
{
  ///ABC must have public virtual destructor
  // * Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules, guidelines, and best practices.
  //   ISBN: 0-32-111358-6. Item 50: 'Make base class destructors public and virtual, or protected and nonvirtual'
  virtual ~WhiteNoiseSystemParameters() {}

  ///The control matrix to determine the influence of the input (in GoToNextState)
  const boost::numeric::ublas::matrix<double>& GetControl() const
    { return m_control; }

  ///Obtain the real initial state
  const boost::numeric::ublas::vector<double>& GetInitialState() const
    { return m_initial_state; }

  ///The real standard deviation of the noise in the state transition
  ///(used in WhiteNoiseSystem::GoToNextState)
  const boost::numeric::ublas::vector<double>& GetProcessNoise() const
    { return m_real_process_noise; }

  ///The real amount of noise in the system
  ///A noise of zero indicates a system that can be measured accurately to infinite precision
  const boost::numeric::ublas::vector<double>& GetMeasurementNoise() const
    { return m_real_measurement_noise; }

  ///The state transitions in the system
  ///(used in WhiteNoiseSystem::GoToNextState)
  const boost::numeric::ublas::matrix<double>& GetStateTransition() const
    { return m_state_transition; }

  ///Obtain the type as an enum
  virtual WhiteNoiseSystemType GetType() const = 0;

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Check two parameter sets for equality using a fuzzy comparison
  static bool IsAboutEqual(const WhiteNoiseSystemParameters& lhs, const WhiteNoiseSystemParameters& rhs);

  protected:
  ///An ABC can only be constructed by derived classes
  WhiteNoiseSystemParameters(
    const boost::numeric::ublas::matrix<double>& control,
    const boost::numeric::ublas::vector<double>& initial_state,
    const boost::numeric::ublas::vector<double>& real_measurement_noise,
    const boost::numeric::ublas::vector<double>& real_process_noise,
    const boost::numeric::ublas::matrix<double>& state_transition);

  private:
  ///The control matrix to determine the influence of the input (in GoToNextState)
  const boost::numeric::ublas::matrix<double> m_control;

  ///The real initial state
  const boost::numeric::ublas::vector<double> m_initial_state;

  ///The real amount of noise in the system
  ///A noise of zero indicates a system that can be measured accurately to infinite precision
  const boost::numeric::ublas::vector<double> m_real_measurement_noise;

  ///The standard deviation of the noise in the state transition (in GoToNextState)
  const boost::numeric::ublas::vector<double> m_real_process_noise;

  ///The state transitions in the system, used in GoToNextState
  const boost::numeric::ublas::matrix<double> m_state_transition;

};

#endif // WHITENOISESYSTEMPARAMETERS_H
