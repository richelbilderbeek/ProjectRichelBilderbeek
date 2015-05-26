#ifndef QTSTATEOBSERVERMAINDIALOG_H
#define QTSTATEOBSERVERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"
#include "stateobserverfwd.h"

#pragma GCC diagnostic pop

//struct LsqFilter;
//struct SlsqFilter;
//struct SymmetricLsqFilter;
struct QwtPlotCurve;

namespace Ui {
  class QtStateObserverMainDialog;
}

namespace ribi {

class QtStateObserverMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtStateObserverMainDialog(QWidget *parent = 0) noexcept;
  QtStateObserverMainDialog(const QtStateObserverMainDialog&) = delete;
  QtStateObserverMainDialog& operator=(const QtStateObserverMainDialog&) = delete;
  ~QtStateObserverMainDialog() noexcept;
  
private slots:
  const boost::shared_ptr<AlphaFilter> CreateAlphaFilter() const noexcept;
  const boost::shared_ptr<AlphaBetaFilter> CreateAlphaBetaFilter() const noexcept;
  const boost::shared_ptr<AlphaBetaGammaFilter> CreateAlphaBetaGammaFilter() const noexcept;
  const boost::shared_ptr<IntegerAlphaFilter> CreateLsqFilter() const noexcept;
  const boost::shared_ptr<IntegerSymmetricalAlphaFilter> CreateSlsqFilter() const noexcept;
  const boost::shared_ptr<MultiAlphaFilter> CreateMultiAlphaFilter() const noexcept;
  const boost::shared_ptr<MultiIntegerStateObserver> CreateMiso() const noexcept;
  double CreateDt() const noexcept { return 1.0; }

  void Run() noexcept;

  void on_button_rerun_clicked() noexcept;


private:
  Ui::QtStateObserverMainDialog *ui;

  QwtPlotCurve * const m_curve_inputs;
  QwtPlotCurve * const m_curve_outputs_alpha;
  QwtPlotCurve * const m_curve_outputs_alpha_beta;
  QwtPlotCurve * const m_curve_outputs_alpha_beta_gamma;
  QwtPlotCurve * const m_curve_outputs_lsq;
  QwtPlotCurve * const m_curve_outputs_slsq;
  QwtPlotCurve * const m_curve_outputs_ma;
  QwtPlotCurve * const m_curve_outputs_miso;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTSTATEOBSERVERMAINDIALOG_H
