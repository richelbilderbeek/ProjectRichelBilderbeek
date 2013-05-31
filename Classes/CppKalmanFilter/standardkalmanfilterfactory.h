#ifndef STANDARDKALMANFILTERFACTORY_H
#define STANDARDKALMANFILTERFACTORY_H

#include <boost/shared_ptr.hpp>
#include "standardkalmanfilter.h"

///Factory for StandardKalmanFilter
struct StandardKalmanFilterFactory
{
  static const boost::shared_ptr<StandardKalmanFilter> Create(
    const boost::shared_ptr<const KalmanFilterParameters>& parameters);
};

#endif // STANDARDKALMANFILTERFACTORY_H
