#ifndef KALMANFILTERFACTORY_H
#define KALMANFILTERFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

#include "kalmanfilter.h"

namespace ribi {
namespace kalman {

///Factory for KalmanFilter
struct KalmanFilterFactory
{
  KalmanFilterFactory();

  boost::shared_ptr<KalmanFilter> Create(
    const boost::shared_ptr<const KalmanFilterParameters>& parameters
  ) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTERFACTORY_H
