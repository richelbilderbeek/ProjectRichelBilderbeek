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

  void SetExample(const boost::shared_ptr<KalmanFilterExample> example);

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

#endif // QTKALMANFILTEREXPERIMENTDIALOG_H
