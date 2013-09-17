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
  class QtToolTestApproximatorXyMainDialog;
}

namespace ribi {

class QtToolTestApproximatorXyMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtToolTestApproximatorXyMainDialog(QWidget *parent = 0) noexcept;
  QtToolTestApproximatorXyMainDialog(const QtToolTestApproximatorXyMainDialog&) = delete;
  QtToolTestApproximatorXyMainDialog& operator=(const QtToolTestApproximatorXyMainDialog&) = delete;
  ~QtToolTestApproximatorXyMainDialog() noexcept;
  
private slots:
  void on_button_clicked() noexcept;

  void on_box_int_x_valueChanged(int arg1) noexcept;

  void on_box_double_y_valueChanged(double arg1) noexcept;

private:
  Ui::QtToolTestApproximatorXyMainDialog *ui;
  typedef Approximator<double,double> Approximator_t;

  Approximator_t m_approximator;

  //const boost::shared_ptr<QwtPlotCurve> m_curve_approximation;
  //const boost::shared_ptr<QwtPlotCurve> m_curve_values;
  QwtPlotCurve * const m_curve_approximation;
  QwtPlotCurve * const m_curve_values;

  ///Contains the plot
  const boost::shared_ptr<QwtPlot> m_plot;


  void Plot() noexcept;
};

} //~namespace ribi

#endif // QTTOOLTESTAPPROXIMATORMAINDIALOG_H
