#ifndef QTKALMANFILTERDIALOG
#define QTKALMANFILTERDIALOG

#include <map>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qthideandshowdialog.h"
#include <QTableWidget>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#pragma GCC diagnostic pop

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

namespace ribi {
namespace kalman {

///QtKalmanFilterDialog is a Facade of multiple QtKalmanFiltererParameterDialog instances
///with the KalmanFilterType as its primary State
class QtKalmanFilterDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  QtKalmanFilterDialog(const QtKalmanFilterDialog&) = delete;
  QtKalmanFilterDialog& operator=(const QtKalmanFilterDialog&) = delete;

  explicit QtKalmanFilterDialog(
    const boost::shared_ptr<QtKalmanFilterExperimentModel> model,
    QWidget *parent = 0);
  ~QtKalmanFilterDialog() noexcept;

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

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_button_calculate_optimal_kalman_gain_steady_state_clicked();
  void on_box_filter_type_currentIndexChanged(int index);

};

} //~namespace kalman
} //~namespace ribi

#endif // QTKALMANFILTERDIALOG
