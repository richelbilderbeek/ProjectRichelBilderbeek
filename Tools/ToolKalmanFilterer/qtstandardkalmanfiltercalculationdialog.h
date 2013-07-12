#ifndef QTSTANDARDKALMANFILTERERALGORITHMDIALOG_H
#define QTSTANDARDKALMANFILTERERALGORITHMDIALOG_H

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
#include "standardkalmanfiltercalculationelements.h"
#include "qtkalmanfiltercalculationdialog.h"

namespace Ui {
  class QtStandardKalmanFilterCalculationDialog;
}

class QtStandardKalmanFilterCalculationDialog : public QtKalmanFilterCalculationDialog
{
  Q_OBJECT
  
public:
  explicit QtStandardKalmanFilterCalculationDialog(QWidget *parent = 0);
  ~QtStandardKalmanFilterCalculationDialog();

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

#endif // QTSTANDARDKALMANFILTERERALGORITHMDIALOG_H
