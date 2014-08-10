#ifndef GAPSFILLEDWHITENOISESYSTEM_H
#define GAPSFILLEDWHITENOISESYSTEM_H

#include <queue>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

#include "whitenoisesystem.h"
#include "whitenoisesystemparameters.h"
#include "gapsfilledwhitenoisesystemparameters.h"

namespace ribi {
namespace kalman {

///A gaps-filled white noise system is a system that does not have a measurement every timestep.
///Instead, it has for example 1 measurement and then 4 non-measurements (which is a gap of 5)
///During the 4 non-measurements the 1 measurement is repeated
struct GapsFilledWhiteNoiseSystem : public WhiteNoiseSystem
{
  ///Obtain the gaps-filled white noise system parameters
  const boost::shared_ptr<const GapsFilledWhiteNoiseSystemParameters>&
    GetGapsFilledWhiteNoiseSystemParameters() const noexcept
      { return m_parameters; }

  ///Obtain the type as an enum
  WhiteNoiseSystemType GetType() const noexcept { return WhiteNoiseSystemType::gaps_filled; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Update reality, that is, let the real system (i.e. reality) go to its next state
  void GoToNextState(const boost::numeric::ublas::vector<double>& input);

  ///Measure a value from this system with normally distributed noise
  boost::numeric::ublas::vector<double> Measure() const;

  ///Peek what the real value is
  const boost::numeric::ublas::vector<double>& PeekAtRealState() const noexcept;

  private:
  ///GapsFilledWhiteNoiseSystem must be created with a GapsFilledWhiteNoiseSystemFactory
  explicit GapsFilledWhiteNoiseSystem(const boost::shared_ptr<const WhiteNoiseSystemParameters>& white_noise_system_parameters);
  friend class GapsFilledWhiteNoiseSystemFactory;

  ///Can only be deleted by boost::checked_delete
  ~GapsFilledWhiteNoiseSystem() noexcept {}
  friend void boost::checked_delete<>(GapsFilledWhiteNoiseSystem*);

  ///The last successfull measurement
  mutable boost::numeric::ublas::vector<double> m_last_measument;

  ///The gaps-filled white noise system parameters
  const boost::shared_ptr<const GapsFilledWhiteNoiseSystemParameters> m_parameters;

  ///The current timestep: zero denotes a measurement will be done
  mutable int m_timestep;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // GAPSFILLEDWHITENOISESYSTEM_H
