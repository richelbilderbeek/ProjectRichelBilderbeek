#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include "kalmanfiltertype.h"
#include "kalmanfilterparameters.h"
#include "kalmanfiltercalculationelements.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace kalman {

///Kalman filter base class
struct KalmanFilter
{
  KalmanFilter(const KalmanFilter&) = delete;
  KalmanFilter& operator=(const KalmanFilter&) = delete;
  virtual ~KalmanFilter() noexcept {}

  ///Obtain the Kalman filter type as an enum
  virtual KalmanFilterType GetType() const = 0;

  ///Get the Kalman filter last calculation elements
  virtual const boost::shared_ptr<KalmanFilterCalculationElements> GetLastCalculation() const = 0;

  ///Obtain the Kalman filter parameters
  virtual const boost::shared_ptr<const KalmanFilterParameters> GetParameters() const = 0;

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  virtual void SupplyMeasurementAndInput(
    const boost::numeric::ublas::vector<double>& measurements,
    const boost::numeric::ublas::vector<double>& input) = 0;

  protected:
  explicit KalmanFilter() {}

  private:
  /*
  ///An ABC can only be constructed by derived classes
  explicit KalmanFilter(
    const boost::shared_ptr<KalmanFilterCalculationElements>& calculation,
    const boost::shared_ptr<const KalmanFilterParameters>& parameters
  );

  ///The Kalman filter last calculation elements
  const boost::shared_ptr<KalmanFilterCalculationElements> m_last_calculation;

  ///The Kalman filter parameters
  const boost::shared_ptr<const KalmanFilterParameters> m_parameters;
  */
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTER_H
