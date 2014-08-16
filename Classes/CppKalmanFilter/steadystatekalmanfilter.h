#ifndef STEADYSTATEKALMANFILTER_H
#define STEADYSTATEKALMANFILTER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#pragma GCC diagnostic pop


#include "kalmanfilter.h"
#include "steadystatekalmanfilterparameters.h"
#include "steadystatekalmanfiltercalculationelements.h"

namespace ribi {
namespace kalman {

///A discrete time Kalman filter
struct SteadyStateKalmanFilter : public KalmanFilter
{
  SteadyStateKalmanFilter(const SteadyStateKalmanFilter&) = delete;
  SteadyStateKalmanFilter& operator=(const SteadyStateKalmanFilter&) = delete;

  ///Clear the calculation, will set IsComplete to false
  //void Clear();

  ///Get the Kalman filter last calculation elements
  boost::shared_ptr<KalmanFilterCalculationElements> GetLastCalculation() const noexcept
  { return m_last_calculation; }

  ///Obtain the Kalman filter parameters
  boost::shared_ptr<const KalmanFilterParameters> GetParameters() const noexcept
  { return m_parameters; }

  ///Obtain the number of values a state consists of
  int GetStateSize() const noexcept;

  ///Obtain the current prediction of the state ('x')
  const boost::numeric::ublas::vector<double>& GetStateEstimate() const noexcept
   { return m_state_estimate; }

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const noexcept { return KalmanFilterType::steady_state; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Give the filter a measurement and input, and it will update its predictions
  void SupplyMeasurementAndInput(
    const boost::numeric::ublas::vector<double>& measurements,
    const boost::numeric::ublas::vector<double>& input);

  ///Let the filter estimate the next state
  boost::numeric::ublas::vector<double> PredictState(
    const boost::numeric::ublas::vector<double>& input) const;

  private:
  ///Initialize the filter with a first measurent
  explicit SteadyStateKalmanFilter(
    const boost::shared_ptr<KalmanFilterCalculationElements>& calculation,
    const boost::shared_ptr<const KalmanFilterParameters>& parameters);
  friend class SteadyStateKalmanFilterFactory;

  ///Can only be deleted by boost::checked_delete
  ~SteadyStateKalmanFilter() noexcept {}
  friend void boost::checked_delete<>(SteadyStateKalmanFilter*);

  ///The last calculation
  const boost::shared_ptr<SteadyStateKalmanFilterCalculationElements> m_last_calculation;

  ///The downcasted parameters
  const boost::shared_ptr<const SteadyStateKalmanFilterParameters> m_parameters;

  ///x: The (current prediction of the) state
  boost::numeric::ublas::vector<double> m_state_estimate;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // STEADYSTATEKALMANFILTER_H
