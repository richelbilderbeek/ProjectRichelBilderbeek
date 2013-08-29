#ifndef QTTOOLTESTAPPROXIMATORMAINDIALOG_H
#define QTTOOLTESTAPPROXIMATORMAINDIALOG_H

#include <boost/shared_ptr.hpp>
#include "approximator.h"
#include "qthideandshowdialog.h"

struct QwtPlot;
struct QwtPlotCurve;

namespace Ui {
  class QtToolTestApproximatorXyzMainDialog;
}

class QtToolTestApproximatorXyzMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtToolTestApproximatorXyzMainDialog(QWidget *parent = 0);
  ~QtToolTestApproximatorXyzMainDialog();
  
private slots:
  void on_button_clicked();

  void on_box_int_x_valueChanged(int arg1);

  void on_box_double_y_valueChanged(double arg1);

private:
  Ui::QtToolTestApproximatorXyzMainDialog *ui;
  typedef Approximator<double,Approximator<double,double> > Approximator_t;
  Approximator_t m_approximator;

  //const boost::shared_ptr<QwtPlotCurve> m_curve_approximation;
  //const boost::shared_ptr<QwtPlotCurve> m_curve_values;
  QwtPlotCurve * const m_curve_approximation;
  QwtPlotCurve * const m_curve_values;

  ///Contains the plots
  const boost::shared_ptr<QwtPlot> m_plot_z_high;
  const boost::shared_ptr<QwtPlot> m_plot_z_low;
  const boost::shared_ptr<QwtPlot> m_plot_z_mid; //To be estimated


  void Plot();
};

#endif // QTTOOLTESTAPPROXIMATORMAINDIALOG_H
