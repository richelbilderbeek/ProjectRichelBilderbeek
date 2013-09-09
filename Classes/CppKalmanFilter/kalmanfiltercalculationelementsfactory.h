#ifndef KALMANFILTERCALCULATIONELEMENTSFACTORY_H
#define KALMANFILTERCALCULATIONELEMENTSFACTORY_H

#include <boost/shared_ptr.hpp>
#include "kalmanfiltercalculationelements.h"

namespace ribi {
namespace kalman {

struct KalmanFilterCalculationElementsFactory
{
  ///Create a KalmanFilterCalculationElements of a certain type
  static const boost::shared_ptr<KalmanFilterCalculationElements> Create(
    const KalmanFilterType type);

  ///Deep copy
  static const boost::shared_ptr<KalmanFilterCalculationElements> DeepCopy(
    const boost::shared_ptr<KalmanFilterCalculationElements>& elements);
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTERCALCULATIONELEMENTSFACTORY_H
