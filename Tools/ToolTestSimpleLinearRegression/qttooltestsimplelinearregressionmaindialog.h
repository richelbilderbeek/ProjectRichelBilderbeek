#ifndef QTTOOLTESTAPPROXIMATORMAINDIALOG_H
#define QTTOOLTESTAPPROXIMATORMAINDIALOG_H

#include <boost/shared_ptr.hpp>
#include "approximator.h"
#include "qthideandshowdialog.h"

struct QwtPlot;
struct QwtPlotCurve;

namespace Ui {
  class QtToolTestSimpleLinearRegressionMainDialog;
}

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

  std::vector<double> m_xs;
  std::vector<double> m_ys;

  ///Contains the plot
  const boost::shared_ptr<QwtPlot> m_plot;


  void Plot();
};

#endif // QTTOOLTESTAPPROXIMATORMAINDIALOG_H
