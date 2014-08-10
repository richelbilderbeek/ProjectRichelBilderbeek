#ifndef STANDARDWHITENOISESYSTEM_H
#define STANDARDWHITENOISESYSTEM_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#pragma GCC diagnostic pop

#include "standardwhitenoisesystemparameters.h"
#include "whitenoisesystem.h"
#include "whitenoisesystemparameters.h"

namespace ribi {
namespace kalman {

struct StandardWhiteNoiseSystem : public WhiteNoiseSystem
{
  ///Obtain the type as an enum
  WhiteNoiseSystemType GetType() const noexcept { return WhiteNoiseSystemType::standard; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Update reality, that is, let the real system (i.e. reality) go to its next state,
  ///without any input
  void GoToNextState();

  ///Update reality, that is, let the real system (i.e. reality) go to its next state
  void GoToNextState(const boost::numeric::ublas::vector<double>& input);

  ///Measure a value from this system with normally distributed noise
  boost::numeric::ublas::vector<double> Measure() const noexcept;

  private:
  ///StandardWhiteNoiseSystem can only be created by a StandardWhiteNoiseSystemFactory
  explicit StandardWhiteNoiseSystem(const boost::shared_ptr<const WhiteNoiseSystemParameters>& parameters);
  friend class StandardWhiteNoiseSystemFactory;

  ///Can only be deleted by boost::checked_delete
  ~StandardWhiteNoiseSystem() noexcept {}
  friend void boost::checked_delete<>(StandardWhiteNoiseSystem*);

  ///The parameters for the white noise system
  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters> m_parameters;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // STANDARDWHITENOISESYSTEM_H
