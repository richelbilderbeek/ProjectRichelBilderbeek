#ifndef QTKALMANFILTEREXPERIMENTDIALOG_H
#define QTKALMANFILTEREXPERIMENTDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <vector>

#include <boost/shared_ptr.hpp>
//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/vector.hpp>
#include <boost/signals2.hpp>

#include <QDialog>
#include <QTableWidget>

#include "qwt_plot.h"

///NEVER FORGET: Do never use forward declarations in header files parsed by MOC
//#include "qtmatrix.h"
#include "kalmanfilterexperiment.h"
#include "kalmanfilterexperimentparametertype.h"
#include "qtkalmanfilterexamplesdialog.h"
#include "qtkalmanfilterdialog.h"
#include "qtwhitenoisesystemparametersdialog.h"
#include "qtkalmanfilterexperimentmodel.h"
#include "kalmanfilterexample.h"

namespace Ui {
  class QtKalmanFilterExperimentDialog;
}

///QtKalmanFilterExperimentDialog is a Facade for
///the KalmanFilterExperiment parameters
class QtKalmanFilterExperimentDialog : public QDialog
{
  Q_OBJECT

  
public:
  explicit QtKalmanFilterExperimentDialog(
    const boost::shared_ptr<QtKalmanFilterExperimentModel> model,
    QWidget *parent = 0);
  ~QtKalmanFilterExperimentDialog();

  ///Click on an example
  void ClickExample(const int i);

  ///Load parameters from a file in DokuWiki format
  void LoadFromDokuWiki(const std::string& filename);

  ///Save the current parameters to a file in DokuWiki format
  void SaveToDokuWiki(const std::string& filename) const;

  boost::signals2::signal <void()> m_signal_new_parameters;

private:
  Ui::QtKalmanFilterExperimentDialog *ui;

  QtKalmanFilterExamplesDialog * const m_examples_dialog;
  QtKalmanFilterDialog * const m_filter_dialog;

  ///This model is intended to share with all other parameter classes
  const boost::shared_ptr<QtKalmanFilterExperimentModel> m_model;

  QtWhiteNoiseSystemParametersDialog * const m_noise_parameters_dialog;

  ///The parameter type and its corresponding dialog, specific for an Experiment
  std::map<KalmanFilterExperimentParameterType,QtKalmanFiltererParameterDialog *> m_parameters;

  ///Set the number of timesteps in the sim
  void SetTimesteps(const int timesteps);

private slots:

  // Don't put a boost::shared_ptr in a signal [1]
  void SetExample(const KalmanFilterExample * const example);

  ///Called when the user changes to a different type of Kalman filter
  void SetKalmanFilterType(const KalmanFilterType new_type);

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
  void on_box_n_timesteps_valueChanged(int arg1);
  void on_button_save_clicked();
  void on_button_load_clicked();
  void on_button_add_state_clicked();
  void on_button_remove_state_clicked();
};

// [1] Don't put a boost::shared_ptr in a signal as it will be
//     reinterpret_cast-ed by the MOC:
//
// void QtKalmanFilterExperimentDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
// {
//     if (_c == QMetaObject::InvokeMetaMethod) {
//         Q_ASSERT(staticMetaObject.cast(_o));
//         QtKalmanFilterExperimentDialog *_t = static_cast<QtKalmanFilterExperimentDialog *>(_o);
//         switch (_id) {
//         case 0: _t->SetExample((*reinterpret_cast< const boost::shared_ptr<KalmanFilterExample>(*)>(_a[1]))); break;
//         //...
//         default: ;
//         }
//     }
// }
//
// Additionally, #include the KalmanFilterExample header file in the dialog its header file:
// I have the hypothesis that
//

#endif // QTKALMANFILTEREXPERIMENTDIALOG_H
