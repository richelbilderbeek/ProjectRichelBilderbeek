#ifndef STEADYSTATEKALMANFILTER_H
#define STEADYSTATEKALMANFILTER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include "kalmanfilter.h"
#include "steadystatekalmanfilterparameters.h"
#include "steadystatekalmanfiltercalculationelements.h"

#pragma GCC diagnostic pop

namespace ribi {

///A discrete time Kalman filter
struct SteadyStateKalmanFilter : public KalmanFilter
{
  ///Clear the calculation, will set IsComplete to false
  void Clear();

  ///Obtain the number of values a state consists of
  int GetStateSize() const;

  ///Obtain the current prediction of the state ('x')
  const boost::numeric::ublas::vector<double>& GetStateEstimate() const { return m_state_estimate; }

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const { return KalmanFilterType::steady_state; }

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Give the filter a measurement and input, and it will update its predictions
  void SupplyMeasurementAndInput(
    const boost::numeric::ublas::vector<double>& measurements,
    const boost::numeric::ublas::vector<double>& input);

  ///Let the filter estimate the next state
  const boost::numeric::ublas::vector<double> PredictState(
    const boost::numeric::ublas::vector<double>& input) const;

  private:
  ///Initialize the filter with a first measurent
  explicit SteadyStateKalmanFilter(
    const boost::shared_ptr<KalmanFilterCalculationElements>& calculation,
    const boost::shared_ptr<const KalmanFilterParameters>& parameters);
  friend class SteadyStateKalmanFilterFactory;

  ///Can only be deleted by boost::checked_delete
  ~SteadyStateKalmanFilter() {}
  friend void boost::checked_delete<>(SteadyStateKalmanFilter*);

  ///The last calculation
  const boost::shared_ptr<SteadyStateKalmanFilterCalculationElements> m_last_calculation;

  ///The downcasted parameters
  const SteadyStateKalmanFilterParameters * const m_parameters;

  ///x: The (current prediction of the) state
  boost::numeric::ublas::vector<double> m_state_estimate;

};

} //~namespace ribi

#endif // STEADYSTATEKALMANFILTER_H
