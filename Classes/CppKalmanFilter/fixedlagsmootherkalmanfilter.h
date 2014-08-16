#ifndef FIXEDLAGSMOOTHERKALMANFILTER_H
#define FIXEDLAGSMOOTHERKALMANFILTER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "kalmanfilter.h"
#include "standardkalmanfilter.h"
#include "standardkalmanfilterparameters.h"
#include "fixedlagsmootherkalmanfilterparameters.h"
#include "fixedlagsmootherkalmanfiltercalculationelements.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace kalman {

struct FixedLagSmootherKalmanFilter : public KalmanFilter
{
  ///The augmented estimation error covariances, that is the estimation error covariance for each lag timestep
  ///Use boost::numeric::ublas::matrix<double> instead of
  ///std::vector<boost::numeric::ublas::vector<double> > to allow for matrix operation
  ///   Complex        Simplified
  /// [ [ A B ] ]
  /// [ [ C D ] ]       [ A B ]
  /// [         ]       [ C D ]
  /// [ [ E F ] ]       [ E F ]
  /// [ [ G H ] ]   ->  [ G H ]
  //const boost::numeric::ublas::matrix<double>& GetEstimationErrorCovariances() const { return m_estimation_error_covariances; }

  ///Get the Kalman filter last calculation elements
  boost::shared_ptr<KalmanFilterCalculationElements> GetLastCalculation() const
  {
    return m_last_calculation;
  }

  ///The last augmented Kalman gains, that is the gain for each lag timestep
  ///Use boost::numeric::ublas::matrix<double> instead of
  ///std::vector<boost::numeric::ublas::vector<double> > to allow for matrix operation
  ///   Complex        Simplified
  /// [ [ A B ] ]
  /// [ [ C D ] ]       [ A B ]
  /// [         ]       [ C D ]
  /// [ [ E F ] ]       [ E F ]
  /// [ [ G H ] ]   ->  [ G H ]
  //const boost::numeric::ublas::matrix<double>& GetLastGains() const { return m_kalman_gains; }

  ///The last predicted augmented estimation error covariances,
  ///that is the estimation error covariance for each lag timestep
  ///Use boost::numeric::ublas::matrix<double> instead of
  ///std::vector<boost::numeric::ublas::vector<double> > to allow for matrix operation
  ///   Complex        Simplified
  /// [ [ A B ] ]
  /// [ [ C D ] ]       [ A B ]
  /// [         ]       [ C D ]
  /// [ [ E F ] ]       [ E F ]
  /// [ [ G H ] ]   ->  [ G H ]
  //const boost::numeric::ublas::matrix<double>& GetLastPredictedCovariances() const { return m_last_predicted_covariances; }

  ///The last predicted augmented states
  ///Use boost::numeric::ublas::vector<double> instead of
  ///std::vector<boost::numeric::ublas::vector<double> > to allow for matrix operation
  ///  Complex       Simplified
  /// [ [ A ] ]
  /// [ [ B ] ]        [ A ]
  /// [       ]        [ B ]
  /// [ [ C ] ]        [ C ]
  /// [ [ D ] ]   ->   [ D ]
  //const boost::numeric::ublas::vector<double>& GetLastPredictedStates() const { return m_last_predicted_states; }

  ///Obtain the Kalman filter parameters
  boost::shared_ptr<const KalmanFilterParameters> GetParameters() const
  {
    return m_parameters;
  }

  ///The augmented states, that is the state for each lag timestep
  ///Use boost::numeric::ublas::vector<double> instead of
  ///std::vector<boost::numeric::ublas::vector<double> > to allow for matrix operation
  ///  Complex       Simplified
  /// [ [ A ] ]
  /// [ [ B ] ]        [ A ]
  /// [       ]        [ B ]
  /// [ [ C ] ]        [ C ]
  /// [ [ D ] ]   ->   [ D ]
  const boost::numeric::ublas::vector<double>& GetStateEstimates() const { return m_state_estimates; }

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const { return KalmanFilterType::fixed_lag_smoother; }

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Let the filter predict
  boost::numeric::ublas::vector<double> PredictState(
    const boost::numeric::ublas::vector<double>& input) const;

  ///Give the filter a measurement and input, and it will update its predictions
  void SupplyMeasurementAndInput(
    const boost::numeric::ublas::vector<double>& x,
    const boost::numeric::ublas::vector<double>& input);

  private:
  ///Only a FixedLagSmootherKalmanFilterFactory can create a FixedLagSmootherKalmanFilter
  explicit FixedLagSmootherKalmanFilter(
    const boost::shared_ptr<FixedLagSmootherKalmanFilterCalculationElements>& calculation,
    const boost::shared_ptr<const KalmanFilterParameters>& parameters);
  friend class FixedLagSmootherKalmanFilterFactory;

  ///Can only be deleted by boost::checked_delete
  ~FixedLagSmootherKalmanFilter() noexcept {}
  friend void boost::checked_delete<>(FixedLagSmootherKalmanFilter*);
  friend void boost::checked_delete<>(const FixedLagSmootherKalmanFilter*);

  ///The Kalman filter last calculation elements
  const boost::shared_ptr<KalmanFilterCalculationElements> m_last_calculation;

  ///The (downcasted) calculation
  const boost::shared_ptr<FixedLagSmootherKalmanFilterCalculationElements> m_last_fixed_lag_smoother_calculation;

  ///The standard (unlagged) Kalman filter used
  const boost::shared_ptr<StandardKalmanFilter> m_standard_filter;

  ///The augmented estimation error covariances, that is the estimation error covariance for each lag timestep
  ///Use boost::numeric::ublas::matrix<double> instead of
  ///std::vector<boost::numeric::ublas::vector<double> > to allow for matrix operation
  ///   Complex        Simplified
  /// [ [ A B ] ]
  /// [ [ C D ] ]       [ A B ]
  /// [         ]       [ C D ]
  /// [ [ E F ] ]       [ E F ]
  /// [ [ G H ] ]   ->  [ G H ]
  //boost::numeric::ublas::matrix<double> m_estimation_error_covariances;

  ///The augmented Kalman gains, that is the gain for each lag timestep
  ///Use boost::numeric::ublas::matrix<double> instead of
  ///std::vector<boost::numeric::ublas::vector<double> > to allow for matrix operation
  ///   Complex        Simplified
  /// [ [ A B ] ]
  /// [ [ C D ] ]       [ A B ]
  /// [         ]       [ C D ]
  /// [ [ E F ] ]       [ E F ]
  /// [ [ G H ] ]   ->  [ G H ]
  //boost::numeric::ublas::matrix<double> m_kalman_gains;

  ///The augmented Kalman gains, that is the gain for each lag timestep
  ///Use boost::numeric::ublas::matrix<double> instead of
  ///std::vector<boost::numeric::ublas::vector<double> > to allow for matrix operation
  ///   Complex        Simplified
  /// [ [ A B ] ]
  /// [ [ C D ] ]       [ A B ]
  /// [         ]       [ C D ]
  /// [ [ E F ] ]       [ E F ]
  /// [ [ G H ] ]   ->  [ G H ]
  //boost::numeric::ublas::matrix<double> m_last_kalman_gains;

  ///The last predicted augmented estimation error covariances,
  ///that is the estimation error covariance for each lag timestep
  ///Use boost::numeric::ublas::matrix<double> instead of
  ///std::vector<boost::numeric::ublas::vector<double> > to allow for matrix operation
  ///   Complex        Simplified
  /// [ [ A B ] ]
  /// [ [ C D ] ]       [ A B ]
  /// [         ]       [ C D ]
  /// [ [ E F ] ]       [ E F ]
  /// [ [ G H ] ]   ->  [ G H ]
  //boost::numeric::ublas::matrix<double> m_last_predicted_covariances;

  ///The last predicted augmented states
  ///Use boost::numeric::ublas::vector<double> instead of
  ///std::vector<boost::numeric::ublas::vector<double> > to allow for matrix operation
  ///  Complex       Simplified
  /// [ [ A ] ]
  /// [ [ B ] ]        [ A ]
  /// [       ]        [ B ]
  /// [ [ C ] ]        [ C ]
  /// [ [ D ] ]   ->   [ D ]
  //boost::numeric::ublas::vector<double> m_last_predicted_states;

  ///The downcasted parameters
  const boost::shared_ptr<const FixedLagSmootherKalmanFilterParameters> m_parameters;

  ///The augmented states, that is the state for each lag timestep
  ///Use boost::numeric::ublas::vector<double> instead of
  ///std::vector<boost::numeric::ublas::vector<double> > to allow for matrix operation
  ///  Complex       Simplified
  /// [ [ A ] ]
  /// [ [ B ] ]        [ A ]
  /// [       ]        [ B ]
  /// [ [ C ] ]        [ C ]
  /// [ [ D ] ]   ->   [ D ]
  boost::numeric::ublas::vector<double> m_state_estimates;

  static boost::numeric::ublas::vector<boost::numeric::ublas::vector<double>> CreateComplexInitialStates(
    const boost::shared_ptr<const FixedLagSmootherKalmanFilterParameters>& parameters);

  static boost::numeric::ublas::vector<boost::numeric::ublas::matrix<double>> CreateInitialGains(
    const int lag,
    const StandardKalmanFilter& filter);

  static boost::numeric::ublas::vector<double> CreateInitialStates(
    const boost::shared_ptr<const FixedLagSmootherKalmanFilterParameters>& parameters);

  ///         [ I ]
  ///         [ 0 ]
  ///term_a = [ 0 ], where I denotes an identity matrix with size input.size() x input.size()
  ///                and where 0 denotes a null matrix with size input.size() x input.size()
  ///The length of term_a is equal to the lag (3 in this example)
  static boost::numeric::ublas::vector<boost::numeric::ublas::matrix<double>> CreateComplexTermA(
    const int lag,
    const int state_size);

  ///         [ 0  0  0]
  ///         [ I  0  0]
  ///term_b = [ 0  I  0], where I denotes an identity matrix with size input.size() x input.size()
  ///                     and where 0 denotes a null matrix with size input.size() x input.size()
  ///The size of term_b is lag x lag (3 in this example)
  static boost::numeric::ublas::matrix<boost::numeric::ublas::matrix<double>> CreateComplexTermB(
    const int lag,
    const int state_size);

  ///                  [ 1 0 ]
  ///                  [ 0 1 ]
  ///                  [ 0 0 ]
  ///         [ I ]    [ 0 0 ]
  ///         [ 0 ]    [ 0 0 ]
  ///term_a = [ 0 ] => [ 0 0 ],
  ///  where I denotes an identity matrix with size input.size() x input.size()
  ///  and where 0 denotes a null matrix with size input.size() x input.size()
  ///The size of term_a will be:
  /// - number of rows   : lag (3) x input.size() (2) = 6
  /// - number of columns:           input.size() (2) = 2
  static boost::numeric::ublas::matrix<double> CreateTermA(
    const int lag,
    const int state_size);

  ///                       [ 0 0 0 0 0 0 ]
  ///                       [ 0 0 0 0 0 0 ]
  ///                       [ 1 0 0 0 0 0 ]
  ///         [ 0  0  0]    [ 0 1 0 0 0 0 ]
  ///         [ I  0  0]    [ 0 0 1 0 0 0 ]
  ///term_b = [ 0  I  0] => [ 0 0 0 1 0 0 ]
  ///where I denotes an identity matrix with size input.size() x input.size()
  ///                     and where 0 denotes a null matrix with size input.size() x input.size()
  ///The size of term_b is lag x lag (3 in this example)
  ///The size of term_b will be:
  /// - number of rows   : lag (3) x input.size() (2) = 6
  /// - number of columns: lag (3) x input.size() (2) = 6
  static boost::numeric::ublas::matrix<double> CreateTermB(
    const int lag,
    const int state_size);

  static boost::shared_ptr<const FixedLagSmootherKalmanFilterParameters> DownCast(
    const boost::shared_ptr<const KalmanFilterParameters>& parameters);

  ///Obtain the (unlagged) Kalman filter
  boost::shared_ptr<const StandardKalmanFilter> GetStandardKalmanFilter() const { return m_standard_filter; }

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // FIXEDLAGSMOOTHERKALMANFILTER_H
