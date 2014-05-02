#ifndef KALMANFILTERCALCULATIONELEMENTS_H
#define KALMANFILTERCALCULATIONELEMENTS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

#include "kalmanfiltertype.h"

namespace ribi {
namespace kalman {

///The elements of a steady-state Kalman filter calculation
struct KalmanFilterCalculationElements
{
  KalmanFilterCalculationElements(const KalmanFilterCalculationElements&) = delete;
  KalmanFilterCalculationElements& operator=(const KalmanFilterCalculationElements&) = delete;


  virtual ~KalmanFilterCalculationElements() noexcept {}

  ///Clear the calculation, will set IsComplete to false
  virtual void Clear();

  ///Obtain the measurement ('z_n')
  const boost::numeric::ublas::vector<double>& GetMeasurement() const;

  ///Get the predicted state ('x_predicted')
  ///Is calculated at step 1 of the algorithm:
  ///x_predicted = [...] x_n-1 [...]
  const boost::numeric::ublas::vector<double>& GetPredictedState() const;

  ///Obtain the previous_state_estimate ('x_prev')
  const boost::numeric::ublas::vector<double>& GetPreviousState() const;

  ///Obtain the updated state ('x_n')
  const boost::numeric::ublas::vector<double>& GetUpdatedState() const;

  ///Obtain the Kalman filter type as an enum
  virtual KalmanFilterType GetType() const = 0;

  ///Checks if the state is complete and valid
  virtual bool IsComplete() const;

  ///Set the measurement ('z_n')
  ///Fails if already set
  void SetMeasurement(const boost::numeric::ublas::vector<double>& measurement);

  ///Set the predicted state ('x_predicted')
  ///Is calculated at step 1 of the algorithm:
  ///x_predicted = [...] x_n-1 [...]
  ///Fails if already set
  void SetPredictedState(const boost::numeric::ublas::vector<double>& predicted_state);

  ///Set the previous_state_estimate ('x_prev'/'x_n-1')
  ///Is read at step 1 of the algorithm:
  ///x_predicted = [...] x_n-1 [...]
  ///Fails if already set
  void SetPreviousStateEstimate(const boost::numeric::ublas::vector<double>& previous_state_estimate);

  ///Set the updated state ('x_n')
  ///Is calculated at step 6 of the algorithm:
  ///x_n = x_predicted + [...]
  ///Fails if already set
  void SetUpdatedState(const boost::numeric::ublas::vector<double>& updated_state);

  protected:
  ///An ABC can only be constructed by derived classes
  explicit KalmanFilterCalculationElements(
    const boost::numeric::ublas::vector<double>& measurement,
    const boost::numeric::ublas::vector<double>& predicted_state,
    const boost::numeric::ublas::vector<double>& previous_state_estimate,
    const boost::numeric::ublas::vector<double>& updated_state);

  private:
  ///Produce a deep copy of the derived class
  virtual boost::shared_ptr<KalmanFilterCalculationElements> Clone() const = 0;
  friend class KalmanFilterCalculationElementsFactory;

  private:
  ///The measurement ('z_n')
  boost::numeric::ublas::vector<double> m_measurement;

  ///The predicted state ('x_predicted')
  boost::numeric::ublas::vector<double> m_predicted_state;

  ///The previous_state_estimate ('x_prev')
  boost::numeric::ublas::vector<double> m_previous_state_estimate;

  ///The updated state ('x_n')
  boost::numeric::ublas::vector<double> m_updated_state;
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTERCALCULATIONELEMENTS_H
