#ifndef STANDARDKALMANFILTERFACTORY_H
#define STANDARDKALMANFILTERFACTORY_H

#include <boost/shared_ptr.hpp>
#include "standardkalmanfilter.h"

namespace ribi {

///Factory for StandardKalmanFilter
struct StandardKalmanFilterFactory
{
  static const boost::shared_ptr<StandardKalmanFilter> Create(
    const boost::shared_ptr<const KalmanFilterParameters>& parameters);
};

} //~namespace ribi

#endif // STANDARDKALMANFILTERFACTORY_H
