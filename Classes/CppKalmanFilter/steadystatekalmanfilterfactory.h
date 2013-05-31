#ifndef STEADYSTATEKALMANFILTERFACTORY_H
#define STEADYSTATEKALMANFILTERFACTORY_H

#include <boost/shared_ptr.hpp>
#include "steadystatekalmanfilter.h"

///Factory for SteadyStateKalmanFilter
struct SteadyStateKalmanFilterFactory
{
  static const boost::shared_ptr<SteadyStateKalmanFilter> Create(
    const boost::shared_ptr<const KalmanFilterParameters>& parameters);

};

#endif // STEADYSTATEKALMANFILTERFACTORY_H
