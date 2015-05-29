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
struct QtOrnsteinUhlenbeckLikelihoodWidget;
struct QtBrownianMotionParametersWidget;

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
  void OnAnyChangeBrownian() noexcept;
  void OnAnyChangeOrnsteinUhlenbeck() noexcept;
  void OnCalculateLikelihood() noexcept;

private:
  Ui::QtStochasticityInspectorMainDialog *ui;

  QtBrownianMotionParametersWidget * const m_bm_parameters_widget;
  QwtPlotCurve * const m_curve_bm;
  QwtPlotCurve * const m_curve_ou;
  QtOrnsteinUhlenbeckLikelihoodWidget * const m_ou_likelihood_widget;
  QtOrnsteinUhlenbeckParametersWidget * const m_ou_parameters_widget;

  ///Timepoints
  std::vector<double> m_ts;

  ///Values measured in OU
  std::vector<double> m_xs_bm;
  std::vector<double> m_xs_ou;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSTOCHASTICITYINSPECTORMAINDIALOG_H
