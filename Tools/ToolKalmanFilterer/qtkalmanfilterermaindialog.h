#ifndef QTKALMANFILTERERMAINDIALOG_H
#define QTKALMANFILTERERMAINDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include <QDialog>
#include <QTableWidget>

#include "qwt_plot.h"

///NEVER FORGET: Do never use forward declarations in header files parsed by MOC
#include "kalmanfilterexperiment.h"
#include "qthideandshowdialog.h"
#include "qtkalmanfilterexperimentdialog.h"
#include "qtstandardkalmanfiltercalculationdialog.h"
#include "qtsteadystatekalmanfiltercalculationdialog.h"
#include "qtwhitenoisesystemparametersdialog.h"

namespace Ui {
  class QtKalmanFiltererMainDialog;
}

class QtKalmanFiltererMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtKalmanFiltererMainDialog(
    const boost::shared_ptr<QtKalmanFilterExperimentModel> model,
    QWidget *parent = 0);
  ~QtKalmanFiltererMainDialog();

  ///Set the checkbox to show the calculation
  void SetShowCalculations(const bool do_show);

  ///Set the checkbox to show the graphs
  void SetShowGraphs(const bool do_show);

  ///Create a QtKalmanFiltererMainDialog
  static boost::shared_ptr<QtKalmanFiltererMainDialog> Create();

protected:
  void keyPressEvent(QKeyEvent * event);
  
private:
  Ui::QtKalmanFiltererMainDialog *ui;

  QtKalmanFilterExperimentDialog * const m_experiment_dialog;

  ///The model
  const boost::shared_ptr<QtKalmanFilterExperimentModel> m_model;

  ///Plot an experiment
  void Plot(const boost::shared_ptr<const KalmanFilterExperiment>& experiment);

  ///Contains the plots, these must be stored because deleting
  ///the layout that contains these does not work properly
  std::vector<boost::shared_ptr<QwtPlot> > m_plots;

  ///Contains the calculations, these must be stored because deleting
  ///the layout that contains these does not work properly
  std::vector<boost::shared_ptr<QtKalmanFilterCalculationDialog> > m_calculations;

private slots:

  static const std::vector<std::vector<double> > CreateData(
    const std::vector<boost::numeric::ublas::vector<double> >& a,
    const std::vector<boost::numeric::ublas::vector<double> >& b,
    const std::vector<boost::numeric::ublas::vector<double> >& c,
    const std::vector<boost::numeric::ublas::vector<double> >& d
    );

  const boost::shared_ptr<QtKalmanFilterCalculationDialog> CreateKalmanFilterCalculationDialog(
    const KalmanFilterType type) const;

  void on_button_start_clicked();

  ///Show the calculation of a StandardKalmanFilterExperiment
  void ShowCalculationExperiment(
    const boost::shared_ptr<const KalmanFilterExperiment>& experiment);

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};

#endif // QTKALMANFILTERERMAINDIALOG_H
