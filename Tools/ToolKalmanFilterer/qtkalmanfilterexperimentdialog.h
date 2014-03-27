#ifndef QTKALMANFILTEREXPERIMENTDIALOG_H
#define QTKALMANFILTEREXPERIMENTDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"
#include <QTableWidget>

#include "qwt_plot.h"

#include "kalmanfilterexperiment.h"
#include "kalmanfilterexperimentparametertype.h"
#include "qtkalmanfilterexamplesdialog.h"
#include "qtkalmanfilterdialog.h"
#include "qtwhitenoisesystemparametersdialog.h"
#include "qtkalmanfilterexperimentmodel.h"
#include "kalmanfilterexample.h"

#pragma GCC diagnostic pop

namespace Ui {
  class QtKalmanFilterExperimentDialog;
}

namespace ribi {
namespace kalman {

///QtKalmanFilterExperimentDialog is a Facade for
///the KalmanFilterExperiment parameters
class QtKalmanFilterExperimentDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  QtKalmanFilterExperimentDialog(const QtKalmanFilterExperimentDialog&) = delete;
  QtKalmanFilterExperimentDialog& operator=(const QtKalmanFilterExperimentDialog&) = delete;

  explicit QtKalmanFilterExperimentDialog(
    const boost::shared_ptr<QtKalmanFilterExperimentModel> model,
    QWidget *parent = 0);
  ~QtKalmanFilterExperimentDialog() noexcept;

  ///Click on an example
  void ClickExample(const int i);

  ///Get the dialog on which an predefined example can be selected
  const QtKalmanFilterExamplesDialog * GetExamplesDialog() const;
        QtKalmanFilterExamplesDialog * GetExamplesDialog();

  ///Get dialog to set up a Kalman filter
  const QtKalmanFilterDialog * GetFilterDialog() const { return m_filter_dialog; }

  ///Obtain the dialog to set the white noise system parameters with
  const QtWhiteNoiseSystemParametersDialog * GetNoiseParametersDialog() const { return m_noise_parameters_dialog; }
        QtWhiteNoiseSystemParametersDialog * GetNoiseParametersDialog()       { return m_noise_parameters_dialog; }

  ///Get the number of timesteps in the sim
  int GetNumberOfTimesteps() const;

  ///Load parameters from a file in DokuWiki format
  void LoadFromDokuWiki(const std::string& filename);

  ///Save the current parameters to a file in DokuWiki format
  void SaveToDokuWiki(const std::string& filename) const;

  ///Set the number of timesteps in the sim
  void SetNumberOfTimesteps(const int timesteps);

public slots:

  // Don't put a boost::shared_ptr in a signal [1]
  void SetExample(const KalmanFilterExample * const example);

  ///Called when the user changes to a different type of Kalman filter
  void SetKalmanFilterType(const KalmanFilterType new_type);

protected:
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtKalmanFilterExperimentDialog *ui;

  ///Dialog with buttons to load a preset example
  QtKalmanFilterExamplesDialog * const m_examples_dialog;

  ///The dialog to set up a Kalman filter
  QtKalmanFilterDialog * const m_filter_dialog;

  ///This model is intended to share with all other parameter classes
  const boost::shared_ptr<QtKalmanFilterExperimentModel> m_model;

  ///The dialog to set the white noise system parameters with
  QtWhiteNoiseSystemParametersDialog * const m_noise_parameters_dialog;

  ///The parameter type and its corresponding dialog, specific for an Experiment
  std::map<KalmanFilterExperimentParameterType,QtKalmanFiltererParameterDialog *> m_parameters;

  #ifndef NDEBUG
  ///Check the internal state of this class
  bool IsValid() const;
  #endif

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

  private slots:

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

} //~namespace kalman
} //~namespace ribi

#endif // QTKALMANFILTEREXPERIMENTDIALOG_H
