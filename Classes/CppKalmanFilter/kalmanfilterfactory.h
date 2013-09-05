#ifndef KALMANFILTERFACTORY_H
#define KALMANFILTERFACTORY_H


#include <boost/shared_ptr.hpp>
#include "kalmanfilter.h"

namespace ribi {

///Factory for KalmanFilter
struct KalmanFilterFactory
{
  static const boost::shared_ptr<KalmanFilter> Create(
    const boost::shared_ptr<const KalmanFilterParameters>& parameters);
};

} //~namespace ribi

#endif // KALMANFILTERFACTORY_H
