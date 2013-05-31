#ifndef STEADYSTATEKALMANFILTERCALCULATIONELEMENTS_H
#define STEADYSTATEKALMANFILTERCALCULATIONELEMENTS_H

#include "kalmanfiltercalculationelements.h"

///The elements of a steady-state Kalman filter calculation
struct SteadyStateKalmanFilterCalculationElements : public KalmanFilterCalculationElements
{
  SteadyStateKalmanFilterCalculationElements(
    const boost::numeric::ublas::vector<double>& measurement = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::vector<double>& predicted_state = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::vector<double>& previous_state_estimate = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::vector<double>& updated_state = boost::numeric::ublas::vector<double>());

  ///Produce a deep copy of the derived class
  const boost::shared_ptr<KalmanFilterCalculationElements> Clone() const;

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const { return KalmanFilterType::steady_state; }

  ///Checks if the state is complete and valid
  bool IsComplete() const;

  private:
  ///Can only be deleted by boost::checked_delete
  ~SteadyStateKalmanFilterCalculationElements() {}
  friend void boost::checked_delete<>(SteadyStateKalmanFilterCalculationElements*);

};

#endif // STEADYSTATEKALMANFILTERCALCULATIONELEMENTS_H
