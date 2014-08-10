#ifndef STANDARDKALMANFILTERCALCULATIONELEMENTS_H
#define STANDARDKALMANFILTERCALCULATIONELEMENTS_H

#include "kalmanfiltertype.h"
#include "kalmanfiltercalculationelements.h"

namespace ribi {
namespace kalman {

///The elements of a standard Kalman filter calculation
struct StandardKalmanFilterCalculationElements : public KalmanFilterCalculationElements
{
  explicit StandardKalmanFilterCalculationElements(
    //Base
    const boost::numeric::ublas::vector<double>& measurement = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::vector<double>& predicted_state = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::vector<double>& previous_state_estimate = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::vector<double>& updated_state = boost::numeric::ublas::vector<double>(),
    //This class
    const boost::numeric::ublas::vector<double>& innovation = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::matrix<double>& innovation_covariance = boost::numeric::ublas::matrix<double>(),
    const boost::numeric::ublas::matrix<double>& kalman_gain = boost::numeric::ublas::matrix<double>(),
    const boost::numeric::ublas::matrix<double>& predicted_covariance = boost::numeric::ublas::matrix<double>(),
    const boost::numeric::ublas::matrix<double>& previous_covariance_estimate = boost::numeric::ublas::matrix<double>(),
    const boost::numeric::ublas::matrix<double>& updated_covariance = boost::numeric::ublas::matrix<double>());

  ///Clear the calculation, will set IsComplete to false
  void Clear();

  ///Produce a deep copy of the derived class
  boost::shared_ptr<KalmanFilterCalculationElements> Clone() const;

  ///Obtain the innovation ('y_squiggle')
  const boost::numeric::ublas::vector<double>& GetInnovation() const
    { return m_innovation; }

  ///Obtain he innovation covariance ('S')
  const boost::numeric::ublas::matrix<double>& GetInnovationCovariance() const
    { return m_innovation_covariance; }

  ///Obtain the Kalman gain ('K')
  const boost::numeric::ublas::matrix<double>& GetKalmanGain() const
    { return m_kalman_gain; }

  ///Obtain the predicted error estimation covariance ('P_predicted')
  const boost::numeric::ublas::matrix<double>& GetPredicatedCovariance() const
    { return m_predicted_covariance; }

  ///Obtain the previous_covariance_estimate ('P_prev'/'P_n-1')
  const boost::numeric::ublas::matrix<double>& GetPreviousCovarianceEstimate() const
    { return m_previous_covariance_estimate; }

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const { return KalmanFilterType::standard; }

  ///Obtain the updated error estimation covariance (in the end of each timestep)
  const boost::numeric::ublas::matrix<double>& GetUpdatedCovariance() const
    { return m_updated_covariance; }

  ///Checks if the state is complete and valid
  bool IsComplete() const;

  ///Set the innovation ('y_squiggle')
  ///Fails if already set
  void SetInnovation(const boost::numeric::ublas::vector<double>& innovation);

  ///Set the innovation covariance ('S')
  ///Fails if already set
  void SetInnovationCovariance(const boost::numeric::ublas::matrix<double>& innovation_covariance);

  ///Set the Kalman gain ('K')
  ///Fails if already set
  void SetKalmanGain(const boost::numeric::ublas::matrix<double>& kalman_gain);

  ///Set the predicted error estimation covariance ('P_predicted')
  ///Calculated at step 2 of the algorithm:
  ///2) P_predicted = [...] P_n-1 [...]
  ///Fails if already set
  void SetPredictedCovariance(const boost::numeric::ublas::matrix<double>& predicted_covariance);

  ///Set the previous_covariance_estimate ('P_prev'/'P_n-1')
  ///Is read at step 2 of the algorithm:
  ///2) P_predicted = [...] P_n-1 [...]
  ///Fails if already set
  void SetPreviousCovarianceEstimate(const boost::numeric::ublas::matrix<double>& previous_covariance_estimate);

  ///Set the updated error estimation covariance (in the end of each timestep)
  ///Calculated at step 7 of the algorithm:
  ///2) P_n = [...] P_predicted
  ///Fails if already set
  void SetUpdatedCovariance(const boost::numeric::ublas::matrix<double>& updated_covariance);

  private:
  ///Can only be deleted by boost::checked_delete
  ~StandardKalmanFilterCalculationElements() noexcept {}
  friend void boost::checked_delete<>(StandardKalmanFilterCalculationElements*);

  ///The innovation ('y_squiggle')
  boost::numeric::ublas::vector<double> m_innovation;

  ///The innovation covariance ('S')
  boost::numeric::ublas::matrix<double> m_innovation_covariance;

  ///The Kalman gain ('K')
  boost::numeric::ublas::matrix<double> m_kalman_gain;

  ///The predicted error estimation covariance ('P_predicted')
  ///Calculated at step 2 of the algorithm:
  ///2) P_predicted = [...] P_n-1 [...]
  boost::numeric::ublas::matrix<double> m_predicted_covariance;

  ///The previous_covariance_estimate ('P_prev'/'P_n-1')
  ///Is read at step 2 of the algorithm:
  ///2) P_predicted = [...] P_n-1 [...]
  boost::numeric::ublas::matrix<double> m_previous_covariance_estimate;

  ///The updated error estimation covariance (in the end of each timestep)
  ///Calculated at step 7 of the algorithm:
  ///2) P_n = [...] P_predicted
  boost::numeric::ublas::matrix<double> m_updated_covariance;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // STANDARDKALMANFILTERCALCULATIONELEMENTS_H
