#ifndef QTTOOLTESTAPPROXIMATORXYZMAINDIALOG_H
#define QTTOOLTESTAPPROXIMATORXYZMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <array>
#include <boost/shared_ptr.hpp>
#include "approximator.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QwtPlot;
struct QwtPlotCurve;

namespace Ui {
  class QtToolTestApproximatorXyzMainDialog;
}

namespace ribi {

class QtToolTestApproximatorXyzMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtToolTestApproximatorXyzMainDialog(QWidget *parent = 0) noexcept;
  QtToolTestApproximatorXyzMainDialog(const QtToolTestApproximatorXyzMainDialog&) = delete;
  QtToolTestApproximatorXyzMainDialog& operator=(const QtToolTestApproximatorXyzMainDialog&) = delete;
  ~QtToolTestApproximatorXyzMainDialog() noexcept;
  
private slots:
  void on_button_clicked() noexcept;
  void on_box_int_x_valueChanged(int arg1) noexcept;
  void on_box_double_y_valueChanged(double arg1) noexcept;
  void on_box_int_z_valueChanged(int arg1) noexcept;

private:
  Ui::QtToolTestApproximatorXyzMainDialog *ui;
  typedef double ApproximatorKey;
  typedef double ApproximatorValue;
  typedef Approximator<ApproximatorKey,Approximator<ApproximatorKey,ApproximatorValue> > Approximator_t;
  Approximator_t m_approximator;

  static const int m_n_curves = 3;
  typedef std::array<std::tuple<QwtPlotCurve *,QwtPlotCurve *,boost::shared_ptr<QwtPlot>>,m_n_curves> Data;
  Data m_data;

  static Data CreateData() noexcept;

  ///The line curve containing the continuous approximation
  QwtPlotCurve * GetCurveApproximation(const int i) noexcept;

  ///The dotted curve containing the raw data points
  QwtPlotCurve * GetCurveValues(const int i) noexcept;
  const boost::shared_ptr<QwtPlot> GetPlot(const int i) noexcept;

  void Plot() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTOOLTESTAPPROXIMATORXYZMAINDIALOG_H
