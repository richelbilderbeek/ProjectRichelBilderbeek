#ifndef FIXEDLAGSMOOTHERKALMANFILTERFACTORY_H
#define FIXEDLAGSMOOTHERKALMANFILTERFACTORY_H

#include "fixedlagsmootherkalmanfilter.h"

namespace ribi {
namespace kalman {

///Factory for FixedLagSmootherKalmanFilter
struct FixedLagSmootherKalmanFilterFactory
{
  static const boost::shared_ptr<FixedLagSmootherKalmanFilter> Create(
    const boost::shared_ptr<const KalmanFilterParameters>& parameters);
};

} //~namespace kalman
} //~namespace ribi

#endif // FIXEDLAGSMOOTHERKALMANFILTERFACTORY_H
