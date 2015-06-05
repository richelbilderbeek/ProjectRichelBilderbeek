#ifndef QTSTOCHASTICITYINSPECTORMAINDIALOG_H
#define QTSTOCHASTICITYINSPECTORMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "stochasticityinspectormaindialog.h"
#pragma GCC diagnostic pop

struct QwtPlotCurve;

namespace Ui {
  class QtStochasticityInspectorMainDialog;
}

struct QtBrownianMotionLikelihoodWidget;
struct QtBrownianMotionMaxLikelihoodWidget;
struct QtBrownianMotionParametersWidget;
struct QtOrnsteinUhlenbeckLikelihoodWidget;
struct QtOrnsteinUhlenbeckMaxLikelihoodWidget;
struct QtOrnsteinUhlenbeckParametersWidget;
struct QtStochasticityInspectorAicWidget;
struct QtStochasticityInspectorHlrtWidget;

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
  void OnNewData() noexcept; //New data is available to analyse

private:
  Ui::QtStochasticityInspectorMainDialog *ui;

  ///Akaike Information Criterion widget
  QtStochasticityInspectorAicWidget * const m_aic_widget;

  QtBrownianMotionLikelihoodWidget * const m_bm_likelihood_widget;
  QtBrownianMotionMaxLikelihoodWidget * const m_bm_max_likelihood_widget;
  QtBrownianMotionParametersWidget * const m_bm_parameters_widget;
  QwtPlotCurve * const m_curve;

  ///Hierarchical Likelihood Ratio Test widget
  QtStochasticityInspectorHlrtWidget * const m_hlrt_widget;

  ribi::StochasticityInspectorMainDialog m_main_dialog;

  QtOrnsteinUhlenbeckLikelihoodWidget * const m_ou_likelihood_widget;
  QtOrnsteinUhlenbeckMaxLikelihoodWidget * const m_ou_max_likelihood_widget;
  QtOrnsteinUhlenbeckParametersWidget * const m_ou_parameters_widget;

  ///Timepoints
  //std::vector<double> m_ts;

  ///Values measured in OU
  //std::vector<double> m_xs;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSTOCHASTICITYINSPECTORMAINDIALOG_H
