#ifndef QTTOOLTESTAPPROXIMATORMAINDIALOG_H
#define QTTOOLTESTAPPROXIMATORMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "approximator.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QwtPlot;
struct QwtPlotCurve;

namespace Ui {
  class QtToolTestSimpleLinearRegressionMainDialog;
}

namespace ribi {

class QtToolTestSimpleLinearRegressionMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtToolTestSimpleLinearRegressionMainDialog(QWidget *parent = 0);
  ~QtToolTestSimpleLinearRegressionMainDialog();
  
private slots:
  void on_button_clicked();

private:
  Ui::QtToolTestSimpleLinearRegressionMainDialog *ui;

  //const boost::shared_ptr<QwtPlotCurve> m_curve_approximation;
  //const boost::shared_ptr<QwtPlotCurve> m_curve_values;
  QwtPlotCurve * const m_curve_approximation;
  QwtPlotCurve * const m_curve_values;

  ///Contains the plot
  const boost::shared_ptr<QwtPlot> m_plot;

  std::vector<double> m_xs;
  std::vector<double> m_ys;

  void Plot();
};

} //~namespace ribi

#endif // QTTOOLTESTAPPROXIMATORMAINDIALOG_H
