#ifndef STANDARDKALMANFILTERFACTORY_H
#define STANDARDKALMANFILTERFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

#include "standardkalmanfilter.h"

namespace ribi {
namespace kalman {

///Factory for StandardKalmanFilter
struct StandardKalmanFilterFactory
{
  StandardKalmanFilterFactory();

  boost::shared_ptr<StandardKalmanFilter> Create(
    const boost::shared_ptr<const KalmanFilterParameters>& parameters
  ) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // STANDARDKALMANFILTERFACTORY_H
