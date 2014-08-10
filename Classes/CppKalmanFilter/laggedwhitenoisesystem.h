#ifndef LAGGEDWHITENOISESYSTEM_H
#define LAGGEDWHITENOISESYSTEM_H

#include <queue>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

#include "whitenoisesystem.h"
#include "whitenoisesystemparameters.h"
#include "laggedwhitenoisesystemparameters.h"
#include "standardwhitenoisesystem.h"

namespace ribi {
namespace kalman {

///A lagged white noise system is a system that can be measured only after a certain number
///of periods.
struct LaggedWhiteNoiseSystem : public WhiteNoiseSystem
{
  ///Obtain the lagged white noise system parameters
  const boost::shared_ptr<const LaggedWhiteNoiseSystemParameters>& GetLaggedWhiteNoiseSystemParameters() const
    { return m_parameters; }

  ///Obtain the type as an enum
  WhiteNoiseSystemType GetType() const noexcept { return WhiteNoiseSystemType::lagged; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Update reality, that is, let the real system (i.e. reality) go to its next state
  void GoToNextState(const boost::numeric::ublas::vector<double>& input);

  ///Measure a value from this system with normally distributed noise
  boost::numeric::ublas::vector<double> Measure() const noexcept;

  ///Peek what the real value is
  const boost::numeric::ublas::vector<double>& PeekAtRealState() const noexcept;

  private:
  ///LaggedWhiteNoiseSystem must be created with a LaggedWhiteNoiseSystemFactory
  explicit LaggedWhiteNoiseSystem(const boost::shared_ptr<const WhiteNoiseSystemParameters>& white_noise_system_parameters);
  friend class LaggedWhiteNoiseSystemFactory;

  ///Can only be deleted by boost::checked_delete
  ~LaggedWhiteNoiseSystem() noexcept {}
  friend void boost::checked_delete<>(LaggedWhiteNoiseSystem*);

  ///The front one is the one that can be read,
  ///the back one is the freshest measurement
  mutable std::queue<boost::numeric::ublas::vector<double> > m_measuments;

  ///The lagged white noise system parameters
  const boost::shared_ptr<const LaggedWhiteNoiseSystemParameters> m_parameters;

  ///The standard white noise system used as an engine
  boost::shared_ptr<StandardWhiteNoiseSystem> m_system;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // LAGGEDWHITENOISESYSTEM_H
