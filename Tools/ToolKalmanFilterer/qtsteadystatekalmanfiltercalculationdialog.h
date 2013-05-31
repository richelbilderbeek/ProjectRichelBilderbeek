#ifndef QTSTEADYSTATEKALMANFILTERCALCULATIONDIALOG_H
#define QTSTEADYSTATEKALMANFILTERCALCULATIONDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <QDialog>

///NEVER FORGET: Do never use forward declarations in header files parsed by MOC
#include <QTableWidget>
#include "kalmanfilterexperiment.h"
#include "qtkalmanfiltercalculationdialog.h"
#include "steadystatekalmanfiltercalculationelements.h"

namespace Ui {
  class QtSteadyStateKalmanFilterCalculationDialog;
}

class QtSteadyStateKalmanFilterCalculationDialog : public QtKalmanFilterCalculationDialog
{
  Q_OBJECT
  
public:
  explicit QtSteadyStateKalmanFilterCalculationDialog(QWidget *parent = 0);
  ~QtSteadyStateKalmanFilterCalculationDialog();

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

#endif // QTSTEADYSTATEKALMANFILTERCALCULATIONDIALOG_H
