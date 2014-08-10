#ifndef STANDARDKALMANFILTER_H
#define STANDARDKALMANFILTER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#pragma GCC diagnostic pop

#include "kalmanfilter.h"
#include "standardkalmanfilterparameters.h"
#include "standardkalmanfiltercalculationelements.h"


namespace ribi {
namespace kalman {

///A discrete time Kalman filter
struct StandardKalmanFilter : public KalmanFilter
{
  ///Obtain the estimation error covariance ('P'), which is updated during SupplyMeasurementAndInput
  const boost::numeric::ublas::matrix<double>& GetEstimationErrorCovariance() const noexcept
    { return m_covariance_estimate; }

  ///Get the Kalman filter last calculation elements
  boost::shared_ptr<KalmanFilterCalculationElements> GetLastCalculation() const noexcept
  { return m_last_standard_calculation; }

  ///Obtain the (downcasted) calculation
  const boost::shared_ptr<StandardKalmanFilterCalculationElements> GetLastStandardCalculation() const noexcept
    { return m_last_standard_calculation; }

  ///Obtain the Kalman filter parameters
  boost::shared_ptr<const KalmanFilterParameters> GetParameters() const noexcept
  { return m_standard_parameters; }

  ///The downcasted parameters
  boost::shared_ptr<const StandardKalmanFilterParameters> GetStandardParameters() const noexcept
    { return m_standard_parameters; }

  ///Obtain the number of values a state consists of
  int GetStateSize() const noexcept;

  ///Obtain the current prediction of the state ('x')
  const boost::numeric::ublas::vector<double>& GetStateEstimate() const noexcept { return m_state_estimate; }

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const noexcept { return KalmanFilterType::standard; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Give the filter a measurement and input, and it will update its predictions
  ///Also logs the calculation
  void SupplyMeasurementAndInput(
    const boost::numeric::ublas::vector<double>& measurements,
    const boost::numeric::ublas::vector<double>& input);

  ///Let the filter estimate the next state
  boost::numeric::ublas::vector<double> PredictState(
    const boost::numeric::ublas::vector<double>& input) const;

  ///Let the filter estimate the next estimation error covariance
  boost::numeric::ublas::matrix<double> PredictCovariance() const;

  private:
  ///Initialize the filter with a first measurent
  explicit StandardKalmanFilter(
    const boost::shared_ptr<StandardKalmanFilterCalculationElements>& calculation,
    const boost::shared_ptr<const KalmanFilterParameters>& parameters
  );
  friend class StandardKalmanFilterFactory;

  ///Can only be deleted by boost::checked_delete
  ~StandardKalmanFilter() noexcept {}
  friend void boost::checked_delete<>(StandardKalmanFilter*);

  ///P: The estimation error covariance
  boost::numeric::ublas::matrix<double> m_covariance_estimate;

  ///The downcasted parameters
  const boost::shared_ptr<StandardKalmanFilterCalculationElements> m_last_standard_calculation;

  ///The Kalman filter parameters
  //const boost::shared_ptr<const KalmanFilterParameters> m_parameters;

  ///The downcasted parameters
  const boost::shared_ptr<const StandardKalmanFilterParameters> m_standard_parameters;

  ///x: The (current prediction of the) state
  boost::numeric::ublas::vector<double> m_state_estimate;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // STANDARDKALMANFILTER_H
