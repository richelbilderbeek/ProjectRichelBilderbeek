#ifndef QTFIXEDLAGSMOOTHERKALMANFILTERCALCULATIONDIALOG_H
#define QTFIXEDLAGSMOOTHERKALMANFILTERCALCULATIONDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#pragma GCC diagnostic pop

#include <QDialog>

///NEVER FORGET: Do never use forward declarations in header files parsed by MOC
#include <QTableWidget>
#include "kalmanfilterexperiment.h"
#include "qtkalmanfiltercalculationdialog.h"
#include "fixedlagsmootherkalmanfiltercalculationelements.h"

namespace Ui {
  class QtFixedLagSmootherKalmanFilterCalculationDialog;
}

class QtFixedLagSmootherKalmanFilterCalculationDialog : public QtKalmanFilterCalculationDialog
{
  Q_OBJECT
  
public:
  explicit QtFixedLagSmootherKalmanFilterCalculationDialog(QWidget *parent = 0);
  ~QtFixedLagSmootherKalmanFilterCalculationDialog();

  ///Obtain the Kalman filter type as an enum
  KalmanFilterType GetType() const { return KalmanFilterType::fixed_lag_smoother; }

  ///Display the calculation of an experiment at a certain timestep
  void ShowCalculation(const int t, const boost::shared_ptr<const KalmanFilterExperiment>& experiment);

protected:
  void SetTime(const int t);

private:
  Ui::QtFixedLagSmootherKalmanFilterCalculationDialog *ui;

  void SetFixedLagSmootherCalculationElements(const boost::shared_ptr<const FixedLagSmootherKalmanFilterCalculationElements>& calculation_elements);

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

#endif // QTFIXEDLAGSMOOTHERKALMANFILTERCALCULATIONDIALOG_H
