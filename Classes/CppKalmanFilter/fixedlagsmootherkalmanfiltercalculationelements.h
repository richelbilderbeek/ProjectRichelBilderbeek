#ifndef FIXEDLAGSMOOTHERKALMANFILTERCALCULATIONELEMENTS_H
#define FIXEDLAGSMOOTHERKALMANFILTERCALCULATIONELEMENTS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "kalmanfiltercalculationelements.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace kalman {

struct StandardKalmanFilterCalculationElements;

struct FixedLagSmootherKalmanFilterCalculationElements : public KalmanFilterCalculationElements
{
  explicit FixedLagSmootherKalmanFilterCalculationElements(
    const boost::numeric::ublas::vector<double>& measurement = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::vector<double>& predicted_state = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::vector<double>& previous_state_estimate = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::vector<double>& updated_state = boost::numeric::ublas::vector<double>());

  ///Clear the calculation, will set IsComplete to false
  void Clear();

  ///Produce a deep copy of the derived class
  boost::shared_ptr<KalmanFilterCalculationElements> Clone() const;

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const { return KalmanFilterType::fixed_lag_smoother; }

  ///Checks if the state is complete and valid
  bool IsComplete() const;

  void SetStandardCalculationElement(
    const boost::shared_ptr<StandardKalmanFilterCalculationElements>& standard_calculation);

  private:
  boost::shared_ptr<const StandardKalmanFilterCalculationElements> m_standard_calculation;

  ///Can only be deleted by boost::checked_delete
  ~FixedLagSmootherKalmanFilterCalculationElements() noexcept {}
  friend void boost::checked_delete<>(FixedLagSmootherKalmanFilterCalculationElements*);

};

} //~namespace kalman
} //~namespace ribi

#endif // FIXEDLAGSMOOTHERKALMANFILTERCALCULATIONELEMENTS_H
