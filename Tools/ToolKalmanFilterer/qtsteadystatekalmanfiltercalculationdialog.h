#ifndef QTSTEADYSTATEKALMANFILTERCALCULATIONDIALOG_H
#define QTSTEADYSTATEKALMANFILTERCALCULATIONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include "qthideandshowdialog.h"
#include <QTableWidget>
#include "kalmanfilterexperiment.h"
#include "qtkalmanfiltercalculationdialog.h"
#include "steadystatekalmanfiltercalculationelements.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtSteadyStateKalmanFilterCalculationDialog;
}

namespace ribi {
namespace kalman {

class QtSteadyStateKalmanFilterCalculationDialog : public QtKalmanFilterCalculationDialog
{
  Q_OBJECT
  
public:
  QtSteadyStateKalmanFilterCalculationDialog(const QtSteadyStateKalmanFilterCalculationDialog&) = delete;
  QtSteadyStateKalmanFilterCalculationDialog& operator=(const QtSteadyStateKalmanFilterCalculationDialog&) = delete;

  explicit QtSteadyStateKalmanFilterCalculationDialog(QWidget *parent = 0);
  ~QtSteadyStateKalmanFilterCalculationDialog() noexcept;

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const { return KalmanFilterType::steady_state; }

  ///Display the calculation of an experiment at a certain timestep
  void ShowCalculation(const int t, const boost::shared_ptr<const KalmanFilterExperiment>& experiment);

protected:
  void SetTime(const int t);

private:
  Ui::QtSteadyStateKalmanFilterCalculationDialog *ui;

  void SetSteadyStateCalculationElements(const boost::shared_ptr<const SteadyStateKalmanFilterCalculationElements>& calculation_elements);

  void SetControl(const boost::numeric::ublas::matrix<double>& m);
  void SetEstimatedOptimalKalmanGain(const boost::numeric::ublas::matrix<double>& m);
  void SetInput(const boost::numeric::ublas::vector<double>& m);
  void SetObservation(const boost::numeric::ublas::matrix<double>& m);
  void SetStateNames(const std::vector<std::string>& names);
  void SetStateTransition(const boost::numeric::ublas::matrix<double>& m);

  void SetMeasurement(const boost::numeric::ublas::vector<double>& m);
  void SetPredictedState(const boost::numeric::ublas::vector<double>& m);
  void SetPreviousStateEstimate(const boost::numeric::ublas::vector<double>& m);

  const std::vector<QTableWidget *> CollectMatrices() const;
  const std::vector<QTableWidget *> CollectVectors() const;

};

} //~namespace kalman
} //~namespace ribi

#endif // QTSTEADYSTATEKALMANFILTERCALCULATIONDIALOG_H
