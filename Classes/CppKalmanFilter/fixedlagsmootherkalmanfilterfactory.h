#ifndef FIXEDLAGSMOOTHERKALMANFILTERFACTORY_H
#define FIXEDLAGSMOOTHERKALMANFILTERFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "fixedlagsmootherkalmanfilter.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace kalman {

///Factory for FixedLagSmootherKalmanFilter
struct FixedLagSmootherKalmanFilterFactory
{
  FixedLagSmootherKalmanFilterFactory();

  boost::shared_ptr<FixedLagSmootherKalmanFilter> Create(
    const boost::shared_ptr<const KalmanFilterParameters>& parameters
  ) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // FIXEDLAGSMOOTHERKALMANFILTERFACTORY_H
