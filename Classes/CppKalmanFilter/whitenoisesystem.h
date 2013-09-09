#ifndef WHITENOISESYSTEM_H
#define WHITENOISESYSTEM_H

//#include <boost/numeric/ublas/vector.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "whitenoisesystemtype.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "whitenoisesystemparameters.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace kalman {

struct WhiteNoiseSystem : public boost::noncopyable
{
  WhiteNoiseSystem(const WhiteNoiseSystem&) = delete;
  WhiteNoiseSystem& operator=(const WhiteNoiseSystem&) = delete;



  virtual ~WhiteNoiseSystem() {}

  ///The parameters
  const boost::shared_ptr<const WhiteNoiseSystemParameters>& GetParameters() const { return m_parameters; }

  ///Obtain the type as an enum
  virtual WhiteNoiseSystemType GetType() const = 0;

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Update reality, that is, let the real system (i.e. reality) go to its next state
  virtual void GoToNextState(const boost::numeric::ublas::vector<double>& input) = 0;

  ///Measure a value from this system with normally distributed noise
  virtual const boost::numeric::ublas::vector<double> Measure() const = 0;

  ///Peek what the real value is
  virtual const boost::numeric::ublas::vector<double>& PeekAtRealState() const { return m_current_state; }

  protected:
  ///An ABC can only be constructed by derived classes
  explicit WhiteNoiseSystem(const boost::shared_ptr<const WhiteNoiseSystemParameters>& parameters);

  ///Obtain a random number from a normal distribution
  ///From http://www.richelbilderbeek.nl/CppGetRandomNormal.htm
  static double GetRandomNormal(const double mean = 0.0, const double sigma = 1.0);

  ///The real state of the system
  const boost::numeric::ublas::vector<double>& GetCurrentState() const { return m_current_state; }

  ///Set the new current state
  void SetNewCurrentState(const boost::numeric::ublas::vector<double>& new_current_state);

  private:
  ///The real state of the system
  boost::numeric::ublas::vector<double> m_current_state;

  ///The parameters
  const boost::shared_ptr<const WhiteNoiseSystemParameters> m_parameters;
};

} //~namespace kalman
} //~namespace ribi

#endif // WHITENOISESYSTEM_H
