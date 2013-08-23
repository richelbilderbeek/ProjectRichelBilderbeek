#ifndef QTTOOLTESTMULTIAPPROXIMATORMAINDIALOG_H
#define QTTOOLTESTMULTIAPPROXIMATORMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "multiapproximator.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QwtPlot;
struct QwtPlotCurve;

namespace Ui {
  class QtToolTestMultiApproximatorMainDialog;
}

class QtToolTestMultiApproximatorMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtToolTestMultiApproximatorMainDialog(QWidget *parent = 0);
  ~QtToolTestMultiApproximatorMainDialog();
  
private slots:
  void on_button_clicked();

private:
  Ui::QtToolTestMultiApproximatorMainDialog *ui;
  typedef MultiApproximator<double,double> MultiApproximator_t;
  MultiApproximator_t m_approximator;

  //const boost::shared_ptr<QwtPlotCurve> m_curve_approximation;
  //const boost::shared_ptr<QwtPlotCurve> m_curve_values;
  QwtPlotCurve * const m_curve_approximation;
  QwtPlotCurve * const m_curve_values;

  ///Contains the plot
  const boost::shared_ptr<QwtPlot> m_plot;


  void Plot();
};

#endif // QTTOOLTESTMULTIAPPROXIMATORMAINDIALOG_H
