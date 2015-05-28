#ifndef QTSTOCHASTICITYINSPECTORMAINDIALOG_H
#define QTSTOCHASTICITYINSPECTORMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QwtPlotCurve;

namespace Ui {
  class QtStochasticityInspectorMainDialog;
}

struct QtOrnsteinUhlenbeckParametersWidget;

namespace ribi {

class QtStochasticityInspectorMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtStochasticityInspectorMainDialog(QWidget *parent = 0) noexcept;
  QtStochasticityInspectorMainDialog(const QtStochasticityInspectorMainDialog&) = delete;
  QtStochasticityInspectorMainDialog& operator=(const QtStochasticityInspectorMainDialog&) = delete;
  ~QtStochasticityInspectorMainDialog() noexcept;
  
private slots:
  void OnAnyChange() noexcept;
  void OnCalculateLikelihood() noexcept;

private:
  Ui::QtStochasticityInspectorMainDialog *ui;

  QwtPlotCurve * const m_curve_ou;
  QtOrnsteinUhlenbeckParametersWidget * const m_ou_parameters_widget;

  ///Timepoints
  std::vector<double> m_ts;

  ///Values measured
  std::vector<double> m_xs;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSTOCHASTICITYINSPECTORMAINDIALOG_H
