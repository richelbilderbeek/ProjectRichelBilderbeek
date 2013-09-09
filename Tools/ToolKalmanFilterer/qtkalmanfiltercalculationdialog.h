#ifndef QTKALMANFILTERCALCULATIONDIALOG_H
#define QTKALMANFILTERCALCULATIONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#pragma GCC diagnostic pop

#include <QDialog>

#include <QTableWidget>
#include "kalmanfilterexperiment.h"

namespace Ui {
  class QtKalmanFilterCalculationDialog;
}

namespace ribi {
namespace kalman {

class QtKalmanFilterCalculationDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtKalmanFilterCalculationDialog(QWidget *parent = 0);
  virtual ~QtKalmanFilterCalculationDialog();

  ///Obtain the Kalman filter type as an enum
  virtual KalmanFilterType GetType() const = 0;

  virtual void SetTime(const int t) = 0;

  ///Display the calculation of an experiment at a certain timestep
  virtual void ShowCalculation(const int t, const boost::shared_ptr<const KalmanFilterExperiment>& experiment) = 0;

private:
  Ui::QtKalmanFilterCalculationDialog *ui;
};

} //~namespace kalman
} //~namespace ribi

#endif // QTKALMANFILTERCALCULATIONDIALOG_H
