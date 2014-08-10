#ifndef GAPSFILLEDWHITENOISESYSTEMFACTORY_H
#define GAPSFILLEDWHITENOISESYSTEMFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

#include "gapsfilledwhitenoisesystem.h"

namespace ribi {
namespace kalman {

///Factory for GapsFilledWhiteNoiseSystem
struct GapsFilledWhiteNoiseSystemFactory
{
  GapsFilledWhiteNoiseSystemFactory();

  ///Create a GapsFilledWhiteNoiseSystem from its parameters
  boost::shared_ptr<GapsFilledWhiteNoiseSystem> Create(
    const boost::numeric::ublas::matrix<double>& control,
    const boost::numeric::ublas::vector<double>& initial_state,
    const boost::numeric::ublas::vector<int>& measurement_frequency,
    const boost::numeric::ublas::vector<double>& real_measurement_noise,
    const boost::numeric::ublas::vector<double>& real_process_noise,
    const boost::numeric::ublas::matrix<double>& state_transition
  ) const noexcept;

  ///Create a GapsFilledWhiteNoiseSystem from the parameters
  boost::shared_ptr<GapsFilledWhiteNoiseSystem> Create(
    const boost::shared_ptr<WhiteNoiseSystemParameters>& parameters
  ) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // GAPSFILLEDWHITENOISESYSTEMFACTORY_H
