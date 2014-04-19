#ifndef QTSTANDARDKALMANFILTERERALGORITHMDIALOG_H
#define QTSTANDARDKALMANFILTERERALGORITHMDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include "qthideandshowdialog.h"
#include <QTableWidget>
#include "standardkalmanfiltercalculationelements.h"
#include "qtkalmanfiltercalculationdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtStandardKalmanFilterCalculationDialog;
}

namespace ribi {
namespace kalman {

class QtStandardKalmanFilterCalculationDialog : public QtKalmanFilterCalculationDialog
{
  Q_OBJECT
  
public:
  QtStandardKalmanFilterCalculationDialog(const QtStandardKalmanFilterCalculationDialog&) = delete;
  QtStandardKalmanFilterCalculationDialog operator=(const QtStandardKalmanFilterCalculationDialog&) = delete;

  explicit QtStandardKalmanFilterCalculationDialog(QWidget *parent = 0);
  ~QtStandardKalmanFilterCalculationDialog() noexcept;

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const { return KalmanFilterType::standard; }

  ///Display the calculation of an experiment at a certain timestep
  void ShowCalculation(const int t, const boost::shared_ptr<const KalmanFilterExperiment>& experiment);

protected:
  void SetTime(const int t);

private:
  Ui::QtStandardKalmanFilterCalculationDialog *ui;

  const std::vector<QTableWidget *> CollectMatrices() const;
  const std::vector<QTableWidget *> CollectVectors() const;

  void SetControl(const boost::numeric::ublas::matrix<double>& m);
  void SetIdentityMatrix(const int sz);
  void SetInput(const boost::numeric::ublas::vector<double>& m);
  void SetMeasurementNoiseEstimate(const boost::numeric::ublas::matrix<double>& m);
  void SetObservation(const boost::numeric::ublas::matrix<double>& m);
  void SetProcessNoiseEstimate(const boost::numeric::ublas::matrix<double>& m);
  void SetStateNames(const std::vector<std::string>& names);
  void SetStateTransition(const boost::numeric::ublas::matrix<double>& m);


  void SetInnovation(const boost::numeric::ublas::vector<double>& m);
  void SetInnovationCovariance(const boost::numeric::ublas::matrix<double>& m);
  void SetKalmanGain(const boost::numeric::ublas::matrix<double>& m);
  void SetMeasurement(const boost::numeric::ublas::vector<double>& m);
  void SetPredictedCovariance(const boost::numeric::ublas::matrix<double>& m);
  void SetPredictedState(const boost::numeric::ublas::vector<double>& m);
  void SetPreviousCovarianceEstimate(const boost::numeric::ublas::matrix<double>& m);
  void SetPreviousStateEstimate(const boost::numeric::ublas::vector<double>& m);

  void SetStandardCalculationElements(
    const boost::shared_ptr<const StandardKalmanFilterCalculationElements>& calculation_elements);

  void SetUpdatedCovariance(const boost::numeric::ublas::matrix<double>& m);
  void SetUpdatedState(const boost::numeric::ublas::vector<double>& m);


};

} //~namespace kalman
} //~namespace ribi

#endif // QTSTANDARDKALMANFILTERERALGORITHMDIALOG_H
