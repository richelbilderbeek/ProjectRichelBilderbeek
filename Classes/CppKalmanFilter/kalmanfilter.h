#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include <vector>
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "kalmanfiltertype.h"
#include "kalmanfilterparameters.h"
#include "kalmanfiltercalculationelements.h"

namespace ribi {
namespace kalman {

///Kalman filter base class
struct KalmanFilter : public boost::noncopyable
{
  virtual ~KalmanFilter() {}

  ///Obtain the Kalman filter type as an enum
  virtual KalmanFilterType GetType() const = 0;

  ///Get the Kalman filter last calculation elements
  const boost::shared_ptr<KalmanFilterCalculationElements>& GetLastCalculation() const
    { return m_last_calculation; }

  ///Obtain the Kalman filter parameters
  const boost::shared_ptr<const KalmanFilterParameters>& GetParameters() const
    { return m_parameters; }

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  virtual void SupplyMeasurementAndInput(
    const boost::numeric::ublas::vector<double>& measurements,
    const boost::numeric::ublas::vector<double>& input) = 0;

  protected:
  ///An ABC can only be constructed by derived classes
  explicit KalmanFilter(
    const boost::shared_ptr<KalmanFilterCalculationElements>& calculation,
    const boost::shared_ptr<const KalmanFilterParameters>& parameters
  );

  private:

  ///The Kalman filter last calculation elements
  const boost::shared_ptr<KalmanFilterCalculationElements> m_last_calculation;

  ///The Kalman filter parameters
  const boost::shared_ptr<const KalmanFilterParameters> m_parameters;
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTER_H
