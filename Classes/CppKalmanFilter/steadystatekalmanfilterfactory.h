#ifndef STEADYSTATEKALMANFILTERFACTORY_H
#define STEADYSTATEKALMANFILTERFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

#include "steadystatekalmanfilter.h"

namespace ribi {
namespace kalman {

///Factory for SteadyStateKalmanFilter
struct SteadyStateKalmanFilterFactory
{
  static const boost::shared_ptr<SteadyStateKalmanFilter> Create(
    const boost::shared_ptr<const KalmanFilterParameters>& parameters);

};

} //~namespace kalman
} //~namespace ribi

#endif // STEADYSTATEKALMANFILTERFACTORY_H
