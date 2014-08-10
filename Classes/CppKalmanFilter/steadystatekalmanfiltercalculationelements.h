#ifndef STEADYSTATEKALMANFILTERCALCULATIONELEMENTS_H
#define STEADYSTATEKALMANFILTERCALCULATIONELEMENTS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "kalmanfiltercalculationelements.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace kalman {

///The elements of a steady-state Kalman filter calculation
struct SteadyStateKalmanFilterCalculationElements : public KalmanFilterCalculationElements
{
  explicit SteadyStateKalmanFilterCalculationElements(
    const boost::numeric::ublas::vector<double>& measurement = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::vector<double>& predicted_state = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::vector<double>& previous_state_estimate = boost::numeric::ublas::vector<double>(),
    const boost::numeric::ublas::vector<double>& updated_state = boost::numeric::ublas::vector<double>());

  ///Produce a deep copy of the derived class
  boost::shared_ptr<KalmanFilterCalculationElements> Clone() const;

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const { return KalmanFilterType::steady_state; }

  ///Checks if the state is complete and valid
  bool IsComplete() const;

  private:
  ///Can only be deleted by boost::checked_delete
  ~SteadyStateKalmanFilterCalculationElements() noexcept {}
  friend void boost::checked_delete<>(SteadyStateKalmanFilterCalculationElements*);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // STEADYSTATEKALMANFILTERCALCULATIONELEMENTS_H
