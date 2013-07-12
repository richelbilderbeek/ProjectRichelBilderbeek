#ifndef STANDARDKALMANFILTER_H
#define STANDARDKALMANFILTER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include "kalmanfilter.h"
#include "standardkalmanfilterparameters.h"
#include "standardkalmanfiltercalculationelements.h"

#pragma GCC diagnostic pop

///A discrete time Kalman filter
struct StandardKalmanFilter : public KalmanFilter
{
  ///Obtain the estimation error covariance ('P'), which is updated during SupplyMeasurementAndInput
  const boost::numeric::ublas::matrix<double>& GetEstimationErrorCovariance() const
    { return m_covariance_estimate; }

  ///Obtain the (downcasted) calculation
  const boost::shared_ptr<StandardKalmanFilterCalculationElements>& GetLastStandardCalculation() const
    { return m_last_standard_calculation; }

  ///The downcasted parameters
  const boost::shared_ptr<const StandardKalmanFilterParameters>& GetStandardParameters() const
    { return m_standard_parameters; }

  ///Obtain the number of values a state consists of
  int GetStateSize() const;

  ///Obtain the current prediction of the state ('x')
  const boost::numeric::ublas::vector<double>& GetStateEstimate() const { return m_state_estimate; }

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const { return KalmanFilterType::standard; }

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Give the filter a measurement and input, and it will update its predictions
  ///Also logs the calculation
  void SupplyMeasurementAndInput(
    const boost::numeric::ublas::vector<double>& measurements,
    const boost::numeric::ublas::vector<double>& input);

  ///Let the filter estimate the next state
  const boost::numeric::ublas::vector<double> PredictState(
    const boost::numeric::ublas::vector<double>& input) const;

  ///Let the filter estimate the next estimation error covariance
  const boost::numeric::ublas::matrix<double> PredictCovariance() const;

  private:
  ///Initialize the filter with a first measurent
  StandardKalmanFilter(
    const boost::shared_ptr<StandardKalmanFilterCalculationElements>& calculation,
    const boost::shared_ptr<const KalmanFilterParameters>& parameters
  );
  friend class StandardKalmanFilterFactory;

  ///Can only be deleted by boost::checked_delete
  ~StandardKalmanFilter() {}
  friend void boost::checked_delete<>(StandardKalmanFilter*);

  ///P: The estimation error covariance
  boost::numeric::ublas::matrix<double> m_covariance_estimate;

  ///The downcasted parameters
  const boost::shared_ptr<StandardKalmanFilterCalculationElements> m_last_standard_calculation;

  ///The downcasted parameters
  const boost::shared_ptr<const StandardKalmanFilterParameters> m_standard_parameters;

  ///x: The (current prediction of the) state
  boost::numeric::ublas::vector<double> m_state_estimate;


};

#endif // STANDARDKALMANFILTER_H
