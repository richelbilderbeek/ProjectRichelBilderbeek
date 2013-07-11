#ifndef QTKALMANFILTERDIALOG
#define QTKALMANFILTERDIALOG

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

#include <map>
#include <vector>

#include <QDialog>
#include <QTableWidget>

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

///NEVER FORGET: Do never use forward declarations in header files parsed by MOC
#include "kalmanfilter.h"
#include "kalmanfiltertype.h"
#include "kalmanfilterparametertype.h"
#include "standardkalmanfilterparameters.h"
#include "steadystatekalmanfilterparameters.h"
#include "qtkalmanfilterexperimentmodel.h"
#include "qtkalmanfiltererparameterdialog.h"

namespace Ui {
  class QtKalmanFilterDialog;
}

///QtKalmanFilterDialog is a Facade of multiple QtKalmanFiltererParameterDialog instances
///with the KalmanFilterType as its primary State
class QtKalmanFilterDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtKalmanFilterDialog(
    const boost::shared_ptr<QtKalmanFilterExperimentModel> model,
    QWidget *parent = 0);
  ~QtKalmanFilterDialog();

  ///Obtain the Kalman filter type the user works on
  KalmanFilterType GetKalmanFilterType() const;

  ///Set the tab to the correct index
  void SetKalmanFilterType(const KalmanFilterType new_type);

  mutable boost::signals2::signal<void(const KalmanFilterType)> m_signal_kalman_filter_type_changed;

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtKalmanFilterDialog *ui;

  ///The model
  const boost::shared_ptr<QtKalmanFilterExperimentModel> m_model;

  ///The parameter type and its corresponding dialog
  std::map<KalmanFilterParameterType,QtKalmanFiltererParameterDialog *> m_parameters;

  ///Obtain the all KalmanFilterParameterType values, ordered for humans
  const std::vector<KalmanFilterParameterType> GetParameterTypes() const;

private slots:

  void on_button_calculate_optimal_kalman_gain_steady_state_clicked();

  void on_box_filter_type_currentIndexChanged(int index);

};

#endif // QTKALMANFILTERDIALOG
